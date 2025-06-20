// summary:	Declares the functions class
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the POLARIZERDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// POLARIZERDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef POLARIZERDLL_EXPORTS
#define POLARIZERDLL_API __declspec(dllexport)
#else
#define POLARIZERDLL_API __declspec(dllimport)
#endif

#include <OaIdl.h>

#pragma once

/** @defgroup Polarizer Polarizer
 *  This section details the Structures and Functions relavent to the  @ref MPCx20_page "Polarization Controller"<br />
 *  For an example of how to connect to the device and perform simple operations use the following links:
 *  <list type=bullet>
 *    <item> \ref namespaces_mpc_x20_ex_1 "Example of using the Thorlabs.MotionControl.Polarizer.DLL from a C or C++ project."<br />
 *									  This requires the DLL to be dynamical linked. </item>
 *    <item> \ref namespaces_mpc_x20_ex_2 "Example of using the Thorlabs.MotionControl.Polarizer.DLL from a C# project"<br />
 *									  This uses Marshalling to load and access the C DLL. </item>
 *  </list>
 *  The Thorlabs.MotionControl.Polarizer.DLL requires the following DLLs
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

	/// <summary> Values that represent POL_Paddles. </summary>
	typedef enum POL_Paddles : unsigned __int16
	{
		/// <summary> An enum constant representing the paddle 1 option. </summary>
		paddle1 = 1,
		/// <summary> An enum constant representing the paddle 2 option. </summary>
		paddle2,
		/// <summary> An enum constant representing the paddle 3 option. </summary>
		paddle3,
	} POL_Paddles;

	/// <summary> Values that represent POL_Paddles. </summary>
	typedef enum POL_PaddleBits : unsigned short
	{
		/// <summary> An enum constant representing no paddles option. </summary>
		None = 0x0,

		/// <summary> An enum constant representing the paddle 1 option. </summary>
		PaddleBit1=0x01,
		/// <summary> An enum constant representing the paddle 2 option. </summary>
		PaddleBit2=0x02,
		/// <summary> An enum constant representing the paddle 3 option. </summary>
		PaddleBit4=0x04,

		/// <summary> An enum constant representing all paddles option. </summary>
		AllPaddles = 0x07,
	} POL_PaddleBits;

	/// <summary> parameters for the polarizer. </summary>
	typedef struct PolarizerParameters
	{
		/// <summary> The velocity. </summary>
		unsigned short Velocity;
		/// <summary> The home position. </summary>
		double HomePosition;
		/// <summary> Size of the jog step 1. </summary>
		double JogSize1;
		/// <summary> Size of the jog step 2. </summary>
		double JogSize2;
		/// <summary> Size of the jog step 3. </summary>
		double JogSize3;
	} PolarizerParameters;

	/// <summary> Values that represent Travel Modes. </summary>
	typedef enum MOT_TravelDirection : short
	{
		MOT_TravelDirectionDisabled = 0x00,///<Disabled or Undefined
		MOT_Forwards = 0x01,///<Move in a Forward direction
		MOT_Reverse = 0x02,///<Move in a Backward / Reverse direction
	} MOT_TravelDirection;

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
		/// <summary> Defines the number of paddles available in this device. </summary>
		short maxPaddles;
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
		/// <summary> The number of paddles the device provides. </summary>
		short numChannels;
	} TLI_HardwareInformation;

	/// <summary> Polarizer IO operations. </summary>
	typedef enum MPC_IOModes : WORD
	{
		/// <summary> Input Mode - Polarizer toggles when signalled (See <see cref="MPC_SignalModes" />). </summary>
		MPC_ToggleOnPositiveEdge = 0x01, 
		/// <summary> Input Mode - Polarizer goes to position when signalled (See <see cref="MPC_SignalModes" />) </summary>
		MPC_SetPositionOnPositiveEdge = 0x02, 
		/// <summary> Output Mode - Output signal set to match position, where 2 = Hi, 1 = Lo. </summary>
		MPC_OutputHighAtSetPosition = 0x04, 
		/// <summary> Output Mode - Output signal high when Polarizer is moving. </summary>
		MPC_OutputHighWhemMoving = 0x08, 
	} MPC_IOModes;

	/// <summary> Polarizer IO operations. </summary>
	typedef enum MPC_SignalModes : WORD
	{
		/// <summary> Signal is raised when Button Pressed i.e. Hi to Lo. Action taken is defined by <see cref="MPC_IOModes" />. </summary>
		MPC_InputButton = 0x01, 
		/// <summary> Signal is raised on on rising edge Lo to Hi. Action taken is defined by <see cref="MPC_IOModes" />. </summary>
		MPC_InputLogic = 0x02, 
		/// <summary> when set will swap Position 1 and 2. </summary>
		MPC_InputSwap = 0x04, 
		/// <summary> Output is set to either be hi when flipper at Position 2 or flipper is moving (see <see cref="MPC_IOModes" />). </summary>
		MPC_OutputLevel = 0x10, 
		/// <summary> Output is set to pulse when flipper operates, either when flipper reaches Position or flipper starts moving (see <see cref="MPC_IOModes" />). </summary>
		MPC_OutputPulse = 0x20, 
		/// <summary> when set will swap output logic levels. </summary>
		MPC_OutputSwap = 0x40, 
	} MPC_SignalModes;

	/// <summary> Structure containing settings specific to filter flipper input / output. </summary>
	typedef struct MPC_IOSettings
	{
		/// <summary> Time taken to get from one position to other in milliseconds.<br />
		/// 		  Range 300 to 2800 ms. </summary>
		unsigned int transitTime;
		/// <summary> Value derived from transition time in ADC units. </summary>
		unsigned int ADCspeedValue;
		/// <summary> I/O 1 Operating Mode
		/// 		  <list type=table>
		///				<item><term>Input Mode - Polarizer toggles when signalled (See <see cref="MPC_SignalModes" />)</term><term>0x01</term></item>
		///				<item><term>Input Mode - Polarizer goes to position when signalled (See <see cref="MPC_SignalModes" />)</term><term>0x02</term></item>
		///				<item><term>Output Mode - Output signal set to match position, where 2 = Hi, 1 = Lo</term><term>0x04</term></item>
		///				<item><term>Output Mode - Output signal high when Polarizer is moving</term><term>0x08</term></item>
		/// 		  </list> </summary>
		MPC_IOModes digIO1OperMode;
		/// <summary> I/O 1 Signal Mode
		/// 		  <list type=table>
		///				<item><term>Signal is raised when Button Pressed i.e. Hi to Lo. Action taken is defined by <see cref="MPC_IOModes" /></term><term>0x01</term></item>
		///				<item><term>Signal is raised on on rising edge Lo to Hi. Action taken is defined by <see cref="MPC_IOModes" /></term><term>0x02</term></item>
		///				<item><term>Toggle Positions, when set will swap Position 1 and 2</term><term>0x04</term></item>
		///				<item><term>Output is set to either be hi when flipper at Position 2 or flipper is moving (see <see cref="MPC_IOModes" />)</term><term>0x10</term></item>
		///				<item><term>Output is set to pulse when flipper operates, either when flipper reaches Position or flipper starts moving (see <see cref="MPC_IOModes" />)</term><term>0x20</term></item>
		///				<item><term>Toggle output levels, when set will swap output logic levels</term><term>0x40</term></item>
		/// 		  </list> </summary>
		MPC_SignalModes digIO1SignalMode;
		/// <summary> Digital IO 1 pulse width in milliseconds,<br />
		/// 		  Range 10 to 200 ms. </summary>
		unsigned int digIO1PulseWidth;
		/// <summary> I/O 2 Operating Mode
		/// 		  <list type=table>
		///				<item><term>Input Mode - Polarizer toggles when signalled (See <see cref="MPC_SignalModes" />)</term><term>0x01</term></item>
		///				<item><term>Input Mode - Polarizer goes to position when signalled (See <see cref="MPC_SignalModes" />)</term><term>0x02</term></item>
		///				<item><term>Output Mode - Output signal set to match position, where 2 = Hi, 1 = Lo</term><term>0x04</term></item>
		///				<item><term>Output Mode - Output signal high when Polarizer is moving</term><term>0x08</term></item>
		/// 		  </list> </summary>
		MPC_IOModes digIO2OperMode;
		/// <summary> I/O 2 Signal Mode
		/// 		  <list type=table>
		///				<item><term>Signal is raised when Button Pressed i.e. Hi to Lo. Action taken is defined by <see cref="MPC_IOModes" /></term><term>0x01</term></item>
		///				<item><term>Signal is raised on on rising edge Lo to Hi. Action taken is defined by <see cref="MPC_IOModes" /></term><term>0x02</term></item>
		///				<item><term>Toggle Positions, when set will swap Position 1 and 2</term><term>0x04</term></item>
		///				<item><term>Output is set to either be hi when flipper at Position 2 or flipper is moving (see <see cref="MPC_IOModes" />)</term><term>0x10</term></item>
		///				<item><term>Output is set to pulse when flipper operates, either when flipper reaches Position or flipper starts moving (see <see cref="MPC_IOModes" />)</term><term>0x20</term></item>
		///				<item><term>Toggle output levels, when set will swap output logic levels</term><term>0x40</term></item>
		/// 		  </list> </summary>
		MPC_SignalModes digIO2SignalMode;
		/// <summary> Digital IO 2 pulse width in milliseconds,<br />
		/// 		  Range 10 to 200 ms. </summary>
		unsigned int digIO2PulseWidth;
		/// <summary> Not used. </summary>
		int reserved1;
		/// <summary> Not used. </summary>
		unsigned int reserved2;
	} MPC_IOSettings;

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
	POLARIZERDLL_API short __cdecl TLI_BuildDeviceList(void);

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
	POLARIZERDLL_API short __cdecl TLI_GetDeviceListSize();

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
	POLARIZERDLL_API short __cdecl TLI_GetDeviceList(SAFEARRAY** stringsReceiver);

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
	POLARIZERDLL_API short __cdecl TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID);

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
	POLARIZERDLL_API short __cdecl TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length);

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
	POLARIZERDLL_API short __cdecl TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer);

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
	POLARIZERDLL_API short __cdecl TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID);

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
	POLARIZERDLL_API short __cdecl TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length);

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
	POLARIZERDLL_API short __cdecl TLI_GetDeviceInfo(char const * serialNo, TLI_DeviceInfo *info);

	/// <summary> Initialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <remarks> Call TLI_InitializeSimulations before TLI_BuildDeviceList at the start of the program to make a connection to the simulation manager.<Br />
	/// 		  Any devices configured in the simulation manager will become visible TLI_BuildDeviceList is called and can be accessed using TLI_GetDeviceList.<Br />
	/// 		  Call TLI_InitializeSimulations at the end of the program to release the simulator.  </remarks>
	/// <seealso cref="TLI_UninitializeSimulations()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	POLARIZERDLL_API void __cdecl TLI_InitializeSimulations();

	/// <summary> Uninitialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <seealso cref="TLI_InitializeSimulations()" />
	POLARIZERDLL_API void __cdecl TLI_UninitializeSimulations();

	/// <summary> Open the device for communications. </summary>
	/// <param name="serialNo">	The serial no of the device to be connected. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="MPC_Close(char const * serialNo)" />
	POLARIZERDLL_API short __cdecl MPC_Open(char const * serialNo);

	/// <summary> Disconnect and close the device. </summary>
	/// <param name="serialNo">	The serial no of the device to be disconnected. </param>
    /// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="MPC_Open(char const * serialNo)" />
	POLARIZERDLL_API void __cdecl MPC_Close(char const * serialNo);

	/// <summary>	Check connection. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> true if the USB is listed by the ftdi controller</returns>
	/// \include CodeSnippet_CheckConnection.cpp
	POLARIZERDLL_API bool __cdecl MPC_CheckConnection(char const * serialNo);

	/// <summary> Sends a command to the device to make it identify iteself. </summary>
	/// <param name="serialNo">	The device serial no. </param>
    /// 		  \include CodeSnippet_identify.cpp
	POLARIZERDLL_API void __cdecl MPC_Identify(char const * serialNo);

	/// <summary> Gets the hardware information from the device. </summary>
	/// <param name="serialNo">		    The device serial no. </param>
	/// <param name="modelNo">		    Address of a buffer to receive the model number string. Minimum 8 characters </param>
	/// <param name="sizeOfModelNo">	    The size of the model number buffer, minimum of 8 characters. </param>
	/// <param name="type">		    Address of a WORD to receive the hardware type number. </param>
	/// <param name="numchannels">	    Address of a short to receive the  number of paddles. </param>
	/// <param name="notes">		    Address of a buffer to receive the notes describing the device. </param>
	/// <param name="sizeOfNotes">		    The size of the notes buffer, minimum of 48 characters. </param>
	/// <param name="firmwareVersion"> Address of a DWORD to receive the  firmware version number made up of 4 byte parts. </param>
	/// <param name="hardwareVersion"> Address of a WORD to receive the  hardware version number. </param>
	/// <param name="modificationState">	    Address of a WORD to receive the hardware modification state number. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	POLARIZERDLL_API short __cdecl MPC_GetHardwareInfo(char const * serialNo, char * modelNo, DWORD sizeOfModelNo, WORD * type, WORD * numchannels, 
													   char * notes, DWORD sizeOfNotes, DWORD * firmwareVersion, WORD * hardwareVersion, WORD * modificationState);

	/// <summary> Gets version number of firmware. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The firmware version number made up of 4 byte parts. </returns>
	POLARIZERDLL_API DWORD __cdecl MPC_GetFirmwareVersion(char const * serialNo);

	/// <summary> Gets version number of the device software. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device software version number made up of 4 byte parts. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	POLARIZERDLL_API DWORD __cdecl MPC_GetSoftwareVersion(char const * serialNo);

	/// <summary> Update device with stored settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
    /// 		  \include CodeSnippet_connection1.cpp
	POLARIZERDLL_API bool __cdecl MPC_LoadSettings(char const * serialNo);

	/// <summary> Update device with named settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="settingsName"> Name of settings stored away from device. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	///             \include CodeSnippet_connection1.cpp
	POLARIZERDLL_API bool __cdecl MPC_LoadNamedSettings(char const * serialNo, char const *settingsName);

	/// <summary> Persist the devices current settings. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	POLARIZERDLL_API bool __cdecl MPC_PersistSettings(char const * serialNo);

	/// <summary> Mpc reset parameters. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> True if it succeeds, false if it fails. </returns>
	POLARIZERDLL_API bool __cdecl MPC_ResetParameters(char const * serialNo);

	/// <summary> Get number of polarizer paddles. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The number of polarizer paddles. </returns>
	/// <seealso cref="MPC_GetMaxTravel(char const * serialNo)" />
	/// <seealso cref="MPC_GetStepsPerDegree" />
    /// 		  \include CodeSnippet_move.cpp
	POLARIZERDLL_API int __cdecl MPC_GetPaddleCount(char const * serialNo);

	/// <summary> Gets enabled paddles. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The enabled paddles. </returns>
	POLARIZERDLL_API POL_PaddleBits __cdecl MPC_GetEnabledPaddles(char const * serialNo);

	/// <summary> Queries if a paddle is enabled. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="paddle"> The Paddle. </param>
	/// <returns> True if the paddle is enabled, false if not. </returns>
	POLARIZERDLL_API bool __cdecl MPC_IsPaddleEnabled(char const * serialNo, POL_Paddles paddle);

	/// <summary> Enables the specified paddles. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="paddles">	A bit mask of the paddles to be enabled. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if move successfully started. </returns>
	POLARIZERDLL_API int __cdecl MPC_SetEnabledPaddles(char const * serialNo, POL_PaddleBits paddles);

	/// <summary> Get the maximum travel in encoder steps. </summary>
	/// <remarks> The GetMaxTravel function will get the maximum position reachable in encoder steps by the device. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The number of positions in encoder steps. </returns>
	/// <seealso cref="MPC_GetPaddleCount(char const * serialNo)" />
	/// <seealso cref="MPC_GetStepsPerDegree(char const * serialNo)" />
    /// 		  \include CodeSnippet_move.cpp
	POLARIZERDLL_API double __cdecl MPC_GetMaxTravel(char const * serialNo);

	/// <summary> Get the Ratio of encoder steps per degree. </summary>
	/// <remarks> The StepsPerDegree function will get the ratio of encoder steps to degrees. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The ratio of encoder steps per degree. </returns>
	/// <seealso cref="MPC_GetPaddleCount(char const * serialNo)" />
	/// <seealso cref="MPC_GetMaxTravel(char const * serialNo)" />
    /// 		  \include CodeSnippet_move.cpp
	POLARIZERDLL_API double __cdecl MPC_GetStepsPerDegree(char const * serialNo);

	/// <summary> Home the device. </summary>
	/// <remarks> Homing the device will set the device to a known state and determine the home position. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="paddle"> The Paddle. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if move successfully started. </returns>
	/// <seealso cref="MPC_GetNumberPositions(char const * serialNo)" />
	/// <seealso cref="MPC_MoveToPosition(char const * serialNo, POL_Paddles paddle, double position)" />
	/// <seealso cref="MPC_GetPosition(char const * serialNo)" />
    /// 		  \include CodeSnippet_move.cpp
	POLARIZERDLL_API short __cdecl MPC_Home(char const * serialNo, POL_Paddles paddle);

	/// <summary> Move the device to the specified position (index). </summary>
	/// <remarks> The motor may need to be \ref C_MOTOR_sec10 "Homed" before a position can be set</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="paddle"> The Paddle. </param>
	/// <param name="position"> The required position in degrees. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if move successfully started. </returns>
	/// <seealso cref="MPC_Stop(char const * serialNo, POL_Paddles paddle)" />
	/// <seealso cref="MPC_GetNumberPositions(char const * serialNo)" />
	/// <seealso cref="MPC_GetPosition(char const * serialNo)" />
	/// <seealso cref="MPC_Home(char const * serialNo)" />
	/// <seealso cref="MPC_GetMaxTravel(char const * serialNo)" />
	/// <seealso cref="MPC_GetStepsPerDegree(char const * serialNo)" />
    /// 		  \include CodeSnippet_move.cpp
	POLARIZERDLL_API short __cdecl MPC_MoveToPosition(char const * serialNo, POL_Paddles paddle, double position);

	/// <summary> Stop the device . </summary>
	/// <remarks> The stops the device</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="paddle"> The Paddle. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if move successfully started. </returns>
	/// <seealso cref="MPC_MoveToPosition(char const * serialNo, POL_Paddles paddle, double position)" />
	/// <seealso cref="MPC_GetNumberPositions(char const * serialNo)" />
	/// <seealso cref="MPC_GetPosition(char const * serialNo)" />
	/// <seealso cref="MPC_Home(char const * serialNo)" />
	/// <seealso cref="MPC_GetMaxTravel(char const * serialNo)" />
	/// <seealso cref="MPC_GetStepsPerDegree(char const * serialNo)" />
    /// 		  \include CodeSnippet_move.cpp
	POLARIZERDLL_API short __cdecl MPC_Stop(char const * serialNo, POL_Paddles paddle);

	/// <summary> Move the device to the specified position (index). </summary>
	/// <remarks> The motor may need to be \ref C_MOTOR_sec10 "Homed" before a position can be set</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="paddle"> The Paddle. </param>
	/// <param name="direction"> The jog direction. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if move successfully started. </returns>
	/// <seealso cref="MPC_GetNumberPositions(char const * serialNo)" />
	/// <seealso cref="MPC_GetPosition(char const * serialNo)" />
	/// <seealso cref="MPC_Home(char const * serialNo)" />
    /// 		  \include CodeSnippet_move.cpp
	POLARIZERDLL_API short __cdecl MPC_Jog(char const * serialNo, POL_Paddles paddle, MOT_TravelDirection direction);

	/// <summary> Move the device to the specified position (index). </summary>
	/// <remarks> The motor may need to be \ref C_MOTOR_sec10 "Homed" before a position can be set</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="paddle"> The Paddle. </param>
	/// <param name="position"> The required position in degrees. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if move successfully started. </returns>
	/// <seealso cref="MPC_GetNumberPositions(char const * serialNo)" />
	/// <seealso cref="MPC_GetPosition(char const * serialNo)" />
	/// <seealso cref="MPC_Home(char const * serialNo)" />
	/// <seealso cref="MPC_GetMaxTravel(char const * serialNo)" />
	/// <seealso cref="MPC_GetStepsPerDegree(char const * serialNo)" />
    /// 		  \include CodeSnippet_move.cpp
	POLARIZERDLL_API short __cdecl MPC_MoveRelative(char const * serialNo, POL_Paddles paddle, double position);

	/// <summary> Get the current position. </summary>
	/// <remarks> The current position is the last recorded position.<br />
	/// 		  The current position is updated either by the polling mechanism or<br />
	/// 		  by calling <see cref="RequestPosition" /> or <see cref="RequestStatus" />.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="paddle"> The Paddle. </param>
	/// <returns> The current position 1 or 2. </returns>
	/// <seealso cref="MPC_GetNumberPositions(char const * serialNo)" />
	/// <seealso cref="MPC_MoveToPosition(char const * serialNo, POL_Paddles paddle, double position)" />
	/// <seealso cref="MPC_Home(char const * serialNo)" />
	/// <seealso cref="MPC_GetMaxTravel(char const * serialNo)" />
	/// <seealso cref="MPC_GetStepsPerDegree(char const * serialNo)" />
    /// 		  \include CodeSnippet_move.cpp
	POLARIZERDLL_API double __cdecl MPC_GetPosition(char const * serialNo, POL_Paddles paddle);

	/// <summary> Request polarizer parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="MPC_GetPolParams(char const * serialNo, PolarizerParameters *polParams)" />
	/// <seealso cref="MPC_SetPolParams(char const * serialNo, PolarizerParameters *polParams)" />
	/// <seealso cref="MPC_SetJogSize(char const * serialNo, POL_Paddles paddle, double jogSize)" />
	/// <seealso cref="MPC_GetJogSize(char const * serialNo, POL_Paddles paddle)" />
	/// <seealso cref="MPC_SetHomeOffset(char const * serialNo, double homeOffset)" />
	/// <seealso cref="MPC_GetHomeOffset(char const * serialNo)" />
	/// <seealso cref="MPC_SetVelocity(char const * serialNo, short velocity)" />
	/// <seealso cref="MPC_GetVelocity(char const * serialNo)" />
	POLARIZERDLL_API short __cdecl MPC_RequestPolParams(char const * serialNo);

	/// <summary> Gets the polarizer parameters. </summary>
	/// <param name="serialNo">    The device serial no. </param>
	/// <param name="polParams"> [in,out] If non-null, the polarizer settings. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="MPC_RequestPolParams(char const * serialNo)" />
	/// <seealso cref="MPC_SetPolParams(char const * serialNo, PolarizerParameters *polParams)" />
	/// <seealso cref="MPC_SetJogSize(char const * serialNo, POL_Paddles paddle, double jogSize)" />
	/// <seealso cref="MPC_GetJogSize(char const * serialNo, POL_Paddles paddle)" />
	/// <seealso cref="MPC_SetHomeOffset(char const * serialNo, double homeOffset)" />
	/// <seealso cref="MPC_GetHomeOffset(char const * serialNo)" />
	/// <seealso cref="MPC_SetVelocity(char const * serialNo, short velocity)" />
	/// <seealso cref="MPC_GetVelocity(char const * serialNo)" />
	/// <seealso cref="MPC_GetMaxTravel(char const * serialNo)" />
	/// <seealso cref="MPC_GetStepsPerDegree(char const * serialNo)" />
	POLARIZERDLL_API short __cdecl MPC_GetPolParams(char const * serialNo, PolarizerParameters *polParams);

	/// <summary> Gets the polarizer parameters. </summary>
	/// <param name="serialNo">    The device serial no. </param>
	/// <param name="polParams"> [in,out] If non-null, the polarizer settings. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="MPC_RequestPolParams(char const * serialNo)" />
	/// <seealso cref="MPC_GetPolParams(char const * serialNo, PolarizerParameters *polParams)" />
	/// <seealso cref="MPC_SetJogSize(char const * serialNo POL_Paddles paddle, double jogSize,)" />
	/// <seealso cref="MPC_GetJogSize(char const * serialNo, POL_Paddles paddle)" />
	/// <seealso cref="MPC_SetHomeOffset(char const * serialNo, double homeOffset)" />
	/// <seealso cref="MPC_GetHomeOffset(char const * serialNo)" />
	/// <seealso cref="MPC_SetVelocity(char const * serialNo, short velocity)" />
	/// <seealso cref="MPC_GetVelocity(char const * serialNo)" />
	/// <seealso cref="MPC_GetMaxTravel(char const * serialNo)" />
	/// <seealso cref="MPC_GetStepsPerDegree(char const * serialNo)" />
	POLARIZERDLL_API short __cdecl MPC_SetPolParams(char const * serialNo, PolarizerParameters *polParams);

	/// <summary> Sets jog size. </summary>
	/// <param name="serialNo">    The device serial no. </param>
	/// <param name="paddle">   The paddle. </param>
	/// <param name="jogSize"> Size of the jog. </param>
	/// <returns> A short. </returns>
	/// <seealso cref="MPC_RequestPolParams(char const * serialNo)" />
	/// <seealso cref="MPC_GetPolParams(char const * serialNo, PolarizerParameters *polParams)" />
	/// <seealso cref="MPC_SetPolParams(char const * serialNo, PolarizerParameters *polParams)" />
	/// <seealso cref="MPC_GetJogSize(char const * serialNo, POL_Paddles paddle)" />
	/// <seealso cref="MPC_GetMaxTravel(char const * serialNo)" />
	/// <seealso cref="MPC_GetStepsPerDegree(char const * serialNo)" />
	POLARIZERDLL_API short __cdecl MPC_SetJogSize(char const * serialNo, POL_Paddles paddle, double jogSize);

	/// <summary> Gets step size. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="paddle">   The paddle. </param>
	/// <returns> The step size. </returns>
	///
	/// <seealso cref="MPC_RequestPolParams(char const * serialNo)"/>
	/// <seealso cref="MPC_GetPolParams(char const * serialNo, PolarizerParameters *polParams)"/>
	/// <seealso cref="MPC_SetPolParams(char const * serialNo, PolarizerParameters *polParams)"/>
	/// <seealso cref="MPC_SetJogSize(char const * serialNo, POL_Paddles paddle, double jogSize)"/>
	/// <seealso cref="MPC_GetMaxTravel(char const * serialNo)"/>
	/// <seealso cref="MPC_GetStepsPerDegree(char const * serialNo)"/>
	POLARIZERDLL_API double __cdecl MPC_GetJogSize(char const * serialNo, POL_Paddles paddle);
	/// <summary> Sets home offset. </summary>
	/// <param name="serialNo">    The device serial no. </param>
	/// <param name="homeOffset"> The home offset. </param>
	/// <returns> A short. </returns>
	/// <seealso cref="MPC_RequestPolParams(char const * serialNo)" />
	/// <seealso cref="MPC_GetPolParams(char const * serialNo, PolarizerParameters *polParams)" />
	/// <seealso cref="MPC_SetPolParams(char const * serialNo, PolarizerParameters *polParams)" />
	/// <seealso cref="MPC_GetHomeOffset(char const * serialNo)" />
	/// <seealso cref="MPC_GetMaxTravel(char const * serialNo)" />
	/// <seealso cref="MPC_GetStepsPerDegree(char const * serialNo)" />
	POLARIZERDLL_API short __cdecl MPC_SetHomeOffset(char const * serialNo, double homeOffset);

	/// <summary> Gets home offset. </summary>
	/// <param name="serialNo">    The device serial no. </param>
	/// <returns> The home offset. </returns>
	/// <seealso cref="MPC_RequestPolParams(char const * serialNo)" />
	/// <seealso cref="MPC_GetPolParams(char const * serialNo, PolarizerParameters *polParams)" />
	/// <seealso cref="MPC_SetPolParams(char const * serialNo, PolarizerParameters *polParams)" />
	/// <seealso cref="MPC_SetHomeOffset(char const * serialNo, double homeOffset)" />
	/// <seealso cref="MPC_GetMaxTravel(char const * serialNo)" />
	/// <seealso cref="MPC_GetStepsPerDegree(char const * serialNo)" />
	POLARIZERDLL_API double __cdecl MPC_GetHomeOffset(char const * serialNo);

	/// <summary> Sets a velocity. </summary>
	/// <param name="serialNo">    The device serial no. </param>
	/// <param name="velocity"> The velocity. </param>
	/// <returns> A short. </returns>
	/// <seealso cref="MPC_RequestPolParams(char const * serialNo)" />
	/// <seealso cref="MPC_GetPolParams(char const * serialNo, PolarizerParameters *polParams)" />
	/// <seealso cref="MPC_SetPolParams(char const * serialNo, PolarizerParameters *polParams)" />
	/// <seealso cref="MPC_SetJogSize(char const * serialNo, double jogSize)" />
	/// <seealso cref="MPC_GetVelocity(char const * serialNo)" />
	POLARIZERDLL_API short __cdecl MPC_SetVelocity(char const * serialNo, short velocity);

	/// <summary> Gets the velocity. </summary>
	/// <param name="serialNo">    The device serial no. </param>
	/// <returns> The velocity. </returns>
	/// <seealso cref="MPC_RequestPolParams(char const * serialNo)" />
	/// <seealso cref="MPC_GetPolParams(char const * serialNo, PolarizerParameters *polParams)" />
	/// <seealso cref="MPC_SetPolParams(char const * serialNo, PolarizerParameters *polParams)" />
	/// <seealso cref="MPC_GetVelocity(char const * serialNo)" />
	POLARIZERDLL_API short __cdecl MPC_GetVelocity(char const * serialNo);


	/// <summary>	Request status bits. </summary>
	/// <remarks> This needs to be called to get the device to send it's current status.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="MPC_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="MPC_GetStatusBits(char const * serialNo)" />
	/// <seealso cref="MPC_StartPolling(char const * serialNo, int milliseconds)" />
	POLARIZERDLL_API short __cdecl MPC_RequestStatus(char const * serialNo);

	/// <summary>Get the current status bits. </summary>
	/// <remarks> This returns the latest status bits received from the device.<br />
	/// 		  To get new status bits, use <see cref="MPC_RequestStatus(char const * serialNo)" />
	/// 		  or use the polling functions, <see cref="MPC_StartPolling(char const * serialNo, int milliseconds)" />.  </remarks>
	/// <param name="serialNo">	The device serial no. </param>
    /// <param name="paddle"> The paddle id</param>
	/// <returns>	The status bits from the device <list type=table>
	///				<item><term>0x00000001</term><term>Forward hardware limit switch (0=No contact, 1=Contact).</term></item>
	///				<item><term>0x00000002</term><term>Reverse hardware limit switch (0=No contact, 1=Contact).</term></item>
	///				<item><term>0x00000004</term><term>Not applicable.</term></item>
 	///				<item><term>0x00000008</term><term>Not applicable.</term></item>
	///				<item><term>0x00000010</term><term>In motion moving forward.</term></item>
 	///				<item><term>0x00000020</term><term>In motion moving backward.</term></item>
	///				<item><term>0x00000040</term><term>In motion jogging forward.</term></item>
	///				<item><term>0x00000080</term><term>In motion jogging backward.</term></item>
 	///				<item><term>0x00000100</term><term>Not applicable.</term></item>
	///				<item><term>0x00000200</term><term>In motion Homing</term></item>
	///				<item><term>0x00000400</term><term>Device has been homed</term></item>
 	///				<item><term>0x00000800</term><term>Not applicable.</term></item>
 	///				<item><term>0x00001000</term><term>Tracking active.</term></item>
 	///				<item><term>0x00002000</term><term>Settled.</term></item>
 	///				<item><term>0x00004000</term><term>Motion error.</term></item>
	///				<item><term>...</term><term></term></item>
	///				<item><term>0x01000000</term><term>Motion current limit reached.</term></item>
	///				<item><term>...</term><term></term></item>
	///				<item><term>0x80000000</term><term>paddle enabled (1=Enabled, 0=Disabled).</term></item>
	/// 		  </list>  </returns>
	/// <seealso cref="MPC_RequestStatus(char const * serialNo)" />
	/// <seealso cref="MPC_StartPolling(char const * serialNo, int milliseconds)" />
	POLARIZERDLL_API DWORD __cdecl MPC_GetStatusBits(char const * serialNo, POL_Paddles paddle);

	/// <summary> Starts the internal polling loop which continuously requests position and status. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="milliseconds">The milliseconds polling rate. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="MPC_StopPolling(char const * serialNo)" />
	/// <seealso cref="MPC_PollingDuration(char const * serialNo)" />
	/// <seealso cref="MPC_RequestStatus(char const * serialNo)" />
	/// <seealso cref="MPC_RequestPosition(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	POLARIZERDLL_API bool __cdecl MPC_StartPolling(char const * serialNo, int milliseconds);

	/// <summary> Gets the polling loop duration. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The time between polls in milliseconds or 0 if polling is not active. </returns>
	/// <seealso cref="MPC_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="MPC_StopPolling(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	POLARIZERDLL_API long __cdecl MPC_PollingDuration(char const * serialNo);

	/// <summary> Stops the internal polling loop. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <seealso cref="MPC_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="MPC_PollingDuration(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	POLARIZERDLL_API void __cdecl MPC_StopPolling(char const * serialNo);

	/// <summary> Gets the time in milliseconds since tha last message was received from the device. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="lastUpdateTimeMS"> The time since the last message was received in milliseconds. </param>
	/// <returns> True if monitoring is enabled otherwize False. </returns>
	/// <seealso cref="MPC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// <seealso cref="MPC_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	POLARIZERDLL_API bool __cdecl MPC_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS );

	/// <summary> Enables the last message monitoring timer. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="enable"> True to enable monitoring otherwise False to disable. </param>
	/// <param name="lastMsgTimeout"> The last message error timeout in ms. 0 to disable. </param>
	/// <seealso cref="MPC_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="MPC_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	POLARIZERDLL_API void __cdecl MPC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout );

	/// <summary> Queries if the time since the last message has exceeded the lastMsgTimeout set by <see cref="MPC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )"/>. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> True if last message timer has elapsed, False if monitoring is not enabled or if time of last message received is less than lastMsgTimeout. </returns>
	/// <seealso cref="MPC_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="MPC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	POLARIZERDLL_API bool __cdecl MPC_HasLastMsgTimerOverrun(char const * serialNo);

	/// <summary> Requests that all settings are download from device. </summary>
	/// <remarks> This function requests that the device upload all it's settings to the DLL.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	POLARIZERDLL_API short __cdecl MPC_RequestSettings(char const * serialNo);

	/// <summary> Clears the device message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	POLARIZERDLL_API void __cdecl MPC_ClearMessageQueue(char const * serialNo);

	/// <summary> Registers a callback on the message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="functionPointer"> A function pointer to be called whenever messages are received. </param>
	/// <seealso cref="MPC_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="MPC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="MPC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	POLARIZERDLL_API void __cdecl MPC_RegisterMessageCallback(char const * serialNo, void (* functionPointer)());

	/// <summary> Gets the MessageQueue size. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> number of messages in the queue. </returns>
	/// <seealso cref="MPC_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="MPC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="MPC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	POLARIZERDLL_API int __cdecl MPC_MessageQueueSize(char const * serialNo);

	/// <summary> Get the next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="MPC_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="MPC_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="MPC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	POLARIZERDLL_API bool __cdecl MPC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Wait for next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="MPC_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="MPC_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="MPC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	POLARIZERDLL_API bool __cdecl MPC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);
}
/** @} */ // Polarizer
