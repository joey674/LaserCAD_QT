// summary:	Declares the functions class
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the TCUBETEC_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// TCUBETEC_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef TCUBETECDLL_EXPORTS
#define TCUBETEC_API __declspec(dllexport)
#else
#define TCUBETEC_API __declspec(dllimport)
#endif

#include <OaIdl.h>

#pragma once

/** @defgroup TCubeTEC TCube TEC
 *  This section details the Structures and Functions relavent to the  @ref TTC001_page "TEC"<br />
 *  For an example of how to connect to the device and perform simple operations use the following links:
 *  <list type=bullet>
 *    <item> \ref namespaces_tec_ex_1 "Example of using the Thorlabs.MotionControl.TCube.TEC.DLL from a C or C++ project."<br />
 *									  This requires the DLL to be dynamical linked. </item>
 *    <item> \ref namespaces_tec_ex_2 "Example of using the Thorlabs.MotionControl.TCube.TEC.DLL from a C# project"<br />
 *									  This uses Marshalling to load and access the C DLL. </item>
 *  </list>
 *  The Thorlabs.MotionControl.TCube.TEC.DLL requires the following DLLs
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

	/// <summary> structure containing temperature parameters used in an algorithm involving calculus. </summary>
	typedef struct TC_LoopParameters
	{
		/// <summary> The proportional gain term, range 1 to 32767 equivalent to 1 to 100. </summary>
		unsigned short proportionalGain;
		/// <summary> The integral gain term, range 0 to 32767 equivalent to 0 to 100. </summary>
		unsigned short integralGain;
		/// <summary> The derivative gain term, range 0 to 32767 equivalent to 0 to 100. </summary>
		/// <remarks> Kept as differentialGain rather than derivativeGain for backward compatibility</remarks>
		unsigned short differentialGain;
	} TC_LoopParameters;

	/// <summary> Values that represent the available sensor types. </summary>
	typedef enum TC_SensorTypes : unsigned short
	{
		TC_Transducer = 0x00,///<Using AD59x IC transducer sensor.
		TC_TH20kOhm = 0x01,///<Using 20kOhm thermistor.
		TC_TH200kOhm = 0x02,///<Using 200kOhm thermistor.
	} TC_SensorTypes;

	/// <summary> Values that represent the display / output modes. </summary>
	typedef enum TC_DisplayModes : unsigned short
	{
		TC_ActualTemperature = 0x00,///<Display actual temperature.
		TC_TargetTemperature = 0x01,///<Display target temperature.
		TC_TempDifference = 0x02,///<Display difference in temperature between actual and target.
		TC_Current = 0x03,///<Display actual current.
	} TC_DisplayModes;
#pragma pack()

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
	TCUBETEC_API short __cdecl TLI_BuildDeviceList(void);

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
	TCUBETEC_API short __cdecl TLI_GetDeviceListSize();

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
	TCUBETEC_API short __cdecl TLI_GetDeviceList(SAFEARRAY** stringsReceiver);

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
	TCUBETEC_API short __cdecl TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID);

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
	TCUBETEC_API short __cdecl TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length);

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
	TCUBETEC_API short __cdecl TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer);

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
	TCUBETEC_API short __cdecl TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID);

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
	TCUBETEC_API short __cdecl TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length);

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
	TCUBETEC_API short __cdecl TLI_GetDeviceInfo(char const * serialNo, TLI_DeviceInfo *info);

	/// <summary> Initialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <remarks> Call TLI_InitializeSimulations before TLI_BuildDeviceList at the start of the program to make a connection to the simulation manager.<Br />
	/// 		  Any devices configured in the simulation manager will become visible TLI_BuildDeviceList is called and can be accessed using TLI_GetDeviceList.<Br />
	/// 		  Call TLI_InitializeSimulations at the end of the program to release the simulator.  </remarks>
	/// <seealso cref="TLI_UninitializeSimulations()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	TCUBETEC_API void __cdecl TLI_InitializeSimulations();

	/// <summary> Uninitialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <seealso cref="TLI_InitializeSimulations()" />
	TCUBETEC_API void __cdecl TLI_UninitializeSimulations();

	/// <summary> Open the device for communications. </summary>
	/// <param name="serialNo">	The serial no of the device to be connected. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="TC_Close(char const * serialNo)" />
	TCUBETEC_API short __cdecl TC_Open(char const * serialNo);

	/// <summary> Disconnect and close the device. </summary>
	/// <param name="serialNo">	The serial no of the device to be disconnected. </param>
    /// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="TC_Open(char const * serialNo)" />
	TCUBETEC_API void __cdecl TC_Close(char const * serialNo);

	/// <summary>	Check connection. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> true if the USB is listed by the ftdi controller</returns>
	/// \include CodeSnippet_CheckConnection.cpp
	TCUBETEC_API bool __cdecl TC_CheckConnection(char const * serialNo);

	/// <summary> Sends a command to the device to make it identify iteself. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	TCUBETEC_API void __cdecl TC_Identify(char const * serialNo);

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
	TCUBETEC_API short __cdecl TC_GetHardwareInfo(char const * serialNo, char * modelNo, DWORD sizeOfModelNo, WORD * type, WORD * numChannels, 
													char * notes, DWORD sizeOfNotes, DWORD * firmwareVersion, WORD * hardwareVersion, WORD * modificationState);

	/// <summary> Gets the hardware information in a block. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="hardwareInfo"> Address of a TLI_HardwareInformation structure to receive the hardware information. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	TCUBETEC_API short __cdecl TC_GetHardwareInfoBlock(char const *serialNo, TLI_HardwareInformation *hardwareInfo);

	/// <summary> Gets version number of the device firmware. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device firmware version number made up of 4 byte parts. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	TCUBETEC_API DWORD __cdecl TC_GetFirmwareVersion(char const * serialNo);

	/// <summary> Gets version number of the device software. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device software version number made up of 4 byte parts. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	TCUBETEC_API DWORD __cdecl TC_GetSoftwareVersion(char const * serialNo);

	/// <summary> Update device with stored settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
    /// 		  \include CodeSnippet_connection1.cpp
	TCUBETEC_API bool __cdecl TC_LoadSettings(char const * serialNo);

	/// <summary> Update device with named settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="settingsName"> Name of settings stored away from device. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	///             \include CodeSnippet_connection1.cpp
	TCUBETEC_API bool __cdecl TC_LoadNamedSettings(char const * serialNo, char const *settingsName);

	/// <summary> persist the devices current settings. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	TCUBETEC_API bool __cdecl TC_PersistSettings(char const * serialNo);

	/// <summary> Disable cube. </summary>

	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="TC_Enable(char const * serialNo)" />
	TCUBETEC_API short __cdecl TC_Disable(char const * serialNo);

	/// <summary> Enable cube for computer control. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="TC_Disable(char const * serialNo)" />
	TCUBETEC_API short __cdecl TC_Enable(char const * serialNo);

	/// <summary> Reset the device. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	TCUBETEC_API short __cdecl TC_Reset(char const * serialNo);

	/// <summary> Tells the device that it is being disconnected. </summary>
	/// <remarks> This does not disconnect the communications.<br />
	/// 		  To disconnect the communications, call the <see cref="TC_Close(char const * serialNo)" /> function. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	TCUBETEC_API short __cdecl TC_Disconnect(char const * serialNo);

	/// <summary> Clears the device message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	TCUBETEC_API void __cdecl TC_ClearMessageQueue(char const * serialNo);

	/// <summary> Registers a callback on the message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="functionPointer"> A function pointer to be called whenever messages are received. </param>
	/// <seealso cref="TC_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="TC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="TC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	TCUBETEC_API void __cdecl TC_RegisterMessageCallback(char const * serialNo, void (* functionPointer)());

	/// <summary> Gets the MessageQueue size. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> number of messages in the queue. </returns>
	/// <seealso cref="TC_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="TC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="TC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	TCUBETEC_API int __cdecl TC_MessageQueueSize(char const * serialNo);

	/// <summary> Get the next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="TC_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="TC_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="TC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	TCUBETEC_API bool __cdecl TC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Wait for next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="TC_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="TC_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="TC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	TCUBETEC_API bool __cdecl TC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Requests the set temperature. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="TC_GetTemperatureSet(char const * serialNo)" />
	/// <seealso cref="TC_SetTemperature(char const * serialNo, short temperature)" />
	TCUBETEC_API short __cdecl TC_RequestTemperatureSet(char const * serialNo);

	/// <summary> Gets the required temperature. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The required temperature. The application is sensor dependent (<see cref="TC_SensorTypes" />), see table for detail.
	/// 		  <list type=table>
	///				<item><term>Thermistor</term><term>range -4500 to 14500, equivalent to -45.0C to 145.0C.</term></item>
	///				<item><term>20kOhm thermistor</term><term>range 0 to 2000, equivalent to 0 to 20kOhm.</term></item>
	///				<item><term>20kOhm thermistor</term><term>range 0 to 2000, equivalent to 0 to 200kOhm</term></item>
	/// 		  </list> </returns>
	/// <seealso cref="TC_RequestTemperatureSet(char const * serialNo)" />
	/// <seealso cref="TC_SetTemperature(char const * serialNo, short temperature)" />
	/// <seealso cref="TC_GetSensorType(char const * serialNo)" />
	TCUBETEC_API short __cdecl TC_GetTemperatureSet(char const * serialNo);

	/// <summary> Sets the required temperature. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="temperature"> The required temperature. The application is sensor dependent (<see cref="TC_SensorTypes" />), see table for detail.
	/// 		  <list type=table>
	///				<item><term>Thermistor</term><term>range -4500 to 14500, equivalent to -45.0C to 145.0C.</term></item>
	///				<item><term>20kOhm thermistor</term><term>range 0 to 2000, equivalent to 0 to 20kOhm.</term></item>
	///				<item><term>20kOhm thermistor</term><term>range 0 to 2000, equivalent to 0 to 200kOhm</term></item>
	/// 		  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="TC_RequestTemperatureSet(char const * serialNo)" />
	/// <seealso cref="TC_GetTemperatureSet(char const * serialNo)" />
	/// <seealso cref="TC_GetSensorType(char const * serialNo)" />
	TCUBETEC_API short __cdecl TC_SetTemperature(char const * serialNo, short temperature);

	/// <summary> Requests the quantity displayed by hardware. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="TC_GetHWDisplayMode(char const * serialNo)" />
	/// <seealso cref="TC_SetHWDisplayMode(char const * serialNo, TC_DisplayModes quantity)" />
	TCUBETEC_API short __cdecl TC_RequestHWDisplayMode(char const * serialNo);

	/// <summary> Gets the display mode / output mode for the device. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The current display mode / output mode.
	/// 		  <list type=table>
	///				<item><term>Actual Temperature</term><term>0</term></item>
	///				<item><term>Set Temperature</term><term>1</term></item>
	///				<item><term>Temperature difference between Actual Temperature and Required Temperature</term><term>2</term></item>
	///				<item><term>Actual Current</term><term>3</term></item>
	/// 		  </list> </returns>
	/// <seealso cref="TC_RequestHWDisplayMode(char const * serialNo)" />
	/// <seealso cref="TC_SetHWDisplayMode(char const * serialNo, TC_DisplayModes quantity)" />
	TCUBETEC_API TC_DisplayModes __cdecl TC_GetHWDisplayMode(char const * serialNo);

	/// <summary> Sets the display mode / output mode for the device. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="mode"> The new display mode / output mode.
	/// 		  <list type=table>
	///				<item><term>Actual Temperature</term><term>0</term></item>
	///				<item><term>Set Temperature</term><term>1</term></item>
	///				<item><term>Temperature difference between Actual Temperature and Required Temperature</term><term>2</term></item>
	///				<item><term>Actual Current</term><term>3</term></item>
	/// 		  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="TC_RequestHWDisplayMode(char const * serialNo)" />
	/// <seealso cref="TC_GetHWDisplayMode(char const * serialNo)" />
	TCUBETEC_API short __cdecl TC_SetHWDisplayMode(char const * serialNo, TC_DisplayModes mode);

	/// <summary> Requests the LED brightness. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="TC_GetLEDBrightness(char const * serialNo)" />
	/// <seealso cref="TC_SetLEDBrightness(char const * serialNo, short brightness)" />
	TCUBETEC_API short __cdecl TC_RequestLEDBrightness(char const * serialNo);

	/// <summary> Gets the LED brightness. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> Intensity from 0 (off) to 255. </returns>
	/// <seealso cref="TC_RequestLEDBrightness(char const * serialNo)" />
	/// <seealso cref="TC_SetLEDBrightness(char const * serialNo, short brightness)" />
	TCUBETEC_API short __cdecl TC_GetLEDBrightness(char const * serialNo);

	/// <summary> Sets the LED brightness. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="brightness"> Intensity from 0 (off) to 255. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="TC_RequestLEDBrightness(char const * serialNo)" />
	/// <seealso cref="TC_GetLEDBrightness(char const * serialNo)" />
	TCUBETEC_API short __cdecl TC_SetLEDBrightness(char const * serialNo, short brightness);

	/// <summary> Requests the device current limit. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="TC_GetCurrentLimit(char const * serialNo)" />
	/// <seealso cref="TC_SetCurrentLimit(char const * serialNo, WORD maxCurrent)" />
	TCUBETEC_API short __cdecl TC_RequestCurrentLimit(char const * serialNo);

	/// <summary> Gets the max current limit. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The maximum current, range 0 to 2000 (0 to 2000mA).  </returns>
	/// <seealso cref="TC_RequestCurrentLimit(char const * serialNo)" />
	/// <seealso cref="TC_SetCurrentLimit(char const * serialNo, WORD maxCurrent)" />
	TCUBETEC_API WORD __cdecl TC_GetCurrentLimit(char const * serialNo);

	/// <summary> Sets the max current limit. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="maxCurrent"> The maximum current, range 0 to 2000 (0 to 2000mA). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful.  </returns>
	/// <seealso cref="TC_RequestCurrentLimit(char const * serialNo)" />
	/// <seealso cref="TC_GetCurrentLimit(char const * serialNo)" />
	TCUBETEC_API short __cdecl TC_SetCurrentLimit(char const * serialNo, WORD maxCurrent);

	/// <summary> Requests the sensor type. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="TC_GetSensorType(char const * serialNo)" />
	/// <seealso cref="TC_SetSensorType(char const * serialNo, TC_SensorTypes sensor)" />
	TCUBETEC_API short __cdecl TC_RequestSensorType(char const * serialNo);

	/// <summary> Gets the sensor type. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The currently selected sensor type
	/// 		  <list type=table>
	///				<item><term>Transducer</term><term>0</term></item>
	///				<item><term>20 kOhm Thermistor</term><term>1</term></item>
	///				<item><term>200 kOhm Thermistor</term><term>2</term></item>
	///			  </list> </returns>
	/// <seealso cref="TC_RequestSensorType(char const * serialNo)" />
	/// <seealso cref="TC_SetSensorType(char const * serialNo, TC_SensorTypes sensor)" />
	TCUBETEC_API TC_SensorTypes __cdecl TC_GetSensorType(char const * serialNo);

	/// <summary> Sets the sensor type. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="sensor">  The new sensor type
	/// 		  <list type=table>
	///				<item><term>Transducer</term><term>0</term></item>
	///				<item><term>20 kOhm Thermistor</term><term>1</term></item>
	///				<item><term>200 kOhm Thermistor</term><term>2</term></item>
	///			  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="TC_RequestSensorType(char const * serialNo)" />
	/// <seealso cref="TC_GetSensorType(char const * serialNo)" />
	TCUBETEC_API short __cdecl TC_SetSensorType(char const * serialNo, TC_SensorTypes sensor);

	/// <summary> Requests the temperature loop parameters. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="TC_GetTempLoopParams(char const * serialNo)" />
	/// <seealso cref="TC_SetTempLoopParams(char const * serialNo, TC_LoopParameters * proportionalIntegralDerivativeParams)" />
	TCUBETEC_API short __cdecl TC_RequestTempLoopParams(char const * serialNo);

	/// <summary> Gets the temperature loop parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="proportionalIntegralDerivativeParams"> The temperature loop PID options. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="TC_RequestTempLoopParams(char const * serialNo)" />
	/// <seealso cref="TC_SetTempLoopParams(char const * serialNo, TC_LoopParameters * proportionalIntegralDerivativeParams)" />
	TCUBETEC_API short __cdecl TC_GetTempLoopParams(const char * serialNo, TC_LoopParameters * proportionalIntegralDerivativeParams);

	/// <summary> Sets the temperature loop parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="proportionalIntegralDerivativeParams"> The temperature loop PID options. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="TC_RequestTempLoopParams(char const * serialNo)" />
	/// <seealso cref="TC_GetTempLoopParams(char const * serialNo)" />
	TCUBETEC_API short __cdecl TC_SetTempLoopParams(const char * serialNo, TC_LoopParameters * proportionalIntegralDerivativeParams);

	/// <summary> Requests the state quantities (actual temperature, current and status bits). </summary>
	/// <remarks> This needs to be called to get the device to send it's current status.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="TC_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="TC_RequestReadings(char const * serialNo)" />
	/// <seealso cref="TC_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="TC_GetCurrentReading(char const * serialNo)" />
	/// <seealso cref="TC_GetTemperatureReading(char const * serialNo)" />
	/// <seealso cref="TC_GetStatusBits(char const * serialNo)" />
	/// <seealso cref="TC_StartPolling(char const * serialNo, int milliseconds)" />
	TCUBETEC_API short __cdecl TC_RequestStatus(char const * serialNo);

	/// <summary> Requests temperature and current readings. </summary>
	/// <remarks> This needs to be called to get the device to send it's current readings.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="TC_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="TC_GetCurrentReading(char const * serialNo)" />
	/// <seealso cref="TC_GetTemperatureReading(char const * serialNo)" />
	/// <seealso cref="TC_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="TC_RequestStatus(char const * serialNo)" />
	/// <seealso cref="TC_StartPolling(char const * serialNo, int milliseconds)" />
	TCUBETEC_API short __cdecl TC_RequestReadings(char const * serialNo);

	/// <summary> Request the status bits which identify the current device state. </summary>
	/// <remarks> This needs to be called to get the device to send it's current status bits.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="TC_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="TC_GetStatusBits(char const * serialNo)" />
	/// <seealso cref="TC_RequestStatus(char const * serialNo)" />
	/// <seealso cref="TC_RequestReadings(char const * serialNo)" />
	/// <seealso cref="TC_StartPolling(char const * serialNo, int milliseconds)" />
	TCUBETEC_API short __cdecl TC_RequestStatusBits(char const * serialNo);

	/// <summary> Gets temperature reading. </summary>
	/// <remarks> This returns the latest reading from the device.<br />
	/// 		  To get new readings, use <see cref="TC_RequestStatus(char const * serialNo)" />
	/// 		  or use the polling functions, <see cref="TC_StartPolling(char const * serialNo, int milliseconds)" />.  </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The temperature in hundredths of deg C or thermistor resistance in hundredths of kOhm. </returns>
	/// <seealso cref="TC_GetCurrentReading(char const * serialNo)" />
	/// <seealso cref="TC_RequestReadings(char const * serialNo)" />
	/// <seealso cref="TC_RequestStatus(char const * serialNo)" />
	/// <seealso cref="TC_StartPolling(char const * serialNo, int milliseconds)" />
	TCUBETEC_API short __cdecl TC_GetTemperatureReading(char const * serialNo);

	/// <summary> Gets current reading. </summary>
	/// <remarks> This returns the latest reading from the device.<br />
	/// 		  To get new readings, use <see cref="TC_RequestStatus(char const * serialNo)" />
	/// 		  or use the polling functions, <see cref="TC_StartPolling(char const * serialNo, int milliseconds)" />.  </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The current in mA. </returns>
	/// <seealso cref="TC_GetTemperatureReading(char const * serialNo)" />
	/// <seealso cref="TC_RequestReadings(char const * serialNo)" />
	/// <seealso cref="TC_RequestStatus(char const * serialNo)" />
	/// <seealso cref="TC_StartPolling(char const * serialNo, int milliseconds)" />
	TCUBETEC_API WORD __cdecl TC_GetCurrentReading(char const * serialNo);

	/// <summary>Get the current status bits. </summary>
	/// <remarks> This returns the latest status bits received from the device.<br />
	/// 		  To get new status bits, use <see cref="TC_RequestStatusBits(char const * serialNo)" />
	///			  or use <see cref="TC_RequestStatus(char const * serialNo)" />
	/// 		  or use the polling functions, <see cref="TC_StartPolling(char const * serialNo, int milliseconds)" />.  </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	The status bits from the device <list type=table>
	///				<item><term>0x00000001</term><term>TEC output enabled state (1=Enabled, 0=Disabled).</term></item>
	///				<item><term>0x00000002</term><term>For Future Use.</term></item>
	///				<item><term>0x00000004</term><term>For Future Use.</term></item>
	///				<item><term>0x00000008</term><term>For Future Use.</term></item>
	///				<item><term>0x00000010</term><term>Display mode (1=TActual, 0=Else).</term></item>
	///				<item><term>0x00000020</term><term>Display mode (1=TSet, 0=Else).</term></item>
	///				<item><term>0x00000040</term><term>Display mode (1=TDelta, 0=Else).</term></item>
	///				<item><term>0x00000080</term><term>Display mode (1=ITec, 0=Else).</term></item>
	///				<item><term>0x00000100</term><term>For Future Use.</term></item>
	///				<item><term>0x00000200</term><term></term></item>
	///				<item><term>...</term><term></term></item>
	///				<item><term>0x20000000</term><term></term></item>
	///				<item><term>0x40000000</term><term>Error.</term></item>
	///				<item><term>0x80000000</term><term>For Future Use.</term></item>
	/// 		  </list> </returns>
	/// <seealso cref="TC_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="TC_RequestStatus(char const * serialNo)" />
	/// <seealso cref="TC_StartPolling(char const * serialNo, int milliseconds)" />
	TCUBETEC_API DWORD __cdecl TC_GetStatusBits(char const * serialNo);

	/// <summary> Starts the internal polling loop which continuously requests position and status. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="milliseconds">The milliseconds polling rate. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="TC_StopPolling(char const * serialNo)" />
	/// <seealso cref="TC_PollingDuration(char const * serialNo)" />
	/// <seealso cref="TC_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="TC_RequestPosition(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	TCUBETEC_API bool __cdecl TC_StartPolling(char const * serialNo, int milliseconds);

	/// <summary> Gets the polling loop duration. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The time between polls in milliseconds or 0 if polling is not active. </returns>
	/// <seealso cref="TC_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="TC_StopPolling(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	TCUBETEC_API long __cdecl TC_PollingDuration(char const * serialNo);

	/// <summary> Stops the internal polling loop. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <seealso cref="TC_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="TC_PollingDuration(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	TCUBETEC_API void __cdecl TC_StopPolling(char const * serialNo);

	/// <summary> Gets the time in milliseconds since tha last message was received from the device. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="lastUpdateTimeMS"> The time since the last message was received in milliseconds. </param>
	/// <returns> True if monitoring is enabled otherwize False. </returns>
	/// <seealso cref="TC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// <seealso cref="TC_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	TCUBETEC_API bool __cdecl TC_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS );

	/// <summary> Enables the last message monitoring timer. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="enable"> True to enable monitoring otherwise False to disable. </param>
	/// <param name="lastMsgTimeout"> The last message error timeout in ms. 0 to disable. </param>
	/// <seealso cref="TC_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="TC_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	TCUBETEC_API void __cdecl TC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout );

	/// <summary> Queries if the time since the last message has exceeded the lastMsgTimeout set by <see cref="TC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )"/>. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> True if last message timer has elapsed, False if monitoring is not enabled or if time of last message received is less than lastMsgTimeout. </returns>
	/// <seealso cref="TC_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="TC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	TCUBETEC_API bool __cdecl TC_HasLastMsgTimerOverrun(char const * serialNo);

	/// <summary> Requests that all settings are download from device. </summary>
	/// <remarks> This function requests that the device upload all it's settings to the DLL.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	TCUBETEC_API short __cdecl TC_RequestSettings(char const * serialNo);
}
/** @} */ // TCubeTEC
