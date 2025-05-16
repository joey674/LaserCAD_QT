#include "laserworker.h"
#include <QThread>

#include "logger.h"
#include <RTC5expl.h>

void LaserWorker::startLaserWorker()
{
    std::call_once(m_startOnce, [this]() {
        m_workerIsRunning = true;
        m_thread = std::thread(&LaserWorker::threadMain, this);
        INFO_MSG("laserworker thread start");
    });
}

void LaserWorker::stopLaserWorker()
{
    m_workerIsRunning = false;
    RTC5close();
}

///
/// \brief LaserWorker::loadDLL
///
void LaserWorker::threadMain()
{
    // 先加载dll/连接卡
    loadDLL();
    connectCard();
    while (m_workerIsRunning) {
        RTC5State state = m_RTC5State.load();

        if (state == RTC5State::Working) {
            RTC5Command cmd;
            if (m_RTC5CommandQueue.try_pop(cmd)) {
                while (executeRTC5Command(cmd) == false) {
                    // 这里返回false可能是rtc5的list满了, 需要等待;
                    WARN_MSG("can not execute rtc5 command; will try again");
                    // 如果在等待的时候有紧急命令也可以响应
                    if (state == RTC5State::Paused) {
                        pauseRTC5Command();
                        break;
                    }

                    if (state == RTC5State::Stopped) {
                        break;
                    }
                };
            }
            continue;
        }
        // 正常打完点时出现的紧急命令响应
        else if (state == RTC5State::Paused) {
            pauseRTC5Command();
            continue;
        } else if (state == RTC5State::Stopped) {
            continue;
        } else {
            continue;
        }
    }
}

///
/// \brief LaserWorker::test code: 不引入库, 只是用自身框架
///
void LaserWorker::loadDLL()
{
    if (RTC5open()) {
        WARN_MSG("RTC5DLL.DLL not found");
        throw std::runtime_error("RTC5 DLL load failed.");
    }
    INFO_MSG("RTC5DLL.DLL is loaded");
}

bool LaserWorker::connectCard()
{
    return true;
}

bool LaserWorker::checkCard()
{
    INFO_MSG("RTC5 has no error");
    return true;
}

bool LaserWorker::executeRTC5Command(const RTC5Command &cmd)
{
    std::visit(
        [](const auto &cmd) {
            using T = std::decay_t<decltype(cmd)>;

            if constexpr (std::is_same_v<T, JumpCommand>) {
                INFO_MSG(" jump_abs " + QString::number(cmd.pos.xval) + " "
                         + QString::number(cmd.pos.yval));
                // jump_abs(cmd.pos.xval, cmd.pos.yval);
            } else if constexpr (std::is_same_v<T, MarkCommand>) {
                INFO_MSG(" mark_abs " + QString::number(cmd.pos.xval) + " "
                         + QString::number(cmd.pos.yval));
                // mark_abs(cmd.pos.xval, cmd.pos.yval);
            } else if constexpr (std::is_same_v<T, SetLaserPulsesCommand>) {
                INFO_MSG(" set_laser_pulses " + QString::number(cmd.halfPeriod) + " "
                         + QString::number(cmd.pulseWidth));
                // set_laser_pulses(cmd.halfPeriod, cmd.pulseWidth);
            } else if constexpr (std::is_same_v<T, SetScannerDelaysCommand>) {
                INFO_MSG(" set_scanner_delays " + QString::number(cmd.jumpDelay) + " "
                         + QString::number(cmd.markDelay) + " " + QString::number(cmd.polygonDelay));
                // set_scanner_delays(cmd.jumpDelay, cmd.markDelay, cmd.polygonDelay);
            } else if constexpr (std::is_same_v<T, SetLaserDelaysCommand>) {
                INFO_MSG(" set_laser_delays " + QString::number(cmd.laserOnDelay) + " "
                         + QString::number(cmd.laserOffDelay));
                // set_laser_delays(cmd.laserOnDelay, cmd.laserOffDelay);
            } else if constexpr (std::is_same_v<T, SetJumpSpeedCommand>) {
                INFO_MSG(" set_jump_speed " + QString::number(cmd.jumpSpeed));
                // set_jump_speed(cmd.jumpSpeed);
            } else if constexpr (std::is_same_v<T, SetMarkSpeedCommand>) {
                INFO_MSG(" set_mark_speed " + QString::number(cmd.markSpeed));
                // set_mark_speed(cmd.markSpeed);
            } else if constexpr (std::is_same_v<T, LongDelayCommand>) {
                INFO_MSG(" long_delay " + QString::number(cmd.time));
                // long_delay(cmd.time);
            }
        },
        cmd);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return true;
}

bool LaserWorker::pauseRTC5Command()
{
    return true;
}

/* void LaserWorker::loadDLL()
{
    if (RTC5open()) {
        WARN_MSG("RTC5DLL.DLL not found");
        throw std::runtime_error("RTC5 DLL load failed.");
    }
    INFO_MSG("RTC5DLL.DLL is loaded");
}

bool LaserWorker::connectCard()
{
    // 判断rtc dll初始化是否成功
    UINT ErrorCode = init_rtc5_dll();
    if (ErrorCode != RTC5_NO_ERROR) {
        if (ErrorCode & RTC5_NO_CARD) {
            PRINT_RTC5_ERROR_INFO(ErrorCode);
        } else {
            const UINT RTC5CountCards = rtc5_count_cards(); //  number of cards found
            UINT AccError(0);
            //  Error analysis in detail
            for (UINT i = 1; i <= RTC5CountCards; i++) {
                const UINT Error = n_get_last_error(i);
                
                if (Error != RTC5_NO_ERROR) {
                    AccError |= Error;
                    PRINT_RTC5_ERROR_INFO(Error);
                    n_reset_error(i, Error);
                }
            }
            if (AccError != RTC5_NO_ERROR) {
                PRINT_RTC5_ERROR_INFO(AccError);
            }
        }
        free_rtc5_dll();
        return false;
    }
    
    // 说明选择卡是否成功
    if (DefaultCard != select_rtc(DefaultCard)) {
        ErrorCode = n_get_last_error(DefaultCard);
        if (ErrorCode & RTC5_VERSION_MISMATCH) {
            //  In this case load_program_file(0) would not work.
            ErrorCode = n_load_program_file(DefaultCard, 0); //  current working path
        } else {
            PRINT_RTC5_ERROR_INFO(ErrorCode);
            free_rtc5_dll();
            return false;
        }
        
        if (ErrorCode != RTC5_NO_ERROR) {
            PRINT_RTC5_ERROR_INFO(ErrorCode);
            free_rtc5_dll();
            return false;
        } else { //  n_load_program_file was successfull
            (void) select_rtc(DefaultCard);
        }
    }
    
    //
    set_rtc4_mode(); //  for RTC4 compatibility
    // Initialize the RTC5
    stop_execution();
    //  If the DefaultCard has been used previously by another application
    //  a list might still be running. This would prevent load_program_file
    //  and load_correction_file from being executed.
    ErrorCode = load_program_file(0); //  path = current working path
    if (ErrorCode) {
        printf("Program file loading error: %d\n", ErrorCode);
        free_rtc5_dll();
        return false;
    }
    ErrorCode = load_correction_file(0,  // initialize like "D2_1to1.ct5",
                                     1,  // table; #1 is used by default
                                     2); // use 2D only
    if (ErrorCode) {
        printf("Correction file loading error: %d\n", ErrorCode);
        free_rtc5_dll();
        return false;
    }
    select_cor_table(1, 0); //  table #1 at primary connector (default)
    //  stop_execution might have created a RTC5_TIMEOUT error
    reset_error(-1); //  clear all previous error codes
    //  Configure list memory, default: config_list( 4000, 4000 ).
    //  One list only
    config_list(ListMemory, 0);
    //  input_list_pointer and out_list_pointer will jump automatically
    //  from the end of the list onto position 0 each without using
    //  set_end_of_list. auto_change won't be executed.
    //  RTC4::set_list_mode( 1 ) is no more supported
    set_laser_mode(LaserMode);
    set_firstpulse_killer(FirstPulseKiller);
    //  This function must be called at least once to activate laser
    //  signals. Later on enable/disable_laser would be sufficient.
    set_laser_control(LaserControl);
    // Activate a home jump and specify the beam dump
    home_position(BeamDump.xval, BeamDump.yval);
    // Turn on the optical pump source
    write_da_x(AnalogOutChannel, AnalogOutValue);
    INFO_MSG("connect success");
    return true;
}

bool LaserWorker::checkCard()
{
    UINT errorCode = n_get_last_error(DefaultCard);
    if (errorCode != RTC5_NO_ERROR) {
        WARN_MSG("RTC5 has error");
        PRINT_RTC5_ERROR_INFO(errorCode);
        free_rtc5_dll();
        return false;
    } else {
        INFO_MSG("RTC5 has no error");
        return true;
    }
}

bool LaserWorker::executeRTC5Command(const RTC5Command &cmd)
{
    static UINT startFlags = 2;
    // OutPos是执行位置,InPos是写入位置
    UINT InPos = get_input_pointer();
    UINT OutPos, Busy;
    
    // ----------- list 状态控制 ----------
    if ((InPos & PointerCount) == PointerCount) {
        get_status(&Busy, &OutPos);
        
        //  Busy & 0x0001: list is still executing, may be paused via pause_list
        //  Busy & 0x00fe: list has finished, but home_jumping is still active
        //  Busy & 0xff00: && (Busy & 0x00ff) = 0: set_wait
        //                 && (Busy & 0x00ff) > 0: pause_list
        //
        //  List is running and not paused, no home_jumping
        if (Busy == 0x0001) {
            //  If OutPos comes too close to InPos it would overtake. Let the list wait.
            if (((InPos >= OutPos) && (InPos - OutPos < StartGap / 2))
                || ((InPos < OutPos) && (InPos + ListMemory - OutPos < StartGap / 2))) {
                //  *start & 4: Set_wait already pending
                //  *start & 8: Final flushing requested, the out_pointer MUST
                //              come very close to the last input_pointer.
                if (!(startFlags & 4) && !(startFlags & 8)) {
                    startFlags |= 4;
                    set_wait(1);
                    InPos = get_input_pointer();
                }
            }
        }
        //  List not running and not paused, no home_jumping
        if (!Busy && !(startFlags & 2)) {
            if (((InPos > OutPos) && (InPos - OutPos > StartGap))
                || ((InPos < OutPos) && (InPos + ListMemory - OutPos > StartGap))) {
                execute_list_pos(1, (OutPos + 1) % ListMemory); // 从特定位置开始一直执行
            }
        }
        //  List not running and not home_jumping, but paused via set_wait
        if (!(Busy & 0x00ff) && (Busy & 0xff00)) {
            if (startFlags & 4) {
                if (((InPos > OutPos) && (InPos - OutPos > StartGap))
                    || ((InPos < OutPos) && (InPos + ListMemory - OutPos > StartGap))) {
                    release_wait();
                    startFlags &= ~4;
                }
            }
        }
    }
    
    // ----------- 写命令 ----------
    get_status(&Busy, &OutPos);
    if (((InPos > OutPos) && (ListMemory - InPos + OutPos > LoadGap))
        || ((InPos < OutPos) && (InPos + LoadGap < OutPos))) {
        std::visit(
            [](const auto &cmd) {
                using T = std::decay_t<decltype(cmd)>;
                
                if constexpr (std::is_same_v<T, JumpCommand>) {
                    INFO_MSG(" jump_abs");
                    jump_abs(cmd.pos.xval, cmd.pos.yval);
                } else if constexpr (std::is_same_v<T, MarkCommand>) {
                    INFO_MSG(" mark_abs");
                    mark_abs(cmd.pos.xval, cmd.pos.yval);
                } else if constexpr (std::is_same_v<T, SetLaserPulsesCommand>) {
                    INFO_MSG(" set_laser_pulses");
                    set_laser_pulses(cmd.halfPeriod, cmd.pulseWidth);
                } else if constexpr (std::is_same_v<T, SetScannerDelaysCommand>) {
                    INFO_MSG(" set_scanner_delays");
                    set_scanner_delays(cmd.jumpDelay, cmd.markDelay, cmd.polygonDelay);
                } else if constexpr (std::is_same_v<T, SetLaserDelaysCommand>) {
                    INFO_MSG(" set_laser_delays");
                    set_laser_delays(cmd.laserOnDelay, cmd.laserOffDelay);
                } else if constexpr (std::is_same_v<T, SetJumpSpeedCommand>) {
                    INFO_MSG(" set_jump_speed");
                    set_jump_speed(cmd.jumpSpeed);
                } else if constexpr (std::is_same_v<T, SetMarkSpeedCommand>) {
                    INFO_MSG(" set_mark_speed");
                    set_mark_speed(cmd.markSpeed);
                } else if constexpr (std::is_same_v<T, LongDelayCommand>) {
                    INFO_MSG(" long_delay");
                    long_delay(cmd.time);
                }
                // } else if constexpr (std::is_same_v<T, SetWaitCommand>) {
                //     set_wait(1);
                // } else if constexpr (std::is_same_v<T, ReleaseWaitCommand>) {
                //     release_wait();
                // }
            },
            cmd);
        
        return true;
    }
    
    // ----------- 写入失败：flush 或等待状态 ----------
    if (Busy && !(startFlags & 8) && abs((int) InPos - (int) OutPos) < (LoadGap / 10)) {
        printf("WARNING: In = %d Out = %d\n", InPos, OutPos);
    }
    
    return false; // 等待下一次调用重试
}

bool LaserWorker::pauseRTC5Command()
{
    pause_list();
    return true;
}
*/

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
    stopLaserWorker();
    if (m_thread.joinable()) {
        m_thread.join();
    }
}
