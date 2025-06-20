// summary:	Declares the functions class
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the KCUBEPIEZO_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// KCUBEPIEZO_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef KCUBEPIEZODLL_EXPORTS
#define KCUBEPIEZO_API __declspec(dllexport)
#else
#define KCUBEPIEZO_API __declspec(dllimport)
#endif

#include <OaIdl.h>

#pragma once

/** @defgroup KCubePiezo KCube Piezo
 *  This section details the Structures and Functions relavent to the  @ref KPZ101_page "KCube Piezo"<br />
 *  For an example of how to connect to the device and perform simple operations use the following links:
 *  <list type=bullet>
 *    <item> \ref namespaces_tpz_ex_1 "Example of using the Thorlabs.MotionControl.KCube.Piezo.DLL from a C or C++ project."<br />
 *									  This requires the DLL to be dynamical linked. </item>
 *    <item> \ref namespaces_tpz_ex_2 "Example of using the Thorlabs.MotionControl.KCube.Piezo.DLL from a C# project"<br />
 *									  This uses Marshalling to load and access the C DLL. </item>
 *  </list>
 *  The Thorlabs.MotionControl.KCube.Piezo.DLL requires the following DLLs
 *  <list type=bullet>
 *    <item> Thorlabs.MotionControl.DeviceManager. </item>
 *  </list>
 *  @{
 */
extern "C"
{
/// \cond NOT_MASTER
	
	/// <summary> Values that represent FT_Status. </summary>
	typedef enum FT_Status : short
	{
		FT_OK = 0x00, /// <OK - no error.
		FT_InvalidHandle = 0x01, ///<Invalid handle.
		FT_DeviceNotFound = 0x02, ///<Device not found.
		FT_DeviceNotOpened = 0x03, ///<Device not opened.
		FT_IOError = 0x04, ///<I/O error.
		FT_InsufficientResources = 0x05, ///<Insufficient resources.
		FT_InvalidParameter = 0x06, ///<Invalid parameter.
		FT_DeviceNotPresent = 0x07, ///<Device not present.
		FT_IncorrectDevice = 0x08 ///<Incorrect device.
	 } FT_Status;

	/// <summary> Values that represent THORLABSDEVICE_API. </summary>
	typedef enum MOT_MotorTypes
	{
		MOT_NotMotor = 0,
		MOT_DCMotor = 1,
		MOT_StepperMotor = 2,
		MOT_BrushlessMotor = 3,
		MOT_CustomMotor = 100,
	} MOT_MotorTypes;

	/// <summary> Values that represent Joystick Direction Sense. </summary>
	typedef enum KPZ_WheelDirectionSense : __int16
	{
		/// <summary> An enum constant representing the kmot js positive option. </summary>
		KPZ_WM_Positive = 0x01,
		/// <summary> An enum constant representing the kmot js negative option. </summary>
		KPZ_WM_Negative = 0x02,
	} KPZ_WheelDirectionSense;

	/// <summary> Values that represent Joystick Mode. </summary>
	typedef enum KPZ_WheelMode : __int16
	{
		/// <summary> An enum constant representing the kmot js voltage option. </summary>
		KPZ_WM_MoveAtVoltage = 0x01,
		/// <summary> An enum constant representing the kmot js jog option. </summary>
		KPZ_WM_JogVoltage = 0x02,
		/// <summary> An enum constant representing the kmot js move absolute option. </summary>
		KPZ_WM_SetVoltage = 0x03,
	} KPZ_WheelMode;

	/// <summary> Values that represent KPZ_WheelChangeRate. </summary>
	typedef enum KPZ_WheelChangeRate : __int16
	{
		/// <summary> An enum constant representing the kmot js high option. </summary>
		KPZ_WM_High = 0x01,
		/// <summary> An enum constant representing the kmot js medium option. </summary>
		KPZ_WM_Medium = 0x02,
		/// <summary> An enum constant representing the kmot js low option. </summary>
		KPZ_WM_Low = 0x03,
	} KPZ_WheelChangeRate;

	/// <summary> Values that represent Trigger Port Mode. </summary>
	typedef enum KPZ_TriggerPortMode : __int16
	{
		KPZ_TrigDisabled = 0x00,///< Trigger Disabled
		KPZ_TrigIn_GPI = 0x01,///< General purpose logic input (<see cref="PCC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)
		KPZ_TrigIn_VoltageStepUp = 0x02,///< Move relative using relative move parameters
		KPZ_TrigIn_VoltageStepDown = 0x03,///< Move absolute using absolute move parameters
		KPZ_TrigOut_GPO = 0x0A,///< General purpose output (<see cref="PCC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)
	} KPZ_TriggerPortMode;

	/// <summary> Values that represent Trigger Port Polarity. </summary>
	typedef enum KPZ_TriggerPortPolarity : __int16
	{
		KPZ_TrigPolarityHigh = 0x01,///< Trigger Polarity high
		KPZ_TrigPolarityLow = 0x02,///< Trigger Polarity Low
	} KPZ_TriggerPortPolarity;
/// \endcond

	/// <summary> Information about the device generated from serial number. </summary>
	#pragma pack(1)
	typedef struct TLI_DeviceInfo
	{
		/// <summary> The device Type ID, see \ref C_DEVICEID_page "Device serial numbers". </summary>
		DWORD typeID;
		/// <summary> The device description. </summary>
		char description[65];
		/// <summary> The device serial number. </summary>
		char serialNo[16];
		/// <summary> The USB PID number. </summary>
		DWORD PID;

		/// <summary> <c>true</c> if this object is a type known to the Motion Control software. </summary>
		bool isKnownType;
		/// <summary> The motor type (if a motor).
		/// 		  <list type=table>
		///				<item><term>MOT_NotMotor</term><term>0</term></item>
		///				<item><term>MOT_DCMotor</term><term>1</term></item>
		///				<item><term>MOT_StepperMotor</term><term>2</term></item>
		///				<item><term>MOT_BrushlessMotor</term><term>3</term></item>
		///				<item><term>MOT_CustomMotor</term><term>100</term></item>
		/// 		  </list> </summary>
		MOT_MotorTypes motorType;

		/// <summary> <c>true</c> if the device is a piezo device. </summary>
		bool isPiezoDevice;
		/// <summary> <c>true</c> if the device is a laser. </summary>
		bool isLaser;
		/// <summary> <c>true</c> if the device is a custom type. </summary>
		bool isCustomType;
		/// <summary> <c>true</c> if the device is a rack. </summary>
		bool isRack;
		/// <summary> Defines the number of channels available in this device. </summary>
		short maxChannels;
	} TLI_DeviceInfo;

	/// <summary> Structure containing the Hardware Information. </summary>
	/// <value> Hardware Information retrieved from tthe device. </value>
	typedef struct TLI_HardwareInformation
	{
		/// <summary> The device serial number. </summary>
		/// <remarks> The device serial number is a serial number,<br />starting with 2 digits representing the device type<br /> and a 6 digit unique value.</remarks>
		DWORD serialNumber;
		/// <summary> The device model number. </summary>
		/// <remarks> The model number uniquely identifies the device type as a string. </remarks>
		char modelNumber[8];
		/// <summary> The type. </summary>
		/// <remarks> Do not use this value to identify a particular device type. Please use <see cref="TLI_DeviceInfo"/> typeID for this purpose.</remarks>
		WORD type;
		/// <summary> The device firmware version. </summary>
		DWORD firmwareVersion;
		/// <summary> The device notes read from the device. </summary>
		char notes[48];
		/// <summary> The device dependant data. </summary>
		BYTE deviceDependantData[12];
		/// <summary> The device hardware version. </summary>
		WORD hardwareVersion;
		/// <summary> The device modification state. </summary>
		WORD modificationState;
		/// <summary> The number of channels the device provides. </summary>
		short numChannels;
	} TLI_HardwareInformation;

/// \cond NOT_MASTER

	/// <summary> The Piezo Control Modes. </summary>
	/// \ingroup Common
	typedef enum PZ_ControlModeTypes : short
	{
		PZ_ControlModeUndefined = 0, ///<Undefined
		PZ_OpenLoop = 1, ///<Open Loop mode.
		PZ_CloseLoop = 2, ///<Closed Loop mode.
		PZ_OpenLoopSmooth = 3, ///<Open Loop mode with smoothing.
		PZ_CloseLoopSmooth = 4 ///<Closed Loop mode with smoothing.
	} PZ_ControlModeTypes;

	/// <summary> The Piezo Input Source Flags. </summary>
	/// \ingroup Common
	typedef enum PZ_InputSourceFlags : short
	{
		PZ_SoftwareOnly = 0, ///<Only read input from software.
		PZ_ExternalSignal = 0x01, ///<Read input from software and External Signal.
		PZ_Potentiometer = 0x02, ///<Read input from software and Potentiometer.
		PZ_All = PZ_ExternalSignal | PZ_Potentiometer ///<Read input from all sources.
	} PZ_InputSourceFlags;

	/// <summary>The Piezo Output LUT Operating Flags. </summary>
	/// \ingroup Common
	typedef enum PZ_OutputLUTModes : short
	{
		PZ_Continuous = 0x01, ///<LUT waveform output continuously.
		PZ_Fixed = 0x02, ///<LUT waveform output for a Fixed number of cycles.
		PZ_OutputTrigEnable = 0x04, ///<Enable Output Triggering.
		PZ_InputTrigEnable = 0x08, ///<Enable Input triggering.
		PZ_OutputTrigSenseHigh = 0x10, ///<Output trigger sense is high.
		PZ_InputTrigSenseHigh = 0x20, ///<Input trigger sense is high.
		PZ_OutputGated = 0x40, ///<Output is gated.
		PZ_OutputTrigRepeat = 0x80, ///<Output trigger repeats.
	} PZ_OutputLUTModes;

	/// <summary> The Hub Analogue Modes. </summary>
	/// \ingroup Common
	typedef enum HubAnalogueModes : short
	{
		AnalogueCh1 = 1, ///<Analogue input applied to all Hub bays.
		AnalogueCh2 = 2, ///<Analogue input applied to adjacent Hub bays, i.e. (1-2,3-4,5-6). 
		ExtSignalSMA = 3 ///<Analogue input is from external SMA.
	} HubAnalogueModes;

	/// <summary> Structure describing the Hub Analog Input and Voltage Limit Modes (MGMSG_PZ_GET_TPZ_IOSETTINGS command). </summary>
	struct TPZ_IOSettings
	{
		HubAnalogueModes _hubAnalogueInput;
		short _maximumOutputVoltage;
	};

/// \endcond

	/// <summary> Structure containing feedback loop constants. </summary>
	typedef struct PZ_FeedbackLoopConstants
	{
		/// <summary> The proportional term. </summary>
		short proportionalTerm;
		/// <summary> The integral term. </summary>
		short integralTerm;
	} PZ_FeedbackLoopConstants;

	/// <summary> Structure containing LUT output wave parameters. </summary>
	typedef struct PZ_LUTWaveParameters
	{
		/// <summary> Specifies the LUT (waveform) output mode (continuous or fixed) </summary>
		PZ_OutputLUTModes mode;
		/// <summary> Specifies the number of LUT values to output for a single waveform cycle (0 to 7999) </summary>
		short cycleLength;
		/// <summary> Specifies the number of waveform cycles to output. </summary>
		unsigned int numCycles;
		/// <summary> Specifies the delay in milliseconds that the system waits after setting each LUT
		/// output value. </summary>
		unsigned int LUTValueDelay;
		/// <summary> The delay time before the system clocks out the LUT values. </summary>
		unsigned int preCycleDelay;
		/// <summary> The delay time after the system clocks out the LUT values. </summary>
		unsigned int postCycleDelay;
		/// <summary> Zero-based index at which the output trigger is fired.<br />
		/// 		  Requires Triggering is enabled. </summary>
		short outTriggerStart;
		/// <summary> Duration of the output trigger in milliseconds.<br />
		/// 		  Requires Triggering is enabled. </summary>
		unsigned int outTriggerDuration;
		/// <summary> The output trigger repeat interval.<br />
		/// 		  Requires Repeat Triggering is enabled </summary>
		short numOutTriggerRepeat;
	} PZ_LUTWaveParameters;

	/// <summary> Structure containing the MMI Parameters. </summary>
	/// <value> Device GUI parameters. </value>
	typedef struct KPZ_MMIParams
	{
		/// <summary> The wheel mode. </summary>
		/// <remarks> The wheel mode is one of the following:
		/// 		  <list type=table>
		///				<item><term>1</term><term>Constant Voltage Adjust<br />The device will continue adjusting until the limits are reached or the duration of the wheel action</term></item>
		///				<item><term>2</term><term>Jog<br />The device will jog forward or backward according to the wheel action.<br />
		///					  The device will jog according to the Voltage Step</term></item>
		///				<item><term>3</term><term>Move Absolute<br />The device will move to either Preset Po 1 or 2 according to the wheel action.</term></item>
		/// 		  </list>
		/// 		  </remarks>
		KPZ_WheelMode JoystickMode;
		/// <summary> The voltage adjust rate. </summary>
		KPZ_WheelChangeRate VoltageAdjustRate; 
		/// <summary> The wheel jog step size. </summary>
		__int32 VoltageStep; 
		/// <summary> The wheel direction sense. </summary>
		KPZ_WheelDirectionSense JoystickDirectionSense;
		/// <summary> The first preset position in encoder counts. </summary>
		__int32 PresetPos1; 
		/// <summary> The second preset position in encoder counts. </summary>
		__int32 PresetPos2; 
		/// <summary> The display intensity, range 0 to 100%. </summary>
		__int16 DisplayIntensity;
		/// <summary> The display timeout in miniutes. </summary>
		__int16 DisplayTimeout;
		/// <summary> The display dim intensity, range 0 to (Display Timeout). </summary>
		__int16 DisplayDimIntensity;
		/// <summary> Reserved fields. </summary>
		__int16 reserved[4];
	} KPZ_MMIParams;

	/// <summary> KCube motor trigger configuration. </summary>
	typedef struct KPZ_TriggerConfig
	{
		/// <summary> The trigger 1 mode. </summary>
		/// <remarks> The trigger 1 operating mode:
		/// 		  <list type=table>
		///				<item><term>0</term><term>Trigger disabled</term></item>
		///				<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="PCC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
		///				<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
		///				<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
		///				<item><term>10</term><term>Trigger Output - General purpose output (<see cref="PCC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
		/// 		  </list>
		/// 		  </remarks>
		KPZ_TriggerPortMode Trigger1Mode;
		/// <summary> The trigger 1 polarity. </summary>
		/// <remarks> The trigger 1 output polaritye:
		/// 		  <list type=table>
		///				<item><term>1</term><term>Output high when set</term></item>
		///				<item><term>2</term><term>Output low when set</term></item>
		/// 		  </list>
		/// 		  </remarks>
		KPZ_TriggerPortPolarity Trigger1Polarity;
		/// <summary> The trigger 2 mode. </summary>
		/// <remarks> The trigger 2 operating mode:
		/// 		  <list type=table>
		///				<item><term>0</term><term>Trigger disabled</term></item>
		///				<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="PCC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
		///				<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
		///				<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
		///				<item><term>10</term><term>Trigger Output - General purpose output (<see cref="PCC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
		/// 		  </list>
		/// 		  </remarks>
		KPZ_TriggerPortMode Trigger2Mode;
		/// <summary> The trigger 2 polarity. </summary>
		/// <remarks> The trigger 2 output polarity:
		/// 		  <list type=table>
		///				<item><term>1</term><term>Output high when set</term></item>
		///				<item><term>2</term><term>Output low when set</term></item>
		/// 		  </list>
		/// 		  </remarks>
		KPZ_TriggerPortPolarity Trigger2Polarity;
		/// <summary> reserved fields. </summary>
		__int16 reserved[6];
	} KPZ_TriggerConfig;
	#pragma pack()

    /// <summary> Build the DeviceList. </summary>
    /// <remarks> This function builds an internal collection of all devices found on the USB that are not currently open. <br />
    /// 		  NOTE, if a device is open, it will not appear in the list until the device has been closed. </remarks>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_identification.cpp
	/// <seealso cref="TLI_GetDeviceListSize()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	/// <seealso cref="TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID)" />
	/// <seealso cref="TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length)" />
	/// <seealso cref="TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer)" />
	/// <seealso cref="TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID)" />
	/// <seealso cref="TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length)" />
	KCUBEPIEZO_API short __cdecl TLI_BuildDeviceList(void);

	/// <summary> Gets the device list size. </summary>
	/// 		  \include CodeSnippet_identification.cpp
	/// <returns> Number of devices in device list. </returns>
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	/// <seealso cref="TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID)" />
	/// <seealso cref="TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length)" />
	/// <seealso cref="TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer)" />
	/// <seealso cref="TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID)" />
	/// <seealso cref="TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length)" />
	KCUBEPIEZO_API short __cdecl TLI_GetDeviceListSize();

	/// <summary> Get the entire contents of the device list. </summary>
	/// <param name="stringsReceiver"> Outputs a SAFEARRAY of strings holding device serial numbers. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_identification.cpp
	/// <seealso cref="TLI_GetDeviceListSize()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID)" />
	/// <seealso cref="TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length)" />
	/// <seealso cref="TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer)" />
	/// <seealso cref="TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID)" />
	/// <seealso cref="TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length)" />
	KCUBEPIEZO_API short __cdecl TLI_GetDeviceList(SAFEARRAY** stringsReceiver);

	/// <summary> Get the contents of the device list which match the supplied typeID. </summary>
	/// <param name="stringsReceiver"> Outputs a SAFEARRAY of strings holding device serial numbers. </param>
	/// <param name="typeID">The typeID of devices to match, see \ref C_DEVICEID_page "Device serial numbers". </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_identification.cpp
	/// <seealso cref="TLI_GetDeviceListSize()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	/// <seealso cref="TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length)" />
	/// <seealso cref="TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer)" />
	/// <seealso cref="TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID)" />
	/// <seealso cref="TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length)" />
	KCUBEPIEZO_API short __cdecl TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID);

	/// <summary> Get the contents of the device list which match the supplied typeIDs. </summary>
	/// <param name="stringsReceiver"> Outputs a SAFEARRAY of strings holding device serial numbers. </param>
	/// <param name="typeIDs"> list of typeIDs of devices to be matched, see \ref C_DEVICEID_page "Device serial numbers"</param>
	/// <param name="length"> length of type list</param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_identification.cpp
	/// <seealso cref="TLI_GetDeviceListSize()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	/// <seealso cref="TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID)" />
	/// <seealso cref="TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer)" />
	/// <seealso cref="TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID)" />
	/// <seealso cref="TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length)" />
	KCUBEPIEZO_API short __cdecl TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length);

	/// <summary> Get the entire contents of the device list. </summary>
	/// <param name="receiveBuffer"> a buffer in which to receive the list as a comma separated string. </param>
	/// <param name="sizeOfBuffer">	The size of the output string buffer. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_identification.cpp
	/// <seealso cref="TLI_GetDeviceListSize()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	/// <seealso cref="TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID)" />
	/// <seealso cref="TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length)" />
	/// <seealso cref="TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID)" />
	/// <seealso cref="TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length)" />
	KCUBEPIEZO_API short __cdecl TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer);

	/// <summary> Get the contents of the device list which match the supplied typeID. </summary>
	/// <param name="receiveBuffer"> a buffer in which to receive the list as a comma separated string. </param>
	/// <param name="sizeOfBuffer">	The size of the output string buffer. </param>
	/// <param name="typeID"> The typeID of devices to be matched, see \ref C_DEVICEID_page "Device serial numbers"</param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_identification.cpp
	/// <seealso cref="TLI_GetDeviceListSize()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	/// <seealso cref="TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID)" />
	/// <seealso cref="TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length)" />
	/// <seealso cref="TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer)" />
	/// <seealso cref="TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length)" />
	KCUBEPIEZO_API short __cdecl TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID);

	/// <summary> Get the contents of the device list which match the supplied typeIDs. </summary>
	/// <param name="receiveBuffer"> a buffer in which to receive the list as a comma separated string. </param>
	/// <param name="sizeOfBuffer">	The size of the output string buffer. </param>
	/// <param name="typeIDs"> list of typeIDs of devices to be matched, see \ref C_DEVICEID_page "Device serial numbers"</param>
	/// <param name="length"> length of type list</param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_identification.cpp
	/// <seealso cref="TLI_GetDeviceListSize()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	/// <seealso cref="TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID)" />
	/// <seealso cref="TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length)" />
	/// <seealso cref="TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer)" />
	/// <seealso cref="TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID)" />
	KCUBEPIEZO_API short __cdecl TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length);

	/// <summary> Get the device information from the USB port. </summary>
	/// <remarks> The Device Info is read from the USB port not from the device itself.<remarks>
	/// <param name="serialNo"> The serial number of the device. </param>
	/// <param name="info">    The <see cref="TLI_DeviceInfo"/> device information. </param>
	/// <returns> 1 if successful, 0 if not. </returns>
    /// 		  \include CodeSnippet_identification.cpp
	/// <seealso cref="TLI_GetDeviceListSize()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	/// <seealso cref="TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID)" />
	/// <seealso cref="TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length)" />
	/// <seealso cref="TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer)" />
	/// <seealso cref="TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID)" />
	/// <seealso cref="TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length)" />
	KCUBEPIEZO_API short __cdecl TLI_GetDeviceInfo(char const * serialNo, TLI_DeviceInfo *info);

	/// <summary> Initialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <remarks> Call TLI_InitializeSimulations before TLI_BuildDeviceList at the start of the program to make a connection to the simulation manager.<Br />
	/// 		  Any devices configured in the simulation manager will become visible TLI_BuildDeviceList is called and can be accessed using TLI_GetDeviceList.<Br />
	/// 		  Call TLI_InitializeSimulations at the end of the program to release the simulator.  </remarks>
	/// <seealso cref="TLI_UninitializeSimulations()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	KCUBEPIEZO_API void __cdecl TLI_InitializeSimulations();

	/// <summary> Uninitialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <seealso cref="TLI_InitializeSimulations()" />
	KCUBEPIEZO_API void __cdecl TLI_UninitializeSimulations();

	/// <summary> Open the device for communications. </summary>
	/// <param name="serialNo">	The serial no of the device to be connected. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="PCC_Close(char const * serialNo)" />
	KCUBEPIEZO_API short __cdecl PCC_Open(char const * serialNo);

	/// <summary> Disconnect and close the device. </summary>
	/// <param name="serialNo">	The serial no of the device to be disconnected. </param>
    /// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="PCC_Open(char const * serialNo)" />
	KCUBEPIEZO_API void __cdecl PCC_Close(char const * serialNo);

	/// <summary>	Check connection. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> true if the USB is listed by the ftdi controller</returns>
	/// \include CodeSnippet_CheckConnection.cpp
	KCUBEPIEZO_API bool __cdecl PCC_CheckConnection(char const * serialNo);

	/// <summary> Tells the device that it is being disconnected. </summary>
	/// <remarks> This does not disconnect the communications.<br />
	/// 		  To disconnect the communications, call the <see cref="PCC_Close(char const * serialNo)" /> function. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	KCUBEPIEZO_API short __cdecl PCC_Disconnect(char const * serialNo);

	/// <summary> Sends a command to the device to make it identify iteself. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	KCUBEPIEZO_API void __cdecl PCC_Identify(char const * serialNo);

	/// <summary> Gets the hardware information from the device. </summary>
	/// <param name="serialNo">		    The device serial no. </param>
	/// <param name="modelNo">		    Address of a buffer to receive the model number string. Minimum 8 characters </param>
	/// <param name="sizeOfModelNo">	    The size of the model number buffer, minimum of 8 characters. </param>
	/// <param name="type">		    Address of a WORD to receive the hardware type number. </param>
	/// <param name="numChannels">	    Address of a short to receive the  number of channels. </param>
	/// <param name="notes">		    Address of a buffer to receive the notes describing the device. </param>
	/// <param name="sizeOfNotes">		    The size of the notes buffer, minimum of 48 characters. </param>
	/// <param name="firmwareVersion"> Address of a DWORD to receive the  firmware version number made up of 4 byte parts. </param>
	/// <param name="hardwareVersion"> Address of a WORD to receive the  hardware version number. </param>
	/// <param name="modificationState">	    Address of a WORD to receive the hardware modification state number. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	KCUBEPIEZO_API short __cdecl PCC_GetHardwareInfo(char const * serialNo, char * modelNo, DWORD sizeOfModelNo, WORD * type, WORD * numChannels, 
													 char * notes, DWORD sizeOfNotes, DWORD * firmwareVersion, WORD * hardwareVersion, WORD * modificationState);

	/// <summary> Gets the hardware information in a block. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="hardwareInfo"> Address of a TLI_HardwareInformation structure to receive the hardware information. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	KCUBEPIEZO_API short __cdecl PCC_GetHardwareInfoBlock(char const * serialNo, TLI_HardwareInformation *hardwareInfo);

	/// <summary> Gets version number of the device firmware. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device firmware version number made up of 4 byte parts. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	KCUBEPIEZO_API DWORD __cdecl PCC_GetFirmwareVersion(char const * serialNo);

	/// <summary> Gets version number of the device software. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device software version number made up of 4 byte parts. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	KCUBEPIEZO_API DWORD __cdecl PCC_GetSoftwareVersion(char const * serialNo);

	/// <summary> Update device with stored settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
    /// 		  \include CodeSnippet_connection1.cpp
	KCUBEPIEZO_API bool __cdecl PCC_LoadSettings(char const * serialNo);

	/// <summary> Update device with named settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="settingsName"> Name of settings stored away from device. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	///             \include CodeSnippet_connection1.cpp
	KCUBEPIEZO_API bool __cdecl PCC_LoadNamedSettings(char const * serialNo, char const *settingsName);

	/// <summary> persist the devices current settings. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	KCUBEPIEZO_API bool __cdecl PCC_PersistSettings(char const * serialNo);

	/// <summary> Disable the cube. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_Enable(char const * serialNo)" />
	KCUBEPIEZO_API short __cdecl PCC_Disable(char const * serialNo);

	/// <summary> Enable cube for computer control. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_Disable(char const * serialNo)" />
	KCUBEPIEZO_API short __cdecl PCC_Enable(char const * serialNo);

	/// <summary> Determine if the device front panel can be locked. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> True if we can lock the device front panel, false if not. </returns>
	/// <seealso cref="PCC_GetFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="PCC_RequestFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="PCC_SetFrontPanelLock(char const * serialNo, bool locked)" />
	KCUBEPIEZO_API bool __cdecl PCC_CanDeviceLockFrontPanel(char const * serialNo);

	/// <summary> Query if the device front panel locked. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> True if the device front panel is locked, false if not. </returns>
	/// <seealso cref="PCC_CanDeviceLockFrontPanel(char const * serialNo)" />
	/// <seealso cref="PCC_RequestFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="PCC_SetFrontPanelLock(char const * serialNo, bool locked)" />
	KCUBEPIEZO_API bool __cdecl  PCC_GetFrontPanelLocked(char const * serialNo);

	/// <summary> Ask the device if its front panel is locked. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_CanDeviceLockFrontPanel(char const * serialNo)" />
	/// <seealso cref="PCC_GetFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="PCC_SetFrontPanelLock(char const * serialNo, bool locked)" />
	KCUBEPIEZO_API short __cdecl  PCC_RequestFrontPanelLocked(char const * serialNo);

	/// <summary> Sets the device front panel lock state. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="locked"> True to lock the device, false to unlock. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_CanDeviceLockFrontPanel(char const * serialNo)" />
	/// <seealso cref="PCC_GetFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="PCC_RequestFrontPanelLocked(char const * serialNo)" />
	KCUBEPIEZO_API short __cdecl  PCC_SetFrontPanelLock(char const * serialNo, bool locked);

	/// <summary> Clears the device message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	KCUBEPIEZO_API void __cdecl PCC_ClearMessageQueue(char const * serialNo);

	/// <summary> Registers a callback on the message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="functionPointer"> A function pointer to be called whenever messages are received. </param>
	/// <seealso cref="PCC_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="PCC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="PCC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KCUBEPIEZO_API void __cdecl PCC_RegisterMessageCallback(char const * serialNo, void (* functionPointer)());

	/// <summary> Gets the MessageQueue size. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> number of messages in the queue. </returns>
	/// <seealso cref="PCC_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="PCC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="PCC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KCUBEPIEZO_API int __cdecl PCC_MessageQueueSize(char const * serialNo);

	/// <summary> Get the next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="PCC_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="PCC_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="PCC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KCUBEPIEZO_API bool __cdecl PCC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Wait for next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="PCC_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="PCC_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="PCC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KCUBEPIEZO_API bool __cdecl PCC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Requests that all settings are download from device. </summary>
	/// <remarks> This function requests that the device upload all it's settings to the DLL.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	KCUBEPIEZO_API short __cdecl PCC_RequestSettings(char const * serialNo);

	/// <summary> Requests the status and position from the device. </summary>
	/// <remarks> This needs to be called to get the device to send it's current status bits and position.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="PCC_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="PCC_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="PCC_RequestPosition(char const * serialNo)" />
	/// <seealso cref="PCC_GetStatusBits(char const * serialNo)" />
	/// <seealso cref="PCC_GetPosition(char const * serialNo)" />
	/// <seealso cref="PCC_StartPolling(char const * serialNo, int milliseconds)" />
	KCUBEPIEZO_API short __cdecl PCC_RequestStatus(char const * serialNo);

	/// <summary> Request the status bits which identify the current device state. </summary>
	/// <remarks> This needs to be called to get the device to send it's current status bits.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="PCC_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="PCC_GetStatusBits(char const * serialNo)" />
	/// <seealso cref="PCC_StartPolling(char const * serialNo, int milliseconds)" />
	KCUBEPIEZO_API short __cdecl PCC_RequestStatusBits(char const * serialNo);

	/// <summary>Get the current status bits. </summary>
	/// <remarks> This returns the latest status bits received from the device.<br />
	/// 		  To get new status bits, use <see cref="PCC_RequestStatusBits(char const * serialNo)" />
	///			  or use <see cref="PCC_RequestStatus(char const * serialNo)" />
	/// 		  or use the polling functions, <see cref="PCC_StartPolling(char const * serialNo, int milliseconds)" />.  </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	The status bits from the device <list type=table>
	///				<item><term>0x00000001</term><term>Piezo actuator connected (1=Connected, 0=Not connected).</term></item>
	///				<item><term>0x00000002</term><term>For Future Use.</term></item>
	///				<item><term>0x00000004</term><term>For Future Use.</term></item>
	///				<item><term>0x00000008</term><term>For Future Use.</term></item>
	///				<item><term>0x00000010</term><term>Piezo channel has been zeroed (1=Zeroed, 0=Not zeroed).</term></item>
	///				<item><term>0x00000020</term><term>Piezo channel is zeroing (1=Zeroing, 0=Not zeroing).</term></item>
	///				<item><term>0x00000040</term><term>For Future Use.</term></item>
	///				<item><term>0x00000080</term><term>For Future Use.</term></item>
	///				<item><term>0x00000100</term><term>Strain gauge feedback connected (1=Connected, 0=Not connected).</term></item>
	///				<item><term>0x00000200</term><term>For Future Use.</term></item>
	///				<item><term>0x00000400</term><term>Position control mode (1=Closed loop, 0=Open loop).</term></item>
	///				<item><term>0x00000800</term><term>For Future Use.</term></item>
	///				<item><term>0x00001000</term><term></term></item>
	///				<item><term>...</term><term></term></item>
	///				<item><term>0x00080000</term><term></term></item>
	///				<item><term>0x00100000</term><term>Digital input 1 state (1=Logic High, 0=Logic Low).</term></item>
	///				<item><term>0x00200000</term><term>Digital input 2 state (1=Logic High, 0=Logic Low).</term></item>
	///				<item><term>0x00400000</term><term>Digital input 3 state (1=Logic High, 0=Logic Low).</term></item>
	///				<item><term>0x00800000</term><term>Digital input 4 state (1=Logic High, 0=Logic Low).</term></item>
	///				<item><term>0x01000000</term><term>Digital input 5 state (1=Logic High, 0=Logic Low).</term></item>
	///				<item><term>0x02000000</term><term>Digital input 6 state (1=Logic High, 0=Logic Low).</term></item>
	///				<item><term>0x04000000</term><term>Digital input 7 state (1=Logic High, 0=Logic Low).</term></item>
	///				<item><term>0x08000000</term><term>Digital input 8 state (1=Logic High, 0=Logic Low).</term></item>
	///				<item><term>0x10000000</term><term>For Future Use.</term></item>
	///				<item><term>0x20000000</term><term>Active (1=Indicates Unit Is Active, 0=Not Active).</term></item>
	///				<item><term>0x40000000</term><term>For Future Use.</term></item>
	///				<item><term>0x80000000</term><term>Channel enabled (1=Enabled, 0=Disabled).</term></item>
	/// 		  </list> <remarks> Bits 21 to 28 (Digital Input States) are only applicable if the associated digital input is fitted to your controller - see the relevant handbook for more details. </remarks> </returns>
	/// <seealso cref="PCC_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="PCC_RequestStatus(char const * serialNo)" />
	/// <seealso cref="PCC_StartPolling(char const * serialNo, int milliseconds)" />
	KCUBEPIEZO_API DWORD __cdecl PCC_GetStatusBits(char const * serialNo);

	/// <summary>	Requests the position index. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_GetPosition(char const * serialNo)" />
	/// <seealso cref="PCC_SetPosition(char const * serialNo, WORD position)" />
	KCUBEPIEZO_API short __cdecl PCC_RequestActualPosition(char const * serialNo);

	/// <summary>	Requests the position index. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_RequestPosition(char const * serialNo)" />
	/// <seealso cref="PCC_GetPosition(char const * serialNo)" />
	/// <seealso cref="PCC_SetPosition(char const * serialNo, WORD position)" />
	/// <seealso cref="PCC_SetPositionToTolerance(char const * serialNo, WORD position, WORD tolerance)" />
	KCUBEPIEZO_API short __cdecl PCC_RequestActualPosition(char const * serialNo);

	/// <summary> Requests the current output voltage or position depending on current mode. </summary>
	/// <remarks> This needs to be called to get the device to send it's current position.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="PCC_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="PCC_RequestActualPosition(char const * serialNo)" />
	/// <seealso cref="PCC_GetPosition(char const * serialNo)" />
	/// <seealso cref="PCC_StartPolling(char const * serialNo, int milliseconds)" />
	KCUBEPIEZO_API short __cdecl PCC_RequestPosition(char const * serialNo);

	/// <summary> Starts the internal polling loop which continuously requests position and status. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="milliseconds">The milliseconds polling rate. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="PCC_StopPolling(char const * serialNo)" />
	/// <seealso cref="PCC_PollingDuration(char const * serialNo)" />
	/// <seealso cref="PCC_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="PCC_RequestPosition(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	KCUBEPIEZO_API bool __cdecl PCC_StartPolling(char const * serialNo, int milliseconds);

	/// <summary> Gets the polling loop duration. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The time between polls in milliseconds or 0 if polling is not active. </returns>
	/// <seealso cref="PCC_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="PCC_StopPolling(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	KCUBEPIEZO_API long __cdecl PCC_PollingDuration(char const * serialNo);

	/// <summary> Stops the internal polling loop. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <seealso cref="PCC_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="PCC_PollingDuration(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	KCUBEPIEZO_API void __cdecl PCC_StopPolling(char const * serialNo);

	/// <summary> Gets the time in milliseconds since tha last message was received from the device. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="lastUpdateTimeMS"> The time since the last message was received in milliseconds. </param>
	/// <returns> True if monitoring is enabled otherwize False. </returns>
	/// <seealso cref="PCC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// <seealso cref="PCC_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	KCUBEPIEZO_API bool __cdecl PCC_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS );

	/// <summary> Enables the last message monitoring timer. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="enable"> True to enable monitoring otherwise False to disable. </param>
	/// <param name="lastMsgTimeout"> The last message error timeout in ms. 0 to disable. </param>
	/// <seealso cref="PCC_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="PCC_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	KCUBEPIEZO_API void __cdecl PCC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout );

	/// <summary> Queries if the time since the last message has exceeded the lastMsgTimeout set by <see cref="PCC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )"/>. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> True if last message timer has elapsed, False if monitoring is not enabled or if time of last message received is less than lastMsgTimeout. </returns>
	/// <seealso cref="PCC_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="PCC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	KCUBEPIEZO_API bool __cdecl PCC_HasLastMsgTimerOverrun(char const * serialNo);


	/// <summary> Gets the Position Control Mode. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The control mode <list type=table>
	///				<item><term>Open Loop</term><term>1</term></item>
	///				<item><term>Closed Loop</term><term>2</term></item>
	///				<item><term>Open Loop smoothed</term><term>3</term></item>
	///				<item><term>Closed Loop smoothed</term><term>4</term></item>
	/// 		  </list> </returns>
	/// <seealso cref="PCC_RequestPositionControlMode(char const * serialNo)" />
	/// <seealso cref="PCC_SetPositionControlMode(char const * serialNo, PZ_ControlModeTypes mode)" />
	KCUBEPIEZO_API PZ_ControlModeTypes __cdecl PCC_GetPositionControlMode(char const * serialNo);

	/// <summary>	Request the Position Control Mode. </summary>
	/// <param name="serialNo">	The serial no. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="PCC_GetPositionControlMode(char const * serialNo)" />
	/// <seealso cref="PCC_SetPositionControlMode(char const * serialNo, PZ_ControlModeTypes mode)" />
	KCUBEPIEZO_API short __cdecl PCC_RequestPositionControlMode(char const * serialNo);

	/// <summary> Sets the Position Control Mode. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="mode"> The control mode <list type=table>
	///				<item><term>Open Loop</term><term>1</term></item>
	///				<item><term>Closed Loop</term><term>2</term></item>
	///				<item><term>Open Loop smoothed</term><term>3</term></item>
	///				<item><term>Closed Loop smoothed</term><term>4</term></item>
	/// 		  </list>. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_RequestPositionControlMode(char const * serialNo)" />
	/// <seealso cref="PCC_GetPositionControlMode(char const * serialNo)" />
	KCUBEPIEZO_API short __cdecl PCC_SetPositionControlMode(char const * serialNo, PZ_ControlModeTypes mode);

	// Voltage Functions
	
	/// <summary>	Set zero reference voltage. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	KCUBEPIEZO_API bool __cdecl PCC_SetZero(char const * serialNo);

	/// <summary> Gets the maximum output voltage. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The maximum output voltage, 750, 1000 or 1500 (75.0, 100.0, 150.0). </returns>
	/// <seealso cref="PCC_RequestMaxOutputVoltage(char const * serialNo)" />
	/// <seealso cref="PCC_SetMaxOutputVoltage(char const * serialNo, short maxVoltage)" />
	KCUBEPIEZO_API short __cdecl PCC_GetMaxOutputVoltage(char const * serialNo);

	/// <summary> Requests the maximum output voltage be read from the device. </summary>
	/// <param name="serialNo">	The device serial no. </param> <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="PCC_GetMaxOutputVoltage(char const * serialNo)" />
	/// <seealso cref="PCC_SetMaxOutputVoltage(char const * serialNo, short maxVoltage)" />
	KCUBEPIEZO_API bool __cdecl PCC_RequestMaxOutputVoltage(char const * serialNo);

	/// <summary> Sets the maximum output voltage. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="maxVoltage">	The maximum output voltage, 750, 1000 or 1500 (75.0, 100.0, 150.0). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_GetMaxOutputVoltage(char const * serialNo)" />
	/// <seealso cref="PCC_RequestMaxOutputVoltage(char const * serialNo)" />
	KCUBEPIEZO_API short __cdecl PCC_SetMaxOutputVoltage(char const * serialNo, short maxVoltage);

	/// <summary> Gets the set Output Voltage. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The voltage as a percentage of MaxOutputVoltage,<br />
	/// 		  range -32767 to 32767 equivalent to -100% to 100%. </returns>
	/// <seealso cref="PCC_RequestOutputVoltage(char const * serialNo)" />
	/// <seealso cref="PCC_SetOutputVoltage(char const * serialNo, short volts)" />
	/// <seealso cref="PCC_SetMaxOutputVoltage(char const * serialNo, short maxVoltage)" />
	/// <seealso cref="PCC_GetMaxOutputVoltage(char const * serialNo)" />
	KCUBEPIEZO_API short __cdecl PCC_GetOutputVoltage(char const * serialNo);

	/// <summary>	Requests output voltage. </summary>
	/// <param name="serialNo">	The deviceserial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_GetOutputVoltage(char const * serialNo)" />
	/// <seealso cref="PCC_SetOutputVoltage(char const * serialNo, short volts)" />
	KCUBEPIEZO_API short __cdecl PCC_RequestOutputVoltage(char const * serialNo);

	/// <summary> Sets the output voltage. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="volts"> The voltage as a percentage of MaxOutputVoltage,<br />
	/// 		  range -32767 to 32767 equivalent to -100% to 100%. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_RequestOutputVoltage(char const * serialNo)" />
	/// <seealso cref="PCC_GetOutputVoltage(char const * serialNo)" />
	/// <seealso cref="PCC_SetMaxOutputVoltage(char const * serialNo, short maxVoltage)" />
	/// <seealso cref="PCC_GetMaxOutputVoltage(char const * serialNo)" />
	KCUBEPIEZO_API short __cdecl PCC_SetOutputVoltage(char const * serialNo, short volts);

	/// <summary> Requests that the current input voltage source be read from the device. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="PCC_GetVoltageSource(char const * serialNo)" />
	/// <seealso cref="PCC_SetVoltageSource(char const * serialNo, PZ_InputSourceFlags source)" />
	KCUBEPIEZO_API bool __cdecl PCC_RequestVoltageSource(char const * serialNo);

	/// <summary> Gets the control voltage source. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The voltage source. <list type=table>
	///				<item><term>Software Only</term><term>0</term></item>
	///				<item><term>Software and External</term><term>1</term></item>
	///				<item><term>Software and Potentiometer</term><term>2</term></item>
	///				<item><term>Software, External and Potentiometer</term><term>3</term></item>
	/// 		  </list> </returns>
	/// <seealso cref="PCC_RequestVoltageSource(char const * serialNo)" />
	/// <seealso cref="PCC_SetVoltageSource(char const * serialNo, PZ_InputSourceFlags source)" />
	KCUBEPIEZO_API PZ_InputSourceFlags __cdecl PCC_GetVoltageSource(char const * serialNo);

	/// <summary> Sets the control voltage source. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="source"> The voltage source <list type=table>
	///				<item><term>Software Only</term><term>0</term></item>
	///				<item><term>Software and External</term><term>1</term></item>
	///				<item><term>Software and Potentiometer</term><term>2</term></item>
	///				<item><term>Software, External and Potentiometer</term><term>3</term></item>
	/// 		  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_RequestVoltageSource(char const * serialNo)" />
	/// <seealso cref="PCC_GetVoltageSource(char const * serialNo)" />
	KCUBEPIEZO_API short __cdecl PCC_SetVoltageSource(char const * serialNo, PZ_InputSourceFlags source);

	/// <summary> Gets the position when in closed loop mode. </summary>
	/// <remarks> The result is undefined if not in closed loop mode</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The position as a percentage of maximum travel,<br />
	/// 		  range 0 to 65535, equivalent to 0 to 100%. </returns>
	/// <seealso cref="PCC_RequestPosition(char const * serialNo)" />
	/// <seealso cref="PCC_RequestActualPosition(char const * serialNo)" />
	/// <seealso cref="PCC_SetPosition(char const * serialNo, WORD position)" />
	/// <seealso cref="PCC_SetPositionToTolerance(char const * serialNo, WORD position, WORD tolerance)" />
	/// <seealso cref="PCC_SetPositionControlMode(char const * serialNo, PZ_ControlModeTypes mode)" />
	/// <seealso cref="PCC_GetPositionControlMode(char const * serialNo)" />
	KCUBEPIEZO_API WORD __cdecl PCC_GetPosition(char const * serialNo);

	/// <summary> Sets the position when in closed loop mode. </summary>
	/// <remarks> The command is ignored if not in closed loop mode</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="position"> The position as a percentage of maximum travel,<br />
	/// 		  range 0 to 65535, equivalent to 0 to 100%. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_RequestPosition(char const * serialNo)" />
	/// <seealso cref="PCC_RequestActualPosition(char const * serialNo)" />
	/// <seealso cref="PCC_SetPositionToTolerance(char const * serialNo, WORD position, WORD tolerance)" />
	/// <seealso cref="PCC_GetPosition(char const * serialNo)" />
	/// <seealso cref="PCC_SetPositionControlMode(char const * serialNo, PZ_ControlModeTypes mode)" />
	/// <seealso cref="PCC_GetPositionControlMode(char const * serialNo)" />
	KCUBEPIEZO_API short __cdecl PCC_SetPosition(char const * serialNo, WORD position);

	/// <summary> Sets the position when in closed loop mode. </summary>
	/// <remarks> The command is ignored if not in closed loop mode</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="position"> The position as a percentage of maximum travel,<br />
	/// 		  range 0 to 65535, equivalent to 0 to 100%. </param>
	/// <param name="tolerance"> The tolerance in position as a percentage of maximum travel,<br />
	/// 		  range 0 to 65535, equivalent to 0 to 100%. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_RequestPosition(char const * serialNo)" />
	/// <seealso cref="PCC_RequestActualPosition(char const * serialNo)" />
	/// <seealso cref="PCC_SetPosition(char const * serialNo, WORD position)" />
	/// <seealso cref="PCC_GetPosition(char const * serialNo)" />
	/// <seealso cref="PCC_SetPositionControlMode(char const * serialNo, PZ_ControlModeTypes mode)" />
	/// <seealso cref="PCC_GetPositionControlMode(char const * serialNo)" />
	KCUBEPIEZO_API short __cdecl PCC_SetPositionToTolerance(char const * serialNo, WORD position, WORD tolerance);

	/// <summary> Requests that the feedback loop constants be read from the device. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="PCC_GetFeedbackLoopPIconsts(char const * serialNo, short * proportionalTerm, short * integralTerm)" />
	/// <seealso cref="PCC_SetFeedbackLoopPIconsts(char const * serialNo, short proportionalTerm, short integralTerm)" />
	/// <seealso cref="PCC_GetFeedbackLoopPIconstsBlock(const char * serialNo, PZ_FeedbackLoopConstants *proportionalAndIntegralConstants)" />
	/// <seealso cref="PCC_SetFeedbackLoopPIconstsBlock(const char * serialNo, PZ_FeedbackLoopConstants *proportionalAndIntegralConstants)" />
	KCUBEPIEZO_API bool __cdecl PCC_RequestFeedbackLoopPIconsts(char const * serialNo);

	/// <summary> Gets the feedback loop parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="proportionalTerm"> The address of the parameter to receive the proportional parameter. </param>
	/// <param name="integralTerm"> The address of the parameter to receive the integral parameter. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_SetFeedbackLoopPIconsts(char const * serialNo, short proportionalTerm, short integralTerm)" />
	/// <seealso cref="PCC_GetFeedbackLoopPIconstsBlock(const char * serialNo, PZ_FeedbackLoopConstants *proportionalAndIntegralConstants)" />
	/// <seealso cref="PCC_SetFeedbackLoopPIconstsBlock(const char * serialNo, PZ_FeedbackLoopConstants *proportionalAndIntegralConstants)" />
	KCUBEPIEZO_API short __cdecl PCC_GetFeedbackLoopPIconsts(char const * serialNo, short * proportionalTerm, short * integralTerm);

	/// <summary> Sets the feedback loop constants. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="proportionalTerm"> The  proportional parameter from 0 to 255. </param>
	/// <param name="integralTerm"> The  integral parameter from 0 to 255. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_GetFeedbackLoopPIconsts(char const * serialNo, short * proportionalTerm, short * integralTerm)" />
	/// <seealso cref="PCC_SetFeedbackLoopPIconsts(char const * serialNo, short proportionalTerm, short integralTerm)" />
	/// <seealso cref="PCC_SetFeedbackLoopPIconstsBlock(const char * serialNo, PZ_FeedbackLoopConstants *proportionalAndIntegralConstants)" />
	KCUBEPIEZO_API short __cdecl PCC_SetFeedbackLoopPIconsts(char const * serialNo, short proportionalTerm, short integralTerm);

	/// <summary> Gets the feedback loop constants in a block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="proportionalAndIntegralConstants"> The address of the PZ_FeedbackLoopConstants to receive the feedback loop constants. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_GetFeedbackLoopPIconsts(char const * serialNo, short * proportionalTerm, short * integralTerm)" />
	/// <seealso cref="PCC_SetFeedbackLoopPIconsts(char const * serialNo, short proportionalTerm, short integralTerm)" />
	/// <seealso cref="PCC_SetFeedbackLoopPIconstsBlock(const char * serialNo, PZ_FeedbackLoopConstants *proportionalAndIntegralConstants)" />
	KCUBEPIEZO_API short __cdecl PCC_GetFeedbackLoopPIconstsBlock(const char * serialNo, PZ_FeedbackLoopConstants *proportionalAndIntegralConstants);

	/// <summary> Sets the feedback loop constants in a block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="proportionalAndIntegralConstants"> The address of the PZ_FeedbackLoopConstants containing the new feedback loop constants. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_GetFeedbackLoopPIconsts(char const * serialNo, short * proportionalTerm, short * integralTerm)" />
	/// <seealso cref="PCC_SetFeedbackLoopPIconsts(char const * serialNo, short proportionalTerm, short integralTerm)" />
	/// <seealso cref="PCC_GetFeedbackLoopPIconstsBlock(const char * serialNo, PZ_FeedbackLoopConstants *proportionalAndIntegralConstants)" />
	KCUBEPIEZO_API short __cdecl PCC_SetFeedbackLoopPIconstsBlock(const char * serialNo, PZ_FeedbackLoopConstants *proportionalAndIntegralConstants);


	/// <summary> Sets the LUT output wave parameters. </summary>
	/// <remarks> NOTE, the get function has never been implemented in firmware, so new parameters need to be generated each time.</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="LUTwaveParams"> The address of the PZ_LUTWaveParameters containing the new LUT output wave parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	KCUBEPIEZO_API short __cdecl PCC_SetLUTwaveParams(const char * serialNo, PZ_LUTWaveParameters *LUTwaveParams);

	/// <summary> Sets a waveform sample. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="index"> The LUT waveform index where the value is to be set. </param>
	/// <param name="value"> The voltage or position as a percentage of full scale.<br />
	/// 					  range -32767 to 32767, equivalemnt to -100% to 100% of maximum voltage / position. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	KCUBEPIEZO_API short __cdecl PCC_SetLUTwaveSample(char const * serialNo, short index, WORD value);

	/// <summary> Starts the LUT waveform output. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully started. </returns>
	KCUBEPIEZO_API short __cdecl PCC_StartLUTwave(char const * serialNo);

	/// <summary> Stops the LUT waveform output. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	KCUBEPIEZO_API short __cdecl PCC_StopLUTwave(char const * serialNo);

	/// <summary> Requests that the LED brightness be read from the device. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	KCUBEPIEZO_API bool __cdecl PCC_RequestLEDBrightness(char const * serialNo);

	/// <summary> Gets the LED brightness. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> Intensity from 0 (off) to 255. </returns>
	KCUBEPIEZO_API short __cdecl PCC_GetLEDBrightness(char const * serialNo);

	/// <summary> Sets the LED brightness. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="brightness"> Intensity from 0 (off) to 255. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	KCUBEPIEZO_API short __cdecl PCC_SetLEDBrightness(char const * serialNo, short brightness);

	/// <summary> Requests that the IO settings are read from the device. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	KCUBEPIEZO_API bool __cdecl PCC_RequestIOSettings(char const * serialNo);

	/// <summary> Gets the IO settings. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	The settings as a TPZ_IOSettings structure. </returns>
	KCUBEPIEZO_API TPZ_IOSettings __cdecl PCC_GetIOSettings(char const * serialNo);

	/// <summary>	Sets the IO settings. </summary>
	/// <param name="serialNo">  	The device serial no. </param>
	/// <param name="ioSettings">	The i/o settings. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	KCUBEPIEZO_API short __cdecl PCC_SetIOSettings(char const * serialNo, TPZ_IOSettings ioSettings);

	/// <summary> Gets the Hub Analog Input. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> Hub Analogue Input Mode. <list type=table>
	///				<item><term>Input applied to all Hub bays</term><term>1</term></item>
	///				<item><term>Input applied to adjacent Hub bays</term><term>2</term></item>
	///				<item><term>Input is from external SMA</term><term>3</term></item>
	/// 		  </list> </returns>
	KCUBEPIEZO_API HubAnalogueModes __cdecl PCC_GetHubAnalogInput(char const * serialNo);

	/// <summary> Sets the Hub Analog Input. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="hubAnalogInput"> Hub Analogue Input Mode. <list type=table>
	///				<item><term>Input applied to all Hub bays</term><term>1</term></item>
	///				<item><term>Input applied to adjacent Hub bays</term><term>2</term></item>
	///				<item><term>Input is from external SMA</term><term>3</term></item>
	/// 		  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	KCUBEPIEZO_API short __cdecl PCC_SetHubAnalogInput(char const * serialNo, HubAnalogueModes hubAnalogInput);

	/// <summary> Request that the MMI Parameters for the KCube Display Interface be read from the device. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	KCUBEPIEZO_API  bool __cdecl PCC_RequestMMIParams(char const * serialNo);

	/// <summary> Get the MMI Parameters for the KCube Display Interface. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="wheelMode">	The device wheel mode.
	/// 					<list type=table>
	///							<item><term>1</term><term>Constant Voltage Rate<br />The device will continue moving until the end stop is reached or the duration of the wheel action</term></item>
	///							<item><term>2</term><term>Jog<br />The device will jog forward or backward according to the wheel action.<br />
	///								  The device will jog according to the Jog parameters</term></item>
	///							<item><term>3</term><term>Set Voltage<br />The device will set either Preset Voltage 1 or 2 according to the wheel action.</term></item>
	/// 					</list> </param>
	/// <param name="voltageAdjustRate">  The wheelmove at voltage rate.
	/// 					<list type=table>
	///							<item><term>1</term><term>Low voltage change rate</term></item>
	///							<item><term>2</term><term>Medium voltage change rate.></item>
	///							<item><term>3</term><term>High voltage change rate.</term></item>
	/// 					</list> </param>
	/// <param name="voltageStep"> The wheel jog voltage as a percentage of MaxOutputVoltage,<br />
	/// 		  range 0 to 32767 equivalent to 0% to 100%. </param>
	/// <param name="directionSense">	    The wheel direction sense. </param>
	/// <param name="presetVoltage1">	    The first preset voltage as a percentage of MaxOutputVoltage,<br />
	/// 		  range -32767 to 32767 equivalent to -100% to 100%. </param>
	/// <param name="presetVoltage2">	    The second preset voltage as a percentage of MaxOutputVoltage,<br />
	/// 		  range -32767 to 32767 equivalent to -100% to 100%. </param>
	/// <param name="displayIntensity">	    The display intensity, range 0 to 100%. </param>
	/// <param name="displayTimeout">	    The display timeout, range 0 to 480 in minutes (0 is off, otherwise the inactivity period before dimming the display). </param>
	/// <param name="displayDimIntensity">	The display dimmed intensity, range 0 to 10 (after the timeout period the device display will dim). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_SetMMIParamsExt(char const * serialNo, KPZ_WheelMode wheelMode, KPZ_WheelChangeRate voltageAdjustRate, __int32 voltageStep, KPZ_WheelDirectionSense directionSense, __int32 presetVoltage1, __int32 presetVoltage2, __int16 displayIntensity)" />
	/// <seealso cref="PCC_SetMMIParamsBlock(const char * serialNo, KPZ_MMIParams *mmiParams)" />
	/// <seealso cref="PCC_GetMMIParamsBlock(const char * serialNo, KPZ_MMIParams *mmiParams)" />
	KCUBEPIEZO_API  short __cdecl PCC_GetMMIParamsExt(char const * serialNo, KPZ_WheelMode *wheelMode, KPZ_WheelChangeRate *voltageAdjustRate, __int32 *voltageStep, KPZ_WheelDirectionSense *directionSense,
								   __int32 *presetVoltage1, __int32 *presetVoltage2, __int16 *displayIntensity, __int16 *displayTimeout, __int16 *displayDimIntensity);

	/// \deprecated
	/// <summary> Get the MMI Parameters for the KCube Display Interface. </summary>
	/// <remarks> superceded by <see cref="PCC_GetMMIParamsExt(char const * serialNo, KPZ_WheelMode *wheelMode, KPZ_WheelChangeRate *voltageAdjustRate, __int32 *voltageStep, KPZ_WheelDirectionSense *directionSense,	__int32 *presetVoltage1, __int32 *presetVoltage2, __int16 *displayIntensity, __int16 *displayTimeout, __int16 *displayDimIntensity)"/> </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="wheelMode">	The device wheel mode.
	/// 					<list type=table>
	///							<item><term>1</term><term>Constant Voltage Rate<br />The device will continue moving until the end stop is reached or the duration of the wheel action</term></item>
	///							<item><term>2</term><term>Jog<br />The device will jog forward or backward according to the wheel action.<br />
	///								  The device will jog according to the Jog parameters</term></item>
	///							<item><term>3</term><term>Set Voltage<br />The device will set either Preset Voltage 1 or 2 according to the wheel action.</term></item>
	/// 					</list> </param>
	/// <param name="voltageAdjustRate">  The wheelmove at voltage rate.
	/// 					<list type=table>
	///							<item><term>1</term><term>Low voltage change rate</term></item>
	///							<item><term>2</term><term>Medium voltage change rate.></item>
	///							<item><term>3</term><term>High voltage change rate.</term></item>
	/// 					</list> </param>
	/// <param name="voltageStep"> The wheel jog voltage as a percentage of MaxOutputVoltage,<br />
	/// 		  range 0 to 32767 equivalent to 0% to 100%. </param>
	/// <param name="directionSense">	    The wheel direction sense. </param>
	/// <param name="presetVoltage1">	    The first preset voltage as a percentage of MaxOutputVoltage,<br />
	/// 		  range -32767 to 32767 equivalent to -100% to 100%. </param>
	/// <param name="presetVoltage2">	    The second preset voltage as a percentage of MaxOutputVoltage,<br />
	/// 		  range -32767 to 32767 equivalent to -100% to 100%. </param>
	/// <param name="displayIntensity">	    The display intensity, range 0 to 100%. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_SetMMIParams(char const * serialNo, KPZ_WheelMode wheelMode, KPZ_WheelChangeRate voltageAdjustRate, __int32 voltageStep, KPZ_WheelDirectionSense directionSense, __int32 presetVoltage1, __int32 presetVoltage2, __int16 displayIntensity)" />
	/// <seealso cref="PCC_SetMMIParamsBlock(const char * serialNo, KPZ_MMIParams *mmiParams)" />
	/// <seealso cref="PCC_GetMMIParamsBlock(const char * serialNo, KPZ_MMIParams *mmiParams)" />
	KCUBEPIEZO_API  short __cdecl PCC_GetMMIParams(char const * serialNo, KPZ_WheelMode *wheelMode, KPZ_WheelChangeRate *voltageAdjustRate, __int32 *voltageStep, KPZ_WheelDirectionSense *directionSense,
		__int32 *presetVoltage1, __int32 *presetVoltage2, __int16 *displayIntensity);

	/// <summary> Set the MMI Parameters for the KCube Display Interface. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="wheelMode">	The device wheel mode.
	/// 					<list type=table>
	///							<item><term>1</term><term>Constant Voltage Rate<br />The device will continue moving until the end stop is reached or the duration of the wheel action</term></item>
	///							<item><term>2</term><term>Jog<br />The device will jog forward or backward according to the wheel action.<br />
	///								  The device will jog according to the Jog parameters</term></item>
	///							<item><term>3</term><term>Set Voltage<br />The device will set either Preset Voltage 1 or 2 according to the wheel action.</term></item>
	/// 					</list> </param>
	/// <param name="voltageAdjustRate">  The wheelmove at voltage rate.
	/// 					<list type=table>
	///							<item><term>1</term><term>Low voltage change rate</term></item>
	///							<item><term>2</term><term>Medium voltage change rate.></item>
	///							<item><term>3</term><term>High voltage change rate.</term></item>
	/// 					</list> </param>
	/// <param name="voltageStep"> The wheel jog voltage as a percentage of MaxOutputVoltage,<br />
	/// 		  range 0 to 32767 equivalent to 0% to 100%. </param>
	/// <param name="directionSense">	    The direction sense. </param>
	/// <param name="presetVoltage1">	    The first preset voltage as a percentage of MaxOutputVoltage,<br />
	/// 		  range -32767 to 32767 equivalent to -100% to 100%. </param>
	/// <param name="presetVoltage2">	    The second preset voltage as a percentage of MaxOutputVoltage,<br />
	/// 		  range -32767 to 32767 equivalent to -100% to 100%. </param>
	/// <param name="displayIntensity">	    The display intensity, range 0 to 100%. </param>
	/// <param name="displayTimeout">	    The display timeout, range 0 to 480 in minutes (0 is off, otherwise the inactivity period before dimming the display). </param>
	/// <param name="displayDimIntensity">	The display dimmed intensity, range 0 to 10 (after the timeout period the device display will dim). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_GetMMIParamsExt(char const * serialNo, KPZ_WheelMode *wheelMode, KPZ_WheelChangeRate *voltageAdjustRate, __int32 *voltageStep, KPZ_WheelDirectionSense *directionSense, __int32 *presetVoltage1, __int32 *presetVoltage2, __int16 *displayIntensity)" />
	/// <seealso cref="PCC_SetMMIParamsBlock(const char * serialNo, KPZ_MMIParams *mmiParams)" />
	/// <seealso cref="PCC_GetMMIParamsBlock(const char * serialNo, KPZ_MMIParams *mmiParams)" />
	KCUBEPIEZO_API short __cdecl PCC_SetMMIParamsExt(char const * serialNo, KPZ_WheelMode wheelMode, KPZ_WheelChangeRate voltageAdjustRate, __int32 voltageStep, KPZ_WheelDirectionSense directionSense,
		__int32 presetVoltage1, __int32 presetVoltage2, __int16 displayIntensity, __int16 displayTimeout, __int16 displayDimIntensity);

	/// \deprecated
	/// <summary> Set the MMI Parameters for the KCube Display Interface. </summary>
	/// <remarks> superceded by <see cref="PCC_SetMMIParamsExt(char const * serialNo, KPZ_WheelMode wheelMode, KPZ_WheelChangeRate voltageAdjustRate, __int32 voltageStep, KPZ_WheelDirectionSense directionSense, __int32 presetVoltage1, __int32 presetVoltage2, __int16 displayIntensity, __int16 displayTimeout, __int16 displayDimIntensity)"/> </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="wheelMode">	The device wheel mode.
	/// 					<list type=table>
	///							<item><term>1</term><term>Constant Voltage Rate<br />The device will continue moving until the end stop is reached or the duration of the wheel action</term></item>
	///							<item><term>2</term><term>Jog<br />The device will jog forward or backward according to the wheel action.<br />
	///								  The device will jog according to the Jog parameters</term></item>
	///							<item><term>3</term><term>Set Voltage<br />The device will set either Preset Voltage 1 or 2 according to the wheel action.</term></item>
	/// 					</list> </param>
	/// <param name="voltageAdjustRate">  The wheelmove at voltage rate.
	/// 					<list type=table>
	///							<item><term>1</term><term>Low voltage change rate</term></item>
	///							<item><term>2</term><term>Medium voltage change rate.></item>
	///							<item><term>3</term><term>High voltage change rate.</term></item>
	/// 					</list> </param>
	/// <param name="voltageStep"> The wheel jog voltage as a percentage of MaxOutputVoltage,<br />
	/// 		  range 0 to 32767 equivalent to 0% to 100%. </param>
	/// <param name="directionSense">	    The direction sense. </param>
	/// <param name="presetVoltage1">	    The first preset voltage as a percentage of MaxOutputVoltage,<br />
	/// 		  range -32767 to 32767 equivalent to -100% to 100%. </param>
	/// <param name="presetVoltage2">	    The second preset voltage as a percentage of MaxOutputVoltage,<br />
	/// 		  range -32767 to 32767 equivalent to -100% to 100%. </param>
	/// <param name="displayIntensity">	    The display intensity, range 0 to 100%. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_GetMMIParams(char const * serialNo, KPZ_WheelMode *wheelMode, KPZ_WheelChangeRate *voltageAdjustRate, __int32 *voltageStep, KPZ_WheelDirectionSense *directionSense, __int32 *presetVoltage1, __int32 *presetVoltage2, __int16 *displayIntensity)" />
	/// <seealso cref="PCC_SetMMIParamsBlock(const char * serialNo, KPZ_MMIParams *mmiParams)" />
	/// <seealso cref="PCC_GetMMIParamsBlock(const char * serialNo, KPZ_MMIParams *mmiParams)" />
	KCUBEPIEZO_API short __cdecl PCC_SetMMIParams(char const * serialNo, KPZ_WheelMode wheelMode, KPZ_WheelChangeRate voltageAdjustRate, __int32 voltageStep, KPZ_WheelDirectionSense directionSense,
								   __int32 presetVoltage1, __int32 presetVoltage2, __int16 displayIntensity);

	/// <summary> Requests that the trigger config parameters are read from the device. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="PCC_GetTriggerConfigParams(char const * serialNo, KPZ_TriggerPortMode *trigger1Mode, KPZ_TriggerPortPolarity *trigger1Polarity, KPZ_TriggerPortMode *trigger2Mode, KPZ_TriggerPortPolarity *trigger2Polarity)" />
	/// <seealso cref="PCC_SetTriggerConfigParams(char const * serialNo, KPZ_TriggerPortMode trigger1Mode, KPZ_TriggerPortPolarity trigger1Polarity, KPZ_TriggerPortMode trigger2Mode, KPZ_TriggerPortPolarity trigger2Polarity)" />
	KCUBEPIEZO_API bool __cdecl PCC_RequestTriggerConfigParams(char const * serialNo);

	/// <summary> Get the Trigger Configuration Parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="trigger1Mode">	    The trigger 1 mode.<list type=table>
	///						<item><term>0</term><term>Trigger disabled</term></item>
	///						<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="PCC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
	///						<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
	///						<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
	///						<item><term>10</term><term>Trigger Output - General purpose output (<see cref="PCC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
	///		 		  </list></param>
	/// <param name="trigger1Polarity"> The trigger 1 polarity.<list type=table>
	///						<item><term>1</term><term>Output high when set</term></item>
	///						<item><term>2</term><term>Output low when set</term></item>
	///		 		  </list> </param>
	/// <param name="trigger2Mode">	    The trigger 2 mode.<list type=table>
	///						<item><term>0</term><term>Trigger disabled</term></item>
	///						<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="PCC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
	///						<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
	///						<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
	///						<item><term>10</term><term>Trigger Output - General purpose output (<see cref="PCC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
	///		 		  </list></param>
	/// <param name="trigger2Polarity"> The trigger 2 polarity.<list type=table>
	///						<item><term>1</term><term>Output high when set</term></item>
	///						<item><term>2</term><term>Output low when set</term></item>
	///		 		  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_SetTriggerConfigParams(char const * serialNo, KPZ_TriggerPortMode trigger1Mode, KPZ_TriggerPortPolarity trigger1Polarity, KPZ_TriggerPortMode trigger2Mode, KPZ_TriggerPortPolarity trigger2Polarity)" />
	/// <seealso cref="PCC_SetTriggerConfigParamsBlock(const char * serialNo, KPZ_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="PCC_GetTriggerConfigParamsBlock(const char * serialNo, KPZ_TriggerConfig *triggerConfigParams)" />
	KCUBEPIEZO_API  short __cdecl PCC_GetTriggerConfigParams(char const * serialNo, KPZ_TriggerPortMode *trigger1Mode, KPZ_TriggerPortPolarity *trigger1Polarity, KPZ_TriggerPortMode *trigger2Mode, KPZ_TriggerPortPolarity *trigger2Polarity);

	/// <summary> Set the Trigger Configuration Parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="trigger1Mode">	    The trigger 1 mode.<list type=table>
	///						<item><term>0</term><term>Trigger disabled</term></item>
	///						<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="PCC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
	///						<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
	///						<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
	///						<item><term>10</term><term>Trigger Output - General purpose output (<see cref="PCC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
	///		 		  </list></param>
	/// <param name="trigger1Polarity"> The trigger 1 polarity.<list type=table>
	///						<item><term>1</term><term>Output high when set</term></item>
	///						<item><term>2</term><term>Output low when set</term></item>
	///		 		  </list> </param>
	/// <param name="trigger2Mode">	    The trigger 2 mode.<list type=table>
	///						<item><term>0</term><term>Trigger disabled</term></item>
	///						<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="PCC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
	///						<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
	///						<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
	///						<item><term>10</term><term>Trigger Output - General purpose output (<see cref="PCC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
	///		 		  </list></param>
	/// <param name="trigger2Polarity"> The trigger 2 polarity.<list type=table>
	///						<item><term>1</term><term>Output high when set</term></item>
	///						<item><term>2</term><term>Output low when set</term></item>
	///		 		  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_GeTriggerConfigParams(char const * serialNo, KPZ_TriggerPortMode *trigger1Mode, KPZ_TriggerPortPolarity *trigger1Polarity, KPZ_TriggerPortMode *trigger2Mode, KPZ_TriggerPortPolarity *trigger2Polarity)" />
	/// <seealso cref="PCC_SetTriggerConfigParamsBlock(const char * serialNo, KPZ_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="PCC_GetTriggerConfigParamsBlock(const char * serialNo, KPZ_TriggerConfig *triggerConfigParams)" />
	KCUBEPIEZO_API short __cdecl PCC_SetTriggerConfigParams(char const * serialNo, KPZ_TriggerPortMode trigger1Mode, KPZ_TriggerPortPolarity trigger1Polarity, KPZ_TriggerPortMode trigger2Mode, KPZ_TriggerPortPolarity trigger2Polarity);

	/// <summary> Gets the MMI parameters for the device. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="mmiParams"> Options for controlling the mmi. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_GetMMIParamsExt(char const * serialNo, KPZ_WheelMode *wheelMode, KPZ_WheelChangeRate *voltageAdjustRate, __int32 *voltageStep, KPZ_WheelDirectionSense *directionSense, __int32 *presetVoltage1, __int32 *presetVoltage2, __int16 *displayIntensity, __int16 *displayTimeout, __int16 *displayDimIntensity)" />
	/// <seealso cref="PCC_SetMMIParamsExt(char const * serialNo, KPZ_WheelMode wheelMode, KPZ_WheelChangeRate voltageAdjustRate, __int32 voltageStep, KPZ_WheelDirectionSense directionSense, __int32 presetVoltage1, __int32 presetVoltage2, __int16 displayIntensity, __int16 displayTimeout, __int16 displayDimIntensity)" />
	/// <seealso cref="PCC_SetMMIParamsBlock(const char * serialNo, KPZ_MMIParams *mmiParams)" />
	KCUBEPIEZO_API short __cdecl PCC_GetMMIParamsBlock(char const * serialNo, KPZ_MMIParams *mmiParams);

	/// <summary> Sets the MMI parameters for the device. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="mmiParams"> Options for controlling the mmi. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_GetMMIParamsExt(char const * serialNo, KPZ_WheelMode *wheelMode, KPZ_WheelChangeRate *voltageAdjustRate, __int32 *voltageStep, KPZ_WheelDirectionSense *directionSense, __int32 *presetVoltage1, __int32 *presetVoltage2, __int16 *displayIntensity, __int16 *displayTimeout, __int16 *displayDimIntensity)" />
	/// <seealso cref="PCC_SetMMIParamsExt(char const * serialNo, KPZ_WheelMode wheelMode, KPZ_WheelChangeRate voltageAdjustRate, __int32 voltageStep, KPZ_WheelDirectionSense directionSense, __int32 presetVoltage1, __int32 presetVoltage2, __int16 displayIntensity, __int16 displayTimeout, __int16 displayDimIntensity)" />
	/// <seealso cref="PCC_GetMMIParamsBlock(const char * serialNo, KPZ_MMIParams *mmiParams)" />
	KCUBEPIEZO_API short __cdecl PCC_SetMMIParamsBlock(char const * serialNo, KPZ_MMIParams *mmiParams);

	/// <summary> Gets the trigger configuration parameters block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="triggerConfigParams"> Options for controlling the trigger configuration. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_GeTriggerConfigParams(char const * serialNo, KPZ_TriggerPortMode *trigger1Mode, KPZ_TriggerPortPolarity *trigger1Polarity, KPZ_TriggerPortMode *trigger2Mode, KPZ_TriggerPortPolarity *trigger2Polarity)" />
	/// <seealso cref="PCC_SetTriggerConfigParams(char const * serialNo, KPZ_TriggerPortMode trigger1Mode, KPZ_TriggerPortPolarity trigger1Polarity, KPZ_TriggerPortMode trigger2Mode, KPZ_TriggerPortPolarity trigger2Polarity)" />
	/// <seealso cref="PCC_SetTriggerConfigParamsBlock(const char * serialNo, KPZ_TriggerConfig *triggerConfigParams)" />
	KCUBEPIEZO_API short __cdecl PCC_GetTriggerConfigParamsBlock(char const * serialNo, KPZ_TriggerConfig *triggerConfigParams);

	/// <summary> Sets the trigger configuration parameters block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="triggerConfigParams"> Options for controlling the trigger configuration. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_GeTriggerConfigParams(char const * serialNo, KPZ_TriggerPortMode *trigger1Mode, KPZ_TriggerPortPolarity *trigger1Polarity, KPZ_TriggerPortMode *trigger2Mode, KPZ_TriggerPortPolarity *trigger2Polarity)" />
	/// <seealso cref="PCC_SetTriggerConfigParams(char const * serialNo, KPZ_TriggerPortMode trigger1Mode, KPZ_TriggerPortPolarity trigger1Polarity, KPZ_TriggerPortMode trigger2Mode, KPZ_TriggerPortPolarity trigger2Polarity)" />
	/// <seealso cref="PCC_GetTriggerConfigParamsBlock(const char * serialNo, KPZ_TriggerConfig *triggerConfigParams)" />
	KCUBEPIEZO_API short __cdecl PCC_SetTriggerConfigParamsBlock(char const * serialNo, KPZ_TriggerConfig *triggerConfigParams);

	/// <summary> Requests the digital output bits. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_SetDigitalOutputs(char const * serialNo, byte outputsBits)" />
	/// <seealso cref="PCC_GetDigitalOutputs(char const * serialNo)" />
	KCUBEPIEZO_API short __cdecl PCC_RequestDigitalOutputs(char const * serialNo);

	/// <summary> Gets the digital output bits. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> Bit mask of states of the 4 digital output pins. </returns>
	/// <seealso cref="PCC_SetDigitalOutputs(char const * serialNo, byte outputsBits)" />
	/// <seealso cref="PCC_RequestDigitalOutputs(char const * serialNo)" />
	KCUBEPIEZO_API byte __cdecl PCC_GetDigitalOutputs(char const * serialNo);

	/// <summary> Sets the digital output bits. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="outputsBits"> Bit mask to set states of the 4 digital output pins. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PCC_GetDigitalOutputs(char const * serialNo)" />
	/// <seealso cref="PCC_RequestDigitalOutputs(char const * serialNo)" />
	KCUBEPIEZO_API short __cdecl PCC_SetDigitalOutputs(char const * serialNo, byte outputsBits);
}
/** @} */ // KCubePiezo
