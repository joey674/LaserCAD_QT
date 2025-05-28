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

    set_rtc4_mode(); //  for RTC4 compatibility

    stop_execution();
    //  If the DefaultCard has been used previously by another application
    //  a list might still be running. This would prevent load_program_file
    //  and load_correction_file from being executed.

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    int bDirect3DMove=0;
    int iEdgeLevel=65535;
    int iMinJumpDelay =10;
    int iJumpLengthLimit = 10;
    //
    QString workPath = QDir::currentPath();

    ErrorCode = load_program_file(workPath.toUtf8().constData());
    if (ErrorCode) {
        WARN_MSG("load_program_file");
        free_rtc5_dll();
        return false;
    }
    QString correctionFilePath = m_settings.correctionFilePath;
    ErrorCode = load_correction_file(correctionFilePath.toUtf8().constData(), 1, 3);
    if (ErrorCode) {
        WARN_MSG("load_correction_file");
        free_rtc5_dll();
        return false;
    }

    // //
    // if(!m_powercurvefile.IsEmpty())
    //     LoadPowerCurve(m_powercurvefile);

    select_cor_table(1, 0); //  table #1 at primary connector (default)
    reset_error(UINT_MAX);

    config_list(-1,-1);

    set_laser_control(0x00);

    config_laser_signals(0x24);

    stop_execution();

    auto xcor = m_settings.scaleCorX;
    auto ycor = m_settings.scaleCorY;
    auto xyrotate = m_settings.rotation;
    auto xoffset = m_settings.offsetX;
    auto yoffset = m_settings.offsetY;
    auto scale = m_settings.scale;
    set_matrix(0, xcor*cos(xyrotate*Pi/180), -xcor*sin(xyrotate*Pi/180), ycor*sin(xyrotate*Pi/180), ycor*cos(xyrotate*Pi/180), 1);
    set_offset(0, xoffset*scale, yoffset*scale, 1);

    // set_delay_mode(m_bVarPolyDelay, bDirect3DMove, iEdgeLevel, iMinJumpDelay, iJumpLengthLimit*m_Scale);//100
    // m_Scale=get_head_para(1,1);

    set_default_pixel(0);

    set_port_default(0,0);

    unsigned int lasermode = UINT_MAX;
    if (m_settings.laserMode == "CO2") lasermode = LaserModeCO2;
    else if (m_settings.laserMode == "YAG") lasermode = LaserModeYAG;
    else WARN_MSG("unknow lasermode");
    set_laser_mode(lasermode);


    // //auto laser control;
    // if(m_bSpeedDepend || m_bPositionDepend)
    // {
    //     m_iSpeedDependMode=2; //actual speed mode
    //     double value=1;

    //     if(!strAutoControlScale.IsEmpty())
    //         load_auto_laser_control(strAutoControlScale, 1);
    //     else
    //         load_auto_laser_control(0, 1);

    //     if(m_bSpeedDepend)	set_auto_laser_control(m_iAutoDependCtrl, value, m_iSpeedDependMode,  m_AdvLaserMin*value, m_AdvLaserMax*value);
    //     else set_auto_laser_control(m_iAutoDependCtrl, value, 0,  m_AdvLaserMin*value, m_AdvLaserMax*value);

    //     if(m_bPositionDepend)load_position_control(strAutoPosScale, 1);
    //     else load_position_control(0,1);
    // }
    // else
    //      set_auto_laser_control(0,1,m_iSpeedDependMode,0,1);

    /// testcode 判断到底需不需要    set_start_list( 1U );
    set_start_list( 1U );
    set_laser_pulses( LaserHalfPeriod, LaserPulseWidth );
    set_scanner_delays( JumpDelay, MarkDelay, PolygonDelay );
    set_laser_delays( LaserOnDelay, LaserOffDelay );
    set_jump_speed( JumpSpeed );
    set_mark_speed( MarkSpeed );
    set_end_of_list();
    execute_list( 1U );
    /// testcode 判断到底需不需要    set_start_list( 1U );

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

bool LaserDeviceRTC5::executeCommand(const std::vector<LaserDeviceCommand> &cmdList) {
    while (!load_list(1U, 0U)) {}

    // 坐标要乘以一个转换系数R 不然输入是以mm为单位 但是内部执行是um
    // 同时由于对graphicsview做了matrx transform(坐标右上为正),需要把角度做反再传回去
    // 我们这里坐标是(double,double), 用mm做单位; 输入的时候变成(long,long),用bit做单位
    const long  R = 1000; // 转换系数: 从graphicsView的mm转换到rtc的um
    const long transferParamX = R*(1);
    const long transferParamY = R*(1);
    const long transferParamAngle = (-1);
    for (const auto &cmd : cmdList) {
        std::visit(
            [](const auto &c) {
                using T = std::decay_t<decltype(c)>;
                if constexpr (std::is_same_v<T, JumpCommand>) {
                    INFO_MSG(" jump_abs " + QString::number(c.x) + " " + QString::number(c.y));
                    jump_abs(c.x * transferParamX, c.y *transferParamY );
                } else if constexpr (std::is_same_v<T, MarkCommand>) {
                    INFO_MSG(" mark_abs " + QString::number(c.x) + " " + QString::number(c.y));
                    mark_abs(c.x  * transferParamX, c.y *transferParamY );
                } else if constexpr (std::is_same_v<T, ArcCommand>) {
                    INFO_MSG(" arc_abs " + QString::number(c.x) + " " + QString::number(c.y) + " " + QString::number(c.angle));
                    arc_abs(c.x * transferParamX, c.y * transferParamY , c.angle *transferParamAngle);
                } else if constexpr (std::is_same_v<T, SetLaserPulsesCommand>) {
                    INFO_MSG(" set_laser_pulses " + QString::number(c.halfPeriod) + " " + QString::number(c.pulseWidth));
                    set_laser_pulses(c.halfPeriod, c.pulseWidth);
                } else if constexpr (std::is_same_v<T, SetScannerDelaysCommand>) {
                    INFO_MSG(" set_scanner_delays " + QString::number(c.jumpDelay) + " " + QString::number(c.markDelay) + " " + QString::number(c.polygonDelay));
                    set_scanner_delays(c.jumpDelay, c.markDelay, c.polygonDelay);
                } else if constexpr (std::is_same_v<T, SetLaserDelaysCommand>) {
                    INFO_MSG(" set_laser_delays " + QString::number(c.laserOnDelay) + " " + QString::number(c.laserOffDelay));
                    set_laser_delays(c.laserOnDelay, c.laserOffDelay);
                } else if constexpr (std::is_same_v<T, SetJumpSpeedCommand>) {
                    INFO_MSG(" set_jump_speed " + QString::number(c.jumpSpeed));
                    set_jump_speed(c.jumpSpeed);
                } else if constexpr (std::is_same_v<T, SetMarkSpeedCommand>) {
                    INFO_MSG(" set_mark_speed " + QString::number(c.markSpeed));
                    set_mark_speed(c.markSpeed);
                } else if constexpr (std::is_same_v<T, LongDelayCommand>) {
                    INFO_MSG(" long_delay " + QString::number(c.time));
                    // long_delay(c.time);
                }
            },
            cmd
            );
    }
    set_end_of_list();
    execute_list(1U);

    /*
    LONG      R(10000L);
    set_start_list( 1U );
    set_laser_pulses( LaserHalfPeriod, LaserPulseWidth );
    set_scanner_delays( JumpDelay, MarkDelay, PolygonDelay );
    set_laser_delays( LaserOnDelay, LaserOffDelay );
    set_jump_speed( JumpSpeed );
    set_mark_speed( MarkSpeed );
    set_end_of_list();
    execute_list( 1U );

    while ( !load_list( 1U, 0U ) ) {}
    jump_abs( 0, 0 );
    mark_abs(2*R, 2*R);
    mark_abs(2*R, -2*R);
    mark_abs(-2*R, 2*R);
    mark_abs(-2*R, -2*R);
    set_end_of_list();
    execute_list( 1U );
    return true;
    */

    /*
    set_start_list( 1U );
    set_laser_pulses( LaserHalfPeriod, LaserPulseWidth );
    set_scanner_delays( JumpDelay, MarkDelay, PolygonDelay );
    set_laser_delays( LaserOnDelay, LaserOffDelay );
    set_jump_speed( JumpSpeed );
    set_mark_speed( MarkSpeed );
    set_end_of_list();
    execute_list( 1U );
    struct polygon
    {
        LONG xval, yval;
    };
    LONG      R(20000L);
    polygon square[] =
        {
            {-R, -R}
            , {-R,  R}
            , {R,  R}
            , {R, -R}
            , {-R, -R}
        };
    if ( sizeof(square)/sizeof(square[0]) )
    {
        while ( !load_list( 1U, 0U ) ) {}
        jump_abs( square->xval, square->yval );
        size_t i(0U);
        for (size_t i = 1; i < sizeof(square)/sizeof(square[0]); ++i)
        {
            mark_abs(square[i].xval, square[i].yval);
        }
        set_end_of_list();
        execute_list( 1U );
    }
*/

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
        return false;
    }
}

/* bool LaserDeviceRTC5::executeCommand(const LaserDeviceCommand &cmd)
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
                    INFO_MSG(" jump_abs " + QString::number(cmd.pos.xval) + " "
                             + QString::number(cmd.pos.yval));
                    jump_abs(cmd.pos.xval, cmd.pos.yval);
                } else if constexpr (std::is_same_v<T, MarkCommand>) {
                    INFO_MSG(" mark_abs " + QString::number(cmd.pos.xval) + " "
                             + QString::number(cmd.pos.yval));
                    mark_abs(cmd.pos.xval, cmd.pos.yval);
                } else if constexpr (std::is_same_v<T, ArcCommand>) {
                    INFO_MSG(" arc_abs " + QString::number(cmd.x) + " " + QString::number(cmd.y)
                             + " " + QString::number(cmd.angle));
                    arc_abs(cmd.x, cmd.y,cmd.angle);
                } else if constexpr (std::is_same_v<T, SetLaserPulsesCommand>) {
                    INFO_MSG(" set_laser_pulses " + QString::number(cmd.halfPeriod) + " "
                             + QString::number(cmd.pulseWidth));
                    set_laser_pulses(cmd.halfPeriod, cmd.pulseWidth);
                } else if constexpr (std::is_same_v<T, SetScannerDelaysCommand>) {
                    INFO_MSG(" set_scanner_delays " + QString::number(cmd.jumpDelay) + " "
                             + QString::number(cmd.markDelay) + " "
                             + QString::number(cmd.polygonDelay));
                    set_scanner_delays(cmd.jumpDelay, cmd.markDelay, cmd.polygonDelay);
                } else if constexpr (std::is_same_v<T, SetLaserDelaysCommand>) {
                    INFO_MSG(" set_laser_delays " + QString::number(cmd.laserOnDelay) + " "
                             + QString::number(cmd.laserOffDelay));
                    set_laser_delays(cmd.laserOnDelay, cmd.laserOffDelay);
                } else if constexpr (std::is_same_v<T, SetJumpSpeedCommand>) {
                    INFO_MSG(" set_jump_speed " + QString::number(cmd.jumpSpeed));
                    set_jump_speed(cmd.jumpSpeed);
                } else if constexpr (std::is_same_v<T, SetMarkSpeedCommand>) {
                    INFO_MSG(" set_mark_speed " + QString::number(cmd.markSpeed));
                    set_mark_speed(cmd.markSpeed);
                } else if constexpr (std::is_same_v<T, LongDelayCommand>) {
                    INFO_MSG(" long_delay " + QString::number(cmd.time));
                    // long_delay(cmd.time);
                }
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
*/

