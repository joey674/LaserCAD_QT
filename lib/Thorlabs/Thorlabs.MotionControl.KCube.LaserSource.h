// summary:	Declares the functions class
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the KLASERSOURCE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// KLASERSOURCE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#pragma once

#ifdef KLASERSOURCEDLL_EXPORTS
#define KLASERSOURCE_API __declspec(dllexport)
#else
#define KLASERSOURCE_API __declspec(dllimport)
#endif

#include <OaIdl.h>

/** @defgroup KCubeLaserSource KCube LaserSource
 *  This section details the Structures and Functions relavent to the  @ref KLSnnn_page "KCube Laser Source"<br />
 *  For an example of how to connect to the device and perform simple operations use the following links:
 *  <list type=bullet>
 *    <item> \ref namespaces_kls_ex_1 "Example of using the Thorlabs.MotionControl.KCube.LaserSource.DLL from a C or C++ project."<br />
 *									  This requires the DLL to be dynamical linked. </item>
 *    <item> \ref namespaces_kls_ex_2 "Example of using the Thorlabs.MotionControl.KCube.LaserSource.DLL from a C# project"<br />
 *									  This uses Marshalling to load and access the C DLL. </item>
 *  </list>
 *  The Thorlabs.MotionControl.KCube.LaserSource.DLL requires the following DLLs
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
	#pragma pack()

	/// <summary> Values that represent Laser Input Source Flags. </summary>
	typedef enum LS_InputSourceFlags : unsigned short
	{
		LS_SoftwareOnly = 0,///< Input is read from software only
		LS_ExternalSignal = 0x01,///<Input is read from software or External signal
		LS_WheelAndSoftware = 0x04,///<Input is read from software or Potentiometer
	} LS_InputSourceFlags;

	/// <summary>	The KLS display parameters. </summary>
	typedef struct KLS_MMIParams
	{
		/// <summary>	The display intensity, range 0 to 100%. </summary>
		__int16 displayIntensity;
		/// <summary>	Reserved. </summary>
		__int16 reserved[3];
	} KLS_MMIParams;

	/// <summary> Values that represent Laser Operating Modes. </summary>
	typedef enum KLS_OpMode : unsigned short
	{
		KLS_ConstantPower = 0,///<Constant Power operation
		KLS_ConstantCurrent = 1,///<Constant Current operation
	} KLS_OpMode;

	/// <summary> Values that represent Quadrant Detector Modes. </summary>
	typedef enum KLS_TriggerMode : unsigned short
	{
		KLS_Disabled = 0,///<Trigger disabled
		KLS_Input = 1,///<General IO input
		KLS_Output = 0x0a,///<General IO Output
		KLS_LaserOn = 0x0b,///<Laser Output ON trigger
		KLS_InterlockEnabled = 0x0c,///<Interlock enabled trigger
		KLS_SetPointChange = 0x0d,///<Set point changed trigger
		KLS_HighStability = 0x0e,///<Gigh Stability trigger
		KLS_LowStability = 0x0f,///<low stability trigger
	} KLS_TriggerMode;

	/// <summary>	Values that represent Trigger Polarities. </summary>
	typedef enum KLS_TrigPolarity : unsigned short
	{
		KLS_TrigPol_High = 0x01,///<Trigger active high
		KLS_TrigPol_Low = 0x02,///<Trigger active low
	} KLS_TrigPolarity;

	/// <summary>	The kls operation mode parameters. </summary>
	typedef struct KLS_TrigIOParams
	{
		/// <summary>	The trigger 1 mode. <list type=table>
		///				<item><term>Disabled</term><term></term>0</item>
		///				<item><term>General Input</term><term></term>1</item>
		///				<item><term>General Output</term><term></term>10</item>
		///				<item><term>Laser Output On</term><term></term>11</item>
		///				<item><term>Interlock enabled</term><term></term>12</item>
		///				<item><term>Set Power changed</term><term></term>13</item>
		///				<item><term>High Stability Out</term><term></term>14</item>
		///				<item><term>Low Stability Out</term><term></term>15</item>
		/// 		  </list></summary>
		KLS_TriggerMode mode1;
		/// <summary>	The trigger 1 polarity. <list type=table>
		///				<item><term>Active High</term><term></term>1</item>
		///				<item><term>Active Low</term><term></term>2</item>
		/// 		  </list></summary>
		KLS_TrigPolarity polarity1;
		/// <summary>	Reserved field for trigger 1. </summary>
		__int16 reserved1;
		/// <summary>	The trigger 2 mode. <list type=table>
		///				<item><term>Disabled</term><term></term>0</item>
		///				<item><term>General Input</term><term></term>1</item>
		///				<item><term>General Output</term><term></term>10</item>
		///				<item><term>Laser Output On</term><term></term>11</item>
		///				<item><term>Interlock enabled</term><term></term>12</item>
		///				<item><term>Set Power changed</term><term></term>13</item>
		///				<item><term>High Stability Out</term><term></term>14</item>
		///				<item><term>Low Stability Out</term><term></term>15</item>
		/// 		  </list></summary>
		KLS_TriggerMode mode2;
		/// <summary>	The trigger 2 polarity. <list type=table>
		///				<item><term>Active High</term><term></term>1</item>
		///				<item><term>Active Low</term><term></term>2</item>
		/// 		  </list></summary>
		KLS_TrigPolarity polarity2;
		/// <summary>	Reserved field for trigger 2. </summary>
		__int16 reserved2;
	} KLS_TrigIOParams;

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
	KLASERSOURCE_API short __cdecl TLI_BuildDeviceList(void);

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
	KLASERSOURCE_API short __cdecl TLI_GetDeviceListSize();

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
	KLASERSOURCE_API short __cdecl TLI_GetDeviceList(SAFEARRAY** stringsReceiver);

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
	KLASERSOURCE_API short __cdecl TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID);

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
	KLASERSOURCE_API short __cdecl TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length);

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
	KLASERSOURCE_API short __cdecl TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer);

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
	KLASERSOURCE_API short __cdecl TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID);

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
	KLASERSOURCE_API short __cdecl TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length);

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
	KLASERSOURCE_API short __cdecl TLI_GetDeviceInfo(char const * serialNo, TLI_DeviceInfo *info);

	/// <summary> Initialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <remarks> Call TLI_InitializeSimulations before TLI_BuildDeviceList at the start of the program to make a connection to the simulation manager.<Br />
	/// 		  Any devices configured in the simulation manager will become visible TLI_BuildDeviceList is called and can be accessed using TLI_GetDeviceList.<Br />
	/// 		  Call TLI_InitializeSimulations at the end of the program to release the simulator.  </remarks>
	/// <seealso cref="TLI_UninitializeSimulations()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	KLASERSOURCE_API void __cdecl TLI_InitializeSimulations();

	/// <summary> Uninitialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <seealso cref="TLI_InitializeSimulations()" />
	KLASERSOURCE_API void __cdecl TLI_UninitializeSimulations();

	/// <summary> Open the device for communications. </summary>
	/// <param name="serialNo">	The serial no of the device to be connected. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="LS_Close(char const * serialNo)" />
	KLASERSOURCE_API short __cdecl LS_Open(char const * serialNo);

	/// <summary> Disconnect and close the device. </summary>
	/// <param name="serialNo">	The serial no of the device to be disconnected. </param>
    /// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="LS_Open(char const * serialNo)" />
	KLASERSOURCE_API void __cdecl LS_Close(char const * serialNo);

	/// <summary>	Check connection. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> true if the USB is listed by the ftdi controller</returns>
	/// \include CodeSnippet_CheckConnection.cpp
	KLASERSOURCE_API bool __cdecl LS_CheckConnection(char const * serialNo);

	/// <summary> Sends a command to the device to make it identify iteself. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	KLASERSOURCE_API void __cdecl LS_Identify(char const * serialNo);

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
	KLASERSOURCE_API short __cdecl LS_GetHardwareInfo(char const * serialNo, char * modelNo, DWORD sizeOfModelNo, WORD * type, WORD * numChannels, 
														char * notes, DWORD sizeOfNotes, DWORD * firmwareVersion, WORD * hardwareVersion, WORD * modificationState);

	/// <summary> Gets the hardware information in a block. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="hardwareInfo"> Address of a TLI_HardwareInformation structure to receive the hardware information. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	KLASERSOURCE_API short __cdecl LS_GetHardwareInfoBlock(char const *serialNo, TLI_HardwareInformation *hardwareInfo);

	/// <summary> Gets version number of the device firmware. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device firmware version number made up of 4 byte parts. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	KLASERSOURCE_API DWORD __cdecl LS_GetFirmwareVersion(char const * serialNo);

	/// <summary> Gets version number of the device software. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device software version number made up of 4 byte parts. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	KLASERSOURCE_API DWORD __cdecl LS_GetSoftwareVersion(char const * serialNo);

	/// <summary> Update device with stored settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
    /// 		  \include CodeSnippet_connection1.cpp
	KLASERSOURCE_API bool __cdecl LS_LoadSettings(char const * serialNo);

	/// <summary> Update device with named settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="settingsName"> Name of settings stored away from device. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	///             \include CodeSnippet_connection1.cpp
	KLASERSOURCE_API bool __cdecl LS_LoadNamedSettings(char const * serialNo, char const *settingsName);

	/// <summary> persist the devices current settings. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	KLASERSOURCE_API bool __cdecl LS_PersistSettings(char const * serialNo);

	/// <summary> Disable laser. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="LS_Enable(char const * serialNo)" />
	KLASERSOURCE_API short __cdecl LS_Disable(char const * serialNo);

	/// <summary> Enable laser for computer control. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="LS_Disable(char const * serialNo)" />
	KLASERSOURCE_API short __cdecl LS_Enable(char const * serialNo);

	/// <summary> Clears the device message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	KLASERSOURCE_API void __cdecl LS_ClearMessageQueue(char const * serialNo);

	/// <summary> Determine if the device front panel can be locked. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> True if we can lock the device front panel, false if not. </returns>
	/// <seealso cref="LS_GetFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="LS_RequestFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="LS_SetFrontPanelLock(char const * serialNo, bool locked)" />
	KLASERSOURCE_API bool __cdecl LS_CanDeviceLockFrontPanel(char const * serialNo);

	/// <summary> Query if the device front panel locked. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> True if the device front panel is locked, false if not. </returns>
	/// <seealso cref="LS_CanDeviceLockFrontPanel(char const * serialNo)" />
	/// <seealso cref="LS_RequestFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="LS_SetFrontPanelLock(char const * serialNo, bool locked)" />
	KLASERSOURCE_API bool __cdecl  LS_GetFrontPanelLocked(char const * serialNo);

	/// <summary> Ask the device if its front panel is locked. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="LS_CanDeviceLockFrontPanel(char const * serialNo)" />
	/// <seealso cref="LS_GetFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="LS_SetFrontPanelLock(char const * serialNo, bool locked)" />
	KLASERSOURCE_API short __cdecl  LS_RequestFrontPanelLocked(char const * serialNo);

	/// <summary> Sets the device front panel lock state. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="locked"> True to lock the device, false to unlock. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="LS_CanDeviceLockFrontPanel(char const * serialNo)" />
	/// <seealso cref="LS_GetFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="LS_RequestFrontPanelLocked(char const * serialNo)" />
	KLASERSOURCE_API short __cdecl  LS_SetFrontPanelLock(char const * serialNo, bool locked);

	/// <summary> Registers a callback on the message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="functionPointer"> A function pointer to be called whenever messages are received. </param>
	/// <seealso cref="LS_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="LS_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="LS_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KLASERSOURCE_API void __cdecl LS_RegisterMessageCallback(char const * serialNo, void (* functionPointer)());

	/// <summary> Gets the MessageQueue size. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> number of messages in the queue. </returns>
	/// <seealso cref="LS_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="LS_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="LS_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KLASERSOURCE_API int __cdecl LS_MessageQueueSize(char const * serialNo);

	/// <summary> Get the next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="LS_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="LS_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="LS_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KLASERSOURCE_API bool __cdecl LS_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Wait for next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="LS_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="LS_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="LS_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KLASERSOURCE_API bool __cdecl LS_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Switch laser off. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="LS_EnableOutput(char const * serialNo)" />
	KLASERSOURCE_API short __cdecl LS_DisableOutput(char const * serialNo);

	/// <summary> Switch laser on. </summary>
	/// <remarks> Laser will be enabled only if interlock is in place AND keyswitch is at ON position. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="LS_DisableOutput(char const * serialNo)" />
	KLASERSOURCE_API short __cdecl LS_EnableOutput(char const * serialNo);

	/// <summary> Gets the control input source. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="LS_SetControlSource(char const * serialNo, LS_InputSourceFlags source)" />
	/// <seealso cref="LS_GetControlSource(char const * serialNo)" />
	KLASERSOURCE_API short __cdecl LS_RequestControlSource(char const * serialNo);

	/// <summary> Gets the control input source. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The control input source.
	/// 		  <list type=table>
	///				<item><term>Software only</term><term></term>0</item>
	///				<item><term>External signal</term><term></term>1</item>
	///				<item><term>Potentiometer</term><term></term>4</item>
	/// 		  </list> </returns>
	/// <seealso cref="LS_SetControlSource(char const * serialNo, LS_InputSourceFlags source)" />
	/// <seealso cref="LS_RequestControlSource(char const * serialNo)" />
	KLASERSOURCE_API LS_InputSourceFlags __cdecl LS_GetControlSource(char const * serialNo);

	/// <summary> Sets the control input source. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="source"> The control input source.
	/// 		  <list type=table>
	///				<item><term>Software only</term><term></term>0</item>
	///				<item><term>External signal</term><term></term>1</item>
	///				<item><term>Potentiometer</term><term></term>4</item>
	/// 		  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="LS_GetControlSource(char const * serialNo)" />
	/// <seealso cref="LS_RequestControlSource(char const * serialNo)" />
	KLASERSOURCE_API short __cdecl LS_SetControlSource(char const * serialNo, LS_InputSourceFlags source);

	/// <summary> Requests the MMI parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="LS_GetMMIParams(char const * serialNo)" />
	/// <seealso cref="LS_SetMMIParams(char const * serialNo, short dispIntensity)" />
	/// <seealso cref="LS_GetMMIParamsBlock(char const * serialNo, KLS_MMIParams *params)" />
	/// <seealso cref="LS_SetMMIParamsBlock(char const * serialNo, KLS_MMIParams *params)" />
	KLASERSOURCE_API short __cdecl LS_RequestMMIParams(char const * serialNo);

	/// <summary>	Gets the MMI parameters. </summary>
	/// <param name="serialNo">			  	The device serial no. </param>
	/// <returns>	The Display Intensity. </returns>
	/// <seealso cref="LS_RequestMMIParams(char const * serialNo)" />
	/// <seealso cref="LS_SetMMIParams(char const * serialNo, short dispIntensity)" />
	/// <seealso cref="LS_GetMMIParamsBlock(char const * serialNo, KLS_MMIParams *params)" />
	/// <seealso cref="LS_SetMMIParamsBlock(char const * serialNo, KLS_MMIParams *params)" />
	KLASERSOURCE_API short __cdecl LS_GetMMIParams(char const * serialNo);

	/// <summary>	Sets the MMI parameters. </summary>
	/// <param name="serialNo">			  	The device serial no. </param>
	/// <param name="dispIntensity">	  	The display intensity, range 30 to 100%. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="LS_RequestMMIParams(char const * serialNo)" />
	/// <seealso cref="LS_GetMMIParams(char const * serialNo)" />
	/// <seealso cref="LS_GetMMIParamsBlock(char const * serialNo, KLS_MMIParams *params)" />
	/// <seealso cref="LS_SetMMIParamsBlock(char const * serialNo, KLS_MMIParams *params)" />
	KLASERSOURCE_API short __cdecl LS_SetMMIParams(char const * serialNo, short dispIntensity);

	/// <summary>	Gets the MMI parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="params">  	The MMI parameters structure. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="LS_RequestMMIParams(char const * serialNo)" />
	/// <seealso cref="LS_GetMMIParams(char const * serialNo)" />
	/// <seealso cref="LS_SetMMIParams(char const * serialNo, short dispIntensity)" />
	/// <seealso cref="LS_SetMMIParamsBlock(char const * serialNo, KLS_MMIParams *params)" />
	KLASERSOURCE_API short __cdecl LS_GetMMIParamsBlock(char const * serialNo, KLS_MMIParams *params);

	/// <summary>	Sets the MMI parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="params">  	The MMI parameters structure. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="LS_RequestMMIParams(char const * serialNo)" />
	/// <seealso cref="LS_GetMMIParams(char const * serialNo)" />
	/// <seealso cref="LS_SetMMIParams(char const * serialNo, short dispIntensity)" />
	/// <seealso cref="LS_GetMMIParamsBlock(char const * serialNo, KLS_MMIParams *params)" />
	KLASERSOURCE_API short __cdecl LS_SetMMIParamsBlock(char const * serialNo, KLS_MMIParams *params);

	/// <summary> Requests the Operation Mode parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="LS_GetOPMode(char const * serialNo, KLS_OpMode *mode)" />
	/// <seealso cref="LS_SetOPMode(char const * serialNo, KLS_OpMode mode)" />
	KLASERSOURCE_API short __cdecl LS_RequestOPMode(char const * serialNo);

	/// <summary>	Gets the Operation Mode parameters. </summary>
	/// <param name="serialNo"> 	The device serial no. </param>
	/// <param name="mode">			The operating mode. <list type=table>
	///				<item><term>Constant Power</term><term></term>0</item>
	///				<item><term>Constant Current</term><term></term>1</item>
	/// 		  </list></param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="LS_RequestOPMode(char const * serialNo)" />
	/// <seealso cref="LS_SetOPMode(char const * serialNo, KLS_OpMode mode)" />
	KLASERSOURCE_API short __cdecl LS_GetOPMode(char const * serialNo, KLS_OpMode *mode);

	/// <summary>	Sets the Operation Mode parameters. </summary>
	/// <param name="serialNo"> 	The device serial no. </param>
	/// <param name="mode">			The operating mode. <list type=table>
	///				<item><term>Constant Power</term><term></term>0</item>
	///				<item><term>Constant Current</term><term></term>1</item>
	/// 		  </list></param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="LS_RequestOPMode(char const * serialNo)" />
	/// <seealso cref="LS_GetOPMode(char const * serialNo, KLS_OpMode *mode)" />
	KLASERSOURCE_API short __cdecl LS_SetOPMode(char const * serialNo, KLS_OpMode mode);

	/// <summary> Requests the Trigger IO parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="LS_GetTrigIOParams(char const * serialNo, KLS_TriggerMode *mode1, KLS_TrigPolarity *polarity1, KLS_TriggerMode *mode2, KLS_TrigPolarity *polarity2)" />
	/// <seealso cref="LS_SetTrigIOParams(char const * serialNo, KLS_TriggerMode mode1, KLS_TrigPolarity polarity1, KLS_TriggerMode mode2, KLS_TrigPolarity polarity2)" />
	/// <seealso cref="LS_GetTrigIOParamsBlock(char const * serialNo, KLS_TrigIOParams *params)" />
	/// <seealso cref="LS_SetTrigIOParamsBlock(char const * serialNo, KLS_TrigIOParams *params)" />
	KLASERSOURCE_API short __cdecl LS_RequestTrigIOParams(char const * serialNo);

	/// <summary>	Gets the Trigger IO parameters. </summary>
	/// <param name="serialNo"> 	The device serial no. </param>
	/// <param name="mode1">		The Trigger1 mode. <list type=table>
	///				<item><term>Disabled</term><term>0</term></item>
	///				<item><term>General Input</term><term>1</term></item>
	///				<item><term>General Output</term><term>10</term></item>
	///				<item><term>Laser Output On</term><term>11</term></item>
	///				<item><term>Interlock enabled</term><term>12</term></item>
	///				<item><term>Set Power changed</term><term>13</term></item>
	///				<item><term>High Stability Out</term><term>14</term></item>
	///				<item><term>Low Stability Out</term><term>15</term></item>
	/// 		  </list></param>
	/// <param name="polarity1">	The Trigger1 polarity. <list type=table>
	///				<item><term>Active High</term><term>1</term></item>
	///				<item><term>Active Low</term><term>2</term></item>
	/// 		  </list></param>
	/// <param name="mode2">		The Trigger2 mode.<list type=table>
	///				<item><term>Disabled</term><term>0</term></item>
	///				<item><term>General Input</term><term>1</term></item>
	///				<item><term>General Output</term><term>10</term></item>
	///				<item><term>Laser Output On</term><term>11</term></item>
	///				<item><term>Interlock enabled</term><term>12</term></item>
	///				<item><term>Set Power changed</term><term>13</term></item>
	///				<item><term>High Stability Out</term><term>14</term></item>
	///				<item><term>Low Stability Out</term><term>15</term></item>
	/// 		  </list></param>
	/// <param name="polarity2">	The Trigger2 polarity.<list type=table>
	///				<item><term>Active High</term><term>1</term></item>
	///				<item><term>Active Low</term><term>2</term></item>
	/// 		  </list> </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="LS_RequestTrigIOParams(char const * serialNo)" />
	/// <seealso cref="LS_SetTrigIOParams(char const * serialNo, KLS_TriggerMode mode1, KLS_TrigPolarity polarity1, KLS_TriggerMode mode2, KLS_TrigPolarity polarity2)" />
	/// <seealso cref="LS_GetTrigIOParamsBlock(char const * serialNo, KLS_TrigIOParams *params)" />
	/// <seealso cref="LS_SetTrigIOParamsBlock(char const * serialNo, KLS_TrigIOParams *params)" />
	KLASERSOURCE_API short __cdecl LS_GetTrigIOParams(char const * serialNo, KLS_TriggerMode *mode1, KLS_TrigPolarity *polarity1, KLS_TriggerMode *mode2, KLS_TrigPolarity *polarity2);

	/// <summary>	Sets the Trigger IO parameters. </summary>
	/// <param name="serialNo"> 	The device serial no. </param>
	/// <param name="mode1">		The Trigger1 mode. <list type=table>
	///				<item><term>Disabled</term><term>0</term></item>
	///				<item><term>General Input</term><term>1</term></item>
	///				<item><term>General Output</term><term>10</term></item>
	///				<item><term>Laser Output On</term><term>11</term></item>
	///				<item><term>Interlock enabled</term><term>12</term></item>
	///				<item><term>Set Power changed</term><term>13</term></item>
	///				<item><term>High Stability Out</term><term>14</term></item>
	///				<item><term>Low Stability Out</term><term>15</term></item>
	/// 		  </list></param>
	/// <param name="polarity1">	The Trigger1 polarity. <list type=table>
	///				<item><term>Active High</term><term>1</term></item>
	///				<item><term>Active Low</term><term>2</term></item>
	/// 		  </list></param>
	/// <param name="mode2">		The Trigger2 mode. <list type=table>
	///				<item><term>Disabled</term><term>0</term></item>
	///				<item><term>General Input</term><term>1</term></item>
	///				<item><term>General Output</term><term>10</term></item>
	///				<item><term>Laser Output On</term><term>11</term></item>
	///				<item><term>Interlock enabled</term><term>12</term></item>
	///				<item><term>Set Power changed</term><term>13</term></item>
	///				<item><term>High Stability Out</term><term>14</term></item>
	///				<item><term>Low Stability Out</term><term>15</term></item>
	/// 		  </list></param>
	/// <param name="polarity2">	The Trigger2 polarity.<list type=table>
	///				<item><term>Active High</term><term>1</term></item>
	///				<item><term>Active Low</term><term>2</term></item>
	/// 		  </list> </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="LS_RequestTrigIOParams(char const * serialNo)" />
	/// <seealso cref="LS_GetTrigIOParams(char const * serialNo, KLS_TriggerMode *mode1, KLS_TrigPolarity *polarity1, KLS_TriggerMode *mode2, KLS_TrigPolarity *polarity2)" />
	/// <seealso cref="LS_GetTrigIOParamsBlock(char const * serialNo, KLS_TrigIOParams *params)" />
	/// <seealso cref="LS_SetTrigIOParamsBlock(char const * serialNo, KLS_TrigIOParams *params)" />
	KLASERSOURCE_API short __cdecl LS_SetTrigIOParams(char const * serialNo, KLS_TriggerMode mode1, KLS_TrigPolarity polarity1, KLS_TriggerMode mode2, KLS_TrigPolarity polarity2);

	/// <summary>	Gets the Trigger IO parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="params">  	The trigger IO structure. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="LS_RequestTrigIOParams(char const * serialNo)" />
	/// <seealso cref="LS_GetTrigIOParams(char const * serialNo, KLS_TriggerMode *mode1, KLS_TrigPolarity *polarity1, KLS_TriggerMode *mode2, KLS_TrigPolarity *polarity2)" />
	/// <seealso cref="LS_SetTrigIOParams(char const * serialNo, KLS_TriggerMode mode1, KLS_TrigPolarity polarity1, KLS_TriggerMode mode2, KLS_TrigPolarity polarity2)" />
	/// <seealso cref="LS_SetTrigIOParamsBlock(char const * serialNo, KLS_TrigIOParams *params)" />
	KLASERSOURCE_API short __cdecl LS_GetTrigIOParamsBlock(char const * serialNo, KLS_TrigIOParams *params);

	/// <summary>	Ls set trig i/o parameters block. </summary>
	/// <param name="serialNo">	The serial no. </param>
	/// <param name="params">  	The trigger IO structure. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="LS_RequestTrigIOParams(char const * serialNo)" />
	/// <seealso cref="LS_GetTrigIOParams(char const * serialNo, KLS_TriggerMode *mode1, KLS_TrigPolarity *polarity1, KLS_TriggerMode *mode2, KLS_TrigPolarity *polarity2)" />
	/// <seealso cref="LS_SetTrigIOParams(char const * serialNo, KLS_TriggerMode mode1, KLS_TrigPolarity polarity1, KLS_TriggerMode mode2, KLS_TrigPolarity polarity2)" />
	/// <seealso cref="LS_GetTrigIOParamsBlock(char const * serialNo, KLS_TrigIOParams *params)" />
	KLASERSOURCE_API short __cdecl LS_SetTrigIOParamsBlock(char const * serialNo, KLS_TrigIOParams *params);

	/// <summary> Gets the Interlock State. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The interlock state.
	/// 		  <list type=table>
	///				<item><term>Enabled</term><term></term>1</item>
	///				<item><term>Disabled</term><term></term>2</item>
	/// 		  </list> </returns>
	KLASERSOURCE_API BYTE __cdecl LS_GetInterlockState(char const * serialNo);

	/// <summary> Requests the limits MaxPower and MaxCurrent. </summary>
	/// <param name="serialNo">The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="LS_GetLimits(char const * serialNo, WORD &maxPower, WORD &maxCurrent)" />
	KLASERSOURCE_API short __cdecl LS_RequestLimits(char const * serialNo);

	/// <summary> Requests the device Wavelength. </summary>
	/// <param name="serialNo">The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="LS_GetWavelength(char const * serialNo)" />
	KLASERSOURCE_API short __cdecl LS_RequestWavelength(char const * serialNo);

	/// <summary> Gets the operating wavelength. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The operating Wavelength in nm. </returns>
	/// <seealso cref="LS_RequestWavelength(char const * serialNo)" />
	KLASERSOURCE_API WORD __cdecl LS_GetWavelength(char const * serialNo);

	/// <summary> Gets the max power and current limits for the device. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="maxPower"> The power limit, range 0 to 65535 equivalent to (0 to 6.5535mW). </param>
	/// <param name="maxCurrent"> The current limit, range 0 to 65535 equivalent to (0 to 655.35mA). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful.  </returns>
	/// <seealso cref="LS_RequestLimits(char const * serialNo)" />
	KLASERSOURCE_API short __cdecl LS_GetLimits(char const * serialNo, WORD &maxPower, WORD &maxCurrent);

	/// <summary> Sets the output power. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="LS_GetPowerSet(char const * serialNo)" />
	/// <seealso cref="LS_SetPower(char const * serialNo, WORD power)" />
	KLASERSOURCE_API short __cdecl LS_RequestSetPower(char const * serialNo);

	/// <summary> Gets the output power currently set. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The output power, range 0 to 32767 representing 0 to 100 % of the maximum power.<br />
	/// 			The maximum output power is defined by  <see cref="LS_GetLimits(char const * serialNo, WORD &maxPower, WORD &maxCurrent)" /> </returns>
	/// <seealso cref="LS_SetPower(char const * serialNo, WORD power)" />
	/// <seealso cref="LS_RequestSetPower(char const * serialNo)" />
	KLASERSOURCE_API WORD __cdecl LS_GetPowerSet(char const * serialNo);

	/// <summary> Sets the output power. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="power"> The output power, range 0 to 32767 representing 0 to 100 % of the maximum power.<br />
	/// 					  The maximum output power is defined by  <see cref="LS_GetLimits(char const * serialNo, WORD &maxPower, WORD &maxCurrent)" /> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="LS_GetPowerSet(char const * serialNo)" />
	/// <seealso cref="LS_RequestSetPower(char const * serialNo)" />
	KLASERSOURCE_API short __cdecl LS_SetPower(char const * serialNo, WORD power);

	/// <summary> Requests the state quantities (actual power, current and status). </summary>
	/// <remarks> This needs to be called to get the device to send it's current status bits.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="LS_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="LS_RequestReadings(char const * serialNo)" />
	/// <seealso cref="LS_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="LS_GetStatusBits(char const * serialNo)" />
	/// <seealso cref="LS_GetPowerReading(char const * serialNo)" />
	/// <seealso cref="LS_GetCurrentReading(char const * serialNo)" />
	/// <seealso cref="LS_StartPolling(char const * serialNo, int milliseconds)" />
	KLASERSOURCE_API short __cdecl LS_RequestStatus(char const * serialNo);

	/// <summary> Request power and current readings. </summary>
	/// <remarks> This needs to be called to get the device to send it's current reading.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="LS_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="LS_GetPowerReading(char const * serialNo)" />
	/// <seealso cref="LS_GetCurrentReading(char const * serialNo)" />
	/// <seealso cref="LS_RequestStatus(char const * serialNo)" />
	/// <seealso cref="LS_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="LS_StartPolling(char const * serialNo, int milliseconds)" />
	KLASERSOURCE_API short __cdecl LS_RequestReadings(char const * serialNo);

	/// <summary> Request the status bits which identify the current device state. </summary>
	/// <remarks> This needs to be called to get the device to send it's current status bits.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="LS_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="LS_GetStatusBits(char const * serialNo)" />
	/// <seealso cref="LS_RequestStatus(char const * serialNo)" />
	/// <seealso cref="LS_RequestReadings(char const * serialNo)" />
	/// <seealso cref="LS_StartPolling(char const * serialNo, int milliseconds)" />
	KLASERSOURCE_API short __cdecl LS_RequestStatusBits(char const * serialNo);

	/// <summary> Gets current power reading. </summary>
	/// <remarks> This returns the latest power received from the device.<br />
	/// 		  To get new power, use <see cref="LS_RequestReadings(char const * serialNo)" />
	///			  or use <see cref="LS_RequestStatus(char const * serialNo)" />
	/// 		  or use the polling functions, <see cref="LS_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The current power, range 0 to 32767 representing 0 to 100 % of the maximum power.<br />
	/// 					  The maximum output power is defined by  <see cref="LS_GetLimits(char const * serialNo, WORD &maxPower, WORD &maxCurrent)" /> </returns>
	/// <seealso cref="LS_GetCurrentReading(char const * serialNo)" />
	/// <seealso cref="LS_GetLimits(char const * serialNo, WORD &maxPower, WORD &maxCurrent)" />
	/// <seealso cref="LS_RequestReadings(char const * serialNo)" />
	/// <seealso cref="LS_RequestStatus(char const * serialNo)" />
	/// <seealso cref="LS_StartPolling(char const * serialNo, int milliseconds)" />
	KLASERSOURCE_API WORD __cdecl LS_GetPowerReading(char const * serialNo);

	/// <summary> Gets current Current reading. </summary>
	/// <remarks> This returns the latest current received from the device.<br />
	/// 		  To get new current, use <see cref="LS_RequestReadings(char const * serialNo)" />
	///			  or use <see cref="LS_RequestStatus(char const * serialNo)" />
	/// 		  or use the polling functions, <see cref="LS_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The current Current, range 0 to 32767 representing 0 to 100 % of the maximum current.<br />
	/// 					  The maximum output Current is defined by  <see cref="LS_GetLimits(char const * serialNo, WORD &maxPower, WORD &maxCurrent)" /> </returns>
	/// <seealso cref="LS_GetPowerReading(char const * serialNo)" />
	/// <seealso cref="LS_GetLimits(char const * serialNo, WORD &maxPower, WORD &maxCurrent)" />
	/// <seealso cref="LS_RequestReadings(char const * serialNo)" />
	/// <seealso cref="LS_RequestStatus(char const * serialNo)" />
	/// <seealso cref="LS_StartPolling(char const * serialNo, int milliseconds)" />
	KLASERSOURCE_API WORD __cdecl LS_GetCurrentReading(char const * serialNo);

	/// <summary>Get the current status bits. </summary>
	/// <remarks> This returns the latest status bits received from the device.<br />
	/// 		  To get new status bits, use <see cref="LS_RequestStatusBits(char const * serialNo)" />
	///			  or use <see cref="LS_RequestStatus(char const * serialNo)" />
	/// 		  or use the polling functions, <see cref="LS_StartPolling(char const * serialNo, int milliseconds)" />.  </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	The status bits from the device <list type=table>
	///				<item><term>0x00000001</term><term>Laser output enabled state (1=Enabled, 0=Disabled).</term></item>
	///				<item><term>0x00000002</term><term>Key switch enabled state (1=Enabled, 0=Disabled).</term></item>
	///				<item><term>0x00000004</term><term>Laser control mode (1=Constant P (Closed Loop), 0=Constant I (Open Loop)).</term></item>
	///				<item><term>0x00000008</term><term>Safety interlock enabled state (1=Enabled, 0=Disabled).</term></item>
	///				<item><term>...</term><term> </term></item>
	///				<item><term>0x00000080</term><term>For Future Use</term></item>
	///				<item><term>0x00000100</term><term></term></item>
	///				<item><term>...</term><term> </term></item>
	///				<item><term>0x20000000</term><term></term></item>
	///				<item><term>0x40000000</term><term>Error</term></item>
	///				<item><term>0x80000000</term>For Future Use<term> </term></item>
	/// 		  </list>. </returns>
	/// <seealso cref="LS_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="LS_RequestStatus(char const * serialNo)" />
	/// <seealso cref="LS_StartPolling(char const * serialNo, int milliseconds)" />
	KLASERSOURCE_API DWORD __cdecl LS_GetStatusBits(char const * serialNo);

	/// <summary> Starts the internal polling loop which continuously requests position and status. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="milliseconds">The milliseconds polling rate. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="LS_StopPolling(char const * serialNo)" />
	/// <seealso cref="LS_PollingDuration(char const * serialNo)" />
	/// <seealso cref="LS_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="LS_RequestStatus(char const * serialNo)" />
	/// <seealso cref="LS_RequestReadings(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	KLASERSOURCE_API bool __cdecl LS_StartPolling(char const * serialNo, int milliseconds);

	/// <summary> Gets the polling loop duration. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The time between polls in milliseconds or 0 if polling is not active. </returns>
	/// <seealso cref="LS_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="LS_StopPolling(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	KLASERSOURCE_API long __cdecl LS_PollingDuration(char const * serialNo);

	/// <summary> Stops the internal polling loop. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <seealso cref="LS_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="LS_PollingDuration(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	KLASERSOURCE_API void __cdecl LS_StopPolling(char const * serialNo);

	/// <summary> Gets the time in milliseconds since tha last message was received from the device. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="lastUpdateTimeMS"> The time since the last message was received in milliseconds. </param>
	/// <returns> True if monitoring is enabled otherwize False. </returns>
	/// <seealso cref="LS_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// <seealso cref="LS_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	KLASERSOURCE_API bool __cdecl LS_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS );

	/// <summary> Enables the last message monitoring timer. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="enable"> True to enable monitoring otherwise False to disable. </param>
	/// <param name="lastMsgTimeout"> The last message error timeout in ms. 0 to disable. </param>
	/// <seealso cref="LS_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="LS_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	KLASERSOURCE_API void __cdecl LS_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout );

	/// <summary> Queries if the time since the last message has exceeded the lastMsgTimeout set by <see cref="LS_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )"/>. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> True if last message timer has elapsed, False if monitoring is not enabled or if time of last message received is less than lastMsgTimeout. </returns>
	/// <seealso cref="LS_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="LS_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	KLASERSOURCE_API bool __cdecl LS_HasLastMsgTimerOverrun(char const * serialNo);

	/// <summary> Requests that all settings are download from device. </summary>
	/// <remarks> This function requests that the device upload all it's settings to the DLL.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	KLASERSOURCE_API short __cdecl LS_RequestSettings(char const * serialNo);
}
/** @} */ // KCubeLaserSource
