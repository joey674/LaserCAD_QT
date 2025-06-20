// summary:	Declares the functions class
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the KCUBESOLENOIDDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// KCUBESOLENOID_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef KCUBESOLENOIDDLL_EXPORTS
#define KCUBESOLENOID_API __declspec(dllexport)
#else
#define KCUBESOLENOID_API __declspec(dllimport)
#endif

#include <OaIdl.h>

#pragma once

/** @defgroup KCubeSolenoid KCube Solenoid
 *  This section details the Structures and Functions relavent to the  @ref KSC101_page "KCube Solenoid"<br />
 *  For an example of how to connect to the device and perform simple operations use the following links:
 *  <list type=bullet>
 *    <item> \ref namespaces_ksc_ex_1 "Example of using the Thorlabs.MotionControl.KCube.Solenoid.DLL from a C or C++ project."<br />
 *									  This requires the DLL to be dynamical linked. </item>
 *    <item> \ref namespaces_ksc_ex_2 "Example of using the Thorlabs.MotionControl.KCube.Solenoid.DLL from a C# project"<br />
 *									  This uses Marshalling to load and access the C DLL. </item>
 *  </list>
 *  The Thorlabs.MotionControl.KCube.Solenoid.DLL requires the following DLLs
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

	/// <summary> Structure containing the cycle parameters. </summary>
	/// <value> Options for implementing the different automatic operation modes. </value>
	typedef struct SC_CycleParameters
	{
		/// <summary> The on time, i.e. the pulse width when in automatic or triggered mode. (see <see cref="SC_OperatingModes"/>) <br /> </summary>
		///			  Range 400 to 40,000,000 in steps of 0.25 milliseconds, i.e. (100ms to 10000s)
		unsigned int openTime;
		/// <summary> The off time, i.e. the time between pulses in continuous mode. (see <see cref="SC_OperatingModes"/>)<br /> </summary>
		///			  Range 400 to 40,000,000 in steps of 0.25 milliseconds, i.e. (100ms to 10000s)
		unsigned int closedTime;
		/// <summary> The number of on/off cycles when running in continuous mode. (see <see cref="SC_OperatingModes"/>)<br />
		/// 		  Range 0 to 1000,000 where 0 represent unlimited.  </summary>
		unsigned int numCycles;
	} SC_CycleParameters;

	/// <summary> Values that represent the Operating Modes. </summary>
	typedef enum SC_OperatingModes : byte
	{
		/// <summary> Manual mode, solenoid follows <see cref="SC_OperatingStates"/> where Active = solenoid open, Inactive = solenoid closed</summary>
		SC_Manual = 0x01,
		/// <summary> Single mode, when <see cref="SC_OperatingStates"/> activates, the solenoid will open and close once as defined by <see cref="SC_CycleParameters"/>. </summary>
		SC_Single = 0x02,
		/// <summary> Continuous mode, when <see cref="SC_OperatingStates"/> activates, the solenoid will continuously open and close as defined by <see cref="SC_CycleParameters"/>. </summary>
		SC_Auto = 0x03,
		/// <summary> Triggered mode, when <see cref="SC_OperatingStates"/> is active and device is triggered, the solenoid will open and close once as defined by <see cref="SC_CycleParameters"/>. </summary>
		SC_Triggered = 0x04
	} SC_OperatingModes;

	/// <summary> Values that represent the operating States. </summary>
	typedef enum SC_OperatingStates : byte
	{
		/// <summary> The active operating state. </summary>
		/// <remarks> When the controller is activated, the operation taken depends upon the current <see cref="SC_OperatingModes"/> value.
		/// 		  <list type=table>
		///				<item><term>Manual</term><term>The solenoid is opened until the state becomes inactive.</term></item>
		///				<item><term>Single</term><term>The solenoid is opened and closed once as defined by <see cref="SC_CycleParameters"/>.
		///					   On completion, the state becomes inactive.</term></item>
		///				<item><term>Auto</term><term>The solenoid is repeatedly opened and closed as defined by <see cref="SC_CycleParameters"/>.
		///					  When the number of cycles completes, the state becomes inactive</term></item>
		///				<item><term>Triggered</term><term>The solenoid waits for a trigger and then opens and closes. 
		///							The state remains active. </term></item>
		/// 		  </list> <br /> </remarks>
		SC_Active = 0x01,
		/// <summary> The inactive operating state. </summary>
		/// <remarks> When the controller becomes inactive, the solenoid is closed.
		SC_Inactive = 0x02
	} SC_OperatingStates;

	/// <summary> The physical solenoid state. </summary>
	typedef enum SC_SolenoidStates : byte
	{
		SC_SolenoidOpen = 0x01,///< The solenoid is open
		SC_SolenoidClosed = 0x02///< The solenoid is closed
	} SC_SolenoidStates;

	/// <summary> Values that represent Trigger Port Mode. </summary>
	typedef enum KSC_TriggerPortMode : __int16
	{
		KSC_TrigDisabled = 0x00,///< Trigger Disabled
		KSC_TrigIn_GPI = 0x01,///< General purpose logic input (<see cref="SC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)
		KSC_TrigOut_GPO = 0x0A,///< General purpose output (<see cref="SC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)
	} KSC_TriggerPortMode;

	/// <summary> Values that represent Trigger Port Polarity. </summary>
	typedef enum KSC_TriggerPortPolarity : __int16
	{
		KSC_TrigPolarityHigh = 0x01,///< Trigger Polarity high
		KSC_TrigPolarityLow = 0x02,///< Trigger Polarity Low
	} KSC_TriggerPortPolarity;

	/// <summary> Structure containing the MMI Parameters. </summary>
	/// <value> Device GUI parameters. </value>
	typedef struct KSC_MMIParams
	{
		/// <summary> The unused fields. </summary>
		__int16 unused[10];
		/// <summary> The display intensity, range 0 to 100%. </summary>
		__int16 DisplayIntensity;
		/// <summary> The display timeout in miniutes. </summary>
		__int16 DisplayTimeout;
		/// <summary> The display dim intensity, range 0 to (Display Timeout). </summary>
		__int16 DisplayDimIntensity;
		/// <summary> Reserved fields. </summary>
		__int16 reserved[4];
	} KSC_MMIParams;

	/// <summary> KCube motor trigger configuration. </summary>
	typedef struct KSC_TriggerConfig
	{
		/// <summary> The trigger 1 mode. </summary>
		/// <remarks> The trigger 1 operating mode:
		/// 		  <list type=table>
		///				<item><term>0</term><term>Trigger disabled</term></item>
		///				<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="SC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
		///				<item><term>10</term><term>Trigger Output - General purpose output (<see cref="SC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
		/// 		  </list>
		/// 		  </remarks>
		KSC_TriggerPortMode Trigger1Mode;
		/// <summary> The trigger 1 polarity. </summary>
		/// <remarks> The trigger 1 output polaritye:
		/// 		  <list type=table>
		///				<item><term>1</term><term>Output high when set</term></item>
		///				<item><term>2</term><term>Output low when set</term></item>
		/// 		  </list>
		/// 		  </remarks>
		KSC_TriggerPortPolarity Trigger1Polarity;
		/// <summary> The trigger 2 mode. </summary>
		/// <remarks> The trigger 2 operating mode:
		/// 		  <list type=table>
		///				<item><term>0</term><term>Trigger disabled</term></item>
		///				<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="SC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
		///				<item><term>10</term><term>Trigger Output - General purpose output (<see cref="SC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
		/// 		  </list>
		/// 		  </remarks>
		KSC_TriggerPortMode Trigger2Mode;
		/// <summary> The trigger 2 polarity. </summary>
		/// <remarks> The trigger 2 output polarity:
		/// 		  <list type=table>
		///				<item><term>1</term><term>Output high when set</term></item>
		///				<item><term>2</term><term>Output low when set</term></item>
		/// 		  </list>
		/// 		  </remarks>
		KSC_TriggerPortPolarity Trigger2Polarity;
		/// <summary> reserved fields. </summary>
		__int16 reserved[6];
	} KSC_TriggerConfig;

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
	KCUBESOLENOID_API short __cdecl TLI_BuildDeviceList(void);

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
	KCUBESOLENOID_API short __cdecl TLI_GetDeviceListSize();

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
	KCUBESOLENOID_API short __cdecl TLI_GetDeviceList(SAFEARRAY** stringsReceiver);

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
	KCUBESOLENOID_API short __cdecl TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID);

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
	KCUBESOLENOID_API short __cdecl TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length);

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
	KCUBESOLENOID_API short __cdecl TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer);

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
	KCUBESOLENOID_API short __cdecl TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID);

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
	KCUBESOLENOID_API short __cdecl TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length);

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
	KCUBESOLENOID_API short __cdecl TLI_GetDeviceInfo(char const * serialNo, TLI_DeviceInfo *info);

	/// <summary> Initialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <remarks> Call TLI_InitializeSimulations before TLI_BuildDeviceList at the start of the program to make a connection to the simulation manager.<Br />
	/// 		  Any devices configured in the simulation manager will become visible TLI_BuildDeviceList is called and can be accessed using TLI_GetDeviceList.<Br />
	/// 		  Call TLI_InitializeSimulations at the end of the program to release the simulator.  </remarks>
	/// <seealso cref="TLI_UninitializeSimulations()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	KCUBESOLENOID_API void __cdecl TLI_InitializeSimulations();

	/// <summary> Uninitialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <seealso cref="TLI_InitializeSimulations()" />
	KCUBESOLENOID_API void __cdecl TLI_UninitializeSimulations();

	/// <summary> Open the device for communications. </summary>
	/// <param name="serialNo">	The serial no of the device to be connected. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="SC_Close(char const * serialNo)" />
	KCUBESOLENOID_API short __cdecl SC_Open(char const * serialNo);

	/// <summary> Disconnect and close the device. </summary>
	/// <param name="serialNo">	The serial no of the device to be disconnected. </param>
    /// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="SC_Open(char const * serialNo)" />
	KCUBESOLENOID_API void __cdecl SC_Close(char const * serialNo);

	/// <summary>	Check connection. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> true if the USB is listed by the ftdi controller</returns>
	/// \include CodeSnippet_CheckConnection.cpp
	KCUBESOLENOID_API bool __cdecl SC_CheckConnection(char const * serialNo);

	/// <summary> Sends a command to the device to make it identify iteself. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	KCUBESOLENOID_API void __cdecl SC_Identify(char const * serialNo);

	/// <summary> Requests the LED indicator bits on cube. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_GetLEDswitches(char const * serialNo)" />
	/// <seealso cref="SC_SetLEDswitches(char const * serialNo, WORD LEDswitches)" />
	KCUBESOLENOID_API short __cdecl SC_RequestLEDswitches(char const * serialNo);

	/// <summary> Get the LED indicator bits on cube. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> Sum of: 8 to indicate moving 2 to indicate end of track and 1 to flash on identify command. </returns>
	/// <seealso cref="SC_RequestLEDswitches(char const * serialNo)" />
	/// <seealso cref="SC_SetLEDswitches(char const * serialNo, WORD LEDswitches)" />
	KCUBESOLENOID_API WORD __cdecl SC_GetLEDswitches(char const * serialNo);

	/// <summary> Set the LED indicator bits on cube. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="LEDswitches"> Sum of: 8 to indicate moving 2 to indicate end of track and 1 to flash on identify command. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_RequestLEDswitches(char const * serialNo)" />
	/// <seealso cref="SC_GetLEDswitches(char const * serialNo)" />
	KCUBESOLENOID_API short __cdecl SC_SetLEDswitches(char const * serialNo, WORD LEDswitches);

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
	KCUBESOLENOID_API short __cdecl SC_GetHardwareInfo(char const * serialNo, char * modelNo, DWORD sizeOfModelNo, WORD * type, WORD * numChannels, 
												  char * notes, DWORD sizeOfNotes, DWORD * firmwareVersion, WORD * hardwareVersion, WORD * modificationState);

	/// <summary> Gets the hardware information in a block. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="hardwareInfo"> Address of a TLI_HardwareInformation structure to receive the hardware information. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	KCUBESOLENOID_API short __cdecl SC_GetHardwareInfoBlock(char const *serialNo, TLI_HardwareInformation *hardwareInfo);

	/// <summary> Requests the hub bay number this device is fitted to. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_GetHubBay(char const * serialNo)" />
	KCUBESOLENOID_API short __cdecl SC_RequestHubBay(char const * serialNo);

	/// <summary> Gets the hub bay number this device is fitted to. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The number, 0x00 if unknown or 0xff if not on a hub. </returns>
	/// <seealso cref="SC_RequestHubBay(char const * serialNo)" />
	KCUBESOLENOID_API char __cdecl SC_GetHubBay(char const * serialNo);

	/// <summary> Gets version number of the device software. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device software version number made up of 4 byte parts. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	KCUBESOLENOID_API DWORD __cdecl SC_GetSoftwareVersion(char const * serialNo);

	/// <summary> Update device with stored settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
    /// 		  \include CodeSnippet_connection1.cpp
	KCUBESOLENOID_API bool __cdecl SC_LoadSettings(char const * serialNo);

	/// <summary> Update device with named settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="settingsName"> Name of settings stored away from device. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	///             \include CodeSnippet_connection1.cpp
	KCUBESOLENOID_API bool __cdecl SC_LoadNamedSettings(char const * serialNo, char const *settingsName);

	/// <summary> persist the devices current settings. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	KCUBESOLENOID_API bool __cdecl SC_PersistSettings(char const * serialNo);

	/// <summary> Clears the device message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	KCUBESOLENOID_API void __cdecl SC_ClearMessageQueue(char const * serialNo);

	/// <summary> Registers a callback on the message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="functionPointer"> A function pointer to be called whenever messages are received. </param>
	/// <seealso cref="SC_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="SC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="SC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KCUBESOLENOID_API void __cdecl SC_RegisterMessageCallback(char const * serialNo, void (* functionPointer)());

	/// <summary> Gets the MessageQueue size. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> number of messages in the queue. </returns>
	/// <seealso cref="SC_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="SC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="SC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KCUBESOLENOID_API int __cdecl SC_MessageQueueSize(char const * serialNo);

	/// <summary> Get the next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="SC_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="SC_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="SC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KCUBESOLENOID_API bool __cdecl SC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Wait for next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="SC_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="SC_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="SC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KCUBESOLENOID_API bool __cdecl SC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Starts the internal polling loop which continuously requests position and status. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="milliseconds">The milliseconds polling rate. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="SC_StopPolling(char const * serialNo)" />
	/// <seealso cref="SC_PollingDuration(char const * serialNo)" />
	/// <seealso cref="SC_RequestStatusBits(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	KCUBESOLENOID_API bool __cdecl SC_StartPolling(char const * serialNo, int milliseconds);

	/// <summary> Gets the polling loop duration. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The time between polls in milliseconds or 0 if polling is not active. </returns>
	/// <seealso cref="SC_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="SC_StopPolling(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	KCUBESOLENOID_API long __cdecl SC_PollingDuration(char const * serialNo);

	/// <summary> Stops the internal polling loop. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <seealso cref="SC_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="SC_PollingDuration(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	KCUBESOLENOID_API void __cdecl SC_StopPolling(char const * serialNo);

	/// <summary> Gets the time in milliseconds since tha last message was received from the device. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="lastUpdateTimeMS"> The time since the last message was received in milliseconds. </param>
	/// <returns> True if monitoring is enabled otherwize False. </returns>
	/// <seealso cref="SC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// <seealso cref="SC_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	KCUBESOLENOID_API bool __cdecl SC_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS );

	/// <summary> Enables the last message monitoring timer. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="enable"> True to enable monitoring otherwise False to disable. </param>
	/// <param name="lastMsgTimeout"> The last message error timeout in ms. 0 to disable. </param>
	/// <seealso cref="SC_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="SC_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	KCUBESOLENOID_API void __cdecl SC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout );

	/// <summary> Queries if the time since the last message has exceeded the lastMsgTimeout set by <see cref="SC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )"/>. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> True if last message timer has elapsed, False if monitoring is not enabled or if time of last message received is less than lastMsgTimeout. </returns>
	/// <seealso cref="SC_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="SC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	KCUBESOLENOID_API bool __cdecl SC_HasLastMsgTimerOverrun(char const * serialNo);

	/// <summary> Requests that all settings are download from device. </summary>
	/// <remarks> This function requests that the device upload all it's settings to the DLL.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	KCUBESOLENOID_API short __cdecl SC_RequestSettings(char const * serialNo);

	/// <summary> Requests the status from the device. </summary>
	/// <remarks> This needs to be called to get the device to send it's current status bits.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="SC_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="SC_GetStatusBits(char const * serialNo)" />
	/// <seealso cref="SC_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="SC_StartPolling(char const * serialNo, int milliseconds)" />
	KCUBESOLENOID_API short __cdecl SC_RequestStatus(char const * serialNo);

	/// <summary> Request the status bits which identify the current device state. </summary>
	/// <remarks> This needs to be called to get the device to send it's current status bits.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="SC_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="SC_GetStatusBits(char const * serialNo)" />
	/// <seealso cref="SC_RequestStatus(char const * serialNo)" />
	/// <seealso cref="SC_StartPolling(char const * serialNo, int milliseconds)" />
	KCUBESOLENOID_API short __cdecl SC_RequestStatusBits(char const * serialNo);

	/// <summary>Get the current status bits. </summary>
	/// <remarks> This returns the latest status bits received from the device.<br />
	/// 		  To get new status bits, use <see cref="SC_RequestStatusBits(char const * serialNo)" />
	/// 		  or use the polling functions, <see cref="SC_StartPolling(char const * serialNo, int milliseconds)" />.  </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	The status bits from the device <list type=table>
	///				<item><term>0x00000001</term><term>Solenoid output state (1=Enabled, 0=Disabled).</term></item>
	///				<item><term>0x00000002</term><term>Not used.</term></item>
	///				<item><term>0x00000004</term><term> </term></item>
	///				<item><term>...</term><term> </term></item>
	///				<item><term>0x00000800</term><term> </term></item>
	///				<item><term>0x00001000</term><term>Interlock state (1=Enabled, 0=Disabled).</term></item>
	///				<item><term>0x00002000</term><term>Not used.</term></item>
	///				<item><term>0x00004000</term><term> </term></item>
	///				<item><term>...</term><term> </term></item>
	///				<item><term>0x40000000</term><term> </term></item>
	///				<item><term>0x80000000</term><term>Channel enabled (1=Enabled, 0=Disabled).</term></item>
	/// 		  </list>. </returns>
	/// <seealso cref="SC_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="SC_StartPolling(char const * serialNo, int milliseconds)" />
	KCUBESOLENOID_API DWORD __cdecl SC_GetStatusBits(char const * serialNo);

	/// <summary> Requests the Operating Mode. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_GetOperatingMode(char const * serialNo)" />
	/// <seealso cref="SC_SetOperatingMode(char const * serialNo, SC_OperatingModes mode)" />
	KCUBESOLENOID_API short __cdecl SC_RequestOperatingMode(char const * serialNo);

	/// <summary> Gets the Operating Mode. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The current operating mode.
	/// 		  <list type=table>
	///				<item><term>Manual</term><term>1</term></item>
	///				<item><term>Single</term><term>2</term></item>
	///				<item><term>Auto</term><term>3</term></item>
	///				<item><term>Triggered</term><term>4</term></item>
	/// 		  </list> </returns>
	/// <seealso cref="SC_RequestOperatingMode(char const * serialNo)" />
	/// <seealso cref="SC_SetOperatingMode(char const * serialNo, SC_OperatingModes mode)" />
	KCUBESOLENOID_API SC_OperatingModes __cdecl SC_GetOperatingMode(char const * serialNo);

	/// <summary> Sets the Operating Mode. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="mode"> The required operating mode.
	/// 		  <list type=table>
	///				<item><term>Manual</term><term>1</term></item>
	///				<item><term>Single</term><term>2</term></item>
	///				<item><term>Auto</term><term>3</term></item>
	///				<item><term>Triggered</term><term>4</term></item>
	/// 		  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_RequestOperatingMode(char const * serialNo)" />
	/// <seealso cref="SC_GetOperatingMode(char const * serialNo)" />
	KCUBESOLENOID_API short __cdecl SC_SetOperatingMode(char const * serialNo, SC_OperatingModes mode);

	/// <summary> Gets the current solenoid state. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The current solenoid state.
	/// 		  <list type=table>
	///				<item><term>Open</term><term>1</term></item>
	///				<item><term>Closed</term><term>2</term></item>
	/// 		  </list> </returns>
	KCUBESOLENOID_API SC_SolenoidStates __cdecl SC_GetSolenoidState(char const * serialNo);

	/// <summary> Requests the operating state. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_GetOperatingState(char const * serialNo)" />
	/// <seealso cref="SC_SetOperatingState(char const * serialNo, SC_OperatingStates state)" />
	KCUBESOLENOID_API short __cdecl SC_RequestOperatingState(char const * serialNo);

	/// <summary> Gets the current operating state. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>The current operating state.
	/// 		  <list type=table>
	///				<item><term>Active</term><term>1</term></item>
	///				<item><term>Inactive</term><term>2</term></item>
	/// 		  </list> </returns>
	/// <seealso cref="SC_RequestOperatingState(char const * serialNo)" />
	/// <seealso cref="SC_SetOperatingState(char const * serialNo, SC_OperatingStates state)" />
	KCUBESOLENOID_API SC_OperatingStates __cdecl SC_GetOperatingState(char const * serialNo);

	/// <summary> Sets the operating state. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="state">The required operating state.
	/// 		  <list type=table>
	///				<item><term>Active</term><term>1</term></item>
	///				<item><term>Inactive</term><term>2</term></item>
	/// 		  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_RequestOperatingState(char const * serialNo)" />
	/// <seealso cref="SC_GetOperatingState(char const * serialNo)" />
	KCUBESOLENOID_API short __cdecl SC_SetOperatingState(char const * serialNo, SC_OperatingStates state);

	/// <summary> Requests the cycle parameters. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_GetCycleParams(char const * serialNo, unsigned int * pOpenTime, unsigned int * pClosedTime, unsigned int * numCycles)" />
	/// <seealso cref="SC_SetCycleParams(char const * serialNo, unsigned int openTime, unsigned int closedTime, unsigned int numCycles)" />
	/// <seealso cref="SC_GetCycleParamsBlock(const char * serialNo, SC_CycleParameters *cycleParams)" />
	/// <seealso cref="SC_SetCycleParamsBlock(const char * serialNo, SC_CycleParameters *cycleParams)" />
	KCUBESOLENOID_API short __cdecl SC_RequestCycleParams(char const * serialNo);

	/// <summary> Gets the cycle parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="onTime"> Address of the parameter to receive the On Time parameter.<br />
	/// 					   Range 250 to 100,000,000 in steps of 1 milliseconds (0.250s to 10,000s). </param>
	/// <param name="offTime"> Address of the parameter to receive the Off Time parameter.<br />
	/// 					   Range 250 to 100,000,000 in steps of 1 milliseconds (0.250s to 10,000s). </param>
	/// <param name="numCycles"> Address of the parameter to receive the Number of Cycles parameter.<br />
	/// 					   Range 0 to 1000,000 where 0 represent unlimited. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_RequestCycleParams(char const * serialNo)" />
	/// <seealso cref="SC_SetCycleParams(char const * serialNo, unsigned int onTime, unsigned int offTime, unsigned int numCycles)" />
	/// <seealso cref="SC_GetCycleParamsBlock(const char * serialNo, SC_CycleParameters *cycleParams)" />
	/// <seealso cref="SC_SetCycleParamsBlock(const char * serialNo, SC_CycleParameters *cycleParams)" />
	KCUBESOLENOID_API short __cdecl SC_GetCycleParams(char const * serialNo, unsigned int * onTime, unsigned int * offTime, unsigned int * numCycles);

	/// <summary> Sets the cycle parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="onTime"> Address of the parameter to receive the On Time parameter.<br />
	/// 					   Range 250 to 100,000,000 in steps of 1 milliseconds (0.250s to 10,000s). </param>
	/// <param name="offTime"> Address of the parameter to receive the Off Time parameter.<br />
	/// 					   Range 250 to 100,000,000 in steps of 1 milliseconds (0.250s to 10,000s). </param>
	/// <param name="numCycles"> The Number of Cycles parameter.<br />
	/// 					   Range 0 to 1000,000 where 0 represent unlimited. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_RequestCycleParams(char const * serialNo)" />
	/// <seealso cref="SC_GetCycleParams(char const * serialNo, unsigned int * onTime, unsigned int * offTime, unsigned int * numCycles)" />
	/// <seealso cref="SC_GetCycleParamsBlock(const char * serialNo, SC_CycleParameters *cycleParams)" />
	/// <seealso cref="SC_SetCycleParamsBlock(const char * serialNo, SC_CycleParameters *cycleParams)" />
	KCUBESOLENOID_API short __cdecl SC_SetCycleParams(char const * serialNo, unsigned int onTime, unsigned int offTime, unsigned int numCycles);

	/// <summary> Gets the cycle parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="cycleParams"> Address of the SC_CycleParameters to recieve the cycle parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_RequestCycleParams(char const * serialNo)" />
	/// <seealso cref="SC_GetCycleParams(char const * serialNo, unsigned int * onTime, unsigned int * offTime, unsigned int * numCycles)" />
	/// <seealso cref="SC_SetCycleParams(char const * serialNo, unsigned int onTime, unsigned int offTime, unsigned int numCycles)" />
	/// <seealso cref="SC_SetCycleParamsBlock(const char * serialNo, SC_CycleParameters *cycleParams)" />
	KCUBESOLENOID_API short __cdecl SC_GetCycleParamsBlock(const char * serialNo, SC_CycleParameters *cycleParams);

	/// <summary> Sets the cycle parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="cycleParams"> Address of the SC_CycleParameters containing the new cycle parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_RequestCycleParams(char const * serialNo)" />
	/// <seealso cref="SC_GetCycleParams(char const * serialNo, unsigned int * onTime, unsigned int * offTime, unsigned int * numCycles)" />
	/// <seealso cref="SC_SetCycleParams(char const * serialNo, unsigned int onTime, unsigned int offTime, unsigned int numCycles)" />
	/// <seealso cref="SC_GetCycleParamsBlock(const char * serialNo, SC_CycleParameters *cycleParams)" />
	KCUBESOLENOID_API short __cdecl SC_SetCycleParamsBlock(const char * serialNo, SC_CycleParameters *cycleParams);

	/// <summary> Requests the MMI Parameters for the KCube Display Interface. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_GetMMIParams(char const * serialNo, __int16 *displayIntensity)" />
	/// <seealso cref="SC_GetMMIParamsExt(char const * serialNo, __int16 *displayIntensity, __int16 *displayTimeout, __int16 *displayDimIntensity)" />
	/// <seealso cref="SC_GetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	KCUBESOLENOID_API short __cdecl SC_RequestMMIParams(char const * serialNo);

	/// <summary> Get the MMI Parameters for the KCube Display Interface. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="displayIntensity">	    The display intensity, range 0 to 100%. </param>
	/// <param name="displayTimeout">	    The display timeout, range 0 to 480 in minutes (0 is off, otherwise the inactivity period before dimming the display). </param>
	/// <param name="displayDimIntensity">	The display dimmed intensity, range 0 to 10 (after the timeout period the device display will dim). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_SetMMIParamsExt(char const * serialNo, __int16 displayIntensity)" />
	/// <seealso cref="SC_SetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	/// <seealso cref="SC_RequestMMIParams(char const * serialNo)" />
	/// <seealso cref="SC_GetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	KCUBESOLENOID_API  short __cdecl SC_GetMMIParamsExt(char const * serialNo, __int16 *displayIntensity, __int16 *displayTimeout, __int16 *displayDimIntensity);

	/// \deprecated
	/// <summary> Get the MMI Parameters for the KCube Display Interface. </summary>
	/// <remarks> superceded by <see cref="SC_GetMMIParamsExt(char const * serialNo, __int16 *displayIntensity, __int16 *displayTimeout, __int16 *displayDimIntensity)"/> </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="displayIntensity">	    The display intensity, range 0 to 100%. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_SetMMIParams(char const * serialNo, __int16 displayIntensity)" />
	/// <seealso cref="SC_SetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	/// <seealso cref="SC_RequestMMIParams(char const * serialNo)" />
	/// <seealso cref="SC_GetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	KCUBESOLENOID_API  short __cdecl SC_GetMMIParams(char const * serialNo, __int16 *displayIntensity);

	/// <summary> Set the MMI Parameters for the KCube Display Interface. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="displayIntensity">	    The display intensity, range 0 to 100%. </param>
	/// <param name="displayTimeout">	    The display timeout, range 0 to 480 in minutes (0 is off, otherwise the inactivity period before dimming the display). </param>
	/// <param name="displayDimIntensity">	The display dimmed intensity, range 0 to 10 (after the timeout period the device display will dim). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_RequestMMIParams(char const * serialNo)" />
	/// <seealso cref="SC_GetMMIParamsExt(char const * serialNo, __int16 *displayIntensity)" />
	/// <seealso cref="SC_SetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	/// <seealso cref="SC_GetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	KCUBESOLENOID_API short __cdecl SC_SetMMIParamsExt(char const * serialNo, __int16 displayIntensity, __int16 displayTimeout, __int16 displayDimIntensity);

	/// \deprecated
	/// <summary> Set the MMI Parameters for the KCube Display Interface. </summary>
	/// <remarks> superceded by <see cref="SC_SetMMIParamsExt(char const * serialNo, __int16 displayIntensity, __int16 displayTimeout, __int16 displayDimIntensity)"/> </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="displayIntensity">	    The display intensity, range 0 to 100%. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_RequestMMIParams(char const * serialNo)" />
	/// <seealso cref="SC_GetMMIParams(char const * serialNo, __int16 *displayIntensity)" />
	/// <seealso cref="SC_SetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	/// <seealso cref="SC_GetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	KCUBESOLENOID_API short __cdecl SC_SetMMIParams(char const * serialNo, __int16 displayIntensity);

	/// <summary> Gets the MMI parameters for the device. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="mmiParams"> Options for controlling the mmi. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_RequestMMIParams(char const * serialNo)" />
	/// <seealso cref="SC_GetMMIParamsExt(char const * serialNo, __int16 *displayIntensity, __int16 *displayTimeout, __int16 *displayDimIntensity)" />
	/// <seealso cref="SC_SetMMIParamsExt(char const * serialNo, __int16 displayIntensity, __int16 displayTimeout, __int16 displayDimIntensity)" />
	/// <seealso cref="SC_SetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	KCUBESOLENOID_API short __cdecl SC_GetMMIParamsBlock(char const * serialNo, KSC_MMIParams *mmiParams);

	/// <summary> Sets the MMI parameters for the device. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="mmiParams"> Options for controlling the mmi. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_RequestMMIParams(char const * serialNo)" />
	/// <seealso cref="SC_GetMMIParamsExt(char const * serialNo, __int16 *displayIntensity, __int16 *displayTimeout, __int16 *displayDimIntensity)" />
	/// <seealso cref="SC_SetMMIParamsExt(char const * serialNo, __int16 displayIntensity, __int16 displayTimeout, __int16 displayDimIntensity)" />
	/// <seealso cref="SC_GetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	KCUBESOLENOID_API short __cdecl SC_SetMMIParamsBlock(char const * serialNo, KSC_MMIParams *mmiParams);

	/// <summary> Requests the Trigger Configuration Parameters. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_SetTriggerConfigParams(char const * serialNo, KSC_TriggerPortMode trigger1Mode, KSC_TriggerPortPolarity trigger1Polarity, KSC_TriggerPortMode trigger2Mode, KSC_TriggerPortPolarity trigger2Polarity)" />
	/// <seealso cref="SC_GeTriggerConfigParams(char const * serialNo, KSC_TriggerPortMode *trigger1Mode, KSC_TriggerPortPolarity *trigger1Polarity, KSC_TriggerPortMode *trigger2Mode, KSC_TriggerPortPolarity *trigger2Polarity)" />
	/// <seealso cref="SC_SetTriggerConfigParamsBlock(const char * serialNo, KSC_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="SC_GetTriggerConfigParamsBlock(const char * serialNo, KSC_TriggerConfig *triggerConfigParams)" />
	KCUBESOLENOID_API short __cdecl SC_RequestTriggerConfigParams(char const * serialNo);

	/// <summary> Get the Trigger Configuration Parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="trigger1Mode">	    The trigger 1 mode.<list type=table>
	///						<item><term>0</term><term>Trigger disabled</term></item>
	///						<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="SC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
	///						<item><term>10</term><term>Trigger Output - General purpose output (<see cref="SC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
	///		 		  </list></param>
	/// <param name="trigger1Polarity"> The trigger 1 polarity.<list type=table>
	///						<item><term>1</term><term>Output high when set</term></item>
	///						<item><term>2</term><term>Output low when set</term></item>
	///		 		  </list> </param>
	/// <param name="trigger2Mode">	    The trigger 2 mode.<list type=table>
	///						<item><term>0</term><term>Trigger disabled</term></item>
	///						<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="SC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
	///						<item><term>10</term><term>Trigger Output - General purpose output (<see cref="SC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
	///		 		  </list></param>
	/// <param name="trigger2Polarity"> The trigger 2 polarity.<list type=table>
	///						<item><term>1</term><term>Output high when set</term></item>
	///						<item><term>2</term><term>Output low when set</term></item>
	///		 		  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_SetTriggerConfigParams(char const * serialNo, KSC_TriggerPortMode trigger1Mode, KSC_TriggerPortPolarity trigger1Polarity, KSC_TriggerPortMode trigger2Mode, KSC_TriggerPortPolarity trigger2Polarity)" />
	/// <seealso cref="SC_SetTriggerConfigParamsBlock(const char * serialNo, KSC_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="SC_RequestTriggerConfigParams(char const * serialNo)" />
	/// <seealso cref="SC_GetTriggerConfigParamsBlock(const char * serialNo, KSC_TriggerConfig *triggerConfigParams)" />
	KCUBESOLENOID_API  short __cdecl SC_GetTriggerConfigParams(char const * serialNo, KSC_TriggerPortMode *trigger1Mode, KSC_TriggerPortPolarity *trigger1Polarity, KSC_TriggerPortMode *trigger2Mode, KSC_TriggerPortPolarity *trigger2Polarity);

	/// <summary> Set the Trigger Configuration Parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="trigger1Mode">	    The trigger 1 mode.<list type=table>
	///						<item><term>0</term><term>Trigger disabled</term></item>
	///						<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="SC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
	///						<item><term>10</term><term>Trigger Output - General purpose output (<see cref="SC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
	///		 		  </list></param>
	/// <param name="trigger1Polarity"> The trigger 1 polarity.<list type=table>
	///						<item><term>1</term><term>Output high when set</term></item>
	///						<item><term>2</term><term>Output low when set</term></item>
	///		 		  </list> </param>
	/// <param name="trigger2Mode">	    The trigger 2 mode.<list type=table>
	///						<item><term>0</term><term>Trigger disabled</term></item>
	///						<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="SC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
	///						<item><term>10</term><term>Trigger Output - General purpose output (<see cref="SC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
	///		 		  </list></param>
	/// <param name="trigger2Polarity"> The trigger 2 polarity.<list type=table>
	///						<item><term>1</term><term>Output high when set</term></item>
	///						<item><term>2</term><term>Output low when set</term></item>
	///		 		  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_RequestTriggerConfigParams(char const * serialNo)" />
	/// <seealso cref="SC_GeTriggerConfigParams(char const * serialNo, KSC_TriggerPortMode *trigger1Mode, KSC_TriggerPortPolarity *trigger1Polarity, KSC_TriggerPortMode *trigger2Mode, KSC_TriggerPortPolarity *trigger2Polarity)" />
	/// <seealso cref="SC_SetTriggerConfigParamsBlock(const char * serialNo, KSC_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="SC_GetTriggerConfigParamsBlock(const char * serialNo, KSC_TriggerConfig *triggerConfigParams)" />
	KCUBESOLENOID_API short __cdecl SC_SetTriggerConfigParams(char const * serialNo, KSC_TriggerPortMode trigger1Mode, KSC_TriggerPortPolarity trigger1Polarity, KSC_TriggerPortMode trigger2Mode, KSC_TriggerPortPolarity trigger2Polarity);

	/// <summary> Gets the trigger configuration parameters block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="triggerConfigParams"> Options for controlling the trigger configuration. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_RequestTriggerConfigParams(char const * serialNo)" />
	/// <seealso cref="SC_GeTriggerConfigParams(char const * serialNo, KSC_TriggerPortMode *trigger1Mode, KSC_TriggerPortPolarity *trigger1Polarity, KSC_TriggerPortMode *trigger2Mode, KSC_TriggerPortPolarity *trigger2Polarity)" />
	/// <seealso cref="SC_SetTriggerConfigParams(char const * serialNo, KSC_TriggerPortMode trigger1Mode, KSC_TriggerPortPolarity trigger1Polarity, KSC_TriggerPortMode trigger2Mode, KSC_TriggerPortPolarity trigger2Polarity)" />
	/// <seealso cref="SC_SetTriggerConfigParamsBlock(const char * serialNo, KSC_TriggerConfig *triggerConfigParams)" />
	KCUBESOLENOID_API short __cdecl SC_GetTriggerConfigParamsBlock(char const * serialNo, KSC_TriggerConfig *triggerConfigParams);

	/// <summary> Sets the trigger configuration parameters block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="triggerConfigParams"> Options for controlling the trigger configuration. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_RequestTriggerConfigParams(char const * serialNo)" />
	/// <seealso cref="SC_GeTriggerConfigParams(char const * serialNo, KSC_TriggerPortMode *trigger1Mode, KSC_TriggerPortPolarity *trigger1Polarity, KSC_TriggerPortMode *trigger2Mode, KSC_TriggerPortPolarity *trigger2Polarity)" />
	/// <seealso cref="SC_SetTriggerConfigParams(char const * serialNo, KSC_TriggerPortMode trigger1Mode, KSC_TriggerPortPolarity trigger1Polarity, KSC_TriggerPortMode trigger2Mode, KSC_TriggerPortPolarity trigger2Polarity)" />
	/// <seealso cref="SC_GetTriggerConfigParamsBlock(const char * serialNo, KSC_TriggerConfig *triggerConfigParams)" />
	KCUBESOLENOID_API short __cdecl SC_SetTriggerConfigParamsBlock(char const * serialNo, KSC_TriggerConfig *triggerConfigParams);

	/// <summary> Requests the digital output bits. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_SetDigitalOutputs(char const * serialNo, byte outputsBits)" />
	/// <seealso cref="SC_GetDigitalOutputs(char const * serialNo)" />
	KCUBESOLENOID_API short __cdecl SC_RequestDigitalOutputs(char const * serialNo);

	/// <summary> Gets the digital output bits. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> Bit mask of states of the 4 digital output pins. </returns>
	/// <seealso cref="SC_SetDigitalOutputs(char const * serialNo, byte outputsBits)" />
	/// <seealso cref="SC_RequestDigitalOutputs(char const * serialNo)" />
	KCUBESOLENOID_API byte __cdecl SC_GetDigitalOutputs(char const * serialNo);

	/// <summary> Sets the digital output bits. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="outputsBits"> Bit mask to set states of the 4 digital output pins. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SC_GetDigitalOutputs(char const * serialNo)" />
	/// <seealso cref="SC_RequestDigitalOutputs(char const * serialNo)" />
	KCUBESOLENOID_API short __cdecl SC_SetDigitalOutputs(char const * serialNo, byte outputsBits);
}
/** @} */ // KCubeSolenoid
