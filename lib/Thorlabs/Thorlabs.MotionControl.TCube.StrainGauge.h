// summary:	Declares the functions class
// The following ifdef block is the standard way of creating macros which make exporting from a
// DLL simpler. All files within this DLL are compiled with the TCUBESTRAINGAUGEDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project that
// uses this DLL. This way any other project whose source files include this file see 
// TCUBESTRAINGAUGE_API functions as being imported from a DLL, whereas this DLL sees
// symbols defined with this macro as being exported.

#pragma once

#ifdef TCUBESTRAINGAUGEDLL_EXPORTS
#define TCUBESTRAINGAUGE_API __declspec(dllexport)
#else
#define TCUBESTRAINGAUGE_API __declspec(dllimport)
#endif

#include <OaIdl.h>

/** @defgroup TCubeStrainGauge TCube Strain Gauge
 *  This section details the Structures and Functions relavent to the  @ref TSG001_page "TCube Strain Gauge"<br />
 *  For an example of how to connect to the device and perform simple operations use the following links:
 *  <list type=bullet>
 *    <item> \ref namespaces_tsg_ex_1 "Example of using the Thorlabs.MotionControl.TCube.StrainGauge.DLL from a C or C++ project."<br />
 *									  This requires the DLL to be dynamical linked. </item>
 *    <item> \ref namespaces_tsg_ex_2 "Example of using the Thorlabs.MotionControl.TCube.StrainGauge.DLL from a C# project"<br />
 *									  This uses Marshalling to load and access the C DLL. </item>
 *  </list>
 *  The Thorlabs.MotionControl.TCube.StrainGauge.DLL requires the following DLLs
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

	/// <summary> Values that represent THORLABSDEVICE_API Motor types. </summary>
	typedef enum MOT_MotorTypes
	{
		MOT_NotMotor = 0, /// <Not a motor.
		MOT_DCMotor = 1, /// <A DC Servo motor.
		MOT_StepperMotor = 2, /// <A Stepper motor.
		MOT_BrushlessMotor = 3, /// <A Brushless DC Motor.
		MOT_CustomMotor = 100, /// <A custom motor
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

	/// <summary> Values that represent Hub Analogue Output Modes. </summary>
	typedef enum TSG_Hub_Analogue_Modes : short
	{
		TSG_HubChannel1 = 1, ///<Analogue output applied to all Hub bays.
		TSG_HubChannel2 = 2, ///<Analogue output applied to adjacent Hub bays, i.e. (1-2,3-4,5-6). 
	} TSG_Hub_Analogue_Modes;

	/// <summary> Values that represent the Display / Status modes. </summary>
	typedef enum TSG_Display_Modes : short
	{
		TSG_Undefined = 0, ///<Undefined.
		TSG_Position = 1, ///<Displays / Outputs the status as a position.
		TSG_Voltage = 2, ///<Displays / Outputs the status as a voltage.
		TSG_Force = 3 ///<Displays / Outputs the status as a force.
	} TSG_Display_Modes;

	/// <summary> Structure containing the Strain Gauge input/output settings. </summary>
	typedef struct TSG_IOSettings
	{
		/// <summary> The hub analogue output mode. <list type=table>
		///				<item><term>Output to all hub positions</term><term>1</term></item>
		///				<item><term>Output to adjacent hub position</term><term>2</term></item>
		/// 		  </list> </summary>
		TSG_Hub_Analogue_Modes hubAnalogOutput;
		/// <summary> The current display / output mode. <list type=table>
		///				<item><term>Position</term><term>1</term></item>
		///				<item><term>Voltage</term><term>2</term></item>
		///				<item><term>Force</term><term>3</term></item>
		/// 		  </list> </summary>
		TSG_Display_Modes displayMode;
		/// <summary> Maximum force in mN, range 1 to 1000000 (0.001N to 1000N). </summary>
		unsigned int forceCalibration;
		/// <summary> Not used. </summary>
		WORD notYetInUse;
		/// <summary> Not used. </summary>
		WORD futureUse;
	} TSG_IOSettings;

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
	TCUBESTRAINGAUGE_API short __cdecl TLI_BuildDeviceList(void);

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
	TCUBESTRAINGAUGE_API short __cdecl TLI_GetDeviceListSize();

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
	TCUBESTRAINGAUGE_API short __cdecl TLI_GetDeviceList(SAFEARRAY** stringsReceiver);

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
	TCUBESTRAINGAUGE_API short __cdecl TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID);

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
	TCUBESTRAINGAUGE_API short __cdecl TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length);

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
	TCUBESTRAINGAUGE_API short __cdecl TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer);

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
	TCUBESTRAINGAUGE_API short __cdecl TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID);

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
	TCUBESTRAINGAUGE_API short __cdecl TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length);

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
	TCUBESTRAINGAUGE_API short __cdecl TLI_GetDeviceInfo(char const * serialNo, TLI_DeviceInfo *info);

	/// <summary> Initialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <remarks> Call TLI_InitializeSimulations before TLI_BuildDeviceList at the start of the program to make a connection to the simulation manager.<Br />
	/// 		  Any devices configured in the simulation manager will become visible TLI_BuildDeviceList is called and can be accessed using TLI_GetDeviceList.<Br />
	/// 		  Call TLI_InitializeSimulations at the end of the program to release the simulator.  </remarks>
	/// <seealso cref="TLI_UninitializeSimulations()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	TCUBESTRAINGAUGE_API void __cdecl TLI_InitializeSimulations();

	/// <summary> Uninitialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <seealso cref="TLI_InitializeSimulations()" />
	TCUBESTRAINGAUGE_API void __cdecl TLI_UninitializeSimulations();

	/// <summary> Open the device for communications. </summary>
	/// <param name="serialNo">	The serial no of the device to be connected. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="SG_Close(char const * serialNo)" />
	TCUBESTRAINGAUGE_API short __cdecl SG_Open(char const * serialNo);

	/// <summary> Disconnect and close the device. </summary>
	/// <param name="serialNo">	The serial no of the device to be disconnected. </param>
    /// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="SG_Open(char const * serialNo)" />
	TCUBESTRAINGAUGE_API void __cdecl SG_Close(char const * serialNo);

	/// <summary>	Check connection. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> true if the USB is listed by the ftdi controller</returns>
	/// \include CodeSnippet_CheckConnection.cpp
	TCUBESTRAINGAUGE_API bool __cdecl SG_CheckConnection(char const * serialNo);

	/// <summary> Sends a command to the device to make it identify iteself. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	TCUBESTRAINGAUGE_API void __cdecl SG_Identify(char const * serialNo);

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
	TCUBESTRAINGAUGE_API short __cdecl SG_GetHardwareInfo(char const * serialNo, char * modelNo, DWORD sizeOfModelNo, WORD * type, WORD * numChannels, 
														  char * notes, DWORD sizeOfNotes, DWORD * firmwareVersion, WORD * hardwareVersion, WORD * modificationState);

	/// <summary> Gets the hardware information in a block. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="hardwareInfo"> Address of a TLI_HardwareInformation structure to receive the hardware information. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	TCUBESTRAINGAUGE_API short __cdecl SG_GetHardwareInfoBlock(char const *serialNo, TLI_HardwareInformation *hardwareInfo);

	/// <summary> Gets version number of the device firmware. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device firmware version number made up of 4 byte parts. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	TCUBESTRAINGAUGE_API DWORD __cdecl SG_GetFirmwareVersion(char const * serialNo);

	/// <summary> Gets version number of the device software. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device software version number made up of 4 byte parts. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	TCUBESTRAINGAUGE_API DWORD __cdecl SG_GetSoftwareVersion(char const * serialNo);

	/// <summary> Update device with stored settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
    /// 		  \include CodeSnippet_connection1.cpp
	TCUBESTRAINGAUGE_API bool __cdecl SG_LoadSettings(char const * serialNo);

	/// <summary> Update device with named settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="settingsName"> Name of settings stored away from device. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	///             \include CodeSnippet_connection1.cpp
	TCUBESTRAINGAUGE_API bool __cdecl SG_LoadNamedSettings(char const * serialNo, char const *settingsName);

	/// <summary> persist the devices current settings. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	TCUBESTRAINGAUGE_API bool __cdecl SG_PersistSettings(char const * serialNo);

	/// <summary> Disable the device. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SG_Enable(char const * serialNo)" />
	TCUBESTRAINGAUGE_API short __cdecl SG_Disable(char const * serialNo);

	/// <summary> Enable device for computer control. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SG_Disable(char const * serialNo)" />
	TCUBESTRAINGAUGE_API short __cdecl SG_Enable(char const * serialNo);

	/// <summary> Tells the device that it is being disconnected. </summary>
	/// <remarks> This does not disconnect the communications.<br />
	/// 		  To disconnect the communications, call the <see cref="SG_Close(char const * serialNo)" /> function. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	TCUBESTRAINGAUGE_API short __cdecl SG_Disconnect(char const * serialNo);

	/// <summary> Gets the hub bay number this device is fitted to. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The number, 0x00 if unknown or 0xff if not on a hub. </returns>
	TCUBESTRAINGAUGE_API char __cdecl SG_GetHubBay(char const * serialNo);

	/// <summary> Requests the LED brightness. </summary>
	/// <param name="serialNo">The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SG_SetLEDBrightness(char const * serialNo, short brightness)" />
	/// <seealso cref="SG_GetLEDBrightness(char const * serialNo)" />
	TCUBESTRAINGAUGE_API short __cdecl SG_RequestLEDBrightness(char const * serialNo);

	/// <summary> Gets the LED brightness. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> Intensity from 0 (off) to 255. </returns>
	/// <seealso cref="SG_SetLEDBrightness(char const * serialNo, short brightness)" />
	/// <seealso cref="SG_RequestLEDBrightness(char const * serialNo)" />
	TCUBESTRAINGAUGE_API short __cdecl SG_GetLEDBrightness(char const * serialNo);

	/// <summary> Sets the LED brightness. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="brightness"> Intensity from 0 (off) to 255. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SG_GetLEDBrightness(char const * serialNo)" />
	/// <seealso cref="SG_RequestLEDBrightness(char const * serialNo)" />
	TCUBESTRAINGAUGE_API short __cdecl SG_SetLEDBrightness(char const * serialNo, short brightness);

	/// <summary> Clears the device message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	TCUBESTRAINGAUGE_API void __cdecl SG_ClearMessageQueue(char const * serialNo);

	/// <summary> Registers a callback on the message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="functionPointer"> A function pointer to be called whenever messages are received. </param>
	/// <seealso cref="SG_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="SG_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="SG_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	TCUBESTRAINGAUGE_API void __cdecl SG_RegisterMessageCallback(char const * serialNo, void (* functionPointer)());

	/// <summary> Gets the MessageQueue size. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> number of messages in the queue. </returns>
	/// <seealso cref="SG_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="SG_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="SG_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	TCUBESTRAINGAUGE_API int __cdecl SG_MessageQueueSize(char const * serialNo);

	/// <summary> Get the next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="SG_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="SG_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="SG_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	TCUBESTRAINGAUGE_API bool __cdecl SG_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Wait for next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="SG_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="SG_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="SG_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	TCUBESTRAINGAUGE_API bool __cdecl SG_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Starts the internal polling loop which continuously requests position and status. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="milliseconds">The milliseconds polling rate. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="SG_StopPolling(char const * serialNo)" />
	/// <seealso cref="SG_PollingDuration(char const * serialNo)" />
	/// <seealso cref="SG_RequestStatus(char const * serialNo)" />
	/// <seealso cref="SG_RequestPosition(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	TCUBESTRAINGAUGE_API bool __cdecl SG_StartPolling(char const * serialNo, int milliseconds);

	/// <summary> Gets the polling loop duration. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The time between polls in milliseconds or 0 if polling is not active. </returns>
	/// <seealso cref="SG_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="SG_StopPolling(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	TCUBESTRAINGAUGE_API long __cdecl SG_PollingDuration(char const * serialNo);

	/// <summary> Stops the internal polling loop. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <seealso cref="SG_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="SG_PollingDuration(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	TCUBESTRAINGAUGE_API void __cdecl SG_StopPolling(char const * serialNo);

	/// <summary> Gets the time in milliseconds since tha last message was received from the device. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="lastUpdateTimeMS"> The time since the last message was received in milliseconds. </param>
	/// <returns> True if monitoring is enabled otherwize False. </returns>
	/// <seealso cref="SG_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// <seealso cref="SG_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	TCUBESTRAINGAUGE_API bool __cdecl SG_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS );

	/// <summary> Enables the last message monitoring timer. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="enable"> True to enable monitoring otherwise False to disable. </param>
	/// <param name="lastMsgTimeout"> The last message error timeout in ms. 0 to disable. </param>
	/// <seealso cref="SG_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="SG_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	TCUBESTRAINGAUGE_API void __cdecl SG_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout );

	/// <summary> Queries if the time since the last message has exceeded the lastMsgTimeout set by <see cref="SG_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )"/>. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> True if last message timer has elapsed, False if monitoring is not enabled or if time of last message received is less than lastMsgTimeout. </returns>
	/// <seealso cref="SG_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="SG_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	TCUBESTRAINGAUGE_API bool __cdecl SG_HasLastMsgTimerOverrun(char const * serialNo);

	/// <summary> Requests that all settings are download from device. </summary>
	/// <remarks> This function requests that the device upload all it's settings to the DLL.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	TCUBESTRAINGAUGE_API short __cdecl SG_RequestSettings(char const * serialNo);

	/// <summary> Requests the status and reading from the device. </summary>
	/// <remarks> This needs to be called to get the device to send it's current status bits and reading.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="SG_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="SG_RequestReading(char const * serialNo)" />
	/// <seealso cref="SG_GetStatusBits(char const * serialNo)" />
	/// <seealso cref="SG_GetReadingExt(char const * serialNo, bool clipped, bool *overrange)" />
	/// <seealso cref="SG_StartPolling(char const * serialNo, int milliseconds)" />
	TCUBESTRAINGAUGE_API short __cdecl SG_RequestStatus(char const * serialNo);

	/// <summary>Get the current status bits. </summary>
	/// <remarks> This returns the latest status bits received from the device.<br />
	/// 		  To get new status bits, use <see cref="SG_RequestStatus(char const * serialNo)" />
	/// 		  or use the polling functions, <see cref="SG_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
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
	/// <seealso cref="SG_RequestStatus(char const * serialNo)" />
	/// <seealso cref="SG_StartPolling(char const * serialNo, int milliseconds)" />
	TCUBESTRAINGAUGE_API DWORD __cdecl SG_GetStatusBits(char const * serialNo);

	/// <summary> Requests the current reading. </summary>
	/// <remarks> This needs to be called to get the device to send it's current reading.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="SG_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="SG_GetReadingExt(char const * serialNo, bool clipped, bool *overrange)" />
	/// <seealso cref="SG_StartPolling(char const * serialNo, int milliseconds)" />
	TCUBESTRAINGAUGE_API short __cdecl SG_RequestReading(char const * serialNo);

	/// \deprecated
	/// <summary> Gets the current reading. </summary>
	/// <remarks> superceded by <see cref="SG_GetReadingExt(char const * serialNo, bool clipped, bool *overrange)"/> </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="smoothed"> not used. </param>
	/// <returns> The reading, which is mode dependent, see <see cref="SG_GetDisplayMode(char const * serialNo)" /><br />
	///			  The range is +/- 32767 which corresponds to +/- 100% of maximum value, see table.
	/// 		  <list type=table>
	///				<item><term>Position</term><term>Reading is the percentage of Max Travel (micrometres) <see cref="SG_GetMaximumTravel(char const * serialNo)" /> </term></item>
	///				<item><term>Voltage</term><term>Reading is the percentage of Max Voltage (V)</term></item>
	///				<item><term>Force</term><term>Reading is the percentage of Max Force (N) <see cref="SG_GetForceCalib(char const * serialNo)" /></term></item>
	/// 		  </list> </returns>
	/// <seealso cref="SG_RequestReading(char const * serialNo)" />
	/// <seealso cref="SG_GetReadingExt(char const * serialNo, bool clipped, bool *overrange)" />
	/// <seealso cref="SG_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="SG_GetDisplayMode(char const * serialNo)" />
	/// <seealso cref="SG_GetMaximumTravel(char const * serialNo)" />
	/// <seealso cref="SG_GetForceCalib(char const * serialNo)" />
	TCUBESTRAINGAUGE_API short __cdecl SG_GetReading(char const * serialNo, bool smoothed);

	/// <summary> Gets the current reading. </summary>
	/// <remarks> This returns the latest reading received from the device.<br />
	/// 		  To get a new reading, use <see cref="SG_RequestReading(char const * serialNo)" />
	/// 		  or use the polling functions, <see cref="SG_StartPolling(char const * serialNo, int milliseconds)" />.  </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="clipReadng"> if set, the reading will be clipped to +/- 32767. </param>
	/// <param name="overrange">  if the reading is overrange (outside +/- 32767) the content of this flag will be set to true. </param>
	/// <returns> The reading, which is mode dependent, see <see cref="SG_GetDisplayMode(char const * serialNo)" /><br />
	///			  The range if clipped is +/- 32767 which corresponds to +/- 100% of maximum value, see table.
	/// 		  <list type=table>
	///				<item><term>Position</term><term>Reading is the percentage of Max Travel (micrometres) <see cref="SG_GetMaximumTravel(char const * serialNo)" /> </term></item>
	///				<item><term>Voltage</term><term>Reading is the percentage of Max Voltage (V)</term></item>
	///				<item><term>Force</term><term>Reading is the percentage of Max Force (N) <see cref="SG_GetForceCalib(char const * serialNo)" /></term></item>
	/// 		  </list> </returns>
	/// <seealso cref="SG_RequestReading(char const * serialNo)" />
	/// <seealso cref="SG_GetReading(char const * serialNo, bool smoothed)" />
	/// <seealso cref="SG_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="SG_GetDisplayMode(char const * serialNo)" />
	/// <seealso cref="SG_GetMaximumTravel(char const * serialNo)" />
	/// <seealso cref="SG_GetForceCalib(char const * serialNo)" />
	TCUBESTRAINGAUGE_API int __cdecl SG_GetReadingExt(char const * serialNo, bool clipReadng, bool * overrange);

	/// <summary>Requests the maximum position. </summary>
	/// <param name="serialNo">The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SG_GetMaximumTravel(char const * serialNo)" />
	TCUBESTRAINGAUGE_API short __cdecl SG_RequestMaximumTravel(char const * serialNo);

	/// <summary> Gets the maximum travel of the strain gauge. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	The maximum travel in steps of 100nm, range 0 to 65535 </returns>
	/// <seealso cref="SG_RequestMaximumTravel(char const * serialNo)" />
	TCUBESTRAINGAUGE_API WORD __cdecl SG_GetMaximumTravel(char const * serialNo);

	/// <summary> Sets the voltage output to zero and defines the ensuing actuator position az zero. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	TCUBESTRAINGAUGE_API short __cdecl SG_SetZero(char const * serialNo);

	/// <summary>Requests the IO settings. </summary>
	/// <param name="serialNo">The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>	/// <seealso cref="SG_SetIOsettingsBlock(const char * serialNo, TSG_IOSettings *inputOutputSettings)" />
	/// <seealso cref="SG_SetIOsettings(char const * serialNo, TSG_Hub_Analogue_Modes hubAnalogOutput, TSG_Display_Modes displayMode, unsigned int calibrationForce)" />
	/// <seealso cref="SG_GetIOsettingsBlock(const char * serialNo, TSG_IOSettings *inputOutputSettings)" />
	/// <seealso cref="SG_SetHubAnalogOutput(char const * serialNo, TSG_Hub_Analogue_Modes hubAnalogOutput)" />
	/// <seealso cref="SG_GetHubAnalogOutput(char const * serialNo)" />
	/// <seealso cref="SG_GetDisplayMode(char const * serialNo)" />
	/// <seealso cref="SG_SetDisplayMode(char const * serialNo, TSG_Display_Modes mode)" />
	/// <seealso cref="SG_SetForceCalib(char const * serialNo, unsigned int forceCalibration)" />
	/// <seealso cref="SG_GetForceCalib(char const * serialNo)" />
	TCUBESTRAINGAUGE_API short __cdecl SG_RequestIOsettings(const char * serialNo);


	/// <summary> Gets the input/output settings in a block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="inputOutputSettings"> The address of the TSG_IOSettings block to receieve the IO Settings. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SG_SetIOsettingsBlock(const char * serialNo, TSG_IOSettings *inputOutputSettings)" />
	/// <seealso cref="SG_SetIOsettings(char const * serialNo, TSG_Hub_Analogue_Modes hubAnalogOutput, TSG_Display_Modes displayMode, unsigned int calibrationForce)" />
	/// <seealso cref="SG_RequestIOsettings(const char * serialNo)" />
	/// <seealso cref="SG_SetHubAnalogOutput(char const * serialNo, TSG_Hub_Analogue_Modes hubAnalogOutput)" />
	/// <seealso cref="SG_GetHubAnalogOutput(char const * serialNo)" />
	/// <seealso cref="SG_GetDisplayMode(char const * serialNo)" />
	/// <seealso cref="SG_SetDisplayMode(char const * serialNo, TSG_Display_Modes mode)" />
	/// <seealso cref="SG_SetForceCalib(char const * serialNo, unsigned int forceCalibration)" />
	/// <seealso cref="SG_GetForceCalib(char const * serialNo)" />
	TCUBESTRAINGAUGE_API short __cdecl SG_GetIOsettingsBlock(const char * serialNo, TSG_IOSettings *inputOutputSettings);

	/// <summary> Sets the input/output options in a block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="inputOutputSettings"> The address of the TSG_IOSettings block containing the new IO Settings. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SG_GetIOsettingsBlock(const char * serialNo, TSG_IOSettings *inputOutputSettings)" />
	/// <seealso cref="SG_SetIOsettings(char const * serialNo, TSG_Hub_Analogue_Modes hubAnalogOutput, TSG_Display_Modes displayMode, unsigned int calibrationForce)" />
	/// <seealso cref="SG_RequestIOsettings(const char * serialNo)" />
	/// <seealso cref="SG_SetHubAnalogOutput(char const * serialNo, TSG_Hub_Analogue_Modes hubAnalogOutput)" />
	/// <seealso cref="SG_GetHubAnalogOutput(char const * serialNo)" />
	/// <seealso cref="SG_GetDisplayMode(char const * serialNo)" />
	/// <seealso cref="SG_SetDisplayMode(char const * serialNo, TSG_Display_Modes mode)" />
	/// <seealso cref="SG_SetForceCalib(char const * serialNo, unsigned int forceCalibration)" />
	/// <seealso cref="SG_GetForceCalib(char const * serialNo)" />
	TCUBESTRAINGAUGE_API short __cdecl SG_SetIOsettingsBlock(const char * serialNo, TSG_IOSettings *inputOutputSettings);

	/// <summary> Sets the input/output options. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="hubAnalogOutput"> The hub analogue output mode
	/// 		<list type=table>
	///				<item><term>Output to all hub positions</term><term>1</term></item>
	///				<item><term>Output to adjacent hub position</term><term>2</term></item>
	/// 		  </list> </param>
	/// <param name="displayMode"> The display mode
	/// 				<list type=table>
	///						<item><term>Position</term><term>1</term></item>
	///						<item><term>Voltage</term><term>2</term></item>
	///						<item><term>Force</term><term>3</term></item>
	///		 		    </list> </param>
	/// <param name="calibrationForce"> The maximum force in mN, range 1000 to 1000000 (1N to 1000N). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SG_SetIOsettingsBlock(const char * serialNo, TSG_IOSettings *inputOutputSettings)" />
	/// <seealso cref="SG_GetIOsettingsBlock(const char * serialNo, TSG_IOSettings *inputOutputSettings)" />
	/// <seealso cref="SG_RequestIOsettings(const char * serialNo)" />
	/// <seealso cref="SG_SetHubAnalogOutput(char const * serialNo, TSG_Hub_Analogue_Modes hubAnalogOutput)" />
	/// <seealso cref="SG_GetHubAnalogOutput(char const * serialNo)" />
	/// <seealso cref="SG_GetDisplayMode(char const * serialNo)" />
	/// <seealso cref="SG_SetDisplayMode(char const * serialNo, TSG_Display_Modes mode)" />
	/// <seealso cref="SG_SetForceCalib(char const * serialNo, unsigned int forceCalibration)" />
	/// <seealso cref="SG_GetForceCalib(char const * serialNo)" />
	TCUBESTRAINGAUGE_API short __cdecl SG_SetIOsettings(char const * serialNo, TSG_Hub_Analogue_Modes hubAnalogOutput, TSG_Display_Modes displayMode, unsigned int calibrationForce);

	/// <summary>Requests the Hub Analog Output. </summary>
	/// <param name="serialNo">The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>	/// <seealso cref="SG_SetIOsettingsBlock(const char * serialNo, TSG_IOSettings *inputOutputSettings)" />
	/// <seealso cref="SG_SetHubAnalogOutput(char const * serialNo, TSG_Hub_Analogue_Modes hubAnalogOutput)" />
	/// <seealso cref="SG_GetHubAnalogOutput(char const * serialNo)" />
	TCUBESTRAINGAUGE_API short __cdecl SG_RequestHubAnalogOutput(const char * serialNo);

	/// <summary> Gets the Hub Analog Output. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The hub analogue mode.
	/// 		  <list type=table>
	///				<item><term>Output to all hub positions</term><term>1</term></item>
	///				<item><term>Output to adjacent hub position</term><term>2</term></item>
	/// 		  </list> </returns>
	/// <seealso cref="SG_SetHubAnalogOutput(char const * serialNo, TSG_Hub_Analogue_Modes hubAnalogOutput)" />
	/// <seealso cref="SG_SetIOsettingsBlock(const char * serialNo, TSG_IOSettings *inputOutputSettings)" />
	/// <seealso cref="SG_GetIOsettingsBlock(const char * serialNo, TSG_IOSettings *inputOutputSettings)" />
	/// <seealso cref="SG_SetIOsettings(char const * serialNo, TSG_Hub_Analogue_Modes hubAnalogOutput, TSG_Display_Modes displayMode, unsigned int calibrationForce)" />
	/// <seealso cref="SG_RequestIOsettings(const char * serialNo)" />
	/// <seealso cref="SG_RequestHubAnalogOutput(const char * serialNo)" />
	/// <seealso cref="SG_GetDisplayMode(char const * serialNo)" />
	/// <seealso cref="SG_SetDisplayMode(char const * serialNo, TSG_Display_Modes mode)" />
	TCUBESTRAINGAUGE_API TSG_Hub_Analogue_Modes __cdecl SG_GetHubAnalogOutput(char const * serialNo);

	/// <summary> Sets the Hub Analog Output. </summary>
	/// <param name="serialNo">		   The serial no. </param>
	/// <param name="hubAnalogOutput"> The hub analogue mode.
	/// 		  <list type=table>
	///				<item><term>Output to all hub positions</term><term>1</term></item>
	///				<item><term>Output to adjacent hub position</term><term>2</term></item>
	/// 		  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SG_GetHubAnalogOutput(char const * serialNo)" />
	/// <seealso cref="SG_SetIOsettingsBlock(const char * serialNo, TSG_IOSettings *inputOutputSettings)" />
	/// <seealso cref="SG_GetIOsettingsBlock(const char * serialNo, TSG_IOSettings *inputOutputSettings)" />
	/// <seealso cref="SG_SetIOsettings(char const * serialNo, TSG_Hub_Analogue_Modes hubAnalogOutput, TSG_Display_Modes displayMode, unsigned int calibrationForce)" />
	/// <seealso cref="SG_RequestIOsettings(const char * serialNo)" />
	/// <seealso cref="SG_RequestHubAnalogOutput(const char * serialNo)" />
	/// <seealso cref="SG_GetDisplayMode(char const * serialNo)" />
	/// <seealso cref="SG_SetDisplayMode(char const * serialNo, TSG_Display_Modes mode)" />
	TCUBESTRAINGAUGE_API short __cdecl SG_SetHubAnalogOutput(char const * serialNo, TSG_Hub_Analogue_Modes hubAnalogOutput);

	/// <summary>Requests the Display Mode. </summary>
	/// <param name="serialNo">The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>	/// <seealso cref="SG_SetIOsettingsBlock(const char * serialNo, TSG_IOSettings *inputOutputSettings)" />
	/// <seealso cref="SG_SetDisplayMode(char const * serialNo, TSG_Display_Modes mode)" />
	/// <seealso cref="SG_GetDisplayMode(char const * serialNo)" />
	TCUBESTRAINGAUGE_API short __cdecl SG_RequestDisplayMode(const char * serialNo);

	/// <summary> Gets the display mode. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The display mode.
	/// 				<list type=table>
	///						<item><term>Position</term><term>1</term></item>
	///						<item><term>Voltage</term><term>2</term></item>
	///						<item><term>Force</term><term>3</term></item>
	///		 		    </list> </returns>
	/// <seealso cref="SG_SetDisplayMode(char const * serialNo, TSG_Display_Modes mode)" />
	/// <seealso cref="SG_SetIOsettingsBlock(const char * serialNo, TSG_IOSettings *inputOutputSettings)" />
	/// <seealso cref="SG_GetIOsettingsBlock(const char * serialNo, TSG_IOSettings *inputOutputSettings)" />
	/// <seealso cref="SG_SetIOsettings(char const * serialNo, TSG_Hub_Analogue_Modes hubAnalogOutput, TSG_Display_Modes displayMode, unsigned int calibrationForce)" />
	/// <seealso cref="SG_RequestIOsettings(const char * serialNo)" />
	/// <seealso cref="SG_RequestDisplayMode(const char * serialNo)" />
	TCUBESTRAINGAUGE_API TSG_Display_Modes __cdecl SG_GetDisplayMode(char const * serialNo);

	/// <summary> Sets the display mode. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="mode"> The display mode.
	/// 				<list type=table>
	///						<item><term>Position</term><term>1</term></item>
	///						<item><term>Voltage</term><term>2</term></item>
	///						<item><term>Force</term><term>3</term></item>
	///		 		    </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SG_GetDisplayMode(char const * serialNo)" />
	/// <seealso cref="SG_SetIOsettingsBlock(const char * serialNo, TSG_IOSettings *inputOutputSettings)" />
	/// <seealso cref="SG_GetIOsettingsBlock(const char * serialNo, TSG_IOSettings *inputOutputSettings)" />
	/// <seealso cref="SG_SetIOsettings(char const * serialNo, TSG_Hub_Analogue_Modes hubAnalogOutput, TSG_Display_Modes displayMode, unsigned int calibrationForce)" />
	/// <seealso cref="SG_RequestIOsettings(const char * serialNo)" />
	/// <seealso cref="SG_RequestDisplayMode(const char * serialNo)" />
	TCUBESTRAINGAUGE_API short __cdecl SG_SetDisplayMode(char const * serialNo, TSG_Display_Modes mode);

	/// <summary>Requests the Force Calib. </summary>
	/// <param name="serialNo">The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>	/// <seealso cref="SG_SetIOsettingsBlock(const char * serialNo, TSG_IOSettings *inputOutputSettings)" />
	/// <seealso cref="SG_SetForceCalib(char const * serialNo, unsigned int forceCalibration)" />
	/// <seealso cref="SG_GetForceCalib(char const * serialNo)" />
	TCUBESTRAINGAUGE_API short __cdecl SG_RequestForceCalib(const char * serialNo);

	/// <summary> Gets the maximum force in calibration. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The maximum force in mN, range 1000 to 1000000 (1N to 1000N). </returns>
	/// <seealso cref="SG_SetForceCalib(char const * serialNo, unsigned int forceCalibration)" />
	/// <seealso cref="SG_SetIOsettingsBlock(const char * serialNo, TSG_IOSettings *inputOutputSettings)" />
	/// <seealso cref="SG_GetIOsettingsBlock(const char * serialNo, TSG_IOSettings *inputOutputSettings)" />
	/// <seealso cref="SG_SetIOsettings(char const * serialNo, TSG_Hub_Analogue_Modes hubAnalogOutput, TSG_Display_Modes displayMode, unsigned int calibrationForce)" />
	/// <seealso cref="SG_RequestIOsettings(const char * serialNo)" />
	/// <seealso cref="SG_RequestForceCalib(const char * serialNo)" />
	TCUBESTRAINGAUGE_API unsigned int __cdecl SG_GetForceCalib(char const * serialNo);

	/// <summary> Sets the maximum force in calibration. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="forceCalibration"> The maximum force in mN, range 1000 to 1000000 (1N to 1000N). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SG_GetForceCalib(char const * serialNo)" />
	/// <seealso cref="SG_SetIOsettingsBlock(const char * serialNo, TSG_IOSettings *inputOutputSettings)" />
	/// <seealso cref="SG_GetIOsettingsBlock(const char * serialNo, TSG_IOSettings *inputOutputSettings)" />
	/// <seealso cref="SG_SetIOsettings(char const * serialNo, TSG_Hub_Analogue_Modes hubAnalogOutput, TSG_Display_Modes displayMode, unsigned int calibrationForce)" />
	/// <seealso cref="SG_RequestIOsettings(const char * serialNo)" />
	/// <seealso cref="SG_RequestForceCalib(const char * serialNo)" />
	TCUBESTRAINGAUGE_API short __cdecl SG_SetForceCalib(char const * serialNo, unsigned int forceCalibration);
}
/** @} */ // TCubeStrainGauge