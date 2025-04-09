//  File: RTC5Wrap.cs
//----------------------------------------------------------------------------
//  Copyright (c) 2024 by SCANLAB GmbH.                   All rights reserved.
//----------------------------------------------------------------------------
//
//
//  Abstract
//      Defines the RTC5Wrap class that imports RTC5 functions from RTC5's
//      dynamic-link library.
//      RTC5Wrap automatically selects RTC5's 64-bit version RTC5DLLx64.dll,
//      if the 64-bit runtime is in use. Otherwise, the 32-bit version
//      RTC5DLL.DLL is going to be selected. That is, RTC5Wrap is good to
//      compile for the platform targets x86, x64, or 'Any CPU', where the
//      application, which is compiled for 'Any CPU' is able to run under
//      32-bit or 64-bit operating systems, as well.
//
//  Author
//      Bernhard Schrems, Christian Lutz
//
//      This file was automatically generated on 2024-09-25
//
//  NOTE
//      THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//      KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//      IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//      PURPOSE.
//
//----------------------------------------------------------------------------
using System;
using System.Runtime.InteropServices;

namespace RTC5Import
{
    /// <summary>
    /// Notice that the construction of the RTC5Import object or an initial
    /// call of any RTC5Import method may throw a TypeInitializationException
    /// exception, which indicates that the required DLL is missing or the
    /// import of a particular DLL function failed. In order to analyze and
    /// properly handle such an error condition you need to catch that
    /// TypeInitializationException type exception.
    /// </summary>
    public class RTC5Wrap
    {
        const int TableSize = 1024;
        const int SampleArraySize = 1024*1024;
        const int SignalSize = 4;
        const int TransformSize = 132130;
        const int SignalSize2 = 8;

        const string DLL_NAMEx86 = "RTC5DLL.dll";     // DLL's 32-bit version.
        const string DLL_NAMEx64 = "RTC5DLLx64.dll";  // DLL's 64-bit version.

        class FunctionImporter
        {
            static string DllName;

            [DllImport("Kernel32.dll")]
            private extern static IntPtr LoadLibrary(string path);

            [DllImport("kernel32.dll")]
            public extern static bool FreeLibrary(IntPtr hModule);

            [DllImport("Kernel32.dll")]
            private extern static IntPtr GetProcAddress(IntPtr hModule,
                                                        string procName);

            static IntPtr hModule;

            static FunctionImporter instance = null;

            protected FunctionImporter(string DllName)
            {
                hModule = LoadLibrary(DllName);
            }

            ~FunctionImporter()
            {
                if (hModule != IntPtr.Zero)
                    FreeLibrary(hModule);
            }

            public static Delegate Import<T>(string functionName)
            {
                if (instance == null)
                {
                    DllName = (Marshal.SizeOf(typeof(IntPtr)) == 4) ? DLL_NAMEx86 : DLL_NAMEx64;
                    instance = new FunctionImporter(DllName);

                    if (hModule == IntPtr.Zero)
                        throw new System.IO.
                                FileNotFoundException(DllName + " not found. ");
                }
                var functionAddress = GetProcAddress(hModule, functionName);
                try
                {
                    return Marshal.
                        GetDelegateForFunctionPointer(functionAddress, typeof(T));
                }
                catch (Exception ex)
                {
                    if ((ex is ArgumentException) || (ex is ArgumentNullException))
                        throw new EntryPointNotFoundException(functionName);
                    else throw;
                }
            }
        }

        #region RTC5FunctionDelegates
        public delegate uint init_rtc5_dllDelegate();
        public delegate void free_rtc5_dllDelegate();
        public delegate void set_rtc4_modeDelegate();
        public delegate void set_rtc5_modeDelegate();
        public delegate uint get_rtc_modeDelegate();
        public delegate uint n_get_errorDelegate(uint CardNo);
        public delegate uint n_get_last_errorDelegate(uint CardNo);
        public delegate void n_reset_errorDelegate(uint CardNo, uint Code);
        public delegate uint n_set_verifyDelegate(uint CardNo, uint Verify);
        public delegate uint get_errorDelegate();
        public delegate uint get_last_errorDelegate();
        public delegate void reset_errorDelegate(uint Code);
        public delegate uint set_verifyDelegate(uint Verify);
        public delegate uint verify_checksumDelegate(string Name);
        public delegate uint read_abc_from_fileDelegate(string Name, out double A, out double B, out double C);
        public delegate uint write_abc_to_fileDelegate(string Name, double A, double B, double C);
        public delegate uint rtc5_count_cardsDelegate();
        public delegate uint acquire_rtcDelegate(uint CardNo);
        public delegate uint release_rtcDelegate(uint CardNo);
        public delegate uint select_rtcDelegate(uint CardNo);
        public delegate uint get_dll_versionDelegate();
        public delegate uint n_get_serial_numberDelegate(uint CardNo);
        public delegate uint n_get_hex_versionDelegate(uint CardNo);
        public delegate uint n_get_rtc_versionDelegate(uint CardNo);
        public delegate uint get_serial_numberDelegate();
        public delegate uint get_hex_versionDelegate();
        public delegate uint get_rtc_versionDelegate();
        public delegate uint n_load_program_fileDelegate(uint CardNo, string Path);
        public delegate void n_sync_slavesDelegate(uint CardNo);
        public delegate uint n_get_sync_statusDelegate(uint CardNo);
        public delegate uint n_load_correction_fileDelegate(uint CardNo, string Name, uint No, uint Dim);
        public delegate uint n_load_zoom_correction_fileDelegate(uint CardNo, string Name, uint No);
        public delegate uint n_load_z_tableDelegate(uint CardNo, double A, double B, double C);
        public delegate void n_select_cor_tableDelegate(uint CardNo, uint HeadA, uint HeadB);
        public delegate uint n_set_dsp_modeDelegate(uint CardNo, uint Mode);
        public delegate int n_load_stretch_tableDelegate(uint CardNo, string Name, int No);
        public delegate void n_number_of_correction_tablesDelegate(uint CardNo, uint Number);
        public delegate double n_get_head_paraDelegate(uint CardNo, uint HeadNo, uint ParaNo);
        public delegate double n_get_table_paraDelegate(uint CardNo, uint TableNo, uint ParaNo);
        public delegate uint load_program_fileDelegate(string Path);
        public delegate void sync_slavesDelegate();
        public delegate uint get_sync_statusDelegate();
        public delegate uint load_correction_fileDelegate(string Name, uint No, uint Dim);
        public delegate uint load_zoom_correction_fileDelegate(string Name, uint No);
        public delegate uint load_z_tableDelegate(double A, double B, double C);
        public delegate void select_cor_tableDelegate(uint HeadA, uint HeadB);
        public delegate uint set_dsp_modeDelegate(uint Mode);
        public delegate int load_stretch_tableDelegate(string Name, int No);
        public delegate void number_of_correction_tablesDelegate(uint Number);
        public delegate double get_head_paraDelegate(uint HeadNo, uint ParaNo);
        public delegate double get_table_paraDelegate(uint TableNo, uint ParaNo);
        public delegate void n_config_listDelegate(uint CardNo, uint Mem1, uint Mem2);
        public delegate void n_get_config_listDelegate(uint CardNo);
        public delegate uint n_save_diskDelegate(uint CardNo, string Name, uint Mode);
        public delegate uint n_load_diskDelegate(uint CardNo, string Name, uint Mode);
        public delegate uint n_get_list_spaceDelegate(uint CardNo);
        public delegate void config_listDelegate(uint Mem1, uint Mem2);
        public delegate void get_config_listDelegate();
        public delegate uint save_diskDelegate(string Name, uint Mode);
        public delegate uint load_diskDelegate(string Name, uint Mode);
        public delegate uint get_list_spaceDelegate();
        public delegate void n_set_start_list_posDelegate(uint CardNo, uint ListNo, uint Pos);
        public delegate void n_set_start_listDelegate(uint CardNo, uint ListNo);
        public delegate void n_set_start_list_1Delegate(uint CardNo);
        public delegate void n_set_start_list_2Delegate(uint CardNo);
        public delegate void n_set_input_pointerDelegate(uint CardNo, uint Pos);
        public delegate uint n_load_listDelegate(uint CardNo, uint ListNo, uint Pos);
        public delegate void n_load_subDelegate(uint CardNo, uint Index);
        public delegate void n_load_charDelegate(uint CardNo, uint Char);
        public delegate void n_load_text_tableDelegate(uint CardNo, uint Index);
        public delegate void n_get_list_pointerDelegate(uint CardNo, out uint ListNo, out uint Pos);
        public delegate uint n_get_input_pointerDelegate(uint CardNo);
        public delegate void set_start_list_posDelegate(uint ListNo, uint Pos);
        public delegate void set_start_listDelegate(uint ListNo);
        public delegate void set_start_list_1Delegate();
        public delegate void set_start_list_2Delegate();
        public delegate void set_input_pointerDelegate(uint Pos);
        public delegate uint load_listDelegate(uint ListNo, uint Pos);
        public delegate void load_subDelegate(uint Index);
        public delegate void load_charDelegate(uint Char);
        public delegate void load_text_tableDelegate(uint Index);
        public delegate void get_list_pointerDelegate(out uint ListNo, out uint Pos);
        public delegate uint get_input_pointerDelegate();
        public delegate void n_execute_list_posDelegate(uint CardNo, uint ListNo, uint Pos);
        public delegate void n_execute_at_pointerDelegate(uint CardNo, uint Pos);
        public delegate void n_execute_listDelegate(uint CardNo, uint ListNo);
        public delegate void n_execute_list_1Delegate(uint CardNo);
        public delegate void n_execute_list_2Delegate(uint CardNo);
        public delegate void n_get_out_pointerDelegate(uint CardNo, out uint ListNo, out uint Pos);
        public delegate void execute_list_posDelegate(uint ListNo, uint Pos);
        public delegate void execute_at_pointerDelegate(uint Pos);
        public delegate void execute_listDelegate(uint ListNo);
        public delegate void execute_list_1Delegate();
        public delegate void execute_list_2Delegate();
        public delegate void get_out_pointerDelegate(out uint ListNo, out uint Pos);
        public delegate void n_auto_change_posDelegate(uint CardNo, uint Pos);
        public delegate void n_start_loopDelegate(uint CardNo);
        public delegate void n_quit_loopDelegate(uint CardNo);
        public delegate void n_pause_listDelegate(uint CardNo);
        public delegate void n_restart_listDelegate(uint CardNo);
        public delegate void n_release_waitDelegate(uint CardNo);
        public delegate void n_stop_executionDelegate(uint CardNo);
        public delegate void n_set_pause_list_condDelegate(uint CardNo, uint Mask1, uint Mask0);
        public delegate void n_set_pause_list_not_condDelegate(uint CardNo, uint Mask1, uint Mask0);
        public delegate void n_auto_changeDelegate(uint CardNo);
        public delegate void n_stop_listDelegate(uint CardNo);
        public delegate uint n_get_wait_statusDelegate(uint CardNo);
        public delegate uint n_read_statusDelegate(uint CardNo);
        public delegate void n_get_statusDelegate(uint CardNo, out uint Status, out uint Pos);
        public delegate void auto_change_posDelegate(uint Pos);
        public delegate void start_loopDelegate();
        public delegate void quit_loopDelegate();
        public delegate void pause_listDelegate();
        public delegate void restart_listDelegate();
        public delegate void release_waitDelegate();
        public delegate void stop_executionDelegate();
        public delegate void set_pause_list_condDelegate(uint Mask1, uint Mask0);
        public delegate void set_pause_list_not_condDelegate(uint Mask1, uint Mask0);
        public delegate void auto_changeDelegate();
        public delegate void stop_listDelegate();
        public delegate uint get_wait_statusDelegate();
        public delegate uint read_statusDelegate();
        public delegate void get_statusDelegate(out uint Status, out uint Pos);
        public delegate void n_set_extstartposDelegate(uint CardNo, uint Pos);
        public delegate void n_set_max_countsDelegate(uint CardNo, uint Counts);
        public delegate void n_set_control_modeDelegate(uint CardNo, uint Mode);
        public delegate void n_simulate_ext_stopDelegate(uint CardNo);
        public delegate void n_simulate_ext_start_ctrlDelegate(uint CardNo);
        public delegate uint n_get_countsDelegate(uint CardNo);
        public delegate uint n_get_startstop_infoDelegate(uint CardNo);
        public delegate void set_extstartposDelegate(uint Pos);
        public delegate void set_max_countsDelegate(uint Counts);
        public delegate void set_control_modeDelegate(uint Mode);
        public delegate void simulate_ext_stopDelegate();
        public delegate void simulate_ext_start_ctrlDelegate();
        public delegate uint get_countsDelegate();
        public delegate uint get_startstop_infoDelegate();
        public delegate void n_copy_dst_srcDelegate(uint CardNo, uint Dst, uint Src, uint Mode);
        public delegate void n_set_char_pointerDelegate(uint CardNo, uint Char, uint Pos);
        public delegate void n_set_sub_pointerDelegate(uint CardNo, uint Index, uint Pos);
        public delegate void n_set_text_table_pointerDelegate(uint CardNo, uint Index, uint Pos);
        public delegate void n_set_char_tableDelegate(uint CardNo, uint Index, uint Pos);
        public delegate uint n_get_char_pointerDelegate(uint CardNo, uint Char);
        public delegate uint n_get_sub_pointerDelegate(uint CardNo, uint Index);
        public delegate uint n_get_text_table_pointerDelegate(uint CardNo, uint Index);
        public delegate void copy_dst_srcDelegate(uint Dst, uint Src, uint Mode);
        public delegate void set_char_pointerDelegate(uint Char, uint Pos);
        public delegate void set_sub_pointerDelegate(uint Index, uint Pos);
        public delegate void set_text_table_pointerDelegate(uint Index, uint Pos);
        public delegate void set_char_tableDelegate(uint Index, uint Pos);
        public delegate uint get_char_pointerDelegate(uint Char);
        public delegate uint get_sub_pointerDelegate(uint Index);
        public delegate uint get_text_table_pointerDelegate(uint Index);
        public delegate void n_time_updateDelegate(uint CardNo);
        public delegate void n_set_serial_stepDelegate(uint CardNo, uint No, uint Step);
        public delegate void n_select_serial_setDelegate(uint CardNo, uint No);
        public delegate void n_set_serialDelegate(uint CardNo, uint No);
        public delegate double n_get_serialDelegate(uint CardNo);
        public delegate double n_get_list_serialDelegate(uint CardNo, out uint SetNo);
        public delegate void time_updateDelegate();
        public delegate void set_serial_stepDelegate(uint No, uint Step);
        public delegate void select_serial_setDelegate(uint No);
        public delegate void set_serialDelegate(uint No);
        public delegate double get_serialDelegate();
        public delegate double get_list_serialDelegate(out uint SetNo);
        public delegate void n_write_io_port_maskDelegate(uint CardNo, uint Value, uint Mask);
        public delegate void n_write_8bit_portDelegate(uint CardNo, uint Value);
        public delegate uint n_read_io_portDelegate(uint CardNo);
        public delegate uint n_read_io_port_bufferDelegate(uint CardNo, uint Index, out uint Value, out int XPos, out int YPos, out uint Time);
        public delegate uint n_get_io_statusDelegate(uint CardNo);
        public delegate uint n_read_analog_inDelegate(uint CardNo);
        public delegate void n_write_da_xDelegate(uint CardNo, uint x, uint Value);
        public delegate void n_set_laser_off_defaultDelegate(uint CardNo, uint AnalogOut1, uint AnalogOut2, uint DigitalOut);
        public delegate void n_set_port_defaultDelegate(uint CardNo, uint Port, uint Value);
        public delegate void n_write_io_portDelegate(uint CardNo, uint Value);
        public delegate void n_write_da_1Delegate(uint CardNo, uint Value);
        public delegate void n_write_da_2Delegate(uint CardNo, uint Value);
        public delegate void write_io_port_maskDelegate(uint Value, uint Mask);
        public delegate void write_8bit_portDelegate(uint Value);
        public delegate uint read_io_portDelegate();
        public delegate uint read_io_port_bufferDelegate(uint Index, out uint Value, out int XPos, out int YPos, out uint Time);
        public delegate uint get_io_statusDelegate();
        public delegate uint read_analog_inDelegate();
        public delegate void write_da_xDelegate(uint x, uint Value);
        public delegate void set_laser_off_defaultDelegate(uint AnalogOut1, uint AnalogOut2, uint DigitalOut);
        public delegate void set_port_defaultDelegate(uint Port, uint Value);
        public delegate void write_io_portDelegate(uint Value);
        public delegate void write_da_1Delegate(uint Value);
        public delegate void write_da_2Delegate(uint Value);
        public delegate void n_disable_laserDelegate(uint CardNo);
        public delegate void n_enable_laserDelegate(uint CardNo);
        public delegate void n_laser_signal_onDelegate(uint CardNo);
        public delegate void n_laser_signal_offDelegate(uint CardNo);
        public delegate void n_set_standbyDelegate(uint CardNo, uint HalfPeriod, uint PulseLength);
        public delegate void n_set_laser_pulses_ctrlDelegate(uint CardNo, uint HalfPeriod, uint PulseLength);
        public delegate void n_set_firstpulse_killerDelegate(uint CardNo, uint Length);
        public delegate void n_set_qswitch_delayDelegate(uint CardNo, uint Delay);
        public delegate void n_set_laser_modeDelegate(uint CardNo, uint Mode);
        public delegate void n_set_laser_controlDelegate(uint CardNo, uint Ctrl);
        public delegate void n_set_laser_pin_outDelegate(uint CardNo, uint Pins);
        public delegate uint n_get_laser_pin_inDelegate(uint CardNo);
        public delegate void n_set_softstart_levelDelegate(uint CardNo, uint Index, uint Level);
        public delegate void n_set_softstart_modeDelegate(uint CardNo, uint Mode, uint Number, uint Delay);
        public delegate uint n_set_auto_laser_controlDelegate(uint CardNo, uint Ctrl, uint Value, uint Mode, uint MinValue, uint MaxValue);
        public delegate uint n_set_auto_laser_paramsDelegate(uint CardNo, uint Ctrl, uint Value, uint MinValue, uint MaxValue);
        public delegate int n_load_auto_laser_controlDelegate(uint CardNo, string Name, uint No);
        public delegate int n_load_position_controlDelegate(uint CardNo, string Name, uint No);
        public delegate void n_set_default_pixelDelegate(uint CardNo, uint PulseLength);
        public delegate void n_get_standbyDelegate(uint CardNo, out uint HalfPeriod, out uint PulseLength);
        public delegate void n_set_pulse_pickingDelegate(uint CardNo, uint No);
        public delegate void n_set_pulse_picking_lengthDelegate(uint CardNo, uint Length);
        public delegate void n_config_laser_signalsDelegate(uint CardNo, uint Config);
        public delegate void disable_laserDelegate();
        public delegate void enable_laserDelegate();
        public delegate void laser_signal_onDelegate();
        public delegate void laser_signal_offDelegate();
        public delegate void set_standbyDelegate(uint HalfPeriod, uint PulseLength);
        public delegate void set_laser_pulses_ctrlDelegate(uint HalfPeriod, uint PulseLength);
        public delegate void set_firstpulse_killerDelegate(uint Length);
        public delegate void set_qswitch_delayDelegate(uint Delay);
        public delegate void set_laser_modeDelegate(uint Mode);
        public delegate void set_laser_controlDelegate(uint Ctrl);
        public delegate void set_laser_pin_outDelegate(uint Pins);
        public delegate uint get_laser_pin_inDelegate();
        public delegate void set_softstart_levelDelegate(uint Index, uint Level);
        public delegate void set_softstart_modeDelegate(uint Mode, uint Number, uint Delay);
        public delegate uint set_auto_laser_controlDelegate(uint Ctrl, uint Value, uint Mode, uint MinValue, uint MaxValue);
        public delegate uint set_auto_laser_paramsDelegate(uint Ctrl, uint Value, uint MinValue, uint MaxValue);
        public delegate int load_auto_laser_controlDelegate(string Name, uint No);
        public delegate int load_position_controlDelegate(string Name, uint No);
        public delegate void set_default_pixelDelegate(uint PulseLength);
        public delegate void get_standbyDelegate(out uint HalfPeriod, out uint PulseLength);
        public delegate void set_pulse_pickingDelegate(uint No);
        public delegate void set_pulse_picking_lengthDelegate(uint Length);
        public delegate void config_laser_signalsDelegate(uint Config);
        public delegate void n_set_ext_start_delayDelegate(uint CardNo, int Delay, uint EncoderNo);
        public delegate void n_set_rot_centerDelegate(uint CardNo, int X, int Y);
        public delegate void n_simulate_encoderDelegate(uint CardNo, uint EncoderNo);
        public delegate uint n_get_marking_infoDelegate(uint CardNo);
        public delegate void n_set_encoder_speed_ctrlDelegate(uint CardNo, uint EncoderNo, double Speed, double Smooth);
        public delegate void n_set_mcbsp_xDelegate(uint CardNo, double ScaleX);
        public delegate void n_set_mcbsp_yDelegate(uint CardNo, double ScaleY);
        public delegate void n_set_mcbsp_rotDelegate(uint CardNo, double Resolution);
        public delegate void n_set_mcbsp_matrixDelegate(uint CardNo);
        public delegate void n_set_mcbsp_global_xDelegate(uint CardNo, double ScaleX);
        public delegate void n_set_mcbsp_global_yDelegate(uint CardNo, double ScaleY);
        public delegate void n_set_mcbsp_global_rotDelegate(uint CardNo, double Resolution);
        public delegate void n_set_mcbsp_global_matrixDelegate(uint CardNo);
        public delegate void n_set_mcbsp_inDelegate(uint CardNo, uint Mode, double Scale);
        public delegate void n_set_multi_mcbsp_inDelegate(uint CardNo, uint Ctrl, uint P, uint Mode);
        public delegate void n_set_fly_tracking_errorDelegate(uint CardNo, uint TrackingErrorX, uint TrackingErrorY);
        public delegate int n_load_fly_2d_tableDelegate(uint CardNo, string Name, uint No);
        public delegate void n_init_fly_2dDelegate(uint CardNo, int OffsetX, int OffsetY);
        public delegate void n_get_fly_2d_offsetDelegate(uint CardNo, out int OffsetX, out int OffsetY);
        public delegate void n_get_encoderDelegate(uint CardNo, out int Encoder0, out int Encoder1);
        public delegate void n_read_encoderDelegate(uint CardNo, out int Encoder0_1, out int Encoder1_1, out int Encoder0_2, out int Encoder1_2);
        public delegate int n_get_mcbspDelegate(uint CardNo);
        public delegate int n_read_mcbspDelegate(uint CardNo, uint No);
        public delegate int n_read_multi_mcbspDelegate(uint CardNo, uint No);
        public delegate void n_clear_fly_overflow_ctrlDelegate(uint CardNo, uint Mode);
        public delegate void set_ext_start_delayDelegate(int Delay, uint EncoderNo);
        public delegate void set_rot_centerDelegate(int X, int Y);
        public delegate void simulate_encoderDelegate(uint EncoderNo);
        public delegate uint get_marking_infoDelegate();
        public delegate void set_encoder_speed_ctrlDelegate(uint EncoderNo, double Speed, double Smooth);
        public delegate void set_mcbsp_xDelegate(double ScaleX);
        public delegate void set_mcbsp_yDelegate(double ScaleY);
        public delegate void set_mcbsp_rotDelegate(double Resolution);
        public delegate void set_mcbsp_matrixDelegate();
        public delegate void set_mcbsp_global_xDelegate(double ScaleX);
        public delegate void set_mcbsp_global_yDelegate(double ScaleY);
        public delegate void set_mcbsp_global_rotDelegate(double Resolution);
        public delegate void set_mcbsp_global_matrixDelegate();
        public delegate void set_mcbsp_inDelegate(uint Mode, double Scale);
        public delegate void set_multi_mcbsp_inDelegate(uint Ctrl, uint P, uint Mode);
        public delegate void set_fly_tracking_errorDelegate(uint TrackingErrorX, uint TrackingErrorY);
        public delegate int load_fly_2d_tableDelegate(string Name, uint No);
        public delegate void init_fly_2dDelegate(int OffsetX, int OffsetY);
        public delegate void get_fly_2d_offsetDelegate(out int OffsetX, out int OffsetY);
        public delegate void get_encoderDelegate(out int Encoder0, out int Encoder1);
        public delegate void read_encoderDelegate(out int Encoder0_1, out int Encoder1_1, out int Encoder0_2, out int Encoder1_2);
        public delegate int get_mcbspDelegate();
        public delegate int read_mcbspDelegate(uint No);
        public delegate int read_multi_mcbspDelegate(uint No);
        public delegate void clear_fly_overflow_ctrlDelegate(uint Mode);
        public delegate double n_get_timeDelegate(uint CardNo);
        public delegate double n_get_lap_timeDelegate(uint CardNo);
        public delegate void n_measurement_statusDelegate(uint CardNo, out uint Busy, out uint Pos);
        public delegate void n_get_waveformDelegate(uint CardNo, uint Channel, uint Number, [MarshalAs(UnmanagedType.LPArray, SizeConst=SampleArraySize)]int[] Ptr);
        public delegate void n_bounce_suppDelegate(uint CardNo, uint Length);
        public delegate void n_home_position_xyzDelegate(uint CardNo, int XHome, int YHome, int ZHome);
        public delegate void n_home_positionDelegate(uint CardNo, int XHome, int YHome);
        public delegate void n_rs232_configDelegate(uint CardNo, uint BaudRate);
        public delegate void n_rs232_write_dataDelegate(uint CardNo, uint Data);
        public delegate void n_rs232_write_textDelegate(uint CardNo, string pData);
        public delegate uint n_rs232_read_dataDelegate(uint CardNo);
        public delegate uint n_set_mcbsp_freqDelegate(uint CardNo, uint Freq);
        public delegate void n_mcbsp_initDelegate(uint CardNo, uint XDelay, uint RDelay);
        public delegate void n_mcbsp_init_spiDelegate(uint CardNo, uint ClockLevel, uint ClockDelay);
        public delegate uint n_get_overrunDelegate(uint CardNo);
        public delegate uint n_get_master_slaveDelegate(uint CardNo);
        public delegate void n_get_transformDelegate(uint CardNo, uint Number, [MarshalAs(UnmanagedType.LPArray, SizeConst=SampleArraySize)]int[] Ptr1, [MarshalAs(UnmanagedType.LPArray, SizeConst=SampleArraySize)]int[] Ptr2, [MarshalAs(UnmanagedType.LPArray, SizeConst=TransformSize)]uint[] Ptr, uint Code);
        public delegate void n_stop_triggerDelegate(uint CardNo);
        public delegate void n_move_toDelegate(uint CardNo, uint Pos);
        public delegate void n_set_enduring_wobbelDelegate(uint CardNo, uint CenterX, uint CenterY, uint CenterZ, uint LimitHi, uint LimitLo, double ScaleX, double ScaleY, double ScaleZ);
        public delegate void n_set_enduring_wobbel_2Delegate(uint CardNo, uint CenterX, uint CenterY, uint CenterZ, uint LimitHi, uint LimitLo, double ScaleX, double ScaleY, double ScaleZ);
        public delegate void n_set_free_variableDelegate(uint CardNo, uint VarNo, uint Value);
        public delegate uint n_get_free_variableDelegate(uint CardNo, uint VarNo);
        public delegate void n_set_mcbsp_out_ptrDelegate(uint CardNo, uint Number, [MarshalAs(UnmanagedType.LPArray, SizeConst=SignalSize2)]uint[] SignalPtr);
        public delegate void n_periodic_toggleDelegate(uint CardNo, uint Port, uint Mask, uint P1, uint P2, uint Count, uint Start);
        public delegate uint n_load_wobbel_powerDelegate(uint CardNo, uint TableNo, [MarshalAs(UnmanagedType.LPArray, SizeConst=SampleArraySize)]int[] Ptr, int Flag);
        public delegate double get_timeDelegate();
        public delegate double get_lap_timeDelegate();
        public delegate void measurement_statusDelegate(out uint Busy, out uint Pos);
        public delegate void get_waveformDelegate(uint Channel, uint Number, [MarshalAs(UnmanagedType.LPArray, SizeConst=SampleArraySize)]int[] Ptr);
        public delegate void bounce_suppDelegate(uint Length);
        public delegate void home_position_xyzDelegate(int XHome, int YHome, int ZHome);
        public delegate void home_positionDelegate(int XHome, int YHome);
        public delegate void rs232_configDelegate(uint BaudRate);
        public delegate void rs232_write_dataDelegate(uint Data);
        public delegate void rs232_write_textDelegate(string pData);
        public delegate uint rs232_read_dataDelegate();
        public delegate uint set_mcbsp_freqDelegate(uint Freq);
        public delegate void mcbsp_initDelegate(uint XDelay, uint RDelay);
        public delegate void mcbsp_init_spiDelegate(uint ClockLevel, uint ClockDelay);
        public delegate uint get_overrunDelegate();
        public delegate uint get_master_slaveDelegate();
        public delegate void get_transformDelegate(uint Number, [MarshalAs(UnmanagedType.LPArray, SizeConst=SampleArraySize)]int[] Ptr1, [MarshalAs(UnmanagedType.LPArray, SizeConst=SampleArraySize)]int[] Ptr2, [MarshalAs(UnmanagedType.LPArray, SizeConst=TransformSize)]uint[] Ptr, uint Code);
        public delegate void stop_triggerDelegate();
        public delegate void move_toDelegate(uint Pos);
        public delegate void set_enduring_wobbelDelegate(uint CenterX, uint CenterY, uint CenterZ, uint LimitHi, uint LimitLo, double ScaleX, double ScaleY, double ScaleZ);
        public delegate void set_enduring_wobbel_2Delegate(uint CenterX, uint CenterY, uint CenterZ, uint LimitHi, uint LimitLo, double ScaleX, double ScaleY, double ScaleZ);
        public delegate void set_free_variableDelegate(uint VarNo, uint Value);
        public delegate uint get_free_variableDelegate(uint VarNo);
        public delegate void set_mcbsp_out_ptrDelegate(uint Number, [MarshalAs(UnmanagedType.LPArray, SizeConst=SignalSize2)]uint[] SignalPtr);
        public delegate void periodic_toggleDelegate(uint Port, uint Mask, uint P1, uint P2, uint Count, uint Start);
        public delegate uint load_wobbel_powerDelegate(uint TableNo, [MarshalAs(UnmanagedType.LPArray, SizeConst=SampleArraySize)]int[] Ptr, int Flag);
        public delegate void n_set_defocusDelegate(uint CardNo, int Shift);
        public delegate void n_set_defocus_offsetDelegate(uint CardNo, int Shift);
        public delegate void n_goto_xyzDelegate(uint CardNo, int X, int Y, int Z);
        public delegate void n_set_zoomDelegate(uint CardNo, uint Zoom);
        public delegate void n_goto_xyDelegate(uint CardNo, int X, int Y);
        public delegate int n_get_z_distanceDelegate(uint CardNo, int X, int Y, int Z);
        public delegate void set_defocusDelegate(int Shift);
        public delegate void set_defocus_offsetDelegate(int Shift);
        public delegate void goto_xyzDelegate(int X, int Y, int Z);
        public delegate void goto_xyDelegate(int X, int Y);
        public delegate void set_zoomDelegate(uint Zoom);
        public delegate int get_z_distanceDelegate(int X, int Y, int Z);
        public delegate void n_set_offset_xyzDelegate(uint CardNo, uint HeadNo, int XOffset, int YOffset, int ZOffset, uint at_once);
        public delegate void n_set_offsetDelegate(uint CardNo, uint HeadNo, int XOffset, int YOffset, uint at_once);
        public delegate void n_set_matrixDelegate(uint CardNo, uint HeadNo, double M11, double M12, double M21, double M22, uint at_once);
        public delegate void n_set_angleDelegate(uint CardNo, uint HeadNo, double Angle, uint at_once);
        public delegate void n_set_scaleDelegate(uint CardNo, uint HeadNo, double Scale, uint at_once);
        public delegate void n_apply_mcbspDelegate(uint CardNo, uint HeadNo, uint at_once);
        public delegate uint n_upload_transformDelegate(uint CardNo, uint HeadNo, [MarshalAs(UnmanagedType.LPArray, SizeConst=TransformSize)]uint[] Ptr);
        public delegate void set_offset_xyzDelegate(uint HeadNo, int XOffset, int YOffset, int ZOffset, uint at_once);
        public delegate void set_offsetDelegate(uint HeadNo, int XOffset, int YOffset, uint at_once);
        public delegate void set_matrixDelegate(uint HeadNo, double M11, double M12, double M21, double M22, uint at_once);
        public delegate void set_angleDelegate(uint HeadNo, double Angle, uint at_once);
        public delegate void set_scaleDelegate(uint HeadNo, double Scale, uint at_once);
        public delegate void apply_mcbspDelegate(uint HeadNo, uint at_once);
        public delegate uint upload_transformDelegate(uint HeadNo, [MarshalAs(UnmanagedType.LPArray, SizeConst=TransformSize)]uint[] Ptr);
        public delegate uint transformDelegate(out int Sig1, out int Sig2, [MarshalAs(UnmanagedType.LPArray, SizeConst=TransformSize)]uint[] Ptr, uint Code);
        public delegate void n_set_delay_modeDelegate(uint CardNo, uint VarPoly, uint DirectMove3D, uint EdgeLevel, uint MinJumpDelay, uint JumpLengthLimit);
        public delegate void n_set_jump_speed_ctrlDelegate(uint CardNo, double Speed);
        public delegate void n_set_mark_speed_ctrlDelegate(uint CardNo, double Speed);
        public delegate void n_set_sky_writing_paraDelegate(uint CardNo, double Timelag, int LaserOnShift, uint Nprev, uint Npost);
        public delegate void n_set_sky_writing_limitDelegate(uint CardNo, double CosAngle);
        public delegate void n_set_sky_writing_modeDelegate(uint CardNo, uint Mode);
        public delegate int n_load_varpolydelayDelegate(uint CardNo, string Name, uint No);
        public delegate void n_set_hiDelegate(uint CardNo, uint HeadNo, double GalvoGainX, double GalvoGainY, int GalvoOffsetX, int GalvoOffsetY);
        public delegate void n_get_hi_posDelegate(uint CardNo, uint HeadNo, out int X1, out int X2, out int Y1, out int Y2);
        public delegate uint n_auto_calDelegate(uint CardNo, uint HeadNo, uint Command);
        public delegate uint n_get_auto_calDelegate(uint CardNo, uint HeadNo);
        public delegate uint n_write_hi_posDelegate(uint CardNo, uint HeadNo, int X1, int X2, int Y1, int Y2);
        public delegate void n_set_sky_writingDelegate(uint CardNo, double Timelag, int LaserOnShift);
        public delegate void n_get_hi_dataDelegate(uint CardNo, out int X1, out int X2, out int Y1, out int Y2);
        public delegate void set_delay_modeDelegate(uint VarPoly, uint DirectMove3D, uint EdgeLevel, uint MinJumpDelay, uint JumpLengthLimit);
        public delegate void set_jump_speed_ctrlDelegate(double Speed);
        public delegate void set_mark_speed_ctrlDelegate(double Speed);
        public delegate void set_sky_writing_paraDelegate(double Timelag, int LaserOnShift, uint Nprev, uint Npost);
        public delegate void set_sky_writing_limitDelegate(double CosAngle);
        public delegate void set_sky_writing_modeDelegate(uint Mode);
        public delegate int load_varpolydelayDelegate(string Name, uint No);
        public delegate void set_hiDelegate(uint HeadNo, double GalvoGainX, double GalvoGainY, int GalvoOffsetX, int GalvoOffsetY);
        public delegate void get_hi_posDelegate(uint HeadNo, out int X1, out int X2, out int Y1, out int Y2);
        public delegate uint auto_calDelegate(uint HeadNo, uint Command);
        public delegate uint get_auto_calDelegate(uint HeadNo);
        public delegate uint write_hi_posDelegate(uint HeadNo, int X1, int X2, int Y1, int Y2);
        public delegate void set_sky_writingDelegate(double Timelag, int LaserOnShift);
        public delegate void get_hi_dataDelegate(out int X1, out int X2, out int Y1, out int Y2);
        public delegate void n_send_user_dataDelegate(uint CardNo, uint Head, uint Axis, int Data0, int Data1, int Data2, int Data3, int Data4);
        public delegate int n_read_user_dataDelegate(uint CardNo, uint Head, uint Axis, out int Data0, out int Data1, out int Data2, out int Data3, out int Data4);
        public delegate void n_control_commandDelegate(uint CardNo, uint Head, uint Axis, uint Data);
        public delegate int n_get_valueDelegate(uint CardNo, uint Signal);
        public delegate void n_get_valuesDelegate(uint CardNo, [MarshalAs(UnmanagedType.LPArray, SizeConst=SignalSize)]uint[] SignalPtr, [MarshalAs(UnmanagedType.LPArray, SizeConst=SignalSize)]int[] ResultPtr);
        public delegate void n_get_galvo_controlsDelegate(uint CardNo, [MarshalAs(UnmanagedType.LPArray, SizeConst=SignalSize2)]int[] SignalPtr, [MarshalAs(UnmanagedType.LPArray, SizeConst=SignalSize)]int[] ResultPtr);
        public delegate uint n_get_head_statusDelegate(uint CardNo, uint Head);
        public delegate int n_set_jump_modeDelegate(uint CardNo, int Flag, uint Length, int VA1, int VA2, int VB1, int VB2, int JA1, int JA2, int JB1, int JB2);
        public delegate int n_load_jump_table_offsetDelegate(uint CardNo, string Name, uint No, uint PosAck, int Offset, uint MinDelay, uint MaxDelay, uint ListPos);
        public delegate uint n_get_jump_tableDelegate(uint CardNo, [MarshalAs(UnmanagedType.LPArray, SizeConst=TableSize)]ushort[] Ptr);
        public delegate uint n_set_jump_tableDelegate(uint CardNo, [MarshalAs(UnmanagedType.LPArray, SizeConst=TableSize)]ushort[] Ptr);
        public delegate int n_load_jump_tableDelegate(uint CardNo, string Name, uint No, uint PosAck, uint MinDelay, uint MaxDelay, uint ListPos);
        public delegate void send_user_dataDelegate(uint Head, uint Axis, int Data0, int Data1, int Data2, int Data3, int Data4);
        public delegate int read_user_dataDelegate(uint Head, uint Axis, out int Data0, out int Data1, out int Data2, out int Data3, out int Data4);
        public delegate void control_commandDelegate(uint Head, uint Axis, uint Data);
        public delegate int get_valueDelegate(uint Signal);
        public delegate void get_valuesDelegate([MarshalAs(UnmanagedType.LPArray, SizeConst=SignalSize)]uint[] SignalPtr, [MarshalAs(UnmanagedType.LPArray, SizeConst=SignalSize)]int[] ResultPtr);
        public delegate void get_galvo_controlsDelegate([MarshalAs(UnmanagedType.LPArray, SizeConst=SignalSize2)]int[] SignalPtr, [MarshalAs(UnmanagedType.LPArray, SizeConst=SignalSize)]int[] ResultPtr);
        public delegate uint get_head_statusDelegate(uint Head);
        public delegate int set_jump_modeDelegate(int Flag, uint Length, int VA1, int VA2, int VB1, int VB2, int JA1, int JA2, int JB1, int JB2);
        public delegate int load_jump_table_offsetDelegate(string Name, uint No, uint PosAck, int Offset, uint MinDelay, uint MaxDelay, uint ListPos);
        public delegate uint get_jump_tableDelegate([MarshalAs(UnmanagedType.LPArray, SizeConst=TableSize)]ushort[] Ptr);
        public delegate uint set_jump_tableDelegate([MarshalAs(UnmanagedType.LPArray, SizeConst=TableSize)]ushort[] Ptr);
        public delegate int load_jump_tableDelegate(string Name, uint No, uint PosAck, uint MinDelay, uint MaxDelay, uint ListPos);
        public delegate void n_stepper_initDelegate(uint CardNo, uint No, uint Period, int Dir, int Pos, uint Tol, uint Enable, uint WaitTime);
        public delegate void n_stepper_enableDelegate(uint CardNo, int Enable1, int Enable2);
        public delegate void n_stepper_disable_switchDelegate(uint CardNo, int Disable1, int Disable2);
        public delegate void n_stepper_controlDelegate(uint CardNo, int Period1, int Period2);
        public delegate void n_stepper_abs_noDelegate(uint CardNo, uint No, int Pos, uint WaitTime);
        public delegate void n_stepper_rel_noDelegate(uint CardNo, uint No, int dPos, uint WaitTime);
        public delegate void n_stepper_absDelegate(uint CardNo, int Pos1, int Pos2, uint WaitTime);
        public delegate void n_stepper_relDelegate(uint CardNo, int dPos1, int dPos2, uint WaitTime);
        public delegate void n_get_stepper_statusDelegate(uint CardNo, out uint Status1, out int Pos1, out uint Status2, out int Pos2);
        public delegate void stepper_initDelegate(uint No, uint Period, int Dir, int Pos, uint Tol, uint Enable, uint WaitTime);
        public delegate void stepper_enableDelegate(int Enable1, int Enable2);
        public delegate void stepper_disable_switchDelegate(int Disable1, int Disable2);
        public delegate void stepper_controlDelegate(int Period1, int Period2);
        public delegate void stepper_abs_noDelegate(uint No, int Pos, uint WaitTime);
        public delegate void stepper_rel_noDelegate(uint No, int dPos, uint WaitTime);
        public delegate void stepper_absDelegate(int Pos1, int Pos2, uint WaitTime);
        public delegate void stepper_relDelegate(int dPos1, int dPos2, uint WaitTime);
        public delegate void get_stepper_statusDelegate(out uint Status1, out int Pos1, out uint Status2, out int Pos2);
        public delegate void n_select_cor_table_listDelegate(uint CardNo, uint HeadA, uint HeadB);
        public delegate void select_cor_table_listDelegate(uint HeadA, uint HeadB);
        public delegate void n_list_nopDelegate(uint CardNo);
        public delegate void n_list_continueDelegate(uint CardNo);
        public delegate void n_list_nextDelegate(uint CardNo);
        public delegate void n_long_delayDelegate(uint CardNo, uint Delay);
        public delegate void n_set_end_of_listDelegate(uint CardNo);
        public delegate void n_set_waitDelegate(uint CardNo, uint WaitWord);
        public delegate void n_list_jump_posDelegate(uint CardNo, uint Pos);
        public delegate void n_list_jump_relDelegate(uint CardNo, int Pos);
        public delegate void n_list_repeatDelegate(uint CardNo);
        public delegate void n_list_untilDelegate(uint CardNo, uint Number);
        public delegate void n_range_checkingDelegate(uint CardNo, uint HeadNo, uint Mode, uint Data);
        public delegate void n_set_list_jumpDelegate(uint CardNo, uint Pos);
        public delegate void list_nopDelegate();
        public delegate void list_continueDelegate();
        public delegate void list_nextDelegate();
        public delegate void long_delayDelegate(uint Delay);
        public delegate void set_end_of_listDelegate();
        public delegate void set_waitDelegate(uint WaitWord);
        public delegate void list_jump_posDelegate(uint Pos);
        public delegate void list_jump_relDelegate(int Pos);
        public delegate void list_repeatDelegate();
        public delegate void list_untilDelegate(uint Number);
        public delegate void range_checkingDelegate(uint HeadNo, uint Mode, uint Data);
        public delegate void set_list_jumpDelegate(uint Pos);
        public delegate void n_set_extstartpos_listDelegate(uint CardNo, uint Pos);
        public delegate void n_set_control_mode_listDelegate(uint CardNo, uint Mode);
        public delegate void n_simulate_ext_startDelegate(uint CardNo, int Delay, uint EncoderNo);
        public delegate void set_extstartpos_listDelegate(uint Pos);
        public delegate void set_control_mode_listDelegate(uint Mode);
        public delegate void simulate_ext_startDelegate(int Delay, uint EncoderNo);
        public delegate void n_list_returnDelegate(uint CardNo);
        public delegate void n_list_call_repeatDelegate(uint CardNo, uint Pos, uint Number);
        public delegate void n_list_call_abs_repeatDelegate(uint CardNo, uint Pos, uint Number);
        public delegate void n_list_callDelegate(uint CardNo, uint Pos);
        public delegate void n_list_call_absDelegate(uint CardNo, uint Pos);
        public delegate void n_sub_call_repeatDelegate(uint CardNo, uint Index, uint Number);
        public delegate void n_sub_call_abs_repeatDelegate(uint CardNo, uint Index, uint Number);
        public delegate void n_sub_callDelegate(uint CardNo, uint Index);
        public delegate void n_sub_call_absDelegate(uint CardNo, uint Index);
        public delegate void list_returnDelegate();
        public delegate void list_call_repeatDelegate(uint Pos, uint Number);
        public delegate void list_call_abs_repeatDelegate(uint Pos, uint Number);
        public delegate void list_callDelegate(uint Pos);
        public delegate void list_call_absDelegate(uint Pos);
        public delegate void sub_call_repeatDelegate(uint Index, uint Number);
        public delegate void sub_call_abs_repeatDelegate(uint Index, uint Number);
        public delegate void sub_callDelegate(uint Index);
        public delegate void sub_call_absDelegate(uint Index);
        public delegate void n_list_call_condDelegate(uint CardNo, uint Mask1, uint Mask0, uint Pos);
        public delegate void n_list_call_abs_condDelegate(uint CardNo, uint Mask1, uint Mask0, uint Pos);
        public delegate void n_sub_call_condDelegate(uint CardNo, uint Mask1, uint Mask0, uint Pos);
        public delegate void n_sub_call_abs_condDelegate(uint CardNo, uint Mask1, uint Mask0, uint Pos);
        public delegate void n_list_jump_pos_condDelegate(uint CardNo, uint Mask1, uint Mask0, uint Index);
        public delegate void n_list_jump_rel_condDelegate(uint CardNo, uint Mask1, uint Mask0, int Index);
        public delegate void n_if_condDelegate(uint CardNo, uint Mask1, uint Mask0);
        public delegate void n_if_not_condDelegate(uint CardNo, uint Mask1, uint Mask0);
        public delegate void n_if_pin_condDelegate(uint CardNo, uint Mask1, uint Mask0);
        public delegate void n_if_not_pin_condDelegate(uint CardNo, uint Mask1, uint Mask0);
        public delegate void n_switch_ioportDelegate(uint CardNo, uint MaskBits, uint ShiftBits);
        public delegate void n_list_jump_condDelegate(uint CardNo, uint Mask1, uint Mask0, uint Pos);
        public delegate void list_call_condDelegate(uint Mask1, uint Mask0, uint Pos);
        public delegate void list_call_abs_condDelegate(uint Mask1, uint Mask0, uint Pos);
        public delegate void sub_call_condDelegate(uint Mask1, uint Mask0, uint Index);
        public delegate void sub_call_abs_condDelegate(uint Mask1, uint Mask0, uint Index);
        public delegate void list_jump_pos_condDelegate(uint Mask1, uint Mask0, uint Pos);
        public delegate void list_jump_rel_condDelegate(uint Mask1, uint Mask0, int Pos);
        public delegate void if_condDelegate(uint Mask1, uint Mask0);
        public delegate void if_not_condDelegate(uint Mask1, uint Mask0);
        public delegate void if_pin_condDelegate(uint Mask1, uint Mask0);
        public delegate void if_not_pin_condDelegate(uint Mask1, uint Mask0);
        public delegate void switch_ioportDelegate(uint MaskBits, uint ShiftBits);
        public delegate void list_jump_condDelegate(uint Mask1, uint Mask0, uint Pos);
        public delegate void n_select_char_setDelegate(uint CardNo, uint No);
        public delegate void n_mark_textDelegate(uint CardNo, string Text);
        public delegate void n_mark_text_absDelegate(uint CardNo, string Text);
        public delegate void n_mark_charDelegate(uint CardNo, uint Char);
        public delegate void n_mark_char_absDelegate(uint CardNo, uint Char);
        public delegate void select_char_setDelegate(uint No);
        public delegate void mark_textDelegate(string Text);
        public delegate void mark_text_absDelegate(string Text);
        public delegate void mark_charDelegate(uint Char);
        public delegate void mark_char_absDelegate(uint Char);
        public delegate void n_mark_serialDelegate(uint CardNo, uint Mode, uint Digits);
        public delegate void n_mark_serial_absDelegate(uint CardNo, uint Mode, uint Digits);
        public delegate void n_mark_dateDelegate(uint CardNo, uint Part, uint Mode);
        public delegate void n_mark_date_absDelegate(uint CardNo, uint Part, uint Mode);
        public delegate void n_mark_timeDelegate(uint CardNo, uint Part, uint Mode);
        public delegate void n_mark_time_absDelegate(uint CardNo, uint Part, uint Mode);
        public delegate void n_select_serial_set_listDelegate(uint CardNo, uint No);
        public delegate void n_set_serial_step_listDelegate(uint CardNo, uint No, uint Step);
        public delegate void n_time_fix_f_offDelegate(uint CardNo, uint FirstDay, uint Offset);
        public delegate void n_time_fix_fDelegate(uint CardNo, uint FirstDay);
        public delegate void n_time_fixDelegate(uint CardNo);
        public delegate void mark_serialDelegate(uint Mode, uint Digits);
        public delegate void mark_serial_absDelegate(uint Mode, uint Digits);
        public delegate void mark_dateDelegate(uint Part, uint Mode);
        public delegate void mark_date_absDelegate(uint Part, uint Mode);
        public delegate void mark_timeDelegate(uint Part, uint Mode);
        public delegate void mark_time_absDelegate(uint Part, uint Mode);
        public delegate void time_fix_f_offDelegate(uint FirstDay, uint Offset);
        public delegate void select_serial_set_listDelegate(uint No);
        public delegate void set_serial_step_listDelegate(uint No, uint Step);
        public delegate void time_fix_fDelegate(uint FirstDay);
        public delegate void time_fixDelegate();
        public delegate void n_clear_io_cond_listDelegate(uint CardNo, uint Mask1, uint Mask0, uint Mask);
        public delegate void n_set_io_cond_listDelegate(uint CardNo, uint Mask1, uint Mask0, uint Mask);
        public delegate void n_write_io_port_mask_listDelegate(uint CardNo, uint Value, uint Mask);
        public delegate void n_write_8bit_port_listDelegate(uint CardNo, uint Value);
        public delegate void n_read_io_port_listDelegate(uint CardNo);
        public delegate void n_write_da_x_listDelegate(uint CardNo, uint x, uint Value);
        public delegate void n_write_io_port_listDelegate(uint CardNo, uint Value);
        public delegate void n_write_da_1_listDelegate(uint CardNo, uint Value);
        public delegate void n_write_da_2_listDelegate(uint CardNo, uint Value);
        public delegate void clear_io_cond_listDelegate(uint Mask1, uint Mask0, uint MaskClear);
        public delegate void set_io_cond_listDelegate(uint Mask1, uint Mask0, uint MaskSet);
        public delegate void write_io_port_mask_listDelegate(uint Value, uint Mask);
        public delegate void write_8bit_port_listDelegate(uint Value);
        public delegate void read_io_port_listDelegate();
        public delegate void write_da_x_listDelegate(uint x, uint Value);
        public delegate void write_io_port_listDelegate(uint Value);
        public delegate void write_da_1_listDelegate(uint Value);
        public delegate void write_da_2_listDelegate(uint Value);
        public delegate void n_laser_signal_on_listDelegate(uint CardNo);
        public delegate void n_laser_signal_off_listDelegate(uint CardNo);
        public delegate void n_para_laser_on_pulses_listDelegate(uint CardNo, uint Period, uint Pulses, uint P);
        public delegate void n_laser_on_pulses_listDelegate(uint CardNo, uint Period, uint Pulses);
        public delegate void n_laser_on_listDelegate(uint CardNo, uint Period);
        public delegate void n_set_laser_delaysDelegate(uint CardNo, int LaserOnDelay, uint LaserOffDelay);
        public delegate void n_set_standby_listDelegate(uint CardNo, uint HalfPeriod, uint PulseLength);
        public delegate void n_set_laser_pulsesDelegate(uint CardNo, uint HalfPeriod, uint PulseLength);
        public delegate void n_set_firstpulse_killer_listDelegate(uint CardNo, uint Length);
        public delegate void n_set_qswitch_delay_listDelegate(uint CardNo, uint Delay);
        public delegate void n_set_laser_pin_out_listDelegate(uint CardNo, uint Pins);
        public delegate void n_set_vector_controlDelegate(uint CardNo, uint Ctrl, uint Value);
        public delegate void n_set_default_pixel_listDelegate(uint CardNo, uint PulseLength);
        public delegate void n_set_port_default_listDelegate(uint CardNo, uint Port, uint Value);
        public delegate void n_set_auto_laser_params_listDelegate(uint CardNo, uint Ctrl, uint Value, uint MinValue, uint MaxValue);
        public delegate void n_set_pulse_picking_listDelegate(uint CardNo, uint No);
        public delegate void n_set_softstart_level_listDelegate(uint CardNo, uint Index, uint Level1, uint Level2, uint Level3);
        public delegate void n_set_softstart_mode_listDelegate(uint CardNo, uint Mode, uint Number, uint Delay);
        public delegate void n_config_laser_signals_listDelegate(uint CardNo, uint Config);
        public delegate void n_set_laser_timingDelegate(uint CardNo, uint HalfPeriod, uint PulseLength1, uint PulseLength2, uint TimeBase);
        public delegate void laser_signal_on_listDelegate();
        public delegate void laser_signal_off_listDelegate();
        public delegate void para_laser_on_pulses_listDelegate(uint Period, uint Pulses, uint P);
        public delegate void laser_on_pulses_listDelegate(uint Period, uint Pulses);
        public delegate void laser_on_listDelegate(uint Period);
        public delegate void set_laser_delaysDelegate(int LaserOnDelay, uint LaserOffDelay);
        public delegate void set_standby_listDelegate(uint HalfPeriod, uint PulseLength);
        public delegate void set_laser_pulsesDelegate(uint HalfPeriod, uint PulseLength);
        public delegate void set_firstpulse_killer_listDelegate(uint Length);
        public delegate void set_qswitch_delay_listDelegate(uint Delay);
        public delegate void set_laser_pin_out_listDelegate(uint Pins);
        public delegate void set_vector_controlDelegate(uint Ctrl, uint Value);
        public delegate void set_default_pixel_listDelegate(uint PulseLength);
        public delegate void set_port_default_listDelegate(uint Port, uint Value);
        public delegate void set_auto_laser_params_listDelegate(uint Ctrl, uint Value, uint MinValue, uint MaxValue);
        public delegate void set_pulse_picking_listDelegate(uint No);
        public delegate void set_softstart_level_listDelegate(uint Index, uint Level1, uint Level2, uint Level3);
        public delegate void set_softstart_mode_listDelegate(uint Mode, uint Number, uint Delay);
        public delegate void config_laser_signals_listDelegate(uint Config);
        public delegate void set_laser_timingDelegate(uint HalfPeriod, uint PulseLength1, uint PulseLength2, uint TimeBase);
        public delegate void n_fly_return_zDelegate(uint CardNo, int X, int Y, int Z);
        public delegate void n_fly_returnDelegate(uint CardNo, int X, int Y);
        public delegate void n_set_rot_center_listDelegate(uint CardNo, int X, int Y);
        public delegate void n_set_ext_start_delay_listDelegate(uint CardNo, int Delay, uint EncoderNo);
        public delegate void n_set_fly_xDelegate(uint CardNo, double ScaleX);
        public delegate void n_set_fly_yDelegate(uint CardNo, double ScaleY);
        public delegate void n_set_fly_zDelegate(uint CardNo, double ScaleZ, uint EndoderNo);
        public delegate void n_set_fly_rotDelegate(uint CardNo, double Resolution);
        public delegate void n_set_fly_2dDelegate(uint CardNo, double ScaleX, double ScaleY);
        public delegate void n_set_fly_x_posDelegate(uint CardNo, double ScaleX);
        public delegate void n_set_fly_y_posDelegate(uint CardNo, double ScaleY);
        public delegate void n_set_fly_rot_posDelegate(uint CardNo, double Resolution);
        public delegate void n_set_fly_limitsDelegate(uint CardNo, int Xmin, int Xmax, int Ymin, int Ymax);
        public delegate void n_set_fly_limits_zDelegate(uint CardNo, int Zmin, int Zmax);
        public delegate void n_if_fly_x_overflowDelegate(uint CardNo, int Mode);
        public delegate void n_if_fly_y_overflowDelegate(uint CardNo, int Mode);
        public delegate void n_if_fly_z_overflowDelegate(uint CardNo, int Mode);
        public delegate void n_if_not_fly_x_overflowDelegate(uint CardNo, int Mode);
        public delegate void n_if_not_fly_y_overflowDelegate(uint CardNo, int Mode);
        public delegate void n_if_not_fly_z_overflowDelegate(uint CardNo, int Mode);
        public delegate void n_clear_fly_overflowDelegate(uint CardNo, uint Mode);
        public delegate void n_set_mcbsp_x_listDelegate(uint CardNo, double ScaleX);
        public delegate void n_set_mcbsp_y_listDelegate(uint CardNo, double ScaleY);
        public delegate void n_set_mcbsp_rot_listDelegate(uint CardNo, double Resolution);
        public delegate void n_set_mcbsp_matrix_listDelegate(uint CardNo);
        public delegate void n_set_mcbsp_global_x_listDelegate(uint CardNo, double ScaleX);
        public delegate void n_set_mcbsp_global_y_listDelegate(uint CardNo, double ScaleY);
        public delegate void n_set_mcbsp_global_rot_listDelegate(uint CardNo, double Resolution);
        public delegate void n_set_mcbsp_global_matrix_listDelegate(uint CardNo);
        public delegate void n_set_mcbsp_in_listDelegate(uint CardNo, uint Mode, double Scale);
        public delegate void n_set_multi_mcbsp_in_listDelegate(uint CardNo, uint Ctrl, uint P, uint Mode);
        public delegate void n_wait_for_encoder_modeDelegate(uint CardNo, int Value, uint EncoderNo, int Mode);
        public delegate void n_wait_for_mcbspDelegate(uint CardNo, uint Axis, int Value, int Mode);
        public delegate void n_set_encoder_speedDelegate(uint CardNo, uint EncoderNo, double Speed, double Smooth);
        public delegate void n_get_mcbsp_listDelegate(uint CardNo);
        public delegate void n_store_encoderDelegate(uint CardNo, uint Pos);
        public delegate void n_wait_for_encoder_in_rangeDelegate(uint CardNo, int EncXmin, int EncXmax, int EncYmin, int EncYmax);
        public delegate void n_activate_fly_xyDelegate(uint CardNo, double ScaleX, double ScaleY);
        public delegate void n_activate_fly_2dDelegate(uint CardNo, double ScaleX, double ScaleY);
        public delegate void n_activate_fly_xy_encoderDelegate(uint CardNo, double ScaleX, double ScaleY, int EncX, int EncY);
        public delegate void n_activate_fly_2d_encoderDelegate(uint CardNo, double ScaleX, double ScaleY, int EncX, int EncY);
        public delegate void n_if_not_activatedDelegate(uint CardNo);
        public delegate void n_park_positionDelegate(uint CardNo, uint Mode, int X, int Y);
        public delegate void n_park_returnDelegate(uint CardNo, uint Mode, int X, int Y);
        public delegate void n_wait_for_encoderDelegate(uint CardNo, int Value, uint EncoderNo);
        public delegate void fly_return_zDelegate(int X, int Y, int Z);
        public delegate void fly_returnDelegate(int X, int Y);
        public delegate void set_rot_center_listDelegate(int X, int Y);
        public delegate void set_ext_start_delay_listDelegate(int Delay, uint EncoderNo);
        public delegate void set_fly_xDelegate(double ScaleX);
        public delegate void set_fly_yDelegate(double ScaleY);
        public delegate void set_fly_zDelegate(double ScaleZ, uint EncoderNo);
        public delegate void set_fly_rotDelegate(double Resolution);
        public delegate void set_fly_2dDelegate(double ScaleX, double ScaleY);
        public delegate void set_fly_x_posDelegate(double ScaleX);
        public delegate void set_fly_y_posDelegate(double ScaleY);
        public delegate void set_fly_rot_posDelegate(double Resolution);
        public delegate void set_fly_limitsDelegate(int Xmin, int Xmax, int Ymin, int Ymax);
        public delegate void set_fly_limits_zDelegate(int Zmin, int Zmax);
        public delegate void if_fly_x_overflowDelegate(int Mode);
        public delegate void if_fly_y_overflowDelegate(int Mode);
        public delegate void if_fly_z_overflowDelegate(int Mode);
        public delegate void if_not_fly_x_overflowDelegate(int Mode);
        public delegate void if_not_fly_y_overflowDelegate(int Mode);
        public delegate void if_not_fly_z_overflowDelegate(int Mode);
        public delegate void clear_fly_overflowDelegate(uint Mode);
        public delegate void set_mcbsp_x_listDelegate(double ScaleX);
        public delegate void set_mcbsp_y_listDelegate(double ScaleY);
        public delegate void set_mcbsp_rot_listDelegate(double Resolution);
        public delegate void set_mcbsp_matrix_listDelegate();
        public delegate void set_mcbsp_global_x_listDelegate(double ScaleX);
        public delegate void set_mcbsp_global_y_listDelegate(double ScaleY);
        public delegate void set_mcbsp_global_rot_listDelegate(double Resolution);
        public delegate void set_mcbsp_global_matrix_listDelegate();
        public delegate void set_mcbsp_in_listDelegate(uint Mode, double Scale);
        public delegate void set_multi_mcbsp_in_listDelegate(uint Ctrl, uint P, uint Mode);
        public delegate void wait_for_encoder_modeDelegate(int Value, uint EncoderNo, int Mode);
        public delegate void wait_for_mcbspDelegate(uint Axis, int Value, int Mode);
        public delegate void set_encoder_speedDelegate(uint EncoderNo, double Speed, double Smooth);
        public delegate void get_mcbsp_listDelegate();
        public delegate void store_encoderDelegate(uint Pos);
        public delegate void wait_for_encoder_in_rangeDelegate(int EncXmin, int EncXmax, int EncYmin, int EncYmax);
        public delegate void activate_fly_xyDelegate(double ScaleX, double ScaleY);
        public delegate void activate_fly_2dDelegate(double ScaleX, double ScaleY);
        public delegate void activate_fly_xy_encoderDelegate(double ScaleX, double ScaleY, int EncX, int EncY);
        public delegate void activate_fly_2d_encoderDelegate(double ScaleX, double ScaleY, int EncX, int EncY);
        public delegate void if_not_activatedDelegate();
        public delegate void park_positionDelegate(uint Mode, int X, int Y);
        public delegate void park_returnDelegate(uint Mode, int X, int Y);
        public delegate void wait_for_encoderDelegate(int Value, uint EncoderNo);
        public delegate void n_save_and_restart_timerDelegate(uint CardNo);
        public delegate void n_set_wobbelDelegate(uint CardNo, uint Transversal, uint Longitudinal, double Freq);
        public delegate void n_set_wobbel_modeDelegate(uint CardNo, uint Transversal, uint Longitudinal, double Freq, int Mode);
        public delegate void n_set_wobbel_mode_phaseDelegate(uint CardNo, uint Transversal, uint Longitudinal, double Freq, int Mode, double Phase);
        public delegate void n_set_wobbel_directionDelegate(uint CardNo, int dX, int dY);
        public delegate void n_set_wobbel_controlDelegate(uint CardNo, uint Ctrl, uint Value, uint MinValue, uint MaxValue);
        public delegate void n_set_wobbel_vectorDelegate(uint CardNo, double dTrans, double dLong, uint Period, double dPower);
        public delegate void n_set_wobbel_offsetDelegate(uint CardNo, int OffsetTrans, int OffsetLong);
        public delegate void n_load_wobbel_power_listDelegate(uint CardNo, uint TableNo, [MarshalAs(UnmanagedType.LPArray, SizeConst=SampleArraySize)]int[] Ptr, int Flag);
        public delegate void n_set_wobbel_power_angleDelegate(uint CardNo, uint Angle);
        public delegate void n_set_triggerDelegate(uint CardNo, uint Period, uint Signal1, uint Signal2);
        public delegate void n_set_trigger4Delegate(uint CardNo, uint Period, uint Signal1, uint Signal2, uint Signal3, uint Signal4);
        public delegate void n_set_pixel_line_3dDelegate(uint CardNo, uint Channel, uint HalfPeriod, double dX, double dY, double dZ);
        public delegate void n_set_pixel_lineDelegate(uint CardNo, uint Channel, uint HalfPeriod, double dX, double dY);
        public delegate void n_stretch_pixel_lineDelegate(uint CardNo, uint Delay, uint Period);
        public delegate void n_set_n_pixelDelegate(uint CardNo, uint PulseLength, uint AnalogOut, uint Number);
        public delegate void n_set_pixelDelegate(uint CardNo, uint PulseLength, uint AnalogOut);
        public delegate void n_rs232_write_text_listDelegate(uint CardNo, string pData);
        public delegate void n_set_mcbsp_outDelegate(uint CardNo, uint Signal1, uint Signal2);
        public delegate void n_set_mcbsp_out_ptr_listDelegate(uint CardNo, uint Number, [MarshalAs(UnmanagedType.LPArray, SizeConst=SignalSize2)]uint[] SignalPtr);
        public delegate void n_cammingDelegate(uint CardNo, uint FirstPos, uint NPos, uint No, uint Ctrl, double Scale, uint Code);
        public delegate void n_periodic_toggle_listDelegate(uint CardNo, uint Port, uint Mask, uint P1, uint P2, uint Count, uint Start);
        public delegate void n_micro_vector_abs_3dDelegate(uint CardNo, int X, int Y, int Z, int LasOn, int LasOf);
        public delegate void n_micro_vector_rel_3dDelegate(uint CardNo, int dX, int dY, int dZ, int LasOn, int LasOf);
        public delegate void n_micro_vector_absDelegate(uint CardNo, int X, int Y, int LasOn, int LasOf);
        public delegate void n_micro_vector_relDelegate(uint CardNo, int dX, int dY, int LasOn, int LasOf);
        public delegate void n_set_free_variable_listDelegate(uint CardNo, uint VarNo, uint Value);
        public delegate void n_jump_abs_drill_2Delegate(uint CardNo, int X, int Y, uint DrillTime, int XOff, int YOff);
        public delegate void n_jump_rel_drill_2Delegate(uint CardNo, int dX, int dY, uint DrillTime, int XOff, int YOff);
        public delegate void n_jump_abs_drillDelegate(uint CardNo, int X, int Y, uint DrillTime);
        public delegate void n_jump_rel_drillDelegate(uint CardNo, int dX, int dY, uint DrillTime);
        public delegate void save_and_restart_timerDelegate();
        public delegate void set_wobbelDelegate(uint Transversal, uint Longitudinal, double Freq);
        public delegate void set_wobbel_modeDelegate(uint Transversal, uint Longitudinal, double Freq, int Mode);
        public delegate void set_wobbel_mode_phaseDelegate(uint Transversal, uint Longitudinal, double Freq, int Mode, double Phase);
        public delegate void set_wobbel_directionDelegate(int dX, int dY);
        public delegate void set_wobbel_controlDelegate(uint Ctrl, uint Value, uint MinValue, uint MaxValue);
        public delegate void set_wobbel_vectorDelegate(double dTrans, double dLong, uint Period, double dPower);
        public delegate void set_wobbel_offsetDelegate(int OffsetTrans, int OffsetLong);
        public delegate void load_wobbel_power_listDelegate(uint TableNo, [MarshalAs(UnmanagedType.LPArray, SizeConst=SampleArraySize)]int[] Ptr, int Flag);
        public delegate void set_wobbel_power_angleDelegate(uint Angle);
        public delegate void set_triggerDelegate(uint Period, uint Signal1, uint Signal2);
        public delegate void set_trigger4Delegate(uint Period, uint Signal1, uint Signal2, uint Signal3, uint Signal4);
        public delegate void set_pixel_line_3dDelegate(uint Channel, uint HalfPeriod, double dX, double dY, double dZ);
        public delegate void set_pixel_lineDelegate(uint Channel, uint HalfPeriod, double dX, double dY);
        public delegate void stretch_pixel_lineDelegate(uint Delay, uint Period);
        public delegate void set_n_pixelDelegate(uint PulseLength, uint AnalogOut, uint Number);
        public delegate void set_pixelDelegate(uint PulseLength, uint AnalogOut);
        public delegate void rs232_write_text_listDelegate(string pData);
        public delegate void set_mcbsp_outDelegate(uint Signal1, uint Signal2);
        public delegate void set_mcbsp_out_ptr_listDelegate(uint Number, [MarshalAs(UnmanagedType.LPArray, SizeConst=SignalSize2)]uint[] SignalPtr);
        public delegate void cammingDelegate(uint FirstPos, uint NPos, uint No, uint Ctrl, double Scale, uint Code);
        public delegate void periodic_toggle_listDelegate(uint Port, uint Mask, uint P1, uint P2, uint Count, uint Start);
        public delegate void micro_vector_abs_3dDelegate(int X, int Y, int Z, int LasOn, int LasOf);
        public delegate void micro_vector_rel_3dDelegate(int dX, int dY, int dZ, int LasOn, int LasOf);
        public delegate void micro_vector_absDelegate(int X, int Y, int LasOn, int LasOf);
        public delegate void micro_vector_relDelegate(int dX, int dY, int LasOn, int LasOf);
        public delegate void set_free_variable_listDelegate(uint VarNo, uint Value);
        public delegate void jump_abs_drill_2Delegate(int X, int Y, uint DrillTime, int XOff, int YOff);
        public delegate void jump_rel_drill_2Delegate(int dX, int dY, uint DrillTime, int XOff, int YOff);
        public delegate void jump_abs_drillDelegate(int X, int Y, uint DrillTime);
        public delegate void jump_rel_drillDelegate(int dX, int dY, uint DrillTime);
        public delegate void n_timed_mark_abs_3dDelegate(uint CardNo, int X, int Y, int Z, double T);
        public delegate void n_timed_mark_rel_3dDelegate(uint CardNo, int dX, int dY, int dZ, double T);
        public delegate void n_timed_mark_absDelegate(uint CardNo, int X, int Y, double T);
        public delegate void n_timed_mark_relDelegate(uint CardNo, int dX, int dY, double T);
        public delegate void timed_mark_abs_3dDelegate(int X, int Y, int Z, double T);
        public delegate void timed_mark_rel_3dDelegate(int dX, int dY, int dZ, double T);
        public delegate void timed_mark_absDelegate(int X, int Y, double T);
        public delegate void timed_mark_relDelegate(int dX, int dY, double T);
        public delegate void n_mark_abs_3dDelegate(uint CardNo, int X, int Y, int Z);
        public delegate void n_mark_rel_3dDelegate(uint CardNo, int dX, int dY, int dZ);
        public delegate void n_mark_absDelegate(uint CardNo, int X, int Y);
        public delegate void n_mark_relDelegate(uint CardNo, int dX, int dY);
        public delegate void mark_abs_3dDelegate(int X, int Y, int Z);
        public delegate void mark_rel_3dDelegate(int dX, int dY, int dZ);
        public delegate void mark_absDelegate(int X, int Y);
        public delegate void mark_relDelegate(int dX, int dY);
        public delegate void n_timed_jump_abs_3dDelegate(uint CardNo, int X, int Y, int Z, double T);
        public delegate void n_timed_jump_rel_3dDelegate(uint CardNo, int dX, int dY, int dZ, double T);
        public delegate void n_timed_jump_absDelegate(uint CardNo, int X, int Y, double T);
        public delegate void n_timed_jump_relDelegate(uint CardNo, int dX, int dY, double T);
        public delegate void timed_jump_abs_3dDelegate(int X, int Y, int Z, double T);
        public delegate void timed_jump_rel_3dDelegate(int dX, int dY, int dZ, double T);
        public delegate void timed_jump_absDelegate(int X, int Y, double T);
        public delegate void timed_jump_relDelegate(int dX, int dY, double T);
        public delegate void n_jump_abs_3dDelegate(uint CardNo, int X, int Y, int Z);
        public delegate void n_jump_rel_3dDelegate(uint CardNo, int dX, int dY, int dZ);
        public delegate void n_jump_absDelegate(uint CardNo, int X, int Y);
        public delegate void n_jump_relDelegate(uint CardNo, int dX, int dY);
        public delegate void jump_abs_3dDelegate(int X, int Y, int Z);
        public delegate void jump_rel_3dDelegate(int dX, int dY, int dZ);
        public delegate void jump_absDelegate(int X, int Y);
        public delegate void jump_relDelegate(int dX, int dY);
        public delegate void n_para_mark_abs_3dDelegate(uint CardNo, int X, int Y, int Z, uint P);
        public delegate void n_para_mark_rel_3dDelegate(uint CardNo, int dX, int dY, int dZ, uint P);
        public delegate void n_para_mark_absDelegate(uint CardNo, int X, int Y, uint P);
        public delegate void n_para_mark_relDelegate(uint CardNo, int dX, int dY, uint P);
        public delegate void para_mark_abs_3dDelegate(int X, int Y, int Z, uint P);
        public delegate void para_mark_rel_3dDelegate(int dX, int dY, int dZ, uint P);
        public delegate void para_mark_absDelegate(int X, int Y, uint P);
        public delegate void para_mark_relDelegate(int dX, int dY, uint P);
        public delegate void n_para_jump_abs_3dDelegate(uint CardNo, int X, int Y, int Z, uint P);
        public delegate void n_para_jump_rel_3dDelegate(uint CardNo, int dX, int dY, int dZ, uint P);
        public delegate void n_para_jump_absDelegate(uint CardNo, int X, int Y, uint P);
        public delegate void n_para_jump_relDelegate(uint CardNo, int dX, int dY, uint P);
        public delegate void para_jump_abs_3dDelegate(int X, int Y, int Z, uint P);
        public delegate void para_jump_rel_3dDelegate(int dX, int dY, int dZ, uint P);
        public delegate void para_jump_absDelegate(int X, int Y, uint P);
        public delegate void para_jump_relDelegate(int dX, int dY, uint P);
        public delegate void n_timed_para_mark_abs_3dDelegate(uint CardNo, int X, int Y, int Z, uint P, double T);
        public delegate void n_timed_para_mark_rel_3dDelegate(uint CardNo, int dX, int dY, int dZ, uint P, double T);
        public delegate void n_timed_para_jump_abs_3dDelegate(uint CardNo, int X, int Y, int Z, uint P, double T);
        public delegate void n_timed_para_jump_rel_3dDelegate(uint CardNo, int dX, int dY, int dZ, uint P, double T);
        public delegate void n_timed_para_mark_absDelegate(uint CardNo, int X, int Y, uint P, double T);
        public delegate void n_timed_para_mark_relDelegate(uint CardNo, int dX, int dY, uint P, double T);
        public delegate void n_timed_para_jump_absDelegate(uint CardNo, int X, int Y, uint P, double T);
        public delegate void n_timed_para_jump_relDelegate(uint CardNo, int dX, int dY, uint P, double T);
        public delegate void timed_para_mark_abs_3dDelegate(int X, int Y, int Z, uint P, double T);
        public delegate void timed_para_mark_rel_3dDelegate(int dX, int dY, int dZ, uint P, double T);
        public delegate void timed_para_jump_abs_3dDelegate(int X, int Y, int Z, uint P, double T);
        public delegate void timed_para_jump_rel_3dDelegate(int dX, int dY, int dZ, uint P, double T);
        public delegate void timed_para_mark_absDelegate(int X, int Y, uint P, double T);
        public delegate void timed_para_mark_relDelegate(int dX, int dY, uint P, double T);
        public delegate void timed_para_jump_absDelegate(int X, int Y, uint P, double T);
        public delegate void timed_para_jump_relDelegate(int dX, int dY, uint P, double T);
        public delegate void n_set_defocus_listDelegate(uint CardNo, int Shift);
        public delegate void n_set_defocus_offset_listDelegate(uint CardNo, int Shift);
        public delegate void n_set_zoom_listDelegate(uint CardNo, uint Zoom);
        public delegate void set_defocus_listDelegate(int Shift);
        public delegate void set_defocus_offset_listDelegate(int Shift);
        public delegate void set_zoom_listDelegate(uint Zoom);
        public delegate void n_timed_arc_absDelegate(uint CardNo, int X, int Y, double Angle, double T);
        public delegate void n_timed_arc_relDelegate(uint CardNo, int dX, int dY, double Angle, double T);
        public delegate void timed_arc_absDelegate(int X, int Y, double Angle, double T);
        public delegate void timed_arc_relDelegate(int dX, int dY, double Angle, double T);
        public delegate void n_arc_abs_3dDelegate(uint CardNo, int X, int Y, int Z, double Angle);
        public delegate void n_arc_rel_3dDelegate(uint CardNo, int dX, int dY, int dZ, double Angle);
        public delegate void n_arc_absDelegate(uint CardNo, int X, int Y, double Angle);
        public delegate void n_arc_relDelegate(uint CardNo, int dX, int dY, double Angle);
        public delegate void n_set_ellipseDelegate(uint CardNo, uint A, uint B, double Phi0, double Phi);
        public delegate void n_mark_ellipse_absDelegate(uint CardNo, int X, int Y, double Alpha);
        public delegate void n_mark_ellipse_relDelegate(uint CardNo, int dX, int dY, double Alpha);
        public delegate void arc_abs_3dDelegate(int X, int Y, int Z, double Angle);
        public delegate void arc_rel_3dDelegate(int dX, int dY, int dZ, double Angle);
        public delegate void arc_absDelegate(int X, int Y, double Angle);
        public delegate void arc_relDelegate(int dX, int dY, double Angle);
        public delegate void set_ellipseDelegate(uint A, uint B, double Phi0, double Phi);
        public delegate void mark_ellipse_absDelegate(int X, int Y, double Alpha);
        public delegate void mark_ellipse_relDelegate(int dX, int dY, double Alpha);
        public delegate void n_set_offset_xyz_listDelegate(uint CardNo, uint HeadNo, int XOffset, int YOffset, int ZOffset, uint at_once);
        public delegate void n_set_offset_listDelegate(uint CardNo, uint HeadNo, int XOffset, int YOffset, uint at_once);
        public delegate void n_set_matrix_listDelegate(uint CardNo, uint HeadNo, uint Ind1, uint Ind2, double Mij, uint at_once);
        public delegate void n_set_angle_listDelegate(uint CardNo, uint HeadNo, double Angle, uint at_once);
        public delegate void n_set_scale_listDelegate(uint CardNo, uint HeadNo, double Scale, uint at_once);
        public delegate void n_apply_mcbsp_listDelegate(uint CardNo, uint HeadNo, uint at_once);
        public delegate void set_offset_xyz_listDelegate(uint HeadNo, int XOffset, int YOffset, int ZOffset, uint at_once);
        public delegate void set_offset_listDelegate(uint HeadNo, int XOffset, int YOffset, uint at_once);
        public delegate void set_matrix_listDelegate(uint HeadNo, uint Ind1, uint Ind2, double Mij, uint at_once);
        public delegate void set_angle_listDelegate(uint HeadNo, double Angle, uint at_once);
        public delegate void set_scale_listDelegate(uint HeadNo, double Scale, uint at_once);
        public delegate void apply_mcbsp_listDelegate(uint HeadNo, uint at_once);
        public delegate void n_set_mark_speedDelegate(uint CardNo, double Speed);
        public delegate void n_set_jump_speedDelegate(uint CardNo, double Speed);
        public delegate void n_set_sky_writing_para_listDelegate(uint CardNo, double Timelag, int LaserOnShift, uint Nprev, uint Npost);
        public delegate void n_set_sky_writing_listDelegate(uint CardNo, double Timelag, int LaserOnShift);
        public delegate void n_set_sky_writing_limit_listDelegate(uint CardNo, double CosAngle);
        public delegate void n_set_sky_writing_mode_listDelegate(uint CardNo, uint Mode);
        public delegate void n_set_scanner_delaysDelegate(uint CardNo, uint Jump, uint Mark, uint Polygon);
        public delegate void n_set_jump_mode_listDelegate(uint CardNo, int Flag);
        public delegate void n_enduring_wobbelDelegate(uint CardNo);
        public delegate void n_set_delay_mode_listDelegate(uint CardNo, uint VarPoly, uint DirectMove3D, uint EdgeLevel, uint MinJumpDelay, uint JumpLengthLimit);
        public delegate void set_mark_speedDelegate(double Speed);
        public delegate void set_jump_speedDelegate(double Speed);
        public delegate void set_sky_writing_para_listDelegate(double Timelag, int LaserOnShift, uint Nprev, uint Npost);
        public delegate void set_sky_writing_listDelegate(double Timelag, int LaserOnShift);
        public delegate void set_sky_writing_limit_listDelegate(double CosAngle);
        public delegate void set_sky_writing_mode_listDelegate(uint Mode);
        public delegate void set_scanner_delaysDelegate(uint Jump, uint Mark, uint Polygon);
        public delegate void set_jump_mode_listDelegate(int Flag);
        public delegate void enduring_wobbelDelegate();
        public delegate void set_delay_mode_listDelegate(uint VarPoly, uint DirectMove3D, uint EdgeLevel, uint MinJumpDelay, uint JumpLengthLimit);
        public delegate void n_stepper_enable_listDelegate(uint CardNo, int Enable1, int Enable2);
        public delegate void n_stepper_control_listDelegate(uint CardNo, int Period1, int Period2);
        public delegate void n_stepper_abs_no_listDelegate(uint CardNo, uint No, int Pos);
        public delegate void n_stepper_rel_no_listDelegate(uint CardNo, uint No, int dPos);
        public delegate void n_stepper_abs_listDelegate(uint CardNo, int Pos1, int Pos2);
        public delegate void n_stepper_rel_listDelegate(uint CardNo, int dPos1, int dPos2);
        public delegate void n_stepper_waitDelegate(uint CardNo, uint No);
        public delegate void stepper_enable_listDelegate(int Enable1, int Enable2);
        public delegate void stepper_control_listDelegate(int Period1, int Period2);
        public delegate void stepper_abs_no_listDelegate(uint No, int Pos);
        public delegate void stepper_rel_no_listDelegate(uint No, int dPos);
        public delegate void stepper_abs_listDelegate(int Pos1, int Pos2);
        public delegate void stepper_rel_listDelegate(int dPos1, int dPos2);
        public delegate void stepper_waitDelegate(uint No);
        #endregion

        #region RTC5UserFunctions
        /// <summary>
        ///  uint init_rtc5_dll();
        /// </summary>
        public static init_rtc5_dllDelegate init_rtc5_dll;

        /// <summary>
        ///  void free_rtc5_dll();
        /// </summary>
        public static free_rtc5_dllDelegate free_rtc5_dll;

        /// <summary>
        ///  void set_rtc4_mode();
        /// </summary>
        public static set_rtc4_modeDelegate set_rtc4_mode;

        /// <summary>
        ///  void set_rtc5_mode();
        /// </summary>
        public static set_rtc5_modeDelegate set_rtc5_mode;

        /// <summary>
        ///  uint get_rtc_mode();
        /// </summary>
        public static get_rtc_modeDelegate get_rtc_mode;

        /// <summary>
        ///  uint n_get_error(uint CardNo);
        /// </summary>
        public static n_get_errorDelegate n_get_error;

        /// <summary>
        ///  uint n_get_last_error(uint CardNo);
        /// </summary>
        public static n_get_last_errorDelegate n_get_last_error;

        /// <summary>
        ///  void n_reset_error(uint CardNo, uint Code);
        /// </summary>
        public static n_reset_errorDelegate n_reset_error;

        /// <summary>
        ///  uint n_set_verify(uint CardNo, uint Verify);
        /// </summary>
        public static n_set_verifyDelegate n_set_verify;

        /// <summary>
        ///  uint get_error();
        /// </summary>
        public static get_errorDelegate get_error;

        /// <summary>
        ///  uint get_last_error();
        /// </summary>
        public static get_last_errorDelegate get_last_error;

        /// <summary>
        ///  void reset_error(uint Code);
        /// </summary>
        public static reset_errorDelegate reset_error;

        /// <summary>
        ///  uint set_verify(uint Verify);
        /// </summary>
        public static set_verifyDelegate set_verify;

        /// <summary>
        ///  uint verify_checksum(string Name);
        /// </summary>
        public static verify_checksumDelegate verify_checksum;

        /// <summary>
        ///  uint read_abc_from_file(string Name, out double A, out double B, out double C);
        /// </summary>
        public static read_abc_from_fileDelegate read_abc_from_file;

        /// <summary>
        ///  uint write_abc_to_file(string Name, double A, double B, double C);
        /// </summary>
        public static write_abc_to_fileDelegate write_abc_to_file;

        /// <summary>
        ///  uint rtc5_count_cards();
        /// </summary>
        public static rtc5_count_cardsDelegate rtc5_count_cards;

        /// <summary>
        ///  uint acquire_rtc(uint CardNo);
        /// </summary>
        public static acquire_rtcDelegate acquire_rtc;

        /// <summary>
        ///  uint release_rtc(uint CardNo);
        /// </summary>
        public static release_rtcDelegate release_rtc;

        /// <summary>
        ///  uint select_rtc(uint CardNo);
        /// </summary>
        public static select_rtcDelegate select_rtc;

        /// <summary>
        ///  uint get_dll_version();
        /// </summary>
        public static get_dll_versionDelegate get_dll_version;

        /// <summary>
        ///  uint n_get_serial_number(uint CardNo);
        /// </summary>
        public static n_get_serial_numberDelegate n_get_serial_number;

        /// <summary>
        ///  uint n_get_hex_version(uint CardNo);
        /// </summary>
        public static n_get_hex_versionDelegate n_get_hex_version;

        /// <summary>
        ///  uint n_get_rtc_version(uint CardNo);
        /// </summary>
        public static n_get_rtc_versionDelegate n_get_rtc_version;

        /// <summary>
        ///  uint get_serial_number();
        /// </summary>
        public static get_serial_numberDelegate get_serial_number;

        /// <summary>
        ///  uint get_hex_version();
        /// </summary>
        public static get_hex_versionDelegate get_hex_version;

        /// <summary>
        ///  uint get_rtc_version();
        /// </summary>
        public static get_rtc_versionDelegate get_rtc_version;

        /// <summary>
        ///  uint n_load_program_file(uint CardNo, string Path);
        /// </summary>
        public static n_load_program_fileDelegate n_load_program_file;

        /// <summary>
        ///  void n_sync_slaves(uint CardNo);
        /// </summary>
        public static n_sync_slavesDelegate n_sync_slaves;

        /// <summary>
        ///  uint n_get_sync_status(uint CardNo);
        /// </summary>
        public static n_get_sync_statusDelegate n_get_sync_status;

        /// <summary>
        ///  uint n_load_correction_file(uint CardNo, string Name, uint No, uint Dim);
        /// </summary>
        public static n_load_correction_fileDelegate n_load_correction_file;

        /// <summary>
        ///  uint n_load_zoom_correction_file(uint CardNo, string Name, uint No);
        /// </summary>
        public static n_load_zoom_correction_fileDelegate n_load_zoom_correction_file;

        /// <summary>
        ///  uint n_load_z_table(uint CardNo, double A, double B, double C);
        /// </summary>
        public static n_load_z_tableDelegate n_load_z_table;

        /// <summary>
        ///  void n_select_cor_table(uint CardNo, uint HeadA, uint HeadB);
        /// </summary>
        public static n_select_cor_tableDelegate n_select_cor_table;

        /// <summary>
        ///  uint n_set_dsp_mode(uint CardNo, uint Mode);
        /// </summary>
        public static n_set_dsp_modeDelegate n_set_dsp_mode;

        /// <summary>
        ///  int n_load_stretch_table(uint CardNo, string Name, int No);
        /// </summary>
        public static n_load_stretch_tableDelegate n_load_stretch_table;

        /// <summary>
        ///  void n_number_of_correction_tables(uint CardNo, uint Number);
        /// </summary>
        public static n_number_of_correction_tablesDelegate n_number_of_correction_tables;

        /// <summary>
        ///  double n_get_head_para(uint CardNo, uint HeadNo, uint ParaNo);
        /// </summary>
        public static n_get_head_paraDelegate n_get_head_para;

        /// <summary>
        ///  double n_get_table_para(uint CardNo, uint TableNo, uint ParaNo);
        /// </summary>
        public static n_get_table_paraDelegate n_get_table_para;

        /// <summary>
        ///  uint load_program_file(string Path);
        /// </summary>
        public static load_program_fileDelegate load_program_file;

        /// <summary>
        ///  void sync_slaves();
        /// </summary>
        public static sync_slavesDelegate sync_slaves;

        /// <summary>
        ///  uint get_sync_status();
        /// </summary>
        public static get_sync_statusDelegate get_sync_status;

        /// <summary>
        ///  uint load_correction_file(string Name, uint No, uint Dim);
        /// </summary>
        public static load_correction_fileDelegate load_correction_file;

        /// <summary>
        ///  uint load_zoom_correction_file(string Name, uint No);
        /// </summary>
        public static load_zoom_correction_fileDelegate load_zoom_correction_file;

        /// <summary>
        ///  uint load_z_table(double A, double B, double C);
        /// </summary>
        public static load_z_tableDelegate load_z_table;

        /// <summary>
        ///  void select_cor_table(uint HeadA, uint HeadB);
        /// </summary>
        public static select_cor_tableDelegate select_cor_table;

        /// <summary>
        ///  uint set_dsp_mode(uint Mode);
        /// </summary>
        public static set_dsp_modeDelegate set_dsp_mode;

        /// <summary>
        ///  int load_stretch_table(string Name, int No);
        /// </summary>
        public static load_stretch_tableDelegate load_stretch_table;

        /// <summary>
        ///  void number_of_correction_tables(uint Number);
        /// </summary>
        public static number_of_correction_tablesDelegate number_of_correction_tables;

        /// <summary>
        ///  double get_head_para(uint HeadNo, uint ParaNo);
        /// </summary>
        public static get_head_paraDelegate get_head_para;

        /// <summary>
        ///  double get_table_para(uint TableNo, uint ParaNo);
        /// </summary>
        public static get_table_paraDelegate get_table_para;

        /// <summary>
        ///  void n_config_list(uint CardNo, uint Mem1, uint Mem2);
        /// </summary>
        public static n_config_listDelegate n_config_list;

        /// <summary>
        ///  void n_get_config_list(uint CardNo);
        /// </summary>
        public static n_get_config_listDelegate n_get_config_list;

        /// <summary>
        ///  uint n_save_disk(uint CardNo, string Name, uint Mode);
        /// </summary>
        public static n_save_diskDelegate n_save_disk;

        /// <summary>
        ///  uint n_load_disk(uint CardNo, string Name, uint Mode);
        /// </summary>
        public static n_load_diskDelegate n_load_disk;

        /// <summary>
        ///  uint n_get_list_space(uint CardNo);
        /// </summary>
        public static n_get_list_spaceDelegate n_get_list_space;

        /// <summary>
        ///  void config_list(uint Mem1, uint Mem2);
        /// </summary>
        public static config_listDelegate config_list;

        /// <summary>
        ///  void get_config_list();
        /// </summary>
        public static get_config_listDelegate get_config_list;

        /// <summary>
        ///  uint save_disk(string Name, uint Mode);
        /// </summary>
        public static save_diskDelegate save_disk;

        /// <summary>
        ///  uint load_disk(string Name, uint Mode);
        /// </summary>
        public static load_diskDelegate load_disk;

        /// <summary>
        ///  uint get_list_space();
        /// </summary>
        public static get_list_spaceDelegate get_list_space;

        /// <summary>
        ///  void n_set_start_list_pos(uint CardNo, uint ListNo, uint Pos);
        /// </summary>
        public static n_set_start_list_posDelegate n_set_start_list_pos;

        /// <summary>
        ///  void n_set_start_list(uint CardNo, uint ListNo);
        /// </summary>
        public static n_set_start_listDelegate n_set_start_list;

        /// <summary>
        ///  void n_set_start_list_1(uint CardNo);
        /// </summary>
        public static n_set_start_list_1Delegate n_set_start_list_1;

        /// <summary>
        ///  void n_set_start_list_2(uint CardNo);
        /// </summary>
        public static n_set_start_list_2Delegate n_set_start_list_2;

        /// <summary>
        ///  void n_set_input_pointer(uint CardNo, uint Pos);
        /// </summary>
        public static n_set_input_pointerDelegate n_set_input_pointer;

        /// <summary>
        ///  uint n_load_list(uint CardNo, uint ListNo, uint Pos);
        /// </summary>
        public static n_load_listDelegate n_load_list;

        /// <summary>
        ///  void n_load_sub(uint CardNo, uint Index);
        /// </summary>
        public static n_load_subDelegate n_load_sub;

        /// <summary>
        ///  void n_load_char(uint CardNo, uint Char);
        /// </summary>
        public static n_load_charDelegate n_load_char;

        /// <summary>
        ///  void n_load_text_table(uint CardNo, uint Index);
        /// </summary>
        public static n_load_text_tableDelegate n_load_text_table;

        /// <summary>
        ///  void n_get_list_pointer(uint CardNo, out uint ListNo, out uint Pos);
        /// </summary>
        public static n_get_list_pointerDelegate n_get_list_pointer;

        /// <summary>
        ///  uint n_get_input_pointer(uint CardNo);
        /// </summary>
        public static n_get_input_pointerDelegate n_get_input_pointer;

        /// <summary>
        ///  void set_start_list_pos(uint ListNo, uint Pos);
        /// </summary>
        public static set_start_list_posDelegate set_start_list_pos;

        /// <summary>
        ///  void set_start_list(uint ListNo);
        /// </summary>
        public static set_start_listDelegate set_start_list;

        /// <summary>
        ///  void set_start_list_1();
        /// </summary>
        public static set_start_list_1Delegate set_start_list_1;

        /// <summary>
        ///  void set_start_list_2();
        /// </summary>
        public static set_start_list_2Delegate set_start_list_2;

        /// <summary>
        ///  void set_input_pointer(uint Pos);
        /// </summary>
        public static set_input_pointerDelegate set_input_pointer;

        /// <summary>
        ///  uint load_list(uint ListNo, uint Pos);
        /// </summary>
        public static load_listDelegate load_list;

        /// <summary>
        ///  void load_sub(uint Index);
        /// </summary>
        public static load_subDelegate load_sub;

        /// <summary>
        ///  void load_char(uint Char);
        /// </summary>
        public static load_charDelegate load_char;

        /// <summary>
        ///  void load_text_table(uint Index);
        /// </summary>
        public static load_text_tableDelegate load_text_table;

        /// <summary>
        ///  void get_list_pointer(out uint ListNo, out uint Pos);
        /// </summary>
        public static get_list_pointerDelegate get_list_pointer;

        /// <summary>
        ///  uint get_input_pointer();
        /// </summary>
        public static get_input_pointerDelegate get_input_pointer;

        /// <summary>
        ///  void n_execute_list_pos(uint CardNo, uint ListNo, uint Pos);
        /// </summary>
        public static n_execute_list_posDelegate n_execute_list_pos;

        /// <summary>
        ///  void n_execute_at_pointer(uint CardNo, uint Pos);
        /// </summary>
        public static n_execute_at_pointerDelegate n_execute_at_pointer;

        /// <summary>
        ///  void n_execute_list(uint CardNo, uint ListNo);
        /// </summary>
        public static n_execute_listDelegate n_execute_list;

        /// <summary>
        ///  void n_execute_list_1(uint CardNo);
        /// </summary>
        public static n_execute_list_1Delegate n_execute_list_1;

        /// <summary>
        ///  void n_execute_list_2(uint CardNo);
        /// </summary>
        public static n_execute_list_2Delegate n_execute_list_2;

        /// <summary>
        ///  void n_get_out_pointer(uint CardNo, out uint ListNo, out uint Pos);
        /// </summary>
        public static n_get_out_pointerDelegate n_get_out_pointer;

        /// <summary>
        ///  void execute_list_pos(uint ListNo, uint Pos);
        /// </summary>
        public static execute_list_posDelegate execute_list_pos;

        /// <summary>
        ///  void execute_at_pointer(uint Pos);
        /// </summary>
        public static execute_at_pointerDelegate execute_at_pointer;

        /// <summary>
        ///  void execute_list(uint ListNo);
        /// </summary>
        public static execute_listDelegate execute_list;

        /// <summary>
        ///  void execute_list_1();
        /// </summary>
        public static execute_list_1Delegate execute_list_1;

        /// <summary>
        ///  void execute_list_2();
        /// </summary>
        public static execute_list_2Delegate execute_list_2;

        /// <summary>
        ///  void get_out_pointer(out uint ListNo, out uint Pos);
        /// </summary>
        public static get_out_pointerDelegate get_out_pointer;

        /// <summary>
        ///  void n_auto_change_pos(uint CardNo, uint Pos);
        /// </summary>
        public static n_auto_change_posDelegate n_auto_change_pos;

        /// <summary>
        ///  void n_start_loop(uint CardNo);
        /// </summary>
        public static n_start_loopDelegate n_start_loop;

        /// <summary>
        ///  void n_quit_loop(uint CardNo);
        /// </summary>
        public static n_quit_loopDelegate n_quit_loop;

        /// <summary>
        ///  void n_pause_list(uint CardNo);
        /// </summary>
        public static n_pause_listDelegate n_pause_list;

        /// <summary>
        ///  void n_restart_list(uint CardNo);
        /// </summary>
        public static n_restart_listDelegate n_restart_list;

        /// <summary>
        ///  void n_release_wait(uint CardNo);
        /// </summary>
        public static n_release_waitDelegate n_release_wait;

        /// <summary>
        ///  void n_stop_execution(uint CardNo);
        /// </summary>
        public static n_stop_executionDelegate n_stop_execution;

        /// <summary>
        ///  void n_set_pause_list_cond(uint CardNo, uint Mask1, uint Mask0);
        /// </summary>
        public static n_set_pause_list_condDelegate n_set_pause_list_cond;

        /// <summary>
        ///  void n_set_pause_list_not_cond(uint CardNo, uint Mask1, uint Mask0);
        /// </summary>
        public static n_set_pause_list_not_condDelegate n_set_pause_list_not_cond;

        /// <summary>
        ///  void n_auto_change(uint CardNo);
        /// </summary>
        public static n_auto_changeDelegate n_auto_change;

        /// <summary>
        ///  void n_stop_list(uint CardNo);
        /// </summary>
        public static n_stop_listDelegate n_stop_list;

        /// <summary>
        ///  uint n_get_wait_status(uint CardNo);
        /// </summary>
        public static n_get_wait_statusDelegate n_get_wait_status;

        /// <summary>
        ///  uint n_read_status(uint CardNo);
        /// </summary>
        public static n_read_statusDelegate n_read_status;

        /// <summary>
        ///  void n_get_status(uint CardNo, out uint Status, out uint Pos);
        /// </summary>
        public static n_get_statusDelegate n_get_status;

        /// <summary>
        ///  void auto_change_pos(uint Pos);
        /// </summary>
        public static auto_change_posDelegate auto_change_pos;

        /// <summary>
        ///  void start_loop();
        /// </summary>
        public static start_loopDelegate start_loop;

        /// <summary>
        ///  void quit_loop();
        /// </summary>
        public static quit_loopDelegate quit_loop;

        /// <summary>
        ///  void pause_list();
        /// </summary>
        public static pause_listDelegate pause_list;

        /// <summary>
        ///  void restart_list();
        /// </summary>
        public static restart_listDelegate restart_list;

        /// <summary>
        ///  void release_wait();
        /// </summary>
        public static release_waitDelegate release_wait;

        /// <summary>
        ///  void stop_execution();
        /// </summary>
        public static stop_executionDelegate stop_execution;

        /// <summary>
        ///  void set_pause_list_cond(uint Mask1, uint Mask0);
        /// </summary>
        public static set_pause_list_condDelegate set_pause_list_cond;

        /// <summary>
        ///  void set_pause_list_not_cond(uint Mask1, uint Mask0);
        /// </summary>
        public static set_pause_list_not_condDelegate set_pause_list_not_cond;

        /// <summary>
        ///  void auto_change();
        /// </summary>
        public static auto_changeDelegate auto_change;

        /// <summary>
        ///  void stop_list();
        /// </summary>
        public static stop_listDelegate stop_list;

        /// <summary>
        ///  uint get_wait_status();
        /// </summary>
        public static get_wait_statusDelegate get_wait_status;

        /// <summary>
        ///  uint read_status();
        /// </summary>
        public static read_statusDelegate read_status;

        /// <summary>
        ///  void get_status(out uint Status, out uint Pos);
        /// </summary>
        public static get_statusDelegate get_status;

        /// <summary>
        ///  void n_set_extstartpos(uint CardNo, uint Pos);
        /// </summary>
        public static n_set_extstartposDelegate n_set_extstartpos;

        /// <summary>
        ///  void n_set_max_counts(uint CardNo, uint Counts);
        /// </summary>
        public static n_set_max_countsDelegate n_set_max_counts;

        /// <summary>
        ///  void n_set_control_mode(uint CardNo, uint Mode);
        /// </summary>
        public static n_set_control_modeDelegate n_set_control_mode;

        /// <summary>
        ///  void n_simulate_ext_stop(uint CardNo);
        /// </summary>
        public static n_simulate_ext_stopDelegate n_simulate_ext_stop;

        /// <summary>
        ///  void n_simulate_ext_start_ctrl(uint CardNo);
        /// </summary>
        public static n_simulate_ext_start_ctrlDelegate n_simulate_ext_start_ctrl;

        /// <summary>
        ///  uint n_get_counts(uint CardNo);
        /// </summary>
        public static n_get_countsDelegate n_get_counts;

        /// <summary>
        ///  uint n_get_startstop_info(uint CardNo);
        /// </summary>
        public static n_get_startstop_infoDelegate n_get_startstop_info;

        /// <summary>
        ///  void set_extstartpos(uint Pos);
        /// </summary>
        public static set_extstartposDelegate set_extstartpos;

        /// <summary>
        ///  void set_max_counts(uint Counts);
        /// </summary>
        public static set_max_countsDelegate set_max_counts;

        /// <summary>
        ///  void set_control_mode(uint Mode);
        /// </summary>
        public static set_control_modeDelegate set_control_mode;

        /// <summary>
        ///  void simulate_ext_stop();
        /// </summary>
        public static simulate_ext_stopDelegate simulate_ext_stop;

        /// <summary>
        ///  void simulate_ext_start_ctrl();
        /// </summary>
        public static simulate_ext_start_ctrlDelegate simulate_ext_start_ctrl;

        /// <summary>
        ///  uint get_counts();
        /// </summary>
        public static get_countsDelegate get_counts;

        /// <summary>
        ///  uint get_startstop_info();
        /// </summary>
        public static get_startstop_infoDelegate get_startstop_info;

        /// <summary>
        ///  void n_copy_dst_src(uint CardNo, uint Dst, uint Src, uint Mode);
        /// </summary>
        public static n_copy_dst_srcDelegate n_copy_dst_src;

        /// <summary>
        ///  void n_set_char_pointer(uint CardNo, uint Char, uint Pos);
        /// </summary>
        public static n_set_char_pointerDelegate n_set_char_pointer;

        /// <summary>
        ///  void n_set_sub_pointer(uint CardNo, uint Index, uint Pos);
        /// </summary>
        public static n_set_sub_pointerDelegate n_set_sub_pointer;

        /// <summary>
        ///  void n_set_text_table_pointer(uint CardNo, uint Index, uint Pos);
        /// </summary>
        public static n_set_text_table_pointerDelegate n_set_text_table_pointer;

        /// <summary>
        ///  void n_set_char_table(uint CardNo, uint Index, uint Pos);
        /// </summary>
        public static n_set_char_tableDelegate n_set_char_table;

        /// <summary>
        ///  uint n_get_char_pointer(uint CardNo, uint Char);
        /// </summary>
        public static n_get_char_pointerDelegate n_get_char_pointer;

        /// <summary>
        ///  uint n_get_sub_pointer(uint CardNo, uint Index);
        /// </summary>
        public static n_get_sub_pointerDelegate n_get_sub_pointer;

        /// <summary>
        ///  uint n_get_text_table_pointer(uint CardNo, uint Index);
        /// </summary>
        public static n_get_text_table_pointerDelegate n_get_text_table_pointer;

        /// <summary>
        ///  void copy_dst_src(uint Dst, uint Src, uint Mode);
        /// </summary>
        public static copy_dst_srcDelegate copy_dst_src;

        /// <summary>
        ///  void set_char_pointer(uint Char, uint Pos);
        /// </summary>
        public static set_char_pointerDelegate set_char_pointer;

        /// <summary>
        ///  void set_sub_pointer(uint Index, uint Pos);
        /// </summary>
        public static set_sub_pointerDelegate set_sub_pointer;

        /// <summary>
        ///  void set_text_table_pointer(uint Index, uint Pos);
        /// </summary>
        public static set_text_table_pointerDelegate set_text_table_pointer;

        /// <summary>
        ///  void set_char_table(uint Index, uint Pos);
        /// </summary>
        public static set_char_tableDelegate set_char_table;

        /// <summary>
        ///  uint get_char_pointer(uint Char);
        /// </summary>
        public static get_char_pointerDelegate get_char_pointer;

        /// <summary>
        ///  uint get_sub_pointer(uint Index);
        /// </summary>
        public static get_sub_pointerDelegate get_sub_pointer;

        /// <summary>
        ///  uint get_text_table_pointer(uint Index);
        /// </summary>
        public static get_text_table_pointerDelegate get_text_table_pointer;

        /// <summary>
        ///  void n_time_update(uint CardNo);
        /// </summary>
        public static n_time_updateDelegate n_time_update;

        /// <summary>
        ///  void n_set_serial_step(uint CardNo, uint No, uint Step);
        /// </summary>
        public static n_set_serial_stepDelegate n_set_serial_step;

        /// <summary>
        ///  void n_select_serial_set(uint CardNo, uint No);
        /// </summary>
        public static n_select_serial_setDelegate n_select_serial_set;

        /// <summary>
        ///  void n_set_serial(uint CardNo, uint No);
        /// </summary>
        public static n_set_serialDelegate n_set_serial;

        /// <summary>
        ///  double n_get_serial(uint CardNo);
        /// </summary>
        public static n_get_serialDelegate n_get_serial;

        /// <summary>
        ///  double n_get_list_serial(uint CardNo, out uint SetNo);
        /// </summary>
        public static n_get_list_serialDelegate n_get_list_serial;

        /// <summary>
        ///  void time_update();
        /// </summary>
        public static time_updateDelegate time_update;

        /// <summary>
        ///  void set_serial_step(uint No, uint Step);
        /// </summary>
        public static set_serial_stepDelegate set_serial_step;

        /// <summary>
        ///  void select_serial_set(uint No);
        /// </summary>
        public static select_serial_setDelegate select_serial_set;

        /// <summary>
        ///  void set_serial(uint No);
        /// </summary>
        public static set_serialDelegate set_serial;

        /// <summary>
        ///  double get_serial();
        /// </summary>
        public static get_serialDelegate get_serial;

        /// <summary>
        ///  double get_list_serial(out uint SetNo);
        /// </summary>
        public static get_list_serialDelegate get_list_serial;

        /// <summary>
        ///  void n_write_io_port_mask(uint CardNo, uint Value, uint Mask);
        /// </summary>
        public static n_write_io_port_maskDelegate n_write_io_port_mask;

        /// <summary>
        ///  void n_write_8bit_port(uint CardNo, uint Value);
        /// </summary>
        public static n_write_8bit_portDelegate n_write_8bit_port;

        /// <summary>
        ///  uint n_read_io_port(uint CardNo);
        /// </summary>
        public static n_read_io_portDelegate n_read_io_port;

        /// <summary>
        ///  uint n_read_io_port_buffer(uint CardNo, uint Index, out uint Value, out int XPos, out int YPos, out uint Time);
        /// </summary>
        public static n_read_io_port_bufferDelegate n_read_io_port_buffer;

        /// <summary>
        ///  uint n_get_io_status(uint CardNo);
        /// </summary>
        public static n_get_io_statusDelegate n_get_io_status;

        /// <summary>
        ///  uint n_read_analog_in(uint CardNo);
        /// </summary>
        public static n_read_analog_inDelegate n_read_analog_in;

        /// <summary>
        ///  void n_write_da_x(uint CardNo, uint x, uint Value);
        /// </summary>
        public static n_write_da_xDelegate n_write_da_x;

        /// <summary>
        ///  void n_set_laser_off_default(uint CardNo, uint AnalogOut1, uint AnalogOut2, uint DigitalOut);
        /// </summary>
        public static n_set_laser_off_defaultDelegate n_set_laser_off_default;

        /// <summary>
        ///  void n_set_port_default(uint CardNo, uint Port, uint Value);
        /// </summary>
        public static n_set_port_defaultDelegate n_set_port_default;

        /// <summary>
        ///  void n_write_io_port(uint CardNo, uint Value);
        /// </summary>
        public static n_write_io_portDelegate n_write_io_port;

        /// <summary>
        ///  void n_write_da_1(uint CardNo, uint Value);
        /// </summary>
        public static n_write_da_1Delegate n_write_da_1;

        /// <summary>
        ///  void n_write_da_2(uint CardNo, uint Value);
        /// </summary>
        public static n_write_da_2Delegate n_write_da_2;

        /// <summary>
        ///  void write_io_port_mask(uint Value, uint Mask);
        /// </summary>
        public static write_io_port_maskDelegate write_io_port_mask;

        /// <summary>
        ///  void write_8bit_port(uint Value);
        /// </summary>
        public static write_8bit_portDelegate write_8bit_port;

        /// <summary>
        ///  uint read_io_port();
        /// </summary>
        public static read_io_portDelegate read_io_port;

        /// <summary>
        ///  uint read_io_port_buffer(uint Index, out uint Value, out int XPos, out int YPos, out uint Time);
        /// </summary>
        public static read_io_port_bufferDelegate read_io_port_buffer;

        /// <summary>
        ///  uint get_io_status();
        /// </summary>
        public static get_io_statusDelegate get_io_status;

        /// <summary>
        ///  uint read_analog_in();
        /// </summary>
        public static read_analog_inDelegate read_analog_in;

        /// <summary>
        ///  void write_da_x(uint x, uint Value);
        /// </summary>
        public static write_da_xDelegate write_da_x;

        /// <summary>
        ///  void set_laser_off_default(uint AnalogOut1, uint AnalogOut2, uint DigitalOut);
        /// </summary>
        public static set_laser_off_defaultDelegate set_laser_off_default;

        /// <summary>
        ///  void set_port_default(uint Port, uint Value);
        /// </summary>
        public static set_port_defaultDelegate set_port_default;

        /// <summary>
        ///  void write_io_port(uint Value);
        /// </summary>
        public static write_io_portDelegate write_io_port;

        /// <summary>
        ///  void write_da_1(uint Value);
        /// </summary>
        public static write_da_1Delegate write_da_1;

        /// <summary>
        ///  void write_da_2(uint Value);
        /// </summary>
        public static write_da_2Delegate write_da_2;

        /// <summary>
        ///  void n_disable_laser(uint CardNo);
        /// </summary>
        public static n_disable_laserDelegate n_disable_laser;

        /// <summary>
        ///  void n_enable_laser(uint CardNo);
        /// </summary>
        public static n_enable_laserDelegate n_enable_laser;

        /// <summary>
        ///  void n_laser_signal_on(uint CardNo);
        /// </summary>
        public static n_laser_signal_onDelegate n_laser_signal_on;

        /// <summary>
        ///  void n_laser_signal_off(uint CardNo);
        /// </summary>
        public static n_laser_signal_offDelegate n_laser_signal_off;

        /// <summary>
        ///  void n_set_standby(uint CardNo, uint HalfPeriod, uint PulseLength);
        /// </summary>
        public static n_set_standbyDelegate n_set_standby;

        /// <summary>
        ///  void n_set_laser_pulses_ctrl(uint CardNo, uint HalfPeriod, uint PulseLength);
        /// </summary>
        public static n_set_laser_pulses_ctrlDelegate n_set_laser_pulses_ctrl;

        /// <summary>
        ///  void n_set_firstpulse_killer(uint CardNo, uint Length);
        /// </summary>
        public static n_set_firstpulse_killerDelegate n_set_firstpulse_killer;

        /// <summary>
        ///  void n_set_qswitch_delay(uint CardNo, uint Delay);
        /// </summary>
        public static n_set_qswitch_delayDelegate n_set_qswitch_delay;

        /// <summary>
        ///  void n_set_laser_mode(uint CardNo, uint Mode);
        /// </summary>
        public static n_set_laser_modeDelegate n_set_laser_mode;

        /// <summary>
        ///  void n_set_laser_control(uint CardNo, uint Ctrl);
        /// </summary>
        public static n_set_laser_controlDelegate n_set_laser_control;

        /// <summary>
        ///  void n_set_laser_pin_out(uint CardNo, uint Pins);
        /// </summary>
        public static n_set_laser_pin_outDelegate n_set_laser_pin_out;

        /// <summary>
        ///  uint n_get_laser_pin_in(uint CardNo);
        /// </summary>
        public static n_get_laser_pin_inDelegate n_get_laser_pin_in;

        /// <summary>
        ///  void n_set_softstart_level(uint CardNo, uint Index, uint Level);
        /// </summary>
        public static n_set_softstart_levelDelegate n_set_softstart_level;

        /// <summary>
        ///  void n_set_softstart_mode(uint CardNo, uint Mode, uint Number, uint Delay);
        /// </summary>
        public static n_set_softstart_modeDelegate n_set_softstart_mode;

        /// <summary>
        ///  uint n_set_auto_laser_control(uint CardNo, uint Ctrl, uint Value, uint Mode, uint MinValue, uint MaxValue);
        /// </summary>
        public static n_set_auto_laser_controlDelegate n_set_auto_laser_control;

        /// <summary>
        ///  uint n_set_auto_laser_params(uint CardNo, uint Ctrl, uint Value, uint MinValue, uint MaxValue);
        /// </summary>
        public static n_set_auto_laser_paramsDelegate n_set_auto_laser_params;

        /// <summary>
        ///  int n_load_auto_laser_control(uint CardNo, string Name, uint No);
        /// </summary>
        public static n_load_auto_laser_controlDelegate n_load_auto_laser_control;

        /// <summary>
        ///  int n_load_position_control(uint CardNo, string Name, uint No);
        /// </summary>
        public static n_load_position_controlDelegate n_load_position_control;

        /// <summary>
        ///  void n_set_default_pixel(uint CardNo, uint PulseLength);
        /// </summary>
        public static n_set_default_pixelDelegate n_set_default_pixel;

        /// <summary>
        ///  void n_get_standby(uint CardNo, out uint HalfPeriod, out uint PulseLength);
        /// </summary>
        public static n_get_standbyDelegate n_get_standby;

        /// <summary>
        ///  void n_set_pulse_picking(uint CardNo, uint No);
        /// </summary>
        public static n_set_pulse_pickingDelegate n_set_pulse_picking;

        /// <summary>
        ///  void n_set_pulse_picking_length(uint CardNo, uint Length);
        /// </summary>
        public static n_set_pulse_picking_lengthDelegate n_set_pulse_picking_length;

        /// <summary>
        ///  void n_config_laser_signals(uint CardNo, uint Config);
        /// </summary>
        public static n_config_laser_signalsDelegate n_config_laser_signals;

        /// <summary>
        ///  void disable_laser();
        /// </summary>
        public static disable_laserDelegate disable_laser;

        /// <summary>
        ///  void enable_laser();
        /// </summary>
        public static enable_laserDelegate enable_laser;

        /// <summary>
        ///  void laser_signal_on();
        /// </summary>
        public static laser_signal_onDelegate laser_signal_on;

        /// <summary>
        ///  void laser_signal_off();
        /// </summary>
        public static laser_signal_offDelegate laser_signal_off;

        /// <summary>
        ///  void set_standby(uint HalfPeriod, uint PulseLength);
        /// </summary>
        public static set_standbyDelegate set_standby;

        /// <summary>
        ///  void set_laser_pulses_ctrl(uint HalfPeriod, uint PulseLength);
        /// </summary>
        public static set_laser_pulses_ctrlDelegate set_laser_pulses_ctrl;

        /// <summary>
        ///  void set_firstpulse_killer(uint Length);
        /// </summary>
        public static set_firstpulse_killerDelegate set_firstpulse_killer;

        /// <summary>
        ///  void set_qswitch_delay(uint Delay);
        /// </summary>
        public static set_qswitch_delayDelegate set_qswitch_delay;

        /// <summary>
        ///  void set_laser_mode(uint Mode);
        /// </summary>
        public static set_laser_modeDelegate set_laser_mode;

        /// <summary>
        ///  void set_laser_control(uint Ctrl);
        /// </summary>
        public static set_laser_controlDelegate set_laser_control;

        /// <summary>
        ///  void set_laser_pin_out(uint Pins);
        /// </summary>
        public static set_laser_pin_outDelegate set_laser_pin_out;

        /// <summary>
        ///  uint get_laser_pin_in();
        /// </summary>
        public static get_laser_pin_inDelegate get_laser_pin_in;

        /// <summary>
        ///  void set_softstart_level(uint Index, uint Level);
        /// </summary>
        public static set_softstart_levelDelegate set_softstart_level;

        /// <summary>
        ///  void set_softstart_mode(uint Mode, uint Number, uint Delay);
        /// </summary>
        public static set_softstart_modeDelegate set_softstart_mode;

        /// <summary>
        ///  uint set_auto_laser_control(uint Ctrl, uint Value, uint Mode, uint MinValue, uint MaxValue);
        /// </summary>
        public static set_auto_laser_controlDelegate set_auto_laser_control;

        /// <summary>
        ///  uint set_auto_laser_params(uint Ctrl, uint Value, uint MinValue, uint MaxValue);
        /// </summary>
        public static set_auto_laser_paramsDelegate set_auto_laser_params;

        /// <summary>
        ///  int load_auto_laser_control(string Name, uint No);
        /// </summary>
        public static load_auto_laser_controlDelegate load_auto_laser_control;

        /// <summary>
        ///  int load_position_control(string Name, uint No);
        /// </summary>
        public static load_position_controlDelegate load_position_control;

        /// <summary>
        ///  void set_default_pixel(uint PulseLength);
        /// </summary>
        public static set_default_pixelDelegate set_default_pixel;

        /// <summary>
        ///  void get_standby(out uint HalfPeriod, out uint PulseLength);
        /// </summary>
        public static get_standbyDelegate get_standby;

        /// <summary>
        ///  void set_pulse_picking(uint No);
        /// </summary>
        public static set_pulse_pickingDelegate set_pulse_picking;

        /// <summary>
        ///  void set_pulse_picking_length(uint Length);
        /// </summary>
        public static set_pulse_picking_lengthDelegate set_pulse_picking_length;

        /// <summary>
        ///  void config_laser_signals(uint Config);
        /// </summary>
        public static config_laser_signalsDelegate config_laser_signals;

        /// <summary>
        ///  void n_set_ext_start_delay(uint CardNo, int Delay, uint EncoderNo);
        /// </summary>
        public static n_set_ext_start_delayDelegate n_set_ext_start_delay;

        /// <summary>
        ///  void n_set_rot_center(uint CardNo, int X, int Y);
        /// </summary>
        public static n_set_rot_centerDelegate n_set_rot_center;

        /// <summary>
        ///  void n_simulate_encoder(uint CardNo, uint EncoderNo);
        /// </summary>
        public static n_simulate_encoderDelegate n_simulate_encoder;

        /// <summary>
        ///  uint n_get_marking_info(uint CardNo);
        /// </summary>
        public static n_get_marking_infoDelegate n_get_marking_info;

        /// <summary>
        ///  void n_set_encoder_speed_ctrl(uint CardNo, uint EncoderNo, double Speed, double Smooth);
        /// </summary>
        public static n_set_encoder_speed_ctrlDelegate n_set_encoder_speed_ctrl;

        /// <summary>
        ///  void n_set_mcbsp_x(uint CardNo, double ScaleX);
        /// </summary>
        public static n_set_mcbsp_xDelegate n_set_mcbsp_x;

        /// <summary>
        ///  void n_set_mcbsp_y(uint CardNo, double ScaleY);
        /// </summary>
        public static n_set_mcbsp_yDelegate n_set_mcbsp_y;

        /// <summary>
        ///  void n_set_mcbsp_rot(uint CardNo, double Resolution);
        /// </summary>
        public static n_set_mcbsp_rotDelegate n_set_mcbsp_rot;

        /// <summary>
        ///  void n_set_mcbsp_matrix(uint CardNo);
        /// </summary>
        public static n_set_mcbsp_matrixDelegate n_set_mcbsp_matrix;

        /// <summary>
        ///  void n_set_mcbsp_global_x(uint CardNo, double ScaleX);
        /// </summary>
        public static n_set_mcbsp_global_xDelegate n_set_mcbsp_global_x;

        /// <summary>
        ///  void n_set_mcbsp_global_y(uint CardNo, double ScaleY);
        /// </summary>
        public static n_set_mcbsp_global_yDelegate n_set_mcbsp_global_y;

        /// <summary>
        ///  void n_set_mcbsp_global_rot(uint CardNo, double Resolution);
        /// </summary>
        public static n_set_mcbsp_global_rotDelegate n_set_mcbsp_global_rot;

        /// <summary>
        ///  void n_set_mcbsp_global_matrix(uint CardNo);
        /// </summary>
        public static n_set_mcbsp_global_matrixDelegate n_set_mcbsp_global_matrix;

        /// <summary>
        ///  void n_set_mcbsp_in(uint CardNo, uint Mode, double Scale);
        /// </summary>
        public static n_set_mcbsp_inDelegate n_set_mcbsp_in;

        /// <summary>
        ///  void n_set_multi_mcbsp_in(uint CardNo, uint Ctrl, uint P, uint Mode);
        /// </summary>
        public static n_set_multi_mcbsp_inDelegate n_set_multi_mcbsp_in;

        /// <summary>
        ///  void n_set_fly_tracking_error(uint CardNo, uint TrackingErrorX, uint TrackingErrorY);
        /// </summary>
        public static n_set_fly_tracking_errorDelegate n_set_fly_tracking_error;

        /// <summary>
        ///  int n_load_fly_2d_table(uint CardNo, string Name, uint No);
        /// </summary>
        public static n_load_fly_2d_tableDelegate n_load_fly_2d_table;

        /// <summary>
        ///  void n_init_fly_2d(uint CardNo, int OffsetX, int OffsetY);
        /// </summary>
        public static n_init_fly_2dDelegate n_init_fly_2d;

        /// <summary>
        ///  void n_get_fly_2d_offset(uint CardNo, out int OffsetX, out int OffsetY);
        /// </summary>
        public static n_get_fly_2d_offsetDelegate n_get_fly_2d_offset;

        /// <summary>
        ///  void n_get_encoder(uint CardNo, out int Encoder0, out int Encoder1);
        /// </summary>
        public static n_get_encoderDelegate n_get_encoder;

        /// <summary>
        ///  void n_read_encoder(uint CardNo, out int Encoder0_1, out int Encoder1_1, out int Encoder0_2, out int Encoder1_2);
        /// </summary>
        public static n_read_encoderDelegate n_read_encoder;

        /// <summary>
        ///  int n_get_mcbsp(uint CardNo);
        /// </summary>
        public static n_get_mcbspDelegate n_get_mcbsp;

        /// <summary>
        ///  int n_read_mcbsp(uint CardNo, uint No);
        /// </summary>
        public static n_read_mcbspDelegate n_read_mcbsp;

        /// <summary>
        ///  int n_read_multi_mcbsp(uint CardNo, uint No);
        /// </summary>
        public static n_read_multi_mcbspDelegate n_read_multi_mcbsp;

        /// <summary>
        ///  void n_clear_fly_overflow_ctrl(uint CardNo, uint Mode);
        /// </summary>
        public static n_clear_fly_overflow_ctrlDelegate n_clear_fly_overflow_ctrl;

        /// <summary>
        ///  void set_ext_start_delay(int Delay, uint EncoderNo);
        /// </summary>
        public static set_ext_start_delayDelegate set_ext_start_delay;

        /// <summary>
        ///  void set_rot_center(int X, int Y);
        /// </summary>
        public static set_rot_centerDelegate set_rot_center;

        /// <summary>
        ///  void simulate_encoder(uint EncoderNo);
        /// </summary>
        public static simulate_encoderDelegate simulate_encoder;

        /// <summary>
        ///  uint get_marking_info();
        /// </summary>
        public static get_marking_infoDelegate get_marking_info;

        /// <summary>
        ///  void set_encoder_speed_ctrl(uint EncoderNo, double Speed, double Smooth);
        /// </summary>
        public static set_encoder_speed_ctrlDelegate set_encoder_speed_ctrl;

        /// <summary>
        ///  void set_mcbsp_x(double ScaleX);
        /// </summary>
        public static set_mcbsp_xDelegate set_mcbsp_x;

        /// <summary>
        ///  void set_mcbsp_y(double ScaleY);
        /// </summary>
        public static set_mcbsp_yDelegate set_mcbsp_y;

        /// <summary>
        ///  void set_mcbsp_rot(double Resolution);
        /// </summary>
        public static set_mcbsp_rotDelegate set_mcbsp_rot;

        /// <summary>
        ///  void set_mcbsp_matrix();
        /// </summary>
        public static set_mcbsp_matrixDelegate set_mcbsp_matrix;

        /// <summary>
        ///  void set_mcbsp_global_x(double ScaleX);
        /// </summary>
        public static set_mcbsp_global_xDelegate set_mcbsp_global_x;

        /// <summary>
        ///  void set_mcbsp_global_y(double ScaleY);
        /// </summary>
        public static set_mcbsp_global_yDelegate set_mcbsp_global_y;

        /// <summary>
        ///  void set_mcbsp_global_rot(double Resolution);
        /// </summary>
        public static set_mcbsp_global_rotDelegate set_mcbsp_global_rot;

        /// <summary>
        ///  void set_mcbsp_global_matrix();
        /// </summary>
        public static set_mcbsp_global_matrixDelegate set_mcbsp_global_matrix;

        /// <summary>
        ///  void set_mcbsp_in(uint Mode, double Scale);
        /// </summary>
        public static set_mcbsp_inDelegate set_mcbsp_in;

        /// <summary>
        ///  void set_multi_mcbsp_in(uint Ctrl, uint P, uint Mode);
        /// </summary>
        public static set_multi_mcbsp_inDelegate set_multi_mcbsp_in;

        /// <summary>
        ///  void set_fly_tracking_error(uint TrackingErrorX, uint TrackingErrorY);
        /// </summary>
        public static set_fly_tracking_errorDelegate set_fly_tracking_error;

        /// <summary>
        ///  int load_fly_2d_table(string Name, uint No);
        /// </summary>
        public static load_fly_2d_tableDelegate load_fly_2d_table;

        /// <summary>
        ///  void init_fly_2d(int OffsetX, int OffsetY);
        /// </summary>
        public static init_fly_2dDelegate init_fly_2d;

        /// <summary>
        ///  void get_fly_2d_offset(out int OffsetX, out int OffsetY);
        /// </summary>
        public static get_fly_2d_offsetDelegate get_fly_2d_offset;

        /// <summary>
        ///  void get_encoder(out int Encoder0, out int Encoder1);
        /// </summary>
        public static get_encoderDelegate get_encoder;

        /// <summary>
        ///  void read_encoder(out int Encoder0_1, out int Encoder1_1, out int Encoder0_2, out int Encoder1_2);
        /// </summary>
        public static read_encoderDelegate read_encoder;

        /// <summary>
        ///  int get_mcbsp();
        /// </summary>
        public static get_mcbspDelegate get_mcbsp;

        /// <summary>
        ///  int read_mcbsp(uint No);
        /// </summary>
        public static read_mcbspDelegate read_mcbsp;

        /// <summary>
        ///  int read_multi_mcbsp(uint No);
        /// </summary>
        public static read_multi_mcbspDelegate read_multi_mcbsp;

        /// <summary>
        ///  void clear_fly_overflow_ctrl(uint Mode);
        /// </summary>
        public static clear_fly_overflow_ctrlDelegate clear_fly_overflow_ctrl;

        /// <summary>
        ///  double n_get_time(uint CardNo);
        /// </summary>
        public static n_get_timeDelegate n_get_time;

        /// <summary>
        ///  double n_get_lap_time(uint CardNo);
        /// </summary>
        public static n_get_lap_timeDelegate n_get_lap_time;

        /// <summary>
        ///  void n_measurement_status(uint CardNo, out uint Busy, out uint Pos);
        /// </summary>
        public static n_measurement_statusDelegate n_measurement_status;

        /// <summary>
        ///  void n_get_waveform(uint CardNo, uint Channel, uint Number, int[] Ptr);
        /// </summary>
        public static n_get_waveformDelegate n_get_waveform;

        /// <summary>
        ///  void n_bounce_supp(uint CardNo, uint Length);
        /// </summary>
        public static n_bounce_suppDelegate n_bounce_supp;

        /// <summary>
        ///  void n_home_position_xyz(uint CardNo, int XHome, int YHome, int ZHome);
        /// </summary>
        public static n_home_position_xyzDelegate n_home_position_xyz;

        /// <summary>
        ///  void n_home_position(uint CardNo, int XHome, int YHome);
        /// </summary>
        public static n_home_positionDelegate n_home_position;

        /// <summary>
        ///  void n_rs232_config(uint CardNo, uint BaudRate);
        /// </summary>
        public static n_rs232_configDelegate n_rs232_config;

        /// <summary>
        ///  void n_rs232_write_data(uint CardNo, uint Data);
        /// </summary>
        public static n_rs232_write_dataDelegate n_rs232_write_data;

        /// <summary>
        ///  void n_rs232_write_text(uint CardNo, string pData);
        /// </summary>
        public static n_rs232_write_textDelegate n_rs232_write_text;

        /// <summary>
        ///  uint n_rs232_read_data(uint CardNo);
        /// </summary>
        public static n_rs232_read_dataDelegate n_rs232_read_data;

        /// <summary>
        ///  uint n_set_mcbsp_freq(uint CardNo, uint Freq);
        /// </summary>
        public static n_set_mcbsp_freqDelegate n_set_mcbsp_freq;

        /// <summary>
        ///  void n_mcbsp_init(uint CardNo, uint XDelay, uint RDelay);
        /// </summary>
        public static n_mcbsp_initDelegate n_mcbsp_init;

        /// <summary>
        ///  void n_mcbsp_init_spi(uint CardNo, uint ClockLevel, uint ClockDelay);
        /// </summary>
        public static n_mcbsp_init_spiDelegate n_mcbsp_init_spi;

        /// <summary>
        ///  uint n_get_overrun(uint CardNo);
        /// </summary>
        public static n_get_overrunDelegate n_get_overrun;

        /// <summary>
        ///  uint n_get_master_slave(uint CardNo);
        /// </summary>
        public static n_get_master_slaveDelegate n_get_master_slave;

        /// <summary>
        ///  void n_get_transform(uint CardNo, uint Number, int[] Ptr1, int[] Ptr2, uint[] Ptr, uint Code);
        /// </summary>
        public static n_get_transformDelegate n_get_transform;

        /// <summary>
        ///  void n_stop_trigger(uint CardNo);
        /// </summary>
        public static n_stop_triggerDelegate n_stop_trigger;

        /// <summary>
        ///  void n_move_to(uint CardNo, uint Pos);
        /// </summary>
        public static n_move_toDelegate n_move_to;

        /// <summary>
        ///  void n_set_enduring_wobbel(uint CardNo, uint CenterX, uint CenterY, uint CenterZ, uint LimitHi, uint LimitLo, double ScaleX, double ScaleY, double ScaleZ);
        /// </summary>
        public static n_set_enduring_wobbelDelegate n_set_enduring_wobbel;

        /// <summary>
        ///  void n_set_enduring_wobbel_2(uint CardNo, uint CenterX, uint CenterY, uint CenterZ, uint LimitHi, uint LimitLo, double ScaleX, double ScaleY, double ScaleZ);
        /// </summary>
        public static n_set_enduring_wobbel_2Delegate n_set_enduring_wobbel_2;

        /// <summary>
        ///  void n_set_free_variable(uint CardNo, uint VarNo, uint Value);
        /// </summary>
        public static n_set_free_variableDelegate n_set_free_variable;

        /// <summary>
        ///  uint n_get_free_variable(uint CardNo, uint VarNo);
        /// </summary>
        public static n_get_free_variableDelegate n_get_free_variable;

        /// <summary>
        ///  void n_set_mcbsp_out_ptr(uint CardNo, uint Number, uint[] SignalPtr);
        /// </summary>
        public static n_set_mcbsp_out_ptrDelegate n_set_mcbsp_out_ptr;

        /// <summary>
        ///  void n_periodic_toggle(uint CardNo, uint Port, uint Mask, uint P1, uint P2, uint Count, uint Start);
        /// </summary>
        public static n_periodic_toggleDelegate n_periodic_toggle;

        /// <summary>
        ///  uint n_load_wobbel_power(uint CardNo, uint TableNo, int[] Ptr, int Flag);
        /// </summary>
        public static n_load_wobbel_powerDelegate n_load_wobbel_power;

        /// <summary>
        ///  double get_time();
        /// </summary>
        public static get_timeDelegate get_time;

        /// <summary>
        ///  double get_lap_time();
        /// </summary>
        public static get_lap_timeDelegate get_lap_time;

        /// <summary>
        ///  void measurement_status(out uint Busy, out uint Pos);
        /// </summary>
        public static measurement_statusDelegate measurement_status;

        /// <summary>
        ///  void get_waveform(uint Channel, uint Number, int[] Ptr);
        /// </summary>
        public static get_waveformDelegate get_waveform;

        /// <summary>
        ///  void bounce_supp(uint Length);
        /// </summary>
        public static bounce_suppDelegate bounce_supp;

        /// <summary>
        ///  void home_position_xyz(int XHome, int YHome, int ZHome);
        /// </summary>
        public static home_position_xyzDelegate home_position_xyz;

        /// <summary>
        ///  void home_position(int XHome, int YHome);
        /// </summary>
        public static home_positionDelegate home_position;

        /// <summary>
        ///  void rs232_config(uint BaudRate);
        /// </summary>
        public static rs232_configDelegate rs232_config;

        /// <summary>
        ///  void rs232_write_data(uint Data);
        /// </summary>
        public static rs232_write_dataDelegate rs232_write_data;

        /// <summary>
        ///  void rs232_write_text(string pData);
        /// </summary>
        public static rs232_write_textDelegate rs232_write_text;

        /// <summary>
        ///  uint rs232_read_data();
        /// </summary>
        public static rs232_read_dataDelegate rs232_read_data;

        /// <summary>
        ///  uint set_mcbsp_freq(uint Freq);
        /// </summary>
        public static set_mcbsp_freqDelegate set_mcbsp_freq;

        /// <summary>
        ///  void mcbsp_init(uint XDelay, uint RDelay);
        /// </summary>
        public static mcbsp_initDelegate mcbsp_init;

        /// <summary>
        ///  void mcbsp_init_spi(uint ClockLevel, uint ClockDelay);
        /// </summary>
        public static mcbsp_init_spiDelegate mcbsp_init_spi;

        /// <summary>
        ///  uint get_overrun();
        /// </summary>
        public static get_overrunDelegate get_overrun;

        /// <summary>
        ///  uint get_master_slave();
        /// </summary>
        public static get_master_slaveDelegate get_master_slave;

        /// <summary>
        ///  void get_transform(uint Number, int[] Ptr1, int[] Ptr2, uint[] Ptr, uint Code);
        /// </summary>
        public static get_transformDelegate get_transform;

        /// <summary>
        ///  void stop_trigger();
        /// </summary>
        public static stop_triggerDelegate stop_trigger;

        /// <summary>
        ///  void move_to(uint Pos);
        /// </summary>
        public static move_toDelegate move_to;

        /// <summary>
        ///  void set_enduring_wobbel(uint CenterX, uint CenterY, uint CenterZ, uint LimitHi, uint LimitLo, double ScaleX, double ScaleY, double ScaleZ);
        /// </summary>
        public static set_enduring_wobbelDelegate set_enduring_wobbel;

        /// <summary>
        ///  void set_enduring_wobbel_2(uint CenterX, uint CenterY, uint CenterZ, uint LimitHi, uint LimitLo, double ScaleX, double ScaleY, double ScaleZ);
        /// </summary>
        public static set_enduring_wobbel_2Delegate set_enduring_wobbel_2;

        /// <summary>
        ///  void set_free_variable(uint VarNo, uint Value);
        /// </summary>
        public static set_free_variableDelegate set_free_variable;

        /// <summary>
        ///  uint get_free_variable(uint VarNo);
        /// </summary>
        public static get_free_variableDelegate get_free_variable;

        /// <summary>
        ///  void set_mcbsp_out_ptr(uint Number, uint[] SignalPtr);
        /// </summary>
        public static set_mcbsp_out_ptrDelegate set_mcbsp_out_ptr;

        /// <summary>
        ///  void periodic_toggle(uint Port, uint Mask, uint P1, uint P2, uint Count, uint Start);
        /// </summary>
        public static periodic_toggleDelegate periodic_toggle;

        /// <summary>
        ///  uint load_wobbel_power(uint TableNo, int[] Ptr, int Flag);
        /// </summary>
        public static load_wobbel_powerDelegate load_wobbel_power;

        /// <summary>
        ///  void n_set_defocus(uint CardNo, int Shift);
        /// </summary>
        public static n_set_defocusDelegate n_set_defocus;

        /// <summary>
        ///  void n_set_defocus_offset(uint CardNo, int Shift);
        /// </summary>
        public static n_set_defocus_offsetDelegate n_set_defocus_offset;

        /// <summary>
        ///  void n_goto_xyz(uint CardNo, int X, int Y, int Z);
        /// </summary>
        public static n_goto_xyzDelegate n_goto_xyz;

        /// <summary>
        ///  void n_set_zoom(uint CardNo, uint Zoom);
        /// </summary>
        public static n_set_zoomDelegate n_set_zoom;

        /// <summary>
        ///  void n_goto_xy(uint CardNo, int X, int Y);
        /// </summary>
        public static n_goto_xyDelegate n_goto_xy;

        /// <summary>
        ///  int n_get_z_distance(uint CardNo, int X, int Y, int Z);
        /// </summary>
        public static n_get_z_distanceDelegate n_get_z_distance;

        /// <summary>
        ///  void set_defocus(int Shift);
        /// </summary>
        public static set_defocusDelegate set_defocus;

        /// <summary>
        ///  void set_defocus_offset(int Shift);
        /// </summary>
        public static set_defocus_offsetDelegate set_defocus_offset;

        /// <summary>
        ///  void goto_xyz(int X, int Y, int Z);
        /// </summary>
        public static goto_xyzDelegate goto_xyz;

        /// <summary>
        ///  void goto_xy(int X, int Y);
        /// </summary>
        public static goto_xyDelegate goto_xy;

        /// <summary>
        ///  void set_zoom(uint Zoom);
        /// </summary>
        public static set_zoomDelegate set_zoom;

        /// <summary>
        ///  int get_z_distance(int X, int Y, int Z);
        /// </summary>
        public static get_z_distanceDelegate get_z_distance;

        /// <summary>
        ///  void n_set_offset_xyz(uint CardNo, uint HeadNo, int XOffset, int YOffset, int ZOffset, uint at_once);
        /// </summary>
        public static n_set_offset_xyzDelegate n_set_offset_xyz;

        /// <summary>
        ///  void n_set_offset(uint CardNo, uint HeadNo, int XOffset, int YOffset, uint at_once);
        /// </summary>
        public static n_set_offsetDelegate n_set_offset;

        /// <summary>
        ///  void n_set_matrix(uint CardNo, uint HeadNo, double M11, double M12, double M21, double M22, uint at_once);
        /// </summary>
        public static n_set_matrixDelegate n_set_matrix;

        /// <summary>
        ///  void n_set_angle(uint CardNo, uint HeadNo, double Angle, uint at_once);
        /// </summary>
        public static n_set_angleDelegate n_set_angle;

        /// <summary>
        ///  void n_set_scale(uint CardNo, uint HeadNo, double Scale, uint at_once);
        /// </summary>
        public static n_set_scaleDelegate n_set_scale;

        /// <summary>
        ///  void n_apply_mcbsp(uint CardNo, uint HeadNo, uint at_once);
        /// </summary>
        public static n_apply_mcbspDelegate n_apply_mcbsp;

        /// <summary>
        ///  uint n_upload_transform(uint CardNo, uint HeadNo, uint[] Ptr);
        /// </summary>
        public static n_upload_transformDelegate n_upload_transform;

        /// <summary>
        ///  void set_offset_xyz(uint HeadNo, int XOffset, int YOffset, int ZOffset, uint at_once);
        /// </summary>
        public static set_offset_xyzDelegate set_offset_xyz;

        /// <summary>
        ///  void set_offset(uint HeadNo, int XOffset, int YOffset, uint at_once);
        /// </summary>
        public static set_offsetDelegate set_offset;

        /// <summary>
        ///  void set_matrix(uint HeadNo, double M11, double M12, double M21, double M22, uint at_once);
        /// </summary>
        public static set_matrixDelegate set_matrix;

        /// <summary>
        ///  void set_angle(uint HeadNo, double Angle, uint at_once);
        /// </summary>
        public static set_angleDelegate set_angle;

        /// <summary>
        ///  void set_scale(uint HeadNo, double Scale, uint at_once);
        /// </summary>
        public static set_scaleDelegate set_scale;

        /// <summary>
        ///  void apply_mcbsp(uint HeadNo, uint at_once);
        /// </summary>
        public static apply_mcbspDelegate apply_mcbsp;

        /// <summary>
        ///  uint upload_transform(uint HeadNo, uint[] Ptr);
        /// </summary>
        public static upload_transformDelegate upload_transform;

        /// <summary>
        ///  uint transform(out int Sig1, out int Sig2, uint[] Ptr, uint Code);
        /// </summary>
        public static transformDelegate transform;

        /// <summary>
        ///  void n_set_delay_mode(uint CardNo, uint VarPoly, uint DirectMove3D, uint EdgeLevel, uint MinJumpDelay, uint JumpLengthLimit);
        /// </summary>
        public static n_set_delay_modeDelegate n_set_delay_mode;

        /// <summary>
        ///  void n_set_jump_speed_ctrl(uint CardNo, double Speed);
        /// </summary>
        public static n_set_jump_speed_ctrlDelegate n_set_jump_speed_ctrl;

        /// <summary>
        ///  void n_set_mark_speed_ctrl(uint CardNo, double Speed);
        /// </summary>
        public static n_set_mark_speed_ctrlDelegate n_set_mark_speed_ctrl;

        /// <summary>
        ///  void n_set_sky_writing_para(uint CardNo, double Timelag, int LaserOnShift, uint Nprev, uint Npost);
        /// </summary>
        public static n_set_sky_writing_paraDelegate n_set_sky_writing_para;

        /// <summary>
        ///  void n_set_sky_writing_limit(uint CardNo, double CosAngle);
        /// </summary>
        public static n_set_sky_writing_limitDelegate n_set_sky_writing_limit;

        /// <summary>
        ///  void n_set_sky_writing_mode(uint CardNo, uint Mode);
        /// </summary>
        public static n_set_sky_writing_modeDelegate n_set_sky_writing_mode;

        /// <summary>
        ///  int n_load_varpolydelay(uint CardNo, string Name, uint No);
        /// </summary>
        public static n_load_varpolydelayDelegate n_load_varpolydelay;

        /// <summary>
        ///  void n_set_hi(uint CardNo, uint HeadNo, double GalvoGainX, double GalvoGainY, int GalvoOffsetX, int GalvoOffsetY);
        /// </summary>
        public static n_set_hiDelegate n_set_hi;

        /// <summary>
        ///  void n_get_hi_pos(uint CardNo, uint HeadNo, out int X1, out int X2, out int Y1, out int Y2);
        /// </summary>
        public static n_get_hi_posDelegate n_get_hi_pos;

        /// <summary>
        ///  uint n_auto_cal(uint CardNo, uint HeadNo, uint Command);
        /// </summary>
        public static n_auto_calDelegate n_auto_cal;

        /// <summary>
        ///  uint n_get_auto_cal(uint CardNo, uint HeadNo);
        /// </summary>
        public static n_get_auto_calDelegate n_get_auto_cal;

        /// <summary>
        ///  uint n_write_hi_pos(uint CardNo, uint HeadNo, int X1, int X2, int Y1, int Y2);
        /// </summary>
        public static n_write_hi_posDelegate n_write_hi_pos;

        /// <summary>
        ///  void n_set_sky_writing(uint CardNo, double Timelag, int LaserOnShift);
        /// </summary>
        public static n_set_sky_writingDelegate n_set_sky_writing;

        /// <summary>
        ///  void n_get_hi_data(uint CardNo, out int X1, out int X2, out int Y1, out int Y2);
        /// </summary>
        public static n_get_hi_dataDelegate n_get_hi_data;

        /// <summary>
        ///  void set_delay_mode(uint VarPoly, uint DirectMove3D, uint EdgeLevel, uint MinJumpDelay, uint JumpLengthLimit);
        /// </summary>
        public static set_delay_modeDelegate set_delay_mode;

        /// <summary>
        ///  void set_jump_speed_ctrl(double Speed);
        /// </summary>
        public static set_jump_speed_ctrlDelegate set_jump_speed_ctrl;

        /// <summary>
        ///  void set_mark_speed_ctrl(double Speed);
        /// </summary>
        public static set_mark_speed_ctrlDelegate set_mark_speed_ctrl;

        /// <summary>
        ///  void set_sky_writing_para(double Timelag, int LaserOnShift, uint Nprev, uint Npost);
        /// </summary>
        public static set_sky_writing_paraDelegate set_sky_writing_para;

        /// <summary>
        ///  void set_sky_writing_limit(double CosAngle);
        /// </summary>
        public static set_sky_writing_limitDelegate set_sky_writing_limit;

        /// <summary>
        ///  void set_sky_writing_mode(uint Mode);
        /// </summary>
        public static set_sky_writing_modeDelegate set_sky_writing_mode;

        /// <summary>
        ///  int load_varpolydelay(string Name, uint No);
        /// </summary>
        public static load_varpolydelayDelegate load_varpolydelay;

        /// <summary>
        ///  void set_hi(uint HeadNo, double GalvoGainX, double GalvoGainY, int GalvoOffsetX, int GalvoOffsetY);
        /// </summary>
        public static set_hiDelegate set_hi;

        /// <summary>
        ///  void get_hi_pos(uint HeadNo, out int X1, out int X2, out int Y1, out int Y2);
        /// </summary>
        public static get_hi_posDelegate get_hi_pos;

        /// <summary>
        ///  uint auto_cal(uint HeadNo, uint Command);
        /// </summary>
        public static auto_calDelegate auto_cal;

        /// <summary>
        ///  uint get_auto_cal(uint HeadNo);
        /// </summary>
        public static get_auto_calDelegate get_auto_cal;

        /// <summary>
        ///  uint write_hi_pos(uint HeadNo, int X1, int X2, int Y1, int Y2);
        /// </summary>
        public static write_hi_posDelegate write_hi_pos;

        /// <summary>
        ///  void set_sky_writing(double Timelag, int LaserOnShift);
        /// </summary>
        public static set_sky_writingDelegate set_sky_writing;

        /// <summary>
        ///  void get_hi_data(out int X1, out int X2, out int Y1, out int Y2);
        /// </summary>
        public static get_hi_dataDelegate get_hi_data;

        /// <summary>
        ///  void n_send_user_data(uint CardNo, uint Head, uint Axis, int Data0, int Data1, int Data2, int Data3, int Data4);
        /// </summary>
        public static n_send_user_dataDelegate n_send_user_data;

        /// <summary>
        ///  int n_read_user_data(uint CardNo, uint Head, uint Axis, out int Data0, out int Data1, out int Data2, out int Data3, out int Data4);
        /// </summary>
        public static n_read_user_dataDelegate n_read_user_data;

        /// <summary>
        ///  void n_control_command(uint CardNo, uint Head, uint Axis, uint Data);
        /// </summary>
        public static n_control_commandDelegate n_control_command;

        /// <summary>
        ///  int n_get_value(uint CardNo, uint Signal);
        /// </summary>
        public static n_get_valueDelegate n_get_value;

        /// <summary>
        ///  void n_get_values(uint CardNo, uint[] SignalPtr, int[] ResultPtr);
        /// </summary>
        public static n_get_valuesDelegate n_get_values;

        /// <summary>
        ///  void n_get_galvo_controls(uint CardNo, int[] SignalPtr, int[] ResultPtr);
        /// </summary>
        public static n_get_galvo_controlsDelegate n_get_galvo_controls;

        /// <summary>
        ///  uint n_get_head_status(uint CardNo, uint Head);
        /// </summary>
        public static n_get_head_statusDelegate n_get_head_status;

        /// <summary>
        ///  int n_set_jump_mode(uint CardNo, int Flag, uint Length, int VA1, int VA2, int VB1, int VB2, int JA1, int JA2, int JB1, int JB2);
        /// </summary>
        public static n_set_jump_modeDelegate n_set_jump_mode;

        /// <summary>
        ///  int n_load_jump_table_offset(uint CardNo, string Name, uint No, uint PosAck, int Offset, uint MinDelay, uint MaxDelay, uint ListPos);
        /// </summary>
        public static n_load_jump_table_offsetDelegate n_load_jump_table_offset;

        /// <summary>
        ///  uint n_get_jump_table(uint CardNo, ushort[] Ptr);
        /// </summary>
        public static n_get_jump_tableDelegate n_get_jump_table;

        /// <summary>
        ///  uint n_set_jump_table(uint CardNo, ushort[] Ptr);
        /// </summary>
        public static n_set_jump_tableDelegate n_set_jump_table;

        /// <summary>
        ///  int n_load_jump_table(uint CardNo, string Name, uint No, uint PosAck, uint MinDelay, uint MaxDelay, uint ListPos);
        /// </summary>
        public static n_load_jump_tableDelegate n_load_jump_table;

        /// <summary>
        ///  void send_user_data(uint Head, uint Axis, int Data0, int Data1, int Data2, int Data3, int Data4);
        /// </summary>
        public static send_user_dataDelegate send_user_data;

        /// <summary>
        ///  int read_user_data(uint Head, uint Axis, out int Data0, out int Data1, out int Data2, out int Data3, out int Data4);
        /// </summary>
        public static read_user_dataDelegate read_user_data;

        /// <summary>
        ///  void control_command(uint Head, uint Axis, uint Data);
        /// </summary>
        public static control_commandDelegate control_command;

        /// <summary>
        ///  int get_value(uint Signal);
        /// </summary>
        public static get_valueDelegate get_value;

        /// <summary>
        ///  void get_values(uint[] SignalPtr, int[] ResultPtr);
        /// </summary>
        public static get_valuesDelegate get_values;

        /// <summary>
        ///  void get_galvo_controls(int[] SignalPtr, int[] ResultPtr);
        /// </summary>
        public static get_galvo_controlsDelegate get_galvo_controls;

        /// <summary>
        ///  uint get_head_status(uint Head);
        /// </summary>
        public static get_head_statusDelegate get_head_status;

        /// <summary>
        ///  int set_jump_mode(int Flag, uint Length, int VA1, int VA2, int VB1, int VB2, int JA1, int JA2, int JB1, int JB2);
        /// </summary>
        public static set_jump_modeDelegate set_jump_mode;

        /// <summary>
        ///  int load_jump_table_offset(string Name, uint No, uint PosAck, int Offset, uint MinDelay, uint MaxDelay, uint ListPos);
        /// </summary>
        public static load_jump_table_offsetDelegate load_jump_table_offset;

        /// <summary>
        ///  uint get_jump_table(ushort[] Ptr);
        /// </summary>
        public static get_jump_tableDelegate get_jump_table;

        /// <summary>
        ///  uint set_jump_table(ushort[] Ptr);
        /// </summary>
        public static set_jump_tableDelegate set_jump_table;

        /// <summary>
        ///  int load_jump_table(string Name, uint No, uint PosAck, uint MinDelay, uint MaxDelay, uint ListPos);
        /// </summary>
        public static load_jump_tableDelegate load_jump_table;

        /// <summary>
        ///  void n_stepper_init(uint CardNo, uint No, uint Period, int Dir, int Pos, uint Tol, uint Enable, uint WaitTime);
        /// </summary>
        public static n_stepper_initDelegate n_stepper_init;

        /// <summary>
        ///  void n_stepper_enable(uint CardNo, int Enable1, int Enable2);
        /// </summary>
        public static n_stepper_enableDelegate n_stepper_enable;

        /// <summary>
        ///  void n_stepper_disable_switch(uint CardNo, int Disable1, int Disable2);
        /// </summary>
        public static n_stepper_disable_switchDelegate n_stepper_disable_switch;

        /// <summary>
        ///  void n_stepper_control(uint CardNo, int Period1, int Period2);
        /// </summary>
        public static n_stepper_controlDelegate n_stepper_control;

        /// <summary>
        ///  void n_stepper_abs_no(uint CardNo, uint No, int Pos, uint WaitTime);
        /// </summary>
        public static n_stepper_abs_noDelegate n_stepper_abs_no;

        /// <summary>
        ///  void n_stepper_rel_no(uint CardNo, uint No, int dPos, uint WaitTime);
        /// </summary>
        public static n_stepper_rel_noDelegate n_stepper_rel_no;

        /// <summary>
        ///  void n_stepper_abs(uint CardNo, int Pos1, int Pos2, uint WaitTime);
        /// </summary>
        public static n_stepper_absDelegate n_stepper_abs;

        /// <summary>
        ///  void n_stepper_rel(uint CardNo, int dPos1, int dPos2, uint WaitTime);
        /// </summary>
        public static n_stepper_relDelegate n_stepper_rel;

        /// <summary>
        ///  void n_get_stepper_status(uint CardNo, out uint Status1, out int Pos1, out uint Status2, out int Pos2);
        /// </summary>
        public static n_get_stepper_statusDelegate n_get_stepper_status;

        /// <summary>
        ///  void stepper_init(uint No, uint Period, int Dir, int Pos, uint Tol, uint Enable, uint WaitTime);
        /// </summary>
        public static stepper_initDelegate stepper_init;

        /// <summary>
        ///  void stepper_enable(int Enable1, int Enable2);
        /// </summary>
        public static stepper_enableDelegate stepper_enable;

        /// <summary>
        ///  void stepper_disable_switch(int Disable1, int Disable2);
        /// </summary>
        public static stepper_disable_switchDelegate stepper_disable_switch;

        /// <summary>
        ///  void stepper_control(int Period1, int Period2);
        /// </summary>
        public static stepper_controlDelegate stepper_control;

        /// <summary>
        ///  void stepper_abs_no(uint No, int Pos, uint WaitTime);
        /// </summary>
        public static stepper_abs_noDelegate stepper_abs_no;

        /// <summary>
        ///  void stepper_rel_no(uint No, int dPos, uint WaitTime);
        /// </summary>
        public static stepper_rel_noDelegate stepper_rel_no;

        /// <summary>
        ///  void stepper_abs(int Pos1, int Pos2, uint WaitTime);
        /// </summary>
        public static stepper_absDelegate stepper_abs;

        /// <summary>
        ///  void stepper_rel(int dPos1, int dPos2, uint WaitTime);
        /// </summary>
        public static stepper_relDelegate stepper_rel;

        /// <summary>
        ///  void get_stepper_status(out uint Status1, out int Pos1, out uint Status2, out int Pos2);
        /// </summary>
        public static get_stepper_statusDelegate get_stepper_status;

        /// <summary>
        ///  void n_select_cor_table_list(uint CardNo, uint HeadA, uint HeadB);
        /// </summary>
        public static n_select_cor_table_listDelegate n_select_cor_table_list;

        /// <summary>
        ///  void select_cor_table_list(uint HeadA, uint HeadB);
        /// </summary>
        public static select_cor_table_listDelegate select_cor_table_list;

        /// <summary>
        ///  void n_list_nop(uint CardNo);
        /// </summary>
        public static n_list_nopDelegate n_list_nop;

        /// <summary>
        ///  void n_list_continue(uint CardNo);
        /// </summary>
        public static n_list_continueDelegate n_list_continue;

        /// <summary>
        ///  void n_list_next(uint CardNo);
        /// </summary>
        public static n_list_nextDelegate n_list_next;

        /// <summary>
        ///  void n_long_delay(uint CardNo, uint Delay);
        /// </summary>
        public static n_long_delayDelegate n_long_delay;

        /// <summary>
        ///  void n_set_end_of_list(uint CardNo);
        /// </summary>
        public static n_set_end_of_listDelegate n_set_end_of_list;

        /// <summary>
        ///  void n_set_wait(uint CardNo, uint WaitWord);
        /// </summary>
        public static n_set_waitDelegate n_set_wait;

        /// <summary>
        ///  void n_list_jump_pos(uint CardNo, uint Pos);
        /// </summary>
        public static n_list_jump_posDelegate n_list_jump_pos;

        /// <summary>
        ///  void n_list_jump_rel(uint CardNo, int Pos);
        /// </summary>
        public static n_list_jump_relDelegate n_list_jump_rel;

        /// <summary>
        ///  void n_list_repeat(uint CardNo);
        /// </summary>
        public static n_list_repeatDelegate n_list_repeat;

        /// <summary>
        ///  void n_list_until(uint CardNo, uint Number);
        /// </summary>
        public static n_list_untilDelegate n_list_until;

        /// <summary>
        ///  void n_range_checking(uint CardNo, uint HeadNo, uint Mode, uint Data);
        /// </summary>
        public static n_range_checkingDelegate n_range_checking;

        /// <summary>
        ///  void n_set_list_jump(uint CardNo, uint Pos);
        /// </summary>
        public static n_set_list_jumpDelegate n_set_list_jump;

        /// <summary>
        ///  void list_nop();
        /// </summary>
        public static list_nopDelegate list_nop;

        /// <summary>
        ///  void list_continue();
        /// </summary>
        public static list_continueDelegate list_continue;

        /// <summary>
        ///  void list_next();
        /// </summary>
        public static list_nextDelegate list_next;

        /// <summary>
        ///  void long_delay(uint Delay);
        /// </summary>
        public static long_delayDelegate long_delay;

        /// <summary>
        ///  void set_end_of_list();
        /// </summary>
        public static set_end_of_listDelegate set_end_of_list;

        /// <summary>
        ///  void set_wait(uint WaitWord);
        /// </summary>
        public static set_waitDelegate set_wait;

        /// <summary>
        ///  void list_jump_pos(uint Pos);
        /// </summary>
        public static list_jump_posDelegate list_jump_pos;

        /// <summary>
        ///  void list_jump_rel(int Pos);
        /// </summary>
        public static list_jump_relDelegate list_jump_rel;

        /// <summary>
        ///  void list_repeat();
        /// </summary>
        public static list_repeatDelegate list_repeat;

        /// <summary>
        ///  void list_until(uint Number);
        /// </summary>
        public static list_untilDelegate list_until;

        /// <summary>
        ///  void range_checking(uint HeadNo, uint Mode, uint Data);
        /// </summary>
        public static range_checkingDelegate range_checking;

        /// <summary>
        ///  void set_list_jump(uint Pos);
        /// </summary>
        public static set_list_jumpDelegate set_list_jump;

        /// <summary>
        ///  void n_set_extstartpos_list(uint CardNo, uint Pos);
        /// </summary>
        public static n_set_extstartpos_listDelegate n_set_extstartpos_list;

        /// <summary>
        ///  void n_set_control_mode_list(uint CardNo, uint Mode);
        /// </summary>
        public static n_set_control_mode_listDelegate n_set_control_mode_list;

        /// <summary>
        ///  void n_simulate_ext_start(uint CardNo, int Delay, uint EncoderNo);
        /// </summary>
        public static n_simulate_ext_startDelegate n_simulate_ext_start;

        /// <summary>
        ///  void set_extstartpos_list(uint Pos);
        /// </summary>
        public static set_extstartpos_listDelegate set_extstartpos_list;

        /// <summary>
        ///  void set_control_mode_list(uint Mode);
        /// </summary>
        public static set_control_mode_listDelegate set_control_mode_list;

        /// <summary>
        ///  void simulate_ext_start(int Delay, uint EncoderNo);
        /// </summary>
        public static simulate_ext_startDelegate simulate_ext_start;

        /// <summary>
        ///  void n_list_return(uint CardNo);
        /// </summary>
        public static n_list_returnDelegate n_list_return;

        /// <summary>
        ///  void n_list_call_repeat(uint CardNo, uint Pos, uint Number);
        /// </summary>
        public static n_list_call_repeatDelegate n_list_call_repeat;

        /// <summary>
        ///  void n_list_call_abs_repeat(uint CardNo, uint Pos, uint Number);
        /// </summary>
        public static n_list_call_abs_repeatDelegate n_list_call_abs_repeat;

        /// <summary>
        ///  void n_list_call(uint CardNo, uint Pos);
        /// </summary>
        public static n_list_callDelegate n_list_call;

        /// <summary>
        ///  void n_list_call_abs(uint CardNo, uint Pos);
        /// </summary>
        public static n_list_call_absDelegate n_list_call_abs;

        /// <summary>
        ///  void n_sub_call_repeat(uint CardNo, uint Index, uint Number);
        /// </summary>
        public static n_sub_call_repeatDelegate n_sub_call_repeat;

        /// <summary>
        ///  void n_sub_call_abs_repeat(uint CardNo, uint Index, uint Number);
        /// </summary>
        public static n_sub_call_abs_repeatDelegate n_sub_call_abs_repeat;

        /// <summary>
        ///  void n_sub_call(uint CardNo, uint Index);
        /// </summary>
        public static n_sub_callDelegate n_sub_call;

        /// <summary>
        ///  void n_sub_call_abs(uint CardNo, uint Index);
        /// </summary>
        public static n_sub_call_absDelegate n_sub_call_abs;

        /// <summary>
        ///  void list_return();
        /// </summary>
        public static list_returnDelegate list_return;

        /// <summary>
        ///  void list_call_repeat(uint Pos, uint Number);
        /// </summary>
        public static list_call_repeatDelegate list_call_repeat;

        /// <summary>
        ///  void list_call_abs_repeat(uint Pos, uint Number);
        /// </summary>
        public static list_call_abs_repeatDelegate list_call_abs_repeat;

        /// <summary>
        ///  void list_call(uint Pos);
        /// </summary>
        public static list_callDelegate list_call;

        /// <summary>
        ///  void list_call_abs(uint Pos);
        /// </summary>
        public static list_call_absDelegate list_call_abs;

        /// <summary>
        ///  void sub_call_repeat(uint Index, uint Number);
        /// </summary>
        public static sub_call_repeatDelegate sub_call_repeat;

        /// <summary>
        ///  void sub_call_abs_repeat(uint Index, uint Number);
        /// </summary>
        public static sub_call_abs_repeatDelegate sub_call_abs_repeat;

        /// <summary>
        ///  void sub_call(uint Index);
        /// </summary>
        public static sub_callDelegate sub_call;

        /// <summary>
        ///  void sub_call_abs(uint Index);
        /// </summary>
        public static sub_call_absDelegate sub_call_abs;

        /// <summary>
        ///  void n_list_call_cond(uint CardNo, uint Mask1, uint Mask0, uint Pos);
        /// </summary>
        public static n_list_call_condDelegate n_list_call_cond;

        /// <summary>
        ///  void n_list_call_abs_cond(uint CardNo, uint Mask1, uint Mask0, uint Pos);
        /// </summary>
        public static n_list_call_abs_condDelegate n_list_call_abs_cond;

        /// <summary>
        ///  void n_sub_call_cond(uint CardNo, uint Mask1, uint Mask0, uint Pos);
        /// </summary>
        public static n_sub_call_condDelegate n_sub_call_cond;

        /// <summary>
        ///  void n_sub_call_abs_cond(uint CardNo, uint Mask1, uint Mask0, uint Pos);
        /// </summary>
        public static n_sub_call_abs_condDelegate n_sub_call_abs_cond;

        /// <summary>
        ///  void n_list_jump_pos_cond(uint CardNo, uint Mask1, uint Mask0, uint Index);
        /// </summary>
        public static n_list_jump_pos_condDelegate n_list_jump_pos_cond;

        /// <summary>
        ///  void n_list_jump_rel_cond(uint CardNo, uint Mask1, uint Mask0, int Index);
        /// </summary>
        public static n_list_jump_rel_condDelegate n_list_jump_rel_cond;

        /// <summary>
        ///  void n_if_cond(uint CardNo, uint Mask1, uint Mask0);
        /// </summary>
        public static n_if_condDelegate n_if_cond;

        /// <summary>
        ///  void n_if_not_cond(uint CardNo, uint Mask1, uint Mask0);
        /// </summary>
        public static n_if_not_condDelegate n_if_not_cond;

        /// <summary>
        ///  void n_if_pin_cond(uint CardNo, uint Mask1, uint Mask0);
        /// </summary>
        public static n_if_pin_condDelegate n_if_pin_cond;

        /// <summary>
        ///  void n_if_not_pin_cond(uint CardNo, uint Mask1, uint Mask0);
        /// </summary>
        public static n_if_not_pin_condDelegate n_if_not_pin_cond;

        /// <summary>
        ///  void n_switch_ioport(uint CardNo, uint MaskBits, uint ShiftBits);
        /// </summary>
        public static n_switch_ioportDelegate n_switch_ioport;

        /// <summary>
        ///  void n_list_jump_cond(uint CardNo, uint Mask1, uint Mask0, uint Pos);
        /// </summary>
        public static n_list_jump_condDelegate n_list_jump_cond;

        /// <summary>
        ///  void list_call_cond(uint Mask1, uint Mask0, uint Pos);
        /// </summary>
        public static list_call_condDelegate list_call_cond;

        /// <summary>
        ///  void list_call_abs_cond(uint Mask1, uint Mask0, uint Pos);
        /// </summary>
        public static list_call_abs_condDelegate list_call_abs_cond;

        /// <summary>
        ///  void sub_call_cond(uint Mask1, uint Mask0, uint Index);
        /// </summary>
        public static sub_call_condDelegate sub_call_cond;

        /// <summary>
        ///  void sub_call_abs_cond(uint Mask1, uint Mask0, uint Index);
        /// </summary>
        public static sub_call_abs_condDelegate sub_call_abs_cond;

        /// <summary>
        ///  void list_jump_pos_cond(uint Mask1, uint Mask0, uint Pos);
        /// </summary>
        public static list_jump_pos_condDelegate list_jump_pos_cond;

        /// <summary>
        ///  void list_jump_rel_cond(uint Mask1, uint Mask0, int Pos);
        /// </summary>
        public static list_jump_rel_condDelegate list_jump_rel_cond;

        /// <summary>
        ///  void if_cond(uint Mask1, uint Mask0);
        /// </summary>
        public static if_condDelegate if_cond;

        /// <summary>
        ///  void if_not_cond(uint Mask1, uint Mask0);
        /// </summary>
        public static if_not_condDelegate if_not_cond;

        /// <summary>
        ///  void if_pin_cond(uint Mask1, uint Mask0);
        /// </summary>
        public static if_pin_condDelegate if_pin_cond;

        /// <summary>
        ///  void if_not_pin_cond(uint Mask1, uint Mask0);
        /// </summary>
        public static if_not_pin_condDelegate if_not_pin_cond;

        /// <summary>
        ///  void switch_ioport(uint MaskBits, uint ShiftBits);
        /// </summary>
        public static switch_ioportDelegate switch_ioport;

        /// <summary>
        ///  void list_jump_cond(uint Mask1, uint Mask0, uint Pos);
        /// </summary>
        public static list_jump_condDelegate list_jump_cond;

        /// <summary>
        ///  void n_select_char_set(uint CardNo, uint No);
        /// </summary>
        public static n_select_char_setDelegate n_select_char_set;

        /// <summary>
        ///  void n_mark_text(uint CardNo, string Text);
        /// </summary>
        public static n_mark_textDelegate n_mark_text;

        /// <summary>
        ///  void n_mark_text_abs(uint CardNo, string Text);
        /// </summary>
        public static n_mark_text_absDelegate n_mark_text_abs;

        /// <summary>
        ///  void n_mark_char(uint CardNo, uint Char);
        /// </summary>
        public static n_mark_charDelegate n_mark_char;

        /// <summary>
        ///  void n_mark_char_abs(uint CardNo, uint Char);
        /// </summary>
        public static n_mark_char_absDelegate n_mark_char_abs;

        /// <summary>
        ///  void select_char_set(uint No);
        /// </summary>
        public static select_char_setDelegate select_char_set;

        /// <summary>
        ///  void mark_text(string Text);
        /// </summary>
        public static mark_textDelegate mark_text;

        /// <summary>
        ///  void mark_text_abs(string Text);
        /// </summary>
        public static mark_text_absDelegate mark_text_abs;

        /// <summary>
        ///  void mark_char(uint Char);
        /// </summary>
        public static mark_charDelegate mark_char;

        /// <summary>
        ///  void mark_char_abs(uint Char);
        /// </summary>
        public static mark_char_absDelegate mark_char_abs;

        /// <summary>
        ///  void n_mark_serial(uint CardNo, uint Mode, uint Digits);
        /// </summary>
        public static n_mark_serialDelegate n_mark_serial;

        /// <summary>
        ///  void n_mark_serial_abs(uint CardNo, uint Mode, uint Digits);
        /// </summary>
        public static n_mark_serial_absDelegate n_mark_serial_abs;

        /// <summary>
        ///  void n_mark_date(uint CardNo, uint Part, uint Mode);
        /// </summary>
        public static n_mark_dateDelegate n_mark_date;

        /// <summary>
        ///  void n_mark_date_abs(uint CardNo, uint Part, uint Mode);
        /// </summary>
        public static n_mark_date_absDelegate n_mark_date_abs;

        /// <summary>
        ///  void n_mark_time(uint CardNo, uint Part, uint Mode);
        /// </summary>
        public static n_mark_timeDelegate n_mark_time;

        /// <summary>
        ///  void n_mark_time_abs(uint CardNo, uint Part, uint Mode);
        /// </summary>
        public static n_mark_time_absDelegate n_mark_time_abs;

        /// <summary>
        ///  void n_select_serial_set_list(uint CardNo, uint No);
        /// </summary>
        public static n_select_serial_set_listDelegate n_select_serial_set_list;

        /// <summary>
        ///  void n_set_serial_step_list(uint CardNo, uint No, uint Step);
        /// </summary>
        public static n_set_serial_step_listDelegate n_set_serial_step_list;

        /// <summary>
        ///  void n_time_fix_f_off(uint CardNo, uint FirstDay, uint Offset);
        /// </summary>
        public static n_time_fix_f_offDelegate n_time_fix_f_off;

        /// <summary>
        ///  void n_time_fix_f(uint CardNo, uint FirstDay);
        /// </summary>
        public static n_time_fix_fDelegate n_time_fix_f;

        /// <summary>
        ///  void n_time_fix(uint CardNo);
        /// </summary>
        public static n_time_fixDelegate n_time_fix;

        /// <summary>
        ///  void mark_serial(uint Mode, uint Digits);
        /// </summary>
        public static mark_serialDelegate mark_serial;

        /// <summary>
        ///  void mark_serial_abs(uint Mode, uint Digits);
        /// </summary>
        public static mark_serial_absDelegate mark_serial_abs;

        /// <summary>
        ///  void mark_date(uint Part, uint Mode);
        /// </summary>
        public static mark_dateDelegate mark_date;

        /// <summary>
        ///  void mark_date_abs(uint Part, uint Mode);
        /// </summary>
        public static mark_date_absDelegate mark_date_abs;

        /// <summary>
        ///  void mark_time(uint Part, uint Mode);
        /// </summary>
        public static mark_timeDelegate mark_time;

        /// <summary>
        ///  void mark_time_abs(uint Part, uint Mode);
        /// </summary>
        public static mark_time_absDelegate mark_time_abs;

        /// <summary>
        ///  void time_fix_f_off(uint FirstDay, uint Offset);
        /// </summary>
        public static time_fix_f_offDelegate time_fix_f_off;

        /// <summary>
        ///  void select_serial_set_list(uint No);
        /// </summary>
        public static select_serial_set_listDelegate select_serial_set_list;

        /// <summary>
        ///  void set_serial_step_list(uint No, uint Step);
        /// </summary>
        public static set_serial_step_listDelegate set_serial_step_list;

        /// <summary>
        ///  void time_fix_f(uint FirstDay);
        /// </summary>
        public static time_fix_fDelegate time_fix_f;

        /// <summary>
        ///  void time_fix();
        /// </summary>
        public static time_fixDelegate time_fix;

        /// <summary>
        ///  void n_clear_io_cond_list(uint CardNo, uint Mask1, uint Mask0, uint Mask);
        /// </summary>
        public static n_clear_io_cond_listDelegate n_clear_io_cond_list;

        /// <summary>
        ///  void n_set_io_cond_list(uint CardNo, uint Mask1, uint Mask0, uint Mask);
        /// </summary>
        public static n_set_io_cond_listDelegate n_set_io_cond_list;

        /// <summary>
        ///  void n_write_io_port_mask_list(uint CardNo, uint Value, uint Mask);
        /// </summary>
        public static n_write_io_port_mask_listDelegate n_write_io_port_mask_list;

        /// <summary>
        ///  void n_write_8bit_port_list(uint CardNo, uint Value);
        /// </summary>
        public static n_write_8bit_port_listDelegate n_write_8bit_port_list;

        /// <summary>
        ///  void n_read_io_port_list(uint CardNo);
        /// </summary>
        public static n_read_io_port_listDelegate n_read_io_port_list;

        /// <summary>
        ///  void n_write_da_x_list(uint CardNo, uint x, uint Value);
        /// </summary>
        public static n_write_da_x_listDelegate n_write_da_x_list;

        /// <summary>
        ///  void n_write_io_port_list(uint CardNo, uint Value);
        /// </summary>
        public static n_write_io_port_listDelegate n_write_io_port_list;

        /// <summary>
        ///  void n_write_da_1_list(uint CardNo, uint Value);
        /// </summary>
        public static n_write_da_1_listDelegate n_write_da_1_list;

        /// <summary>
        ///  void n_write_da_2_list(uint CardNo, uint Value);
        /// </summary>
        public static n_write_da_2_listDelegate n_write_da_2_list;

        /// <summary>
        ///  void clear_io_cond_list(uint Mask1, uint Mask0, uint MaskClear);
        /// </summary>
        public static clear_io_cond_listDelegate clear_io_cond_list;

        /// <summary>
        ///  void set_io_cond_list(uint Mask1, uint Mask0, uint MaskSet);
        /// </summary>
        public static set_io_cond_listDelegate set_io_cond_list;

        /// <summary>
        ///  void write_io_port_mask_list(uint Value, uint Mask);
        /// </summary>
        public static write_io_port_mask_listDelegate write_io_port_mask_list;

        /// <summary>
        ///  void write_8bit_port_list(uint Value);
        /// </summary>
        public static write_8bit_port_listDelegate write_8bit_port_list;

        /// <summary>
        ///  void read_io_port_list();
        /// </summary>
        public static read_io_port_listDelegate read_io_port_list;

        /// <summary>
        ///  void write_da_x_list(uint x, uint Value);
        /// </summary>
        public static write_da_x_listDelegate write_da_x_list;

        /// <summary>
        ///  void write_io_port_list(uint Value);
        /// </summary>
        public static write_io_port_listDelegate write_io_port_list;

        /// <summary>
        ///  void write_da_1_list(uint Value);
        /// </summary>
        public static write_da_1_listDelegate write_da_1_list;

        /// <summary>
        ///  void write_da_2_list(uint Value);
        /// </summary>
        public static write_da_2_listDelegate write_da_2_list;

        /// <summary>
        ///  void n_laser_signal_on_list(uint CardNo);
        /// </summary>
        public static n_laser_signal_on_listDelegate n_laser_signal_on_list;

        /// <summary>
        ///  void n_laser_signal_off_list(uint CardNo);
        /// </summary>
        public static n_laser_signal_off_listDelegate n_laser_signal_off_list;

        /// <summary>
        ///  void n_para_laser_on_pulses_list(uint CardNo, uint Period, uint Pulses, uint P);
        /// </summary>
        public static n_para_laser_on_pulses_listDelegate n_para_laser_on_pulses_list;

        /// <summary>
        ///  void n_laser_on_pulses_list(uint CardNo, uint Period, uint Pulses);
        /// </summary>
        public static n_laser_on_pulses_listDelegate n_laser_on_pulses_list;

        /// <summary>
        ///  void n_laser_on_list(uint CardNo, uint Period);
        /// </summary>
        public static n_laser_on_listDelegate n_laser_on_list;

        /// <summary>
        ///  void n_set_laser_delays(uint CardNo, int LaserOnDelay, uint LaserOffDelay);
        /// </summary>
        public static n_set_laser_delaysDelegate n_set_laser_delays;

        /// <summary>
        ///  void n_set_standby_list(uint CardNo, uint HalfPeriod, uint PulseLength);
        /// </summary>
        public static n_set_standby_listDelegate n_set_standby_list;

        /// <summary>
        ///  void n_set_laser_pulses(uint CardNo, uint HalfPeriod, uint PulseLength);
        /// </summary>
        public static n_set_laser_pulsesDelegate n_set_laser_pulses;

        /// <summary>
        ///  void n_set_firstpulse_killer_list(uint CardNo, uint Length);
        /// </summary>
        public static n_set_firstpulse_killer_listDelegate n_set_firstpulse_killer_list;

        /// <summary>
        ///  void n_set_qswitch_delay_list(uint CardNo, uint Delay);
        /// </summary>
        public static n_set_qswitch_delay_listDelegate n_set_qswitch_delay_list;

        /// <summary>
        ///  void n_set_laser_pin_out_list(uint CardNo, uint Pins);
        /// </summary>
        public static n_set_laser_pin_out_listDelegate n_set_laser_pin_out_list;

        /// <summary>
        ///  void n_set_vector_control(uint CardNo, uint Ctrl, uint Value);
        /// </summary>
        public static n_set_vector_controlDelegate n_set_vector_control;

        /// <summary>
        ///  void n_set_default_pixel_list(uint CardNo, uint PulseLength);
        /// </summary>
        public static n_set_default_pixel_listDelegate n_set_default_pixel_list;

        /// <summary>
        ///  void n_set_port_default_list(uint CardNo, uint Port, uint Value);
        /// </summary>
        public static n_set_port_default_listDelegate n_set_port_default_list;

        /// <summary>
        ///  void n_set_auto_laser_params_list(uint CardNo, uint Ctrl, uint Value, uint MinValue, uint MaxValue);
        /// </summary>
        public static n_set_auto_laser_params_listDelegate n_set_auto_laser_params_list;

        /// <summary>
        ///  void n_set_pulse_picking_list(uint CardNo, uint No);
        /// </summary>
        public static n_set_pulse_picking_listDelegate n_set_pulse_picking_list;

        /// <summary>
        ///  void n_set_softstart_level_list(uint CardNo, uint Index, uint Level1, uint Level2, uint Level3);
        /// </summary>
        public static n_set_softstart_level_listDelegate n_set_softstart_level_list;

        /// <summary>
        ///  void n_set_softstart_mode_list(uint CardNo, uint Mode, uint Number, uint Delay);
        /// </summary>
        public static n_set_softstart_mode_listDelegate n_set_softstart_mode_list;

        /// <summary>
        ///  void n_config_laser_signals_list(uint CardNo, uint Config);
        /// </summary>
        public static n_config_laser_signals_listDelegate n_config_laser_signals_list;

        /// <summary>
        ///  void n_set_laser_timing(uint CardNo, uint HalfPeriod, uint PulseLength1, uint PulseLength2, uint TimeBase);
        /// </summary>
        public static n_set_laser_timingDelegate n_set_laser_timing;

        /// <summary>
        ///  void laser_signal_on_list();
        /// </summary>
        public static laser_signal_on_listDelegate laser_signal_on_list;

        /// <summary>
        ///  void laser_signal_off_list();
        /// </summary>
        public static laser_signal_off_listDelegate laser_signal_off_list;

        /// <summary>
        ///  void para_laser_on_pulses_list(uint Period, uint Pulses, uint P);
        /// </summary>
        public static para_laser_on_pulses_listDelegate para_laser_on_pulses_list;

        /// <summary>
        ///  void laser_on_pulses_list(uint Period, uint Pulses);
        /// </summary>
        public static laser_on_pulses_listDelegate laser_on_pulses_list;

        /// <summary>
        ///  void laser_on_list(uint Period);
        /// </summary>
        public static laser_on_listDelegate laser_on_list;

        /// <summary>
        ///  void set_laser_delays(int LaserOnDelay, uint LaserOffDelay);
        /// </summary>
        public static set_laser_delaysDelegate set_laser_delays;

        /// <summary>
        ///  void set_standby_list(uint HalfPeriod, uint PulseLength);
        /// </summary>
        public static set_standby_listDelegate set_standby_list;

        /// <summary>
        ///  void set_laser_pulses(uint HalfPeriod, uint PulseLength);
        /// </summary>
        public static set_laser_pulsesDelegate set_laser_pulses;

        /// <summary>
        ///  void set_firstpulse_killer_list(uint Length);
        /// </summary>
        public static set_firstpulse_killer_listDelegate set_firstpulse_killer_list;

        /// <summary>
        ///  void set_qswitch_delay_list(uint Delay);
        /// </summary>
        public static set_qswitch_delay_listDelegate set_qswitch_delay_list;

        /// <summary>
        ///  void set_laser_pin_out_list(uint Pins);
        /// </summary>
        public static set_laser_pin_out_listDelegate set_laser_pin_out_list;

        /// <summary>
        ///  void set_vector_control(uint Ctrl, uint Value);
        /// </summary>
        public static set_vector_controlDelegate set_vector_control;

        /// <summary>
        ///  void set_default_pixel_list(uint PulseLength);
        /// </summary>
        public static set_default_pixel_listDelegate set_default_pixel_list;

        /// <summary>
        ///  void set_port_default_list(uint Port, uint Value);
        /// </summary>
        public static set_port_default_listDelegate set_port_default_list;

        /// <summary>
        ///  void set_auto_laser_params_list(uint Ctrl, uint Value, uint MinValue, uint MaxValue);
        /// </summary>
        public static set_auto_laser_params_listDelegate set_auto_laser_params_list;

        /// <summary>
        ///  void set_pulse_picking_list(uint No);
        /// </summary>
        public static set_pulse_picking_listDelegate set_pulse_picking_list;

        /// <summary>
        ///  void set_softstart_level_list(uint Index, uint Level1, uint Level2, uint Level3);
        /// </summary>
        public static set_softstart_level_listDelegate set_softstart_level_list;

        /// <summary>
        ///  void set_softstart_mode_list(uint Mode, uint Number, uint Delay);
        /// </summary>
        public static set_softstart_mode_listDelegate set_softstart_mode_list;

        /// <summary>
        ///  void config_laser_signals_list(uint Config);
        /// </summary>
        public static config_laser_signals_listDelegate config_laser_signals_list;

        /// <summary>
        ///  void set_laser_timing(uint HalfPeriod, uint PulseLength1, uint PulseLength2, uint TimeBase);
        /// </summary>
        public static set_laser_timingDelegate set_laser_timing;

        /// <summary>
        ///  void n_fly_return_z(uint CardNo, int X, int Y, int Z);
        /// </summary>
        public static n_fly_return_zDelegate n_fly_return_z;

        /// <summary>
        ///  void n_fly_return(uint CardNo, int X, int Y);
        /// </summary>
        public static n_fly_returnDelegate n_fly_return;

        /// <summary>
        ///  void n_set_rot_center_list(uint CardNo, int X, int Y);
        /// </summary>
        public static n_set_rot_center_listDelegate n_set_rot_center_list;

        /// <summary>
        ///  void n_set_ext_start_delay_list(uint CardNo, int Delay, uint EncoderNo);
        /// </summary>
        public static n_set_ext_start_delay_listDelegate n_set_ext_start_delay_list;

        /// <summary>
        ///  void n_set_fly_x(uint CardNo, double ScaleX);
        /// </summary>
        public static n_set_fly_xDelegate n_set_fly_x;

        /// <summary>
        ///  void n_set_fly_y(uint CardNo, double ScaleY);
        /// </summary>
        public static n_set_fly_yDelegate n_set_fly_y;

        /// <summary>
        ///  void n_set_fly_z(uint CardNo, double ScaleZ, uint EndoderNo);
        /// </summary>
        public static n_set_fly_zDelegate n_set_fly_z;

        /// <summary>
        ///  void n_set_fly_rot(uint CardNo, double Resolution);
        /// </summary>
        public static n_set_fly_rotDelegate n_set_fly_rot;

        /// <summary>
        ///  void n_set_fly_2d(uint CardNo, double ScaleX, double ScaleY);
        /// </summary>
        public static n_set_fly_2dDelegate n_set_fly_2d;

        /// <summary>
        ///  void n_set_fly_x_pos(uint CardNo, double ScaleX);
        /// </summary>
        public static n_set_fly_x_posDelegate n_set_fly_x_pos;

        /// <summary>
        ///  void n_set_fly_y_pos(uint CardNo, double ScaleY);
        /// </summary>
        public static n_set_fly_y_posDelegate n_set_fly_y_pos;

        /// <summary>
        ///  void n_set_fly_rot_pos(uint CardNo, double Resolution);
        /// </summary>
        public static n_set_fly_rot_posDelegate n_set_fly_rot_pos;

        /// <summary>
        ///  void n_set_fly_limits(uint CardNo, int Xmin, int Xmax, int Ymin, int Ymax);
        /// </summary>
        public static n_set_fly_limitsDelegate n_set_fly_limits;

        /// <summary>
        ///  void n_set_fly_limits_z(uint CardNo, int Zmin, int Zmax);
        /// </summary>
        public static n_set_fly_limits_zDelegate n_set_fly_limits_z;

        /// <summary>
        ///  void n_if_fly_x_overflow(uint CardNo, int Mode);
        /// </summary>
        public static n_if_fly_x_overflowDelegate n_if_fly_x_overflow;

        /// <summary>
        ///  void n_if_fly_y_overflow(uint CardNo, int Mode);
        /// </summary>
        public static n_if_fly_y_overflowDelegate n_if_fly_y_overflow;

        /// <summary>
        ///  void n_if_fly_z_overflow(uint CardNo, int Mode);
        /// </summary>
        public static n_if_fly_z_overflowDelegate n_if_fly_z_overflow;

        /// <summary>
        ///  void n_if_not_fly_x_overflow(uint CardNo, int Mode);
        /// </summary>
        public static n_if_not_fly_x_overflowDelegate n_if_not_fly_x_overflow;

        /// <summary>
        ///  void n_if_not_fly_y_overflow(uint CardNo, int Mode);
        /// </summary>
        public static n_if_not_fly_y_overflowDelegate n_if_not_fly_y_overflow;

        /// <summary>
        ///  void n_if_not_fly_z_overflow(uint CardNo, int Mode);
        /// </summary>
        public static n_if_not_fly_z_overflowDelegate n_if_not_fly_z_overflow;

        /// <summary>
        ///  void n_clear_fly_overflow(uint CardNo, uint Mode);
        /// </summary>
        public static n_clear_fly_overflowDelegate n_clear_fly_overflow;

        /// <summary>
        ///  void n_set_mcbsp_x_list(uint CardNo, double ScaleX);
        /// </summary>
        public static n_set_mcbsp_x_listDelegate n_set_mcbsp_x_list;

        /// <summary>
        ///  void n_set_mcbsp_y_list(uint CardNo, double ScaleY);
        /// </summary>
        public static n_set_mcbsp_y_listDelegate n_set_mcbsp_y_list;

        /// <summary>
        ///  void n_set_mcbsp_rot_list(uint CardNo, double Resolution);
        /// </summary>
        public static n_set_mcbsp_rot_listDelegate n_set_mcbsp_rot_list;

        /// <summary>
        ///  void n_set_mcbsp_matrix_list(uint CardNo);
        /// </summary>
        public static n_set_mcbsp_matrix_listDelegate n_set_mcbsp_matrix_list;

        /// <summary>
        ///  void n_set_mcbsp_global_x_list(uint CardNo, double ScaleX);
        /// </summary>
        public static n_set_mcbsp_global_x_listDelegate n_set_mcbsp_global_x_list;

        /// <summary>
        ///  void n_set_mcbsp_global_y_list(uint CardNo, double ScaleY);
        /// </summary>
        public static n_set_mcbsp_global_y_listDelegate n_set_mcbsp_global_y_list;

        /// <summary>
        ///  void n_set_mcbsp_global_rot_list(uint CardNo, double Resolution);
        /// </summary>
        public static n_set_mcbsp_global_rot_listDelegate n_set_mcbsp_global_rot_list;

        /// <summary>
        ///  void n_set_mcbsp_global_matrix_list(uint CardNo);
        /// </summary>
        public static n_set_mcbsp_global_matrix_listDelegate n_set_mcbsp_global_matrix_list;

        /// <summary>
        ///  void n_set_mcbsp_in_list(uint CardNo, uint Mode, double Scale);
        /// </summary>
        public static n_set_mcbsp_in_listDelegate n_set_mcbsp_in_list;

        /// <summary>
        ///  void n_set_multi_mcbsp_in_list(uint CardNo, uint Ctrl, uint P, uint Mode);
        /// </summary>
        public static n_set_multi_mcbsp_in_listDelegate n_set_multi_mcbsp_in_list;

        /// <summary>
        ///  void n_wait_for_encoder_mode(uint CardNo, int Value, uint EncoderNo, int Mode);
        /// </summary>
        public static n_wait_for_encoder_modeDelegate n_wait_for_encoder_mode;

        /// <summary>
        ///  void n_wait_for_mcbsp(uint CardNo, uint Axis, int Value, int Mode);
        /// </summary>
        public static n_wait_for_mcbspDelegate n_wait_for_mcbsp;

        /// <summary>
        ///  void n_set_encoder_speed(uint CardNo, uint EncoderNo, double Speed, double Smooth);
        /// </summary>
        public static n_set_encoder_speedDelegate n_set_encoder_speed;

        /// <summary>
        ///  void n_get_mcbsp_list(uint CardNo);
        /// </summary>
        public static n_get_mcbsp_listDelegate n_get_mcbsp_list;

        /// <summary>
        ///  void n_store_encoder(uint CardNo, uint Pos);
        /// </summary>
        public static n_store_encoderDelegate n_store_encoder;

        /// <summary>
        ///  void n_wait_for_encoder_in_range(uint CardNo, int EncXmin, int EncXmax, int EncYmin, int EncYmax);
        /// </summary>
        public static n_wait_for_encoder_in_rangeDelegate n_wait_for_encoder_in_range;

        /// <summary>
        ///  void n_activate_fly_xy(uint CardNo, double ScaleX, double ScaleY);
        /// </summary>
        public static n_activate_fly_xyDelegate n_activate_fly_xy;

        /// <summary>
        ///  void n_activate_fly_2d(uint CardNo, double ScaleX, double ScaleY);
        /// </summary>
        public static n_activate_fly_2dDelegate n_activate_fly_2d;

        /// <summary>
        ///  void n_activate_fly_xy_encoder(uint CardNo, double ScaleX, double ScaleY, int EncX, int EncY);
        /// </summary>
        public static n_activate_fly_xy_encoderDelegate n_activate_fly_xy_encoder;

        /// <summary>
        ///  void n_activate_fly_2d_encoder(uint CardNo, double ScaleX, double ScaleY, int EncX, int EncY);
        /// </summary>
        public static n_activate_fly_2d_encoderDelegate n_activate_fly_2d_encoder;

        /// <summary>
        ///  void n_if_not_activated(uint CardNo);
        /// </summary>
        public static n_if_not_activatedDelegate n_if_not_activated;

        /// <summary>
        ///  void n_park_position(uint CardNo, uint Mode, int X, int Y);
        /// </summary>
        public static n_park_positionDelegate n_park_position;

        /// <summary>
        ///  void n_park_return(uint CardNo, uint Mode, int X, int Y);
        /// </summary>
        public static n_park_returnDelegate n_park_return;

        /// <summary>
        ///  void n_wait_for_encoder(uint CardNo, int Value, uint EncoderNo);
        /// </summary>
        public static n_wait_for_encoderDelegate n_wait_for_encoder;

        /// <summary>
        ///  void fly_return_z(int X, int Y, int Z);
        /// </summary>
        public static fly_return_zDelegate fly_return_z;

        /// <summary>
        ///  void fly_return(int X, int Y);
        /// </summary>
        public static fly_returnDelegate fly_return;

        /// <summary>
        ///  void set_rot_center_list(int X, int Y);
        /// </summary>
        public static set_rot_center_listDelegate set_rot_center_list;

        /// <summary>
        ///  void set_ext_start_delay_list(int Delay, uint EncoderNo);
        /// </summary>
        public static set_ext_start_delay_listDelegate set_ext_start_delay_list;

        /// <summary>
        ///  void set_fly_x(double ScaleX);
        /// </summary>
        public static set_fly_xDelegate set_fly_x;

        /// <summary>
        ///  void set_fly_y(double ScaleY);
        /// </summary>
        public static set_fly_yDelegate set_fly_y;

        /// <summary>
        ///  void set_fly_z(double ScaleZ, uint EncoderNo);
        /// </summary>
        public static set_fly_zDelegate set_fly_z;

        /// <summary>
        ///  void set_fly_rot(double Resolution);
        /// </summary>
        public static set_fly_rotDelegate set_fly_rot;

        /// <summary>
        ///  void set_fly_2d(double ScaleX, double ScaleY);
        /// </summary>
        public static set_fly_2dDelegate set_fly_2d;

        /// <summary>
        ///  void set_fly_x_pos(double ScaleX);
        /// </summary>
        public static set_fly_x_posDelegate set_fly_x_pos;

        /// <summary>
        ///  void set_fly_y_pos(double ScaleY);
        /// </summary>
        public static set_fly_y_posDelegate set_fly_y_pos;

        /// <summary>
        ///  void set_fly_rot_pos(double Resolution);
        /// </summary>
        public static set_fly_rot_posDelegate set_fly_rot_pos;

        /// <summary>
        ///  void set_fly_limits(int Xmin, int Xmax, int Ymin, int Ymax);
        /// </summary>
        public static set_fly_limitsDelegate set_fly_limits;

        /// <summary>
        ///  void set_fly_limits_z(int Zmin, int Zmax);
        /// </summary>
        public static set_fly_limits_zDelegate set_fly_limits_z;

        /// <summary>
        ///  void if_fly_x_overflow(int Mode);
        /// </summary>
        public static if_fly_x_overflowDelegate if_fly_x_overflow;

        /// <summary>
        ///  void if_fly_y_overflow(int Mode);
        /// </summary>
        public static if_fly_y_overflowDelegate if_fly_y_overflow;

        /// <summary>
        ///  void if_fly_z_overflow(int Mode);
        /// </summary>
        public static if_fly_z_overflowDelegate if_fly_z_overflow;

        /// <summary>
        ///  void if_not_fly_x_overflow(int Mode);
        /// </summary>
        public static if_not_fly_x_overflowDelegate if_not_fly_x_overflow;

        /// <summary>
        ///  void if_not_fly_y_overflow(int Mode);
        /// </summary>
        public static if_not_fly_y_overflowDelegate if_not_fly_y_overflow;

        /// <summary>
        ///  void if_not_fly_z_overflow(int Mode);
        /// </summary>
        public static if_not_fly_z_overflowDelegate if_not_fly_z_overflow;

        /// <summary>
        ///  void clear_fly_overflow(uint Mode);
        /// </summary>
        public static clear_fly_overflowDelegate clear_fly_overflow;

        /// <summary>
        ///  void set_mcbsp_x_list(double ScaleX);
        /// </summary>
        public static set_mcbsp_x_listDelegate set_mcbsp_x_list;

        /// <summary>
        ///  void set_mcbsp_y_list(double ScaleY);
        /// </summary>
        public static set_mcbsp_y_listDelegate set_mcbsp_y_list;

        /// <summary>
        ///  void set_mcbsp_rot_list(double Resolution);
        /// </summary>
        public static set_mcbsp_rot_listDelegate set_mcbsp_rot_list;

        /// <summary>
        ///  void set_mcbsp_matrix_list();
        /// </summary>
        public static set_mcbsp_matrix_listDelegate set_mcbsp_matrix_list;

        /// <summary>
        ///  void set_mcbsp_global_x_list(double ScaleX);
        /// </summary>
        public static set_mcbsp_global_x_listDelegate set_mcbsp_global_x_list;

        /// <summary>
        ///  void set_mcbsp_global_y_list(double ScaleY);
        /// </summary>
        public static set_mcbsp_global_y_listDelegate set_mcbsp_global_y_list;

        /// <summary>
        ///  void set_mcbsp_global_rot_list(double Resolution);
        /// </summary>
        public static set_mcbsp_global_rot_listDelegate set_mcbsp_global_rot_list;

        /// <summary>
        ///  void set_mcbsp_global_matrix_list();
        /// </summary>
        public static set_mcbsp_global_matrix_listDelegate set_mcbsp_global_matrix_list;

        /// <summary>
        ///  void set_mcbsp_in_list(uint Mode, double Scale);
        /// </summary>
        public static set_mcbsp_in_listDelegate set_mcbsp_in_list;

        /// <summary>
        ///  void set_multi_mcbsp_in_list(uint Ctrl, uint P, uint Mode);
        /// </summary>
        public static set_multi_mcbsp_in_listDelegate set_multi_mcbsp_in_list;

        /// <summary>
        ///  void wait_for_encoder_mode(int Value, uint EncoderNo, int Mode);
        /// </summary>
        public static wait_for_encoder_modeDelegate wait_for_encoder_mode;

        /// <summary>
        ///  void wait_for_mcbsp(uint Axis, int Value, int Mode);
        /// </summary>
        public static wait_for_mcbspDelegate wait_for_mcbsp;

        /// <summary>
        ///  void set_encoder_speed(uint EncoderNo, double Speed, double Smooth);
        /// </summary>
        public static set_encoder_speedDelegate set_encoder_speed;

        /// <summary>
        ///  void get_mcbsp_list();
        /// </summary>
        public static get_mcbsp_listDelegate get_mcbsp_list;

        /// <summary>
        ///  void store_encoder(uint Pos);
        /// </summary>
        public static store_encoderDelegate store_encoder;

        /// <summary>
        ///  void wait_for_encoder_in_range(int EncXmin, int EncXmax, int EncYmin, int EncYmax);
        /// </summary>
        public static wait_for_encoder_in_rangeDelegate wait_for_encoder_in_range;

        /// <summary>
        ///  void activate_fly_xy(double ScaleX, double ScaleY);
        /// </summary>
        public static activate_fly_xyDelegate activate_fly_xy;

        /// <summary>
        ///  void activate_fly_2d(double ScaleX, double ScaleY);
        /// </summary>
        public static activate_fly_2dDelegate activate_fly_2d;

        /// <summary>
        ///  void activate_fly_xy_encoder(double ScaleX, double ScaleY, int EncX, int EncY);
        /// </summary>
        public static activate_fly_xy_encoderDelegate activate_fly_xy_encoder;

        /// <summary>
        ///  void activate_fly_2d_encoder(double ScaleX, double ScaleY, int EncX, int EncY);
        /// </summary>
        public static activate_fly_2d_encoderDelegate activate_fly_2d_encoder;

        /// <summary>
        ///  void if_not_activated();
        /// </summary>
        public static if_not_activatedDelegate if_not_activated;

        /// <summary>
        ///  void park_position(uint Mode, int X, int Y);
        /// </summary>
        public static park_positionDelegate park_position;

        /// <summary>
        ///  void park_return(uint Mode, int X, int Y);
        /// </summary>
        public static park_returnDelegate park_return;

        /// <summary>
        ///  void wait_for_encoder(int Value, uint EncoderNo);
        /// </summary>
        public static wait_for_encoderDelegate wait_for_encoder;

        /// <summary>
        ///  void n_save_and_restart_timer(uint CardNo);
        /// </summary>
        public static n_save_and_restart_timerDelegate n_save_and_restart_timer;

        /// <summary>
        ///  void n_set_wobbel(uint CardNo, uint Transversal, uint Longitudinal, double Freq);
        /// </summary>
        public static n_set_wobbelDelegate n_set_wobbel;

        /// <summary>
        ///  void n_set_wobbel_mode(uint CardNo, uint Transversal, uint Longitudinal, double Freq, int Mode);
        /// </summary>
        public static n_set_wobbel_modeDelegate n_set_wobbel_mode;

        /// <summary>
        ///  void n_set_wobbel_mode_phase(uint CardNo, uint Transversal, uint Longitudinal, double Freq, int Mode, double Phase);
        /// </summary>
        public static n_set_wobbel_mode_phaseDelegate n_set_wobbel_mode_phase;

        /// <summary>
        ///  void n_set_wobbel_direction(uint CardNo, int dX, int dY);
        /// </summary>
        public static n_set_wobbel_directionDelegate n_set_wobbel_direction;

        /// <summary>
        ///  void n_set_wobbel_control(uint CardNo, uint Ctrl, uint Value, uint MinValue, uint MaxValue);
        /// </summary>
        public static n_set_wobbel_controlDelegate n_set_wobbel_control;

        /// <summary>
        ///  void n_set_wobbel_vector(uint CardNo, double dTrans, double dLong, uint Period, double dPower);
        /// </summary>
        public static n_set_wobbel_vectorDelegate n_set_wobbel_vector;

        /// <summary>
        ///  void n_set_wobbel_offset(uint CardNo, int OffsetTrans, int OffsetLong);
        /// </summary>
        public static n_set_wobbel_offsetDelegate n_set_wobbel_offset;

        /// <summary>
        ///  void n_load_wobbel_power_list(uint CardNo, uint TableNo, int[] Ptr, int Flag);
        /// </summary>
        public static n_load_wobbel_power_listDelegate n_load_wobbel_power_list;

        /// <summary>
        ///  void n_set_wobbel_power_angle(uint CardNo, uint Angle);
        /// </summary>
        public static n_set_wobbel_power_angleDelegate n_set_wobbel_power_angle;

        /// <summary>
        ///  void n_set_trigger(uint CardNo, uint Period, uint Signal1, uint Signal2);
        /// </summary>
        public static n_set_triggerDelegate n_set_trigger;

        /// <summary>
        ///  void n_set_trigger4(uint CardNo, uint Period, uint Signal1, uint Signal2, uint Signal3, uint Signal4);
        /// </summary>
        public static n_set_trigger4Delegate n_set_trigger4;

        /// <summary>
        ///  void n_set_pixel_line_3d(uint CardNo, uint Channel, uint HalfPeriod, double dX, double dY, double dZ);
        /// </summary>
        public static n_set_pixel_line_3dDelegate n_set_pixel_line_3d;

        /// <summary>
        ///  void n_set_pixel_line(uint CardNo, uint Channel, uint HalfPeriod, double dX, double dY);
        /// </summary>
        public static n_set_pixel_lineDelegate n_set_pixel_line;

        /// <summary>
        ///  void n_stretch_pixel_line(uint CardNo, uint Delay, uint Period);
        /// </summary>
        public static n_stretch_pixel_lineDelegate n_stretch_pixel_line;

        /// <summary>
        ///  void n_set_n_pixel(uint CardNo, uint PulseLength, uint AnalogOut, uint Number);
        /// </summary>
        public static n_set_n_pixelDelegate n_set_n_pixel;

        /// <summary>
        ///  void n_set_pixel(uint CardNo, uint PulseLength, uint AnalogOut);
        /// </summary>
        public static n_set_pixelDelegate n_set_pixel;

        /// <summary>
        ///  void n_rs232_write_text_list(uint CardNo, string pData);
        /// </summary>
        public static n_rs232_write_text_listDelegate n_rs232_write_text_list;

        /// <summary>
        ///  void n_set_mcbsp_out(uint CardNo, uint Signal1, uint Signal2);
        /// </summary>
        public static n_set_mcbsp_outDelegate n_set_mcbsp_out;

        /// <summary>
        ///  void n_set_mcbsp_out_ptr_list(uint CardNo, uint Number, uint[] SignalPtr);
        /// </summary>
        public static n_set_mcbsp_out_ptr_listDelegate n_set_mcbsp_out_ptr_list;

        /// <summary>
        ///  void n_camming(uint CardNo, uint FirstPos, uint NPos, uint No, uint Ctrl, double Scale, uint Code);
        /// </summary>
        public static n_cammingDelegate n_camming;

        /// <summary>
        ///  void n_periodic_toggle_list(uint CardNo, uint Port, uint Mask, uint P1, uint P2, uint Count, uint Start);
        /// </summary>
        public static n_periodic_toggle_listDelegate n_periodic_toggle_list;

        /// <summary>
        ///  void n_micro_vector_abs_3d(uint CardNo, int X, int Y, int Z, int LasOn, int LasOf);
        /// </summary>
        public static n_micro_vector_abs_3dDelegate n_micro_vector_abs_3d;

        /// <summary>
        ///  void n_micro_vector_rel_3d(uint CardNo, int dX, int dY, int dZ, int LasOn, int LasOf);
        /// </summary>
        public static n_micro_vector_rel_3dDelegate n_micro_vector_rel_3d;

        /// <summary>
        ///  void n_micro_vector_abs(uint CardNo, int X, int Y, int LasOn, int LasOf);
        /// </summary>
        public static n_micro_vector_absDelegate n_micro_vector_abs;

        /// <summary>
        ///  void n_micro_vector_rel(uint CardNo, int dX, int dY, int LasOn, int LasOf);
        /// </summary>
        public static n_micro_vector_relDelegate n_micro_vector_rel;

        /// <summary>
        ///  void n_set_free_variable_list(uint CardNo, uint VarNo, uint Value);
        /// </summary>
        public static n_set_free_variable_listDelegate n_set_free_variable_list;

        /// <summary>
        ///  void n_jump_abs_drill_2(uint CardNo, int X, int Y, uint DrillTime, int XOff, int YOff);
        /// </summary>
        public static n_jump_abs_drill_2Delegate n_jump_abs_drill_2;

        /// <summary>
        ///  void n_jump_rel_drill_2(uint CardNo, int dX, int dY, uint DrillTime, int XOff, int YOff);
        /// </summary>
        public static n_jump_rel_drill_2Delegate n_jump_rel_drill_2;

        /// <summary>
        ///  void n_jump_abs_drill(uint CardNo, int X, int Y, uint DrillTime);
        /// </summary>
        public static n_jump_abs_drillDelegate n_jump_abs_drill;

        /// <summary>
        ///  void n_jump_rel_drill(uint CardNo, int dX, int dY, uint DrillTime);
        /// </summary>
        public static n_jump_rel_drillDelegate n_jump_rel_drill;

        /// <summary>
        ///  void save_and_restart_timer();
        /// </summary>
        public static save_and_restart_timerDelegate save_and_restart_timer;

        /// <summary>
        ///  void set_wobbel(uint Transversal, uint Longitudinal, double Freq);
        /// </summary>
        public static set_wobbelDelegate set_wobbel;

        /// <summary>
        ///  void set_wobbel_mode(uint Transversal, uint Longitudinal, double Freq, int Mode);
        /// </summary>
        public static set_wobbel_modeDelegate set_wobbel_mode;

        /// <summary>
        ///  void set_wobbel_mode_phase(uint Transversal, uint Longitudinal, double Freq, int Mode, double Phase);
        /// </summary>
        public static set_wobbel_mode_phaseDelegate set_wobbel_mode_phase;

        /// <summary>
        ///  void set_wobbel_direction(int dX, int dY);
        /// </summary>
        public static set_wobbel_directionDelegate set_wobbel_direction;

        /// <summary>
        ///  void set_wobbel_control(uint Ctrl, uint Value, uint MinValue, uint MaxValue);
        /// </summary>
        public static set_wobbel_controlDelegate set_wobbel_control;

        /// <summary>
        ///  void set_wobbel_vector(double dTrans, double dLong, uint Period, double dPower);
        /// </summary>
        public static set_wobbel_vectorDelegate set_wobbel_vector;

        /// <summary>
        ///  void set_wobbel_offset(int OffsetTrans, int OffsetLong);
        /// </summary>
        public static set_wobbel_offsetDelegate set_wobbel_offset;

        /// <summary>
        ///  void load_wobbel_power_list(uint TableNo, int[] Ptr, int Flag);
        /// </summary>
        public static load_wobbel_power_listDelegate load_wobbel_power_list;

        /// <summary>
        ///  void set_wobbel_power_angle(uint Angle);
        /// </summary>
        public static set_wobbel_power_angleDelegate set_wobbel_power_angle;

        /// <summary>
        ///  void set_trigger(uint Period, uint Signal1, uint Signal2);
        /// </summary>
        public static set_triggerDelegate set_trigger;

        /// <summary>
        ///  void set_trigger4(uint Period, uint Signal1, uint Signal2, uint Signal3, uint Signal4);
        /// </summary>
        public static set_trigger4Delegate set_trigger4;

        /// <summary>
        ///  void set_pixel_line_3d(uint Channel, uint HalfPeriod, double dX, double dY, double dZ);
        /// </summary>
        public static set_pixel_line_3dDelegate set_pixel_line_3d;

        /// <summary>
        ///  void set_pixel_line(uint Channel, uint HalfPeriod, double dX, double dY);
        /// </summary>
        public static set_pixel_lineDelegate set_pixel_line;

        /// <summary>
        ///  void stretch_pixel_line(uint Delay, uint Period);
        /// </summary>
        public static stretch_pixel_lineDelegate stretch_pixel_line;

        /// <summary>
        ///  void set_n_pixel(uint PulseLength, uint AnalogOut, uint Number);
        /// </summary>
        public static set_n_pixelDelegate set_n_pixel;

        /// <summary>
        ///  void set_pixel(uint PulseLength, uint AnalogOut);
        /// </summary>
        public static set_pixelDelegate set_pixel;

        /// <summary>
        ///  void rs232_write_text_list(string pData);
        /// </summary>
        public static rs232_write_text_listDelegate rs232_write_text_list;

        /// <summary>
        ///  void set_mcbsp_out(uint Signal1, uint Signal2);
        /// </summary>
        public static set_mcbsp_outDelegate set_mcbsp_out;

        /// <summary>
        ///  void set_mcbsp_out_ptr_list(uint Number, uint[] SignalPtr);
        /// </summary>
        public static set_mcbsp_out_ptr_listDelegate set_mcbsp_out_ptr_list;

        /// <summary>
        ///  void camming(uint FirstPos, uint NPos, uint No, uint Ctrl, double Scale, uint Code);
        /// </summary>
        public static cammingDelegate camming;

        /// <summary>
        ///  void periodic_toggle_list(uint Port, uint Mask, uint P1, uint P2, uint Count, uint Start);
        /// </summary>
        public static periodic_toggle_listDelegate periodic_toggle_list;

        /// <summary>
        ///  void micro_vector_abs_3d(int X, int Y, int Z, int LasOn, int LasOf);
        /// </summary>
        public static micro_vector_abs_3dDelegate micro_vector_abs_3d;

        /// <summary>
        ///  void micro_vector_rel_3d(int dX, int dY, int dZ, int LasOn, int LasOf);
        /// </summary>
        public static micro_vector_rel_3dDelegate micro_vector_rel_3d;

        /// <summary>
        ///  void micro_vector_abs(int X, int Y, int LasOn, int LasOf);
        /// </summary>
        public static micro_vector_absDelegate micro_vector_abs;

        /// <summary>
        ///  void micro_vector_rel(int dX, int dY, int LasOn, int LasOf);
        /// </summary>
        public static micro_vector_relDelegate micro_vector_rel;

        /// <summary>
        ///  void set_free_variable_list(uint VarNo, uint Value);
        /// </summary>
        public static set_free_variable_listDelegate set_free_variable_list;

        /// <summary>
        ///  void jump_abs_drill_2(int X, int Y, uint DrillTime, int XOff, int YOff);
        /// </summary>
        public static jump_abs_drill_2Delegate jump_abs_drill_2;

        /// <summary>
        ///  void jump_rel_drill_2(int dX, int dY, uint DrillTime, int XOff, int YOff);
        /// </summary>
        public static jump_rel_drill_2Delegate jump_rel_drill_2;

        /// <summary>
        ///  void jump_abs_drill(int X, int Y, uint DrillTime);
        /// </summary>
        public static jump_abs_drillDelegate jump_abs_drill;

        /// <summary>
        ///  void jump_rel_drill(int dX, int dY, uint DrillTime);
        /// </summary>
        public static jump_rel_drillDelegate jump_rel_drill;

        /// <summary>
        ///  void n_timed_mark_abs_3d(uint CardNo, int X, int Y, int Z, double T);
        /// </summary>
        public static n_timed_mark_abs_3dDelegate n_timed_mark_abs_3d;

        /// <summary>
        ///  void n_timed_mark_rel_3d(uint CardNo, int dX, int dY, int dZ, double T);
        /// </summary>
        public static n_timed_mark_rel_3dDelegate n_timed_mark_rel_3d;

        /// <summary>
        ///  void n_timed_mark_abs(uint CardNo, int X, int Y, double T);
        /// </summary>
        public static n_timed_mark_absDelegate n_timed_mark_abs;

        /// <summary>
        ///  void n_timed_mark_rel(uint CardNo, int dX, int dY, double T);
        /// </summary>
        public static n_timed_mark_relDelegate n_timed_mark_rel;

        /// <summary>
        ///  void timed_mark_abs_3d(int X, int Y, int Z, double T);
        /// </summary>
        public static timed_mark_abs_3dDelegate timed_mark_abs_3d;

        /// <summary>
        ///  void timed_mark_rel_3d(int dX, int dY, int dZ, double T);
        /// </summary>
        public static timed_mark_rel_3dDelegate timed_mark_rel_3d;

        /// <summary>
        ///  void timed_mark_abs(int X, int Y, double T);
        /// </summary>
        public static timed_mark_absDelegate timed_mark_abs;

        /// <summary>
        ///  void timed_mark_rel(int dX, int dY, double T);
        /// </summary>
        public static timed_mark_relDelegate timed_mark_rel;

        /// <summary>
        ///  void n_mark_abs_3d(uint CardNo, int X, int Y, int Z);
        /// </summary>
        public static n_mark_abs_3dDelegate n_mark_abs_3d;

        /// <summary>
        ///  void n_mark_rel_3d(uint CardNo, int dX, int dY, int dZ);
        /// </summary>
        public static n_mark_rel_3dDelegate n_mark_rel_3d;

        /// <summary>
        ///  void n_mark_abs(uint CardNo, int X, int Y);
        /// </summary>
        public static n_mark_absDelegate n_mark_abs;

        /// <summary>
        ///  void n_mark_rel(uint CardNo, int dX, int dY);
        /// </summary>
        public static n_mark_relDelegate n_mark_rel;

        /// <summary>
        ///  void mark_abs_3d(int X, int Y, int Z);
        /// </summary>
        public static mark_abs_3dDelegate mark_abs_3d;

        /// <summary>
        ///  void mark_rel_3d(int dX, int dY, int dZ);
        /// </summary>
        public static mark_rel_3dDelegate mark_rel_3d;

        /// <summary>
        ///  void mark_abs(int X, int Y);
        /// </summary>
        public static mark_absDelegate mark_abs;

        /// <summary>
        ///  void mark_rel(int dX, int dY);
        /// </summary>
        public static mark_relDelegate mark_rel;

        /// <summary>
        ///  void n_timed_jump_abs_3d(uint CardNo, int X, int Y, int Z, double T);
        /// </summary>
        public static n_timed_jump_abs_3dDelegate n_timed_jump_abs_3d;

        /// <summary>
        ///  void n_timed_jump_rel_3d(uint CardNo, int dX, int dY, int dZ, double T);
        /// </summary>
        public static n_timed_jump_rel_3dDelegate n_timed_jump_rel_3d;

        /// <summary>
        ///  void n_timed_jump_abs(uint CardNo, int X, int Y, double T);
        /// </summary>
        public static n_timed_jump_absDelegate n_timed_jump_abs;

        /// <summary>
        ///  void n_timed_jump_rel(uint CardNo, int dX, int dY, double T);
        /// </summary>
        public static n_timed_jump_relDelegate n_timed_jump_rel;

        /// <summary>
        ///  void timed_jump_abs_3d(int X, int Y, int Z, double T);
        /// </summary>
        public static timed_jump_abs_3dDelegate timed_jump_abs_3d;

        /// <summary>
        ///  void timed_jump_rel_3d(int dX, int dY, int dZ, double T);
        /// </summary>
        public static timed_jump_rel_3dDelegate timed_jump_rel_3d;

        /// <summary>
        ///  void timed_jump_abs(int X, int Y, double T);
        /// </summary>
        public static timed_jump_absDelegate timed_jump_abs;

        /// <summary>
        ///  void timed_jump_rel(int dX, int dY, double T);
        /// </summary>
        public static timed_jump_relDelegate timed_jump_rel;

        /// <summary>
        ///  void n_jump_abs_3d(uint CardNo, int X, int Y, int Z);
        /// </summary>
        public static n_jump_abs_3dDelegate n_jump_abs_3d;

        /// <summary>
        ///  void n_jump_rel_3d(uint CardNo, int dX, int dY, int dZ);
        /// </summary>
        public static n_jump_rel_3dDelegate n_jump_rel_3d;

        /// <summary>
        ///  void n_jump_abs(uint CardNo, int X, int Y);
        /// </summary>
        public static n_jump_absDelegate n_jump_abs;

        /// <summary>
        ///  void n_jump_rel(uint CardNo, int dX, int dY);
        /// </summary>
        public static n_jump_relDelegate n_jump_rel;

        /// <summary>
        ///  void jump_abs_3d(int X, int Y, int Z);
        /// </summary>
        public static jump_abs_3dDelegate jump_abs_3d;

        /// <summary>
        ///  void jump_rel_3d(int dX, int dY, int dZ);
        /// </summary>
        public static jump_rel_3dDelegate jump_rel_3d;

        /// <summary>
        ///  void jump_abs(int X, int Y);
        /// </summary>
        public static jump_absDelegate jump_abs;

        /// <summary>
        ///  void jump_rel(int dX, int dY);
        /// </summary>
        public static jump_relDelegate jump_rel;

        /// <summary>
        ///  void n_para_mark_abs_3d(uint CardNo, int X, int Y, int Z, uint P);
        /// </summary>
        public static n_para_mark_abs_3dDelegate n_para_mark_abs_3d;

        /// <summary>
        ///  void n_para_mark_rel_3d(uint CardNo, int dX, int dY, int dZ, uint P);
        /// </summary>
        public static n_para_mark_rel_3dDelegate n_para_mark_rel_3d;

        /// <summary>
        ///  void n_para_mark_abs(uint CardNo, int X, int Y, uint P);
        /// </summary>
        public static n_para_mark_absDelegate n_para_mark_abs;

        /// <summary>
        ///  void n_para_mark_rel(uint CardNo, int dX, int dY, uint P);
        /// </summary>
        public static n_para_mark_relDelegate n_para_mark_rel;

        /// <summary>
        ///  void para_mark_abs_3d(int X, int Y, int Z, uint P);
        /// </summary>
        public static para_mark_abs_3dDelegate para_mark_abs_3d;

        /// <summary>
        ///  void para_mark_rel_3d(int dX, int dY, int dZ, uint P);
        /// </summary>
        public static para_mark_rel_3dDelegate para_mark_rel_3d;

        /// <summary>
        ///  void para_mark_abs(int X, int Y, uint P);
        /// </summary>
        public static para_mark_absDelegate para_mark_abs;

        /// <summary>
        ///  void para_mark_rel(int dX, int dY, uint P);
        /// </summary>
        public static para_mark_relDelegate para_mark_rel;

        /// <summary>
        ///  void n_para_jump_abs_3d(uint CardNo, int X, int Y, int Z, uint P);
        /// </summary>
        public static n_para_jump_abs_3dDelegate n_para_jump_abs_3d;

        /// <summary>
        ///  void n_para_jump_rel_3d(uint CardNo, int dX, int dY, int dZ, uint P);
        /// </summary>
        public static n_para_jump_rel_3dDelegate n_para_jump_rel_3d;

        /// <summary>
        ///  void n_para_jump_abs(uint CardNo, int X, int Y, uint P);
        /// </summary>
        public static n_para_jump_absDelegate n_para_jump_abs;

        /// <summary>
        ///  void n_para_jump_rel(uint CardNo, int dX, int dY, uint P);
        /// </summary>
        public static n_para_jump_relDelegate n_para_jump_rel;

        /// <summary>
        ///  void para_jump_abs_3d(int X, int Y, int Z, uint P);
        /// </summary>
        public static para_jump_abs_3dDelegate para_jump_abs_3d;

        /// <summary>
        ///  void para_jump_rel_3d(int dX, int dY, int dZ, uint P);
        /// </summary>
        public static para_jump_rel_3dDelegate para_jump_rel_3d;

        /// <summary>
        ///  void para_jump_abs(int X, int Y, uint P);
        /// </summary>
        public static para_jump_absDelegate para_jump_abs;

        /// <summary>
        ///  void para_jump_rel(int dX, int dY, uint P);
        /// </summary>
        public static para_jump_relDelegate para_jump_rel;

        /// <summary>
        ///  void n_timed_para_mark_abs_3d(uint CardNo, int X, int Y, int Z, uint P, double T);
        /// </summary>
        public static n_timed_para_mark_abs_3dDelegate n_timed_para_mark_abs_3d;

        /// <summary>
        ///  void n_timed_para_mark_rel_3d(uint CardNo, int dX, int dY, int dZ, uint P, double T);
        /// </summary>
        public static n_timed_para_mark_rel_3dDelegate n_timed_para_mark_rel_3d;

        /// <summary>
        ///  void n_timed_para_jump_abs_3d(uint CardNo, int X, int Y, int Z, uint P, double T);
        /// </summary>
        public static n_timed_para_jump_abs_3dDelegate n_timed_para_jump_abs_3d;

        /// <summary>
        ///  void n_timed_para_jump_rel_3d(uint CardNo, int dX, int dY, int dZ, uint P, double T);
        /// </summary>
        public static n_timed_para_jump_rel_3dDelegate n_timed_para_jump_rel_3d;

        /// <summary>
        ///  void n_timed_para_mark_abs(uint CardNo, int X, int Y, uint P, double T);
        /// </summary>
        public static n_timed_para_mark_absDelegate n_timed_para_mark_abs;

        /// <summary>
        ///  void n_timed_para_mark_rel(uint CardNo, int dX, int dY, uint P, double T);
        /// </summary>
        public static n_timed_para_mark_relDelegate n_timed_para_mark_rel;

        /// <summary>
        ///  void n_timed_para_jump_abs(uint CardNo, int X, int Y, uint P, double T);
        /// </summary>
        public static n_timed_para_jump_absDelegate n_timed_para_jump_abs;

        /// <summary>
        ///  void n_timed_para_jump_rel(uint CardNo, int dX, int dY, uint P, double T);
        /// </summary>
        public static n_timed_para_jump_relDelegate n_timed_para_jump_rel;

        /// <summary>
        ///  void timed_para_mark_abs_3d(int X, int Y, int Z, uint P, double T);
        /// </summary>
        public static timed_para_mark_abs_3dDelegate timed_para_mark_abs_3d;

        /// <summary>
        ///  void timed_para_mark_rel_3d(int dX, int dY, int dZ, uint P, double T);
        /// </summary>
        public static timed_para_mark_rel_3dDelegate timed_para_mark_rel_3d;

        /// <summary>
        ///  void timed_para_jump_abs_3d(int X, int Y, int Z, uint P, double T);
        /// </summary>
        public static timed_para_jump_abs_3dDelegate timed_para_jump_abs_3d;

        /// <summary>
        ///  void timed_para_jump_rel_3d(int dX, int dY, int dZ, uint P, double T);
        /// </summary>
        public static timed_para_jump_rel_3dDelegate timed_para_jump_rel_3d;

        /// <summary>
        ///  void timed_para_mark_abs(int X, int Y, uint P, double T);
        /// </summary>
        public static timed_para_mark_absDelegate timed_para_mark_abs;

        /// <summary>
        ///  void timed_para_mark_rel(int dX, int dY, uint P, double T);
        /// </summary>
        public static timed_para_mark_relDelegate timed_para_mark_rel;

        /// <summary>
        ///  void timed_para_jump_abs(int X, int Y, uint P, double T);
        /// </summary>
        public static timed_para_jump_absDelegate timed_para_jump_abs;

        /// <summary>
        ///  void timed_para_jump_rel(int dX, int dY, uint P, double T);
        /// </summary>
        public static timed_para_jump_relDelegate timed_para_jump_rel;

        /// <summary>
        ///  void n_set_defocus_list(uint CardNo, int Shift);
        /// </summary>
        public static n_set_defocus_listDelegate n_set_defocus_list;

        /// <summary>
        ///  void n_set_defocus_offset_list(uint CardNo, int Shift);
        /// </summary>
        public static n_set_defocus_offset_listDelegate n_set_defocus_offset_list;

        /// <summary>
        ///  void n_set_zoom_list(uint CardNo, uint Zoom);
        /// </summary>
        public static n_set_zoom_listDelegate n_set_zoom_list;

        /// <summary>
        ///  void set_defocus_list(int Shift);
        /// </summary>
        public static set_defocus_listDelegate set_defocus_list;

        /// <summary>
        ///  void set_defocus_offset_list(int Shift);
        /// </summary>
        public static set_defocus_offset_listDelegate set_defocus_offset_list;

        /// <summary>
        ///  void set_zoom_list(uint Zoom);
        /// </summary>
        public static set_zoom_listDelegate set_zoom_list;

        /// <summary>
        ///  void n_timed_arc_abs(uint CardNo, int X, int Y, double Angle, double T);
        /// </summary>
        public static n_timed_arc_absDelegate n_timed_arc_abs;

        /// <summary>
        ///  void n_timed_arc_rel(uint CardNo, int dX, int dY, double Angle, double T);
        /// </summary>
        public static n_timed_arc_relDelegate n_timed_arc_rel;

        /// <summary>
        ///  void timed_arc_abs(int X, int Y, double Angle, double T);
        /// </summary>
        public static timed_arc_absDelegate timed_arc_abs;

        /// <summary>
        ///  void timed_arc_rel(int dX, int dY, double Angle, double T);
        /// </summary>
        public static timed_arc_relDelegate timed_arc_rel;

        /// <summary>
        ///  void n_arc_abs_3d(uint CardNo, int X, int Y, int Z, double Angle);
        /// </summary>
        public static n_arc_abs_3dDelegate n_arc_abs_3d;

        /// <summary>
        ///  void n_arc_rel_3d(uint CardNo, int dX, int dY, int dZ, double Angle);
        /// </summary>
        public static n_arc_rel_3dDelegate n_arc_rel_3d;

        /// <summary>
        ///  void n_arc_abs(uint CardNo, int X, int Y, double Angle);
        /// </summary>
        public static n_arc_absDelegate n_arc_abs;

        /// <summary>
        ///  void n_arc_rel(uint CardNo, int dX, int dY, double Angle);
        /// </summary>
        public static n_arc_relDelegate n_arc_rel;

        /// <summary>
        ///  void n_set_ellipse(uint CardNo, uint A, uint B, double Phi0, double Phi);
        /// </summary>
        public static n_set_ellipseDelegate n_set_ellipse;

        /// <summary>
        ///  void n_mark_ellipse_abs(uint CardNo, int X, int Y, double Alpha);
        /// </summary>
        public static n_mark_ellipse_absDelegate n_mark_ellipse_abs;

        /// <summary>
        ///  void n_mark_ellipse_rel(uint CardNo, int dX, int dY, double Alpha);
        /// </summary>
        public static n_mark_ellipse_relDelegate n_mark_ellipse_rel;

        /// <summary>
        ///  void arc_abs_3d(int X, int Y, int Z, double Angle);
        /// </summary>
        public static arc_abs_3dDelegate arc_abs_3d;

        /// <summary>
        ///  void arc_rel_3d(int dX, int dY, int dZ, double Angle);
        /// </summary>
        public static arc_rel_3dDelegate arc_rel_3d;

        /// <summary>
        ///  void arc_abs(int X, int Y, double Angle);
        /// </summary>
        public static arc_absDelegate arc_abs;

        /// <summary>
        ///  void arc_rel(int dX, int dY, double Angle);
        /// </summary>
        public static arc_relDelegate arc_rel;

        /// <summary>
        ///  void set_ellipse(uint A, uint B, double Phi0, double Phi);
        /// </summary>
        public static set_ellipseDelegate set_ellipse;

        /// <summary>
        ///  void mark_ellipse_abs(int X, int Y, double Alpha);
        /// </summary>
        public static mark_ellipse_absDelegate mark_ellipse_abs;

        /// <summary>
        ///  void mark_ellipse_rel(int dX, int dY, double Alpha);
        /// </summary>
        public static mark_ellipse_relDelegate mark_ellipse_rel;

        /// <summary>
        ///  void n_set_offset_xyz_list(uint CardNo, uint HeadNo, int XOffset, int YOffset, int ZOffset, uint at_once);
        /// </summary>
        public static n_set_offset_xyz_listDelegate n_set_offset_xyz_list;

        /// <summary>
        ///  void n_set_offset_list(uint CardNo, uint HeadNo, int XOffset, int YOffset, uint at_once);
        /// </summary>
        public static n_set_offset_listDelegate n_set_offset_list;

        /// <summary>
        ///  void n_set_matrix_list(uint CardNo, uint HeadNo, uint Ind1, uint Ind2, double Mij, uint at_once);
        /// </summary>
        public static n_set_matrix_listDelegate n_set_matrix_list;

        /// <summary>
        ///  void n_set_angle_list(uint CardNo, uint HeadNo, double Angle, uint at_once);
        /// </summary>
        public static n_set_angle_listDelegate n_set_angle_list;

        /// <summary>
        ///  void n_set_scale_list(uint CardNo, uint HeadNo, double Scale, uint at_once);
        /// </summary>
        public static n_set_scale_listDelegate n_set_scale_list;

        /// <summary>
        ///  void n_apply_mcbsp_list(uint CardNo, uint HeadNo, uint at_once);
        /// </summary>
        public static n_apply_mcbsp_listDelegate n_apply_mcbsp_list;

        /// <summary>
        ///  void set_offset_xyz_list(uint HeadNo, int XOffset, int YOffset, int ZOffset, uint at_once);
        /// </summary>
        public static set_offset_xyz_listDelegate set_offset_xyz_list;

        /// <summary>
        ///  void set_offset_list(uint HeadNo, int XOffset, int YOffset, uint at_once);
        /// </summary>
        public static set_offset_listDelegate set_offset_list;

        /// <summary>
        ///  void set_matrix_list(uint HeadNo, uint Ind1, uint Ind2, double Mij, uint at_once);
        /// </summary>
        public static set_matrix_listDelegate set_matrix_list;

        /// <summary>
        ///  void set_angle_list(uint HeadNo, double Angle, uint at_once);
        /// </summary>
        public static set_angle_listDelegate set_angle_list;

        /// <summary>
        ///  void set_scale_list(uint HeadNo, double Scale, uint at_once);
        /// </summary>
        public static set_scale_listDelegate set_scale_list;

        /// <summary>
        ///  void apply_mcbsp_list(uint HeadNo, uint at_once);
        /// </summary>
        public static apply_mcbsp_listDelegate apply_mcbsp_list;

        /// <summary>
        ///  void n_set_mark_speed(uint CardNo, double Speed);
        /// </summary>
        public static n_set_mark_speedDelegate n_set_mark_speed;

        /// <summary>
        ///  void n_set_jump_speed(uint CardNo, double Speed);
        /// </summary>
        public static n_set_jump_speedDelegate n_set_jump_speed;

        /// <summary>
        ///  void n_set_sky_writing_para_list(uint CardNo, double Timelag, int LaserOnShift, uint Nprev, uint Npost);
        /// </summary>
        public static n_set_sky_writing_para_listDelegate n_set_sky_writing_para_list;

        /// <summary>
        ///  void n_set_sky_writing_list(uint CardNo, double Timelag, int LaserOnShift);
        /// </summary>
        public static n_set_sky_writing_listDelegate n_set_sky_writing_list;

        /// <summary>
        ///  void n_set_sky_writing_limit_list(uint CardNo, double CosAngle);
        /// </summary>
        public static n_set_sky_writing_limit_listDelegate n_set_sky_writing_limit_list;

        /// <summary>
        ///  void n_set_sky_writing_mode_list(uint CardNo, uint Mode);
        /// </summary>
        public static n_set_sky_writing_mode_listDelegate n_set_sky_writing_mode_list;

        /// <summary>
        ///  void n_set_scanner_delays(uint CardNo, uint Jump, uint Mark, uint Polygon);
        /// </summary>
        public static n_set_scanner_delaysDelegate n_set_scanner_delays;

        /// <summary>
        ///  void n_set_jump_mode_list(uint CardNo, int Flag);
        /// </summary>
        public static n_set_jump_mode_listDelegate n_set_jump_mode_list;

        /// <summary>
        ///  void n_enduring_wobbel(uint CardNo);
        /// </summary>
        public static n_enduring_wobbelDelegate n_enduring_wobbel;

        /// <summary>
        ///  void n_set_delay_mode_list(uint CardNo, uint VarPoly, uint DirectMove3D, uint EdgeLevel, uint MinJumpDelay, uint JumpLengthLimit);
        /// </summary>
        public static n_set_delay_mode_listDelegate n_set_delay_mode_list;

        /// <summary>
        ///  void set_mark_speed(double Speed);
        /// </summary>
        public static set_mark_speedDelegate set_mark_speed;

        /// <summary>
        ///  void set_jump_speed(double Speed);
        /// </summary>
        public static set_jump_speedDelegate set_jump_speed;

        /// <summary>
        ///  void set_sky_writing_para_list(double Timelag, int LaserOnShift, uint Nprev, uint Npost);
        /// </summary>
        public static set_sky_writing_para_listDelegate set_sky_writing_para_list;

        /// <summary>
        ///  void set_sky_writing_list(double Timelag, int LaserOnShift);
        /// </summary>
        public static set_sky_writing_listDelegate set_sky_writing_list;

        /// <summary>
        ///  void set_sky_writing_limit_list(double CosAngle);
        /// </summary>
        public static set_sky_writing_limit_listDelegate set_sky_writing_limit_list;

        /// <summary>
        ///  void set_sky_writing_mode_list(uint Mode);
        /// </summary>
        public static set_sky_writing_mode_listDelegate set_sky_writing_mode_list;

        /// <summary>
        ///  void set_scanner_delays(uint Jump, uint Mark, uint Polygon);
        /// </summary>
        public static set_scanner_delaysDelegate set_scanner_delays;

        /// <summary>
        ///  void set_jump_mode_list(int Flag);
        /// </summary>
        public static set_jump_mode_listDelegate set_jump_mode_list;

        /// <summary>
        ///  void enduring_wobbel();
        /// </summary>
        public static enduring_wobbelDelegate enduring_wobbel;

        /// <summary>
        ///  void set_delay_mode_list(uint VarPoly, uint DirectMove3D, uint EdgeLevel, uint MinJumpDelay, uint JumpLengthLimit);
        /// </summary>
        public static set_delay_mode_listDelegate set_delay_mode_list;

        /// <summary>
        ///  void n_stepper_enable_list(uint CardNo, int Enable1, int Enable2);
        /// </summary>
        public static n_stepper_enable_listDelegate n_stepper_enable_list;

        /// <summary>
        ///  void n_stepper_control_list(uint CardNo, int Period1, int Period2);
        /// </summary>
        public static n_stepper_control_listDelegate n_stepper_control_list;

        /// <summary>
        ///  void n_stepper_abs_no_list(uint CardNo, uint No, int Pos);
        /// </summary>
        public static n_stepper_abs_no_listDelegate n_stepper_abs_no_list;

        /// <summary>
        ///  void n_stepper_rel_no_list(uint CardNo, uint No, int dPos);
        /// </summary>
        public static n_stepper_rel_no_listDelegate n_stepper_rel_no_list;

        /// <summary>
        ///  void n_stepper_abs_list(uint CardNo, int Pos1, int Pos2);
        /// </summary>
        public static n_stepper_abs_listDelegate n_stepper_abs_list;

        /// <summary>
        ///  void n_stepper_rel_list(uint CardNo, int dPos1, int dPos2);
        /// </summary>
        public static n_stepper_rel_listDelegate n_stepper_rel_list;

        /// <summary>
        ///  void n_stepper_wait(uint CardNo, uint No);
        /// </summary>
        public static n_stepper_waitDelegate n_stepper_wait;

        /// <summary>
        ///  void stepper_enable_list(int Enable1, int Enable2);
        /// </summary>
        public static stepper_enable_listDelegate stepper_enable_list;

        /// <summary>
        ///  void stepper_control_list(int Period1, int Period2);
        /// </summary>
        public static stepper_control_listDelegate stepper_control_list;

        /// <summary>
        ///  void stepper_abs_no_list(uint No, int Pos);
        /// </summary>
        public static stepper_abs_no_listDelegate stepper_abs_no_list;

        /// <summary>
        ///  void stepper_rel_no_list(uint No, int dPos);
        /// </summary>
        public static stepper_rel_no_listDelegate stepper_rel_no_list;

        /// <summary>
        ///  void stepper_abs_list(int Pos1, int Pos2);
        /// </summary>
        public static stepper_abs_listDelegate stepper_abs_list;

        /// <summary>
        ///  void stepper_rel_list(int dPos1, int dPos2);
        /// </summary>
        public static stepper_rel_listDelegate stepper_rel_list;

        /// <summary>
        ///  void stepper_wait(uint No);
        /// </summary>
        public static stepper_waitDelegate stepper_wait;

        #endregion

        // Notice that the static constructor is used to initialize any static data,
        //    or to perform a particular action that needs to be performed once only.
        //    It is called automatically before the first instance is created or any
        //    static members are referenced.
        static RTC5Wrap()
        {
            // Import functions and set them up as delegates.
            //
            #region DLLFunctionImport
            init_rtc5_dll = (init_rtc5_dllDelegate)FunctionImporter.Import<init_rtc5_dllDelegate>("init_rtc5_dll");
            free_rtc5_dll = (free_rtc5_dllDelegate)FunctionImporter.Import<free_rtc5_dllDelegate>("free_rtc5_dll");
            set_rtc4_mode = (set_rtc4_modeDelegate)FunctionImporter.Import<set_rtc4_modeDelegate>("set_rtc4_mode");
            set_rtc5_mode = (set_rtc5_modeDelegate)FunctionImporter.Import<set_rtc5_modeDelegate>("set_rtc5_mode");
            get_rtc_mode = (get_rtc_modeDelegate)FunctionImporter.Import<get_rtc_modeDelegate>("get_rtc_mode");
            n_get_error = (n_get_errorDelegate)FunctionImporter.Import<n_get_errorDelegate>("n_get_error");
            n_get_last_error = (n_get_last_errorDelegate)FunctionImporter.Import<n_get_last_errorDelegate>("n_get_last_error");
            n_reset_error = (n_reset_errorDelegate)FunctionImporter.Import<n_reset_errorDelegate>("n_reset_error");
            n_set_verify = (n_set_verifyDelegate)FunctionImporter.Import<n_set_verifyDelegate>("n_set_verify");
            get_error = (get_errorDelegate)FunctionImporter.Import<get_errorDelegate>("get_error");
            get_last_error = (get_last_errorDelegate)FunctionImporter.Import<get_last_errorDelegate>("get_last_error");
            reset_error = (reset_errorDelegate)FunctionImporter.Import<reset_errorDelegate>("reset_error");
            set_verify = (set_verifyDelegate)FunctionImporter.Import<set_verifyDelegate>("set_verify");
            verify_checksum = (verify_checksumDelegate)FunctionImporter.Import<verify_checksumDelegate>("verify_checksum");
            read_abc_from_file = (read_abc_from_fileDelegate)FunctionImporter.Import<read_abc_from_fileDelegate>("read_abc_from_file");
            write_abc_to_file = (write_abc_to_fileDelegate)FunctionImporter.Import<write_abc_to_fileDelegate>("write_abc_to_file");
            rtc5_count_cards = (rtc5_count_cardsDelegate)FunctionImporter.Import<rtc5_count_cardsDelegate>("rtc5_count_cards");
            acquire_rtc = (acquire_rtcDelegate)FunctionImporter.Import<acquire_rtcDelegate>("acquire_rtc");
            release_rtc = (release_rtcDelegate)FunctionImporter.Import<release_rtcDelegate>("release_rtc");
            select_rtc = (select_rtcDelegate)FunctionImporter.Import<select_rtcDelegate>("select_rtc");
            get_dll_version = (get_dll_versionDelegate)FunctionImporter.Import<get_dll_versionDelegate>("get_dll_version");
            n_get_serial_number = (n_get_serial_numberDelegate)FunctionImporter.Import<n_get_serial_numberDelegate>("n_get_serial_number");
            n_get_hex_version = (n_get_hex_versionDelegate)FunctionImporter.Import<n_get_hex_versionDelegate>("n_get_hex_version");
            n_get_rtc_version = (n_get_rtc_versionDelegate)FunctionImporter.Import<n_get_rtc_versionDelegate>("n_get_rtc_version");
            get_serial_number = (get_serial_numberDelegate)FunctionImporter.Import<get_serial_numberDelegate>("get_serial_number");
            get_hex_version = (get_hex_versionDelegate)FunctionImporter.Import<get_hex_versionDelegate>("get_hex_version");
            get_rtc_version = (get_rtc_versionDelegate)FunctionImporter.Import<get_rtc_versionDelegate>("get_rtc_version");
            n_load_program_file = (n_load_program_fileDelegate)FunctionImporter.Import<n_load_program_fileDelegate>("n_load_program_file");
            n_sync_slaves = (n_sync_slavesDelegate)FunctionImporter.Import<n_sync_slavesDelegate>("n_sync_slaves");
            n_get_sync_status = (n_get_sync_statusDelegate)FunctionImporter.Import<n_get_sync_statusDelegate>("n_get_sync_status");
            n_load_correction_file = (n_load_correction_fileDelegate)FunctionImporter.Import<n_load_correction_fileDelegate>("n_load_correction_file");
            n_load_zoom_correction_file = (n_load_zoom_correction_fileDelegate)FunctionImporter.Import<n_load_zoom_correction_fileDelegate>("n_load_zoom_correction_file");
            n_load_z_table = (n_load_z_tableDelegate)FunctionImporter.Import<n_load_z_tableDelegate>("n_load_z_table");
            n_select_cor_table = (n_select_cor_tableDelegate)FunctionImporter.Import<n_select_cor_tableDelegate>("n_select_cor_table");
            n_set_dsp_mode = (n_set_dsp_modeDelegate)FunctionImporter.Import<n_set_dsp_modeDelegate>("n_set_dsp_mode");
            n_load_stretch_table = (n_load_stretch_tableDelegate)FunctionImporter.Import<n_load_stretch_tableDelegate>("n_load_stretch_table");
            n_number_of_correction_tables = (n_number_of_correction_tablesDelegate)FunctionImporter.Import<n_number_of_correction_tablesDelegate>("n_number_of_correction_tables");
            n_get_head_para = (n_get_head_paraDelegate)FunctionImporter.Import<n_get_head_paraDelegate>("n_get_head_para");
            n_get_table_para = (n_get_table_paraDelegate)FunctionImporter.Import<n_get_table_paraDelegate>("n_get_table_para");
            load_program_file = (load_program_fileDelegate)FunctionImporter.Import<load_program_fileDelegate>("load_program_file");
            sync_slaves = (sync_slavesDelegate)FunctionImporter.Import<sync_slavesDelegate>("sync_slaves");
            get_sync_status = (get_sync_statusDelegate)FunctionImporter.Import<get_sync_statusDelegate>("get_sync_status");
            load_correction_file = (load_correction_fileDelegate)FunctionImporter.Import<load_correction_fileDelegate>("load_correction_file");
            load_zoom_correction_file = (load_zoom_correction_fileDelegate)FunctionImporter.Import<load_zoom_correction_fileDelegate>("load_zoom_correction_file");
            load_z_table = (load_z_tableDelegate)FunctionImporter.Import<load_z_tableDelegate>("load_z_table");
            select_cor_table = (select_cor_tableDelegate)FunctionImporter.Import<select_cor_tableDelegate>("select_cor_table");
            set_dsp_mode = (set_dsp_modeDelegate)FunctionImporter.Import<set_dsp_modeDelegate>("set_dsp_mode");
            load_stretch_table = (load_stretch_tableDelegate)FunctionImporter.Import<load_stretch_tableDelegate>("load_stretch_table");
            number_of_correction_tables = (number_of_correction_tablesDelegate)FunctionImporter.Import<number_of_correction_tablesDelegate>("number_of_correction_tables");
            get_head_para = (get_head_paraDelegate)FunctionImporter.Import<get_head_paraDelegate>("get_head_para");
            get_table_para = (get_table_paraDelegate)FunctionImporter.Import<get_table_paraDelegate>("get_table_para");
            n_config_list = (n_config_listDelegate)FunctionImporter.Import<n_config_listDelegate>("n_config_list");
            n_get_config_list = (n_get_config_listDelegate)FunctionImporter.Import<n_get_config_listDelegate>("n_get_config_list");
            n_save_disk = (n_save_diskDelegate)FunctionImporter.Import<n_save_diskDelegate>("n_save_disk");
            n_load_disk = (n_load_diskDelegate)FunctionImporter.Import<n_load_diskDelegate>("n_load_disk");
            n_get_list_space = (n_get_list_spaceDelegate)FunctionImporter.Import<n_get_list_spaceDelegate>("n_get_list_space");
            config_list = (config_listDelegate)FunctionImporter.Import<config_listDelegate>("config_list");
            get_config_list = (get_config_listDelegate)FunctionImporter.Import<get_config_listDelegate>("get_config_list");
            save_disk = (save_diskDelegate)FunctionImporter.Import<save_diskDelegate>("save_disk");
            load_disk = (load_diskDelegate)FunctionImporter.Import<load_diskDelegate>("load_disk");
            get_list_space = (get_list_spaceDelegate)FunctionImporter.Import<get_list_spaceDelegate>("get_list_space");
            n_set_start_list_pos = (n_set_start_list_posDelegate)FunctionImporter.Import<n_set_start_list_posDelegate>("n_set_start_list_pos");
            n_set_start_list = (n_set_start_listDelegate)FunctionImporter.Import<n_set_start_listDelegate>("n_set_start_list");
            n_set_start_list_1 = (n_set_start_list_1Delegate)FunctionImporter.Import<n_set_start_list_1Delegate>("n_set_start_list_1");
            n_set_start_list_2 = (n_set_start_list_2Delegate)FunctionImporter.Import<n_set_start_list_2Delegate>("n_set_start_list_2");
            n_set_input_pointer = (n_set_input_pointerDelegate)FunctionImporter.Import<n_set_input_pointerDelegate>("n_set_input_pointer");
            n_load_list = (n_load_listDelegate)FunctionImporter.Import<n_load_listDelegate>("n_load_list");
            n_load_sub = (n_load_subDelegate)FunctionImporter.Import<n_load_subDelegate>("n_load_sub");
            n_load_char = (n_load_charDelegate)FunctionImporter.Import<n_load_charDelegate>("n_load_char");
            n_load_text_table = (n_load_text_tableDelegate)FunctionImporter.Import<n_load_text_tableDelegate>("n_load_text_table");
            n_get_list_pointer = (n_get_list_pointerDelegate)FunctionImporter.Import<n_get_list_pointerDelegate>("n_get_list_pointer");
            n_get_input_pointer = (n_get_input_pointerDelegate)FunctionImporter.Import<n_get_input_pointerDelegate>("n_get_input_pointer");
            set_start_list_pos = (set_start_list_posDelegate)FunctionImporter.Import<set_start_list_posDelegate>("set_start_list_pos");
            set_start_list = (set_start_listDelegate)FunctionImporter.Import<set_start_listDelegate>("set_start_list");
            set_start_list_1 = (set_start_list_1Delegate)FunctionImporter.Import<set_start_list_1Delegate>("set_start_list_1");
            set_start_list_2 = (set_start_list_2Delegate)FunctionImporter.Import<set_start_list_2Delegate>("set_start_list_2");
            set_input_pointer = (set_input_pointerDelegate)FunctionImporter.Import<set_input_pointerDelegate>("set_input_pointer");
            load_list = (load_listDelegate)FunctionImporter.Import<load_listDelegate>("load_list");
            load_sub = (load_subDelegate)FunctionImporter.Import<load_subDelegate>("load_sub");
            load_char = (load_charDelegate)FunctionImporter.Import<load_charDelegate>("load_char");
            load_text_table = (load_text_tableDelegate)FunctionImporter.Import<load_text_tableDelegate>("load_text_table");
            get_list_pointer = (get_list_pointerDelegate)FunctionImporter.Import<get_list_pointerDelegate>("get_list_pointer");
            get_input_pointer = (get_input_pointerDelegate)FunctionImporter.Import<get_input_pointerDelegate>("get_input_pointer");
            n_execute_list_pos = (n_execute_list_posDelegate)FunctionImporter.Import<n_execute_list_posDelegate>("n_execute_list_pos");
            n_execute_at_pointer = (n_execute_at_pointerDelegate)FunctionImporter.Import<n_execute_at_pointerDelegate>("n_execute_at_pointer");
            n_execute_list = (n_execute_listDelegate)FunctionImporter.Import<n_execute_listDelegate>("n_execute_list");
            n_execute_list_1 = (n_execute_list_1Delegate)FunctionImporter.Import<n_execute_list_1Delegate>("n_execute_list_1");
            n_execute_list_2 = (n_execute_list_2Delegate)FunctionImporter.Import<n_execute_list_2Delegate>("n_execute_list_2");
            n_get_out_pointer = (n_get_out_pointerDelegate)FunctionImporter.Import<n_get_out_pointerDelegate>("n_get_out_pointer");
            execute_list_pos = (execute_list_posDelegate)FunctionImporter.Import<execute_list_posDelegate>("execute_list_pos");
            execute_at_pointer = (execute_at_pointerDelegate)FunctionImporter.Import<execute_at_pointerDelegate>("execute_at_pointer");
            execute_list = (execute_listDelegate)FunctionImporter.Import<execute_listDelegate>("execute_list");
            execute_list_1 = (execute_list_1Delegate)FunctionImporter.Import<execute_list_1Delegate>("execute_list_1");
            execute_list_2 = (execute_list_2Delegate)FunctionImporter.Import<execute_list_2Delegate>("execute_list_2");
            get_out_pointer = (get_out_pointerDelegate)FunctionImporter.Import<get_out_pointerDelegate>("get_out_pointer");
            n_auto_change_pos = (n_auto_change_posDelegate)FunctionImporter.Import<n_auto_change_posDelegate>("n_auto_change_pos");
            n_start_loop = (n_start_loopDelegate)FunctionImporter.Import<n_start_loopDelegate>("n_start_loop");
            n_quit_loop = (n_quit_loopDelegate)FunctionImporter.Import<n_quit_loopDelegate>("n_quit_loop");
            n_pause_list = (n_pause_listDelegate)FunctionImporter.Import<n_pause_listDelegate>("n_pause_list");
            n_restart_list = (n_restart_listDelegate)FunctionImporter.Import<n_restart_listDelegate>("n_restart_list");
            n_release_wait = (n_release_waitDelegate)FunctionImporter.Import<n_release_waitDelegate>("n_release_wait");
            n_stop_execution = (n_stop_executionDelegate)FunctionImporter.Import<n_stop_executionDelegate>("n_stop_execution");
            n_set_pause_list_cond = (n_set_pause_list_condDelegate)FunctionImporter.Import<n_set_pause_list_condDelegate>("n_set_pause_list_cond");
            n_set_pause_list_not_cond = (n_set_pause_list_not_condDelegate)FunctionImporter.Import<n_set_pause_list_not_condDelegate>("n_set_pause_list_not_cond");
            n_auto_change = (n_auto_changeDelegate)FunctionImporter.Import<n_auto_changeDelegate>("n_auto_change");
            n_stop_list = (n_stop_listDelegate)FunctionImporter.Import<n_stop_listDelegate>("n_stop_list");
            n_get_wait_status = (n_get_wait_statusDelegate)FunctionImporter.Import<n_get_wait_statusDelegate>("n_get_wait_status");
            n_read_status = (n_read_statusDelegate)FunctionImporter.Import<n_read_statusDelegate>("n_read_status");
            n_get_status = (n_get_statusDelegate)FunctionImporter.Import<n_get_statusDelegate>("n_get_status");
            auto_change_pos = (auto_change_posDelegate)FunctionImporter.Import<auto_change_posDelegate>("auto_change_pos");
            start_loop = (start_loopDelegate)FunctionImporter.Import<start_loopDelegate>("start_loop");
            quit_loop = (quit_loopDelegate)FunctionImporter.Import<quit_loopDelegate>("quit_loop");
            pause_list = (pause_listDelegate)FunctionImporter.Import<pause_listDelegate>("pause_list");
            restart_list = (restart_listDelegate)FunctionImporter.Import<restart_listDelegate>("restart_list");
            release_wait = (release_waitDelegate)FunctionImporter.Import<release_waitDelegate>("release_wait");
            stop_execution = (stop_executionDelegate)FunctionImporter.Import<stop_executionDelegate>("stop_execution");
            set_pause_list_cond = (set_pause_list_condDelegate)FunctionImporter.Import<set_pause_list_condDelegate>("set_pause_list_cond");
            set_pause_list_not_cond = (set_pause_list_not_condDelegate)FunctionImporter.Import<set_pause_list_not_condDelegate>("set_pause_list_not_cond");
            auto_change = (auto_changeDelegate)FunctionImporter.Import<auto_changeDelegate>("auto_change");
            stop_list = (stop_listDelegate)FunctionImporter.Import<stop_listDelegate>("stop_list");
            get_wait_status = (get_wait_statusDelegate)FunctionImporter.Import<get_wait_statusDelegate>("get_wait_status");
            read_status = (read_statusDelegate)FunctionImporter.Import<read_statusDelegate>("read_status");
            get_status = (get_statusDelegate)FunctionImporter.Import<get_statusDelegate>("get_status");
            n_set_extstartpos = (n_set_extstartposDelegate)FunctionImporter.Import<n_set_extstartposDelegate>("n_set_extstartpos");
            n_set_max_counts = (n_set_max_countsDelegate)FunctionImporter.Import<n_set_max_countsDelegate>("n_set_max_counts");
            n_set_control_mode = (n_set_control_modeDelegate)FunctionImporter.Import<n_set_control_modeDelegate>("n_set_control_mode");
            n_simulate_ext_stop = (n_simulate_ext_stopDelegate)FunctionImporter.Import<n_simulate_ext_stopDelegate>("n_simulate_ext_stop");
            n_simulate_ext_start_ctrl = (n_simulate_ext_start_ctrlDelegate)FunctionImporter.Import<n_simulate_ext_start_ctrlDelegate>("n_simulate_ext_start_ctrl");
            n_get_counts = (n_get_countsDelegate)FunctionImporter.Import<n_get_countsDelegate>("n_get_counts");
            n_get_startstop_info = (n_get_startstop_infoDelegate)FunctionImporter.Import<n_get_startstop_infoDelegate>("n_get_startstop_info");
            set_extstartpos = (set_extstartposDelegate)FunctionImporter.Import<set_extstartposDelegate>("set_extstartpos");
            set_max_counts = (set_max_countsDelegate)FunctionImporter.Import<set_max_countsDelegate>("set_max_counts");
            set_control_mode = (set_control_modeDelegate)FunctionImporter.Import<set_control_modeDelegate>("set_control_mode");
            simulate_ext_stop = (simulate_ext_stopDelegate)FunctionImporter.Import<simulate_ext_stopDelegate>("simulate_ext_stop");
            simulate_ext_start_ctrl = (simulate_ext_start_ctrlDelegate)FunctionImporter.Import<simulate_ext_start_ctrlDelegate>("simulate_ext_start_ctrl");
            get_counts = (get_countsDelegate)FunctionImporter.Import<get_countsDelegate>("get_counts");
            get_startstop_info = (get_startstop_infoDelegate)FunctionImporter.Import<get_startstop_infoDelegate>("get_startstop_info");
            n_copy_dst_src = (n_copy_dst_srcDelegate)FunctionImporter.Import<n_copy_dst_srcDelegate>("n_copy_dst_src");
            n_set_char_pointer = (n_set_char_pointerDelegate)FunctionImporter.Import<n_set_char_pointerDelegate>("n_set_char_pointer");
            n_set_sub_pointer = (n_set_sub_pointerDelegate)FunctionImporter.Import<n_set_sub_pointerDelegate>("n_set_sub_pointer");
            n_set_text_table_pointer = (n_set_text_table_pointerDelegate)FunctionImporter.Import<n_set_text_table_pointerDelegate>("n_set_text_table_pointer");
            n_set_char_table = (n_set_char_tableDelegate)FunctionImporter.Import<n_set_char_tableDelegate>("n_set_char_table");
            n_get_char_pointer = (n_get_char_pointerDelegate)FunctionImporter.Import<n_get_char_pointerDelegate>("n_get_char_pointer");
            n_get_sub_pointer = (n_get_sub_pointerDelegate)FunctionImporter.Import<n_get_sub_pointerDelegate>("n_get_sub_pointer");
            n_get_text_table_pointer = (n_get_text_table_pointerDelegate)FunctionImporter.Import<n_get_text_table_pointerDelegate>("n_get_text_table_pointer");
            copy_dst_src = (copy_dst_srcDelegate)FunctionImporter.Import<copy_dst_srcDelegate>("copy_dst_src");
            set_char_pointer = (set_char_pointerDelegate)FunctionImporter.Import<set_char_pointerDelegate>("set_char_pointer");
            set_sub_pointer = (set_sub_pointerDelegate)FunctionImporter.Import<set_sub_pointerDelegate>("set_sub_pointer");
            set_text_table_pointer = (set_text_table_pointerDelegate)FunctionImporter.Import<set_text_table_pointerDelegate>("set_text_table_pointer");
            set_char_table = (set_char_tableDelegate)FunctionImporter.Import<set_char_tableDelegate>("set_char_table");
            get_char_pointer = (get_char_pointerDelegate)FunctionImporter.Import<get_char_pointerDelegate>("get_char_pointer");
            get_sub_pointer = (get_sub_pointerDelegate)FunctionImporter.Import<get_sub_pointerDelegate>("get_sub_pointer");
            get_text_table_pointer = (get_text_table_pointerDelegate)FunctionImporter.Import<get_text_table_pointerDelegate>("get_text_table_pointer");
            n_time_update = (n_time_updateDelegate)FunctionImporter.Import<n_time_updateDelegate>("n_time_update");
            n_set_serial_step = (n_set_serial_stepDelegate)FunctionImporter.Import<n_set_serial_stepDelegate>("n_set_serial_step");
            n_select_serial_set = (n_select_serial_setDelegate)FunctionImporter.Import<n_select_serial_setDelegate>("n_select_serial_set");
            n_set_serial = (n_set_serialDelegate)FunctionImporter.Import<n_set_serialDelegate>("n_set_serial");
            n_get_serial = (n_get_serialDelegate)FunctionImporter.Import<n_get_serialDelegate>("n_get_serial");
            n_get_list_serial = (n_get_list_serialDelegate)FunctionImporter.Import<n_get_list_serialDelegate>("n_get_list_serial");
            time_update = (time_updateDelegate)FunctionImporter.Import<time_updateDelegate>("time_update");
            set_serial_step = (set_serial_stepDelegate)FunctionImporter.Import<set_serial_stepDelegate>("set_serial_step");
            select_serial_set = (select_serial_setDelegate)FunctionImporter.Import<select_serial_setDelegate>("select_serial_set");
            set_serial = (set_serialDelegate)FunctionImporter.Import<set_serialDelegate>("set_serial");
            get_serial = (get_serialDelegate)FunctionImporter.Import<get_serialDelegate>("get_serial");
            get_list_serial = (get_list_serialDelegate)FunctionImporter.Import<get_list_serialDelegate>("get_list_serial");
            n_write_io_port_mask = (n_write_io_port_maskDelegate)FunctionImporter.Import<n_write_io_port_maskDelegate>("n_write_io_port_mask");
            n_write_8bit_port = (n_write_8bit_portDelegate)FunctionImporter.Import<n_write_8bit_portDelegate>("n_write_8bit_port");
            n_read_io_port = (n_read_io_portDelegate)FunctionImporter.Import<n_read_io_portDelegate>("n_read_io_port");
            n_read_io_port_buffer = (n_read_io_port_bufferDelegate)FunctionImporter.Import<n_read_io_port_bufferDelegate>("n_read_io_port_buffer");
            n_get_io_status = (n_get_io_statusDelegate)FunctionImporter.Import<n_get_io_statusDelegate>("n_get_io_status");
            n_read_analog_in = (n_read_analog_inDelegate)FunctionImporter.Import<n_read_analog_inDelegate>("n_read_analog_in");
            n_write_da_x = (n_write_da_xDelegate)FunctionImporter.Import<n_write_da_xDelegate>("n_write_da_x");
            n_set_laser_off_default = (n_set_laser_off_defaultDelegate)FunctionImporter.Import<n_set_laser_off_defaultDelegate>("n_set_laser_off_default");
            n_set_port_default = (n_set_port_defaultDelegate)FunctionImporter.Import<n_set_port_defaultDelegate>("n_set_port_default");
            n_write_io_port = (n_write_io_portDelegate)FunctionImporter.Import<n_write_io_portDelegate>("n_write_io_port");
            n_write_da_1 = (n_write_da_1Delegate)FunctionImporter.Import<n_write_da_1Delegate>("n_write_da_1");
            n_write_da_2 = (n_write_da_2Delegate)FunctionImporter.Import<n_write_da_2Delegate>("n_write_da_2");
            write_io_port_mask = (write_io_port_maskDelegate)FunctionImporter.Import<write_io_port_maskDelegate>("write_io_port_mask");
            write_8bit_port = (write_8bit_portDelegate)FunctionImporter.Import<write_8bit_portDelegate>("write_8bit_port");
            read_io_port = (read_io_portDelegate)FunctionImporter.Import<read_io_portDelegate>("read_io_port");
            read_io_port_buffer = (read_io_port_bufferDelegate)FunctionImporter.Import<read_io_port_bufferDelegate>("read_io_port_buffer");
            get_io_status = (get_io_statusDelegate)FunctionImporter.Import<get_io_statusDelegate>("get_io_status");
            read_analog_in = (read_analog_inDelegate)FunctionImporter.Import<read_analog_inDelegate>("read_analog_in");
            write_da_x = (write_da_xDelegate)FunctionImporter.Import<write_da_xDelegate>("write_da_x");
            set_laser_off_default = (set_laser_off_defaultDelegate)FunctionImporter.Import<set_laser_off_defaultDelegate>("set_laser_off_default");
            set_port_default = (set_port_defaultDelegate)FunctionImporter.Import<set_port_defaultDelegate>("set_port_default");
            write_io_port = (write_io_portDelegate)FunctionImporter.Import<write_io_portDelegate>("write_io_port");
            write_da_1 = (write_da_1Delegate)FunctionImporter.Import<write_da_1Delegate>("write_da_1");
            write_da_2 = (write_da_2Delegate)FunctionImporter.Import<write_da_2Delegate>("write_da_2");
            n_disable_laser = (n_disable_laserDelegate)FunctionImporter.Import<n_disable_laserDelegate>("n_disable_laser");
            n_enable_laser = (n_enable_laserDelegate)FunctionImporter.Import<n_enable_laserDelegate>("n_enable_laser");
            n_laser_signal_on = (n_laser_signal_onDelegate)FunctionImporter.Import<n_laser_signal_onDelegate>("n_laser_signal_on");
            n_laser_signal_off = (n_laser_signal_offDelegate)FunctionImporter.Import<n_laser_signal_offDelegate>("n_laser_signal_off");
            n_set_standby = (n_set_standbyDelegate)FunctionImporter.Import<n_set_standbyDelegate>("n_set_standby");
            n_set_laser_pulses_ctrl = (n_set_laser_pulses_ctrlDelegate)FunctionImporter.Import<n_set_laser_pulses_ctrlDelegate>("n_set_laser_pulses_ctrl");
            n_set_firstpulse_killer = (n_set_firstpulse_killerDelegate)FunctionImporter.Import<n_set_firstpulse_killerDelegate>("n_set_firstpulse_killer");
            n_set_qswitch_delay = (n_set_qswitch_delayDelegate)FunctionImporter.Import<n_set_qswitch_delayDelegate>("n_set_qswitch_delay");
            n_set_laser_mode = (n_set_laser_modeDelegate)FunctionImporter.Import<n_set_laser_modeDelegate>("n_set_laser_mode");
            n_set_laser_control = (n_set_laser_controlDelegate)FunctionImporter.Import<n_set_laser_controlDelegate>("n_set_laser_control");
            n_set_laser_pin_out = (n_set_laser_pin_outDelegate)FunctionImporter.Import<n_set_laser_pin_outDelegate>("n_set_laser_pin_out");
            n_get_laser_pin_in = (n_get_laser_pin_inDelegate)FunctionImporter.Import<n_get_laser_pin_inDelegate>("n_get_laser_pin_in");
            n_set_softstart_level = (n_set_softstart_levelDelegate)FunctionImporter.Import<n_set_softstart_levelDelegate>("n_set_softstart_level");
            n_set_softstart_mode = (n_set_softstart_modeDelegate)FunctionImporter.Import<n_set_softstart_modeDelegate>("n_set_softstart_mode");
            n_set_auto_laser_control = (n_set_auto_laser_controlDelegate)FunctionImporter.Import<n_set_auto_laser_controlDelegate>("n_set_auto_laser_control");
            n_set_auto_laser_params = (n_set_auto_laser_paramsDelegate)FunctionImporter.Import<n_set_auto_laser_paramsDelegate>("n_set_auto_laser_params");
            n_load_auto_laser_control = (n_load_auto_laser_controlDelegate)FunctionImporter.Import<n_load_auto_laser_controlDelegate>("n_load_auto_laser_control");
            n_load_position_control = (n_load_position_controlDelegate)FunctionImporter.Import<n_load_position_controlDelegate>("n_load_position_control");
            n_set_default_pixel = (n_set_default_pixelDelegate)FunctionImporter.Import<n_set_default_pixelDelegate>("n_set_default_pixel");
            n_get_standby = (n_get_standbyDelegate)FunctionImporter.Import<n_get_standbyDelegate>("n_get_standby");
            n_set_pulse_picking = (n_set_pulse_pickingDelegate)FunctionImporter.Import<n_set_pulse_pickingDelegate>("n_set_pulse_picking");
            n_set_pulse_picking_length = (n_set_pulse_picking_lengthDelegate)FunctionImporter.Import<n_set_pulse_picking_lengthDelegate>("n_set_pulse_picking_length");
            n_config_laser_signals = (n_config_laser_signalsDelegate)FunctionImporter.Import<n_config_laser_signalsDelegate>("n_config_laser_signals");
            disable_laser = (disable_laserDelegate)FunctionImporter.Import<disable_laserDelegate>("disable_laser");
            enable_laser = (enable_laserDelegate)FunctionImporter.Import<enable_laserDelegate>("enable_laser");
            laser_signal_on = (laser_signal_onDelegate)FunctionImporter.Import<laser_signal_onDelegate>("laser_signal_on");
            laser_signal_off = (laser_signal_offDelegate)FunctionImporter.Import<laser_signal_offDelegate>("laser_signal_off");
            set_standby = (set_standbyDelegate)FunctionImporter.Import<set_standbyDelegate>("set_standby");
            set_laser_pulses_ctrl = (set_laser_pulses_ctrlDelegate)FunctionImporter.Import<set_laser_pulses_ctrlDelegate>("set_laser_pulses_ctrl");
            set_firstpulse_killer = (set_firstpulse_killerDelegate)FunctionImporter.Import<set_firstpulse_killerDelegate>("set_firstpulse_killer");
            set_qswitch_delay = (set_qswitch_delayDelegate)FunctionImporter.Import<set_qswitch_delayDelegate>("set_qswitch_delay");
            set_laser_mode = (set_laser_modeDelegate)FunctionImporter.Import<set_laser_modeDelegate>("set_laser_mode");
            set_laser_control = (set_laser_controlDelegate)FunctionImporter.Import<set_laser_controlDelegate>("set_laser_control");
            set_laser_pin_out = (set_laser_pin_outDelegate)FunctionImporter.Import<set_laser_pin_outDelegate>("set_laser_pin_out");
            get_laser_pin_in = (get_laser_pin_inDelegate)FunctionImporter.Import<get_laser_pin_inDelegate>("get_laser_pin_in");
            set_softstart_level = (set_softstart_levelDelegate)FunctionImporter.Import<set_softstart_levelDelegate>("set_softstart_level");
            set_softstart_mode = (set_softstart_modeDelegate)FunctionImporter.Import<set_softstart_modeDelegate>("set_softstart_mode");
            set_auto_laser_control = (set_auto_laser_controlDelegate)FunctionImporter.Import<set_auto_laser_controlDelegate>("set_auto_laser_control");
            set_auto_laser_params = (set_auto_laser_paramsDelegate)FunctionImporter.Import<set_auto_laser_paramsDelegate>("set_auto_laser_params");
            load_auto_laser_control = (load_auto_laser_controlDelegate)FunctionImporter.Import<load_auto_laser_controlDelegate>("load_auto_laser_control");
            load_position_control = (load_position_controlDelegate)FunctionImporter.Import<load_position_controlDelegate>("load_position_control");
            set_default_pixel = (set_default_pixelDelegate)FunctionImporter.Import<set_default_pixelDelegate>("set_default_pixel");
            get_standby = (get_standbyDelegate)FunctionImporter.Import<get_standbyDelegate>("get_standby");
            set_pulse_picking = (set_pulse_pickingDelegate)FunctionImporter.Import<set_pulse_pickingDelegate>("set_pulse_picking");
            set_pulse_picking_length = (set_pulse_picking_lengthDelegate)FunctionImporter.Import<set_pulse_picking_lengthDelegate>("set_pulse_picking_length");
            config_laser_signals = (config_laser_signalsDelegate)FunctionImporter.Import<config_laser_signalsDelegate>("config_laser_signals");
            n_set_ext_start_delay = (n_set_ext_start_delayDelegate)FunctionImporter.Import<n_set_ext_start_delayDelegate>("n_set_ext_start_delay");
            n_set_rot_center = (n_set_rot_centerDelegate)FunctionImporter.Import<n_set_rot_centerDelegate>("n_set_rot_center");
            n_simulate_encoder = (n_simulate_encoderDelegate)FunctionImporter.Import<n_simulate_encoderDelegate>("n_simulate_encoder");
            n_get_marking_info = (n_get_marking_infoDelegate)FunctionImporter.Import<n_get_marking_infoDelegate>("n_get_marking_info");
            n_set_encoder_speed_ctrl = (n_set_encoder_speed_ctrlDelegate)FunctionImporter.Import<n_set_encoder_speed_ctrlDelegate>("n_set_encoder_speed_ctrl");
            n_set_mcbsp_x = (n_set_mcbsp_xDelegate)FunctionImporter.Import<n_set_mcbsp_xDelegate>("n_set_mcbsp_x");
            n_set_mcbsp_y = (n_set_mcbsp_yDelegate)FunctionImporter.Import<n_set_mcbsp_yDelegate>("n_set_mcbsp_y");
            n_set_mcbsp_rot = (n_set_mcbsp_rotDelegate)FunctionImporter.Import<n_set_mcbsp_rotDelegate>("n_set_mcbsp_rot");
            n_set_mcbsp_matrix = (n_set_mcbsp_matrixDelegate)FunctionImporter.Import<n_set_mcbsp_matrixDelegate>("n_set_mcbsp_matrix");
            n_set_mcbsp_global_x = (n_set_mcbsp_global_xDelegate)FunctionImporter.Import<n_set_mcbsp_global_xDelegate>("n_set_mcbsp_global_x");
            n_set_mcbsp_global_y = (n_set_mcbsp_global_yDelegate)FunctionImporter.Import<n_set_mcbsp_global_yDelegate>("n_set_mcbsp_global_y");
            n_set_mcbsp_global_rot = (n_set_mcbsp_global_rotDelegate)FunctionImporter.Import<n_set_mcbsp_global_rotDelegate>("n_set_mcbsp_global_rot");
            n_set_mcbsp_global_matrix = (n_set_mcbsp_global_matrixDelegate)FunctionImporter.Import<n_set_mcbsp_global_matrixDelegate>("n_set_mcbsp_global_matrix");
            n_set_mcbsp_in = (n_set_mcbsp_inDelegate)FunctionImporter.Import<n_set_mcbsp_inDelegate>("n_set_mcbsp_in");
            n_set_multi_mcbsp_in = (n_set_multi_mcbsp_inDelegate)FunctionImporter.Import<n_set_multi_mcbsp_inDelegate>("n_set_multi_mcbsp_in");
            n_set_fly_tracking_error = (n_set_fly_tracking_errorDelegate)FunctionImporter.Import<n_set_fly_tracking_errorDelegate>("n_set_fly_tracking_error");
            n_load_fly_2d_table = (n_load_fly_2d_tableDelegate)FunctionImporter.Import<n_load_fly_2d_tableDelegate>("n_load_fly_2d_table");
            n_init_fly_2d = (n_init_fly_2dDelegate)FunctionImporter.Import<n_init_fly_2dDelegate>("n_init_fly_2d");
            n_get_fly_2d_offset = (n_get_fly_2d_offsetDelegate)FunctionImporter.Import<n_get_fly_2d_offsetDelegate>("n_get_fly_2d_offset");
            n_get_encoder = (n_get_encoderDelegate)FunctionImporter.Import<n_get_encoderDelegate>("n_get_encoder");
            n_read_encoder = (n_read_encoderDelegate)FunctionImporter.Import<n_read_encoderDelegate>("n_read_encoder");
            n_get_mcbsp = (n_get_mcbspDelegate)FunctionImporter.Import<n_get_mcbspDelegate>("n_get_mcbsp");
            n_read_mcbsp = (n_read_mcbspDelegate)FunctionImporter.Import<n_read_mcbspDelegate>("n_read_mcbsp");
            n_read_multi_mcbsp = (n_read_multi_mcbspDelegate)FunctionImporter.Import<n_read_multi_mcbspDelegate>("n_read_multi_mcbsp");
            n_clear_fly_overflow_ctrl = (n_clear_fly_overflow_ctrlDelegate)FunctionImporter.Import<n_clear_fly_overflow_ctrlDelegate>("n_clear_fly_overflow_ctrl");
            set_ext_start_delay = (set_ext_start_delayDelegate)FunctionImporter.Import<set_ext_start_delayDelegate>("set_ext_start_delay");
            set_rot_center = (set_rot_centerDelegate)FunctionImporter.Import<set_rot_centerDelegate>("set_rot_center");
            simulate_encoder = (simulate_encoderDelegate)FunctionImporter.Import<simulate_encoderDelegate>("simulate_encoder");
            get_marking_info = (get_marking_infoDelegate)FunctionImporter.Import<get_marking_infoDelegate>("get_marking_info");
            set_encoder_speed_ctrl = (set_encoder_speed_ctrlDelegate)FunctionImporter.Import<set_encoder_speed_ctrlDelegate>("set_encoder_speed_ctrl");
            set_mcbsp_x = (set_mcbsp_xDelegate)FunctionImporter.Import<set_mcbsp_xDelegate>("set_mcbsp_x");
            set_mcbsp_y = (set_mcbsp_yDelegate)FunctionImporter.Import<set_mcbsp_yDelegate>("set_mcbsp_y");
            set_mcbsp_rot = (set_mcbsp_rotDelegate)FunctionImporter.Import<set_mcbsp_rotDelegate>("set_mcbsp_rot");
            set_mcbsp_matrix = (set_mcbsp_matrixDelegate)FunctionImporter.Import<set_mcbsp_matrixDelegate>("set_mcbsp_matrix");
            set_mcbsp_global_x = (set_mcbsp_global_xDelegate)FunctionImporter.Import<set_mcbsp_global_xDelegate>("set_mcbsp_global_x");
            set_mcbsp_global_y = (set_mcbsp_global_yDelegate)FunctionImporter.Import<set_mcbsp_global_yDelegate>("set_mcbsp_global_y");
            set_mcbsp_global_rot = (set_mcbsp_global_rotDelegate)FunctionImporter.Import<set_mcbsp_global_rotDelegate>("set_mcbsp_global_rot");
            set_mcbsp_global_matrix = (set_mcbsp_global_matrixDelegate)FunctionImporter.Import<set_mcbsp_global_matrixDelegate>("set_mcbsp_global_matrix");
            set_mcbsp_in = (set_mcbsp_inDelegate)FunctionImporter.Import<set_mcbsp_inDelegate>("set_mcbsp_in");
            set_multi_mcbsp_in = (set_multi_mcbsp_inDelegate)FunctionImporter.Import<set_multi_mcbsp_inDelegate>("set_multi_mcbsp_in");
            set_fly_tracking_error = (set_fly_tracking_errorDelegate)FunctionImporter.Import<set_fly_tracking_errorDelegate>("set_fly_tracking_error");
            load_fly_2d_table = (load_fly_2d_tableDelegate)FunctionImporter.Import<load_fly_2d_tableDelegate>("load_fly_2d_table");
            init_fly_2d = (init_fly_2dDelegate)FunctionImporter.Import<init_fly_2dDelegate>("init_fly_2d");
            get_fly_2d_offset = (get_fly_2d_offsetDelegate)FunctionImporter.Import<get_fly_2d_offsetDelegate>("get_fly_2d_offset");
            get_encoder = (get_encoderDelegate)FunctionImporter.Import<get_encoderDelegate>("get_encoder");
            read_encoder = (read_encoderDelegate)FunctionImporter.Import<read_encoderDelegate>("read_encoder");
            get_mcbsp = (get_mcbspDelegate)FunctionImporter.Import<get_mcbspDelegate>("get_mcbsp");
            read_mcbsp = (read_mcbspDelegate)FunctionImporter.Import<read_mcbspDelegate>("read_mcbsp");
            read_multi_mcbsp = (read_multi_mcbspDelegate)FunctionImporter.Import<read_multi_mcbspDelegate>("read_multi_mcbsp");
            clear_fly_overflow_ctrl = (clear_fly_overflow_ctrlDelegate)FunctionImporter.Import<clear_fly_overflow_ctrlDelegate>("clear_fly_overflow_ctrl");
            n_get_time = (n_get_timeDelegate)FunctionImporter.Import<n_get_timeDelegate>("n_get_time");
            n_get_lap_time = (n_get_lap_timeDelegate)FunctionImporter.Import<n_get_lap_timeDelegate>("n_get_lap_time");
            n_measurement_status = (n_measurement_statusDelegate)FunctionImporter.Import<n_measurement_statusDelegate>("n_measurement_status");
            n_get_waveform = (n_get_waveformDelegate)FunctionImporter.Import<n_get_waveformDelegate>("n_get_waveform");
            n_bounce_supp = (n_bounce_suppDelegate)FunctionImporter.Import<n_bounce_suppDelegate>("n_bounce_supp");
            n_home_position_xyz = (n_home_position_xyzDelegate)FunctionImporter.Import<n_home_position_xyzDelegate>("n_home_position_xyz");
            n_home_position = (n_home_positionDelegate)FunctionImporter.Import<n_home_positionDelegate>("n_home_position");
            n_rs232_config = (n_rs232_configDelegate)FunctionImporter.Import<n_rs232_configDelegate>("n_rs232_config");
            n_rs232_write_data = (n_rs232_write_dataDelegate)FunctionImporter.Import<n_rs232_write_dataDelegate>("n_rs232_write_data");
            n_rs232_write_text = (n_rs232_write_textDelegate)FunctionImporter.Import<n_rs232_write_textDelegate>("n_rs232_write_text");
            n_rs232_read_data = (n_rs232_read_dataDelegate)FunctionImporter.Import<n_rs232_read_dataDelegate>("n_rs232_read_data");
            n_set_mcbsp_freq = (n_set_mcbsp_freqDelegate)FunctionImporter.Import<n_set_mcbsp_freqDelegate>("n_set_mcbsp_freq");
            n_mcbsp_init = (n_mcbsp_initDelegate)FunctionImporter.Import<n_mcbsp_initDelegate>("n_mcbsp_init");
            n_mcbsp_init_spi = (n_mcbsp_init_spiDelegate)FunctionImporter.Import<n_mcbsp_init_spiDelegate>("n_mcbsp_init_spi");
            n_get_overrun = (n_get_overrunDelegate)FunctionImporter.Import<n_get_overrunDelegate>("n_get_overrun");
            n_get_master_slave = (n_get_master_slaveDelegate)FunctionImporter.Import<n_get_master_slaveDelegate>("n_get_master_slave");
            n_get_transform = (n_get_transformDelegate)FunctionImporter.Import<n_get_transformDelegate>("n_get_transform");
            n_stop_trigger = (n_stop_triggerDelegate)FunctionImporter.Import<n_stop_triggerDelegate>("n_stop_trigger");
            n_move_to = (n_move_toDelegate)FunctionImporter.Import<n_move_toDelegate>("n_move_to");
            n_set_enduring_wobbel = (n_set_enduring_wobbelDelegate)FunctionImporter.Import<n_set_enduring_wobbelDelegate>("n_set_enduring_wobbel");
            n_set_enduring_wobbel_2 = (n_set_enduring_wobbel_2Delegate)FunctionImporter.Import<n_set_enduring_wobbel_2Delegate>("n_set_enduring_wobbel_2");
            n_set_free_variable = (n_set_free_variableDelegate)FunctionImporter.Import<n_set_free_variableDelegate>("n_set_free_variable");
            n_get_free_variable = (n_get_free_variableDelegate)FunctionImporter.Import<n_get_free_variableDelegate>("n_get_free_variable");
            n_set_mcbsp_out_ptr = (n_set_mcbsp_out_ptrDelegate)FunctionImporter.Import<n_set_mcbsp_out_ptrDelegate>("n_set_mcbsp_out_ptr");
            n_periodic_toggle = (n_periodic_toggleDelegate)FunctionImporter.Import<n_periodic_toggleDelegate>("n_periodic_toggle");
            n_load_wobbel_power = (n_load_wobbel_powerDelegate)FunctionImporter.Import<n_load_wobbel_powerDelegate>("n_load_wobbel_power");
            get_time = (get_timeDelegate)FunctionImporter.Import<get_timeDelegate>("get_time");
            get_lap_time = (get_lap_timeDelegate)FunctionImporter.Import<get_lap_timeDelegate>("get_lap_time");
            measurement_status = (measurement_statusDelegate)FunctionImporter.Import<measurement_statusDelegate>("measurement_status");
            get_waveform = (get_waveformDelegate)FunctionImporter.Import<get_waveformDelegate>("get_waveform");
            bounce_supp = (bounce_suppDelegate)FunctionImporter.Import<bounce_suppDelegate>("bounce_supp");
            home_position_xyz = (home_position_xyzDelegate)FunctionImporter.Import<home_position_xyzDelegate>("home_position_xyz");
            home_position = (home_positionDelegate)FunctionImporter.Import<home_positionDelegate>("home_position");
            rs232_config = (rs232_configDelegate)FunctionImporter.Import<rs232_configDelegate>("rs232_config");
            rs232_write_data = (rs232_write_dataDelegate)FunctionImporter.Import<rs232_write_dataDelegate>("rs232_write_data");
            rs232_write_text = (rs232_write_textDelegate)FunctionImporter.Import<rs232_write_textDelegate>("rs232_write_text");
            rs232_read_data = (rs232_read_dataDelegate)FunctionImporter.Import<rs232_read_dataDelegate>("rs232_read_data");
            set_mcbsp_freq = (set_mcbsp_freqDelegate)FunctionImporter.Import<set_mcbsp_freqDelegate>("set_mcbsp_freq");
            mcbsp_init = (mcbsp_initDelegate)FunctionImporter.Import<mcbsp_initDelegate>("mcbsp_init");
            mcbsp_init_spi = (mcbsp_init_spiDelegate)FunctionImporter.Import<mcbsp_init_spiDelegate>("mcbsp_init_spi");
            get_overrun = (get_overrunDelegate)FunctionImporter.Import<get_overrunDelegate>("get_overrun");
            get_master_slave = (get_master_slaveDelegate)FunctionImporter.Import<get_master_slaveDelegate>("get_master_slave");
            get_transform = (get_transformDelegate)FunctionImporter.Import<get_transformDelegate>("get_transform");
            stop_trigger = (stop_triggerDelegate)FunctionImporter.Import<stop_triggerDelegate>("stop_trigger");
            move_to = (move_toDelegate)FunctionImporter.Import<move_toDelegate>("move_to");
            set_enduring_wobbel = (set_enduring_wobbelDelegate)FunctionImporter.Import<set_enduring_wobbelDelegate>("set_enduring_wobbel");
            set_enduring_wobbel_2 = (set_enduring_wobbel_2Delegate)FunctionImporter.Import<set_enduring_wobbel_2Delegate>("set_enduring_wobbel_2");
            set_free_variable = (set_free_variableDelegate)FunctionImporter.Import<set_free_variableDelegate>("set_free_variable");
            get_free_variable = (get_free_variableDelegate)FunctionImporter.Import<get_free_variableDelegate>("get_free_variable");
            set_mcbsp_out_ptr = (set_mcbsp_out_ptrDelegate)FunctionImporter.Import<set_mcbsp_out_ptrDelegate>("set_mcbsp_out_ptr");
            periodic_toggle = (periodic_toggleDelegate)FunctionImporter.Import<periodic_toggleDelegate>("periodic_toggle");
            load_wobbel_power = (load_wobbel_powerDelegate)FunctionImporter.Import<load_wobbel_powerDelegate>("load_wobbel_power");
            n_set_defocus = (n_set_defocusDelegate)FunctionImporter.Import<n_set_defocusDelegate>("n_set_defocus");
            n_set_defocus_offset = (n_set_defocus_offsetDelegate)FunctionImporter.Import<n_set_defocus_offsetDelegate>("n_set_defocus_offset");
            n_goto_xyz = (n_goto_xyzDelegate)FunctionImporter.Import<n_goto_xyzDelegate>("n_goto_xyz");
            n_set_zoom = (n_set_zoomDelegate)FunctionImporter.Import<n_set_zoomDelegate>("n_set_zoom");
            n_goto_xy = (n_goto_xyDelegate)FunctionImporter.Import<n_goto_xyDelegate>("n_goto_xy");
            n_get_z_distance = (n_get_z_distanceDelegate)FunctionImporter.Import<n_get_z_distanceDelegate>("n_get_z_distance");
            set_defocus = (set_defocusDelegate)FunctionImporter.Import<set_defocusDelegate>("set_defocus");
            set_defocus_offset = (set_defocus_offsetDelegate)FunctionImporter.Import<set_defocus_offsetDelegate>("set_defocus_offset");
            goto_xyz = (goto_xyzDelegate)FunctionImporter.Import<goto_xyzDelegate>("goto_xyz");
            goto_xy = (goto_xyDelegate)FunctionImporter.Import<goto_xyDelegate>("goto_xy");
            set_zoom = (set_zoomDelegate)FunctionImporter.Import<set_zoomDelegate>("set_zoom");
            get_z_distance = (get_z_distanceDelegate)FunctionImporter.Import<get_z_distanceDelegate>("get_z_distance");
            n_set_offset_xyz = (n_set_offset_xyzDelegate)FunctionImporter.Import<n_set_offset_xyzDelegate>("n_set_offset_xyz");
            n_set_offset = (n_set_offsetDelegate)FunctionImporter.Import<n_set_offsetDelegate>("n_set_offset");
            n_set_matrix = (n_set_matrixDelegate)FunctionImporter.Import<n_set_matrixDelegate>("n_set_matrix");
            n_set_angle = (n_set_angleDelegate)FunctionImporter.Import<n_set_angleDelegate>("n_set_angle");
            n_set_scale = (n_set_scaleDelegate)FunctionImporter.Import<n_set_scaleDelegate>("n_set_scale");
            n_apply_mcbsp = (n_apply_mcbspDelegate)FunctionImporter.Import<n_apply_mcbspDelegate>("n_apply_mcbsp");
            n_upload_transform = (n_upload_transformDelegate)FunctionImporter.Import<n_upload_transformDelegate>("n_upload_transform");
            set_offset_xyz = (set_offset_xyzDelegate)FunctionImporter.Import<set_offset_xyzDelegate>("set_offset_xyz");
            set_offset = (set_offsetDelegate)FunctionImporter.Import<set_offsetDelegate>("set_offset");
            set_matrix = (set_matrixDelegate)FunctionImporter.Import<set_matrixDelegate>("set_matrix");
            set_angle = (set_angleDelegate)FunctionImporter.Import<set_angleDelegate>("set_angle");
            set_scale = (set_scaleDelegate)FunctionImporter.Import<set_scaleDelegate>("set_scale");
            apply_mcbsp = (apply_mcbspDelegate)FunctionImporter.Import<apply_mcbspDelegate>("apply_mcbsp");
            upload_transform = (upload_transformDelegate)FunctionImporter.Import<upload_transformDelegate>("upload_transform");
            transform = (transformDelegate)FunctionImporter.Import<transformDelegate>("transform");
            n_set_delay_mode = (n_set_delay_modeDelegate)FunctionImporter.Import<n_set_delay_modeDelegate>("n_set_delay_mode");
            n_set_jump_speed_ctrl = (n_set_jump_speed_ctrlDelegate)FunctionImporter.Import<n_set_jump_speed_ctrlDelegate>("n_set_jump_speed_ctrl");
            n_set_mark_speed_ctrl = (n_set_mark_speed_ctrlDelegate)FunctionImporter.Import<n_set_mark_speed_ctrlDelegate>("n_set_mark_speed_ctrl");
            n_set_sky_writing_para = (n_set_sky_writing_paraDelegate)FunctionImporter.Import<n_set_sky_writing_paraDelegate>("n_set_sky_writing_para");
            n_set_sky_writing_limit = (n_set_sky_writing_limitDelegate)FunctionImporter.Import<n_set_sky_writing_limitDelegate>("n_set_sky_writing_limit");
            n_set_sky_writing_mode = (n_set_sky_writing_modeDelegate)FunctionImporter.Import<n_set_sky_writing_modeDelegate>("n_set_sky_writing_mode");
            n_load_varpolydelay = (n_load_varpolydelayDelegate)FunctionImporter.Import<n_load_varpolydelayDelegate>("n_load_varpolydelay");
            n_set_hi = (n_set_hiDelegate)FunctionImporter.Import<n_set_hiDelegate>("n_set_hi");
            n_get_hi_pos = (n_get_hi_posDelegate)FunctionImporter.Import<n_get_hi_posDelegate>("n_get_hi_pos");
            n_auto_cal = (n_auto_calDelegate)FunctionImporter.Import<n_auto_calDelegate>("n_auto_cal");
            n_get_auto_cal = (n_get_auto_calDelegate)FunctionImporter.Import<n_get_auto_calDelegate>("n_get_auto_cal");
            n_write_hi_pos = (n_write_hi_posDelegate)FunctionImporter.Import<n_write_hi_posDelegate>("n_write_hi_pos");
            n_set_sky_writing = (n_set_sky_writingDelegate)FunctionImporter.Import<n_set_sky_writingDelegate>("n_set_sky_writing");
            n_get_hi_data = (n_get_hi_dataDelegate)FunctionImporter.Import<n_get_hi_dataDelegate>("n_get_hi_data");
            set_delay_mode = (set_delay_modeDelegate)FunctionImporter.Import<set_delay_modeDelegate>("set_delay_mode");
            set_jump_speed_ctrl = (set_jump_speed_ctrlDelegate)FunctionImporter.Import<set_jump_speed_ctrlDelegate>("set_jump_speed_ctrl");
            set_mark_speed_ctrl = (set_mark_speed_ctrlDelegate)FunctionImporter.Import<set_mark_speed_ctrlDelegate>("set_mark_speed_ctrl");
            set_sky_writing_para = (set_sky_writing_paraDelegate)FunctionImporter.Import<set_sky_writing_paraDelegate>("set_sky_writing_para");
            set_sky_writing_limit = (set_sky_writing_limitDelegate)FunctionImporter.Import<set_sky_writing_limitDelegate>("set_sky_writing_limit");
            set_sky_writing_mode = (set_sky_writing_modeDelegate)FunctionImporter.Import<set_sky_writing_modeDelegate>("set_sky_writing_mode");
            load_varpolydelay = (load_varpolydelayDelegate)FunctionImporter.Import<load_varpolydelayDelegate>("load_varpolydelay");
            set_hi = (set_hiDelegate)FunctionImporter.Import<set_hiDelegate>("set_hi");
            get_hi_pos = (get_hi_posDelegate)FunctionImporter.Import<get_hi_posDelegate>("get_hi_pos");
            auto_cal = (auto_calDelegate)FunctionImporter.Import<auto_calDelegate>("auto_cal");
            get_auto_cal = (get_auto_calDelegate)FunctionImporter.Import<get_auto_calDelegate>("get_auto_cal");
            write_hi_pos = (write_hi_posDelegate)FunctionImporter.Import<write_hi_posDelegate>("write_hi_pos");
            set_sky_writing = (set_sky_writingDelegate)FunctionImporter.Import<set_sky_writingDelegate>("set_sky_writing");
            get_hi_data = (get_hi_dataDelegate)FunctionImporter.Import<get_hi_dataDelegate>("get_hi_data");
            n_send_user_data = (n_send_user_dataDelegate)FunctionImporter.Import<n_send_user_dataDelegate>("n_send_user_data");
            n_read_user_data = (n_read_user_dataDelegate)FunctionImporter.Import<n_read_user_dataDelegate>("n_read_user_data");
            n_control_command = (n_control_commandDelegate)FunctionImporter.Import<n_control_commandDelegate>("n_control_command");
            n_get_value = (n_get_valueDelegate)FunctionImporter.Import<n_get_valueDelegate>("n_get_value");
            n_get_values = (n_get_valuesDelegate)FunctionImporter.Import<n_get_valuesDelegate>("n_get_values");
            n_get_galvo_controls = (n_get_galvo_controlsDelegate)FunctionImporter.Import<n_get_galvo_controlsDelegate>("n_get_galvo_controls");
            n_get_head_status = (n_get_head_statusDelegate)FunctionImporter.Import<n_get_head_statusDelegate>("n_get_head_status");
            n_set_jump_mode = (n_set_jump_modeDelegate)FunctionImporter.Import<n_set_jump_modeDelegate>("n_set_jump_mode");
            n_load_jump_table_offset = (n_load_jump_table_offsetDelegate)FunctionImporter.Import<n_load_jump_table_offsetDelegate>("n_load_jump_table_offset");
            n_get_jump_table = (n_get_jump_tableDelegate)FunctionImporter.Import<n_get_jump_tableDelegate>("n_get_jump_table");
            n_set_jump_table = (n_set_jump_tableDelegate)FunctionImporter.Import<n_set_jump_tableDelegate>("n_set_jump_table");
            n_load_jump_table = (n_load_jump_tableDelegate)FunctionImporter.Import<n_load_jump_tableDelegate>("n_load_jump_table");
            send_user_data = (send_user_dataDelegate)FunctionImporter.Import<send_user_dataDelegate>("send_user_data");
            read_user_data = (read_user_dataDelegate)FunctionImporter.Import<read_user_dataDelegate>("read_user_data");
            control_command = (control_commandDelegate)FunctionImporter.Import<control_commandDelegate>("control_command");
            get_value = (get_valueDelegate)FunctionImporter.Import<get_valueDelegate>("get_value");
            get_values = (get_valuesDelegate)FunctionImporter.Import<get_valuesDelegate>("get_values");
            get_galvo_controls = (get_galvo_controlsDelegate)FunctionImporter.Import<get_galvo_controlsDelegate>("get_galvo_controls");
            get_head_status = (get_head_statusDelegate)FunctionImporter.Import<get_head_statusDelegate>("get_head_status");
            set_jump_mode = (set_jump_modeDelegate)FunctionImporter.Import<set_jump_modeDelegate>("set_jump_mode");
            load_jump_table_offset = (load_jump_table_offsetDelegate)FunctionImporter.Import<load_jump_table_offsetDelegate>("load_jump_table_offset");
            get_jump_table = (get_jump_tableDelegate)FunctionImporter.Import<get_jump_tableDelegate>("get_jump_table");
            set_jump_table = (set_jump_tableDelegate)FunctionImporter.Import<set_jump_tableDelegate>("set_jump_table");
            load_jump_table = (load_jump_tableDelegate)FunctionImporter.Import<load_jump_tableDelegate>("load_jump_table");
            n_stepper_init = (n_stepper_initDelegate)FunctionImporter.Import<n_stepper_initDelegate>("n_stepper_init");
            n_stepper_enable = (n_stepper_enableDelegate)FunctionImporter.Import<n_stepper_enableDelegate>("n_stepper_enable");
            n_stepper_disable_switch = (n_stepper_disable_switchDelegate)FunctionImporter.Import<n_stepper_disable_switchDelegate>("n_stepper_disable_switch");
            n_stepper_control = (n_stepper_controlDelegate)FunctionImporter.Import<n_stepper_controlDelegate>("n_stepper_control");
            n_stepper_abs_no = (n_stepper_abs_noDelegate)FunctionImporter.Import<n_stepper_abs_noDelegate>("n_stepper_abs_no");
            n_stepper_rel_no = (n_stepper_rel_noDelegate)FunctionImporter.Import<n_stepper_rel_noDelegate>("n_stepper_rel_no");
            n_stepper_abs = (n_stepper_absDelegate)FunctionImporter.Import<n_stepper_absDelegate>("n_stepper_abs");
            n_stepper_rel = (n_stepper_relDelegate)FunctionImporter.Import<n_stepper_relDelegate>("n_stepper_rel");
            n_get_stepper_status = (n_get_stepper_statusDelegate)FunctionImporter.Import<n_get_stepper_statusDelegate>("n_get_stepper_status");
            stepper_init = (stepper_initDelegate)FunctionImporter.Import<stepper_initDelegate>("stepper_init");
            stepper_enable = (stepper_enableDelegate)FunctionImporter.Import<stepper_enableDelegate>("stepper_enable");
            stepper_disable_switch = (stepper_disable_switchDelegate)FunctionImporter.Import<stepper_disable_switchDelegate>("stepper_disable_switch");
            stepper_control = (stepper_controlDelegate)FunctionImporter.Import<stepper_controlDelegate>("stepper_control");
            stepper_abs_no = (stepper_abs_noDelegate)FunctionImporter.Import<stepper_abs_noDelegate>("stepper_abs_no");
            stepper_rel_no = (stepper_rel_noDelegate)FunctionImporter.Import<stepper_rel_noDelegate>("stepper_rel_no");
            stepper_abs = (stepper_absDelegate)FunctionImporter.Import<stepper_absDelegate>("stepper_abs");
            stepper_rel = (stepper_relDelegate)FunctionImporter.Import<stepper_relDelegate>("stepper_rel");
            get_stepper_status = (get_stepper_statusDelegate)FunctionImporter.Import<get_stepper_statusDelegate>("get_stepper_status");
            n_select_cor_table_list = (n_select_cor_table_listDelegate)FunctionImporter.Import<n_select_cor_table_listDelegate>("n_select_cor_table_list");
            select_cor_table_list = (select_cor_table_listDelegate)FunctionImporter.Import<select_cor_table_listDelegate>("select_cor_table_list");
            n_list_nop = (n_list_nopDelegate)FunctionImporter.Import<n_list_nopDelegate>("n_list_nop");
            n_list_continue = (n_list_continueDelegate)FunctionImporter.Import<n_list_continueDelegate>("n_list_continue");
            n_list_next = (n_list_nextDelegate)FunctionImporter.Import<n_list_nextDelegate>("n_list_next");
            n_long_delay = (n_long_delayDelegate)FunctionImporter.Import<n_long_delayDelegate>("n_long_delay");
            n_set_end_of_list = (n_set_end_of_listDelegate)FunctionImporter.Import<n_set_end_of_listDelegate>("n_set_end_of_list");
            n_set_wait = (n_set_waitDelegate)FunctionImporter.Import<n_set_waitDelegate>("n_set_wait");
            n_list_jump_pos = (n_list_jump_posDelegate)FunctionImporter.Import<n_list_jump_posDelegate>("n_list_jump_pos");
            n_list_jump_rel = (n_list_jump_relDelegate)FunctionImporter.Import<n_list_jump_relDelegate>("n_list_jump_rel");
            n_list_repeat = (n_list_repeatDelegate)FunctionImporter.Import<n_list_repeatDelegate>("n_list_repeat");
            n_list_until = (n_list_untilDelegate)FunctionImporter.Import<n_list_untilDelegate>("n_list_until");
            n_range_checking = (n_range_checkingDelegate)FunctionImporter.Import<n_range_checkingDelegate>("n_range_checking");
            n_set_list_jump = (n_set_list_jumpDelegate)FunctionImporter.Import<n_set_list_jumpDelegate>("n_set_list_jump");
            list_nop = (list_nopDelegate)FunctionImporter.Import<list_nopDelegate>("list_nop");
            list_continue = (list_continueDelegate)FunctionImporter.Import<list_continueDelegate>("list_continue");
            list_next = (list_nextDelegate)FunctionImporter.Import<list_nextDelegate>("list_next");
            long_delay = (long_delayDelegate)FunctionImporter.Import<long_delayDelegate>("long_delay");
            set_end_of_list = (set_end_of_listDelegate)FunctionImporter.Import<set_end_of_listDelegate>("set_end_of_list");
            set_wait = (set_waitDelegate)FunctionImporter.Import<set_waitDelegate>("set_wait");
            list_jump_pos = (list_jump_posDelegate)FunctionImporter.Import<list_jump_posDelegate>("list_jump_pos");
            list_jump_rel = (list_jump_relDelegate)FunctionImporter.Import<list_jump_relDelegate>("list_jump_rel");
            list_repeat = (list_repeatDelegate)FunctionImporter.Import<list_repeatDelegate>("list_repeat");
            list_until = (list_untilDelegate)FunctionImporter.Import<list_untilDelegate>("list_until");
            range_checking = (range_checkingDelegate)FunctionImporter.Import<range_checkingDelegate>("range_checking");
            set_list_jump = (set_list_jumpDelegate)FunctionImporter.Import<set_list_jumpDelegate>("set_list_jump");
            n_set_extstartpos_list = (n_set_extstartpos_listDelegate)FunctionImporter.Import<n_set_extstartpos_listDelegate>("n_set_extstartpos_list");
            n_set_control_mode_list = (n_set_control_mode_listDelegate)FunctionImporter.Import<n_set_control_mode_listDelegate>("n_set_control_mode_list");
            n_simulate_ext_start = (n_simulate_ext_startDelegate)FunctionImporter.Import<n_simulate_ext_startDelegate>("n_simulate_ext_start");
            set_extstartpos_list = (set_extstartpos_listDelegate)FunctionImporter.Import<set_extstartpos_listDelegate>("set_extstartpos_list");
            set_control_mode_list = (set_control_mode_listDelegate)FunctionImporter.Import<set_control_mode_listDelegate>("set_control_mode_list");
            simulate_ext_start = (simulate_ext_startDelegate)FunctionImporter.Import<simulate_ext_startDelegate>("simulate_ext_start");
            n_list_return = (n_list_returnDelegate)FunctionImporter.Import<n_list_returnDelegate>("n_list_return");
            n_list_call_repeat = (n_list_call_repeatDelegate)FunctionImporter.Import<n_list_call_repeatDelegate>("n_list_call_repeat");
            n_list_call_abs_repeat = (n_list_call_abs_repeatDelegate)FunctionImporter.Import<n_list_call_abs_repeatDelegate>("n_list_call_abs_repeat");
            n_list_call = (n_list_callDelegate)FunctionImporter.Import<n_list_callDelegate>("n_list_call");
            n_list_call_abs = (n_list_call_absDelegate)FunctionImporter.Import<n_list_call_absDelegate>("n_list_call_abs");
            n_sub_call_repeat = (n_sub_call_repeatDelegate)FunctionImporter.Import<n_sub_call_repeatDelegate>("n_sub_call_repeat");
            n_sub_call_abs_repeat = (n_sub_call_abs_repeatDelegate)FunctionImporter.Import<n_sub_call_abs_repeatDelegate>("n_sub_call_abs_repeat");
            n_sub_call = (n_sub_callDelegate)FunctionImporter.Import<n_sub_callDelegate>("n_sub_call");
            n_sub_call_abs = (n_sub_call_absDelegate)FunctionImporter.Import<n_sub_call_absDelegate>("n_sub_call_abs");
            list_return = (list_returnDelegate)FunctionImporter.Import<list_returnDelegate>("list_return");
            list_call_repeat = (list_call_repeatDelegate)FunctionImporter.Import<list_call_repeatDelegate>("list_call_repeat");
            list_call_abs_repeat = (list_call_abs_repeatDelegate)FunctionImporter.Import<list_call_abs_repeatDelegate>("list_call_abs_repeat");
            list_call = (list_callDelegate)FunctionImporter.Import<list_callDelegate>("list_call");
            list_call_abs = (list_call_absDelegate)FunctionImporter.Import<list_call_absDelegate>("list_call_abs");
            sub_call_repeat = (sub_call_repeatDelegate)FunctionImporter.Import<sub_call_repeatDelegate>("sub_call_repeat");
            sub_call_abs_repeat = (sub_call_abs_repeatDelegate)FunctionImporter.Import<sub_call_abs_repeatDelegate>("sub_call_abs_repeat");
            sub_call = (sub_callDelegate)FunctionImporter.Import<sub_callDelegate>("sub_call");
            sub_call_abs = (sub_call_absDelegate)FunctionImporter.Import<sub_call_absDelegate>("sub_call_abs");
            n_list_call_cond = (n_list_call_condDelegate)FunctionImporter.Import<n_list_call_condDelegate>("n_list_call_cond");
            n_list_call_abs_cond = (n_list_call_abs_condDelegate)FunctionImporter.Import<n_list_call_abs_condDelegate>("n_list_call_abs_cond");
            n_sub_call_cond = (n_sub_call_condDelegate)FunctionImporter.Import<n_sub_call_condDelegate>("n_sub_call_cond");
            n_sub_call_abs_cond = (n_sub_call_abs_condDelegate)FunctionImporter.Import<n_sub_call_abs_condDelegate>("n_sub_call_abs_cond");
            n_list_jump_pos_cond = (n_list_jump_pos_condDelegate)FunctionImporter.Import<n_list_jump_pos_condDelegate>("n_list_jump_pos_cond");
            n_list_jump_rel_cond = (n_list_jump_rel_condDelegate)FunctionImporter.Import<n_list_jump_rel_condDelegate>("n_list_jump_rel_cond");
            n_if_cond = (n_if_condDelegate)FunctionImporter.Import<n_if_condDelegate>("n_if_cond");
            n_if_not_cond = (n_if_not_condDelegate)FunctionImporter.Import<n_if_not_condDelegate>("n_if_not_cond");
            n_if_pin_cond = (n_if_pin_condDelegate)FunctionImporter.Import<n_if_pin_condDelegate>("n_if_pin_cond");
            n_if_not_pin_cond = (n_if_not_pin_condDelegate)FunctionImporter.Import<n_if_not_pin_condDelegate>("n_if_not_pin_cond");
            n_switch_ioport = (n_switch_ioportDelegate)FunctionImporter.Import<n_switch_ioportDelegate>("n_switch_ioport");
            n_list_jump_cond = (n_list_jump_condDelegate)FunctionImporter.Import<n_list_jump_condDelegate>("n_list_jump_cond");
            list_call_cond = (list_call_condDelegate)FunctionImporter.Import<list_call_condDelegate>("list_call_cond");
            list_call_abs_cond = (list_call_abs_condDelegate)FunctionImporter.Import<list_call_abs_condDelegate>("list_call_abs_cond");
            sub_call_cond = (sub_call_condDelegate)FunctionImporter.Import<sub_call_condDelegate>("sub_call_cond");
            sub_call_abs_cond = (sub_call_abs_condDelegate)FunctionImporter.Import<sub_call_abs_condDelegate>("sub_call_abs_cond");
            list_jump_pos_cond = (list_jump_pos_condDelegate)FunctionImporter.Import<list_jump_pos_condDelegate>("list_jump_pos_cond");
            list_jump_rel_cond = (list_jump_rel_condDelegate)FunctionImporter.Import<list_jump_rel_condDelegate>("list_jump_rel_cond");
            if_cond = (if_condDelegate)FunctionImporter.Import<if_condDelegate>("if_cond");
            if_not_cond = (if_not_condDelegate)FunctionImporter.Import<if_not_condDelegate>("if_not_cond");
            if_pin_cond = (if_pin_condDelegate)FunctionImporter.Import<if_pin_condDelegate>("if_pin_cond");
            if_not_pin_cond = (if_not_pin_condDelegate)FunctionImporter.Import<if_not_pin_condDelegate>("if_not_pin_cond");
            switch_ioport = (switch_ioportDelegate)FunctionImporter.Import<switch_ioportDelegate>("switch_ioport");
            list_jump_cond = (list_jump_condDelegate)FunctionImporter.Import<list_jump_condDelegate>("list_jump_cond");
            n_select_char_set = (n_select_char_setDelegate)FunctionImporter.Import<n_select_char_setDelegate>("n_select_char_set");
            n_mark_text = (n_mark_textDelegate)FunctionImporter.Import<n_mark_textDelegate>("n_mark_text");
            n_mark_text_abs = (n_mark_text_absDelegate)FunctionImporter.Import<n_mark_text_absDelegate>("n_mark_text_abs");
            n_mark_char = (n_mark_charDelegate)FunctionImporter.Import<n_mark_charDelegate>("n_mark_char");
            n_mark_char_abs = (n_mark_char_absDelegate)FunctionImporter.Import<n_mark_char_absDelegate>("n_mark_char_abs");
            select_char_set = (select_char_setDelegate)FunctionImporter.Import<select_char_setDelegate>("select_char_set");
            mark_text = (mark_textDelegate)FunctionImporter.Import<mark_textDelegate>("mark_text");
            mark_text_abs = (mark_text_absDelegate)FunctionImporter.Import<mark_text_absDelegate>("mark_text_abs");
            mark_char = (mark_charDelegate)FunctionImporter.Import<mark_charDelegate>("mark_char");
            mark_char_abs = (mark_char_absDelegate)FunctionImporter.Import<mark_char_absDelegate>("mark_char_abs");
            n_mark_serial = (n_mark_serialDelegate)FunctionImporter.Import<n_mark_serialDelegate>("n_mark_serial");
            n_mark_serial_abs = (n_mark_serial_absDelegate)FunctionImporter.Import<n_mark_serial_absDelegate>("n_mark_serial_abs");
            n_mark_date = (n_mark_dateDelegate)FunctionImporter.Import<n_mark_dateDelegate>("n_mark_date");
            n_mark_date_abs = (n_mark_date_absDelegate)FunctionImporter.Import<n_mark_date_absDelegate>("n_mark_date_abs");
            n_mark_time = (n_mark_timeDelegate)FunctionImporter.Import<n_mark_timeDelegate>("n_mark_time");
            n_mark_time_abs = (n_mark_time_absDelegate)FunctionImporter.Import<n_mark_time_absDelegate>("n_mark_time_abs");
            n_select_serial_set_list = (n_select_serial_set_listDelegate)FunctionImporter.Import<n_select_serial_set_listDelegate>("n_select_serial_set_list");
            n_set_serial_step_list = (n_set_serial_step_listDelegate)FunctionImporter.Import<n_set_serial_step_listDelegate>("n_set_serial_step_list");
            n_time_fix_f_off = (n_time_fix_f_offDelegate)FunctionImporter.Import<n_time_fix_f_offDelegate>("n_time_fix_f_off");
            n_time_fix_f = (n_time_fix_fDelegate)FunctionImporter.Import<n_time_fix_fDelegate>("n_time_fix_f");
            n_time_fix = (n_time_fixDelegate)FunctionImporter.Import<n_time_fixDelegate>("n_time_fix");
            mark_serial = (mark_serialDelegate)FunctionImporter.Import<mark_serialDelegate>("mark_serial");
            mark_serial_abs = (mark_serial_absDelegate)FunctionImporter.Import<mark_serial_absDelegate>("mark_serial_abs");
            mark_date = (mark_dateDelegate)FunctionImporter.Import<mark_dateDelegate>("mark_date");
            mark_date_abs = (mark_date_absDelegate)FunctionImporter.Import<mark_date_absDelegate>("mark_date_abs");
            mark_time = (mark_timeDelegate)FunctionImporter.Import<mark_timeDelegate>("mark_time");
            mark_time_abs = (mark_time_absDelegate)FunctionImporter.Import<mark_time_absDelegate>("mark_time_abs");
            time_fix_f_off = (time_fix_f_offDelegate)FunctionImporter.Import<time_fix_f_offDelegate>("time_fix_f_off");
            select_serial_set_list = (select_serial_set_listDelegate)FunctionImporter.Import<select_serial_set_listDelegate>("select_serial_set_list");
            set_serial_step_list = (set_serial_step_listDelegate)FunctionImporter.Import<set_serial_step_listDelegate>("set_serial_step_list");
            time_fix_f = (time_fix_fDelegate)FunctionImporter.Import<time_fix_fDelegate>("time_fix_f");
            time_fix = (time_fixDelegate)FunctionImporter.Import<time_fixDelegate>("time_fix");
            n_clear_io_cond_list = (n_clear_io_cond_listDelegate)FunctionImporter.Import<n_clear_io_cond_listDelegate>("n_clear_io_cond_list");
            n_set_io_cond_list = (n_set_io_cond_listDelegate)FunctionImporter.Import<n_set_io_cond_listDelegate>("n_set_io_cond_list");
            n_write_io_port_mask_list = (n_write_io_port_mask_listDelegate)FunctionImporter.Import<n_write_io_port_mask_listDelegate>("n_write_io_port_mask_list");
            n_write_8bit_port_list = (n_write_8bit_port_listDelegate)FunctionImporter.Import<n_write_8bit_port_listDelegate>("n_write_8bit_port_list");
            n_read_io_port_list = (n_read_io_port_listDelegate)FunctionImporter.Import<n_read_io_port_listDelegate>("n_read_io_port_list");
            n_write_da_x_list = (n_write_da_x_listDelegate)FunctionImporter.Import<n_write_da_x_listDelegate>("n_write_da_x_list");
            n_write_io_port_list = (n_write_io_port_listDelegate)FunctionImporter.Import<n_write_io_port_listDelegate>("n_write_io_port_list");
            n_write_da_1_list = (n_write_da_1_listDelegate)FunctionImporter.Import<n_write_da_1_listDelegate>("n_write_da_1_list");
            n_write_da_2_list = (n_write_da_2_listDelegate)FunctionImporter.Import<n_write_da_2_listDelegate>("n_write_da_2_list");
            clear_io_cond_list = (clear_io_cond_listDelegate)FunctionImporter.Import<clear_io_cond_listDelegate>("clear_io_cond_list");
            set_io_cond_list = (set_io_cond_listDelegate)FunctionImporter.Import<set_io_cond_listDelegate>("set_io_cond_list");
            write_io_port_mask_list = (write_io_port_mask_listDelegate)FunctionImporter.Import<write_io_port_mask_listDelegate>("write_io_port_mask_list");
            write_8bit_port_list = (write_8bit_port_listDelegate)FunctionImporter.Import<write_8bit_port_listDelegate>("write_8bit_port_list");
            read_io_port_list = (read_io_port_listDelegate)FunctionImporter.Import<read_io_port_listDelegate>("read_io_port_list");
            write_da_x_list = (write_da_x_listDelegate)FunctionImporter.Import<write_da_x_listDelegate>("write_da_x_list");
            write_io_port_list = (write_io_port_listDelegate)FunctionImporter.Import<write_io_port_listDelegate>("write_io_port_list");
            write_da_1_list = (write_da_1_listDelegate)FunctionImporter.Import<write_da_1_listDelegate>("write_da_1_list");
            write_da_2_list = (write_da_2_listDelegate)FunctionImporter.Import<write_da_2_listDelegate>("write_da_2_list");
            n_laser_signal_on_list = (n_laser_signal_on_listDelegate)FunctionImporter.Import<n_laser_signal_on_listDelegate>("n_laser_signal_on_list");
            n_laser_signal_off_list = (n_laser_signal_off_listDelegate)FunctionImporter.Import<n_laser_signal_off_listDelegate>("n_laser_signal_off_list");
            n_para_laser_on_pulses_list = (n_para_laser_on_pulses_listDelegate)FunctionImporter.Import<n_para_laser_on_pulses_listDelegate>("n_para_laser_on_pulses_list");
            n_laser_on_pulses_list = (n_laser_on_pulses_listDelegate)FunctionImporter.Import<n_laser_on_pulses_listDelegate>("n_laser_on_pulses_list");
            n_laser_on_list = (n_laser_on_listDelegate)FunctionImporter.Import<n_laser_on_listDelegate>("n_laser_on_list");
            n_set_laser_delays = (n_set_laser_delaysDelegate)FunctionImporter.Import<n_set_laser_delaysDelegate>("n_set_laser_delays");
            n_set_standby_list = (n_set_standby_listDelegate)FunctionImporter.Import<n_set_standby_listDelegate>("n_set_standby_list");
            n_set_laser_pulses = (n_set_laser_pulsesDelegate)FunctionImporter.Import<n_set_laser_pulsesDelegate>("n_set_laser_pulses");
            n_set_firstpulse_killer_list = (n_set_firstpulse_killer_listDelegate)FunctionImporter.Import<n_set_firstpulse_killer_listDelegate>("n_set_firstpulse_killer_list");
            n_set_qswitch_delay_list = (n_set_qswitch_delay_listDelegate)FunctionImporter.Import<n_set_qswitch_delay_listDelegate>("n_set_qswitch_delay_list");
            n_set_laser_pin_out_list = (n_set_laser_pin_out_listDelegate)FunctionImporter.Import<n_set_laser_pin_out_listDelegate>("n_set_laser_pin_out_list");
            n_set_vector_control = (n_set_vector_controlDelegate)FunctionImporter.Import<n_set_vector_controlDelegate>("n_set_vector_control");
            n_set_default_pixel_list = (n_set_default_pixel_listDelegate)FunctionImporter.Import<n_set_default_pixel_listDelegate>("n_set_default_pixel_list");
            n_set_port_default_list = (n_set_port_default_listDelegate)FunctionImporter.Import<n_set_port_default_listDelegate>("n_set_port_default_list");
            n_set_auto_laser_params_list = (n_set_auto_laser_params_listDelegate)FunctionImporter.Import<n_set_auto_laser_params_listDelegate>("n_set_auto_laser_params_list");
            n_set_pulse_picking_list = (n_set_pulse_picking_listDelegate)FunctionImporter.Import<n_set_pulse_picking_listDelegate>("n_set_pulse_picking_list");
            n_set_softstart_level_list = (n_set_softstart_level_listDelegate)FunctionImporter.Import<n_set_softstart_level_listDelegate>("n_set_softstart_level_list");
            n_set_softstart_mode_list = (n_set_softstart_mode_listDelegate)FunctionImporter.Import<n_set_softstart_mode_listDelegate>("n_set_softstart_mode_list");
            n_config_laser_signals_list = (n_config_laser_signals_listDelegate)FunctionImporter.Import<n_config_laser_signals_listDelegate>("n_config_laser_signals_list");
            n_set_laser_timing = (n_set_laser_timingDelegate)FunctionImporter.Import<n_set_laser_timingDelegate>("n_set_laser_timing");
            laser_signal_on_list = (laser_signal_on_listDelegate)FunctionImporter.Import<laser_signal_on_listDelegate>("laser_signal_on_list");
            laser_signal_off_list = (laser_signal_off_listDelegate)FunctionImporter.Import<laser_signal_off_listDelegate>("laser_signal_off_list");
            para_laser_on_pulses_list = (para_laser_on_pulses_listDelegate)FunctionImporter.Import<para_laser_on_pulses_listDelegate>("para_laser_on_pulses_list");
            laser_on_pulses_list = (laser_on_pulses_listDelegate)FunctionImporter.Import<laser_on_pulses_listDelegate>("laser_on_pulses_list");
            laser_on_list = (laser_on_listDelegate)FunctionImporter.Import<laser_on_listDelegate>("laser_on_list");
            set_laser_delays = (set_laser_delaysDelegate)FunctionImporter.Import<set_laser_delaysDelegate>("set_laser_delays");
            set_standby_list = (set_standby_listDelegate)FunctionImporter.Import<set_standby_listDelegate>("set_standby_list");
            set_laser_pulses = (set_laser_pulsesDelegate)FunctionImporter.Import<set_laser_pulsesDelegate>("set_laser_pulses");
            set_firstpulse_killer_list = (set_firstpulse_killer_listDelegate)FunctionImporter.Import<set_firstpulse_killer_listDelegate>("set_firstpulse_killer_list");
            set_qswitch_delay_list = (set_qswitch_delay_listDelegate)FunctionImporter.Import<set_qswitch_delay_listDelegate>("set_qswitch_delay_list");
            set_laser_pin_out_list = (set_laser_pin_out_listDelegate)FunctionImporter.Import<set_laser_pin_out_listDelegate>("set_laser_pin_out_list");
            set_vector_control = (set_vector_controlDelegate)FunctionImporter.Import<set_vector_controlDelegate>("set_vector_control");
            set_default_pixel_list = (set_default_pixel_listDelegate)FunctionImporter.Import<set_default_pixel_listDelegate>("set_default_pixel_list");
            set_port_default_list = (set_port_default_listDelegate)FunctionImporter.Import<set_port_default_listDelegate>("set_port_default_list");
            set_auto_laser_params_list = (set_auto_laser_params_listDelegate)FunctionImporter.Import<set_auto_laser_params_listDelegate>("set_auto_laser_params_list");
            set_pulse_picking_list = (set_pulse_picking_listDelegate)FunctionImporter.Import<set_pulse_picking_listDelegate>("set_pulse_picking_list");
            set_softstart_level_list = (set_softstart_level_listDelegate)FunctionImporter.Import<set_softstart_level_listDelegate>("set_softstart_level_list");
            set_softstart_mode_list = (set_softstart_mode_listDelegate)FunctionImporter.Import<set_softstart_mode_listDelegate>("set_softstart_mode_list");
            config_laser_signals_list = (config_laser_signals_listDelegate)FunctionImporter.Import<config_laser_signals_listDelegate>("config_laser_signals_list");
            set_laser_timing = (set_laser_timingDelegate)FunctionImporter.Import<set_laser_timingDelegate>("set_laser_timing");
            n_fly_return_z = (n_fly_return_zDelegate)FunctionImporter.Import<n_fly_return_zDelegate>("n_fly_return_z");
            n_fly_return = (n_fly_returnDelegate)FunctionImporter.Import<n_fly_returnDelegate>("n_fly_return");
            n_set_rot_center_list = (n_set_rot_center_listDelegate)FunctionImporter.Import<n_set_rot_center_listDelegate>("n_set_rot_center_list");
            n_set_ext_start_delay_list = (n_set_ext_start_delay_listDelegate)FunctionImporter.Import<n_set_ext_start_delay_listDelegate>("n_set_ext_start_delay_list");
            n_set_fly_x = (n_set_fly_xDelegate)FunctionImporter.Import<n_set_fly_xDelegate>("n_set_fly_x");
            n_set_fly_y = (n_set_fly_yDelegate)FunctionImporter.Import<n_set_fly_yDelegate>("n_set_fly_y");
            n_set_fly_z = (n_set_fly_zDelegate)FunctionImporter.Import<n_set_fly_zDelegate>("n_set_fly_z");
            n_set_fly_rot = (n_set_fly_rotDelegate)FunctionImporter.Import<n_set_fly_rotDelegate>("n_set_fly_rot");
            n_set_fly_2d = (n_set_fly_2dDelegate)FunctionImporter.Import<n_set_fly_2dDelegate>("n_set_fly_2d");
            n_set_fly_x_pos = (n_set_fly_x_posDelegate)FunctionImporter.Import<n_set_fly_x_posDelegate>("n_set_fly_x_pos");
            n_set_fly_y_pos = (n_set_fly_y_posDelegate)FunctionImporter.Import<n_set_fly_y_posDelegate>("n_set_fly_y_pos");
            n_set_fly_rot_pos = (n_set_fly_rot_posDelegate)FunctionImporter.Import<n_set_fly_rot_posDelegate>("n_set_fly_rot_pos");
            n_set_fly_limits = (n_set_fly_limitsDelegate)FunctionImporter.Import<n_set_fly_limitsDelegate>("n_set_fly_limits");
            n_set_fly_limits_z = (n_set_fly_limits_zDelegate)FunctionImporter.Import<n_set_fly_limits_zDelegate>("n_set_fly_limits_z");
            n_if_fly_x_overflow = (n_if_fly_x_overflowDelegate)FunctionImporter.Import<n_if_fly_x_overflowDelegate>("n_if_fly_x_overflow");
            n_if_fly_y_overflow = (n_if_fly_y_overflowDelegate)FunctionImporter.Import<n_if_fly_y_overflowDelegate>("n_if_fly_y_overflow");
            n_if_fly_z_overflow = (n_if_fly_z_overflowDelegate)FunctionImporter.Import<n_if_fly_z_overflowDelegate>("n_if_fly_z_overflow");
            n_if_not_fly_x_overflow = (n_if_not_fly_x_overflowDelegate)FunctionImporter.Import<n_if_not_fly_x_overflowDelegate>("n_if_not_fly_x_overflow");
            n_if_not_fly_y_overflow = (n_if_not_fly_y_overflowDelegate)FunctionImporter.Import<n_if_not_fly_y_overflowDelegate>("n_if_not_fly_y_overflow");
            n_if_not_fly_z_overflow = (n_if_not_fly_z_overflowDelegate)FunctionImporter.Import<n_if_not_fly_z_overflowDelegate>("n_if_not_fly_z_overflow");
            n_clear_fly_overflow = (n_clear_fly_overflowDelegate)FunctionImporter.Import<n_clear_fly_overflowDelegate>("n_clear_fly_overflow");
            n_set_mcbsp_x_list = (n_set_mcbsp_x_listDelegate)FunctionImporter.Import<n_set_mcbsp_x_listDelegate>("n_set_mcbsp_x_list");
            n_set_mcbsp_y_list = (n_set_mcbsp_y_listDelegate)FunctionImporter.Import<n_set_mcbsp_y_listDelegate>("n_set_mcbsp_y_list");
            n_set_mcbsp_rot_list = (n_set_mcbsp_rot_listDelegate)FunctionImporter.Import<n_set_mcbsp_rot_listDelegate>("n_set_mcbsp_rot_list");
            n_set_mcbsp_matrix_list = (n_set_mcbsp_matrix_listDelegate)FunctionImporter.Import<n_set_mcbsp_matrix_listDelegate>("n_set_mcbsp_matrix_list");
            n_set_mcbsp_global_x_list = (n_set_mcbsp_global_x_listDelegate)FunctionImporter.Import<n_set_mcbsp_global_x_listDelegate>("n_set_mcbsp_global_x_list");
            n_set_mcbsp_global_y_list = (n_set_mcbsp_global_y_listDelegate)FunctionImporter.Import<n_set_mcbsp_global_y_listDelegate>("n_set_mcbsp_global_y_list");
            n_set_mcbsp_global_rot_list = (n_set_mcbsp_global_rot_listDelegate)FunctionImporter.Import<n_set_mcbsp_global_rot_listDelegate>("n_set_mcbsp_global_rot_list");
            n_set_mcbsp_global_matrix_list = (n_set_mcbsp_global_matrix_listDelegate)FunctionImporter.Import<n_set_mcbsp_global_matrix_listDelegate>("n_set_mcbsp_global_matrix_list");
            n_set_mcbsp_in_list = (n_set_mcbsp_in_listDelegate)FunctionImporter.Import<n_set_mcbsp_in_listDelegate>("n_set_mcbsp_in_list");
            n_set_multi_mcbsp_in_list = (n_set_multi_mcbsp_in_listDelegate)FunctionImporter.Import<n_set_multi_mcbsp_in_listDelegate>("n_set_multi_mcbsp_in_list");
            n_wait_for_encoder_mode = (n_wait_for_encoder_modeDelegate)FunctionImporter.Import<n_wait_for_encoder_modeDelegate>("n_wait_for_encoder_mode");
            n_wait_for_mcbsp = (n_wait_for_mcbspDelegate)FunctionImporter.Import<n_wait_for_mcbspDelegate>("n_wait_for_mcbsp");
            n_set_encoder_speed = (n_set_encoder_speedDelegate)FunctionImporter.Import<n_set_encoder_speedDelegate>("n_set_encoder_speed");
            n_get_mcbsp_list = (n_get_mcbsp_listDelegate)FunctionImporter.Import<n_get_mcbsp_listDelegate>("n_get_mcbsp_list");
            n_store_encoder = (n_store_encoderDelegate)FunctionImporter.Import<n_store_encoderDelegate>("n_store_encoder");
            n_wait_for_encoder_in_range = (n_wait_for_encoder_in_rangeDelegate)FunctionImporter.Import<n_wait_for_encoder_in_rangeDelegate>("n_wait_for_encoder_in_range");
            n_activate_fly_xy = (n_activate_fly_xyDelegate)FunctionImporter.Import<n_activate_fly_xyDelegate>("n_activate_fly_xy");
            n_activate_fly_2d = (n_activate_fly_2dDelegate)FunctionImporter.Import<n_activate_fly_2dDelegate>("n_activate_fly_2d");
            n_activate_fly_xy_encoder = (n_activate_fly_xy_encoderDelegate)FunctionImporter.Import<n_activate_fly_xy_encoderDelegate>("n_activate_fly_xy_encoder");
            n_activate_fly_2d_encoder = (n_activate_fly_2d_encoderDelegate)FunctionImporter.Import<n_activate_fly_2d_encoderDelegate>("n_activate_fly_2d_encoder");
            n_if_not_activated = (n_if_not_activatedDelegate)FunctionImporter.Import<n_if_not_activatedDelegate>("n_if_not_activated");
            n_park_position = (n_park_positionDelegate)FunctionImporter.Import<n_park_positionDelegate>("n_park_position");
            n_park_return = (n_park_returnDelegate)FunctionImporter.Import<n_park_returnDelegate>("n_park_return");
            n_wait_for_encoder = (n_wait_for_encoderDelegate)FunctionImporter.Import<n_wait_for_encoderDelegate>("n_wait_for_encoder");
            fly_return_z = (fly_return_zDelegate)FunctionImporter.Import<fly_return_zDelegate>("fly_return_z");
            fly_return = (fly_returnDelegate)FunctionImporter.Import<fly_returnDelegate>("fly_return");
            set_rot_center_list = (set_rot_center_listDelegate)FunctionImporter.Import<set_rot_center_listDelegate>("set_rot_center_list");
            set_ext_start_delay_list = (set_ext_start_delay_listDelegate)FunctionImporter.Import<set_ext_start_delay_listDelegate>("set_ext_start_delay_list");
            set_fly_x = (set_fly_xDelegate)FunctionImporter.Import<set_fly_xDelegate>("set_fly_x");
            set_fly_y = (set_fly_yDelegate)FunctionImporter.Import<set_fly_yDelegate>("set_fly_y");
            set_fly_z = (set_fly_zDelegate)FunctionImporter.Import<set_fly_zDelegate>("set_fly_z");
            set_fly_rot = (set_fly_rotDelegate)FunctionImporter.Import<set_fly_rotDelegate>("set_fly_rot");
            set_fly_2d = (set_fly_2dDelegate)FunctionImporter.Import<set_fly_2dDelegate>("set_fly_2d");
            set_fly_x_pos = (set_fly_x_posDelegate)FunctionImporter.Import<set_fly_x_posDelegate>("set_fly_x_pos");
            set_fly_y_pos = (set_fly_y_posDelegate)FunctionImporter.Import<set_fly_y_posDelegate>("set_fly_y_pos");
            set_fly_rot_pos = (set_fly_rot_posDelegate)FunctionImporter.Import<set_fly_rot_posDelegate>("set_fly_rot_pos");
            set_fly_limits = (set_fly_limitsDelegate)FunctionImporter.Import<set_fly_limitsDelegate>("set_fly_limits");
            set_fly_limits_z = (set_fly_limits_zDelegate)FunctionImporter.Import<set_fly_limits_zDelegate>("set_fly_limits_z");
            if_fly_x_overflow = (if_fly_x_overflowDelegate)FunctionImporter.Import<if_fly_x_overflowDelegate>("if_fly_x_overflow");
            if_fly_y_overflow = (if_fly_y_overflowDelegate)FunctionImporter.Import<if_fly_y_overflowDelegate>("if_fly_y_overflow");
            if_fly_z_overflow = (if_fly_z_overflowDelegate)FunctionImporter.Import<if_fly_z_overflowDelegate>("if_fly_z_overflow");
            if_not_fly_x_overflow = (if_not_fly_x_overflowDelegate)FunctionImporter.Import<if_not_fly_x_overflowDelegate>("if_not_fly_x_overflow");
            if_not_fly_y_overflow = (if_not_fly_y_overflowDelegate)FunctionImporter.Import<if_not_fly_y_overflowDelegate>("if_not_fly_y_overflow");
            if_not_fly_z_overflow = (if_not_fly_z_overflowDelegate)FunctionImporter.Import<if_not_fly_z_overflowDelegate>("if_not_fly_z_overflow");
            clear_fly_overflow = (clear_fly_overflowDelegate)FunctionImporter.Import<clear_fly_overflowDelegate>("clear_fly_overflow");
            set_mcbsp_x_list = (set_mcbsp_x_listDelegate)FunctionImporter.Import<set_mcbsp_x_listDelegate>("set_mcbsp_x_list");
            set_mcbsp_y_list = (set_mcbsp_y_listDelegate)FunctionImporter.Import<set_mcbsp_y_listDelegate>("set_mcbsp_y_list");
            set_mcbsp_rot_list = (set_mcbsp_rot_listDelegate)FunctionImporter.Import<set_mcbsp_rot_listDelegate>("set_mcbsp_rot_list");
            set_mcbsp_matrix_list = (set_mcbsp_matrix_listDelegate)FunctionImporter.Import<set_mcbsp_matrix_listDelegate>("set_mcbsp_matrix_list");
            set_mcbsp_global_x_list = (set_mcbsp_global_x_listDelegate)FunctionImporter.Import<set_mcbsp_global_x_listDelegate>("set_mcbsp_global_x_list");
            set_mcbsp_global_y_list = (set_mcbsp_global_y_listDelegate)FunctionImporter.Import<set_mcbsp_global_y_listDelegate>("set_mcbsp_global_y_list");
            set_mcbsp_global_rot_list = (set_mcbsp_global_rot_listDelegate)FunctionImporter.Import<set_mcbsp_global_rot_listDelegate>("set_mcbsp_global_rot_list");
            set_mcbsp_global_matrix_list = (set_mcbsp_global_matrix_listDelegate)FunctionImporter.Import<set_mcbsp_global_matrix_listDelegate>("set_mcbsp_global_matrix_list");
            set_mcbsp_in_list = (set_mcbsp_in_listDelegate)FunctionImporter.Import<set_mcbsp_in_listDelegate>("set_mcbsp_in_list");
            set_multi_mcbsp_in_list = (set_multi_mcbsp_in_listDelegate)FunctionImporter.Import<set_multi_mcbsp_in_listDelegate>("set_multi_mcbsp_in_list");
            wait_for_encoder_mode = (wait_for_encoder_modeDelegate)FunctionImporter.Import<wait_for_encoder_modeDelegate>("wait_for_encoder_mode");
            wait_for_mcbsp = (wait_for_mcbspDelegate)FunctionImporter.Import<wait_for_mcbspDelegate>("wait_for_mcbsp");
            set_encoder_speed = (set_encoder_speedDelegate)FunctionImporter.Import<set_encoder_speedDelegate>("set_encoder_speed");
            get_mcbsp_list = (get_mcbsp_listDelegate)FunctionImporter.Import<get_mcbsp_listDelegate>("get_mcbsp_list");
            store_encoder = (store_encoderDelegate)FunctionImporter.Import<store_encoderDelegate>("store_encoder");
            wait_for_encoder_in_range = (wait_for_encoder_in_rangeDelegate)FunctionImporter.Import<wait_for_encoder_in_rangeDelegate>("wait_for_encoder_in_range");
            activate_fly_xy = (activate_fly_xyDelegate)FunctionImporter.Import<activate_fly_xyDelegate>("activate_fly_xy");
            activate_fly_2d = (activate_fly_2dDelegate)FunctionImporter.Import<activate_fly_2dDelegate>("activate_fly_2d");
            activate_fly_xy_encoder = (activate_fly_xy_encoderDelegate)FunctionImporter.Import<activate_fly_xy_encoderDelegate>("activate_fly_xy_encoder");
            activate_fly_2d_encoder = (activate_fly_2d_encoderDelegate)FunctionImporter.Import<activate_fly_2d_encoderDelegate>("activate_fly_2d_encoder");
            if_not_activated = (if_not_activatedDelegate)FunctionImporter.Import<if_not_activatedDelegate>("if_not_activated");
            park_position = (park_positionDelegate)FunctionImporter.Import<park_positionDelegate>("park_position");
            park_return = (park_returnDelegate)FunctionImporter.Import<park_returnDelegate>("park_return");
            wait_for_encoder = (wait_for_encoderDelegate)FunctionImporter.Import<wait_for_encoderDelegate>("wait_for_encoder");
            n_save_and_restart_timer = (n_save_and_restart_timerDelegate)FunctionImporter.Import<n_save_and_restart_timerDelegate>("n_save_and_restart_timer");
            n_set_wobbel = (n_set_wobbelDelegate)FunctionImporter.Import<n_set_wobbelDelegate>("n_set_wobbel");
            n_set_wobbel_mode = (n_set_wobbel_modeDelegate)FunctionImporter.Import<n_set_wobbel_modeDelegate>("n_set_wobbel_mode");
            n_set_wobbel_mode_phase = (n_set_wobbel_mode_phaseDelegate)FunctionImporter.Import<n_set_wobbel_mode_phaseDelegate>("n_set_wobbel_mode_phase");
            n_set_wobbel_direction = (n_set_wobbel_directionDelegate)FunctionImporter.Import<n_set_wobbel_directionDelegate>("n_set_wobbel_direction");
            n_set_wobbel_control = (n_set_wobbel_controlDelegate)FunctionImporter.Import<n_set_wobbel_controlDelegate>("n_set_wobbel_control");
            n_set_wobbel_vector = (n_set_wobbel_vectorDelegate)FunctionImporter.Import<n_set_wobbel_vectorDelegate>("n_set_wobbel_vector");
            n_set_wobbel_offset = (n_set_wobbel_offsetDelegate)FunctionImporter.Import<n_set_wobbel_offsetDelegate>("n_set_wobbel_offset");
            n_load_wobbel_power_list = (n_load_wobbel_power_listDelegate)FunctionImporter.Import<n_load_wobbel_power_listDelegate>("n_load_wobbel_power_list");
            n_set_wobbel_power_angle = (n_set_wobbel_power_angleDelegate)FunctionImporter.Import<n_set_wobbel_power_angleDelegate>("n_set_wobbel_power_angle");
            n_set_trigger = (n_set_triggerDelegate)FunctionImporter.Import<n_set_triggerDelegate>("n_set_trigger");
            n_set_trigger4 = (n_set_trigger4Delegate)FunctionImporter.Import<n_set_trigger4Delegate>("n_set_trigger4");
            n_set_pixel_line_3d = (n_set_pixel_line_3dDelegate)FunctionImporter.Import<n_set_pixel_line_3dDelegate>("n_set_pixel_line_3d");
            n_set_pixel_line = (n_set_pixel_lineDelegate)FunctionImporter.Import<n_set_pixel_lineDelegate>("n_set_pixel_line");
            n_stretch_pixel_line = (n_stretch_pixel_lineDelegate)FunctionImporter.Import<n_stretch_pixel_lineDelegate>("n_stretch_pixel_line");
            n_set_n_pixel = (n_set_n_pixelDelegate)FunctionImporter.Import<n_set_n_pixelDelegate>("n_set_n_pixel");
            n_set_pixel = (n_set_pixelDelegate)FunctionImporter.Import<n_set_pixelDelegate>("n_set_pixel");
            n_rs232_write_text_list = (n_rs232_write_text_listDelegate)FunctionImporter.Import<n_rs232_write_text_listDelegate>("n_rs232_write_text_list");
            n_set_mcbsp_out = (n_set_mcbsp_outDelegate)FunctionImporter.Import<n_set_mcbsp_outDelegate>("n_set_mcbsp_out");
            n_set_mcbsp_out_ptr_list = (n_set_mcbsp_out_ptr_listDelegate)FunctionImporter.Import<n_set_mcbsp_out_ptr_listDelegate>("n_set_mcbsp_out_ptr_list");
            n_camming = (n_cammingDelegate)FunctionImporter.Import<n_cammingDelegate>("n_camming");
            n_periodic_toggle_list = (n_periodic_toggle_listDelegate)FunctionImporter.Import<n_periodic_toggle_listDelegate>("n_periodic_toggle_list");
            n_micro_vector_abs_3d = (n_micro_vector_abs_3dDelegate)FunctionImporter.Import<n_micro_vector_abs_3dDelegate>("n_micro_vector_abs_3d");
            n_micro_vector_rel_3d = (n_micro_vector_rel_3dDelegate)FunctionImporter.Import<n_micro_vector_rel_3dDelegate>("n_micro_vector_rel_3d");
            n_micro_vector_abs = (n_micro_vector_absDelegate)FunctionImporter.Import<n_micro_vector_absDelegate>("n_micro_vector_abs");
            n_micro_vector_rel = (n_micro_vector_relDelegate)FunctionImporter.Import<n_micro_vector_relDelegate>("n_micro_vector_rel");
            n_set_free_variable_list = (n_set_free_variable_listDelegate)FunctionImporter.Import<n_set_free_variable_listDelegate>("n_set_free_variable_list");
            n_jump_abs_drill_2 = (n_jump_abs_drill_2Delegate)FunctionImporter.Import<n_jump_abs_drill_2Delegate>("n_jump_abs_drill_2");
            n_jump_rel_drill_2 = (n_jump_rel_drill_2Delegate)FunctionImporter.Import<n_jump_rel_drill_2Delegate>("n_jump_rel_drill_2");
            n_jump_abs_drill = (n_jump_abs_drillDelegate)FunctionImporter.Import<n_jump_abs_drillDelegate>("n_jump_abs_drill");
            n_jump_rel_drill = (n_jump_rel_drillDelegate)FunctionImporter.Import<n_jump_rel_drillDelegate>("n_jump_rel_drill");
            save_and_restart_timer = (save_and_restart_timerDelegate)FunctionImporter.Import<save_and_restart_timerDelegate>("save_and_restart_timer");
            set_wobbel = (set_wobbelDelegate)FunctionImporter.Import<set_wobbelDelegate>("set_wobbel");
            set_wobbel_mode = (set_wobbel_modeDelegate)FunctionImporter.Import<set_wobbel_modeDelegate>("set_wobbel_mode");
            set_wobbel_mode_phase = (set_wobbel_mode_phaseDelegate)FunctionImporter.Import<set_wobbel_mode_phaseDelegate>("set_wobbel_mode_phase");
            set_wobbel_direction = (set_wobbel_directionDelegate)FunctionImporter.Import<set_wobbel_directionDelegate>("set_wobbel_direction");
            set_wobbel_control = (set_wobbel_controlDelegate)FunctionImporter.Import<set_wobbel_controlDelegate>("set_wobbel_control");
            set_wobbel_vector = (set_wobbel_vectorDelegate)FunctionImporter.Import<set_wobbel_vectorDelegate>("set_wobbel_vector");
            set_wobbel_offset = (set_wobbel_offsetDelegate)FunctionImporter.Import<set_wobbel_offsetDelegate>("set_wobbel_offset");
            load_wobbel_power_list = (load_wobbel_power_listDelegate)FunctionImporter.Import<load_wobbel_power_listDelegate>("load_wobbel_power_list");
            set_wobbel_power_angle = (set_wobbel_power_angleDelegate)FunctionImporter.Import<set_wobbel_power_angleDelegate>("set_wobbel_power_angle");
            set_trigger = (set_triggerDelegate)FunctionImporter.Import<set_triggerDelegate>("set_trigger");
            set_trigger4 = (set_trigger4Delegate)FunctionImporter.Import<set_trigger4Delegate>("set_trigger4");
            set_pixel_line_3d = (set_pixel_line_3dDelegate)FunctionImporter.Import<set_pixel_line_3dDelegate>("set_pixel_line_3d");
            set_pixel_line = (set_pixel_lineDelegate)FunctionImporter.Import<set_pixel_lineDelegate>("set_pixel_line");
            stretch_pixel_line = (stretch_pixel_lineDelegate)FunctionImporter.Import<stretch_pixel_lineDelegate>("stretch_pixel_line");
            set_n_pixel = (set_n_pixelDelegate)FunctionImporter.Import<set_n_pixelDelegate>("set_n_pixel");
            set_pixel = (set_pixelDelegate)FunctionImporter.Import<set_pixelDelegate>("set_pixel");
            rs232_write_text_list = (rs232_write_text_listDelegate)FunctionImporter.Import<rs232_write_text_listDelegate>("rs232_write_text_list");
            set_mcbsp_out = (set_mcbsp_outDelegate)FunctionImporter.Import<set_mcbsp_outDelegate>("set_mcbsp_out");
            set_mcbsp_out_ptr_list = (set_mcbsp_out_ptr_listDelegate)FunctionImporter.Import<set_mcbsp_out_ptr_listDelegate>("set_mcbsp_out_ptr_list");
            camming = (cammingDelegate)FunctionImporter.Import<cammingDelegate>("camming");
            periodic_toggle_list = (periodic_toggle_listDelegate)FunctionImporter.Import<periodic_toggle_listDelegate>("periodic_toggle_list");
            micro_vector_abs_3d = (micro_vector_abs_3dDelegate)FunctionImporter.Import<micro_vector_abs_3dDelegate>("micro_vector_abs_3d");
            micro_vector_rel_3d = (micro_vector_rel_3dDelegate)FunctionImporter.Import<micro_vector_rel_3dDelegate>("micro_vector_rel_3d");
            micro_vector_abs = (micro_vector_absDelegate)FunctionImporter.Import<micro_vector_absDelegate>("micro_vector_abs");
            micro_vector_rel = (micro_vector_relDelegate)FunctionImporter.Import<micro_vector_relDelegate>("micro_vector_rel");
            set_free_variable_list = (set_free_variable_listDelegate)FunctionImporter.Import<set_free_variable_listDelegate>("set_free_variable_list");
            jump_abs_drill_2 = (jump_abs_drill_2Delegate)FunctionImporter.Import<jump_abs_drill_2Delegate>("jump_abs_drill_2");
            jump_rel_drill_2 = (jump_rel_drill_2Delegate)FunctionImporter.Import<jump_rel_drill_2Delegate>("jump_rel_drill_2");
            jump_abs_drill = (jump_abs_drillDelegate)FunctionImporter.Import<jump_abs_drillDelegate>("jump_abs_drill");
            jump_rel_drill = (jump_rel_drillDelegate)FunctionImporter.Import<jump_rel_drillDelegate>("jump_rel_drill");
            n_timed_mark_abs_3d = (n_timed_mark_abs_3dDelegate)FunctionImporter.Import<n_timed_mark_abs_3dDelegate>("n_timed_mark_abs_3d");
            n_timed_mark_rel_3d = (n_timed_mark_rel_3dDelegate)FunctionImporter.Import<n_timed_mark_rel_3dDelegate>("n_timed_mark_rel_3d");
            n_timed_mark_abs = (n_timed_mark_absDelegate)FunctionImporter.Import<n_timed_mark_absDelegate>("n_timed_mark_abs");
            n_timed_mark_rel = (n_timed_mark_relDelegate)FunctionImporter.Import<n_timed_mark_relDelegate>("n_timed_mark_rel");
            timed_mark_abs_3d = (timed_mark_abs_3dDelegate)FunctionImporter.Import<timed_mark_abs_3dDelegate>("timed_mark_abs_3d");
            timed_mark_rel_3d = (timed_mark_rel_3dDelegate)FunctionImporter.Import<timed_mark_rel_3dDelegate>("timed_mark_rel_3d");
            timed_mark_abs = (timed_mark_absDelegate)FunctionImporter.Import<timed_mark_absDelegate>("timed_mark_abs");
            timed_mark_rel = (timed_mark_relDelegate)FunctionImporter.Import<timed_mark_relDelegate>("timed_mark_rel");
            n_mark_abs_3d = (n_mark_abs_3dDelegate)FunctionImporter.Import<n_mark_abs_3dDelegate>("n_mark_abs_3d");
            n_mark_rel_3d = (n_mark_rel_3dDelegate)FunctionImporter.Import<n_mark_rel_3dDelegate>("n_mark_rel_3d");
            n_mark_abs = (n_mark_absDelegate)FunctionImporter.Import<n_mark_absDelegate>("n_mark_abs");
            n_mark_rel = (n_mark_relDelegate)FunctionImporter.Import<n_mark_relDelegate>("n_mark_rel");
            mark_abs_3d = (mark_abs_3dDelegate)FunctionImporter.Import<mark_abs_3dDelegate>("mark_abs_3d");
            mark_rel_3d = (mark_rel_3dDelegate)FunctionImporter.Import<mark_rel_3dDelegate>("mark_rel_3d");
            mark_abs = (mark_absDelegate)FunctionImporter.Import<mark_absDelegate>("mark_abs");
            mark_rel = (mark_relDelegate)FunctionImporter.Import<mark_relDelegate>("mark_rel");
            n_timed_jump_abs_3d = (n_timed_jump_abs_3dDelegate)FunctionImporter.Import<n_timed_jump_abs_3dDelegate>("n_timed_jump_abs_3d");
            n_timed_jump_rel_3d = (n_timed_jump_rel_3dDelegate)FunctionImporter.Import<n_timed_jump_rel_3dDelegate>("n_timed_jump_rel_3d");
            n_timed_jump_abs = (n_timed_jump_absDelegate)FunctionImporter.Import<n_timed_jump_absDelegate>("n_timed_jump_abs");
            n_timed_jump_rel = (n_timed_jump_relDelegate)FunctionImporter.Import<n_timed_jump_relDelegate>("n_timed_jump_rel");
            timed_jump_abs_3d = (timed_jump_abs_3dDelegate)FunctionImporter.Import<timed_jump_abs_3dDelegate>("timed_jump_abs_3d");
            timed_jump_rel_3d = (timed_jump_rel_3dDelegate)FunctionImporter.Import<timed_jump_rel_3dDelegate>("timed_jump_rel_3d");
            timed_jump_abs = (timed_jump_absDelegate)FunctionImporter.Import<timed_jump_absDelegate>("timed_jump_abs");
            timed_jump_rel = (timed_jump_relDelegate)FunctionImporter.Import<timed_jump_relDelegate>("timed_jump_rel");
            n_jump_abs_3d = (n_jump_abs_3dDelegate)FunctionImporter.Import<n_jump_abs_3dDelegate>("n_jump_abs_3d");
            n_jump_rel_3d = (n_jump_rel_3dDelegate)FunctionImporter.Import<n_jump_rel_3dDelegate>("n_jump_rel_3d");
            n_jump_abs = (n_jump_absDelegate)FunctionImporter.Import<n_jump_absDelegate>("n_jump_abs");
            n_jump_rel = (n_jump_relDelegate)FunctionImporter.Import<n_jump_relDelegate>("n_jump_rel");
            jump_abs_3d = (jump_abs_3dDelegate)FunctionImporter.Import<jump_abs_3dDelegate>("jump_abs_3d");
            jump_rel_3d = (jump_rel_3dDelegate)FunctionImporter.Import<jump_rel_3dDelegate>("jump_rel_3d");
            jump_abs = (jump_absDelegate)FunctionImporter.Import<jump_absDelegate>("jump_abs");
            jump_rel = (jump_relDelegate)FunctionImporter.Import<jump_relDelegate>("jump_rel");
            n_para_mark_abs_3d = (n_para_mark_abs_3dDelegate)FunctionImporter.Import<n_para_mark_abs_3dDelegate>("n_para_mark_abs_3d");
            n_para_mark_rel_3d = (n_para_mark_rel_3dDelegate)FunctionImporter.Import<n_para_mark_rel_3dDelegate>("n_para_mark_rel_3d");
            n_para_mark_abs = (n_para_mark_absDelegate)FunctionImporter.Import<n_para_mark_absDelegate>("n_para_mark_abs");
            n_para_mark_rel = (n_para_mark_relDelegate)FunctionImporter.Import<n_para_mark_relDelegate>("n_para_mark_rel");
            para_mark_abs_3d = (para_mark_abs_3dDelegate)FunctionImporter.Import<para_mark_abs_3dDelegate>("para_mark_abs_3d");
            para_mark_rel_3d = (para_mark_rel_3dDelegate)FunctionImporter.Import<para_mark_rel_3dDelegate>("para_mark_rel_3d");
            para_mark_abs = (para_mark_absDelegate)FunctionImporter.Import<para_mark_absDelegate>("para_mark_abs");
            para_mark_rel = (para_mark_relDelegate)FunctionImporter.Import<para_mark_relDelegate>("para_mark_rel");
            n_para_jump_abs_3d = (n_para_jump_abs_3dDelegate)FunctionImporter.Import<n_para_jump_abs_3dDelegate>("n_para_jump_abs_3d");
            n_para_jump_rel_3d = (n_para_jump_rel_3dDelegate)FunctionImporter.Import<n_para_jump_rel_3dDelegate>("n_para_jump_rel_3d");
            n_para_jump_abs = (n_para_jump_absDelegate)FunctionImporter.Import<n_para_jump_absDelegate>("n_para_jump_abs");
            n_para_jump_rel = (n_para_jump_relDelegate)FunctionImporter.Import<n_para_jump_relDelegate>("n_para_jump_rel");
            para_jump_abs_3d = (para_jump_abs_3dDelegate)FunctionImporter.Import<para_jump_abs_3dDelegate>("para_jump_abs_3d");
            para_jump_rel_3d = (para_jump_rel_3dDelegate)FunctionImporter.Import<para_jump_rel_3dDelegate>("para_jump_rel_3d");
            para_jump_abs = (para_jump_absDelegate)FunctionImporter.Import<para_jump_absDelegate>("para_jump_abs");
            para_jump_rel = (para_jump_relDelegate)FunctionImporter.Import<para_jump_relDelegate>("para_jump_rel");
            n_timed_para_mark_abs_3d = (n_timed_para_mark_abs_3dDelegate)FunctionImporter.Import<n_timed_para_mark_abs_3dDelegate>("n_timed_para_mark_abs_3d");
            n_timed_para_mark_rel_3d = (n_timed_para_mark_rel_3dDelegate)FunctionImporter.Import<n_timed_para_mark_rel_3dDelegate>("n_timed_para_mark_rel_3d");
            n_timed_para_jump_abs_3d = (n_timed_para_jump_abs_3dDelegate)FunctionImporter.Import<n_timed_para_jump_abs_3dDelegate>("n_timed_para_jump_abs_3d");
            n_timed_para_jump_rel_3d = (n_timed_para_jump_rel_3dDelegate)FunctionImporter.Import<n_timed_para_jump_rel_3dDelegate>("n_timed_para_jump_rel_3d");
            n_timed_para_mark_abs = (n_timed_para_mark_absDelegate)FunctionImporter.Import<n_timed_para_mark_absDelegate>("n_timed_para_mark_abs");
            n_timed_para_mark_rel = (n_timed_para_mark_relDelegate)FunctionImporter.Import<n_timed_para_mark_relDelegate>("n_timed_para_mark_rel");
            n_timed_para_jump_abs = (n_timed_para_jump_absDelegate)FunctionImporter.Import<n_timed_para_jump_absDelegate>("n_timed_para_jump_abs");
            n_timed_para_jump_rel = (n_timed_para_jump_relDelegate)FunctionImporter.Import<n_timed_para_jump_relDelegate>("n_timed_para_jump_rel");
            timed_para_mark_abs_3d = (timed_para_mark_abs_3dDelegate)FunctionImporter.Import<timed_para_mark_abs_3dDelegate>("timed_para_mark_abs_3d");
            timed_para_mark_rel_3d = (timed_para_mark_rel_3dDelegate)FunctionImporter.Import<timed_para_mark_rel_3dDelegate>("timed_para_mark_rel_3d");
            timed_para_jump_abs_3d = (timed_para_jump_abs_3dDelegate)FunctionImporter.Import<timed_para_jump_abs_3dDelegate>("timed_para_jump_abs_3d");
            timed_para_jump_rel_3d = (timed_para_jump_rel_3dDelegate)FunctionImporter.Import<timed_para_jump_rel_3dDelegate>("timed_para_jump_rel_3d");
            timed_para_mark_abs = (timed_para_mark_absDelegate)FunctionImporter.Import<timed_para_mark_absDelegate>("timed_para_mark_abs");
            timed_para_mark_rel = (timed_para_mark_relDelegate)FunctionImporter.Import<timed_para_mark_relDelegate>("timed_para_mark_rel");
            timed_para_jump_abs = (timed_para_jump_absDelegate)FunctionImporter.Import<timed_para_jump_absDelegate>("timed_para_jump_abs");
            timed_para_jump_rel = (timed_para_jump_relDelegate)FunctionImporter.Import<timed_para_jump_relDelegate>("timed_para_jump_rel");
            n_set_defocus_list = (n_set_defocus_listDelegate)FunctionImporter.Import<n_set_defocus_listDelegate>("n_set_defocus_list");
            n_set_defocus_offset_list = (n_set_defocus_offset_listDelegate)FunctionImporter.Import<n_set_defocus_offset_listDelegate>("n_set_defocus_offset_list");
            n_set_zoom_list = (n_set_zoom_listDelegate)FunctionImporter.Import<n_set_zoom_listDelegate>("n_set_zoom_list");
            set_defocus_list = (set_defocus_listDelegate)FunctionImporter.Import<set_defocus_listDelegate>("set_defocus_list");
            set_defocus_offset_list = (set_defocus_offset_listDelegate)FunctionImporter.Import<set_defocus_offset_listDelegate>("set_defocus_offset_list");
            set_zoom_list = (set_zoom_listDelegate)FunctionImporter.Import<set_zoom_listDelegate>("set_zoom_list");
            n_timed_arc_abs = (n_timed_arc_absDelegate)FunctionImporter.Import<n_timed_arc_absDelegate>("n_timed_arc_abs");
            n_timed_arc_rel = (n_timed_arc_relDelegate)FunctionImporter.Import<n_timed_arc_relDelegate>("n_timed_arc_rel");
            timed_arc_abs = (timed_arc_absDelegate)FunctionImporter.Import<timed_arc_absDelegate>("timed_arc_abs");
            timed_arc_rel = (timed_arc_relDelegate)FunctionImporter.Import<timed_arc_relDelegate>("timed_arc_rel");
            n_arc_abs_3d = (n_arc_abs_3dDelegate)FunctionImporter.Import<n_arc_abs_3dDelegate>("n_arc_abs_3d");
            n_arc_rel_3d = (n_arc_rel_3dDelegate)FunctionImporter.Import<n_arc_rel_3dDelegate>("n_arc_rel_3d");
            n_arc_abs = (n_arc_absDelegate)FunctionImporter.Import<n_arc_absDelegate>("n_arc_abs");
            n_arc_rel = (n_arc_relDelegate)FunctionImporter.Import<n_arc_relDelegate>("n_arc_rel");
            n_set_ellipse = (n_set_ellipseDelegate)FunctionImporter.Import<n_set_ellipseDelegate>("n_set_ellipse");
            n_mark_ellipse_abs = (n_mark_ellipse_absDelegate)FunctionImporter.Import<n_mark_ellipse_absDelegate>("n_mark_ellipse_abs");
            n_mark_ellipse_rel = (n_mark_ellipse_relDelegate)FunctionImporter.Import<n_mark_ellipse_relDelegate>("n_mark_ellipse_rel");
            arc_abs_3d = (arc_abs_3dDelegate)FunctionImporter.Import<arc_abs_3dDelegate>("arc_abs_3d");
            arc_rel_3d = (arc_rel_3dDelegate)FunctionImporter.Import<arc_rel_3dDelegate>("arc_rel_3d");
            arc_abs = (arc_absDelegate)FunctionImporter.Import<arc_absDelegate>("arc_abs");
            arc_rel = (arc_relDelegate)FunctionImporter.Import<arc_relDelegate>("arc_rel");
            set_ellipse = (set_ellipseDelegate)FunctionImporter.Import<set_ellipseDelegate>("set_ellipse");
            mark_ellipse_abs = (mark_ellipse_absDelegate)FunctionImporter.Import<mark_ellipse_absDelegate>("mark_ellipse_abs");
            mark_ellipse_rel = (mark_ellipse_relDelegate)FunctionImporter.Import<mark_ellipse_relDelegate>("mark_ellipse_rel");
            n_set_offset_xyz_list = (n_set_offset_xyz_listDelegate)FunctionImporter.Import<n_set_offset_xyz_listDelegate>("n_set_offset_xyz_list");
            n_set_offset_list = (n_set_offset_listDelegate)FunctionImporter.Import<n_set_offset_listDelegate>("n_set_offset_list");
            n_set_matrix_list = (n_set_matrix_listDelegate)FunctionImporter.Import<n_set_matrix_listDelegate>("n_set_matrix_list");
            n_set_angle_list = (n_set_angle_listDelegate)FunctionImporter.Import<n_set_angle_listDelegate>("n_set_angle_list");
            n_set_scale_list = (n_set_scale_listDelegate)FunctionImporter.Import<n_set_scale_listDelegate>("n_set_scale_list");
            n_apply_mcbsp_list = (n_apply_mcbsp_listDelegate)FunctionImporter.Import<n_apply_mcbsp_listDelegate>("n_apply_mcbsp_list");
            set_offset_xyz_list = (set_offset_xyz_listDelegate)FunctionImporter.Import<set_offset_xyz_listDelegate>("set_offset_xyz_list");
            set_offset_list = (set_offset_listDelegate)FunctionImporter.Import<set_offset_listDelegate>("set_offset_list");
            set_matrix_list = (set_matrix_listDelegate)FunctionImporter.Import<set_matrix_listDelegate>("set_matrix_list");
            set_angle_list = (set_angle_listDelegate)FunctionImporter.Import<set_angle_listDelegate>("set_angle_list");
            set_scale_list = (set_scale_listDelegate)FunctionImporter.Import<set_scale_listDelegate>("set_scale_list");
            apply_mcbsp_list = (apply_mcbsp_listDelegate)FunctionImporter.Import<apply_mcbsp_listDelegate>("apply_mcbsp_list");
            n_set_mark_speed = (n_set_mark_speedDelegate)FunctionImporter.Import<n_set_mark_speedDelegate>("n_set_mark_speed");
            n_set_jump_speed = (n_set_jump_speedDelegate)FunctionImporter.Import<n_set_jump_speedDelegate>("n_set_jump_speed");
            n_set_sky_writing_para_list = (n_set_sky_writing_para_listDelegate)FunctionImporter.Import<n_set_sky_writing_para_listDelegate>("n_set_sky_writing_para_list");
            n_set_sky_writing_list = (n_set_sky_writing_listDelegate)FunctionImporter.Import<n_set_sky_writing_listDelegate>("n_set_sky_writing_list");
            n_set_sky_writing_limit_list = (n_set_sky_writing_limit_listDelegate)FunctionImporter.Import<n_set_sky_writing_limit_listDelegate>("n_set_sky_writing_limit_list");
            n_set_sky_writing_mode_list = (n_set_sky_writing_mode_listDelegate)FunctionImporter.Import<n_set_sky_writing_mode_listDelegate>("n_set_sky_writing_mode_list");
            n_set_scanner_delays = (n_set_scanner_delaysDelegate)FunctionImporter.Import<n_set_scanner_delaysDelegate>("n_set_scanner_delays");
            n_set_jump_mode_list = (n_set_jump_mode_listDelegate)FunctionImporter.Import<n_set_jump_mode_listDelegate>("n_set_jump_mode_list");
            n_enduring_wobbel = (n_enduring_wobbelDelegate)FunctionImporter.Import<n_enduring_wobbelDelegate>("n_enduring_wobbel");
            n_set_delay_mode_list = (n_set_delay_mode_listDelegate)FunctionImporter.Import<n_set_delay_mode_listDelegate>("n_set_delay_mode_list");
            set_mark_speed = (set_mark_speedDelegate)FunctionImporter.Import<set_mark_speedDelegate>("set_mark_speed");
            set_jump_speed = (set_jump_speedDelegate)FunctionImporter.Import<set_jump_speedDelegate>("set_jump_speed");
            set_sky_writing_para_list = (set_sky_writing_para_listDelegate)FunctionImporter.Import<set_sky_writing_para_listDelegate>("set_sky_writing_para_list");
            set_sky_writing_list = (set_sky_writing_listDelegate)FunctionImporter.Import<set_sky_writing_listDelegate>("set_sky_writing_list");
            set_sky_writing_limit_list = (set_sky_writing_limit_listDelegate)FunctionImporter.Import<set_sky_writing_limit_listDelegate>("set_sky_writing_limit_list");
            set_sky_writing_mode_list = (set_sky_writing_mode_listDelegate)FunctionImporter.Import<set_sky_writing_mode_listDelegate>("set_sky_writing_mode_list");
            set_scanner_delays = (set_scanner_delaysDelegate)FunctionImporter.Import<set_scanner_delaysDelegate>("set_scanner_delays");
            set_jump_mode_list = (set_jump_mode_listDelegate)FunctionImporter.Import<set_jump_mode_listDelegate>("set_jump_mode_list");
            enduring_wobbel = (enduring_wobbelDelegate)FunctionImporter.Import<enduring_wobbelDelegate>("enduring_wobbel");
            set_delay_mode_list = (set_delay_mode_listDelegate)FunctionImporter.Import<set_delay_mode_listDelegate>("set_delay_mode_list");
            n_stepper_enable_list = (n_stepper_enable_listDelegate)FunctionImporter.Import<n_stepper_enable_listDelegate>("n_stepper_enable_list");
            n_stepper_control_list = (n_stepper_control_listDelegate)FunctionImporter.Import<n_stepper_control_listDelegate>("n_stepper_control_list");
            n_stepper_abs_no_list = (n_stepper_abs_no_listDelegate)FunctionImporter.Import<n_stepper_abs_no_listDelegate>("n_stepper_abs_no_list");
            n_stepper_rel_no_list = (n_stepper_rel_no_listDelegate)FunctionImporter.Import<n_stepper_rel_no_listDelegate>("n_stepper_rel_no_list");
            n_stepper_abs_list = (n_stepper_abs_listDelegate)FunctionImporter.Import<n_stepper_abs_listDelegate>("n_stepper_abs_list");
            n_stepper_rel_list = (n_stepper_rel_listDelegate)FunctionImporter.Import<n_stepper_rel_listDelegate>("n_stepper_rel_list");
            n_stepper_wait = (n_stepper_waitDelegate)FunctionImporter.Import<n_stepper_waitDelegate>("n_stepper_wait");
            stepper_enable_list = (stepper_enable_listDelegate)FunctionImporter.Import<stepper_enable_listDelegate>("stepper_enable_list");
            stepper_control_list = (stepper_control_listDelegate)FunctionImporter.Import<stepper_control_listDelegate>("stepper_control_list");
            stepper_abs_no_list = (stepper_abs_no_listDelegate)FunctionImporter.Import<stepper_abs_no_listDelegate>("stepper_abs_no_list");
            stepper_rel_no_list = (stepper_rel_no_listDelegate)FunctionImporter.Import<stepper_rel_no_listDelegate>("stepper_rel_no_list");
            stepper_abs_list = (stepper_abs_listDelegate)FunctionImporter.Import<stepper_abs_listDelegate>("stepper_abs_list");
            stepper_rel_list = (stepper_rel_listDelegate)FunctionImporter.Import<stepper_rel_listDelegate>("stepper_rel_list");
            stepper_wait = (stepper_waitDelegate)FunctionImporter.Import<stepper_waitDelegate>("stepper_wait");
            #endregion
        }
  }
}
