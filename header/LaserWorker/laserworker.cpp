#include "laserworker.h"
#include "logger.h"
#include <RTC5expl.h>
#include <QThread>

void LaserWorker::run()
{
    std::call_once(_startOnce, [this]() {
        _workerIsRunning = true;
        _thread = std::thread(&LaserWorker::threadMain, this);
        INFO_MSG("laserworker thread start");
    });
}

void LaserWorker::stop()
{
    _workerIsRunning = false;
    RTC5close();
}

void LaserWorker::postCommand(const LaserCommand &cmd)
{
    INFO_MSG("post command start");
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _commandQueue.push(cmd);
    }
    _cv.notify_one();
    INFO_MSG("post command end");
}

// Definition of "pi"
const double Pi = 3.14159265358979323846;
// Change these values according to your system
const UINT DefaultCard = 1;     //  number of default card
const UINT ListMemory = 10000;  //  size of list 1 memory (default 4000)
const UINT LaserMode = 1;       //  YAG 1 mode
const UINT LaserControl = 0x18; //  Laser signals LOW active (Bits #3 and #4)
const UINT StartGap = 1000;     //  gap ahead between input_pointer and out_pointer
const UINT LoadGap = 100;       //  gap ahead between out_pointer and input_pointer
const UINT PointerCount = 0x3F; //  pointer mask for checking the gap
// RTC4 compatibility mode assumed
const UINT AnalogOutChannel = 1;       //  AnalogOut Channel 1 used
const UINT AnalogOutValue = 640;       //  Standard Pump Source Value
const UINT AnalogOutStandby = 0;       //  Standby Pump Source Value
const UINT WarmUpTime = 2000000 / 10;  //    2  s [10 us]
const UINT LaserHalfPeriod = 50 * 8;   //   50 us [1/8 us] must be at least 13
const UINT LaserPulseWidth = 5 * 8;    //    5 us [1/8 us]
const UINT FirstPulseKiller = 200 * 8; //  200 us [1/8 us]
const long LaserOnDelay = 100 * 1;     //  100 us [1 us]
const UINT LaserOffDelay = 100 * 1;    //  100 us [1 us]
const UINT JumpDelay = 250 / 10;       //  250 us [10 us]
const UINT MarkDelay = 100 / 10;       //  100 us [10 us]
const UINT PolygonDelay = 50 / 10;     //   50 us [10 us]
const double MarkSpeed = 250.0;        //  [16 Bits/ms]
const double JumpSpeed = 1000.0;       //  [16 Bits/ms]
// Spiral Parameters
const double Amplitude = 10000.0;
const double Period = 512.0; // amount of vectors per turn
const double Omega = 2.0 * Pi / Period;
// End Locus of a Line
struct locus
{
    long xval, yval;
};
const locus BeamDump = {-32000, -32000}; //  Beam Dump Location

void LaserWorker::loadDLL()
{
    if (RTC5open()) {
        WARN_MSG("RTC5DLL.DLL not found");
        throw std::runtime_error("RTC5 DLL load failed.");
    }
    INFO_MSG("RTC5DLL.DLL is loaded");
}

void LaserWorker::connectCard()
{
    _cardIsConnected = false;

    UINT ErrorCode;
    //  This function must be called at the very first
    ErrorCode = init_rtc5_dll();

    if (ErrorCode) // =1
    {
        const UINT RTC5CountCards = rtc5_count_cards(); //  number of cards found

        if (RTC5CountCards) {
            UINT AccError(0);

            //  Error analysis in detail
            for (UINT i = 1; i <= RTC5CountCards; i++) {
                const UINT Error = n_get_last_error(i);

                if (Error != 0) {
                    AccError |= Error;
                    WARN_MSG("card no." + QString::number(i));
                    WARN_MSG("error:" + QString::number(DefaultCard));
                    n_reset_error(i, Error);
                }
            }

            if (AccError) {
                free_rtc5_dll();
                return;
            } else {
                INFO_MSG("success??");
            }

        } else {
            WARN_MSG(" no card deteceted");
            free_rtc5_dll();
            return;
        }

    } else // =0
    {
        if (DefaultCard != select_rtc(DefaultCard)) //  use card no. 1 as default,
        {
            ErrorCode = n_get_last_error(DefaultCard);

            if (ErrorCode & 256) //  RTC5_VERSION_MISMATCH
            {
                //  In this case load_program_file(0) would not work.
                ErrorCode = n_load_program_file(DefaultCard, 0); //  current working path

            } else {
                WARN_MSG("No acces to card no." + QString::number(DefaultCard));
                free_rtc5_dll();
                return;
            }

            if (ErrorCode) {
                WARN_MSG("No acces to card no." + QString::number(DefaultCard));
                free_rtc5_dll();
                return;

            } else { //  n_load_program_file was successfull
                (void) select_rtc(DefaultCard);
                INFO_MSG("success??");
            }
        }
    }

    set_rtc4_mode(); //  for RTC4 compatibility

    // Initialize the RTC5
    stop_execution();
    //  If the DefaultCard has been used previously by another application
    //  a list might still be running. This would prevent load_program_file
    //  and load_correction_file from being executed.
    ErrorCode = load_program_file(0); //  path = current working path

    if (ErrorCode) {
        WARN_MSG("Program file loading error:" + QString::number(ErrorCode));
        free_rtc5_dll();
        return;
    }

    ErrorCode = load_correction_file(0,  // initialize like "D2_1to1.ct5",
                                     1,  // table; #1 is used by default
                                     2); // use 2D only
    if (ErrorCode) {
        WARN_MSG("Correction file loading error:" + QString::number(ErrorCode));
        free_rtc5_dll();
        return;
    }

    select_cor_table(1, 0); //  table #1 at primary connector (default)

    //  stop_execution might have created a RTC5_TIMEOUT error
    reset_error(-1); //  clear all previous error codes

    _cardIsConnected = true;
    INFO_MSG("RTC5 card is connected.");
}

void LaserWorker::threadMain()
{
    // 先加载dll
    loadDLL();
    //
    while (_workerIsRunning) {
        // 取出命令
        LaserCommand cmd;
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _cv.wait(lock, [&] {
                return !_commandQueue.empty() || !_workerIsRunning;
            }); // 等待有命令或退出
            if (!_workerIsRunning && _commandQueue.empty())
                break;
            cmd = std::move(_commandQueue.front());
            _commandQueue.pop();
        }
        // 执行命令(每次执行前连接一下卡判断卡有没有连接上,没有连接就跳过执行)
        connectCard();
        if (!_cardIsConnected) {
            WARN_MSG("can not connect card");
            continue;
        }
        handleCommand(cmd);
    }
    INFO_MSG("laserworker thread end");
}

void LaserWorker::handleCommand(const LaserCommand &cmd)
{
    INFO_MSG("handle command start");
    if (cmd.type == LaserCommandType::ConnectCard) {
        connectCard();
        return;
    }
    INFO_MSG("handle command end");
}

///
/// \brief LaserWorker::ins
///
LaserWorker LaserWorker::ins;

LaserWorker &LaserWorker::getIns()
{
    return ins;
}

LaserWorker::~LaserWorker()
{
    stop();
    if (_thread.joinable()) {
        _thread.join();
    }
}
