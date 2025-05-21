//-----------------------------------------------------------------------------
//  File: RTC5expl.c                             Copyright (c) 2010 SCANLAB AG
//-----------------------------------------------------------------------------
//
//
//
//  Abstract
//      DLL handling functions for explicitly linking to the RTC5DLL.DLL
//      This file was automatically generated at 04.12.2013
//
//  Function List
//      RTC5open
//      RTC5close
//-----------------------------------------------------------------------------


//  RTC5open
//
//  This function explicitly or dynamically links to the RTC5DLL.DLL.
//  Call it before using any RTC5 function.
//
//      Return      Meaning
//
//       0          Success. Using of the RTC5 functions is possible.
//      -1          Error: file RTC5DLL.DLL not found. The RTC5 functions
//                  cannot be used.
//      -2          Error: file RTC5DLL.DLL is already loaded.
// 


#include <windows.h>

#include "STDAFX.H"
#include "RTC5expl.h"
#include "math.h"


RTC5::~RTC5()
{
	int bValue;
	
	Update("GalvoSettings", "LaserSignal", m_LaserSignal, true);
	bValue=(int)m_bFirstPulseSync;
	Update("GalvoSettings", "FirstPulseSync", bValue, true);
	bValue=(int)m_bSpeedDepend;
	Update("GalvoSettings", "SpeedDepend", bValue, true);	
	bValue=(int)m_bPositionDepend;
	Update("GalvoSettings", "PositionDepend", bValue, true);
// 	bValue=(int)m_bVectorDepend;
// 	Update("GalvoSettings", "VectorDepend", bValue, true);
// 	Update("GalvoSettings", "AutoVectorCtrl", m_iVectorDependCtrl, true);	
		
	Update("GalvoSettings", "AutoLaserCtrl", m_iAutoDependCtrl, true);	

	Update("GalvoSettings", "strAutoControlScale", strAutoControlScale, true);
	Update("GalvoSettings", "strAutoPosScale", strAutoPosScale, true);
		
	Update("GalvoSettings", "AutoLaserMax", m_AdvLaserMax, true);
	Update("GalvoSettings", "AutoLaserMin", m_AdvLaserMin, true);

	if(gLibRTC!=NULL)
	{
		free_rtc5_dll();
		(void)FreeLibrary(gLibRTC);
	}
	
	gLibRTC=NULL;
	
}

RTC5::RTC5(CWnd* pOwner):RTC4(pOwner)
{
	int bValue;
	
	if(!Update("GalvoSettings", "LaserSignal", m_LaserSignal, false))
		m_LaserSignal=0x24;

	if(!Update("GalvoSettings", "FirstPulseSync", bValue, false))
		bValue=0;
	m_bFirstPulseSync=(bool)bValue;

	if(!Update("GalvoSettings", "SpeedDepend", bValue, false))
		bValue=0;
	m_bSpeedDepend=(bool)bValue;

	if(!Update("GalvoSettings", "PositionDepend", bValue, false))
		bValue=0;
	m_bPositionDepend=(bool)bValue;

	if(!Update("GalvoSettings", "AutoLaserCtrl", m_iAutoDependCtrl, false))
		m_iAutoDependCtrl=0;
	
	if(!Update("GalvoSettings", "strAutoControlScale", strAutoControlScale, false))
		strAutoControlScale="";
	if(!Update("GalvoSettings", "strAutoPosScale", strAutoPosScale, false))
		strAutoPosScale="";

	if(!Update("GalvoSettings", "AutoLaserMax", m_AdvLaserMax, false))
		m_AdvLaserMax=1;

	if(!Update("GalvoSettings", "AutoLaserMin", m_AdvLaserMin, false))
		m_AdvLaserMin=1;

	bWaiterCanSet=true;

	gLibRTC=NULL;
	m_State=DEVICE_STATE_NOT_INITIALIZED;
}

long RTC5::RTCOpen(HINSTANCE gLibRTC) 
{
	// Get the addresses of the DLL-Functions
	init_rtc5_dll = (INIT_RTC5_DLL_FP) GetProcAddress(gLibRTC,"init_rtc5_dll");
	free_rtc5_dll = (FREE_RTC5_DLL_FP) GetProcAddress(gLibRTC,"free_rtc5_dll");
	set_rtc4_mode = (SET_RTC4_MODE_FP) GetProcAddress(gLibRTC,"set_rtc4_mode");
	set_rtc5_mode = (SET_RTC5_MODE_FP) GetProcAddress(gLibRTC,"set_rtc5_mode");
	get_rtc_mode = (GET_RTC_MODE_FP) GetProcAddress(gLibRTC,"get_rtc_mode");
	n_get_error = (N_GET_ERROR_FP) GetProcAddress(gLibRTC,"n_get_error");
	n_get_last_error = (N_GET_LAST_ERROR_FP) GetProcAddress(gLibRTC,"n_get_last_error");
	n_reset_error = (N_RESET_ERROR_FP) GetProcAddress(gLibRTC,"n_reset_error");
	n_set_verify = (N_SET_VERIFY_FP) GetProcAddress(gLibRTC,"n_set_verify");
	get_error = (GET_ERROR_FP) GetProcAddress(gLibRTC,"get_error");
	get_last_error = (GET_LAST_ERROR_FP) GetProcAddress(gLibRTC,"get_last_error");
	reset_error = (RESET_ERROR_FP) GetProcAddress(gLibRTC,"reset_error");
	set_verify = (SET_VERIFY_FP) GetProcAddress(gLibRTC,"set_verify");
	verify_checksum = (VERIFY_CHECKSUM_FP) GetProcAddress(gLibRTC,"verify_checksum");
	read_abc_from_file = (READ_ABC_FROM_FILE_FP) GetProcAddress(gLibRTC,"read_abc_from_file");
	write_abc_to_file = (WRITE_ABC_TO_FILE_FP) GetProcAddress(gLibRTC,"write_abc_to_file");
	od_aoyszs = (OD_AOYSZS_FP) GetProcAddress(gLibRTC,"od_aoyszs");
	rtc5_count_cards = (RTC5_COUNT_CARDS_FP) GetProcAddress(gLibRTC,"rtc5_count_cards");
	acquire_rtc = (ACQUIRE_RTC_FP) GetProcAddress(gLibRTC,"acquire_rtc");
	release_rtc = (RELEASE_RTC_FP) GetProcAddress(gLibRTC,"release_rtc");
	select_rtc = (SELECT_RTC_FP) GetProcAddress(gLibRTC,"select_rtc");
	get_dll_version = (GET_DLL_VERSION_FP) GetProcAddress(gLibRTC,"get_dll_version");
	n_get_serial_number = (N_GET_SERIAL_NUMBER_FP) GetProcAddress(gLibRTC,"n_get_serial_number");
	n_get_hex_version = (N_GET_HEX_VERSION_FP) GetProcAddress(gLibRTC,"n_get_hex_version");
	n_get_rtc_version = (N_GET_RTC_VERSION_FP) GetProcAddress(gLibRTC,"n_get_rtc_version");
	get_serial_number = (GET_SERIAL_NUMBER_FP) GetProcAddress(gLibRTC,"get_serial_number");
	get_hex_version = (GET_HEX_VERSION_FP) GetProcAddress(gLibRTC,"get_hex_version");
	get_rtc_version = (GET_RTC_VERSION_FP) GetProcAddress(gLibRTC,"get_rtc_version");
	n_load_program_file = (N_LOAD_PROGRAM_FILE_FP) GetProcAddress(gLibRTC,"n_load_program_file");
	n_sync_slaves = (N_SYNC_SLAVES_FP) GetProcAddress(gLibRTC,"n_sync_slaves");
	n_get_sync_status = (N_GET_SYNC_STATUS_FP) GetProcAddress(gLibRTC,"n_get_sync_status");
	n_load_correction_file = (N_LOAD_CORRECTION_FILE_FP) GetProcAddress(gLibRTC,"n_load_correction_file");
	n_load_zoom_correction_file = (N_LOAD_ZOOM_CORRECTION_FILE_FP) GetProcAddress(gLibRTC,"n_load_zoom_correction_file");
	n_load_z_table = (N_LOAD_Z_TABLE_FP) GetProcAddress(gLibRTC,"n_load_z_table");
	n_select_cor_table = (N_SELECT_COR_TABLE_FP) GetProcAddress(gLibRTC,"n_select_cor_table");
	n_set_dsp_mode = (N_SET_DSP_MODE_FP) GetProcAddress(gLibRTC,"n_set_dsp_mode");
	n_load_stretch_table = (N_LOAD_STRETCH_TABLE_FP) GetProcAddress(gLibRTC,"n_load_stretch_table");
	n_number_of_correction_tables = (N_NUMBER_OF_CORRECTION_TABLES_FP) GetProcAddress(gLibRTC,"n_number_of_correction_tables");
	n_get_head_para = (N_GET_HEAD_PARA_FP) GetProcAddress(gLibRTC,"n_get_head_para");
	n_get_table_para = (N_GET_TABLE_PARA_FP) GetProcAddress(gLibRTC,"n_get_table_para");
	load_program_file = (LOAD_PROGRAM_FILE_FP) GetProcAddress(gLibRTC,"load_program_file");
	sync_slaves = (SYNC_SLAVES_FP) GetProcAddress(gLibRTC,"sync_slaves");
	get_sync_status = (GET_SYNC_STATUS_FP) GetProcAddress(gLibRTC,"get_sync_status");
	load_correction_file = (LOAD_CORRECTION_FILE_FP) GetProcAddress(gLibRTC,"load_correction_file");
	load_zoom_correction_file = (LOAD_ZOOM_CORRECTION_FILE_FP) GetProcAddress(gLibRTC,"load_zoom_correction_file");
	load_z_table = (LOAD_Z_TABLE_FP) GetProcAddress(gLibRTC,"load_z_table");
	select_cor_table = (SELECT_COR_TABLE_FP) GetProcAddress(gLibRTC,"select_cor_table");
	set_dsp_mode = (SET_DSP_MODE_FP) GetProcAddress(gLibRTC,"set_dsp_mode");
	load_stretch_table = (LOAD_STRETCH_TABLE_FP) GetProcAddress(gLibRTC,"load_stretch_table");
	number_of_correction_tables = (NUMBER_OF_CORRECTION_TABLES_FP) GetProcAddress(gLibRTC,"number_of_correction_tables");
	get_head_para = (GET_HEAD_PARA_FP) GetProcAddress(gLibRTC,"get_head_para");
	get_table_para = (GET_TABLE_PARA_FP) GetProcAddress(gLibRTC,"get_table_para");
	n_config_list = (N_CONFIG_LIST_FP) GetProcAddress(gLibRTC,"n_config_list");
	n_get_config_list = (N_GET_CONFIG_LIST_FP) GetProcAddress(gLibRTC,"n_get_config_list");
	n_save_disk = (N_SAVE_DISK_FP) GetProcAddress(gLibRTC,"n_save_disk");
	n_load_disk = (N_LOAD_DISK_FP) GetProcAddress(gLibRTC,"n_load_disk");
	n_get_list_space = (N_GET_LIST_SPACE_FP) GetProcAddress(gLibRTC,"n_get_list_space");
	config_list = (CONFIG_LIST_FP) GetProcAddress(gLibRTC,"config_list");
	get_config_list = (GET_CONFIG_LIST_FP) GetProcAddress(gLibRTC,"get_config_list");
	save_disk = (SAVE_DISK_FP) GetProcAddress(gLibRTC,"save_disk");
	load_disk = (LOAD_DISK_FP) GetProcAddress(gLibRTC,"load_disk");
	get_list_space = (GET_LIST_SPACE_FP) GetProcAddress(gLibRTC,"get_list_space");
	n_set_start_list_pos = (N_SET_START_LIST_POS_FP) GetProcAddress(gLibRTC,"n_set_start_list_pos");
	n_set_start_list = (N_SET_START_LIST_FP) GetProcAddress(gLibRTC,"n_set_start_list");
	n_set_start_list_1 = (N_SET_START_LIST_1_FP) GetProcAddress(gLibRTC,"n_set_start_list_1");
	n_set_start_list_2 = (N_SET_START_LIST_2_FP) GetProcAddress(gLibRTC,"n_set_start_list_2");
	n_set_input_pointer = (N_SET_INPUT_POINTER_FP) GetProcAddress(gLibRTC,"n_set_input_pointer");
	n_load_list = (N_LOAD_LIST_FP) GetProcAddress(gLibRTC,"n_load_list");
	n_load_sub = (N_LOAD_SUB_FP) GetProcAddress(gLibRTC,"n_load_sub");
	n_load_char = (N_LOAD_CHAR_FP) GetProcAddress(gLibRTC,"n_load_char");
	n_load_text_table = (N_LOAD_TEXT_TABLE_FP) GetProcAddress(gLibRTC,"n_load_text_table");
	n_get_list_pointer = (N_GET_LIST_POINTER_FP) GetProcAddress(gLibRTC,"n_get_list_pointer");
	n_get_input_pointer = (N_GET_INPUT_POINTER_FP) GetProcAddress(gLibRTC,"n_get_input_pointer");
	set_start_list_pos = (SET_START_LIST_POS_FP) GetProcAddress(gLibRTC,"set_start_list_pos");
	set_start_list = (SET_START_LIST_FP) GetProcAddress(gLibRTC,"set_start_list");
	set_start_list_1 = (SET_START_LIST_1_FP) GetProcAddress(gLibRTC,"set_start_list_1");
	set_start_list_2 = (SET_START_LIST_2_FP) GetProcAddress(gLibRTC,"set_start_list_2");
	set_input_pointer = (SET_INPUT_POINTER_FP) GetProcAddress(gLibRTC,"set_input_pointer");
	load_list = (LOAD_LIST_FP) GetProcAddress(gLibRTC,"load_list");
	load_sub = (LOAD_SUB_FP) GetProcAddress(gLibRTC,"load_sub");
	load_char = (LOAD_CHAR_FP) GetProcAddress(gLibRTC,"load_char");
	load_text_table = (LOAD_TEXT_TABLE_FP) GetProcAddress(gLibRTC,"load_text_table");
	get_list_pointer = (GET_LIST_POINTER_FP) GetProcAddress(gLibRTC,"get_list_pointer");
	get_input_pointer = (GET_INPUT_POINTER_FP) GetProcAddress(gLibRTC,"get_input_pointer");
	n_execute_list_pos = (N_EXECUTE_LIST_POS_FP) GetProcAddress(gLibRTC,"n_execute_list_pos");
	n_execute_at_pointer = (N_EXECUTE_AT_POINTER_FP) GetProcAddress(gLibRTC,"n_execute_at_pointer");
	n_execute_list = (N_EXECUTE_LIST_FP) GetProcAddress(gLibRTC,"n_execute_list");
	n_execute_list_1 = (N_EXECUTE_LIST_1_FP) GetProcAddress(gLibRTC,"n_execute_list_1");
	n_execute_list_2 = (N_EXECUTE_LIST_2_FP) GetProcAddress(gLibRTC,"n_execute_list_2");
	n_get_out_pointer = (N_GET_OUT_POINTER_FP) GetProcAddress(gLibRTC,"n_get_out_pointer");
	execute_list_pos = (EXECUTE_LIST_POS_FP) GetProcAddress(gLibRTC,"execute_list_pos");
	execute_at_pointer = (EXECUTE_AT_POINTER_FP) GetProcAddress(gLibRTC,"execute_at_pointer");
	execute_list = (EXECUTE_LIST_FP) GetProcAddress(gLibRTC,"execute_list");
	execute_list_1 = (EXECUTE_LIST_1_FP) GetProcAddress(gLibRTC,"execute_list_1");
	execute_list_2 = (EXECUTE_LIST_2_FP) GetProcAddress(gLibRTC,"execute_list_2");
	get_out_pointer = (GET_OUT_POINTER_FP) GetProcAddress(gLibRTC,"get_out_pointer");
	n_auto_change_pos = (N_AUTO_CHANGE_POS_FP) GetProcAddress(gLibRTC,"n_auto_change_pos");
	n_start_loop = (N_START_LOOP_FP) GetProcAddress(gLibRTC,"n_start_loop");
	n_quit_loop = (N_QUIT_LOOP_FP) GetProcAddress(gLibRTC,"n_quit_loop");
	n_pause_list = (N_PAUSE_LIST_FP) GetProcAddress(gLibRTC,"n_pause_list");
	n_restart_list = (N_RESTART_LIST_FP) GetProcAddress(gLibRTC,"n_restart_list");
	n_release_wait = (N_RELEASE_WAIT_FP) GetProcAddress(gLibRTC,"n_release_wait");
	n_stop_execution = (N_STOP_EXECUTION_FP) GetProcAddress(gLibRTC,"n_stop_execution");
	n_set_pause_list_cond = (N_SET_PAUSE_LIST_COND_FP) GetProcAddress(gLibRTC,"n_set_pause_list_cond");
	n_auto_change = (N_AUTO_CHANGE_FP) GetProcAddress(gLibRTC,"n_auto_change");
	n_stop_list = (N_STOP_LIST_FP) GetProcAddress(gLibRTC,"n_stop_list");
	n_get_wait_status = (N_GET_WAIT_STATUS_FP) GetProcAddress(gLibRTC,"n_get_wait_status");
	n_read_status = (N_READ_STATUS_FP) GetProcAddress(gLibRTC,"n_read_status");
	n_get_status = (N_GET_STATUS_FP) GetProcAddress(gLibRTC,"n_get_status");
	auto_change_pos = (AUTO_CHANGE_POS_FP) GetProcAddress(gLibRTC,"auto_change_pos");
	start_loop = (START_LOOP_FP) GetProcAddress(gLibRTC,"start_loop");
	quit_loop = (QUIT_LOOP_FP) GetProcAddress(gLibRTC,"quit_loop");
	pause_list = (PAUSE_LIST_FP) GetProcAddress(gLibRTC,"pause_list");
	restart_list = (RESTART_LIST_FP) GetProcAddress(gLibRTC,"restart_list");
	release_wait = (RELEASE_WAIT_FP) GetProcAddress(gLibRTC,"release_wait");
	stop_execution = (STOP_EXECUTION_FP) GetProcAddress(gLibRTC,"stop_execution");
	set_pause_list_cond = (SET_PAUSE_LIST_COND_FP) GetProcAddress(gLibRTC,"set_pause_list_cond");
	auto_change = (AUTO_CHANGE_FP) GetProcAddress(gLibRTC,"auto_change");
	stop_list = (STOP_LIST_FP) GetProcAddress(gLibRTC,"stop_list");
	get_wait_status = (GET_WAIT_STATUS_FP) GetProcAddress(gLibRTC,"get_wait_status");
	read_status = (READ_STATUS_FP) GetProcAddress(gLibRTC,"read_status");
	get_status = (GET_STATUS_FP) GetProcAddress(gLibRTC,"get_status");
	n_set_extstartpos = (N_SET_EXTSTARTPOS_FP) GetProcAddress(gLibRTC,"n_set_extstartpos");
	n_set_max_counts = (N_SET_MAX_COUNTS_FP) GetProcAddress(gLibRTC,"n_set_max_counts");
	n_set_control_mode = (N_SET_CONTROL_MODE_FP) GetProcAddress(gLibRTC,"n_set_control_mode");
	n_simulate_ext_stop = (N_SIMULATE_EXT_STOP_FP) GetProcAddress(gLibRTC,"n_simulate_ext_stop");
	n_simulate_ext_start_ctrl = (N_SIMULATE_EXT_START_CTRL_FP) GetProcAddress(gLibRTC,"n_simulate_ext_start_ctrl");
	n_get_counts = (N_GET_COUNTS_FP) GetProcAddress(gLibRTC,"n_get_counts");
	n_get_startstop_info = (N_GET_STARTSTOP_INFO_FP) GetProcAddress(gLibRTC,"n_get_startstop_info");
	set_extstartpos = (SET_EXTSTARTPOS_FP) GetProcAddress(gLibRTC,"set_extstartpos");
	set_max_counts = (SET_MAX_COUNTS_FP) GetProcAddress(gLibRTC,"set_max_counts");
	set_control_mode = (SET_CONTROL_MODE_FP) GetProcAddress(gLibRTC,"set_control_mode");
	simulate_ext_stop = (SIMULATE_EXT_STOP_FP) GetProcAddress(gLibRTC,"simulate_ext_stop");
	simulate_ext_start_ctrl = (SIMULATE_EXT_START_CTRL_FP) GetProcAddress(gLibRTC,"simulate_ext_start_ctrl");
	get_counts = (GET_COUNTS_FP) GetProcAddress(gLibRTC,"get_counts");
	get_startstop_info = (GET_STARTSTOP_INFO_FP) GetProcAddress(gLibRTC,"get_startstop_info");
	n_copy_dst_src = (N_COPY_DST_SRC_FP) GetProcAddress(gLibRTC,"n_copy_dst_src");
	n_set_char_pointer = (N_SET_CHAR_POINTER_FP) GetProcAddress(gLibRTC,"n_set_char_pointer");
	n_set_sub_pointer = (N_SET_SUB_POINTER_FP) GetProcAddress(gLibRTC,"n_set_sub_pointer");
	n_set_text_table_pointer = (N_SET_TEXT_TABLE_POINTER_FP) GetProcAddress(gLibRTC,"n_set_text_table_pointer");
	n_set_char_table = (N_SET_CHAR_TABLE_FP) GetProcAddress(gLibRTC,"n_set_char_table");
	n_get_char_pointer = (N_GET_CHAR_POINTER_FP) GetProcAddress(gLibRTC,"n_get_char_pointer");
	n_get_sub_pointer = (N_GET_SUB_POINTER_FP) GetProcAddress(gLibRTC,"n_get_sub_pointer");
	n_get_text_table_pointer = (N_GET_TEXT_TABLE_POINTER_FP) GetProcAddress(gLibRTC,"n_get_text_table_pointer");
	copy_dst_src = (COPY_DST_SRC_FP) GetProcAddress(gLibRTC,"copy_dst_src");
	set_char_pointer = (SET_CHAR_POINTER_FP) GetProcAddress(gLibRTC,"set_char_pointer");
	set_sub_pointer = (SET_SUB_POINTER_FP) GetProcAddress(gLibRTC,"set_sub_pointer");
	set_text_table_pointer = (SET_TEXT_TABLE_POINTER_FP) GetProcAddress(gLibRTC,"set_text_table_pointer");
	set_char_table = (SET_CHAR_TABLE_FP) GetProcAddress(gLibRTC,"set_char_table");
	get_char_pointer = (GET_CHAR_POINTER_FP) GetProcAddress(gLibRTC,"get_char_pointer");
	get_sub_pointer = (GET_SUB_POINTER_FP) GetProcAddress(gLibRTC,"get_sub_pointer");
	get_text_table_pointer = (GET_TEXT_TABLE_POINTER_FP) GetProcAddress(gLibRTC,"get_text_table_pointer");
	n_time_update = (N_TIME_UPDATE_FP) GetProcAddress(gLibRTC,"n_time_update");
	n_set_serial_step = (N_SET_SERIAL_STEP_FP) GetProcAddress(gLibRTC,"n_set_serial_step");
	n_select_serial_set = (N_SELECT_SERIAL_SET_FP) GetProcAddress(gLibRTC,"n_select_serial_set");
	n_set_serial = (N_SET_SERIAL_FP) GetProcAddress(gLibRTC,"n_set_serial");
	n_get_serial = (N_GET_SERIAL_FP) GetProcAddress(gLibRTC,"n_get_serial");
	n_get_list_serial = (N_GET_LIST_SERIAL_FP) GetProcAddress(gLibRTC,"n_get_list_serial");
	time_update = (TIME_UPDATE_FP) GetProcAddress(gLibRTC,"time_update");
	set_serial_step = (SET_SERIAL_STEP_FP) GetProcAddress(gLibRTC,"set_serial_step");
	select_serial_set = (SELECT_SERIAL_SET_FP) GetProcAddress(gLibRTC,"select_serial_set");
	set_serial = (SET_SERIAL_FP) GetProcAddress(gLibRTC,"set_serial");
	get_serial = (GET_SERIAL_FP) GetProcAddress(gLibRTC,"get_serial");
	get_list_serial = (GET_LIST_SERIAL_FP) GetProcAddress(gLibRTC,"get_list_serial");
	n_write_io_port_mask = (N_WRITE_IO_PORT_MASK_FP) GetProcAddress(gLibRTC,"n_write_io_port_mask");
	n_write_8bit_port = (N_WRITE_8BIT_PORT_FP) GetProcAddress(gLibRTC,"n_write_8bit_port");
	n_read_io_port = (N_READ_IO_PORT_FP) GetProcAddress(gLibRTC,"n_read_io_port");
	n_read_io_port_buffer = (N_READ_IO_PORT_BUFFER_FP) GetProcAddress(gLibRTC,"n_read_io_port_buffer");
	n_get_io_status = (N_GET_IO_STATUS_FP) GetProcAddress(gLibRTC,"n_get_io_status");
	n_read_analog_in = (N_READ_ANALOG_IN_FP) GetProcAddress(gLibRTC,"n_read_analog_in");
	n_write_da_x = (N_WRITE_DA_X_FP) GetProcAddress(gLibRTC,"n_write_da_x");
	n_set_laser_off_default = (N_SET_LASER_OFF_DEFAULT_FP) GetProcAddress(gLibRTC,"n_set_laser_off_default");
	n_set_port_default = (N_SET_PORT_DEFAULT_FP) GetProcAddress(gLibRTC,"n_set_port_default");
	n_write_io_port = (N_WRITE_IO_PORT_FP) GetProcAddress(gLibRTC,"n_write_io_port");
	n_write_da_1 = (N_WRITE_DA_1_FP) GetProcAddress(gLibRTC,"n_write_da_1");
	n_write_da_2 = (N_WRITE_DA_2_FP) GetProcAddress(gLibRTC,"n_write_da_2");
	write_io_port_mask = (WRITE_IO_PORT_MASK_FP) GetProcAddress(gLibRTC,"write_io_port_mask");
	write_8bit_port = (WRITE_8BIT_PORT_FP) GetProcAddress(gLibRTC,"write_8bit_port");
	read_io_port = (READ_IO_PORT_FP) GetProcAddress(gLibRTC,"read_io_port");
	read_io_port_buffer = (READ_IO_PORT_BUFFER_FP) GetProcAddress(gLibRTC,"read_io_port_buffer");
	get_io_status = (GET_IO_STATUS_FP) GetProcAddress(gLibRTC,"get_io_status");
	read_analog_in = (READ_ANALOG_IN_FP) GetProcAddress(gLibRTC,"read_analog_in");
	write_da_x = (WRITE_DA_X_FP) GetProcAddress(gLibRTC,"write_da_x");
	set_laser_off_default = (SET_LASER_OFF_DEFAULT_FP) GetProcAddress(gLibRTC,"set_laser_off_default");
	set_port_default = (SET_PORT_DEFAULT_FP) GetProcAddress(gLibRTC,"set_port_default");
	write_io_port = (WRITE_IO_PORT_FP) GetProcAddress(gLibRTC,"write_io_port");
	write_da_1 = (WRITE_DA_1_FP) GetProcAddress(gLibRTC,"write_da_1");
	write_da_2 = (WRITE_DA_2_FP) GetProcAddress(gLibRTC,"write_da_2");
	n_disable_laser = (N_DISABLE_LASER_FP) GetProcAddress(gLibRTC,"n_disable_laser");
	n_enable_laser = (N_ENABLE_LASER_FP) GetProcAddress(gLibRTC,"n_enable_laser");
	n_laser_signal_on = (N_LASER_SIGNAL_ON_FP) GetProcAddress(gLibRTC,"n_laser_signal_on");
	n_laser_signal_off = (N_LASER_SIGNAL_OFF_FP) GetProcAddress(gLibRTC,"n_laser_signal_off");
	n_set_standby = (N_SET_STANDBY_FP) GetProcAddress(gLibRTC,"n_set_standby");
	n_set_laser_pulses_ctrl = (N_SET_LASER_PULSES_CTRL_FP) GetProcAddress(gLibRTC,"n_set_laser_pulses_ctrl");
	n_set_firstpulse_killer = (N_SET_FIRSTPULSE_KILLER_FP) GetProcAddress(gLibRTC,"n_set_firstpulse_killer");
	n_set_qswitch_delay = (N_SET_QSWITCH_DELAY_FP) GetProcAddress(gLibRTC,"n_set_qswitch_delay");
	n_set_laser_mode = (N_SET_LASER_MODE_FP) GetProcAddress(gLibRTC,"n_set_laser_mode");
	n_set_laser_control = (N_SET_LASER_CONTROL_FP) GetProcAddress(gLibRTC,"n_set_laser_control");
	n_set_laser_pin_out = (N_SET_LASER_PIN_OUT_FP) GetProcAddress(gLibRTC,"n_set_laser_pin_out");
	n_get_laser_pin_in = (N_GET_LASER_PIN_IN_FP) GetProcAddress(gLibRTC,"n_get_laser_pin_in");
	n_set_softstart_level = (N_SET_SOFTSTART_LEVEL_FP) GetProcAddress(gLibRTC,"n_set_softstart_level");
	n_set_softstart_mode = (N_SET_SOFTSTART_MODE_FP) GetProcAddress(gLibRTC,"n_set_softstart_mode");
	n_set_auto_laser_control = (N_SET_AUTO_LASER_CONTROL_FP) GetProcAddress(gLibRTC,"n_set_auto_laser_control");
	n_set_auto_laser_params = (N_SET_AUTO_LASER_PARAMS_FP) GetProcAddress(gLibRTC,"n_set_auto_laser_params");
	n_load_auto_laser_control = (N_LOAD_AUTO_LASER_CONTROL_FP) GetProcAddress(gLibRTC,"n_load_auto_laser_control");
	n_load_position_control = (N_LOAD_POSITION_CONTROL_FP) GetProcAddress(gLibRTC,"n_load_position_control");
	n_set_default_pixel = (N_SET_DEFAULT_PIXEL_FP) GetProcAddress(gLibRTC,"n_set_default_pixel");
	n_get_standby = (N_GET_STANDBY_FP) GetProcAddress(gLibRTC,"n_get_standby");
	n_set_pulse_picking = (N_SET_PULSE_PICKING_FP) GetProcAddress(gLibRTC,"n_set_pulse_picking");
	n_set_pulse_picking_length = (N_SET_PULSE_PICKING_LENGTH_FP) GetProcAddress(gLibRTC,"n_set_pulse_picking_length");
	n_config_laser_signals = (N_CONFIG_LASER_SIGNALS_FP) GetProcAddress(gLibRTC,"n_config_laser_signals");
	disable_laser = (DISABLE_LASER_FP) GetProcAddress(gLibRTC,"disable_laser");
	enable_laser = (ENABLE_LASER_FP) GetProcAddress(gLibRTC,"enable_laser");
	laser_signal_on = (LASER_SIGNAL_ON_FP) GetProcAddress(gLibRTC,"laser_signal_on");
	laser_signal_off = (LASER_SIGNAL_OFF_FP) GetProcAddress(gLibRTC,"laser_signal_off");
	set_standby = (SET_STANDBY_FP) GetProcAddress(gLibRTC,"set_standby");
	set_laser_pulses_ctrl = (SET_LASER_PULSES_CTRL_FP) GetProcAddress(gLibRTC,"set_laser_pulses_ctrl");
	set_firstpulse_killer = (SET_FIRSTPULSE_KILLER_FP) GetProcAddress(gLibRTC,"set_firstpulse_killer");
	set_qswitch_delay = (SET_QSWITCH_DELAY_FP) GetProcAddress(gLibRTC,"set_qswitch_delay");
	set_laser_mode = (SET_LASER_MODE_FP) GetProcAddress(gLibRTC,"set_laser_mode");
	set_laser_control = (SET_LASER_CONTROL_FP) GetProcAddress(gLibRTC,"set_laser_control");
	set_laser_pin_out = (SET_LASER_PIN_OUT_FP) GetProcAddress(gLibRTC,"set_laser_pin_out");
	get_laser_pin_in = (GET_LASER_PIN_IN_FP) GetProcAddress(gLibRTC,"get_laser_pin_in");
	set_softstart_level = (SET_SOFTSTART_LEVEL_FP) GetProcAddress(gLibRTC,"set_softstart_level");
	set_softstart_mode = (SET_SOFTSTART_MODE_FP) GetProcAddress(gLibRTC,"set_softstart_mode");
	set_auto_laser_control = (SET_AUTO_LASER_CONTROL_FP) GetProcAddress(gLibRTC,"set_auto_laser_control");
	set_auto_laser_params = (SET_AUTO_LASER_PARAMS_FP) GetProcAddress(gLibRTC,"set_auto_laser_params");
	load_auto_laser_control = (LOAD_AUTO_LASER_CONTROL_FP) GetProcAddress(gLibRTC,"load_auto_laser_control");
	load_position_control = (LOAD_POSITION_CONTROL_FP) GetProcAddress(gLibRTC,"load_position_control");
	set_default_pixel = (SET_DEFAULT_PIXEL_FP) GetProcAddress(gLibRTC,"set_default_pixel");
	get_standby = (GET_STANDBY_FP) GetProcAddress(gLibRTC,"get_standby");
	set_pulse_picking = (SET_PULSE_PICKING_FP) GetProcAddress(gLibRTC,"set_pulse_picking");
	set_pulse_picking_length = (SET_PULSE_PICKING_LENGTH_FP) GetProcAddress(gLibRTC,"set_pulse_picking_length");
	config_laser_signals = (CONFIG_LASER_SIGNALS_FP) GetProcAddress(gLibRTC,"config_laser_signals");
	n_set_ext_start_delay = (N_SET_EXT_START_DELAY_FP) GetProcAddress(gLibRTC,"n_set_ext_start_delay");
	n_set_rot_center = (N_SET_ROT_CENTER_FP) GetProcAddress(gLibRTC,"n_set_rot_center");
	n_simulate_encoder = (N_SIMULATE_ENCODER_FP) GetProcAddress(gLibRTC,"n_simulate_encoder");
	n_get_marking_info = (N_GET_MARKING_INFO_FP) GetProcAddress(gLibRTC,"n_get_marking_info");
	n_set_encoder_speed_ctrl = (N_SET_ENCODER_SPEED_CTRL_FP) GetProcAddress(gLibRTC,"n_set_encoder_speed_ctrl");
	n_set_mcbsp_x = (N_SET_MCBSP_X_FP) GetProcAddress(gLibRTC,"n_set_mcbsp_x");
	n_set_mcbsp_y = (N_SET_MCBSP_Y_FP) GetProcAddress(gLibRTC,"n_set_mcbsp_y");
	n_set_mcbsp_rot = (N_SET_MCBSP_ROT_FP) GetProcAddress(gLibRTC,"n_set_mcbsp_rot");
	n_set_mcbsp_matrix = (N_SET_MCBSP_MATRIX_FP) GetProcAddress(gLibRTC,"n_set_mcbsp_matrix");
	n_set_mcbsp_in = (N_SET_MCBSP_IN_FP) GetProcAddress(gLibRTC,"n_set_mcbsp_in");
	n_set_multi_mcbsp_in = (N_SET_MULTI_MCBSP_IN_FP) GetProcAddress(gLibRTC,"n_set_multi_mcbsp_in");
	n_set_fly_tracking_error = (N_SET_FLY_TRACKING_ERROR_FP) GetProcAddress(gLibRTC,"n_set_fly_tracking_error");
	n_load_fly_2d_table = (N_LOAD_FLY_2D_TABLE_FP) GetProcAddress(gLibRTC,"n_load_fly_2d_table");
	n_init_fly_2d = (N_INIT_FLY_2D_FP) GetProcAddress(gLibRTC,"n_init_fly_2d");
	n_get_fly_2d_offset = (N_GET_FLY_2D_OFFSET_FP) GetProcAddress(gLibRTC,"n_get_fly_2d_offset");
	n_get_encoder = (N_GET_ENCODER_FP) GetProcAddress(gLibRTC,"n_get_encoder");
	n_read_encoder = (N_READ_ENCODER_FP) GetProcAddress(gLibRTC,"n_read_encoder");
	n_get_mcbsp = (N_GET_MCBSP_FP) GetProcAddress(gLibRTC,"n_get_mcbsp");
	n_read_mcbsp = (N_READ_MCBSP_FP) GetProcAddress(gLibRTC,"n_read_mcbsp");
	n_read_multi_mcbsp = (N_READ_MULTI_MCBSP_FP) GetProcAddress(gLibRTC,"n_read_multi_mcbsp");
	set_ext_start_delay = (SET_EXT_START_DELAY_FP) GetProcAddress(gLibRTC,"set_ext_start_delay");
	set_rot_center = (SET_ROT_CENTER_FP) GetProcAddress(gLibRTC,"set_rot_center");
	simulate_encoder = (SIMULATE_ENCODER_FP) GetProcAddress(gLibRTC,"simulate_encoder");
	get_marking_info = (GET_MARKING_INFO_FP) GetProcAddress(gLibRTC,"get_marking_info");
	set_encoder_speed_ctrl = (SET_ENCODER_SPEED_CTRL_FP) GetProcAddress(gLibRTC,"set_encoder_speed_ctrl");
	set_mcbsp_x = (SET_MCBSP_X_FP) GetProcAddress(gLibRTC,"set_mcbsp_x");
	set_mcbsp_y = (SET_MCBSP_Y_FP) GetProcAddress(gLibRTC,"set_mcbsp_y");
	set_mcbsp_rot = (SET_MCBSP_ROT_FP) GetProcAddress(gLibRTC,"set_mcbsp_rot");
	set_mcbsp_matrix = (SET_MCBSP_MATRIX_FP) GetProcAddress(gLibRTC,"set_mcbsp_matrix");
	set_mcbsp_in = (SET_MCBSP_IN_FP) GetProcAddress(gLibRTC,"set_mcbsp_in");
	set_multi_mcbsp_in = (SET_MULTI_MCBSP_IN_FP) GetProcAddress(gLibRTC,"set_multi_mcbsp_in");
	set_fly_tracking_error = (SET_FLY_TRACKING_ERROR_FP) GetProcAddress(gLibRTC,"set_fly_tracking_error");
	load_fly_2d_table = (LOAD_FLY_2D_TABLE_FP) GetProcAddress(gLibRTC,"load_fly_2d_table");
	init_fly_2d = (INIT_FLY_2D_FP) GetProcAddress(gLibRTC,"init_fly_2d");
	get_fly_2d_offset = (GET_FLY_2D_OFFSET_FP) GetProcAddress(gLibRTC,"get_fly_2d_offset");
	get_encoder = (GET_ENCODER_FP) GetProcAddress(gLibRTC,"get_encoder");
	read_encoder = (READ_ENCODER_FP) GetProcAddress(gLibRTC,"read_encoder");
	get_mcbsp = (GET_MCBSP_FP) GetProcAddress(gLibRTC,"get_mcbsp");
	read_mcbsp = (READ_MCBSP_FP) GetProcAddress(gLibRTC,"read_mcbsp");
	read_multi_mcbsp = (READ_MULTI_MCBSP_FP) GetProcAddress(gLibRTC,"read_multi_mcbsp");
	n_get_time = (N_GET_TIME_FP) GetProcAddress(gLibRTC,"n_get_time");
	n_get_lap_time = (N_GET_LAP_TIME_FP) GetProcAddress(gLibRTC,"n_get_lap_time");
	n_measurement_status = (N_MEASUREMENT_STATUS_FP) GetProcAddress(gLibRTC,"n_measurement_status");
	n_get_waveform = (N_GET_WAVEFORM_FP) GetProcAddress(gLibRTC,"n_get_waveform");
	n_bounce_supp = (N_BOUNCE_SUPP_FP) GetProcAddress(gLibRTC,"n_bounce_supp");
	n_home_position_xyz = (N_HOME_POSITION_XYZ_FP) GetProcAddress(gLibRTC,"n_home_position_xyz");
	n_home_position = (N_HOME_POSITION_FP) GetProcAddress(gLibRTC,"n_home_position");
	n_rs232_config = (N_RS232_CONFIG_FP) GetProcAddress(gLibRTC,"n_rs232_config");
	n_rs232_write_data = (N_RS232_WRITE_DATA_FP) GetProcAddress(gLibRTC,"n_rs232_write_data");
	n_rs232_write_text = (N_RS232_WRITE_TEXT_FP) GetProcAddress(gLibRTC,"n_rs232_write_text");
	n_rs232_read_data = (N_RS232_READ_DATA_FP) GetProcAddress(gLibRTC,"n_rs232_read_data");
	n_set_mcbsp_freq = (N_SET_MCBSP_FREQ_FP) GetProcAddress(gLibRTC,"n_set_mcbsp_freq");
	n_mcbsp_init = (N_MCBSP_INIT_FP) GetProcAddress(gLibRTC,"n_mcbsp_init");
	n_mcbsp_init_spi = (N_MCBSP_INIT_SPI_FP) GetProcAddress(gLibRTC,"n_mcbsp_init_spi");
	n_get_overrun = (N_GET_OVERRUN_FP) GetProcAddress(gLibRTC,"n_get_overrun");
	n_get_master_slave = (N_GET_MASTER_SLAVE_FP) GetProcAddress(gLibRTC,"n_get_master_slave");
	n_get_transform = (N_GET_TRANSFORM_FP) GetProcAddress(gLibRTC,"n_get_transform");
	n_stop_trigger = (N_STOP_TRIGGER_FP) GetProcAddress(gLibRTC,"n_stop_trigger");
	n_move_to = (N_MOVE_TO_FP) GetProcAddress(gLibRTC,"n_move_to");
	n_set_enduring_wobbel = (N_SET_ENDURING_WOBBEL_FP) GetProcAddress(gLibRTC,"n_set_enduring_wobbel");
	n_set_enduring_wobbel_2 = (N_SET_ENDURING_WOBBEL_2_FP) GetProcAddress(gLibRTC,"n_set_enduring_wobbel_2");
	n_set_free_variable = (N_SET_FREE_VARIABLE_FP) GetProcAddress(gLibRTC,"n_set_free_variable");
	n_get_free_variable = (N_GET_FREE_VARIABLE_FP) GetProcAddress(gLibRTC,"n_get_free_variable");
	n_set_mcbsp_out_ptr = (N_SET_MCBSP_OUT_PTR_FP) GetProcAddress(gLibRTC,"n_set_mcbsp_out_ptr");
	n_periodic_toggle = (N_PERIODIC_TOGGLE_FP) GetProcAddress(gLibRTC,"n_periodic_toggle");
	get_time = (GET_TIME_FP) GetProcAddress(gLibRTC,"get_time");
	get_lap_time = (GET_LAP_TIME_FP) GetProcAddress(gLibRTC,"get_lap_time");
	measurement_status = (MEASUREMENT_STATUS_FP) GetProcAddress(gLibRTC,"measurement_status");
	get_waveform = (GET_WAVEFORM_FP) GetProcAddress(gLibRTC,"get_waveform");
	bounce_supp = (BOUNCE_SUPP_FP) GetProcAddress(gLibRTC,"bounce_supp");
	home_position_xyz = (HOME_POSITION_XYZ_FP) GetProcAddress(gLibRTC,"home_position_xyz");
	home_position = (HOME_POSITION_FP) GetProcAddress(gLibRTC,"home_position");
	rs232_config = (RS232_CONFIG_FP) GetProcAddress(gLibRTC,"rs232_config");
	rs232_write_data = (RS232_WRITE_DATA_FP) GetProcAddress(gLibRTC,"rs232_write_data");
	rs232_write_text = (RS232_WRITE_TEXT_FP) GetProcAddress(gLibRTC,"rs232_write_text");
	rs232_read_data = (RS232_READ_DATA_FP) GetProcAddress(gLibRTC,"rs232_read_data");
	set_mcbsp_freq = (SET_MCBSP_FREQ_FP) GetProcAddress(gLibRTC,"set_mcbsp_freq");
	mcbsp_init = (MCBSP_INIT_FP) GetProcAddress(gLibRTC,"mcbsp_init");
	mcbsp_init_spi = (MCBSP_INIT_SPI_FP) GetProcAddress(gLibRTC,"mcbsp_init_spi");
	get_overrun = (GET_OVERRUN_FP) GetProcAddress(gLibRTC,"get_overrun");
	get_master_slave = (GET_MASTER_SLAVE_FP) GetProcAddress(gLibRTC,"get_master_slave");
	get_transform = (GET_TRANSFORM_FP) GetProcAddress(gLibRTC,"get_transform");
	stop_trigger = (STOP_TRIGGER_FP) GetProcAddress(gLibRTC,"stop_trigger");
	move_to = (MOVE_TO_FP) GetProcAddress(gLibRTC,"move_to");
	set_enduring_wobbel = (SET_ENDURING_WOBBEL_FP) GetProcAddress(gLibRTC,"set_enduring_wobbel");
	set_enduring_wobbel_2 = (SET_ENDURING_WOBBEL_2_FP) GetProcAddress(gLibRTC,"set_enduring_wobbel_2");
	set_free_variable = (SET_FREE_VARIABLE_FP) GetProcAddress(gLibRTC,"set_free_variable");
	get_free_variable = (GET_FREE_VARIABLE_FP) GetProcAddress(gLibRTC,"get_free_variable");
	set_mcbsp_out_ptr = (SET_MCBSP_OUT_PTR_FP) GetProcAddress(gLibRTC,"set_mcbsp_out_ptr");
	periodic_toggle = (PERIODIC_TOGGLE_FP) GetProcAddress(gLibRTC,"periodic_toggle");
	n_set_defocus = (N_SET_DEFOCUS_FP) GetProcAddress(gLibRTC,"n_set_defocus");
	n_set_defocus_offset = (N_SET_DEFOCUS_OFFSET_FP) GetProcAddress(gLibRTC,"n_set_defocus_offset");
	n_goto_xyz = (N_GOTO_XYZ_FP) GetProcAddress(gLibRTC,"n_goto_xyz");
	n_set_zoom = (N_SET_ZOOM_FP) GetProcAddress(gLibRTC,"n_set_zoom");
	n_goto_xy = (N_GOTO_XY_FP) GetProcAddress(gLibRTC,"n_goto_xy");
	n_get_z_distance = (N_GET_Z_DISTANCE_FP) GetProcAddress(gLibRTC,"n_get_z_distance");
	set_defocus = (SET_DEFOCUS_FP) GetProcAddress(gLibRTC,"set_defocus");
	set_defocus_offset = (SET_DEFOCUS_OFFSET_FP) GetProcAddress(gLibRTC,"set_defocus_offset");
	goto_xyz = (GOTO_XYZ_FP) GetProcAddress(gLibRTC,"goto_xyz");
	goto_xy = (GOTO_XY_FP) GetProcAddress(gLibRTC,"goto_xy");
	set_zoom = (SET_ZOOM_FP) GetProcAddress(gLibRTC,"set_zoom");
	get_z_distance = (GET_Z_DISTANCE_FP) GetProcAddress(gLibRTC,"get_z_distance");
	n_set_offset_xyz = (N_SET_OFFSET_XYZ_FP) GetProcAddress(gLibRTC,"n_set_offset_xyz");
	n_set_offset = (N_SET_OFFSET_FP) GetProcAddress(gLibRTC,"n_set_offset");
	n_set_matrix = (N_SET_MATRIX_FP) GetProcAddress(gLibRTC,"n_set_matrix");
	n_set_angle = (N_SET_ANGLE_FP) GetProcAddress(gLibRTC,"n_set_angle");
	n_set_scale = (N_SET_SCALE_FP) GetProcAddress(gLibRTC,"n_set_scale");
	n_apply_mcbsp = (N_APPLY_MCBSP_FP) GetProcAddress(gLibRTC,"n_apply_mcbsp");
	n_upload_transform = (N_UPLOAD_TRANSFORM_FP) GetProcAddress(gLibRTC,"n_upload_transform");
	set_offset_xyz = (SET_OFFSET_XYZ_FP) GetProcAddress(gLibRTC,"set_offset_xyz");
	set_offset = (SET_OFFSET_FP) GetProcAddress(gLibRTC,"set_offset");
	set_matrix = (SET_MATRIX_FP) GetProcAddress(gLibRTC,"set_matrix");
	set_angle = (SET_ANGLE_FP) GetProcAddress(gLibRTC,"set_angle");
	set_scale = (SET_SCALE_FP) GetProcAddress(gLibRTC,"set_scale");
	apply_mcbsp = (APPLY_MCBSP_FP) GetProcAddress(gLibRTC,"apply_mcbsp");
	upload_transform = (UPLOAD_TRANSFORM_FP) GetProcAddress(gLibRTC,"upload_transform");
	transform = (TRANSFORM_FP) GetProcAddress(gLibRTC,"transform");
	n_set_delay_mode = (N_SET_DELAY_MODE_FP) GetProcAddress(gLibRTC,"n_set_delay_mode");
	n_set_jump_speed_ctrl = (N_SET_JUMP_SPEED_CTRL_FP) GetProcAddress(gLibRTC,"n_set_jump_speed_ctrl");
	n_set_mark_speed_ctrl = (N_SET_MARK_SPEED_CTRL_FP) GetProcAddress(gLibRTC,"n_set_mark_speed_ctrl");
	n_set_sky_writing_para = (N_SET_SKY_WRITING_PARA_FP) GetProcAddress(gLibRTC,"n_set_sky_writing_para");
	n_set_sky_writing_limit = (N_SET_SKY_WRITING_LIMIT_FP) GetProcAddress(gLibRTC,"n_set_sky_writing_limit");
	n_set_sky_writing_mode = (N_SET_SKY_WRITING_MODE_FP) GetProcAddress(gLibRTC,"n_set_sky_writing_mode");
	n_load_varpolydelay = (N_LOAD_VARPOLYDELAY_FP) GetProcAddress(gLibRTC,"n_load_varpolydelay");
	n_set_hi = (N_SET_HI_FP) GetProcAddress(gLibRTC,"n_set_hi");
	n_get_hi_pos = (N_GET_HI_POS_FP) GetProcAddress(gLibRTC,"n_get_hi_pos");
	n_auto_cal = (N_AUTO_CAL_FP) GetProcAddress(gLibRTC,"n_auto_cal");
	n_get_auto_cal = (N_GET_AUTO_CAL_FP) GetProcAddress(gLibRTC,"n_get_auto_cal");
	n_write_hi_pos = (N_WRITE_HI_POS_FP) GetProcAddress(gLibRTC,"n_write_hi_pos");
	n_set_sky_writing = (N_SET_SKY_WRITING_FP) GetProcAddress(gLibRTC,"n_set_sky_writing");
	n_get_hi_data = (N_GET_HI_DATA_FP) GetProcAddress(gLibRTC,"n_get_hi_data");
	set_delay_mode = (SET_DELAY_MODE_FP) GetProcAddress(gLibRTC,"set_delay_mode");
	set_jump_speed_ctrl = (SET_JUMP_SPEED_CTRL_FP) GetProcAddress(gLibRTC,"set_jump_speed_ctrl");
	set_mark_speed_ctrl = (SET_MARK_SPEED_CTRL_FP) GetProcAddress(gLibRTC,"set_mark_speed_ctrl");
	set_sky_writing_para = (SET_SKY_WRITING_PARA_FP) GetProcAddress(gLibRTC,"set_sky_writing_para");
	set_sky_writing_limit = (SET_SKY_WRITING_LIMIT_FP) GetProcAddress(gLibRTC,"set_sky_writing_limit");
	set_sky_writing_mode = (SET_SKY_WRITING_MODE_FP) GetProcAddress(gLibRTC,"set_sky_writing_mode");
	load_varpolydelay = (LOAD_VARPOLYDELAY_FP) GetProcAddress(gLibRTC,"load_varpolydelay");
	set_hi = (SET_HI_FP) GetProcAddress(gLibRTC,"set_hi");
	get_hi_pos = (GET_HI_POS_FP) GetProcAddress(gLibRTC,"get_hi_pos");
	auto_cal = (AUTO_CAL_FP) GetProcAddress(gLibRTC,"auto_cal");
	get_auto_cal = (GET_AUTO_CAL_FP) GetProcAddress(gLibRTC,"get_auto_cal");
	write_hi_pos = (WRITE_HI_POS_FP) GetProcAddress(gLibRTC,"write_hi_pos");
	set_sky_writing = (SET_SKY_WRITING_FP) GetProcAddress(gLibRTC,"set_sky_writing");
	get_hi_data = (GET_HI_DATA_FP) GetProcAddress(gLibRTC,"get_hi_data");
	n_send_user_data = (N_SEND_USER_DATA_FP) GetProcAddress(gLibRTC,"n_send_user_data");
	n_read_user_data = (N_READ_USER_DATA_FP) GetProcAddress(gLibRTC,"n_read_user_data");
	n_control_command = (N_CONTROL_COMMAND_FP) GetProcAddress(gLibRTC,"n_control_command");
	n_get_value = (N_GET_VALUE_FP) GetProcAddress(gLibRTC,"n_get_value");
	n_get_values = (N_GET_VALUES_FP) GetProcAddress(gLibRTC,"n_get_values");
	n_get_galvo_controls = (N_GET_GALVO_CONTROLS_FP) GetProcAddress(gLibRTC,"n_get_galvo_controls");
	n_get_head_status = (N_GET_HEAD_STATUS_FP) GetProcAddress(gLibRTC,"n_get_head_status");
	n_set_jump_mode = (N_SET_JUMP_MODE_FP) GetProcAddress(gLibRTC,"n_set_jump_mode");
	n_load_jump_table_offset = (N_LOAD_JUMP_TABLE_OFFSET_FP) GetProcAddress(gLibRTC,"n_load_jump_table_offset");
	n_get_jump_table = (N_GET_JUMP_TABLE_FP) GetProcAddress(gLibRTC,"n_get_jump_table");
	n_set_jump_table = (N_SET_JUMP_TABLE_FP) GetProcAddress(gLibRTC,"n_set_jump_table");
	n_load_jump_table = (N_LOAD_JUMP_TABLE_FP) GetProcAddress(gLibRTC,"n_load_jump_table");
	send_user_data = (SEND_USER_DATA_FP) GetProcAddress(gLibRTC,"send_user_data");
	read_user_data = (READ_USER_DATA_FP) GetProcAddress(gLibRTC,"read_user_data");
	control_command = (CONTROL_COMMAND_FP) GetProcAddress(gLibRTC,"control_command");
	get_value = (GET_VALUE_FP) GetProcAddress(gLibRTC,"get_value");
	get_values = (GET_VALUES_FP) GetProcAddress(gLibRTC,"get_values");
	get_galvo_controls = (GET_GALVO_CONTROLS_FP) GetProcAddress(gLibRTC,"get_galvo_controls");
	get_head_status = (GET_HEAD_STATUS_FP) GetProcAddress(gLibRTC,"get_head_status");
	set_jump_mode = (SET_JUMP_MODE_FP) GetProcAddress(gLibRTC,"set_jump_mode");
	load_jump_table_offset = (LOAD_JUMP_TABLE_OFFSET_FP) GetProcAddress(gLibRTC,"load_jump_table_offset");
	get_jump_table = (GET_JUMP_TABLE_FP) GetProcAddress(gLibRTC,"get_jump_table");
	set_jump_table = (SET_JUMP_TABLE_FP) GetProcAddress(gLibRTC,"set_jump_table");
	load_jump_table = (LOAD_JUMP_TABLE_FP) GetProcAddress(gLibRTC,"load_jump_table");
	n_stepper_init = (N_STEPPER_INIT_FP) GetProcAddress(gLibRTC,"n_stepper_init");
	n_stepper_enable = (N_STEPPER_ENABLE_FP) GetProcAddress(gLibRTC,"n_stepper_enable");
	n_stepper_disable_switch = (N_STEPPER_DISABLE_SWITCH_FP) GetProcAddress(gLibRTC,"n_stepper_disable_switch");
	n_stepper_control = (N_STEPPER_CONTROL_FP) GetProcAddress(gLibRTC,"n_stepper_control");
	n_stepper_abs_no = (N_STEPPER_ABS_NO_FP) GetProcAddress(gLibRTC,"n_stepper_abs_no");
	n_stepper_rel_no = (N_STEPPER_REL_NO_FP) GetProcAddress(gLibRTC,"n_stepper_rel_no");
	n_stepper_abs = (N_STEPPER_ABS_FP) GetProcAddress(gLibRTC,"n_stepper_abs");
	n_stepper_rel = (N_STEPPER_REL_FP) GetProcAddress(gLibRTC,"n_stepper_rel");
	n_get_stepper_status = (N_GET_STEPPER_STATUS_FP) GetProcAddress(gLibRTC,"n_get_stepper_status");
	stepper_init = (STEPPER_INIT_FP) GetProcAddress(gLibRTC,"stepper_init");
	stepper_enable = (STEPPER_ENABLE_FP) GetProcAddress(gLibRTC,"stepper_enable");
	stepper_disable_switch = (STEPPER_DISABLE_SWITCH_FP) GetProcAddress(gLibRTC,"stepper_disable_switch");
	stepper_control = (STEPPER_CONTROL_FP) GetProcAddress(gLibRTC,"stepper_control");
	stepper_abs_no = (STEPPER_ABS_NO_FP) GetProcAddress(gLibRTC,"stepper_abs_no");
	stepper_rel_no = (STEPPER_REL_NO_FP) GetProcAddress(gLibRTC,"stepper_rel_no");
	stepper_abs = (STEPPER_ABS_FP) GetProcAddress(gLibRTC,"stepper_abs");
	stepper_rel = (STEPPER_REL_FP) GetProcAddress(gLibRTC,"stepper_rel");
	get_stepper_status = (GET_STEPPER_STATUS_FP) GetProcAddress(gLibRTC,"get_stepper_status");
	n_select_cor_table_list = (N_SELECT_COR_TABLE_LIST_FP) GetProcAddress(gLibRTC,"n_select_cor_table_list");
	select_cor_table_list = (SELECT_COR_TABLE_LIST_FP) GetProcAddress(gLibRTC,"select_cor_table_list");
	n_list_nop = (N_LIST_NOP_FP) GetProcAddress(gLibRTC,"n_list_nop");
	n_list_continue = (N_LIST_CONTINUE_FP) GetProcAddress(gLibRTC,"n_list_continue");
	n_list_next = (N_LIST_NEXT_FP) GetProcAddress(gLibRTC,"n_list_next");
	n_long_delay = (N_LONG_DELAY_FP) GetProcAddress(gLibRTC,"n_long_delay");
	n_set_end_of_list = (N_SET_END_OF_LIST_FP) GetProcAddress(gLibRTC,"n_set_end_of_list");
	n_set_wait = (N_SET_WAIT_FP) GetProcAddress(gLibRTC,"n_set_wait");
	n_list_jump_pos = (N_LIST_JUMP_POS_FP) GetProcAddress(gLibRTC,"n_list_jump_pos");
	n_list_jump_rel = (N_LIST_JUMP_REL_FP) GetProcAddress(gLibRTC,"n_list_jump_rel");
	n_list_repeat = (N_LIST_REPEAT_FP) GetProcAddress(gLibRTC,"n_list_repeat");
	n_list_until = (N_LIST_UNTIL_FP) GetProcAddress(gLibRTC,"n_list_until");
	n_range_checking = (N_RANGE_CHECKING_FP) GetProcAddress(gLibRTC,"n_range_checking");
	n_set_list_jump = (N_SET_LIST_JUMP_FP) GetProcAddress(gLibRTC,"n_set_list_jump");
	list_nop = (LIST_NOP_FP) GetProcAddress(gLibRTC,"list_nop");
	list_continue = (LIST_CONTINUE_FP) GetProcAddress(gLibRTC,"list_continue");
	list_next = (LIST_NEXT_FP) GetProcAddress(gLibRTC,"list_next");
	long_delay = (LONG_DELAY_FP) GetProcAddress(gLibRTC,"long_delay");
	set_end_of_list = (SET_END_OF_LIST_FP) GetProcAddress(gLibRTC,"set_end_of_list");
	set_wait = (SET_WAIT_FP) GetProcAddress(gLibRTC,"set_wait");
	list_jump_pos = (LIST_JUMP_POS_FP) GetProcAddress(gLibRTC,"list_jump_pos");
	list_jump_rel = (LIST_JUMP_REL_FP) GetProcAddress(gLibRTC,"list_jump_rel");
	list_repeat = (LIST_REPEAT_FP) GetProcAddress(gLibRTC,"list_repeat");
	list_until = (LIST_UNTIL_FP) GetProcAddress(gLibRTC,"list_until");
	range_checking = (RANGE_CHECKING_FP) GetProcAddress(gLibRTC,"range_checking");
	set_list_jump = (SET_LIST_JUMP_FP) GetProcAddress(gLibRTC,"set_list_jump");
	n_set_extstartpos_list = (N_SET_EXTSTARTPOS_LIST_FP) GetProcAddress(gLibRTC,"n_set_extstartpos_list");
	n_set_control_mode_list = (N_SET_CONTROL_MODE_LIST_FP) GetProcAddress(gLibRTC,"n_set_control_mode_list");
	n_simulate_ext_start = (N_SIMULATE_EXT_START_FP) GetProcAddress(gLibRTC,"n_simulate_ext_start");
	set_extstartpos_list = (SET_EXTSTARTPOS_LIST_FP) GetProcAddress(gLibRTC,"set_extstartpos_list");
	set_control_mode_list = (SET_CONTROL_MODE_LIST_FP) GetProcAddress(gLibRTC,"set_control_mode_list");
	simulate_ext_start = (SIMULATE_EXT_START_FP) GetProcAddress(gLibRTC,"simulate_ext_start");
	n_list_return = (N_LIST_RETURN_FP) GetProcAddress(gLibRTC,"n_list_return");
	n_list_call_repeat = (N_LIST_CALL_REPEAT_FP) GetProcAddress(gLibRTC,"n_list_call_repeat");
	n_list_call_abs_repeat = (N_LIST_CALL_ABS_REPEAT_FP) GetProcAddress(gLibRTC,"n_list_call_abs_repeat");
	n_list_call = (N_LIST_CALL_FP) GetProcAddress(gLibRTC,"n_list_call");
	n_list_call_abs = (N_LIST_CALL_ABS_FP) GetProcAddress(gLibRTC,"n_list_call_abs");
	n_sub_call_repeat = (N_SUB_CALL_REPEAT_FP) GetProcAddress(gLibRTC,"n_sub_call_repeat");
	n_sub_call_abs_repeat = (N_SUB_CALL_ABS_REPEAT_FP) GetProcAddress(gLibRTC,"n_sub_call_abs_repeat");
	n_sub_call = (N_SUB_CALL_FP) GetProcAddress(gLibRTC,"n_sub_call");
	n_sub_call_abs = (N_SUB_CALL_ABS_FP) GetProcAddress(gLibRTC,"n_sub_call_abs");
	list_return = (LIST_RETURN_FP) GetProcAddress(gLibRTC,"list_return");
	list_call_repeat = (LIST_CALL_REPEAT_FP) GetProcAddress(gLibRTC,"list_call_repeat");
	list_call_abs_repeat = (LIST_CALL_ABS_REPEAT_FP) GetProcAddress(gLibRTC,"list_call_abs_repeat");
	list_call = (LIST_CALL_FP) GetProcAddress(gLibRTC,"list_call");
	list_call_abs = (LIST_CALL_ABS_FP) GetProcAddress(gLibRTC,"list_call_abs");
	sub_call_repeat = (SUB_CALL_REPEAT_FP) GetProcAddress(gLibRTC,"sub_call_repeat");
	sub_call_abs_repeat = (SUB_CALL_ABS_REPEAT_FP) GetProcAddress(gLibRTC,"sub_call_abs_repeat");
	sub_call = (SUB_CALL_FP) GetProcAddress(gLibRTC,"sub_call");
	sub_call_abs = (SUB_CALL_ABS_FP) GetProcAddress(gLibRTC,"sub_call_abs");
	n_list_call_cond = (N_LIST_CALL_COND_FP) GetProcAddress(gLibRTC,"n_list_call_cond");
	n_list_call_abs_cond = (N_LIST_CALL_ABS_COND_FP) GetProcAddress(gLibRTC,"n_list_call_abs_cond");
	n_sub_call_cond = (N_SUB_CALL_COND_FP) GetProcAddress(gLibRTC,"n_sub_call_cond");
	n_sub_call_abs_cond = (N_SUB_CALL_ABS_COND_FP) GetProcAddress(gLibRTC,"n_sub_call_abs_cond");
	n_list_jump_pos_cond = (N_LIST_JUMP_POS_COND_FP) GetProcAddress(gLibRTC,"n_list_jump_pos_cond");
	n_list_jump_rel_cond = (N_LIST_JUMP_REL_COND_FP) GetProcAddress(gLibRTC,"n_list_jump_rel_cond");
	n_if_cond = (N_IF_COND_FP) GetProcAddress(gLibRTC,"n_if_cond");
	n_if_not_cond = (N_IF_NOT_COND_FP) GetProcAddress(gLibRTC,"n_if_not_cond");
	n_if_pin_cond = (N_IF_PIN_COND_FP) GetProcAddress(gLibRTC,"n_if_pin_cond");
	n_if_not_pin_cond = (N_IF_NOT_PIN_COND_FP) GetProcAddress(gLibRTC,"n_if_not_pin_cond");
	n_switch_ioport = (N_SWITCH_IOPORT_FP) GetProcAddress(gLibRTC,"n_switch_ioport");
	n_list_jump_cond = (N_LIST_JUMP_COND_FP) GetProcAddress(gLibRTC,"n_list_jump_cond");
	list_call_cond = (LIST_CALL_COND_FP) GetProcAddress(gLibRTC,"list_call_cond");
	list_call_abs_cond = (LIST_CALL_ABS_COND_FP) GetProcAddress(gLibRTC,"list_call_abs_cond");
	sub_call_cond = (SUB_CALL_COND_FP) GetProcAddress(gLibRTC,"sub_call_cond");
	sub_call_abs_cond = (SUB_CALL_ABS_COND_FP) GetProcAddress(gLibRTC,"sub_call_abs_cond");
	list_jump_pos_cond = (LIST_JUMP_POS_COND_FP) GetProcAddress(gLibRTC,"list_jump_pos_cond");
	list_jump_rel_cond = (LIST_JUMP_REL_COND_FP) GetProcAddress(gLibRTC,"list_jump_rel_cond");
	if_cond = (IF_COND_FP) GetProcAddress(gLibRTC,"if_cond");
	if_not_cond = (IF_NOT_COND_FP) GetProcAddress(gLibRTC,"if_not_cond");
	if_pin_cond = (IF_PIN_COND_FP) GetProcAddress(gLibRTC,"if_pin_cond");
	if_not_pin_cond = (IF_NOT_PIN_COND_FP) GetProcAddress(gLibRTC,"if_not_pin_cond");
	switch_ioport = (SWITCH_IOPORT_FP) GetProcAddress(gLibRTC,"switch_ioport");
	list_jump_cond = (LIST_JUMP_COND_FP) GetProcAddress(gLibRTC,"list_jump_cond");
	n_select_char_set = (N_SELECT_CHAR_SET_FP) GetProcAddress(gLibRTC,"n_select_char_set");
	n_mark_text = (N_MARK_TEXT_FP) GetProcAddress(gLibRTC,"n_mark_text");
	n_mark_text_abs = (N_MARK_TEXT_ABS_FP) GetProcAddress(gLibRTC,"n_mark_text_abs");
	n_mark_char = (N_MARK_CHAR_FP) GetProcAddress(gLibRTC,"n_mark_char");
	n_mark_char_abs = (N_MARK_CHAR_ABS_FP) GetProcAddress(gLibRTC,"n_mark_char_abs");
	select_char_set = (SELECT_CHAR_SET_FP) GetProcAddress(gLibRTC,"select_char_set");
	mark_text = (MARK_TEXT_FP) GetProcAddress(gLibRTC,"mark_text");
	mark_text_abs = (MARK_TEXT_ABS_FP) GetProcAddress(gLibRTC,"mark_text_abs");
	mark_char = (MARK_CHAR_FP) GetProcAddress(gLibRTC,"mark_char");
	mark_char_abs = (MARK_CHAR_ABS_FP) GetProcAddress(gLibRTC,"mark_char_abs");
	n_mark_serial = (N_MARK_SERIAL_FP) GetProcAddress(gLibRTC,"n_mark_serial");
	n_mark_serial_abs = (N_MARK_SERIAL_ABS_FP) GetProcAddress(gLibRTC,"n_mark_serial_abs");
	n_mark_date = (N_MARK_DATE_FP) GetProcAddress(gLibRTC,"n_mark_date");
	n_mark_date_abs = (N_MARK_DATE_ABS_FP) GetProcAddress(gLibRTC,"n_mark_date_abs");
	n_mark_time = (N_MARK_TIME_FP) GetProcAddress(gLibRTC,"n_mark_time");
	n_mark_time_abs = (N_MARK_TIME_ABS_FP) GetProcAddress(gLibRTC,"n_mark_time_abs");
	n_select_serial_set_list = (N_SELECT_SERIAL_SET_LIST_FP) GetProcAddress(gLibRTC,"n_select_serial_set_list");
	n_set_serial_step_list = (N_SET_SERIAL_STEP_LIST_FP) GetProcAddress(gLibRTC,"n_set_serial_step_list");
	n_time_fix_f_off = (N_TIME_FIX_F_OFF_FP) GetProcAddress(gLibRTC,"n_time_fix_f_off");
	n_time_fix_f = (N_TIME_FIX_F_FP) GetProcAddress(gLibRTC,"n_time_fix_f");
	n_time_fix = (N_TIME_FIX_FP) GetProcAddress(gLibRTC,"n_time_fix");
	mark_serial = (MARK_SERIAL_FP) GetProcAddress(gLibRTC,"mark_serial");
	mark_serial_abs = (MARK_SERIAL_ABS_FP) GetProcAddress(gLibRTC,"mark_serial_abs");
	mark_date = (MARK_DATE_FP) GetProcAddress(gLibRTC,"mark_date");
	mark_date_abs = (MARK_DATE_ABS_FP) GetProcAddress(gLibRTC,"mark_date_abs");
	mark_time = (MARK_TIME_FP) GetProcAddress(gLibRTC,"mark_time");
	mark_time_abs = (MARK_TIME_ABS_FP) GetProcAddress(gLibRTC,"mark_time_abs");
	time_fix_f_off = (TIME_FIX_F_OFF_FP) GetProcAddress(gLibRTC,"time_fix_f_off");
	select_serial_set_list = (SELECT_SERIAL_SET_LIST_FP) GetProcAddress(gLibRTC,"select_serial_set_list");
	set_serial_step_list = (SET_SERIAL_STEP_LIST_FP) GetProcAddress(gLibRTC,"set_serial_step_list");
	time_fix_f = (TIME_FIX_F_FP) GetProcAddress(gLibRTC,"time_fix_f");
	time_fix = (TIME_FIX_FP) GetProcAddress(gLibRTC,"time_fix");
	n_clear_io_cond_list = (N_CLEAR_IO_COND_LIST_FP) GetProcAddress(gLibRTC,"n_clear_io_cond_list");
	n_set_io_cond_list = (N_SET_IO_COND_LIST_FP) GetProcAddress(gLibRTC,"n_set_io_cond_list");
	n_write_io_port_mask_list = (N_WRITE_IO_PORT_MASK_LIST_FP) GetProcAddress(gLibRTC,"n_write_io_port_mask_list");
	n_write_8bit_port_list = (N_WRITE_8BIT_PORT_LIST_FP) GetProcAddress(gLibRTC,"n_write_8bit_port_list");
	n_read_io_port_list = (N_READ_IO_PORT_LIST_FP) GetProcAddress(gLibRTC,"n_read_io_port_list");
	n_write_da_x_list = (N_WRITE_DA_X_LIST_FP) GetProcAddress(gLibRTC,"n_write_da_x_list");
	n_write_io_port_list = (N_WRITE_IO_PORT_LIST_FP) GetProcAddress(gLibRTC,"n_write_io_port_list");
	n_write_da_1_list = (N_WRITE_DA_1_LIST_FP) GetProcAddress(gLibRTC,"n_write_da_1_list");
	n_write_da_2_list = (N_WRITE_DA_2_LIST_FP) GetProcAddress(gLibRTC,"n_write_da_2_list");
	clear_io_cond_list = (CLEAR_IO_COND_LIST_FP) GetProcAddress(gLibRTC,"clear_io_cond_list");
	set_io_cond_list = (SET_IO_COND_LIST_FP) GetProcAddress(gLibRTC,"set_io_cond_list");
	write_io_port_mask_list = (WRITE_IO_PORT_MASK_LIST_FP) GetProcAddress(gLibRTC,"write_io_port_mask_list");
	write_8bit_port_list = (WRITE_8BIT_PORT_LIST_FP) GetProcAddress(gLibRTC,"write_8bit_port_list");
	read_io_port_list = (READ_IO_PORT_LIST_FP) GetProcAddress(gLibRTC,"read_io_port_list");
	write_da_x_list = (WRITE_DA_X_LIST_FP) GetProcAddress(gLibRTC,"write_da_x_list");
	write_io_port_list = (WRITE_IO_PORT_LIST_FP) GetProcAddress(gLibRTC,"write_io_port_list");
	write_da_1_list = (WRITE_DA_1_LIST_FP) GetProcAddress(gLibRTC,"write_da_1_list");
	write_da_2_list = (WRITE_DA_2_LIST_FP) GetProcAddress(gLibRTC,"write_da_2_list");
	n_laser_signal_on_list = (N_LASER_SIGNAL_ON_LIST_FP) GetProcAddress(gLibRTC,"n_laser_signal_on_list");
	n_laser_signal_off_list = (N_LASER_SIGNAL_OFF_LIST_FP) GetProcAddress(gLibRTC,"n_laser_signal_off_list");
	n_para_laser_on_pulses_list = (N_PARA_LASER_ON_PULSES_LIST_FP) GetProcAddress(gLibRTC,"n_para_laser_on_pulses_list");
	n_laser_on_pulses_list = (N_LASER_ON_PULSES_LIST_FP) GetProcAddress(gLibRTC,"n_laser_on_pulses_list");
	n_laser_on_list = (N_LASER_ON_LIST_FP) GetProcAddress(gLibRTC,"n_laser_on_list");
	n_set_laser_delays = (N_SET_LASER_DELAYS_FP) GetProcAddress(gLibRTC,"n_set_laser_delays");
	n_set_standby_list = (N_SET_STANDBY_LIST_FP) GetProcAddress(gLibRTC,"n_set_standby_list");
	n_set_laser_pulses = (N_SET_LASER_PULSES_FP) GetProcAddress(gLibRTC,"n_set_laser_pulses");
	n_set_firstpulse_killer_list = (N_SET_FIRSTPULSE_KILLER_LIST_FP) GetProcAddress(gLibRTC,"n_set_firstpulse_killer_list");
	n_set_qswitch_delay_list = (N_SET_QSWITCH_DELAY_LIST_FP) GetProcAddress(gLibRTC,"n_set_qswitch_delay_list");
	n_set_laser_pin_out_list = (N_SET_LASER_PIN_OUT_LIST_FP) GetProcAddress(gLibRTC,"n_set_laser_pin_out_list");
	n_set_vector_control = (N_SET_VECTOR_CONTROL_FP) GetProcAddress(gLibRTC,"n_set_vector_control");
	n_set_default_pixel_list = (N_SET_DEFAULT_PIXEL_LIST_FP) GetProcAddress(gLibRTC,"n_set_default_pixel_list");
	n_set_auto_laser_params_list = (N_SET_AUTO_LASER_PARAMS_LIST_FP) GetProcAddress(gLibRTC,"n_set_auto_laser_params_list");
	n_set_pulse_picking_list = (N_SET_PULSE_PICKING_LIST_FP) GetProcAddress(gLibRTC,"n_set_pulse_picking_list");
	n_set_softstart_level_list = (N_SET_SOFTSTART_LEVEL_LIST_FP) GetProcAddress(gLibRTC,"n_set_softstart_level_list");
	n_set_softstart_mode_list = (N_SET_SOFTSTART_MODE_LIST_FP) GetProcAddress(gLibRTC,"n_set_softstart_mode_list");
	n_config_laser_signals_list = (N_CONFIG_LASER_SIGNALS_LIST_FP) GetProcAddress(gLibRTC,"n_config_laser_signals_list");
	n_set_laser_timing = (N_SET_LASER_TIMING_FP) GetProcAddress(gLibRTC,"n_set_laser_timing");
	laser_signal_on_list = (LASER_SIGNAL_ON_LIST_FP) GetProcAddress(gLibRTC,"laser_signal_on_list");
	laser_signal_off_list = (LASER_SIGNAL_OFF_LIST_FP) GetProcAddress(gLibRTC,"laser_signal_off_list");
	para_laser_on_pulses_list = (PARA_LASER_ON_PULSES_LIST_FP) GetProcAddress(gLibRTC,"para_laser_on_pulses_list");
	laser_on_pulses_list = (LASER_ON_PULSES_LIST_FP) GetProcAddress(gLibRTC,"laser_on_pulses_list");
	laser_on_list = (LASER_ON_LIST_FP) GetProcAddress(gLibRTC,"laser_on_list");
	set_laser_delays = (SET_LASER_DELAYS_FP) GetProcAddress(gLibRTC,"set_laser_delays");
	set_standby_list = (SET_STANDBY_LIST_FP) GetProcAddress(gLibRTC,"set_standby_list");
	set_laser_pulses = (SET_LASER_PULSES_FP) GetProcAddress(gLibRTC,"set_laser_pulses");
	set_firstpulse_killer_list = (SET_FIRSTPULSE_KILLER_LIST_FP) GetProcAddress(gLibRTC,"set_firstpulse_killer_list");
	set_qswitch_delay_list = (SET_QSWITCH_DELAY_LIST_FP) GetProcAddress(gLibRTC,"set_qswitch_delay_list");
	set_laser_pin_out_list = (SET_LASER_PIN_OUT_LIST_FP) GetProcAddress(gLibRTC,"set_laser_pin_out_list");
	set_vector_control = (SET_VECTOR_CONTROL_FP) GetProcAddress(gLibRTC,"set_vector_control");
	set_default_pixel_list = (SET_DEFAULT_PIXEL_LIST_FP) GetProcAddress(gLibRTC,"set_default_pixel_list");
	set_auto_laser_params_list = (SET_AUTO_LASER_PARAMS_LIST_FP) GetProcAddress(gLibRTC,"set_auto_laser_params_list");
	set_pulse_picking_list = (SET_PULSE_PICKING_LIST_FP) GetProcAddress(gLibRTC,"set_pulse_picking_list");
	set_softstart_level_list = (SET_SOFTSTART_LEVEL_LIST_FP) GetProcAddress(gLibRTC,"set_softstart_level_list");
	set_softstart_mode_list = (SET_SOFTSTART_MODE_LIST_FP) GetProcAddress(gLibRTC,"set_softstart_mode_list");
	config_laser_signals_list = (CONFIG_LASER_SIGNALS_LIST_FP) GetProcAddress(gLibRTC,"config_laser_signals_list");
	set_laser_timing = (SET_LASER_TIMING_FP) GetProcAddress(gLibRTC,"set_laser_timing");
	n_fly_return_z = (N_FLY_RETURN_Z_FP) GetProcAddress(gLibRTC,"n_fly_return_z");
	n_fly_return = (N_FLY_RETURN_FP) GetProcAddress(gLibRTC,"n_fly_return");
	n_set_rot_center_list = (N_SET_ROT_CENTER_LIST_FP) GetProcAddress(gLibRTC,"n_set_rot_center_list");
	n_set_ext_start_delay_list = (N_SET_EXT_START_DELAY_LIST_FP) GetProcAddress(gLibRTC,"n_set_ext_start_delay_list");
	n_set_fly_x = (N_SET_FLY_X_FP) GetProcAddress(gLibRTC,"n_set_fly_x");
	n_set_fly_y = (N_SET_FLY_Y_FP) GetProcAddress(gLibRTC,"n_set_fly_y");
	n_set_fly_z = (N_SET_FLY_Z_FP) GetProcAddress(gLibRTC,"n_set_fly_z");
	n_set_fly_rot = (N_SET_FLY_ROT_FP) GetProcAddress(gLibRTC,"n_set_fly_rot");
	n_set_fly_2d = (N_SET_FLY_2D_FP) GetProcAddress(gLibRTC,"n_set_fly_2d");
	n_set_fly_x_pos = (N_SET_FLY_X_POS_FP) GetProcAddress(gLibRTC,"n_set_fly_x_pos");
	n_set_fly_y_pos = (N_SET_FLY_Y_POS_FP) GetProcAddress(gLibRTC,"n_set_fly_y_pos");
	n_set_fly_rot_pos = (N_SET_FLY_ROT_POS_FP) GetProcAddress(gLibRTC,"n_set_fly_rot_pos");
	n_set_fly_limits = (N_SET_FLY_LIMITS_FP) GetProcAddress(gLibRTC,"n_set_fly_limits");
	n_set_fly_limits_z = (N_SET_FLY_LIMITS_Z_FP) GetProcAddress(gLibRTC,"n_set_fly_limits_z");
	n_if_fly_x_overflow = (N_IF_FLY_X_OVERFLOW_FP) GetProcAddress(gLibRTC,"n_if_fly_x_overflow");
	n_if_fly_y_overflow = (N_IF_FLY_Y_OVERFLOW_FP) GetProcAddress(gLibRTC,"n_if_fly_y_overflow");
	n_if_fly_z_overflow = (N_IF_FLY_Z_OVERFLOW_FP) GetProcAddress(gLibRTC,"n_if_fly_z_overflow");
	n_if_not_fly_x_overflow = (N_IF_NOT_FLY_X_OVERFLOW_FP) GetProcAddress(gLibRTC,"n_if_not_fly_x_overflow");
	n_if_not_fly_y_overflow = (N_IF_NOT_FLY_Y_OVERFLOW_FP) GetProcAddress(gLibRTC,"n_if_not_fly_y_overflow");
	n_if_not_fly_z_overflow = (N_IF_NOT_FLY_Z_OVERFLOW_FP) GetProcAddress(gLibRTC,"n_if_not_fly_z_overflow");
	n_clear_fly_overflow = (N_CLEAR_FLY_OVERFLOW_FP) GetProcAddress(gLibRTC,"n_clear_fly_overflow");
	n_set_mcbsp_x_list = (N_SET_MCBSP_X_LIST_FP) GetProcAddress(gLibRTC,"n_set_mcbsp_x_list");
	n_set_mcbsp_y_list = (N_SET_MCBSP_Y_LIST_FP) GetProcAddress(gLibRTC,"n_set_mcbsp_y_list");
	n_set_mcbsp_rot_list = (N_SET_MCBSP_ROT_LIST_FP) GetProcAddress(gLibRTC,"n_set_mcbsp_rot_list");
	n_set_mcbsp_matrix_list = (N_SET_MCBSP_MATRIX_LIST_FP) GetProcAddress(gLibRTC,"n_set_mcbsp_matrix_list");
	n_set_mcbsp_in_list = (N_SET_MCBSP_IN_LIST_FP) GetProcAddress(gLibRTC,"n_set_mcbsp_in_list");
	n_set_multi_mcbsp_in_list = (N_SET_MULTI_MCBSP_IN_LIST_FP) GetProcAddress(gLibRTC,"n_set_multi_mcbsp_in_list");
	n_wait_for_encoder_mode = (N_WAIT_FOR_ENCODER_MODE_FP) GetProcAddress(gLibRTC,"n_wait_for_encoder_mode");
	n_wait_for_mcbsp = (N_WAIT_FOR_MCBSP_FP) GetProcAddress(gLibRTC,"n_wait_for_mcbsp");
	n_set_encoder_speed = (N_SET_ENCODER_SPEED_FP) GetProcAddress(gLibRTC,"n_set_encoder_speed");
	n_get_mcbsp_list = (N_GET_MCBSP_LIST_FP) GetProcAddress(gLibRTC,"n_get_mcbsp_list");
	n_store_encoder = (N_STORE_ENCODER_FP) GetProcAddress(gLibRTC,"n_store_encoder");
	n_wait_for_encoder_in_range = (N_WAIT_FOR_ENCODER_IN_RANGE_FP) GetProcAddress(gLibRTC,"n_wait_for_encoder_in_range");
	n_activate_fly_xy = (N_ACTIVATE_FLY_XY_FP) GetProcAddress(gLibRTC,"n_activate_fly_xy");
	n_activate_fly_2d = (N_ACTIVATE_FLY_2D_FP) GetProcAddress(gLibRTC,"n_activate_fly_2d");
	n_if_not_activated = (N_IF_NOT_ACTIVATED_FP) GetProcAddress(gLibRTC,"n_if_not_activated");
	n_park_position = (N_PARK_POSITION_FP) GetProcAddress(gLibRTC,"n_park_position");
	n_park_return = (N_PARK_RETURN_FP) GetProcAddress(gLibRTC,"n_park_return");
	n_wait_for_encoder = (N_WAIT_FOR_ENCODER_FP) GetProcAddress(gLibRTC,"n_wait_for_encoder");
	fly_return_z = (FLY_RETURN_Z_FP) GetProcAddress(gLibRTC,"fly_return_z");
	fly_return = (FLY_RETURN_FP) GetProcAddress(gLibRTC,"fly_return");
	set_rot_center_list = (SET_ROT_CENTER_LIST_FP) GetProcAddress(gLibRTC,"set_rot_center_list");
	set_ext_start_delay_list = (SET_EXT_START_DELAY_LIST_FP) GetProcAddress(gLibRTC,"set_ext_start_delay_list");
	set_fly_x = (SET_FLY_X_FP) GetProcAddress(gLibRTC,"set_fly_x");
	set_fly_y = (SET_FLY_Y_FP) GetProcAddress(gLibRTC,"set_fly_y");
	set_fly_z = (SET_FLY_Z_FP) GetProcAddress(gLibRTC,"set_fly_z");
	set_fly_rot = (SET_FLY_ROT_FP) GetProcAddress(gLibRTC,"set_fly_rot");
	set_fly_2d = (SET_FLY_2D_FP) GetProcAddress(gLibRTC,"set_fly_2d");
	set_fly_x_pos = (SET_FLY_X_POS_FP) GetProcAddress(gLibRTC,"set_fly_x_pos");
	set_fly_y_pos = (SET_FLY_Y_POS_FP) GetProcAddress(gLibRTC,"set_fly_y_pos");
	set_fly_rot_pos = (SET_FLY_ROT_POS_FP) GetProcAddress(gLibRTC,"set_fly_rot_pos");
	set_fly_limits = (SET_FLY_LIMITS_FP) GetProcAddress(gLibRTC,"set_fly_limits");
	set_fly_limits_z = (SET_FLY_LIMITS_Z_FP) GetProcAddress(gLibRTC,"set_fly_limits_z");
	if_fly_x_overflow = (IF_FLY_X_OVERFLOW_FP) GetProcAddress(gLibRTC,"if_fly_x_overflow");
	if_fly_y_overflow = (IF_FLY_Y_OVERFLOW_FP) GetProcAddress(gLibRTC,"if_fly_y_overflow");
	if_fly_z_overflow = (IF_FLY_Z_OVERFLOW_FP) GetProcAddress(gLibRTC,"if_fly_z_overflow");
	if_not_fly_x_overflow = (IF_NOT_FLY_X_OVERFLOW_FP) GetProcAddress(gLibRTC,"if_not_fly_x_overflow");
	if_not_fly_y_overflow = (IF_NOT_FLY_Y_OVERFLOW_FP) GetProcAddress(gLibRTC,"if_not_fly_y_overflow");
	if_not_fly_z_overflow = (IF_NOT_FLY_Z_OVERFLOW_FP) GetProcAddress(gLibRTC,"if_not_fly_z_overflow");
	clear_fly_overflow = (CLEAR_FLY_OVERFLOW_FP) GetProcAddress(gLibRTC,"clear_fly_overflow");
	set_mcbsp_x_list = (SET_MCBSP_X_LIST_FP) GetProcAddress(gLibRTC,"set_mcbsp_x_list");
	set_mcbsp_y_list = (SET_MCBSP_Y_LIST_FP) GetProcAddress(gLibRTC,"set_mcbsp_y_list");
	set_mcbsp_rot_list = (SET_MCBSP_ROT_LIST_FP) GetProcAddress(gLibRTC,"set_mcbsp_rot_list");
	set_mcbsp_matrix_list = (SET_MCBSP_MATRIX_LIST_FP) GetProcAddress(gLibRTC,"set_mcbsp_matrix_list");
	set_mcbsp_in_list = (SET_MCBSP_IN_LIST_FP) GetProcAddress(gLibRTC,"set_mcbsp_in_list");
	set_multi_mcbsp_in_list = (SET_MULTI_MCBSP_IN_LIST_FP) GetProcAddress(gLibRTC,"set_multi_mcbsp_in_list");
	wait_for_encoder_mode = (WAIT_FOR_ENCODER_MODE_FP) GetProcAddress(gLibRTC,"wait_for_encoder_mode");
	wait_for_mcbsp = (WAIT_FOR_MCBSP_FP) GetProcAddress(gLibRTC,"wait_for_mcbsp");
	set_encoder_speed = (SET_ENCODER_SPEED_FP) GetProcAddress(gLibRTC,"set_encoder_speed");
	get_mcbsp_list = (GET_MCBSP_LIST_FP) GetProcAddress(gLibRTC,"get_mcbsp_list");
	store_encoder = (STORE_ENCODER_FP) GetProcAddress(gLibRTC,"store_encoder");
	wait_for_encoder_in_range = (WAIT_FOR_ENCODER_IN_RANGE_FP) GetProcAddress(gLibRTC,"wait_for_encoder_in_range");
	activate_fly_xy = (ACTIVATE_FLY_XY_FP) GetProcAddress(gLibRTC,"activate_fly_xy");
	activate_fly_2d = (ACTIVATE_FLY_2D_FP) GetProcAddress(gLibRTC,"activate_fly_2d");
	if_not_activated = (IF_NOT_ACTIVATED_FP) GetProcAddress(gLibRTC,"if_not_activated");
	park_position = (PARK_POSITION_FP) GetProcAddress(gLibRTC,"park_position");
	park_return = (PARK_RETURN_FP) GetProcAddress(gLibRTC,"park_return");
	wait_for_encoder = (WAIT_FOR_ENCODER_FP) GetProcAddress(gLibRTC,"wait_for_encoder");
	n_save_and_restart_timer = (N_SAVE_AND_RESTART_TIMER_FP) GetProcAddress(gLibRTC,"n_save_and_restart_timer");
	n_set_wobbel = (N_SET_WOBBEL_FP) GetProcAddress(gLibRTC,"n_set_wobbel");
	n_set_wobbel_mode = (N_SET_WOBBEL_MODE_FP) GetProcAddress(gLibRTC,"n_set_wobbel_mode");
	n_set_wobbel_mode_phase = (N_SET_WOBBEL_MODE_PHASE_FP) GetProcAddress(gLibRTC,"n_set_wobbel_mode_phase");
	n_set_wobbel_direction = (N_SET_WOBBEL_DIRECTION_FP) GetProcAddress(gLibRTC,"n_set_wobbel_direction");
	n_set_wobbel_control = (N_SET_WOBBEL_CONTROL_FP) GetProcAddress(gLibRTC,"n_set_wobbel_control");
	n_set_wobbel_vector = (N_SET_WOBBEL_VECTOR_FP) GetProcAddress(gLibRTC,"n_set_wobbel_vector");
	n_set_wobbel_offset = (N_SET_WOBBEL_OFFSET_FP) GetProcAddress(gLibRTC,"n_set_wobbel_offset");
	n_set_trigger = (N_SET_TRIGGER_FP) GetProcAddress(gLibRTC,"n_set_trigger");
	n_set_trigger4 = (N_SET_TRIGGER4_FP) GetProcAddress(gLibRTC,"n_set_trigger4");
	n_set_pixel_line_3d = (N_SET_PIXEL_LINE_3D_FP) GetProcAddress(gLibRTC,"n_set_pixel_line_3d");
	n_set_pixel_line = (N_SET_PIXEL_LINE_FP) GetProcAddress(gLibRTC,"n_set_pixel_line");
	n_stretch_pixel_line = (N_STRETCH_PIXEL_LINE_FP) GetProcAddress(gLibRTC,"n_stretch_pixel_line");
	n_set_n_pixel = (N_SET_N_PIXEL_FP) GetProcAddress(gLibRTC,"n_set_n_pixel");
	n_set_pixel = (N_SET_PIXEL_FP) GetProcAddress(gLibRTC,"n_set_pixel");
	n_rs232_write_text_list = (N_RS232_WRITE_TEXT_LIST_FP) GetProcAddress(gLibRTC,"n_rs232_write_text_list");
	n_set_mcbsp_out = (N_SET_MCBSP_OUT_FP) GetProcAddress(gLibRTC,"n_set_mcbsp_out");
	n_camming = (N_CAMMING_FP) GetProcAddress(gLibRTC,"n_camming");
	n_periodic_toggle_list = (N_PERIODIC_TOGGLE_LIST_FP) GetProcAddress(gLibRTC,"n_periodic_toggle_list");
	n_micro_vector_abs_3d = (N_MICRO_VECTOR_ABS_3D_FP) GetProcAddress(gLibRTC,"n_micro_vector_abs_3d");
	n_micro_vector_rel_3d = (N_MICRO_VECTOR_REL_3D_FP) GetProcAddress(gLibRTC,"n_micro_vector_rel_3d");
	n_micro_vector_abs = (N_MICRO_VECTOR_ABS_FP) GetProcAddress(gLibRTC,"n_micro_vector_abs");
	n_micro_vector_rel = (N_MICRO_VECTOR_REL_FP) GetProcAddress(gLibRTC,"n_micro_vector_rel");
	n_set_free_variable_list = (N_SET_FREE_VARIABLE_LIST_FP) GetProcAddress(gLibRTC,"n_set_free_variable_list");
	n_control_command_list = (N_CONTROL_COMMAND_LIST_FP) GetProcAddress(gLibRTC,"n_control_command_list");
	n_jump_abs_drill = (N_JUMP_ABS_DRILL_FP) GetProcAddress(gLibRTC,"n_jump_abs_drill");
	n_jump_rel_drill = (N_JUMP_REL_DRILL_FP) GetProcAddress(gLibRTC,"n_jump_rel_drill");
	save_and_restart_timer = (SAVE_AND_RESTART_TIMER_FP) GetProcAddress(gLibRTC,"save_and_restart_timer");
	set_wobbel = (SET_WOBBEL_FP) GetProcAddress(gLibRTC,"set_wobbel");
	set_wobbel_mode = (SET_WOBBEL_MODE_FP) GetProcAddress(gLibRTC,"set_wobbel_mode");
	set_wobbel_mode_phase = (SET_WOBBEL_MODE_PHASE_FP) GetProcAddress(gLibRTC,"set_wobbel_mode_phase");
	set_wobbel_direction = (SET_WOBBEL_DIRECTION_FP) GetProcAddress(gLibRTC,"set_wobbel_direction");
	set_wobbel_control = (SET_WOBBEL_CONTROL_FP) GetProcAddress(gLibRTC,"set_wobbel_control");
	set_wobbel_vector = (SET_WOBBEL_VECTOR_FP) GetProcAddress(gLibRTC,"set_wobbel_vector");
	set_wobbel_offset = (SET_WOBBEL_OFFSET_FP) GetProcAddress(gLibRTC,"set_wobbel_offset");
	set_trigger = (SET_TRIGGER_FP) GetProcAddress(gLibRTC,"set_trigger");
	set_trigger4 = (SET_TRIGGER4_FP) GetProcAddress(gLibRTC,"set_trigger4");
	set_pixel_line_3d = (SET_PIXEL_LINE_3D_FP) GetProcAddress(gLibRTC,"set_pixel_line_3d");
	set_pixel_line = (SET_PIXEL_LINE_FP) GetProcAddress(gLibRTC,"set_pixel_line");
	stretch_pixel_line = (STRETCH_PIXEL_LINE_FP) GetProcAddress(gLibRTC,"stretch_pixel_line");
	set_n_pixel = (SET_N_PIXEL_FP) GetProcAddress(gLibRTC,"set_n_pixel");
	set_pixel = (SET_PIXEL_FP) GetProcAddress(gLibRTC,"set_pixel");
	rs232_write_text_list = (RS232_WRITE_TEXT_LIST_FP) GetProcAddress(gLibRTC,"rs232_write_text_list");
	set_mcbsp_out = (SET_MCBSP_OUT_FP) GetProcAddress(gLibRTC,"set_mcbsp_out");
	camming = (CAMMING_FP) GetProcAddress(gLibRTC,"camming");
	periodic_toggle_list = (PERIODIC_TOGGLE_LIST_FP) GetProcAddress(gLibRTC,"periodic_toggle_list");
	micro_vector_abs_3d = (MICRO_VECTOR_ABS_3D_FP) GetProcAddress(gLibRTC,"micro_vector_abs_3d");
	micro_vector_rel_3d = (MICRO_VECTOR_REL_3D_FP) GetProcAddress(gLibRTC,"micro_vector_rel_3d");
	micro_vector_abs = (MICRO_VECTOR_ABS_FP) GetProcAddress(gLibRTC,"micro_vector_abs");
	micro_vector_rel = (MICRO_VECTOR_REL_FP) GetProcAddress(gLibRTC,"micro_vector_rel");
	set_free_variable_list = (SET_FREE_VARIABLE_LIST_FP) GetProcAddress(gLibRTC,"set_free_variable_list");
	control_command_list = (CONTROL_COMMAND_LIST_FP) GetProcAddress(gLibRTC,"control_command_list");
	jump_abs_drill = (JUMP_ABS_DRILL_FP) GetProcAddress(gLibRTC,"jump_abs_drill");
	jump_rel_drill = (JUMP_REL_DRILL_FP) GetProcAddress(gLibRTC,"jump_rel_drill");
	n_timed_mark_abs_3d = (N_TIMED_MARK_ABS_3D_FP) GetProcAddress(gLibRTC,"n_timed_mark_abs_3d");
	n_timed_mark_rel_3d = (N_TIMED_MARK_REL_3D_FP) GetProcAddress(gLibRTC,"n_timed_mark_rel_3d");
	n_timed_mark_abs = (N_TIMED_MARK_ABS_FP) GetProcAddress(gLibRTC,"n_timed_mark_abs");
	n_timed_mark_rel = (N_TIMED_MARK_REL_FP) GetProcAddress(gLibRTC,"n_timed_mark_rel");
	timed_mark_abs_3d = (TIMED_MARK_ABS_3D_FP) GetProcAddress(gLibRTC,"timed_mark_abs_3d");
	timed_mark_rel_3d = (TIMED_MARK_REL_3D_FP) GetProcAddress(gLibRTC,"timed_mark_rel_3d");
	timed_mark_abs = (TIMED_MARK_ABS_FP) GetProcAddress(gLibRTC,"timed_mark_abs");
	timed_mark_rel = (TIMED_MARK_REL_FP) GetProcAddress(gLibRTC,"timed_mark_rel");
	n_mark_abs_3d = (N_MARK_ABS_3D_FP) GetProcAddress(gLibRTC,"n_mark_abs_3d");
	n_mark_rel_3d = (N_MARK_REL_3D_FP) GetProcAddress(gLibRTC,"n_mark_rel_3d");
	n_mark_abs = (N_MARK_ABS_FP) GetProcAddress(gLibRTC,"n_mark_abs");
	n_mark_rel = (N_MARK_REL_FP) GetProcAddress(gLibRTC,"n_mark_rel");
	mark_abs_3d = (MARK_ABS_3D_FP) GetProcAddress(gLibRTC,"mark_abs_3d");
	mark_rel_3d = (MARK_REL_3D_FP) GetProcAddress(gLibRTC,"mark_rel_3d");
	mark_abs = (MARK_ABS_FP) GetProcAddress(gLibRTC,"mark_abs");
	mark_rel = (MARK_REL_FP) GetProcAddress(gLibRTC,"mark_rel");
	n_timed_jump_abs_3d = (N_TIMED_JUMP_ABS_3D_FP) GetProcAddress(gLibRTC,"n_timed_jump_abs_3d");
	n_timed_jump_rel_3d = (N_TIMED_JUMP_REL_3D_FP) GetProcAddress(gLibRTC,"n_timed_jump_rel_3d");
	n_timed_jump_abs = (N_TIMED_JUMP_ABS_FP) GetProcAddress(gLibRTC,"n_timed_jump_abs");
	n_timed_jump_rel = (N_TIMED_JUMP_REL_FP) GetProcAddress(gLibRTC,"n_timed_jump_rel");
	timed_jump_abs_3d = (TIMED_JUMP_ABS_3D_FP) GetProcAddress(gLibRTC,"timed_jump_abs_3d");
	timed_jump_rel_3d = (TIMED_JUMP_REL_3D_FP) GetProcAddress(gLibRTC,"timed_jump_rel_3d");
	timed_jump_abs = (TIMED_JUMP_ABS_FP) GetProcAddress(gLibRTC,"timed_jump_abs");
	timed_jump_rel = (TIMED_JUMP_REL_FP) GetProcAddress(gLibRTC,"timed_jump_rel");
	n_jump_abs_3d = (N_JUMP_ABS_3D_FP) GetProcAddress(gLibRTC,"n_jump_abs_3d");
	n_jump_rel_3d = (N_JUMP_REL_3D_FP) GetProcAddress(gLibRTC,"n_jump_rel_3d");
	n_jump_abs = (N_JUMP_ABS_FP) GetProcAddress(gLibRTC,"n_jump_abs");
	n_jump_rel = (N_JUMP_REL_FP) GetProcAddress(gLibRTC,"n_jump_rel");
	jump_abs_3d = (JUMP_ABS_3D_FP) GetProcAddress(gLibRTC,"jump_abs_3d");
	jump_rel_3d = (JUMP_REL_3D_FP) GetProcAddress(gLibRTC,"jump_rel_3d");
	jump_abs = (JUMP_ABS_FP) GetProcAddress(gLibRTC,"jump_abs");
	jump_rel = (JUMP_REL_FP) GetProcAddress(gLibRTC,"jump_rel");
	n_para_mark_abs_3d = (N_PARA_MARK_ABS_3D_FP) GetProcAddress(gLibRTC,"n_para_mark_abs_3d");
	n_para_mark_rel_3d = (N_PARA_MARK_REL_3D_FP) GetProcAddress(gLibRTC,"n_para_mark_rel_3d");
	n_para_mark_abs = (N_PARA_MARK_ABS_FP) GetProcAddress(gLibRTC,"n_para_mark_abs");
	n_para_mark_rel = (N_PARA_MARK_REL_FP) GetProcAddress(gLibRTC,"n_para_mark_rel");
	para_mark_abs_3d = (PARA_MARK_ABS_3D_FP) GetProcAddress(gLibRTC,"para_mark_abs_3d");
	para_mark_rel_3d = (PARA_MARK_REL_3D_FP) GetProcAddress(gLibRTC,"para_mark_rel_3d");
	para_mark_abs = (PARA_MARK_ABS_FP) GetProcAddress(gLibRTC,"para_mark_abs");
	para_mark_rel = (PARA_MARK_REL_FP) GetProcAddress(gLibRTC,"para_mark_rel");
	n_para_jump_abs_3d = (N_PARA_JUMP_ABS_3D_FP) GetProcAddress(gLibRTC,"n_para_jump_abs_3d");
	n_para_jump_rel_3d = (N_PARA_JUMP_REL_3D_FP) GetProcAddress(gLibRTC,"n_para_jump_rel_3d");
	n_para_jump_abs = (N_PARA_JUMP_ABS_FP) GetProcAddress(gLibRTC,"n_para_jump_abs");
	n_para_jump_rel = (N_PARA_JUMP_REL_FP) GetProcAddress(gLibRTC,"n_para_jump_rel");
	para_jump_abs_3d = (PARA_JUMP_ABS_3D_FP) GetProcAddress(gLibRTC,"para_jump_abs_3d");
	para_jump_rel_3d = (PARA_JUMP_REL_3D_FP) GetProcAddress(gLibRTC,"para_jump_rel_3d");
	para_jump_abs = (PARA_JUMP_ABS_FP) GetProcAddress(gLibRTC,"para_jump_abs");
	para_jump_rel = (PARA_JUMP_REL_FP) GetProcAddress(gLibRTC,"para_jump_rel");
	n_timed_para_mark_abs_3d = (N_TIMED_PARA_MARK_ABS_3D_FP) GetProcAddress(gLibRTC,"n_timed_para_mark_abs_3d");
	n_timed_para_mark_rel_3d = (N_TIMED_PARA_MARK_REL_3D_FP) GetProcAddress(gLibRTC,"n_timed_para_mark_rel_3d");
	n_timed_para_jump_abs_3d = (N_TIMED_PARA_JUMP_ABS_3D_FP) GetProcAddress(gLibRTC,"n_timed_para_jump_abs_3d");
	n_timed_para_jump_rel_3d = (N_TIMED_PARA_JUMP_REL_3D_FP) GetProcAddress(gLibRTC,"n_timed_para_jump_rel_3d");
	n_timed_para_mark_abs = (N_TIMED_PARA_MARK_ABS_FP) GetProcAddress(gLibRTC,"n_timed_para_mark_abs");
	n_timed_para_mark_rel = (N_TIMED_PARA_MARK_REL_FP) GetProcAddress(gLibRTC,"n_timed_para_mark_rel");
	n_timed_para_jump_abs = (N_TIMED_PARA_JUMP_ABS_FP) GetProcAddress(gLibRTC,"n_timed_para_jump_abs");
	n_timed_para_jump_rel = (N_TIMED_PARA_JUMP_REL_FP) GetProcAddress(gLibRTC,"n_timed_para_jump_rel");
	timed_para_mark_abs_3d = (TIMED_PARA_MARK_ABS_3D_FP) GetProcAddress(gLibRTC,"timed_para_mark_abs_3d");
	timed_para_mark_rel_3d = (TIMED_PARA_MARK_REL_3D_FP) GetProcAddress(gLibRTC,"timed_para_mark_rel_3d");
	timed_para_jump_abs_3d = (TIMED_PARA_JUMP_ABS_3D_FP) GetProcAddress(gLibRTC,"timed_para_jump_abs_3d");
	timed_para_jump_rel_3d = (TIMED_PARA_JUMP_REL_3D_FP) GetProcAddress(gLibRTC,"timed_para_jump_rel_3d");
	timed_para_mark_abs = (TIMED_PARA_MARK_ABS_FP) GetProcAddress(gLibRTC,"timed_para_mark_abs");
	timed_para_mark_rel = (TIMED_PARA_MARK_REL_FP) GetProcAddress(gLibRTC,"timed_para_mark_rel");
	timed_para_jump_abs = (TIMED_PARA_JUMP_ABS_FP) GetProcAddress(gLibRTC,"timed_para_jump_abs");
	timed_para_jump_rel = (TIMED_PARA_JUMP_REL_FP) GetProcAddress(gLibRTC,"timed_para_jump_rel");
	n_set_defocus_list = (N_SET_DEFOCUS_LIST_FP) GetProcAddress(gLibRTC,"n_set_defocus_list");
	n_set_defocus_offset_list = (N_SET_DEFOCUS_OFFSET_LIST_FP) GetProcAddress(gLibRTC,"n_set_defocus_offset_list");
	n_set_zoom_list = (N_SET_ZOOM_LIST_FP) GetProcAddress(gLibRTC,"n_set_zoom_list");
	set_defocus_list = (SET_DEFOCUS_LIST_FP) GetProcAddress(gLibRTC,"set_defocus_list");
	set_defocus_offset_list = (SET_DEFOCUS_OFFSET_LIST_FP) GetProcAddress(gLibRTC,"set_defocus_offset_list");
	set_zoom_list = (SET_ZOOM_LIST_FP) GetProcAddress(gLibRTC,"set_zoom_list");
	n_timed_arc_abs = (N_TIMED_ARC_ABS_FP) GetProcAddress(gLibRTC,"n_timed_arc_abs");
	n_timed_arc_rel = (N_TIMED_ARC_REL_FP) GetProcAddress(gLibRTC,"n_timed_arc_rel");
	timed_arc_abs = (TIMED_ARC_ABS_FP) GetProcAddress(gLibRTC,"timed_arc_abs");
	timed_arc_rel = (TIMED_ARC_REL_FP) GetProcAddress(gLibRTC,"timed_arc_rel");
	n_arc_abs_3d = (N_ARC_ABS_3D_FP) GetProcAddress(gLibRTC,"n_arc_abs_3d");
	n_arc_rel_3d = (N_ARC_REL_3D_FP) GetProcAddress(gLibRTC,"n_arc_rel_3d");
	n_arc_abs = (N_ARC_ABS_FP) GetProcAddress(gLibRTC,"n_arc_abs");
	n_arc_rel = (N_ARC_REL_FP) GetProcAddress(gLibRTC,"n_arc_rel");
	n_set_ellipse = (N_SET_ELLIPSE_FP) GetProcAddress(gLibRTC,"n_set_ellipse");
	n_mark_ellipse_abs = (N_MARK_ELLIPSE_ABS_FP) GetProcAddress(gLibRTC,"n_mark_ellipse_abs");
	n_mark_ellipse_rel = (N_MARK_ELLIPSE_REL_FP) GetProcAddress(gLibRTC,"n_mark_ellipse_rel");
	arc_abs_3d = (ARC_ABS_3D_FP) GetProcAddress(gLibRTC,"arc_abs_3d");
	arc_rel_3d = (ARC_REL_3D_FP) GetProcAddress(gLibRTC,"arc_rel_3d");
	arc_abs = (ARC_ABS_FP) GetProcAddress(gLibRTC,"arc_abs");
	arc_rel = (ARC_REL_FP) GetProcAddress(gLibRTC,"arc_rel");
	set_ellipse = (SET_ELLIPSE_FP) GetProcAddress(gLibRTC,"set_ellipse");
	mark_ellipse_abs = (MARK_ELLIPSE_ABS_FP) GetProcAddress(gLibRTC,"mark_ellipse_abs");
	mark_ellipse_rel = (MARK_ELLIPSE_REL_FP) GetProcAddress(gLibRTC,"mark_ellipse_rel");
	n_set_offset_xyz_list = (N_SET_OFFSET_XYZ_LIST_FP) GetProcAddress(gLibRTC,"n_set_offset_xyz_list");
	n_set_offset_list = (N_SET_OFFSET_LIST_FP) GetProcAddress(gLibRTC,"n_set_offset_list");
	n_set_matrix_list = (N_SET_MATRIX_LIST_FP) GetProcAddress(gLibRTC,"n_set_matrix_list");
	n_set_angle_list = (N_SET_ANGLE_LIST_FP) GetProcAddress(gLibRTC,"n_set_angle_list");
	n_set_scale_list = (N_SET_SCALE_LIST_FP) GetProcAddress(gLibRTC,"n_set_scale_list");
	n_apply_mcbsp_list = (N_APPLY_MCBSP_LIST_FP) GetProcAddress(gLibRTC,"n_apply_mcbsp_list");
	set_offset_xyz_list = (SET_OFFSET_XYZ_LIST_FP) GetProcAddress(gLibRTC,"set_offset_xyz_list");
	set_offset_list = (SET_OFFSET_LIST_FP) GetProcAddress(gLibRTC,"set_offset_list");
	set_matrix_list = (SET_MATRIX_LIST_FP) GetProcAddress(gLibRTC,"set_matrix_list");
	set_angle_list = (SET_ANGLE_LIST_FP) GetProcAddress(gLibRTC,"set_angle_list");
	set_scale_list = (SET_SCALE_LIST_FP) GetProcAddress(gLibRTC,"set_scale_list");
	apply_mcbsp_list = (APPLY_MCBSP_LIST_FP) GetProcAddress(gLibRTC,"apply_mcbsp_list");
	n_set_mark_speed = (N_SET_MARK_SPEED_FP) GetProcAddress(gLibRTC,"n_set_mark_speed");
	n_set_jump_speed = (N_SET_JUMP_SPEED_FP) GetProcAddress(gLibRTC,"n_set_jump_speed");
	n_set_sky_writing_para_list = (N_SET_SKY_WRITING_PARA_LIST_FP) GetProcAddress(gLibRTC,"n_set_sky_writing_para_list");
	n_set_sky_writing_list = (N_SET_SKY_WRITING_LIST_FP) GetProcAddress(gLibRTC,"n_set_sky_writing_list");
	n_set_sky_writing_limit_list = (N_SET_SKY_WRITING_LIMIT_LIST_FP) GetProcAddress(gLibRTC,"n_set_sky_writing_limit_list");
	n_set_sky_writing_mode_list = (N_SET_SKY_WRITING_MODE_LIST_FP) GetProcAddress(gLibRTC,"n_set_sky_writing_mode_list");
	n_set_scanner_delays = (N_SET_SCANNER_DELAYS_FP) GetProcAddress(gLibRTC,"n_set_scanner_delays");
	n_set_jump_mode_list = (N_SET_JUMP_MODE_LIST_FP) GetProcAddress(gLibRTC,"n_set_jump_mode_list");
	n_enduring_wobbel = (N_ENDURING_WOBBEL_FP) GetProcAddress(gLibRTC,"n_enduring_wobbel");
	n_set_delay_mode_list = (N_SET_DELAY_MODE_LIST_FP) GetProcAddress(gLibRTC,"n_set_delay_mode_list");
	set_mark_speed = (SET_MARK_SPEED_FP) GetProcAddress(gLibRTC,"set_mark_speed");
	set_jump_speed = (SET_JUMP_SPEED_FP) GetProcAddress(gLibRTC,"set_jump_speed");
	set_sky_writing_para_list = (SET_SKY_WRITING_PARA_LIST_FP) GetProcAddress(gLibRTC,"set_sky_writing_para_list");
	set_sky_writing_list = (SET_SKY_WRITING_LIST_FP) GetProcAddress(gLibRTC,"set_sky_writing_list");
	set_sky_writing_limit_list = (SET_SKY_WRITING_LIMIT_LIST_FP) GetProcAddress(gLibRTC,"set_sky_writing_limit_list");
	set_sky_writing_mode_list = (SET_SKY_WRITING_MODE_LIST_FP) GetProcAddress(gLibRTC,"set_sky_writing_mode_list");
	set_scanner_delays = (SET_SCANNER_DELAYS_FP) GetProcAddress(gLibRTC,"set_scanner_delays");
	set_jump_mode_list = (SET_JUMP_MODE_LIST_FP) GetProcAddress(gLibRTC,"set_jump_mode_list");
	enduring_wobbel = (ENDURING_WOBBEL_FP) GetProcAddress(gLibRTC,"enduring_wobbel");
	set_delay_mode_list = (SET_DELAY_MODE_LIST_FP) GetProcAddress(gLibRTC,"set_delay_mode_list");
	n_stepper_enable_list = (N_STEPPER_ENABLE_LIST_FP) GetProcAddress(gLibRTC,"n_stepper_enable_list");
	n_stepper_control_list = (N_STEPPER_CONTROL_LIST_FP) GetProcAddress(gLibRTC,"n_stepper_control_list");
	n_stepper_abs_no_list = (N_STEPPER_ABS_NO_LIST_FP) GetProcAddress(gLibRTC,"n_stepper_abs_no_list");
	n_stepper_rel_no_list = (N_STEPPER_REL_NO_LIST_FP) GetProcAddress(gLibRTC,"n_stepper_rel_no_list");
	n_stepper_abs_list = (N_STEPPER_ABS_LIST_FP) GetProcAddress(gLibRTC,"n_stepper_abs_list");
	n_stepper_rel_list = (N_STEPPER_REL_LIST_FP) GetProcAddress(gLibRTC,"n_stepper_rel_list");
	n_stepper_wait = (N_STEPPER_WAIT_FP) GetProcAddress(gLibRTC,"n_stepper_wait");
	stepper_enable_list = (STEPPER_ENABLE_LIST_FP) GetProcAddress(gLibRTC,"stepper_enable_list");
	stepper_control_list = (STEPPER_CONTROL_LIST_FP) GetProcAddress(gLibRTC,"stepper_control_list");
	stepper_abs_no_list = (STEPPER_ABS_NO_LIST_FP) GetProcAddress(gLibRTC,"stepper_abs_no_list");
	stepper_rel_no_list = (STEPPER_REL_NO_LIST_FP) GetProcAddress(gLibRTC,"stepper_rel_no_list");
	stepper_abs_list = (STEPPER_ABS_LIST_FP) GetProcAddress(gLibRTC,"stepper_abs_list");
	stepper_rel_list = (STEPPER_REL_LIST_FP) GetProcAddress(gLibRTC,"stepper_rel_list");
	stepper_wait = (STEPPER_WAIT_FP) GetProcAddress(gLibRTC,"stepper_wait");
	
	return(0);
	
}

int RTC5::GetDLLVersion()
{
	return get_dll_version();
}


WORD RTC5::GetHeadStatus()
{
	return get_head_status(1);
}

// const UINT HeadA			    =      1;
// const UINT XAxis			    =      1;
// const UINT YAxis			    =      2;
// const UINT StatusAX		        =      1;
// const UINT StatusAY		        =      2;
// 
// const UINT SendFirmWare		    = 0x0522;
// const UINT SendStatus		    = 0x0500;


bool RTC5::SetRTC()
{
	CString str;
	CString filepath;

	int bDirect3DMove; 	
	int iEdgeLevel;
	int iMinJumpDelay;
	int iJumpLengthLimit;

	if(!Update("GalvoSettings", "Direct3DMove", bDirect3DMove, false))
		bDirect3DMove=0;
	
	if(!Update("GalvoSettings", "EdgeLevel", iEdgeLevel, false))
		iEdgeLevel=65535;
	
	if(!Update("GalvoSettings", "MiniJumpDelay", iMinJumpDelay, false))
		iMinJumpDelay=10;
	
	if(!Update("GalvoSettings", "JumpLengthLimit", iJumpLengthLimit, false))
		iJumpLengthLimit=10;

   ::GetModuleFileName(NULL, filepath.GetBuffer(MAX_PATH), MAX_PATH);
	filepath.ReleaseBuffer();
	int Pos=filepath.ReverseFind('\\');	
 	filepath=filepath.Mid(0,Pos); 

	if(!LoadFile(filepath))
	{
		free_rtc5_dll();
		return false;
	}

	if(!m_powercurvefile.IsEmpty())
		LoadPowerCurve(m_powercurvefile);
	
	select_cor_table(1, 0); //  table #1 at primary connector (default)
	reset_error(UINT_MAX);
	
	// 	control_command( HeadA, XAxis, SendStatus );	// send Status on X status channel
	//     delay( 10 );	// Wait until command is transfered to the head, executed and new status data is updated
	//     const short Test1( GetValue( StatusAX ) );
	// 	
	//     control_command( HeadA, XAxis, SendFirmWare );	// send FirmWare No on X status channel
	//     delay( 10 );	// Wait until command is transfered to the head, executed and new status data is updated
	//     const short Test2( GetValue( StatusAX ) );
	// 	
	//     if ( Test1 == Test2 )
	//     {
	//         AfxMessageBox("Please check HeadA: no intelliSCAN connected\n\n" );	//         
	//     }
		
	//all space to list 1
	config_list(-1,-1);

	iMaxListPos=get_list_space();

	if(m_bFirstPulseSync)
		set_laser_control(0x40);
	else
		set_laser_control(0x00);

	config_laser_signals(m_LaserSignal);

	stop_execution();
	set_matrix(0, xcor*cos(xyrotate*PI/180), -xcor*sin(xyrotate*PI/180), ycor*sin(xyrotate*PI/180), ycor*cos(xyrotate*PI/180), 1);
	set_offset(0, xoffset*m_Scale, yoffset*m_Scale, 1);

	set_delay_mode(m_bVarPolyDelay, bDirect3DMove, iEdgeLevel, iMinJumpDelay, iJumpLengthLimit*m_Scale);//100	
	
	m_Scale=get_head_para(1,1);
	set_default_pixel(0);
	set_port_default(0,0);
	set_laser_mode(m_lasermode);
	//auto laser control;
	if(m_bSpeedDepend || m_bPositionDepend)
	{
		m_iSpeedDependMode=2; //actual speed mode
		double value=1;

		if(!strAutoControlScale.IsEmpty())
			load_auto_laser_control(strAutoControlScale, 1);
		else
			load_auto_laser_control(0, 1);

		if(m_bSpeedDepend)	set_auto_laser_control(m_iAutoDependCtrl, value, m_iSpeedDependMode,  m_AdvLaserMin*value, m_AdvLaserMax*value);
		else set_auto_laser_control(m_iAutoDependCtrl, value, 0,  m_AdvLaserMin*value, m_AdvLaserMax*value);
		
		if(m_bPositionDepend)load_position_control(strAutoPosScale, 1);
		else load_position_control(0,1);
	}
	else
		set_auto_laser_control(0,1,m_iSpeedDependMode,0,1);

	StartList();
	//ExcuteGalvoPara(&m_GalvoPara, false, false);
	SetLaserDelays(m_GalvoPara.m_dLaserOnDelay, m_GalvoPara.m_dLaserOffDelay);
	//scanner delays
	SetScannerDelay(m_GalvoPara.m_dJumpDelay, m_GalvoPara.m_dMarkDelay, m_GalvoPara.m_dPolygonDelay);
	SetMarkSpeed(m_GalvoPara.m_dMarkSpeed);		
	SetJumpSpeed(m_GalvoPara.m_dJumpSpeed);	
	//wobbel
	SetWobbel(m_GalvoPara.m_dWobelAmpl, m_GalvoPara.m_dWobelFreq);	
	//frequency
	SetLaserPara(m_GalvoPara.m_dFrequency, m_GalvoPara.m_dPulseWidth);	
	SSetAnologOut1(Power2Volt(m_GalvoPara.m_dPower));
	EndOfList();

	return true;
}


bool RTC5::InitialRTC()
{
	m_State=DEVICE_STATE_NOT_INITIALIZED;
	
	if(gLibRTC!=NULL)
	{
		free_rtc5_dll();
		FreeLibrary(gLibRTC);
		gLibRTC=NULL;
	}
	
	gLibRTC=LoadLibrary("RTC5DLL.dll");
	
	if(gLibRTC==NULL)
	{
		return false;
	}
	
	RTCOpen(gLibRTC);
	
	UINT  ErrorCode;	
	CString str;
	
	ErrorCode=init_rtc5_dll();
	
	if ( ErrorCode != 0U )
	{
		const UINT QuantityOfRTC5s(rtc5_count_cards());		
		if ( QuantityOfRTC5s )
		{
			UINT AccError( 0U );
			
			//  Detailed error analysis
			for (UINT i(1); i <= QuantityOfRTC5s; i++ )
			{
				acquire_rtc(i);
				
				const UINT Error(n_get_last_error( i ));
				
				if ( Error != 0U ) 
				{
					AccError |= Error;
					str.Format("Laser error detected on card no. %u, code %u detected, reset error!\n", i, Error );
					n_reset_error( i, Error );
					//					free_rtc5_dll();
					AfxMessageBox(str);
					//					return false;
				}
			}
			//  			
			//  			if ( AccError != 0U )
			//  			{
			//  				free_rtc5_dll();
			//  				return false;
			//  			}
		}
		else
		{
			str.Format("Initializing the DLL: Error %u detected\n, no RTC5 card was found!", ErrorCode );
			AfxMessageBox(str);
			free_rtc5_dll();
			return false;
		}
	}
	else 
	{
		const UINT  DefaultCard(1U);            //  number of default card
		
		if ( DefaultCard!= select_rtc(DefaultCard))
		{
			ErrorCode =n_get_last_error(DefaultCard);
			
			if(ErrorCode&256U ) //  RTC5_VERSION_MISMATCH
			{
				//  In this case load_program_file(0) would not work.
				ErrorCode = n_load_program_file( DefaultCard, 0 );
			}
			else
			{
				str.Format( "No acces to card no. %u\n", DefaultCard );
				AfxMessageBox(str);
				free_rtc5_dll();
				return false;
			}
			
			if ( ErrorCode )
			{
				str.Format( "No access to card no. %u\n", DefaultCard );
				AfxMessageBox(str);
				free_rtc5_dll();
				return false;
			}
			else
			{   //  n_load_program_file was successfull
				(void)select_rtc( DefaultCard );
			}
		}
	}		
	
	//	(void) select_rtc( 1 );
	stop_execution();
	
	if(SetRTC())
	{
		Sleep(1000);
		m_State=DEVICE_STATE_OK;
		return true;
	}
	
	return false;
}

bool RTC5::LoadFile(CString filepath)
{
	UINT  ErrorCode;	
	CString str;
	
	ErrorCode = load_program_file(filepath);		//  current working path	
	if(ErrorCode) 
	{
		switch(ErrorCode)
		{
		case 1: str="Reset error: the board could not be reset.";break;
		case 2: str="Un-reset error: the board does not restart.";break;
		case 3: str="File error:program file not found or cannot be opened.";break;
		case 4: str="Format error: RTC5OUT.out has incorrect format. PCI error: driver reported an error during PCI transfer because driver is not compatible with DLL. This occurs particularly when DLL 533 or earlier is used with driver 6.1.7600.16385, or if PCI communication is in any way impaired.Up to DLL 536, error code 4 indicates a PCI error, too. As of DLL 537, PCI errors are indicated by error code 16, see the description there.";break;
		case 5: str="System error: not enough Windows memory.";break;
		case 6: str="Access error: board reserved for another user program.";break;
		case 7: str="Version error: DLL version (RTC5 DLL), RTC version (firmware file) and HEX version (DSP program file) not compatible.";break;
		case 8: str="System driver not found (get_last_error return code: RTC5_ACCESS_DENIED).";break;
		case 9: str="DriverCall error: loading of RTC5OUT.out file failed.";break;
		case 10: str="Configuration error: DSP register initialization failed.";break;
		case 11: str="Firmware error: loading of RTC5RBF.rbf file failed.";break;
		case 12: str="PCI download error: loading of RTC5DAT.dat file failed.";break;
		case 13: str="Busy error: Download locked, board is BUSY or INTERNAL-BUSY (get_last_error return code: RTC5_BUSY).";break;
		case 14: str="DSP memory error.";break;
		case 15: str="Verify error (only applicable for download verification).";break;
		case 16: str="PCI error: as of DLL 537. Or a possible driver/DLL conflict, see note on page 26:Older RTC5 DLL files (version DLL 533 and lower) are not compatible with the new WDF drivers..";break;
		default:
			str="Unknown Error.";break;
		}
		
		AfxMessageBox(str);
		m_State=DEVICE_STATE_NOT_INSTALLED;
		return false; 
	}
	
//	filepath=filepath +"\\Correction Files\\"+ m_corfile;
	
	ErrorCode = load_correction_file(filepath +"\\Correction Files\\"+ m_corfile,	1,  3);        // table; #1 is used by default, 3D
	
	if(ErrorCode)
	{
		switch(ErrorCode)
		{
		case 1: str="File error (file corrupt or incomplete).";break;
		case 2: str="Memory error (DLL-internal, WINDOWS system memory).";break;
		case 3: str="Cor File open error.";break;
		case 4: str="DSP memory error";break;
		case 5: str="PCI download error (driver error).";break;
		case 8: str="System driver not found (get_last_error return code: RTC5_ACCESS_DENIED).";break;
		case 10: str="Parameter error (incorrect No).";break;
		case 11: str="Access error: board reserved for another application (get_last_error return code: RTC5_ACCESS_DENIED) or version check has detected an error (OUT or RTC version not compatible to the current DLL version, get_last_error return code: RTC5_ACCESS_DENIED |RTC5_VERSION_MISMATCH).";break;
		case 12: str="Warning: 3D table or Dim = 3 selected, but the 3D option is not enabled. The system will subsequently operate as an ordinary 2D system (this warning is only returned, if no other error has occurred).";break;
		case 13: str="Busy error: no download, board is BUSY or INTERNAL-BUSY (get_last_error return code: RTC5_BUSY).";break;
		case 14: str="PCI upload error (driver error, only applicable for download verification).";break;
		case 15: str="Verify error (only applicable for download verification).";break;
		}
		AfxMessageBox(str);
		
		m_State=DEVICE_STATE_NOT_INSTALLED;
		return false;
	}
	
	return true;
}

void RTC5::EndOfList(bool bWait)
{
	WaitForListSpace(1);	

	set_end_of_list();
	GetBusy();

	if(!m_bTriggered && !m_Quit)
	{
		execute_list_pos(1,0);	
		m_bTriggered=true;
	}

	//	TRACE("End of List!\n");
	if(m_bTriggered && (status&0x8000))
		release_wait();	
		
	if(bWait)
		WaitForStop();
}

DriverCard RTC5::GetCardType()
{
	return cardRTC5;
}

int RTC5::GetSerielNr()
{
	return get_serial_number();
}

double RTC5::GetScanField()
{
	if(m_Scale!=0)
		return iMaxBits/m_Scale*16;
	else
		return 1;
}


void RTC5::StartList()
{
	m_Quit=false;
	m_bTriggered=false;

	bWaiterCanSet=false;
	bAskforWaiter=false;

	set_end_of_list();
	restart_list();

    set_input_pointer(0);	
	GapRun=0;
}

void RTC5::StopExcute()
{
	m_Quit=true;
	//	m_bTriggered=false;
	if(m_State>=3)	
	{
		set_end_of_list();
		stop_execution();
	}
}

void RTC5::WaitForStop()
{
    do {      
		Sleep(1);
    } while(GetBusy() && !m_Quit);
}

void RTC5::LaserOn()
{
	laser_signal_on();
}

void RTC5::LaserOff()
{
	laser_signal_off();
}

void RTC5::SetPulse(double freq, double pwidth)
{
	set_laser_pulses_ctrl(int(1.0/freq*1000000*64/2), int(pwidth*64.0));     // half of the standby period in 1/64 microseconds
}

void RTC5::SetAnalog1(double Volt)
{
	Volt=Volt>=5?5:Volt;
	Volt=Volt<0?0:Volt;
	write_da_1(int(Volt/10.0*4096));

	m_GalvoPara.m_dPower=Volt;
}

bool RTC5::SelectRTC5(int iDefault)
{
	CString str;
	UINT  ErrorCode=0;	
	const UINT QuantityOfRTC5s(rtc5_count_cards());	
	
	const UINT  DefaultCard=iDefault;            //  number of default card
	if ( DefaultCard!= select_rtc(DefaultCard))
	{
		ErrorCode =get_last_error();
		
		if(ErrorCode&256U ) //  RTC5_VERSION_MISMATCH
		{
			//  In this case load_program_file(0) would not work.
			ErrorCode = load_program_file(0 );
		}
		else
		{
			str.Format( "No Access to card no. %u\n", DefaultCard );
			AfxMessageBox(str);
			free_rtc5_dll();
			return false;
		}
		
		if (ErrorCode )
		{
			str.Format( "No access to card no. %u\n", DefaultCard );
			AfxMessageBox(str);
			free_rtc5_dll();
			return false;
		}
		else
		{   //  n_load_program_file was successful
			(void)select_rtc( DefaultCard );
		}
	}
	
	return true;
}


bool RTC5::GetBusy()
{
	get_status(&status, &position);		
	return status & 1;
}

double RTC5::GetMarkTime()
{
	ResetTimer();
	return get_time();
}

void RTC5::ResetTimer()
{
	set_start_list(1);
	save_and_restart_timer();
	set_end_of_list();
	execute_list(1);
}

void RTC5::SetOffsetList(double dx, double dy)
{
	set_offset_list(1, dx*m_Scale, dy*m_Scale, 1);
}


UINT RTC5::GetPosition()
{
	get_status(&status, &position);

	return position;
}

void RTC5::GetCurPos()
{
	//get_values()
	CurX=(double)get_value(7)/m_Scale;
	CurY=(double)get_value(8)/m_Scale;
	CurZ=(double)get_value(9)/m_Scale;
}

void RTC5::ExcuteGalvoPara(CLaserPara *pPara, bool bJudge, bool bSet)
{
	if(pPara->m_bVectorDepend)
		bJudge=false;
	//excute laser para anyway!
	if(m_bSpeedDepend||m_bPositionDepend) //last time have then reset!
	{
		SetAutoLaserParaList();
	}

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

	//frequency
	if(!bJudge || (m_GalvoPara.m_dPulseWidth!=pPara->m_dPulseWidth || m_GalvoPara.m_dFrequency!=pPara->m_dFrequency))
		SetLaserPara(pPara->m_dFrequency, pPara->m_dPulseWidth);		
	
	//wobbel
	if(!bJudge || (m_GalvoPara.m_dWobelAmpl!=pPara->m_dWobelAmpl || m_GalvoPara.m_dWobelFreq!=pPara->m_dWobelFreq))
		SetWobbel(pPara->m_dWobelAmpl, pPara->m_dWobelFreq);		

	SSetSkyWritingMode(pPara->m_iSkywritingMode);
	
	if(pPara->m_iSkywritingMode!=0)
		SSetSkyWritingPara(pPara->m_dSkywritingTimeleg, pPara->m_dSkywritingLaserOnShift, pPara->m_dSkywritingNprev, pPara->m_dSkywritingNpost);

	//	if(!bJudge || (m_GalvoPara.m_dPower!=pPara->m_dPower))
	{
		SSetAnologOut1(Power2Volt(pPara->m_dPower));
	}
	
	//have to be use para_mark_cmd
	if(pPara->m_bVectorDepend)
		SetAutoVectorCtrl(pPara->m_iVectorDependCtrl, pPara->m_dVectorDependValue);	
	//if it is closed then no necessary to repeat
	else if(bJudge && pPara->m_bVectorDepend) 
		SetAutoVectorCtrl(0, pPara->m_dVectorDependValue);	

	m_GalvoPara.SetPara(pPara);		
}

//ctrl cmd
UINT RTC5::SetAutoLaserControl(const UINT Ctrl, const UINT Value, const UINT Mode, const UINT MinValue, const UINT MaxValue)
{
	//1. Analog1 2. Analog2 3. OutputDigital 4.Pulse Width  5.Freq	
	UINT ErrorCode=0;
	switch(Ctrl)
	{
	case 1:	//analog
	case 2:
		ErrorCode=set_auto_laser_control(Ctrl, int(Value/10.0*4096), Mode, int(MinValue/10.0*4096), int(MaxValue/10.0*4096));
		break;
	case 3:
		set_auto_laser_control(Ctrl, int(Value/10*4096), Mode, int(MinValue/10*4096), int(MaxValue/10*4096));
		break;
	case 4:
		ErrorCode=set_auto_laser_control(Ctrl, int(Value*64.0), Mode, int(MinValue*64.0), int(MaxValue*64.0));	
	case 5:
		ErrorCode= set_auto_laser_control(Ctrl, int(1.0/Value*1000000*64/2), Mode, int(1.0/MaxValue*1000000*64/2), 
			int(1.0/MinValue*1000000*64/2));	
		break;
	case 6:
		set_auto_laser_control(Ctrl, int(Value/10*4096), Mode, int(MinValue/10*4096), int(MaxValue/10*4096));
		break;
	default:
		ErrorCode=set_auto_laser_control(0, Value, 0, MinValue, MaxValue);
		break;
	}
	
	switch(ErrorCode)
	{
	case 0:
		break;
	case 1:
		AfxMessageBox("No primary scan head active!");
		break;
	case 2:
		AfxMessageBox("Not an iDriver scan system!");
		break;
	case 3:
		AfxMessageBox("Ctrl parameter error!");
		break;
	case 4:
		AfxMessageBox("Mode parameter error!");
		break;
	case 5:
		AfxMessageBox("RTC5 Access denied!");
		break;
	default:
		break;
	}	
	return 1;
}

void RTC5:: SetAutoLaserParaList()
{
	WaitForListSpace(1);
	//1. Analog1 2. Analog2 3. OutputDigital 4.Pulse Width  5.Freq	
	double dmin;
	double dmax;
	double dvalue;

	switch(m_iAutoDependCtrl)
	{
	case 1:	//analog
	case 2:
		dvalue=Power2Volt(m_GalvoPara.m_dPower);
		dmin=m_AdvLaserMin*dvalue;
		dmax=m_AdvLaserMax*dvalue;
		set_auto_laser_params_list(m_iAutoDependCtrl, int(dvalue/10.0*4096), int(dmin/10.0*4096), int(dmax/10.0*4096));
		break;
	case 3: //OutputDigital
		dvalue=Power2Volt(m_GalvoPara.m_dPower);
		dmin=m_AdvLaserMin*dvalue;
		dmax=m_AdvLaserMax*dvalue;
		set_auto_laser_params_list(m_iAutoDependCtrl, int(dvalue/10*4096), int(dmin/10*4096), int(dmax/10*4096));
		break;
	case 4: //Pulse Width
		dvalue=m_GalvoPara.m_dPulseWidth;
		dmin=m_AdvLaserMin*dvalue;
		dmax=m_AdvLaserMax*dvalue;
		set_auto_laser_params_list(m_iAutoDependCtrl, int(dvalue*64.0), int(dmin*64.0), int(dmax*64.0));	
	case 5: //Freq
		dvalue=m_GalvoPara.m_dFrequency;
		dmin=m_AdvLaserMin*dvalue;
		dmax=m_AdvLaserMax*dvalue;
		set_auto_laser_params_list(m_iAutoDependCtrl, int(1.0/dvalue*1000000*64/2), int(1.0/dmax*1000000*64/2), 
			int(1.0/dmin*1000000*64/2));	
		break;
	case 6:	//digital out
		dvalue=Power2Volt(m_GalvoPara.m_dPower);
		dmin=m_AdvLaserMin*dvalue;
		dmax=m_AdvLaserMax*dvalue;
		set_auto_laser_params_list(m_iAutoDependCtrl, int(dvalue/10*4096), int(dmin/10*4096), int(dmax/10*4096));
		break;
	default:
		set_auto_laser_params_list(0, 0, 0, 0);
		break;
	}
	//	m_iAutoDependCtrl=(int)icrtrl;
}

void RTC5:: SetAutoVectorCtrl(int ictrl, double dvalue)
{
	switch((int)ictrl)
	{
	case 1:
	case 2: //analog
		dvalue=dvalue/10.0*4096;
		break;
	case 3:
		dvalue=dvalue/10.0*4096;
		break;
	case 4:
		dvalue=dvalue*64.0;
	case 5:
		dvalue=1.0/dvalue*1000000*64/2;
		break;
	case 6:
		dvalue=dvalue/10.0*4096;
		break;
	case 7: // focus
		dvalue=dvalue*m_Scale/16.0;
		break;
	default:
		break;
	}
	WaitForListSpace(1);	

	set_vector_control((int)ictrl, (int)dvalue);	
}

void RTC5::StopAutoLaserControl() //ctrl cmd
{
	set_auto_laser_control(0,0,0,0,0);	
}


void  RTC5::SetTrigger(UINT Period, UINT Signal1,UINT Signal2)
{
	set_trigger(Period, Signal1, Signal2);
}

void RTC5::MeasurementStatus( UINT* busy, UINT* position )
{
	measurement_status(busy, position);
}


void RTC5:: WaitForListSpace(int iGap)
{
	iLoadPos=get_input_pointer(); 
		//go back to 0
	if(iLoadPos==iMaxListPos) //must =iMaxlistPos, not iMaxlistpos-1, otherwise position cann't go back to head!!!!!	
	{
		set_input_pointer(0);
		iLoadPos=0; 
	}

	if(bAskforWaiter && bWaiterCanSet && m_bTriggered)
	{
		set_wait(1);				
		bWaiterCanSet=false;
		bAskforWaiter=false;
	}

	GetBusy();

	if(!m_bTriggered)
		position=0;
	//load wait
	do
	{		
		LoadGap= (position< iLoadPos)? (position+iMaxListPos-iLoadPos):(position-iLoadPos);		
		
	}while(LoadGap<(iGap+10) && GetBusy() && !m_Quit);
	
	//get_wait_status not trustable, status paused not trustable!
	if(!m_bTriggered)
		position=0;

	if(position<= iLoadPos)
        GapRun= iLoadPos - position;
    else 
        GapRun=iLoadPos + iMaxListPos-position;
	
	if(GapRun > RunGap) // in wait??
	{
        if (m_bTriggered && (status & 0x8000)) //not busy and paused
			release_wait();

		if(!m_bTriggered)
		{
			execute_at_pointer(0);			
			m_bTriggered=true;
		}	
	}
	//run speed too fast
	if((GapRun < RunGap/3) && (status &0x8000)) //pause not set
	{
		bAskforWaiter=true;
		bWaiterCanSet=false;
	}	
}

void RTC5:: SetLaserDelays(double dlaserondelay, double dlaseroffdelay)
{
	WaitForListSpace(1);
	set_laser_delays(dlaserondelay/0.5, dlaseroffdelay/0.5);

	m_GalvoPara.m_dLaserOnDelay= dlaserondelay;
	m_GalvoPara.m_dLaserOffDelay= dlaseroffdelay;
}		//laser on and off delays


void RTC5:: SetScannerDelay(double dmarkdelay, double djumpdelay, double dpolygondelay)
{
	WaitForListSpace(1);
	set_scanner_delays(djumpdelay/10, dmarkdelay/10, dpolygondelay/10);

	m_GalvoPara.m_dJumpDelay=djumpdelay;
	m_GalvoPara.m_dMarkDelay=dmarkdelay;
	m_GalvoPara.m_dPolygonDelay=dpolygondelay;

}	//jump,mark and polygon delays

void RTC5:: SetJumpSpeed(double djumpspeed)
{
	WaitForListSpace(1);
	set_jump_speed(djumpspeed*m_Scale/1000);
	m_GalvoPara.m_dJumpSpeed=djumpspeed;

}
void RTC5:: SetMarkSpeed(double dmarkspeed)
{
	WaitForListSpace(1);
	set_mark_speed(dmarkspeed*m_Scale/1000);
	m_GalvoPara.m_dMarkSpeed=dmarkspeed;
}


void RTC5:: SetLaserPara(double dfreq, double dpulsewidth)
{
	WaitForListSpace(1);

	set_laser_pulses(32.0/dfreq*1000000,     // half of the standby period in 1/64 microseconds
			dpulsewidth*64);

	m_GalvoPara.m_dFrequency=dfreq;
	m_GalvoPara.m_dPulseWidth=dpulsewidth;
} 		//freq, p


void RTC5:: SetWobbel(double dampl, double dfreq)
{
	WaitForListSpace(1);
	set_wobbel(dampl*m_Scale, dampl*m_Scale, dfreq);
	m_GalvoPara.m_dWobelAmpl=dampl;
	m_GalvoPara.m_dWobelFreq=dfreq;

}

void RTC5:: SPoint(double dx, double dy, double dz, double dtime)
{
	WaitForListSpace(1);
	jump_abs_3d(dx*m_Scale, dy*m_Scale,dz*m_Scale/16);
	laser_on_list(dtime/10+1);
}
///	
void RTC5:: SMarkTo(double dx, double dy)
{
	WaitForListSpace(1);
	mark_abs(dx*m_Scale,dy*m_Scale);
}
void RTC5:: SJumpTo(double dx, double dy)
{
	bWaiterCanSet=true;
	WaitForListSpace(1);
	jump_abs(dx*m_Scale,dy*m_Scale);
}
void RTC5:: SArcTo(double dx, double dy, double dangle)
{
	if(dangle>3600 || dangle<-3600)
	{
		if(dangle>3600)
		{
			WaitForListSpace(1);
			arc_abs(dx*m_Scale,dy*m_Scale,3600);
			dangle-=3600;
		}
		else if(dangle<-3600)
		{
			WaitForListSpace(1);
			arc_abs(dx*m_Scale,dy*m_Scale, -3600);
			dangle+=3600;
		}
		
		SArcTo(dx, dy, dangle);
	}
	else
	{
		WaitForListSpace(1);
		arc_abs(dx*m_Scale,dy*m_Scale, dangle);
	}
}

void RTC5:: SMark3DTo(double dx, double dy, double dz)
{
	WaitForListSpace(1);
	mark_abs_3d(dx*m_Scale,dy*m_Scale, dz*m_Scale/16);
}

void RTC5:: SJump3DTo(double dx, double dy, double dz)
{
	bWaiterCanSet=true;
	WaitForListSpace(1);
	jump_abs_3d(dx*m_Scale,dy*m_Scale, dz*m_Scale/16);
}

void RTC5:: SArc3DTo(double dx, double dy, double dz, double dangle)
{	
	if(dangle>3600 || dangle<-3600)
	{
		if(dangle>3600)
		{
			WaitForListSpace(1);
			arc_abs(dx*m_Scale,dy*m_Scale,3600);
			dangle-=3600;
		}
		else if(dangle<-3600)
		{
			WaitForListSpace(1);
			arc_abs(dx*m_Scale,dy*m_Scale, -3600);
			dangle+=3600;
		}
		
		SArc3DTo(dx, dy, dz, dangle);
	}
	else
	{
		WaitForListSpace(1);
		arc_abs(dx*m_Scale,dy*m_Scale, dangle);
	}

}

void RTC5:: SMarkRelTo(double dx, double dy)
{
	WaitForListSpace(1);
	mark_rel(dx*m_Scale,dy*m_Scale);
}
void RTC5:: SJumpRelTo(double dx, double dy)
{
	bWaiterCanSet=true;
	WaitForListSpace(1);
	jump_rel(dx*m_Scale,dy*m_Scale);
}
	
void RTC5:: SArcRelTo(double dx, double dy, double dangle)
{
	if(dangle>3600 || dangle<-3600)
	{
		if(dangle>3600)
		{
			WaitForListSpace(1);
			arc_rel(dx*m_Scale,dy*m_Scale,3600);
			dangle-=3600;
		}
		else if(dangle<-3600)
		{
			WaitForListSpace(1);
			arc_rel(dx*m_Scale,dy*m_Scale, -3600);
			dangle+=3600;
		}
		
		SArcRelTo(dx, dy, dangle);
	}
	else
	{
		WaitForListSpace(1);
		arc_rel(dx*m_Scale,dy*m_Scale, dangle);
	}

}

void RTC5:: SMark3DRelTo(double dx, double dy, double dz)
{
	WaitForListSpace(1);
	mark_rel_3d(dx*m_Scale,dy*m_Scale, dz*m_Scale/16);
}
void RTC5:: SJump3DRelTo(double dx, double dy, double dz)
{
	bWaiterCanSet=true;
	WaitForListSpace(1);
	jump_rel_3d(dx*m_Scale,dy*m_Scale, dz*m_Scale/16);
}
void RTC5:: SArc3DRelTo(double dx, double dy, double dz, double dangle)
{
	if(dangle>3600 || dangle<-3600)
	{
		if(dangle>3600)
		{
			WaitForListSpace(1);
			arc_rel(dx*m_Scale,dy*m_Scale,3600);
			dangle-=3600;
		}
		else if(dangle<-3600)
		{
			WaitForListSpace(1);
			arc_rel(dx*m_Scale,dy*m_Scale, -3600);
			dangle+=3600;
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
void RTC5:: SSetZPosition(double dz)
{
	WaitForListSpace(1);
	jump_rel_3d(0,0, dz*m_Scale/16);
}

void RTC5:: SSetPixelLine(int ichanel, double dperiod, double dx, double dy, double dz)
{
	WaitForListSpace(1);
	set_pixel_line_3d(ichanel, dperiod*32, dx*m_Scale, dy*m_Scale,dz*m_Scale/16);	
	
	iBmpChanel=ichanel;
	dBmpPeriod=dperiod;
	dBmpx=dx;
	dBmpy=dy;
	dBmpz=dz;

}
void RTC5:: SSetPixel(double dpulsewidth, double dvoltage, int npixel)
{
	WaitForListSpace(2);

	if(m_bTriggered && get_input_pointer()==0)
		set_pixel_line_3d(iBmpChanel, dBmpPeriod*32, dBmpx*m_Scale, dBmpy*m_Scale, dBmpz*m_Scale/16);	

	set_n_pixel(dpulsewidth*64, dvoltage/10*4096, npixel);
}

//LaserControl
void RTC5:: SSetLaserOnList(double dt)
{
	WaitForListSpace(1);
	laser_on_list(dt/10);
}
void RTC5:: SSetDelayOnList(double dt)
{
	WaitForListSpace(1);
	long_delay(unsigned(dt/10)+1);
}
//	SAnologOut1List,// power
void RTC5:: SSetAnologOut1(double dvoltage)
{
	//	write_da_1(para1/10*4096); //us
	dvoltage=dvoltage>=5?5:dvoltage;
	dvoltage=dvoltage<0?0:dvoltage;

	WaitForListSpace(1);

	write_da_1_list(int(dvoltage/10.0*4096));

	m_GalvoPara.m_dPower=dvoltage;
} 
void RTC5:: SSetLongDelay(double dt)
{
	WaitForListSpace(1);

	long_delay(dt/10);	//us
}

void RTC5:: SSetFirstKiller(double dlength)
{
	WaitForListSpace(1);

	set_firstpulse_killer_list(int(dlength*64));
}

//only for rtc5
void RTC5:: SParaMarkTo(double dx, double dy, double dpara)
{
	WaitForListSpace(1);

	para_mark_abs(dx*m_Scale,dy*m_Scale,dpara);
}

void RTC5:: SParaJumpTo(double dx, double dy, double dpara)
{
	bWaiterCanSet=true;
	WaitForListSpace(1);
	para_jump_abs(dx*m_Scale,dy*m_Scale,dpara);
}

void RTC5:: SParaMark3DTo(double dx, double dy, double dz, double dpara)
{
	WaitForListSpace(1);

	para_mark_abs_3d(dx*m_Scale,dy*m_Scale,dz*m_Scale/16, dpara);
}

void RTC5:: SParaJump3DTo(double dx, double dy, double dz, double dpara)
{
	bWaiterCanSet=true;
	WaitForListSpace(1);
	para_jump_abs_3d(dx*m_Scale,dy*m_Scale,dz*m_Scale/16, dpara);
}

//microvector
void RTC5:: SMicroVector(double dx, double dy, double laseron, double laseroff)
{
	WaitForListSpace(1);
	micro_vector_abs(dx*m_Scale, dy*m_Scale, laseron/0.5, laseroff/0.5);
}

void RTC5:: SMicroVector3D(double dx, double dy, double dz, double laseron, double laseroff)
{
	WaitForListSpace(1);
	micro_vector_abs_3d(dx*m_Scale, dy*m_Scale, dz*m_Scale/16, laseron/0.5, laseroff/0.5);
}

void RTC5:: SMicroVectorRel(double dx, double dy,  double laseron, double laseroff)
{
	WaitForListSpace(1);

	micro_vector_rel(dx*m_Scale, dy*m_Scale, laseron/0.5, laseroff/0.5);
}

void RTC5:: SMicroVectorRel3D(double dx, double dy, double dz, double laseron, double laseroff)
{
	WaitForListSpace(1);

	micro_vector_rel_3d(dx*m_Scale, dy*m_Scale, dz*m_Scale/16, laseron/0.5, laseroff/0.5);
}

//SkyWriting
void RTC5:: SSetSkyWritingMode(int imode)
{
	WaitForListSpace(1);
	m_GalvoPara.m_iSkywritingMode=imode;
	set_sky_writing_mode_list(m_GalvoPara.m_iSkywritingMode);
}
void RTC5:: SSetSkyWritingPara(double dtimeleg, double dlaseronshift, double nprev, double npost)
{
// 	m_GalvoPara.m_dSkywritingTimeleg=dtimeleg;
// 	m_GalvoPara.m_dSkywritingLaserOnShift=dlaseronshift;
// 	m_GalvoPara.m_dSkywritingNprev=nprev;
// 	m_GalvoPara.m_dSkywritingNpost=npost;

	WaitForListSpace(1);

	set_sky_writing_para_list(m_GalvoPara.m_dSkywritingTimeleg,2*m_GalvoPara.m_dSkywritingLaserOnShift,
		m_GalvoPara.m_dSkywritingNprev/10,m_GalvoPara.m_dSkywritingNpost/10);
}
//
void RTC5:: SListContinue()
{
	WaitForListSpace(1);
	list_continue();
}

