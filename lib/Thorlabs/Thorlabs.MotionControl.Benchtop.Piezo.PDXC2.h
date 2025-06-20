
#pragma once

#ifdef BENCHPIEZODLL_EXPORTS
#define BENCHPIEZO_API __declspec(dllexport)
#else
#define BENCHPIEZO_API __declspec(dllimport)
#endif

#include <OAIdl.h>

/** @defgroup BenchtopPiezoPDXC2 Benchtop Piezo PDXC2
 *  This section details the Structures and Functions relavent to the  @ref PDXC2_page "PDXC2"<br />
 *  For an example of how to connect to the device and perform simple operations use the following links:
 *  <list type=bullet>
 *    <item> \ref namespaces_pdxc2_ex_1 "Example of using the Thorlabs.MotionControl.Benchtop.Piezo.DLL from a C or C++ project."<br />
 *									  This requires the DLL to be dynamical linked. </item>
 *    <item> \ref namespaces_pdxc2_ex_2 "Example of using the Thorlabs.MotionControl.Benchtop.Piezo.DLL from a C# project"<br />
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


	/// <summary> Values that represent Travel Modes. </summary>
	enum MOT_TravelDirection : short
	{
		MOT_TravelDirectionDisabled = 0x00,///<Disabled or Undefined
		MOT_Forwards = 0x01,///<Move in a Forward direction
		MOT_Reverse = 0x02,///<Move in a Backward / Reverse direction
	};

	/// <summary> Values that represent Piezo Jog Mode. </summary>
	enum PZ_JogModes : unsigned __int16
	{
		/// <summary> An enum constant representing the jog continuous option. </summary>
		JogContinuous = 0x01,
		/// <summary> An enum constant representing the jog step option. </summary>
		JogStep = 0x02,
	};
	/// \endcond

	//<summary> PDXC2 Jog parameters. </summary>
	BENCHPIEZO_API typedef struct
	{
		/// <summary> The jog mode</summary>
		PZ_JogModes JogMode;
		/// <summary> Size of the open loop jog step. </summary>
		__int32 OpenLoopStepSize;
		/// <summary> The open loop jog rate. </summary>
		__int32 OpenLoopStepRate;
		/// <summary> The open loop jog acceleration. </summary>
		__int32 OpenLoopAcceleration;
		/// <summary> Size of the closed loop jog step. </summary>
		__int32 ClosedLoopStepSize;
		/// <summary> The closed loop speed. </summary>
		__int32 ClosedLoopSpeed;
		/// <summary> The closed loop jog acceleration. </summary>
		__int32 ClosedLoopAcceleration;
	} PDXC2_JogParameters;


	/// \cond NOT_MASTER
	/// <summary> Values that represent Output Amplitude parameters . </summary>
	enum PZ_AmpOutMode : unsigned __int16
	{
		/// <summary> use one output to control stage forward and backward.	</summary>
		BothDirections = 0x01,
		/// <summary> use one output to control stage forward,another to control backward.	</summary>
		OneOutputPerDirection = 0x02,
	};



	/// <summary> Amplifier board output parameters. </summary>
	struct PZ_AmpOutParameters
	{
		/// <summary> The output mode. </summary>
		PZ_AmpOutMode Mode;
		/// <summary> The forward amplitude level (a percentage). </summary>
		__int16 ForwardAmplitude;
		/// <summary> The reverse amplitude level (a percentage). </summary>
		__int16 ReverseAmplitude;
	};


	/// <summary> Structure containing stage axis parameters. </summary>
	/// <value> The stage parameters for one axis. </value>
	typedef struct
	{
		/// <summary> Two digit identifier of stage type. </summary>
		WORD stageID;
		/// <summary> 0 for x axis, 1 for y axis or 2 for z axis. </summary>
		WORD axisID;
		/// <summary> Catalogue part number. </summary>
		char partNumber[16];
		/// <summary> Eight digit serial number. </summary>
		DWORD serialNumber;
		/// <summary> Encoder counts per mm or degree. </summary>
		DWORD countsPerUnit;
		/// <summary> Minimum position in encoder counts usually 0. </summary>
		int minPosition;
		/// <summary> Maximum position in encoder counts. </summary>
		int maxPosition;
		/// <summary> Maximum acceleration in encoder counts per cycle per cycle. </summary>
		int maxAcceleration;
		/// <summary> Maximum deceleration in encoder counts per cycle per cycle. </summary>
		int maxDeceleration;
		/// <summary> Maximum speed in encoder counts per cycle. </summary>
		int maxVelocity;
		/// <summary> reserved. </summary>
		WORD reserved1;
		/// <summary> reserved. </summary>
		WORD reserved2;
		/// <summary> reserved. </summary>
		WORD reserved3;
		/// <summary> reserved. </summary>
		WORD reserved4;
		/// <summary> reserved. </summary>
		DWORD reserved5;
		/// <summary> reserved. </summary>
		DWORD reserved6;
		/// <summary> reserved. </summary>
		DWORD reserved7;
		/// <summary> reserved. </summary>
		DWORD reserved8;
	} PZ_StageAxisParameters;
	/// \endcond


	/// <summary> Values that represent Trigger Modes. </summary>
	enum PDXC2_TriggerModes : unsigned __int16
	{
		/// <summary> Manual mode, no external triggering. </summary>
		Manual = 0x00,
		/// <summary> Analog input with rising trigger edge mode. </summary>
		AnalogRising = 0x01,
		/// <summary> Analog input with falling trigger edge mode. </summary>
		AnalogFalling = 0x02,
		/// <summary> Fixed step distance with rising trigger edge mode. </summary>
		FixedStepRising = 0x03,
		/// <summary> Fixed step distance with falling trigger edge mode. </summary>
		FixedStepFalling = 0x04,
		/// <summary> Two Fixed positions with rising trigger edge mode. </summary>
		TwoPositionRising = 0x05,
		/// <summary> Two Fixed positions with falling trigger edge mode. </summary>
		TwoPositionFalling = 0x06,
	};



	/// <summary> PDXC2 Closed Loop Parameters. </summary>
	typedef struct
	{
		/// <summary> Reference Speed for the stage. </summary>
		unsigned __int32 RefSpeed;
		/// <summary> The proportional component. </summary>
		unsigned __int32 Proportional;
		/// <summary> The integral component. </summary>
		unsigned __int32 Integral;
		/// <summary> The differential component. </summary>
		unsigned __int32 Differential;
		/// <summary> The acceleration. </summary>
		unsigned __int32 Acceleration;
	} PDXC2_ClosedLoopParameters;

	/// <summary> PDXC2 Open Loop Move Parameters. </summary>
	typedef struct
	{
		/// <summary> The step size. Range 1 - 65535 </summary>
		unsigned __int32 StepSize;
	} PDXC2_OpenLoopMoveParameters;

	/// <summary> PDXC2 Status struct. </summary>
	typedef struct
	{
		/// <summary> The current position in nm </summary>
		__int32 Position;
		/// <summary> Unused data (structure is based on MGMSG_PZMOT_GET_STATUSUPDATE) </summary>
		__int32 Unused;
		/// <summary> Status Bits </summary>
		__int32 StatusBits;

	} PDXC2_Status;

	/// <summary> PDXC2 Trigger Params Struct. </summary>
	typedef struct
	{
		/// <summary> The rising edge fixed step in nm </summary>
		__int32 RiseFixedStep;
		/// <summary>  The falling edge fixed step in nm </summary>
		__int32 FallFixedStep;
		/// <summary> The rising edge fixed position 1</summary>
		__int32 RisePosition1;
		/// <summary> The falling edge fixed position 1</summary>
		__int32 FallPosition1;
		/// <summary> The rising edge fixed position 2</summary>
		__int32 RisePosition2;
		/// <summary> The falling edge fixed position 2</summary>
		__int32 FallPosition2;
		/// <summary> The analog input gain</summary>
		float AnalogInGain;
		/// <summary> The analog input offset</summary>
		float AnalogInOffset;
		/// <summary> The analog output gain</summary>
		float AnalogOutGain;
		/// <summary> The analog output offset</summary>
		float AnalogOutOffset;
	} PDXC2_TriggerParams;


#pragma pack()

	/// <summary> Build the DeviceList. </summary>
	/// <remarks> This function builds an internal collection of all devices found on the USB that are not currently open. <br />
	/// 		  NOTE, if a device is open, it will not appear in the list until the device has been closed. <br />
	///			  If you are attempting to connect to a device using TCP/IP you will need to call this method twice
	///			  with a delay of a few seconds between calls to give time for the list of TCP/IP connected devices to be built.
	///</remarks>
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
	BENCHPIEZO_API short __cdecl TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int* typeIDs, int length);

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
	BENCHPIEZO_API short __cdecl TLI_GetDeviceListExt(char* receiveBuffer, DWORD sizeOfBuffer);

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
	BENCHPIEZO_API short __cdecl TLI_GetDeviceListByTypeExt(char* receiveBuffer, DWORD sizeOfBuffer, int typeID);

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
	BENCHPIEZO_API short __cdecl TLI_GetDeviceListByTypesExt(char* receiveBuffer, DWORD sizeOfBuffer, int* typeIDs, int length);

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
	BENCHPIEZO_API short __cdecl TLI_GetDeviceInfo(char const* serialNo, TLI_DeviceInfo* info);

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

	/// <summary> Scans a range of addresses and returns a list of the ip addresses of Thorlabs devices found. </summary>
	/// <param name="startIPAddress"> The start IP address. </param>
	/// <param name="endIPAddress">	 The end IP address. </param>
	/// <param name="portNo">	 The port no, usually 40303. </param>
	/// <param name="openTimeout">	The timeout used when attempting to open a connection. </param>
	/// <param name="foundAddressesBuffer">  The character array to receive a comma seperated list of Thorlabs IP adresses. </param>
	/// <param name="sizeOfBuffer">  The size of the Buffer. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl TLI_ScanEthernetRange(char* startIPAddress, char* endIPAddress, int portNo, int openTimeout, char* foundAddressesBuffer, DWORD sizeOfBuffer);


	/// <summary> Open the device for communications. </summary>
	/// <param name="serialNo">	The serial no of the device to be connected. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// 		  \include CodeSnippet_connectionN.cpp
	/// <seealso cref="PDXC2_Close(char const * serialNo)" />
	BENCHPIEZO_API short __cdecl PDXC2_Open(char const* serialNo);

	/// <summary> Disconnect and close the device. </summary>
	/// <param name="serialNo">	The serial no of the device to be disconnected. </param>
	/// 		  \include CodeSnippet_connectionN.cpp
	/// <seealso cref="PDXC2_Open(char const * serialNo)" />
	BENCHPIEZO_API void __cdecl PDXC2_Close(char const* serialNo);

	/// <summary>	Check connection. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> true if the USB is listed by the ftdi controller</returns>
	/// \include CodeSnippet_CheckConnection.cpp
	BENCHPIEZO_API bool __cdecl PDXC2_CheckConnection(char const* serialNo);

	/// <summary> Sends a command to the device to make it identify iteself. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	BENCHPIEZO_API void __cdecl PDXC2_Identify(char const* serialNo);

	/// <summary> Tells the device that it is being disconnected. </summary>
	/// <remarks> This does not disconnect the communications.<br />
	/// 		  To disconnect the communications, call the <see cref="PDXC2_Close(char const * serialNo)" /> function. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PDXC2_Disconnect(char const* serialNo);



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
	BENCHPIEZO_API short __cdecl PDXC2_GetHardwareInfo(char const* serialNo, char* modelNo, DWORD sizeOfModelNo, WORD* type, WORD* numChannels,
		char* notes, DWORD sizeOfNotes, DWORD* firmwareVersion, WORD* hardwareVersion, WORD* modificationState);

	/// <summary> Gets the hardware information in a block. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="hardwareInfo"> Address of a TLI_HardwareInformation structure to receive the hardware information. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// 		  \include CodeSnippet_identify.cpp
	BENCHPIEZO_API short __cdecl PDXC2_GetHardwareInfoBlock(char const* serialNo, TLI_HardwareInformation* hardwareInfo);


	/// <summary> Gets version number of the device firmware. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device firmware version number made up of 4 byte parts. </returns>
	/// 		  \include CodeSnippet_identify.cpp
	BENCHPIEZO_API DWORD __cdecl PDXC2_GetFirmwareVersion(char const* serialNo);

	/// <summary> Gets version number of the device software. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device software version number made up of 4 byte parts. </returns>
	/// 		  \include CodeSnippet_identify.cpp
	BENCHPIEZO_API DWORD __cdecl PDXC2_GetSoftwareVersion(char const* serialNo);

	/// <summary> Update device with stored settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// 		  \include CodeSnippet_connection1.cpp
	BENCHPIEZO_API bool __cdecl PDXC2_LoadSettings(char const* serialNo);

	/// <summary> Update device with named settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="settingsName"> Name of settings stored away from device. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	///             \include CodeSnippet_connection1.cpp
	BENCHPIEZO_API bool __cdecl PDXC2_LoadNamedSettings(char const* serialNo, char const* settingsName);

	/// <summary>	Persist device settings to device. </summary>
	/// <param name="serialNo">	The serial no. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	BENCHPIEZO_API bool __cdecl PDXC2_PersistSettings(char const* serialNo);

	/// <summary> Disable the channel so that motor can be moved by hand. </summary>
	/// <remarks> When disabled power is removed from the actuator.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PDXC2_EnableChannel(char const * serialNo, short channel)" />
	BENCHPIEZO_API short __cdecl PDXC2_Disable(char const* serialNo);

	/// <summary> Enable channel for computer control. </summary>
	/// <remarks> When enabled power is applied to the actuator so it is fixed in position.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PDXC2_DisableChannel(char const * serialNo, short channel)" />
	BENCHPIEZO_API short __cdecl PDXC2_Enable(char const* serialNo);


	/// <summary> Registers a callback on the message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="functionPointer"> A function pointer to be called whenever messages are received. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PDXC2_RegisterMessageCallback(char const* serialNo, void (*functionPointer)());

	/// <summary> Gets the MessageQueue size. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> number of messages in the queue. </returns>
	BENCHPIEZO_API int __cdecl PDXC2_MessageQueueSize(char const* serialNo);

	/// <summary> Clears the device message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PDXC2_ClearMessageQueue(char const* serialNo);

	/// <summary> Get the next MessageQueue item if it is available. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> Address of the WORD to receive the message type. </param>
	/// <param name="messageID"> Address of the WORD to receive themessage ID. </param>
	/// <param name="messageData"> Address of the DWORD to receive the messageData. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	BENCHPIEZO_API bool __cdecl PDXC2_GetNextMessage(char const* serialNo, WORD* messageType, WORD* messageID, DWORD* messageData);

	/// <summary> Get the next MessageQueue item if it is available. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> Address of the WORD to receive the message type. </param>
	/// <param name="messageID"> Address of the WORD to receive themessage ID. </param>
	/// <param name="messageData"> Address of the DWORD to receive the messageData. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	BENCHPIEZO_API bool __cdecl PDXC2_WaitForMessage(char const* serialNo, WORD* messageType, WORD* messageID, DWORD* messageData);

	/// <summary> Starts the internal polling loop which continuously requests position and status. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="milliseconds">The milliseconds polling rate. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="PDXC2_StopPolling(char const * serialNo)" />
	/// <seealso cref="PDXC2_PollingDuration(char const * serialNo)" />
	/// <seealso cref="PDXC2_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="PDXC2_RequestPosition(char const * serialNo)" />
	/// \include CodeSnippet_connectionN.cpp
	BENCHPIEZO_API bool __cdecl PDXC2_StartPolling(char const* serialNo, int milliseconds);

	/// <summary> Gets the polling loop duration. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The time between polls in milliseconds or 0 if polling is not active. </returns>
	/// <seealso cref="PDXC2_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="PDXC2_StopPolling(char const * serialNo)" />
	/// \include CodeSnippet_connectionN.cpp
	BENCHPIEZO_API long __cdecl PDXC2_PollingDuration(char const* serialNo);

	/// <summary> Stops the internal polling loop. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <seealso cref="PDXC2_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="PDXC2_PollingDuration(char const * serialNo)" />
	/// \include CodeSnippet_connectionN.cpp
	BENCHPIEZO_API void __cdecl PDXC2_StopPolling(char const* serialNo);

	/// <summary> Gets the time in milliseconds since tha last message was received from the device. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="lastUpdateTimeMS"> The time since the last message was received in milliseconds. </param>
	/// <returns> True if monitoring is enabled otherwize False. </returns>
	/// <seealso cref="PDXC2_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// <seealso cref="PDXC2_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	BENCHPIEZO_API bool __cdecl PDXC2_TimeSinceLastMsgReceived(char const* serialNo, __int64& lastUpdateTimeMS);

	/// <summary> Enables the last message monitoring timer. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="enable"> True to enable monitoring otherwise False to disable. </param>
	/// <param name="lastMsgTimeout"> The last message error timeout in ms. 0 to disable. </param>
	/// <seealso cref="PDXC2_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="PDXC2_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	BENCHPIEZO_API void __cdecl PDXC2_EnableLastMsgTimer(char const* serialNo, bool enable, __int32 lastMsgTimeout);

	/// <summary> Queries if the time since the last message has exceeded the lastMsgTimeout set by <see cref="PDXC2_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )"/>. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> True if last message timer has elapsed, False if monitoring is not enabled or if time of last message received is less than lastMsgTimeout. </returns>
	/// <seealso cref="PDXC2_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="PDXC2_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	BENCHPIEZO_API bool __cdecl PDXC2_HasLastMsgTimerOverrun(char const* serialNo);

	/// <summary> Requests that all settings are download from device. </summary>
	/// <remarks> This function requests that the device upload all it's settings to the DLL.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	BENCHPIEZO_API short __cdecl PDXC2_RequestSettings(char const* serialNo);

	/// <summary> Requests the status bits and position. </summary>
	/// <remarks> This needs to be called to get the device to send it's current position and status bits.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="PDXC2_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="PDXC2_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="PDXC2_GetPosition(char const * serialNo)" />
	/// <seealso cref="PDXC2_GetStatusBits(char const * serialNo)" />
	/// <seealso cref="PDXC2_StartPolling(char const * serialNo, int milliseconds)" />
	BENCHPIEZO_API short __cdecl PDXC2_RequestStatus(char const* serialNo);

	/// <summary> Request the status bits which identify the current device state. </summary>
	/// <remarks> This needs to be called to get the device to send it's current status bits.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="PDXC2_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="PDXC2_GetStatusBits(char const * serialNo)" />
	/// <seealso cref="PDXC2_StartPolling(char const * serialNo, int milliseconds)" />
	BENCHPIEZO_API short __cdecl PDXC2_RequestStatusBits(char const* serialNo);

	/// <summary>Get the current status bits. </summary>
		/// <remarks> This returns the latest status bits received from the device.<br />
		/// 		  To get new status bits, use <see cref="PDXC2_RequestStatusBits(char const * serialNo)" /> <br />
		///			  or use <see cref="BPC_RequestStatus(char const * serialNo)" />
		/// 		  or use the polling functions, <see cref="PDXC2_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
		/// <param name="serialNo">	The device serial no. </param>
		/// <returns>	The status bits from the device <list type=table>
		///				<item><term>0x00000010</term><term>In motion, moving forward (CW).</term></item>
		///				<item><term>0x00000020</term><term>In motion, moving backward (CCW).</term></item>
		///				<item><term>0x00000200</term><term>in motion, homing.</term></item>
		///				<item><term>0x00000400</term><term>Homed.</term></item>
		///				<item><term>0x00000800</term><term>Closed loop working state.</term></item>
		///				<item><term>0x00200000</term><term>Acquiring pulse parameters.</term></item>
		///				<item><term>0x00400000</term><term>Pulse parameters acquired.</term></item>
		///				<item><term>0x00800000</term><term>Error - device in wrong mode.</term></item>
		///				<item><term>0x01000000</term><term>Error - excessive current.</term></item>
		///				<item><term>0x02000000</term><term>Error - excessive temperature.</term></item>
		///				<item><term>0x04000000</term><term>Error - abnormal stage movement.</term></item>
		///				<item><term>0x08000000</term><term>Error - wrong stage detected.</term></item>
		///				<item><term>0x40000000</term><term>Error.</term></item>
		/// 		  </list> 
		/// <seealso cref="PDXC2_RequestStatusBits(char const * serialNo)" />
		/// <seealso cref="PDXC2_RequestStatus(char const * serialNo)" />
		/// <seealso cref="PDXC2_StartPolling(char const * serialNo, int milliseconds)" />
	BENCHPIEZO_API DWORD __cdecl PDXC2_GetStatusBits(char const* serialNo);

	/// <summary>	Resets all parameters to power-up values. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PDXC2_ResetParameters(char const* serialNo);


	/// <summary> Gets the Position Control Mode. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The control mode <list type=table>
	///				<item><term>Open Loop</term><term>1</term></item>
	///				<item><term>Closed Loop</term><term>2</term></item>
	/// 		  </list> </returns>
	/// <seealso cref="PDXC2_RequestPositionControlMode(char const * serialNo)" />
	/// <seealso cref="PDXC2_SetPositionControlMode(char const * serialNo, PZ_ControlModeTypes mode)" />
	BENCHPIEZO_API PZ_ControlModeTypes __cdecl PDXC2_GetPositionControlMode(char const* serialNo);

	/// <summary> Sets the Position Control Mode. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="mode"> The control mode <list type=table>
	///				<item><term>Open Loop</term><term>1</term></item>
	///				<item><term>Closed Loop</term><term>2</term></item>
	/// 		  </list>. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="PDXC2_GetPositionControlMode(char const * serialNo)" />
	/// <seealso cref="PDXC2_SetPositionControlMode(char const * serialNo, PZ_ControlModeTypes mode)" />
	BENCHPIEZO_API bool __cdecl PDXC2_RequestPositionControlMode(char const* serialNo);

	/// <summary> Sets the Position Control Mode. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="mode"> The control mode <list type=table>
	///				<item><term>Open Loop</term><term>1</term></item>
	///				<item><term>Closed Loop</term><term>2</term></item>
	/// 		  </list>. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="PDXC2_RequestPositionControlMode(char const * serialNo)" />
	/// <seealso cref="PDXC2_GetPositionControlMode(char const * serialNo)" />
	BENCHPIEZO_API short __cdecl PDXC2_SetPositionControlMode(char const* serialNo, PZ_ControlModeTypes mode);


	/// <summary> Sets the current position to the Home position (Position = 0). </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PDXC2_Home(char const* serialNo);

	/// <summary> Move jog. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="jogDirection">	The jog direction. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PDXC2_MoveJog(char const* serialNo, MOT_TravelDirection jogDirection);

	/// <summary> Move start. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PDXC2_MoveStart(char const* serialNo);

	/// <summary> Move stop. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PDXC2_MoveStop(char const* serialNo);

	/// <summary> Start pulse parameter acquistion. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PDXC2_PulseParamsAcquireStart(char const* serialNo);

	/// <summary>	Request the closed loop  parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PDXC2_RequestClosedLoopParams(char const* serialNo);

	/// <summary> Sets the closed loop  parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="params"> Options for controlling closed loop parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PDXC2_SetClosedLoopParams(char const* serialNo, PDXC2_ClosedLoopParameters* params);

	/// <summary> Gets the closed loop  parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="params"> Options for controlling closed loop parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl  PDXC2_GetClosedLoopParams(char const* serialNo, PDXC2_ClosedLoopParameters* params);

	/// <summary>	Request the closed loop target position. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl  PDXC2_RequestClosedLoopTarget(char const* serialNo);

	/// <summary> Sets the closed loop target position. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="target"> The target in nm units. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl  PDXC2_SetClosedLoopTarget(char const* serialNo, int target);

	/// <summary> Gets the closed loop target position. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The target in nm units. </returns>
	BENCHPIEZO_API int __cdecl  PDXC2_GetClosedLoopTarget(char const* serialNo);

	/// <summary>	Request the open loop move parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl  PDXC2_RequestOpenLoopMoveParams(char const* serialNo);

	/// <summary> Sets the open loop move parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="params"> Options for controlling open loop move parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl  PDXC2_SetOpenLoopMoveParams(char const* serialNo, PDXC2_OpenLoopMoveParameters* params);

	/// <summary> Gets the open loop move   parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="params"> Options for controlling open loop move parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl  PDXC2_GetOpenLoopMoveParams(char const* serialNo, PDXC2_OpenLoopMoveParameters* params);

	/// <summary>	Request the jog  parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl  PDXC2_RequestJogParams(char const* serialNo);

	/// <summary> Sets the jog  parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="params"> Options for controlling jog parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl  PDXC2_SetJogParams(char const* serialNo, PDXC2_JogParameters* params);

	/// <summary> Gets the jog  parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="params"> Options for controlling jog parameters. </param>
	/// <returns> The Options for controlling joge parameters. </returns>
	BENCHPIEZO_API short __cdecl  PDXC2_GetJogParams(char const* serialNo, PDXC2_JogParameters* params);

	/// <summary>	Request the amplifier output parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl  PDXC2_RequestAmpOutParams(char const* serialNo);

	/// <summary> Sets the amplifier output parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="params"> Options for controlling amplifier output parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PDXC2_SetAmpOutParams(char const* serialNo, PZ_AmpOutParameters* params);

	/// <summary> Gets the amplifier output parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="params"> Options for controlling amplifier output parameters. </param>
	/// <returns> The Options for controlling amplifier output parameters. </returns>
	BENCHPIEZO_API short __cdecl PDXC2_GetAmpOutParams(char const* serialNo, PZ_AmpOutParameters* params);

	/// <summary>	Request the abnormal mode detection state. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl  PDXC2_RequestAbnormalMoveDetectionEnabled(char const* serialNo);

	/// <summary> Sets the abnormal mode detection state. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="isEnabled"> True to enable, false to disable. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl  PDXC2_SetAbnormalMoveDetectionEnabled(char const* serialNo, bool isEnabled);

	/// <summary> Gets the abnormal mode detection state. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The abnormal mode detection state. </returns>
	BENCHPIEZO_API bool __cdecl PDXC2_GetAbnormalMoveDetectionEnabled(char const* serialNo);

	/// <summary>	Request the external trigger mode. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl  PDXC2_RequestExternalTriggerConfig(char const* serialNo);

	/// <summary> Sets the external trigger mode. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="mode"> The trigger mode. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl  PDXC2_SetExternalTriggerConfig(char const* serialNo, PDXC2_TriggerModes mode);

	/// <summary> Gets the external trigger mode. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The Trigger Mode </returns>
	BENCHPIEZO_API PDXC2_TriggerModes __cdecl  PDXC2_GetExternalTriggerConfig(char const* serialNo);

	/// <summary>	Request the external trigger parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PDXC2_RequestExternalTriggerParams(char const* serialNo);

	/// <summary> Sets the external trigger parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="params"> The trigger parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PDXC2_SetExternalTriggerParams(char const* serialNo, PDXC2_TriggerParams* params);

	/// <summary> Gets the external trigger parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="params"> The trigger parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PDXC2_GetExternalTriggerParams(char const* serialNo, PDXC2_TriggerParams* params);

	/// <summary>	Request the external trigger target. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PDXC2_RequestExternalTriggerTarget(char const* serialNo);

	/// <summary> Gets the external trigger target. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The trigger target. </returns>
	BENCHPIEZO_API int __cdecl  PDXC2_GetExternalTriggerTarget(char const* serialNo);

	/// <summary>	Requests the stage axis parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PDXC2_RequestStageAxisParams(char const* serialNo);

	/// <summary> Gets the stage axis parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="params"> The stage axis parameters. </param>
	/// <returns>	The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHPIEZO_API short __cdecl PDXC2_GetStageAxisParams(char const* serialNo, PZ_StageAxisParameters* params);

	/// <summary>
	/// Requests the current position.
	///  </summary>
	/// <param name="serialNo">The device serial no.</param>
	/// <returns></returns>
	BENCHPIEZO_API short __cdecl PDXC2_RequestPosition(char const* serialNo);
	
	/// <summary>
	/// Get the current position. 
	/// </summary>
	/// <param name="serialNo">The device serial no.</param>
	/// <param name="position">The device position. In closed loop mode the position value is in nanometres, in open loop mode the value is in steps.</param>
	/// <returns></returns>
	BENCHPIEZO_API short __cdecl PDXC2_GetPosition(char const* serialNo, __int32* position);
}

/** @} */ // BenchtopPiezoPDXC2
