#ifndef LASERDEVICEPROTOCOL_H
#define LASERDEVICEPROTOCOL_H

#include "logger.h"


/*****************************************************************************
* RTC5 ERROR
 *****************************************************************************/
#define RTC5_NO_ERROR 0
#define RTC5_NO_CARD 1
#define RTC5_ACCESS_DENIED 2
#define RTC5_SEND_ERROR 4
#define RTC5_TIMEOUT 8
#define RTC5_PARAM_ERROR 16
#define RTC5_BUSY 32
#define RTC5_REJECTED 64
#define RTC5_IGNORED 128
#define RTC5_VERSION_MISMATCH 256
#define RTC5_VERIFY_ERROR 512
#define RTC5_TYPE_REJECTED 1024

#define PRINT_RTC5_ERROR_INFO(error, i)                              \
do {                                                             \
        if ((error) == 0)                                            \
        WARN_MSG(QString("Card %1 没有错误").arg(i));           \
        if ((error) & RTC5_NO_CARD)                                  \
        WARN_MSG(QString("Card %1 未检测到任何板卡 (RTC5_NO_CARD)").arg(i)); \
        if ((error) & RTC5_ACCESS_DENIED)                            \
        WARN_MSG(QString("Card %1 访问权限被拒绝 (RTC5_ACCESS_DENIED)").arg(i)); \
        if ((error) & RTC5_SEND_ERROR)                               \
        WARN_MSG(QString("Card %1 命令未发送出去，可能是驱动或连接问题 (RTC5_SEND_ERROR)").arg(i)); \
        if ((error) & RTC5_TIMEOUT)                                  \
        WARN_MSG(QString("Card %1 板卡无响应，可能未加载程序文件 (RTC5_TIMEOUT)").arg(i)); \
        if ((error) & RTC5_PARAM_ERROR)                              \
        WARN_MSG(QString("Card %1 命令参数无效 (RTC5_PARAM_ERROR)").arg(i)); \
        if ((error) & RTC5_BUSY)                                     \
        WARN_MSG(QString("Card %1 当前没有 List 正在运行 (RTC5_BUSY)").arg(i)); \
        if ((error) & RTC5_VERSION_MISMATCH)                         \
        WARN_MSG(QString("Card %1 RTC5 DLL 和固件版本不一致 (RTC5_VERSION_MISMATCH)").arg(i)); \
} while (0)


/*****************************************************************************
* List Status
* read_status()  =>   bool = (result & LOAD1)
* LOAD     代表正在装载某个list 但是还没execute
* READY  表示装载完毕 可以execute(set_end_of_list()已经被设置)
* BUSY     表示正在打印; 如果pause了也将保持BUSY
* USED     执行完成
 *****************************************************************************/
const unsigned int LOAD1   = (1 << 0);  // Bit 0
const unsigned int LOAD2   = (1 << 1);  // Bit 1
const unsigned int READY1  = (1 << 2);  // Bit 2
const unsigned int READY2  = (1 << 3);  // Bit 3
const unsigned int BUSY1   = (1 << 4);  // Bit 4
const unsigned int BUSY2   = (1 << 5);  // Bit 5
const unsigned int USED1   = (1 << 6);  // Bit 6
const unsigned int USED2   = (1 << 7);  // Bit 7



/*****************************************************************************
* 确认好的protocol params
 *****************************************************************************/
const double Pi = 3.14159265358979323846;
const unsigned int LaserModeYAG = 1;       //  YAG 1 mode
const unsigned int LaserModeCO2 = 0;       //  CO2
const unsigned int DefaultCard = 1;     //  number of default card


/*****************************************************************************
* example
 *****************************************************************************/
// Change these values according to your system
const unsigned int ListMemory = 10000;  //  size of list 1 memory (default 4000)
const unsigned int LaserControl = 0x18; //  Laser signals LOW active (Bits #3 and #4)
const unsigned int StartGap = 1000;     //  gap ahead between input_pointer and out_pointer
const unsigned int LoadGap = 100;       //  gap ahead between out_pointer and input_pointer
const unsigned int PointerCount = 0x3F; //  pointer mask for checking the gap
// RTC4 compatibility mode assumed
const unsigned int AnalogOutChannel = 1;       //  AnalogOut Channel 1 used
const unsigned int AnalogOutValue = 640;       //  Standard Pump Source Value
const unsigned int AnalogOutStandby = 0;       //  Standby Pump Source Value
const unsigned int WarmUpTime = 2000000 / 10;  //    2  s [10 us]
const unsigned int LaserHalfPeriod = 50 * 8;   //   50 us [1/8 us] must be at least 13
const unsigned int LaserPulseWidth = 5 * 8;    //    5 us [1/8 us]
const unsigned int FirstPulseKiller = 200 * 8; //  200 us [1/8 us]
const long LaserOnDelay = 100 * 1;     //  100 us [1 us]
const unsigned int LaserOffDelay = 100 * 1; //  100 us [1 us]
const unsigned int JumpDelay = 250 / 10;    //  250 us [10 us]
const unsigned int MarkDelay = 100 / 10;    //  100 us [10 us]
const unsigned int PolygonDelay = 50 / 10;  //   50 us [10 us]
const double MarkSpeed = 250.0;        //  [16 Bits/ms]
const double JumpSpeed = 1000.0;       //  [16 Bits/ms]
// End Locus of a Line
// const locus BeamDump = {-32000, -32000}; //  Beam Dump Location


/*****************************************************************************
* operation abstract command
 *****************************************************************************/
// jump_abs
struct JumpCommand
{
    long x;
    long y;
};

// mark_abs
struct MarkCommand
{
    long x;
    long y;
};

// arc_abs
struct ArcCommand
{
    long x;
    long y;
    double angle;
};

struct SetLaserPulsesCommand
{
    unsigned int halfPeriod;
    unsigned int pulseWidth;
};

struct SetScannerDelaysCommand
{
    unsigned int jumpDelay;
    unsigned int markDelay;
    unsigned int polygonDelay;
};

struct SetLaserDelaysCommand
{
    unsigned int laserOnDelay;
    unsigned int laserOffDelay;
};

struct SetJumpSpeedCommand
{
    unsigned int jumpSpeed;
};

struct SetMarkSpeedCommand
{
    unsigned int markSpeed;
};

struct LongDelayCommand
{
    unsigned int time;
};

// RTC5命令; 不考虑list,以及一些初始化命令1, 只负责设置参数和打印命令
using LaserDeviceCommand = std::variant<JumpCommand,
                                 MarkCommand,
                                 ArcCommand,
                                 SetLaserPulsesCommand,
                                 SetScannerDelaysCommand,
                                 SetLaserDelaysCommand,
                                 SetJumpSpeedCommand,
                                 SetMarkSpeedCommand,
                                 LongDelayCommand>;
#endif // LASERDEVICEPROTOCOL_H
