// summary:	Declares the functions class
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the BENCHPIEZO_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// BENCHPIEZO_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#pragma once

#ifdef BENCHPIEZODLL_EXPORTS
#define BENCHPIEZO_API __declspec(dllexport)
#else
#define BENCHPIEZO_API __declspec(dllimport)
#endif

#include <OaIdl.h>

/** @defgroup BenchtopPiezo Benchtop Piezo
 *  This section details the Structures and Functions relavent to the  @ref BPC103_page "Benchtop Piezo"<br />
 *  For an example of how to connect to the device and perform simple operations use the following links:
 *  <list type=bullet>
 *    <item> \ref namespaces_bpc_ex_1 "Example of using the Thorlabs.MotionControl.Benchtop.Piezo.DLL from a C or C++ project."<br />
 *									  This requires the DLL to be dynamical linked. </item>
 *    <item> \ref namespaces_bpc_ex_2 "Example of using the Thorlabs.MotionControl.Benchtop.Piezo.DLL from a C# project"<br />
 *									  This uses Marshalling to load and access the C DLL. </item>
 *  </list>
 *  The Thorlabs.MotionControl.Benchtop.Piezo.DLL requires the following DLLs
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
	BENCHPIEZO_API short __cdecl TLI_BuildDeviceList(void);

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
	BENCHPIEZO_API short __cdecl TLI_GetDeviceListSize();

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
	BENCHPIEZO_API short __cdecl TLI_GetDeviceList(SAFEARRAY** stringsReceiver);

	/// <summary> Get the contents of the device list which match the supplied typeID. </summary>
	/// <param name="stringsReceiver"> Outputs a SAFEARRAY of strings holding device serial numbers. </param>
	/// <param name="typeID">					    The typeID of devices to match. </param>
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
	BENCHPIEZO_API short __cdecl TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID);

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
	BENCHPIEZO_API short __cdecl TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length);

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
	BENCHPIEZO_API short __cdecl TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer);

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
	BENCHPIEZO_API short __cdecl TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID);

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
	BENCHPIEZO_API short __cdecl TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length);

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
	BENCHPIEZO_API short __cdecl TLI_GetDeviceInfo(char const * serialNo, TLI_DeviceInfo *info);

	/// <summary> Initialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <remarks> Call TLI_InitializeSimulations before TLI_BuildDeviceList at the start of the program to make a connection to the simulation manager.<Br />
	/// 		  Any devices configured in the simulation manager will become visible TLI_BuildDeviceList is called and can be accessed using TLI_GetDeviceList.<Br />
	/// 		  Call TLI_UninitializeSimulations at the end of the program to release the simulator.  </remarks>
	/// <seealso cref="TLI_UninitializeSimulations()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	BENCHPIEZO_API void __cdecl TLI_InitializeSimulations();

	/// <summary> Uninitialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <seealso cref="TLI_InitializeSimulations()" />
	BENCHPIEZO_API void __cdecl TLI_UninitializeSimulations();

	/// <summary> Open the device for communications. </summary>
	/// <param name="serialNo">	The serial no of the controller to be connected. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_connectionN.cpp
	/// <seealso cref="PBC_Close(char const * serialNo)" />
	BENCHPIEZO_API short __cdecl PBC_Open(char const * serialNo);

	/// <summary> Disconnect and close the device. </summary>
	/// <param name="serialNo">	The serial no of the controller to be disconnected. </param>
    /// 		  \include CodeSnippet_connectionN.cpp
	/// <seealso cref="PBC_Open(char const * serialNo)" />
	BENCHPIEZO_API void __cdecl PBC_Close(char const * serialNo);

	/// <summary>	Check connection. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> true if the USB is listed by the ftdi controller</returns>
	/// \include CodeSnippet_CheckConnection.cpp
	BENCHPIEZO_API bool __cdecl PBC_CheckConnection(char const * serialNo);

	/// <summary> Sends a command to the device to make it identify iteself. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	BENCHPIEZO_API void __cdecl PBC_Identify(char const * serialNo, short channel);

	/// <summary> Tells the device that it is being disconnected. </summary>
	/// <remarks> This does not disconnect the communications.<br />
	/// 		  To disconnect the communications, call the <see cref="PBC_Close(char const * serialNo)" /> function. </remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PBC_Disconnect(char const * serialNo);

	/// <summary> Gets the number of channels available to this device. </summary>
	/// <remarks> This function returns ther number of available bays, not the number of bays filled.</remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <returns> The number of channels available on this device. </returns>
    /// 		  \include CodeSnippet_connectionN.cpp
	BENCHPIEZO_API int __cdecl PBC_MaxChannelCount(char const * serialNo);

	/// <summary> Verifies that the specified channel is valid. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The requested channel (1 to n). </param>
	/// <returns> <c>true</c> if the channel is valid. </returns>
    /// 		  \include CodeSnippet_connectionN.cpp
	BENCHPIEZO_API bool __cdecl PBC_IsChannelValid(char const * serialNo, short channel);

	/// <summary> Gets the hardware information from the device. </summary>
	/// <param name="serialNo">		    The controller serial no. </param>
	/// <param name="channel">		    The channel (1 to n). </param>
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
	BENCHPIEZO_API short __cdecl PBC_GetHardwareInfo(char const * serialNo, short channel, char * modelNo, DWORD sizeOfModelNo, WORD * type, WORD * numChannels, 
															char * notes, DWORD sizeOfNotes, DWORD * firmwareVersion, WORD * hardwareVersion, WORD * modificationState);

	/// <summary> Gets the hardware information in a block. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="hardwareInfo"> Address of a TLI_HardwareInformation structure to receive the hardware information. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	BENCHPIEZO_API short __cdecl PBC_GetHardwareInfoBlock(char const  * serialNo, short channel, TLI_HardwareInformation *hardwareInfo);

	/// <summary> Gets the number of channels in the device. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <returns> The number of channels. </returns>
	BENCHPIEZO_API short __cdecl PBC_GetNumChannels(char const * serialNo);

	/// <summary> Gets version number of the device firmware. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <returns> The device firmware version number made up of 4 byte parts. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	BENCHPIEZO_API DWORD __cdecl PBC_GetFirmwareVersion(char const * serialNo);

	/// <summary> Gets version number of the device software. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <returns> The device software version number made up of 4 byte parts. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	BENCHPIEZO_API DWORD __cdecl PBC_GetSoftwareVersion(char const * serialNo);

	/// <summary> Update device with stored settings. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	BENCHPIEZO_API bool __cdecl PBC_LoadSettings(char const * serialNo, short channel);

	/// <summary> Update device with named settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">  The channel. </param>
	/// <param name="settingsName"> Name of settings stored away from device. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	///             \include CodeSnippet_connection1.cpp
	BENCHPIEZO_API bool __cdecl PBC_LoadNamedSettings(char const * serialNo, short channel, char const *settingsName);

	/// <summary>	Persist device settings to device. </summary>
	/// <param name="serialNo">	The serial no. </param>
	/// <param name="channel"> 	The channel. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	BENCHPIEZO_API bool __cdecl PBC_PersistSettings(char const * serialNo, short channel);

	/// <summary> Disable the channel so that motor can be moved by hand. </summary>
	/// <remarks> When disabled power is removed from the actuator.</remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PBC_EnableChannel(char const * serialNo, short channel)" />
	BENCHPIEZO_API short __cdecl PBC_DisableChannel(char const * serialNo, short channel);

	/// <summary> Enable channel for computer control. </summary>
	/// <remarks> When enabled power is applied to the actuator so it is fixed in position.</remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PBC_DisableChannel(char const * serialNo, short channel)" />
	BENCHPIEZO_API short __cdecl PBC_EnableChannel(char const * serialNo, short channel);


	/// <summary> Registers a callback on the message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="functionPointer"> A function pointer to be called whenever messages are received. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PBC_RegisterMessageCallback(char const * serialNo, short channel, void (* functionPointer)());

	/// <summary> Gets the MessageQueue size. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> number of messages in the queue. </returns>
	BENCHPIEZO_API int __cdecl PBC_MessageQueueSize(char const * serialNo, short channel);

	/// <summary> Clears the device message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PBC_ClearMessageQueue(char const * serialNo, short channel);

	/// <summary> Get the next MessageQueue item if it is available. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="messageType"> Address of the WORD to receive the message type. </param>
	/// <param name="messageID"> Address of the WORD to receive themessage ID. </param>
	/// <param name="messageData"> Address of the DWORD to receive the messageData. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	BENCHPIEZO_API bool __cdecl PBC_GetNextMessage(char const * serialNo, short channel, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Get the next MessageQueue item if it is available. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="messageType"> Address of the WORD to receive the message type. </param>
	/// <param name="messageID"> Address of the WORD to receive themessage ID. </param>
	/// <param name="messageData"> Address of the DWORD to receive the messageData. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	BENCHPIEZO_API bool __cdecl PBC_WaitForMessage(char const * serialNo, short channel, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Starts the internal polling loop which continuously requests position and status. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="milliseconds">	    The milliseconds polling rate. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="PBC_StopPolling(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_PollingDuration(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_RequestStatusBits(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_RequestPosition(char const * serialNo, short channel)" />
	/// \include CodeSnippet_connectionN.cpp
	BENCHPIEZO_API bool __cdecl PBC_StartPolling(char const * serialNo, short channel, int milliseconds);

	/// <summary> Gets the polling loop duration. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <returns> The time between polls in milliseconds or 0 if polling is not active. </returns>
	/// <seealso cref="PBC_StartPolling(char const * serialNo, short channel, int milliseconds)" />
	/// <seealso cref="PBC_StopPolling(char const * serialNo, short channel)" />
	/// \include CodeSnippet_connectionN.cpp
	BENCHPIEZO_API long __cdecl PBC_PollingDuration(char const * serialNo, short channel);

	/// <summary> Stops the internal polling loop. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <seealso cref="PBC_StartPolling(char const * serialNo, short channel, int milliseconds)" />
	/// <seealso cref="PBC_PollingDuration(char const * serialNo, short channel)" />
	/// \include CodeSnippet_connectionN.cpp
	BENCHPIEZO_API void __cdecl PBC_StopPolling(char const * serialNo, short channel);

	/// <summary> Gets the time in milliseconds since tha last message was received from the device. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="lastUpdateTimeMS"> The time since the last message was received in milliseconds. </param>
	/// <returns> True if monitoring is enabled otherwize False. </returns>
	/// <seealso cref="PBC_EnableLastMsgTimer(char const * serialNo, short channel, bool enable, __int32 lastMsgTimeout )" />
	/// <seealso cref="PBC_HasLastMsgTimerOverrun(char const * serialNo, short channel)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	BENCHPIEZO_API bool __cdecl PBC_TimeSinceLastMsgReceived(char const * serialNo, short channel, __int64 &lastUpdateTimeMS );

	/// <summary> Enables the last message monitoring timer. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="enable"> True to enable monitoring otherwise False to disable. </param>
	/// <param name="lastMsgTimeout"> The last message error timeout in ms. 0 to disable. </param>
	/// <seealso cref="PBC_TimeSinceLastMsgReceived(char const * serialNo, short channel, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="PBC_HasLastMsgTimerOverrun(char const * serialNo, short channel)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	BENCHPIEZO_API void __cdecl PBC_EnableLastMsgTimer(char const * serialNo, short channel, bool enable, __int32 lastMsgTimeout );

	/// <summary> Queries if the time since the last message has exceeded the lastMsgTimeout set by <see cref="PBC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )"/>. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <returns> True if last message timer has elapsed, False if monitoring is not enabled or if time of last message received is less than lastMsgTimeout. </returns>
	/// <seealso cref="PBC_TimeSinceLastMsgReceived(char const * serialNo, short channel, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="PBC_EnableLastMsgTimer(char const * serialNo, short channel, bool enable, __int32 lastMsgTimeout )" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	BENCHPIEZO_API bool __cdecl PBC_HasLastMsgTimerOverrun(char const * serialNo, short channel);

	/// <summary> Requests that all settings are download from device. </summary>
	/// <remarks> This function requests that the device upload all it's settings to the DLL.</remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	BENCHPIEZO_API short __cdecl PBC_RequestSettings(char const * serialNo, short channel);

	/// <summary> Requests the status bits and position. </summary>
	/// <remarks> This needs to be called to get the device to send it's current position and status bits.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="PBC_StartPolling(char const * serialNo, short channel, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="PBC_RequestStatusBits(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_GetPosition(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_GetStatusBits(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_StartPolling(char const * serialNo, short channel, int milliseconds)" />
	BENCHPIEZO_API short __cdecl PBC_RequestStatus(char const * serialNo, short channel);

	/// <summary> Request the status bits which identify the current device state. </summary>
	/// <remarks> This needs to be called to get the device to send it's current status bits.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="PBC_StartPolling(char const * serialNo, short channel, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="PBC_GetStatusBits(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_StartPolling(char const * serialNo, short channel, int milliseconds)" />
	BENCHPIEZO_API short __cdecl PBC_RequestStatusBits(char const * serialNo, short channel);

	/// <summary>Get the current status bits. </summary>
	/// <remarks> This returns the latest status bits received from the device.<br />
	/// 		  To get new status bits, use <see cref="PBC_RequestStatusBits(char const * serialNo, short channel)" /> <br />
	///			  or use <see cref="BPC_RequestStatus(char const * serialNo)" />
	/// 		  or use the polling functions, <see cref="PBC_StartPolling(char const * serialNo, short channel, int milliseconds)" />.</remarks>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="serialNo">	The controller serial no. </param>
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
	/// <seealso cref="PBC_RequestStatusBits(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_RequestStatus(char const * serialNo)" />
	/// <seealso cref="PBC_StartPolling(char const * serialNo, short channel, int milliseconds)" />
	BENCHPIEZO_API DWORD __cdecl PBC_GetStatusBits(char const * serialNo, short channel);

	/// <summary>	Requests the position. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">  The channel. </param>
	/// <seealso cref="PBC_RequestPosition(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_GetPosition(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_SetPosition(char const * serialNo, short channel, short position)" />
	/// <seealso cref="PBC_SetPositionToTolerance(char const * serialNo, short channel, short position, short tolerance)" />
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	BENCHPIEZO_API short __cdecl PBC_RequestActualPosition(char const * serialNo, short channel);

	/// <summary> Requests the current output voltage or position depending on current mode. </summary>
	/// <remarks> This needs to be called to get the device to send it's current position.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="PBC_StartPolling(char const * serialNo, short channel, int milliseconds)" />. </remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="PBC_GetPosition(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_RequestActualPosition(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_StartPolling(char const * serialNo, short channel, int milliseconds)" />
	BENCHPIEZO_API short __cdecl PBC_RequestPosition(char const * serialNo, short channel);

	/// <summary>	Resets all parameters to power-up values. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PBC_ResetParameters(char const * serialNo, short channel);

	/// <summary> Sets the voltage output to zero and defines the ensuing actuator position az zero. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PBC_SetZero(char const * serialNo, short channel);

	/// <summary> Gets the Position Control Mode. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The control mode <list type=table>
	///				<item><term>Open Loop</term><term>1</term></item>
	///				<item><term>Closed Loop</term><term>2</term></item>
	///				<item><term>Open Loop smoothed</term><term>3</term></item>
	///				<item><term>Closed Loop smoothed</term><term>4</term></item>
	/// 		  </list> </returns>
	/// <seealso cref="PBC_RequestPositionControlMode(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_SetPositionControlMode(char const * serialNo, short channel, PZ_ControlModeTypes mode)" />
	BENCHPIEZO_API PZ_ControlModeTypes __cdecl PBC_GetPositionControlMode(char const * serialNo, short channel);

	/// <summary> Requests the Position Control Mode be read from the device for the device and channel. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="PBC_GetPositionControlMode(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_SetPositionControlMode(char const * serialNo, short channel, PZ_ControlModeTypes mode)" />
	BENCHPIEZO_API bool __cdecl PBC_RequestPositionControlMode(char const * serialNo, short channel);

	/// <summary> Sets the Position Control Mode. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="mode"> The control mode <list type=table>
	///				<item><term>Open Loop</term><term>1</term></item>
	///				<item><term>Closed Loop</term><term>2</term></item>
	///				<item><term>Open Loop smoothed</term><term>3</term></item>
	///				<item><term>Closed Loop smoothed</term><term>4</term></item>
	/// 		  </list>. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PBC_GetPositionControlMode(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_RequestPositionControlMode(char const * serialNo, short channel)" />
	BENCHPIEZO_API short __cdecl PBC_SetPositionControlMode(char const * serialNo, short channel, PZ_ControlModeTypes mode);

	// Voltage Functions
	
	/// <summary> Gets the maximum output voltage. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The maximum output voltage, 750, 1000 or 1500 (75.0, 100.0, 150.0). </returns>
	/// <seealso cref="PBC_SetMaxOutputVoltage(char const * serialNo, short channel, short maxVoltage)" />
	/// <seealso cref="PBC_RequestMaxOutputVoltage(char const * serialNo, short channel)" />
	BENCHPIEZO_API short __cdecl PBC_GetMaxOutputVoltage(char const * serialNo, short channel);

	/// <summary> Requests that the maximum output voltage be read from the device. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <seealso cref="PBC_GetMaxOutputVoltage(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_SetMaxOutputVoltage(char const * serialNo, short channel, short maxVoltage)" />
	/// <returns>	True if it succeeds, false if it fails. </returns>
	BENCHPIEZO_API bool __cdecl PBC_RequestMaxOutputVoltage(char const * serialNo, short channel);

	/// <summary> Sets the maximum output voltage. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="maxVoltage">	The maximum output voltage, 750, 1000 or 1500 (75.0, 100.0, 150.0). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PBC_RequestMaxOutputVoltage(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_GetMaxOutputVoltage(char const * serialNo, short channel)" />
	BENCHPIEZO_API short __cdecl PBC_SetMaxOutputVoltage(char const * serialNo, short channel, short maxVoltage);

	/// <summary> Gets the set Output Voltage. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The voltage as a percentage of MaxOutputVoltage,<br />
	/// 		  range -32767 to 32767 equivalent to -100% to 100%. </returns>
	/// <seealso cref="PBC_RequestOutputVoltage(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_SetOutputVoltage(char const * serialNo, short channel, short volts)" />
	/// <seealso cref="PBC_SetMaxOutputVoltage(char const * serialNo, short channel, short eVoltage)" />
	/// <seealso cref="PBC_GetMaxOutputVoltage(char const * serialNo, short channel)" />
	BENCHPIEZO_API short __cdecl PBC_GetOutputVoltage(char const * serialNo, short channel);

	/// <summary> Requests the output voltage be read from the device. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="PBC_GetOutputVoltage(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_SetOutputVoltage(char const * serialNo, short channel, short volts)" />
	/// <seealso cref="PBC_SetMaxOutputVoltage(char const * serialNo, short channel, short eVoltage)" />
	/// <seealso cref="PBC_GetMaxOutputVoltage(char const * serialNo, short channel)" />
	BENCHPIEZO_API bool __cdecl PBC_RequestOutputVoltage(char const * serialNo, short channel);

	/// <summary> Sets the output voltage. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="volts"> The voltage as a percentage of MaxOutputVoltage,<br />
	/// 		  range -32767 to 32767 equivalent to -100% to 100%. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PBC_RequestOutputVoltage(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_GetOutputVoltage(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_SetMaxOutputVoltage(char const * serialNo, short channel, short eVoltage)" />
	/// <seealso cref="PBC_GetMaxOutputVoltage(char const * serialNo, short channel)" />
	BENCHPIEZO_API short __cdecl PBC_SetOutputVoltage(char const * serialNo, short channel, short volts);

	/// <summary> Requests that the current input voltage source be read from the device. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">  The channel. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="PBC_GetVoltageSource(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_SetVoltageSource(char const * serialNo, short channel, PZ_InputSourceFlags source)" />
	BENCHPIEZO_API bool __cdecl PBC_RequestVoltageSource(char const * serialNo, short channel);

	/// <summary> Gets the control voltage source. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The voltage source. <list type=table>
	///				<item><term>Software Only</term><term>0</term></item>
	///				<item><term>Software and External</term><term>1</term></item>
	///				<item><term>Software and Potentiometer</term><term>2</term></item>
	///				<item><term>Software, External and Potentiometer</term><term>3</term></item>
	/// 		  </list> </returns>
	/// <seealso cref="PBC_RequestVoltageSource(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_SetVoltageSource(char const * serialNo, short channel, PZ_InputSourceFlags source)" />
	BENCHPIEZO_API PZ_InputSourceFlags __cdecl PBC_GetVoltageSource(char const * serialNo, short channel);

	/// <summary> Sets the control voltage source. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="source"> The voltage source <list type=table>
	///				<item><term>Software Only</term><term>0</term></item>
	///				<item><term>Software and External</term><term>1</term></item>
	///				<item><term>Software and Potentiometer</term><term>2</term></item>
	///				<item><term>Software, External and Potentiometer</term><term>3</term></item>
	/// 		  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PBC_RequestVoltageSource(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_GetVoltageSource(char const * serialNo, short channel)" />
	BENCHPIEZO_API short __cdecl PBC_SetVoltageSource(char const * serialNo, short channel, PZ_InputSourceFlags source);

	/// <summary> Requests the maximum travel be read from the device. </summary>
	/// <remarks> This requires an actuator with built in position sensing</remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="PBC_GetMaximumTravel(char const * serialNo, short channel)" />
	BENCHPIEZO_API bool __cdecl PBC_RequestMaximumTravel(char const * serialNo, short channel);

	/// <summary> Gets the maximum travel of the device. </summary>
	/// <remarks> This requires an actuator with built in position sensing</remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns>	The distance in steps of 100nm,<br />
	/// 			range 0 to 65535 (10000 is equivalent to 1mm). </returns>
	/// <seealso cref="PBC_RequestMaximumTravel(char const * serialNo, short channel)" />
	BENCHPIEZO_API WORD __cdecl PBC_GetMaximumTravel(char const * serialNo, short channel);

	/// <summary> Gets the position when in closed loop mode. </summary>
	/// <remarks> The result is undefined if not in closed loop mode</remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The position as a percentage of maximum travel,<br />
	/// 		  range -32767 to 32767, equivalent to -100 to 100%. </returns>
	/// <seealso cref="PBC_RequestActualPosition(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_SetPosition(char const * serialNo, short channel, short position)" />
	/// <seealso cref="PBC_SetPositionToTolerance(char const * serialNo, short channel, short position, short tolerance)" />
	/// <seealso cref="PBC_SetPositionControlMode(char const * serialNo, short channel, PZ_ControlModeTypes mode)" />
	/// <seealso cref="PBC_GetPositionControlMode(char const * serialNo, short channel)" />
	BENCHPIEZO_API short __cdecl PBC_GetPosition(char const * serialNo, short channel);

	/// <summary> Sets the position when in closed loop mode. </summary>
	/// <remarks> The command is ignored if not in closed loop mode</remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="position"> The position as a percentage of maximum travel,<br />
	/// 		  range 0 to 32767, equivalent to 0 to 100%. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PBC_RequestActualPosition(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_SetPositionToTolerance(char const * serialNo, short channel, short position, short tolerance)" />
	/// <seealso cref="PBC_GetPosition(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_SetPositionControlMode(char const * serialNo, short channel, PZ_ControlModeTypes mode)" />
	/// <seealso cref="PBC_GetPositionControlMode(char const * serialNo, short channel)" />
	BENCHPIEZO_API short __cdecl PBC_SetPosition(char const * serialNo, short channel, short position);

	/// <summary> Sets the position when in closed loop mode. </summary>
	/// <remarks> The command is ignored if not in closed loop mode</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">  The channel. </param>
	/// <param name="position"> The position as a percentage of maximum travel,<br />
	/// 		  range 0 to 32767, equivalent to 0 to 100%. </param>
	/// <param name="tolerance"> The tolerance in position as a percentage of maximum travel,<br />
	/// 		  range 0 to 32767, equivalent to 0 to 100%. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PBC_RequestActualPosition(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_SetPosition(char const * serialNo, short channel, short position)" />
	/// <seealso cref="PBC_GetPosition(char const * serialNo, short channel)" />
	/// <seealso cref="PBC_SetPositionControlMode(char const * serialNo, short channel, PZ_ControlModeTypes mode)" />
	/// <seealso cref="PBC_GetPositionControlMode(char const * serialNo, short channel)" />
	BENCHPIEZO_API short __cdecl PBC_SetPositionToTolerance(char const * serialNo, short channel, short position, short tolerance);

	/// <summary> Requests that the feedback loop constants be read from the device. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="PBC_GetFeedbackLoopPIconsts(char const * serialNo, short channel, short * proportionalTerm, short * integralTerm)" />
	/// <seealso cref="PBC_SetFeedbackLoopPIconsts(char const * serialNo, short channel, short proportionalTerm, short integralTerm)" />
	/// <seealso cref="PBC_GetFeedbackLoopPIconstsBlock(const char * serialNo, short channel, PZ_FeedbackLoopConstants *proportionalAndIntegralConstants)" />
	/// <seealso cref="PBC_SetFeedbackLoopPIconstsBlock(const char * serialNo, short channel, PZ_FeedbackLoopConstants *proportionalAndIntegralConstants)" />
	BENCHPIEZO_API bool __cdecl PBC_RequestFeedbackLoopPIconsts(char const * serialNo, short channel);

	/// <summary> Gets the feedback loop parameters. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="proportionalTerm"> The address of the parameter to receive the proportional parameter. </param>
	/// <param name="integralTerm"> The address of the parameter to receive the integral parameter. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PBC_SetFeedbackLoopPIconsts(char const * serialNo, short channel, short proportionalTerm, short integralTerm)" />
	/// <seealso cref="PBC_GetFeedbackLoopPIconstsBlock(const char * serialNo, short channel, PZ_FeedbackLoopConstants *proportionalAndIntegralConstants)" />
	/// <seealso cref="PBC_SetFeedbackLoopPIconstsBlock(const char * serialNo, short channel, PZ_FeedbackLoopConstants *proportionalAndIntegralConstants)" />
	BENCHPIEZO_API short __cdecl PBC_GetFeedbackLoopPIconsts(char const * serialNo, short channel, short * proportionalTerm, short * integralTerm);

	/// <summary> Sets the feedback loop constants. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="proportionalTerm"> The proportional gain term from 0 to 255. </param>
	/// <param name="integralTerm">	 The integral gain term from 0 to 255. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PBC_GetFeedbackLoopPIconsts(char const * serialNo, short channel, short * proportionalTerm, short * integralTerm)" />
	/// <seealso cref="PBC_GetFeedbackLoopPIconstsBlock(char const * serialNo, short channel, PZ_FeedbackLoopConstants *proportionalAndIntegralConstants)" />
	/// <seealso cref="PBC_SetFeedbackLoopPIconstsBlock(const char * serialNo, short channel, PZ_FeedbackLoopConstants *proportionalAndIntegralConstants)" />
	BENCHPIEZO_API short __cdecl PBC_SetFeedbackLoopPIconsts(char const * serialNo, short channel, short proportionalTerm, short integralTerm);

	/// <summary> Gets the feedback loop constants in a block. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="proportionalAndIntegralConstants"> The address of the PZ_FeedbackLoopConstants to receive the feedback loop constants. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PBC_GetFeedbackLoopPIconsts(char const * serialNo, short channel, short * proportionalTerm, short * integralTerm)" />
	/// <seealso cref="PBC_SetFeedbackLoopPIconsts(char const * serialNo, short channel, short proportionalTerm, short integralTerm)" />
	/// <seealso cref="PBC_SetFeedbackLoopPIconstsBlock(const char * serialNo, short channel, PZ_FeedbackLoopConstants *proportionalAndIntegralConstants)" />
	BENCHPIEZO_API short __cdecl PBC_GetFeedbackLoopPIconstsBlock(const char * serialNo, short channel, PZ_FeedbackLoopConstants *proportionalAndIntegralConstants);

	/// <summary> Sets the feedback loop constants in a block. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="proportionalAndIntegralConstants"> The address of the PZ_FeedbackLoopConstants containing the new feedback loop constants. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PBC_GetFeedbackLoopPIconsts(char const * serialNo, short channel, short * proportionalTerm, short * integralTerm)" />
	/// <seealso cref="PBC_SetFeedbackLoopPIconsts(char const * serialNo, short channel, short proportionalTerm, short integralTerm)" />
	/// <seealso cref="PBC_GetFeedbackLoopPIconstsBlock(const char * serialNo, short channel, PZ_FeedbackLoopConstants *proportionalAndIntegralConstants)" />
	BENCHPIEZO_API short __cdecl PBC_SetFeedbackLoopPIconstsBlock(const char * serialNo, short channel, PZ_FeedbackLoopConstants *proportionalAndIntegralConstants);

	/// <summary> Sets the LUT output wave parameters. </summary>
	/// <remarks> NOTE, the get function has never been implemented in firmware, so new parameters need to be generated each time.</remarks>
	/// <param name="serialNo">		  The controller serial no. </param>
	/// <param name="channel">		  The channel (1 to n). </param>
	/// <param name="LUTwaveParams"> Address of the PZ_LUTWaveParameters containing the new LUT wave parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PBC_SetLUTwaveParams(const char * serialNo, short channel, PZ_LUTWaveParameters *LUTwaveParams);

	/// <summary> Sets a waveform sample. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="index"> The phase index in waveform where value is to be set. </param>
	/// <param name="value"> The voltage or position as a percentage of full scale.<br />
	/// 					  range -32767 to 32767, equivalemnt to -100% to 100% of maximum voltage / position. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PBC_SetLUTwaveSample(char const * serialNo, short channel, short index, WORD value);

	/// <summary> Starts the LUT waveform output. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully started. </returns>
	BENCHPIEZO_API short __cdecl PBC_StartLUTwave(char const * serialNo, short channel);

	/// <summary> Stops the LUT waveform output. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PBC_StopLUTwave(char const * serialNo, short channel);

	/// <summary> Requests the rack digital output bits. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PBC_SetRackDigitalOutputs(char const * serialNo, byte outputsBits)" />
	/// <seealso cref="PBC_GetRackDigitalOutputs(char const * serialNo)" />
	BENCHPIEZO_API short __cdecl PBC_RequestRackDigitalOutputs(char const * serialNo);

	/// <summary> Gets the rack digital output bits. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> Bit mask of states of the 4 digital output pins. </returns>
	/// <seealso cref="PBC_SetRackDigitalOutputs(char const * serialNo, byte outputsBits)" />
	/// <seealso cref="PBC_RequestRackDigitalOutputs(char const * serialNo)" />
	BENCHPIEZO_API byte __cdecl PBC_GetRackDigitalOutputs(char const * serialNo);

	/// <summary> Sets the rack digital output bits. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="outputsBits"> Bit mask to set states of the 4 digital output pins. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PBC_GetRackDigitalOutputs(char const * serialNo)" />
	/// <seealso cref="PBC_RequestRackDigitalOutputs(char const * serialNo)" />
	BENCHPIEZO_API short __cdecl PBC_SetRackDigitalOutputs(char const * serialNo, byte outputsBits);

	/// <summary> Requests the Rack status bits be downloaded. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PBC_GetRackStatusBits(char const * serialNo)" />
	BENCHPIEZO_API short __cdecl PBC_RequestRackStatusBits(char const * serialNo);

	/// <summary> Gets the Rack status bits. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The status bits including 4 with one per electronic input pin. </returns>
	/// <seealso cref="PBC_RequestRackStatusBits(char const * serialNo)" />
	BENCHPIEZO_API DWORD __cdecl PBC_GetRackStatusBits(char const * serialNo);

}
/** @} */ // BenchtopPiezo