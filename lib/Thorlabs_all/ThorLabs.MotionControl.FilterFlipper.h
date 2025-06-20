// summary:	Declares the functions class
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the FILTERFLIPPERDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// FILTERFLIPPERDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef FILTERFLIPPERDLL_EXPORTS
#define FILTERFLIPPERDLL_API __declspec(dllexport)
#else
#define FILTERFLIPPERDLL_API __declspec(dllimport)
#endif

#include <OaIdl.h>

#pragma once

/** @defgroup FilterFlipper FilterFlipper
 *  This section details the Structures and Functions relavent to the  @ref MFF101_page "Filter Flipper"<br />
 *  For an example of how to connect to the device and perform simple operations use the following links:
 *  <list type=bullet>
 *    <item> \ref namespaces_mff_ex_1 "Example of using the Thorlabs.MotionControl.FilterFlipper.DLL from a C or C++ project."<br />
 *									  This requires the DLL to be dynamical linked. </item>
 *    <item> \ref namespaces_mff_ex_2 "Example of using the Thorlabs.MotionControl.FilterFlipper.DLL from a C# project"<br />
 *									  This uses Marshalling to load and access the C DLL. </item>
 *  </list>
 *  The Thorlabs.MotionControl.FilterFlipper.DLL requires the following DLLs
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

	/// <summary> Values that represent the two filter flipper positions. </summary>
	typedef enum FF_Positions : int
	{
		FF_PositionError=0,///<Position error
		Position1 = 0x01,///<Position 1
		Position2 = 0x02,///<Position 2
	} FF_Positions;

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

	/// <summary> FilterFlipper IO operations. </summary>
	typedef enum FF_IOModes : WORD
	{
		/// <summary> Input Mode - FilterFlipper toggles when signalled (See <see cref="FF_SignalModes" />). </summary>
		FF_ToggleOnPositiveEdge = 0x01, 
		/// <summary> Input Mode - FilterFlipper goes to position when signalled (See <see cref="FF_SignalModes" />) </summary>
		FF_SetPositionOnPositiveEdge = 0x02, 
		/// <summary> Output Mode - Output signal set to match position, where 2 = Hi, 1 = Lo. </summary>
		FF_OutputHighAtSetPosition = 0x04, 
		/// <summary> Output Mode - Output signal high when FilterFlipper is moving. </summary>
		FF_OutputHighWhemMoving = 0x08, 
	} FF_IOModes;

	/// <summary> FilterFlipper IO operations. </summary>
	typedef enum FF_SignalModes : WORD
	{
		/// <summary> Signal is raised when Button Pressed i.e. Hi to Lo. Action taken is defined by <see cref="FF_IOModes" />. </summary>
		FF_InputButton = 0x01, 
		/// <summary> Signal is raised on on rising edge Lo to Hi. Action taken is defined by <see cref="FF_IOModes" />. </summary>
		FF_InputLogic = 0x02, 
		/// <summary> when set will swap Position 1 and 2. </summary>
		FF_InputSwap = 0x04, 
		/// <summary> Output is set to either be hi when flipper at Position 2 or flipper is moving (see <see cref="FF_IOModes" />). </summary>
		FF_OutputLevel = 0x10, 
		/// <summary> Output is set to pulse when flipper operates, either when flipper reaches Position or flipper starts moving (see <see cref="FF_IOModes" />). </summary>
		FF_OutputPulse = 0x20, 
		/// <summary> when set will swap output logic levels. </summary>
		FF_OutputSwap = 0x40, 
	} FF_SignalModes;

	/// <summary> Structure containing settings specific to filter flipper input / output. </summary>
	typedef struct FF_IOSettings
	{
		/// <summary> Time taken to get from one position to other in milliseconds.<br />
		/// 		  Range 300 to 2800 ms. </summary>
		unsigned int transitTime;
		/// <summary> Value derived from transition time in ADC units. </summary>
		unsigned int ADCspeedValue;
		/// <summary> I/O 1 Operating Mode
		/// 		  <list type=table>
		///				<item><term>Input Mode - FilterFlipper toggles when signalled (See <see cref="FF_SignalModes" />)</term><term>0x01</term></item>
		///				<item><term>Input Mode - FilterFlipper goes to position when signalled (See <see cref="FF_SignalModes" />)</term><term>0x02</term></item>
		///				<item><term>Output Mode - Output signal set to match position, where 2 = Hi, 1 = Lo</term><term>0x04</term></item>
		///				<item><term>Output Mode - Output signal high when FilterFlipper is moving</term><term>0x08</term></item>
		/// 		  </list> </summary>
		FF_IOModes digIO1OperMode;
		/// <summary> I/O 1 Signal Mode
		/// 		  <list type=table>
		///				<item><term>Signal is raised when Button Pressed i.e. Hi to Lo. Action taken is defined by <see cref="FF_IOModes" /></term><term>0x01</term></item>
		///				<item><term>Signal is raised on on rising edge Lo to Hi. Action taken is defined by <see cref="FF_IOModes" /></term><term>0x02</term></item>
		///				<item><term>Toggle Positions, when set will swap Position 1 and 2</term><term>0x04</term></item>
		///				<item><term>Output is set to either be hi when flipper at Position 2 or flipper is moving (see <see cref="FF_IOModes" />)</term><term>0x10</term></item>
		///				<item><term>Output is set to pulse when flipper operates, either when flipper reaches Position or flipper starts moving (see <see cref="FF_IOModes" />)</term><term>0x20</term></item>
		///				<item><term>Toggle output levels, when set will swap output logic levels</term><term>0x40</term></item>
		/// 		  </list> </summary>
		FF_SignalModes digIO1SignalMode;
		/// <summary> Digital IO 1 pulse width in milliseconds,<br />
		/// 		  Range 10 to 200 ms. </summary>
		unsigned int digIO1PulseWidth;
		/// <summary> I/O 2 Operating Mode
		/// 		  <list type=table>
		///				<item><term>Input Mode - FilterFlipper toggles when signalled (See <see cref="FF_SignalModes" />)</term><term>0x01</term></item>
		///				<item><term>Input Mode - FilterFlipper goes to position when signalled (See <see cref="FF_SignalModes" />)</term><term>0x02</term></item>
		///				<item><term>Output Mode - Output signal set to match position, where 2 = Hi, 1 = Lo</term><term>0x04</term></item>
		///				<item><term>Output Mode - Output signal high when FilterFlipper is moving</term><term>0x08</term></item>
		/// 		  </list> </summary>
		FF_IOModes digIO2OperMode;
		/// <summary> I/O 2 Signal Mode
		/// 		  <list type=table>
		///				<item><term>Signal is raised when Button Pressed i.e. Hi to Lo. Action taken is defined by <see cref="FF_IOModes" /></term><term>0x01</term></item>
		///				<item><term>Signal is raised on on rising edge Lo to Hi. Action taken is defined by <see cref="FF_IOModes" /></term><term>0x02</term></item>
		///				<item><term>Toggle Positions, when set will swap Position 1 and 2</term><term>0x04</term></item>
		///				<item><term>Output is set to either be hi when flipper at Position 2 or flipper is moving (see <see cref="FF_IOModes" />)</term><term>0x10</term></item>
		///				<item><term>Output is set to pulse when flipper operates, either when flipper reaches Position or flipper starts moving (see <see cref="FF_IOModes" />)</term><term>0x20</term></item>
		///				<item><term>Toggle output levels, when set will swap output logic levels</term><term>0x40</term></item>
		/// 		  </list> </summary>
		FF_SignalModes digIO2SignalMode;
		/// <summary> Digital IO 2 pulse width in milliseconds,<br />
		/// 		  Range 10 to 200 ms. </summary>
		unsigned int digIO2PulseWidth;
		/// <summary> Not used. </summary>
		int reserved1;
		/// <summary> Not used. </summary>
		unsigned int reserved2;
	} FF_IOSettings;

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
	FILTERFLIPPERDLL_API short __cdecl TLI_BuildDeviceList(void);

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
	FILTERFLIPPERDLL_API short __cdecl TLI_GetDeviceListSize();

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
	FILTERFLIPPERDLL_API short __cdecl TLI_GetDeviceList(SAFEARRAY** stringsReceiver);

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
	FILTERFLIPPERDLL_API short __cdecl TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID);

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
	FILTERFLIPPERDLL_API short __cdecl TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length);

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
	FILTERFLIPPERDLL_API short __cdecl TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer);

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
	FILTERFLIPPERDLL_API short __cdecl TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID);

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
	FILTERFLIPPERDLL_API short __cdecl TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length);

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
	FILTERFLIPPERDLL_API short __cdecl TLI_GetDeviceInfo(char const * serialNo, TLI_DeviceInfo *info);

	/// <summary> Initialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <remarks> Call TLI_InitializeSimulations before TLI_BuildDeviceList at the start of the program to make a connection to the simulation manager.<Br />
	/// 		  Any devices configured in the simulation manager will become visible TLI_BuildDeviceList is called and can be accessed using TLI_GetDeviceList.<Br />
	/// 		  Call TLI_InitializeSimulations at the end of the program to release the simulator.  </remarks>
	/// <seealso cref="TLI_UninitializeSimulations()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	FILTERFLIPPERDLL_API void __cdecl TLI_InitializeSimulations();

	/// <summary> Uninitialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <seealso cref="TLI_InitializeSimulations()" />
	FILTERFLIPPERDLL_API void __cdecl TLI_UninitializeSimulations();

	/// <summary> Open the device for communications. </summary>
	/// <param name="serialNo">	The serial no of the device to be connected. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="FF_Close(char const * serialNo)" />
	FILTERFLIPPERDLL_API short __cdecl FF_Open(char const * serialNo);

	/// <summary> Disconnect and close the device. </summary>
	/// <param name="serialNo">	The serial no of the device to be disconnected. </param>
    /// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="FF_Open(char const * serialNo)" />
	FILTERFLIPPERDLL_API void __cdecl FF_Close(char const * serialNo);

	/// <summary>	Check connection. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> true if the USB is listed by the ftdi controller</returns>
	/// \include CodeSnippet_CheckConnection.cpp
	FILTERFLIPPERDLL_API bool __cdecl FF_CheckConnection(char const * serialNo);

	/// <summary> Sends a command to the device to make it identify iteself. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	FILTERFLIPPERDLL_API void __cdecl FF_Identify(char const * serialNo);

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
	FILTERFLIPPERDLL_API short __cdecl FF_GetHardwareInfo(char const * serialNo, char * modelNo, DWORD sizeOfModelNo, WORD * type, WORD * numChannels, 
													   char * notes, DWORD sizeOfNotes, DWORD * firmwareVersion, WORD * hardwareVersion, WORD * modificationState);

	/// <summary> Gets version number of firmware. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The firmware version number made up of 4 byte parts. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	FILTERFLIPPERDLL_API DWORD __cdecl FF_GetFirmwareVersion(char const * serialNo);

	/// <summary> Gets version number of the device software. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device software version number made up of 4 byte parts. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	FILTERFLIPPERDLL_API DWORD __cdecl FF_GetSoftwareVersion(char const * serialNo);

	/// <summary> Update device with stored settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
    /// 		  \include CodeSnippet_connection1.cpp
	FILTERFLIPPERDLL_API bool __cdecl FF_LoadSettings(char const * serialNo);

	/// <summary> Update device with named settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="settingsName"> Name of settings stored away from device. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	///             \include CodeSnippet_connection1.cpp
	FILTERFLIPPERDLL_API bool __cdecl FF_LoadNamedSettings(char const * serialNo, char const *settingsName);

	/// <summary> Persist the devices current settings. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	FILTERFLIPPERDLL_API bool __cdecl FF_PersistSettings(char const * serialNo);

	/// <summary> Get number of positions. </summary>
	/// <remarks> The GetNumberPositions function will get the maximum position reachable by the device.<br />
	/// 		  The motor may need to be \ref C_MOTOR_sec10 "Homed" before this parameter can be used. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The number of positions. </returns>
	/// <seealso cref="FF_MoveToPosition(char const * serialNo, int index)" />
	/// <seealso cref="FF_GetPosition(char const * serialNo)" />
	/// <seealso cref="FF_Home(char const * serialNo)" />
    /// 		  \include CodeSnippet_move.cpp
	FILTERFLIPPERDLL_API int __cdecl FF_GetNumberPositions(char const * serialNo);

	/// <summary> Home the device. </summary>
	/// <remarks> Homing the device will set the device to a known state and determine the home position. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if move successfully started. </returns>
	/// <seealso cref="FF_GetNumberPositions(char const * serialNo)" />
	/// <seealso cref="FF_MoveToPosition(char const * serialNo, int index)" />
	/// <seealso cref="FF_GetPosition(char const * serialNo)" />
    /// 		  \include CodeSnippet_move.cpp
	FILTERFLIPPERDLL_API short __cdecl FF_Home(char const * serialNo);

	/// <summary> Move the device to the specified position (index). </summary>
	/// <remarks> The motor may need to be \ref C_MOTOR_sec10 "Homed" before a position can be set</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="position"> The required position. must be 1 or 2. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if move successfully started. </returns>
	/// <seealso cref="FF_GetNumberPositions(char const * serialNo)" />
	/// <seealso cref="FF_GetPosition(char const * serialNo)" />
	/// <seealso cref="FF_Home(char const * serialNo)" />
    /// 		  \include CodeSnippet_move.cpp
	FILTERFLIPPERDLL_API short __cdecl FF_MoveToPosition(char const * serialNo, FF_Positions position);

	/// <summary> Get the current position. </summary>
	/// <remarks> The current position is the last recorded position.<br />
	/// 		  The current position is updated either by the polling mechanism or<br />
	/// 		  by calling <see cref="RequestPosition" /> or <see cref="RequestStatus" />.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The current position 1 or 2. </returns>
	/// <seealso cref="FF_GetNumberPositions(char const * serialNo)" />
	/// <seealso cref="FF_MoveToPosition(char const * serialNo, int index)" />
	/// <seealso cref="FF_Home(char const * serialNo)" />
    /// 		  \include CodeSnippet_move.cpp
	FILTERFLIPPERDLL_API FF_Positions __cdecl FF_GetPosition(char const * serialNo);

	/// <summary> Gets the I/O settings from filter flipper. </summary>
	/// <param name="serialNo">  The device serial no. </param>
	/// <param name="settings"> The address of the FF_IOSettings structure to receive the Filter Flipper I/O settings. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="FF_SetIOSettings(const char * serialNo, FF_IOSettings *settings)" />
	/// <seealso cref="FF_RequestIOSettings(const char * serialNo)" />
	FILTERFLIPPERDLL_API short __cdecl FF_GetIOSettings(const char * serialNo, FF_IOSettings *settings);

	/// <summary>	Requests the I/O settings from filter flipper. </summary>
	/// <param name="serialNo">	The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="FF_GetIOSettings(const char * serialNo, FF_IOSettings *settings)" />
	/// <seealso cref="FF_SetIOSettings(const char * serialNo, FF_IOSettings *settings)" />
	FILTERFLIPPERDLL_API short __cdecl FF_RequestIOSettings(const char * serialNo);

	/// <summary> Sets the settings on filter flipper. </summary>
	/// <param name="serialNo">  The device serial no. </param>
	/// <param name="settings"> The address of the FF_IOSettings structure containing the new Filter Flipper I/O settings. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="FF_GetIOSettings(const char * serialNo, FF_IOSettings *settings)" />
	/// <seealso cref="FF_RequestIOSettings(const char * serialNo)" />
	FILTERFLIPPERDLL_API short __cdecl FF_SetIOSettings(const char * serialNo, FF_IOSettings *settings);

	/// <summary> Gets the transit time. </summary>
	/// <param name="serialNo">  The device serial no. </param>
	/// <returns> The transit time in milliseconds, range 300 to 2800 ms. </returns>
	/// <seealso cref="FF_SetTransitTime(const char * serialNo, unsigned int transitTime)" />
	FILTERFLIPPERDLL_API unsigned int __cdecl FF_GetTransitTime(const char * serialNo);

	/// <summary> Sets the transit time. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="transitTime"> The transit time in milliseconds, range 300 to 2800 ms. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="FF_GetTransitTime(const char * serialNo)" />
	FILTERFLIPPERDLL_API short __cdecl FF_SetTransitTime(const char * serialNo, unsigned int transitTime);

	/// <summary>	Request status bits. </summary>
	/// <remarks> This needs to be called to get the device to send it's current status.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="FF_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="FF_GetStatusBits(char const * serialNo)" />
	/// <seealso cref="FF_StartPolling(char const * serialNo, int milliseconds)" />
	FILTERFLIPPERDLL_API short __cdecl FF_RequestStatus(char const * serialNo);

	/// <summary>Get the current status bits. </summary>
	/// <remarks> This returns the latest status bits received from the device.<br />
	/// 		  To get new status bits, use <see cref="FF_RequestStatus(char const * serialNo)" />
	/// 		  or use the polling functions, <see cref="FF_StartPolling(char const * serialNo, int milliseconds)" />.  </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	The status bits from the device <list type=table>
	///				<item><term>0x00000001</term><term>CW hardware limit switch (0=No contact, 1=Contact).</term></item>
	///				<item><term>0x00000002</term><term>CCW hardware limit switch (0=No contact, 1=Contact).</term></item>
	///				<item><term>0x00000004</term><term>Not applicable.</term></item>
 	///				<item><term>0x00000008</term><term>Not applicable.</term></item>
	///				<item><term>0x00000010</term><term>Not applicable.</term></item>
 	///				<item><term>0x00000020</term><term>Not applicable.</term></item>
	///				<item><term>0x00000040</term><term>Shaft jogging clockwise (1=Moving, 0=Stationary).</term></item>
	///				<item><term>0x00000080</term><term>Shaft jogging counterclockwise (1=Moving, 0=Stationary).</term></item>
 	///				<item><term>0x00000100</term><term>Not applicable.</term></item>
	///				<item><term>0x00000200</term><term></term></item>
	///				<item><term>...</term><term></term></item>
	///				<item><term>0x00080000</term><term></term></item>
	///				<item><term>0x00100000</term><term>Digital input 1 state (1=Logic high, 0=Logic low).</term></item>
	///				<item><term>0x00200000</term><term>Digital input 2 state (1=Logic high, 0=Logic low).</term></item>
 	///				<item><term>0x00400000</term><term>Not applicable.</term></item>
	///				<item><term>0x00800000</term><term></term></item>
	///				<item><term>...</term><term></term></item>
	///				<item><term>0x00080000</term><term></term></item>
	///				<item><term>0x00100000</term><term>General Digital Input 1.</term></item>
	///				<item><term>0x00200000</term><term>General Digital Input 2.</term></item>
	///				<item><term>0x00400000</term><term>General Digital Input 3.</term></item>
	///				<item><term>0x00800000</term><term>General Digital Input 4.</term></item>
	///				<item><term>0x01000000</term><term>General Digital Input 5.</term></item>
	///				<item><term>0x02000000</term><term>General Digital Input 6.</term></item>
	///				<item><term>0x04000000</term><term>For Future Use.</term></item>
	///				<item><term>0x08000000</term><term>For Future Use.</term></item>
	///				<item><term>0x10000000</term><term>For Future Use.</term></item>
	///				<item><term>0x20000000</term><term>Active (1=Active, 0=Not active).</term></item>
	///				<item><term>0x40000000</term><term>For Future Use.</term></item>
	///				<item><term>0x80000000</term><term>Channel enabled (1=Enabled, 0=Disabled).</term></item>
	/// 		  </list> <remarks> Bits 21 and 22 (Digital Input States) are only applicable if the associated digital input is fitted to your controller - see the relevant handbook for more details. </remarks> </returns>
	/// <seealso cref="FF_RequestStatus(char const * serialNo)" />
	/// <seealso cref="FF_StartPolling(char const * serialNo, int milliseconds)" />
	FILTERFLIPPERDLL_API DWORD __cdecl FF_GetStatusBits(char const * serialNo);

	/// <summary> Starts the internal polling loop which continuously requests position and status. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="milliseconds">The milliseconds polling rate. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="FF_StopPolling(char const * serialNo)" />
	/// <seealso cref="FF_PollingDuration(char const * serialNo)" />
	/// <seealso cref="FF_RequestStatus(char const * serialNo)" />
	/// <seealso cref="FF_RequestPosition(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	FILTERFLIPPERDLL_API bool __cdecl FF_StartPolling(char const * serialNo, int milliseconds);

	/// <summary> Gets the polling loop duration. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The time between polls in milliseconds or 0 if polling is not active. </returns>
	/// <seealso cref="FF_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="FF_StopPolling(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	FILTERFLIPPERDLL_API long __cdecl FF_PollingDuration(char const * serialNo);

	/// <summary> Stops the internal polling loop. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <seealso cref="FF_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="FF_PollingDuration(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	FILTERFLIPPERDLL_API void __cdecl FF_StopPolling(char const * serialNo);

	/// <summary> Gets the time in milliseconds since tha last message was received from the device. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="lastUpdateTimeMS"> The time since the last message was received in milliseconds. </param>
	/// <returns> True if monitoring is enabled otherwize False. </returns>
	/// <seealso cref="FF_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// <seealso cref="FF_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	FILTERFLIPPERDLL_API bool __cdecl FF_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS );

	/// <summary> Enables the last message monitoring timer. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="enable"> True to enable monitoring otherwise False to disable. </param>
	/// <param name="lastMsgTimeout"> The last message error timeout in ms. 0 to disable. </param>
	/// <seealso cref="FF_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="FF_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	FILTERFLIPPERDLL_API void __cdecl FF_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout );

	/// <summary> Queries if the time since the last message has exceeded the lastMsgTimeout set by <see cref="FF_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )"/>. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> True if last message timer has elapsed, False if monitoring is not enabled or if time of last message received is less than lastMsgTimeout. </returns>
	/// <seealso cref="FF_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="FF_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	FILTERFLIPPERDLL_API bool __cdecl FF_HasLastMsgTimerOverrun(char const * serialNo);

	/// <summary> Requests that all settings are download from device. </summary>
	/// <remarks> This function requests that the device upload all it's settings to the DLL.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	FILTERFLIPPERDLL_API short __cdecl FF_RequestSettings(char const * serialNo);

	/// <summary> Clears the device message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	FILTERFLIPPERDLL_API void __cdecl FF_ClearMessageQueue(char const * serialNo);

	/// <summary> Registers a callback on the message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="functionPointer"> A function pointer to be called whenever messages are received. </param>
	/// <seealso cref="FF_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="FF_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="FF_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	FILTERFLIPPERDLL_API void __cdecl FF_RegisterMessageCallback(char const * serialNo, void (* functionPointer)());

	/// <summary> Gets the MessageQueue size. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> number of messages in the queue. </returns>
	/// <seealso cref="FF_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="FF_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="FF_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	FILTERFLIPPERDLL_API int __cdecl FF_MessageQueueSize(char const * serialNo);

	/// <summary> Get the next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="FF_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="FF_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="FF_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	FILTERFLIPPERDLL_API bool __cdecl FF_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Wait for next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="FF_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="FF_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="FF_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	FILTERFLIPPERDLL_API bool __cdecl FF_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);
}
/** @} */ // FilterFlipper
