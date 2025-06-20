// summary:	Declares the functions class
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the KCUBELIQUIDCRYSTALDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// KCUBELIQUIDCRYSTAL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef KCUBELIQUIDCRYSTALDLL_EXPORTS
#define KCUBELIQUIDCRYSTAL_API __declspec(dllexport)
#else
#define KCUBELIQUIDCRYSTAL_API __declspec(dllimport)
#endif

#include <OaIdl.h>

#pragma once

/** @defgroup KCubeLiquidCrystal KCube Liquid Crystal
 *  This section details the Structures and Functions relavent to the  @ref KLC101_page "KCube Liquid Crystal"<br />
 *  For an example of how to connect to the device and perform simple operations use the following links:
 *  <list type=bullet>
 *    <item> \ref namespaces_klc_ex_1 "Example of using the Thorlabs.MotionControl.KCube.LiquidCrystal.DLL from a C or C++ project."<br />
 *									  This requires the DLL to be dynamical linked. </item>
 *    <item> \ref namespaces_klc_ex_2 "Example of using the Thorlabs.MotionControl.KCube.LiquidCrystal.DLL from a C# project"<br />
 *									  This uses Marshalling to load and access the C DLL. </item>
 *  </list>
 *  The Thorlabs.MotionControl.KCube.LiquidCrystal.DLL requires the following DLLs
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

	/// <summary> Structure containing the KLC operating parameters. </summary>
	typedef struct KLC_KCubeMMIParams
	{
		/// <summary> The display intensity. Range: 0 (0%) to 100 (100%). </summary>
		unsigned __int16 DisplayIntensity;
		/// <summary> The display timeout in miniutes. Range: -1 to 480 (-1 = Timeout disabled). </summary>
		__int16 DisplayTimeout;

		__int16 reserved[2];
	} KLC_KCubeMMIParams;

	/// <summary> Structure containing the preset voltage for a KLC preset. </summary>
	typedef struct KLC_Preset
	{
		/// <summary> Voltage, range 0 (0V) to 25000 (25V). </summary>
		unsigned __int16 Voltage;
		/// <summary> Frequency, range 2000 (2kHz) to 10000 (10kHz). </summary>
		unsigned __int16 Frequency;
	} KLC_Preset;

#pragma pack()

#pragma region Common

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
	KCUBELIQUIDCRYSTAL_API short __cdecl TLI_BuildDeviceList(void);

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
	KCUBELIQUIDCRYSTAL_API short __cdecl TLI_GetDeviceListSize();

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
	KCUBELIQUIDCRYSTAL_API short __cdecl TLI_GetDeviceList(SAFEARRAY** stringsReceiver);

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
	KCUBELIQUIDCRYSTAL_API short __cdecl TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID);

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
	KCUBELIQUIDCRYSTAL_API short __cdecl TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length);

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
	KCUBELIQUIDCRYSTAL_API short __cdecl TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer);

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
	KCUBELIQUIDCRYSTAL_API short __cdecl TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID);

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
	KCUBELIQUIDCRYSTAL_API short __cdecl TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length);

	/// <summary> Get the device information from the USB port. </summary>
	/// <remarks> The Device Info is read from the USB port not from the device itself.<remarks>
	/// <param name="serialNo"> The serial number of the device. </param>
	/// <param name="info">    The <see cref="CDeviceInfo"/> device information. </param>
	/// <returns>   1 if successful, 0 if not. </returns>
	/// 		  \include CodeSnippet_identification.cpp
	/// <seealso cref="TLI_GetDeviceListSize()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	/// <seealso cref="TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID)" />
	/// <seealso cref="TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length)" />
	/// <seealso cref="TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer)" />
	/// <seealso cref="TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID)" />
	/// <seealso cref="TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length)" />
	KCUBELIQUIDCRYSTAL_API short __cdecl TLI_GetDeviceInfo(char const * serialNo, TLI_DeviceInfo *info);

	/// <summary> Initialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <remarks> Call TLI_InitializeSimulations before TLI_BuildDeviceList at the start of the program to make a connection to the simulation manager.<Br />
	/// 		  Any devices configured in the simulation manager will become visible TLI_BuildDeviceList is called and can be accessed using TLI_GetDeviceList.<Br />
	/// 		  Call TLI_InitializeSimulations at the end of the program to release the simulator.  </remarks>
	/// <seealso cref="TLI_UninitializeSimulations()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	KCUBELIQUIDCRYSTAL_API void __cdecl TLI_InitializeSimulations();

	/// <summary> Uninitialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <seealso cref="TLI_InitializeSimulations()" />
	KCUBELIQUIDCRYSTAL_API void __cdecl TLI_UninitializeSimulations();

#pragma endregion

	/// <summary> Open the device for communications. </summary>
	/// <param name="serialNo">	The serial no of the device to be connected. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="KLC_Close(char const * serialNo)" />
	KCUBELIQUIDCRYSTAL_API short __cdecl KLC_Open(char const * serialNo);

	/// <summary> Disconnect and close the device. </summary>
	/// <param name="serialNo">	The serial no of the device to be disconnected. </param>
	/// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="KLC_Open(char const * serialNo)" />
	KCUBELIQUIDCRYSTAL_API void __cdecl KLC_Close(char const * serialNo);

	/// <summary>	Check connection. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> true if the USB is listed by the FTDI controller</returns>
	/// \include CodeSnippet_CheckConnection.cpp
	KCUBELIQUIDCRYSTAL_API bool __cdecl KLC_CheckConnection(char const * serialNo);

	/// <summary> Sends a command to the device to make it identify iteself. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	KCUBELIQUIDCRYSTAL_API void __cdecl KLC_Identify(char const * serialNo);

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
	KCUBELIQUIDCRYSTAL_API short __cdecl KLC_GetHardwareInfo(char const * serialNo, char * modelNo, DWORD sizeOfModelNo, WORD * type, WORD * numChannels,
		char * notes, DWORD sizeOfNotes, DWORD * firmwareVersion, WORD * hardwareVersion, WORD * modificationState);

	/// <summary> Gets the hardware information in a block. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="hardwareInfo"> Address of a TLI_HardwareInformation structure to receive the hardware information. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// 		  \include CodeSnippet_identify.cpp
	KCUBELIQUIDCRYSTAL_API short __cdecl KLC_GetHardwareInfoBlock(char const *serialNo, TLI_HardwareInformation *hardwareInfo);

	///// <summary> Requests the hub bay number this device is fitted to. </summary>
	///// <param name="serialNo"> The serial no. </param>
	///// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	///// <seealso cref="SC_GetHubBay(char const * serialNo)" />
	//KCUBELIQUIDCRYSTAL_API short __cdecl KLC_RequestHubBay(char const * serialNo);

	///// <summary> Gets the hub bay number this device is fitted to. </summary>
	///// <param name="serialNo">	The device serial no. </param>
	///// <returns> The number, 0x00 if unknown or 0xff if not on a hub. </returns>
	///// <seealso cref="SC_RequestHubBay(char const * serialNo)" />
	//KCUBELIQUIDCRYSTAL_API char __cdecl KLC_GetHubBay(char const * serialNo);

	/// <summary> Gets version number of the device software. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device software version number made up of 4 byte parts. </returns>
	/// 		  \include CodeSnippet_identify.cpp
	KCUBELIQUIDCRYSTAL_API DWORD __cdecl KLC_GetSoftwareVersion(char const * serialNo);

	/// <summary> Clears the device message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	KCUBELIQUIDCRYSTAL_API void __cdecl KLC_ClearMessageQueue(char const * serialNo);

	/// <summary> Registers a callback on the message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="functionPointer"> A function pointer to be called whenever messages are received. </param>
	/// <seealso cref="KLC_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="KLC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="KLC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KCUBELIQUIDCRYSTAL_API void __cdecl KLC_RegisterMessageCallback(char const * serialNo, void(*functionPointer)());

	/// <summary> Gets the MessageQueue size. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> number of messages in the queue. </returns>
	/// <seealso cref="KLC_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="KLC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="KLC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KCUBELIQUIDCRYSTAL_API int __cdecl KLC_MessageQueueSize(char const * serialNo);

	/// <summary> Get the next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> True if successful, false if not. </returns>
	/// <seealso cref="KLC_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="KLC_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="KLC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KCUBELIQUIDCRYSTAL_API bool __cdecl KLC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Wait for next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> True if successful, false if not. </returns>
	/// <seealso cref="KLC_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="KLC_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="KLC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KCUBELIQUIDCRYSTAL_API bool __cdecl KLC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Starts the internal polling loop which continuously requests position and status. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="milliseconds">The milliseconds polling rate. </param>
	/// <returns> True if successful, false if not. </returns>
	/// <seealso cref="SC_StopPolling(char const * serialNo)" />
	/// <seealso cref="SC_PollingDuration(char const * serialNo)" />
	/// <seealso cref="SC_RequestStatusBits(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	KCUBELIQUIDCRYSTAL_API bool __cdecl KLC_StartPolling(char const * serialNo, int milliseconds);

	/// <summary> Gets the polling loop duration. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The time between polls in milliseconds or 0 if polling is not active. </returns>
	/// <seealso cref="KLC_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="KLC_StopPolling(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	KCUBELIQUIDCRYSTAL_API long __cdecl KLC_PollingDuration(char const * serialNo);

	/// <summary> Stops the internal polling loop. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <seealso cref="KLC_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="KLC_PollingDuration(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	KCUBELIQUIDCRYSTAL_API void __cdecl KLC_StopPolling(char const * serialNo);

	/// <summary> Gets the time in milliseconds since tha last message was received from the device. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="lastUpdateTimeMS"> The time since the last message was received in milliseconds. </param>
	/// <returns> True if monitoring is enabled otherwize False. </returns>
	/// <seealso cref="KLC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// <seealso cref="KLC_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	KCUBELIQUIDCRYSTAL_API bool __cdecl KLC_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS);

	/// <summary> Enables the last message monitoring timer. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="enable"> True to enable monitoring otherwise False to disable. </param>
	/// <param name="lastMsgTimeout"> The last message error timeout in ms. 0 to disable. </param>
	/// <seealso cref="KLC_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="KLC_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	KCUBELIQUIDCRYSTAL_API void __cdecl KLC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout);

	/// <summary> Queries if the time since the last message has exceeded the lastMsgTimeout set by <see cref="SC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )"/>. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> True if last message timer has elapsed, False if monitoring is not enabled or if time of last message received is less than lastMsgTimeout. </returns>
	/// <seealso cref="KLC_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="KLC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	KCUBELIQUIDCRYSTAL_API bool __cdecl KLC_HasLastMsgTimerOverrun(char const * serialNo);

#pragma region Settings

	/// <summary> Requests that all settings are download from device. </summary>
	/// <remarks> This function requests that the device upload all it's settings to the DLL.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	KCUBELIQUIDCRYSTAL_API short __cdecl KLC_RequestSettings(char const * serialNo);

	/// <summary> Update device with stored settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> True if successful, false if not. </returns>
	/// 		  \include CodeSnippet_connection1.cpp
	KCUBELIQUIDCRYSTAL_API bool __cdecl KLC_LoadSettings(char const * serialNo);

	/// <summary> Update device with named settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="settingsName"> Name of settings stored away from device. </param>
	/// <returns> True if successful, false if not. </returns>
	///             \include CodeSnippet_connection1.cpp
	KCUBELIQUIDCRYSTAL_API bool __cdecl KLC_LoadNamedSettings(char const * serialNo, char const *settingsName);

	/// <summary> Persist the devices current settings. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> True if successful, false if not. </returns>
	KCUBELIQUIDCRYSTAL_API bool __cdecl KLC_PersistSettings(char const * serialNo);

#pragma endregion

#pragma region Params

	/// <summary> Requests the parameters for the KCube. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KLC_GetParams(char const * serialNo, __int16 *displayIntensity)" />
	/// <seealso cref="KLC_GetParamsExt(char const * serialNo, __int16 *displayIntensity, __int16 *displayTimeout, __int16 *displayDimIntensity)" />
	/// <seealso cref="KLC_GetParamsBlock(const char * serialNo, KLC_Params *params)" />
	KCUBELIQUIDCRYSTAL_API short __cdecl KLC_RequestParams(char const * serialNo);

	/// <summary> Get the parameters for the KCube. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="displayIntensity">	    The display intensity, range 0 to 100%. </param>
	/// <param name="displayTimeout">	    The display timeout, range 0 to 480 in minutes (0 is off, otherwise the inactivity period before dimming the display). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KLC_SetParamsExt(char const * serialNo, __int16 displayIntensity)" />
	/// <seealso cref="KLC_SetParamsBlock(const char * serialNo, KLC_Params *params)" />
	/// <seealso cref="KLC_RequestParams(char const * serialNo)" />
	/// <seealso cref="KLC_GetParamsBlock(const char * serialNo, KLC_Params *params)" />
	KCUBELIQUIDCRYSTAL_API  short __cdecl KLC_GetParamsExt(char const * serialNo, __int16 *displayIntensity, __int16 *displayTimeout);

	/// \deprecated
	/// <summary> Get the parameters for the KCube. </summary>
	/// <remarks> superceded by <see cref="SC_GetParamsExt(char const * serialNo, __int16 *displayIntensity, __int16 *displayTimeout)"/> </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="displayIntensity">	    The display intensity, range 0 to 100%. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KLC_SetParams(char const * serialNo, __int16 displayIntensity)" />
	/// <seealso cref="KLC_SetParamsBlock(const char * serialNo, KLC_Params *params)" />
	/// <seealso cref="KLC_RequestParams(char const * serialNo)" />
	/// <seealso cref="KLC_GetParamsBlock(const char * serialNo, KLC_Params *params)" />
	KCUBELIQUIDCRYSTAL_API  short __cdecl KLC_GetParams(char const * serialNo, __int16 *displayIntensity);

	/// <summary> Set the parameters for the KCube. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="displayIntensity">	    The display intensity, range 0 to 100%. </param>
	/// <param name="displayTimeout">	    The display timeout, range 0 to 480 in minutes (0 is off, otherwise the inactivity period before dimming the display). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KLC_GetParamsExt(char const * serialNo, __int16 *displayIntensity)" />
	/// <seealso cref="KLC_SetParamsBlock(const char * serialNo, KLC_Params *params)" />
	/// <seealso cref="KLC_GetParamsBlock(const char * serialNo, KLC_Params *params)" />
	KCUBELIQUIDCRYSTAL_API short __cdecl KLC_SetParamsExt(char const * serialNo, __int16 displayIntensity, __int16 displayTimeout);

	/// \deprecated
	/// <summary> Set the parameters for the KCube. </summary>
	/// <remarks> superceded by <see cref="SC_SetParamsExt(char const * serialNo, __int16 displayIntensity, __int16 displayTimeout)"/> </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="displayIntensity">	    The display intensity, range 0 to 100%. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KLC_GetParams(char const * serialNo, __int16 *displayIntensity)" />
	/// <seealso cref="KLC_SetParamsBlock(const char * serialNo, KLC_Params *params)" />
	/// <seealso cref="KLC_GetParamsBlock(const char * serialNo, KLC_Params *params)" />
	KCUBELIQUIDCRYSTAL_API short __cdecl KLC_SetParams(char const * serialNo, __int16 displayIntensity);

	/// <summary> Gets the parameters for the KCube. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="params"> Options for controlling the device. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KLC_RequestParams(char const * serialNo)" />
	/// <seealso cref="KLC_GetParamsExt(char const * serialNo, __int16 *displayIntensity, __int16 *displayTimeout)" />
	/// <seealso cref="KLC_SetParamsExt(char const * serialNo, __int16 displayIntensity, __int16 displayTimeout)" />
	/// <seealso cref="KLC_SetParamsBlock(const char * serialNo, KLC_Params *params)" />
	KCUBELIQUIDCRYSTAL_API short __cdecl KLC_GetParamsBlock(char const * serialNo, KLC_KCubeMMIParams *params);

	/// <summary> Sets the parameters for the KCube. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="params"> Options for controlling the device. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="KLC_GetParamsExt(char const * serialNo, __int16 *displayIntensity, __int16 *displayTimeout)" />
	/// <seealso cref="KLC_SetParamsExt(char const * serialNo, __int16 displayIntensity, __int16 displayTimeout)" />
	/// <seealso cref="KLC_GetParamsBlock(const char * serialNo, KLC_Params *params)" />
	KCUBELIQUIDCRYSTAL_API short __cdecl KLC_SetParamsBlock(char const * serialNo, KLC_KCubeMMIParams *params);

#pragma endregion

}
/** @} */ // KCubeLiquidCrystal
