// summary:	Declares the functions class
// The following ifdef block is the standard way of creating macros which make exporting from a
// DLL simpler. All files within this DLL are compiled with the NANOTRAKDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project that
// uses this DLL. This way any other project whose source files include this file see 
// NANOTRAK_API functions as being imported from a DLL, whereas this DLL sees
// symbols defined with this macro as being exported.

#pragma once

#ifdef NANOTRAKDLL_EXPORTS
#define NANOTRAK_API __declspec(dllexport)
#else
#define NANOTRAK_API __declspec(dllimport)
#endif

#include <OaIdl.h>


/** @defgroup KCubeNanoTrak KCube NanoTrak
 *  This section details the Structures and Functions relavent to the  @ref KNA101_page "KCube NanoTrak"<br />
 *  For an example of how to connect to the device and perform simple operations use the following links:
 *  <list type=bullet>
 *    <item> \ref namespaces_kna_ex_1 "Example of using the Thorlabs.MotionControl.KCube.NanoTrak.DLL from a C or C++ project."<br />
 *									  This requires the DLL to be dynamical linked. </item>
 *    <item> \ref namespaces_kna_ex_2 "Example of using the Thorlabs.MotionControl.KCube.NanoTrak.DLL from a C# project"<br />
 *									  This uses Marshalling to load and access the C DLL. </item>
 *  </list>
 *  The Thorlabs.MotionControl.KCube.NanoTrak.DLL requires the following DLLs
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

/// \cond NOT_MASTER
	
	/// <summary> NanoTrak Signal States. </summary>
	/// \ingroup Common
	typedef enum NT_SignalState
	{
		NT_BadSignal = 0x00, ///<The bad signal state.
		NT_GoodSignal = 0x01, ///<The good signal state.
	} NT_SignalState;

	/// <summary> NanoTrak Operating mode. </summary>
	/// \ingroup Common
	typedef enum NT_Mode : WORD
	{
		NT_ModeUndefined = 0x00, ///< Undefined nanoTrak mode.
		NT_Piezo = 0x01, ///< The Piezo nanoTrak mode.
		NT_Latch = 0x02, ///< The Latched NanoTrak mode.
		NT_Tracking = 0x03, ///< The Tracking NanoTrak mode.
		NT_HorizontalTracking = 0x04, ///< The Horizontal Tracking NanoTrak mode.
		NT_VerticalTracking = 0x05, ///< The Vertical Tracking NanoTrak mode.
	} NT_Mode;

	/// <summary> Values that represent NanoTrak Operating Modes. </summary>
	/// \ingroup Common
	typedef enum NT_ControlMode : WORD
	{
		NT_ControlModeUndefined = 0x00, ///<undefined nanoTrak mode.
		NT_OpenLoop = 0x01, ///<the open loop nanoTrak mode.
		NT_ClosedLoop = 0x02, ///<the closed loop nanoTrak mode.
		NT_OpenLoopSmoothed = 0x03, ///<the smoothed open loop nanoTrak mode.
		NT_ClosedLoopSmoothed = 0x04, ///<the smoother closed loop nanoTrak mode.
	} NT_ControlMode;

	/// <summary> NanoTrak Feedback Source. </summary>
	/// \ingroup Common
	typedef enum KNA_FeedbackSource : WORD
	{
		NT_FeedbackSourceUndefined = 0x00, ///< Undefined.
		NT_TIA = 0x01, ///< The TIA input source.
		NT_IO1_5v = 0x04, ///< The  IO1 input source at 5V.
	} KNA_FeedbackSource;

	/// <summary> Defines the number TIA ranges. </summary>
	#define NUM_TIA_RANGES	16

	/// <summary> Values that represent KNA_TIARange. </summary>
	typedef enum KNA_TIARange : WORD
	{
		/// <summary> An enum constant representing the NT tia range 1 5n an option. </summary>
		KNA_TIARange1_5nA = 0x0003,
		/// <summary> An enum constant representing the NT tia range 2 16.6n an option. </summary>
		KNA_TIARange2_16_6nA = 0x0004,
		/// <summary> An enum constant representing the NT tia range 3 50n an option. </summary>
		KNA_TIARange3_50nA = 0x0005,
		/// <summary> An enum constant representing the NT tia range 4 166n an option. </summary>
		KNA_TIARange4_166nA = 0x0006,
		/// <summary> An enum constant representing the NT tia range 5 500n an option. </summary>
		KNA_TIARange5_500nA = 0x0007,
		/// <summary> An enum constant representing the NT tia range 6 1.65u an option. </summary>
		KNA_TIARange6_1_66uA = 0x0008,
		/// <summary> An enum constant representing the NT tia range 7 5u an option. </summary>
		KNA_TIARange7_5uA = 0x0009,
		/// <summary> An enum constant representing the NT tia range 8 16.6u an option. </summary>
		KNA_TIARange8_16_6uA = 0x000A,
		/// <summary> An enum constant representing the NT tia range 9 50u an option. </summary>
		KNA_TIARange9_50uA = 0x000B,
		/// <summary> An enum constant representing the NT tia range 10 166u an option. </summary>
		KNA_TIARange10_166uA = 0x000C,
		/// <summary> An enum constant representing the NT tia range 11 500u an option. </summary>
		KNA_TIARange11_500uA = 0x000D,
		/// <summary> An enum constant representing the NT tia range 12 1.66m an option. </summary>
		KNA_TIARange12_1_66mA = 0x000E,
		/// <summary> An enum constant representing the NT tia range 13 5m an option. </summary>
		KNA_TIARange13_5mA = 0x000F,
	} KNA_TIARange;

	/// <summary> The Odd or Even TIA Range specification. </summary>
	/// \ingroup Common
	typedef enum NT_OddOrEven : WORD
	{
		NT_OddAndEven = 0x0001, ///< Both odd or even TIA ranges. 
		NT_Odd = 0x0002, ///< Odd TIA ranges.
		NT_Even = 0x0003 ///< Even TIA ranges.
	} NT_OddOrEven;

	/// <summary> The in range specification. </summary>
	/// \ingroup Common
	typedef enum NT_UnderOrOver : WORD
	{
		NT_InRange = 0x0001, ///< Signal is in range. 
		NT_UnderRange = 0x0002, ///< Signal is under range. 
		NT_OverRange = 0x0003 ///< Signal is over range. 
	} NT_UnderOrOver;

	/// <summary> Circle diameter mode types. </summary>
	/// \ingroup Common
	typedef enum NT_CircleDiameterMode : WORD
	{
		NT_ParameterCircleMode = 0x0001, ///<Use the fixed diameter definition.
		NT_AbsPowerCircleMode = 0x0002, ///<Use the algorithm to calculate circle diameter.
		NT_LUTCircleMode = 0x0003 ///<Use the circle look up table (LUT).
	} NT_CircleDiameterMode;

	/// <summary> The methods used by circle diameter algorithm. </summary>
	/// \ingroup Common
	typedef enum NT_CircleAdjustment : WORD
	{
		NT_LinearCircleAdjustment = 0x0001, ///<Linear Adjustment method.
		NT_LogCircleAdjustment = 0x0002, ///<Logarithmic circle adjustment.
		NT_SquareCircleAdjustment = 0x0003, ///<Square circle adjustment.
		NT_CubeCircleAdjustment = 0x0004 ///<Cubic circle adjustment.
	} NT_CircleAdjustment;

	/// <summary> TIA Ranging Mode. </summary>
	/// \ingroup Common
	typedef enum NT_TIARangeMode : WORD
	{
		NT_TIARangeModeUndefined = 0x0000, ///<Undefined.
		NT_AutoRangeAtSelected = 0x0001, ///<Autorange TIA at selected range.
		NT_ManualRangeAtSelected = 0x0002, ///<Manual TIA at selected range.
		NT_ManualRangeAtParameter = 0x0003, ///<Manual TIA at supplied parameter range.
		NT_AutoRangeAtParameter = 0x0004 ///<Autorange TIA at supplied parameter range.
	} NT_TIARangeMode;

	/// <summary> NanoTrak Output Voltage Range. </summary>
	/// \ingroup Common
	/// 
	/// <summary> Values that represent Low Voltage Range. </summary>
	/// <remarks> This field is fixed and cannt be changed</remarks>
	enum KNA_LowVoltageRange : WORD
	{
		KNA_VoltageRange_10v = 0x0002 ///<10v output range.
	};

	/// <summary> Values that represent Low Output Voltage Route. </summary>
	/// <remarks> This field is fixed and cannt be changed</remarks>
	enum KNA_LowOutputVoltageRoute : WORD
	{
		KNA_IO1Only = 0x0001 ///<Output to IO1 connector only.
	};

	/// <summary> Values that represent High Voltage Range. </summary>
	/// <remarks> The 2 channels parameters must be combined with a bitwise OR</remarks>
	enum KNA_HighVoltageRange : WORD
	{
		KNA_Default_Range = 0x00, ///<Default value both channels 75v.
		KNA_VoltageRange_CH1_75v = 0x00, ///<Channel 1 75v.
		KNA_VoltageRange_CH1_150v = 0x01, ///<Channel 1 150v.
		KNA_VoltageRange_CH2_75v = 0x00, ///<Channel 2 75v.
		KNA_VoltageRange_CH2_150v = 0x10 ///<Channel 2 150v.
	};

	/// <summary> Values that represent High Output Voltage Route. </summary>
	/// <remarks> The IN, OUT and Boost parameters must be combined with a bitwise OR</remarks>
	enum KNA_HighOutputVoltageRoute : WORD
	{
		KNA_Default_Route = 0x0000,///<Default value, all off
		KNA_ExtIn_PIN = 0x0000,///<Input via PIn
		KNA_ExtIn_IO1 = 0x0001,///<Input via IO1
		KNA_ExtOut_Dis = 0x0000,///<Output Disabled
		KNA_ExtOut_IO2 = 0x0010,///<Output via IO2
		KNA_EnableInputBoost = 0x0100///<Boost inputs enabled
	};

	typedef enum NT_VoltageRange : WORD
	{
		NT_VoltageRangeUndefined = 0x0000, ///<Undefined.
		NT_VoltageRange_5v = 0x0001, ///<5v output rangen.
		NT_VoltageRange_10v = 0x0002 ///<10v output range.
	} NT_VoltageRange;

	/// <summary> NanoTrak Output Route. </summary>
	/// \ingroup Common
	typedef enum NT_OutputVoltageRoute : WORD
	{
		NT_IO1Only = 0x0001, ///<Output to IO1 connector only.
		NT_HubOrIO1 = 0x0002 ///<Output to IO1 connector and Hub.
	} NT_OutputVoltageRoute;

	/// <summary> The Input mode units. </summary>
	/// \ingroup Common
	typedef enum NT_PowerInputUnits : WORD
	{
		NT_Amps, ///<Display as mAmps.
		NT_Watts, ///<Display as mWatts
		NT_Db ///<Display as dBm.
	} NT_PowerInputUnits;

	/// <summary> The IO1 units. </summary>
	/// \ingroup Common
	typedef enum NT_IO1_Units : WORD
	{
		NT_Voltage, ///<IO1 output as Voltage.
		NT_FullRange, ///<IO1 output as % Full Range.
		NT_UserDefined ///<IO1 output as User Defined.
	} NT_IO1_Units;

	/// <summary> Values that represent wheel Rate of Change. </summary>
	typedef enum KNA_WheelAdjustRate : __int16
	{
		/// <summary> An enum constant representing the kmot js low option. </summary>
		KNA_WM_Low = 0x00,
		/// <summary> An enum constant representing the kmot js medium option. </summary>
		KNA_WM_Medium = 0x01,
		/// <summary> An enum constant representing the kmot js high option. </summary>
		KNA_WM_High = 0x02,
	} KNA_WheelAdjustRate;

	/// <summary> Values that represent Trigger Port Mode. </summary>
	typedef enum KNA_TriggerPortMode : __int16
	{
		KNA_TrigDisabled = 0x00,///< Trigger Disabled
		KNA_TrigIn_GPI = 0x01,///< General purpose logic input (<see cref="NT_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)
		KNA_TrigIn_VoltageStepUp = 0x02,///< Move relative using relative move parameters
		KNA_TrigIn_VoltageStepDown = 0x03,///< Move absolute using absolute move parameters
		KNA_TrigOut_GPO = 0x0A,///< General purpose output (<see cref="NT_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)
	} KNA_TriggerPortMode;

	/// <summary> Values that represent Trigger Port Polarity. </summary>
	typedef enum KNA_TriggerPortPolarity : __int16
	{
		KNA_TrigPolarityHigh = 0x01,///< Trigger Polarity high
		KNA_TrigPolarityLow = 0x02,///< Trigger Polarity Low
	} KNA_TriggerPortPolarity;
/// \endcond

	/// <summary> Values that represent NT_FeedbackSource. </summary>
	enum KNA_Channels : WORD
	{
		/// <summary>	An enum constant representing the kna channel undefined option. </summary>
		KNA_ChannelUndefined = 0x00,
		/// <summary>	An enum constant representing the kna channel 1 option. </summary>
		KNA_Channel1 = 0x01,
		/// <summary>	An enum constant representing the kna channel 2 option. </summary>
		KNA_Channel2 = 0x02,
	};

	/// <summary> The Piezo Control Modes. </summary>
	typedef enum KNA_FeedbackModeTypes : short
	{
		PZ_ControlModeUndefined = 0, ///<Undefined
		PZ_OpenLoop = 1, ///<Open Loop mode.
		PZ_CloseLoop = 2, ///<Closed Loop mode.
		PZ_OpenLoopSmooth = 3, ///<Open Loop mode with smoothing.
		PZ_CloseLoopSmooth = 4 ///<Closed Loop mode with smoothing.
	} KNA_FeedbackModeTypes;

	#pragma pack(1)
	
	/// <summary> Structure used to hold any parameter which has a horizontal and vertical component, i.e. position. </summary>
	typedef struct NT_HVComponent
	{
		/// <summary> The horizontal component, range 0 to 65535, usage dependant. </summary>
		WORD horizontalComponent;
		/// <summary> The vertical component, range 0 to 65535, useage dependant. </summary>
		WORD verticalComponent;
	} NT_HVComponent;

	/// <summary> Structure containing the scan circle parameters. </summary>
	typedef struct NT_CircleParameters
	{
		/// <summary> Circle diameter mode, <see cref="NT_CircleDiameterMode" />
		///		<list type=table>
		///			<item><term>Use supplied Parameters.</term><term>1</term></item>
		///			<item><term>Use supplied Algorithm.</term><term>2</term></item>
		///			<item><term>use Lookup Table (LUT)</term><term>3</term></item>
		///		</list> </summary>
		NT_CircleDiameterMode mode;
		/// <summary> Circle Diameter where 65535 corresponding to maximum voltage, 10 NT units. </summary>
		WORD diameter;
		/// <summary> Number of samples read per revolution (multiple of 4). </summary>
		WORD samplesPerRevolution;
		/// <summary> Minimum diameter imposed on algorithm 0 to 32767 in NT units. </summary>
		WORD minDiameter;
		/// <summary> Maximum diameter imposed on algorithm 0 to 32767 in NT units. </summary>
		WORD maxDiameter;
		/// <summary> Algorithm adjustment method: <see cref="NT_CircleAdjustment" />
		/// 	 <list type=table>
		///			<item><term>Linear Algorithm.</term><term>1</term></item>
		///			<item><term>Logarithmic algorithm.</term><term>2</term></item>
		///			<item><term>Square algorithm</term><term>3</term></item>
		///			<item><term>Cubic algorithm</term><term>4</term></item>
		///		</list> </summary>
		NT_CircleAdjustment algorithmAdjustment;
	} NT_CircleParameters;

	/// <summary> Structure containing circle the diameter lookup table entries. </summary>
	typedef struct NT_CircleDiameterLUT
	{
		/// <summary> Array of diameters for each TIA range with 65535 corresponding to maximum voltage. </summary>
		WORD LUTdiameter[NUM_TIA_RANGES];
	} NT_CircleDiameterLUT;

	/// <summary> Structure containing TIA range parameters. </summary>
	typedef struct KNA_TIARangeParameters
	{
		/// <summary> Chooses automatic or manual ranging and currently selected or new range. <see cref="NT_TIARangeMode" />
		/// 	<list type=table>
		///			<item><term>Automatic Ranging at current range.</term><term>1</term></item>
		///			<item><term>Manual Ranging at current range.</term><term>2</term></item>
		///			<item><term>Manual Ranging using supplied range</term><term>3</term></item>
		///			<item><term>Automatic ranging using supplied range</term><term>4</term></item>
		///		</list>  </summary>
		NT_TIARangeMode mode;
		/// <summary> Up switching threshold as a percentage of the current range.<br />
		/// 		  When in an automatic mode, the range rises above this threshold, the TIA range will rise to the higher TIA range.<br />
		/// 		  Range 0 to 1000 equivalent to 0 to 100% </summary>
		WORD upLimit;
		/// <summary> Down switching threshold as a percentage of the current range.<br />
		/// 		  When in an automatic mode, the range drops below this threshold, the TIA range will drop to the lower TIA range.<br />
		/// 		  Range 0 to 1000 equivalent to 0 to 100%  </summary>
		WORD downLimit;
		/// <summary> The number of samples for averaging to give auto-range input from 2 to 32. </summary>
		short settleSamples;
		/// <summary> parameter determining which TIA ranges to include when auto ranging: <see cref="NT_OddOrEven" />
		/// 	<list type=table>
		///			<item><term>All TIA Ranges.</term><term>1</term></item>
		///			<item><term>Only use Odd TIA ranges.</term><term>2</term></item>
		///			<item><term>Only use even TIA ranges</term><term>3</term></item>
		///		</list> </summary>
		NT_OddOrEven changeToOddOrEven;
		/// <summary> TIA Range to use if in manual mode: <br />
		/// 		  <see cref="KNA_TIARange" /> for TIA ranges. </summary>
		KNA_TIARange newRange;
	} KNA_TIARangeParameters;

	/// <summary> Structure containing TIA reading. </summary>
	typedef struct KNA_TIAReading
	{
		/// <summary> Absolute reading. </summary>
		float absoluteReading;
		/// <summary> Relative reading 0-32767 for 0 - 100% of selected current range value. </summary>
		WORD relativeReading;
		/// <summary> Selected current range from the <see cref="KNA_TIARange" />. </summary>
		KNA_TIARange selectedRange;
		/// <summary> Indicates whether read signal is in range, over range or under range. </summary>
		NT_UnderOrOver underOrOverRead;
	} KNA_TIAReading;


	/// <summary> Structure containing electronic input and output settings. </summary>
	typedef struct KNA_IOSettings
	{
		/// <summary> Low Voltage Output range: <see cref="NT_VoltageRange" />
		///		<list type=table>
		///			<item><term>0 - 10V output range.</term><term>2</term></item>
		///		</list> </summary>
		KNA_LowVoltageRange lowVoltageOutRange;
		/// <summary> Low Voltage Output routing: <see cref="NT_OutputVoltageRoute" />
		///		<list type=table>
		///			<item><term>Output to IO1 connector.</term><term>1</term></item>
		KNA_LowOutputVoltageRoute lowVoltageOutputRoute;
		/// <summary> High Voltage Output routing flags: <see cref="NT_OutputVoltageRoute" />
		/// <Remarks> Default Value = 0, (CH1_75V | CH2_75V) </Remarks>
		///		<list type=table>
		///			<item><term>CH1_150v (0x01).</term><term>Set Channel 1 range to 150v when set otherwise 75v</term></item>
		///			<item><term>CH2_150v (0x01).</term><term>Set Channel 2 range to 150v when set otherwise 75v</term></item>
		///		</list> </summary>
		KNA_HighVoltageRange highVoltageOutRange;
		/// <summary> High Voltage Output routing: <see cref="NT_OutputVoltageRoute" />
		/// <Remarks> Default Value = 0, (ExtIn_PIN | ExtOut_Dis) </Remarks>
		///		<list type=table>
		///			<item><term>ExtIn_IO1 (0x01).</term><term>Set input from IO1 otherwise input from PIn</term></item>
		///			<item><term>ExtOut_IO1 (0x10).</term><term>Set output via IO1 otherwise disable IO1 output</term></item>
		///			<item><term>EnableInputBoost (0x100).</term><term>Enable Input Boost when set</term></item>
		///		</list> </summary>
		KNA_HighOutputVoltageRoute highVoltageOutputRoute;
	} KNA_IOSettings;

	/// <summary> structure containing NT Gain parameters. </summary>
	typedef struct NT_GainParameters
	{
		/// <summary> The control mode (Always set to 0x02). </summary>
		WORD controlMode;
		/// <summary> The gain setting, range is 100 to 10000. </summary>
		short gain;
	} NT_GainParameters;

	/// <summary> Structure containing the MMI Parameters. </summary>
	/// <value> Device GUI parameters. </value>
	typedef struct KNA_MMIParams
	{
		/// <summary> The voltage adjust rate. </summary>
		KNA_WheelAdjustRate WheelAdjustRate;
		/// <summary> The display intensity, range 0 to 100%. </summary>
		__int16 DisplayIntensity;
		/// <summary> Reserved fields. </summary>
		__int16 reserved[6];
	} KNA_MMIParams;

	/// <summary> KCube piezo trigger configuration. </summary>
	typedef struct KNA_TriggerConfig
	{
		/// <summary> The trigger 1 mode. </summary>
		/// <remarks> The trigger 1 operating mode:
		/// 		  <list type=table>
		///				<item><term>0</term><term>Trigger disabled</term></item>
		///				<item><term>1</term><term>Trigger Input - set as latched</term></item>
		///				<item><term>2</term><term>Trigger Tracking - set as tracking</term></item>
		///				<item><term>3</term><term>Trigger Home - Trigger when homed</term></item>
		///				<item><term>10</term><term>Trigger Output - Trigger Output</term></item>
		///				<item><term>11</term><term>Trigger Output - Trigger when tracking</term></item>
		/// 		  </list>
		/// 		  </remarks>
		KNA_TriggerPortMode Trigger1Mode;
		/// <summary> The trigger 1 polarity. </summary>
		/// <remarks> The trigger 1 output polaritye:
		/// 		  <list type=table>
		///				<item><term>1</term><term>Output high when set</term></item>
		///				<item><term>2</term><term>Output low when set</term></item>
		/// 		  </list>
		/// 		  </remarks>
		KNA_TriggerPortPolarity Trigger1Polarity;
		/// <summary> unused in this device. </summary>
		__int16 unused1;
		/// <summary> The trigger 2 mode. </summary>
		/// <remarks> The trigger 2 operating mode:
		/// 		  <list type=table>
		///				<item><term>0</term><term>Trigger disabled</term></item>
		///				<item><term>1</term><term>Trigger Input - set as latched</term></item>
		///				<item><term>2</term><term>Trigger Tracking - set as tracking</term></item>
		///				<item><term>3</term><term>Trigger Home - Trigger when homed</term></item>
		///				<item><term>10</term><term>Trigger Output - Trigger Output</term></item>
		///				<item><term>11</term><term>Trigger Output - Trigger when tracking</term></item>
		/// 		  </list>
		/// 		  </remarks>
		KNA_TriggerPortMode Trigger2Mode;
		/// <summary> The trigger 2 polarity. </summary>
		/// <remarks> The trigger 2 output polarity:
		/// 		  <list type=table>
		///				<item><term>1</term><term>Output high when set</term></item>
		///				<item><term>2</term><term>Output low when set</term></item>
		/// 		  </list>
		/// 		  </remarks>
		KNA_TriggerPortPolarity Trigger2Polarity;
		/// <summary> unused in this device. </summary>
		__int16 unused2;
		/// <summary> reserved fields. </summary>
		__int16 reserved[4];
	} KNA_TriggerConfig;

	/// <summary> Structure containing feedback loop constants. </summary>
	typedef struct KNA_FeedbackLoopConstants
	{
		/// <summary> The proportional term. </summary>
		short proportionalTerm;
		/// <summary> The integral term. </summary>
		short integralTerm;
	} KNA_FeedbackLoopConstants;

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
	NANOTRAK_API short __cdecl TLI_BuildDeviceList();

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
	NANOTRAK_API short __cdecl TLI_GetDeviceListSize();

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
	NANOTRAK_API short __cdecl TLI_GetDeviceList(SAFEARRAY** stringsReceiver);

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
	NANOTRAK_API short __cdecl TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID);

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
	NANOTRAK_API short __cdecl TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length);

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
	NANOTRAK_API short __cdecl TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer);

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
	NANOTRAK_API short __cdecl TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID);

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
	NANOTRAK_API short __cdecl TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length);

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
	NANOTRAK_API short __cdecl TLI_GetDeviceInfo(char const * serialNo, TLI_DeviceInfo *info);

	/// <summary> Initialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <remarks> Call TLI_InitializeSimulations before TLI_BuildDeviceList at the start of the program to make a connection to the simulation manager.<Br />
	/// 		  Any devices configured in the simulation manager will become visible TLI_BuildDeviceList is called and can be accessed using TLI_GetDeviceList.<Br />
	/// 		  Call TLI_InitializeSimulations at the end of the program to release the simulator.  </remarks>
	/// <seealso cref="TLI_UninitializeSimulations()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	NANOTRAK_API void __cdecl TLI_InitializeSimulations();

	/// <summary> Uninitialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <seealso cref="TLI_InitializeSimulations()" />
	NANOTRAK_API void __cdecl TLI_UninitializeSimulations();

	/// <summary> Open the device for communications. </summary>
	/// <param name="serialNo">	The serial no of the device to be connected. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="NT_Close(char const * serialNo)" />
	NANOTRAK_API short __cdecl NT_Open(char const * serialNo);

	/// <summary> Disconnect and close the device. </summary>
	/// <param name="serialNo">	The serial no of the device to be disconnected. </param>
    /// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="NT_Open(char const * serialNo)" />
	NANOTRAK_API void __cdecl NT_Close(char const * serialNo);

	/// <summary>	Check connection. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> true if the USB is listed by the ftdi controller</returns>
	/// \include CodeSnippet_CheckConnection.cpp
	NANOTRAK_API bool __cdecl NT_CheckConnection(char const * serialNo);

	/// <summary> Determine if the device front panel can be locked. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> True if we can lock the device front panel, false if not. </returns>
	/// <seealso cref="NT_GetFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="NT_RequestFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="NT_SetFrontPanelLock(char const * serialNo, bool locked)" />
	NANOTRAK_API bool __cdecl NT_CanDeviceLockFrontPanel(char const * serialNo);

	/// <summary> Query if the device front panel locked. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> True if the device front panel is locked, false if not. </returns>
	/// <seealso cref="NT_CanDeviceLockFrontPanel(char const * serialNo)" />
	/// <seealso cref="NT_RequestFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="NT_SetFrontPanelLock(char const * serialNo, bool locked)" />
	NANOTRAK_API bool __cdecl  NT_GetFrontPanelLocked(char const * serialNo);

	/// <summary> Ask the device if its front panel is locked. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_CanDeviceLockFrontPanel(char const * serialNo)" />
	/// <seealso cref="NT_GetFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="NT_SetFrontPanelLock(char const * serialNo, bool locked)" />
	NANOTRAK_API short __cdecl  NT_RequestFrontPanelLocked(char const * serialNo);

	/// <summary> Sets the device front panel lock state. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="locked"> True to lock the device, false to unlock. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_CanDeviceLockFrontPanel(char const * serialNo)" />
	/// <seealso cref="NT_GetFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="NT_RequestFrontPanelLocked(char const * serialNo)" />
	NANOTRAK_API short __cdecl  NT_SetFrontPanelLock(char const * serialNo, bool locked);

	/// <summary> Sends a command to the device to make it identify iteself. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	NANOTRAK_API void __cdecl NT_Identify(char const * serialNo);

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
	NANOTRAK_API short __cdecl NT_GetHardwareInfo(char const * serialNo, char * modelNo, DWORD sizeOfModelNo, WORD * type, WORD * numChannels, 
													char * notes, DWORD sizeOfNotes, DWORD * firmwareVersion, WORD * hardwareVersion, WORD * modificationState);

	/// <summary> Gets the hardware information in a block. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="hardwareInfo"> Address of a TLI_HardwareInformation structure to receive the hardware information. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	NANOTRAK_API short __cdecl NT_GetHardwareInfoBlock(char const *serialNo, TLI_HardwareInformation *hardwareInfo);

	/// <summary> Gets version number of the device firmware. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device firmware version number made up of 4 byte parts. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	NANOTRAK_API DWORD __cdecl NT_GetFirmwareVersion(char const * serialNo);

	/// <summary> Gets version number of the device software. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device software version number made up of 4 byte parts. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	NANOTRAK_API DWORD __cdecl NT_GetSoftwareVersion(char const * serialNo);

	/// <summary> Update device with stored settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
    /// 		  \include CodeSnippet_connection1.cpp
	NANOTRAK_API bool __cdecl NT_LoadSettings(char const * serialNo);

	/// <summary> Update device with named settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="settingsName"> Name of settings stored away from device. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	///             \include CodeSnippet_connection1.cpp
	NANOTRAK_API bool __cdecl NT_LoadNamedSettings(char const * serialNo, char const *settingsName);

	/// <summary> persist the devices current settings. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	NANOTRAK_API bool __cdecl NT_PersistSettings(char const * serialNo);

	/// <summary> Tells the device that it is being disconnected. </summary>
	/// <remarks> This does not disconnect the communications.<br />
	/// 		  To disconnect the communications, call the <see cref="NT_Close(char const * serialNo)" /> function. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	NANOTRAK_API short __cdecl NT_Disconnect(char const * serialNo);

	/// <summary> Requests the NanoTrak signal state. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_GetSignalState(char const * serialNo)" />
	NANOTRAK_API short __cdecl NT_RequestSignalState(char const * serialNo);

	/// <summary> Gets the NanoTrak signal state. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> <list type=table>
	///				<item><term>Not tracking or poor signal</term><term>0</term></item>
	///				<item><term>Tracking and good signal</term><term>1</term></item>
	/// 		  </list> </returns>
	/// <seealso cref="NT_RequestSignalState(char const * serialNo)" />
	NANOTRAK_API NT_SignalState __cdecl NT_GetSignalState(char const * serialNo);

	/// <summary> Requests the NanoTrak mode. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_GetMode(char const * serialNo)" />
	/// <seealso cref="NT_SetMode(char const * serialNo, NT_Mode mode)" />
	NANOTRAK_API short __cdecl NT_RequestMode(char const * serialNo);

	/// <summary> Gets the nanoTrak operating mode. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The NanoTrak operating mode.
	/// 		  <list type=table>
	///				<item><term>Undefined</term><term>0</term></item>
	///				<item><term>Piezo Mode</term><term>1</term></item>
	///				<item><term>Latched output mode</term><term>2</term></item>
	///				<item><term>Tracking mode</term><term>3</term></item>
	///				<item><term>Horizontal tracking mode</term><term>4</term></item>
	///				<item><term>Vertical Tracking Mode</term><term>5</term></item>
	/// 		  </list> </returns>
	/// <seealso cref="NT_SetMode(char const * serialNo, NT_Mode mode)" />
	/// <seealso cref="NT_RequestMode(char const * serialNo)" />
	NANOTRAK_API NT_Mode __cdecl NT_GetMode(char const * serialNo);

	/// <summary> Setsthe nanoTrak operating mode. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="mode"> The NanoTrak operating mode.
	/// 		<list type=table>
	///				<item><term>Undefined</term><term>0</term></item>
	///				<item><term>Piezo Mode</term><term>1</term></item>
	///				<item><term>Latched output mode</term><term>2</term></item>
	///				<item><term>Tracking mode</term><term>3</term></item>
	///				<item><term>Horizontal tracking mode</term><term>4</term></item>
	///				<item><term>Vertical Tracking Mode</term><term>5</term></item>
	/// 		  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_RequestMode(char const * serialNo)" />
	/// <seealso cref="NT_GetMode(char const * serialNo)" />
	NANOTRAK_API short __cdecl NT_SetMode(char const * serialNo, NT_Mode mode);

	/// <summary> Requests the NanoTrak tracking threshold signal. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_GetTrackingThresholdSignal(char const * serialNo)" />
	/// <seealso cref="NT_SetTrackingThresholdSignal(char const * serialNo, float threshold)" />
	NANOTRAK_API short __cdecl NT_RequestTrackingThresholdSignal(char const * serialNo);

	/// <summary> Gets the tracking threshold signal. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> Tracking threshold signal in amps from 1.0e-9 to 1.0e-3. </returns>
	/// <seealso cref="NT_RequestrackingThresholdSignal(char const * serialNo)" />
	/// <seealso cref="NT_SetTrackingThresholdSignal(char const * serialNo, float threshold)" />
	NANOTRAK_API float __cdecl NT_GetTrackingThresholdSignal(char const * serialNo);

	/// <summary> Sets the tracking threshold signal. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="threshold"> Tracking threshold signal in amps from 1.0e-9 to 1.0e-3. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_RequestrackingThresholdSignal(char const * serialNo)" />
	/// <seealso cref="NT_GetTrackingThresholdSignal(char const * serialNo)" />
	NANOTRAK_API short __cdecl NT_SetTrackingThresholdSignal(char const * serialNo, float threshold);

	/// <summary> Requests the home position of the scan circle. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_GetCircleHomePosition(char const * serialNo)" />
	/// <seealso cref="NT_SetCircleHomePosition(char const * serialNo, NT_HVComponent *position)" />
	NANOTRAK_API short __cdecl NT_RequestCircleHomePosition(char const * serialNo);

	/// <summary> Gets the home position of the scan circle. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="position"> Address of the NT_HVComponent to receive the position as an XY pair,<br />
	/// 				   range 0 to 65535 equivalent to 0 to 10 NT Units. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_RequesCircleHomePosition(char const * serialNo)" />
	/// <seealso cref="NT_SetCircleHomePosition(char const * serialNo, NT_HVComponent *position)" />
	/// <seealso cref="NT_HomeCircle(char const * serialNo)" />
	NANOTRAK_API short __cdecl NT_GetCircleHomePosition(char const * serialNo, NT_HVComponent *position);

	/// <summary> Sets the home position of the scan circle. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="position"> Address of the NT_HVComponent containing the new position as an XY pair<br />
	/// 				   range 0 to 65535 equivalent to 0 to 10 NT Units. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_RequesCircleHomePosition(char const * serialNo)" />
	/// <seealso cref="NT_GetCircleHomePosition(char const * serialNo, NT_HVComponent *position)" />
	/// <seealso cref="NT_HomeCircle(char const * serialNo)" />
	NANOTRAK_API short __cdecl NT_SetCircleHomePosition(char const * serialNo, NT_HVComponent *position);

	/// <summary> Move the scan circle to the home position. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_SetCircleHomePosition(char const * serialNo, NT_HVComponent *position)" />
	/// <seealso cref="NT_GetCircleHomePosition(char const * serialNo, NT_HVComponent *position)" />
	NANOTRAK_API short __cdecl NT_HomeCircle(char const * serialNo);

	/// <summary>Requests the current scan circle centre position. </summary>
	/// <remarks> This command will request an update from the device.<br />
	/// 		  NOTE this is nor required if the device is being continously polled using <see cref="NT_StartPolling(char const * serialNo, int milliseconds)" />.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="NT_GetCirclePosition(char const * serialNo, NT_HVComponent *position)" />
	/// <seealso cref="NT_StartPolling(char const * serialNo, int milliseconds)" />
	NANOTRAK_API short __cdecl NT_RequestCirclePosition(char const * serialNo);

	/// <summary> Gets the current scan circle centre position. </summary>
	/// <remarks> This command will return the latest value received from the device.<br />
	///			  To get an updated value use <see cref="NT_RequestCirclePosition(char const * serialNo)" /> or <see cref="NT_StartPolling(char const * serialNo, int milliseconds)" /></remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="position"> Address of the NT_HVComponent to receive the position as an XY pair<br />
	/// 				   range 0 to 65535 equivalent to 0 to 10 NT Units. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_RequestCirclePosition(char const * serialNo)" />
	/// <seealso cref="NT_StartPolling(char const * serialNo, int milliseconds)" />
	NANOTRAK_API short __cdecl NT_GetCirclePosition(char const * serialNo, NT_HVComponent *position);

	/// <summary> Requests the scanning circle parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_GetCircleParams(char const * serialNo)" />
	/// <seealso cref="NT_SetCircleParams(char const * serialNo, NT_CircleParameters *params" />
	NANOTRAK_API short __cdecl NT_RequestCircleParams(char const * serialNo);

	/// <summary> Gets the scanning circle parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="params"> Address of the NT_CircleParameters to receive the parameters defining the scan circle. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_RequesCircleParams(char const * serialNo)" />
	/// <seealso cref="NT_SetCircleParams(char const * serialNo, NT_CircleParameters *params)" />
	/// <seealso cref="NT_GetCircleDiameter(char const * serialNo)" />
	/// <seealso cref="NT_SetCircleDiameter(char const * serialNo, WORD diameter)" />
	/// <seealso cref="NT_GetCircleDiameterLUT(char const * serialNo, NT_CircleDiameterLUT *LUT)" />
	/// <seealso cref="NT_SetCircleDiameterLUT(char const * serialNo, NT_CircleDiameterLUT *LUT)" />
	NANOTRAK_API short __cdecl NT_GetCircleParams(char const * serialNo, NT_CircleParameters *params);

	/// <summary> Sets the scanning circle parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="params"> Address of the NT_CircleParameters containing the new parameters defining the scan circle. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_RequesCircleParams(char const * serialNo)" />
	/// <seealso cref="NT_GetCircleParams(char const * serialNo, NT_CircleParameters *params)" />
	/// <seealso cref="NT_GetCircleDiameter(char const * serialNo)" />
	/// <seealso cref="NT_SetCircleDiameter(char const * serialNo, WORD diameter)" />
	/// <seealso cref="NT_GetCircleDiameterLUT(char const * serialNo, NT_CircleDiameterLUT *LUT)" />
	/// <seealso cref="NT_SetCircleDiameterLUT(char const * serialNo, NT_CircleDiameterLUT *LUT)" />
	NANOTRAK_API short __cdecl NT_SetCircleParams(char const * serialNo, NT_CircleParameters *params);

	/// <summary> Gets the scan circle diameter. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The scanning circle diameter, range 0 to 65535 (0 to 10 NT Units). </returns>
	/// <seealso cref="NT_SetCircleDiameter(char const * serialNo, WORD diameter)" />
	/// <seealso cref="NT_SetCircleParams(char const * serialNo, NT_CircleParameters *params)" />
	/// <seealso cref="NT_GetCircleParams(char const * serialNo, NT_CircleParameters *params)" />
	/// <seealso cref="NT_GetCircleDiameterLUT(char const * serialNo, NT_CircleDiameterLUT *LUT)" />
	/// <seealso cref="NT_SetCircleDiameterLUT(char const * serialNo, NT_CircleDiameterLUT *LUT)" />
	NANOTRAK_API WORD __cdecl NT_GetCircleDiameter(char const * serialNo);

	/// <summary> Sets the scan circle diameter. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="diameter"> The scanning circle diameter, range 0 to 65535 (0 to 10 NT Units). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_GetCircleDiameter(char const * serialNo)" />
	/// <seealso cref="NT_SetCircleParams(char const * serialNo, NT_CircleParameters *params)" />
	/// <seealso cref="NT_GetCircleParams(char const * serialNo, NT_CircleParameters *params)" />
	/// <seealso cref="NT_GetCircleDiameterLUT(char const * serialNo, NT_CircleDiameterLUT *LUT)" />
	/// <seealso cref="NT_SetCircleDiameterLUT(char const * serialNo, NT_CircleDiameterLUT *LUT)" />
	NANOTRAK_API short __cdecl NT_SetCircleDiameter(char const * serialNo, WORD diameter);

	/// <summary> Requests the scan circle diameter Lookup Table (LUT). </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_SetCircleDiameterLUT(char const * serialNo, NT_CircleDiameterLUT *LUT)" />
	/// <seealso cref="NT_GetCircleDiameterLUT(char const * serialNo, NT_CircleDiameterLUT *LUT)" />
	/// <seealso cref="NT_SetCircleParams(char const * serialNo, NT_CircleParameters *params)" />
	/// <seealso cref="NT_GetCircleParams(char const * serialNo, NT_CircleParameters *params)" />
	/// <seealso cref="NT_GetCircleDiameter(char const * serialNo)" />
	/// <seealso cref="NT_SetCircleDiameter(char const * serialNo, WORD diameter)" />
	NANOTRAK_API short __cdecl NT_RequestCircleDiameterLUT(char const * serialNo);

	/// <summary> Gets the scan circle diameter Lookup Table (LUT). </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="LUT"> Address of the NT_CircleDiameterLUT to receive the  scan circle diameter lookup table. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_SetCircleDiameterLUT(char const * serialNo, NT_CircleDiameterLUT *LUT)" />
	/// <seealso cref="NT_RequestCircleDiameterLUT(char const * serialNo)" />
	/// <seealso cref="NT_SetCircleParams(char const * serialNo, NT_CircleParameters *params)" />
	/// <seealso cref="NT_GetCircleParams(char const * serialNo, NT_CircleParameters *params)" />
	/// <seealso cref="NT_GetCircleDiameter(char const * serialNo)" />
	/// <seealso cref="NT_SetCircleDiameter(char const * serialNo, WORD diameter)" />
	NANOTRAK_API short __cdecl NT_GetCircleDiameterLUT(char const * serialNo, NT_CircleDiameterLUT *LUT);

	/// <summary> Sets the scan circle diameter Lookup Table (LUT). </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="LUT"> Address of the NT_CircleParameters containing the new scan circle diameter lookup table. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_GetCircleDiameterLUT(char const * serialNo, NT_CircleDiameterLUT *LUT)" />
	/// <seealso cref="NT_RequestCircleDiameterLUT(char const * serialNo)" />
	/// <seealso cref="NT_SetCircleParams(char const * serialNo, NT_CircleParameters *params)" />
	/// <seealso cref="NT_GetCircleParams(char const * serialNo, NT_CircleParameters *params)" />
	/// <seealso cref="NT_GetCircleDiameter(char const * serialNo)" />
	/// <seealso cref="NT_SetCircleDiameter(char const * serialNo, WORD diameter)" />
	NANOTRAK_API short __cdecl NT_SetCircleDiameterLUT(char const * serialNo, NT_CircleDiameterLUT *LUT);

	/// <summary> Requests the phase compensation parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_GetPhaseCompensationParams(char const * serialNo)" />
	/// <seealso cref="NT_SetPhaseCompensationParams(char const * serialNo, NT_HVComponent *params)" />
	NANOTRAK_API short __cdecl NT_RequestPhaseCompensationParams(char const * serialNo);

	/// <summary> Gets the phase compensation parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="params"> Address of the NT_HVComponent to receive the  phase compensation,<br />
	/// 				   range 0 to 65535, value = phase(degrees) * OscillatingFrequency / 360. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_RequesPhaseCompensationParams(char const * serialNo)" />
	/// <seealso cref="NT_SetPhaseCompensationParams(char const * serialNo, NT_HVComponent *params)" />
	/// <seealso cref="NT_SetCircleParams(char const * serialNo, NT_CircleParameters *params)" />
	/// <seealso cref="NT_GetCircleParams(char const * serialNo, NT_CircleParameters *params)" />
	NANOTRAK_API short __cdecl NT_GetPhaseCompensationParams(char const * serialNo, NT_HVComponent *params);

	/// <summary> Sets the phase compensation parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="params"> Address of the NT_HVComponent containing the new phase compensation<br />
	/// 				   range 0 to 65535, value = phase(degrees) * OscillatingFrequency / 360. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_RequesPhaseCompensationParams(char const * serialNo)" />
	/// <seealso cref="NT_GetPhaseCompensationParams(char const * serialNo, NT_HVComponent *params)" />
	/// <seealso cref="NT_SetCircleParams(char const * serialNo, NT_CircleParameters *params)" />
	/// <seealso cref="NT_GetCircleParams(char const * serialNo, NT_CircleParameters *params)" />
	NANOTRAK_API short __cdecl NT_SetPhaseCompensationParams(char const * serialNo, NT_HVComponent *params);

	/// <summary> Requests  the TIA range parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_GetTIArangeParams(char const * serialNo)" />
	/// <seealso cref="NT_SetTIArangeParams(char const * serialNo, KNA_TIARangeParameters *params)" />
	/// <seealso cref="NT_GetRangeMode(char const * serialNo, NT_TIARangeMode *mode, NT_OddOrEven *oddOrEven)" />
	/// <seealso cref="NT_SetRangeMode(char const * serialNo, NT_TIARangeMode mode, NT_OddOrEven oddOrEven)" />
	/// <seealso cref="NT_GetTIARange(char const * serialNo)" />
	/// <seealso cref="NT_SetTIARange(char const * serialNo, KNA_TIARange range)" />
	NANOTRAK_API short __cdecl NT_RequestTIArangeParams(char const * serialNo);

	/// <summary> Gets the TIA range parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="params"> Address of the KNA_TIARangeParameters to receive the  TIA range parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_SetTIArangeParams(char const * serialNo, KNA_TIARangeParameters *params)" />
	/// <seealso cref="NT_GetRangeMode(char const * serialNo, NT_TIARangeMode *mode, NT_OddOrEven *oddOrEven)" />
	/// <seealso cref="NT_SetRangeMode(char const * serialNo, NT_TIARangeMode mode, NT_OddOrEven oddOrEven)" />
	/// <seealso cref="NT_GetTIARange(char const * serialNo)" />
	/// <seealso cref="NT_SetTIARange(char const * serialNo, KNA_TIARange range)" />
	NANOTRAK_API short __cdecl NT_GetTIArangeParams(char const * serialNo, KNA_TIARangeParameters *params);

	/// <summary> Sets the TIA range parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="params"> Address of the KNA_TIARangeParameters containing the new TIA range parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_GetTIArangeParams(char const * serialNo)" />
	/// <seealso cref="NT_GetRangeMode(char const * serialNo, NT_TIARangeMode *mode, NT_OddOrEven *oddOrEven)" />
	/// <seealso cref="NT_SetRangeMode(char const * serialNo, NT_TIARangeMode mode, NT_OddOrEven oddOrEven)" />
	/// <seealso cref="NT_GetTIARange(char const * serialNo)" />
	/// <seealso cref="NT_SetTIARange(char const * serialNo, KNA_TIARange range)" />
	NANOTRAK_API short __cdecl NT_SetTIArangeParams(char const * serialNo, KNA_TIARangeParameters *params);

	/// <summary> Get the TIA Range Mode and OddEven mode. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="mode">	Address of the parameter to receive the TIA range mode.
	/// 					<list type=table>
	///							<item><term>Automatic Ranging at current range.</term><term>1</term></item>
	///							<item><term>Manual Ranging at current range.</term><term>2</term></item>
	///							<item><term>Manual Ranging using supplied range</term><term>3</term></item>
	///							<item><term>Automatic ranging using supplied range</term><term>4</term></item>
	/// 					</list> </param>
	/// <param name="oddOrEven"> Address of the parameter to receive the TIA odd or even state.
	/// 					<list type=table>
	///							<item><term>All TIA Ranges.</term><term>1</term></item>
	///							<item><term>Only use Odd TIA ranges.</term><term>2</term></item>
	///							<item><term>Only use even TIA ranges</term><term>3</term></item>
	/// 					</list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_GetTIArangeParams(char const * serialNo)" />
	/// <seealso cref="NT_SetTIArangeParams(char const * serialNo, KNA_TIARangeParameters *params)" />
	/// <seealso cref="NT_SetRangeMode(char const * serialNo, NT_TIARangeMode mode, NT_OddOrEven oddOrEven)" />
	/// <seealso cref="NT_GetTIARange(char const * serialNo)" />
	/// <seealso cref="NT_SetTIARange(char const * serialNo, KNA_TIARange range)" />
	NANOTRAK_API short __cdecl NT_GetRangeMode(char const * serialNo, NT_TIARangeMode *mode, NT_OddOrEven *oddOrEven);

	/// <summary> Get the TIA Range Mode and OddEven mode. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="mode">	The TIA range mode.
	/// 					<list type=table>
	///							<item><term>Automatic Ranging at current range.</term><term>1</term></item>
	///							<item><term>Manual Ranging at current range.</term><term>2</term></item>
	///							<item><term>Manual Ranging using supplied range</term><term>3</term></item>
	///							<item><term>Automatic ranging using supplied range</term><term>4</term></item>
	/// 					</list> </param>
	/// <param name="oddOrEven"> The TIA odd or even state.
	/// 					<list type=table>
	///							<item><term>All TIA Ranges.</term><term>1</term></item>
	///							<item><term>Only use Odd TIA ranges.</term><term>2</term></item>
	///							<item><term>Only use even TIA ranges</term><term>3</term></item>
	/// 					</list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_GetTIArangeParams(char const * serialNo)" />
	/// <seealso cref="NT_SetTIArangeParams(char const * serialNo, KNA_TIARangeParameters *params)" />
	/// <seealso cref="NT_GetRangeMode(char const * serialNo, NT_TIARangeMode *mode, NT_OddOrEven *oddOrEven)" />
	/// <seealso cref="NT_GetTIARange(char const * serialNo)" />
	/// <seealso cref="NT_SetTIARange(char const * serialNo, KNA_TIARange range)" />
	NANOTRAK_API short __cdecl NT_SetRangeMode(char const * serialNo, NT_TIARangeMode mode, NT_OddOrEven oddOrEven);

	/// <summary> Gets the TIA range. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The range value, 
	/// 					<list type=table>
	///								<item><term>0-5nA range.</term><term>3</term></item>
	///								<item><term>0-16.6nA range.</term><term>4</term></item>
	///								<item><term>0-50nA range.</term><term>5</term></item>
	///								<item><term>0-166nA range.</term><term>6</term></item>
	///								<item><term>0-500nA range.</term><term>7</term></item>
	///								<item><term>0-1.66uA range.</term><term>8</term></item>
	///								<item><term>0-5uA range.</term><term>9</term></item>
	///								<item><term>0-16.6uA range.</term><term>10</term></item>
	///								<item><term>0-50uA range.</term><term>11</term></item>
	///								<item><term>0-166uA range.</term><term>12</term></item>
	///								<item><term>0-500uA range.</term><term>13</term></item>
	///								<item><term>0-1.66mA range.</term><term>14</term></item>
	///								<item><term>0-5mA range.</term><term>15</term></item>
	///							  </list>  </returns>
	/// <seealso cref="NT_RequesTIArangeParams(char const * serialNo)" />
	/// <seealso cref="NT_GetTIArangeParams(char const * serialNo)" />
	/// <seealso cref="NT_SetTIArangeParams(char const * serialNo, KNA_TIARangeParameters *params)" />
	/// <seealso cref="NT_GetRangeMode(char const * serialNo, NT_TIARangeMode *mode, NT_OddOrEven *oddOrEven)" />
	/// <seealso cref="NT_SetRangeMode(char const * serialNo, NT_TIARangeMode mode, NT_OddOrEven oddOrEven)" />
	/// <seealso cref="NT_SetTIARange(char const * serialNo, KNA_TIARange range)" />
	NANOTRAK_API KNA_TIARange __cdecl NT_GetTIARange(char const * serialNo);

	/// <summary> Sets TIA range. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="range">	The TIA range.
	/// 					<list type=table>
	///								<item><term>0-5nA range.</term><term>3</term></item>
	///								<item><term>0-16.6nA range.</term><term>4</term></item>
	///								<item><term>0-50nA range.</term><term>5</term></item>
	///								<item><term>0-166nA range.</term><term>6</term></item>
	///								<item><term>0-500nA range.</term><term>7</term></item>
	///								<item><term>0-1.66uA range.</term><term>8</term></item>
	///								<item><term>0-5uA range.</term><term>9</term></item>
	///								<item><term>0-16.6uA range.</term><term>10</term></item>
	///								<item><term>0-50uA range.</term><term>11</term></item>
	///								<item><term>0-166uA range.</term><term>12</term></item>
	///								<item><term>0-500uA range.</term><term>13</term></item>
	///								<item><term>0-1.66mA range.</term><term>14</term></item>
	///								<item><term>0-5mA range.</term><term>15</term></item>
	///							  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_RequesTIArangeParams(char const * serialNo)" />
	/// <seealso cref="NT_GetTIArangeParams(char const * serialNo)" />
	/// <seealso cref="NT_SetTIArangeParams(char const * serialNo, KNA_TIARangeParameters *params)" />
	/// <seealso cref="NT_GetRangeMode(char const * serialNo, NT_TIARangeMode *mode, NT_OddOrEven *oddOrEven)" />
	/// <seealso cref="NT_SetRangeMode(char const * serialNo, NT_TIARangeMode mode, NT_OddOrEven oddOrEven)" />
	/// <seealso cref="NT_GetTIARange(char const * serialNo)" />
	NANOTRAK_API short __cdecl NT_SetTIARange(char const * serialNo, KNA_TIARange range);

	/// <summary> Requests the control loop gain. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_GetGain(char const * serialNo)" />
	/// <seealso cref="NT_SetGain(char const * serialNo, short gain)" />
	NANOTRAK_API short __cdecl NT_RequestGain(char const * serialNo);

	/// <summary> Gets the control loop gain. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The gain value, range 100 to 10000. Typically ~600. </returns>
	/// <seealso cref="NT_RequesGain(char const * serialNo)" />
	/// <seealso cref="NT_SetGain(char const * serialNo, short gain)" />
	NANOTRAK_API short __cdecl NT_GetGain(char const * serialNo);

	/// <summary> Sets the control loop gain. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="gain"> The new Gain value, range 100 to 10000. Typically ~600.. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_RequesGain(char const * serialNo)" />
	/// <seealso cref="NT_GetGain(char const * serialNo)" />
	NANOTRAK_API short __cdecl NT_SetGain(char const * serialNo, short gain);

	/// <summary> Requests the NanoTrak Feedback Source. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_GetFeedbackSource(char const * serialNo)" />
	/// <seealso cref="NT_SetFeedbackSource(char const * serialNo, KNA_FeedbackSource input)" />
	NANOTRAK_API short __cdecl NT_RequestFeedbackSource(char const * serialNo);

	/// <summary> Gets the NanoTrak feedback source. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device feedback source
	/// 					<list type=table>
	///							<item><term>TIA value</term><term>1</term></item>
	///							<item><term>BNC 1v range</term><term>2</term></item>
	///							<item><term>BNC 2v range</term><term>3</term></item>
	///							<item><term>BNC 5v range</term><term>4</term></item>
	///							<item><term>BNC 10v range</term><term>5</term></item>
	/// 					 </list> </returns>
	/// <seealso cref="NT_RequesFeedbackSource(char const * serialNo)" />
	/// <seealso cref="NT_SetFeedbackSource(char const * serialNo, KNA_FeedbackSource input)" />
	NANOTRAK_API KNA_FeedbackSource __cdecl NT_GetFeedbackSource(char const * serialNo);

	/// <summary> Sets the NanoTrak feedback source. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="input"> The device feedback source.
	/// 					 <list type=table>
	///							<item><term>TIA value</term><term>1</term></item>
	///							<item><term>BNC 1v range</term><term>2</term></item>
	///							<item><term>BNC 2v range</term><term>3</term></item>
	///							<item><term>BNC 5v range</term><term>4</term></item>
	///							<item><term>BNC 10v range</term><term>5</term></item>
	/// 					 </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_RequesFeedbackSource(char const * serialNo)" />
	/// <seealso cref="NT_GetFeedbackSource(char const * serialNo)" />
	NANOTRAK_API short __cdecl NT_SetFeedbackSource(char const * serialNo, KNA_FeedbackSource input);

	/// <summary> Gets the LED brightness. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> Intensity from 0 (off) to 255. </returns>
	/// <seealso cref="NT_SetLEDBrightness(char const * serialNo, short brightness)" />
	NANOTRAK_API short __cdecl NT_GetLEDBrightness(char const * serialNo);

	/// <summary> Sets the LED brightness. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="brightness"> Intensity from 0 (off) to 255. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_GetLEDBrightness(char const * serialNo)" />
	NANOTRAK_API short __cdecl NT_SetLEDBrightness(char const * serialNo, short brightness);

	/// <summary> Requests the input/output options. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_GetIOsettings(const char * serialNo, KNA_HighVoltageRange *highVoltageOutRange, KNA_HighOutputVoltageRoute *highVoltageOutputRoute)" />
	/// <seealso cref="NT_SetIOsettings(const char * serialNo, KNA_HighVoltageRange highVoltageOutRange, KNA_HighOutputVoltageRoute highVoltageOutputRoute)" />
	/// <seealso cref="NT_GetIOsettingsBlock(const char * serialNo, KNA_IOSettings *IOsettings)" />
	/// <seealso cref="NT_SetIOsettingsBlock(const char * serialNo, KNA_IOSettings *IOsettings)" />
	NANOTRAK_API short __cdecl NT_RequestIOsettings(char const * serialNo);

	/// <summary> Gets the input/output settings in a block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="IOsettings"> Address of the KNA_IOSettings to receive the input/output settings. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_RequestIOsettings(const char * serialNo)" />
	/// <seealso cref="NT_SetIOsettings(const char * serialNo, KNA_HighVoltageRange highVoltageOutRange, KNA_HighOutputVoltageRoute highVoltageOutputRoute)" />
	/// <seealso cref="NT_GetIOsettings(char const * serialNo, KNA_HighVoltageRange *highVoltageOutRange, KNA_HighOutputVoltageRoute *highVoltageOutputRoute)" />
	/// <seealso cref="NT_SetIOsettingsBlock(const char * serialNo, KNA_IOSettings *IOsettings)" />
	NANOTRAK_API short __cdecl NT_GetIOsettingsBlock(const char * serialNo, KNA_IOSettings *IOsettings);

	/// <summary> Sets the input/output options in a block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="IOsettings"> Address of the KNA_IOSettings containing the new input/output settings.. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_RequestIOsettings(const char * serialNo)" />
	/// <seealso cref="NT_GetIOsettings(char const * serialNo, KNA_HighVoltageRange *highVoltageOutRange, KNA_HighOutputVoltageRoute *highVoltageOutputRoute)" />
	/// <seealso cref="NT_GetIOsettingsBlock(const char * serialNo, KNA_IOSettings *IOsettings)" />
	/// <seealso cref="NT_SetIOsettingsBlock(const char * serialNo, KNA_IOSettings *IOsettings)" />
	NANOTRAK_API short __cdecl NT_SetIOsettingsBlock(const char * serialNo, KNA_IOSettings *IOsettings);

	/// <summary> Gets the input/output options. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="highVoltageOutRange">Default Value = 0, (CH1_75V | CH2_75V) </Remarks>
	///		<list type=table>
	///			<item><term>CH1_150v (0x01).</term><term>Set Channel 1 range to 150v when set otherwise 75v</term></item>
	///			<item><term>CH2_150v (0x01).</term><term>Set Channel 2 range to 150v when set otherwise 75v</term></item>
	///		</list>  </param>
	/// <param name="highVoltageOutputRoute"> Default Value = 0, (ExtIn_PIN | ExtOut_Dis) </Remarks>
	///		<list type=table>
	///			<item><term>ExtIn_SMA (0x01).</term><term>Set input from SMA otherwise input from PIn</term></item>
	///			<item><term>ExtOut_SMA (0x10).</term><term>Set output via SMA otherwise disable SMA output</term></item>
	///			<item><term>EnableInputBoost (0x100).</term><term>Enable Input Boost when set</term></item>
	///		</list>   </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_RequestIOsettings(const char * serialNo)" />
	/// <seealso cref="NT_SetIOsettings(const char * serialNo, KNA_HighVoltageRange highVoltageOutRange, KNA_HighOutputVoltageRoute highVoltageOutputRoute)" />
	/// <seealso cref="NT_GetIOsettingsBlock(const char * serialNo, KNA_IOSettings *IOsettings)" />
	/// <seealso cref="NT_SetIOsettingsBlock(const char * serialNo, KNA_IOSettings *IOsettings)" />
	NANOTRAK_API short __cdecl NT_GetIOsettings(char const * serialNo, KNA_HighVoltageRange *highVoltageOutRange, KNA_HighOutputVoltageRoute *highVoltageOutputRoute);

	/// <summary> Sets the input/output options. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="highVoltageOutRange">Default Value = 0, (CH1_75V | CH2_75V) </Remarks>
	///		<list type=table>
	///			<item><term>CH1_150v (0x01).</term><term>Set Channel 1 range to 150v when set otherwise 75v</term></item>
	///			<item><term>CH2_150v (0x01).</term><term>Set Channel 2 range to 150v when set otherwise 75v</term></item>
	///		</list>  </param>
	/// <param name="highVoltageOutputRoute"> Default Value = 0, (ExtIn_PIN | ExtOut_Dis) </Remarks>
	///		<list type=table>
	///			<item><term>ExtIn_SMA (0x01).</term><term>Set input from SMA otherwise input from PIn</term></item>
	///			<item><term>ExtOut_SMA (0x10).</term><term>Set output via SMA otherwise disable SMA output</term></item>
	///			<item><term>EnableInputBoost (0x100).</term><term>Enable Input Boost when set</term></item>
	///		</list>   </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_RequestIOsettings(const char * serialNo)" />
	/// <seealso cref="NT_GetIOsettings(const char * serialNo, KNA_HighVoltageRange *highVoltageOutRange, KNA_HighOutputVoltageRoute *highVoltageOutputRoute)" />
	/// <seealso cref="NT_SetIOsettingsBlock(const char * serialNo, KNA_IOSettings *IOsettings)" />
	/// <seealso cref="NT_GetIOsettings(char const * serialNo, KNA_HighVoltageRange *highVoltageOutRange, KNA_HighOutputVoltageRoute *highVoltageOutputRoute)" />
	NANOTRAK_API short __cdecl NT_SetIOsettings(char const * serialNo, KNA_HighVoltageRange highVoltageOutRange, KNA_HighOutputVoltageRoute highVoltageOutputRoute);

	/// <summary> Gets the feedback mode. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel"> The channel (1 or 2)</param>
	/// <returns> The feedback mode <list type=table>
	///				<item><term>Open Loop</term><term>1</term></item>
	///				<item><term>Closed Loop</term><term>2</term></item>
	///				<item><term>Open Loop smoothed</term><term>3</term></item>
	///				<item><term>Closed Loop smoothed</term><term>4</term></item>
	/// 		  </list> </returns>
	/// <seealso cref="NT_RequestFeedbackMode(char const * serialNo, KNA_Channels channel)" />
	/// <seealso cref="NT_SetFeedbackMode(char const * serialNo, KNA_Channels channel, KNA_FeedbackModeTypes mode)" />
	NANOTRAK_API KNA_FeedbackModeTypes __cdecl NT_GetFeedbackMode(char const * serialNo, KNA_Channels channel);

	/// <summary>	Requests the feedback mode from the device. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel"> The channel (1 or 2)</param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_GetFeedbackMode(char const * serialNo, KNA_Channels channel)" />
	/// <seealso cref="NT_SetFeedbackMode(char const * serialNo, KNA_Channels channel, KNA_FeedbackModeTypes mode)" />
	NANOTRAK_API bool __cdecl NT_RequestFeedbackMode(char const * serialNo, KNA_Channels channel);

	/// <summary> Sets the feedback mode. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel"> The channel (1 or 2)</param>
	/// <param name="mode"> The feedback mode <list type=table>
	///				<item><term>Open Loop</term><term>1</term></item>
	///				<item><term>Closed Loop</term><term>2</term></item>
	///				<item><term>Open Loop smoothed</term><term>3</term></item>
	///				<item><term>Closed Loop smoothed</term><term>4</term></item>
	/// 		  </list>. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_RequestFeedbackMode(char const * serialNo, KNA_Channels channel)" />
	/// <seealso cref="NT_GetFeedbackMode(char const * serialNo, KNA_Channels channel)" />
	NANOTRAK_API short __cdecl NT_SetFeedbackMode(char const * serialNo, KNA_Channels channel, KNA_FeedbackModeTypes mode);

	/// <summary> Requests that the feedback loop constants be read from the device. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel"> The channel (1 or 2)</param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="NT_GetFeedbackLoopPIconsts(char const * serialNo, KNA_Channels channel, short * proportionalTerm, short * integralTerm)" />
	/// <seealso cref="NT_SetFeedbackLoopPIconsts(char const * serialNo, KNA_Channels channel, short proportionalTerm, short integralTerm)" />
	/// <seealso cref="NT_GetFeedbackLoopPIconstsBlock(const char * serialNo, KNA_Channels channel, KNA_FeedbackLoopConstants *proportionalAndIntegralConstants)" />
	/// <seealso cref="NT_SetFeedbackLoopPIconstsBlock(const char * serialNo, KNA_Channels channel, KNA_FeedbackLoopConstants *proportionalAndIntegralConstants)" />
	NANOTRAK_API bool __cdecl NT_RequestFeedbackLoopPIconsts(char const * serialNo, KNA_Channels channel);

	/// <summary> Gets the feedback loop constants. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel"> The channel (1 or 2)</param>
	/// <param name="proportionalTerm"> The address of the parameter to receive the proportional parameter. </param>
	/// <param name="integralTerm"> The address of the parameter to receive the integral parameter. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_RequestFeedbackLoopPIconsts(char const * serialNo, KNA_Channels channel)" />
	/// <seealso cref="NT_SetFeedbackLoopPIconsts(char const * serialNo, KNA_Channels channel, short proportionalTerm, short integralTerm)" />
	/// <seealso cref="NT_GetFeedbackLoopPIconstsBlock(const char * serialNo, KNA_Channels channel, KNA_FeedbackLoopConstants *proportionalAndIntegralConstants)" />
	/// <seealso cref="NT_SetFeedbackLoopPIconstsBlock(const char * serialNo, KNA_Channels channel, KNA_FeedbackLoopConstants *proportionalAndIntegralConstants)" />
	NANOTRAK_API short __cdecl NT_GetFeedbackLoopPIconsts(char const * serialNo, KNA_Channels channel, short * proportionalTerm, short * integralTerm);

	/// <summary> Sets the feedback loop constants. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel"> The channel (1 or 2)</param>
	/// <param name="proportionalTerm"> The proportional term of the PID loop from 0 to 255. </param>
	/// <param name="integralTerm"> The integral term of the PID loop from 0 to 255. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_RequestFeedbackLoopPIconsts(char const * serialNo, KNA_Channels channel)" />
	/// <seealso cref="NT_GetFeedbackLoopPIconsts(char const * serialNo, KNA_Channels channel, short * proportionalTerm, short * integralTerm)" />
	/// <seealso cref="NT_SetFeedbackLoopPIconsts(char const * serialNo, KNA_Channels channel, short proportionalTerm, short integralTerm)" />
	/// <seealso cref="NT_SetFeedbackLoopPIconstsBlock(const char * serialNo, KNA_Channels channel, KNA_FeedbackLoopConstants *proportionalAndIntegralConstants)" />
	NANOTRAK_API short __cdecl NT_SetFeedbackLoopPIconsts(char const * serialNo, KNA_Channels channel, short proportionalTerm, short integralTerm);

	/// <summary> Gets the feedback loop constants in a block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel"> The channel (1 or 2)</param>
	/// <param name="proportionalAndIntegralConstants"> The address of the KNA_FeedbackLoopConstants to receive the feedback loop constants. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_GetFeedbackLoopPIconsts(char const * serialNo, KNA_Channels channel, short * proportionalTerm, short * integralTerm)" />
	/// <seealso cref="NT_SetFeedbackLoopPIconsts(char const * serialNo, KNA_Channels channel, short proportionalTerm, short integralTerm)" />
	/// <seealso cref="NT_SetFeedbackLoopPIconstsBlock(const char * serialNo, KNA_Channels channel, KNA_FeedbackLoopConstants *proportionalAndIntegralConstants)" />
	NANOTRAK_API short __cdecl NT_GetFeedbackLoopPIconstsBlock(const char * serialNo, KNA_Channels channel, KNA_FeedbackLoopConstants *proportionalAndIntegralConstants);

	/// <summary> Sets the feedback loop constants in a block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel"> The channel (1 or 2)</param>
	/// <param name="proportionalAndIntegralConstants"> The address of the KNA_FeedbackLoopConstants containing the new feedback loop constants. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_GetFeedbackLoopPIconsts(char const * serialNo, KNA_Channels channel, short * proportionalTerm, short * integralTerm)" />
	/// <seealso cref="NT_SetFeedbackLoopPIconsts(char const * serialNo, KNA_Channels channel, short proportionalTerm, short integralTerm)" />
	/// <seealso cref="NT_GetFeedbackLoopPIconstsBlock(const char * serialNo, KNA_Channels channel, KNA_FeedbackLoopConstants *proportionalAndIntegralConstants)" />
	NANOTRAK_API short __cdecl NT_SetFeedbackLoopPIconstsBlock(const char * serialNo, KNA_Channels channel, KNA_FeedbackLoopConstants *proportionalAndIntegralConstants);

	/// <summary> Request that the MMI Parameters for the KCube Display Interface be read from the device. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	NANOTRAK_API  bool __cdecl NT_RequestMMIParams(char const * serialNo);

	/// \deprecated
	/// <summary> Get the MMI Parameters for the KCube Display Interface. </summary>
	/// <remarks> superceded by <see cref="CC_SetMMIParams(char const * serialNo, KMOT_WheelMode wheelMode, __int32 wheelMaxVelocity, __int32 wheelAcceleration, KMOT_WheelDirectionSense directionSense, __int32 presetPosition1, __int32 presetPosition2, __int16 displayIntensity)"/> </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="wheelAdjustRate">  The wheel move at voltage rate.
	/// 					<list type=table>
	///							<item><term>0</term><term>Low voltage change rate</term></item>
	///							<item><term>1</term><term>Medium voltage change rate.></item>
	///							<item><term>2</term><term>High voltage change rate.</term></item>
	/// 					</list> </param>
	/// <param name="displayIntensity">	    The display intensity, range 0 to 100%. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_SetMMIParams(char const * serialNo, KNA_WheelAdjustRate voltageAdjustRate, __int16 displayIntensity)" />
	/// <seealso cref="NT_SetMMIParamsBlock(const char * serialNo, KNA_MMIParams *mmiParams)" />
	/// <seealso cref="NT_GetMMIParamsBlock(const char * serialNo, KNA_MMIParams *mmiParams)" />
	NANOTRAK_API  short __cdecl NT_GetMMIParams(char const * serialNo, KNA_WheelAdjustRate *wheelAdjustRate, __int16 *displayIntensity);

	/// <summary> Set the MMI Parameters for the KCube Display Interface. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="wheelAdjustRate">  The wheel move at voltage rate.
	/// 					<list type=table>
	///							<item><term>0</term><term>Low voltage change rate</term></item>
	///							<item><term>1</term><term>Medium voltage change rate.></item>
	///							<item><term>2</term><term>High voltage change rate.</term></item>
	/// 					</list> </param>
	/// <param name="displayIntensity">	    The display intensity, range 0 to 100%. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_GetMMIParamsExt(char const * serialNo, KNA_WheelMode *wheelMode, KNA_WheelAdjustRate *voltageAdjustRate, __int32 *voltageStep, KNA_WheelDirectionSense *directionSense, __int32 *presetVoltage1, __int32 *presetVoltage2, __int16 *displayIntensity)" />
	/// <seealso cref="NT_SetMMIParamsBlock(const char * serialNo, KNA_MMIParams *mmiParams)" />
	/// <seealso cref="NT_GetMMIParamsBlock(const char * serialNo, KNA_MMIParams *mmiParams)" />
	NANOTRAK_API short __cdecl NT_SetMMIParams(char const * serialNo, KNA_WheelAdjustRate wheelAdjustRate, __int16 displayIntensity);

	/// <summary> Requests that the trigger config parameters are read from the device. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="NT_GetTriggerConfigParams(char const * serialNo, KNA_TriggerPortMode *trigger1Mode, KNA_TriggerPortPolarity *trigger1Polarity, KNA_TriggerPortMode *trigger2Mode, KNA_TriggerPortPolarity *trigger2Polarity)" />
	/// <seealso cref="NT_SetTriggerConfigParams(char const * serialNo, KNA_TriggerPortMode trigger1Mode, KNA_TriggerPortPolarity trigger1Polarity, KNA_TriggerPortMode trigger2Mode, KNA_TriggerPortPolarity trigger2Polarity)" />
	NANOTRAK_API bool __cdecl NT_RequestTriggerConfigParams(char const * serialNo);

	/// <summary> Get the Trigger Configuration Parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="trigger1Mode">	    The trigger 1 mode.<list type=table>
	///				<item><term>0</term><term>Trigger disabled</term></item>
	///				<item><term>1</term><term>Trigger Input - set as latched</term></item>
	///				<item><term>2</term><term>Trigger Tracking - set as tracking</term></item>
	///				<item><term>3</term><term>Trigger Home - Trigger when homed</term></item>
	///				<item><term>10</term><term>Trigger Output - Trigger Output</term></item>
	///				<item><term>11</term><term>Trigger Output - Trigger when tracking</term></item>
	///		 		  </list></param>
	/// <param name="trigger1Polarity"> The trigger 1 polarity.<list type=table>
	///						<item><term>1</term><term>Output high when set</term></item>
	///						<item><term>2</term><term>Output low when set</term></item>
	///		 		  </list> </param>
	/// <param name="trigger2Mode">	    The trigger 2 mode.<list type=table>
	///				<item><term>0</term><term>Trigger disabled</term></item>
	///				<item><term>1</term><term>Trigger Input - set as latched</term></item>
	///				<item><term>2</term><term>Trigger Tracking - set as tracking</term></item>
	///				<item><term>3</term><term>Trigger Home - Trigger when homed</term></item>
	///				<item><term>10</term><term>Trigger Output - Trigger Output</term></item>
	///				<item><term>11</term><term>Trigger Output - Trigger when tracking</term></item>
	///		 		  </list></param>
	/// <param name="trigger2Polarity"> The trigger 2 polarity.<list type=table>
	///						<item><term>1</term><term>Output high when set</term></item>
	///						<item><term>2</term><term>Output low when set</term></item>
	///		 		  </list> </param>
	///	<returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	///	<seealso cref="NT_RequestTriggerConfigParams(char const * serialNo)" />
	///	<seealso cref="NT_SetTriggerConfigParams(char const * serialNo, KNA_TriggerPortMode trigger1Mode, KNA_TriggerPortPolarity trigger1Polarity, KNA_TriggerPortMode trigger2Mode, KNA_TriggerPortPolarity trigger2Polarity)" />
	/// <seealso cref="NT_SetTriggerConfigParamsBlock(const char * serialNo, KNA_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="NT_GetTriggerConfigParamsBlock(const char * serialNo, KNA_TriggerConfig *triggerConfigParams)" />
	NANOTRAK_API  short __cdecl NT_GetTriggerConfigParams(char const * serialNo, KNA_TriggerPortMode *trigger1Mode, KNA_TriggerPortPolarity *trigger1Polarity, KNA_TriggerPortMode *trigger2Mode, KNA_TriggerPortPolarity *trigger2Polarity);

	/// <summary> Set the Trigger Configuration Parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="trigger1Mode">	    The trigger 1 mode.<list type=table>
	///				<item><term>0</term><term>Trigger disabled</term></item>
	///				<item><term>1</term><term>Trigger Input - set as latched</term></item>
	///				<item><term>2</term><term>Trigger Tracking - set as tracking</term></item>
	///				<item><term>3</term><term>Trigger Home - Trigger when homed</term></item>
	///				<item><term>10</term><term>Trigger Output - Trigger Output</term></item>
	///				<item><term>11</term><term>Trigger Output - Trigger when tracking</term></item>
	///		 		  </list></param>
	/// <param name="trigger1Polarity"> The trigger 1 polarity.<list type=table>
	///						<item><term>1</term><term>Output high when set</term></item>
	///						<item><term>2</term><term>Output low when set</term></item>
	///		 		  </list> </param>
	/// <param name="trigger2Mode">	    The trigger 2 mode.<list type=table>
	///				<item><term>0</term><term>Trigger disabled</term></item>
	///				<item><term>1</term><term>Trigger Input - set as latched</term></item>
	///				<item><term>2</term><term>Trigger Tracking - set as tracking</term></item>
	///				<item><term>3</term><term>Trigger Home - Trigger when homed</term></item>
	///				<item><term>10</term><term>Trigger Output - Trigger Output</term></item>
	///				<item><term>11</term><term>Trigger Output - Trigger when tracking</term></item>
	///		 		  </list></param>
	/// <param name="trigger2Polarity"> The trigger 2 polarity.<list type=table>
	///						<item><term>1</term><term>Output high when set</term></item>
	///						<item><term>2</term><term>Output low when set</term></item>
	///		 		  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	///	<seealso cref="NT_RequestTriggerConfigParams(char const * serialNo)" />
	/// <seealso cref="NT_GetTriggerConfigParams(char const * serialNo, KNA_TriggerPortMode *trigger1Mode, KNA_TriggerPortPolarity *trigger1Polarity, KNA_TriggerPortMode *trigger2Mode, KNA_TriggerPortPolarity *trigger2Polarity)" />
	/// <seealso cref="NT_SetTriggerConfigParamsBlock(const char * serialNo, KNA_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="NT_GetTriggerConfigParamsBlock(const char * serialNo, KNA_TriggerConfig *triggerConfigParams)" />
	NANOTRAK_API short __cdecl NT_SetTriggerConfigParams(char const * serialNo, KNA_TriggerPortMode trigger1Mode, KNA_TriggerPortPolarity trigger1Polarity, KNA_TriggerPortMode trigger2Mode, KNA_TriggerPortPolarity trigger2Polarity);

	/// <summary> Gets the MMI parameters for the device. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="mmiParams"> Options for controlling the mmi. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_GetMMIParamsExt(char const * serialNo, KNA_WheelMode *wheelMode, KNA_WheelAdjustRate *voltageAdjustRate, __int32 *voltageStep, KNA_WheelDirectionSense *directionSense, __int32 *presetVoltage1, __int32 *presetVoltage2, __int16 *displayIntensity, __int16 *displayTimeout, __int16 *displayDimIntensity)" />
	/// <seealso cref="NT_SetMMIParamsExt(char const * serialNo, KNA_WheelMode wheelMode, KNA_WheelAdjustRate voltageAdjustRate, __int32 voltageStep, KNA_WheelDirectionSense directionSense, __int32 presetVoltage1, __int32 presetVoltage2, __int16 displayIntensity, __int16 displayTimeout, __int16 displayDimIntensity)" />
	/// <seealso cref="NT_SetMMIParamsBlock(const char * serialNo, KNA_MMIParams *mmiParams)" />
	NANOTRAK_API short __cdecl NT_GetMMIParamsBlock(char const * serialNo, KNA_MMIParams *mmiParams);

	/// <summary> Sets the MMI parameters for the device. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="mmiParams"> Options for controlling the mmi. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_GetMMIParamsExt(char const * serialNo, KNA_WheelMode *wheelMode, KNA_WheelAdjustRate *voltageAdjustRate, __int32 *voltageStep, KNA_WheelDirectionSense *directionSense, __int32 *presetVoltage1, __int32 *presetVoltage2, __int16 *displayIntensity, __int16 *displayTimeout, __int16 *displayDimIntensity)" />
	/// <seealso cref="NT_SetMMIParamsExt(char const * serialNo, KNA_WheelMode wheelMode, KNA_WheelAdjustRate voltageAdjustRate, __int32 voltageStep, KNA_WheelDirectionSense directionSense, __int32 presetVoltage1, __int32 presetVoltage2, __int16 displayIntensity, __int16 displayTimeout, __int16 displayDimIntensity)" />
	/// <seealso cref="NT_GetMMIParamsBlock(const char * serialNo, KNA_MMIParams *mmiParams)" />
	NANOTRAK_API short __cdecl NT_SetMMIParamsBlock(char const * serialNo, KNA_MMIParams *mmiParams);

	/// <summary> Gets the trigger configuration parameters block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="triggerConfigParams"> Options for controlling the trigger configuration. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_GeTriggerConfigParams(char const * serialNo, KNA_TriggerPortMode *trigger1Mode, KNA_TriggerPortPolarity *trigger1Polarity, KNA_TriggerPortMode *trigger2Mode, KNA_TriggerPortPolarity *trigger2Polarity)" />
	/// <seealso cref="NT_SetTriggerConfigParams(char const * serialNo, KNA_TriggerPortMode trigger1Mode, KNA_TriggerPortPolarity trigger1Polarity, KNA_TriggerPortMode trigger2Mode, KNA_TriggerPortPolarity trigger2Polarity)" />
	/// <seealso cref="NT_SetTriggerConfigParamsBlock(const char * serialNo, KNA_TriggerConfig *triggerConfigParams)" />
	NANOTRAK_API short __cdecl NT_GetTriggerConfigParamsBlock(char const * serialNo, KNA_TriggerConfig *triggerConfigParams);

	/// <summary> Sets the trigger configuration parameters block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="triggerConfigParams"> Options for controlling the trigger configuration. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_GeTriggerConfigParams(char const * serialNo, KNA_TriggerPortMode *trigger1Mode, KNA_TriggerPortPolarity *trigger1Polarity, KNA_TriggerPortMode *trigger2Mode, KNA_TriggerPortPolarity *trigger2Polarity)" />
	/// <seealso cref="NT_SetTriggerConfigParams(char const * serialNo, KNA_TriggerPortMode trigger1Mode, KNA_TriggerPortPolarity trigger1Polarity, KNA_TriggerPortMode trigger2Mode, KNA_TriggerPortPolarity trigger2Polarity)" />
	/// <seealso cref="NT_GetTriggerConfigParamsBlock(const char * serialNo, KNA_TriggerConfig *triggerConfigParams)" />
	NANOTRAK_API short __cdecl NT_SetTriggerConfigParamsBlock(char const * serialNo, KNA_TriggerConfig *triggerConfigParams);

	/// <summary> clears the message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <seealso cref="NT_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="NT_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="NT_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="NT_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	NANOTRAK_API void __cdecl NT_ClearMessageQueue(char const * serialNo);

	/// <summary> Registers a callback on the message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="functionPointer"> A function pointer to be called whenever messages are received. </param>
	/// <seealso cref="NT_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="NT_ClearMessageQueue(char const * serialNo)" />
	/// <seealso cref="NT_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="NT_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	NANOTRAK_API void __cdecl NT_RegisterMessageCallback(char const * serialNo, void (* functionPointer)());

	/// <summary> Gets the MessageQueue size. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> number of messages in the queue. </returns>
	/// <seealso cref="NT_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="NT_ClearMessageQueue(char const * serialNo)" />
	/// <seealso cref="NT_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="NT_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	NANOTRAK_API int __cdecl NT_MessageQueueSize(char const * serialNo);

	/// <summary> Get the next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="NT_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="NT_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="NT_ClearMessageQueue(char const * serialNo)" />
	/// <seealso cref="NT_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	NANOTRAK_API bool __cdecl NT_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Wait for next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="NT_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="NT_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="NT_ClearMessageQueue(char const * serialNo)" />
	/// <seealso cref="NT_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	NANOTRAK_API bool __cdecl NT_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary>	Requests a TIA reading. </summary>
	/// <remarks> This needs to be called to get the device to send it's current reading.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="NT_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref=" NT_GetReading(const char * serialNo, KNA_TIAReading *reading)" />
	/// <seealso cref="NT_StartPolling(char const * serialNo, int milliseconds)" />
	NANOTRAK_API short __cdecl NT_RequestReading(char const * serialNo);

	/// <summary> Gets a reading. </summary>
	/// <remarks> This returns the latest reading received from the device.<br />
	/// 		  To get new readings, use <see cref="NT_RequestReading(char const * serialNo)" />
	///			  or use <see cref="NT_RequestStatus(char const * serialNo)" />
	/// 		  or use the polling functions, <see cref="NT_StartPolling(char const * serialNo, int milliseconds)" />.  </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="reading"> Address of the KNA_TIAReading to recieve the TIA data. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="NT_RequestReading(char const * serialNo)" />
	/// <seealso cref="NT_RequestStatus(char const * serialNo)" />
	/// <seealso cref="NT_StartPolling(char const * serialNo, int milliseconds)" />
	NANOTRAK_API short __cdecl NT_GetReading(const char * serialNo, KNA_TIAReading *reading);

	/// <summary> Requests the status bits and reading. </summary>
	/// <remarks> This needs to be called to get the device to send it's current status.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="NT_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="NT_RequestReading(char const * serialNo)" />
	/// <seealso cref="NT_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="NT_GetReading(const char * serialNo, KNA_TIAReading *reading)" />
	/// <seealso cref="NT_GetStatusBits(char const * serialNo)" />
	/// <seealso cref="NT_StartPolling(char const * serialNo, int milliseconds)" />
	NANOTRAK_API short __cdecl NT_RequestStatus(char const * serialNo);

	/// <summary> Request the status bits which identify the current device state. </summary>
	/// <remarks> This needs to be called to get the device to send it's current status bits.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="NT_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="NT_GetStatusBits(char const * serialNo)" />
	/// <seealso cref="NT_StartPolling(char const * serialNo, int milliseconds)" />
	NANOTRAK_API short __cdecl NT_RequestStatusBits(char const * serialNo);

	/// <summary>Get the current status bits. </summary>
	/// <remarks> This returns the latest status bits received from the device.<br />
	/// 		  To get new status bits, use <see cref="NT_RequestStatusBits(char const * serialNo)" />
	///			  or use <see cref="NT_RequestStatus(char const * serialNo)" />
	/// 		  or use the polling functions, <see cref="NT_StartPolling(char const * serialNo, int milliseconds)" />.  </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	The status bits from the device <list type=table>
	///				<item><term>0x00000001</term><term>Tracking (1=Tracking, 0=Latched).</term></item>
	///				<item><term>0x00000002</term><term>Tracking with Signal (1=With Signal, 0=No Signal).</term></item>
	///				<item><term>0x00000004</term><term>Tracking Channel A (1=Chan A Only, 0=Both Channels).</term></item>
	///				<item><term>0x00000008</term><term>Tracking Channel B (1=Chan B Only, 0=Both Channels).</term></item>
	///				<item><term>0x00000010</term><term>Auto-ranging (1=Auto Ranging, 0=Manual Ranging).</term></item>
	///				<item><term>0x00000020</term><term>Under Read (1=Under Reading, 0=Reading Within Range).</term></item>
	///				<item><term>0x00000040</term><term>Over Read (1=Over Reading, 0=Reading Within Range).</term></item>
	///				<item><term>0x00000100</term><term>For Future Use.</term></item>
	///				<item><term>0x00000200</term><term></term></item>
	///				<item><term>...</term><term></term></item>
	///				<item><term>0x00008000</term><term></term></item>
	///				<item><term>0x00010000</term><term>Channel A Connected (1=Connected, 0=Not Connected).</term></item>
	///				<item><term>0x00020000</term><term>Channel B Connected (1=Connected, 0=Not Connected).</term></item>
	///				<item><term>0x00040000</term><term>Channel A Enabled (1=Enabled, 0=Disabled).</term></item>
	///				<item><term>0x00080000</term><term>Channel B Enabled (1=Enabled, 0=Disabled).</term></item>
	///				<item><term>0x00100000</term><term>Channel A Control Mode (1=Closed Loop, 0=Open Loop).</term></item>
	///				<item><term>0x00200000</term><term>Channel B Control Mode (1=Closed Loop, 0=Open Loop).</term></item>
	///				<item><term>0x00400000</term><term>For Future Use.</term></item>
	///				<item><term>0x00800000</term><term></term></item>
	///				<item><term>...</term><term></term></item>
	///				<item><term>0x80000000</term><term></term></item>
	/// 		  </list> </returns>
	/// <seealso cref="NT_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="NT_RequestStatus(char const * serialNo)" />
	/// <seealso cref="NT_StartPolling(char const * serialNo, int milliseconds)" />
	NANOTRAK_API DWORD __cdecl NT_GetStatusBits(char const * serialNo);

	/// <summary> Starts the internal polling loop which continuously requests position and status. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="milliseconds">The milliseconds polling rate. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="NT_StopPolling(char const * serialNo)" />
	/// <seealso cref="NT_PollingDuration(char const * serialNo)" />
	/// <seealso cref="NT_RequestStatusBits(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	NANOTRAK_API bool __cdecl NT_StartPolling(char const * serialNo, int milliseconds);

	/// <summary> Gets the polling loop duration. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The time between polls in milliseconds or 0 if polling is not active. </returns>
	/// <seealso cref="NT_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="NT_StopPolling(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	NANOTRAK_API long __cdecl NT_PollingDuration(char const * serialNo);

	/// <summary> Stops the internal polling loop. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <seealso cref="NT_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="NT_PollingDuration(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	NANOTRAK_API void __cdecl NT_StopPolling(char const * serialNo);

	/// <summary> Gets the time in milliseconds since tha last message was received from the device. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="lastUpdateTimeMS"> The time since the last message was received in milliseconds. </param>
	/// <returns> True if monitoring is enabled otherwize False. </returns>
	/// <seealso cref="NT_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// <seealso cref="NT_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	NANOTRAK_API bool __cdecl NT_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS );

	/// <summary> Enables the last message monitoring timer. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="enable"> True to enable monitoring otherwise False to disable. </param>
	/// <param name="lastMsgTimeout"> The last message error timeout in ms. 0 to disable. </param>
	/// <seealso cref="NT_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="NT_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	NANOTRAK_API void __cdecl NT_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout );

	/// <summary> Queries if the time since the last message has exceeded the lastMsgTimeout set by <see cref="NT_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )"/>. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> True if last message timer has elapsed, False if monitoring is not enabled or if time of last message received is less than lastMsgTimeout. </returns>
	/// <seealso cref="NT_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="NT_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	NANOTRAK_API bool __cdecl NT_HasLastMsgTimerOverrun(char const * serialNo);

	/// <summary> Requests that all settings are download from device. </summary>
	/// <remarks> This function requests that the device upload all it's settings to the DLL.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	NANOTRAK_API short __cdecl NT_RequestSettings(char const * serialNo);

	/// <summary>	Request an XY scan. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns>	A short. </returns>
	NANOTRAK_API short __cdecl NT_RequestXYScan(char const * serialNo);

	/// <summary>	Stops an XY scan. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns>	A short. </returns>
	NANOTRAK_API short __cdecl NT_StopXYScan(char const * serialNo);

	/// <summary>	Query if the device is XY scanning. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns>	True if xy scanning, false if not. </returns>
	NANOTRAK_API bool __cdecl NT_IsXYScanning(char const * serialNo);

	/// <summary>	Queries if an XY scan line is available. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="lineNo">	The line no. </param>
	/// <returns>	True if the xy scan line is available, false if not. </returns>
	NANOTRAK_API bool __cdecl NT_IsXYScanLineAvailable(char const * serialNo, int lineNo);

	/// <summary>	Queries if the XY scan is available. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns>	True if the xy scan is available, false if not. </returns>
	NANOTRAK_API bool __cdecl NT_IsXYScanAvailable(char const * serialNo);

	/// <summary>	Gets XY scan range. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns>	The calculated xy scan range. </returns>
	NANOTRAK_API KNA_TIARange __cdecl NT_GetXYScanRange(char const * serialNo);

	/// <summary>	Gets XY scan line. </summary>
	/// <param name="serialNo">  	The device serial no. </param>
	/// <param name="lineNo">	 	The line no. </param>
	/// <param name="line">		 	[in,out] The line. </param>
	/// <param name="bufferSize">	Size of the buffer (96 bytes required for each line). </param>
	/// <returns>	The xy scan line. </returns>
	NANOTRAK_API short __cdecl NT_GetXYScanLine(char const * serialNo, int lineNo, byte *line, int bufferSize);
}
/** @} */ // KCubeNanoTrak
