#include <windows.h>

#include "STDAFX.H"
#include "RTC6expl.h"
#include "math.h"


RTC6::~RTC6()
{
	int bValue;
	bValue=(int)m_bAdvScanAheadDelay;

	Update("GalvoSettings", "ScanAheadDelay", bValue, true);
	Update("GalvoSettings", "ScanAheadCornerScale", m_dCornerScale, true);
	Update("GalvoSettings", "ScanAheadEndScale", m_dEndScale, true);
	Update("GalvoSettings", "ScanAheadAccScale", m_dAccScale, true);

	Update("GalvoSettings", "ScanAheadLaserOn", m_dAdvScanAheadLaserOn, true);
	Update("GalvoSettings", "ScanAheadLaserOff", m_dAdvScanAheadLaserOff, true);

	if (gLibRTC != NULL)
	{
		free_rtc6_dll();
		(void)FreeLibrary(gLibRTC);		
		gLibRTC=NULL;
	}
	
}

RTC6::RTC6(CWnd* pOwner) :RTC5(pOwner)
{
	//	m_CardType = cardRTC6;
	int bValue;
	bValue=(int)m_bAdvScanAheadDelay;

	if(!Update("GalvoSettings", "ScanAheadDelay", bValue, false))
		m_bAdvScanAheadDelay=false;
	else
		m_bAdvScanAheadDelay=(bool)bValue;

	if(!Update("GalvoSettings", "ScanAheadCornerScale", m_dCornerScale, false))
		m_dCornerScale=0;

	if(!Update("GalvoSettings", "ScanAheadEndScale", m_dEndScale, false))
		m_dEndScale=0;

	if(!Update("GalvoSettings", "ScanAheadAccScale", m_dAccScale, false))
		m_dAccScale=0;

	if(!Update("GalvoSettings", "ScanAheadLaserOn", m_dAdvScanAheadLaserOn, false))
		m_dAdvScanAheadLaserOn=0;

	if(!Update("GalvoSettings", "ScanAheadLaserOff", m_dAdvScanAheadLaserOff, false))
		m_dAdvScanAheadLaserOff=0;

	gLibRTC=NULL;
	
	m_State = DEVICE_STATE_NOT_INITIALIZED;
}

long RTC6::RTCOpen(HINSTANCE gLibRTC)
{
	
	// Get the addresses of the DLL-Functions
	init_rtc6_dll = (INIT_RTC6_DLL_FP) GetProcAddress(gLibRTC,"init_rtc6_dll");
	free_rtc6_dll = (FREE_RTC6_DLL_FP) GetProcAddress(gLibRTC,"free_rtc6_dll");
	set_rtc4_mode = (SET_RTC4_MODE_FP) GetProcAddress(gLibRTC,"set_rtc4_mode");
	set_rtc5_mode = (SET_RTC5_MODE_FP) GetProcAddress(gLibRTC,"set_rtc5_mode");
	set_rtc6_mode = (SET_RTC6_MODE_FP) GetProcAddress(gLibRTC,"set_rtc6_mode");

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

	eth_count_cards = (ETH_COUNT_CARDS_FP) GetProcAddress(gLibRTC,"eth_count_cards");
	eth_found_cards = (ETH_FOUND_CARDS_FP) GetProcAddress(gLibRTC,"eth_found_cards");
	eth_max_card = (ETH_MAX_CARD_FP) GetProcAddress(gLibRTC,"eth_max_card");
	eth_remove_card = (ETH_REMOVE_CARD_FP) GetProcAddress(gLibRTC,"eth_remove_card");
	eth_get_card_info = (ETH_GET_CARD_INFO_FP) GetProcAddress(gLibRTC,"eth_get_card_info");
	eth_get_card_info_search = (ETH_GET_CARD_INFO_SEARCH_FP) GetProcAddress(gLibRTC,"eth_get_card_info_search");
	eth_set_search_cards_timeout = (ETH_SET_SEARCH_CARDS_TIMEOUT_FP) GetProcAddress(gLibRTC,"eth_set_search_cards_timeout");
	eth_search_cards = (ETH_SEARCH_CARDS_FP) GetProcAddress(gLibRTC,"eth_search_cards");
	eth_search_cards_range = (ETH_SEARCH_CARDS_RANGE_FP) GetProcAddress(gLibRTC,"eth_search_cards_range");
	eth_assign_card_ip = (ETH_ASSIGN_CARD_IP_FP) GetProcAddress(gLibRTC,"eth_assign_card_ip");
	eth_assign_card = (ETH_ASSIGN_CARD_FP) GetProcAddress(gLibRTC,"eth_assign_card");
	eth_convert_string_to_ip = (ETH_CONVERT_STRING_TO_IP_FP) GetProcAddress(gLibRTC,"eth_convert_string_to_ip");
	eth_convert_ip_to_string = (ETH_CONVERT_IP_TO_STRING_FP) GetProcAddress(gLibRTC,"eth_convert_ip_to_string");
	eth_get_ip = (ETH_GET_IP_FP) GetProcAddress(gLibRTC,"eth_get_ip");
	eth_get_ip_search = (ETH_GET_IP_SEARCH_FP) GetProcAddress(gLibRTC,"eth_get_ip_search");
	eth_get_serial_search = (ETH_GET_SERIAL_SEARCH_FP) GetProcAddress(gLibRTC,"eth_get_serial_search");
	n_eth_get_last_error = (N_ETH_GET_LAST_ERROR_FP) GetProcAddress(gLibRTC,"n_eth_get_last_error");
	n_eth_get_error = (N_ETH_GET_ERROR_FP) GetProcAddress(gLibRTC,"n_eth_get_error");
	n_eth_error_dump = (N_ETH_ERROR_DUMP_FP) GetProcAddress(gLibRTC,"n_eth_error_dump");
	n_eth_set_static_ip = (N_ETH_SET_STATIC_IP_FP) GetProcAddress(gLibRTC,"n_eth_set_static_ip");
	n_eth_get_static_ip = (N_ETH_GET_STATIC_IP_FP) GetProcAddress(gLibRTC,"n_eth_get_static_ip");
	n_eth_set_port_numbers = (N_ETH_SET_PORT_NUMBERS_FP) GetProcAddress(gLibRTC,"n_eth_set_port_numbers");
	n_eth_get_port_numbers = (N_ETH_GET_PORT_NUMBERS_FP) GetProcAddress(gLibRTC,"n_eth_get_port_numbers");
	n_eth_set_com_timeouts = (N_ETH_SET_COM_TIMEOUTS_FP) GetProcAddress(gLibRTC,"n_eth_set_com_timeouts");
	n_eth_get_com_timeouts = (N_ETH_GET_COM_TIMEOUTS_FP) GetProcAddress(gLibRTC,"n_eth_get_com_timeouts");
	n_eth_check_connection = (N_ETH_CHECK_CONNECTION_FP) GetProcAddress(gLibRTC,"n_eth_check_connection");
	eth_get_last_error = (ETH_GET_LAST_ERROR_FP) GetProcAddress(gLibRTC,"eth_get_last_error");
	eth_get_error = (ETH_GET_ERROR_FP) GetProcAddress(gLibRTC,"eth_get_error");
	eth_error_dump = (ETH_ERROR_DUMP_FP) GetProcAddress(gLibRTC,"eth_error_dump");
	eth_set_static_ip = (ETH_SET_STATIC_IP_FP) GetProcAddress(gLibRTC,"eth_set_static_ip");
	eth_get_static_ip = (ETH_GET_STATIC_IP_FP) GetProcAddress(gLibRTC,"eth_get_static_ip");
	eth_set_port_numbers = (ETH_SET_PORT_NUMBERS_FP) GetProcAddress(gLibRTC,"eth_set_port_numbers");
	eth_get_port_numbers = (ETH_GET_PORT_NUMBERS_FP) GetProcAddress(gLibRTC,"eth_get_port_numbers");
	eth_set_com_timeouts = (ETH_SET_COM_TIMEOUTS_FP) GetProcAddress(gLibRTC,"eth_set_com_timeouts");
	eth_get_com_timeouts = (ETH_GET_COM_TIMEOUTS_FP) GetProcAddress(gLibRTC,"eth_get_com_timeouts");
	eth_check_connection = (ETH_CHECK_CONNECTION_FP) GetProcAddress(gLibRTC,"eth_check_connection");
	read_abc_from_file = (READ_ABC_FROM_FILE_FP) GetProcAddress(gLibRTC,"read_abc_from_file");
	write_abc_to_file = (WRITE_ABC_TO_FILE_FP) GetProcAddress(gLibRTC,"write_abc_to_file");
	rtc6_count_cards = (RTC6_COUNT_CARDS_FP) GetProcAddress(gLibRTC,"rtc6_count_cards");
	acquire_rtc = (ACQUIRE_RTC_FP) GetProcAddress(gLibRTC,"acquire_rtc");
	release_rtc = (RELEASE_RTC_FP) GetProcAddress(gLibRTC,"release_rtc");
	select_rtc = (SELECT_RTC_FP) GetProcAddress(gLibRTC,"select_rtc");
	get_dll_version = (GET_DLL_VERSION_FP) GetProcAddress(gLibRTC,"get_dll_version");
	n_get_card_type = (N_GET_CARD_TYPE_FP) GetProcAddress(gLibRTC,"n_get_card_type");
	n_get_serial_number = (N_GET_SERIAL_NUMBER_FP) GetProcAddress(gLibRTC,"n_get_serial_number");
	n_get_hex_version = (N_GET_HEX_VERSION_FP) GetProcAddress(gLibRTC,"n_get_hex_version");
	n_get_rtc_version = (N_GET_RTC_VERSION_FP) GetProcAddress(gLibRTC,"n_get_rtc_version");
	n_get_bios_version = (N_GET_BIOS_VERSION_FP) GetProcAddress(gLibRTC,"n_get_bios_version");
	get_card_type = (GET_CARD_TYPE_FP) GetProcAddress(gLibRTC,"get_card_type");
	get_serial_number = (GET_SERIAL_NUMBER_FP) GetProcAddress(gLibRTC,"get_serial_number");
	get_hex_version = (GET_HEX_VERSION_FP) GetProcAddress(gLibRTC,"get_hex_version");
	get_rtc_version = (GET_RTC_VERSION_FP) GetProcAddress(gLibRTC,"get_rtc_version");
	get_bios_version = (GET_BIOS_VERSION_FP) GetProcAddress(gLibRTC,"get_bios_version");
	n_load_program_file = (N_LOAD_PROGRAM_FILE_FP) GetProcAddress(gLibRTC,"n_load_program_file");
//	n_store_program = (N_STORE_PROGRAM_FP) GetProcAddress(gLibRTC,"n_store_program");
//	n_get_init_status = (N_GET_INIT_STATUS_FP) GetProcAddress(gLibRTC,"n_get_init_status");
	n_sync_slaves = (N_SYNC_SLAVES_FP) GetProcAddress(gLibRTC,"n_sync_slaves");
	n_get_sync_status = (N_GET_SYNC_STATUS_FP) GetProcAddress(gLibRTC,"n_get_sync_status");
	n_load_correction_file = (N_LOAD_CORRECTION_FILE_FP) GetProcAddress(gLibRTC,"n_load_correction_file");
	n_load_zoom_correction_file = (N_LOAD_ZOOM_CORRECTION_FILE_FP) GetProcAddress(gLibRTC,"n_load_zoom_correction_file");
	n_load_z_table = (N_LOAD_Z_TABLE_FP) GetProcAddress(gLibRTC,"n_load_z_table");
	n_select_cor_table = (N_SELECT_COR_TABLE_FP) GetProcAddress(gLibRTC,"n_select_cor_table");
	n_set_dsp_mode = (N_SET_DSP_MODE_FP) GetProcAddress(gLibRTC,"n_set_dsp_mode");
	n_load_stretch_table = (N_LOAD_STRETCH_TABLE_FP) GetProcAddress(gLibRTC,"n_load_stretch_table");
	n_get_head_para = (N_GET_HEAD_PARA_FP) GetProcAddress(gLibRTC,"n_get_head_para");
	n_get_table_para = (N_GET_TABLE_PARA_FP) GetProcAddress(gLibRTC,"n_get_table_para");
	load_program_file = (LOAD_PROGRAM_FILE_FP) GetProcAddress(gLibRTC,"load_program_file");
//	store_program = (STORE_PROGRAM_FP) GetProcAddress(gLibRTC,"store_program");
//	get_init_status = (GET_INIT_STATUS_FP) GetProcAddress(gLibRTC,"get_init_status");
	sync_slaves = (SYNC_SLAVES_FP) GetProcAddress(gLibRTC,"sync_slaves");
	get_sync_status = (GET_SYNC_STATUS_FP) GetProcAddress(gLibRTC,"get_sync_status");
	load_correction_file = (LOAD_CORRECTION_FILE_FP) GetProcAddress(gLibRTC,"load_correction_file");
	load_zoom_correction_file = (LOAD_ZOOM_CORRECTION_FILE_FP) GetProcAddress(gLibRTC,"load_zoom_correction_file");
	load_z_table = (LOAD_Z_TABLE_FP) GetProcAddress(gLibRTC,"load_z_table");
	select_cor_table = (SELECT_COR_TABLE_FP) GetProcAddress(gLibRTC,"select_cor_table");
	set_dsp_mode = (SET_DSP_MODE_FP) GetProcAddress(gLibRTC,"set_dsp_mode");
	load_stretch_table = (LOAD_STRETCH_TABLE_FP) GetProcAddress(gLibRTC,"load_stretch_table");
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
//	n_set_laser_power = (N_SET_LASER_POWER_FP) GetProcAddress(gLibRTC,"n_set_laser_power");
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
//	set_laser_power = (SET_LASER_POWER_FP) GetProcAddress(gLibRTC,"set_laser_power");
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
	n_set_free_variable = (N_SET_FREE_VARIABLE_FP) GetProcAddress(gLibRTC,"n_set_free_variable");
	n_get_free_variable = (N_GET_FREE_VARIABLE_FP) GetProcAddress(gLibRTC,"n_get_free_variable");
	n_set_mcbsp_out_ptr = (N_SET_MCBSP_OUT_PTR_FP) GetProcAddress(gLibRTC,"n_set_mcbsp_out_ptr");
	n_periodic_toggle = (N_PERIODIC_TOGGLE_FP) GetProcAddress(gLibRTC,"n_periodic_toggle");
//	n_multi_axis_config = (N_MULTI_AXIS_CONFIG_FP) GetProcAddress(gLibRTC,"n_multi_axis_config");
//	n_quad_axis_init = (N_QUAD_AXIS_INIT_FP) GetProcAddress(gLibRTC,"n_quad_axis_init");
//	n_quad_axis_get_status = (N_QUAD_AXIS_GET_STATUS_FP) GetProcAddress(gLibRTC,"n_quad_axis_get_status");
//	n_quad_axis_get_values = (N_QUAD_AXIS_GET_VALUES_FP) GetProcAddress(gLibRTC,"n_quad_axis_get_values");
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
	set_free_variable = (SET_FREE_VARIABLE_FP) GetProcAddress(gLibRTC,"set_free_variable");
	get_free_variable = (GET_FREE_VARIABLE_FP) GetProcAddress(gLibRTC,"get_free_variable");
	set_mcbsp_out_ptr = (SET_MCBSP_OUT_PTR_FP) GetProcAddress(gLibRTC,"set_mcbsp_out_ptr");
	periodic_toggle = (PERIODIC_TOGGLE_FP) GetProcAddress(gLibRTC,"periodic_toggle");
//	multi_axis_config = (MULTI_AXIS_CONFIG_FP) GetProcAddress(gLibRTC,"multi_axis_config");
//	quad_axis_init = (QUAD_AXIS_INIT_FP) GetProcAddress(gLibRTC,"quad_axis_init");
//	quad_axis_get_status = (QUAD_AXIS_GET_STATUS_FP) GetProcAddress(gLibRTC,"quad_axis_get_status");
//	quad_axis_get_values = (QUAD_AXIS_GET_VALUES_FP) GetProcAddress(gLibRTC,"quad_axis_get_values");
	n_set_defocus = (N_SET_DEFOCUS_FP) GetProcAddress(gLibRTC,"n_set_defocus");
	n_goto_xyz = (N_GOTO_XYZ_FP) GetProcAddress(gLibRTC,"n_goto_xyz");
	n_set_zoom = (N_SET_ZOOM_FP) GetProcAddress(gLibRTC,"n_set_zoom");
	n_goto_xy = (N_GOTO_XY_FP) GetProcAddress(gLibRTC,"n_goto_xy");
	n_get_z_distance = (N_GET_Z_DISTANCE_FP) GetProcAddress(gLibRTC,"n_get_z_distance");
	set_defocus = (SET_DEFOCUS_FP) GetProcAddress(gLibRTC,"set_defocus");
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
//	n_set_timelag_compensation = (N_SET_TIMELAG_COMPENSATION_FP) GetProcAddress(gLibRTC,"n_set_timelag_compensation");
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
//	set_timelag_compensation = (SET_TIMELAG_COMPENSATION_FP) GetProcAddress(gLibRTC,"set_timelag_compensation");
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
	n_get_scanahead_params = (N_GET_SCANAHEAD_PARAMS_FP) GetProcAddress(gLibRTC,"n_get_scanahead_params");
	n_activate_scanahead_autodelays = (N_ACTIVATE_SCANAHEAD_AUTODELAYS_FP) GetProcAddress(gLibRTC,"n_activate_scanahead_autodelays");
	n_set_scanahead_laser_shifts = (N_SET_SCANAHEAD_LASER_SHIFTS_FP) GetProcAddress(gLibRTC,"n_set_scanahead_laser_shifts");
	n_set_scanahead_line_params = (N_SET_SCANAHEAD_LINE_PARAMS_FP) GetProcAddress(gLibRTC,"n_set_scanahead_line_params");
	n_set_scanahead_params = (N_SET_SCANAHEAD_PARAMS_FP) GetProcAddress(gLibRTC,"n_set_scanahead_params");
	get_scanahead_params = (GET_SCANAHEAD_PARAMS_FP) GetProcAddress(gLibRTC,"get_scanahead_params");
	activate_scanahead_autodelays = (ACTIVATE_SCANAHEAD_AUTODELAYS_FP) GetProcAddress(gLibRTC,"activate_scanahead_autodelays");
	set_scanahead_laser_shifts = (SET_SCANAHEAD_LASER_SHIFTS_FP) GetProcAddress(gLibRTC,"set_scanahead_laser_shifts");
	set_scanahead_line_params = (SET_SCANAHEAD_LINE_PARAMS_FP) GetProcAddress(gLibRTC,"set_scanahead_line_params");
	set_scanahead_params = (SET_SCANAHEAD_PARAMS_FP) GetProcAddress(gLibRTC,"set_scanahead_params");
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
	n_list_call = (N_LIST_CALL_FP) GetProcAddress(gLibRTC,"n_list_call");
	n_list_call_abs = (N_LIST_CALL_ABS_FP) GetProcAddress(gLibRTC,"n_list_call_abs");
	n_sub_call_repeat = (N_SUB_CALL_REPEAT_FP) GetProcAddress(gLibRTC,"n_sub_call_repeat");
	n_sub_call_abs_repeat = (N_SUB_CALL_ABS_REPEAT_FP) GetProcAddress(gLibRTC,"n_sub_call_abs_repeat");
	n_sub_call = (N_SUB_CALL_FP) GetProcAddress(gLibRTC,"n_sub_call");
	n_sub_call_abs = (N_SUB_CALL_ABS_FP) GetProcAddress(gLibRTC,"n_sub_call_abs");
	list_return = (LIST_RETURN_FP) GetProcAddress(gLibRTC,"list_return");
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
	n_set_wobbel_direction = (N_SET_WOBBEL_DIRECTION_FP) GetProcAddress(gLibRTC,"n_set_wobbel_direction");
	n_set_wobbel_control = (N_SET_WOBBEL_CONTROL_FP) GetProcAddress(gLibRTC,"n_set_wobbel_control");
	n_set_wobbel_vector = (N_SET_WOBBEL_VECTOR_FP) GetProcAddress(gLibRTC,"n_set_wobbel_vector");
	n_set_wobbel_offset = (N_SET_WOBBEL_OFFSET_FP) GetProcAddress(gLibRTC,"n_set_wobbel_offset");
	n_set_trigger = (N_SET_TRIGGER_FP) GetProcAddress(gLibRTC,"n_set_trigger");
	n_set_trigger4 = (N_SET_TRIGGER4_FP) GetProcAddress(gLibRTC,"n_set_trigger4");
	n_set_pixel_line_3d = (N_SET_PIXEL_LINE_3D_FP) GetProcAddress(gLibRTC,"n_set_pixel_line_3d");
	n_set_pixel_line = (N_SET_PIXEL_LINE_FP) GetProcAddress(gLibRTC,"n_set_pixel_line");
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
//	n_micro_vector_quad_axis = (N_MICRO_VECTOR_QUAD_AXIS_FP) GetProcAddress(gLibRTC,"n_micro_vector_quad_axis");
//	n_micro_vector_set_position = (N_MICRO_VECTOR_SET_POSITION_FP) GetProcAddress(gLibRTC,"n_micro_vector_set_position");
	n_multi_axis_flags = (N_MULTI_AXIS_FLAGS_FP) GetProcAddress(gLibRTC,"n_multi_axis_flags");
	n_set_free_variable_list = (N_SET_FREE_VARIABLE_LIST_FP) GetProcAddress(gLibRTC,"n_set_free_variable_list");
	n_control_command_list = (N_CONTROL_COMMAND_LIST_FP) GetProcAddress(gLibRTC,"n_control_command_list");
	n_jump_abs_drill = (N_JUMP_ABS_DRILL_FP) GetProcAddress(gLibRTC,"n_jump_abs_drill");
	n_jump_rel_drill = (N_JUMP_REL_DRILL_FP) GetProcAddress(gLibRTC,"n_jump_rel_drill");
	save_and_restart_timer = (SAVE_AND_RESTART_TIMER_FP) GetProcAddress(gLibRTC,"save_and_restart_timer");
	set_wobbel = (SET_WOBBEL_FP) GetProcAddress(gLibRTC,"set_wobbel");
	set_wobbel_mode = (SET_WOBBEL_MODE_FP) GetProcAddress(gLibRTC,"set_wobbel_mode");
	set_wobbel_direction = (SET_WOBBEL_DIRECTION_FP) GetProcAddress(gLibRTC,"set_wobbel_direction");
	set_wobbel_control = (SET_WOBBEL_CONTROL_FP) GetProcAddress(gLibRTC,"set_wobbel_control");
	set_wobbel_vector = (SET_WOBBEL_VECTOR_FP) GetProcAddress(gLibRTC,"set_wobbel_vector");
	set_wobbel_offset = (SET_WOBBEL_OFFSET_FP) GetProcAddress(gLibRTC,"set_wobbel_offset");
	set_trigger = (SET_TRIGGER_FP) GetProcAddress(gLibRTC,"set_trigger");
	set_trigger4 = (SET_TRIGGER4_FP) GetProcAddress(gLibRTC,"set_trigger4");
	set_pixel_line_3d = (SET_PIXEL_LINE_3D_FP) GetProcAddress(gLibRTC,"set_pixel_line_3d");
	set_pixel_line = (SET_PIXEL_LINE_FP) GetProcAddress(gLibRTC,"set_pixel_line");
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
//	micro_vector_quad_axis = (MICRO_VECTOR_QUAD_AXIS_FP) GetProcAddress(gLibRTC,"micro_vector_quad_axis");
//	micro_vector_set_position = (MICRO_VECTOR_SET_POSITION_FP) GetProcAddress(gLibRTC,"micro_vector_set_position");
//	multi_axis_flags = (MULTI_AXIS_FLAGS_FP) GetProcAddress(gLibRTC,"multi_axis_flags");
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
	n_set_zoom_list = (N_SET_ZOOM_LIST_FP) GetProcAddress(gLibRTC,"n_set_zoom_list");
	set_defocus_list = (SET_DEFOCUS_LIST_FP) GetProcAddress(gLibRTC,"set_defocus_list");
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
	n_activate_scanahead_autodelays_list = (N_ACTIVATE_SCANAHEAD_AUTODELAYS_LIST_FP) GetProcAddress(gLibRTC,"n_activate_scanahead_autodelays_list");
	n_set_scanahead_laser_shifts_list = (N_SET_SCANAHEAD_LASER_SHIFTS_LIST_FP) GetProcAddress(gLibRTC,"n_set_scanahead_laser_shifts_list");
	n_set_scanahead_line_params_list = (N_SET_SCANAHEAD_LINE_PARAMS_LIST_FP) GetProcAddress(gLibRTC,"n_set_scanahead_line_params_list");
	activate_scanahead_autodelays_list = (ACTIVATE_SCANAHEAD_AUTODELAYS_LIST_FP) GetProcAddress(gLibRTC,"activate_scanahead_autodelays_list");
	set_scanahead_laser_shifts_list = (SET_SCANAHEAD_LASER_SHIFTS_LIST_FP) GetProcAddress(gLibRTC,"set_scanahead_laser_shifts_list");
	set_scanahead_line_params_list = (SET_SCANAHEAD_LINE_PARAMS_LIST_FP) GetProcAddress(gLibRTC,"set_scanahead_line_params_list");
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


bool RTC6::SetRTC()
{
	//	CString filepath="Correction Files\\"+ m_corfile;
	CString filepath; 

	int bDirect3DMove; 	
	int iEdgeLevel;
	int iMinJumpDelay;
	int iJumpLengthLimit;
	
	if(!Update("GalvoSettings", "VarPolygonDelay", bDirect3DMove, false))
		bDirect3DMove=0;
	
	if(!Update("GalvoSettings", "EdgeLevel", iEdgeLevel, false))
		iEdgeLevel=65535;
	
	if(!Update("GalvoSettings", "MiniJumpDelay", iMinJumpDelay, false))
		iMinJumpDelay=10;
	
	if(!Update("GalvoSettings", "JumpLengthLimit", iJumpLengthLimit, false))
		iJumpLengthLimit=10;

	GetModuleFileName(NULL, filepath.GetBuffer(MAX_PATH), MAX_PATH);
	filepath.ReleaseBuffer();
	int Pos=filepath.ReverseFind('\\');	
	filepath=filepath.Mid(0,Pos); 	
		
	if(!LoadFile(filepath))
	{
		free_rtc6_dll();
		return false;
	}
	
	if(!m_powercurvefile.IsEmpty())
		LoadPowerCurve(filepath +"\\"+ m_powercurvefile);
	
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
	//         AfxMessageBox("Please check HeadA: no intelliSCAN connected\n\n" );
	//         
	//     }	

	//For excelliScan
	if(m_bAdvScanAheadDelay)
	{
		set_scanahead_params( 1, 1, 1, 0, 0, 0); //mode, headno, tableno, prevtime, vmax, vmin
		activate_scanahead_autodelays( 1 );
		set_scanahead_line_params( m_dCornerScale, m_dEndScale, m_dAccScale); 
		set_scanahead_laser_shifts(64*m_dAdvScanAheadLaserOn, 64*m_dAdvScanAheadLaserOff);
	}
	else
		set_scanahead_params( 0, 1, 1, 0, 0, 0); //mode, headno, tableno, prevtime, vmax, vmin

	set_delay_mode(m_bVarPolyDelay, bDirect3DMove, iEdgeLevel, iMinJumpDelay, iJumpLengthLimit*m_Scale);//100	
	//all list space to list1
	config_list(-1,0);	
	iMaxListPos=get_list_space();

	config_laser_signals(m_LaserSignal);

	stop_execution();
	set_laser_mode(m_lasermode);
	set_matrix(0, xcor*cos(xyrotate*PI/180), -xcor*sin(xyrotate*PI/180), ycor*sin(xyrotate*PI/180), ycor * cos(xyrotate*PI/180), 1);
	set_offset(0, xoffset*m_Scale, yoffset*m_Scale, 1);

	set_firstpulse_killer( 64*2 );
	set_default_pixel(0);

	m_Scale=get_head_para(1,1);
	set_port_default(0,0);	
	
	if(m_bFirstPulseSync)
		set_laser_control(0x41);
	else
		set_laser_control(0x01);

	StartList();
	SetPulse(m_GalvoPara.m_dFrequency, m_GalvoPara.m_dPulseWidth);
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

bool RTC6::SelectRTC6(int iDefault)
{
	CString str;
	UINT  ErrorCode = 0;
	const UINT QuantityOfRTC5s(rtc6_count_cards());//RTC6
	
	const UINT  DefaultCard = iDefault;            //  number of default card
	if (DefaultCard != select_rtc(DefaultCard))
	{
		ErrorCode = get_last_error();
		
		if (ErrorCode & 256U) //  RTC5_VERSION_MISMATCH
		{
			//  In this case load_program_file(0) would not work.
			ErrorCode = load_program_file(0);//RTC6
		}
		else
		{
			str.Format("No Access to card no. %u\n", DefaultCard);
			AfxMessageBox(str);
			free_rtc6_dll();//RTC6
			return false;
		}
		
		if (ErrorCode)
		{
			str.Format("No access to card no. %u\n", DefaultCard);
			AfxMessageBox(str);
			free_rtc6_dll();//RTC6
			return false;
		}
		else
		{   //  n_load_program_file was successful
			(void)select_rtc(DefaultCard);
		}
	}
	
	return true;
}

DriverCard RTC6::GetCardType()
{
	return cardRTC6;
}

bool RTC6::InitialRTC()
{
	m_State = DEVICE_STATE_NOT_INITIALIZED;
	
	if (gLibRTC != NULL)
	{
		free_rtc6_dll();//RTC6
		FreeLibrary(gLibRTC);
		gLibRTC = NULL;
	}
	
	gLibRTC = LoadLibrary("RTC6DLL.dll");//RTC6
	
	if (gLibRTC == NULL)
		return false;
	
	RTCOpen(gLibRTC);//RTC6
	
	UINT  ErrorCode;
	CString str;
	
	ErrorCode = init_rtc6_dll();//RTC6
	
	if (ErrorCode != 0U)
	{
		const UINT QuantityOfRTC6s(rtc6_count_cards());//RTC6
		
		if (QuantityOfRTC6s)
		{
			UINT AccError(0U);
			
			//  Detailed error analysis
			for (UINT i(1U); i <= QuantityOfRTC6s; i++)
			{
				const UINT Error(n_get_last_error(i));
				
				if (Error != 0U)
				{
					AccError |= Error;
					str.Format("Card no. %u: Error %u detected, reset error!\n", i, Error);
					AfxMessageBox(str);
					n_reset_error(i, Error);
				}
			}
			
			if (AccError != 0U)
			{
				free_rtc6_dll();//RTC6
				return false;
			}
		}
		else
		{
			str.Format("Initializing the DLL: Error %u detected\n", ErrorCode);
			AfxMessageBox(str);
			free_rtc6_dll();//RTC6
			return false;
		}
	}
	else
	{
		const UINT  DefaultCard(1U);            //  number of default card
		if (DefaultCard != select_rtc(DefaultCard))
		{
			ErrorCode = n_get_last_error(DefaultCard);
			
			if (ErrorCode & 256U) //  RTC5_VERSION_MISMATCH
			{
				//  In this case load_program_file(0) would not work.
				ErrorCode = n_load_program_file(DefaultCard, 0);//RTC6
			}
			else
			{
				str.Format("No acces to card no. %u\n", DefaultCard);
				AfxMessageBox(str);
				free_rtc6_dll();//RTC6
				return false;
			}
			
			if (ErrorCode)
			{
				str.Format("No access to card no. %u\n", DefaultCard);
				AfxMessageBox(str);
				free_rtc6_dll();//RTC6
				return false;
			}
			else
			{   //  n_load_program_file was successfull
				(void)select_rtc(DefaultCard);
			}
		}
	}
	
	stop_execution();
	
	if (SetRTC())
	{
		Sleep(1000);
		m_State = DEVICE_STATE_OK;
		return true;
	}

	return false;
}

bool RTC6::LoadFile(CString filepath)
{
	UINT  ErrorCode;	
	CString str;
	
	ErrorCode = load_program_file(filepath);		//  current working path	
	if(ErrorCode) 
	{
		switch(ErrorCode)
		{
		case 1: str="";break;
		case 2: str="BOARD NOT RUNNING. If a renewed call does not bring success, then a Power-Cycle is necessary.";break;
		case 3: str="RTC6DAT.dat file or RTC6RBF.rbf file not found.";break;
		case 5: str="Not enough WINDOWS memory.";break;
		case 6: str="Access error: the board is reserved for another user program.";break;
		case 7: str="Version error: DLL version (RTC6DLL.dll), RTC version (firmware file RTC6RBF.rbf) and HEX version (DSP program file RTC6OUT.out) incompatible with another.";break;
		case 8: str="System driver not found.";break;
		case 9: str="Loading of RTC6OUT.out file failed or RTC6OUT.out has incorrect format or other error.";break;
		case 11: str="Firmware error: Loading of RTC6RBF.rbf file failed.";break;
		case 12: str="Error opening/reading file (RTC6DAT.dat).";break;
		case 14: str="DSP memory error.";break;
		case 15: str="Verify memory error.";break;
		case 17: str="Ethernet error.";break;
			
		default:
			str="Unknown Error.";break;
		}
		
		AfxMessageBox(str);
		m_State=DEVICE_STATE_NOT_INSTALLED;
		return false; 
	}
	
	filepath=filepath +"\\Correction Files\\"+ m_corfile;	

	ErrorCode = load_correction_file(filepath,	1,  3);        // table; #1 is used by default, 3D
	
	if(ErrorCode)
	{
		switch(ErrorCode)
		{
		case 3: str="Load correction file error"; break;
		case 4: str="Load correction file verify error"; break;
		case 8:	str="Load correction file error, System driver not found or locked by another application";break;
		case 10: str="Load correction file error, Parameter error";break;
		case 11: str="Load correction file error, RTC4 not found";break;
		case 12: str="Load correction file error, A 3D correction file could not be loaded, the function is not installed";break;
		}
		AfxMessageBox(str);
		
		m_State=DEVICE_STATE_NOT_INSTALLED;
		return false;
	}
	
	return true;
}

// 
// bool RTC6::GetBusy()
// {
// 	get_status(&busy, &position);	//RTC6
// 	//need to change for excelliSCAN. return busy & 0B0100 0000 0000 0000 0000 0001 
// 	return busy & 1;
// }
/*
void RTC6::ExcuteCMDFunc(ScannerCMD CMDCode, double para1, double para2, double para3, double para4)
{
	iLoadPos=get_input_pointer(); 
	
	if(iLoadPos==iMaxListPos)	
	{
		set_input_pointer(0);
		iLoadPos=0; 
	}
	//load wait
	do
	{
		GetBusy();
		if(!m_bTriggered)
			position=0;
		
		if(position<= iLoadPos)
			LoadGap= position+iMaxListPos-iLoadPos;		
		else
			LoadGap=position-iLoadPos;		
		
	}while(LoadGap<GapLoad && !m_Quit);
	
	//run wait
	if(position<= iLoadPos)
		RunGap= iLoadPos - position;
	else
		RunGap=iLoadPos + iMaxListPos-position;
	
	
	if(RunGap>GapRun && !m_bTriggered)
	{
		execute_list_pos(1, 0);
		m_bTriggered=true;
	}
	
	if(m_bTriggered && !m_Quit)
	{
		if(RunGap <GapRun/2 && (!(busy&0x8000))) //pause not set
		{
			pause_list();
			get_status(&busy, &RecordPos);
		}
		
		if(RunGap >GapRun && (busy&0x8000))
		{
			restart_list();
			execute_list_pos(1, RecordPos+1);
			
		}		
	}
	
	switch(CMDCode)
	{
	case SPoint:
		micro_vector_abs_3d(para1*m_Scale,para2*m_Scale, para3*m_Scale/16, 0,  para4/0.5);
		break;
	case SDelayOnList:
		long_delay(para1/10);
		break;
	case SetLaserDelays:
		set_laser_delays(para1/0.5,para2/0.5);
		m_GalvoPara.m_dLaserOnDelay= para1;
		m_GalvoPara.m_dLaserOffDelay= para2;
		break;
	case SetScannerDelay:			//in ms 
		set_scanner_delays(para1/10,para2/10,para3/10);
		m_GalvoPara.m_dJumpDelay=para1;
		m_GalvoPara.m_dMarkDelay=para2;
		m_GalvoPara.m_dPolygonDelay=para3;
		break;
	case SetLaserPara:
		set_laser_pulses(32/para1*1000000,     // half of the standby period in 1/64 microseconds
			para2*64);
		m_GalvoPara.m_dFrequency=para1;
		m_GalvoPara.m_dPulseWidth=para2;
		break;
	case SetJumpSpeed:
		set_jump_speed(para1*m_Scale/1000);
		m_GalvoPara.m_dJumpSpeed=para1;
		break;
	case SetMarkSpeed:
		set_mark_speed(para1*m_Scale/1000);
		m_GalvoPara.m_dMarkSpeed=para1;
		break;
	case SetWobbel:
		set_wobbel(para1*m_Scale,para1*m_Scale, para2);
		m_GalvoPara.m_dWobelAmpl=para1;
		m_GalvoPara.m_dWobelFreq=para2;
		break;
	case SMarkTo:
		mark_abs(para1*m_Scale,para2*m_Scale);
		break;
	case SJumpTo:
		jump_abs(para1*m_Scale,para2*m_Scale);
		break;
	case SMark3DTo:
		mark_abs_3d(para1*m_Scale,para2*m_Scale,para3*m_Scale/16);
		break;
	case SJump3DTo:
		jump_abs_3d(para1*m_Scale,para2*m_Scale,para3*m_Scale/16);
		break;
	case SMarkRelTo:
		mark_rel(para1*m_Scale,para2*m_Scale);
		break;
	case SJumpRelTo:
		jump_rel(para1*m_Scale,para2*m_Scale);
		break;
	case SMark3DRelTo:
		mark_rel_3d(para1*m_Scale,para2*m_Scale,para3*m_Scale/16);
		break;
	case SJump3DRelTo:
		jump_rel_3d(para1*m_Scale,para2*m_Scale,para3*m_Scale/16);
		break;
	case SParaMarkTo:
		para_mark_abs(para1*m_Scale,para2*m_Scale,para3);
		break;
	case SParaMark3DTo:
		para_mark_abs_3d(para1*m_Scale,para2*m_Scale,para3*m_Scale/16,para4);
		break;
	case SParaJumpTo:
		para_jump_abs(para1*m_Scale,para2*m_Scale, para3);
		break;
	case SParaJump3DTo:
		para_jump_abs_3d(para1*m_Scale,para2*m_Scale,para3*m_Scale/16, para4);
		break;
	case SArcTo:
		arc_abs(para1*m_Scale,para2*m_Scale,para3);
		break;
	case SArc3DTo:
		arc_abs_3d(para1*m_Scale,para2*m_Scale, para3*m_Scale/16, para4);
		break;
	case SArcRelTo:
		arc_rel(para1*m_Scale,para2*m_Scale,para3);
		break;
	case SArc3DRelTo:
		arc_rel_3d(para1*m_Scale,para2*m_Scale,para3*m_Scale, para4);
		break;
	case SZPosition:
		jump_rel_3d(0,0, para1*m_Scale/16);
		break;
	case SSetPixelLine:  //occupied 2 entries for RTC4
		set_pixel_line(para1, para2*64.0, para3*m_Scale, para4*m_Scale);		
		break;
	case SSetPixel:
		set_pixel(para1*64.0, para2/10.0*4096);
		break;
	case SSetNPixel:
		set_n_pixel(para1*64.0, para2/10.0*4096, para3);
		break;		
	case SAnologOut1:
		//	write_da_1(para1/10*4096); //us
		para1=para1>=5?5:para1;
		para1=para1<0?0:para1;
		write_da_1_list(int(para1/10.0*4096));
		m_GalvoPara.m_dPower=para1;
		break;
	case SLaserOnList:
		laser_on_list(int(para1/10.0)); //us
		break; 
	case SLongDelay:
		long_delay(para1/10.0);	//us
		break;
	case SMicroVector:
		micro_vector_abs(para1*m_Scale,para2*m_Scale, para3/0.5, para4/0.5);
		break;
	case SMicroVector3D:
		micro_vector_abs_3d(para1*m_Scale,para2*m_Scale, 0, para3/0.5, para4/0.5);
		break;
	case SMicroVectorRel:
		micro_vector_rel(para1*m_Scale,para2*m_Scale, para3/0.5, para4/0.5);
		break;
	case SMicroVectorRel3D:
		micro_vector_rel_3d(para1*m_Scale,para2*m_Scale, 0, para3/0.5, para4/0.5);
		break;
	case SSetAutoLaserPara:
		set_auto_laser_params_list((int)para1, para2, para3, para4);
		m_GalvoPara.m_iDependCtrl=(int)para1;
		break;	
	case SSetAutoVectorCtrl:
		m_GalvoPara.m_dVectorDependValue=para2;
		switch((int)para1)
		{
		case 1:
		case 2:
			para2=(para2/10.0*4096)>=5?5:(para2/10.0*4096);
			break;
		case 3:
			para2=(para2/10.0*4096)>=5?5:(para2/10.0*4096);
			break;
		case 4:
			para2=para2*64.0;
		case 5:
			para2=1.0/para2*1000000*64/2;
			break;
		case 6:
			para2=(para2/10.0*4096)>=5?5:(para2/10.0*4096);
			break;
		case 7:
			para2=para2*m_Scale/16.0;
			break;
		default:
			break;
		}
		m_GalvoPara.m_iVectorDependCtrl=(int)para1;
		set_vector_control((int)para1, (int)para2);		
		break;
		case SSetSkyWritingMode:
			set_sky_writing_mode_list(m_GalvoPara.m_iSkywritingMode);
			break;
		case SSetSkyWritingPara:
			set_sky_writing_para_list(m_GalvoPara.m_dSkywritingTimeleg,2*m_GalvoPara.m_dSkywritingLaserOnShift,
				m_GalvoPara.m_dSkywritingNprev/10,m_GalvoPara.m_dSkywritingNpost/10);
			break;
		case SListContinue:
			list_continue();
			break;
		case SSetFirstKiller:
			set_firstpulse_killer_list(int(para1*64));
			break;
		default:
			break;
			
	}
	
}
*/

UINT RTC6::SetAutoLaserControl(const UINT Ctrl, const UINT Value, const UINT Mode, const UINT MinValue, const UINT MaxValue)
{
	UINT ErrorCode=0;
	switch(Ctrl)
	{
	case 1:
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


void RTC6:: SSetPixelLine(int ichanel, double dperiod, double dx, double dy, double dz)
{
	WaitForListSpace(1);
	set_pixel_line_3d(ichanel, dperiod*32, dx*m_Scale, dy*m_Scale, dz*m_Scale);	

	iBmpChanel=ichanel;
	dBmpPeriod=dperiod;
	dBmpx=dx;
	dBmpy=dy;
	dBmpz=dz;
}

void RTC6:: SSetPixel(double dpulsewidth, double dvoltage, int npixel)
{
	WaitForListSpace(2);
	if(get_input_pointer()==0)
		set_pixel_line_3d(iBmpChanel, dBmpPeriod*32, dBmpx*m_Scale, dBmpy*m_Scale, dBmpz*m_Scale);	
	
	switch(iBmpChanel)
	{
	case 17:
	case 529:
		set_n_pixel(dpulsewidth*4096/10, dvoltage*4096/10, npixel);
		break;
	case 21:
	case 533:
		set_n_pixel(dpulsewidth*64, dvoltage*64, npixel);
		break;
	}
}

void RTC6:: SMark3DTo(double dx, double dy, double dz)
{
	WaitForListSpace(1);
	mark_abs_3d(dx*m_Scale,dy*m_Scale, dz*m_Scale);
}

void RTC6:: SJump3DTo(double dx, double dy, double dz)
{
	bWaiterCanSet=true;
	WaitForListSpace(1);
	jump_abs_3d(dx*m_Scale,dy*m_Scale, dz*m_Scale);
}

void RTC6:: SMark3DRelTo(double dx, double dy, double dz)
{
	WaitForListSpace(1);
	mark_rel_3d(dx*m_Scale,dy*m_Scale, dz*m_Scale);
}

void RTC6:: SJump3DRelTo(double dx, double dy, double dz)
{
	bWaiterCanSet=true;
	WaitForListSpace(1);
	jump_rel_3d(dx*m_Scale,dy*m_Scale, dz*m_Scale);
}

void RTC6:: SArc3DRelTo(double dx, double dy, double dz, double dangle)
{
	if(dangle>3600 || dangle<-3600)
	{
		if(dangle>3600)
		{
			WaitForListSpace(1);
			arc_rel_3d(dx*m_Scale,dy*m_Scale, dz*m_Scale, 3600);
			dangle-=3600;
		}
		else if(dangle<-3600)
		{
			WaitForListSpace(1);
			arc_rel_3d(dx*m_Scale,dy*m_Scale, dz*m_Scale, -3600);
			dangle+=3600;
		}
		
		SArc3DRelTo(dx, dy, dz, dangle);
	}
	else
	{
		WaitForListSpace(1);
		arc_rel_3d(dx*m_Scale,dy*m_Scale, dz*m_Scale, dangle);
	}
}

void RTC6:: SArc3DTo(double dx, double dy, double dz, double dangle)
{
	if(dangle>3600 || dangle<-3600)
	{
		if(dangle>3600)
		{
			WaitForListSpace(1);
			arc_abs_3d(dx*m_Scale,dy*m_Scale, dz*m_Scale, 3600);
			dangle-=3600;
		}
		else if(dangle<-3600)
		{
			WaitForListSpace(1);
			arc_abs_3d(dx*m_Scale,dy*m_Scale, dz*m_Scale, -3600);
			dangle+=3600;
		}
		
		SArc3DTo(dx, dy, dz, dangle);
	}
	else
	{
		WaitForListSpace(1);
		arc_abs_3d(dx*m_Scale,dy*m_Scale, dz*m_Scale, dangle);
	}
}

//Bitmap
void RTC6:: SSetZPosition(double dz)
{
	WaitForListSpace(1);
	jump_rel_3d(0,0, dz*m_Scale);
}

void RTC6:: SParaMark3DTo(double dx, double dy, double dz, double dpara)
{
	WaitForListSpace(1);	
	para_mark_abs_3d(dx*m_Scale,dy*m_Scale,dz*m_Scale, dpara);
}

void RTC6:: SParaJump3DTo(double dx, double dy, double dz, double dpara)
{
	bWaiterCanSet=true;
	WaitForListSpace(1);
	para_jump_abs_3d(dx*m_Scale,dy*m_Scale,dz*m_Scale, dpara);
}

void RTC6:: SPoint(double dx, double dy, double dz, double dtime)
{
	WaitForListSpace(1);
	jump_abs_3d(dx*m_Scale, dy*m_Scale,dz*m_Scale);
	laser_on_list(dtime/10);
}
///	
void RTC6:: SMicroVector3D(double dx, double dy, double dz, double laseron, double laseroff)
{
	WaitForListSpace(1)	;
	micro_vector_abs_3d(dx*m_Scale, dy*m_Scale, dz*m_Scale, laseron/0.5, laseroff/0.5);
}

void RTC6:: SMicroVectorRel3D(double dx, double dy, double dz, double laseron, double laseroff)
{
	WaitForListSpace(1);	
	micro_vector_rel_3d(dx*m_Scale, dy*m_Scale, dz*m_Scale, laseron/0.5, laseroff/0.5);
}

void RTC6:: SetLaserDelays(double dlaserondelay, double dlaseroffdelay)
{
	WaitForListSpace(1);
	set_laser_delays(dlaserondelay*64, dlaseroffdelay*64);
	
	m_GalvoPara.m_dLaserOnDelay= dlaserondelay;
	m_GalvoPara.m_dLaserOffDelay= dlaseroffdelay;
}		//laser on and off delays
