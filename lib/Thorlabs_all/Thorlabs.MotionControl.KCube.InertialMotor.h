// summary:	Declares the functions class
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the TCUBEInertialMotor_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// KCUBEINERTIALMOTOR_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef KCUBEINERTIALMOTORDLL_EXPORTS
#define KCUBEINERTIALMOTOR_API __declspec(dllexport)
#else
#define KCUBEINERTIALMOTOR_API __declspec(dllimport)
#endif

#include <OaIdl.h>

#pragma once

/** @defgroup KCubeInertialMotor KCube InertialMotor
 *  This section details the Structures and Functions relavent to the  @ref KIM101_page "InertialMotor"<br />
 *  For an example of how to connect to the device and perform simple operations use the following links:
 *  <list type=bullet>
 *    <item> \ref namespaces_kim_ex_1 "Example of using the Thorlabs.MotionControl.KCube.InertialMotor.DLL from a C or C++ project."<br />
 *									  This requires the DLL to be dynamical linked. </item>
 *    <item> \ref namespaces_kim_ex_2 "Example of using the Thorlabs.MotionControl.KCube.InertialMotor.DLL from a C# project"<br />
 *									  This uses Marshalling to load and access the C DLL. </item>
 *  </list>
 *  The Thorlabs.MotionControl.KCube.InertialMotor.DLL requires the following DLLs
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
	/// \endcond
#pragma pack(1)

	/// <summary> Values that represent kim stages. </summary>
	typedef enum KIM_Stages : unsigned short
	{
		/// <summary> An enum constant representing the undefined stage option. </summary>
		Undefined_stage = 0,
		/// <summary> An enum constant representing the PIA stage option. </summary>
		PIA_stage = 1,
		/// <summary> An enum constant representing the PD(R) stage option. </summary>
		PDR_Stage = 2,
	} KIM_Stages;

	/// <summary> Values that represent KIM_Channels. </summary>
	typedef enum KIM_Channels : unsigned __int16
	{
		/// <summary> An enum constant representing the channel 1 option. </summary>
		Channel1 = 1,
		/// <summary> An enum constant representing the channel 2 option. </summary>
		Channel2,
		/// <summary> An enum constant representing the channel 3 option. </summary>
		Channel3,
		/// <summary> An enum constant representing the channel 4 option. </summary>
		Channel4
	} KIM_Channels;

	/// <summary> Values that represent KIM_JogMode. </summary>
	typedef enum KIM_JogMode : unsigned __int16
	{
		/// <summary> An enum constant representing the jog continuous option. </summary>
		JogContinuous = 0x01,
		/// <summary> An enum constant representing the jog step option. </summary>
		JogStep = 0x02,
	} KIM_JogMode;

	/// <summary> Values that represent KIM_TravelDirection. </summary>
	typedef enum KIM_TravelDirection : byte
	{
		/// <summary> An enum constant representing the forward option. </summary>
		Forward = 0x01,
		/// <summary> An enum constant representing the reverse option. </summary>
		Reverse = 0x02,
	} KIM_TravelDirection;

	/// <summary> KIM Drive Operation Parameters. </summary>
	typedef struct KIM_DriveOPParameters
	{
		/// <summary> The maximum voltage. </summary>
		__int16 _maxVoltage;
		/// <summary> The step rate. </summary>
		__int32 _stepRate;
		/// <summary> The step acceleration. </summary>
		__int32 _stepAcceleration;
	} KIM_DriveOPParameters;

	/// <summary> KIM jog parameters. </summary>
	typedef struct KIM_JogParameters
	{
		/// <summary> The jog mode. </summary>
		KIM_JogMode _jogMode;
		/// <summary>	Size of the jog step. </summary>
		__int32 _jogStepSizeFwd;
		/// <summary>	The jog step size reverse. </summary>
		__int32 _jogStepSizeRev;
		/// <summary> The jog step rate. </summary>
		__int32 _jogStepRate;
		/// <summary> The jog step acceleration. </summary>
		__int32 _jogStepAcceleration;
	} KIM_JogParameters;

	/// <summary>	Values that represent KIM fb signal modes. </summary>
	typedef enum KIM_FBSignalMode : __int16
	{
		/// <summary>	An enum constant representing the fb limit switch option. </summary>
		FB_LimitSwitch = 0x01,
		/// <summary>	An enum constant representing the fb encoder option. </summary>
		FB_Encoder = 0x02,
	} KIM_FBSignalMode;

	/// <summary>	Values that represent KIM limit switch modes. </summary>
	typedef enum KIM_LimitSwitchModes : __int16
	{
		/// <summary>	An enum constant representing the ignore option. </summary>
		Ignore = 0x01,
		/// <summary>	An enum constant representing the switch makes option. </summary>
		SwitchMakes = 0x02,
		/// <summary>	An enum constant representing the switch breaks option. </summary>
		SwitchBreaks = 0x03,
		/// <summary>	An enum constant representing the switch makes home only option. </summary>
		SwitchMakes_HomeOnly = 0x04,
		/// <summary>	An enum constant representing the switch breaks home only option. </summary>
		SwitchBreaks_HomeOnly = 0x05,
	} KIM_LimitSwitchModes;

	/// <summary> Values that represent KIM_TravelDirection. </summary>
	typedef enum KIM_DirectionSense : __int16
	{
		Dir_Disabled = 0x0,
		/// <summary> An enum constant representing the forward option. </summary>
		Dir_Forward = 0x01,
		/// <summary> An enum constant representing the reverse option. </summary>
		Dir_Reverse = 0x02,
	} KIM_DirectionSense;

	/// <summary>	Values that represent KIM trig modes. </summary>
	typedef enum KIM_TrigModes : __int16
	{
		/// <summary>	An enum constant representing the trig disabled option. </summary>
		Trig_Disabled = 0x00,
		/// <summary>	An enum constant representing the trig in gpi option. </summary>
		Trig_In_GPI = 0x01,
		/// <summary>	An enum constant representing the trig in relative move option. </summary>
		Trig_InRelativeMove = 0x02,
		/// <summary>	An enum constant representing the trig in absolute move option. </summary>
		Trig_InAbsoluteMove = 0x03,
		/// <summary>	An enum constant representing the trig in reset count option. </summary>
		Trig_InResetCount = 0x04,
		/// <summary>	An enum constant representing the trig out gp 0 option. </summary>
		Trig_Out_GP0 = 0x0A,
		/// <summary>	An enum constant representing the trig out in motion option. </summary>
		Trig_Out_InMotion = 0x0B,
		/// <summary>	An enum constant representing the trig out at Maximum velocity option. </summary>
		Trig_Out_AtMaxVelocity = 0x0C,

		/// <summary>	An enum constant representing the trig out Position step Forward option. </summary>
		Trig_Out_PosStepFwd = 0x0D,
		/// <summary>	An enum constant representing the trig out Position step Reverse option. </summary>
		Trig_Out_PosStepRev = 0x0E,
		/// <summary>	An enum constant representing the trig out Position step both option. </summary>
		Trig_Out_PosStepBoth = 0x0F,

		/// <summary>	An enum constant representing the trig out at Forward limit option. </summary>
		Trig_Out_AtFwdLimit = 0x10,
		/// <summary>	An enum constant representing the trig out at Reverse limit option. </summary>
		Trig_Out_AtRevLimit = 0x11,
		/// <summary>	An enum constant representing the trig out at either limit option. </summary>
		Trig_Out_AtEitherLimit = 0x12,
	} KIM_TrigModes;

	/// <summary>	Values that represent KIM trig polarities. </summary>
	typedef enum KIM_TrigPolarities : __int16
	{
		/// <summary>	An enum constant representing the trig high option. </summary>
		Trig_High = 0x01,
		/// <summary>	An enum constant representing the trig low option. </summary>
		Trig_Low = 0x02,
	} KIM_TrigPolarities;

	/// <summary>	Values that represent KIM joystic modes. </summary>
	typedef enum KIM_JoysticModes : __int16
	{
		JS_Velocity = 0x01,
		JS_Jog = 0x02,
		JS_GotoPosition = 0x03,
	} KIM_JoysticModes;

	/// <summary> Values that represent channel enable modes. </summary>
	typedef enum ChannelEnableModes : __int16
	{
		/// <summary>	An enum constant representing the none option. </summary>
		None = 0x00,
		/// <summary>	An enum constant representing the channel 1 only option. </summary>
		Channel1Only = 0x01,
		/// <summary>	An enum constant representing the channel 2 only option. </summary>
		Channel2Only = 0x02,
		/// <summary>	An enum constant representing the channel 3 only option. </summary>
		Channel3Only = 0x03,
		/// <summary>	An enum constant representing the channel 4 only option. </summary>
		Channel4Only = 0x04,

		/// <summary>	An enum constant representing the channels 1 and 2 option. </summary>
		Channels1and2 = 0x05,
		/// <summary>	An enum constant representing the channels 3 and 4 option. </summary>
		Channels3and4 = 0x06,
	} ChannelEnableModes;

	/// <summary>	A KIM limit switch parameters. </summary>
	struct KIM_LimitSwitchParameters
	{
		/// <summary>	The forward limit. </summary>
		KIM_LimitSwitchModes _forwardLimit;
		/// <summary>	The reverse limit. </summary>
		KIM_LimitSwitchModes _reverseLimit;
		/// <summary>	Identifier for the stage. </summary>
		__int16 _stageID;
	};

	/// <summary>	A KIM home parameters. </summary>
	struct KIM_HomeParameters
	{
		/// <summary>	The home direction. </summary>
		KIM_TravelDirection _homeDirection;
		/// <summary>	The home limit switch. </summary>
		KIM_TravelDirection _homeLimitSwitch;
		/// <summary>	The home step rate. </summary>
		__int32 _homeStepRate;
		/// <summary>	The home offset. </summary>
		__int32 _homeOffset;
	};

	/// <summary>	A KIM mmi parameters a. </summary>
	struct KIM_MMIParameters
	{
		/// <summary>	The joystick mode. </summary>
		KIM_JoysticModes _joystickMode;
		/// <summary>	The maximum step rate. </summary>
		__int32 _maxStepRate;
		/// <summary>	The direction sense. </summary>
		KIM_DirectionSense _directionSense;
		/// <summary>	The display intensity. </summary>
		__int16 _displayIntensity;
	};

	/// <summary>	A KIM mmi parameters b. </summary>
	struct KIM_MMIChannelParameters
	{
		/// <summary>	The first preset position. </summary>
		__int32 _presetPos1;
		/// <summary>	The second preset position. </summary>
		__int32 _presetPos2;
	};

	/// <summary>	A KIM trig i/o configuration. </summary>
	struct KIM_TrigIOConfig
	{
		/// <summary>	The first trig channel. </summary>
		KIM_Channels _trigChannel1;
		/// <summary>	The second trig channel. </summary>
		KIM_Channels _trigChannel2;
		/// <summary>	The trig 1 mode. </summary>
		KIM_TrigModes _trig1Mode;
		/// <summary>	The trig 1 polarity. </summary>
		KIM_TrigPolarities _trig1Polarity;
		/// <summary>	The trig 2 mode. </summary>
		KIM_TrigModes _trig2Mode;
		/// <summary>	The trig 2 polarity. </summary>
		KIM_TrigPolarities _trig2Polarity;
	};

	/// <summary>	A KIM trig parameters parameters. </summary>
	struct KIM_TrigParamsParameters
	{
		/// <summary>	The start position forward. </summary>
		__int32 _startPosFwd;
		/// <summary>	The interval forward. </summary>
		__int32 _intervalFwd;
		/// <summary>	Number of pulses forwards. </summary>
		__int32 _numberOfPulsesFwd;
		/// <summary>	The start position reverse. </summary>
		__int32 _startPosRev;
		/// <summary>	The interval reverse. </summary>
		__int32 _intervalRev;
		/// <summary>	Number of pulses reverses. </summary>
		__int32 _numberOfPulsesRev;
		/// <summary>	Width of the pulse. </summary>
		__int32 _pulseWidth;
		/// <summary>	Number of cycles. </summary>
		__int32 _numberOfCycles;

		/// <summary>	The reserved[ 6]. </summary>
		__int16 _reserved[6];
	};

	/// <summary>	A KIM feedback signal parameters. </summary>
	struct KIM_FeedbackSigParams
	{
		/// <summary>	The feedback signal mode. </summary>
		KIM_FBSignalMode _feedbackSignalMode;
		/// <summary>	The encoder constant. </summary>
		__int32 _encoderConst;
		/// <summary>	The reserved[ 4]. </summary>
		__int16 _reserved[4];
	};

	/// <summary> KIM status. </summary>
	typedef struct KIM_Status
	{
		/// <summary> The position. </summary>
		__int32 _position;
		/// <summary> Number of encoders. </summary>
		__int32 _encoderCount;
		/// <summary> The status bits. </summary>
		unsigned __int32 _statusBits;
	} KIM_Status;


#pragma pack()

#pragma pack(1)

	/// <summary> Information about the device generated from serial number. </summary>
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

		/// <summary> True if this object is a type known to the Motion Control software. </summary>
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

		/// <summary> True if the device is a piezo device. </summary>
		bool isPiezoDevice;
		/// <summary> True if the device is a laser. </summary>
		bool isLaser;
		/// <summary> True if the device is a custom type. </summary>
		bool isCustomType;
		/// <summary> True if the device is a rack. </summary>
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
	KCUBEINERTIALMOTOR_API short __cdecl TLI_BuildDeviceList(void);

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
	KCUBEINERTIALMOTOR_API short __cdecl TLI_GetDeviceListSize();

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
	KCUBEINERTIALMOTOR_API short __cdecl TLI_GetDeviceList(SAFEARRAY** stringsReceiver);

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
	KCUBEINERTIALMOTOR_API short __cdecl TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID);

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
	KCUBEINERTIALMOTOR_API short __cdecl TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length);

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
	KCUBEINERTIALMOTOR_API short __cdecl TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer);

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
	KCUBEINERTIALMOTOR_API short __cdecl TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID);

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
	KCUBEINERTIALMOTOR_API short __cdecl TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length);

	/// <summary> Get the device information from the USB port. </summary>
	/// <remarks> The Device Info is read from the USB port not from the device itself.<remarks>
	/// <param name="serialNumber"> The serial number of the device. </param>
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
	KCUBEINERTIALMOTOR_API short __cdecl TLI_GetDeviceInfo(char const * serialNumber, TLI_DeviceInfo *info);

	/// <summary> Initialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <remarks> Call TLI_InitializeSimulations before TLI_BuildDeviceList at the start of the program to make a connection to the simulation manager.<Br />
	/// 		  Any devices configured in the simulation manager will become visible TLI_BuildDeviceList is called and can be accessed using TLI_GetDeviceList.<Br />
	/// 		  Call TLI_InitializeSimulations at the end of the program to release the simulator.  </remarks>
	/// <seealso cref="TLI_UninitializeSimulations()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	KCUBEINERTIALMOTOR_API void __cdecl TLI_InitializeSimulations();

	/// <summary> Uninitialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <seealso cref="TLI_InitializeSimulations()" />
	KCUBEINERTIALMOTOR_API void __cdecl TLI_UninitializeSimulations();

	/// <summary> Open the device for communications. </summary>
	/// <param name="serialNumber">	The serial no of the device to be connected. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="KIM_Close(char const * serialNumber)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_Open(char const * serialNumber);

	/// <summary> Disconnect and close the device. </summary>
	/// <param name="serialNumber">	The serial no of the device to be disconnected. </param>
	/// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="KIM_Open(char const * serialNumber)" />
	KCUBEINERTIALMOTOR_API void __cdecl KIM_Close(char const * serialNumber);

	/// <summary>	Check connection. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <returns> true if the USB is listed by the ftdi controller</returns>
	/// \include CodeSnippet_CheckConnection.cpp
	KCUBEINERTIALMOTOR_API bool __cdecl KIM_CheckConnection(char const * serialNumber);

	/// <summary> Sends a command to the device to make it identify iteself. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	KCUBEINERTIALMOTOR_API void __cdecl KIM_Identify(char const * serialNumber);

	/// <summary> Gets the hardware information from the device. </summary>
	/// <param name="serialNumber">			The device serial number. </param>
	/// <param name="modelNo">				Address of a buffer to receive the model number string. Minimum 8 characters </param>
	/// <param name="sizeOfModelNo">		The size of the model number buffer, minimum of 8 characters. </param>
	/// <param name="type">					Address of a WORD to receive the hardware type number. </param>
	/// <param name="numChannels">			Address of a short to receive the  number of channels. </param>
	/// <param name="notes">				Address of a buffer to receive the notes describing the device. </param>
	/// <param name="sizeOfNotes">			The size of the notes buffer, minimum of 48 characters. </param>
	/// <param name="firmwareVersion">		Address of a DWORD to receive the  firmware version number made up of 4 byte parts. </param>
	/// <param name="hardwareVersion">		Address of a WORD to receive the  hardware version number. </param>
	/// <param name="modificationState">	Address of a WORD to receive the hardware modification state number. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// 		  \include CodeSnippet_identify.cpp
	KCUBEINERTIALMOTOR_API short __cdecl KIM_GetHardwareInfo(char const * serialNumber, char * modelNo, DWORD sizeOfModelNo, WORD * type, WORD * numChannels,
		char * notes, DWORD sizeOfNotes, DWORD * firmwareVersion, WORD * hardwareVersion, WORD * modificationState);

	/// <summary> Gets the hardware information in a block. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <param name="hardwareInfo">	Address of a TLI_HardwareInformation structure to receive the hardware information. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// 		  \include CodeSnippet_identify.cpp
	KCUBEINERTIALMOTOR_API short __cdecl KIM_GetHardwareInfoBlock(char const *serialNumber, TLI_HardwareInformation *hardwareInfo);

	/// <summary> Gets version number of the device firmware. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <returns> The device firmware version number made up of 4 byte parts. </returns>
	/// 		  \include CodeSnippet_identify.cpp
	KCUBEINERTIALMOTOR_API DWORD __cdecl KIM_GetFirmwareVersion(char const * serialNumber);

	/// <summary> Gets version number of the device software. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <returns> The device software version number made up of 4 byte parts. </returns>
	/// 		  \include CodeSnippet_identify.cpp
	KCUBEINERTIALMOTOR_API DWORD __cdecl KIM_GetSoftwareVersion(char const * serialNumber);

	/// <summary> Update device with stored settings. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <returns> True if successful, false if not. </returns>
	/// 		  \include CodeSnippet_connection1.cpp
	KCUBEINERTIALMOTOR_API bool __cdecl KIM_LoadSettings(char const * serialNumber);

	/// <summary> Update device with named settings. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <param name="settingsName">	Name of settings stored away from device. </param>
	/// <returns> True if successful, false if not. </returns>
	///             \include CodeSnippet_connection1.cpp
	KCUBEINERTIALMOTOR_API bool __cdecl KIM_LoadNamedSettings(char const * serialNumber, char const *settingsName);

	/// <summary> persist the devices current settings. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <returns> True if successful, false if not. </returns>
	KCUBEINERTIALMOTOR_API bool __cdecl KIM_PersistSettings(char const * serialNumber);

	/// <summary> Disable cube. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_Enable(char const * serialNumber)" />
	/// <seealso cref="KIM_EnableChannel(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_DisableChannel(char const * serialNumber, KIM_Channels channel)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_Disable(char const * serialNumber);

	/// <summary> Disable a channel. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_EnableChannel(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_Enable(char const * serialNumber)" />
	/// <seealso cref="KIM_Disable(char const * serialNumber)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_DisableChannel(char const * serialNumber, KIM_Channels channel);

	/// <summary> Enable cube for computer control. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_Disable(char const * serialNumber)" />
	/// <seealso cref="KIM_EnableChannel(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_DisableChannel(char const * serialNumber, KIM_Channels channel)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_Enable(char const * serialNumber);

	/// <summary> Enable a channel. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_DisableChannel(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_Enable(char const * serialNumber)" />
	/// <seealso cref="KIM_Disable(char const * serialNumber)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_EnableChannel(char const * serialNumber, KIM_Channels channel);

	/// <summary> Determine if the device front panel can be locked. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <returns> True if we can lock the device front panel, false if not. </returns>
	/// <seealso cref="KIM_GetFrontPanelLocked(char const * serialNumber)" />
	/// <seealso cref="KIM_RequestFrontPanelLocked(char const * serialNumber)" />
	/// <seealso cref="KIM_SetFrontPanelLock(char const * serialNumber, bool locked)" />
	KCUBEINERTIALMOTOR_API bool __cdecl KIM_CanDeviceLockFrontPanel(char const * serialNumber);

	/// <summary> Query if the device front panel locked. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <returns> True if the device front panel is locked, false if not. </returns>
	/// <seealso cref="KIM_CanDeviceLockFrontPanel(char const * serialNumber)" />
	/// <seealso cref="KIM_RequestFrontPanelLocked(char const * serialNumber)" />
	/// <seealso cref="KIM_SetFrontPanelLock(char const * serialNumber, bool locked)" />
	KCUBEINERTIALMOTOR_API bool __cdecl  KIM_GetFrontPanelLocked(char const * serialNumber);

	/// <summary> Ask the device if its front panel is locked. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_CanDeviceLockFrontPanel(char const * serialNumber)" />
	/// <seealso cref="KIM_GetFrontPanelLocked(char const * serialNumber)" />
	/// <seealso cref="KIM_SetFrontPanelLock(char const * serialNumber, bool locked)" />
	KCUBEINERTIALMOTOR_API short __cdecl  KIM_RequestFrontPanelLocked(char const * serialNumber);

	/// <summary> Sets the device front panel lock state. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <param name="locked"> True to lock the device, false to unlock. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_CanDeviceLockFrontPanel(char const * serialNumber)" />
	/// <seealso cref="KIM_GetFrontPanelLocked(char const * serialNumber)" />
	/// <seealso cref="KIM_RequestFrontPanelLocked(char const * serialNumber)" />
	KCUBEINERTIALMOTOR_API short __cdecl  KIM_SetFrontPanelLock(char const * serialNumber, bool locked);

	/// <summary> Reset the device. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	KCUBEINERTIALMOTOR_API short __cdecl KIM_Reset(char const * serialNumber);

	/// <summary> Tells the device that it is being disconnected. </summary>
	/// <remarks> This does not disconnect the communications.<br />
	/// 		  To disconnect the communications, call the <see cref="KIM_Close(char const * serialNumber)" /> function. </remarks>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	KCUBEINERTIALMOTOR_API short __cdecl KIM_Disconnect(char const * serialNumber);

	/// <summary> Clears the device message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNumber"> The device serial number. </param>
	KCUBEINERTIALMOTOR_API void __cdecl KIM_ClearMessageQueue(char const * serialNumber);

	/// <summary> Registers a callback on the message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNumber">		The device serial number. </param>
	/// <param name="functionPointer">	A function pointer to be called whenever messages are received. </param>
	/// <seealso cref="KIM_MessageQueueSize(char const * serialNumber)" />
	/// <seealso cref="KIM_GetNextMessage(char const * serialNumber, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="KIM_WaitForMessage(char const * serialNumber, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KCUBEINERTIALMOTOR_API void __cdecl KIM_RegisterMessageCallback(char const * serialNumber, void(*functionPointer)());

	/// <summary> Gets the MessageQueue size. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <returns> number of messages in the queue. </returns>
	/// <seealso cref="KIM_RegisterMessageCallback(char const * serialNumber, void (* functionPointer)())" />
	/// <seealso cref="KIM_GetNextMessage(char const * serialNumber, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="KIM_WaitForMessage(char const * serialNumber, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KCUBEINERTIALMOTOR_API int __cdecl KIM_MessageQueueSize(char const * serialNumber);

	/// <summary> Get the next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <param name="messageType">	The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">	The address of the parameter to receive the message id. </param>
	/// <param name="messageData">	The address of the parameter to receive the message data. </param>
	/// <returns> True if successful, false if not. </returns>
	/// <seealso cref="KIM_RegisterMessageCallback(char const * serialNumber, void (* functionPointer)())" />
	/// <seealso cref="KIM_MessageQueueSize(char const * serialNumber)" />
	/// <seealso cref="KIM_WaitForMessage(char const * serialNumber, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KCUBEINERTIALMOTOR_API bool __cdecl KIM_GetNextMessage(char const * serialNumber, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Wait for next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <param name="messageType">	The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">	The address of the parameter to receive the message id. </param>
	/// <param name="messageData">	The address of the parameter to receive the message data. </param>
	/// <returns> True if successful, false if not. </returns>
	/// <seealso cref="KIM_RegisterMessageCallback(char const * serialNumber, void (* functionPointer)())" />
	/// <seealso cref="KIM_MessageQueueSize(char const * serialNumber)" />
	/// <seealso cref="KIM_GetNextMessage(char const * serialNumber, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KCUBEINERTIALMOTOR_API bool __cdecl KIM_WaitForMessage(char const * serialNumber, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Home the device to a limit switch or reset to zero if no limit switches available. </summary>
	/// <param name="serialNumber">	The serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	KCUBEINERTIALMOTOR_API short __cdecl KIM_Home(char const * serialNumber, KIM_Channels channel);

	/// <summary> Sets the current position to zero. </summary>
	/// <param name="serialNumber">	The serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	KCUBEINERTIALMOTOR_API short __cdecl KIM_ZeroPosition(char const * serialNumber, KIM_Channels channel);

	/// <summary> set the position. </summary>
	/// <param name="serialNumber">	The serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <param name="position">		The position. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	KCUBEINERTIALMOTOR_API short __cdecl KIM_SetPosition(char const * serialNumber, KIM_Channels channel, long position);

	/// <summary> Move absolute. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <param name="position">		The position. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	KCUBEINERTIALMOTOR_API short __cdecl KIM_MoveAbsolute(char const * serialNumber, KIM_Channels channel, __int32 position);

	/// <summary> Move relative. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <param name="stepSize">		The relative move step size. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	KCUBEINERTIALMOTOR_API short __cdecl KIM_MoveRelative(char const * serialNumber, KIM_Channels channel, __int32 stepSize);

	/// <summary> Move jog. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <param name="jogDirection">	The jog direction. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	KCUBEINERTIALMOTOR_API short __cdecl KIM_MoveJog(char const * serialNumber, KIM_Channels channel, KIM_TravelDirection jogDirection);

	/// <summary> Move stop. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	KCUBEINERTIALMOTOR_API short __cdecl KIM_MoveStop(char const * serialNumber, KIM_Channels channel);

	/// <summary> Gets a flag to show whether the KIM stage type is supported. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <seealso cref="KIM_SetStageType(char const * serialNumber, KIM_Stages stageType)" />
	/// <seealso cref="KIM_RequestStageType(char const * serialNumber)" />
	/// <seealso cref="KIM_GetStageType(char const * serialNumber)" />
	/// <returns> true if <see cref="KIM_GetStageType(char const * serialNumber)" /> is supported. </returns>
	KCUBEINERTIALMOTOR_API bool __cdecl KIM_SupportsStageType(char const * serialNumber);

	/// <summary> Gets the KIM stage type. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <seealso cref="KIM_SetStageType(char const * serialNumber, KIM_Stages stageType)" />
	/// <seealso cref="KIM_RequestStageType(char const * serialNumber)" />
	/// <seealso cref="KIM_SupportsStageType(char const * serialNumber)" />
	/// <returns> The stage type. </returns>
	KCUBEINERTIALMOTOR_API KIM_Stages __cdecl KIM_GetStageType(char const * serialNumber);

	/// <summary> Sets the KIM stage type. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <param name="stageType">	Type of the stage. </param>
	/// <seealso cref="KIM_RequestStageType(char const * serialNumber)" />
	/// <seealso cref="KIM_GetStageType(char const * serialNumber)" />
	/// <seealso cref="KIM_SupportsStageType(char const * serialNumber)" />
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	KCUBEINERTIALMOTOR_API short __cdecl KIM_SetStageType(char const * serialNumber, KIM_Stages stageType);

	/// <summary> Request KIM stage type. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <seealso cref="KIM_SetStageType(char const * serialNumber, KIM_Stages stageType)" />
	/// <seealso cref="KIM_GetStageType(char const * serialNumber)" />
	/// <seealso cref="KIM_SupportsStageType(char const * serialNumber)" />
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	KCUBEINERTIALMOTOR_API short __cdecl KIM_RequestStageType(char const * serialNumber);

	/// <summary> Requests the operation drive parameters. </summary>
	/// <param name="serialNumber">	The serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_SetDriveOPParameters(char const * serialNumber, KIM_Channels channel, __int16 maxVoltage, __int32 stepRate, __int32 stepAcceleration)" />
	/// <seealso cref="KIM_GetDriveOPParameters(char const * serialNumber, KIM_Channels channel, __int16 &maxVoltage, __int32 &stepRate, __int32 &stepAcceleration)" />
	/// <seealso cref="KIM_SetDriveOPParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_DriveOPParameters &driveOPParameters)" />
	/// <seealso cref="KIM_GetDriveOPParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_DriveOPParameters &driveOPParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_RequestDriveOPParameters(char const * serialNumber, KIM_Channels channel);

	/// <summary> Sets the operation drive parameters. </summary>
	/// <param name="serialNumber">		The device serial number. </param>
	/// <param name="channel">			The channel. </param>
	/// <param name="maxVoltage">		The maximum voltage. </param>
	/// <param name="stepRate">			The step rate. </param>
	/// <param name="stepAcceleration">	The step acceleration. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestDriveOPParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_GetDriveOPParameters(char const * serialNumber, KIM_Channels channel, __int16 &maxVoltage, __int32 &stepRate, __int32 &stepAcceleration)" />
	/// <seealso cref="KIM_SetDriveOPParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_DriveOPParameters &driveOPParameters)" />
	/// <seealso cref="KIM_GetDriveOPParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_DriveOPParameters &driveOPParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_SetDriveOPParameters(char const * serialNumber, KIM_Channels channel, __int16 maxVoltage, __int32 stepRate, __int32 stepAcceleration);

	/// <summary> Gets the operation drive parameters. </summary>
	/// <param name="serialNumber">		The device serial number. </param>
	/// <param name="channel">			The channel. </param>
	/// <param name="maxVoltage">		[out] The maximum voltage. </param>
	/// <param name="stepRate">			[out] The step rate. </param>
	/// <param name="stepAcceleration">	[out] The step acceleration. </param>
	/// <returns> The operation drive parameters. </returns>
	/// <seealso cref="KIM_RequestDriveOPParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetDriveOPParameters(char const * serialNumber, KIM_Channels channel, __int16 maxVoltage, __int32 stepRate, __int32 stepAcceleration)" />
	/// <seealso cref="KIM_SetDriveOPParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_DriveOPParameters &driveOPParameters)" />
	/// <seealso cref="KIM_GetDriveOPParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_DriveOPParameters &driveOPParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_GetDriveOPParameters(char const * serialNumber, KIM_Channels channel, __int16 &maxVoltage, __int32 &stepRate, __int32 &stepAcceleration);

	/// <summary> Sets the operation drive parameters. </summary>
	/// <param name="serialNumber">			The device serial number. </param>
	/// <param name="channel">				The channel. </param>
	/// <param name="driveOPParameters">	Options for controlling the drive operation. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestDriveOPParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetDriveOPParameters(char const * serialNumber, KIM_Channels channel, __int16 maxVoltage, __int32 stepRate, __int32 stepAcceleration)" />
	/// <seealso cref="KIM_GetDriveOPParameters(char const * serialNumber, KIM_Channels channel, __int16 &maxVoltage, __int32 &stepRate, __int32 &stepAcceleration)" />
	/// <seealso cref="KIM_GetDriveOPParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_DriveOPParameters &driveOPParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_SetDriveOPParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_DriveOPParameters &driveOPParameters);

	/// <summary> Gets the operation drive parameters. </summary>
	/// <param name="serialNumber">			The device serial number. </param>
	/// <param name="channel">				The channel. </param>
	/// <param name="driveOPParameters">	Options for controlling the drive operation. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestDriveOPParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetDriveOPParameters(char const * serialNumber, KIM_Channels channel, __int16 maxVoltage, __int32 stepRate, __int32 stepAcceleration)" />
	/// <seealso cref="KIM_GetDriveOPParameters(char const * serialNumber, KIM_Channels channel, __int16 &maxVoltage, __int32 &stepRate, __int32 &stepAcceleration)" />
	/// <seealso cref="KIM_SetDriveOPParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_DriveOPParameters &driveOPParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_GetDriveOPParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_DriveOPParameters &driveOPParameters);

	/// <summary> Requests the jog parameters. </summary>
	/// <param name="serialNumber">	The serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_SetJogParameters(char const * serialNumber, KIM_Channels channel, KIM_JogMode jogMode, __int32 jogStepSizeFwd, __int32 jogStepSizeRev, __int32 jogStepRate, __int32 jogStepAcceleration)" />
	/// <seealso cref="KIM_GetJogParameters(char const * serialNumber, KIM_Channels channel, KIM_JogMode &jogMode, __int32 &jogStepSizeFwd, __int32 &jogStepSizeRev, __int32 &jogStepRate, __int32 &jogStepAcceleration)" />
	/// <seealso cref="KIM_SetJogParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_JogParameters &jogParameters)" />
	/// <seealso cref="KIM_GetJogParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_JogParameters &jogParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_RequestJogParameters(char const * serialNumber, KIM_Channels channel);

	/// <summary>	Sets the jog parameters. </summary>
	/// <param name="serialNumber">			The device serial number. </param>
	/// <param name="channel">				The channel. </param>
	/// <param name="jogMode">				The jog mode. </param>
	/// <param name="jogStepSizeFwd">		Size of the jog step. </param>
	/// <param name="jogStepSizeRev">		The jog step size reverse. </param>
	/// <param name="jogStepRate">			The jog step rate. </param>
	/// <param name="jogStepAcceleration">	The jog step acceleration. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestJogParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_GetJogParameters(char const * serialNumber, KIM_Channels channel, KIM_JogMode &jogMode, __int32 &jogStepSizeFwd, __int32 &jogStepSizeRev, __int32 &jogStepRate, __int32 &jogStepAcceleration)" />
	/// <seealso cref="KIM_SetJogParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_JogParameters &jogParameters)" />
	/// <seealso cref="KIM_GetJogParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_JogParameters &jogParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_SetJogParameters(char const * serialNumber, KIM_Channels channel, KIM_JogMode jogMode, __int32 jogStepSizeFwd, __int32 jogStepSizeRev, __int32 jogStepRate, __int32 jogStepAcceleration);

	/// <summary>	Gets the jog parameters. </summary>
	/// <param name="serialNumber">			The device serial number. </param>
	/// <param name="channel">				The channel. </param>
	/// <param name="jogMode">				[out] The jog mode. </param>
	/// <param name="jogStepSizeFwd">		[out] Size of the jog step. </param>
	/// <param name="jogStepSizeRev">		[out] The jog step size reverse. </param>
	/// <param name="jogStepRate">			[out] The jog step rate. </param>
	/// <param name="jogStepAcceleration">	[out] The jog step acceleration. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestJogParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetJogParameters(char const * serialNumber, KIM_Channels channel, KIM_JogMode jogMode, __int32 jogStepSizeFwd, __int32 jogStepSizeRev, __int32 jogStepRate, __int32 jogStepAcceleration)" />
	/// <seealso cref="KIM_SetJogParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_JogParameters &jogParameters)" />
	/// <seealso cref="KIM_GetJogParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_JogParameters &jogParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_GetJogParameters(char const * serialNumber, KIM_Channels channel, KIM_JogMode &jogMode, __int32 &jogStepSizeFwd, __int32 &jogStepSizeRev, __int32 &jogStepRate, __int32 &jogStepAcceleration);

	/// <summary> Sets the jog parameters. </summary>
	/// <param name="serialNumber">		The device serial number. </param>
	/// <param name="channel">			 The channel. </param>
	/// <param name="jogParameters">	Options for controlling the drive operation. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestJogParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetJogParameters(char const * serialNumber, KIM_Channels channel, KIM_JogMode jogMode, __int32 jogStepSizeFwd, __int32 jogStepSizeRev, __int32 jogStepRate, __int32 jogStepAcceleration)" />
	/// <seealso cref="KIM_GetJogParameters(char const * serialNumber, KIM_Channels channel, KIM_JogMode &jogMode, __int32 &jogStepSizeFwd, __int32 &jogStepSizeRev, __int32 &jogStepRate, __int32 &jogStepAcceleration)" />
	/// <seealso cref="KIM_GetJogParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_JogParameters &jogParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_SetJogParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_JogParameters &jogParameters);

	/// <summary> Gets the jog parameters. </summary>
	/// <param name="serialNumber">		The device serial number. </param>
	/// <param name="channel">			The channel. </param>
	/// <param name="jogParameters">	Options for controlling the drive operation. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestJogParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetJogParameters(char const * serialNumber, KIM_Channels channel, KIM_JogMode jogMode, __int32 jogStepSizeFwd, __int32 jogStepSizeRev, __int32 jogStepRate, __int32 jogStepAcceleration)" />
	/// <seealso cref="KIM_GetJogParameters(char const * serialNumber, KIM_Channels channel, KIM_JogMode &jogMode, __int32 &jogStepSizeFwd, __int32 &jogStepSizeRev, __int32 &jogStepRate, __int32 &jogStepAcceleration)" />
	/// <seealso cref="KIM_SetJogParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_JogParameters &jogParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_GetJogParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_JogParameters &jogParameters);

	/// <summary>	Gets a limit switch parameters. </summary>
	/// <param name="serialNumber">	The serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <param name="forwardLimit">	[out] The forward limit switch configuration. </param>
	/// <param name="reverseLimit">	[out] The reverse limit switch configuration. </param>
	/// <param name="stageID">		[out] Identifier for the stage type. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestLimitSwitchParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetLimitSwitchParameters(char const * serialNumber, KIM_Channels channel, KIM_LimitSwitchModes forwardLimit, KIM_LimitSwitchModes reverseLimit, __int16 stageID)" />
	/// <seealso cref="KIM_GetLimitSwitchParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_LimitSwitchParameters& limitSwitchParameters)" />
	/// <seealso cref="KIM_SetLimitSwitchParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_LimitSwitchParameters& limitSwitchParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_GetLimitSwitchParameters(char const * serialNumber, KIM_Channels channel, KIM_LimitSwitchModes &forwardLimit, KIM_LimitSwitchModes &reverseLimit, __int16 &stageID);

	/// <summary>	Sets the limit switch parameters. </summary>
	/// <param name="serialNumber">	The serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <param name="forwardLimit">	The forward limit switch configuration. </param>
	/// <param name="reverseLimit">	The reverse limit switch configuration. </param>
	/// <param name="stageID">		Identifier for the stage. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestLimitSwitchParameters(char const * serialNumber, KIM_Channels channel)"/>
	/// <seealso cref="KIM_GetLimitSwitchParameters(char const * serialNumber, KIM_Channels channel, KIM_LimitSwitchModes &forwardLimit, KIM_LimitSwitchModes &reverseLimit, __int16 &stageID)"/>
	/// <seealso cref="KIM_GetLimitSwitchParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_LimitSwitchParameters& limitSwitchParameters)"/>
	/// <seealso cref="KIM_SetLimitSwitchParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_LimitSwitchParameters& limitSwitchParameters)"/>
	KCUBEINERTIALMOTOR_API short __cdecl KIM_SetLimitSwitchParameters(char const * serialNumber, KIM_Channels channel, KIM_LimitSwitchModes forwardLimit, KIM_LimitSwitchModes reverseLimit, __int16 stageID);

	/// <summary> Gets a limit switch parameters. </summary>
	/// <param name="serialNumber">				The serial number. </param>
	/// <param name="channel">					The channel. </param>
	/// <param name="limitSwitchParameters">	Options for controlling the limit switches. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestLimitSwitchParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetLimitSwitchParameters(char const * serialNumber, KIM_Channels channel, KIM_LimitSwitchModes forwardLimit, KIM_LimitSwitchModes reverseLimit, __int16 stageID)" />
	/// <seealso cref="KIM_GetLimitSwitchParameters(char const * serialNumber, KIM_Channels channel, KIM_LimitSwitchModes &forwardLimit, KIM_LimitSwitchModes &reverseLimit, __int16 &stageID)" />
	/// <seealso cref="KIM_SetLimitSwitchParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_LimitSwitchParameters& limitSwitchParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_GetLimitSwitchParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_LimitSwitchParameters& limitSwitchParameters);

	/// <summary> Sets the limit switch parameters. </summary>
	/// <param name="serialNumber">				The serial number. </param>
	/// <param name="channel">					The channel. </param>
	/// <param name="limitSwitchParameters">	Options for controlling the limit switch. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestLimitSwitchParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetLimitSwitchParameters(char const * serialNumber, KIM_Channels channel, KIM_LimitSwitchModes forwardLimit, KIM_LimitSwitchModes reverseLimit, __int16 stageID)" />
	/// <seealso cref="KIM_GetLimitSwitchParameters(char const * serialNumber, KIM_Channels channel, KIM_LimitSwitchModes &forwardLimit, KIM_LimitSwitchModes &reverseLimit, __int16 &stageID)" />
	/// <seealso cref="KIM_GetLimitSwitchParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_LimitSwitchParameters& limitSwitchParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_SetLimitSwitchParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_LimitSwitchParameters& limitSwitchParameters);

	/// <summary>	Request the limit switch parameters. </summary>
	/// <param name="serialNumber">	The serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_SetLimitSwitchParameters(char const * serialNumber, KIM_Channels channel, KIM_LimitSwitchModes forwardLimit, KIM_LimitSwitchModes reverseLimit, __int16 stageID)" />
	/// <seealso cref="KIM_GetLimitSwitchParameters(char const * serialNumber, KIM_Channels channel, KIM_LimitSwitchModes &forwardLimit, KIM_LimitSwitchModes &reverseLimit, __int16 &stageID)" />
	/// <seealso cref="KIM_GetLimitSwitchParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_LimitSwitchParameters& limitSwitchParameters)" />
	/// <seealso cref="KIM_SetLimitSwitchParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_LimitSwitchParameters& limitSwitchParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_RequestLimitSwitchParameters(char const * serialNumber, KIM_Channels channel);

	/// <summary>	Gets a home parameters. </summary>
	/// <param name="serialNumber">		The serial number. </param>
	/// <param name="channel">			The channel. </param>
	/// <param name="homeDirection">	[out] The home direction. </param>
	/// <param name="homeLimitSwitch">	[out] The home limit switch. </param>
	/// <param name="homeStepRate">		[out] The home step rate. </param>
	/// <param name="homeOffset">		[out] The home offset. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestHomeParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetHomeParameters(char const * serialNumber, KIM_Channels channel, KIM_TravelDirection homeDirection, KIM_TravelDirection homeLimitSwitch, __int32 homeStepRate, __int32 homeOffset)" />
	/// <seealso cref="KIM_GetHomeParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_HomeParameters& homeParameters)" />
	/// <seealso cref="KIM_SetHomeParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_HomeParameters& homeParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_GetHomeParameters(char const * serialNumber, KIM_Channels channel, KIM_TravelDirection &homeDirection, KIM_TravelDirection &homeLimitSwitch, __int32 &homeStepRate, __int32 &homeOffset);

	/// <summary>	Sets the home parameters. </summary>
	/// <param name="serialNumber">		The serial number. </param>
	/// <param name="channel">			The channel. </param>
	/// <param name="homeDirection">	Options for controlling the home. </param>
	/// <param name="homeLimitSwitch">	The home limit switch. </param>
	/// <param name="homeStepRate">		The home step rate. </param>
	/// <param name="homeOffset">		The home offset. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestHomeParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_GetHomeParameters(char const * serialNumber, KIM_Channels channel, KIM_TravelDirection &homeDirection, KIM_TravelDirection &homeLimitSwitch, __int32 &homeStepRate, __int32 &homeOffset)" />
	/// <seealso cref="KIM_GetHomeParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_HomeParameters& homeParameters)" />
	/// <seealso cref="KIM_SetHomeParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_HomeParameters& homeParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_SetHomeParameters(char const * serialNumber, KIM_Channels channel, KIM_TravelDirection homeDirection, KIM_TravelDirection homeLimitSwitch, __int32 homeStepRate, __int32 homeOffset);

	/// <summary> Gets a home parameters. </summary>
	/// <param name="serialNumber">		The serial number. </param>
	/// <param name="channel">			The channel. </param>
	/// <param name="homeParameters">	Options for controlling the home. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestHomeParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetHomeParameters(char const * serialNumber, KIM_Channels channel, KIM_TravelDirection homeDirection, KIM_TravelDirection homeLimitSwitch, __int32 homeStepRate, __int32 homeOffset)" />
	/// <seealso cref="KIM_GetHomeParameters(char const * serialNumber, KIM_Channels channel, KIM_TravelDirection &homeDirection, KIM_TravelDirection &homeLimitSwitch, __int32 &homeStepRate, __int32 &homeOffset)" />
	/// <seealso cref="KIM_SetHomeParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_HomeParameters& homeParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_GetHomeParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_HomeParameters& homeParameters);

	/// <summary> Sets the home parameters. </summary>
	/// <param name="serialNumber">		The serial number. </param>
	/// <param name="channel">			The channel. </param>
	/// <param name="homeParameters">	Options for controlling the home. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestHomeParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetHomeParameters(char const * serialNumber, KIM_Channels channel, KIM_TravelDirection homeDirection, KIM_TravelDirection homeLimitSwitch, __int32 homeStepRate, __int32 homeOffset)" />
	/// <seealso cref="KIM_GetHomeParameters(char const * serialNumber, KIM_Channels channel, KIM_TravelDirection &homeDirection, KIM_TravelDirection &homeLimitSwitch, __int32 &homeStepRate, __int32 &homeOffset)" />
	/// <seealso cref="KIM_GetHomeParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_HomeParameters& homeParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_SetHomeParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_HomeParameters& homeParameters);

	/// <summary>	Request the home parameters. </summary>
	/// <param name="serialNumber">	The serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_SetHomeParameters(char const * serialNumber, KIM_Channels channel, KIM_TravelDirection homeDirection, KIM_TravelDirection homeLimitSwitch, __int32 homeStepRate, __int32 homeOffset)" />
	/// <seealso cref="KIM_GetHomeParameters(char const * serialNumber, KIM_Channels channel, KIM_TravelDirection &homeDirection, KIM_TravelDirection &homeLimitSwitch, __int32 &homeStepRate, __int32 &homeOffset)" />
	/// <seealso cref="KIM_GetHomeParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_HomeParameters& homeParameters)" />
	/// <seealso cref="KIM_SetHomeParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_HomeParameters& homeParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_RequestHomeParameters(char const * serialNumber, KIM_Channels channel);

	/// <summary>	Gets a mmi parameters. </summary>
	/// <param name="serialNumber">		The serial number. </param>
	/// <param name="channel">			The channel. </param>
	/// <param name="joystickMode">		[out] The joystick mode. </param>
	/// <param name="maxStepRate">		[out] The maximum step rate. </param>
	/// <param name="directionSense">	[out] The direction sense. </param>
	/// <param name="displayIntensity">	[out] The display intensity. </param>
	/// <param name="presetPos1">		[out] The first preset position. </param>
	/// <param name="presetPos2">		[out] The second preset position. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestMMIParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetMMIDeviceParameters(char const * serialNumber, KIM_JoysticModes joystickMode, __int32 maxStepRate, KIM_DirectionSense directionSense, __int16 displayIntensity)" />
	/// <seealso cref="KIM_GetMMIDeviceParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_MMIParameters& mmiParameters)" />
	/// <seealso cref="KIM_SetMMIDeviceParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_MMIParameters& mmiParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_GetMMIDeviceParameters(char const * serialNumber, KIM_Channels channel, KIM_JoysticModes &joystickMode, __int32 &maxStepRate, KIM_DirectionSense &directionSense, __int32 &presetPos1, __int32 &presetPos2, __int32 &displayIntensity);

	/// <summary>	Gets a mmi parameters. </summary>
	/// <param name="serialNumber">		The serial number. </param>
	/// <param name="channel">			The channel. </param>
	/// <param name="presetPos1">		[out] The first preset position. </param>
	/// <param name="presetPos2">		[out] The second preset position. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestMMIParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetMMIChannelParameters(char const * serialNumber, KIM_Channels channel, __int32 presetPos1, __int32 presetPos2)" />
	/// <seealso cref="KIM_GetMMIChannelParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_MMIChannelParameters& mmiParameters)" />
	/// <seealso cref="KIM_SetMMIChannelParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_MMIChannelParameters& mmiParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_GetMMIChannelParameters(char const * serialNumber, KIM_Channels channel, __int32 &presetPos1, __int32 &presetPos2);

	/// <summary>	Sets the mmi parameters. </summary>
	/// <param name="serialNumber">		The serial number. </param>
	/// <param name="joystickMode">		The joystick mode. </param>
	/// <param name="maxStepRate">		The maximum step rate. </param>
	/// <param name="directionSense">	The direction sense. </param>
	/// <param name="displayIntensity">	The display intensity. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestMMIParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_GetMMIDeviceParameters(char const * serialNumber, KIM_JoysticModes &joystickMode, __int32 &maxStepRate, KIM_DirectionSense &directionSense, __int32 &displayIntensity)" />
	/// <seealso cref="KIM_GetMMIDeviceParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_MMIParameters& mmiParameters)" />
	/// <seealso cref="KIM_SetMMIDeviceParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_MMIParameters& mmiParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_SetMMIDeviceParameters(char const * serialNumber, KIM_JoysticModes joystickMode, __int32 maxStepRate, KIM_DirectionSense directionSense, __int16 displayIntensity);

	/// <summary>	Sets the mmi parameters. </summary>
	/// <param name="serialNumber">		The serial number. </param>
	/// <param name="channel">			The channel. </param>
	/// <param name="presetPos1">		The first preset position. </param>
	/// <param name="presetPos2">		The second preset position. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestMMIParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_GetMMIChannelParameters(char const * serialNumber, KIM_Channels channel, __int32 &presetPos1, __int32 &presetPos2)" />
	/// <seealso cref="KIM_GetMMIChannelParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_MMIChannelParameters& mmiParameters)" />
	/// <seealso cref="KIM_SetMMIChannelParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_MMIChannelParameters& mmiParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_SetMMIChannelParameters(char const * serialNumber, KIM_Channels channel, __int32 presetPos1, __int32 presetPos2);

	/// <summary> Gets a mmi parameters. </summary>
	/// <param name="serialNumber">		The serial number. </param>
	/// <param name="mmiParameters">	Options for controlling the mmi. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestMMIParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetMMIParameters(char const * serialNumber, KIM_Channels channel, KIM_JoysticModes joystickMode, __int32 maxStepRate, KIM_DirectionSense directionSense, __int32 presetPos1, __int32 presetPos2, __int16 displayIntensity)" />
	/// <seealso cref="KIM_GetMMIParameters(char const * serialNumber, KIM_Channels channel, KIM_JoysticModes &joystickMode, __int32 &maxStepRate, KIM_DirectionSense &directionSense, __int32 &presetPos1, __int32 &presetPos2, __int32 &displayIntensity)" />
	/// <seealso cref="KIM_SetMMIParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_MMIParametersInternal& mmiParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_GetMMIDeviceParametersStruct(char const * serialNumber, KIM_MMIParameters& mmiParameters);

	/// <summary> Gets a mmi parameters. </summary>
	/// <param name="serialNumber">		The serial number. </param>
	/// <param name="channel">			The channel. </param>
	/// <param name="mmiParameters">	Options for controlling the mmi. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestMMIParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetMMIParameters(char const * serialNumber, KIM_Channels channel, KIM_JoysticModes joystickMode, __int32 maxStepRate, KIM_DirectionSense directionSense, __int32 presetPos1, __int32 presetPos2, __int16 displayIntensity)" />
	/// <seealso cref="KIM_GetMMIParameters(char const * serialNumber, KIM_Channels channel, KIM_JoysticModes &joystickMode, __int32 &maxStepRate, KIM_DirectionSense &directionSense, __int32 &presetPos1, __int32 &presetPos2, __int32 &displayIntensity)" />
	/// <seealso cref="KIM_SetMMIParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_MMIParametersInternal& mmiParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_GetMMIChannelParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_MMIChannelParameters& mmiParameters);

	/// <summary> Sets the mmi parameters. </summary>
	/// <param name="serialNumber">		The serial number. </param>
	/// <param name="mmiParameters">	Options for controlling the mmi. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestMMIParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetMMIParameters(char const * serialNumber, KIM_Channels channel, KIM_JoysticModes joystickMode, __int32 maxStepRate, KIM_DirectionSense directionSense, __int32 presetPos1, __int32 presetPos2, __int16 displayIntensity)" />
	/// <seealso cref="KIM_GetMMIParameters(char const * serialNumber, KIM_Channels channel, KIM_JoysticModes &joystickMode, __int32 &maxStepRate, KIM_DirectionSense &directionSense, __int32 &presetPos1, __int32 &presetPos2, __int32 &displayIntensity)" />
	/// <seealso cref="KIM_GetMMIParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_MMIParametersInternal& mmiParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_SetMMIDeviceParametersStruct(char const * serialNumber, KIM_MMIParameters& mmiParameters);

	/// <summary> Sets the mmi parameters. </summary>
	/// <param name="serialNumber">		The serial number. </param>
	/// <param name="channel">			The channel. </param>
	/// <param name="mmiParameters">	Options for controlling the mmi. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestMMIParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetMMIParameters(char const * serialNumber, KIM_Channels channel, KIM_JoysticModes joystickMode, __int32 maxStepRate, KIM_DirectionSense directionSense, __int32 presetPos1, __int32 presetPos2, __int16 displayIntensity)" />
	/// <seealso cref="KIM_GetMMIParameters(char const * serialNumber, KIM_Channels channel, KIM_JoysticModes &joystickMode, __int32 &maxStepRate, KIM_DirectionSense &directionSense, __int32 &presetPos1, __int32 &presetPos2, __int32 &displayIntensity)" />
	/// <seealso cref="KIM_GetMMIParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_MMIParametersInternal& mmiParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_SetMMIChannelParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_MMIChannelParameters& mmiParameters);

	/// <summary>	Request the mmi parameters. </summary>
	/// <param name="serialNumber">	The serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_SetMMIDeviceParameters(char const * serialNumber, KIM_JoysticModes joystickMode, __int32 maxStepRate, KIM_DirectionSense directionSense, __int16 displayIntensity)" />
	/// <seealso cref="KIM_GetMMIDeviceParameters(char const * serialNumber, KIM_JoysticModes &joystickMode, __int32 &maxStepRate, KIM_DirectionSense &directionSense, __int32 &displayIntensity)" />
	/// <seealso cref="KIM_GetMMIDeviceParametersStruct(char const * serialNumber, KIM_MMIParameters& mmiParameters)" />
	/// <seealso cref="KIM_SetMMIDeviceParametersStruct(char const * serialNumber, KIM_MMIParameters& mmiParameters)" />
	/// <seealso cref="KIM_SetMMIChannelParameters(char const * serialNumber, KIM_Channels channel, __int32 presetPos1, __int32 presetPos2)" />
	/// <seealso cref="KIM_GetMMIChannelParameters(char const * serialNumber, KIM_Channels channel, __int32 &presetPos1, __int32 &presetPos2)" />
	/// <seealso cref="KIM_GetMMIChannelParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_MMIChannelParameters& mmiParameters)" />
	/// <seealso cref="KIM_SetMMIChannelParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_MMIChannelParameters& mmiParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_RequestMMIParameters(char const * serialNumber, KIM_Channels channel);

	/// <summary>	Gets a trig IO parameters. </summary>
	/// <param name="serialNumber">		The serial number. </param>
	/// <param name="trig1Mode">		[out] The trig 1 mode. </param>
	/// <param name="trig1Polarity">	[out] The trig 1 polarity. </param>
	/// <param name="trigChannel1"> 	[out] The first trig channel. </param>
	/// <param name="trig2Mode">		[out] The trig 2 mode. </param>
	/// <param name="trig2Polarity">	[out] The trig 2 polarity. </param>
	/// <param name="trigChannel2"> 	[out] The second trig channel. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestTrigIOParameters(char const * serialNumber)" />
	/// <seealso cref="KIM_SetTrigIOParameters(char const * serialNumber, KIM_TrigModes trig1Mode, KIM_TrigPolarities trig1Polarity, KIM_Channels trigChannel1, KIM_TrigModes trig2Mode, KIM_TrigPolarities trig2Polarity, KIM_Channels trigChannel2)" />
	/// <seealso cref="KIM_GetTrigIOParametersStruct(char const * serialNumber, KIM_TrigIOConfig& trigIOParameters)" />
	/// <seealso cref="KIM_SetTrigIOParametersStruct(char const * serialNumber, KIM_TrigIOConfig& trigIOParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_GetTrigIOParameters(char const * serialNumber, KIM_TrigModes & trig1Mode, KIM_TrigPolarities & trig1Polarity, KIM_Channels & trigChannel1, KIM_TrigModes & trig2Mode, KIM_TrigPolarities & trig2Polarity, KIM_Channels & trigChannel2);

	/// <summary>	Sets the limit switch parameters. </summary>
	/// <param name="serialNumber">		The serial number. </param>
	/// <param name="trig1Mode">		The trig 1 mode. </param>
	/// <param name="trig1Polarity">	The trig 1 polarity. </param>
	/// <param name="trigChannel1"> 	The first trig channel. </param>
	/// <param name="trig2Mode">		The trig 2 mode. </param>
	/// <param name="trig2Polarity">	The trig 2 polarity. </param>
	/// <param name="trigChannel2"> 	The second trig channel. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestTrigIOParameters(char const * serialNumber)" />
	/// <seealso cref="KIM_GetTrigIOParameters(char const * serialNumber, KIM_TrigModes & trig1Mode, KIM_TrigPolarities & trig1Polarity, __int16 & trigChannel1, KIM_TrigModes & trig2Mode, KIM_TrigPolarities & trig2Polarity, __int16 & trigChannel2)" />
	/// <seealso cref="KIM_GetTrigIOParametersStruct(char const * serialNumber, KIM_TrigIOConfig& trigIOParameters)" />
	/// <seealso cref="KIM_SetTrigIOParametersStruct(char const * serialNumber, KIM_TrigIOConfig& trigIOParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_SetTrigIOParameters(char const * serialNumber, KIM_TrigModes trig1Mode, KIM_TrigPolarities trig1Polarity, KIM_Channels trigChannel1, KIM_TrigModes trig2Mode, KIM_TrigPolarities trig2Polarity, KIM_Channels trigChannel2);

	/// <summary> Gets a trig IO parameters. </summary>
	/// <param name="serialNumber">		The serial number. </param>
	/// <param name="trigIOParameters">	Options for controlling the trig IO. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestTrigIOParameters(char const * serialNumber)" />
	/// <seealso cref="KIM_SetTrigIOParameters(char const * serialNumber, KIM_TrigModes trig1Mode, KIM_TrigPolarities trig1Polarity, KIM_Channels trigChannel1, KIM_TrigModes trig2Mode, KIM_TrigPolarities trig2Polarity, KIM_Channels trigChannel2)" />
	/// <seealso cref="KIM_GetTrigIOParameters(char const * serialNumber, KIM_TrigModes & trig1Mode, KIM_TrigPolarities & trig1Polarity, KIM_Channels & trigChannel1, KIM_TrigModes & trig2Mode, KIM_TrigPolarities & trig2Polarity, KIM_Channels & trigChannel2)" />
	/// <seealso cref="KIM_SetTrigIOParametersStruct(char const * serialNumber, KIM_TrigIOConfig& trigIOParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_GetTrigIOParametersStruct(char const * serialNumber, KIM_TrigIOConfig& trigIOParameters);

	/// <summary> Sets the limit switch parameters. </summary>
	/// <param name="serialNumber">		The serial number. </param>
	/// <param name="trigIOParameters">	Options for controlling the trig IO. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestTrigIOParameters(char const * serialNumber)" />
	/// <seealso cref="KIM_SetTrigIOParameters(char const * serialNumber, KIM_TrigModes trig1Mode, KIM_TrigPolarities trig1Polarity, KIM_Channels trigChannel1, KIM_TrigModes trig2Mode, KIM_TrigPolarities trig2Polarity, KIM_Channels trigChannel2)" />
	/// <seealso cref="KIM_GetTrigIOParameters(char const * serialNumber, KIM_TrigModes & trig1Mode, KIM_TrigPolarities & trig1Polarity, KIM_Channels & trigChannel1, KIM_TrigModes & trig2Mode, KIM_TrigPolarities & trig2Polarity, KIM_Channels & trigChannel2)" />
	/// <seealso cref="KIM_GetTrigIOParametersStruct(char const * serialNumber, KIM_TrigIOConfig& trigIOParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_SetTrigIOParametersStruct(char const * serialNumber, KIM_TrigIOConfig& trigIOParameters);

	/// <summary>	Request the trig IO parameters. </summary>
	/// <param name="serialNumber">	The serial number. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_SetTrigIOParameters(char const * serialNumber, KIM_TrigModes trig1Mode, KIM_TrigPolarities trig1Polarity, KIM_Channels trigChannel1, KIM_TrigModes trig2Mode, KIM_TrigPolarities trig2Polarity, KIM_Channels trigChannel2)" />
	/// <seealso cref="KIM_GetTrigIOParameters(char const * serialNumber, KIM_TrigModes & trig1Mode, KIM_TrigPolarities & trig1Polarity, KIM_Channels & trigChannel1, KIM_TrigModes & trig2Mode, KIM_TrigPolarities & trig2Polarity, KIM_Channels & trigChannel2)" />
	/// <seealso cref="KIM_GetTrigIOParametersStruct(char const * serialNumber, KIM_TrigIOConfig& trigIOParameters)" />
	/// <seealso cref="KIM_SetTrigIOParametersStruct(char const * serialNumber, KIM_TrigIOConfig& trigIOParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_RequestTrigIOParameters(char const * serialNumber);

	/// <summary>	Gets a trigger parameters. </summary>
	/// <param name="serialNumber">			The serial number. </param>
	/// <param name="channel">				The channel. </param>
	/// <param name="startPosFwd">			[out] The start position forward. </param>
	/// <param name="intervalFwd">			[out] The interval forward. </param>
	/// <param name="numberOfPulsesFwd">	[out] Number of pulses forwards. </param>
	/// <param name="startPosRev">			[out] The start position reverse. </param>
	/// <param name="intervalRev">			[out] The interval reverse. </param>
	/// <param name="numberOfPulsesRev">	[out] Number of pulses reverses. </param>
	/// <param name="pulseWidth">			[out] Width of the pulse. </param>
	/// <param name="numberOfCycles">		[out] Number of cycles. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestTrigParamsParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetTrigParamsParameters(char const * serialNumber, KIM_Channels channel, KIM_TrigParamsParameters& trigParameters, __int32 startPosFwd, __int32 intervalFwd, __int32 numberOfPulsesFwd, __int32 startPosRev, __int32 intervalRev, __int32 numberOfPulsesRev, __int32 pulseWidth, __int32 numberOfCycles)" />
	/// <seealso cref="KIM_GetTrigParamsParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_TrigParamsParameters& trigParameters)" />
	/// <seealso cref="KIM_SetTrigParamsParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_TrigParamsParameters& trigParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_GetTrigParamsParameters(char const * serialNumber, KIM_Channels channel, __int32 & startPosFwd, __int32 & intervalFwd, __int32 & numberOfPulsesFwd, __int32 & startPosRev, __int32 & intervalRev, __int32 & numberOfPulsesRev, __int32 & pulseWidth, __int32 & numberOfCycles);

	/// <summary>	Sets the trigger parameters. </summary>
	/// <param name="serialNumber">			The serial number. </param>
	/// <param name="channel">				The channel. </param>
	/// <param name="trigParameters">		The start position forward. </param>
	/// <param name="startPosFwd">			The start position forward. </param>
	/// <param name="intervalFwd">			The interval forward. </param>
	/// <param name="numberOfPulsesFwd">	Number of pulses forwards. </param>
	/// <param name="startPosRev">			The start position reverse. </param>
	/// <param name="intervalRev">			The interval reverse. </param>
	/// <param name="numberOfPulsesRev">	Number of pulses reverses. </param>
	/// <param name="pulseWidth">			Width of the pulse. </param>
	/// <param name="numberOfCycles">		Number of cycles. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestTrigParamsParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_GetTrigParamsParameters(char const * serialNumber, KIM_Channels channel, __int32 & startPosFwd, __int32 & intervalFwd, __int32 & numberOfPulsesFwd, __int32 & startPosRev, __int32 & intervalRev, __int32 & numberOfPulsesRev, __int32 & pulseWidth, __int32 & numberOfCycles)" />
	/// <seealso cref="KIM_GetTrigParamsParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_TrigParamsParameters& trigParameters)" />
	/// <seealso cref="KIM_SetTrigParamsParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_TrigParamsParameters& trigParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_SetTrigParamsParameters(char const * serialNumber, KIM_Channels channel, KIM_TrigParamsParameters& trigParameters, __int32 startPosFwd, __int32 intervalFwd, __int32 numberOfPulsesFwd, __int32 startPosRev, __int32 intervalRev, __int32 numberOfPulsesRev, __int32 pulseWidth, __int32 numberOfCycles);

	/// <summary> Gets a trigger parameters. </summary>
	/// <param name="serialNumber">		The serial number. </param>
	/// <param name="channel">			The channel. </param>
	/// <param name="trigParameters">	Options for controlling the trigger parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestTrigParamsParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetTrigParamsParameters(char const * serialNumber, KIM_Channels channel, KIM_TrigParamsParameters& trigParameters, __int32 startPosFwd, __int32 intervalFwd, __int32 numberOfPulsesFwd, __int32 startPosRev, __int32 intervalRev, __int32 numberOfPulsesRev, __int32 pulseWidth, __int32 numberOfCycles)" />
	/// <seealso cref="KIM_GetTrigParamsParameters(char const * serialNumber, KIM_Channels channel, __int32 & startPosFwd, __int32 & intervalFwd, __int32 & numberOfPulsesFwd, __int32 & startPosRev, __int32 & intervalRev, __int32 & numberOfPulsesRev, __int32 & pulseWidth, __int32 & numberOfCycles)" />
	/// <seealso cref="KIM_SetTrigParamsParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_TrigParamsParameters& trigParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_GetTrigParamsParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_TrigParamsParameters& trigParameters);

	/// <summary> Sets the trigger parameters. </summary>
	/// <param name="serialNumber">		The serial number. </param>
	/// <param name="channel">			The channel. </param>
	/// <param name="trigParameters">	Options for controlling the trigger parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestTrigParamsParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetTrigParamsParameters(char const * serialNumber, KIM_Channels channel, KIM_TrigParamsParameters& trigParameters, __int32 startPosFwd, __int32 intervalFwd, __int32 numberOfPulsesFwd, __int32 startPosRev, __int32 intervalRev, __int32 numberOfPulsesRev, __int32 pulseWidth, __int32 numberOfCycles)" />
	/// <seealso cref="KIM_GetTrigParamsParameters(char const * serialNumber, KIM_Channels channel, __int32 & startPosFwd, __int32 & intervalFwd, __int32 & numberOfPulsesFwd, __int32 & startPosRev, __int32 & intervalRev, __int32 & numberOfPulsesRev, __int32 & pulseWidth, __int32 & numberOfCycles)" />
	/// <seealso cref="KIM_GetTrigParamsParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_TrigParamsParameters& trigParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_SetTrigParamsParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_TrigParamsParameters& trigParameters);

	/// <summary>	Request the trigger parameters. </summary>
	/// <param name="serialNumber">	The serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_SetTrigParamsParameters(char const * serialNumber, KIM_Channels channel, KIM_TrigParamsParameters& trigParameters, __int32 startPosFwd, __int32 intervalFwd, __int32 numberOfPulsesFwd, __int32 startPosRev, __int32 intervalRev, __int32 numberOfPulsesRev, __int32 pulseWidth, __int32 numberOfCycles)" />
	/// <seealso cref="KIM_GetTrigParamsParameters(char const * serialNumber, KIM_Channels channel, __int32 & startPosFwd, __int32 & intervalFwd, __int32 & numberOfPulsesFwd, __int32 & startPosRev, __int32 & intervalRev, __int32 & numberOfPulsesRev, __int32 & pulseWidth, __int32 & numberOfCycles)" />
	/// <seealso cref="KIM_GetTrigParamsParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_TrigParamsParameters& trigParameters)" />
	/// <seealso cref="KIM_SetTrigParamsParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_TrigParamsParameters& trigParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_RequestTrigParamsParameters(char const * serialNumber, KIM_Channels channel);

	/// <summary>	Gets a feedback signal parameters. </summary>
	/// <param name="serialNumber">			The serial number. </param>
	/// <param name="channel">				The channel. </param>
	/// <param name="feedbackSignalMode">	[out] The feedback signal mode. </param>
	/// <param name="encoderConst">			[out] The encoder constant. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestFeedbackSigParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetFeedbackSigParameters(char const * serialNumber, KIM_Channels channel, KIM_FBSignalMode feedbackSignalMode, __int32 encoderConst)" />
	/// <seealso cref="KIM_SetFeedbackSigParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_FeedbackSigParams& fbSigParameters)" />
	/// <seealso cref="KIM_GetFeedbackSigParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_FeedbackSigParams& fbSigParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_GetFeedbackSigParameters(char const * serialNumber, KIM_Channels channel, KIM_FBSignalMode & feedbackSignalMode, __int32 & encoderConst);

	/// <summary>	Sets the feedback signal parameters. </summary>
	/// <param name="serialNumber">		 	The serial number. </param>
	/// <param name="channel">				The channel. </param>
	/// <param name="feedbackSignalMode">	The feedback signal mode. </param>
	/// <param name="encoderConst">			The encoder constant. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestFeedbackSigParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_GetFeedbackSigParameters(char const * serialNumber, KIM_Channels channel, KIM_FBSignalMode & feedbackSignalMode, __int32 & encoderConst)" />
	/// <seealso cref="KIM_SetFeedbackSigParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_FeedbackSigParams& fbSigParameters)" />
	/// <seealso cref="KIM_GetFeedbackSigParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_FeedbackSigParams& fbSigParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_SetFeedbackSigParameters(char const * serialNumber, KIM_Channels channel, KIM_FBSignalMode feedbackSignalMode, __int32 encoderConst);

	/// <summary> Gets a feedback signal parameters. </summary>
	/// <param name="serialNumber">		The serial number. </param>
	/// <param name="channel">			The channel. </param>
	/// <param name="fbSigParameters">	Options for controlling the feedback signal. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestFeedbackSigParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetFeedbackSigParameters(char const * serialNumber, KIM_Channels channel, KIM_FBSignalMode feedbackSignalMode, __int32 encoderConst)" />
	/// <seealso cref="KIM_GetFeedbackSigParameters(char const * serialNumber, KIM_Channels channel, KIM_FBSignalMode & feedbackSignalMode, __int32 & encoderConst)" />
	/// <seealso cref="KIM_SetFeedbackSigParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_FeedbackSigParams& fbSigParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_GetFeedbackSigParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_FeedbackSigParams& fbSigParameters);

	/// <summary> Sets the feedback signal parameters. </summary>
	/// <param name="serialNumber">		The serial number. </param>
	/// <param name="channel">			The channel. </param>
	/// <param name="fbSigParameters">	Options for controlling the feedback signal. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestFeedbackSigParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetFeedbackSigParameters(char const * serialNumber, KIM_Channels channel, KIM_FBSignalMode feedbackSignalMode, __int32 encoderConst)" />
	/// <seealso cref="KIM_GetFeedbackSigParameters(char const * serialNumber, KIM_Channels channel, KIM_FBSignalMode & feedbackSignalMode, __int32 & encoderConst)" />
	/// <seealso cref="KIM_GetFeedbackSigParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_FeedbackSigParams& fbSigParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_SetFeedbackSigParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_FeedbackSigParams& fbSigParameters);

	/// <summary>	Request the feedback signal parameters. </summary>
	/// <param name="serialNumber">	The serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_SetFeedbackSigParameters(char const * serialNumber, KIM_Channels channel, KIM_FBSignalMode feedbackSignalMode, __int32 encoderConst)" />
	/// <seealso cref="KIM_GetFeedbackSigParameters(char const * serialNumber, KIM_Channels channel, KIM_FBSignalMode & feedbackSignalMode, __int32 & encoderConst)" />
	/// <seealso cref="KIM_SetFeedbackSigParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_FeedbackSigParams& fbSigParameters)" />
	/// <seealso cref="KIM_GetFeedbackSigParametersStruct(char const * serialNumber, KIM_Channels channel, KIM_FeedbackSigParams& fbSigParameters)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_RequestFeedbackSigParameters(char const * serialNumber, KIM_Channels channel);

	/// <summary> Gets a relative move parameters. </summary>
	/// <param name="serialNumber">		The serial number. </param>
	/// <param name="channel">			The channel. </param>
	/// <param name="relativeMoveStep">	Options for controlling the relative move. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestRelativeMoveParameter(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetRelativeMoveParameter(char const * serialNumber, KIM_Channels channel, __int32& relativeMove)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_GetRelativeMoveParameter(char const * serialNumber, KIM_Channels channel, __int32& relativeMoveStep);

	/// <summary> Sets the relative move parameters. </summary>
	/// <param name="serialNumber">	The serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <param name="relativeMove">	Options for controlling the relative move. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestRelativeMoveParameter(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_GetRelativeMoveParameter(char const * serialNumber, KIM_Channels channel, __int32& relativeMoveStep)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_SetRelativeMoveParameter(char const * serialNumber, KIM_Channels channel, __int32& relativeMove);

	/// <summary>	Request the relative move parameters. </summary>
	/// <param name="serialNumber">	The serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_SetRelativeMoveParameter(char const * serialNumber, KIM_Channels channel, __int32& relativeMove)" />
	/// <seealso cref="KIM_GetRelativeMoveParameter(char const * serialNumber, KIM_Channels channel, __int32& relativeMoveStep)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_RequestRelativeMoveParameter(char const * serialNumber, KIM_Channels channel);

	/// <summary> Gets a absolute move parameters. </summary>
	/// <param name="serialNumber">	The serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <param name="absoluteMove">	Options for controlling the absolute move. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestAbsoluteMoveParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_SetAbsoluteMoveParameters(char const * serialNumber, KIM_Channels channel, __int32& absoluteMove)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_GetAbsoluteMoveParameters(char const * serialNumber, KIM_Channels channel, __int32& absoluteMove);

	/// <summary> Sets the absolute move parameters. </summary>
	/// <param name="serialNumber">	The serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <param name="absoluteMove">	Options for controlling the absolute move. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_RequestAbsoluteMoveParameters(char const * serialNumber, KIM_Channels channel)" />
	/// <seealso cref="KIM_GetAbsoluteMoveParameters(char const * serialNumber, KIM_Channels channel, __int32& absoluteMove)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_SetAbsoluteMoveParameters(char const * serialNumber, KIM_Channels channel, __int32& absoluteMove);

	/// <summary>	Request the absolute move parameters. </summary>
	/// <param name="serialNumber">	The serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_SetAbsoluteMoveParameters(char const * serialNumber, KIM_Channels channel, __int32& absoluteMove)" />
	/// <seealso cref="KIM_GetAbsoluteMoveParameters(char const * serialNumber, KIM_Channels channel, __int32& absoluteMove)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_RequestAbsoluteMoveParameters(char const * serialNumber, KIM_Channels channel);

	/// <summary> Requests the state quantities (actual temperature, current and status bits). </summary>
	/// <remarks> This needs to be called to get the device to send it's current status.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="KIM_StartPolling(char const * serialNumber, int milliseconds)" />. </remarks>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="KIM_RequestReadings(char const * serialNumber)" />
	/// <seealso cref="KIM_RequestStatusBits(char const * serialNumber)" />
	/// <seealso cref="KIM_GetCurrentReading(char const * serialNumber)" />
	/// <seealso cref="KIM_GetTemperatureReading(char const * serialNumber)" />
	/// <seealso cref="KIM_GetStatusBits(char const * serialNumber)" />
	/// <seealso cref="KIM_StartPolling(char const * serialNumber, int milliseconds)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_RequestStatus(char const * serialNumber);

	/// <summary> Request the status bits which identify the current device state. </summary>
	/// <remarks> This needs to be called to get the device to send it's current status bits.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="KIM_StartPolling(char const * serialNumber, int milliseconds)" />. </remarks>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="KIM_GetStatusBits(char const * serialNumber)" />
	/// <seealso cref="KIM_RequestStatus(char const * serialNumber)" />
	/// <seealso cref="KIM_RequestReadings(char const * serialNumber)" />
	/// <seealso cref="KIM_StartPolling(char const * serialNumber, int milliseconds)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_RequestStatusBits(char const * serialNumber);

	/// <summary> Requests the current position. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_GetCurrentPosition(char const * serialNumber, KIM_Channels channel)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_RequestCurrentPosition(char const * serialNumber, KIM_Channels channel);

	/// <summary> Gets current position. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <returns> The position. </returns>
	/// <seealso cref="KIM_RequestCurrentPosition(char const * serialNumber, KIM_Channels channel)" />
	KCUBEINERTIALMOTOR_API __int32 __cdecl KIM_GetCurrentPosition(char const * serialNumber, KIM_Channels channel);

	/// <summary> Tc get status bits. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <param name="channel">		The channel. </param>
	/// <returns> . </returns>
	KCUBEINERTIALMOTOR_API DWORD __cdecl KIM_GetStatusBits(char const * serialNumber, KIM_Channels channel);

	/// <summary> Determines whether the device supports Dual Channel Mode. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <returns> True if the device supports Dual Channel Mode, otherwise false. </returns>
	/// <seealso cref="KIM_IsDualChannelMode(char const * serialNumber)" />
	/// <seealso cref="KIM_SetDualChannelMode(char const * serialNumber, bool enableDualChannel)" />
	KCUBEINERTIALMOTOR_API bool __cdecl KIM_SupportsDualChannelMode(char const * serialNumber);

	/// <summary> Gets the Dual Channel Mode state. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <returns> True if the device is being used in Dual Channel Mode otherwise false. </returns>
	/// <seealso cref="KIM_SetDualChannelMode(char const * serialNumber, bool enableDualChannel)" />
	/// <seealso cref="KIM_SupportsDualChannelMode(char const * serialNumber)" />
	KCUBEINERTIALMOTOR_API bool __cdecl KIM_IsDualChannelMode(char const * serialNumber);

	/// <summary> Sets the Dual Channel Mode. </summary>
	/// <param name="serialNumber">			The device serial number. </param>
	/// <param name="enableDualChannel">	The dual channel mode state. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KIM_IsDualChannelMode(char const * serialNumber)" />
	/// <seealso cref="KIM_SupportsDualChannelMode(char const * serialNumber)" />
	KCUBEINERTIALMOTOR_API short __cdecl KIM_SetDualChannelMode(char const * serialNumber, bool enableDualChannel);

	/// <summary> Starts the internal polling loop which continuously requests position and status. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <param name="milliseconds">	The milliseconds polling rate. </param>
	/// <returns> True if successful, false if not. </returns>
	/// <seealso cref="KIM_StopPolling(char const * serialNumber)" />
	/// <seealso cref="KIM_PollingDuration(char const * serialNumber)" />
	/// <seealso cref="KIM_RequestStatusBits(char const * serialNumber)" />
	/// <seealso cref="KIM_RequestPosition(char const * serialNumber)" />
	/// \include CodeSnippet_connection1.cpp
	KCUBEINERTIALMOTOR_API bool __cdecl KIM_StartPolling(char const * serialNumber, int milliseconds);

	/// <summary> Gets the polling loop duration. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <returns> The time between polls in milliseconds or 0 if polling is not active. </returns>
	/// <seealso cref="KIM_StartPolling(char const * serialNumber, int milliseconds)" />
	/// <seealso cref="KIM_StopPolling(char const * serialNumber)" />
	/// \include CodeSnippet_connection1.cpp
	KCUBEINERTIALMOTOR_API long __cdecl KIM_PollingDuration(char const * serialNumber);

	/// <summary> Stops the internal polling loop. </summary>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <seealso cref="KIM_StartPolling(char const * serialNumber, int milliseconds)" />
	/// <seealso cref="KIM_PollingDuration(char const * serialNumber)" />
	/// \include CodeSnippet_connection1.cpp
	KCUBEINERTIALMOTOR_API void __cdecl KIM_StopPolling(char const * serialNumber);

	/// <summary> Gets the time in milliseconds since tha last message was received from the device. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNumber">		The device serial number. </param>
	/// <param name="lastUpdateTimeMS">	The time since the last message was received in milliseconds. </param>
	/// <returns> True if monitoring is enabled otherwize False. </returns>
	/// <seealso cref="KIM_EnableLastMsgTimer(char const * serialNumber, bool enable, __int32 lastMsgTimeout )" />
	/// <seealso cref="KIM_HasLastMsgTimerOverrun(char const * serialNumber)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	KCUBEINERTIALMOTOR_API bool __cdecl KIM_TimeSinceLastMsgReceived(char const * serialNumber, __int64 &lastUpdateTimeMS);

	/// <summary> Enables the last message monitoring timer. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNumber">		The device serial number. </param>
	/// <param name="enable">			True to enable monitoring otherwise False to disable. </param>
	/// <param name="lastMsgTimeout">	The last message error timeout in ms. 0 to disable. </param>
	/// <seealso cref="KIM_TimeSinceLastMsgReceived(char const * serialNumber, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="KIM_HasLastMsgTimerOverrun(char const * serialNumber)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	KCUBEINERTIALMOTOR_API void __cdecl KIM_EnableLastMsgTimer(char const * serialNumber, bool enable, __int32 lastMsgTimeout);

	/// <summary> Queries if the time since the last message has exceeded the lastMsgTimeout set by <see cref="KIM_EnableLastMsgTimer(char const * serialNumber, bool enable, __int32 lastMsgTimeout )"/>. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <returns> True if last message timer has elapsed, False if monitoring is not enabled or if time of last message received is less than lastMsgTimeout. </returns>
	/// <seealso cref="KIM_TimeSinceLastMsgReceived(char const * serialNumber, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="KIM_EnableLastMsgTimer(char const * serialNumber, bool enable, __int32 lastMsgTimeout )" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	KCUBEINERTIALMOTOR_API bool __cdecl KIM_HasLastMsgTimerOverrun(char const * serialNumber);

	/// <summary> Requests that all settings are download from device. </summary>
	/// <remarks> This function requests that the device upload all it's settings to the DLL.</remarks>
	/// <param name="serialNumber">	The device serial number. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	KCUBEINERTIALMOTOR_API short __cdecl KIM_RequestSettings(char const * serialNumber);
}
/** @} */ // KCubeInertialMotor
