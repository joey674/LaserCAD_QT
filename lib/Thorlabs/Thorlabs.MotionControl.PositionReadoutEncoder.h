// summary:	Declares the functions class
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the POSITIONREADOUTENCODERDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// POSITIONREADOUTENCODER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef POSITIONREADOUTENCODERDLL_EXPORTS
#define POSITIONREADOUTENCODER_API __declspec(dllexport)
#else
#define POSITIONREADOUTENCODER_API __declspec(dllimport)
#endif

#include <OaIdl.h>

#pragma once

/** @defgroup Common Common Enums, structs and Functions
 *  This section details the Structures and Functions common to all devices
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

	/// <summary> Values that represent Display Backlight. </summary>
	typedef enum ENC_DisplayBacklightData
	{
		ENC_On = 0,
		ENC_Off = 1,
	} ENC_DisplayBacklightData;

	/// <summary> Values that represent Directional Sense. </summary>
	typedef enum ENC_DirectionalSenseData
	{
		ENC_DirNormal = 0,
		ENC_DirInverted = 1,
	} ENC_DirectionalSenseData;

	/// <summary> Values that represent Display Orientation. </summary>
	typedef enum ENC_DisplayOrientationData
	{
		ENC_OriNormal = 0,
		ENC_OriInverted = 1,
	} ENC_DisplayOrientationData;

	/// <summary> Values that represent Display Units. </summary>
	typedef enum ENC_DisplayUnitsData
	{
		ENC_MM = 0,
		ENC_INCH = 1,
	} ENC_DisplayUnitsData;
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

	typedef struct TLI_DevParams
	{
		/// <summary>	The params[10]. </summary>
		long params[0x0a];
	}TLI_DevParams;
	#pragma pack()

	/// <summary>	A qd display parameters. </summary>
	typedef struct ENC_DisplayParams
	{
		/// <summary>	The display backlight. </summary>
		ENC_DisplayBacklightData displayBacklight;
		/// <summary>	The directional sense. </summary>
		ENC_DirectionalSenseData directionalSense;
		/// <summary>	The display orientation. </summary>
		ENC_DisplayOrientationData displayOrientation;
		/// <summary>	The display unit. </summary>
		ENC_DisplayUnitsData displayUnit;
		/// <summary>	Reserved. </summary>
		__int16 reserved1;
		/// <summary>	Reserved. </summary>
		__int16 reserved2;
		/// <summary>	Reserved. </summary>
		__int16 reserved3;
		/// <summary>	Reserved. </summary>
		__int16 reserved4;
	} ENC_DisplayParams;

	extern "C"
	{
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
		POSITIONREADOUTENCODER_API short __cdecl TLI_BuildDeviceList(void);

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
		POSITIONREADOUTENCODER_API short __cdecl TLI_GetDeviceListSize();

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
		POSITIONREADOUTENCODER_API short __cdecl TLI_GetDeviceList(SAFEARRAY** stringsReceiver);

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
		POSITIONREADOUTENCODER_API short __cdecl TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID);

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
		POSITIONREADOUTENCODER_API short __cdecl TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length);

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
		POSITIONREADOUTENCODER_API short __cdecl TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer);

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
		POSITIONREADOUTENCODER_API short __cdecl TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID);

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
		POSITIONREADOUTENCODER_API short __cdecl TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length);

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
		POSITIONREADOUTENCODER_API short __cdecl TLI_GetDeviceInfo(char const * serialNo, TLI_DeviceInfo *info);

		/// <summary> Initialize a connection to the Simulation Manager, which must already be running. </summary>
		/// <remarks> Call TLI_InitializeSimulations before TLI_BuildDeviceList at the start of the program to make a connection to the simulation manager.<Br />
		/// 		  Any devices configured in the simulation manager will become visible TLI_BuildDeviceList is called and can be accessed using TLI_GetDeviceList.<Br />
		/// 		  Call TLI_InitializeSimulations at the end of the program to release the simulator.  </remarks>
		/// <seealso cref="TLI_UninitializeSimulations()" />
		/// <seealso cref="TLI_BuildDeviceList()" />
		/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
		POSITIONREADOUTENCODER_API void __cdecl TLI_InitializeSimulations();

		/// <summary> Uninitialize a connection to the Simulation Manager, which must already be running. </summary>
		/// <seealso cref="TLI_InitializeSimulations()" />
		POSITIONREADOUTENCODER_API void __cdecl TLI_UninitializeSimulations();

		/// <summary> Open the device for communications. </summary>
		/// <param name="serialNo">	The serial no of the device to be connected. </param>
		/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
		/// 		  \include CodeSnippet_connection1.cpp
		/// <seealso cref="EN_Close(char const * serialNo)" />
		POSITIONREADOUTENCODER_API short __cdecl EN_Open(char const * serialNo);

		/// <summary> Disconnect and close the device. </summary>
		/// <param name="serialNo">	The serial no of the device to be disconnected. </param>
		/// 		  \include CodeSnippet_connection1.cpp
		/// <seealso cref="EN_Open(char const * serialNo)" />
		POSITIONREADOUTENCODER_API void __cdecl EN_Close(char const * serialNo);

		/// <summary>	Check connection. </summary>
		/// <param name="serialNo">	The device serial no. </param>
		/// <returns> true if the USB is listed by the ftdi controller</returns>
		/// \include CodeSnippet_CheckConnection.cpp
		POSITIONREADOUTENCODER_API bool __cdecl EN_CheckConnection(char const * serialNo);

		/// <summary> Sends a command to the device to make it identify iteself. </summary>
		/// <param name="serialNo">	The device serial no. </param>
		POSITIONREADOUTENCODER_API void __cdecl EN_Identify(char const * serialNo);

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
		POSITIONREADOUTENCODER_API short __cdecl EN_GetHardwareInfo(char const * serialNo, char * modelNo, DWORD sizeOfModelNo, WORD * type, WORD * numChannels,
			char * notes, DWORD sizeOfNotes, DWORD * firmwareVersion, WORD * hardwareVersion, WORD * modificationState);

		/// <summary> Gets the hardware information in a block. </summary>
		/// <param name="serialNo">	The device serial no. </param>
		/// <param name="hardwareInfo"> Address of a TLI_HardwareInformation structure to receive the hardware information. </param>
		/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
		/// 		  \include CodeSnippet_identify.cpp
		POSITIONREADOUTENCODER_API short __cdecl EN_GetHardwareInfoBlock(char const *serialNo, TLI_HardwareInformation *hardwareInfo);

		/// <summary> Gets version number of the device firmware. </summary>
		/// <param name="serialNo">	The device serial no. </param>
		/// <returns> The device firmware version number made up of 4 byte parts. </returns>
		/// 		  \include CodeSnippet_identify.cpp
		POSITIONREADOUTENCODER_API DWORD __cdecl EN_GetFirmwareVersion(char const * serialNo);

		/// <summary> Gets version number of the device software. </summary>
		/// <param name="serialNo">	The device serial no. </param>
		/// <returns> The device software version number made up of 4 byte parts. </returns>
		/// 		  \include CodeSnippet_identify.cpp
		POSITIONREADOUTENCODER_API DWORD __cdecl EN_GetSoftwareVersion(char const * serialNo);

		/// <summary> Update device with stored settings. </summary>
		/// <param name="serialNo"> The device serial no. </param>
		/// <returns> <c>true</c> if successful, false if not. </returns>
		/// 		  \include CodeSnippet_connection1.cpp
		POSITIONREADOUTENCODER_API bool __cdecl EN_LoadSettings(char const * serialNo);

		/// <summary> Update device with named settings. </summary>
		/// <param name="serialNo"> The device serial no. </param>
		/// <param name="settingsName"> Name of settings stored away from device. </param>
		/// <returns> <c>true</c> if successful, false if not. </returns>
		///             \include CodeSnippet_connection1.cpp
		POSITIONREADOUTENCODER_API bool __cdecl EN_LoadNamedSettings(char const * serialNo, char const *settingsName);

		/// <summary> persist the devices current settings. </summary>
		/// <param name="serialNo">	The device serial no. </param>
		/// <returns> <c>true</c> if successful, false if not. </returns>
		POSITIONREADOUTENCODER_API bool __cdecl EN_PersistSettings(char const * serialNo);

		/// <summary> Reset the stage settings to defaults. </summary>
		/// <param name="serialNo"> The device serial no. </param>
		/// <returns> <c>true</c> if successful, false if not. </returns>
		POSITIONREADOUTENCODER_API short __cdecl EN_ResetParameters(char const * serialNo);
	
		/// <summary> Get the current position. </summary>
		/// <param name="serialNo">	The device serial no. </param>
		/// <returns> The current position. </returns>
		/// \note
		/// Prior to Kinesis version 1.14.42 the return type for this function is WORD.
		///
		/// <seealso cref="EN_RequestPosition(char const * serialNo)" />
		/// <seealso cref="EN_SetZero(char const * serialNo)" />
		POSITIONREADOUTENCODER_API int __cdecl EN_GetPosition(char const * serialNo);

		/// <summary>	Requests the current position. </summary>
		/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
		POSITIONREADOUTENCODER_API short __cdecl EN_RequestPosition(char const * serialNo);

		/// <summary> Sets the device to zero. </summary>
		/// <param name="serialNo">	The device serial no. </param>
		/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
		/// <seealso cref="EN_RequestPosition(char const * serialNo)" />
		/// <seealso cref="EN_GetPosition(char const * serialNo)" />
		POSITIONREADOUTENCODER_API short __cdecl EN_SetZero(char const * serialNo);

		/// <summary> Request the device calibration. </summary>
		/// <param name="serialNo">	The device serial no. </param>
		/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
		POSITIONREADOUTENCODER_API short __cdecl EN_RequestCalibrate(char const * serialNo);

		/// <summary> Get the device calibration status. </summary>
		/// <param name="serialNo">	The device serial no. </param>
		/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
		POSITIONREADOUTENCODER_API bool __cdecl EN_GetCalibrateStatus(char const * serialNo);

		/// <summary> Requests the display parameters. </summary>
		/// <param name="serialNo">	The device serial no. </param>
		/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
		/// <seealso cref="EN_GetDisplayParams(char const * serialNo, ENC_DisplayBacklightData *dispBacklight, ENC_DirectionalSenseData *directionalSense, ENC_DisplayOrientationData *dispOrientation, ENC_DisplayUnitsData *dispUnit)" />
		/// <seealso cref="EN_SetDisplayParams(char const * serialNo, ENC_DisplayBacklightData dispBacklight, ENC_DirectionalSenseData directionalSense, ENC_DisplayOrientationData dispOrientation, ENC_DisplayUnitsData dispUnit)" />
		/// <seealso cref="EN_GetDisplayParamsBlock(char const * serialNo, ENC_DisplayParams *params)" />
		/// <seealso cref="EN_SetDisplayParamsBlock(char const * serialNo, ENC_DisplayParams *params)" />
		POSITIONREADOUTENCODER_API short __cdecl EN_RequestDisplayParams(char const * serialNo);

		/// <summary> Get the display parameters. </summary>
		/// <param name="serialNo">	The device serial no. </param>
		/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
		/// <seealso cref="EN_RequestDisplayParams(char const * serialNo)" />
		/// <seealso cref="EN_SetDisplayParams(char const * serialNo, ENC_DisplayBacklightData dispBacklight, ENC_DirectionalSenseData directionalSense, ENC_DisplayOrientationData dispOrientation, ENC_DisplayUnitsData dispUnit)" />
		/// <seealso cref="EN_GetDisplayParamsBlock(char const * serialNo, ENC_DisplayParams *params)" />
		/// <seealso cref="EN_SetDisplayParamsBlock(char const * serialNo, ENC_DisplayParams *params)" />
		POSITIONREADOUTENCODER_API short __cdecl EN_GetDisplayParams(char const * serialNo, ENC_DisplayBacklightData *dispBacklight, ENC_DirectionalSenseData *directionalSense, ENC_DisplayOrientationData *dispOrientation, ENC_DisplayUnitsData *dispUnit);

		/// <summary> Set the display parameters. </summary>
		/// <param name="serialNo">	The device serial no. </param>
		/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
		/// <seealso cref="EN_RequestDisplayParams(char const * serialNo)" />
		/// <seealso cref="EN_GetDisplayParams(char const * serialNo, ENC_DisplayBacklightData *dispBacklight, ENC_DirectionalSenseData *directionalSense, ENC_DisplayOrientationData *dispOrientation, ENC_DisplayUnitsData *dispUnit)" />
		/// <seealso cref="EN_GetDisplayParamsBlock(char const * serialNo, ENC_DisplayParams *params)" />
		/// <seealso cref="EN_SetDisplayParamsBlock(char const * serialNo, ENC_DisplayParams *params)" />
		POSITIONREADOUTENCODER_API short __cdecl EN_SetDisplayParams(char const * serialNo, ENC_DisplayBacklightData dispBacklight, ENC_DirectionalSenseData directionalSense, ENC_DisplayOrientationData dispOrientation, ENC_DisplayUnitsData dispUnit);

		/// <summary> Get the display parameters block. </summary>
		/// <param name="serialNo">	The device serial no. </param>
		/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
		/// <seealso cref="EN_RequestDisplayParams(char const * serialNo)" />
		/// <seealso cref="EN_GetDisplayParams(char const * serialNo, ENC_DisplayBacklightData *dispBacklight, ENC_DirectionalSenseData *directionalSense, ENC_DisplayOrientationData *dispOrientation, ENC_DisplayUnitsData *dispUnit)" />
		/// <seealso cref="EN_SetDisplayParams(char const * serialNo, ENC_DisplayBacklightData dispBacklight, ENC_DirectionalSenseData directionalSense, ENC_DisplayOrientationData dispOrientation, ENC_DisplayUnitsData dispUnit)" />
		/// <seealso cref="EN_SetDisplayParamsBlock(char const * serialNo, ENC_DisplayParams *params)" />
		POSITIONREADOUTENCODER_API short __cdecl EN_GetDisplayParamsBlock(char const * serialNo, ENC_DisplayParams *params);

		/// <summary> Set the display parameters block. </summary>
		/// <param name="serialNo">	The device serial no. </param>
		/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
		/// <seealso cref="EN_RequestDisplayParams(char const * serialNo)" />
		/// <seealso cref="EN_GetDisplayParams(char const * serialNo, ENC_DisplayBacklightData *dispBacklight, ENC_DirectionalSenseData *directionalSense, ENC_DisplayOrientationData *dispOrientation, ENC_DisplayUnitsData *dispUnit)" />
		/// <seealso cref="EN_SetDisplayParams(char const * serialNo, ENC_DisplayBacklightData dispBacklight, ENC_DirectionalSenseData directionalSense, ENC_DisplayOrientationData dispOrientation, ENC_DisplayUnitsData dispUnit)" />
		/// <seealso cref="EN_GetDisplayParamsBlock(char const * serialNo, ENC_DisplayParams *params)" />
		POSITIONREADOUTENCODER_API short __cdecl EN_SetDisplayParamsBlock(char const * serialNo, ENC_DisplayParams *params);

		/// <summary> Clears the device message queue. </summary>
		/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
		/// <param name="serialNo"> The device serial no. </param>
		POSITIONREADOUTENCODER_API void __cdecl EN_ClearMessageQueue(char const * serialNo);

		/// <summary> Registers a callback on the message queue. </summary>
		/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
		/// <param name="serialNo"> The device serial no. </param>
		/// <param name="functionPointer"> A function pointer to be called whenever messages are received. </param>
		/// <seealso cref="EN_MessageQueueSize(char const * serialNo)" />
		/// <seealso cref="EN_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
		/// <seealso cref="EN_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
		POSITIONREADOUTENCODER_API void __cdecl EN_RegisterMessageCallback(char const * serialNo, void(*functionPointer)());

		/// <summary> Gets the MessageQueue size. </summary>
		/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
		/// <param name="serialNo"> The device serial no. </param>
		/// <returns> number of messages in the queue. </returns>
		/// <seealso cref="EN_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
		/// <seealso cref="EN_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
		/// <seealso cref="EN_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
		POSITIONREADOUTENCODER_API int __cdecl EN_MessageQueueSize(char const * serialNo);

		/// <summary> Get the next MessageQueue item. </summary>
		/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
		/// <param name="serialNo"> The device serial no. </param>
		/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
		/// <param name="messageID">   The address of the parameter to receive the message id. </param>
		/// <param name="messageData"> The address of the parameter to receive the message data. </param>
		/// <returns> <c>true</c> if successful, false if not. </returns>
		/// <seealso cref="EN_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
		/// <seealso cref="EN_MessageQueueSize(char const * serialNo)" />
		/// <seealso cref="EN_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
		POSITIONREADOUTENCODER_API bool __cdecl EN_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

		/// <summary> Wait for next MessageQueue item. </summary>
		/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
		/// <param name="serialNo"> The device serial no. </param>
		/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
		/// <param name="messageID">   The address of the parameter to receive the message id. </param>
		/// <param name="messageData"> The address of the parameter to receive the message data. </param>
		/// <returns> <c>true</c> if successful, false if not. </returns>
		/// <seealso cref="EN_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
		/// <seealso cref="EN_MessageQueueSize(char const * serialNo)" />
		/// <seealso cref="EN_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
		POSITIONREADOUTENCODER_API bool __cdecl EN_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

		/// <summary> Starts the internal polling loop which continuously requests position and status. </summary>
		/// <param name="serialNo"> The device serial no. </param>
		/// <param name="milliseconds">The milliseconds polling rate. </param>
		/// <returns> <c>true</c> if successful, false if not. </returns>
		/// <seealso cref="EN_StopPolling(char const * serialNo)" />
		/// <seealso cref="EN_PollingDuration(char const * serialNo)" />
		/// <seealso cref="EN_RequestStatusBits(char const * serialNo)" />
		/// <seealso cref="EN_RequestStatus(char const * serialNo)" />
		/// <seealso cref="EN_RequestReadings(char const * serialNo)" />
		/// \include CodeSnippet_connection1.cpp
		POSITIONREADOUTENCODER_API bool __cdecl EN_StartPolling(char const * serialNo, int milliseconds);

		/// <summary> Gets the polling loop duration. </summary>
		/// <param name="serialNo"> The device serial no. </param>
		/// <returns> The time between polls in milliseconds or 0 if polling is not active. </returns>
		/// <seealso cref="EN_StartPolling(char const * serialNo, int milliseconds)" />
		/// <seealso cref="EN_StopPolling(char const * serialNo)" />
		/// \include CodeSnippet_connection1.cpp
		POSITIONREADOUTENCODER_API long __cdecl EN_PollingDuration(char const * serialNo);

		/// <summary> Stops the internal polling loop. </summary>
		/// <param name="serialNo"> The device serial no. </param>
		/// <seealso cref="EN_StartPolling(char const * serialNo, int milliseconds)" />
		/// <seealso cref="EN_PollingDuration(char const * serialNo)" />
		/// \include CodeSnippet_connection1.cpp
		POSITIONREADOUTENCODER_API void __cdecl EN_StopPolling(char const * serialNo);

		/// <summary> Gets the time in milliseconds since tha last message was received from the device. </summary>
		/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
		/// <param name="serialNo"> The device serial no. </param>
		/// <param name="lastUpdateTimeMS"> The time since the last message was received in milliseconds. </param>
		/// <returns> True if monitoring is enabled otherwize False. </returns>
		/// <seealso cref="EN_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
		/// <seealso cref="EN_HasLastMsgTimerOverrun(char const * serialNo)" />
		/// \include CodeSnippet_connectionMonitoring.cpp
		POSITIONREADOUTENCODER_API bool __cdecl EN_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS);

		/// <summary> Enables the last message monitoring timer. </summary>
		/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
		/// <param name="serialNo"> The device serial no. </param>
		/// <param name="enable"> True to enable monitoring otherwise False to disable. </param>
		/// <param name="lastMsgTimeout"> The last message error timeout in ms. 0 to disable. </param>
		/// <seealso cref="EN_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
		/// <seealso cref="EN_HasLastMsgTimerOverrun(char const * serialNo)" />
		/// \include CodeSnippet_connectionMonitoring.cpp
		POSITIONREADOUTENCODER_API void __cdecl EN_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout);

		/// <summary> Queries if the time since the last message has exceeded the lastMsgTimeout set by <see cref="LD_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )"/>. </summary>
		/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
		/// <param name="serialNo"> The device serial no. </param>
		/// <returns> True if last message timer has elapsed, False if monitoring is not enabled or if time of last message received is less than lastMsgTimeout. </returns>
		/// <seealso cref="EN_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
		/// <seealso cref="EN_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
		/// \include CodeSnippet_connectionMonitoring.cpp
		POSITIONREADOUTENCODER_API bool __cdecl EN_HasLastMsgTimerOverrun(char const * serialNo);

		/// <summary> Requests that all settings are download from device. </summary>
		/// <remarks> This function requests that the device upload all it's settings to the DLL.</remarks>
		/// <param name="serialNo">	The device serial no. </param>
		/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
		POSITIONREADOUTENCODER_API short __cdecl EN_RequestSettings(char const * serialNo);

		POSITIONREADOUTENCODER_API short __cdecl XXX_RequestDevParams(char const * serialNo);

		POSITIONREADOUTENCODER_API short __cdecl XXX_GetDevParams(char const * serialNo, TLI_DevParams * devParams);

		POSITIONREADOUTENCODER_API short __cdecl XXX_SetDevParams(char const * serialNo, TLI_DevParams * devParams);
	}
}
/** @} */ // Position Readout Encoder
