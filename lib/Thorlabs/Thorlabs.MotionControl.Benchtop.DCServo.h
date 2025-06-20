// summary:	Declares the functions class
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the BENCHTOPDCSERVO_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// BENCHTOPDCSERVO_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#pragma once

#ifdef BENCHTOPDCSERVODLL_EXPORTS
/// <summary> Gets the Benchtop DCServo API. </summary>
#define BENCHTOPDCSERVO_API __declspec(dllexport)
#else
#define BENCHTOPDCSERVO_API __declspec(dllimport)
#endif

#include <OaIdl.h>

/** @defgroup BenchtopDCServo Benchtop DC Servo
 *  This section details the Structures and Functions relavent to the  @ref BDC103_page "Benchtop DC Servo"<br />
 *  For an example of how to connect to the device and perform simple operations use the following links:
 *  <list type=bullet>
 *    <item> \ref namespaces_bdc_ex_1 "Example of using the Thorlabs.MotionControl.Benchtop.DCServo.DLL from a C or C++ project."<br />
 *									  This requires the DLL to be dynamical linked. </item>
 *    <item> \ref namespaces_bdc_ex_2 "Example of using the Thorlabs.MotionControl.Benchtop.DCServo.DLL from a C# project"<br />
 *									  This uses Marshalling to load and access the C DLL. </item>
 *  </list>
 *  The Thorlabs.MotionControl.Benchtop.DCServo.DLL requires the following DLLs
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
		MOT_DCServo = 2,
		MOT_BrushlessMotor = 3,
		MOT_CustomMotor = 100,
	} MOT_MotorTypes;

	/// <summary> Values that represent Travel Modes. </summary>
	typedef enum MOT_TravelModes : int
	{
		MOT_TravelModeUndefined,///<Undefined
		MOT_Linear = 0x01,///<Linear travel, default units are millimeters
		MOT_Rotational = 0x02,///<Rotational travel, default units are degrees
	} MOT_TravelModes;

	/// <summary> Values that represent Travel Modes. </summary>
	typedef enum MOT_TravelDirection : short
	{
		MOT_TravelDirectionUndefined,///<Undefined
		MOT_Forwards = 0x01,///<Move in a Forward direction
		MOT_Reverse = 0x02,///<Move in a Backward / Reverse direction
	} MOT_TravelDirection;

	/// <summary> Values that represent Limit Switch Directions. </summary>
	typedef enum MOT_HomeLimitSwitchDirection : short
	{
		MOT_LimitSwitchDirectionUndefined,///<Undefined
		MOT_ReverseLimitSwitch = 0x01,///<Limit switch in forward direction
		MOT_ForwardLimitSwitch = 0x04,///<Limit switch in reverse direction
	} MOT_HomeLimitSwitchDirection;

	/// <summary> Values that represent Direction Type. </summary>
	typedef enum MOT_DirectionSense : short
	{
		MOT_Normal = 0x00,///<Move / Jog direction is normal (clockwise).
		MOT_Backwards = 0x01,///<Move / Jog direction is reversed (anti clockwise).
	} MOT_DirectionSense;

	/// <summary> Values that represent the motor Jog Modes. </summary>
	typedef enum MOT_JogModes : short
	{
		MOT_JogModeUndefined = 0x00,///<Undefined
		MOT_Continuous = 0x01,///<Continuous jogging
		MOT_SingleStep = 0x02,///<Jog 1 step at a time
	} MOT_JogModes;

	/// <summary> Values that represent the motor Jog Modes. </summary>
	typedef enum MOT_StopModes : short
	{
		MOT_StopModeUndefined = 0x00,///<Undefined
		MOT_Immediate = 0x01,///<Stops immediate
		MOT_Profiled = 0x02,///<Stops using a velocity profile
	} MOT_StopModes;

	/// <summary> Values that represent the motor Button Modes. </summary>
	typedef enum MOT_ButtonModes : WORD
	{
		MOT_ButtonModeUndefined = 0x00,///<Undefined
		MOT_JogMode = 0x01,///<Jog motor in correct direction for button
		MOT_Preset = 0x02,///<Move to preset position
	} MOT_ButtonModes;

	/// <summary> Value that represent action to be taken when motor hits a limit switch. </summary>
	typedef enum MOT_LimitSwitchModes : WORD
	{
		MOT_LimitSwitchModeUndefined = 0x00,///<Undefined
		MOT_LimitSwitchIgnoreSwitch=0x01,///<Ignore limit switch
		MOT_LimitSwitchMakeOnContact=0x02,///<Switch makes on contact
		MOT_LimitSwitchBreakOnContact=0x03,///<Switch breaks on contact
		MOT_LimitSwitchMakeOnHome=0x04,///<Switch makes on contact when homing
		MOT_LimitSwitchBreakOnHome=0x05,///<Switch breaks on contact when homing
		MOT_PMD_Reserved=0x06,///<Reserved for PMD brushless servo controllers
		MOT_LimitSwitchIgnoreSwitchSwapped = 0x81,///<Ignore limit switch (swapped)
		MOT_LimitSwitchMakeOnContactSwapped = 0x82,///<Switch makes on contact (swapped)
		MOT_LimitSwitchBreakOnContactSwapped = 0x83,///<Switch breaks on contact (swapped)
		MOT_LimitSwitchMakeOnHomeSwapped = 0x84,///<Switch makes on contact when homing (swapped)
		MOT_LimitSwitchBreakOnHomeSwapped = 0x85,///<Switch breaks on contact when homing (swapped)
	} MOT_LimitSwitchModes;

	/// <summary> Value that represent action to be taken when motor hits a limit switch. </summary>
	typedef enum MOT_LimitSwitchSWModes : WORD
	{
		MOT_LimitSwitchSWModeUndefined = 0x00,///<Undefined
		MOT_LimitSwitchIgnored=0x01,///<Ignore limit switch
		MOT_LimitSwitchStopImmediate=0x02,///<Stop immediately when hitting limit switch
		MOT_LimitSwitchStopProfiled=0x03,///<Stop profiled when hitting limit switch
		MOT_LimitSwitchIgnored_Rotational=0x81,///<Ignore limit switch (rotational stage)
		MOT_LimitSwitchStopImmediate_Rotational=0x82,///<Stop immediately when hitting limit switch (rotational stage)
		MOT_LimitSwitchStopProfiled_Rotational=0x83,///<Stop profiled when hitting limit switch (rotational stage)
	} MOT_LimitSwitchSWModes;

	/// <summary> Values that represent MOT_LimitsSoftwareApproachPolicy. </summary>
	typedef enum MOT_LimitsSoftwareApproachPolicy : __int16
	{
		DisallowIllegalMoves = 0,///<Disable any move outside of the current travel range of the stage
		AllowPartialMoves,///<Truncate moves to within the current travel range of the stage.
		AllowAllMoves,///<Allow all moves, regardless of whether they are within the current travel range of the stage.
	} MOT_LimitsSoftwareApproachPolicy;

	/// <summary> Values that represent the Encoder PID Loop modes. </summary>
	typedef enum MOT_PID_LoopMode : WORD
	{
		MOT_PIDLoopModeDisabled = 0x00,///<Disabled or Undefined
		MOT_PIDOpenLoopMode = 0x01,///<Encoder is in open loop mode
		MOT_PIDClosedLoopMode = 0x02,///<Encoder is in closed loop mode
	} MOT_PID_LoopMode;

	/// <summary> Values that represent DeviceMessageClass message types. </summary>
	typedef enum MOT_MovementModes
	{
		LinearRange = 0x00,///< Fixed Angular Range defined by MinPosition and MaxPosition
		RotationalUnlimited = 0x01,///< Unlimited angle
		RotationalWrapping = 0x02,///< Angular Range 0 to 360 with wrap around
	} MOT_MovementModes;

	/// <summary> Values that represent DeviceMessageClass message types. </summary>
	typedef enum MOT_MovementDirections
	{
		Quickest = 0x00,///< Uses the shortest travel between two angles
		Forwards = 0x01,///< Only rotate in a forward direction
		Reverse = 0x02,///< Only rotate in a backward direction
	} MOT_MovementDirections;

	/// <summary> Values that represent Trigger Port Mode. </summary>
	typedef enum KMOT_TriggerPortMode
	{
		KMOT_TrigDisabled = 0x00,///< Trigger Disabled
		KMOT_TrigIn_GPI = 0x01,///< General purpose logic input
		KMOT_TrigIn_RelativeMove = 0x02,///< Move relative using relative move parameters
		KMOT_TrigIn_AbsoluteMove = 0x03,///< Move absolute using absolute move parameters
		KMOT_TrigIn_Home = 0x04,///< Perform a Home action
		KMOT_TrigIn_Stop = 0x05,///< Perform a Stop Immediate action
		KMOT_TrigIn_StartScan = 0x06,///< Perform a Scan Start (on supported devices)
		KMOT_TrigIn_ShuttleMove = 0x07,///< Move shuttle using absolute move parameters (on supported devices)
		KMOT_TrigOut_GPO = 0x0A,///< General purpose output (set using MOT_SET_DIGOUTPUTS)
		KMOT_TrigOut_InMotion = 0x0B,///< Set when device moving
		KMOT_TrigOut_AtMaxVelocity = 0x0C,///< Set when at max velocity
		KMOT_TrigOut_AtPositionStepFwd = 0x0D,///< Set when at predefine position steps, Forward,<br />Set using wTrigStartPos, wTrigInterval, wTrigNumPulses,wTrigPulseWidth
		KMOT_TrigOut_AtPositionStepRev = 0x0E,///< Set when at predefine position steps, Reverse,<br />Set using wTrigStartPos, wTrigInterval, wTrigNumPulses,wTrigPulseWidth
		KMOT_TrigOut_AtPositionStepBoth = 0x0F,///< Set when at predefine position steps, Both,<br />Set using wTrigStartPos, wTrigInterval, wTrigNumPulses,wTrigPulseWidth
		KMOT_TrigOut_AtFwdLimit = 0x10,///< Set when forward limit switch is active
		KMOT_TrigOut_AtBwdLimit = 0x11,///< Set when backward limit switch is active
		KMOT_TrigOut_AtLimit = 0x12,///< Set when either limit switch is active
	} KMOT_TriggerPortMode;

	/// <summary> Values that represent Trigger Port Polarity. </summary>
	typedef enum KMOT_TriggerPortPolarity
	{
		KMOT_TrigPolarityHigh = 0x01,///< Trigger Polarity high
		KMOT_TrigPolarityLow = 0x02,///< Trigger Polarity Low
	} KMOT_TriggerPortPolarity;
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
		///				<item><term>MOT_DCServo</term><term>2</term></item>
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

	/// <summary> Structure containing the velocity parameters. </summary>
	/// <remarks> Moves are performed using a velocity profile.<br />
	/// 		  The move starts at the Minimum Velocity (always 0 at present) and accelerated to the Maximum Velocity using the defined Acceleration.<br/>
	/// 		  The move is usually completed using a similar deceleration.<br/>
	/// 		  For further information see \ref C_MOTOR_sec11 "Positioning" </remarks>
	/// <seealso cref="MOT_JogParameters"/>
	/// <seealso cref="MOT_HomingParameters"/>
	typedef struct MOT_VelocityParameters
	{
		/// <summary> The minimum velocity in \ref DeviceUnits_page usually 0. </summary>
		int minVelocity;
		/// <summary> The acceleration in \ref DeviceUnits_page. </summary>
		int acceleration;
		/// <summary> The maximum velocity in \ref DeviceUnits_page. </summary>
		int maxVelocity;
	} MOT_VelocityParameters;

	/// <summary> Structure containing the jog parameters. </summary>
	/// <remarks> Jogs are performed using a velocity profile over small fixed distances.<br />
	/// 		  The move starts at the Minimum Velocity (always 0 at present) and accelerated to the Maximum Velocity using the defined Acceleration.<br/>
	/// 		  The move is usually completed using a similar deceleration.<br/>
	/// 		  For further information see \ref C_MOTOR_sec12 "Jogging" </remarks>
	/// <seealso cref="MOT_VelocityParameters"/>
	/// <seealso cref="MOT_HomingParameters"/>
	typedef struct MOT_JogParameters
	{
		/// <summary> The jogging mode. </summary>
		/// <remarks> The mode can be one of the following:
		/// 		  <list type=table>
		///				<item><term>1</term><term>Continuous Jogging<br />The device will continue moving until the end stop is reached or the device button is raised</term></item>
		///				<item><term>2</term><term>Step Jogbr />The device will move by a fixed amount as defined in this structure.</term></item>
		/// 		  </list></remarks>
		MOT_JogModes mode;
		/// <summary> The step size in \ref DeviceUnits_page. </summary>
		unsigned int stepSize;
		/// <summary> The MOT_VelocityParameters for the jog. </summary>
		MOT_VelocityParameters velParams;
		/// <summary> The Stop Mode</summary>
		/// <remarks> The Stop Mode determines how the jog should stop.
		/// 		  <list type=table>
		///				<item><term>1</term><term>Immediate</term></item>
		///				<item><term>2</term><term>Profiled.</term></item>
		/// 		  </list> </remarks>
		MOT_StopModes stopMode;
	} MOT_JogParameters;

	/// <summary> Structure containing the homing parameters. </summary>
	/// <remarks> Homing is performed using a constant velocity.<br />
	/// 		  The home starts moving the motor in the defined direction until the limit switch is detected.<br/>
	/// 		  The device will then vback off from the limit switch by  the defined offset distance.<br />
	/// 		  For further information see \ref C_MOTOR_sec10 "Homing" </remarks>
	/// <seealso cref="MOT_VelocityParameters"/>
	/// <seealso cref="MOT_JogParameters"/>
	typedef struct MOT_HomingParameters
	{
		/// <summary> The Homing direction sense </summary>
		/// <remarks> The Homing Operation will always move in a decreasing position sense, but the actuator gearing may change the actual physical sense<br/>
		/// 		  Therefore the homing direction can correct the physical sense.
		/// 		 <list type=table>
		///				<item><term>1</term><term>Forwards</term></item>
		///				<item><term>2</term><term>Backwards.</term></item>
		/// 		  </list></remarks>
		MOT_TravelDirection direction;
		/// <summary> The limit switch direction. </summary>
		/// <remarks> The limit switch which will be hit when homing completes.
		/// 		 <list type=table>
		///				<item><term>1</term><term>Forward Limit Switch</term></item>
		///				<item><term>2</term><term>Reverse Limit Switch.</term></item>
		/// 		  </list</remarks>
		MOT_HomeLimitSwitchDirection limitSwitch;
		/// <summary> The velocity in small indivisible units. </summary>
		/// <remarks> As the homing operation is performed at a much lower velocity, to achieve accuracy, a profile is not required.</remarks>
		unsigned int velocity;
		/// <summary> Distance of home from limit in small indivisible units. </summary>
		unsigned int offsetDistance;
	} MOT_HomingParameters;

	/// <summary> Structure containing the limit switch parameters. </summary>
	typedef struct MOT_LimitSwitchParameters
	{
		/// <summary> Defines the clockwise hardware limit. </summary>
		/// <remarks> The clockwise hardware limit
		/// 		 <list type=table>
		///				<item><term>0x01</term><term>Ignore limit switch</term></item>
		///				<item><term>0x02</term><term>Make on contact.</term></item>
		///				<item><term>0x03</term><term>Break on contact.</term></item>
		///				<item><term>0x04</term><term>Makes on contact when homing</term></item>
		///				<item><term>0x05</term><term>Break on contact when homing.</term></item>
		///				<item><term>0x06</term><term>Reserved for PMD brushless servo controllers.</term></item>
		///				<item><term>0x80</term><term>Switch mode when using a rotational stage.</term></item>
		/// 		  </list> </remarks>
		MOT_LimitSwitchModes clockwiseHardwareLimit;
		/// <summary> Defines the anticlockwise hardware limit. </summary>
		/// <remarks> The anticlockwise hardware limit
		/// 		 <list type=table>
		///				<item><term>0x01</term><term>Ignore limit switch</term></item>
		///				<item><term>0x02</term><term>Make on contact.</term></item>
		///				<item><term>0x03</term><term>Break on contact.</term></item>
		///				<item><term>0x04</term><term>Makes on contact when homing</term></item>
		///				<item><term>0x05</term><term>Break on contact when homing.</term></item>
		///				<item><term>0x06</term><term>Reserved for PMD brushless servo controllers.</term></item>
		///				<item><term>0x80</term><term>Switch mode when using a rotational stage.</term></item>
		/// 		  </list> </remarks>
		MOT_LimitSwitchModes anticlockwiseHardwareLimit;
		/// <summary> poition of clockwise software limit in \ref DeviceUnits_page. </summary>
		DWORD clockwisePosition;
		/// <summary> poition of anticlockwise software limit in \ref DeviceUnits_page. </summary>
		DWORD anticlockwisePosition;
		/// <summary> Actions to take when software limit is detected. </summary>
		/// <remarks> The anticlockwise hardware limit
		/// 		 <list type=table>
		///				<item><term>0x01</term><term>Ignore limit switche.</term></item>
		///				<item><term>0x02</term><term>Stop Immediate.</term></item>
		///				<item><term>0x03</term><term>Profiled stop.</term></item>
		///				<item><term>0x82</term><term>Stop Immediate (rotational stage).</term></item>
		///				<item><term>0x83</term><term>Profiled stop (rotational stage).</term></item>
		/// 		  </list> </remarks>
		MOT_LimitSwitchSWModes softLimitMode;
	} MOT_LimitSwitchParameters;

	/// <summary> Structure containing power settings for the stepper controllers. </summary>
	typedef struct MOT_PowerParameters
	{
		/// <summary> Percentage of full power to give while not moving (0 - 100). </summary>
		WORD restPercentage;
		/// <summary> Percentage of full power to give while moving (0 - 100). </summary>
		WORD movePercentage;
	} MOT_PowerParameters;

	/// <summary> Structure containing the joystick parameters. </summary>
	typedef struct MOT_JoystickParameters
	{
		/// <summary> Maximum speed in low gear mode in encoder counts per cycle. </summary>
		DWORD lowGearMaxVelocity;
		/// <summary> Maximum speed in high gear mode in encoder counts per cycle.  </summary>
		DWORD highGearMaxVelocity;
		/// <summary> Low gear acceleration in encoder counts per cycle per cycle. </summary>
		DWORD lowGearAcceleration;
		/// <summary> High gear acceleration in encoder counts per cycle per cycle. </summary>
		DWORD highGearAcceleration;
		/// <summary> Travel Direction for the joystick
		/// 		 <list type=table>
		///				<item><term>1</term><term>Forwards</term></item>
		///				<item><term>2</term><term>Backwards.</term></item>
		/// 		  </list></remarks>
		MOT_TravelDirection directionSense;
	} MOT_JoystickParameters;

	/// <summary> structure containing the PID Loop Parameters. </summary>
	typedef struct MOT_DC_PIDParameters
	{
		/// <summary> The PID Proportional Gain. </summary>
		int proportionalGain;
		/// <summary> The PID Integral Gain. </summary>
		int integralGain;
		/// <summary> The PID Derivative Gain. </summary>
		/// <remarks> Kept as differentialGain rather than derivativeGain for backward compatibility</remarks>
		int differentialGain;
		/// <summary> The PID Integral Limit. </summary>
		int integralLimit;
		/// <summary> Bit Mask To enable / disable the PID components. </summary>
		/// <remarks> Bit Mask To enable / disable the PID components.
		/// 		 <list type=table>
		///				<item><term>Bit 1 (0x01)</term><term>When set, enable Proportional Gain component.</term></item>
		///				<item><term>Bit 2 (0x02)</term><term>When set, enable Integral Gain component.</term></item>
		///				<item><term>Bit 3 (0x04)</term><term>When set, enable Derivative Gain component.</term></item>
		///				<item><term>Bit 4 (0x08)</term><term>When set, enable Integral Limit component.</term></item>
		/// 		  </list> </remarks>
		WORD parameterFilter;
	} MOT_DC_PIDParameters;

	/// <summary> Motor trigger configuration. </summary>
	typedef struct KMOT_TriggerConfig
	{
		/// <summary> The trigger 1 mode. </summary>
		/// <remarks> The trigger 1 operating mode:
		/// 		  <list type=table>
		///				<item><term>0</term><term>Trigger disabled</term></item>
		///				<item><term>1</term><term>Trigger Input - General purpose logic input</term></item>
		///				<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
		///				<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
		///				<item><term>4</term><term>Trigger Input - Perform a Home action</term></item>
		///				<item><term>5</term><term>Trigger Input - Perform a Stop Immediate action.<Br />Currently only supported on KST101</term></item>
		/// 			<item><term>6</term><term>Trigger Input - Perform a Start scan move</term></item>
		/// 			<item><term>7</term><term>Trigger Input - Move shuttle using absolute move parameters</term></item>
		///				<item><term>10</term><term>Trigger Output - General purpose output (set using MOT_SET_DIGOUTPUTS)</term></item>
		///				<item><term>11</term><term>Trigger Output - Set when device moving</term></item>
		///				<item><term>12</term><term>Trigger Output - Set when at max velocity</term></item>
		///				<item><term>13</term><term>Trigger Output - Set when at predefine position steps</term></item>
		///				<item><term>14</term><term>Trigger Output - TBD mode</term></item>
		/// 		  </list>
		/// 		  </remarks>
		KMOT_TriggerPortMode Trigger1Mode;
		/// <summary> The trigger 1 polarity. </summary>
		/// <remarks> The trigger 1 output polaritye:
		/// 		  <list type=table>
		///				<item><term>1</term><term>Output high when set</term></item>
		///				<item><term>2</term><term>Output low when set</term></item>
		/// 		  </list>
		/// 		  </remarks>
		KMOT_TriggerPortPolarity Trigger1Polarity;
		/// <summary> The trigger 2 mode. </summary>
		/// <remarks> The trigger 2 operating mode:
		/// 		  <list type=table>
		///				<item><term>0</term><term>Trigger disabled</term></item>
		///				<item><term>1</term><term>Trigger Input - General purpose logic input</term></item>
		///				<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
		///				<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
		///				<item><term>4</term><term>Trigger Input - Perform a Home action</term></item>
		///				<item><term>5</term><term>Trigger Input - Perform a Stop Immediate action.<Br />Currently only supported on KST101</term></item>
		/// 			<item><term>6</term><term>Trigger Input - Perform a Start scan move</term></item>
		/// 			<item><term>7</term><term>Trigger Input - Move shuttle using absolute move parameters</term></item>
		///				<item><term>10</term><term>Trigger Output - General purpose output (set using MOT_SET_DIGOUTPUTS)</term></item>
		///				<item><term>11</term><term>Trigger Output - Set when device moving</term></item>
		///				<item><term>12</term><term>Trigger Output - Set when at max velocity</term></item>
		///				<item><term>13</term><term>Trigger Output - Set when at predefine position steps</term></item>
		///				<item><term>14</term><term>Trigger Output - TBD mode</term></item>
		/// 		  </list>
		/// 		  </remarks>
		KMOT_TriggerPortMode Trigger2Mode;
		/// <summary> The trigger 2 polarity. </summary>
		/// <remarks> The trigger 2 output polarity:
		/// 		  <list type=table>
		///				<item><term>1</term><term>Output high when set</term></item>
		///				<item><term>2</term><term>Output low when set</term></item>
		/// 		  </list>
		/// 		  </remarks>
		KMOT_TriggerPortPolarity Trigger2Polarity;
	} KMOT_TriggerConfig;

	/// <summary> structure containing the   encoder resolution parameters. </summary>
	/// <value> The encoder parameters. </value>
	typedef struct MOT_EncoderResolutionParams
	{
		/// <summary> Endcoder resolution whole number part. </summary>
		DWORD encoderResolutionWholeNumber;
		/// <summary> Endcoder resolution fractional part. </summary>
		WORD encoderResolutionFraction;
		/// <summary> Reserved for future use. </summary>
		WORD unused1;
		/// <summary> Reserved for future use. </summary>
		WORD unused2;
		/// <summary> Reserved for future use. </summary>
		WORD unused3;
	} MOT_EncoderResolutionParams;

	/// <summary> Motor trigger output configuration. </summary>
	typedef struct KMOT_TriggerParams
	{
		/// <summary> The trigger output start position in encoder units. </summary>
		__int32 TriggerStartPositionFwd;
		/// <summary> The trigger interval in encoder units. </summary>
		__int32 TriggerIntervalFwd;
		/// <summary> Number of trigger pulses. </summary>
		__int32 TriggerPulseCountFwd;
		/// <summary> The trigger output start position in encoder units. </summary>
		__int32 TriggerStartPositionRev;
		/// <summary> The trigger interval in encoder units. </summary>
		__int32 TriggerIntervalRev;
		/// <summary> Number of trigger pulses. </summary>
		__int32 TriggerPulseCountRev;
		/// <summary> Width of the trigger pulse in encoder units. </summary>
		__int32 TriggerPulseWidth;
		/// <summary> Number of cycles. </summary>
		__int32 CycleCount;
	} KMOT_TriggerParams;
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
	BENCHTOPDCSERVO_API short __cdecl TLI_BuildDeviceList(void);

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
	BENCHTOPDCSERVO_API short __cdecl TLI_GetDeviceListSize();

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
	BENCHTOPDCSERVO_API short __cdecl TLI_GetDeviceList(SAFEARRAY** stringsReceiver);

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
	BENCHTOPDCSERVO_API short __cdecl TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID);

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
	BENCHTOPDCSERVO_API short __cdecl TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length);

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
	BENCHTOPDCSERVO_API short __cdecl TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer);

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
	BENCHTOPDCSERVO_API short __cdecl TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID);

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
	BENCHTOPDCSERVO_API short __cdecl TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length);

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
	BENCHTOPDCSERVO_API short __cdecl TLI_GetDeviceInfo(char const * serialNo, TLI_DeviceInfo *info);

	/// <summary> Initialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <remarks> Call TLI_InitializeSimulations before TLI_BuildDeviceList at the start of the program to make a connection to the simulation manager.<Br />
	/// 		  Any devices configured in the simulation manager will become visible TLI_BuildDeviceList is called and can be accessed using TLI_GetDeviceList.<Br />
	/// 		  Call TLI_InitializeSimulations at the end of the program to release the simulator.  </remarks>
	/// <seealso cref="TLI_UninitializeSimulations()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	BENCHTOPDCSERVO_API void __cdecl TLI_InitializeSimulations();

	/// <summary> Uninitialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <seealso cref="TLI_InitializeSimulations()" />
	BENCHTOPDCSERVO_API void __cdecl TLI_UninitializeSimulations();

	/// <summary> Open the device for communications. </summary>
	/// <param name="serialNo">	The serial no of the controller to be connected. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_connectionN.cpp
	/// <seealso cref="BDC_Close(char const * serialNo)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_Open(char const * serialNo);

	/// <summary> Disconnect and close the device. </summary>
	/// <param name="serialNo">	The serial no of the controller to be disconnected. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_connectionN.cpp
	/// <seealso cref="BDC_Open(char const * serialNo)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_Close(char const * serialNo);

	/// <summary>	Check connection. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> true if the USB is listed by the ftdi controller</returns>
	/// \include CodeSnippet_CheckConnection.cpp
	BENCHTOPDCSERVO_API bool __cdecl BDC_CheckConnection(char const * serialNo);

	/// <summary> Verifies that the specified channel is valid. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The requested channel (1 to n). </param>
	/// <returns> <c>true</c> if the channel is valid. </returns>
    /// 		  \include CodeSnippet_connectionN.cpp
	BENCHTOPDCSERVO_API bool __cdecl BDC_IsChannelValid(char const * serialNo, short channel);

	/// <summary> Gets the number of channels available to this device. </summary>
	/// <remarks> This function returns ther number of available bays, not the number of bays filled.</remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <returns> The number of channels available on this device. </returns>
    /// 		  \include CodeSnippet_connectionN.cpp
	BENCHTOPDCSERVO_API int __cdecl BDC_MaxChannelCount(char const * serialNo);

	/// <summary> Sends a command to the device to make it identify iteself. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHTOPDCSERVO_API short __cdecl BDC_Identify(char const * serialNo);

	/// <summary> Gets the hardware information from the device. </summary>
	/// <param name="serialNo">		    The controller serial no. </param>
	/// <param name="channel">		    The channel (1 to n). </param>
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
	BENCHTOPDCSERVO_API short __cdecl BDC_GetHardwareInfo(char const * serialNo, short channel, char * modelNo, DWORD sizeOfModelNo, WORD * type, WORD * numChannels, 
																	char * notes, DWORD sizeOfNotes, DWORD * firmwareVersion, WORD * hardwareVersion, WORD * modificationState);

	/// <summary> Gets the hardware information in a block. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="hardwareInfo"> Address of a TLI_HardwareInformation structure to receive the hardware information. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	BENCHTOPDCSERVO_API short __cdecl BDC_GetHardwareInfoBlock(char const * serialNo, short channel, TLI_HardwareInformation *hardwareInfo);

	/// <summary> Gets the number of channels in the device. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <returns> The number of channels. </returns>
	BENCHTOPDCSERVO_API short __cdecl BDC_GetNumChannels(char const * serialNo);

	/// <summary> Gets version number of the device firmware. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The device firmware version number made up of 4 byte parts. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	BENCHTOPDCSERVO_API DWORD __cdecl BDC_GetFirmwareVersion(char const * serialNo, short channel);

	/// <summary> Gets version number of the device software. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <returns> The device software version number made up of 4 byte parts. </returns>
    /// 		  \include CodeSnippet_identify.cpp
	BENCHTOPDCSERVO_API DWORD __cdecl BDC_GetSoftwareVersion(char const * serialNo);

	/// <summary> Update device with stored settings. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
    /// 		  \include CodeSnippet_connectionN.cpp
	BENCHTOPDCSERVO_API bool __cdecl BDC_LoadSettings(char const * serialNo, short channel);

	/// <summary> Update device with named settings. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <param name="channel">  The channel. </param>
	/// <param name="settingsName"> Name of settings stored away from device. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	///             \include CodeSnippet_connection1.cpp
	BENCHTOPDCSERVO_API bool __cdecl BDC_LoadNamedSettings(char const * serialNo, short channel, char const *settingsName);

	/// <summary>	Persist device settings to device. </summary>
	/// <param name="serialNo">	The serial no. </param>
	/// <param name="channel"> 	The channel. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	BENCHTOPDCSERVO_API bool __cdecl BDC_PersistSettings(char const * serialNo, short channel);

	/// <summary> Set the calibration file for this motor. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="filename"> Filename of the calibration file to load. </param>
	/// <param name="enabled">  <c>true</c> to enable,  <c>false</c> to disable. </param>
	/// <seealso cref="BDC_IsCalibrationActive(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_GetCalibrationFile(char const * serialNo, short channel, char * filename, short sizeOfBuffer)" />
	BENCHTOPDCSERVO_API void __cdecl BDC_SetCalibrationFile(char const * serialNo, short channel, char const *filename, bool enabled);

	/// <summary> Is a calibration file active for this motor. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> <c>true</c> if A calibration file is active. </returns>
	/// <seealso cref="BDC_GetCalibrationFile(char const * serialNo, short channel, char * filename, short sizeOfBuffer)" />
	/// <seealso cref="BDC_SetCalibrationFile(char const * serialNo, short channel, char const *filename, bool enabled)" />
	BENCHTOPDCSERVO_API bool __cdecl BDC_IsCalibrationActive(char const * serialNo, short channel);

	/// <summary> Get calibration file for this motor. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="filename"> Address of an output buffer to receive the filename. </param>
	/// <param name="sizeOfBuffer"> The size of the filename output buffer. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="BDC_IsCalibrationActive(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetCalibrationFile(char const * serialNo, short channel, char const *filename, bool enabled)" />
	BENCHTOPDCSERVO_API bool __cdecl BDC_GetCalibrationFile(char const * serialNo, short channel, char * filename, short sizeOfBuffer);

	/// <summary> Disable the channel so that motor can be moved by hand. </summary>
	/// <remarks> When disabled power is removed from the motor and it can be freely moved.</remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_EnableChannel(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_DisableChannel(char const * serialNo, short channel);

	/// <summary> Enable channel for computer control. </summary>
	/// <remarks> When enabled power is applied to the motor so it is fixed in position.</remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_DisableChannel(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_EnableChannel(char const * serialNo, short channel);

	/// <summary> Get number of positions. </summary>
	/// <remarks> The GetNumberPositions function will get the maximum position reachable by the device.<br />
	/// 		  The motor may need to be \ref C_MOTOR_sec10 "Homed" before this parameter can be used. </remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The number of positions. </returns>
	/// <seealso cref="BDC_MoveToPosition(char const * serialNo, short channel, int index)" />
	/// <seealso cref="BDC_GetPosition(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_Home(char const * serialNo, short channel)" />
    /// 		  \include CodeSnippet_move.cpp
	BENCHTOPDCSERVO_API int __cdecl BDC_GetNumberPositions(char const * serialNo, short channel);

	/// <summary> Move the device to the specified position (index). </summary>
	/// <remarks> The motor may need to be \ref C_MOTOR_sec10 "Homed" before a position can be set<br />
	/// 		  see \ref C_MOTOR_sec11 "Positioning" for more detail. </remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="index">   	The position in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if move successfully started. </returns>
	/// <seealso cref="BDC_GetNumberPositions(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="BDC_GetPosition(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_GetVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BDC_GetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters  *velocityParams)" />
	/// <seealso cref="BDC_SetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters *velocityParams)" />
	/// <seealso cref="BDC_MoveRelative(char const * serialNo, short channel, int displacement)" />
	/// <seealso cref="BDC_MoveAtVelocity(char const * serialNo, short channel, MOT_TravelDirection direction)" />
    /// 		  \include CodeSnippet_move.cpp
	BENCHTOPDCSERVO_API short __cdecl BDC_MoveToPosition(char const * serialNo, short channel, int index);

	/// <summary> Get the current position. </summary>
	/// <remarks> The current position is the last recorded position.<br />
	/// 		  The current position is updated either by the polling mechanism or<br />
	/// 		  by calling <see cref="RequestPosition" /> or <see cref="RequestStatus" />.</remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The current position in \ref DeviceUnits_page. </returns>
	/// <seealso cref="BDC_GetNumberPositions(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_MoveToPosition(char const * serialNo, short channel, int index)" />
	/// <seealso cref="BDC_Home(char const * serialNo, short channel)" />
    /// 		  \include CodeSnippet_move.cpp
	BENCHTOPDCSERVO_API int __cdecl BDC_GetPosition(char const * serialNo, short channel);

	/// <summary> Can the device perform a Home. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> <c>true</c> if the device can home. </returns>
	BENCHTOPDCSERVO_API bool __cdecl BDC_CanHome(char const * serialNo, short channel);

	/// \deprecated
	/// <summary> Does the device need to be Homed before a move can be performed. </summary>
	/// <remarks> superceded by <see cref="BDC_CanMoveWithoutHomingFirst(char const * serialNo, short channel)"/> </remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> <c>true</c> if the device needs homing. </returns>
	BENCHTOPDCSERVO_API bool __cdecl BDC_NeedsHoming(char const * serialNo, short channel);

	/// <summary> Can this device be moved without Homing. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> <c>true</c> if the device does not need to be homed before a move can be commanded. </returns>
	BENCHTOPDCSERVO_API bool __cdecl BDC_CanMoveWithoutHomingFirst(char const * serialNo, short channel);

	/// <summary> Home the device. </summary>
	/// <remarks> Homing the device will set the device to a known state and determine the home position,<br />
	/// 		  see \ref C_MOTOR_sec10 "Homing" for more detail. </remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if move successfully started. </returns>
	/// <seealso cref="BDC_GetNumberPositions(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_MoveToPosition(char const * serialNo, short channel, int index)" />
	/// <seealso cref="BDC_GetPosition(char const * serialNo, short channel)" />
    /// 		  \include CodeSnippet_move.cpp
	BENCHTOPDCSERVO_API short __cdecl BDC_Home(char const * serialNo, short channel);

	/// <summary> Clears the device message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHTOPDCSERVO_API short __cdecl BDC_ClearMessageQueue(char const * serialNo, short channel);

	/// <summary> Registers a callback on the message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="functionPointer"> A function pointer to be called whenever messages are received. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHTOPDCSERVO_API short __cdecl BDC_RegisterMessageCallback(char const * serialNo, short channel, void (* functionPointer)());

	/// <summary> Gets the MessageQueue size. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> number of messages in the queue. </returns>
	BENCHTOPDCSERVO_API int __cdecl BDC_MessageQueueSize(char const * serialNo, short channel);

	/// <summary> Get the next MessageQueue item if it is available. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="messageType"> Address of the WORD to receive the message type. </param>
	/// <param name="messageID"> Address of the WORD to receive themessage ID. </param>
	/// <param name="messageData"> Address of the DWORD to receive the messageData. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	BENCHTOPDCSERVO_API bool __cdecl BDC_GetNextMessage(char const * serialNo, short channel, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Get the next MessageQueue item if it is available. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="messageType"> Address of the WORD to receive the message type. </param>
	/// <param name="messageID"> Address of the WORD to receive themessage ID. </param>
	/// <param name="messageData"> Address of the DWORD to receive the messageData. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	BENCHTOPDCSERVO_API bool __cdecl BDC_WaitForMessage(char const * serialNo, short channel, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Requests the homing parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec10 "Homing" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetHomingVelocity(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetHomingVelocity(char const * serialNo, short channel, unsigned int velocity)" />
	/// <seealso cref="BDC_GetHomingParamsBlock(char const * serialNo, short channel, MOT_HomingParameters *homingParams)" />
	/// <seealso cref="BDC_SetHomingParamsBlock(char const * serialNo, short channel, MOT_HomingParameters *homingParams)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_RequestHomingParams(char const * serialNo, short channel);

	/// <summary> Gets the homing velocity. </summary>
	/// <remarks> see \ref C_MOTOR_sec10 "Homing" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The homing velocity in \ref DeviceUnits_page. </returns>
	/// <seealso cref="BDC_RequestHomingParams(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetHomingVelocity(char const * serialNo, short channel, unsigned int velocity)" />
	/// <seealso cref="BDC_GetHomingParamsBlock(char const * serialNo, short channel, MOT_HomingParameters *homingParams)" />
	/// <seealso cref="BDC_SetHomingParamsBlock(char const * serialNo, short channel, MOT_HomingParameters *homingParams)" />
	BENCHTOPDCSERVO_API unsigned int __cdecl BDC_GetHomingVelocity(char const * serialNo, short channel);

	/// <summary> Sets the homing velocity. </summary>
	/// <remarks> see \ref C_MOTOR_sec10 "Homing" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="velocity"> The homing velocity in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_RequestHomingParams(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_GetHomingVelocity(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_GetHomingParamsBlock(char const * serialNo, short channel, MOT_HomingParameters *homingParams)" />
	/// <seealso cref="BDC_SetHomingParamsBlock(char const * serialNo, short channel, MOT_HomingParameters *homingParams)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_SetHomingVelocity(char const * serialNo, short channel, unsigned int velocity);

	/// <summary> Move the motor by a relative amount. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="displacement"> Signed displacement in \ref DeviceUnits_page.</param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetNumberPositions(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_GetVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BDC_SetVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="BDC_GetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters  *velocityParams)" />
	/// <seealso cref="BDC_SetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters *velocityParams)" />
	/// <seealso cref="BDC_MoveToPosition(char const * serialNo, short channel, int index)" />
	/// <seealso cref="BDC_MoveAtVelocity(char const * serialNo, short channel, MOT_TravelDirection direction)" />
    /// 		  \include CodeSnippet_move.cpp
	BENCHTOPDCSERVO_API short __cdecl BDC_MoveRelative(char const * serialNo, short channel, int displacement);

	/// <summary> Requests the jog parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetJogMode(char const * serialNo, short channel, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="BDC_GetJogStepSize(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_GetJogVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BDC_GetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParams)" />
	/// 		  \include CodeSnippet_jogpars.cpp
	BENCHTOPDCSERVO_API short __cdecl BDC_RequestJogParams(char const * serialNo, short channel);

	/// <summary> Gets the jog mode. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="mode"> The address of the short mode to recieve the Mode.
	/// 					 <list type=table>
	///							<item><term>Jog step</term><term>1</term></item>
	///							<item><term>Continuous</term><term>2</term></item>
	/// 					 </list> </param>
	/// <param name="stopMode"> The address of the short stopMode to recieve the StopMode.
	/// 					<list type=table>
	///							<item><term>Immediate Stop</term><term>1</term></item>
	///							<item><term>Profiled Stop</term><term>2</term></item>
	/// 					 </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_RequestJogParams(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetJogMode(char const * serialNo, short channel, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="BDC_GetJogStepSize(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetJogStepSize(char const * serialNo, short channel, unsigned int stepSize)" />
	/// <seealso cref="BDC_SetJogVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="BDC_GetJogVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BDC_GetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BDC_SetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BDC_MoveJog(char const * serialNo, short channel, MOT_TravelDirection jogDirection)" />
    /// 		  \include CodeSnippet_jogpars.cpp
	BENCHTOPDCSERVO_API short __cdecl BDC_GetJogMode(char const * serialNo, short channel, MOT_JogModes * mode, MOT_StopModes * stopMode);

	/// <summary> Sets the jog mode. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="mode"> The jog mode.
	/// 					 <list type=table>
	///							<item><term>Jog step</term><term>1</term></item>
	///							<item><term>Continuous</term><term>2</term></item>
	/// 					 </list> </param>
	/// <param name="stopMode"> The StopMode.
	/// 					<list type=table>
	///							<item><term>Immediate Stop</term><term>1</term></item>
	///							<item><term>Profiled Stop</term><term>2</term></item>
	/// 					 </list>  </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetJogMode(char const * serialNo, short channel, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="BDC_GetJogStepSize(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetJogStepSize(char const * serialNo, short channel, unsigned int stepSize)" />
	/// <seealso cref="BDC_SetJogVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="BDC_GetJogVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BDC_GetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BDC_SetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BDC_MoveJog(char const * serialNo, short channel, MOT_TravelDirection jogDirection)" />
    /// 		  \include CodeSnippet_jogpars.cpp
	BENCHTOPDCSERVO_API short __cdecl BDC_SetJogMode(char const * serialNo, short channel, MOT_JogModes mode, MOT_StopModes stopMode);

	/// <summary> Gets the distance to move when jogging. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <returns> The step in \ref DeviceUnits_page. </returns>
	/// <seealso cref="BDC_RequestJogParams(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_GetJogMode(char const * serialNo, short channel, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="BDC_SetJogMode(char const * serialNo, short channel, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="BDC_SetJogStepSize(char const * serialNo, short channel, unsigned int stepSize)" />
	/// <seealso cref="BDC_SetJogVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="BDC_GetJogVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BDC_GetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BDC_SetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BDC_MoveJog(char const * serialNo, short channel, MOT_TravelDirection jogDirection)" />
    /// 		  \include CodeSnippet_jogpars.cpp
	BENCHTOPDCSERVO_API unsigned int __cdecl BDC_GetJogStepSize(char const * serialNo, short channel);

	/// <summary> Sets the distance to move on jogging. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="stepSize"> The step in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetJogMode(char const * serialNo, short channel, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="BDC_SetJogMode(char const * serialNo, short channel, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="BDC_GetJogStepSize(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetJogVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="BDC_GetJogVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BDC_GetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BDC_SetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BDC_MoveJog(char const * serialNo, short channel, MOT_TravelDirection jogDirection)" />
    /// 		  \include CodeSnippet_jogpars.cpp
	BENCHTOPDCSERVO_API short __cdecl BDC_SetJogStepSize(char const * serialNo, short channel, unsigned int stepSize);

	/// <summary> Gets the jog velocity parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="acceleration"> Address of the parameter to receive the acceleration in \ref DeviceUnits_page. </param>
	/// <param name="maxVelocity"> Address of the parameter to receive the velocity in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_RequestJogParams(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_GetJogMode(char const * serialNo, short channel, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="BDC_SetJogMode(char const * serialNo, short channel, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="BDC_GetJogStepSize(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetJogStepSize(char const * serialNo, short channel, unsigned int stepSize)" />
	/// <seealso cref="BDC_SetJogVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="BDC_GetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BDC_SetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BDC_MoveJog(char const * serialNo, short channel, MOT_TravelDirection jogDirection)" />
    /// 		  \include CodeSnippet_jogpars.cpp
	BENCHTOPDCSERVO_API short __cdecl BDC_GetJogVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity);

	/// <summary> Sets jog velocity parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="acceleration">   The acceleration in \ref DeviceUnits_page. </param>
	/// <param name="maxVelocity"> The maximum velocity in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetJogMode(char const * serialNo, short channel, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="BDC_SetJogMode(char const * serialNo, short channel, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="BDC_GetJogStepSize(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetJogStepSize(char const * serialNo, short channel, unsigned int stepSize)" />
	/// <seealso cref="BDC_GetJogVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BDC_GetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BDC_SetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BDC_MoveJog(char const * serialNo, short channel, MOT_TravelDirection jogDirection)" />
    /// 		  \include CodeSnippet_jogpars.cpp
	BENCHTOPDCSERVO_API short __cdecl BDC_SetJogVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity);

	/// <summary> Perform a jog. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="jogDirection"> The jog direction
	/// 					 <list type=table>
	///							<item><term>Forwards</term><term>1</term></item>
	///							<item><term>Backwards</term><term>2</term></item>
	/// 					 </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetJogMode(char const * serialNo, short channel, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="BDC_SetJogMode(char const * serialNo, short channel, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="BDC_GetJogStepSize(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetJogStepSize(char const * serialNo, short channel, unsigned int stepSize)" />
	/// <seealso cref="BDC_SetJogVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="BDC_GetJogVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BDC_GetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BDC_SetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParams)" />
    /// 		  \include CodeSnippet_jog.cpp
	BENCHTOPDCSERVO_API short __cdecl BDC_MoveJog(char const * serialNo, short channel, MOT_TravelDirection jogDirection);

	/// <summary> Requests the velocity parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec11 "Positioning" for more detail.<remarks>
	/// <param name="serialNo"> The serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BDC_GetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters  *velocityParams)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_RequestVelParams(char const * serialNo, short channel);

	/// <summary> Gets the move velocity parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec11 "Positioning" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="acceleration"> Address of the parameter to receive the acceleration value in \ref DeviceUnits_page. </param>
	/// <param name="maxVelocity"> Address of the parameter to receive the maximum velocity value in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_RequestVelParams(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="BDC_GetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters  *velocityParams)" />
	/// <seealso cref="BDC_SetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters *velocityParams)" />
	/// <seealso cref="BDC_MoveToPosition(char const * serialNo, short channel, int index)" />
	/// <seealso cref="BDC_MoveRelative(char const * serialNo, short channel, int displacement)" />
	/// <seealso cref="BDC_MoveAtVelocity(char const * serialNo, short channel, MOT_TravelDirection direction)" />
    /// 		  \include CodeSnippet_movepars.cpp
	BENCHTOPDCSERVO_API short __cdecl BDC_GetVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity);

	/// <summary> Sets the move velocity parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec11 "Positioning" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="acceleration"> The new acceleration value in \ref DeviceUnits_page. </param>
	/// <param name="maxVelocity"> The new maximum velocity value in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BDC_GetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters  *velocityParams)" />
	/// <seealso cref="BDC_SetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters *velocityParams)" />
	/// <seealso cref="BDC_MoveToPosition(char const * serialNo, short channel, int index)" />
	/// <seealso cref="BDC_MoveRelative(char const * serialNo, short channel, int displacement)" />
	/// <seealso cref="BDC_MoveAtVelocity(char const * serialNo, short channel, MOT_TravelDirection direction)" />
    /// 		  \include CodeSnippet_movepars.cpp
	BENCHTOPDCSERVO_API short __cdecl BDC_SetVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity);

	/// <summary> Start moving at the current velocity in the specified direction. </summary>
	/// <remarks> see \ref C_MOTOR_sec11 "Positioning" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="direction"> The required direction of travel.
	/// 					 <list type=table>
	///							<item><term>Forwards</term><term>1</term></item>
	///							<item><term>Backwards</term><term>2</term></item>
	/// 					 </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BDC_SetVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="BDC_GetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters  *velocityParams)" />
	/// <seealso cref="BDC_SetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters *velocityParams)" />
	/// <seealso cref="BDC_MoveToPosition(char const * serialNo, short channel, int index)" />
	/// <seealso cref="BDC_MoveRelative(char const * serialNo, short channel, int displacement)" />
    /// 		  \include CodeSnippet_move.cpp
	BENCHTOPDCSERVO_API short __cdecl BDC_MoveAtVelocity(char const * serialNo, short channel, MOT_TravelDirection direction);

	/// <summary> Sets the motor direction sense. </summary>
	/// <remarks> This function is used because some actuators use have directions of motion reversed.<br />
	/// 		  This parameter will tell the system to reverse the direction sense whnd moving, jogging etc. </remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="reverse"> if  <c>true</c> then directions will be swapped on these moves. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BENCHTOPDCSERVO_API short __cdecl BDC_SetDirection(char const * serialNo, short channel, bool reverse);

	/// <summary> Stop the current move immediately (with risk of losing track of position). </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_StopProfiled(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_StopImmediate(char const * serialNo, short channel);

	/// <summary> Stop the current move using the current velocity profile. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_StopImmediate(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_StopProfiled(char const * serialNo, short channel);

	/// <summary> Requests the backlash. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetBacklash(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetBacklash(char const * serialNo, short channel, long distance)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_RequestBacklash(char const * serialNo, short channel);

	/// <summary> Get the backlash distance setting (used to control hysteresis). </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <returns> The backlash distance in \ref DeviceUnits_page. </returns>
	/// <seealso cref="BDC_RequestBacklash(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetBacklash(char const * serialNo, short channel, long distance)" />
	BENCHTOPDCSERVO_API long __cdecl BDC_GetBacklash(char const * serialNo, short channel);

	/// <summary> Sets the backlash distance (used to control hysteresis). </summary>
	/// <param name="serialNo">  The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="distance"> The distance in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_RequestBacklash(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_GetBacklash(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_SetBacklash(char const * serialNo, short channel, long distance);

	/// <summary> Get the Position Counter. </summary>
	/// <remarks> The position counter is identical to the position parameter.<br />
	/// 		  The position counter is set to zero when homing is complete.<br />
	/// 		  The position counter can also be set using <see cref="BDC_SetPositionCounter(char const * serialNo, short channel, long count)" /> <br />
	/// 		  if homing is not to be perforned</remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> Position count in \ref DeviceUnits_page. </returns>
	/// <seealso cref="BDC_GetPosition(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetPositionCounter(char const * serialNo, short channel, long count)" />
	BENCHTOPDCSERVO_API long __cdecl BDC_GetPositionCounter(char const * serialNo, short channel);

	/// <summary> Set the Position Counter. </summary>
	/// <remarks> Setting the position counter will locate the current position. <br />
	/// 		  Setting the position counter will effectively define the home position of a motor. </remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="count"> Position count in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetPositionCounter(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_GetPosition(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_SetPositionCounter(char const * serialNo, short channel, long count);

	/// <summary> Requests the encoder counter. </summary>
	/// <remarks> For devices that have an encoder, the current encoder position can be read. </remarks>
	/// <param name="serialNo"> The serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetEncoderCounter(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetEncoderCounter(char const * serialNo, short channel, long count)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_RequestEncoderCounter(char const * serialNo, short channel);

	/// <summary> Get the Encoder Counter. </summary>
	/// <remarks> For devices that have an encoder, the current encoder position can be read. </remarks>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <returns> Encoder count of encoder units. </returns>
	/// <seealso cref="BDC_RequestEncoderCounter(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetEncoderCounter(char const * serialNo, short channel, long count)" />
	BENCHTOPDCSERVO_API long __cdecl BDC_GetEncoderCounter(char const * serialNo, short channel);

	/// <summary> Set the Encoder Counter values. </summary>
	/// <remarks> setting the encoder counter to zero, effectively defines a home position on the encoder strip.<br />
	/// 		  NOTE, setting this value does not move the device.</remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="count"> The encoder count in encoder units. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_RequestEncoderCounter(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_GetEncoderCounter(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_SetEncoderCounter(char const * serialNo, short channel, long count);


	/// <summary> Requests the limit switch parameters. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetLimitSwitchParams(char const * serialNo, short channel, MOT_LimitSwitchModes * clockwiseHardwareLimit, MOT_LimitSwitchModes * anticlockwiseHardwareLimit, unsigned int * clockwisePosition, unsigned int * anticlockwisePosition, MOT_LimitSwitchSWModes * softLimitMode)" />
	/// <seealso cref="BDC_GetLimitSwitchParamsBlock(char const * serialNo, short channel, MOT_LimitSwitchParameters *limitSwitchParams)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_RequestLimitSwitchParams(char const * serialNo, short channel);

	/// <summary> Gets the limit switch parameters. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="clockwiseHardwareLimit"> The clockwise hardware limit mode.
	/// 					<list type=table>
	///							<item><term> Ignore switch or switch not present. </term><term>1</term></item>
	///							<item><term> Switch makes on contact. </term><term>2</term></item>
	///							<item><term> Switch breaks on contact. </term><term>3</term></item>
	/// 					 </list> <remarks> If these are bitwise-ORed with 0x0080 then the limits are swapped. </remarks> </param>
	/// <param name="anticlockwiseHardwareLimit"> The anticlockwise hardware limit mode
	/// 					 <list type=table>
	///							<item><term> Ignore switch or switch not present. </term><term>1</term></item>
	///							<item><term> Switch makes on contact. </term><term>2</term></item>
	///							<item><term> Switch breaks on contact. </term><term>3</term></item>
	/// 					 </list> <remarks> If these are bitwise-ORed with 0x0080 then the limits are swapped. </remarks> </param>
	/// 
	/// <param name="clockwisePosition"> The poition of the clockwise software limit in \ref DeviceUnits_page. </param>
	/// <param name="anticlockwisePosition"> The position of the anticlockwise software limit in \ref DeviceUnits_page. </param>
	/// <param name="softLimitMode"> The soft limit mode
	/// 					 <list type=table>
	///							<item><term> Ignore limit. </term><term>1</term></item>
	///							<item><term> Immediate Stop. </term><term>2</term></item>
	///							<item><term> SProfiled stop. </term><term>3</term></item>
	/// 					 </list> <remarks> If these are bitwise-ORed with 0x0080 then the limits are swapped. </remarks> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_RequestLimitSwitchParams(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetLimitSwitchParams(char const * serialNo, short channel, MOT_LimitSwitchModes clockwiseHardwareLimit, MOT_LimitSwitchModes anticlockwiseHardwareLimit, unsigned int clockwisePosition, unsigned int anticlockwisePosition, MOT_LimitSwitchSWModes softLimitMode)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_GetLimitSwitchParams(char const * serialNo, short channel, MOT_LimitSwitchModes * clockwiseHardwareLimit, MOT_LimitSwitchModes * anticlockwiseHardwareLimit, unsigned int * clockwisePosition, unsigned int * anticlockwisePosition, MOT_LimitSwitchSWModes * softLimitMode);

	/// <summary> Sets the limit switch parameters. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="clockwiseHardwareLimit"> The clockwise hardware limit mode.
	/// 					<list type=table>
	///							<item><term> Ignore switch or switch not present. </term><term>1</term></item>
	///							<item><term> Switch makes on contact. </term><term>2</term></item>
	///							<item><term> Switch breaks on contact. </term><term>3</term></item>
	/// 					 </list> <remarks> If these are bitwise-ORed with 0x0080 then the limits are swapped. </remarks> </param>
	/// <param name="anticlockwiseHardwareLimit"> The anticlockwise hardware limit mode
	/// 					 <list type=table>
	///							<item><term> Ignore switch or switch not present. </term><term>1</term></item>
	///							<item><term> Switch makes on contact. </term><term>2</term></item>
	///							<item><term> Switch breaks on contact. </term><term>3</term></item>
	/// 					 </list> <remarks> If these are bitwise-ORed with 0x0080 then the limits are swapped. </remarks> </param>
	/// 
	/// <param name="clockwisePosition"> The poition of the clockwise software limit in \ref DeviceUnits_page. </param>
	/// <param name="anticlockwisePosition"> The position of the anticlockwise software limit in \ref DeviceUnits_page. </param>
	/// <param name="softLimitMode"> The soft limit mode
	/// 					 <list type=table>
	///							<item><term> Ignore limit. </term><term>1</term></item>
	///							<item><term> Immediate Stop. </term><term>2</term></item>
	///							<item><term> SProfiled stop. </term><term>3</term></item>
	/// 					 </list> <remarks> If these are bitwise-ORed with 0x0080 then the limits are swapped. </remarks> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_SetLimitSwitchParams(char const * serialNo, short channel, MOT_LimitSwitchModes clockwiseHardwareLimit, MOT_LimitSwitchModes anticlockwiseHardwareLimit, unsigned int clockwisePosition, unsigned int anticlockwisePosition, MOT_LimitSwitchSWModes softLimitMode)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_SetLimitSwitchParams(char const * serialNo, short channel, MOT_LimitSwitchModes clockwiseHardwareLimit, MOT_LimitSwitchModes anticlockwiseHardwareLimit, unsigned int clockwisePosition, unsigned int anticlockwisePosition, MOT_LimitSwitchSWModes softLimitMode);

	/// <summary> Gets the software limits mode. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <returns>	The software limits mode <list type=table>
	///							<item><term> Disable any move outside of the current travel range of the stage. </term><term>0</term></item>
	///							<item><term> Truncate moves to within the current travel range of the stage. </term><term>1</term></item>
	///							<item><term> Allow all moves, regardless of whether they are within the current travel range of the stage. </term><term>2</term></item>
	/// 		  </list>. </returns>
	/// <returns> The software limits mode. </returns>
	/// <seealso cref="BDC_SetLimitsSoftwareApproachPolicy(const char * serialNo, MOT_LimitsSoftwareApproachPolicy limitsSoftwareApproachPolicy)" />
	BENCHTOPDCSERVO_API MOT_LimitsSoftwareApproachPolicy __cdecl BDC_GetSoftLimitMode(char const * serialNo, short channel);

	/// <summary> Sets the software limits mode. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="limitsSoftwareApproachPolicy"> The soft limit mode
	/// 					 <list type=table>
	///							<item><term> Disable any move outside of the current travel range of the stage. </term><term>0</term></item>
	///							<item><term> Truncate moves to within the current travel range of the stage. </term><term>1</term></item>
	///							<item><term> Allow all moves, regardless of whether they are within the current travel range of the stage. </term><term>2</term></item>
	/// 					 </list> </param>
	/// <seealso cref="BDC_GetSoftLimitMode(const char * serialNo)" />
	BENCHTOPDCSERVO_API void __cdecl BDC_SetLimitsSoftwareApproachPolicy(char const * serialNo, short channel, MOT_LimitsSoftwareApproachPolicy limitsSoftwareApproachPolicy);

	/// <summary> Get the move velocity parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec11 "Positioning" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="velocityParams"> Address of the MOT_VelocityParameters to recieve the velocity parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_RequestVelParams(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_GetVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BDC_SetVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="BDC_SetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters *velocityParams)" />
	/// <seealso cref="BDC_MoveToPosition(char const * serialNo, short channel, int index)" />
	/// <seealso cref="BDC_MoveRelative(char const * serialNo, short channel, int displacement)" />
	/// <seealso cref="BDC_MoveAtVelocity(char const * serialNo, short channel, MOT_TravelDirection direction)" />
    /// 		  \include CodeSnippet_movepars.cpp
    BENCHTOPDCSERVO_API short __cdecl BDC_GetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters  *velocityParams);

	/// <summary> Set the move velocity parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec11 "Positioning" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="velocityParams"> The address of the MOT_VelocityParameters holding the new velocity parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BDC_SetVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="BDC_GetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters  *velocityParams)" />
	/// <seealso cref="BDC_MoveToPosition(char const * serialNo, short channel, int index)" />
	/// <seealso cref="BDC_MoveRelative(char const * serialNo, short channel, int displacement)" />
	/// <seealso cref="BDC_MoveAtVelocity(char const * serialNo, short channel, MOT_TravelDirection direction)" />
    /// 		  \include CodeSnippet_movepars.cpp
	BENCHTOPDCSERVO_API short __cdecl BDC_SetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters *velocityParams);

	/// <summary> Sets the move absolute position. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="position"> The absolute position in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_RequestMoveAbsolutePosition(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_GetMoveAbsolutePosition(const char * serialNo, short channel)" />
	/// <seealso cref="BDC_MoveAbsolute(const char * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_SetMoveAbsolutePosition(const char * serialNo, short channel, int position);

	/// <summary> Requests the position of next absolute move. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetMoveAbsolutePosition(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetMoveAbsolutePosition(char const * serialNo, short channel, int position)" />
	/// <seealso cref="BDC_MoveAbsolute(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_RequestMoveAbsolutePosition(char const * serialNo, short channel);

	/// <summary> Gets the move absolute position. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <returns> The move absolute position in \ref DeviceUnits_page. </returns>
	/// <seealso cref="BDC_RequestMoveAbsolutePosition(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetMoveAbsolutePosition(const char * serialNo, short channel, int position)" />
	/// <seealso cref="BDC_MoveAbsolute(const char * serialNo, short channel)" />
	BENCHTOPDCSERVO_API int __cdecl BDC_GetMoveAbsolutePosition(const char * serialNo, short channel);

	/// <summary> Moves the device to the position defined in the SetMoveAbsolute command. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_SetMoveAbsolutePosition(const char * serialNo, short channel, int position)" />
	/// <seealso cref="BDC_RequestMoveAbsolutePosition(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_GetMoveAbsolutePosition(const char * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_MoveAbsolute(const char * serialNo, short channel);

	/// <summary> Sets the move relative distance. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="distance"> The relative distance in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_RequestMoveRelativeDistance(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_GetMoveRelativeDistance(const char * serialNo, short channel)" />
	/// <seealso cref="BDC_MoveRelativeDistance(const char * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_SetMoveRelativeDistance(const char * serialNo, short channel, int distance);

	/// <summary> Requests the relative move distance. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetMoveRelativeDistance(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetMoveRelativeDistance(char const * serialNo, short channel, int distance)" />
	/// <seealso cref="BDC_MoveRelativeDistance(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_RequestMoveRelativeDistance(char const * serialNo, short channel);

	/// <summary> Gets the move relative distance. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <returns> The move relative distance in \ref DeviceUnits_page. </returns>
	/// <seealso cref="BDC_RequestMoveRelativeDistance(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetMoveRelativeDistance(const char * serialNo, short channel, int distance)" />
	/// <seealso cref="BDC_MoveRelativeDistance(const char * serialNo, short channel)" />
	BENCHTOPDCSERVO_API int __cdecl BDC_GetMoveRelativeDistance(const char * serialNo, short channel);

	/// <summary> Moves the device by a relative distancce defined by SetMoveRelativeDistance. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_SetMoveRelativeDistance(const char * serialNo, short channel, int distance)" />
	/// <seealso cref="BDC_RequestMoveRelativeDistance(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_GetMoveRelativeDistance(const char * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_MoveRelativeDistance(const char * serialNo, short channel);

	/// <summary> Get the homing parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec10 "Homing" for more detail.<remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="homingParams"> Address of the MOT_HomingParameters to recieve the homing parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_RequestHomingParams(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_GetHomingVelocity(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetHomingVelocity(char const * serialNo, short channel, unsigned int velocity)" />
	/// <seealso cref="BDC_SetHomingParamsBlock(char const * serialNo, short channel, MOT_HomingParameters *homingParams)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_GetHomingParamsBlock(char const * serialNo, short channel, MOT_HomingParameters *homingParams);

	/// <summary> Set the homing parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec10 "Homing" for more detail.<remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="homingParams"> Address of the new homing parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_RequestHomingParams(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_GetHomingVelocity(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetHomingVelocity(char const * serialNo, short channel, unsigned int velocity)" />
	/// <seealso cref="BDC_GetHomingParamsBlock(char const * serialNo, short channel, MOT_HomingParameters *homingParams)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_SetHomingParamsBlock(char const * serialNo, short channel, MOT_HomingParameters *homingParams);

	/// <summary> Get the jog parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">  The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="jogParams"> The address of the MOT_JogParameters block to recieve the jog parameters </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_RequestJogParams(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_GetJogMode(char const * serialNo, short channel, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="BDC_SetJogMode(char const * serialNo, short channel, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="BDC_GetJogStepSize(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetJogStepSize(char const * serialNo, short channel, unsigned int stepSize)" />
	/// <seealso cref="BDC_SetJogVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="BDC_GetJogVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BDC_SetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BDC_MoveJog(char const * serialNo, short channel, MOT_TravelDirection jogDirection)" />
    /// 		  \include CodeSnippet_jogpars.cpp
	BENCHTOPDCSERVO_API short __cdecl BDC_GetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParams);

	/// <summary> Set the jog parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="jogParams"> The address of the new MOT_JogParameters block. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetJogMode(char const * serialNo, short channel, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="BDC_SetJogMode(char const * serialNo, short channel, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="BDC_GetJogStepSize(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetJogStepSize(char const * serialNo, short channel, unsigned int stepSize)" />
	/// <seealso cref="BDC_SetJogVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="BDC_GetJogVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BDC_GetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BDC_MoveJog(char const * serialNo, short channel, MOT_TravelDirection jogDirection)" />
    /// 		  \include CodeSnippet_jogpars.cpp
	BENCHTOPDCSERVO_API short __cdecl BDC_SetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParams);

	/// <summary> Get the limit switch parameters. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="limitSwitchParams"> Address of the MOT_LimitSwitchParameters parameter to recieve the  limit switch parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_RequestLimitSwitchParams(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetLimitSwitchParams(char const * serialNo, MOT_LimitSwitchModes clockwiseHardwareLimit, MOT_LimitSwitchModes anticlockwiseHardwareLimit, unsigned int clockwisePosition, unsigned int anticlockwisePosition, MOT_LimitSwitchSWModes softLimitMode)" />
	/// <seealso cref="BDC_GetLimitSwitchParams(char const * serialNo, MOT_LimitSwitchModes * clockwiseHardwareLimit, MOT_LimitSwitchModes * anticlockwiseHardwareLimit, unsigned int * clockwisePosition, unsigned int * anticlockwisePosition, MOT_LimitSwitchSWModes * softLimitMode)" />
	/// <seealso cref="BDC_SetLimitSwitchParamsBlock(const char * serialNo, MOT_LimitSwitchParameters *limitSwitchParams)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_GetLimitSwitchParamsBlock(char const * serialNo, short channel, MOT_LimitSwitchParameters *limitSwitchParams);

	/// <summary> Set the limit switch parameters. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="limitSwitchParams"> Address of the MOT_LimitSwitchParameters parameter containing the new limit switch parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetLimitSwitchParams(char const * serialNo, MOT_LimitSwitchModes * clockwiseHardwareLimit, MOT_LimitSwitchModes * anticlockwiseHardwareLimit, unsigned int * clockwisePosition, unsigned int * anticlockwisePosition, MOT_LimitSwitchSWModes * softLimitMode)" />
	/// <seealso cref="BDC_SetLimitSwitchParams(char const * serialNo, MOT_LimitSwitchModes clockwiseHardwareLimit, MOT_LimitSwitchModes anticlockwiseHardwareLimit, unsigned int clockwisePosition, unsigned int anticlockwisePosition, MOT_LimitSwitchSWModes softLimitMode)" />
	/// <seealso cref="BDC_GetLimitSwitchParamsBlock(const char * serialNo, MOT_LimitSwitchParameters *limitSwitchParams)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_SetLimitSwitchParamsBlock(char const * serialNo, short channel, MOT_LimitSwitchParameters *limitSwitchParams);


	/// <summary> Requests the trigger switch parameter. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetTriggerSwitches(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetDigitalOutputs(char const * serialNo, short channel, byte outputsBits)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_RequestTriggerSwitches(char const * serialNo, short channel);

	/// <summary> Gets the trigger switch parameter. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> Trigger mask where:
	/// 				<list type=table>
	///						<item><term> Bit 0. </term><term>Input trigger enabled.</term></item>
	///						<item><term> Bit 1. </term><term>Output trigger enabled.</term></item>
	///						<item><term> Bit 2. </term><term>Output Passthrough mode enabled where Output Trigger mirrors Input Trigger.</term></item>
	///						<item><term> Bit 3. </term><term>Output trigger high when moving.</term></item>
	///						<item><term> Bit 4. </term><term>Performs relative move when input trigger goes high.</term></item>
	///						<item><term> Bit 5. </term><term>Performs absolute move when input trigger goes high.</term></item>
	///						<item><term> Bit 6. </term><term>Perfgorms home when input trigger goes high.</term></item>
	///						<item><term> Bit 7. </term><term></term>Output triggers when motor moved by software command.</item>
	/// 				 </list> </returns>
	/// <seealso cref="BDC_RequestTriggerSwitches(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_SetTriggerSwitches(char const * serialNo, short channel, byte indicatorBits)" />
	BENCHTOPDCSERVO_API byte __cdecl BDC_GetTriggerSwitches(char const * serialNo, short channel);

	/// <summary> Sets the trigger switch parameter. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="indicatorBits"> The trigger mode:
	/// 					  <list type=table>
	///							<item><term> Bit 0. </term><term>Input trigger enabled.</term></item>
	///							<item><term> Bit 1. </term><term>Output trigger enabled.</term></item>
	///							<item><term> Bit 2. </term><term>Output Passthrough mode enabled where Output Trigger mirrors Input Trigger.</term></item>
	///							<item><term> Bit 3. </term><term>Output trigger high when moving.</term></item>
	///							<item><term> Bit 4. </term><term>Performs relative move when input trigger goes high.</term></item>
	///							<item><term> Bit 5. </term><term>Performs absolute move when input trigger goes high.</term></item>
	///							<item><term> Bit 6. </term><term>Perfgorms home when input trigger goes high.</term></item>
	///							<item><term> Bit 7. </term><term></term>Output triggers when motor moved by software command.</item>
	/// 					 </list>. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_RequestTriggerSwitches(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_GetTriggerSwitches(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_SetTriggerSwitches(char const * serialNo, short channel, byte indicatorBits);

	/// <summary> Requests the digital output bits. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_SetDigitalOutputs(char const * serialNo, short channel, byte outputsBits)" />
	/// <seealso cref="BDC_GetDigitalOutputs(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_RequestDigitalOutputs(char const * serialNo, short channel);

	/// <summary> Gets the digital output bits. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> Bit mask of states of the 4 digital output pins. </returns>
	/// <seealso cref="BDC_SetDigitalOutputs(char const * serialNo, short channel, byte outputsBits)" />
	/// <seealso cref="BDC_RequestDigitalOutputs(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API byte __cdecl BDC_GetDigitalOutputs(char const * serialNo, short channel);

	/// <summary> Sets the digital output bits. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="outputsBits"> Bit mask to set states of the 4 digital output pins. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetDigitalOutputs(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_RequestDigitalOutputs(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_SetDigitalOutputs(char const * serialNo, short channel, byte outputsBits);

	/// <summary> Requests the rack digital output bits. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_SetRackDigitalOutputs(char const * serialNo, byte outputsBits)" />
	/// <seealso cref="BDC_GetRackDigitalOutputs(char const * serialNo)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_RequestRackDigitalOutputs(char const * serialNo);

	/// <summary> Gets the rack digital output bits. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <returns> Bit mask of states of the 4 digital output pins. </returns>
	/// <seealso cref="BDC_SetRackDigitalOutputs(char const * serialNo, byte outputsBits)" />
	/// <seealso cref="BDC_RequestRackDigitalOutputs(char const * serialNo)" />
	BENCHTOPDCSERVO_API byte __cdecl BDC_GetRackDigitalOutputs(char const * serialNo);

	/// <summary> Sets the rack digital output bits. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="outputsBits"> Bit mask to set states of the 4 digital output pins. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetRackDigitalOutputs(char const * serialNo)" />
	/// <seealso cref="BDC_RequestRackDigitalOutputs(char const * serialNo)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_SetRackDigitalOutputs(char const * serialNo, byte outputsBits);

	/// <summary> Requests the Rack status bits be downloaded. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetRackStatusBits(char const * serialNo)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_RequestRackStatusBits(char const * serialNo);

	/// <summary> Gets the Rack status bits. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The status bits including 4 with one per electronic input pin. </returns>
	/// <seealso cref="BDC_RequestRackStatusBits(char const * serialNo)" />
	BENCHTOPDCSERVO_API DWORD __cdecl BDC_GetRackStatusBits(char const * serialNo);

	/// <summary> Requests the analogue input voltage reading. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="BDC_GetDigitalOutputs(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_RequestInputVoltage(char const * serialNo, short channel);

	/// <summary> Gets the analogue input voltage reading. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The input voltage 0-32768 corresponding to 0-5V. </returns>
	/// <seealso cref="BDC_RequestInputVoltage(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API WORD __cdecl BDC_GetInputVoltage(char const * serialNo, short channel);

	/// <summary> Requests the PID parameters for DC motors used in an algorithm involving calculus. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetDCPIDParams(const char * serialNo, MOT_DC_PIDParameters *DCproportionalIntegralDerivativeParams, short channel)" />
	/// <seealso cref="BDC_SetDCPIDParams(const char * serialNo, MOT_DC_PIDParameters *DCproportionalIntegralDerivativeParams, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_RequestDCPIDParams(const char * serialNo, short channel);

	/// <summary> Gets the DC PID parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="DCproportionalIntegralDerivativeParams"> Address of the MOT_DC_PIDParameters parameter to recieve the DC PID parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_SetDCPIDParams(const char * serialNo, MOT_DC_PIDParameters *DCproportionalIntegralDerivativeParams, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_GetDCPIDParams(const char * serialNo, MOT_DC_PIDParameters *DCproportionalIntegralDerivativeParams, short channel);

	/// <summary> Sets the DC PID parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="DCproportionalIntegralDerivativeParams"> Address of the MOT_DC_PIDParameters parameter containing the new  DC PID parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetDCPIDParams(const char * serialNo, MOT_DC_PIDParameters *DCproportionalIntegralDerivativeParams, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_SetDCPIDParams(const char * serialNo, MOT_DC_PIDParameters *DCproportionalIntegralDerivativeParams, short channel);

	/// <summary> Suspend automatic messages at ends of moves. </summary>
	/// <remarks> Useful to speed up part of real-time system with lots of short moves. </remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_ResumeMoveMessages(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_SuspendMoveMessages(char const * serialNo, short channel);

	/// <summary> Resume suspended move messages. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_SuspendMoveMessages(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_ResumeMoveMessages(char const * serialNo, short channel);

	/// <summary> Requests the current position. </summary>
	/// <remarks> This needs to be called to get the device to send it's current position.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="BDC_StartPolling(char const * serialNo, short channel, int milliseconds)" />. </remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
    /// 		  \include CodeSnippet_move.cpp
	/// <seealso cref="BDC_GetPosition(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_StartPolling(char const * serialNo, short channel, int milliseconds)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_RequestPosition(char const * serialNo, short channel);
	
	/// <summary> Request the status bits which identify the current motor state. </summary>
	/// <remarks> This needs to be called to get the device to send it's current status bits.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="BDC_StartPolling(char const * serialNo, short channel, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="BDC_GetStatusBits(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_StartPolling(char const * serialNo, short channel, int milliseconds)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_RequestStatusBits(char const * serialNo, short channel);

	/// <summary>Get the current status bits. </summary>
	/// <remarks> This returns the latest status bits received from the device.<br />
	/// 		  To get new status bits, use <see cref="BDC_RequestStatusBits(char const * serialNo, short channel)" />
	/// 		  or use the polling functions, <see cref="BDC_StartPolling(char const * serialNo, short channel, int milliseconds)" />.  </remarks>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <returns>	The status bits from the device <list type=table>
	///				<item><term>0x00000001</term><term>CW hardware limit switch (0=No contact, 1=Contact).</term></item>
	///				<item><term>0x00000002</term><term>CCW hardware limit switch (0=No contact, 1=Contact).</term></item>
	///				<item><term>0x00000004</term><term>CW software limit switch (0=No contact, 1=Contact).</term></item>
 	///				<item><term>0x00000008</term><term>CCW software limit switch (0=No contact, 1=Contact).</term></item>
	///				<item><term>0x00000010</term><term>Motor shaft moving clockwise (1=Moving, 0=Stationary).</term></item>
	///				<item><term>0x00000020</term><term>Motor shaft moving counterclockwise (1=Moving, 0=Stationary).</term></item>
	///				<item><term>0x00000040</term><term>Shaft jogging clockwise (1=Moving, 0=Stationary).</term></item>
	///				<item><term>0x00000080</term><term>Shaft jogging counterclockwise (1=Moving, 0=Stationary).</term></item>
	///				<item><term>0x00000100</term><term>Motor connected (1=Connected, 0=Not connected).</term></item>
 	///				<item><term>0x00000200</term><term>Motor homing (1=Homing, 0=Not homing).</term></item>
	///				<item><term>0x00000400</term><term>Motor homed (1=Homed, 0=Not homed).</term></item>
	///				<item><term>0x00000800</term><term>For Future Use.</term></item>
 	///				<item><term>0x00001000</term><term>Not applicable.</term></item>
	///				<item><term>0x00002000</term><term></term></item>
	///				<item><term>...</term><term></term></item>
	///				<item><term>0x00080000</term><term></term></item>
	///				<item><term>0x00100000</term><term>Digital input 1 state (1=Logic high, 0=Logic low).</term></item>
	///				<item><term>0x00200000</term><term>Digital input 2 state (1=Logic high, 0=Logic low).</term></item>
	///				<item><term>0x00400000</term><term>Digital input 3 state (1=Logic high, 0=Logic low).</term></item>
	///				<item><term>0x00800000</term><term>Digital input 4 state (1=Logic high, 0=Logic low).</term></item>
	///				<item><term>0x01000000</term><term>Digital input 5 state (1=Logic high, 0=Logic low).</term></item>
	///				<item><term>0x02000000</term><term>Digital input 6 state (1=Logic high, 0=Logic low).</term></item>
	///				<item><term>0x04000000</term><term>For Future Use.</term></item>
	///				<item><term>0x08000000</term><term>For Future Use.</term></item>
	///				<item><term>0x10000000</term><term>For Future Use.</term></item>
	///				<item><term>0x20000000</term><term>Active (1=Active, 0=Not active).</term></item>
	///				<item><term>0x40000000</term><term>For Future Use.</term></item>
	///				<item><term>0x80000000</term><term>Channel enabled (1=Enabled, 0=Disabled).</term></item>
	/// 		  </list> <remarks> Bits 21 to 26 (Digital Input States) are only applicable if the associated digital input is fitted to your controller - see the relevant handbook for more details. </remarks> </returns>
	/// <seealso cref="BDC_RequestStatusBits(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_StartPolling(char const * serialNo, short channel, int milliseconds)" />
	BENCHTOPDCSERVO_API DWORD __cdecl BDC_GetStatusBits(char const * serialNo, short channel);

	/// <summary> Starts the internal polling loop which continuously requests position and status. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="milliseconds">The milliseconds polling rate. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="BDC_StopPolling(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_PollingDuration(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_RequestStatusBits(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_RequestPosition(char const * serialNo, short channel)" />
	/// \include CodeSnippet_connectionN.cpp
	BENCHTOPDCSERVO_API bool __cdecl BDC_StartPolling(char const * serialNo, short channel, int milliseconds);

	/// <summary> Gets the polling loop duration. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <returns> The time between polls in milliseconds or 0 if polling is not active. </returns>
	/// <seealso cref="BDC_StartPolling(char const * serialNo, short channel, int milliseconds)" />
	/// <seealso cref="BDC_StopPolling(char const * serialNo, short channel)" />
	/// \include CodeSnippet_connectionN.cpp
	BENCHTOPDCSERVO_API long __cdecl BDC_PollingDuration(char const * serialNo, short channel);

	/// <summary> Stops the internal polling loop. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <seealso cref="BDC_StartPolling(char const * serialNo, short channel, int milliseconds)" />
	/// <seealso cref="BDC_PollingDuration(char const * serialNo, short channel)" />
	/// \include CodeSnippet_connectionN.cpp
	BENCHTOPDCSERVO_API void __cdecl BDC_StopPolling(char const * serialNo, short channel);

	/// <summary> Gets the time in milliseconds since tha last message was received from the device. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="lastUpdateTimeMS"> The time since the last message was received in milliseconds. </param>
	/// <returns> True if monitoring is enabled otherwize False. </returns>
	/// <seealso cref="BDC_EnableLastMsgTimer(char const * serialNo, short channel, bool enable, __int32 lastMsgTimeout )" />
	/// <seealso cref="BDC_HasLastMsgTimerOverrun(char const * serialNo, short channel)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	BENCHTOPDCSERVO_API bool __cdecl BDC_TimeSinceLastMsgReceived(char const * serialNo, short channel, __int64 &lastUpdateTimeMS );

	/// <summary> Enables the last message monitoring timer. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <param name="enable"> True to enable monitoring otherwise False to disable. </param>
	/// <param name="lastMsgTimeout"> The last message error timeout in ms. 0 to disable. </param>
	/// <seealso cref="BDC_TimeSinceLastMsgReceived(char const * serialNo, short channel, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="BDC_HasLastMsgTimerOverrun(char const * serialNo, short channel)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	BENCHTOPDCSERVO_API void __cdecl BDC_EnableLastMsgTimer(char const * serialNo, short channel, bool enable, __int32 lastMsgTimeout );

	/// <summary> Queries if the time since the last message has exceeded the lastMsgTimeout set by <see cref="BDC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )"/>. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel"> The channel (1 to n). </param>
	/// <returns> True if last message timer has elapsed, False if monitoring is not enabled or if time of last message received is less than lastMsgTimeout. </returns>
	/// <seealso cref="BDC_TimeSinceLastMsgReceived(char const * serialNo, short channel, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="BDC_EnableLastMsgTimer(char const * serialNo, short channel, bool enable, __int32 lastMsgTimeout )" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	BENCHTOPDCSERVO_API bool __cdecl BDC_HasLastMsgTimerOverrun(char const * serialNo, short channel);

	/// <summary> Requests that all settings are download from device. </summary>
	/// <remarks> This function requests that the device upload all it's settings to the DLL.</remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	BENCHTOPDCSERVO_API short __cdecl BDC_RequestSettings(char const * serialNo, short channel);

	/// <summary> Gets the DC Servo minimum stage position. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The Minimum position in \ref DeviceUnits_page. </returns>
	/// <seealso cref="BDC_SetStageAxisLimits(char const * serialNo, short channel, int minPosition, int maxPosition)" />
	/// <seealso cref="BDC_GetStageAxisMaxPos(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API int __cdecl BDC_GetStageAxisMinPos(char const * serialNo, short channel);

	/// <summary> Gets the DC Servo maximum stage position. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The Maximum position in \ref DeviceUnits_page. </returns>
	/// <seealso cref="BDC_SetStageAxisLimits(char const * serialNo, short channel, int minPosition, int maxPosition)" />
	/// <seealso cref="BDC_GetStageAxisMinPos(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API int __cdecl BDC_GetStageAxisMaxPos(char const * serialNo, short channel);

	/// <summary> Sets the stage axis position limits. </summary>
	/// <remarks> This function sets the limits of travel for the stage.<Br />
	/// 		  The implementation will depend upon the nature of the travel being requested and the Soft Limits mode which can be obtained using <see cref="BDC_GetSoftLimitMode(char const * serialNo)" />. <Br />
	/// 		  <B>MoveAbsolute</B>, <B>MoveRelative</B> and <B>Jog (Single Step)</B> will obey the Soft Limit Mode.
	/// 		  If the target position is outside the limits then either a full move, a partial move or no move will occur.<Br />
	/// 		  <B>Jog (Continuous)</B> and <B>Move Continuous</B> will attempt to obey the limits, but as these moves rely on position information feedback from the device to detect if the travel is exceeding the limits, the device will stop, but it is likely to overshoot the limit, especially at high velocity.<Br />
	/// 		  <B>Home</B> will always ignore the software limits.</remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="minPosition"> The minimum position in \ref DeviceUnits_page. </param>
	/// <param name="maxPosition"> The maximum position in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetStageAxisMinPos(char const * serialNo, short channel)" />
	/// <seealso cref="BDC_GetStageAxisMaxPos(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_SetStageAxisLimits(char const * serialNo, short channel, int minPosition, int maxPosition);

	/// <summary> Set the motor travel mode. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="travelMode"> The travel mode.
	/// 						  <list type=table>
	///								<item><term>Linear motion</term><term>1</term></item>
	///								<item><term>Rotational motion</term><term>2</term></item>
	/// 						  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetMotorTravelMode(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_SetMotorTravelMode(char const * serialNo, short channel, MOT_TravelModes travelMode);

	/// <summary> Get the motor travel mode. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <returns> The travel mode.
	/// 						  <list type=table>
	///								<item><term>Linear motion</term><term>1</term></item>
	///								<item><term>Rotational motion</term><term>2</term></item>
	/// 						  </list> </returns>
	/// <seealso cref="BDC_SetMotorTravelMode(char const * serialNo, short channel, int travelMode)" />
	BENCHTOPDCSERVO_API MOT_TravelModes __cdecl BDC_GetMotorTravelMode(char const * serialNo, short channel);

	/// \deprecated
	/// <summary> Sets the motor stage parameters. </summary>
	/// <remarks> superceded by <see cref="BDC_SetMotorParamsExt(char const * serialNo, short channel, double stepsPerRevolution, double gearboxRatio, double pitch)"/> </remarks>
	/// <remarks> These parameters, when combined define the stage motion in terms of \ref RealWorldUnits_page. (mm or degrees)<br />
	/// 		  The real world unit is defined from stepsPerRev * gearBoxRatio / pitch.</remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="stepsPerRev">  The steps per revolution. </param>
	/// <param name="gearBoxRatio"> The gear box ratio. </param>
	/// <param name="pitch">	    The pitch. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetMotorParams(char const * serialNo, short channel, long *stepsPerRev, long *gearBoxRatio, float *pitch)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_SetMotorParams(char const * serialNo, short channel, long stepsPerRev, long gearBoxRatio, float pitch);

	/// \deprecated
	/// <summary> Sets the motor stage parameters. </summary>
	/// <remarks> superceded by <see cref="BDC_GetMotorParamsExt(char const * serialNo, short channel, double *stepsPerRevolution, double *gearboxRatio, double *pitch)"/> </remarks>
	/// <remarks> These parameters, when combined define the stage motion in terms of \ref RealWorldUnits_page. (mm or degrees)<br />
	/// 		  The real world unit is defined from stepsPerRev * gearBoxRatio / pitch.</remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="stepsPerRev">  The steps per revolution. </param>
	/// <param name="gearBoxRatio"> The gear box ratio. </param>
	/// <param name="pitch">	    The pitch. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetMotorParams(char const * serialNo, short channel, long *stepsPerRev, long *gearBoxRatio, float *pitch)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_GetMotorParams(char const * serialNo, short channel, long *stepsPerRev, long *gearBoxRatio, float *pitch);

	/// <summary> Sets the motor stage parameters. </summary>
	/// <remarks> These parameters, when combined define the stage motion in terms of \ref RealWorldUnits_page. (mm or degrees)<br />
	/// 		  The real world unit is defined from stepsPerRev * gearBoxRatio / pitch.</remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="stepsPerRev">  The steps per revolution. </param>
	/// <param name="gearBoxRatio"> The gear box ratio. </param>
	/// <param name="pitch">	    The pitch. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetMotorParamsExt(char const * serialNo, short channel, long *stepsPerRev, long *gearBoxRatio, float *pitch)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_SetMotorParamsExt(char const * serialNo, short channel, double stepsPerRev, double gearBoxRatio, double pitch);

	/// <summary> Sets the motor stage parameters. </summary>
	/// <remarks> These parameters, when combined define the stage motion in terms of \ref RealWorldUnits_page. (mm or degrees)<br />
	/// 		  The real world unit is defined from stepsPerRev * gearBoxRatio / pitch.</remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="stepsPerRev">  The steps per revolution. </param>
	/// <param name="gearBoxRatio"> The gear box ratio. </param>
	/// <param name="pitch">	    The pitch. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetMotorParamsExt(char const * serialNo, short channel, long *stepsPerRev, long *gearBoxRatio, float *pitch)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_GetMotorParamsExt(char const * serialNo, short channel, double *stepsPerRev, double *gearBoxRatio, double *pitch);

	/// \deprecated
	/// <summary> Sets the absolute maximum velocity and acceleration constants for the current stage. </summary>
	/// <remarks> These parameters are maintained for user info only and do not reflect the current stage parameters.<Br />
    ///           The absolute maximum velocity and acceleration constants are initialized from the stage settings..</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="maxVelocity">  The absolute maximum velocity in real world units. </param>
	/// <param name="maxAcceleration"> The absolute maximum acceleration in real world units. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetMotorVelocityLimits(char const * serialNo, short channel, double *maxVelocity, double *maxAcceleration)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_SetMotorVelocityLimits(char const * serialNo, short channel, double maxVelocity, double maxAcceleration);

	/// <summary> Gets the absolute maximum velocity and acceleration constants for the current stage. </summary>
	/// <remarks> These parameters are maintained for user info only and do not reflect the current stage parameters.<Br />
    ///           The absolute maximum velocity and acceleration constants are initialized from the stage settings..</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="maxVelocity">  Address of the parameter to receive the absolute maximum velocity in real world units. </param>
	/// <param name="maxAcceleration"> Address of the parameter to receive the absolute maximum acceleration in real world units. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_SetMotorVelocityLimits(char const * serialNo, short channel, double maxVelocity, double maxAcceleration)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_GetMotorVelocityLimits(char const * serialNo, short channel, double *maxVelocity, double *maxAcceleration);

	/// <summary>	Reset the rotation modes for a rotational device. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">		 The channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_SetRotationModes(char const * serialNo, MOT_MovementModes mode, MOT_MovementDirections direction)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_ResetRotationModes(char const * serialNo, short channel);

	/// <summary>	Set the rotation modes for a rotational device. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">		 The channel. </param>
	/// <param name="mode">	The rotation mode.<list type=table>
	///								<item><term>Linear Range (Fixed Limit, cannot rotate)</term><term>0</term></item>
	///								<item><term>RotationalUnlimited (Ranges between +/- Infinity)</term><term>1</term></item>
	///								<item><term>Rotational Wrapping (Ranges between 0 to 360 with wrapping)</term><term>2</term></item>
	/// 						  </list> </param>
	/// <param name="direction"> The rotation direction when moving between two angles.<list type=table>
	///								<item><term>Quickets (Always takes the shortedt path)</term><term>0</term></item>
	///								<item><term>Forwards (Always moves forwards)</term><term>1</term></item>
	///								<item><term>Backwards (Always moves backwards)</term><term>2</term></item>
	/// 						  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_ResetRotationModes(char const * serialNo)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_SetRotationModes(char const * serialNo, short channel, MOT_MovementModes mode, MOT_MovementDirections direction);

	/// \deprecated
	/// <summary> Sets the absolute minimum and maximum travel range constants for the current stage. </summary>
	/// <remarks> These parameters are maintained for user info only and do not reflect the current travel range of the stage.<Br />
    ///           The absolute minimum and maximum travel range constants are initialized from the stage settings. These values can be adjusted to relative positions based upon the Home Offset.<Br />
    ///           <Br />
    ///           To set the working travel range of the stage use the function <see cref="BDC_SetStageAxisLimits(char const * serialNo, short channel, int minPosition, int maxPosition)" /><Br />
    ///           Use the following to convert between real worl and device units.<Br />
    ///           <see cref="BDC_GetRealValueFromDeviceUnit(char const * serialNo, short channel, int device_unit, double *real_unit, int unitType)" /><Br />
    ///           <see cref="BDC_GetDeviceUnitFromRealValue(char const * serialNo, short channel, double real_unit, int *device_unit, int unitType)" /> </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">		 The channel. </param>
	/// <param name="minPosition">  The absolute minimum position in real world units. </param>
	/// <param name="maxPosition"> The absolute maximum position in real world units. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetMotorTravelLimits(char const * serialNo, short channel, double *minPosition, double *maxPosition)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_SetMotorTravelLimits(char const * serialNo, short channel, double minPosition, double maxPosition);

	/// <summary> Gets the absolute minimum and maximum travel range constants for the current stage. </summary>
	/// <remarks> These parameters are maintained for user info only and do not reflect the current travel range of the stage.<Br />
    ///           The absolute minimum and maximum travel range constants are initialized from the stage settings. These values can be adjusted to relative positions based upon the Home Offset.</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">		 The channel. </param>
	/// <param name="minPosition">  Address of the parameter to receive the absolute minimum position in real world units. </param>
	/// <param name="maxPosition"> Address of the parameter to receive the absolute maximum position in real world units. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_SetMotorTravelLimits(char const * serialNo, short channel, double minPosition, double maxPosition)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_GetMotorTravelLimits(char const * serialNo, short channel, double *minPosition, double *maxPosition);

	/// <summary>	Converts a device unit to a real world unit. </summary>
	/// <param name="serialNo">   	The serial no. </param>
	/// <param name="device_unit">	The device unit. </param>
	/// <param name="channel">		 The channel (1 to n). </param>
	/// <param name="real_unit">  	The real unit. </param>
	/// <param name="unitType">   	Type of the unit.<list type=table>
	///								<item><term>Distance</term><term>0</term></item>
	///								<item><term>Velocity</term><term>1</term></item>
	///								<item><term>Acceleration</term><term>2</term></item>
	/// 						  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetDeviceUnitFromRealValue(char const * serialNo, short channel, double real_unit, int *device_unit, int unitType)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_GetRealValueFromDeviceUnit(char const * serialNo, short channel, int device_unit, double *real_unit, int unitType);

	/// <summary>	Converts a device unit to a real world unit. </summary>
	/// <param name="serialNo">   	The serial no. </param>
	/// <param name="channel">		 The channel (1 to n). </param>
	/// <param name="device_unit">	The device unit. </param>
	/// <param name="real_unit">  	The real unit. </param>
	/// <param name="unitType">   	Type of the unit.<list type=table>
	///								<item><term>Distance</term><term>0</term></item>
	///								<item><term>Velocity</term><term>1</term></item>
	///								<item><term>Acceleration</term><term>2</term></item>
	/// 						  </list> </param>
	/// <returns>	Success. </returns>
	/// <seealso cref="BDC_GetRealValueFromDeviceUnit(char const * serialNo, short channel, int device_unit, double *real_unit, int unitType)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_GetDeviceUnitFromRealValue(char const * serialNo, short channel, double real_unit, int *device_unit, int unitType);
	
	/// <summary> Requests the encoder resolution parameters. </summary>
	/// <remarks> For devices that have an encoder, the current encoder resolution can be read. </remarks>
	/// <param name="serialNo"> The serial no. </param>
	/// <param name="channel"> The channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetEncoderResolutionParams(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_RequestEncoderResolutionParams(char const * serialNo, short channel);

	/// <summary> Get the encoder resolution parameters. </summary>
	/// <remarks> For devices that have an encoder, the current encoder resolution can be read. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">  The channel. </param>
	/// <param name="resolutionParams"> Options for controlling the resolution parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_RequestEncoderResolutionParams(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_GetEncoderResolutionParams(char const * serialNo, short channel, MOT_EncoderResolutionParams * resolutionParams);

	/// <summary>Requests the trigger parameters. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <param name="channel">	The channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetTriggerConfigParams(char const * serialNo, short channel, KMOT_TriggerPortMode *trigger1Mode, KMOT_TriggerPortPolarity *trigger1Polarity, KMOT_TriggerPortMode *trigger2Mode, KMOT_TriggerPortPolarity *trigger2Polarity)" />
	/// <seealso cref="BDC_GetTriggerConfigParamsBlock(char const * serialNo, short channel, KMOT_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="BDC_SetTriggerConfigParams(char const * serialNo, short channel, KMOT_TriggerPortMode trigger1Mode, KMOT_TriggerPortPolarity trigger1Polarity, KMOT_TriggerPortMode trigger2Mode, KMOT_TriggerPortPolarity trigger2Polarity)" />
	/// <seealso cref="BDC_SetTriggerConfigParamsBlock(char const * serialNo, short channel, KMOT_TriggerConfig *triggerConfigParams)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_RequestTriggerConfigParams(char const * serialNo, short channel);

	/// <summary> Gets the trigger configuration parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The channel. </param>
	/// <param name="trigger1Mode">	    The trigger 1 mode.<list type=table>
	///						<item><term>0</term><term>Trigger disabled</term></item>
	///						<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="BMC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
	///						<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
	///						<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
	///						<item><term>4</term><term>Trigger Input - Perform a Home action</term></item>
	///						<item><term>5</term><term>Trigger Input - Perform a Stop Immediate action</term></item>
	///						<item><term>10</term><term>Trigger Output - General purpose output (<see cref="BMC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
	///						<item><term>11</term><term>Trigger Output - Set when device moving</term></item>
	///						<item><term>12</term><term>Trigger Output - Set when at max velocity</term></item>
	///						<item><term>13</term><term>Trigger Output - Set when at predefine position steps</term></item>
	///						<item><term>14</term><term>Trigger Output - TBD mode</term></item>
	///		 		  </list></param>
	/// <param name="trigger1Polarity"> The trigger 1 polarity.<list type=table>
	///						<item><term>1</term><term>Output high when set</term></item>
	///						<item><term>2</term><term>Output low when set</term></item>
	///		 		  </list> </param>
	/// <param name="trigger2Mode">	    The trigger 2 mode.<list type=table>
	///						<item><term>0</term><term>Trigger disabled</term></item>
	///						<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="BMC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
	///						<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
	///						<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
	///						<item><term>4</term><term>Trigger Input - Perform a Home action</term></item>
	///						<item><term>5</term><term>Trigger Input - Perform a Stop Immediate action</term></item>
	///						<item><term>10</term><term>Trigger Output - General purpose output (<see cref="BMC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
	///						<item><term>11</term><term>Trigger Output - Set when device moving</term></item>
	///						<item><term>12</term><term>Trigger Output - Set when at max velocity</term></item>
	///						<item><term>13</term><term>Trigger Output - Set when at predefine position steps</term></item>
	///						<item><term>14</term><term>Trigger Output - TBD mode</term></item>
	///		 		  </list></param>
	/// <param name="trigger2Polarity"> The trigger 2 polarity.<list type=table>
	///						<item><term>1</term><term>Output high when set</term></item>
	///						<item><term>2</term><term>Output low when set</term></item>
	///		 		  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetTriggerConfigParamsBlock(char const * serialNo, short channel, KMOT_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="BDC_SetTriggerConfigParams(char const * serialNo, short channel, KMOT_TriggerPortMode trigger1Mode, KMOT_TriggerPortPolarity trigger1Polarity, KMOT_TriggerPortMode trigger2Mode, KMOT_TriggerPortPolarity trigger2Polarity)" />
	/// <seealso cref="BDC_SetTriggerConfigParamsBlock(char const * serialNo, short channel, KMOT_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="BDC_RequestTriggerConfigParams(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_GetTriggerConfigParams(char const * serialNo, short channel, KMOT_TriggerPortMode *trigger1Mode, KMOT_TriggerPortPolarity *trigger1Polarity, KMOT_TriggerPortMode *trigger2Mode, KMOT_TriggerPortPolarity *trigger2Polarity);

	/// <summary> Gets the trigger configuration parameters block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The channel. </param>
	/// <param name="triggerConfigParams"> Options for controlling the trigger configuration. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetTriggerConfigParams(char const * serialNo, short channel, KMOT_TriggerPortMode *trigger1Mode, KMOT_TriggerPortPolarity *trigger1Polarity, KMOT_TriggerPortMode *trigger2Mode, KMOT_TriggerPortPolarity *trigger2Polarity)" />
	/// <seealso cref="BDC_SetTriggerConfigParams(char const * serialNo, short channel, KMOT_TriggerPortMode trigger1Mode, KMOT_TriggerPortPolarity trigger1Polarity, KMOT_TriggerPortMode trigger2Mode, KMOT_TriggerPortPolarity trigger2Polarity)" />
	/// <seealso cref="BDC_SetTriggerConfigParamsBlock(char const * serialNo, short channel, KMOT_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="BDC_RequestTriggerConfigParams(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_GetTriggerConfigParamsBlock(char const * serialNo, short channel, KMOT_TriggerConfig *triggerConfigParams);

	/// <summary> Sets the trigger configuration parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The channel. </param>
	/// <param name="trigger1Mode">	    The trigger 1 mode.<list type=table>
	///						<item><term>0</term><term>Trigger disabled</term></item>
	///						<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="BMC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
	///						<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
	///						<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
	///						<item><term>4</term><term>Trigger Input - Perform a Home action</term></item>
	///						<item><term>5</term><term>Trigger Input - Perform a Stop Immediate action</term></item>
	///						<item><term>10</term><term>Trigger Output - General purpose output (<see cref="BMC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
	///						<item><term>11</term><term>Trigger Output - Set when device moving</term></item>
	///						<item><term>12</term><term>Trigger Output - Set when at max velocity</term></item>
	///						<item><term>13</term><term>Trigger Output - Set when at predefine position steps</term></item>
	///						<item><term>14</term><term>Trigger Output - TBD mode</term></item>
	///		 		  </list></param>
	/// <param name="trigger1Polarity"> The trigger 1 polarity.<list type=table>
	///						<item><term>1</term><term>Output high when set</term></item>
	///						<item><term>2</term><term>Output low when set</term></item>
	///		 		  </list> </param>
	/// <param name="trigger2Mode">	    The trigger 2 mode.<list type=table>
	///						<item><term>0</term><term>Trigger disabled</term></item>
	///						<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="BMC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
	///						<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
	///						<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
	///						<item><term>4</term><term>Trigger Input - Perform a Home action</term></item>
	///						<item><term>5</term><term>Trigger Input - Perform a Stop Immediate action</term></item>
	///						<item><term>10</term><term>Trigger Output - General purpose output (<see cref="BMC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
	///						<item><term>11</term><term>Trigger Output - Set when device moving</term></item>
	///						<item><term>12</term><term>Trigger Output - Set when at max velocity</term></item>
	///						<item><term>13</term><term>Trigger Output - Set when at predefine position steps</term></item>
	///						<item><term>14</term><term>Trigger Output - TBD mode</term></item>
	///		 		  </list></param>
	/// <param name="trigger2Polarity"> The trigger 2 polarity.<list type=table>
	///						<item><term>1</term><term>Output high when set</term></item>
	///						<item><term>2</term><term>Output low when set</term></item>
	///		 		  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetTriggerConfigParams(char const * serialNo, short channel, KMOT_TriggerPortMode *trigger1Mode, KMOT_TriggerPortPolarity *trigger1Polarity, KMOT_TriggerPortMode *trigger2Mode, KMOT_TriggerPortPolarity *trigger2Polarity)" />
	/// <seealso cref="BDC_GetTriggerConfigParamsBlock(char const * serialNo, short channel, KMOT_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="BDC_SetTriggerConfigParamsBlock(char const * serialNo, short channel, KMOT_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="BDC_RequestTriggerConfigParams(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_SetTriggerConfigParams(char const * serialNo, short channel, KMOT_TriggerPortMode trigger1Mode, KMOT_TriggerPortPolarity trigger1Polarity, KMOT_TriggerPortMode trigger2Mode, KMOT_TriggerPortPolarity trigger2Polarity);

	/// <summary> Sets the trigger configuration parameters block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The channel. </param>
	/// <param name="triggerConfigParams"> Options for controlling the trigger configuration. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetTriggerConfigParams(char const * serialNo, short channel, KMOT_TriggerPortMode *trigger1Mode, KMOT_TriggerPortPolarity *trigger1Polarity, KMOT_TriggerPortMode *trigger2Mode, KMOT_TriggerPortPolarity *trigger2Polarity)" />
	/// <seealso cref="BDC_GetTriggerConfigParamsBlock(char const * serialNo, short channel, KMOT_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="BDC_SetTriggerConfigParams(char const * serialNo, short channel, KMOT_TriggerPortMode trigger1Mode, KMOT_TriggerPortPolarity trigger1Polarity, KMOT_TriggerPortMode trigger2Mode, KMOT_TriggerPortPolarity trigger2Polarity)" />
	/// <seealso cref="BDC_RequestTriggerConfigParams(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_SetTriggerConfigParamsBlock(char const * serialNo, short channel, KMOT_TriggerConfig *triggerConfigParams);

	/// <summary>Requests the trigger parameters. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <param name="channel">	The channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetTriggerParams(char const * serialNo, short channel, __int32 *triggerStartPositionFwd, __int32 *triggerIntervalFwd, __int32 *triggerPulseCountFwd, __int32 *triggerStartPositionRev, __int32 *triggerIntervalRev, __int32 *triggerPulseCountRev, __int32 *triggerPulseWidth, __int32 *cycleCount)" />
	/// <seealso cref="BDC_GetTriggerParamsBlock(char const * serialNo, short channel, KMOT_TriggerParams *triggerParams)" />
	/// <seealso cref="BDC_SetTriggerParams(char const * serialNo, short channel, __int32 triggerStartPositionFwd, __int32 triggerIntervalFwd, __int32 triggerPulseCountFwd, __int32 triggerStartPositionRev, __int32 triggerIntervalRev, __int32 triggerPulseCountRev, __int32 triggerPulseWidth, __int32 cycleCount)" />
	/// <seealso cref="BDC_SetTriggerParamsBlock(char const * serialNo, short channel, KMOT_TriggerParams *triggerParams)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_RequestTriggerParams(char const * serialNo, short channel);

	/// <summary> Gets the trigger parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The channel. </param>
	/// <param name="triggerStartPositionFwd"> The trigger start position in \ref DeviceUnits_page. </param>
	/// <param name="triggerIntervalFwd">	    The trigger interval in \ref DeviceUnits_page. </param>
	/// <param name="triggerPulseCountFwd">    Number of trigger pulses. </param>
	/// <param name="triggerStartPositionRev"> The trigger start position in \ref DeviceUnits_page. </param>
	/// <param name="triggerIntervalRev">	    The trigger interval in \ref DeviceUnits_page. </param>
	/// <param name="triggerPulseCountRev">    Number of trigger pulses. </param>
	/// <param name="triggerPulseWidth">    Width of the trigger pulse in milliseconds, range 1 (1us) to 1000000 (1s). </param>
	/// <param name="cycleCount">   Number of cycles to perform triggering. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetTriggerParamsBlock(char const * serialNo, short channel, KMOT_TriggerParams *triggerParams)" />
	/// <seealso cref="BDC_SetTriggerParams(char const * serialNo, short channel, __int32 triggerStartPositionFwd, __int32 triggerIntervalFwd, __int32 triggerPulseCountFwd, __int32 triggerStartPositionRev, __int32 triggerIntervalRev, __int32 triggerPulseCountRev, __int32 triggerPulseWidth, __int32 cycleCount)" />
	/// <seealso cref="BDC_SetTriggerParamsBlock(char const * serialNo, short channel, KMOT_TriggerParams *triggerParams)" />
	/// <seealso cref="BDC_RequestTriggerParams(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_GetTriggerParams(char const * serialNo, short channel, __int32 *triggerStartPositionFwd, __int32 *triggerIntervalFwd, __int32 *triggerPulseCountFwd, __int32 *triggerStartPositionRev, __int32 *triggerIntervalRev, __int32 *triggerPulseCountRev, __int32 *triggerPulseWidth, __int32 *cycleCount);

	/// <summary> Gets the trigger parameters block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The channel. </param>
	/// <param name="triggerParams"> Options for controlling the trigger parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetTriggerParams(char const * serialNo, short channel, __int32 *triggerStartPositionFwd, __int32 *triggerIntervalFwd, __int32 *triggerPulseCountFwd, __int32 *triggerStartPositionRev, __int32 *triggerIntervalRev, __int32 *triggerPulseCountRev, __int32 *triggerPulseWidth, __int32 *cycleCount)" />
	/// <seealso cref="BDC_SetTriggerParams(char const * serialNo, short channel, __int32 triggerStartPositionFwd, __int32 triggerIntervalFwd, __int32 triggerPulseCountFwd, __int32 triggerStartPositionRev, __int32 triggerIntervalRev, __int32 triggerPulseCountRev, __int32 triggerPulseWidth, __int32 cycleCount)" />
	/// <seealso cref="BDC_SetTriggerParamsBlock(char const * serialNo, short channel, KMOT_TriggerParams *triggerParams)" />
	/// <seealso cref="BDC_RequestTriggerParams(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_GetTriggerParamsBlock(char const * serialNo, short channel, KMOT_TriggerParams *triggerParams);

	/// <summary> Sets the trigger parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The channel. </param>
	/// <param name="triggerStartPositionFwd"> The trigger start position in \ref DeviceUnits_page. </param>
	/// <param name="triggerIntervalFwd">	    The trigger interval in \ref DeviceUnits_page. </param>
	/// <param name="triggerPulseCountFwd">    Number of trigger pulses. </param>
	/// <param name="triggerStartPositionRev"> The trigger start position in \ref DeviceUnits_page. </param>
	/// <param name="triggerIntervalRev">	    The trigger interval in \ref DeviceUnits_page. </param>
	/// <param name="triggerPulseCountRev">    Number of trigger pulses. </param>
	/// <param name="triggerPulseWidth">    Width of the trigger pulse in milliseconds, range 1 (1us) to 1000000 (1s). </param>
	/// <param name="cycleCount">   Number of cycles to perform triggering. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetTriggerParams(char const * serialNo, short channel, __int32 *triggerStartPositionFwd, __int32 *triggerIntervalFwd, __int32 *triggerPulseCountFwd, __int32 *triggerStartPositionRev, __int32 *triggerIntervalRev, __int32 *triggerPulseCountRev, __int32 *triggerPulseWidth, __int32 *cycleCount)" />
	/// <seealso cref="BDC_GetTriggerParamsBlock(char const * serialNo, short channel, KMOT_TriggerParams *triggerParams)" />
	/// <seealso cref="BDC_SetTriggerParamsBlock(char const * serialNo, short channel, KMOT_TriggerParams *triggerParams)" />
	/// <seealso cref="BDC_RequestTriggerParams(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_SetTriggerParams(char const * serialNo, short channel, __int32 triggerStartPositionFwd, __int32 triggerIntervalFwd, __int32 triggerPulseCountFwd, __int32 triggerStartPositionRev, __int32 triggerIntervalRev, __int32 triggerPulseCountRev, __int32 triggerPulseWidth, __int32 cycleCount);

	/// <summary> Sets the trigger parameters block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">	The channel. </param>
	/// <param name="triggerParams"> Options for controlling the trigger parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BDC_GetTriggerParams(char const * serialNo, short channel, __int32 *triggerStartPositionFwd, __int32 *triggerIntervalFwd, __int32 *triggerPulseCountFwd, __int32 *triggerStartPositionRev, __int32 *triggerIntervalRev, __int32 *triggerPulseCountRev, __int32 *triggerPulseWidth, __int32 *cycleCount)" />
	/// <seealso cref="BDC_GetTriggerParamsBlock(char const * serialNo, short channel, KMOT_TriggerParams *triggerParams)" />
	/// <seealso cref="BDC_SetTriggerParams(char const * serialNo, short channel, __int32 triggerStartPositionFwd, __int32 triggerIntervalFwd, __int32 triggerPulseCountFwd, __int32 triggerStartPositionRev, __int32 triggerIntervalRev, __int32 triggerPulseCountRev, __int32 triggerPulseWidth, __int32 cycleCount)" />
	/// <seealso cref="BDC_RequestTriggerParams(char const * serialNo, short channel)" />
	BENCHTOPDCSERVO_API short __cdecl BDC_SetTriggerParamsBlock(char const * serialNo, short channel, KMOT_TriggerParams *triggerParams);

}
/** @} */ // BenchtopDCServo
