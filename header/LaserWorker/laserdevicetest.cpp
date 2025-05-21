#include "laserdevicetest.h"

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

bool LaserDeviceTest::executeCommand(const LaserDeviceCommand &cmd)
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
            } else if constexpr (std::is_same_v<T, ArcCommand>) {
                INFO_MSG(" arc_abs " + QString::number(cmd.x) + " " + QString::number(cmd.y)
                         + " " + QString::number(cmd.angle));
                // arc_abs(cmd.x, cmd.y,cmd.angle);
            } else if constexpr (std::is_same_v<T, SetLaserPulsesCommand>) {
                INFO_MSG(" set_laser_pulses " + QString::number(cmd.halfPeriod) + " "
                         + QString::number(cmd.pulseWidth));
                // set_laser_pulses(cmd.halfPeriod, cmd.pulseWidth);
            } else if constexpr (std::is_same_v<T, SetScannerDelaysCommand>) {
                INFO_MSG(" set_scanner_delays " + QString::number(cmd.jumpDelay) + " "
                         + QString::number(cmd.markDelay) + " "
                         + QString::number(cmd.polygonDelay));
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
    return true;
}

bool LaserDeviceTest::pauseExecution() {
    INFO_MSG(" pause_list ");
    // pause_list();
    return true;
}
