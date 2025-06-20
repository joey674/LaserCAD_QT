// summary:	Declares the functions class
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the BENCHPIEZO_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// BENCHPRECISIONPIEZO_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#pragma once

#ifdef BENCHPRECISIONPIEZODLL_EXPORTS
#define BENCHPRECISIONPIEZO_API __declspec(dllexport)
#else
#define BENCHPRECISIONPIEZO_API __declspec(dllimport)
#endif

#include <OaIdl.h>

/** @defgroup BenchtopPrecisionPiezo Benchtop Precision Piezo
 *  This section details the Structures and Functions relavent to the  @ref PPC001_page "Benchtop Piezo"<br />
 *  For an example of how to connect to the device and perform simple operations use the following links:
 *  <list type=bullet>
 *    <item> \ref namespaces_ppc_ex_1 "Example of using the Thorlabs.MotionControl.Benchtop.PrecisionPiezo.DLL from a C or C++ project."<br />
 *									  This requires the DLL to be dynamical linked. </item>
 *    <item> \ref namespaces_ppc_ex_2 "Example of using the Thorlabs.MotionControl.Benchtop.PrecisionPiezo.DLL from a C# project"<br />
 *									  This uses Marshalling to load and access the C DLL. </item>
 *  </list>
 *  The Thorlabs.MotionControl.Benchtop.PrecisionPiezo.DLL requires the following DLLs
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
		PZ_Undefined = 0, ///<Undefined
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

/// \endcond
	
	/// <summary> Values that represent PPC_FilterState. </summary>
	typedef enum PPC_DerivFilterState : byte
	{
		/// <summary> An enum constant representing the filter on option. </summary>
		DerivFilterOn = 0x1,
		/// <summary> An enum constant representing the filter off option. </summary>
		DerivFilterOff = 0x2,
	} PPC_DerivFilterState;

	/// <summary> Values that represent PPC_FilterState. </summary>
	typedef enum PPC_NotchFilterState : short
	{
		/// <summary> An enum constant representing the filter on option. </summary>
		NotchFilterOn = 0x01,
		/// <summary> An enum constant representing the filter off option. </summary>
		NotchFilterOff = 0x02,
	} PPC_NotchFilterState;

	/// <summary> Values that represent PPC_NotchFilterChannel. </summary>
	typedef enum PPC_NotchFilterChannel : short
	{
		/// <summary> An enum constant representing the notch filter 1 option. </summary>
		NotchFilter1 = 0x01,
		/// <summary> An enum constant representing the notch filter 2 option. </summary>
		NotchFilter2 = 0x02,
		/// <summary> An enum constant representing the notch filter both option. </summary>
		NotchFilterBoth = 0x03,
	} PPC_NotchFilterChannel;

	/// <summary> Values that represent PPC_IOControlMode. </summary>
	typedef enum PPC_IOControlMode : short
	{
		/// <summary> An enum constant representing the software only option. </summary>
		SWOnly = 0x00,
		/// <summary> An enum constant representing the extent bnc option. </summary>
		ExtBNC = 0x01,
		/// <summary> An enum constant representing the joystick option. </summary>
		Joystick = 0x02,
		/// <summary> An enum constant representing the joystick bnc option. </summary>
		JoystickBnc = 0x03,
	} PPC_IOControlMode;

	/// <summary> Values that represent PPC_IOOutputModeMode. </summary>
	typedef enum PPC_IOOutputMode : short
	{
		/// <summary> An enum constant representing the hv option. </summary>
		HV = 0x01,
		/// <summary> An enum constant representing the position raw option. </summary>
		PosRaw = 0x02,
		/// <summary> An enum constant representing the position corrected option. </summary>
		PosCorrected = 0x03,
	} PPC_IOOutputMode;

	/// <summary> Values that represent PPC_IOOutput Bandwidth. </summary>
	typedef enum PPC_IOOutputBandwidth : short
	{
		/// <summary> An enum constant representing the operation unfiltered option. </summary>
		OP_Unfiltered = 0x01,
		/// <summary> An enum constant representing the operation 200 Hz option. </summary>
		OP_200Hz = 0x02,
	} PPC_IOOutputBandwidth;

	/// <summary> Values that represent PPC_IOSourceDefinition. </summary>
	typedef enum PPC_IOFeedbackSourceDefinition : short
	{
		/// <summary> An enum constant representing the operation unfiltered option. </summary>
		StrainGauge = 0x01,
		/// <summary> An enum constant representing the operation 200 Hz option. </summary>
		Capacitive = 0x02,
		/// <summary>	An enum constant representing the optical option (Only appicable to the PPC102). </summary>
		Optical = 0x03,
	} PPC_IOFeedbackSourceDefinition;

	/// <summary> Values that represent PPC Feedback Polarities. </summary>
	typedef enum PPC_FeedbackPolarity : WORD
	{
		/// <summary> An enum constant representing the non inverted option. </summary>
		NonInverted = 0,
		/// <summary> An enum constant representing the inverted option. </summary>
		Inverted = -1
	} PPC_FeedbackPolarity;

	/// <summary> Values that represent PPC_DisplayIntensity. </summary>
	typedef enum PPC_DisplayIntensity : short
	{
		/// <summary> An enum constant representing the bright option. </summary>
		Bright = 0x01,
		/// <summary> An enum constant representing the dim option. </summary>
		Dim = 0x02,
		/// <summary> An enum constant representing the off option. </summary>
		Off = 0x03,
	} PPC_DisplayIntensity;

	/// <summary> PPC PID consts. </summary>
	typedef struct PPC_PIDConsts
	{
		/// <summary> PID constants proportional. </summary>
		/// <remarks> The PID Proportional Gain constant, range 0 to 10000</remarks>
		float PIDConstsP;
		/// <summary> PID constants integral. </summary>
		/// <remarks> The PID Integral Gain constant, range 0 to 10000</remarks>
		float PIDConstsI;
		/// <summary> PID constants derivative. </summary>
		/// <remarks> The PID Derivative Gain constant, range 0 to 10000</remarks>
		float PIDConstsD;
		/// <summary> PID constants derivative low pass filter cut-off frequency. </summary>
		/// <remarks> The PID Derivative Gain filter, range 0 to 10000</remarks>
		float PIDConstsDFc;
		/// <summary> PID Derivative filter on or off. </summary>
		/// <remarks> The Filter Enabled state:
		/// 		  <list type=table>
		///				<item><term>1</term><term>Filter Enabled</term></item>
		///				<item><term>2</term><term>Filter Disabled.</term></item>
		/// 		  </list></remarks>
		PPC_DerivFilterState PIDDerivFilterOn;
		/// <summary> PID index, O for normal operation </summary>
		byte PIDIndex;
	} PPC_PIDConsts;

	/// <summary> PPC notch filter parameters. </summary>
	typedef struct PPC_NotchParams
	{
		/// <summary> Flags that define which filters are updated with this structure. </summary>
		/// <remarks> The Notch Filter selection flags:
		/// 		  <list type=table>
		///				<item><term>1</term><term>Filter 1 parameters are updated.</term></item>
		///				<item><term>2</term><term>Filter 2 parameters are updated.</term></item>
		///				<item><term>2</term><term>Filter 1 and 2 parameters are updated.</term></item>
		/// 		  </list></remarks>
		PPC_NotchFilterChannel filterNo;
		/// <summary> Notch filter 1 centre frequency. </summary>
		/// <remarks> The Notch Filter Center Frequency, range 20 to 500Hz</remarks>
		float filter1Fc;
		/// <summary> Notch filter 1 Q. </summary>
		/// <remarks> The Notch Filter Q Value, range 0.2 to 100</remarks>
		float filter1Q;
		/// <summary> Notch filter 1 on or off. </summary>
		/// <remarks> The Filter Enabled state:
		/// 		  <list type=table>
		///				<item><term>1</term><term>Filter Enabled</term></item>
		///				<item><term>2</term><term>Filter Disabled.</term></item>
		/// 		  </list></remarks>
		PPC_NotchFilterState notchFilter1On;
		/// <summary> Notch filter 2 centre frequency. </summary>
		/// <remarks> The Notch Filter Center Frequency, range 20 to 500Hz</remarks>
		float filter2Fc;
		/// <summary> Notch filter 2 Q. </summary>
		/// <remarks> The Notch Filter Q Value, range 0.2 to 100</remarks>
		float filter2Q;
		/// <summary> Notch filter 2 on or off. </summary>
		/// <remarks> The Filter Enabled state:
		/// 		  <list type=table>
		///				<item><term>1</term><term>Filter Enabled</term></item>
		///				<item><term>2</term><term>Filter Disabled.</term></item>
		/// 		  </list></remarks>
		PPC_NotchFilterState notchFilter2On;

	} PPC_NotchParams;

	/// <summary> PPC i/o settings. </summary>
	typedef struct PPC_IOSettings
	{
		/// <summary> Voltage/Position control input source. </summary>
		/// <remarks> The enabled input sources:
		/// 		  <list type=table>
		///				<item><term>0</term><term>Software input only.</term></item>
		///				<item><term>1</term><term>Software and external BNC.</term></item>
		///				<item><term>2</term><term>Software and external joystick.</term></item>
		///				<item><term>2</term><term>Software, External BNC and Joystick.</term></item>
		/// 		  </list></remarks>
		PPC_IOControlMode controlSrc;
		/// <summary> Monitor output BNC signal. </summary>
		/// <remarks> The Monitor output modes:
		/// 		  <list type=table>
		///				<item><term>1</term><term>High Voltage output.</term></item>
		///				<item><term>2</term><term>Position (Uncorrected).</term></item>
		///				<item><term>2</term><term>Position (Corrected).</term></item>
		/// 		  </list></remarks>
		PPC_IOOutputMode monitorOPSig;
		/// <summary> Monitor output bandwidth. </summary>
		/// <remarks> The output bandwidth modes:
		/// 		  <list type=table>
		///				<item><term>1</term><term>Unfiltered.</term></item>
		///				<item><term>2</term><term>200Hz filter.</term></item>
		/// 		  </list></remarks>
		PPC_IOOutputBandwidth monitorOPBandwidth;
		/// <summary> Type of feedback in operation. </summary>
		/// <remarks> The feedback loop mode (read only):
		/// 		  <list type=table>
		///				<item><term>1</term><term>Strain Gauge.</term></item>
		///				<item><term>2</term><term>Capacitive.</term></item>
		///				<item><term>3</term><term>Optical (PPC102 only).</term></item>
		/// 		  </list></remarks>
		PPC_IOFeedbackSourceDefinition feedbackSrc;
		/// <summary> Brightness of the from panel LED's. </summary>
		/// <remarks> The display brightness:
		/// 		  <list type=table>
		///				<item><term>1</term><term>Bright.</term></item>
		///				<item><term>2</term><term>Dim.</term></item>
		///				<item><term>3</term><term>Off.</term></item>
		/// 		  </list></remarks>
		PPC_DisplayIntensity FPBrightness;
		/// <summary> The Feedback source polarity. </summary>
		/// <remarks> The Feedback Polarity:
		/// 		  <list type=table>
		///				<item><term>0</term><term>Non Inverted.</term></item>
		///				<item><term>-1</term><term>Inverted.</term></item>
		/// 		  </list></remarks>
		PPC_FeedbackPolarity feedbackPolarity;
	} PPC_IOSettings;
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
	BENCHPRECISIONPIEZO_API short __cdecl TLI_BuildDeviceList(void);

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
	BENCHPRECISIONPIEZO_API short __cdecl TLI_GetDeviceListSize();

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
	BENCHPRECISIONPIEZO_API short __cdecl TLI_GetDeviceList(SAFEARRAY** stringsReceiver);

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
	BENCHPRECISIONPIEZO_API short __cdecl TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID);

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
	BENCHPRECISIONPIEZO_API short __cdecl TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length);

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
	BENCHPRECISIONPIEZO_API short __cdecl TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer);

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
	BENCHPRECISIONPIEZO_API short __cdecl TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID);

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
	BENCHPRECISIONPIEZO_API short __cdecl TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length);

	/// <summary> Get the device information from the USB port. </summary>
	/// <remarks> The Device Info is read from the USB port not from the device itself.<remarks>
	/// <param name="serialNo"> The serial number of the device. </param>
	/// <param name="info">    The <see cref="CDeviceInfo"/> device information. </param>
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
	BENCHPRECISIONPIEZO_API short __cdecl TLI_GetDeviceInfo(char const * serialNo, TLI_DeviceInfo *info);

	/// <summary> Initialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <remarks> Call TLI_InitializeSimulations before TLI_BuildDeviceList at the start of the program to make a connection to the simulation manager.<Br />
	/// 		  Any devices configured in the simulation manager will become visible TLI_BuildDeviceList is called and can be accessed using TLI_GetDeviceList.<Br />
	/// 		  Call TLI_InitializeSimulations at the end of the program to release the simulator.  </remarks>
	/// <seealso cref="TLI_UninitializeSimulations()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	BENCHPRECISIONPIEZO_API void __cdecl TLI_InitializeSimulations();

	/// <summary> Uninitialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <seealso cref="TLI_InitializeSimulations()" />
	BENCHPRECISIONPIEZO_API void __cdecl TLI_UninitializeSimulations();

	/// <summary> Open the device for communications. </summary>
	/// <param name="serialNo">	The serial no of the device to be connected. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// 		  \include CodeSnippet_connectionN.cpp
	/// <seealso cref="PPC_Close(char const * serialNo)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC_Open(char const * serialNo);

	/// <summary> Disconnect and close the device. </summary>
	/// <param name="serialNo">	The serial no of the device to be disconnected. </param>
	/// 		  \include CodeSnippet_connectionN.cpp
	/// <seealso cref="PPC_Open(char const * serialNo)" />
	BENCHPRECISIONPIEZO_API void __cdecl PPC_Close(char const * serialNo);

	/// <summary>	Check connection. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> true if the USB is listed by the ftdi controller</returns>
	/// \include CodeSnippet_CheckConnection.cpp
	BENCHPRECISIONPIEZO_API bool __cdecl PPC_CheckConnection(char const * serialNo);

	/// <summary> Sends a command to the device to make it identify iteself. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	BENCHPRECISIONPIEZO_API void __cdecl PPC_Identify(char const * serialNo);

	/// <summary> Tells the device that it is being disconnected. </summary>
	/// <remarks> This does not disconnect the communications.<br />
	/// 		  To disconnect the communications, call the <see cref="PPC_Close(char const * serialNo)" /> function. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPRECISIONPIEZO_API short __cdecl PPC_Disconnect(char const * serialNo);

	/// <summary> Gets the hardware information from the device. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
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
	BENCHPRECISIONPIEZO_API short __cdecl PPC_GetHardwareInfo(char const * serialNo, char * modelNo, DWORD sizeOfModelNo, WORD * type, WORD * numChannels,
		char * notes, DWORD sizeOfNotes, DWORD * firmwareVersion, WORD * hardwareVersion, WORD * modificationState);

	/// <summary> Gets the hardware information in a block. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="hardwareInfo"> Address of a TLI_HardwareInformation structure to receive the hardware information. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// 		  \include CodeSnippet_identify.cpp
	BENCHPRECISIONPIEZO_API short __cdecl PPC_GetHardwareInfoBlock(char const  *serialNo, TLI_HardwareInformation *hardwareInfo);

	/// <summary> Gets version number of the device firmware. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device firmware version number made up of 4 byte parts. </returns>
	/// 		  \include CodeSnippet_identify.cpp
	BENCHPRECISIONPIEZO_API DWORD __cdecl PPC_GetFirmwareVersion(char const * serialNo);

	/// <summary> Gets version number of the device software. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device software version number made up of 4 byte parts. </returns>
	/// 		  \include CodeSnippet_identify.cpp
	BENCHPRECISIONPIEZO_API DWORD __cdecl PPC_GetSoftwareVersion(char const * serialNo);

	/// <summary> Update device with stored settings. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// 		  \include CodeSnippet_connection1.cpp
	BENCHPRECISIONPIEZO_API bool __cdecl PPC_LoadSettings(char const * serialNo);

	/// <summary> Update device with named settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="settingsName"> Name of settings stored away from device. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	///             \include CodeSnippet_connection1.cpp
	BENCHPRECISIONPIEZO_API bool __cdecl PPC_LoadNamedSettings(char const * serialNo, char const *settingsName);

	/// <summary>	Persist device settings to device. </summary>
	/// <param name="serialNo">	The serial no. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	BENCHPRECISIONPIEZO_API bool __cdecl PPC_PersistSettings(char const * serialNo);

	/// <summary> Disable the channel so that motor can be moved by hand. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <remarks> When disabled power is removed from the actuator.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC_EnableChannel(char const * serialNo)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC_DisableChannel(char const * serialNo);

	/// <summary> Enable channel for computer control. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <remarks> When enabled power is applied to the actuator so it is fixed in position.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC_DisableChannel(char const * serialNo)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC_EnableChannel(char const * serialNo);

	/// <summary> Registers a callback on the message queue. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="functionPointer"> A function pointer to be called whenever messages are received. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPRECISIONPIEZO_API short __cdecl PPC_RegisterMessageCallback(char const * serialNo, void(*functionPointer)());

	/// <summary> Gets the MessageQueue size. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> number of messages in the queue. </returns>
	BENCHPRECISIONPIEZO_API int __cdecl PPC_MessageQueueSize(char const * serialNo);

	/// <summary> Clears the device message queue. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPRECISIONPIEZO_API short __cdecl PPC_ClearMessageQueue(char const * serialNo);

	/// <summary> Get the next MessageQueue item if it is available. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> Address of the WORD to receive the message type. </param>
	/// <param name="messageID"> Address of the WORD to receive themessage ID. </param>
	/// <param name="messageData"> Address of the DWORD to receive the messageData. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	BENCHPRECISIONPIEZO_API bool __cdecl PPC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Get the next MessageQueue item if it is available. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> Address of the WORD to receive the message type. </param>
	/// <param name="messageID"> Address of the WORD to receive themessage ID. </param>
	/// <param name="messageData"> Address of the DWORD to receive the messageData. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	BENCHPRECISIONPIEZO_API bool __cdecl PPC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Starts the internal polling loop which continuously requests position and status. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="milliseconds">The milliseconds polling rate. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="PPC_StopPolling(char const * serialNo)" />
	/// <seealso cref="PPC_PollingDuration(char const * serialNo)" />
	/// <seealso cref="PPC_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="PPC_RequestPosition(char const * serialNo)" />
	/// \include CodeSnippet_connectionN.cpp
	BENCHPRECISIONPIEZO_API bool __cdecl PPC_StartPolling(char const * serialNo, int milliseconds);

	/// <summary> Gets the polling loop duration. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The time between polls in milliseconds or 0 if polling is not active. </returns>
	/// <seealso cref="PPC_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="PPC_StopPolling(char const * serialNo)" />
	/// \include CodeSnippet_connectionN.cpp
	BENCHPRECISIONPIEZO_API long __cdecl PPC_PollingDuration(char const * serialNo);

	/// <summary> Stops the internal polling loop. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <seealso cref="PPC_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="PPC_PollingDuration(char const * serialNo)" />
	/// \include CodeSnippet_connectionN.cpp
	BENCHPRECISIONPIEZO_API void __cdecl PPC_StopPolling(char const * serialNo);


	/// <summary> Requests that all settings are download from device. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <remarks> This function requests that the device upload all it's settings to the DLL.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	BENCHPRECISIONPIEZO_API short __cdecl PPC_RequestSettings(char const * serialNo);

	/// <summary> Requests the status bits and position. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <remarks> This needs to be called to get the device to send it's current position and status bits.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="PPC_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="PPC_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="PPC_GetPosition(char const * serialNo)" />
	/// <seealso cref="PPC_GetStatusBits(char const * serialNo)" />
	/// <seealso cref="PPC_StartPolling(char const * serialNo, int milliseconds)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC_RequestStatus(char const * serialNo);

	/// <summary> Request the status bits which identify the current device state. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <remarks> This needs to be called to get the device to send it's current status bits.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="PPC_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="PPC_GetStatusBits(char const * serialNo)" />
	/// <seealso cref="PPC_StartPolling(char const * serialNo, int milliseconds)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC_RequestStatusBits(char const * serialNo);

	/// <summary>Get the current status bits. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <remarks> This returns the latest status bits received from the device.<br />
	/// 		  To get new status bits, use <see cref="PPC_RequestStatusBits(char const * serialNo)" /> <br />
	///			  or use <see cref="BPC_RequestStatus(char const * serialNo)" />
	/// 		  or use the polling functions, <see cref="PPC_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
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
	///				<item><term>0x00000800</term><term>High voltage amplifier temeprature above safe limit.</term></item>
	///				<item><term>0x00001000</term><term>Position reading is below normal range</term></item>
	///				<item><term>0x00002000</term><term>Position reading is above normal range</term></item>
	///				<item><term>0x00004000</term><term></term></item>
	///				<item><term>0x00080000</term><term></term></item>
	///				<item><term>0x00100000</term><term>Digital input 1 state (1=Logic High, 0=Logic Low).</term></item>
	///				<item><term>0x00200000</term><term>Digital input 2 state (1=Logic High, 0=Logic Low).</term></item>
	///				<item><term>0x00400000</term><term>Digital input 3 state (1=Logic High, 0=Logic Low).</term></item>
	///				<item><term>0x00800000</term><term>Digital input 4 state (1=Logic High, 0=Logic Low).</term></item>
	///				<item><term>0x01000000</term><term>For Future Use.</term></item>
	///				<item><term>0x02000000</term><term>For Future Use.</term></item>
	///				<item><term>0x04000000</term><term>For Future Use.</term></item>
	///				<item><term>0x08000000</term><term>For Future Use.</term></item>
	///				<item><term>0x10000000</term><term>For Future Use.</term></item>
	///				<item><term>0x20000000</term><term>Active (1=Indicates Unit Is Active, 0=Not Active).</term></item>
	///				<item><term>0x40000000</term><term>Error (mirrors LED for rack based modules.</term></item>
	///				<item><term>0x80000000</term><term>Channel enabled (1=Enabled, 0=Disabled).</term></item>
	/// 		  </list> <remarks> Bits 21 to 28 (Digital Input States) are only applicable if the associated digital input is fitted to your controller - see the relevant handbook for more details. </remarks> </returns>
	/// <seealso cref="PPC_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="PPC_RequestStatus(char const * serialNo)" />
	/// <seealso cref="PPC_StartPolling(char const * serialNo, int milliseconds)" />
	BENCHPRECISIONPIEZO_API DWORD __cdecl PPC_GetStatusBits(char const * serialNo);

	/// <summary>	Resets all parameters to power-up values. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPRECISIONPIEZO_API short __cdecl PPC_ResetParameters(char const * serialNo);

	/// <summary> Sets the voltage output to zero and defines the ensuing actuator position az zero. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPRECISIONPIEZO_API short __cdecl PPC_SetZero(char const * serialNo);

	/// <summary>	Requests the position. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <seealso cref="PPC_RequestPosition(char const * serialNo)" />
	/// <seealso cref="PPC_GetPosition(char const * serialNo)" />
	/// <seealso cref="PPC_SetPosition(char const * serialNo, short position)" />
	/// <seealso cref="PPC_SetPositionToTolerance(char const * serialNo, short position, short tolerance)" />
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	BENCHPRECISIONPIEZO_API short __cdecl PPC_RequestActualPosition(char const * serialNo);

	/// <summary> Requests the current output voltage or position depending on current mode. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <remarks> This needs to be called to get the device to send it's current position.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="PPC_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="PPC_GetPosition(char const * serialNo)" />
	/// <seealso cref="PPC_RequestActualPosition(char const * serialNo)" />
	/// <seealso cref="PPC_StartPolling(char const * serialNo, int milliseconds)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC_RequestPosition(char const * serialNo);

	/// <summary> Gets the Position Control Mode. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The control mode <list type=table>
	///				<item><term>Open Loop</term><term>1</term></item>
	///				<item><term>Closed Loop</term><term>2</term></item>
	///				<item><term>Open Loop smoothed</term><term>3</term></item>
	///				<item><term>Closed Loop smoothed</term><term>4</term></item>
	/// 		  </list> </returns>
	/// <seealso cref="PPC_RequestPositionControlMode(char const * serialNo)" />
	/// <seealso cref="PPC_SetPositionControlMode(char const * serialNo, PZ_ControlModeTypes mode)" />
	BENCHPRECISIONPIEZO_API PZ_ControlModeTypes __cdecl PPC_GetPositionControlMode(char const * serialNo);

	/// <summary> Requests that the Position Control Mode be read from the device. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="PPC_GetPositionControlMode(char const * serialNo)" />
	/// <seealso cref="PPC_SetPositionControlMode(char const * serialNo, PZ_ControlModeTypes mode)" />
	BENCHPRECISIONPIEZO_API bool __cdecl PPC_RequestPositionControlMode(char const * serialNo);

	/// <summary> Sets the Position Control Mode. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="mode"> The control mode <list type=table>
	///				<item><term>Open Loop</term><term>1</term></item>
	///				<item><term>Closed Loop</term><term>2</term></item>
	///				<item><term>Open Loop smoothed</term><term>3</term></item>
	///				<item><term>Closed Loop smoothed</term><term>4</term></item>
	/// 		  </list>. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC_GetPositionControlMode(char const * serialNo)" />
	/// <seealso cref="PPC_RequestPositionControlMode(char const * serialNo)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC_SetPositionControlMode(char const * serialNo, PZ_ControlModeTypes mode);

	// Voltage Functions

	/// <summary> Gets the minimum output voltage. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The minimum output voltage, normally -30 for Precision Piezo. </returns>
	/// <seealso cref="PPC_SetMaxOutputVoltage(char const * serialNo, short maxVoltage)" />
	/// <seealso cref="PPC_GetMaxOutputVoltage(char const * serialNo)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC_GetMinOutputVoltage(char const * serialNo);

	/// <summary> Gets the maximum output voltage. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The maximum output voltage, range 0 to 1500 (0.0 to 150.0 Volts). </returns>
	/// <seealso cref="PPC_RequestMaxOutputVoltage(char const * serialNo)" />
	/// <seealso cref="PPC_SetMaxOutputVoltage(char const * serialNo, short maxVoltage)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC_GetMaxOutputVoltage(char const * serialNo);

	/// <summary> Requests the maximum output voltage be read from the device. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="PPC_GetMaxOutputVoltage(char const * serialNo)" />
	/// <seealso cref="PPC_SetMaxOutputVoltage(char const * serialNo, short maxVoltage)" />
	BENCHPRECISIONPIEZO_API bool __cdecl PPC_RequestMaxOutputVoltage(char const * serialNo);

	/// <summary> Sets the maximum output voltage. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="maxVoltage">	The maximum output voltage, 0 to 1500 (0.0 to 150.0 Volts). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC_GetMaxOutputVoltage(char const * serialNo)" />
	/// <seealso cref="PPC_RequestMaxOutputVoltage(char const * serialNo)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC_SetMaxOutputVoltage(char const * serialNo, short maxVoltage);

	/// <summary> Gets the set Output Voltage. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The voltage as a percentage of MaxOutputVoltage,<br />
	/// 		  range -32767 to 32767 equivalent to -100% to 100%. </returns>
	/// <seealso cref="PPC_RequestOutputVoltage(char const * serialNo)" />
	/// <seealso cref="PPC_SetOutputVoltage(char const * serialNo, short volts)" />
	/// <seealso cref="PPC_SetMaxOutputVoltage(char const * serialNo, short eVoltage)" />
	/// <seealso cref="PPC_GetMaxOutputVoltage(char const * serialNo)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC_GetOutputVoltage(char const * serialNo);

	/// <summary> Requests the Output Voltage be read from the device. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="PPC_GetOutputVoltage(char const * serialNo)" />
	/// <seealso cref="PPC_SetOutputVoltage(char const * serialNo, short volts)" />
	/// <seealso cref="PPC_SetMaxOutputVoltage(char const * serialNo, short eVoltage)" />
	/// <seealso cref="PPC_GetMaxOutputVoltage(char const * serialNo)" />
	BENCHPRECISIONPIEZO_API bool __cdecl PPC_RequestOutputVoltage(char const * serialNo);

	/// <summary> Sets the output voltage. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="volts"> The voltage as a percentage of MaxOutputVoltage,<br />
	/// 		  range -32767 to 32767 equivalent to -100% to 100%. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC_GetOutputVoltage(char const * serialNo)" />
	/// <seealso cref="PPC_RequestOutputVoltage(char const * serialNo)" />
	/// <seealso cref="PPC_SetMaxOutputVoltage(char const * serialNo, short eVoltage)" />
	/// <seealso cref="PPC_GetMaxOutputVoltage(char const * serialNo)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC_SetOutputVoltage(char const * serialNo, short volts);

	/// <summary> Requests that the current input voltage source be read from the device. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="PPC_GetVoltageSource(char const * serialNo)" />
	/// <seealso cref="PPC_SetVoltageSource(char const * serialNo, PZ_InputSourceFlags source)" />
	BENCHPRECISIONPIEZO_API bool __cdecl PPC_RequestVoltageSource(char const * serialNo);

	/// <summary> Gets the control voltage source. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The voltage source. <list type=table>
	///				<item><term>Software Only</term><term>0</term></item>
	///				<item><term>Software and External</term><term>1</term></item>
	///				<item><term>Software and Potentiometer</term><term>2</term></item>
	///				<item><term>Software, External and Potentiometer</term><term>3</term></item>
	/// 		  </list> </returns>
	/// <seealso cref="PPC_RequestVoltageSource(char const * serialNo, short channel)" />
	/// <seealso cref="PPC_SetVoltageSource(char const * serialNo, PZ_InputSourceFlags source)" />
	BENCHPRECISIONPIEZO_API PZ_InputSourceFlags __cdecl PPC_GetVoltageSource(char const * serialNo);

	/// <summary> Sets the control voltage source. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="source"> The voltage source <list type=table>
	///				<item><term>Software Only</term><term>0</term></item>
	///				<item><term>Software and External</term><term>1</term></item>
	///				<item><term>Software and Potentiometer</term><term>2</term></item>
	///				<item><term>Software, External and Potentiometer</term><term>3</term></item>
	/// 		  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC_RequestVoltageSource(char const * serialNo)" />
	/// <seealso cref="PPC_GetVoltageSource(char const * serialNo)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC_SetVoltageSource(char const * serialNo, PZ_InputSourceFlags source);

	/// <summary> Gets the maximum travel of the device. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <remarks> This requires an actuator with built in position sensing</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns>	The distance in steps of 100nm,<br />
	/// 			range 0 to 65535 (10000 is equivalent to 1mm). </returns>
	BENCHPRECISIONPIEZO_API WORD __cdecl PPC_GetMaximumTravel(char const * serialNo);

	/// <summary> Gets the position when in closed loop mode. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <remarks> The result is undefined if not in closed loop mode</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The position as a percentage of maximum travel,<br />
	/// 		  range -32767 to 32767, equivalent to -100 to 100%. </returns>
	/// <seealso cref="PPC_RequestActualPosition(char const * serialNo)" />
	/// <seealso cref="PPC_SetPosition(char const * serialNo, short position)" />
	/// <seealso cref="PPC_SetPositionToTolerance(char const * serialNo, short position, short tolerance)" />
	/// <seealso cref="PPC_SetPositionControlMode(char const * serialNo, PZ_ControlModeTypes mode)" />
	/// <seealso cref="PPC_GetPositionControlMode(char const * serialNo)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC_GetPosition(char const * serialNo);

	/// <summary> Sets the position when in closed loop mode. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <remarks> The command is ignored if not in closed loop mode</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="position"> The position as a percentage of maximum travel,<br />
	/// 		  range 0 to 32767, equivalent to 0 to 100%. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC_RequestActualPosition(char const * serialNo)" />
	/// <seealso cref="PPC_SetPositionToTolerance(char const * serialNo, short position, short tolerance)" />
	/// <seealso cref="PPC_GetPosition(char const * serialNo)" />
	/// <seealso cref="PPC_SetPositionControlMode(char const * serialNo, PZ_ControlModeTypes mode)" />
	/// <seealso cref="PPC_GetPositionControlMode(char const * serialNo)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC_SetPosition(char const * serialNo, short position);

	/// <summary> Sets the position when in closed loop mode. </summary>
	/// <remarks> The command is ignored if not in closed loop mode</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="position"> The position as a percentage of maximum travel,<br />
	/// 		  range 0 to 32767, equivalent to 0 to 100%. </param>
	/// <param name="tolerance"> The tolerance in position as a percentage of maximum travel,<br />
	/// 		  range 0 to 32767, equivalent to 0 to 100%. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC_RequestActualPosition(char const * serialNo)" />
	/// <seealso cref="PPC_SetPosition(char const * serialNo, short position)" />
	/// <seealso cref="PPC_GetPosition(char const * serialNo)" />
	/// <seealso cref="PPC_SetPositionControlMode(char const * serialNo, PZ_ControlModeTypes mode)" />
	/// <seealso cref="PPC_GetPositionControlMode(char const * serialNo)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC_SetPositionToTolerance(char const * serialNo, short position, short tolerance);

	/// <summary> Gets the PPC IO Settings. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="ioSettings"> The i/o settings <see cref="PPC_IOSettings"/>. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC_SetIOSettings(const char * serialNo, PPC_IOSettings *ioSettings)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC_GetIOSettings(const char * serialNo, PPC_IOSettings *ioSettings);

	/// <summary> Sets the PPC IO Setting. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="ioSettings"> The i/o setting <see cref="PPC_IOSettings"/>. </returns> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC_GetIOSettings(const char * serialNo, PPC_IOSettings *ioSettings)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC_SetIOSettings(const char * serialNo, PPC_IOSettings *ioSettings);

	/// <summary> Gets the PPC Notch Filter Parameters. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <remarks> The PPC Notch Filter Parameters. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="notchParams"> Options for controlling the notch <see cref="PPC_NotchParams"/>. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC_SetNotchParams(const char * serialNo, PPC_NotchParams *notchParams)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC_GetNotchParams(const char * serialNo, PPC_NotchParams *notchParams);

	/// <summary> Sets the PPC Notch Filter Parameters. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="notchParams"> The PPC Notch Filter Parameters <see cref="PPC_NotchParams"/>. </returns> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC_GetNotchParams(const char * serialNo, PPC_NotchParams *notchParams)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC_SetNotchParams(const char * serialNo, PPC_NotchParams *notchParams);

	/// <summary> Requests the PPC PID Constants. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="PPC_GetPIDConsts(const char * serialNo, PPC_PIDConsts *pidConsts)" />
	/// <seealso cref="PPC_SetPIDConsts(const char * serialNo, PPC_PIDConsts *pidConsts)" />
	BENCHPRECISIONPIEZO_API bool __cdecl PPC_RequestPIDConsts(const char * serialNo);

	/// <summary> Gets the PPC PID Constants. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="pidConsts"> The PID consts <see cref="PPC_PIDConsts"/>. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC_RequestPIDConsts(const char * serialNo)" />
	/// <seealso cref="PPC_SetPIDConsts(const char * serialNo, PPC_PIDConsts *pidConsts)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC_GetPIDConsts(const char * serialNo, PPC_PIDConsts *pidConsts);

	/// <summary> Sets the PPC PID Constants. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="pidConsts"> The PPC PID Constants <see cref="PPC_PIDConsts"/>. </returns> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC_RequestPIDConsts(const char * serialNo)" />
	/// <seealso cref="PPC_GetPIDConsts(const char * serialNo, PPC_PIDConsts *pidConsts)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC_SetPIDConsts(const char * serialNo, PPC_PIDConsts *pidConsts);

	/// <summary> Requests the rack digital output bits. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC_SetRackDigitalOutputs(char const * serialNo, byte outputsBits)" />
	/// <seealso cref="PPC_GetRackDigitalOutputs(char const * serialNo)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC_RequestRackDigitalOutputs(char const * serialNo);

	/// <summary> Gets the rack digital output bits. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> Bit mask of states of the 4 digital output pins. </returns>
	/// <seealso cref="PPC_SetRackDigitalOutputs(char const * serialNo, byte outputsBits)" />
	/// <seealso cref="PPC_RequestRackDigitalOutputs(char const * serialNo)" />
	BENCHPRECISIONPIEZO_API byte __cdecl PPC_GetRackDigitalOutputs(char const * serialNo);

	/// <summary> Sets the rack digital output bits. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="outputsBits"> Bit mask to set states of the 4 digital output pins. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC_GetRackDigitalOutputs(char const * serialNo)" />
	/// <seealso cref="PPC_RequestRackDigitalOutputs(char const * serialNo)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC_SetRackDigitalOutputs(char const * serialNo, byte outputsBits);

	/// <summary> Requests the Rack status bits be downloaded. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC_GetRackStatusBits(char const * serialNo)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC_RequestRackStatusBits(char const * serialNo);

	/// <summary> Gets the Rack status bits. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The status bits including 4 with one per electronic input pin. </returns>
	/// <seealso cref="PPC_RequestRackStatusBits(char const * serialNo)" />
	BENCHPRECISIONPIEZO_API DWORD __cdecl PPC_GetRackStatusBits(char const * serialNo);

	/// <summary> Sends a command to the device to make it identify iteself. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	BENCHPRECISIONPIEZO_API void __cdecl PPC2_Identify(char const * serialNo, int channel);

	/// <summary> Gets the hardware information from the device. </summary>
	/// <param name="serialNo">		    The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
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
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_GetHardwareInfo(char const * serialNo, int channel, char * modelNo, DWORD sizeOfModelNo, WORD * type, WORD * numChannels,
		char * notes, DWORD sizeOfNotes, DWORD * firmwareVersion, WORD * hardwareVersion, WORD * modificationState);

	/// <summary> Gets the hardware information in a block. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <param name="hardwareInfo"> Address of a TLI_HardwareInformation structure to receive the hardware information. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// 		  \include CodeSnippet_identify.cpp
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_GetHardwareInfoBlock(char const  *serialNo, int channel, TLI_HardwareInformation *hardwareInfo);

	/// <summary> Update device with stored settings. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// 		  \include CodeSnippet_connection1.cpp
	BENCHPRECISIONPIEZO_API bool __cdecl PPC2_LoadSettings(char const * serialNo, int channel);

	/// <summary> Update device with named settings. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <param name="channel">  The channel. </param>
	/// <param name="settingsName"> Name of settings stored away from device. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	///             \include CodeSnippet_connection1.cpp
	BENCHPRECISIONPIEZO_API bool __cdecl PPC2_LoadNamedSettings(char const * serialNo, short channel, char const *settingsName);

	/// <summary>	Persist device settings to device. </summary>
	/// <param name="serialNo">	The serial no. </param>
	/// <param name="channel"> 	The channel. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	BENCHPRECISIONPIEZO_API bool __cdecl PPC2_PersistSettings(char const * serialNo, int channel);

	/// <summary> Disable the channel so that motor can be moved by hand. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <remarks> When disabled power is removed from the actuator.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC2_EnableChannel(char const * serialNo, int channel)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_DisableChannel(char const * serialNo, int channel);

	/// <summary> Enable channel for computer control. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <remarks> When enabled power is applied to the actuator so it is fixed in position.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC2_DisableChannel(char const * serialNo, int channel)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_EnableChannel(char const * serialNo, int channel);

	/// <summary> Registers a callback on the message queue. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <param name="functionPointer"> A function pointer to be called whenever messages are received. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_RegisterMessageCallback(char const * serialNo, int channel, void(*functionPointer)());

	/// <summary> Gets the MessageQueue size. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <returns> number of messages in the queue. </returns>
	BENCHPRECISIONPIEZO_API int __cdecl PPC2_MessageQueueSize(char const * serialNo, int channel);

	/// <summary> Clears the device message queue. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="channel">	The device channel. </param>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_ClearMessageQueue(char const * serialNo, int channel);

	/// <summary> Get the next MessageQueue item if it is available. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <param name="messageType"> Address of the WORD to receive the message type. </param>
	/// <param name="messageID"> Address of the WORD to receive themessage ID. </param>
	/// <param name="messageData"> Address of the DWORD to receive the messageData. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	BENCHPRECISIONPIEZO_API bool __cdecl PPC2_GetNextMessage(char const * serialNo, int channel, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Get the next MessageQueue item if it is available. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <param name="messageType"> Address of the WORD to receive the message type. </param>
	/// <param name="messageID"> Address of the WORD to receive themessage ID. </param>
	/// <param name="messageData"> Address of the DWORD to receive the messageData. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	BENCHPRECISIONPIEZO_API bool __cdecl PPC2_WaitForMessage(char const * serialNo, int channel, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Starts the internal polling loop which continuously requests position and status. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <param name="milliseconds">The milliseconds polling rate. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="PPC2_StopPolling(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_PollingDuration(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_RequestStatusBits(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_RequestPosition(char const * serialNo, int channel)" />
	/// \include CodeSnippet_connectionN.cpp
	BENCHPRECISIONPIEZO_API bool __cdecl PPC2_StartPolling(char const * serialNo, int channel, int milliseconds);

	/// <summary> Gets the polling loop duration. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <returns> The time between polls in milliseconds or 0 if polling is not active. </returns>
	/// <seealso cref="PPC2_StartPolling(char const * serialNo, int channel, int milliseconds)" />
	/// <seealso cref="PPC2_StopPolling(char const * serialNo, int channel)" />
	/// \include CodeSnippet_connectionN.cpp
	BENCHPRECISIONPIEZO_API long __cdecl PPC2_PollingDuration(char const * serialNo, int channel);

	/// <summary> Stops the internal polling loop. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <seealso cref="PPC2_StartPolling(char const * serialNo, int channel, int milliseconds)" />
	/// <seealso cref="PPC2_PollingDuration(char const * serialNo, int channel)" />
	/// \include CodeSnippet_connectionN.cpp
	BENCHPRECISIONPIEZO_API void __cdecl PPC2_StopPolling(char const * serialNo, int channel);

	/// <summary> Requests that all settings are download from device. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <remarks> This function requests that the device upload all it's settings to the DLL.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_RequestSettings(char const * serialNo, int channel);

	/// <summary> Requests the status bits and position. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <remarks> This needs to be called to get the device to send it's current position and status bits.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="PPC2_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="PPC2_RequestStatusBits(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_GetPosition(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_GetStatusBits(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_StartPolling(char const * serialNo, int channel, int milliseconds)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_RequestStatus(char const * serialNo, int channel);

	/// <summary> Request the status bits which identify the current device state. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <remarks> This needs to be called to get the device to send it's current status bits.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="PPC2_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="PPC2_GetStatusBits(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_StartPolling(char const * serialNo, int channel, int milliseconds)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_RequestStatusBits(char const * serialNo, int channel);

	/// <summary>Get the current status bits. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <remarks> This returns the latest status bits received from the device.<br />
	/// 		  To get new status bits, use <see cref="PPC2_RequestStatusBits(char const * serialNo)" /> <br />
	///			  or use <see cref="BPC_RequestStatus(char const * serialNo)" />
	/// 		  or use the polling functions, <see cref="PPC2_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
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
	///				<item><term>0x00000800</term><term>High voltage amplifier temeprature above safe limit.</term></item>
	///				<item><term>0x00001000</term><term>Position reading is below normal range</term></item>
	///				<item><term>0x00002000</term><term>Position reading is above normal range</term></item>
	///				<item><term>0x00004000</term><term></term></item>
	///				<item><term>0x00080000</term><term></term></item>
	///				<item><term>0x00100000</term><term>Digital input 1 state (1=Logic High, 0=Logic Low).</term></item>
	///				<item><term>0x00200000</term><term>Digital input 2 state (1=Logic High, 0=Logic Low).</term></item>
	///				<item><term>0x00400000</term><term>Digital input 3 state (1=Logic High, 0=Logic Low).</term></item>
	///				<item><term>0x00800000</term><term>Digital input 4 state (1=Logic High, 0=Logic Low).</term></item>
	///				<item><term>0x01000000</term><term>For Future Use.</term></item>
	///				<item><term>0x02000000</term><term>For Future Use.</term></item>
	///				<item><term>0x04000000</term><term>For Future Use.</term></item>
	///				<item><term>0x08000000</term><term>For Future Use.</term></item>
	///				<item><term>0x10000000</term><term>For Future Use.</term></item>
	///				<item><term>0x20000000</term><term>Active (1=Indicates Unit Is Active, 0=Not Active).</term></item>
	///				<item><term>0x40000000</term><term>Error (mirrors LED for rack based modules.</term></item>
	///				<item><term>0x80000000</term><term>Channel enabled (1=Enabled, 0=Disabled).</term></item>
	/// 		  </list> <remarks> Bits 21 to 28 (Digital Input States) are only applicable if the associated digital input is fitted to your controller - see the relevant handbook for more details. </remarks> </returns>
	/// <seealso cref="PPC2_RequestStatusBits(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_RequestStatus(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_StartPolling(char const * serialNo, int channel, int milliseconds)" />
	BENCHPRECISIONPIEZO_API DWORD __cdecl PPC2_GetStatusBits(char const * serialNo, int channel);

	/// <summary>	Resets all parameters to power-up values. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_ResetParameters(char const * serialNo, int channel);

	/// <summary> Sets the voltage output to zero and defines the ensuing actuator position az zero. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_SetZero(char const * serialNo, int channel);

	/// <summary>	Requests the position. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">  The channel. </param>
	/// <seealso cref="PPC2_RequestPosition(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_GetPosition(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_SetPosition(char const * serialNo, int channel, short position)" />
	/// <seealso cref="PPC2_SetPositionToTolerance(char const * serialNo, int channel, short position, short tolerance)" />
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_RequestActualPosition(char const * serialNo, int channel);

	/// <summary> Requests the current output voltage or position depending on current mode. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <remarks> This needs to be called to get the device to send it's current position.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="PPC2_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="channel">	The device channel. </param>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="PPC2_RequestActualPosition(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_GetPosition(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_StartPolling(char const * serialNo, int channel, int milliseconds)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_RequestPosition(char const * serialNo, int channel);

	/// <summary> Gets the Position Control Mode. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <returns> The control mode <list type=table>
	///				<item><term>Open Loop</term><term>1</term></item>
	///				<item><term>Closed Loop</term><term>2</term></item>
	///				<item><term>Open Loop smoothed</term><term>3</term></item>
	///				<item><term>Closed Loop smoothed</term><term>4</term></item>
	/// 		  </list> </returns>
	/// <seealso cref="PPC2_SetPositionControlMode(char const * serialNo, int channel, PZ_ControlModeTypes mode)" />
	BENCHPRECISIONPIEZO_API PZ_ControlModeTypes __cdecl PPC2_GetPositionControlMode(char const * serialNo, int channel);

	/// <summary> Sets the Position Control Mode. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <param name="mode"> The control mode <list type=table>
	///				<item><term>Open Loop</term><term>1</term></item>
	///				<item><term>Closed Loop</term><term>2</term></item>
	///				<item><term>Open Loop smoothed</term><term>3</term></item>
	///				<item><term>Closed Loop smoothed</term><term>4</term></item>
	/// 		  </list>. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC2_GetPositionControlMode(char const * serialNo, int channel)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_SetPositionControlMode(char const * serialNo, int channel, PZ_ControlModeTypes mode);

	// Voltage Functions

	/// <summary> Gets the minimum output voltage. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <returns> The minimum output voltage, normally -30 for Precision Piezo. </returns>
	/// <seealso cref="PPC2_SetMaxOutputVoltage(char const * serialNo, int channel, short maxVoltage)" />
	/// <seealso cref="PPC2_GetMaxOutputVoltage(char const * serialNo, int channel)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_GetMinOutputVoltage(char const * serialNo, int channel);

	/// <summary> Gets the maximum output voltage. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <returns> The maximum output voltage, range 0 to 1500 (0.0 to 150.0 Volts). </returns>
	/// <seealso cref="PPC2_RequestMaxOutputVoltage(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_SetMaxOutputVoltage(char const * serialNo, int channel, short maxVoltage)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_GetMaxOutputVoltage(char const * serialNo, int channel);

	/// <summary> Requests the maximum output voltage be read from the device. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="PPC2_GetMaxOutputVoltage(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_SetMaxOutputVoltage(char const * serialNo, int channel, short maxVoltage)" />
	BENCHPRECISIONPIEZO_API bool __cdecl PPC2_RequestMaxOutputVoltage(char const * serialNo, int channel);

	/// <summary> Sets the maximum output voltage. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <param name="maxVoltage">	The maximum output voltage, 0 to 1500 (0.0 to 150.0 Volts). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC2_GetMaxOutputVoltage(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_RequestMaxOutputVoltage(char const * serialNo, int channel)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_SetMaxOutputVoltage(char const * serialNo, int channel, short maxVoltage);

	/// <summary> Gets the set Output Voltage. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <returns> The voltage as a percentage of MaxOutputVoltage,<br />
	/// 		  range -32767 to 32767 equivalent to -100% to 100%. </returns>
	/// <seealso cref="PPC2_SetOutputVoltage(char const * serialNo, int channel, short volts)" />
	/// <seealso cref="PPC2_RequestOutputVoltage(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_SetMaxOutputVoltage(char const * serialNo, int channel, short eVoltage)" />
	/// <seealso cref="PPC2_GetMaxOutputVoltage(char const * serialNo, int channel)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_GetOutputVoltage(char const * serialNo, int channel);

	/// <summary> Requests the Output Voltage be read from the device. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="PPC2_GetOutputVoltage(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_SetOutputVoltage(char const * serialNo, int channel, short volts)" />
	/// <seealso cref="PPC2_SetMaxOutputVoltage(char const * serialNo, int channel, short eVoltage)" />
	/// <seealso cref="PPC2_GetMaxOutputVoltage(char const * serialNo, int channel)" />
	BENCHPRECISIONPIEZO_API bool __cdecl PPC2_RequestOutputVoltage(char const * serialNo, int channel);

	/// <summary> Sets the output voltage. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <param name="volts"> The voltage as a percentage of MaxOutputVoltage,<br />
	/// 		  range -32767 to 32767 equivalent to -100% to 100%. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC2_RequestOutputVoltage(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_GetOutputVoltage(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_SetMaxOutputVoltage(char const * serialNo, int channel, short eVoltage)" />
	/// <seealso cref="PPC2_GetMaxOutputVoltage(char const * serialNo, int channel)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_SetOutputVoltage(char const * serialNo, int channel, short volts);


	/// <summary> Requests that the current input voltage source be read from the device. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="PPC2_GetVoltageSource(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_SetVoltageSource(char const * serialNo, int channel, PZ_InputSourceFlags source)" />
	BENCHPRECISIONPIEZO_API bool __cdecl PPC2_RequestVoltageSource(char const * serialNo, int channel);

	/// <summary> Gets the control voltage source. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <returns> The voltage source. <list type=table>
	///				<item><term>Software Only</term><term>0</term></item>
	///				<item><term>Software and External</term><term>1</term></item>
	///				<item><term>Software and Potentiometer</term><term>2</term></item>
	///				<item><term>Software, External and Potentiometer</term><term>3</term></item>
	/// 		  </list> </returns>
	/// <seealso cref="PPC2_RequestVoltageSource(char const * serialNo, short channel)" />
	/// <seealso cref="PPC2_SetVoltageSource(char const * serialNo, PZ_InputSourceFlags source)" />
	BENCHPRECISIONPIEZO_API PZ_InputSourceFlags __cdecl PPC2_GetVoltageSource(char const * serialNo, int channel);

	/// <summary> Sets the control voltage source. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <param name="source"> The voltage source <list type=table>
	///				<item><term>Software Only</term><term>0</term></item>
	///				<item><term>Software and External</term><term>1</term></item>
	///				<item><term>Software and Potentiometer</term><term>2</term></item>
	///				<item><term>Software, External and Potentiometer</term><term>3</term></item>
	/// 		  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC2_RequestVoltageSource(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_GetVoltageSource(char const * serialNo, int channel)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_SetVoltageSource(char const * serialNo, int channel, PZ_InputSourceFlags source);

	/// <summary> Gets the maximum travel of the device. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <remarks> This requires an actuator with built in position sensing</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <returns>	The distance in steps of 100nm,<br />
	/// 			range 0 to 65535 (10000 is equivalent to 1mm). </returns>
	BENCHPRECISIONPIEZO_API WORD __cdecl PPC2_GetMaximumTravel(char const * serialNo, int channel);

	/// <summary> Gets the position when in closed loop mode. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <remarks> The result is undefined if not in closed loop mode</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <returns> The position as a percentage of maximum travel,<br />
	/// 		  range -32767 to 32767, equivalent to -100 to 100%. </returns>
	/// <seealso cref="PPC2_RequestActualPosition(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_SetPosition(char const * serialNo, int channel, short position)" />
	/// <seealso cref="PPC2_SetPositionToTolerance(char const * serialNo, int channel, short position, short tolerance)" />
	/// <seealso cref="PPC2_SetPositionControlMode(char const * serialNo, int channel, PZ_ControlModeTypes mode)" />
	/// <seealso cref="PPC2_GetPositionControlMode(char const * serialNo, int channel)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_GetPosition(char const * serialNo, int channel);

	/// <summary> Sets the position when in closed loop mode. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <remarks> The command is ignored if not in closed loop mode</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <param name="position"> The position as a percentage of maximum travel,<br />
	/// 		  range 0 to 32767, equivalent to 0 to 100%. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC2_RequestPosition(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_RequestActualPosition(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_SetPositionToTolerance(char const * serialNo, int channel, short position, short tolerance)" />
	/// <seealso cref="PPC2_GetPosition(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_SetPositionControlMode(char const * serialNo, int channel, PZ_ControlModeTypes mode)" />
	/// <seealso cref="PPC2_GetPositionControlMode(char const * serialNo, int channel)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_SetPosition(char const * serialNo, int channel, short position);

	/// <summary> Sets the position when in closed loop mode. </summary>
	/// <remarks> The command is ignored if not in closed loop mode</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">  The channel. </param>
	/// <param name="position"> The position as a percentage of maximum travel,<br />
	/// 		  range 0 to 32767, equivalent to 0 to 100%. </param>
	/// <param name="tolerance"> The tolerance in position as a percentage of maximum travel,<br />
	/// 		  range 0 to 32767, equivalent to 0 to 100%. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC2_RequestPosition(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_RequestActualPosition(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_SetPosition(char const * serialNo, int channel, short position)" />
	/// <seealso cref="PPC2_GetPosition(char const * serialNo, int channel)" />
	/// <seealso cref="PPC2_SetPositionControlMode(char const * serialNo, int channel, PZ_ControlModeTypes mode)" />
	/// <seealso cref="PPC2_GetPositionControlMode(char const * serialNo, int channel)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_SetPositionToTolerance(char const * serialNo, int channel, short position, short tolerance);

	/// <summary> Gets the PPC IO Settings. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <param name="ioSettings"> The i/o settings <see cref="PPC2_IOSettings"/>. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC2_SetIOSettings(const char * serialNo, int channel, PPC_IOSettings *ioSettings)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_GetIOSettings(const char * serialNo, int channel, PPC_IOSettings *ioSettings);

	/// <summary> Sets the PPC IO Setting. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <param name="ioSettings"> The i/o setting <see cref="PPC2_IOSettings"/>. </returns> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC2_GetIOSettings(const char * serialNo, int channel, PPC_IOSettings *ioSettings)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_SetIOSettings(const char * serialNo, int channel, PPC_IOSettings *ioSettings);

	/// <summary> Gets the PPC Notch Filter Parameters. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <remarks> The PPC Notch Filter Parameters. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <param name="notchParams"> Options for controlling the notch <see cref="PPC2_NotchParams"/>. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC2_SetNotchParams(const char * serialNo, int channel, PPC_NotchParams *notchParams)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_GetNotchParams(const char * serialNo, int channel, PPC_NotchParams *notchParams);

	/// <summary> Sets the PPC Notch Filter Parameters. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <param name="notchParams"> The PPC Notch Filter Parameters <see cref="PPC2_NotchParams"/>. </returns> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC2_GetNotchParams(const char * serialNo, int channel, PPC_NotchParams *notchParams)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_SetNotchParams(const char * serialNo, int channel, PPC_NotchParams *notchParams);

	/// <summary> Requests that the PPC PID Constants be read from the device. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For single channel use PPC_ equivalent.</I></remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="PPC2_GetPIDConsts(const char * serialNo, int channel, PPC_PIDConsts *pidConsts)" />
	/// <seealso cref="PP2C_SetPIDConsts(const char * serialNo, int channel, PPC_PIDConsts *pidConsts)" />
	BENCHPRECISIONPIEZO_API bool __cdecl PPC2_RequestPIDConsts(const char * serialNo, int channel);

	/// <summary> Gets the PPC PID Constants. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <param name="pidConsts"> The PID consts <see cref="PPC2_PIDConsts"/>. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC2_RequestPIDConsts(const char * serialNo, int channel)" />
	/// <seealso cref="PPC2_SetPIDConsts(const char * serialNo, int channel, PPC_PIDConsts *pidConsts)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_GetPIDConsts(const char * serialNo, int channel, PPC_PIDConsts *pidConsts);

	/// <summary> Sets the PPC PID Constants. </summary>
	/// <remarks> <I>Applies to Multi Channel Precision Piezo Devices only. For Single channel use PPC_ equivalent.</I></remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The device channel. </param>
	/// <param name="pidConsts"> The PPC PID Constants <see cref="PPC2_PIDConsts"/>. </returns> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC2_RequestPIDConsts(const char * serialNo, int channel)" />
	/// <seealso cref="PPC2_GetPIDConsts(const char * serialNo, int channel, PPC_PIDConsts *pidConsts)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_SetPIDConsts(const char * serialNo, int channel, PPC_PIDConsts *pidConsts);

	/// <summary> Requests the rack digital output bits. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC2_SetRackDigitalOutputs(char const * serialNo, byte outputsBits)" />
	/// <seealso cref="PPC2_GetRackDigitalOutputs(char const * serialNo)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_RequestRackDigitalOutputs(char const * serialNo);

	/// <summary> Gets the rack digital output bits. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> Bit mask of states of the 4 digital output pins. </returns>
	/// <seealso cref="PPC2_SetRackDigitalOutputs(char const * serialNo, byte outputsBits)" />
	/// <seealso cref="PPC2_RequestRackDigitalOutputs(char const * serialNo)" />
	BENCHPRECISIONPIEZO_API byte __cdecl PPC2_GetRackDigitalOutputs(char const * serialNo);

	/// <summary> Sets the rack digital output bits. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="outputsBits"> Bit mask to set states of the 4 digital output pins. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC2_GetRackDigitalOutputs(char const * serialNo)" />
	/// <seealso cref="PPC2_RequestRackDigitalOutputs(char const * serialNo)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_SetRackDigitalOutputs(char const * serialNo, byte outputsBits);

	/// <summary> Requests the Rack status bits be downloaded. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PPC2_GetRackStatusBits(char const * serialNo)" />
	BENCHPRECISIONPIEZO_API short __cdecl PPC2_RequestRackStatusBits(char const * serialNo);

	/// <summary> Gets the Rack status bits. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The status bits including 4 with one per electronic input pin. </returns>
	/// <seealso cref="PPC2_RequestRackStatusBits(char const * serialNo)" />
	BENCHPRECISIONPIEZO_API DWORD __cdecl PPC2_GetRackStatusBits(char const * serialNo);

}
/** @} */ // BenchtopPrecisionPiezo
