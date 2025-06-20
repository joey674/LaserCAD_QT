// summary:	Declares the functions class
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the TCUBEInertialMotor_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// TCUBEINERTIALMOTOR_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef TCUBEINERTIALMOTORDLL_EXPORTS
#define TCUBEINERTIALMOTOR_API __declspec(dllexport)
#else
#define TCUBEINERTIALMOTOR_API __declspec(dllimport)
#endif

#include <OaIdl.h>

#pragma once

/** @defgroup TCubeInertialMotor TCube InertialMotor
 *  This section details the Structures and Functions relavent to the  @ref TIM101_page "InertialMotor"<br />
 *  For an example of how to connect to the device and perform simple operations use the following links:
 *  <list type=bullet>
 *    <item> \ref namespaces_tim_ex_1 "Example of using the Thorlabs.MotionControl.TCube.InertialMotor.DLL from a C or C++ project."<br />
 *									  This requires the DLL to be dynamical linked. </item>
 *    <item> \ref namespaces_tim_ex_2 "Example of using the Thorlabs.MotionControl.TCube.InertialMotor.DLL from a C# project"<br />
 *									  This uses Marshalling to load and access the C DLL. </item>
 *  </list>
 *  The Thorlabs.MotionControl.TCube.InertialMotor.DLL requires the following DLLs
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

#pragma pack(1)

	/// <summary> Values that represent TIM_Channels. </summary>
	typedef enum TIM_Channels : unsigned short
	{
		/// <summary> An enum constant representing the channel 1 option. </summary>
		Channel1 = 1,
		/// <summary> An enum constant representing the channel 2 option. </summary>
		Channel2,
		/// <summary> An enum constant representing the channel 3 option. </summary>
		Channel3,
		/// <summary> An enum constant representing the channel 4 option. </summary>
		Channel4
	} TIM_Channels;

	/// <summary> Values that represent TIM_JogMode. </summary>
	typedef enum TIM_JogMode : unsigned __int16
	{
		/// <summary> An enum constant representing the jog continuous option. </summary>
		JogContinuous = 0x01,
		/// <summary> An enum constant representing the jog step option. </summary>
		JogStep = 0x02,
	} TIM_JogMode;

	/// <summary> Values that represent TIM_ButtonsMode. </summary>
	typedef enum TIM_ButtonsMode : unsigned __int16
	{
		/// <summary> An enum constant representing the jog option. </summary>
		Jog = 0x01,
		/// <summary> An enum constant representing the position option. </summary>
		Position = 0x02,
	} TIM_ButtonsMode;

	/// <summary> Values that represent TIM_Direction. </summary>
	typedef enum TIM_Direction : byte
	{
		/// <summary> An enum constant representing the forward option. </summary>
		Forward = 0x01,
		/// <summary> An enum constant representing the reverse option. </summary>
		Reverse = 0x02,
	} TIM_Direction;

	/// <summary> TIM Drive Operation Parameters. </summary>
	typedef struct TIM_DriveOPParameters
	{
		/// <summary> The maximum voltage. </summary>
		__int16 _maxVoltage;
		/// <summary> The step rate. </summary>
		__int32 _stepRate;
		/// <summary> The step acceleration. </summary>
		__int32 _stepAcceleration;
	} TIM_DriveOPParameters;

	/// <summary> TIM jog parameters. </summary>
	typedef struct TIM_JogParameters
	{
		/// <summary> The jog mode. </summary>
		TIM_JogMode _jogMode;
		/// <summary> Size of the jog step. </summary>
		__int32 _jogStepSize;
		/// <summary> The jog step rate. </summary>
		__int32 _jogStepRate;
		/// <summary> The jog step acceleration. </summary>
		__int32 _jogStepAcceleration;
	} TIM_JogParameters;

	/// <summary> TIM button parameters. </summary>
	typedef struct TIM_ButtonParameters
	{
		/// <summary> The button mode. </summary>
		TIM_ButtonsMode _buttonMode;
		/// <summary> The first position. </summary>
		__int32 _position1;
		/// <summary> The second position. </summary>
		__int32 _position2;
		/// <summary> The reserved fields. </summary>
		__int16 _reserved[2];
	} TIM_ButtonParameters;

	/// <summary> TIM status. </summary>
	typedef struct TIM_Status
	{
		/// <summary> The position. </summary>
		__int32 _position;
		/// <summary> Number of encoders. </summary>
		__int32 _encoderCount;
		/// <summary> The status bits. </summary>
		unsigned __int32 _statusBits;
	} TIM_Status;

/// \endcond

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
	TCUBEINERTIALMOTOR_API short __cdecl TLI_BuildDeviceList(void);

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
	TCUBEINERTIALMOTOR_API short __cdecl TLI_GetDeviceListSize();

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
	TCUBEINERTIALMOTOR_API short __cdecl TLI_GetDeviceList(SAFEARRAY** stringsReceiver);

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
	TCUBEINERTIALMOTOR_API short __cdecl TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID);

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
	TCUBEINERTIALMOTOR_API short __cdecl TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length);

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
	TCUBEINERTIALMOTOR_API short __cdecl TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer);

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
	TCUBEINERTIALMOTOR_API short __cdecl TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID);

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
	TCUBEINERTIALMOTOR_API short __cdecl TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length);

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
	TCUBEINERTIALMOTOR_API short __cdecl TLI_GetDeviceInfo(char const * serialNo, TLI_DeviceInfo *info);

	/// <summary> Initialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <remarks> Call TLI_InitializeSimulations before TLI_BuildDeviceList at the start of the program to make a connection to the simulation manager.<Br />
	/// 		  Any devices configured in the simulation manager will become visible TLI_BuildDeviceList is called and can be accessed using TLI_GetDeviceList.<Br />
	/// 		  Call TLI_InitializeSimulations at the end of the program to release the simulator.  </remarks>
	/// <seealso cref="TLI_UninitializeSimulations()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	TCUBEINERTIALMOTOR_API void __cdecl TLI_InitializeSimulations();

	/// <summary> Uninitialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <seealso cref="TLI_InitializeSimulations()" />
	TCUBEINERTIALMOTOR_API void __cdecl TLI_UninitializeSimulations();

	/// <summary> Open the device for communications. </summary>
	/// <param name="serialNo">	The serial no of the device to be connected. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="TIM_Close(char const * serialNo)" />
	TCUBEINERTIALMOTOR_API short __cdecl TIM_Open(char const * serialNo);

	/// <summary> Disconnect and close the device. </summary>
	/// <param name="serialNo">	The serial no of the device to be disconnected. </param>
    /// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="TIM_Open(char const * serialNo)" />
	TCUBEINERTIALMOTOR_API void __cdecl TIM_Close(char const * serialNo);

	/// <summary>	Check connection. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> true if the USB is listed by the ftdi controller</returns>
	/// \include CodeSnippet_CheckConnection.cpp
	TCUBEINERTIALMOTOR_API bool __cdecl TIM_CheckConnection(char const * serialNo);

	/// <summary> Sends a command to the device to make it identify iteself. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	TCUBEINERTIALMOTOR_API void __cdecl TIM_Identify(char const * serialNo);

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
	TCUBEINERTIALMOTOR_API short __cdecl TIM_GetHardwareInfo(char const * serialNo, char * modelNo, DWORD sizeOfModelNo, WORD * type, WORD * numChannels, 
													char * notes, DWORD sizeOfNotes, DWORD * firmwareVersion, WORD * hardwareVersion, WORD * modificationState);

	/// <summary> Gets the hardware information in a block. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="hardwareInfo"> Address of a TLI_HardwareInformation structure to receive the hardware information. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	TCUBEINERTIALMOTOR_API short __cdecl TIM_GetHardwareInfoBlock(char const *serialNo, TLI_HardwareInformation *hardwareInfo);

	/// <summary> Gets version number of the device firmware. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device firmware version number made up of 4 byte parts. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	TCUBEINERTIALMOTOR_API DWORD __cdecl TIM_GetFirmwareVersion(char const * serialNo);

	/// <summary> Gets version number of the device software. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device software version number made up of 4 byte parts. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	TCUBEINERTIALMOTOR_API DWORD __cdecl TIM_GetSoftwareVersion(char const * serialNo);

	/// <summary> Update device with stored settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
    /// 		  \include CodeSnippet_connection1.cpp
	TCUBEINERTIALMOTOR_API bool __cdecl TIM_LoadSettings(char const * serialNo);

	/// <summary> Update device with named settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="settingsName"> Name of settings stored away from device. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	///             \include CodeSnippet_connection1.cpp
	TCUBEINERTIALMOTOR_API bool __cdecl TIM_LoadNamedSettings(char const * serialNo, char const *settingsName);

	/// <summary> persist the devices current settings. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	TCUBEINERTIALMOTOR_API bool __cdecl TIM_PersistSettings(char const * serialNo);

	/// <summary> Disable cube. </summary>

	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="TIM_Enable(char const * serialNo)" />
	TCUBEINERTIALMOTOR_API short __cdecl TIM_Disable(char const * serialNo);

	/// <summary> Enable cube for computer control. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="TIM_Disable(char const * serialNo)" />
	TCUBEINERTIALMOTOR_API short __cdecl TIM_Enable(char const * serialNo);

	/// <summary> Reset the device. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	TCUBEINERTIALMOTOR_API short __cdecl TIM_Reset(char const * serialNo);

	/// <summary> Tells the device that it is being disconnected. </summary>
	/// <remarks> This does not disconnect the communications.<br />
	/// 		  To disconnect the communications, call the <see cref="TIM_Close(char const * serialNo)" /> function. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	TCUBEINERTIALMOTOR_API short __cdecl TIM_Disconnect(char const * serialNo);

	/// <summary> Clears the device message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	TCUBEINERTIALMOTOR_API void __cdecl TIM_ClearMessageQueue(char const * serialNo);

	/// <summary> Registers a callback on the message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="functionPointer"> A function pointer to be called whenever messages are received. </param>
	/// <seealso cref="TIM_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="TIM_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="TIM_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	TCUBEINERTIALMOTOR_API void __cdecl TIM_RegisterMessageCallback(char const * serialNo, void (* functionPointer)());

	/// <summary> Gets the MessageQueue size. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> number of messages in the queue. </returns>
	/// <seealso cref="TIM_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="TIM_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="TIM_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	TCUBEINERTIALMOTOR_API int __cdecl TIM_MessageQueueSize(char const * serialNo);

	/// <summary> Get the next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="TIM_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="TIM_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="TIM_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	TCUBEINERTIALMOTOR_API bool __cdecl TIM_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Wait for next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="TIM_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="TIM_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="TIM_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	TCUBEINERTIALMOTOR_API bool __cdecl TIM_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Sets the current position to the Home position (Position = 0). </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <param name="channel">  The channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	TCUBEINERTIALMOTOR_API short __cdecl TIM_Home(char const * serialNo, TIM_Channels channel);

	/// <summary> set the position. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <param name="channel">  The channel. </param>
	/// <param name="position"> The position. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	TCUBEINERTIALMOTOR_API short __cdecl TIM_SetPosition(char const * serialNo, TIM_Channels channel, long position);

	/// <summary> Move absolute. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">  The channel. </param>
	/// <param name="position"> The position. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	TCUBEINERTIALMOTOR_API short __cdecl TIM_MoveAbsolute(char const * serialNo, TIM_Channels channel, __int32 position);

	/// <summary> Move jog. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">	    The channel. </param>
	/// <param name="jogDirection"> The jog direction. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	TCUBEINERTIALMOTOR_API short __cdecl TIM_MoveJog(char const * serialNo, TIM_Channels channel, TIM_Direction jogDirection);

	/// <summary> Move stop. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel"> The channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	TCUBEINERTIALMOTOR_API short __cdecl TIM_MoveStop(char const * serialNo, TIM_Channels channel);

	/// <summary> Requests the operation drive parameters. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <param name="channel">	The channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	TCUBEINERTIALMOTOR_API short __cdecl TIM_RequestDriveOPParameters(char const * serialNo, TIM_Channels channel);

	/// <summary> Sets the operation drive parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">		    The channel. </param>
	/// <param name="maxVoltage">	    The maximum voltage. </param>
	/// <param name="stepRate">		    The step rate. </param>
	/// <param name="stepAcceleration"> The step acceleration. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	TCUBEINERTIALMOTOR_API short __cdecl TIM_SetDriveOPParameters(char const * serialNo, TIM_Channels channel, __int16 maxVoltage, __int32 stepRate, __int32 stepAcceleration);

	/// <summary> Gets the operation drive parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">		    The channel. </param>
	/// <param name="maxVoltage">	    The maximum voltage. </param>
	/// <param name="stepRate">		    The step rate. </param>
	/// <param name="stepAcceleration"> The step acceleration. </param>
	/// <returns> The operation drive parameters. </returns>
	TCUBEINERTIALMOTOR_API short __cdecl TIM_GetDriveOPParameters(char const * serialNo, TIM_Channels channel, __int16 &maxVoltage, __int32 &stepRate, __int32 &stepAcceleration);

	/// <summary> Sets the operation drive parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">			 The channel. </param>
	/// <param name="driveOPParameters"> Options for controlling the drive operation. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	TCUBEINERTIALMOTOR_API short __cdecl TIM_SetDriveOPParametersStruct(char const * serialNo, TIM_Channels channel, TIM_DriveOPParameters &driveOPParameters);

	/// <summary> Gets the operation drive parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">			 The channel. </param>
	/// <param name="driveOPParameters"> Options for controlling the drive operation. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	TCUBEINERTIALMOTOR_API short __cdecl TIM_GetDriveOPParametersStruct(char const * serialNo, TIM_Channels channel, TIM_DriveOPParameters &driveOPParameters);

	/// <summary> Requests the jog parameters. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <param name="channel">	The channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	TCUBEINERTIALMOTOR_API short __cdecl TIM_RequestJogParameters(char const * serialNo, TIM_Channels channel);

	/// <summary> Sets the jog parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">			   The channel. </param>
	/// <param name="jogMode">			   The jog mode. </param>
	/// <param name="jogStepSize">		   Size of the jog step. </param>
	/// <param name="jogStepRate">		   The jog step rate. </param>
	/// <param name="jogStepAcceleration"> The jog step acceleration. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	TCUBEINERTIALMOTOR_API short __cdecl TIM_SetJogParameters(char const * serialNo, TIM_Channels channel, TIM_JogMode jogMode, __int32 jogStepSize, __int32 jogStepRate, __int32 jogStepAcceleration);

	/// <summary> Gets the jog parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">			   The channel. </param>
	/// <param name="jogMode">			   The jog mode. </param>
	/// <param name="jogStepSize">		   Size of the jog step. </param>
	/// <param name="jogStepRate">		   The jog step rate. </param>
	/// <param name="jogStepAcceleration"> The jog step acceleration. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	TCUBEINERTIALMOTOR_API short __cdecl TIM_GetJogParameters(char const * serialNo, TIM_Channels channel, TIM_JogMode &jogMode, __int32 &jogStepSize, __int32 &jogStepRate, __int32 &jogStepAcceleration);

	/// <summary> Sets the jog parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">			 The channel. </param>
	/// <param name="jogParameters"> Options for controlling the drive operation. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	TCUBEINERTIALMOTOR_API short __cdecl TIM_SetJogParametersStruct(char const * serialNo, TIM_Channels channel, TIM_JogParameters &jogParameters);

	/// <summary> Gets the jog parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">			 The channel. </param>
	/// <param name="jogParameters"> Options for controlling the drive operation. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	TCUBEINERTIALMOTOR_API short __cdecl TIM_GetJogParametersStruct(char const * serialNo, TIM_Channels channel, TIM_JogParameters &jogParameters);

	/// <summary> Requests the button parameters. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <param name="channel">	The channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	TCUBEINERTIALMOTOR_API short __cdecl TIM_RequestButtonParameters(char const * serialNo, TIM_Channels channel);

	/// <summary> Sets a button parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">    The channel. </param>
	/// <param name="buttonMode"> The button mode. </param>
	/// <param name="position1">  The first position. </param>
	/// <param name="position2">  The second position. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	TCUBEINERTIALMOTOR_API short __cdecl TIM_SetButtonParameters(char const * serialNo, TIM_Channels channel, TIM_ButtonsMode buttonMode, __int32 position1, __int32 position2);

	/// <summary> Gets a button parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">    The channel. </param>
	/// <param name="buttonMode"> The button mode. </param>
	/// <param name="position1">  The first position. </param>
	/// <param name="position2">  The second position. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	TCUBEINERTIALMOTOR_API short __cdecl TIM_GetButtonParameters(char const * serialNo, TIM_Channels channel, TIM_ButtonsMode &buttonMode, __int32 &position1, __int32 &position2);

	/// <summary> Sets a button parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">		    The channel. </param>
	/// <param name="buttonParameters"> Options for controlling the button. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	TCUBEINERTIALMOTOR_API short __cdecl TIM_SetButtonParametersStruct(char const * serialNo, TIM_Channels channel, TIM_ButtonParameters &buttonParameters);

	/// <summary> Gets a button parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">		    The channel. </param>
	/// <param name="buttonParameters"> Options for controlling the button. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	TCUBEINERTIALMOTOR_API short __cdecl TIM_GetButtonParametersStruct(char const * serialNo, TIM_Channels channel, TIM_ButtonParameters &buttonParameters);

	/// <summary> Sets a maximum pot step rate. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">		  The channel. </param>
	/// <param name="maxPotStepRate"> The maximum pot step rate. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="TIM_RequestMaxPotStepRate(char const * serialNo, TIM_Channels channel)" />
	/// <seealso cref="TIM_GetMaxPotStepRate(char const * serialNo, TIM_Channels channel)" />
	TCUBEINERTIALMOTOR_API short __cdecl TIM_SetMaxPotStepRate(char const * serialNo, TIM_Channels channel, __int32 maxPotStepRate);

	/// <summary> Requests the maximum potentiometer step rate. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <param name="channel">	The channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="TIM_GetMaxPotStepRate(char const * serialNo, TIM_Channels channel)" />
	/// <seealso cref="TIM_SetMaxPotStepRate(char const * serialNo, TIM_Channels channel, __int32 maxPotStepRate)" />
	TCUBEINERTIALMOTOR_API short __cdecl TIM_RequestMaxPotStepRate(char const * serialNo, TIM_Channels channel);

	/// <summary> Gets the maximum potentiometer step rate. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel"> The channel. </param>
	/// <returns> The maximum pot step rate or 0 if an error occured. </returns>
	/// <seealso cref="TIM_RequestMaxPotStepRate(char const * serialNo, TIM_Channels channel)" />
	/// <seealso cref="TIM_SetMaxPotStepRate(char const * serialNo, TIM_Channels channel, __int32 maxPotStepRate)" />
	TCUBEINERTIALMOTOR_API __int32 __cdecl TIM_GetMaxPotStepRate(char const * serialNo, TIM_Channels channel);

	/// <summary> Gets the LED brightness. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> Intensity from 0 (off) to 255. </returns>
	/// <seealso cref="TIM_SetLEDBrightness(char const * serialNo, short brightness)" />
	TCUBEINERTIALMOTOR_API short __cdecl TIM_GetLEDBrightness(char const * serialNo);

	/// <summary> Sets the LED brightness. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="brightness"> Intensity from 0 (off) to 255. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="TIM_GetLEDBrightness(char const * serialNo)" />
	TCUBEINERTIALMOTOR_API short __cdecl TIM_SetLEDBrightness(char const * serialNo, short brightness);

	/// <summary> Requests the state quantities (actual temperature, current and status bits). </summary>
	/// <remarks> This needs to be called to get the device to send it's current status.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="TIM_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="TIM_RequestReadings(char const * serialNo)" />
	/// <seealso cref="TIM_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="TIM_GetCurrentReading(char const * serialNo)" />
	/// <seealso cref="TIM_GetTemperatureReading(char const * serialNo)" />
	/// <seealso cref="TIM_GetStatusBits(char const * serialNo)" />
	/// <seealso cref="TIM_StartPolling(char const * serialNo, int milliseconds)" />
	TCUBEINERTIALMOTOR_API short __cdecl TIM_RequestStatus(char const * serialNo);

	/// <summary> Request the status bits which identify the current device state. </summary>
	/// <remarks> This needs to be called to get the device to send it's current status bits.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="TIM_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="TIM_GetStatusBits(char const * serialNo)" />
	/// <seealso cref="TIM_RequestStatus(char const * serialNo)" />
	/// <seealso cref="TIM_RequestReadings(char const * serialNo)" />
	/// <seealso cref="TIM_StartPolling(char const * serialNo, int milliseconds)" />
	TCUBEINERTIALMOTOR_API short __cdecl TIM_RequestStatusBits(char const * serialNo);

	/// <summary> Requests the current position. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <param name="channel">	The channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="TIM_GetCurrentPosition(char const * serialNo, TIM_Channels channel)" />
	TCUBEINERTIALMOTOR_API short __cdecl TIM_RequestCurrentPosition(char const * serialNo, TIM_Channels channel);

	/// <summary> Gets current position. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">  The channel. </param>
	/// <returns> The position. </returns>
	/// <seealso cref="TIM_RequestCurrentPosition(char const * serialNo, TIM_Channels channel)" />
	TCUBEINERTIALMOTOR_API __int32 __cdecl TIM_GetCurrentPosition(char const * serialNo, TIM_Channels channel);

	/// <summary> Tc get status bits. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <param name="channel">  The channel. </param>
	/// <returns> . </returns>
	TCUBEINERTIALMOTOR_API DWORD __cdecl TIM_GetStatusBits(char const * serialNo, TIM_Channels channel);

	/// <summary> Starts the internal polling loop which continuously requests position and status. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="milliseconds">The milliseconds polling rate. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="TIM_StopPolling(char const * serialNo)" />
	/// <seealso cref="TIM_PollingDuration(char const * serialNo)" />
	/// <seealso cref="TIM_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="TIM_RequestPosition(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	TCUBEINERTIALMOTOR_API bool __cdecl TIM_StartPolling(char const * serialNo, int milliseconds);

	/// <summary> Gets the polling loop duration. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The time between polls in milliseconds or 0 if polling is not active. </returns>
	/// <seealso cref="TIM_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="TIM_StopPolling(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	TCUBEINERTIALMOTOR_API long __cdecl TIM_PollingDuration(char const * serialNo);

	/// <summary> Stops the internal polling loop. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <seealso cref="TIM_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="TIM_PollingDuration(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	TCUBEINERTIALMOTOR_API void __cdecl TIM_StopPolling(char const * serialNo);

	/// <summary> Gets the time in milliseconds since tha last message was received from the device. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="lastUpdateTimeMS"> The time since the last message was received in milliseconds. </param>
	/// <returns> True if monitoring is enabled otherwize False. </returns>
	/// <seealso cref="TIM_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// <seealso cref="TIM_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	TCUBEINERTIALMOTOR_API bool __cdecl TIM_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS );

	/// <summary> Enables the last message monitoring timer. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="enable"> True to enable monitoring otherwise False to disable. </param>
	/// <param name="lastMsgTimeout"> The last message error timeout in ms. 0 to disable. </param>
	/// <seealso cref="TIM_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="TIM_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	TCUBEINERTIALMOTOR_API void __cdecl TIM_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout );

	/// <summary> Queries if the time since the last message has exceeded the lastMsgTimeout set by <see cref="TIM_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )"/>. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> True if last message timer has elapsed, False if monitoring is not enabled or if time of last message received is less than lastMsgTimeout. </returns>
	/// <seealso cref="TIM_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="TIM_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	TCUBEINERTIALMOTOR_API bool __cdecl TIM_HasLastMsgTimerOverrun(char const * serialNo);

	/// <summary> Requests that all settings are download from device. </summary>
	/// <remarks> This function requests that the device upload all it's settings to the DLL.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	TCUBEINERTIALMOTOR_API short __cdecl TIM_RequestSettings(char const * serialNo);
}
/** @} */ // TCubeInertialMotor
