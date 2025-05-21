#include "laserdevicertc4.h"
#include "laserdeviceprotocol.h"
#include "logger.h"
// #include <RTC4expl.h>

bool LaserDeviceRTC4::loadDLL()
{
    if (RTC4open()) {
        WARN_MSG("RTC4DLL.DLL not found");
        throw std::runtime_error("RTC4 DLL load failed.");
    }
    INFO_MSG("RTC4DLL.DLL is loaded");
    return true;
}

bool LaserDeviceRTC4::unloadDLL()
{
    // free_rtc4_dll();
    // RTC4close();
    INFO_MSG("RTC4DLL.DLL is unloaded");
    return true;
}

bool LaserDeviceRTC4::connectCard()
{
    // // 判断rtc dll初始化是否成功
    // UINT ErrorCode = init_rtc4_dll();
    // if (ErrorCode != RTC4_NO_ERROR) {
    //     if (ErrorCode & RTC4_NO_CARD) {
    //         PRINT_RTC4_ERROR_INFO(ErrorCode);
    //     } else {
    //         const UINT RTC4CountCards = rtc4_count_cards(); //  number of cards found
    //         UINT AccError(0);
    //         //  Error analysis in detail
    //         for (UINT i = 1; i <= RTC4CountCards; i++) {
    //             const UINT Error = n_get_last_error(i);

    //             if (Error != RTC4_NO_ERROR) {
    //                 AccError |= Error;
    //                 PRINT_RTC4_ERROR_INFO(Error);
    //                 n_reset_error(i, Error);
    //             }
    //         }
    //         if (AccError != RTC4_NO_ERROR) {
    //             PRINT_RTC4_ERROR_INFO(AccError);
    //         }
    //     }
    //     free_rtc4_dll();
    //     return false;
    // }

    // // 说明选择卡是否成功
    // if (DefaultCard != select_rtc(DefaultCard)) {
    //     ErrorCode = n_get_last_error(DefaultCard);
    //     if (ErrorCode & RTC4_VERSION_MISMATCH) {
    //         //  In this case load_program_file(0) would not work.
    //         ErrorCode = n_load_program_file(DefaultCard, 0); //  current working path
    //     } else {
    //         PRINT_RTC4_ERROR_INFO(ErrorCode);
    //         free_rtc4_dll();
    //         return false;
    //     }

    //     if (ErrorCode != RTC4_NO_ERROR) {
    //         PRINT_RTC4_ERROR_INFO(ErrorCode);
    //         free_rtc4_dll();
    //         return false;
    //     } else { //  n_load_program_file was successfull
    //         (void) select_rtc(DefaultCard);
    //     }
    // }

    // //
    // set_rtc4_mode(); //  for RTC4 compatibility
    // // Initialize the RTC4
    // stop_execution();
    // //  If the DefaultCard has been used previously by another application
    // //  a list might still be running. This would prevent load_program_file
    // //  and load_correction_file from being executed.
    // ErrorCode = load_program_file(0); //  path = current working path
    // if (ErrorCode) {
    //     printf("Program file loading error: %d\n", ErrorCode);
    //     free_rtc4_dll();
    //     return false;
    // }
    // ErrorCode = load_correction_file(0, // initialize like "D2_1to1.ct4",
    //                                  1, // table; #1 is used by default
    //                                  2); // use 2D only
    // if (ErrorCode) {
    //     printf("Correction file loading error: %d\n", ErrorCode);
    //     free_rtc4_dll();
    //     return false;
    // }
    // select_cor_table(1, 0); //  table #1 at primary connector (default)
    // //  stop_execution might have created a RTC4_TIMEOUT error
    // reset_error(-1); //  clear all previous error codes
    // //  Configure list memory, default: config_list( 4000, 4000 ).
    // //  One list only
    // config_list(ListMemory, 0);
    // //  input_list_pointer and out_list_pointer will jump automatically
    // //  from the end of the list onto position 0 each without using
    // //  set_end_of_list. auto_change won't be executed.
    // //  RTC4::set_list_mode( 1 ) is no more supported
    // set_laser_mode(LaserMode);
    // set_firstpulse_killer(FirstPulseKiller);
    // //  This function must be called at least once to activate laser
    // //  signals. Later on enable/disable_laser would be sufficient.
    // set_laser_control(LaserControl);
    // // Activate a home jump and specify the beam dump
    // home_position(BeamDump.xval, BeamDump.yval);
    // // Turn on the optical pump source
    // write_da_x(AnalogOutChannel, AnalogOutValue);
    // INFO_MSG("connect success");
    return true;
}

bool LaserDeviceRTC4::disconnectCard()
{
    return true;
}

bool LaserDeviceRTC4::checkCard()
{
    // UINT errorCode = n_get_last_error(DefaultCard);
    // if (errorCode != RTC4_NO_ERROR) {
    //     WARN_MSG("RTC4 has error");
    //     PRINT_RTC4_ERROR_INFO(errorCode);
    //     free_rtc4_dll();
    //     return false;
    // } else {
    //     INFO_MSG("RTC4 has no error");
    //     return true;
    // }
}

bool LaserDeviceRTC4::executeCommand(const LaserDeviceCommand &cmd)
{
    // static UINT startFlags = 2;
    // // OutPos是执行位置,InPos是写入位置
    // UINT InPos = get_input_pointer();
    // UINT OutPos, Busy;

    // // ----------- list 状态控制 ----------
    // if ((InPos & PointerCount) == PointerCount) {
    //     get_status(&Busy, &OutPos);

    //     //  Busy & 0x0001: list is still executing, may be paused via pause_list
    //     //  Busy & 0x00fe: list has finished, but home_jumping is still active
    //     //  Busy & 0xff00: && (Busy & 0x00ff) = 0: set_wait
    //     //                 && (Busy & 0x00ff) > 0: pause_list
    //     //
    //     //  List is running and not paused, no home_jumping
    //     if (Busy == 0x0001) {
    //         //  If OutPos comes too close to InPos it would overtake. Let the list wait.
    //         if (((InPos >= OutPos) && (InPos - OutPos < StartGap / 2))
    //             || ((InPos < OutPos) && (InPos + ListMemory - OutPos < StartGap / 2))) {
    //             //  *start & 4: Set_wait already pending
    //             //  *start & 8: Final flushing requested, the out_pointer MUST
    //             //              come very close to the last input_pointer.
    //             if (!(startFlags & 4) && !(startFlags & 8)) {
    //                 startFlags |= 4;
    //                 set_wait(1);
    //                 InPos = get_input_pointer();
    //             }
    //         }
    //     }
    //     //  List not running and not paused, no home_jumping
    //     if (!Busy && !(startFlags & 2)) {
    //         if (((InPos > OutPos) && (InPos - OutPos > StartGap))
    //             || ((InPos < OutPos) && (InPos + ListMemory - OutPos > StartGap))) {
    //             execute_list_pos(1, (OutPos + 1) % ListMemory); // 从特定位置开始一直执行
    //         }
    //     }
    //     //  List not running and not home_jumping, but paused via set_wait
    //     if (!(Busy & 0x00ff) && (Busy & 0xff00)) {
    //         if (startFlags & 4) {
    //             if (((InPos > OutPos) && (InPos - OutPos > StartGap))
    //                 || ((InPos < OutPos) && (InPos + ListMemory - OutPos > StartGap))) {
    //                 release_wait();
    //                 startFlags &= ~4;
    //             }
    //         }
    //     }
    // }

    // // ----------- 写命令 ----------
    // get_status(&Busy, &OutPos);
    // if (((InPos > OutPos) && (ListMemory - InPos + OutPos > LoadGap))
    //     || ((InPos < OutPos) && (InPos + LoadGap < OutPos))) {
    //     std::visit(
    //         [](const auto &cmd) {
    //             using T = std::decay_t<decltype(cmd)>;

    //             if constexpr (std::is_same_v<T, JumpCommand>) {
    //                 INFO_MSG(" jump_abs " + QString::number(cmd.pos.xval) + " "
    //                          + QString::number(cmd.pos.yval));
    //                 jump_abs(cmd.pos.xval, cmd.pos.yval);
    //             } else if constexpr (std::is_same_v<T, MarkCommand>) {
    //                 INFO_MSG(" mark_abs " + QString::number(cmd.pos.xval) + " "
    //                          + QString::number(cmd.pos.yval));
    //                 mark_abs(cmd.pos.xval, cmd.pos.yval);
    //             } else if constexpr (std::is_same_v<T, ArcCommand>) {
    //                 INFO_MSG(" arc_abs " + QString::number(cmd.x) + " " + QString::number(cmd.y)
    //                          + " " + QString::number(cmd.angle));
    //                 arc_abs(cmd.x, cmd.y,cmd.angle);
    //             } else if constexpr (std::is_same_v<T, SetLaserPulsesCommand>) {
    //                 INFO_MSG(" set_laser_pulses " + QString::number(cmd.halfPeriod) + " "
    //                          + QString::number(cmd.pulseWidth));
    //                 set_laser_pulses(cmd.halfPeriod, cmd.pulseWidth);
    //             } else if constexpr (std::is_same_v<T, SetScannerDelaysCommand>) {
    //                 INFO_MSG(" set_scanner_delays " + QString::number(cmd.jumpDelay) + " "
    //                          + QString::number(cmd.markDelay) + " "
    //                          + QString::number(cmd.polygonDelay));
    //                 set_scanner_delays(cmd.jumpDelay, cmd.markDelay, cmd.polygonDelay);
    //             } else if constexpr (std::is_same_v<T, SetLaserDelaysCommand>) {
    //                 INFO_MSG(" set_laser_delays " + QString::number(cmd.laserOnDelay) + " "
    //                          + QString::number(cmd.laserOffDelay));
    //                 set_laser_delays(cmd.laserOnDelay, cmd.laserOffDelay);
    //             } else if constexpr (std::is_same_v<T, SetJumpSpeedCommand>) {
    //                 INFO_MSG(" set_jump_speed " + QString::number(cmd.jumpSpeed));
    //                 set_jump_speed(cmd.jumpSpeed);
    //             } else if constexpr (std::is_same_v<T, SetMarkSpeedCommand>) {
    //                 INFO_MSG(" set_mark_speed " + QString::number(cmd.markSpeed));
    //                 set_mark_speed(cmd.markSpeed);
    //             } else if constexpr (std::is_same_v<T, LongDelayCommand>) {
    //                 INFO_MSG(" long_delay " + QString::number(cmd.time));
    //                 // long_delay(cmd.time);
    //             }
    //         },
    //         cmd);

    //     return true;
    // }

    // // ----------- 写入失败：flush 或等待状态 ----------
    // if (Busy && !(startFlags & 8) && abs((int) InPos - (int) OutPos) < (LoadGap / 10)) {
    //     printf("WARNING: In = %d Out = %d\n", InPos, OutPos);
    // }

    // return false; // 等待下一次调用重试
}

bool LaserDeviceRTC4::pauseExecution() {
    // pause_list();
    return true;
}
