#include "laserdevicetest.h"
#include <thread>

bool LaserDeviceTest::loadDLL()
{
    return true;
}

bool LaserDeviceTest::unloadDLL()
{
    INFO_MSG("testDLL.DLL is unloaded");
    return true;
}

bool LaserDeviceTest::connectCard()
{
    INFO_MSG("connect success");
    return true;
}

bool LaserDeviceTest::disconnectCard()
{
        return true;
}

bool LaserDeviceTest::checkCard()
{
        return true;
}

bool LaserDeviceTest::executeCommandList(const std::vector<LaserDeviceCommand> &cmdList) {
    const long  R = 1000; // 转换系数: 从graphicsView的mm转换到rtc的um
    const long transferParamX = R*(1);
    const long transferParamY = R*(1);
    const long transferParamAngle = (-1);
    for (const auto &cmd : cmdList) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::visit(
            [](const auto &c) {
                using T = std::decay_t<decltype(c)>;
                if constexpr (std::is_same_v<T, JumpCommand>) {
                    INFO_MSG(" jump_abs " + QString::number(c.x) + " " + QString::number(c.y));
                    // jump_abs(c.x * transferParamX, c.y *transferParamY );
                } else if constexpr (std::is_same_v<T, MarkCommand>) {
                    INFO_MSG(" mark_abs " + QString::number(c.x) + " " + QString::number(c.y));
                    // mark_abs(c.x  * transferParamX, c.y *transferParamY );
                } else if constexpr (std::is_same_v<T, ArcCommand>) {
                    INFO_MSG(" arc_abs " + QString::number(c.x) + " " + QString::number(c.y) + " " + QString::number(c.angle));
                    // arc_abs(c.x * transferParamX, c.y * transferParamY , c.angle *transferParamAngle);
                } else if constexpr (std::is_same_v<T, SetLaserPulsesCommand>) {
                    INFO_MSG(" set_laser_pulses " + QString::number(c.halfPeriod) + " " + QString::number(c.pulseLength));
                    // set_laser_pulses(c.halfPeriod, c.pulseLength);
                } else if constexpr (std::is_same_v<T, SetScannerDelaysCommand>) {
                    INFO_MSG(" set_scanner_delays " + QString::number(c.jumpDelay) + " " + QString::number(c.markDelay) + " " + QString::number(c.polygonDelay));
                    // set_scanner_delays(c.jumpDelay, c.markDelay, c.polygonDelay);
                } else if constexpr (std::is_same_v<T, SetLaserDelaysCommand>) {
                    INFO_MSG(" set_laser_delays " + QString::number(c.laserOnDelay) + " " + QString::number(c.laserOffDelay));
                    // set_laser_delays(c.laserOnDelay, c.laserOffDelay);
                } else if constexpr (std::is_same_v<T, SetJumpSpeedCommand>) {
                    INFO_MSG(" set_jump_speed " + QString::number(c.jumpSpeed));
                    // set_jump_speed(c.jumpSpeed);
                } else if constexpr (std::is_same_v<T, SetMarkSpeedCommand>) {
                    INFO_MSG(" set_mark_speed " + QString::number(c.markSpeed));
                    // set_mark_speed(c.markSpeed);
                } else if constexpr (std::is_same_v<T, LongDelayCommand>) {
                    INFO_MSG(" long_delay " + QString::number(c.time));
                    // long_delay(c.time);
                }
            },
            cmd
            );
    }
    return true;
}

void LaserDeviceTest::resumeExecution() {
    // restart_list();
}

void LaserDeviceTest::pauseExecution() {
    // pause_list();
}

void LaserDeviceTest::abortExecution() {
    // stop_execution();
}

bool LaserDeviceTest::getListStatus() {
    // unsigned int result = read_status();
    // if ((result & BUSY1) || (result & BUSY2) ){
    //     return true;// 繁忙返回1
    // } else if ((result & USED1) || (result & USED2)){
    //     return false; // 结束返回0
    // } else {
    //     return false;
    // }
}
