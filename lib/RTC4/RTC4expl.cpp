//-----------------------------------------------------------------------------
//  File: RTC4expl.cpp                            Copyright (c) 2003 SCANLAB AG
//-----------------------------------------------------------------------------
//
//
//
//  Abstract
//      DLL handling functions for explicitly linking to the RTC4DLL.DLL
//
//  Authors
//      Gerald Schmid, Bernhard Schrems
//
//  Revision History
//      +-----+---------+--------+------------------------------------------+
//      | Mod |  Date   | Author | Description                              |
//      +-----+---------+--------+------------------------------------------+
//      | 0.0 | 15Jan01 | GS, BS | * initial release                        |
//      |     |         |        |                                          |
//      +-----+---------+--------+------------------------------------------+
//
//  Function List
//      RTC4open
//      RTC4close
//-----------------------------------------------------------------------------

#include <windows.h>
#include "STDAFX.H"
#include "RTC4expl.h"
#include "math.h"

//  RTC4open
//
//  This function explicitly or dynamically links to the RTC4DLL.DLL.
//  Call it before using any RTC4 function.
//
//      Return      Meaning
//
//       0          Success. Using of the RTC4 functions is possible.
//      -1          Error: file RTC4DLL.DLL not found. The RTC4 functions
//                  cannot be used.
//      -2          Error: file RTC4DLL.DLL is already loaded.


RTC4::RTC4(CWnd* pOwner): CScanner(pOwner)
{
	iMaxBits=65536;
	iMaxListPos=8000;

	if(!Update("GalvoSettings", "Scale", m_Scale, false))
		m_Scale=945.0;
	
	if(!Update("GalvoSettings", "LaserMode", m_lasermode, false))
		m_lasermode=1;
	
	int bVarPolyDelay;
	if(!Update("GalvoSettings", "VarPolyDelay", bVarPolyDelay, false))
		m_bVarPolyDelay=(bool)bVarPolyDelay;
	
	if(!Update("GalvoSettings", "CorFile", m_corfile, false))
		m_corfile="";

	if(!Update("GalvoSettings", "PowerFile", m_powercurvefile, false))
		m_powercurvefile="";

	if(!Update("GalvoSettings", "VarPolyDelayFile", m_varpolyfile, false))
		m_varpolyfile="";
	
	if(!Update("GalvoSettings", "XCor", xcor, false))
		xcor=1.0;
	if(!Update("GalvoSettings", "YCor", ycor, false))
		ycor=1.0;
	
	if(!Update("GalvoSettings", "XOffset", xoffset, false))
		xoffset=0.0;
	if(!Update("GalvoSettings", "YOffset", yoffset, false))
		yoffset=0.0;
	
	if(!Update("GalvoSettings", "Angle", xyrotate, false))
		xyrotate=0.0;	
	
	if(!Update("GalvoSettings", "LoadGap", LoadGap, false))
		LoadGap=10;
	
	if(!Update("GalvoSettings", "RunGap", RunGap, false))
		RunGap=1000;

	gLibRTC=NULL;

	m_State=DEVICE_STATE_NOT_INITIALIZED;
}

RTC4::~RTC4()
{
	Update("GalvoSettings", "Scale", m_Scale, true);
	Update("GalvoSettings", "LaserMode", m_lasermode, true);
	
	Update("GalvoSettings", "CorFile", m_corfile, true);
	Update("GalvoSettings", "PowerFile", m_powercurvefile, true);
	Update("GalvoSettings", "VarPolyDelayFile", m_varpolyfile, true);
	
	Update("GalvoSettings", "XCor", xcor, true);
	Update("GalvoSettings", "YCor", ycor, true);
	
	Update("GalvoSettings", "XOffset", xoffset, true);
	Update("GalvoSettings", "YOffset", yoffset, true);
	
	Update("GalvoSettings", "Angle", xyrotate, true);
	Update("GalvoSettings", "LoadGap", LoadGap, true);
	Update("GalvoSettings", "RunGap", RunGap, true);
	
	int bVarPolyDelay=m_bVarPolyDelay?1:0;;
	
	Update("GalvoSettings", "VarPolyDelay", bVarPolyDelay, true);

	if(gLibRTC!=NULL)
		(void)FreeLibrary(gLibRTC);

	gLibRTC=NULL;	
}

int RTC4::RTC4open(HINSTANCE gLibRTC4)
{
     // Get the addresses of the DLL-Functions
    getmemory = (GETMEMORY) GetProcAddress(gLibRTC4,"getmemory");
    n_get_waveform = (N_GET_WAVEFORM) GetProcAddress(gLibRTC4,"n_get_waveform");
    get_waveform = (GET_WAVEFORM) GetProcAddress(gLibRTC4,"get_waveform");
    n_measurement_status = (N_MEASUREMENT_STATUS) GetProcAddress(gLibRTC4,"n_measurement_status");
    measurement_status = (MEASUREMENT_STATUS) GetProcAddress(gLibRTC4,"measurement_status");
    n_load_varpolydelay = (N_LOAD_VARPOLYDELAY) GetProcAddress(gLibRTC4,"n_load_varpolydelay");
    load_varpolydelay = (LOAD_VARPOLYDELAY) GetProcAddress(gLibRTC4,"load_varpolydelay");
    n_load_program_file = (N_LOAD_PROGRAM_FILE) GetProcAddress(gLibRTC4,"n_load_program_file");
    load_program_file = (LOAD_PROGRAM_FILE) GetProcAddress(gLibRTC4,"load_program_file");
    n_load_correction_file = (N_LOAD_CORRECTION_FILE) GetProcAddress(gLibRTC4,"n_load_correction_file");
    load_correction_file = (LOAD_CORRECTION_FILE) GetProcAddress(gLibRTC4,"load_correction_file");
    n_load_z_table = (N_LOAD_Z_TABLE) GetProcAddress(gLibRTC4,"n_load_z_table");
    load_z_table = (LOAD_Z_TABLE) GetProcAddress(gLibRTC4,"load_z_table");
    n_list_nop = (N_LIST_NOP) GetProcAddress(gLibRTC4,"n_list_nop");
    list_nop = (LIST_NOP) GetProcAddress(gLibRTC4,"list_nop");
    n_set_end_of_list = (N_SET_END_OF_LIST) GetProcAddress(gLibRTC4,"n_set_end_of_list");
    set_end_of_list = (SET_END_OF_LIST) GetProcAddress(gLibRTC4,"set_end_of_list");
    n_jump_abs_3d = (N_JUMP_ABS_3D) GetProcAddress(gLibRTC4,"n_jump_abs_3d");
    jump_abs_3d = (JUMP_ABS_3D) GetProcAddress(gLibRTC4,"jump_abs_3d");
    n_jump_abs = (N_JUMP_ABS) GetProcAddress(gLibRTC4,"n_jump_abs");
    jump_abs = (JUMP_ABS) GetProcAddress(gLibRTC4,"jump_abs");
    n_mark_abs_3d = (N_MARK_ABS_3D) GetProcAddress(gLibRTC4,"n_mark_abs_3d");
    mark_abs_3d = (MARK_ABS_3D) GetProcAddress(gLibRTC4,"mark_abs_3d");
    n_mark_abs = (N_MARK_ABS) GetProcAddress(gLibRTC4,"n_mark_abs");
    mark_abs = (MARK_ABS) GetProcAddress(gLibRTC4,"mark_abs");
    n_jump_rel_3d = (N_JUMP_REL_3D) GetProcAddress(gLibRTC4,"n_jump_rel_3d");
    jump_rel_3d = (JUMP_REL_3D) GetProcAddress(gLibRTC4,"jump_rel_3d");
    n_jump_rel = (N_JUMP_REL) GetProcAddress(gLibRTC4,"n_jump_rel");
    jump_rel = (JUMP_REL) GetProcAddress(gLibRTC4,"jump_rel");
    n_mark_rel_3d = (N_MARK_REL_3D) GetProcAddress(gLibRTC4,"n_mark_rel_3d");
    mark_rel_3d = (MARK_REL_3D) GetProcAddress(gLibRTC4,"mark_rel_3d");
    n_mark_rel = (N_MARK_REL) GetProcAddress(gLibRTC4,"n_mark_rel");
    mark_rel = (MARK_REL) GetProcAddress(gLibRTC4,"mark_rel");
    n_write_8bit_port_list = (N_WRITE_8BIT_PORT_LIST) GetProcAddress(gLibRTC4,"n_write_8bit_port_list");
    write_8bit_port_list = (WRITE_8BIT_PORT_LIST) GetProcAddress(gLibRTC4,"write_8bit_port_list");
    n_write_da_1_list = (N_WRITE_DA_1_LIST) GetProcAddress(gLibRTC4,"n_write_da_1_list");
    write_da_1_list = (WRITE_DA_1_LIST) GetProcAddress(gLibRTC4,"write_da_1_list");
    n_write_da_2_list = (N_WRITE_DA_2_LIST) GetProcAddress(gLibRTC4,"n_write_da_2_list");
    write_da_2_list = (WRITE_DA_2_LIST) GetProcAddress(gLibRTC4,"write_da_2_list");
    n_set_matrix_list = (N_SET_MATRIX_LIST) GetProcAddress(gLibRTC4,"n_set_matrix_list");
    set_matrix_list = (SET_MATRIX_LIST) GetProcAddress(gLibRTC4,"set_matrix_list");
    n_set_defocus_list = (N_SET_DEFOCUS_LIST) GetProcAddress(gLibRTC4,"n_set_defocus_list");
    set_defocus_list = (SET_DEFOCUS_LIST) GetProcAddress(gLibRTC4,"set_defocus_list");
    n_set_control_mode_list = (N_SET_CONTROL_MODE_LIST) GetProcAddress(gLibRTC4,"n_set_control_mode_list");
    set_control_mode_list = (SET_CONTROL_MODE_LIST) GetProcAddress(gLibRTC4,"set_control_mode_list");
    n_set_offset_list = (N_SET_OFFSET_LIST) GetProcAddress(gLibRTC4,"n_set_offset_list");
    set_offset_list = (SET_OFFSET_LIST) GetProcAddress(gLibRTC4,"set_offset_list");
    n_long_delay = (N_LONG_DELAY) GetProcAddress(gLibRTC4,"n_long_delay");
    long_delay = (LONG_DELAY) GetProcAddress(gLibRTC4,"long_delay");
    n_laser_on_list = (N_LASER_ON_LIST) GetProcAddress(gLibRTC4,"n_laser_on_list");
    laser_on_list = (LASER_ON_LIST) GetProcAddress(gLibRTC4,"laser_on_list");
    n_set_jump_speed = (N_SET_JUMP_SPEED) GetProcAddress(gLibRTC4,"n_set_jump_speed");
    set_jump_speed = (SET_JUMP_SPEED) GetProcAddress(gLibRTC4,"set_jump_speed");
    n_set_mark_speed = (N_SET_MARK_SPEED) GetProcAddress(gLibRTC4,"n_set_mark_speed");
    set_mark_speed = (SET_MARK_SPEED) GetProcAddress(gLibRTC4,"set_mark_speed");
    n_set_laser_delays = (N_SET_LASER_DELAYS) GetProcAddress(gLibRTC4,"n_set_laser_delays");
    set_laser_delays = (SET_LASER_DELAYS) GetProcAddress(gLibRTC4,"set_laser_delays");
    n_set_scanner_delays = (N_SET_SCANNER_DELAYS) GetProcAddress(gLibRTC4,"n_set_scanner_delays");
    set_scanner_delays = (SET_SCANNER_DELAYS) GetProcAddress(gLibRTC4,"set_scanner_delays");
    n_set_list_jump = (N_SET_LIST_JUMP) GetProcAddress(gLibRTC4,"n_set_list_jump");
    set_list_jump = (SET_LIST_JUMP) GetProcAddress(gLibRTC4,"set_list_jump");
    n_set_input_pointer = (N_SET_INPUT_POINTER) GetProcAddress(gLibRTC4,"n_set_input_pointer");
    set_input_pointer = (SET_INPUT_POINTER) GetProcAddress(gLibRTC4,"set_input_pointer");
    n_list_call = (N_LIST_CALL) GetProcAddress(gLibRTC4,"n_list_call");
    list_call = (LIST_CALL) GetProcAddress(gLibRTC4,"list_call");
    n_list_return = (N_LIST_RETURN) GetProcAddress(gLibRTC4,"n_list_return");
    list_return = (LIST_RETURN) GetProcAddress(gLibRTC4,"list_return");
    n_z_out_list = (N_Z_OUT_LIST) GetProcAddress(gLibRTC4,"n_z_out_list");
    z_out_list = (Z_OUT_LIST) GetProcAddress(gLibRTC4,"z_out_list");
    n_set_standby_list = (N_SET_STANDBY_LIST) GetProcAddress(gLibRTC4,"n_set_standby_list");
    set_standby_list = (SET_STANDBY_LIST) GetProcAddress(gLibRTC4,"set_standby_list");
    n_timed_jump_abs = (N_TIMED_JUMP_ABS) GetProcAddress(gLibRTC4,"n_timed_jump_abs");
    timed_jump_abs = (TIMED_JUMP_ABS) GetProcAddress(gLibRTC4,"timed_jump_abs");
    n_timed_mark_abs = (N_TIMED_MARK_ABS) GetProcAddress(gLibRTC4,"n_timed_mark_abs");
    timed_mark_abs = (TIMED_MARK_ABS) GetProcAddress(gLibRTC4,"timed_mark_abs");
    n_timed_jump_rel = (N_TIMED_JUMP_REL) GetProcAddress(gLibRTC4,"n_timed_jump_rel");
    timed_jump_rel = (TIMED_JUMP_REL) GetProcAddress(gLibRTC4,"timed_jump_rel");
    n_timed_mark_rel = (N_TIMED_MARK_REL) GetProcAddress(gLibRTC4,"n_timed_mark_rel");
    timed_mark_rel = (TIMED_MARK_REL) GetProcAddress(gLibRTC4,"timed_mark_rel");
    n_set_laser_timing = (N_SET_LASER_TIMING) GetProcAddress(gLibRTC4,"n_set_laser_timing");
    set_laser_timing = (SET_LASER_TIMING) GetProcAddress(gLibRTC4,"set_laser_timing");
    n_set_wobbel_xy = (N_SET_WOBBEL_XY) GetProcAddress(gLibRTC4,"n_set_wobbel_xy");
    set_wobbel_xy = (SET_WOBBEL_XY) GetProcAddress(gLibRTC4,"set_wobbel_xy");
    n_set_wobbel = (N_SET_WOBBEL) GetProcAddress(gLibRTC4,"n_set_wobbel");
    set_wobbel = (SET_WOBBEL) GetProcAddress(gLibRTC4,"set_wobbel");
    n_set_fly_x = (N_SET_FLY_X) GetProcAddress(gLibRTC4,"n_set_fly_x");
    set_fly_x = (SET_FLY_X) GetProcAddress(gLibRTC4,"set_fly_x");
    n_set_fly_y = (N_SET_FLY_Y) GetProcAddress(gLibRTC4,"n_set_fly_y");
    set_fly_y = (SET_FLY_Y) GetProcAddress(gLibRTC4,"set_fly_y");
    n_set_fly_rot = (N_SET_FLY_ROT) GetProcAddress(gLibRTC4,"n_set_fly_rot");
    set_fly_rot = (SET_FLY_ROT) GetProcAddress(gLibRTC4,"set_fly_rot");
    n_fly_return = (N_FLY_RETURN) GetProcAddress(gLibRTC4,"n_fly_return");
    fly_return = (FLY_RETURN) GetProcAddress(gLibRTC4,"fly_return");
    n_calculate_fly = (N_CALCULATE_FLY) GetProcAddress(gLibRTC4,"n_calculate_fly");
    calculate_fly = (CALCULATE_FLY) GetProcAddress(gLibRTC4,"calculate_fly");
    n_write_io_port_list = (N_WRITE_IO_PORT_LIST) GetProcAddress(gLibRTC4,"n_write_io_port_list");
    write_io_port_list = (WRITE_IO_PORT_LIST) GetProcAddress(gLibRTC4,"write_io_port_list");
    n_select_cor_table_list = (N_SELECT_COR_TABLE_LIST) GetProcAddress(gLibRTC4,"n_select_cor_table_list");
    select_cor_table_list = (SELECT_COR_TABLE_LIST) GetProcAddress(gLibRTC4,"select_cor_table_list");
    n_set_wait = (N_SET_WAIT) GetProcAddress(gLibRTC4,"n_set_wait");
    set_wait = (SET_WAIT) GetProcAddress(gLibRTC4,"set_wait");
    n_simulate_ext_start = (N_SIMULATE_EXT_START) GetProcAddress(gLibRTC4,"n_simulate_ext_start");
    simulate_ext_start = (SIMULATE_EXT_START) GetProcAddress(gLibRTC4,"simulate_ext_start");
    n_write_da_x_list = (N_WRITE_DA_X_LIST) GetProcAddress(gLibRTC4,"n_write_da_x_list");
    write_da_x_list = (WRITE_DA_X_LIST) GetProcAddress(gLibRTC4,"write_da_x_list");
    n_set_pixel_line = (N_SET_PIXEL_LINE) GetProcAddress(gLibRTC4,"n_set_pixel_line");
    set_pixel_line = (SET_PIXEL_LINE) GetProcAddress(gLibRTC4,"set_pixel_line");
    n_set_pixel = (N_SET_PIXEL) GetProcAddress(gLibRTC4,"n_set_pixel");
    set_pixel = (SET_PIXEL) GetProcAddress(gLibRTC4,"set_pixel");
    n_set_extstartpos_list = (N_SET_EXTSTARTPOS_LIST) GetProcAddress(gLibRTC4,"n_set_extstartpos_list");
    set_extstartpos_list = (SET_EXTSTARTPOS_LIST) GetProcAddress(gLibRTC4,"set_extstartpos_list");
    n_laser_signal_on_list = (N_LASER_SIGNAL_ON_LIST) GetProcAddress(gLibRTC4,"n_laser_signal_on_list");
    laser_signal_on_list = (LASER_SIGNAL_ON_LIST) GetProcAddress(gLibRTC4,"laser_signal_on_list");
    n_laser_signal_off_list = (N_LASER_SIGNAL_OFF_LIST) GetProcAddress(gLibRTC4,"n_laser_signal_off_list");
    laser_signal_off_list = (LASER_SIGNAL_OFF_LIST) GetProcAddress(gLibRTC4,"laser_signal_off_list");
    n_set_firstpulse_killer_list = (N_SET_FIRSTPULSE_KILLER_LIST) GetProcAddress(gLibRTC4,"n_set_firstpulse_killer_list");
    set_firstpulse_killer_list = (SET_FIRSTPULSE_KILLER_LIST) GetProcAddress(gLibRTC4,"set_firstpulse_killer_list");
    n_set_io_cond_list = (N_SET_IO_COND_LIST) GetProcAddress(gLibRTC4,"n_set_io_cond_list");
    set_io_cond_list = (SET_IO_COND_LIST) GetProcAddress(gLibRTC4,"set_io_cond_list");
    n_clear_io_cond_list = (N_CLEAR_IO_COND_LIST) GetProcAddress(gLibRTC4,"n_clear_io_cond_list");
    clear_io_cond_list = (CLEAR_IO_COND_LIST) GetProcAddress(gLibRTC4,"clear_io_cond_list");
    n_list_jump_cond = (N_LIST_JUMP_COND) GetProcAddress(gLibRTC4,"n_list_jump_cond");
    list_jump_cond = (LIST_JUMP_COND) GetProcAddress(gLibRTC4,"list_jump_cond");
    n_list_call_cond = (N_LIST_CALL_COND) GetProcAddress(gLibRTC4,"n_list_call_cond");
    list_call_cond = (LIST_CALL_COND) GetProcAddress(gLibRTC4,"list_call_cond");
    n_save_and_restart_timer = (N_SAVE_AND_RESTART_TIMER) GetProcAddress(gLibRTC4,"n_save_and_restart_timer");
    save_and_restart_timer = (SAVE_AND_RESTART_TIMER) GetProcAddress(gLibRTC4,"save_and_restart_timer");
    n_set_ext_start_delay_list = (N_SET_EXT_START_DELAY_LIST) GetProcAddress(gLibRTC4,"n_set_ext_start_delay_list");
    set_ext_start_delay_list = (SET_EXT_START_DELAY_LIST) GetProcAddress(gLibRTC4,"set_ext_start_delay_list");
    n_set_trigger = (N_SET_TRIGGER) GetProcAddress(gLibRTC4,"n_set_trigger");
    set_trigger = (SET_TRIGGER) GetProcAddress(gLibRTC4,"set_trigger");
    n_arc_rel = (N_ARC_REL) GetProcAddress(gLibRTC4,"n_arc_rel");
    arc_rel = (ARC_REL) GetProcAddress(gLibRTC4,"arc_rel");
    n_arc_abs = (N_ARC_ABS) GetProcAddress(gLibRTC4,"n_arc_abs");
    arc_abs = (ARC_ABS) GetProcAddress(gLibRTC4,"arc_abs");
    drilling = (DRILLING) GetProcAddress(gLibRTC4,"drilling");
    regulation = (REGULATION) GetProcAddress(gLibRTC4,"regulation");
    flyline = (FLYLINE) GetProcAddress(gLibRTC4,"flyline");
    n_get_input_pointer = (N_GET_INPUT_POINTER) GetProcAddress(gLibRTC4,"n_get_input_pointer");
    get_input_pointer = (GET_INPUT_POINTER) GetProcAddress(gLibRTC4,"get_input_pointer");
    select_rtc = (SELECT_RTC) GetProcAddress(gLibRTC4,"select_rtc");
    rtc4_count_cards = (RTC4_COUNT_CARDS) GetProcAddress(gLibRTC4,"rtc4_count_cards");
    n_get_status = (N_GET_STATUS) GetProcAddress(gLibRTC4,"n_get_status");
    get_status = (GET_STATUS) GetProcAddress(gLibRTC4,"get_status");
    n_read_status = (N_READ_STATUS) GetProcAddress(gLibRTC4,"n_read_status");
    read_status = (READ_STATUS) GetProcAddress(gLibRTC4,"read_status");
    n_get_startstop_info = (N_GET_STARTSTOP_INFO) GetProcAddress(gLibRTC4,"n_get_startstop_info");
    get_startstop_info = (GET_STARTSTOP_INFO) GetProcAddress(gLibRTC4,"get_startstop_info");
    n_get_marking_info = (N_GET_MARKING_INFO) GetProcAddress(gLibRTC4,"n_get_marking_info");
    get_marking_info = (GET_MARKING_INFO) GetProcAddress(gLibRTC4,"get_marking_info");
    get_dll_version = (GET_DLL_VERSION) GetProcAddress(gLibRTC4,"get_dll_version");
    n_set_start_list_1 = (N_SET_START_LIST_1) GetProcAddress(gLibRTC4,"n_set_start_list_1");
    set_start_list_1 = (SET_START_LIST_1) GetProcAddress(gLibRTC4,"set_start_list_1");
    n_set_start_list_2 = (N_SET_START_LIST_2) GetProcAddress(gLibRTC4,"n_set_start_list_2");
    set_start_list_2 = (SET_START_LIST_2) GetProcAddress(gLibRTC4,"set_start_list_2");
    n_set_start_list = (N_SET_START_LIST) GetProcAddress(gLibRTC4,"n_set_start_list");
    set_start_list = (SET_START_LIST) GetProcAddress(gLibRTC4,"set_start_list");
    n_execute_list_1 = (N_EXECUTE_LIST_1) GetProcAddress(gLibRTC4,"n_execute_list_1");
    execute_list_1 = (EXECUTE_LIST_1) GetProcAddress(gLibRTC4,"execute_list_1");
    n_execute_list_2 = (N_EXECUTE_LIST_2) GetProcAddress(gLibRTC4,"n_execute_list_2");
    execute_list_2 = (EXECUTE_LIST_2) GetProcAddress(gLibRTC4,"execute_list_2");
    n_execute_list = (N_EXECUTE_LIST) GetProcAddress(gLibRTC4,"n_execute_list");
    execute_list = (EXECUTE_LIST) GetProcAddress(gLibRTC4,"execute_list");
    n_write_8bit_port = (N_WRITE_8BIT_PORT) GetProcAddress(gLibRTC4,"n_write_8bit_port");
    write_8bit_port = (WRITE_8BIT_PORT) GetProcAddress(gLibRTC4,"write_8bit_port");
    n_write_io_port = (N_WRITE_IO_PORT) GetProcAddress(gLibRTC4,"n_write_io_port");
    write_io_port = (WRITE_IO_PORT) GetProcAddress(gLibRTC4,"write_io_port");
    n_auto_change = (N_AUTO_CHANGE) GetProcAddress(gLibRTC4,"n_auto_change");
    auto_change = (AUTO_CHANGE) GetProcAddress(gLibRTC4,"auto_change");
    n_auto_change_pos = (N_AUTO_CHANGE_POS) GetProcAddress(gLibRTC4,"n_auto_change_pos");
    auto_change_pos = (AUTO_CHANGE_POS) GetProcAddress(gLibRTC4,"auto_change_pos");
    aut_change = (AUT_CHANGE) GetProcAddress(gLibRTC4,"aut_change");
    n_start_loop = (N_START_LOOP) GetProcAddress(gLibRTC4,"n_start_loop");
    start_loop = (START_LOOP) GetProcAddress(gLibRTC4,"start_loop");
    n_quit_loop = (N_QUIT_LOOP) GetProcAddress(gLibRTC4,"n_quit_loop");
    quit_loop = (QUIT_LOOP) GetProcAddress(gLibRTC4,"quit_loop");
    n_set_list_mode = (N_SET_LIST_MODE) GetProcAddress(gLibRTC4,"n_set_list_mode");
    set_list_mode = (SET_LIST_MODE) GetProcAddress(gLibRTC4,"set_list_mode");
    n_stop_execution = (N_STOP_EXECUTION) GetProcAddress(gLibRTC4,"n_stop_execution");
    stop_execution = (STOP_EXECUTION) GetProcAddress(gLibRTC4,"stop_execution");
    n_read_io_port = (N_READ_IO_PORT) GetProcAddress(gLibRTC4,"n_read_io_port");
    read_io_port = (READ_IO_PORT) GetProcAddress(gLibRTC4,"read_io_port");
    n_write_da_1 = (N_WRITE_DA_1) GetProcAddress(gLibRTC4,"n_write_da_1");
    write_da_1 = (WRITE_DA_1) GetProcAddress(gLibRTC4,"write_da_1");
    n_write_da_2 = (N_WRITE_DA_2) GetProcAddress(gLibRTC4,"n_write_da_2");
    write_da_2 = (WRITE_DA_2) GetProcAddress(gLibRTC4,"write_da_2");
    n_set_max_counts = (N_SET_MAX_COUNTS) GetProcAddress(gLibRTC4,"n_set_max_counts");
    set_max_counts = (SET_MAX_COUNTS) GetProcAddress(gLibRTC4,"set_max_counts");
    n_get_counts = (N_GET_COUNTS) GetProcAddress(gLibRTC4,"n_get_counts");
    get_counts = (GET_COUNTS) GetProcAddress(gLibRTC4,"get_counts");
    n_set_matrix = (N_SET_MATRIX) GetProcAddress(gLibRTC4,"n_set_matrix");
    set_matrix = (SET_MATRIX) GetProcAddress(gLibRTC4,"set_matrix");
    n_set_offset = (N_SET_OFFSET) GetProcAddress(gLibRTC4,"n_set_offset");
    set_offset = (SET_OFFSET) GetProcAddress(gLibRTC4,"set_offset");
    n_goto_xyz = (N_GOTO_XYZ) GetProcAddress(gLibRTC4,"n_goto_xyz");
    goto_xyz = (GOTO_XYZ) GetProcAddress(gLibRTC4,"goto_xyz");
    n_goto_xy = (N_GOTO_XY) GetProcAddress(gLibRTC4,"n_goto_xy");
    goto_xy = (GOTO_XY) GetProcAddress(gLibRTC4,"goto_xy");
    n_get_hex_version = (N_GET_HEX_VERSION) GetProcAddress(gLibRTC4,"n_get_hex_version");
    get_hex_version = (GET_HEX_VERSION) GetProcAddress(gLibRTC4,"get_hex_version");
    n_disable_laser = (N_DISABLE_LASER) GetProcAddress(gLibRTC4,"n_disable_laser");
    disable_laser = (DISABLE_LASER) GetProcAddress(gLibRTC4,"disable_laser");
    n_enable_laser = (N_ENABLE_LASER) GetProcAddress(gLibRTC4,"n_enable_laser");
    enable_laser = (ENABLE_LASER) GetProcAddress(gLibRTC4,"enable_laser");
    n_stop_list = (N_STOP_LIST) GetProcAddress(gLibRTC4,"n_stop_list");
    stop_list = (STOP_LIST) GetProcAddress(gLibRTC4,"stop_list");
    n_restart_list = (N_RESTART_LIST) GetProcAddress(gLibRTC4,"n_restart_list");
    restart_list = (RESTART_LIST) GetProcAddress(gLibRTC4,"restart_list");
    n_get_xyz_pos = (N_GET_XYZ_POS) GetProcAddress(gLibRTC4,"n_get_xyz_pos");
    get_xyz_pos = (GET_XYZ_POS) GetProcAddress(gLibRTC4,"get_xyz_pos");
    n_get_xy_pos = (N_GET_XY_POS) GetProcAddress(gLibRTC4,"n_get_xy_pos");
    get_xy_pos = (GET_XY_POS) GetProcAddress(gLibRTC4,"get_xy_pos");
    n_select_list = (N_SELECT_LIST) GetProcAddress(gLibRTC4,"n_select_list");
    select_list = (SELECT_LIST) GetProcAddress(gLibRTC4,"select_list");
    n_z_out = (N_Z_OUT) GetProcAddress(gLibRTC4,"n_z_out");
    z_out = (Z_OUT) GetProcAddress(gLibRTC4,"z_out");
    n_set_firstpulse_killer = (N_SET_FIRSTPULSE_KILLER) GetProcAddress(gLibRTC4,"n_set_firstpulse_killer");
    set_firstpulse_killer = (SET_FIRSTPULSE_KILLER) GetProcAddress(gLibRTC4,"set_firstpulse_killer");
    n_set_standby = (N_SET_STANDBY) GetProcAddress(gLibRTC4,"n_set_standby");
    set_standby = (SET_STANDBY) GetProcAddress(gLibRTC4,"set_standby");
    n_laser_signal_on = (N_LASER_SIGNAL_ON) GetProcAddress(gLibRTC4,"n_laser_signal_on");
    laser_signal_on = (LASER_SIGNAL_ON) GetProcAddress(gLibRTC4,"laser_signal_on");
    n_laser_signal_off = (N_LASER_SIGNAL_OFF) GetProcAddress(gLibRTC4,"n_laser_signal_off");
    laser_signal_off = (LASER_SIGNAL_OFF) GetProcAddress(gLibRTC4,"laser_signal_off");
    n_set_delay_mode = (N_SET_DELAY_MODE) GetProcAddress(gLibRTC4,"n_set_delay_mode");
    set_delay_mode = (SET_DELAY_MODE) GetProcAddress(gLibRTC4,"set_delay_mode");
    n_set_piso_control = (N_SET_PISO_CONTROL) GetProcAddress(gLibRTC4,"n_set_piso_control");
    set_piso_control = (SET_PISO_CONTROL) GetProcAddress(gLibRTC4,"set_piso_control");
    n_select_status = (N_SELECT_STATUS) GetProcAddress(gLibRTC4,"n_select_status");
    select_status = (SELECT_STATUS) GetProcAddress(gLibRTC4,"select_status");
    n_get_encoder = (N_GET_ENCODER) GetProcAddress(gLibRTC4,"n_get_encoder");
    get_encoder = (GET_ENCODER) GetProcAddress(gLibRTC4,"get_encoder");
    n_select_cor_table = (N_SELECT_COR_TABLE) GetProcAddress(gLibRTC4,"n_select_cor_table");
    select_cor_table = (SELECT_COR_TABLE) GetProcAddress(gLibRTC4,"select_cor_table");
    n_execute_at_pointer = (N_EXECUTE_AT_POINTER) GetProcAddress(gLibRTC4,"n_execute_at_pointer");
    execute_at_pointer = (EXECUTE_AT_POINTER) GetProcAddress(gLibRTC4,"execute_at_pointer");
    n_get_head_status = (N_GET_HEAD_STATUS) GetProcAddress(gLibRTC4,"n_get_head_status");
    get_head_status = (GET_HEAD_STATUS) GetProcAddress(gLibRTC4,"get_head_status");
    n_simulate_encoder = (N_SIMULATE_ENCODER) GetProcAddress(gLibRTC4,"n_simulate_encoder");
    simulate_encoder = (SIMULATE_ENCODER) GetProcAddress(gLibRTC4,"simulate_encoder");
    n_set_hi = (N_SET_HI) GetProcAddress(gLibRTC4,"n_set_hi");
    set_hi = (SET_HI) GetProcAddress(gLibRTC4,"set_hi");
    n_release_wait = (N_RELEASE_WAIT) GetProcAddress(gLibRTC4,"n_release_wait");
    release_wait = (RELEASE_WAIT) GetProcAddress(gLibRTC4,"release_wait");
    n_get_wait_status = (N_GET_WAIT_STATUS) GetProcAddress(gLibRTC4,"n_get_wait_status");
    get_wait_status = (GET_WAIT_STATUS) GetProcAddress(gLibRTC4,"get_wait_status");
    n_set_control_mode = (N_SET_CONTROL_MODE) GetProcAddress(gLibRTC4,"n_set_control_mode");
    set_control_mode = (SET_CONTROL_MODE) GetProcAddress(gLibRTC4,"set_control_mode");
    n_set_laser_mode = (N_SET_LASER_MODE) GetProcAddress(gLibRTC4,"n_set_laser_mode");
    set_laser_mode = (SET_LASER_MODE) GetProcAddress(gLibRTC4,"set_laser_mode");
    n_set_ext_start_delay = (N_SET_EXT_START_DELAY) GetProcAddress(gLibRTC4,"n_set_ext_start_delay");
    set_ext_start_delay = (SET_EXT_START_DELAY) GetProcAddress(gLibRTC4,"set_ext_start_delay");
    n_home_position = (N_HOME_POSITION) GetProcAddress(gLibRTC4,"n_home_position");
    home_position = (HOME_POSITION) GetProcAddress(gLibRTC4,"home_position");
    n_set_rot_center = (N_SET_ROT_CENTER) GetProcAddress(gLibRTC4,"n_set_rot_center");
    set_rot_center = (SET_ROT_CENTER) GetProcAddress(gLibRTC4,"set_rot_center");
    n_dsp_start = (N_DSP_START) GetProcAddress(gLibRTC4,"n_dsp_start");
    dsp_start = (DSP_START) GetProcAddress(gLibRTC4,"dsp_start");
    n_write_da_x = (N_WRITE_DA_X) GetProcAddress(gLibRTC4,"n_write_da_x");
    write_da_x = (WRITE_DA_X) GetProcAddress(gLibRTC4,"write_da_x");
    n_read_ad_x = (N_READ_AD_X) GetProcAddress(gLibRTC4,"n_read_ad_x");
    read_ad_x = (READ_AD_X) GetProcAddress(gLibRTC4,"read_ad_x");
    n_read_pixel_ad = (N_READ_PIXEL_AD) GetProcAddress(gLibRTC4,"n_read_pixel_ad");
    read_pixel_ad = (READ_PIXEL_AD) GetProcAddress(gLibRTC4,"read_pixel_ad");
    n_get_z_distance = (N_GET_Z_DISTANCE) GetProcAddress(gLibRTC4,"n_get_z_distance");
    get_z_distance = (GET_Z_DISTANCE) GetProcAddress(gLibRTC4,"get_z_distance");
    n_get_io_status = (N_GET_IO_STATUS) GetProcAddress(gLibRTC4,"n_get_io_status");
    get_io_status = (GET_IO_STATUS) GetProcAddress(gLibRTC4,"get_io_status");
    n_get_time = (N_GET_TIME) GetProcAddress(gLibRTC4,"n_get_time");
    get_time = (GET_TIME) GetProcAddress(gLibRTC4,"get_time");
    n_set_defocus = (N_SET_DEFOCUS) GetProcAddress(gLibRTC4,"n_set_defocus");
    set_defocus = (SET_DEFOCUS) GetProcAddress(gLibRTC4,"set_defocus");
    n_set_softstart_mode = (N_SET_SOFTSTART_MODE) GetProcAddress(gLibRTC4,"n_set_softstart_mode");
    set_softstart_mode = (SET_SOFTSTART_MODE) GetProcAddress(gLibRTC4,"set_softstart_mode");
    n_set_softstart_level = (N_SET_SOFTSTART_LEVEL) GetProcAddress(gLibRTC4,"n_set_softstart_level");
    set_softstart_level = (SET_SOFTSTART_LEVEL) GetProcAddress(gLibRTC4,"set_softstart_level");
    n_control_command = (N_CONTROL_COMMAND) GetProcAddress(gLibRTC4,"n_control_command");
    control_command = (CONTROL_COMMAND) GetProcAddress(gLibRTC4,"control_command");
    load_cor = (LOAD_COR) GetProcAddress(gLibRTC4,"load_cor");
    load_pro = (LOAD_PRO) GetProcAddress(gLibRTC4,"load_pro");
    n_get_serial_number = (N_GET_SERIAL_NUMBER) GetProcAddress(gLibRTC4,"n_get_serial_number");
    get_serial_number = (GET_SERIAL_NUMBER) GetProcAddress(gLibRTC4,"get_serial_number");
    n_get_rtc_version = (N_GET_RTC_VERSION) GetProcAddress(gLibRTC4,"n_get_rtc_version");
    get_rtc_version = (GET_RTC_VERSION) GetProcAddress(gLibRTC4,"get_rtc_version");
    get_hi_data = (GET_HI_DATA) GetProcAddress(gLibRTC4,"get_hi_data");
    n_auto_cal = (N_AUTO_CAL) GetProcAddress(gLibRTC4,"n_auto_cal");
    auto_cal = (AUTO_CAL) GetProcAddress(gLibRTC4,"auto_cal");
    n_get_list_space = (N_GET_LIST_SPACE) GetProcAddress(gLibRTC4,"n_get_list_space");
    get_list_space = (GET_LIST_SPACE) GetProcAddress(gLibRTC4,"get_list_space");
    teachin = (TEACHIN) GetProcAddress(gLibRTC4,"teachin");
    n_get_value = (N_GET_VALUE) GetProcAddress(gLibRTC4,"n_get_value");
    get_value = (GET_VALUE) GetProcAddress(gLibRTC4,"get_value");
    n_set_io_bit = (N_SET_IO_BIT) GetProcAddress(gLibRTC4,"n_set_io_bit");
    set_io_bit = (SET_IO_BIT) GetProcAddress(gLibRTC4,"set_io_bit");
    n_clear_io_bit = (N_CLEAR_IO_BIT) GetProcAddress(gLibRTC4,"n_clear_io_bit");
    clear_io_bit = (CLEAR_IO_BIT) GetProcAddress(gLibRTC4,"clear_io_bit");
    set_duty_cycle_table = (SET_DUTY_CYCLE_TABLE) GetProcAddress(gLibRTC4,"set_duty_cycle_table");
    n_move_to = (N_MOVE_TO) GetProcAddress(gLibRTC4,"n_move_to");
    move_to = (MOVE_TO) GetProcAddress(gLibRTC4,"move_to");

    return(0);
}




bool RTC4::SetRTC()
{
	CString filepath; 
	CString str;

	int bDirect3DMove;
    int iEdgeLevel;
	int iMinJumpDelay;
	int iJumpLengthLimit;

	GetModuleFileName(NULL, filepath.GetBuffer(MAX_PATH), MAX_PATH);
	filepath.ReleaseBuffer();
	int Pos=filepath.ReverseFind('\\');	
	filepath=filepath.Mid(0,Pos); 	

	if(!Update("GalvoSettings", "VarPolygonDelay", (int&)m_bVarPolyDelay, false))
		m_bVarPolyDelay=0;
	if(!Update("GalvoSettings", "Direct3DMove", bDirect3DMove, false))
		bDirect3DMove=0;	
	if(!Update("GalvoSettings", "EdgeLevel", iEdgeLevel, false))
		iEdgeLevel=65535;	
	if(!Update("GalvoSettings", "MiniJumpDelay", iMinJumpDelay, false))
		iMinJumpDelay=10;	
	if(!Update("GalvoSettings", "JumpLengthLimit", iJumpLengthLimit, false))
		iJumpLengthLimit=10;

	if(!LoadFile(filepath))
		return false;

	if(!m_powercurvefile.IsEmpty())
		LoadPowerCurve(filepath +"\\"+ m_powercurvefile);

	set_list_mode(1);        //deactivate circular mode
	set_laser_mode(m_lasermode); 

	set_matrix(xcor*cos(xyrotate*PI/180), -xcor*sin(xyrotate*PI/180), ycor*sin(xyrotate*PI/180), ycor*cos(xyrotate*PI/180));
	set_offset(xoffset*m_Scale, yoffset*m_Scale);

	set_delay_mode(m_bVarPolyDelay, bDirect3DMove,iEdgeLevel, iMinJumpDelay, iJumpLengthLimit*m_Scale);//100	
	iMaxListPos=get_list_space();

	SetPulse(m_GalvoPara.m_dFrequency, m_GalvoPara.m_dPulseWidth);	
	StartList();
	ExcuteGalvoPara(&m_GalvoPara, false, false);
	EndOfList();
	WaitForStop();

	return true;
}

void RTC4::LaserOn()
{
	laser_signal_on();
}

void RTC4::LaserOff()
{
	laser_signal_off();
}

int RTC4::GetDLLVersion()
{
	return get_dll_version();
}

WORD RTC4::GetHeadStatus()
{
	return get_head_status(1);
}


void RTC4::SetPulse(double freq, double pwidth)
{
	WaitForListSpace(1);

	set_laser_timing(1000000*8/2.0/freq,				 // half of the standby period in 1/8 microseconds
		pwidth*8.0, pwidth*8.0,							//signal 1 as pulse triger, signal 2 as gate for pulse number
		1);																// pulse width in 1/8 microseconds
}
void RTC4:: SetOffsetList(double dx, double dy)
{
	WaitForListSpace(1);
	set_offset_list(dx*m_Scale, dy*m_Scale);
}


void RTC4::SetAnalog1(double Volt)
{
	if(Volt>5 || Volt<0)
		return;

	write_da_1(int(Volt/10.0*1024));
}


void RTC4::WaitForStop()
{
	m_State=DEVICE_STATE_BUSY;
 
	do {		        
		Sleep(1);
		if(busy)m_bTriggered=true;

	} while(GetBusy() && !m_Quit);

	m_State=DEVICE_STATE_OK;
}

bool RTC4::InitialRTC()
{
	m_State=DEVICE_STATE_NOT_INITIALIZED;

	if(gLibRTC!=NULL)
	{
		FreeLibrary(gLibRTC);
		gLibRTC=NULL;
	}

	gLibRTC=LoadLibrary("RTC4DLL.dll");

	if (gLibRTC == NULL)
	{
		AfxMessageBox("Load RTC4Dll.dll error!");
		return false;
	}

	RTC4open(gLibRTC);

	if(!SetRTC())
		return false;

	m_State=DEVICE_STATE_OK;

	TRACE("RTC4 initial successfully!\n");
	return true;
	
}

int RTC4::GetSerielNr()
{
	return get_serial_number();
}
double RTC4::GetScanField()
{
	if(m_Scale!=0)
		return iMaxBits/m_Scale;
	else
		return 60;
}

DriverCard RTC4::GetCardType()
{
	return cardRTC4;
}

void RTC4::StartList()
{
	m_Quit=false;
	m_bTriggered=false;
	save_and_restart_timer();
	set_end_of_list();

}


bool RTC4::LoadFile(CString filepath)
{
	UINT  ErrorCode;	
	CString str;

	ErrorCode = load_correction_file( filepath+ "\\Correction Files\\"+ m_corfile,
		1,          // table; #1 is used by default
		1.0, 1.0,   // scale factor
		0,	// rotation in degrees, counterclockwise
		0, 0);		// offset in bits
	if(ErrorCode)
	{
		CString str;
		switch(ErrorCode)
		{
		case 3: str="Load correction file error."; break;
		case 4: str="Load correction file verify error."; break;
		case 8:	str="Load correction file error, System driver not found or locked by another application.";break;
		case 10: str="Load correction file error, Parameter error.";break;
		case 11: str="Load correction file error, RTC4 not found.";break;
		case 12: str="Load correction file error, A 3D correction file could not be loaded, the function is not installed.";break;
		}
		AfxMessageBox(str);

		m_State=DEVICE_STATE_NOT_INSTALLED;

		return false;
	}

	if(m_prgmfile.IsEmpty())
		ErrorCode =load_program_file(filepath + "\\RTC4D3.hex");
	else
		ErrorCode =load_program_file(m_prgmfile);


	if(ErrorCode) 
	{
		CString str;
		switch(ErrorCode)
		{
		case 3: str="Load program file error"; break;
		case 4: str="Load program file verify error"; break;
		case 6:	str="Load program file error, Number of bytes in Intel hex file is odd.";break;
		case 7: str="Load program file error, Checksum error in hex file";break;
		case 8: str="Load program file error, System driver not found or locked by another application.";break;
		case 9: str="Load program file error, program file not complete.";break;
		case 11: str="Load program file error, RTC4 not found";break;
		}
		AfxMessageBox(str);

		m_State=DEVICE_STATE_NOT_INSTALLED;
		return false; 
	}	

	return true;
}

void RTC4::EndOfList(bool bWait)
{
	WaitForListSpace(2);

	if(!m_bTriggered)
		execute_list(1);	
	WaitForListSpace(2);
	save_and_restart_timer();
	set_end_of_list();
	
	if(!m_bTriggered)
		execute_list(1);

	if(bWait)
		WaitForStop();

	m_State=DEVICE_STATE_OK;
}

void RTC4:: WaitForListSpace(int iGap)
{
	iLoadPos = get_input_pointer();	

	do
	{
		GetBusy();
		LoadGap=get_list_space();		
		//for progress display
		iLoadPos=position+LoadGap;
		iLoadPos=iLoadPos>iMaxListPos?iLoadPos-iMaxListPos:iLoadPos;
		if(busy)
			m_bTriggered=true;
		//	
	}while(LoadGap<iGap && GetBusy() && !m_Quit);

	if(m_Quit)
		stop_execution();

}

void RTC4:: SetLaserDelays(double dlaserondelay, double dlaseroffdelay)
{
	WaitForListSpace(1);
	set_laser_delays(dlaserondelay,dlaseroffdelay);
	m_GalvoPara.m_dLaserOnDelay= dlaserondelay;
	m_GalvoPara.m_dLaserOffDelay= dlaseroffdelay;
}		//laser on and off delays


void RTC4:: SetScannerDelay(double dmarkdelay, double djumpdelay, double dpolygondelay)
{
	WaitForListSpace(1);
	set_scanner_delays(djumpdelay/10, dmarkdelay/10, dpolygondelay/10);
	m_GalvoPara.m_dJumpDelay=djumpdelay;
	m_GalvoPara.m_dMarkDelay=dmarkdelay;
	m_GalvoPara.m_dPolygonDelay=dpolygondelay;

}	//jump,mark and polygon delays

void RTC4:: SetJumpSpeed(double djumpspeed)
{
	WaitForListSpace(1);
	set_jump_speed(djumpspeed*m_Scale/1000);
	m_GalvoPara.m_dJumpSpeed=djumpspeed;

}
void RTC4:: SetMarkSpeed(double dmarkspeed)
{
	WaitForListSpace(1);
	set_mark_speed(dmarkspeed*m_Scale/1000);
	m_GalvoPara.m_dMarkSpeed=dmarkspeed;
}


void RTC4:: SetLaserPara(double dfreq, double dpulsewidth)
{
	WaitForListSpace(1);
	set_laser_timing(1000000*8/2.0/dfreq,				// half of the standby period in 1/64 microseconds
		dpulsewidth*8.0, dpulsewidth*8.0,				//signal 1 as pulse triger, signal 2 as gate for pulse number
		1);										// pulse width in 1/8 microseconds
	m_GalvoPara.m_dFrequency=dfreq;
	m_GalvoPara.m_dPulseWidth=dpulsewidth;
} 		//freq, p


void RTC4:: SetWobbel(double dampl, double dfreq)
{
	WaitForListSpace(1);
	set_wobbel(dampl*m_Scale, dfreq);
	m_GalvoPara.m_dWobelAmpl=dampl;
	m_GalvoPara.m_dWobelFreq=dfreq;

}

void RTC4:: SPoint(double dx, double dy, double dz, double dtime)
{
	WaitForListSpace(2);
	jump_abs_3d(dx*m_Scale,dy*m_Scale,dz*m_Scale);
	laser_on_list(dtime/10+1);
}
///	
void RTC4:: SMarkTo(double dx, double dy)
{
	WaitForListSpace(1);
	mark_abs(dx*m_Scale,dy*m_Scale);
}
void RTC4:: SJumpTo(double dx, double dy)
{
	WaitForListSpace(1);
	jump_abs(dx*m_Scale,dy*m_Scale);
}
void RTC4:: SArcTo(double dx, double dy, double dangle)
{
	if(dangle>360 || dangle<-360)
	{
		if(dangle>360)
		{
			WaitForListSpace(1);
			arc_abs(dx*m_Scale,dy*m_Scale,360);
			dangle-=360;
		}
		else if(dangle<-360)
		{
			WaitForListSpace(1);
			arc_abs(dx*m_Scale,dy*m_Scale, -360);
			dangle+=360;
		}
		
		SArcTo(dx, dy, dangle);
	}
	else
	{
		WaitForListSpace(1);
		arc_abs(dx*m_Scale,dy*m_Scale, dangle);
	}

}

void RTC4:: SMark3DTo(double dx, double dy, double dz)
{
	WaitForListSpace(1);
	mark_abs_3d(dx*m_Scale,dy*m_Scale, dz*m_Scale);
}

void RTC4:: SJump3DTo(double dx, double dy, double dz)
{
	WaitForListSpace(1);
	jump_abs_3d(dx*m_Scale,dy*m_Scale, dz*m_Scale);
}

void RTC4:: SArc3DTo(double dx, double dy, double dz, double dangle)
{	
	if(dangle>360 || dangle<-360)
	{
		if(dangle>360)
		{
			WaitForListSpace(1);
			arc_abs(dx*m_Scale,dz*m_Scale,360);
			dangle-=360;
		}
		else if(dangle<-360)
		{
			WaitForListSpace(1);
			arc_abs(dx*m_Scale,dy*m_Scale, -360);
			dangle+=360;
		}
		
		SArc3DTo(dx, dy, dz, dangle);
	}
	else
	{
		WaitForListSpace(1);
		arc_abs(dx*m_Scale,dy*m_Scale, dangle);
	}
}

void RTC4:: SMarkRelTo(double dx, double dy)
{
	WaitForListSpace(1);
	mark_rel(dx*m_Scale,dy*m_Scale);
}
void RTC4:: SJumpRelTo(double dx, double dy)
{
	WaitForListSpace(1);
	jump_rel(dx*m_Scale,dy*m_Scale);
}
	
void RTC4:: SArcRelTo(double dx, double dy, double dangle)
{
	if(dangle>360 || dangle<-360)
	{
		if(dangle>360)
		{
			WaitForListSpace(1);
			arc_rel(dx*m_Scale,dy*m_Scale,360);
			dangle-=360;
		}
		else if(dangle<-360)
		{
			WaitForListSpace(1);
			arc_rel(dx*m_Scale,dy*m_Scale, -360);
			dangle+=360;
		}
		
		SArcRelTo(dx, dy, dangle);
	}
	else
	{
		WaitForListSpace(1);
		arc_rel(dx*m_Scale,dy*m_Scale, dangle);
	}
}

void RTC4:: SMark3DRelTo(double dx, double dy, double dz)
{
	WaitForListSpace(1);
	mark_rel_3d(dx*m_Scale,dy*m_Scale, dz*m_Scale);
}
void RTC4:: SJump3DRelTo(double dx, double dy, double dz)
{
	WaitForListSpace(1);
	jump_rel_3d(dx*m_Scale,dy*m_Scale, dz*m_Scale);
}
void RTC4:: SArc3DRelTo(double dx, double dy, double dz, double dangle)
{
	if(dangle>360 || dangle<-360)
	{
		if(dangle>360)
		{
			WaitForListSpace(1);
			arc_rel(dx*m_Scale,dz*m_Scale,360);
			dangle-=360;
		}
		else if(dangle<-360)
		{
			WaitForListSpace(1);
			arc_rel(dx*m_Scale,dy*m_Scale, -360);
			dangle+=360;
		}
		
		SArc3DRelTo(dx, dy, dz, dangle);
	}
	else
	{
		WaitForListSpace(1);
		arc_rel(dx*m_Scale,dy*m_Scale, dangle);
	}
}


//Bitmap
void RTC4:: SSetZPosition(double dz)
{
	WaitForListSpace(1);
	jump_rel_3d(0,0, dz*m_Scale);
}

void RTC4:: SSetPixelLine(int ichanel, double dperiod, double dx, double dy, double dz)
{
	WaitForListSpace(2);
	set_pixel_line(1, dperiod/10, dx*m_Scale, dy*m_Scale);	

	dBmpPeriod=dperiod;
	dBmpx=dx;
	dBmpy=dy;
	dBmpz=dz;
}	


void RTC4:: SSetPixel(double dpulsewidth, double dvoltage, int npixel)
{
	for(int i=0; i<npixel; i++)
	{
		WaitForListSpace(2);
		if(get_input_pointer()==0)
			set_pixel_line(1, dBmpPeriod/10, dBmpx*m_Scale, dBmpy*m_Scale);	
		set_pixel(dpulsewidth*8, dvoltage/10*1024, 0);
	}
}

//LaserControl
void RTC4:: SSetLaserOnList(double dt)
{
	WaitForListSpace(1);
	laser_on_list(dt/10+1);
}
void RTC4:: SSetDelayOnList(double dt)
{
	WaitForListSpace(1);
	long_delay(unsigned(dt/10)+1);
}
//	SAnologOut1List,// power
void RTC4:: SSetAnologOut1(double dvoltage)
{
	WaitForListSpace(1);
	write_da_1_list(dvoltage/10*1024); //us
} 
void RTC4:: SSetLongDelay(double dt)
{
	WaitForListSpace(1);
	long_delay(dt/10+1);	//us
}

void RTC4:: SSetFirstKiller(double dlength)
{
	WaitForListSpace(1);
	set_firstpulse_killer_list(int(dlength*8));
}



//SkyWriting
void RTC4:: SSetSkyWritingMode(int imode){}
void RTC4:: SSetSkyWritingPara(double dtimeleg, double dlaseronshift, double nprev, double npost){}
//
void RTC4:: SListContinue(){}

void RTC4::StopExcute()
{
	m_Quit=true;

	if(m_State>=3)
	{
		stop_execution();
		save_and_restart_timer();
//		set_end_of_list();
	}
	
}

bool RTC4::GetBusy()
{
	if(m_State>=3)
	{
		busy=0;
		get_status(&busy, &position);
	}

//	TRACE("execute at, %d\n", position);

	return busy&0x01;
}

double RTC4::GetMarkTime()
{
	ResetTimer();
	return get_time();
}

void RTC4::ResetTimer()
{
	save_and_restart_timer();
//	set_end_of_list();
}

UINT RTC4::GetPosition()
{
//	GetBusy();
	return position;
}

void RTC4::GetCurPos()
{
	if(m_State<=1)
		return;
	CurX=(double)get_value(7)/m_Scale;
	CurY=(double)get_value(8)/m_Scale;
	CurZ=(double)get_value(9)/m_Scale;
}


//  RTC4close
//
//  This function terminates the explicit linking to the RTC4DLL.DLL.
//  Call it when the use of the RTC4 functions is finished.

void RTC4::ExcuteGalvoPara(CLaserPara* pPara, bool bJudge, bool bSet)
{
	//laser delay
	if(!bJudge || (m_GalvoPara.m_dLaserOnDelay!=pPara->m_dLaserOnDelay ||
		m_GalvoPara.m_dLaserOffDelay!=pPara->m_dLaserOffDelay))
		SetLaserDelays(pPara->m_dLaserOnDelay, pPara->m_dLaserOffDelay);
	
	//scanner delays
	if(!bJudge || (m_GalvoPara.m_dMarkDelay!=pPara->m_dMarkDelay || m_GalvoPara.m_dJumpDelay!=pPara->m_dJumpDelay 
		|| m_GalvoPara.m_dPolygonDelay!=pPara->m_dPolygonDelay))
		SetScannerDelay(pPara->m_dMarkDelay, pPara->m_dJumpDelay, pPara->m_dPolygonDelay);
	
	if(!bJudge || (m_GalvoPara.m_dMarkSpeed!=pPara->m_dMarkSpeed || m_GalvoPara.m_dJumpSpeed!=pPara->m_dJumpSpeed))
	{
		SetMarkSpeed(pPara->m_dMarkSpeed);		
		SetJumpSpeed(pPara->m_dJumpSpeed);
	}
	
	//wobbel
	if(!bJudge || (m_GalvoPara.m_dWobelAmpl!=pPara->m_dWobelAmpl || m_GalvoPara.m_dWobelFreq!=pPara->m_dWobelFreq))
		SetWobbel(pPara->m_dWobelAmpl, pPara->m_dWobelFreq);		
	
	//frequency
	if(!bJudge || (m_GalvoPara.m_dPulseWidth!=pPara->m_dPulseWidth || m_GalvoPara.m_dFrequency!=pPara->m_dFrequency))
		SetLaserPara(pPara->m_dFrequency, pPara->m_dPulseWidth);		
	
	if(!bJudge || (m_GalvoPara.m_dPower!=pPara->m_dPower))
		SSetAnologOut1(Power2Volt(pPara->m_dPower));
	
	if(bSet)
		m_GalvoPara.SetPara(pPara);
}


void  RTC4::SetTrigger(UINT Period, UINT Signal1,UINT Signal2)
{
	set_trigger(Period, Signal1, Signal2);
}

void RTC4::MeasurementStatus( UINT* busy, UINT* position )
{
	measurement_status((unsigned short*)busy, (unsigned short*)position);
}