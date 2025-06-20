// summary:	Declares the functions class
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the KCUBEPOSITIONALIGNER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// KCUBEPOSITIONALIGNER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#pragma once

#ifdef KCUBEPOSITIONALIGNERDLL_EXPORTS
#define KCUBEPOSITIONALIGNER_API __declspec(dllexport)
#else
#define KCUBEPOSITIONALIGNER_API __declspec(dllimport)
#endif

#include <OaIdl.h>
/** @defgroup KCubePositionAligner KCube PositionAligner
 *  This section details the Structures and Functions relavent to the  @ref KPA101_page "KCube PositionAligner or KCube Position Aligner"<br />
 *  For an example of how to connect to the device and perform simple operations use the following links:
 *  <list type=bullet>
 *    <item> \ref namespaces_kpa_ex_1 "Example of using the Thorlabs.MotionControl.KCube.PositionAligner.DLL from a C or C++ project."<br />
 *									  This requires the DLL to be dynamical linked. </item>
 *    <item> \ref namespaces_kpa_ex_2 "Example of using the Thorlabs.MotionControl.KCube.PositionAligner.DLL from a C# project"<br />
 *									  This uses Marshalling to load and access the C DLL. </item>
 *  </list>
 *  The Thorlabs.MotionControl.KCube.PositionAligner.DLL requires the following DLLs
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

	/// <summary> Values that represent the operating modes. </summary>
	typedef enum QD_OperatingMode : short
	{
		QD_ModeUndefined = 0,///<Undefined
		QD_Monitor = 1,///<Monitor only
		QD_OpenLoop = 2,///<Open loop mode
		QD_ClosedLoop = 3,///<Closed loop mode
		QD_AutoOpenClosedLoop = 4,///<Auto Open Closed Loop Mode
	} QD_OperatingMode;

	/// <summary> Values that represent low voltage output routing. </summary>
	typedef enum QD_LowVoltageRoute : short
	{
		QD_RouteUndefined = 0,///<Undefined
		QD_SMAOnly = 1,///<Output via SMA only
		QD_HubAndSMA = 2,///<Output via Hub and SMA
	} QD_LowVoltageRoute;

	/// <summary> Values that represent choice of value to hold at in open loop. </summary>
	typedef enum QD_OpenLoopHoldValues : short
	{
		QD_HoldOnZero = 1,///<Hold at zero volts
		QD_HoldOnLastValue = 2,///<Hold at the last Closed Loop position
	} QD_OpenLoopHoldValues;

	/// <summary> Filter enabled / disable states. </summary>
	typedef enum QD_FilterEnable : WORD
	{
		QD_Undefined = 0,///<Undefined
		QD_Enabled = 1,///<Filter enabled
		QD_Disabled = 2,///<Filter disabled
	} QD_FilterEnable;

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

	/// <summary> structure containing parameters in the feedback process. </summary>
	/// <value> The loop PID and filter parameters. </value>
	typedef struct QD_LoopParameters
	{
		/// <summary> The proportional gain term, range 0 to 10000. </summary>
		float proportionalGain;
		/// <summary> The integral gain term, range 0 to 10000. </summary>
		float integralGain;
		/// <summary> The derivative gain term, range 0 to 10000. </summary>
		/// <remarks> Kept as differentialGain rather than derivativeGain for backward compatibility</remarks>
		float differentialGain;
		/// <summary> The low pass filter cut off frequency, range 0 to 10000. </summary>
		/// <remarks>Not used by HW version &lt; 3</remarks>
		float lowPassFilterCutOffFreq;
		/// <summary> The notch filter center frequency, range 0 to 10000. </summary>
		/// <remarks>Not used by HW version &lt; 3</remarks>
		float notchFilterCenterFrequency;
		/// <summary> The notch filter q value, range 0.1 to 100. </summary>
		/// <remarks>Not used by HW version &lt; 3</remarks>
		float notchFilterQ;
		/// <summary> The notch filter enabled.
		/// 		  <list type=table>
		///				<item><term>Enabled</term><term>1</term></item>
		///				<item><term>Disabled</term><term>2</term></item>
		/// 		  </list> </summary>
		/// <remarks>Not used by HW version &lt; 3</remarks>
		QD_FilterEnable notchFilterEnabled;
		/// <summary> The low pass filter enabled.
		/// 		  <list type=table>
		///				<item><term>Enabled</term><term>1</term></item>
		///				<item><term>Disabled</term><term>2</term></item>
		/// 		  </list> </summary>
		/// <remarks>Not used by HW version &lt; 3</remarks>
		QD_FilterEnable lowPassFilterEnabled;
	} QD_LoopParameters;

	/// <summary> PositionAligner PID parameters. </summary>
	typedef struct QD_PIDParameters
	{
		/// <summary> The proportional gain term, range 0 to 10000. </summary>
		float proportionalGain;
		/// <summary> The integral gain term, range 0 to 10000. </summary>
		float integralGain;
		/// <summary> The derivative gain term, range 0 to 10000. </summary>
		/// <remarks> Kept as differentialGain rather than derivativeGain for backward compatibility</remarks>
		float differentialGain;
	} QD_PIDParameters;

	/// <summary> PositionAligner lowpassfilter parameters. </summary>
	/// <remarks>Not used by HW version &lt; 3</remarks>
	typedef struct QD_LowPassFilterParameters
	{
		/// <summary> The low pass filter cut off frequency, range 0 to 10000. </summary>
		/// <remarks>Not used by HW version &lt; 3</remarks>
		float lowPassFilterCutOffFreq;
		/// <summary> The low pass filter enabled.
		/// 		  <list type=table>
		///				<item><term>Enabled</term><term>1</term></item>
		///				<item><term>Disabled</term><term>2</term></item>
		/// 		  </list> </summary>
		/// <remarks>Not used by HW version &lt; 3</remarks>
		QD_FilterEnable lowPassFilterEnabled;
	} QD_LowPassFilterParameters;

	/// <summary> PositionAligner notchfilter parameters. </summary>
	/// <remarks>Not used by HW version &lt; 3</remarks>
	typedef struct QD_NotchFilterParameters
	{
		/// <summary> The notch filter center frequency, range 0 to 10000. </summary>
		/// <remarks>Not used by HW version &lt; 3</remarks>
		float notchFilterCenterFrequency;
		/// <summary> The notch filter q value, range 0.1 to 100. </summary>
		/// <remarks>Not used by HW version &lt; 3</remarks>
		float notchFilterQ;
		/// <summary> The notch filter enabled.
		/// 		  <list type=table>
		///				<item><term>Enabled</term><term>1</term></item>
		///				<item><term>Disabled</term><term>2</term></item>
		/// 		  </list> </summary>
		/// <remarks>Not used by HW version &lt; 3</remarks>
		QD_FilterEnable notchFilterEnabled;
	} QD_NotchFilterParameters;

	/// <summary> structure containing parameters to contol position demand output. </summary>
	/// <value> The position demand parameters. </value>
	typedef struct QD_PositionDemandParameters
	{
		/// <summary> Minimum X demand position, range -32768 to 32767 for -10V to +10V. </summary>
		__int16 minXdemand;
		/// <summary> Minimum Y demand position, range -32768 to 32767 for -10V to +10V. </summary>
		__int16 minYdemand;
		/// <summary> Maximum X demand position, range -32768 to 32767 for -10V to +10V. </summary>
		__int16 maxXdemand;
		/// <summary> Maximum Y demand position, range -32768 to 32767 for -10V to +10V. </summary>
		__int16 maxYdemand;
		/// <summary> The Low Voltage Output route.
		/// 		  <list type=table>
		///				<item><term>Output via SMA only</term><term>1</term></item>
		///				<item><term>Output via Hub and SMA</term><term>2</term></item>
		/// 		  </list> </summary>
		QD_LowVoltageRoute lowVoltageOutputRoute;
		/// <summary> The Open loop hold modes
		/// 		  <list type=table>
		///				<item><term>Hold at zero volts</term><term>1</term></item>
		///				<item><term>Hold at the last Closed Loop position</term><term>2</term></item>
		/// 		  </list> </summary>
		QD_OpenLoopHoldValues openLoopOption;
		/// <summary> The X direction Signal Gain Factor, range -32767 to +32767 with negative reversing sense of x axis demand signal with gain up to 1.0 . </summary>
		__int16 xFeedbackSignedGain;
		/// <summary> The Y direction Signal Gain Factor, range -32767 to +32767 with negative reversing sense of y axis demand signal with gain up to 1.0 . </summary>
		__int16 yFeedbackSignedGain;
	} QD_PositionDemandParameters;

	/// <summary> 2 Dimensional Position . </summary>
	typedef struct QD_Position
	{
		/// <summary> The horizontal component. </summary>
		__int16 x;
		/// <summary> The vertical component. </summary>
		__int16 y;
	} QD_Position;

	/// <summary> Structure holding position readings. </summary>
	typedef struct QD_Readings
	{
		/// <summary> Present x and y axis differences -32768 to 32767 for -10V to +10V. </summary>
		QD_Position posDifference;
		///  <summary> Present total of position signals 0 to 65535 for 0 to +10V. </summary>
		WORD sum;
		/// <summary> x and y values being output -32768 to 32767 for -10V to +10V. </summary>
		QD_Position demandedPos;
	} QD_Readings;

	/// <summary>	Values that represent qd kpa trig modes. </summary>
	typedef enum QD_KPA_TrigModes : WORD
	{
		/// <summary>	An enum constant representing the qd trig disabled option. </summary>
		QD_Trig_Disabled = 0x00,
		/// <summary>	An enum constant representing the qd trig in gpi option. </summary>
		QD_TrigIn_GPI = 0x01,
		/// <summary>	An enum constant representing the qd trig in loop open close option. </summary>
		QD_TrigIn_LoopOpenClose = 0x02,
		/// <summary>	An enum constant representing the gd trig out gpo option. </summary>
		KD_TrigOut_GPO = 0x0A,
		/// <summary>	An enum constant representing the gd trig out sum option. </summary>
		KD_TrigOut_Sum = 0x0B,
		/// <summary>	An enum constant representing the gd trig out difference option. </summary>
		KD_TrigOut_Diff = 0x0C,
		/// <summary>	An enum constant representing the gd trig out sum difference option. </summary>
		KD_TrigOut_SumDiff = 0x0D,
	} QD_KPA_TrigModes;

	/// <summary>	Values that represent qd kpa trig polarities. </summary>
	typedef enum QD_KPA_TrigPolarities : WORD
	{
		/// <summary>	An enum constant representing the gd trig high option. </summary>
		GD_Trig_High = 0x01,
		/// <summary>	An enum constant representing the gd trig low option. </summary>
		GD_Trig_Low = 0x02,
	} QD_KPA_TrigPolarities;

	/// <summary>	Structure holding the KCube KPA Trig IO Config. </summary>
	typedef struct QD_KPA_TrigIOConfig
	{
		/// <summary>	Trigger port 1 mode. </summary>
		QD_KPA_TrigModes trig1Mode;
		/// <summary>	Trigger port 1 polarity. </summary>
		QD_KPA_TrigPolarities trig1Polarity;

		/// <summary>	SUM window minimum value (0 to 100 -> 0% to 100% of FSD) </summary>
		WORD trig1SumMin;
		/// <summary>	SUM window maximum value (0 to 100 -> 0% to 100% of FSD) </summary>
		WORD trig1SumMax;

		/// <summary>	DIFF threshold value below which ouput trigger asserted (0 to 100 -> 0% to 100%
		/// 			of +ve and -ve FSD i.e. percentage deflection either side of zero) . </summary>
		WORD trig1DiffThreshold;

		/// <summary>	Trigger port 2 mode. </summary>
		QD_KPA_TrigModes trig2Mode;
		/// <summary>	Trigger port 2 polarity. </summary>
		QD_KPA_TrigPolarities trig2Polarity;

		/// <summary>	SUM window minimum value (0 to 100 -> 0% to 100% of FSD) </summary>
		WORD trig2SumMin;
		/// <summary>	SUM window maximum value (0 to 100 -> 0% to 100% of FSD) </summary>
		WORD trig2SumMax;

		/// <summary>	DIFF threshold value below which ouput trigger asserted (0 to 100 -> 0% to 100%
		/// 			of +ve and -ve FSD i.e. percentage deflection either side of zero) . </summary>
		WORD trig2DiffThreshold;

		/// <summary>	reserved fields. </summary>
		WORD wReserved[6];

	} QD_KPA_TrigIOConfig;

	/// <summary>	A qd kpa digital i/o. </summary>
	typedef struct QD_KPA_DigitalIO
	{
		/// <summary>	Digital output states (lowest two bits relating to the two trigger outputs on the
		/// 			KPA101). </summary>
		WORD wDigOPs;
		/// <summary>	reserved fields. </summary>
		WORD wReserved[6];
	} QD_KPA_DigitalIO;

	/// <summary> Position in system with 2 axes. </summary>
	/// <value> Pair of x and y coordinates. </value>
	typedef struct QD_ClosedLoopPosition
	{
		/// <summary> Horizontal component. </summary>
		__int16 x;
		/// <summary> Vertical component. </summary>
		__int16 y;
	} QD_ClosedLoopPosition;

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
	KCUBEPOSITIONALIGNER_API short __cdecl TLI_BuildDeviceList(void);

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
	KCUBEPOSITIONALIGNER_API short __cdecl TLI_GetDeviceListSize();

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
	KCUBEPOSITIONALIGNER_API short __cdecl TLI_GetDeviceList(SAFEARRAY** stringsReceiver);

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
	KCUBEPOSITIONALIGNER_API short __cdecl TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID);

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
	KCUBEPOSITIONALIGNER_API short __cdecl TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length);

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
	KCUBEPOSITIONALIGNER_API short __cdecl TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer);

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
	KCUBEPOSITIONALIGNER_API short __cdecl TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID);

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
	KCUBEPOSITIONALIGNER_API short __cdecl TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length);

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
	KCUBEPOSITIONALIGNER_API short __cdecl TLI_GetDeviceInfo(char const * serialNo, TLI_DeviceInfo *info);

	/// <summary> Initialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <remarks> Call TLI_InitializeSimulations before TLI_BuildDeviceList at the start of the program to make a connection to the simulation manager.<Br />
	/// 		  Any devices configured in the simulation manager will become visible TLI_BuildDeviceList is called and can be accessed using TLI_GetDeviceList.<Br />
	/// 		  Call TLI_InitializeSimulations at the end of the program to release the simulator.  </remarks>
	/// <seealso cref="TLI_UninitializeSimulations()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	KCUBEPOSITIONALIGNER_API void __cdecl TLI_InitializeSimulations();

	/// <summary> Uninitialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <seealso cref="TLI_InitializeSimulations()" />
	KCUBEPOSITIONALIGNER_API void __cdecl TLI_UninitializeSimulations();

	/// <summary> Open the device for communications. </summary>
	/// <param name="serialNo">	The serial no of the device to be connected. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="QD_Close(char const * serialNo)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_Open(char const * serialNo);

	/// <summary> Disconnect and close the device. </summary>
	/// <param name="serialNo">	The serial no of the device to be disconnected. </param>
    /// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="QD_Open(char const * serialNo)" />
	KCUBEPOSITIONALIGNER_API void __cdecl QD_Close(char const * serialNo);

	/// <summary>	Check connection. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> true if the USB is listed by the ftdi controller</returns>
	/// \include CodeSnippet_CheckConnection.cpp
	KCUBEPOSITIONALIGNER_API bool __cdecl QD_CheckConnection(char const * serialNo);

	/// <summary> Determine if the device front panel can be locked. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> True if we can lock the device front panel, false if not. </returns>
	/// <seealso cref="QD_GetFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="QD_RequestFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="QD_SetFrontPanelLock(char const * serialNo, bool locked)" />
	KCUBEPOSITIONALIGNER_API bool __cdecl QD_CanDeviceLockFrontPanel(char const * serialNo);

	/// <summary> Query if the device front panel locked. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> True if the device front panel is locked, false if not. </returns>
	/// <seealso cref="QD_CanDeviceLockFrontPanel(char const * serialNo)" />
	/// <seealso cref="QD_RequestFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="QD_SetFrontPanelLock(char const * serialNo, bool locked)" />
	KCUBEPOSITIONALIGNER_API bool __cdecl  QD_GetFrontPanelLocked(char const * serialNo);

	/// <summary> Ask the device if its front panel is locked. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_CanDeviceLockFrontPanel(char const * serialNo)" />
	/// <seealso cref="QD_GetFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="QD_SetFrontPanelLock(char const * serialNo, bool locked)" />
	KCUBEPOSITIONALIGNER_API short __cdecl  QD_RequestFrontPanelLocked(char const * serialNo);

	/// <summary> Sets the device front panel lock state. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="locked"> True to lock the device, false to unlock. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_CanDeviceLockFrontPanel(char const * serialNo)" />
	/// <seealso cref="QD_GetFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="QD_RequestFrontPanelLocked(char const * serialNo)" />
	KCUBEPOSITIONALIGNER_API short __cdecl  QD_SetFrontPanelLock(char const * serialNo, bool locked);

	/// <summary> Sends a command to the device to make it identify iteself. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	KCUBEPOSITIONALIGNER_API void __cdecl QD_Identify(char const * serialNo);

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
	KCUBEPOSITIONALIGNER_API short __cdecl QD_GetHardwareInfo(char const * serialNo, char * modelNo, DWORD sizeOfModelNo, WORD * type, WORD * numChannels, 
														char * notes, DWORD sizeOfNotes, DWORD * firmwareVersion, WORD * hardwareVersion, WORD * modificationState);

	/// <summary> Gets the hardware information in a block. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="hardwareInfo"> Address of a TLI_HardwareInformation structure to receive the hardware information. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	KCUBEPOSITIONALIGNER_API short __cdecl QD_GetHardwareInfoBlock(char const *serialNo, TLI_HardwareInformation *hardwareInfo);

	/// <summary> Gets version number of the device firmware. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device firmware version number made up of 4 byte parts. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	KCUBEPOSITIONALIGNER_API DWORD __cdecl QD_GetFirmwareVersion(char const * serialNo);

	/// <summary> Gets version number of the device software. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device software version number made up of 4 byte parts. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	KCUBEPOSITIONALIGNER_API DWORD __cdecl QD_GetSoftwareVersion(char const * serialNo);

	/// <summary> Update device with stored settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
    /// 		  \include CodeSnippet_connection1.cpp
	KCUBEPOSITIONALIGNER_API bool __cdecl QD_LoadSettings(char const * serialNo);

	/// <summary> Update device with named settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="settingsName"> Name of settings stored away from device. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	///             \include CodeSnippet_connection1.cpp
	KCUBEPOSITIONALIGNER_API bool __cdecl QD_LoadNamedSettings(char const * serialNo, char const *settingsName);

	/// <summary> persist the devices current settings. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	KCUBEPOSITIONALIGNER_API bool __cdecl QD_PersistSettings(char const * serialNo);

	/// <summary> Clears the device message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	KCUBEPOSITIONALIGNER_API void __cdecl QD_ClearMessageQueue(char const * serialNo);

	/// <summary> Registers a callback on the message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="functionPointer"> A function pointer to be called whenever messages are received. </param>
	/// <seealso cref="QD_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="QD_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="QD_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KCUBEPOSITIONALIGNER_API void __cdecl QD_RegisterMessageCallback(char const * serialNo, void (* functionPointer)());

	/// <summary> Gets the MessageQueue size. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> number of messages in the queue. </returns>
	/// <seealso cref="QD_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="QD_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="QD_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KCUBEPOSITIONALIGNER_API int __cdecl QD_MessageQueueSize(char const * serialNo);

	/// <summary> Get the next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="QD_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="QD_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="QD_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KCUBEPOSITIONALIGNER_API bool __cdecl QD_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Wait for next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="QD_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="QD_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="QD_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KCUBEPOSITIONALIGNER_API bool __cdecl QD_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Requests the feedback loop parameters. </summary>
	/// <remarks> NOTE This feature was added to the TPA101 device, hardware version &gt;= 3</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_GetLoopPIDparams(char const *serialNo, QD_LoopParameters *loopParams)" />
	/// <seealso cref="QD_SetLoopPIDparams(char const *serialNo, QD_LoopParameters *loopParams)" />
	/// <seealso cref="QD_SetPIDparams(char const *serialNo, QD_PIDParameters *proportionalIntegralDerivativeParams)" />
	/// <seealso cref="QD_GetPIDparams(char const *serialNo, QD_PIDParameters *proportionalIntegralDerivativeParams)" />
	/// <seealso cref="QD_GetLowPassFilterparams(char const *serialNo, QD_LowPassFilterParameters *lowPassParams)" />
	/// <seealso cref="QD_SetLowPassFilterparams(char const *serialNo, QD_LowPassFilterParameters *lowPassParams)" />
	/// <seealso cref="QD_SetNotchFilterparams(char const *serialNo, QD_NotchFilterParameters *proportionalIntegralDerivativeParams)" />
	/// <seealso cref="QD_GetNotchFilterparams(char const *serialNo, QD_NotchFilterParameters *notchParams)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_RequestLoopPIDparams(char const *serialNo);

	/// <summary> Gets the feedback loop parameters. </summary>
	/// <remarks> NOTE This feature was added to the TPA101 device, hardware version &gt;= 3</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="loopParams"> Address of the QD_LoopParameters to recieve the Feedback Loop Parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_SetLoopPIDparams(char const *serialNo, QD_LoopParameters *loopParams)" />
	/// <seealso cref="QD_SetPIDparams(char const *serialNo, QD_PIDParameters *proportionalIntegralDerivativeParams)" />
	/// <seealso cref="QD_GetPIDparams(char const *serialNo, QD_PIDParameters *proportionalIntegralDerivativeParams)" />
	/// <seealso cref="QD_GetLowPassFilterparams(char const *serialNo, QD_LowPassFilterParameters *lowPassParams)" />
	/// <seealso cref="QD_SetLowPassFilterparams(char const *serialNo, QD_LowPassFilterParameters *lowPassParams)" />
	/// <seealso cref="QD_SetNotchFilterparams(char const *serialNo, QD_NotchFilterParameters *proportionalIntegralDerivativeParams)" />
	/// <seealso cref="QD_GetNotchFilterparams(char const *serialNo, QD_NotchFilterParameters *notchParams)" />
	/// <seealso cref="QD_RequestLoopPIDparams(char const *serialNo)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_GetLoopPIDparams(char const *serialNo, QD_LoopParameters *loopParams);

	/// <summary> Sets the feedback loop parameters. </summary>
	/// <remarks> NOTE This feature was added to the TPA101 device, hardware version &gt;= 3</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="loopParams"> Address of the QD_LoopParameters containing the new Feedback Loop Parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_GetLoopPIDparams(char const *serialNo, QD_LoopParameters *loopParams)" />
	/// <seealso cref="QD_SetPIDparams(char const *serialNo, QD_PIDParameters *proportionalIntegralDerivativeParams)" />
	/// <seealso cref="QD_GetPIDparams(char const *serialNo, QD_PIDParameters *proportionalIntegralDerivativeParams)" />
	/// <seealso cref="QD_GetLowPassFilterparams(char const *serialNo, QD_LowPassFilterParameters *lowPassParams)" />
	/// <seealso cref="QD_SetLowPassFilterparams(char const *serialNo, QD_LowPassFilterParameters *lowPassParams)" />
	/// <seealso cref="QD_SetNotchFilterparams(char const *serialNo, QD_NotchFilterParameters *proportionalIntegralDerivativeParams)" />
	/// <seealso cref="QD_GetNotchFilterparams(char const *serialNo, QD_NotchFilterParameters *notchParams)" />
	/// <seealso cref="QD_RequestLoopPIDparams(char const *serialNo)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_SetLoopPIDparams(char const *serialNo, QD_LoopParameters *loopParams);

	/// <summary> Gets the feedback loop parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="proportionalIntegralDerivativeParams"> Address of the QD_PIDParameters to recieve the Feedback Loop Parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_SetPIDparams(char const *serialNo, QD_PIDParameters *proportionalIntegralDerivativeParams)" />
	/// <seealso cref="QD_SetLoopPIDparams(char const *serialNo, QD_LoopParameters *loopParams)" />
	/// <seealso cref="QD_GetLoopPIDparams(char const *serialNo, QD_LoopParameters *loopParams)" />
	/// <seealso cref="QD_GetLowPassFilterparams(char const *serialNo, QD_LowPassFilterParameters *lowPassParams)" />
	/// <seealso cref="QD_SetLowPassFilterparams(char const *serialNo, QD_LowPassFilterParameters *lowPassParams)" />
	/// <seealso cref="QD_SetNotchFilterparams(char const *serialNo, QD_NotchFilterParameters *proportionalIntegralDerivativeParams)" />
	/// <seealso cref="QD_GetNotchFilterparams(char const *serialNo, QD_NotchFilterParameters *notchParams)" />
	/// <seealso cref="QD_RequestLoopPIDparams(char const *serialNo)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_GetPIDparams(char const *serialNo, QD_PIDParameters *proportionalIntegralDerivativeParams);

	/// <summary> Sets the feedback loop parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="proportionalIntegralDerivativeParams"> Address of the QD_PIDParameters containing the new Feedback Loop Parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_GetPIDparams(char const *serialNo, QD_PIDParameters *proportionalIntegralDerivativeParams)" />
	/// <seealso cref="QD_GetLoopPIDparams(char const *serialNo, QD_LoopParameters *loopParams)" />
	/// <seealso cref="QD_SetLoopPIDparams(char const *serialNo, QD_LoopParameters *loopParams)" />
	/// <seealso cref="QD_GetLowPassFilterparams(char const *serialNo, QD_LowPassFilterParameters *lowPassParams)" />
	/// <seealso cref="QD_SetLowPassFilterparams(char const *serialNo, QD_LowPassFilterParameters *lowPassParams)" />
	/// <seealso cref="QD_SetNotchFilterparams(char const *serialNo, QD_NotchFilterParameters *proportionalIntegralDerivativeParams)" />
	/// <seealso cref="QD_GetNotchFilterparams(char const *serialNo, QD_NotchFilterParameters *notchParams)" />
	/// <seealso cref="QD_RequestLoopPIDparams(char const *serialNo)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_SetPIDparams(char const *serialNo, QD_PIDParameters *proportionalIntegralDerivativeParams);

	/// <summary> Gets the low pass filter parameters. </summary>
	/// <remarks> NOTE This feature was added to the TPA101 device, hardware version &gt;= 3</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="lowPassParams"> Address of the QD_LowPassFilterParameters to receive the Low Pass Filter Parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_SetLowPassFilterparams(char const *serialNo, QD_LowPassFilterParameters *lowPassParams)" />
	/// <seealso cref="QD_SetNotchFilterparams(char const *serialNo, QD_NotchFilterParameters *proportionalIntegralDerivativeParams)" />
	/// <seealso cref="QD_GetNotchFilterparams(char const *serialNo, QD_NotchFilterParameters *notchParams)" />
	/// <seealso cref="QD_GetLoopPIDparams(char const *serialNo, QD_LoopParameters *loopParams)" />
	/// <seealso cref="QD_SetLoopPIDparams(char const *serialNo, QD_LoopParameters *loopParams)" />
	/// <seealso cref="QD_SetPIDparams(char const *serialNo, QD_PIDParameters *proportionalIntegralDerivativeParams)" />
	/// <seealso cref="QD_GetPIDparams(char const *serialNo, QD_PIDParameters *proportionalIntegralDerivativeParams)" />
	/// <seealso cref="QD_RequestLoopPIDparams(char const *serialNo)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_GetLowPassFilterparams(char const *serialNo, QD_LowPassFilterParameters *lowPassParams);

	/// <summary> Sets the low pass filter parameters. </summary>
	/// <remarks> NOTE This feature was added to the TPA101 device, hardware version &gt;= 3</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="lowPassParams"> Address of the QD_LowPassFilterParameters containing the new Feedback Low Pass Filter Parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_GetLowPassFilterparams(char const *serialNo, QD_LowPassFilterParameters *lowPassParams)" />
	/// <seealso cref="QD_SetNotchFilterparams(char const *serialNo, QD_NotchFilterParameters *proportionalIntegralDerivativeParams)" />
	/// <seealso cref="QD_GetNotchFilterparams(char const *serialNo, QD_NotchFilterParameters *notchParams)" />
	/// <seealso cref="QD_GetLoopPIDparams(char const *serialNo, QD_LoopParameters *loopParams)" />
	/// <seealso cref="QD_SetLoopPIDparams(char const *serialNo, QD_LoopParameters *loopParams)" />
	/// <seealso cref="QD_SetPIDparams(char const *serialNo, QD_PIDParameters *proportionalIntegralDerivativeParams)" />
	/// <seealso cref="QD_GetPIDparams(char const *serialNo, QD_PIDParameters *proportionalIntegralDerivativeParams)" />
	/// <seealso cref="QD_RequestLoopPIDparams(char const *serialNo)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_SetLowPassFilterparams(char const *serialNo, QD_LowPassFilterParameters *lowPassParams);

	/// <summary> Gets the notch filter parameters. </summary>
	/// <remarks> NOTE This feature was added to the TPA101 device, hardware version &gt;= 3</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="notchParams"> Address of the QD_NotchFilterParameters to receive the Notch Filter Parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_SetNotchFilterparams(char const *serialNo, QD_NotchFilterParameters *proportionalIntegralDerivativeParams)" />
	/// <seealso cref="QD_GetLowPassFilterparams(char const *serialNo, QD_LowPassFilterParameters *lowPassParams)" />
	/// <seealso cref="QD_SetLowPassFilterparams(char const *serialNo, QD_LowPassFilterParameters *lowPassParams)" />
	/// <seealso cref="QD_GetLoopPIDparams(char const *serialNo, QD_LoopParameters *loopParams)" />
	/// <seealso cref="QD_SetLoopPIDparams(char const *serialNo, QD_LoopParameters *loopParams)" />
	/// <seealso cref="QD_SetPIDparams(char const *serialNo, QD_PIDParameters *proportionalIntegralDerivativeParams)" />
	/// <seealso cref="QD_GetPIDparams(char const *serialNo, QD_PIDParameters *proportionalIntegralDerivativeParams)" />
	/// <seealso cref="QD_RequestLoopPIDparams(char const *serialNo)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_GetNotchFilterparams(char const *serialNo, QD_NotchFilterParameters *notchParams);

	/// <summary> Sets the notch filter parameters. </summary>
	/// <remarks> NOTE This feature was added to the TPA101 device, hardware version &gt;= 3</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="proportionalIntegralDerivativeParams"> Address of the QD_NotchFilterParameters containing the new Feedback Notch Filter Parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_GetNotchFilterparams(char const *serialNo, QD_NotchFilterParameters *notchParams)" />
	/// <seealso cref="QD_GetLowPassFilterparams(char const *serialNo, QD_LowPassFilterParameters *lowPassParams)" />
	/// <seealso cref="QD_SetLowPassFilterparams(char const *serialNo, QD_LowPassFilterParameters *lowPassParams)" />
	/// <seealso cref="QD_GetLoopPIDparams(char const *serialNo, QD_LoopParameters *loopParams)" />
	/// <seealso cref="QD_SetLoopPIDparams(char const *serialNo, QD_LoopParameters *loopParams)" />
	/// <seealso cref="QD_SetPIDparams(char const *serialNo, QD_PIDParameters *proportionalIntegralDerivativeParams)" />
	/// <seealso cref="QD_GetPIDparams(char const *serialNo, QD_PIDParameters *proportionalIntegralDerivativeParams)" />
	/// <seealso cref="QD_RequestLoopPIDparams(char const *serialNo)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_SetNotchFilterparams(char const *serialNo, QD_NotchFilterParameters *proportionalIntegralDerivativeParams);

	/// <summary> Requests the position demand output parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_SetPosDemandParams(char const *serialNo, QD_PositionDemandParameters *demandParams)" />
	/// <seealso cref="QD_GetPosDemandParams(char const *serialNo, QD_PositionDemandParameters *demandParams)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_RequestPosDemandParams(char const *serialNo);

	/// <summary> Gets the position demand output parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="demandParams"> Address of the QD_PositionDemandParameters to receive the Position Demand Output parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_SetPosDemandParams(char const *serialNo, QD_PositionDemandParameters *demandParams)" />
	/// <seealso cref="QD_RequestPosDemandParams(char const *serialNo)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_GetPosDemandParams(char const *serialNo, QD_PositionDemandParameters *demandParams);

	/// <summary> Sets the position demand parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="demandParams"> Address of the QD_PositionDemandParameters containing the new Position Demand Output parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_GetPosDemandParams(char const *serialNo, QD_PositionDemandParameters *demandParams)" />
	/// <seealso cref="QD_RequestPosDemandParams(char const *serialNo)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_SetPosDemandParams(char const *serialNo, QD_PositionDemandParameters *demandParams);

	/// <summary> Requests the trigger config parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_GetTriggerConfigParams(char const *serialNo, QD_KPA_TrigIOConfig *triggerParams)" />
	/// <seealso cref="QD_SetTriggerConfigParams(char const *serialNo, QD_KPA_TrigIOConfig *triggerParams)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_RequestTriggerConfigParams(char const *serialNo);

	/// <summary> Gets the trigger config parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="triggerParams"> Address of the QD_KPA_TrigIOConfig to receive the trigger config parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_SetTriggerConfigParams(char const *serialNo, QD_KPA_TrigIOConfig *triggerParams)" />
	/// <seealso cref="QD_RequestTriggerConfigParams(char const *serialNo)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_GetTriggerConfigParams(char const *serialNo, QD_KPA_TrigIOConfig *triggerParams);

	/// <summary> Sets the trigger config parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="triggerParams"> Address of the QD_KPA_TrigIOConfig containing the new trigger config parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_GetTriggerConfigParams(char const *serialNo, QD_KPA_TrigIOConfig *triggerParams)" />
	/// <seealso cref="QD_RequestTriggerConfigParams(char const *serialNo)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_SetTriggerConfigParams(char const *serialNo, QD_KPA_TrigIOConfig *triggerParams);

	/// <summary> Requests the digital IO parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_GetDigitalOutput(char const *serialNo, QD_KPA_DigitalIO *demandParams)" />
	/// <seealso cref="QD_SetPosDemandParams(char const *serialNo, QD_KPA_DigitalIO *demandParams)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_RequestDigitalOutput(char const *serialNo);

	/// <summary> Gets the digital IO parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="digitalIO"> Address of the QD_KPA_DigitalIO to receive the digital IO parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_GetDigitalOutput(char const *serialNo, QD_KPA_DigitalIO *demandParams)" />
	/// <seealso cref="QD_RequestDigitalOutput(char const *serialNo)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_SetDigitalOutput(char const *serialNo, QD_KPA_DigitalIO *digitalIO);

	/// <summary> Sets the digital IO parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="digitalIO"> Address of the QD_KPA_DigitalIO containing the new digital IO parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_SetPosDemandParams(char const *serialNo, QD_KPA_DigitalIO *demandParams)" />
	/// <seealso cref="QD_RequestDigitalOutput(char const *serialNo)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_GetDigitalOutput(char const *serialNo, QD_KPA_DigitalIO *digitalIO);


	/// <summary> Requests the operating mode. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_SetOperatingMode(char const * serialNo, QD_OperatingMode mode, bool autoOpenCloseLoop)" />
	/// <seealso cref="QD_GetOperatingMode(char const * serialNo)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_RequestOperatingMode(char const * serialNo);

	/// <summary> Gets the operating mode. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The current operating mode.
	/// 		  <list type=table>
	///				<item><term>Monitoring only</term><term>1</term></item>
	///				<item><term>Open Loop Mode</term><term>2</term></item>
	///				<item><term>Closed Loop Mode</term><term>3</term></item>
	/// 		  </list> </returns>
	/// <seealso cref="QD_SetOperatingMode(char const * serialNo, QD_OperatingMode mode, bool autoOpenCloseLoop)" />
	/// <seealso cref="QD_RequestOperatingMode(char const * serialNo)" />
	KCUBEPOSITIONALIGNER_API QD_OperatingMode __cdecl QD_GetOperatingMode(char const * serialNo);

	/// <summary> Sets the operating mode. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="mode"> The current operating mode.
	/// 		  <list type=table>
	///				<item><term>Monitoring only</term><term>1</term></item>
	///				<item><term>Open Loop Mode</term><term>2</term></item>
	///				<item><term>Closed Loop Mode</term><term>3</term></item>
	/// 		  </list>  </param>
	/// <param name="autoOpenCloseLoop">A flag that if set will allow the KPA101 to automatically switch to Open Loop mode
	/// 								if it detects that the beam is blocked</param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_GetOperatingMode(char const * serialNo)" />
	/// <seealso cref="QD_RequestOperatingMode(char const * serialNo)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_SetOperatingMode(char const * serialNo, QD_OperatingMode mode, bool autoOpenCloseLoop);

	/// <summary> Requests the LED brightness. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_GetLEDBrightness(char const * serialNo)" />
	/// <seealso cref="QD_SetLEDBrightness(char const * serialNo, short brightness)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_RequestLEDBrightness(char const * serialNo);

	/// <summary> Gets the LED brightness. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> Intensity from 0 (off) to 255. </returns>
	/// <seealso cref="QD_SetLEDBrightness(char const * serialNo, short brightness)" />
	/// <seealso cref="QD_RequestLEDBrightness(char const * serialNo)" />
	KCUBEPOSITIONALIGNER_API WORD __cdecl QD_GetLEDBrightness(char const * serialNo);

	/// <summary> Sets the LED brightness. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="brightness"> Intensity from 0 (off) to 255. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_GetLEDBrightness(char const * serialNo)" />
	/// <seealso cref="QD_RequestLEDBrightness(char const * serialNo)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_SetLEDBrightness(char const * serialNo, short brightness);

	/// <summary> Gets position demand output. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="position"> Address of the QD_Position to receive the current Demanded Position. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_SetPosition(char const *serialNo, QD_Position *position)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_GetDemandedPosition(char const *serialNo, QD_Position *position);

	/// <summary> Sets position demand output. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="position"> Address of the QD_Position containing the new Demanded Position. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_GetDemandedPosition(char const *serialNo, QD_Position *position)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_SetPosition(char const *serialNo, QD_Position *position);

	/// <summary> Gets closed loop position. </summary>
	/// <remarks> Only available for device versions >= 2.0.2</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="position"> Address of the QD_Position containing the new Demanded Position. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_RequestClosedLoopPosition(char const *serialNo)" />
	/// <seealso cref="QD_SetClosedLoopPosition(char const *serialNo, QD_ClosedLoopPosition *position)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_GetClosedLoopPosition(char const *serialNo, QD_ClosedLoopPosition *position);

	/// <summary> Sets the closed loop position. </summary>
	/// <remarks> Only available for device versions >= 2.0.2</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="position"> Address of the QD_Position containing the new Demanded Position. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_RequestClosedLoopPosition(char const *serialNo)" />
	/// <seealso cref="QD_GetClosedLoopPosition(char const *serialNo, QD_ClosedLoopPosition *position)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_SetClosedLoopPosition(char const *serialNo, QD_ClosedLoopPosition *position);

	/// <summary> Request the closed loop position. </summary>
	/// <remarks> Only available for device versions >= 2.0.2</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_SetClosedLoopPosition(char const *serialNo, QD_ClosedLoopPosition *position)" />
	/// <seealso cref="QD_GetClosedLoopPosition(char const *serialNo, QD_ClosedLoopPosition *pos)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_RequestClosedLoopPosition(char const *serialNo);

	/// <summary> Requests the state quantities (actual power, current and status bits). </summary>
	/// <remarks> This needs to be called to get the device to send it's current status.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="QD_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="QD_RequestReading(char const * serialNo)" />
	/// <seealso cref="QD_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="QD_GetReading(char const *serialNo, QD_Readings *reading)" />
	/// <seealso cref="QD_GetStatusBits(char const * serialNo)" />
	/// <seealso cref="QD_StartPolling(char const * serialNo, int milliseconds)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_RequestStatus(char const * serialNo);

	/// <summary> Request reading. </summary>
	/// <remarks> This needs to be called to get the device to send it's current reading.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="QD_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="QD_GetReading(char const *serialNo, QD_Readings *reading)" />
	/// <seealso cref="QD_StartPolling(char const * serialNo, int milliseconds)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_RequestReading(char const * serialNo);

	/// <summary> Request the status bits which identify the current device state. </summary>
	/// <remarks> This needs to be called to get the device to send it's current status bits.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="QD_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="QD_GetStatusBits(char const * serialNo)" />
	/// <seealso cref="QD_StartPolling(char const * serialNo, int milliseconds)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_RequestStatusBits(char const * serialNo);

	/// <summary> Gets a reading. </summary>
	/// <remarks> This returns the latest reading received from the device.<br />
	/// 		  To get new readings, use <see cref="QD_RequestReading(char const * serialNo)" />
	///			  or use <see cref="QD_RequestStatus(char const * serialNo)" />
	/// 		  or use the polling functions, <see cref="QD_StartPolling(char const * serialNo, int milliseconds)" />.  </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="reading">	Address of the QD_Readings to receive the current Position Readings. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="QD_RequestReading(char const * serialNo)" />
	/// <seealso cref="QD_RequestStatus(char const * serialNo)" />
	/// <seealso cref="QD_StartPolling(char const * serialNo, int milliseconds)" />
	KCUBEPOSITIONALIGNER_API short __cdecl QD_GetReading(char const *serialNo, QD_Readings *reading);

	/// <summary>Get the current status bits. </summary>
	/// <remarks> This returns the latest status bits received from the device.<br />
	/// 		  To get new status bits, use <see cref="QD_RequestStatusBits(char const * serialNo)" />
	///			  or use <see cref="QD_RequestStatus(char const * serialNo)" />
	/// 		  or use the polling functions, <see cref="QD_StartPolling(char const * serialNo, int milliseconds)" />.  </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	The status bits from the device <list type=table>
	///				<item><term>0x00000001</term><term>Position monitoring mode (1=Enabled, 0=Disabled).</term></item>
	///				<item><term>0x00000002</term><term>Open loop operating mode (1=Enabled, 0=Disabled).</term></item>
	///				<item><term>0x00000004</term><term>Closed loop operating mode (1=Enabled, 0=Disabled).</term></item>
	///				<item><term>0x00000008</term><term>For Future Use.</term></item>
	///				<item><term>0x00000010</term><term></term></item>
	///				<item><term>...</term><term></term></item>
	///				<item><term>0x80000000</term><term></term></item>
	/// 		  </list> </returns>
	/// <seealso cref="QD_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="QD_RequestStatus(char const * serialNo)" />
	/// <seealso cref="QD_StartPolling(char const * serialNo, int milliseconds)" />
	KCUBEPOSITIONALIGNER_API DWORD __cdecl QD_GetStatusBits(char const * serialNo);

	/// <summary> Starts the internal polling loop which continuously requests position and status. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="milliseconds">The milliseconds polling rate. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="QD_StopPolling(char const * serialNo)" />
	/// <seealso cref="QD_PollingDuration(char const * serialNo)" />
	/// <seealso cref="QD_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="QD_RequestPosition(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	KCUBEPOSITIONALIGNER_API bool __cdecl QD_StartPolling(char const * serialNo, int milliseconds);

	/// <summary> Gets the polling loop duration. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The time between polls in milliseconds or 0 if polling is not active. </returns>
	/// <seealso cref="QD_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="QD_StopPolling(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	KCUBEPOSITIONALIGNER_API long __cdecl QD_PollingDuration(char const * serialNo);

	/// <summary> Stops the internal polling loop. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <seealso cref="QD_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="QD_PollingDuration(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	KCUBEPOSITIONALIGNER_API void __cdecl QD_StopPolling(char const * serialNo);

	/// <summary> Gets the time in milliseconds since tha last message was received from the device. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="lastUpdateTimeMS"> The time since the last message was received in milliseconds. </param>
	/// <returns> True if monitoring is enabled otherwize False. </returns>
	/// <seealso cref="QD_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// <seealso cref="QD_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	KCUBEPOSITIONALIGNER_API bool __cdecl QD_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS );

	/// <summary> Enables the last message monitoring timer. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="enable"> True to enable monitoring otherwise False to disable. </param>
	/// <param name="lastMsgTimeout"> The last message error timeout in ms. 0 to disable. </param>
	/// <seealso cref="QD_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="QD_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	KCUBEPOSITIONALIGNER_API void __cdecl QD_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout );

	/// <summary> Queries if the time since the last message has exceeded the lastMsgTimeout set by <see cref="QD_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )"/>. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> True if last message timer has elapsed, False if monitoring is not enabled or if time of last message received is less than lastMsgTimeout. </returns>
	/// <seealso cref="QD_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="QD_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	KCUBEPOSITIONALIGNER_API bool __cdecl QD_HasLastMsgTimerOverrun(char const * serialNo);

	/// <summary> Requests that all settings are download from device. </summary>
	/// <remarks> This function requests that the device upload all it's settings to the DLL.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	KCUBEPOSITIONALIGNER_API short __cdecl QD_RequestSettings(char const * serialNo);
}
/** @} */ // KCubePositionAligner
