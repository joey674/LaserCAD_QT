#include "laserdevicertc5.h"
#include "logger.h"
#include <RTC5expl.h>
#include <QDir>
#include <vector.hpp>

bool LaserDeviceRTC5::loadDLL()
{
    auto errorCode = RTC5open();
    if (errorCode !=0 ) {
        WARN_MSG("RTC5DLL.DLL load fail: " + QString::number (errorCode));
        // Q_ASSERT("RTC5 DLL load failed.");
        return false;
    }else{
        INFO_MSG("RTC5DLL.DLL is loaded");
        return true;
    }
}

bool LaserDeviceRTC5::unloadDLL()
{
    free_rtc5_dll();
    RTC5close();
    INFO_MSG("RTC5DLL.DLL is unloaded");
    return true;
}

bool LaserDeviceRTC5::connectCard()
{
    // 判断rtc dll初始化是否成功
    UINT ErrorCode = init_rtc5_dll();
    if (ErrorCode != RTC5_NO_ERROR) {
        if (ErrorCode & RTC5_NO_CARD) {
            PRINT_RTC5_ERROR_INFO(ErrorCode,0);// 判断有没有卡
        } else {
            const UINT RTC5CountCards = rtc5_count_cards();
            INFO_VAR("Found "+ QString::number (RTC5CountCards) + "RTC5 cards;");
            for (UINT i = 1; i <= RTC5CountCards; i++) { //  打印每张板卡的错误
                const UINT Error = n_get_last_error(i);
                if (Error != RTC5_NO_ERROR) {
                    PRINT_RTC5_ERROR_INFO(Error,i);
                    n_reset_error(i, Error);
                }
            }
        }
        free_rtc5_dll();
        return false;
    }
    INFO_MSG("connect to card success");

    // 说明选择目标卡后的设置是否成功
    if (DefaultCard != select_rtc(DefaultCard)) {
        ErrorCode = n_get_last_error(DefaultCard);
        if (ErrorCode & RTC5_VERSION_MISMATCH) {
            //  In this case load_program_file(0) would not work.
            ErrorCode = n_load_program_file(DefaultCard, 0); //  current working path
        } else {
            PRINT_RTC5_ERROR_INFO(ErrorCode,DefaultCard);
            free_rtc5_dll();
            return false;
        }

        if (ErrorCode != RTC5_NO_ERROR) {
            PRINT_RTC5_ERROR_INFO(ErrorCode,DefaultCard);
            free_rtc5_dll();
            return false;
        } else { //  n_load_program_file was successfull
            (void) select_rtc(DefaultCard);
        }
    }

    //  for RTC4 compatibility
    set_rtc4_mode();

    //  If the DefaultCard has been used previously by another application
    //  a list might still be running. This would prevent load_program_file
    //  and load_correction_file from being executed.
    stop_execution();

    // 加载当前工作目录
    QString workPath = QDir::currentPath();
    ErrorCode = load_program_file(workPath.toUtf8().constData());
    if (ErrorCode) {
        WARN_MSG("load_program_file");
        free_rtc5_dll();
        return false;
    }

    // 加载correction file
    QString correctionFilePath = m_settings.correctionFilePath;
    ErrorCode = load_correction_file(correctionFilePath.toUtf8().constData(), 1, 3);
    if (ErrorCode) {
        WARN_MSG("load_correction_file");
        free_rtc5_dll();
        return false;
    }

    // 获取矫正factor
    this->m_calibrationFactor = get_head_para(1,1);
    DEBUG_VAR(this->m_calibrationFactor);
    this->m_focalLength = get_head_para(1,2);
    DEBUG_VAR(this->m_focalLength);

    //  table #1 at primary connector (default)
    select_cor_table(1, 0);

    reset_error(UINT_MAX);

    this->configList ();

    set_laser_control(0x00);

    config_laser_signals(0x24);

    stop_execution();

    // auto xcor = m_settings.scaleCorX;
    // auto ycor = m_settings.scaleCorY;
    // auto xyrotate = m_settings.rotation;
    // set_matrix(0, xcor*cos(xyrotate*Pi/180), -xcor*sin(xyrotate*Pi/180), ycor*sin(xyrotate*Pi/180), ycor*cos(xyrotate*Pi/180), 1);

    // auto xoffset = m_settings.offsetX;
    // auto yoffset = m_settings.offsetY;
    // auto scale = m_settings.scale * this->m_calibrationFactor;
    // set_offset(0, xoffset*scale, yoffset*scale, 1);

    // set_default_pixel(0);

    // set_port_default(0,0);

    unsigned int lasermode = UINT_MAX;
    if (m_settings.laserMode == "CO2") lasermode = LaserModeCO2;
    else if (m_settings.laserMode == "YAG1") lasermode = LaserModeYAG1;
    else if (m_settings.laserMode == "YAG2") lasermode = LaserModeYAG2;
    else if (m_settings.laserMode == "YAG3") lasermode = LaserModeYAG3;
    else WARN_MSG("unknow lasermode");
    set_laser_mode(lasermode);

    // /// testcode 判断到底需不需要    set_start_list( 1U );
    // set_start_list( 1U );
    // set_laser_pulses( LaserHalfPeriod, LaserPulseWidth );
    // set_scanner_delays( JumpDelay, MarkDelay, PolygonDelay );
    // set_laser_delays( LaserOnDelay, LaserOffDelay );
    // set_jump_speed( JumpSpeed );
    // set_mark_speed( MarkSpeed );
    // jump_abs(0,0);
    // set_end_of_list();
    // execute_list( 1U );
    // /// testcode 判断到底需不需要    set_start_list( 1U );

    ErrorCode = n_get_last_error(DefaultCard);
    if (ErrorCode) {
        WARN_MSG("'in connect card;may has error");
    }
    return true;
}

bool LaserDeviceRTC5::disconnectCard()
{
    return true;
}

bool LaserDeviceRTC5::checkCard()
{
    UINT errorCode = n_get_last_error(DefaultCard);
    if (errorCode != RTC5_NO_ERROR) {
        WARN_MSG("RTC5 has error");
        PRINT_RTC5_ERROR_INFO(errorCode,DefaultCard);
        free_rtc5_dll();
        return false;
    } else {
        INFO_MSG("RTC5 has no error");
        return true;
    }
}

bool LaserDeviceRTC5::executeCommandList(const std::vector<LaserDeviceCommand> &cmdList) {
    if (this->m_settings.executeMode == "SingleList") {
        this->executeCommandListBySingleList (cmdList);
    } else if (this->m_settings.executeMode == "DoubleLists") {
        this->executeCommandListByDoubleLists (cmdList);
    } else if (this->m_settings.executeMode  == "CircleList") {

    }
    return true;
}

bool LaserDeviceRTC5::configList() {
    if (this->m_settings.executeMode == "SingleList") {
        config_list(-1,-1); // 把空间全部分配给list1
    } else if (this->m_settings.executeMode == "DoubleLists") {
        config_list( List1Size, List2Size ); // 两个list各分4000
    } else if (this->m_settings.executeMode  == "CircleList") {

    }
    return true;
}

bool LaserDeviceRTC5::executeCommand(const LaserDeviceCommand &cmd) {
    // 坐标要乘以一个转换系数,这个数从correctionfile中读到; 不然输入是以mm为单位 但是内部执行是bit
    // 同时由于对graphicsview做了matrx transform(坐标右上为正),需要把角度做反再传回去
    // 我们这里坐标是(double,double), 用mm做单位; 输入的时候变成(long,long),用bit做单位
    const long R = static_cast<long>(this->m_calibrationFactor * this->m_settings.scale);
    const long transferParamX = R*(1);
    const long transferParamY = R*(1);
    const long transferParamAngle = (-1);
    const long transferParamSpeed = R*(1)/1000;

    std::visit(
        [&](const auto &c) {
            using T = std::decay_t<decltype(c)>;
            if constexpr (std::is_same_v<T, JumpCommand>) {
                // mm ==> bit
                INFO_MSG(" jump_abs " + QString::number(c.x) + " " + QString::number(c.y));
                DEBUG_VAR(c.x * transferParamX);
                DEBUG_VAR(c.y *transferParamY );
                jump_abs(c.x * transferParamX, c.y *transferParamY );
            }
            else if constexpr (std::is_same_v<T, MarkCommand>) {
                // mm ==> bit
                INFO_MSG(" mark_abs " + QString::number(c.x) + " " + QString::number(c.y));
                DEBUG_VAR(c.x  * transferParamX);
                DEBUG_VAR(c.y *transferParamY);
                mark_abs(c.x  * transferParamX, c.y *transferParamY );
            }
            else if constexpr (std::is_same_v<T, ArcCommand>) {
                // mm ==> bit
                INFO_MSG(" arc_abs " + QString::number(c.x) + " " + QString::number(c.y) + " " + QString::number(c.angle));
                arc_abs(c.x * transferParamX, c.y * transferParamY , c.angle *transferParamAngle);
            }
            else if constexpr (std::is_same_v<T, EllipseCommand>) {
                // mm ==> bit
                INFO_MSG("set_ellipse" + QString::number(c.a) + " " + QString::number(c.b) + " " + QString::number(c.phi0)+ " " + QString::number(c.phi));
                INFO_MSG(" mark_ellipse_abs " + QString::number(c.X) + " " + QString::number(c.Y) + " " + QString::number(c.Alpha));
                set_ellipse(c.a * transferParamX, c.b * transferParamY , c.phi0 *transferParamAngle, c.phi);
                mark_ellipse_abs(c.X* transferParamX,c.Y* transferParamY,c.Alpha*transferParamAngle);
            }
            else if constexpr (std::is_same_v<T, SetLaserPulsesCommand>) {
                // kHz ==> us ==> bit (1 bit equals 1/64 µs) kHz * 1000 ==> Hz *64/2 ==> bit
                // ms ==> us ==> bit (1 bit equals 1/64 µs)  ms * 1000 ==> us * 64 ==> bit
                uint32_t halfPeriod = static_cast<uint32_t>(1e3/ c.frequency / 2 *64);
                uint32_t pulseLength = static_cast<uint32_t>(c.pulseLength*1e3 *64);
                INFO_MSG(" set_laser_pulses(SetLaserPulsesCommand) (halfPeriod pulseLength)" + QString::number(halfPeriod) + " " + QString::number(pulseLength));
                set_laser_pulses(halfPeriod, pulseLength);
            }
            else if constexpr (std::is_same_v<T, SetScannerDelaysCommand>) {
                // ms ==> bit(1 bit equals 0.5 µs)
                uint32_t jumpDelay = static_cast<uint32_t>(std::round(c.jumpDelay /** 2000.0*/));
                uint32_t markDelay = static_cast<uint32_t>(std::round(c.markDelay/* * 2000.0*/));
                uint32_t polygonDelay = static_cast<uint32_t>(std::round(c.polygonDelay /** 2000.0*/));
                INFO_MSG(" set_scanner_delays " + QString::number(jumpDelay) + " " + QString::number(markDelay) + " " + QString::number(polygonDelay));
                set_scanner_delays(jumpDelay, markDelay, polygonDelay);
            }
            else if constexpr (std::is_same_v<T, SetLaserDelaysCommand>) {
                // ms ==> bit(1 bit equals 0.5 µs)
                uint32_t laserOnDelay = static_cast<uint32_t>(std::round(c.laserOnDelay /** 2000.0*/));
                uint32_t laserOffDelay = static_cast<uint32_t>(std::round(c.laserOffDelay /** 2000.0*/));
                INFO_MSG(" set_laser_delays " + QString::number(laserOnDelay) + " " + QString::number(laserOffDelay));
                set_laser_delays(laserOnDelay, laserOffDelay);
            }
            else if constexpr (std::is_same_v<T, SetJumpSpeedCommand>) {
                INFO_MSG(" set_jump_speed " + QString::number(c.jumpSpeed));
                set_jump_speed(c.jumpSpeed* transferParamSpeed);
            }
            else if constexpr (std::is_same_v<T, SetMarkSpeedCommand>) {
                INFO_MSG(" set_mark_speed " + QString::number(c.markSpeed));
                set_mark_speed(c.markSpeed* transferParamSpeed);
            }
            else if constexpr (std::is_same_v<T, LongDelayCommand>) {
                INFO_MSG(" long_delay() " + QString::number(c.time));
                long_delay(c.time);
            }
            else if constexpr (std::is_same_v<T, SetLaserPowerCommand>) {
                // percentage ==> V
                uint32_t voltage =  static_cast<uint32_t>((c.percentage / 100 /2) * (4096));
                INFO_MSG(" write_da_1_list(SetLaserPowerCommand) 没开"  + QString::number(voltage));
                // write_da_1_list(voltage);
            }
        },
        cmd
        );
    return true;
}

bool LaserDeviceRTC5::executeCommandListBySingleList(const std::vector<LaserDeviceCommand> &cmdList) {
    while (!load_list(1U, 0U)) {}

    for (const auto &cmd : cmdList) {
        this->executeCommand (cmd);
    }

    set_end_of_list();
    execute_list(1U);

    return true;
}

bool LaserDeviceRTC5::executeCommandListByDoubleLists(const std::vector<LaserDeviceCommand> &cmdList) {
    int list = 1;
    bool firstTime = true;
    int listLevel = 0;
    const int maxListLevel = List1Size;

    auto flushCurrentList = [&]() {
        set_end_of_list();
        if (firstTime) {
            execute_list(list);
            firstTime = false;
        } else {
            auto_change();
        }
        list = (list == 1) ? 2 : 1;
        listLevel = 0;
        while (!load_list(list, 0)) {}
    };

    while (!load_list(list, 0)) {}

    for (const auto &cmd : cmdList) {
        this->executeCommand (cmd);
        listLevel++;
        if (listLevel >= maxListLevel - 1) {
            flushCurrentList();
        }
    }

    if (listLevel > 0) {
        flushCurrentList();
    }

    return true;
}

bool LaserDeviceRTC5::executeCommandListByCircleList(const std::vector<LaserDeviceCommand> &cmdList) {
    WARN_MSG("TODO");
    return true;
}


void LaserDeviceRTC5::resumeExecution() {
      restart_list();
}

void LaserDeviceRTC5::pauseExecution() {
    pause_list();
}

void LaserDeviceRTC5::abortExecution() {
    stop_execution();
}

bool LaserDeviceRTC5::getListStatus() {
    unsigned int result = read_status();
    if ((result & BUSY1) || (result & BUSY2) ){
        return true;// 繁忙返回1
    } else if ((result & USED1) || (result & USED2)){
        return false; // 结束返回0
    } else {
        return true;// 在装载也算是繁忙
    }
}

