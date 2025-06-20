// summary:	Declares the functions class
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the BRUSHLESSMOTOR_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// BRUSHLESSMOTOR_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#pragma once

#ifdef BRUSHLESSMOTORDLL_EXPORTS
#define BRUSHLESSMOTOR_API __declspec(dllexport)
#else
#define BRUSHLESSMOTOR_API __declspec(dllimport)
#endif

#include <OaIdl.h>

/** @defgroup KCubeBrushlessMotor KCube Brushless Motor
 *  This section details the Structures and Functions relavent to the  @ref KBD101_page "KCube Brushless Motor"<br />
 *  For an example of how to connect to the device and perform simple operations use the following links:
 *  <list type=bullet>
 *    <item> \ref namespaces_kbd_ex_1 "Example of using the Thorlabs.MotionControl.KCube.BrushlessMotor.DLL from a C or C++ project."<br />
 *									  This requires the DLL to be dynamical linked. </item>
 *    <item> \ref namespaces_kbd_ex_2 "Example of using the Thorlabs.MotionControl.KCube.BrushlessMotor.DLL from a C# project"<br />
 *									  This uses Marshalling to load and access the C DLL. </item>
 *  </list>
 *  The Thorlabs.MotionControl.KCube.BrushlessMotor.DLL requires the following DLLs
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
		FT_OK = 0x00, ///<OK - no error.
		FT_InvalidHandle = 0x01, ///<Invalid handle.
		FT_DeviceNotFound = 0x02, ///<Device not found.
		FT_DeviceNotOpened = 0x03, ///<Device not opened.
		FT_IOError = 0x04, ///<I/O error.
		FT_InsufficientResources = 0x05, ///<Insufficient resources.
		FT_InvalidParameter = 0x06, ///<Invalid parameter.
		FT_DeviceNotPresent = 0x07, ///<Device not present.
		FT_IncorrectDevice = 0x08 ///<Incorrect device.
	 } FT_Status;

	/// <summary> Values that represent different Motor Types. </summary>
	typedef enum MOT_MotorTypes
	{
		MOT_NotMotor = 0, ///<Not a motor
		MOT_DCMotor = 1, ///< Motor is a DC Servo motor
		MOT_StepperMotor = 2, ///< Motor is a Stepper Motor
		MOT_BrushlessMotor = 3, ///< Motor is a Brushless Motor
		MOT_CustomMotor = 100, ///< Motor is a custom motor
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
		MOT_TravelDirectionUndefined = 0x00,///<Undefined
		MOT_Forwards = 0x01,///<Move in a Forward direction
		MOT_Reverse = 0x02,///<Move in a Backward / Reverse direction
	} MOT_TravelDirection;

	/// <summary> Values that represent Direction Type. </summary>
	typedef enum MOT_DirectionSense : short
	{
		MOT_Normal = 0x00,///<Move / Jog direction is normal (clockwise).
		MOT_Backwards = 0x01,///<Move / Jog direction is reversed (anti clockwise).
	} MOT_DirectionSense;

	/// <summary> Values that represent Limit Switch Directions. </summary>
	typedef enum MOT_HomeLimitSwitchDirection : short
	{
		MOT_LimitSwitchDirectionUndefined,///<Undefined
		MOT_ReverseLimitSwitch = 0x01,///<Limit switch in forward direction
		MOT_ForwardLimitSwitch = 0x04,///<Limit switch in reverse direction
	} MOT_HomeLimitSwitchDirection;

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

	/// <summary> Values that represent Velocity profile Modes. </summary>
	typedef enum MOT_VelocityProfileModes : WORD
	{
		MOT_Trapezoidal = 0x00,///<Trapezoidal Profile
		MOT_SCurve = 0x02,///<S-Curve profile
	} MOT_VelocityProfileModes;

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

	/// <summary> Values that represent MOT_CurrentLoopPhases. </summary>
	typedef enum MOT_CurrentLoopPhases : WORD
	{
		MOT_PhaseA = 0x0,///< Phase A
		MOT_PhaseB = 0x1,///< Phase B
		MOT_PhaseAB = 0x2,///< Phase A and B
	} MOT_CurrentLoopPhases;

	/// <summary> Values that represent Wheel Direction Sense. </summary>
	typedef enum KMOT_WheelDirectionSense : __int16
	{
		KMOT_WM_Positive = 0x01,///< Move at constant velocity
		KMOT_WM_Negative = 0x02,///< Phase B
	} KMOT_WheelDirectionSense;

	/// <summary> Values that represent the Wheel Mode. </summary>
	typedef enum KMOT_WheelMode : __int16
	{
		KMOT_WM_Velocity = 0x01,///< Move at constant velocity
		KMOT_WM_Jog = 0x02,///< Phase B
		KMOT_WM_MoveAbsolute = 0x03,///< Phase A and B
	} KMOT_WheelMode;

	/// <summary> Values that represent Trigger Port Mode. </summary>
	typedef enum KMOT_TriggerPortMode : __int16
	{
		KMOT_TrigDisabled = 0x00,///< Trigger Disabled
		KMOT_TrigIn_GPI = 0x01,///< General purpose logic input (<see cref="BMC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)
		KMOT_TrigIn_RelativeMove = 0x02,///< Move relative using relative move parameters
		KMOT_TrigIn_AbsoluteMove = 0x03,///< Move absolute using absolute move parameters
		KMOT_TrigIn_Home = 0x04,///< Perform a Home action
		KMOT_TrigIn_Stop = 0x05,///< Perform a Stop Immediate action
		KMOT_TrigIn_StartScan = 0x06,///< Perform a Scan Start (on supported devices)
		KMOT_TrigIn_ShuttleMove = 0x07,///< Move shuttle using absolute move parameters (on supported devices)
		KMOT_TrigOut_GPO = 0x0A,///< General purpose output (<see cref="BMC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)
		KMOT_TrigOut_InMotion = 0x0B,///< Set when device moving
		KMOT_TrigOut_AtMaxVelocity = 0x0C,///< Set when at max velocity
		KMOT_TrigOut_AtPositionSteps = 0x0D,///< Set when at predefine position steps,<br />Set using wTrigStartPos, wTrigInterval, wTrigNumPulses,wTrigPulseWidth
		KMOT_TrigOut_Synch = 0x0E,///< TBD ?
	} KMOT_TriggerPortMode;

	/// <summary> Values that represent Trigger Port Polarity. </summary>
	typedef enum KMOT_TriggerPortPolarity : __int16
	{
		KMOT_TrigPolarityHigh = 0x01,///< Trigger Polarity high
		KMOT_TrigPolarityLow = 0x02,///< Trigger Polarity Low
	} KMOT_TriggerPortPolarity;

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

	/// <summary> Values that represent scan movement pattern options. </summary>
	typedef enum MOT_ScanMovePattern : unsigned short
	{
		MOT_ScanMovePattern_NotSpecified = 0x00,
		MOT_ScanMovePattern_Sine = 0x01,
		MOT_ScanMovePattern_Triangle = 0x02
	};

	/// <summary> Values that represent scan movement trigger options. </summary>
	typedef enum MOT_ScanMoveTrigger : unsigned short
	{
		MOT_ScanMoveTrigger_NotSpecified = 0x00,
		MOT_ScanMoveTrigger_Software = 0x01, ///< Software trigger, scan move starts immediately on recept of scan start
		MOT_ScanMoveTrigger_Hardware = 0x02 ///< Hardware trigger, scan move starts when trigger condition met
	};

	/// <summary> Values that represent scan movement commands options. </summary>
	typedef enum MOT_ScanMoveCommands : short
	{
		MOT_SCAN_MOVE_START = 0x01, ///< Start scan move
		MOT_SCAN_MOVE_PAUSE = 0x02, ///< Pause scan move
		MOT_SCAN_MOVE_STOP = 0x03, ///< Stop scan move
	};

	/// <summary> Values that represent analogue input modes. </summary>
	typedef enum MOT_AnalogInputMode : unsigned short
	{
		MOT_ANALOG_IP_DISABLED = 0x00,
		MOT_ANALOG_IP_POSCONTROL = 0x01 ///< Position control mode
	};

	/// <summary> Values that represent monitor output modes. </summary>
	typedef enum MOT_MonitorOutputMode : unsigned short
	{
		MOT_MON_OP_SOFTWARE = 0x00,
		MOT_MON_OP_POSITION = 0x01 ///< Position control mode
	};

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

	/// <summary> Structure containing velocity profile parameters for advanced motor control. </summary>
	typedef struct MOT_VelocityProfileParameters
	{
		/// <summary> The Velocity Profile Mode. </summary>
		/// <remarks> The Velocity Profile mode can be onw of the following:
		/// 		 <list type=table>
		///				<item><term>0</term><term>Trapezoidal Profile</term></item>
		///				<item><term>2</term><term>S-curve.</term></item>
		/// 		  </list></remarks>
		MOT_VelocityProfileModes mode;
		/// <summary> Maximum rate of change of acceleration. </summary>
		DWORD jerk;
		/// <summary> Not used. </summary>
		WORD notUsed;
		/// <summary> Not used. </summary>
		WORD lastNotUsed;
	} MOT_VelocityProfileParameters;

	/// <summary> Structure containing stage axis parameters. </summary>
	typedef struct MOT_StageAxisParameters
	{
		/// <summary> Two digit identifier of stage type. </summary>
		WORD stageID;
		/// <summary>Defines the axis to which this is applied. </summary>
		/// <remarks> The axis of operation
		/// 		 <list type=table>
		///				<item><term>0</term><term>X Axis</term></item>
		///				<item><term>1</term><term>Y Axis.</term></item>
		///				<item><term>2</term><term>Z Axis.</term></item>
		/// 		  </list></remarks>
		WORD axisID;
		/// <summary> The Catalogue part number. </summary>
		char partNumber[16];
		/// <summary> Eight digit stage serial number. </summary>
		DWORD serialNumber;
		/// <summary> The number of Encoder counts per mm or degree. </summary>
		DWORD countsPerUnit;
		/// <summary> Minimum position in encoder counts usually 0. </summary>
		int minPosition;
		/// <summary> Maximum position in encoder counts. </summary>
		int maxPosition;
		/// <summary> Maximum acceleration in encoder counts per cycle per cycle. </summary>
		int maxAcceleration;
		/// <summary> Maximum decceleration in encoder counts per cycle per cycle. </summary>
		int maxDecceleration;
		/// <summary> Maximum speed in encoder counts per cycle. </summary>
		int maxVelocity;
		/// <summary> Reserved for future use. </summary>
		WORD reserved1;
		/// <summary> Reserved for future use. </summary>
		WORD reserved2;
		/// <summary> Reserved for future use. </summary>
		WORD reserved3;
		/// <summary> Reserved for future use. </summary>
		WORD reserved4;
		/// <summary> Reserved for future use. </summary>
		DWORD reserved5;
		/// <summary> Reserved for future use. </summary>
		DWORD reserved6;
		/// <summary> Reserved for future use. </summary>
		DWORD reserved7;
		/// <summary> Reserved for future use. </summary>
		DWORD reserved8;
	} MOT_StageAxisParameters;

	/// <summary> Structure containing the PID Parameters with extension for brushless DC motors used
	/// in an algorithm involving calculus to control position. </summary>
	typedef struct MOT_BrushlessPositionLoopParameters
	{
		/// <summary> The PID Proportional Gain, range 0 to 0x7FFF. </summary>
		WORD proportionalGain;
		/// <summary> The PID Integral Gain, range 0 to 0x7FFF. </summary>
		WORD integralGain;
		/// <summary> The PID Integral Limit, range 0 to 0x7FFFFFFF. </summary>
		DWORD integralLimit;
		/// <summary> The PID Derivative Gain, range 0 to 0x7FFF. </summary>
		/// <remarks> Kept as differentialGain rather than derivativeGain for backward compatibility</remarks>
		WORD differentialGain;
		/// <summary> The PID Derivative Recalculation Time, range 0 to 0x7FFF. </summary>
		WORD derivativeRecalculationTime;
		/// <summary> The PID Factor for Output, range 0 to 0xFFFF where 0xFFFF is 100 %. </summary>
		WORD factorForOutput;
		/// <summary> The PID Velocity Feed Forward factor, range 0 to 0x7FFF. </summary>
		WORD velocityFeedForward;
		/// <summary> The PID Acceleration Feed Forward factor, range 0 to 0x7FFF. </summary>
		WORD accelerationFeedForward;
		/// <summary> The PID Position Error Limit, range 0 to 0x7FFFFFFF. </summary>
		DWORD positionErrorLimit;
		/// <summary> Not used. </summary>
		WORD notUsed;
		/// <summary> Not used. </summary>
		WORD lastNotUsed;
	} MOT_BrushlessPositionLoopParameters;

	/// <summary> Structure containing parameters used to decide when brushless DC motor is settled at the right position. </summary>
	typedef struct MOT_BrushlessTrackSettleParameters
	{
		/// <summary> Time in cycles of 102.4 microsec given for stage to settle, range 1 to 0x7FFF. </summary>
		WORD time;
		/// <summary> Low position error in encoder units when stage is considered settled, range 0 to 0xFFFF. </summary>
		WORD settledError;
		/// <summary> Maximum tolerated position error in encoder units whilst stage settling, range 0 to 0xFFFF. </summary>
		WORD maxTrackingError;
		/// <summary> Not used. </summary>
		WORD notUsed;
		/// <summary> Not used. </summary>
		WORD lastNotUsed;
	} MOT_BrushlessTrackSettleParameters;

	/// <summary> Structure containing the PI Parameters with extension for brushless DC motors used in an algorithm involving calculus to control current. </summary>
	typedef struct MOT_BrushlessCurrentLoopParameters
	{
		/// <summary> The Current Loop Phase. </summary>
		/// <remarks> The current loop phases to be used
		/// 		 <list type=table>
		///				<item><term>0</term><term>Phase A</term></item>
		///				<item><term>1</term><term>Phase B</term></item>
		///				<item><term>2</term><term>Phases A and B.</term></item>
		/// 		  </list></remarks>
		MOT_CurrentLoopPhases phase;
		/// <summary> The PI Proportional Gain, range 0 to 0x7FFF. </summary>
		WORD proportionalGain;
		/// <summary> The PI Integral Gain, range 0 to 0x7FFF. </summary>
		WORD integralGain;
		/// <summary> The PI Integral Limit, range 0 to 0x7FFF. </summary>
		WORD integralLimit;
		/// <summary> The PI Dead error band, range 0 to 0x7FFF. </summary>
		WORD deadErrorBand;
		/// <summary> The PI Feed forward, range 0 to 0x7FFF. </summary>
		WORD feedForward;
		/// <summary> Not used. </summary>
		WORD notUsed;
		/// <summary> Not used. </summary>
		WORD lastNotUsed;
	} MOT_BrushlessCurrentLoopParameters;

	/// <summary> Structure containing parameters to control electrical output to brushless DC motors. </summary>
	typedef struct MOT_BrushlessElectricOutputParameters
	{
		/// <summary> The Continuous current limit, range 0 to 0x7FFF (0 to 100%). </summary>
		WORD continuousCurrentLimit;
		/// <summary> The Excess energy limit, range 0 to 0x7FFF (0 to 100%). </summary>
		WORD excessEnergyLimit;
		/// <summary> The Motor signal limit, range 0 to 0x7FFF (0 to 100%). </summary>
		short motorSignalLimit;
		/// <summary> The Motor signal bias, range -0x7FFF to 0x7FFF. </summary>
		short motorSignalBias;
		/// <summary> Not used. </summary>
		WORD notUsed;
		/// <summary> Not used. </summary>
		WORD lastNotUsed;
	} MOT_BrushlessElectricOutputParameters;

	/// <summary> Structure containing the MMI Parameters. </summary>
	/// <value> Device GUI parameters. </value>
	typedef struct KMOT_MMIParams
	{
		/// <summary> The wheel mode. </summary>
		/// <remarks> The wheel mode is one of the following:
		/// 		  <list type=table>
		///				<item><term>1</term><term>Constant Velocity<br />The device will continue moving until the end stop is reached or the duration of the wheel action</term></item>
		///				<item><term>2</term><term>Jog<br />The device will jog forward or backward according to the wheel action.<br />
		///					  The device will jog according to the Jog parameters</term></item>
		///				<item><term>3</term><term>Move Absolute<br />The device will move to either Preset Po 1 or 2 according to the wheel action.</term></item>
		/// 		  </list>
		/// 		  </remarks>
		KMOT_WheelMode WheelMode;
		/// <summary> The wheel maximum velocity. </summary>
		__int32 WheelMaxVelocity; 
		/// <summary> The wheel acceleration. </summary>
		__int32 WheelAcceleration; 
		/// <summary> The wheel direction sense. </summary>
		MOT_DirectionSense WheelDirectionSense;
		/// <summary> The first preset position in encoder counts. </summary>
		__int32 PresetPos1; 
		/// <summary> The second preset position in encoder counts. </summary>
		__int32 PresetPos2; 
		/// <summary> The display intensity, range 0 to 100%. </summary>
		__int16 DisplayIntensity;
		/// <summary> The display timeout in miniutes. </summary>
		__int16 DisplayTimeout;
		/// <summary> The display dim intensity, range 0 to (Display Timeout). </summary>
		__int16 DisplayDimIntensity;
		/// <summary> Reserved fields. </summary>
		__int16 reserved[4];
	} KMOT_MMIParams;

	/// <summary> KCube motor trigger configuration. </summary>
	typedef struct KMOT_TriggerConfig
	{
		/// <summary> The trigger 1 mode. </summary>
		/// <remarks> The trigger 1 operating mode:
		/// 		  <list type=table>
		///				<item><term>0</term><term>Trigger disabled</term></item>
		///				<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="BMC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
		///				<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
		///				<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
		///				<item><term>4</term><term>Trigger Input - Perform a Home action</term></item>
		///				<item><term>5</term><term>Trigger Input - Perform a Stop Immediate action</term></item>
		/// 			<item><term>6</term><term>Trigger Input - Perform a Start scan move</term></item>
		/// 			<item><term>7</term><term>Trigger Input - Move shuttle using absolute move parameters</term></item>
		///				<item><term>10</term><term>Trigger Output - General purpose output (<see cref="BMC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
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
		///				<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="BMC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
		///				<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
		///				<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
		///				<item><term>4</term><term>Trigger Input - Perform a Home action</term></item>
		///				<item><term>5</term><term>Trigger Input - Perform a Stop Immediate action</term></item>
		/// 			<item><term>6</term><term>Trigger Input - Perform a Start scan move</term></item>
		/// 			<item><term>7</term><term>Trigger Input - Move shuttle using absolute move parameters</term></item>
		///				<item><term>10</term><term>Trigger Output - General purpose output (<see cref="BMC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
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
		/// <summary> reserved fields. </summary>
		__int16 reserved[6];
	} KMOT_TriggerConfig;

	/// <summary> KCube motor trigger output configuration. </summary>
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
		/// <summary> reserved fields. </summary>
		__int32 reserved[6];
	} KMOT_TriggerParams;

	/// <summary> KCube scan move configuration. </summary>
	typedef struct MOT_ScanMoveParams
	{
		/// <summary> The start position in device units. </summary>
		long StartPosition;
		/// <summary> The distance to move from start position in device units. </summary>
		long Amplitude;
		/// <summary> The frequency (angular velocity) in machine units. </summary>
		long Frequency;
		/// <summary> The angular acceleration in machine units. </summary>
		long AngularAcceleration;
		/// <summary> The number of Cycles. A value of 0 results in continuous movement. </summary>
		long NumberOfCycles;
		/// <summary> The scan pattern. Sinusoidal or triangular.</summary>
		MOT_ScanMovePattern ScanPattern;
		/// <summary> The trigger mode. Software or hardware.</summary>
		MOT_ScanMoveTrigger TriggerMode;

	} MOT_ScanMoveParams;

	/// <summary> KCube analog IO configuration. </summary>
	typedef struct MOT_AnalogIOConfigParams
	{
		/// <summary> External analogue input mode.</summary>
		MOT_AnalogInputMode ExternalInputMode;
		/// <summary> External input voltage corresponding to the minimum position (±32767 corresponding to ±10V).</summary> 
		short ExternalInputMinPositionVoltage;
		/// <summary> External input voltage corresponding to the maximum position (±32767 corresponding to ±10V).</summary>
		short ExternalInputMaxPositionVoltage;
		/// <summary> Minimum position for the external input, in encoder counts.</summary>
		LONG ExternalInputMinPosition;
		/// <summary> Maximum position for the external input, in encoder counts.</summary>
		LONG ExternalInputMaxPosition;
		/// <summary> External input filter frequency in Hz, or zero to turn filter off.</summary>
		WORD ExternalInputFilterFrequency;
		/// <summary> Monitor output SMA signal function (see #defines below)..</summary>
		MOT_MonitorOutputMode MonitorOutputMode;
		/// <summary> Monitor output software defined value (±32767 corresponding to ±10V).</summary>
		WORD MonitorOutputSoftwareValue;
		/// <summary> Monitor output voltage corresponding to the minimum position (±32767 corresponding to ±10V).</summary>
		short MonitorOutputMinPositionVoltage;
		/// <summary> Monitor output voltage corresponding to the maximum position (±32767 corresponding to ±10V).</summary>
		short MonitorOutputMaxPositionVoltage;
		/// <summary> Minimum position for monitor output, in encoder counts.</summary>
		LONG MonitorOutputMinPosition;
		/// <summary> Maximum position for monitor output, in encoder counts.</summary>
		LONG MonitorOutputMaxPosition;
		/// <summary> Reserved for future use.</summary>
		WORD Reserved[4];
	} MOT_AnalogIOConfigParams;

	/// <summary> KCube analog input configuration. </summary>
	typedef struct MOT_AnalogInputParams
	{
		/// <summary> External analogue input mode.</summary>
		MOT_AnalogInputMode ExternalInputMode;
		/// <summary> External input voltage corresponding to the minimum position (±32767 corresponding to ±10V).</summary> 
		short ExternalInputReading;
		/// <summary> Reserved for future use.</summary>
		short wReserved[4];
	} MOT_AnalogInputParams;

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
	BRUSHLESSMOTOR_API short __cdecl TLI_BuildDeviceList(void);

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
	BRUSHLESSMOTOR_API short __cdecl TLI_GetDeviceListSize();

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
	BRUSHLESSMOTOR_API short __cdecl TLI_GetDeviceList(SAFEARRAY** stringsReceiver);

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
	BRUSHLESSMOTOR_API short __cdecl TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID);

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
	BRUSHLESSMOTOR_API short __cdecl TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length);

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
	BRUSHLESSMOTOR_API short __cdecl TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer);

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
	BRUSHLESSMOTOR_API short __cdecl TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID);

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
	BRUSHLESSMOTOR_API short __cdecl TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length);

	/// <summary> Get the device information from the USB port. </summary>
	/// <remarks> The Device Info is read from the USB port not from the device itself.<remarks>
	/// <param name="serialNo"> The serial number of the device. </param>
	/// <param name="info">    The <see cref="TLI_DeviceInfo"/> device information. </param>
	/// <returns>	1 if successful, 0 if not. </returns>
    /// 		  \include CodeSnippet_identification.cpp
	/// <seealso cref="TLI_GetDeviceListSize()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	/// <seealso cref="TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID)" />
	/// <seealso cref="TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length)" />
	/// <seealso cref="TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer)" />
	/// <seealso cref="TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID)" />
	/// <seealso cref="TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length)" />
	BRUSHLESSMOTOR_API short __cdecl TLI_GetDeviceInfo(char const * serialNo, TLI_DeviceInfo *info);

	/// <summary> Initialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <remarks> Call TLI_InitializeSimulations before TLI_BuildDeviceList at the start of the program to make a connection to the simulation manager.<Br />
	/// 		  Any devices configured in the simulation manager will become visible TLI_BuildDeviceList is called and can be accessed using TLI_GetDeviceList.<Br />
	/// 		  Call TLI_InitializeSimulations at the end of the program to release the simulator.  </remarks>
	/// <seealso cref="TLI_UninitializeSimulations()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	BRUSHLESSMOTOR_API void __cdecl TLI_InitializeSimulations();

	/// <summary> Uninitialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <seealso cref="TLI_InitializeSimulations()" />
	BRUSHLESSMOTOR_API void __cdecl TLI_UninitializeSimulations();

	/// <summary> Open the device for communications. </summary>
	/// <param name="serialNo">	The serial no of the device to be connected. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="BMC_Close(char const * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_Open(char const * serialNo);

	/// <summary> Disconnect and close the device. </summary>
	/// <param name="serialNo">	The serial no of the device to be disconnected. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="BMC_Open(char const * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_Close(char const * serialNo);

	/// <summary>	Check connection. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> true if the USB is listed by the ftdi controller</returns>
	/// \include CodeSnippet_CheckConnection.cpp
	BRUSHLESSMOTOR_API bool __cdecl BMC_CheckConnection(char const * serialNo);

	/// <summary> Sends a command to the device to make it identify iteself. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	BRUSHLESSMOTOR_API void __cdecl BMC_Identify(char const * serialNo);

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
	BRUSHLESSMOTOR_API short __cdecl BMC_GetHardwareInfo(char const * serialNo, char * modelNo, DWORD sizeOfModelNo, WORD * type, short * numChannels, char * notes, DWORD sizeOfNotes, DWORD * firmwareVersion, WORD * hardwareVersion, WORD * modificationState);

	/// <summary> Gets the hardware information in a block. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="hardwareInfo"> Address of a TLI_HardwareInformation structure to receive the hardware information. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// 		  \include CodeSnippet_identify.cpp
	BRUSHLESSMOTOR_API short __cdecl BMC_GetHardwareInfoBlock(char const * serialNo, TLI_HardwareInformation *hardwareInfo);

	/// <summary> Gets version number of the device firmware. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device firmware version number made up of 4 byte parts. </returns>
	/// 		  \include CodeSnippet_identify.cpp
	BRUSHLESSMOTOR_API DWORD __cdecl BMC_GetFirmwareVersion(char const * serialNo);

	/// <summary> Gets version number of the device software. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device software version number made up of 4 byte parts. </returns>
	/// 		  \include CodeSnippet_identify.cpp
	BRUSHLESSMOTOR_API DWORD __cdecl BMC_GetSoftwareVersion(char const * serialNo);

	/// <summary> Update device with stored settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// 		  \include CodeSnippet_connection1.cpp
	BRUSHLESSMOTOR_API bool __cdecl BMC_LoadSettings(char const * serialNo);

	/// <summary> Update device with named settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="settingsName"> Name of settings stored away from device. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	///             \include CodeSnippet_connection1.cpp
	BRUSHLESSMOTOR_API bool __cdecl BMC_LoadNamedSettings(char const * serialNo, char const *settingsName);

	/// <summary> persist the devices current settings. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	BRUSHLESSMOTOR_API bool __cdecl BMC_PersistSettings(char const * serialNo);

	/// <summary> Reset the stage settings to defaults. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	BRUSHLESSMOTOR_API short __cdecl BMC_ResetStageToDefaults(char const * serialNo);

	/// <summary> Disable the channel so that motor can be moved by hand. </summary>
	/// <remarks> When disabled power is removed from the motor and it can be freely moved.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_EnableChannel(char const * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_DisableChannel(char const * serialNo);

	/// <summary> Enable channel for computer control. </summary>
	/// <remarks> When enabled power is applied to the motor so it is fixed in position.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_DisableChannel(char const * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_EnableChannel(char const * serialNo);

	/// <summary> Determine if the device front panel can be locked. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> True if we can lock the device front panel, false if not. </returns>
	/// <seealso cref="BMC_GetFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="BMC_RequestFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="BMC_SetFrontPanelLock(char const * serialNo, bool locked)" />
	BRUSHLESSMOTOR_API bool __cdecl BMC_CanDeviceLockFrontPanel(char const * serialNo);

	/// <summary> Query if the device front panel locked. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> True if the device front panel is locked, false if not. </returns>
	/// <seealso cref="BMC_CanDeviceLockFrontPanel(char const * serialNo)" />
	/// <seealso cref="BMC_RequestFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="BMC_SetFrontPanelLock(char const * serialNo, bool locked)" />
	BRUSHLESSMOTOR_API bool __cdecl  BMC_GetFrontPanelLocked(char const * serialNo);

	/// <summary> Ask the device if its front panel is locked. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_CanDeviceLockFrontPanel(char const * serialNo)" />
	/// <seealso cref="BMC_GetFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="BMC_SetFrontPanelLock(char const * serialNo, bool locked)" />
	BRUSHLESSMOTOR_API short __cdecl  BMC_RequestFrontPanelLocked(char const * serialNo);

	/// <summary> Sets the device front panel lock state. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="locked"> True to lock the device, false to unlock. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_CanDeviceLockFrontPanel(char const * serialNo)" />
	/// <seealso cref="BMC_GetFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="BMC_RequestFrontPanelLocked(char const * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl  BMC_SetFrontPanelLock(char const * serialNo, bool locked);

	/// <summary> Get number of positions. </summary>
	/// <remarks> The GetNumberPositions function will get the maximum position reachable by the device.<br />
	/// 		  The motor may need to be \ref C_MOTOR_sec10 "Homed" before this parameter can be used. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The number of positions. </returns>
	/// <seealso cref="BMC_MoveToPosition(char const * serialNo, int index)" />
	/// <seealso cref="BMC_GetPosition(char const * serialNo)" />
	/// <seealso cref="BMC_Home(char const * serialNo)" />
	/// 		  \include CodeSnippet_move.cpp
	BRUSHLESSMOTOR_API int __cdecl BMC_GetNumberPositions(char const * serialNo);

	/// <summary> Move the device to the specified position (index). </summary>
	/// <remarks> The motor may need to be \ref C_MOTOR_sec10 "Homed" before a position can be set<br />
	/// 		  see \ref C_MOTOR_sec11 "Positioning" for more detail. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="index">   	The position in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if move successfully started. </returns>
	/// <seealso cref="BMC_GetNumberPositions(char const * serialNo)" />
	/// <seealso cref="BMC_SetVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="BMC_GetPosition(char const * serialNo)" />
	/// <seealso cref="BMC_GetVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BMC_GetVelParamsBlock(char const * serialNo, MOT_VelocityParameters  *velocityParams)" />
	/// <seealso cref="BMC_SetVelParamsBlock(char const * serialNo, MOT_VelocityParameters *velocityParams)" />
	/// <seealso cref="BMC_MoveRelative(char const * serialNo, int displacement)" />
	/// <seealso cref="BMC_MoveAtVelocity(char const * serialNo, MOT_TravelDirection direction)" />
	/// 		  \include CodeSnippet_move.cpp
	BRUSHLESSMOTOR_API short __cdecl BMC_MoveToPosition(char const * serialNo, int index);

	/// <summary> Get the current position. </summary>
	/// <remarks> The current position is the last recorded position.<br />
	/// 		  The current position is updated either by the polling mechanism or<br />
	/// 		  by calling <see cref="RequestPosition" /> or <see cref="RequestStatus" />.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The current position in \ref DeviceUnits_page. </returns>
	/// <seealso cref="BMC_GetNumberPositions(char const * serialNo)" />
	/// <seealso cref="BMC_MoveToPosition(char const * serialNo, int index)" />
	/// <seealso cref="BMC_Home(char const * serialNo)" />
	/// 		  \include CodeSnippet_move.cpp
	BRUSHLESSMOTOR_API int __cdecl BMC_GetPosition(char const * serialNo);

	/// <summary> Can the device perform a Home. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> <c>true</c> if the device can home. </returns>
	BRUSHLESSMOTOR_API bool __cdecl BMC_CanHome(char const * serialNo);

	/// \deprecated
	/// <summary> Does the device need to be Homed before a move can be performed. </summary>
	/// <remarks> superceded by <see cref="BMC_CanMoveWithoutHomingFirst(char const * serialNo)"/> </remarks>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> <c>true</c> if the device needs homing. </returns>
	BRUSHLESSMOTOR_API bool __cdecl BMC_NeedsHoming(char const * serialNo);

	/// <summary> Can this device be moved without Homing. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> <c>true</c> if the device does not need to be homed before a move can be commanded. </returns>
	BRUSHLESSMOTOR_API bool __cdecl BMC_CanMoveWithoutHomingFirst(char const * serialNo);

	/// <summary> Home the device. </summary>
	/// <remarks> Homing the device will set the device to a known state and determine the home position,<br />
	/// 		  see \ref C_MOTOR_sec10 "Homing" for more detail. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if move successfully started. </returns>
	/// <seealso cref="BMC_GetNumberPositions(char const * serialNo)" />
	/// <seealso cref="BMC_MoveToPosition(char const * serialNo, int index)" />
	/// <seealso cref="BMC_GetPosition(char const * serialNo)" />
	/// 		  \include CodeSnippet_move.cpp
	BRUSHLESSMOTOR_API short __cdecl BMC_Home(char const * serialNo);

	/// <summary> Set to allow a device to be positioned without prior homing. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if move successfully started. </returns>
	BRUSHLESSMOTOR_API short BMC_OverrideHomeRequirement(char const * serialNo);

	/// <summary> Clears the device message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BRUSHLESSMOTOR_API short BMC_ClearMessageQueue(char const * serialNo);

	/// <summary> Registers a callback on the message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="functionPointer"> A function pointer to be called whenever messages are received. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="BMC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="BMC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_RegisterMessageCallback(char const * serialNo, void(*functionPointer)());

	/// <summary> Gets the MessageQueue size. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> number of messages in the queue. </returns>
	/// <seealso cref="BMC_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="BMC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="BMC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	BRUSHLESSMOTOR_API int __cdecl BMC_MessageQueueSize(char const * serialNo);

	/// <summary> Get the next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="BMC_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="BMC_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="BMC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	BRUSHLESSMOTOR_API bool __cdecl BMC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Wait for next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="BMC_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="BMC_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="BMC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	BRUSHLESSMOTOR_API bool __cdecl BMC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Requests the homing parameters. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetHomingVelocity(char const * serialNo)" />
	/// <seealso cref="BMC_GetHomingParamsBlock(char const * serialNo, MOT_HomingParameters *homingParams)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_RequestHomingParams(char const * serialNo);

	/// <summary> Gets the homing velocity. </summary>
	/// <remarks> see \ref C_MOTOR_sec10 "Homing" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The homing velocity in \ref DeviceUnits_page. </returns>
	/// <seealso cref="BMC_RequestHomingParams(char const * serialNo)" />
	/// <seealso cref="BMC_SetHomingVelocity(char const * serialNo, unsigned int velocity)" />
	/// <seealso cref="BMC_GetHomingParamsBlock(char const * serialNo, MOT_HomingParameters *homingParams)" />
	/// <seealso cref="BMC_SetHomingParamsBlock(char const * serialNo, MOT_HomingParameters *homingParams)" />
	BRUSHLESSMOTOR_API unsigned int __cdecl BMC_GetHomingVelocity(char const * serialNo);

	/// <summary> Sets the homing velocity. </summary>
	/// <remarks> see \ref C_MOTOR_sec10 "Homing" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="velocity"> The homing velocity in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestHomingParams(char const * serialNo)" />
	/// <seealso cref="BMC_GetHomingVelocity(char const * serialNo)" />
	/// <seealso cref="BMC_GetHomingParamsBlock(char const * serialNo, MOT_HomingParameters *homingParams)" />
	/// <seealso cref="BMC_SetHomingParamsBlock(char const * serialNo, MOT_HomingParameters *homingParams)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_SetHomingVelocity(char const * serialNo, unsigned int velocity);

	/// <summary> Move the motor by a relative amount. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="displacement"> Signed displacement in \ref DeviceUnits_page.</param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetNumberPositions(char const * serialNo)" />
	/// <seealso cref="BMC_GetVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BMC_SetVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="BMC_GetVelParamsBlock(char const * serialNo, MOT_VelocityParameters  *velocityParams)" />
	/// <seealso cref="BMC_SetVelParamsBlock(char const * serialNo, MOT_VelocityParameters *velocityParams)" />
	/// <seealso cref="BMC_MoveToPosition(char const * serialNo, int index)" />
	/// <seealso cref="BMC_MoveAtVelocity(char const * serialNo, MOT_TravelDirection direction)" />
	/// 		  \include CodeSnippet_move.cpp
	BRUSHLESSMOTOR_API short __cdecl BMC_MoveRelative(char const * serialNo, int displacement);

	/// <summary> Requests the jog parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetJogMode(char const * serialNo, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="BMC_GetJogStepSize(char const * serialNo)" />
	/// <seealso cref="BMC_GetJogVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BMC_GetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// 		  \include CodeSnippet_jogpars.cpp
	BRUSHLESSMOTOR_API short __cdecl BMC_RequestJogParams(const char * serialNo);

	/// <summary> Gets the jog mode. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
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
	/// <seealso cref="BMC_RequestJogParams(char const * serialNo)" />
	/// <seealso cref="BMC_SetJogMode(char const * serialNo, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="BMC_GetJogStepSize(char const * serialNo)" />
	/// <seealso cref="BMC_SetJogStepSize(char const * serialNo, unsigned int stepSize)" />
	/// <seealso cref="BMC_SetJogVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="BMC_GetJogVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BMC_GetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BMC_SetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BMC_MoveJog(char const * serialNo, MOT_TravelDirection jogDirection)" />
	/// 		  \include CodeSnippet_jogpars.cpp
	BRUSHLESSMOTOR_API short __cdecl BMC_GetJogMode(char const * serialNo, MOT_JogModes * mode, MOT_StopModes * stopMode);

	/// <summary> Sets the jog mode. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
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
	/// <seealso cref="BMC_GetJogMode(char const * serialNo, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="BMC_GetJogStepSize(char const * serialNo)" />
	/// <seealso cref="BMC_SetJogStepSize(char const * serialNo, unsigned int stepSize)" />
	/// <seealso cref="BMC_SetJogVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="BMC_GetJogVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BMC_GetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BMC_SetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BMC_MoveJog(char const * serialNo, MOT_TravelDirection jogDirection)" />
	/// 		  \include CodeSnippet_jogpars.cpp
	BRUSHLESSMOTOR_API short __cdecl BMC_SetJogMode(char const * serialNo, MOT_JogModes mode, MOT_StopModes stopMode);

	/// <summary> Gets the distance to move when jogging. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The step in \ref DeviceUnits_page. </returns>
	/// <seealso cref="BMC_RequestJogParams(char const * serialNo)" />
	/// <seealso cref="BMC_GetJogMode(char const * serialNo, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="BMC_SetJogMode(char const * serialNo, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="BMC_SetJogStepSize(char const * serialNo, unsigned int stepSize)" />
	/// <seealso cref="BMC_SetJogVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="BMC_GetJogVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BMC_GetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BMC_SetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BMC_MoveJog(char const * serialNo, MOT_TravelDirection jogDirection)" />
	/// 		  \include CodeSnippet_jogpars.cpp
	BRUSHLESSMOTOR_API unsigned int __cdecl BMC_GetJogStepSize(char const * serialNo);

	/// <summary> Sets the distance to move on jogging. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="stepSize"> The step in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetJogMode(char const * serialNo, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="BMC_SetJogMode(char const * serialNo, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="BMC_GetJogStepSize(char const * serialNo)" />
	/// <seealso cref="BMC_SetJogVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="BMC_GetJogVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BMC_GetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BMC_SetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BMC_MoveJog(char const * serialNo, MOT_TravelDirection jogDirection)" />
	/// 		  \include CodeSnippet_jogpars.cpp
	BRUSHLESSMOTOR_API short __cdecl BMC_SetJogStepSize(char const * serialNo, unsigned int stepSize);

	/// <summary> Gets the jog velocity parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="acceleration"> Address of the parameter to receive the acceleration in \ref DeviceUnits_page. </param>
	/// <param name="maxVelocity"> Address of the parameter to receive the velocity in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestJogParams(char const * serialNo)" />
	/// <seealso cref="BMC_GetJogMode(char const * serialNo, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="BMC_SetJogMode(char const * serialNo, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="BMC_GetJogStepSize(char const * serialNo)" />
	/// <seealso cref="BMC_SetJogStepSize(char const * serialNo, unsigned int stepSize)" />
	/// <seealso cref="BMC_SetJogVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="BMC_GetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BMC_SetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BMC_MoveJog(char const * serialNo, MOT_TravelDirection jogDirection)" />
	/// 		  \include CodeSnippet_jogpars.cpp
	BRUSHLESSMOTOR_API short __cdecl BMC_GetJogVelParams(char const * serialNo, int * acceleration, int * maxVelocity);

	/// <summary> Sets jog velocity parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="acceleration">   The acceleration in \ref DeviceUnits_page. </param>
	/// <param name="maxVelocity"> The maximum velocity in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetJogMode(char const * serialNo, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="BMC_SetJogMode(char const * serialNo, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="BMC_GetJogStepSize(char const * serialNo)" />
	/// <seealso cref="BMC_SetJogStepSize(char const * serialNo, unsigned int stepSize)" />
	/// <seealso cref="BMC_GetJogVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BMC_GetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BMC_SetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BMC_MoveJog(char const * serialNo, MOT_TravelDirection jogDirection)" />
	/// 		  \include CodeSnippet_jogpars.cpp
	BRUSHLESSMOTOR_API short __cdecl BMC_SetJogVelParams(char const * serialNo, int acceleration, int maxVelocity);

	/// <summary> Perform a jog. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="jogDirection"> The jog direction
	/// 					 <list type=table>
	///							<item><term>Forwards</term><term>1</term></item>
	///							<item><term>Backwards</term><term>2</term></item>
	/// 					 </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetJogMode(char const * serialNo, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="BMC_SetJogMode(char const * serialNo, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="BMC_GetJogStepSize(char const * serialNo)" />
	/// <seealso cref="BMC_SetJogStepSize(char const * serialNo, unsigned int stepSize)" />
	/// <seealso cref="BMC_SetJogVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="BMC_GetJogVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BMC_GetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BMC_SetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// 		  \include CodeSnippet_jog.cpp
	BRUSHLESSMOTOR_API short __cdecl BMC_MoveJog(char const * serialNo, MOT_TravelDirection jogDirection);

	/// <summary> Requests the velocity parameters. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BMC_GetVelParamsBlock(char const * serialNo, MOT_VelocityParameters  *velocityParams)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_RequestVelParams(char const * serialNo);

	/// <summary> Gets the move velocity parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec11 "Positioning" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="acceleration"> Address of the parameter to receive the acceleration value in \ref DeviceUnits_page. </param>
	/// <param name="maxVelocity"> Address of the parameter to receive the maximum velocity value in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestVelParams(char const * serialNo)" />
	/// <seealso cref="BMC_SetVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="BMC_GetVelParamsBlock(char const * serialNo, MOT_VelocityParameters  *velocityParams)" />
	/// <seealso cref="BMC_SetVelParamsBlock(char const * serialNo, MOT_VelocityParameters *velocityParams)" />
	/// <seealso cref="BMC_MoveToPosition(char const * serialNo, int index)" />
	/// <seealso cref="BMC_MoveRelative(char const * serialNo, int displacement)" />
	/// <seealso cref="BMC_MoveAtVelocity(char const * serialNo, MOT_TravelDirection direction)" />
	/// 		  \include CodeSnippet_movepars.cpp
	BRUSHLESSMOTOR_API short __cdecl BMC_GetVelParams(char const * serialNo, int * acceleration, int * maxVelocity);

	/// <summary> Sets the move velocity parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec11 "Positioning" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="acceleration"> The new acceleration value in \ref DeviceUnits_page. </param>
	/// <param name="maxVelocity"> The new maximum velocity value in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BMC_GetVelParamsBlock(char const * serialNo, MOT_VelocityParameters  *velocityParams)" />
	/// <seealso cref="BMC_SetVelParamsBlock(char const * serialNo, MOT_VelocityParameters *velocityParams)" />
	/// <seealso cref="BMC_MoveToPosition(char const * serialNo, int index)" />
	/// <seealso cref="BMC_MoveRelative(char const * serialNo, int displacement)" />
	/// <seealso cref="BMC_MoveAtVelocity(char const * serialNo, MOT_TravelDirection direction)" />
	/// 		  \include CodeSnippet_movepars.cpp
	BRUSHLESSMOTOR_API short __cdecl BMC_SetVelParams(char const * serialNo, int acceleration, int maxVelocity);

	/// <summary> Start moving at the current velocity in the specified direction. </summary>
	/// <remarks> see \ref C_MOTOR_sec11 "Positioning" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="direction"> The required direction of travel.
	/// 					 <list type=table>
	///							<item><term>Forwards</term><term>1</term></item>
	///							<item><term>Backwards</term><term>2</term></item>
	/// 					 </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BMC_SetVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="BMC_GetVelParamsBlock(char const * serialNo, MOT_VelocityParameters  *velocityParams)" />
	/// <seealso cref="BMC_SetVelParamsBlock(char const * serialNo, MOT_VelocityParameters *velocityParams)" />
	/// <seealso cref="BMC_MoveToPosition(char const * serialNo, int index)" />
	/// <seealso cref="BMC_MoveRelative(char const * serialNo, int displacement)" />
	/// 		  \include CodeSnippet_move.cpp
	BRUSHLESSMOTOR_API short __cdecl BMC_MoveAtVelocity(char const * serialNo, MOT_TravelDirection direction);

	/// <summary> Sets the motor direction sense. </summary>
	/// <remarks> This function is used because some actuators use have directions of motion reversed.<br />
	/// 		  This parameter will tell the system to reverse the direction sense whnd moving, jogging etc. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="reverse"> if  <c>true</c> then directions will be swapped on these moves. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BRUSHLESSMOTOR_API short __cdecl BMC_SetDirection(char const * serialNo, bool reverse);

	/// <summary> Stop the current move immediately (with risk of losing track of position). </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_StopProfiled(char const * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_StopImmediate(char const * serialNo);

	/// <summary> Stop the current move using the current velocity profile. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_StopImmediate(char const * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_StopProfiled(char const * serialNo);

	/// <summary> Requests the backlash. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetBacklash(char const * serialNo)" />
	/// <seealso cref="BMC_SetBacklash(char const * serialNo, long distance)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_RequestBacklash(char const * serialNo);

	/// <summary> Get the backlash distance setting (used to control hysteresis). </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The backlash distance in \ref DeviceUnits_page. </returns>
	/// <seealso cref="BMC_RequestBacklash(char const * serialNo)" />
	/// <seealso cref="BMC_SetBacklash(char const * serialNo, long distance)" />
	BRUSHLESSMOTOR_API long __cdecl BMC_GetBacklash(char const * serialNo);

	/// <summary> Sets the backlash distance (used to control hysteresis). </summary>
	/// <param name="serialNo">  The serial no. </param>
	/// <param name="distance"> The distance in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestBacklash(char const * serialNo)" />
	/// <seealso cref="BMC_GetBacklash(char const * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_SetBacklash(char const * serialNo, long distance);

	/// <summary> Get the Position Counter. </summary>
	/// <remarks> The position counter is identical to the position parameter.<br />
	/// 		  The position counter is set to zero when homing is complete.<br />
	/// 		  The position counter can also be set using <see cref="BMC_SetPositionCounter(char const * serialNo, long count)" /> <br />
	/// 		  if homing is not to be perforned</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> Position Counter in \ref DeviceUnits_page. </returns>
	/// <seealso cref="BMC_GetPosition(char const * serialNo)" />
	/// <seealso cref="BMC_SetPositionCounter(char const * serialNo, long count)" />
	BRUSHLESSMOTOR_API long __cdecl BMC_GetPositionCounter(char const * serialNo);

	/// <summary> Set the Position Counter. </summary>
	/// <remarks> Setting the position counter will locate the current position. <br />
	/// 		  Setting the position counter will effectively define the home position of a motor. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="count"> Position count in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetPositionCounter(char const * serialNo)" />
	/// <seealso cref="BMC_GetPosition(char const * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_SetPositionCounter(char const * serialNo, long count);

	/// <summary> Requests the encoder counter. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetEncoderCounter(char const * serialNo)" />
	/// <seealso cref="BMC_SetEncoderCounter(char const * serialNo, long count)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_RequestEncoderCounter(char const * serialNo);

	/// <summary> Get the Encoder Counter. </summary>
	/// <remarks> For devices that have an encoder, the current encoder position can be read. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> Encoder Count of encoder units. </returns>
	/// <seealso cref="BMC_RequestEncoderCounter(char const * serialNo)" />
	/// <seealso cref="BMC_SetEncoderCounter(char const * serialNo, long count)" />
	BRUSHLESSMOTOR_API long __cdecl BMC_GetEncoderCounter(char const * serialNo);

	/// <summary> Set the Encoder Counter values. </summary>
	/// <remarks> setting the encoder counter to zero, effectively defines a home position on the encoder strip.<br />
	/// 		  NOTE, setting this value does not move the device.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="count"> The encoder count in encoder units. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestEncoderCounter(char const * serialNo)" />
	/// <seealso cref="BMC_GetEncoderCounter(char const * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_SetEncoderCounter(char const * serialNo, long count);


	/// <summary> Gets the software limits mode. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	The software limits mode <list type=table>
	///							<item><term> Disable any move outside of the current travel range of the stage. </term><term>0</term></item>
	///							<item><term> Truncate moves to within the current travel range of the stage. </term><term>1</term></item>
	///							<item><term> Allow all moves, regardless of whether they are within the current travel range of the stage. </term><term>2</term></item>
	/// 		  </list>. </returns>
	/// <returns> The software limits mode. </returns>
	/// <seealso cref="BMC_SetLimitsSoftwareApproachPolicy(const char * serialNo, MOT_LimitsSoftwareApproachPolicy limitsSoftwareApproachPolicy)" />
	BRUSHLESSMOTOR_API MOT_LimitsSoftwareApproachPolicy __cdecl BMC_GetSoftLimitMode(char const * serialNo);

	/// <summary> Sets the software limits mode. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="limitsSoftwareApproachPolicy"> The soft limit mode
	/// 					 <list type=table>
	///							<item><term> Disable any move outside of the current travel range of the stage. </term><term>0</term></item>
	///							<item><term> Truncate moves to within the current travel range of the stage. </term><term>1</term></item>
	///							<item><term> Allow all moves, regardless of whether they are within the current travel range of the stage. </term><term>2</term></item>
	/// 					 </list> </param>
	/// <seealso cref="BMC_GetSoftLimitMode(const char * serialNo)" />
	BRUSHLESSMOTOR_API void __cdecl BMC_SetLimitsSoftwareApproachPolicy(char const * serialNo, MOT_LimitsSoftwareApproachPolicy limitsSoftwareApproachPolicy);

	/// <summary> Requests the MMI Parameters for the KCube Display Interface. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetMMIParams(char const * serialNo, __int16 *displayIntensity)" />
	/// <seealso cref="BMC_GetMMIParamsExt(char const * serialNo, __int16 *displayIntensity, __int16 *displayTimeout, __int16 *displayDimIntensity)" />
	/// <seealso cref="BMC_GetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_RequestMMIparams(char const * serialNo);

	/// <summary> Get the MMI Parameters for the KCube Display Interface. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="wheelMode">	The device wheel mode.
	/// 					<list type=table>
	///							<item><term>1</term><term>Constant Velocity<br />The device will continue moving until the end stop is reached or the duration of the wheel action</term></item>
	///							<item><term>2</term><term>Jog<br />The device will jog forward or backward according to the wheel action.<br />
	///								  The device will jog according to the Jog parameters</term></item>
	///							<item><term>3</term><term>Move Absolute<br />The device will move to either Preset Po 1 or 2 according to the wheel action.</term></item>
	/// 					</list> </param>
	/// <param name="wheelMaxVelocity">  The wheel maximum velocity in \ref DeviceUnits_page. </param>
	/// <param name="wheelAcceleration"> The wheel acceleration in \ref DeviceUnits_page. </param>
	/// <param name="directionSense">	    The wheel direction sense. </param>
	/// <param name="presetPosition1">	    The first preset position in \ref DeviceUnits_page. </param>
	/// <param name="presetPosition2">	    The second preset position in \ref DeviceUnits_page. </param>
	/// <param name="displayIntensity">	    The display intensity, range 0 to 100%. </param>
	/// <param name="displayTimeout">	    The display timeout, range 0 to 480 in minutes (0 is off, otherwise the inactivity period before dimming the display). </param>
	/// <param name="displayDimIntensity">	The display dimmed intensity, range 0 to 10 (after the timeout period the device display will dim). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestMMIParams(char const * serialNo)" />
	/// <seealso cref="BMC_SetMMIParamsExt(char const * serialNo, KMOT_WheelMode wheelMode, __int32 wheelMaxVelocity, __int32 wheelAcceleration, KMOT_WheelDirectionSense directionSense, __int32 presetPosition1, __int32 presetPosition2, __int16 displayIntensity, __int16 displayTimeout, __int16 displayDimIntensity)" />
	/// <seealso cref="BMC_SetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	/// <seealso cref="BMC_GetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	BRUSHLESSMOTOR_API  short __cdecl BMC_GetMMIParamsExt(char const * serialNo, KMOT_WheelMode *wheelMode, __int32 *wheelMaxVelocity, __int32 *wheelAcceleration, KMOT_WheelDirectionSense *directionSense,
		__int32 *presetPosition1, __int32 *presetPosition2, __int16 *displayIntensity, __int16 *displayTimeout, __int16 *displayDimIntensity);

	/// \deprecated
	/// <summary> Get the MMI Parameters for the KCube Display Interface. </summary>
	/// <remarks> superceded by <see cref="BMC_GetMMIParamsExt(char const * serialNo, KMOT_WheelMode *wheelMode, __int32 *wheelMaxVelocity, __int32 *wheelAcceleration, KMOT_WheelDirectionSense *directionSense, __int32 *presetPosition1, __int32 *presetPosition2, __int16 *displayIntensity, __int16 *displayTimeout, __int16 *displayDimIntensity)"/> </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="wheelMode">	The device wheel mode.
	/// 					<list type=table>
	///							<item><term>1</term><term>Constant Velocity<br />The device will continue moving until the end stop is reached or the duration of the wheel action</term></item>
	///							<item><term>2</term><term>Jog<br />The device will jog forward or backward according to the wheel action.<br />
	///								  The device will jog according to the Jog parameters</term></item>
	///							<item><term>3</term><term>Move Absolute<br />The device will move to either Preset Po 1 or 2 according to the wheel action.</term></item>
	/// 					</list> </param>
	/// <param name="wheelMaxVelocity">  The wheel maximum velocity in \ref DeviceUnits_page. </param>
	/// <param name="wheelAcceleration"> The wheel acceleration in \ref DeviceUnits_page. </param>
	/// <param name="directionSense">	    The wheel direction sense. </param>
	/// <param name="presetPosition1">	    The first preset position in \ref DeviceUnits_page. </param>
	/// <param name="presetPosition2">	    The second preset position in \ref DeviceUnits_page. </param>
	/// <param name="displayIntensity">	    The display intensity, range 0 to 100%. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestMMIParams(char const * serialNo)" />
	/// <seealso cref="BMC_SetMMIParams(char const * serialNo, KMOT_WheelMode wheelMode, __int32 wheelMaxVelocity, __int32 wheelAcceleration, KMOT_WheelDirectionSense directionSense, __int32 presetPosition1, __int32 presetPosition2, __int16 displayIntensity)" />
	/// <seealso cref="BMC_SetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	/// <seealso cref="BMC_GetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	BRUSHLESSMOTOR_API  short __cdecl BMC_GetMMIParams(char const * serialNo, KMOT_WheelMode *wheelMode, __int32 *wheelMaxVelocity, __int32 *wheelAcceleration, KMOT_WheelDirectionSense *directionSense,
		__int32 *presetPosition1, __int32 *presetPosition2, __int16 *displayIntensity);

	/// <summary> Set the MMI Parameters for the KCube Display Interface. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="wheelMode">	The device wheel mode.
	/// 					<list type=table>
	///							<item><term>1</term><term>Constant Velocity<br />The device will continue moving until the end stop is reached or the duration of the wheel action</term></item>
	///							<item><term>2</term><term>Jog<br />The device will jog forward or backward according to the wheel action.<br />
	///								  The device will jog according to the Jog parameters</term></item>
	///							<item><term>3</term><term>Move Absolute<br />The device will move to either Preset Po 1 or 2 according to the wheel action.</term></item>
	/// 					</list> </param>
	/// <param name="wheelMaxVelocity">  The wheel maximum velocity in \ref DeviceUnits_page. </param>
	/// <param name="wheelAcceleration"> The wheel acceleration in \ref DeviceUnits_page. </param>
	/// <param name="directionSense">	    The direction sense. </param>
	/// <param name="presetPosition1">	    The first preset position in \ref DeviceUnits_page. </param>
	/// <param name="presetPosition2">	    The second preset position in \ref DeviceUnits_page. </param>
	/// <param name="displayIntensity">	    The display intensity, range 0 to 100%. </param>
	/// <param name="displayTimeout">	    The display timeout, range 0 to 480 in minutes (0 is off, otherwise the inactivity period before dimming the display). </param>
	/// <param name="displayDimIntensity">	The display dimmed intensity, range 0 to 10 (after the timeout period the device display will dim). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestMMIParams(char const * serialNo)" />
	/// <seealso cref="BMC_GetMMIParamsExt(char const * serialNo, KMOT_WheelMode *wheelMode, __int32 *wheelMaxVelocity, __int32 *wheelAcceleration, KMOT_WheelDirectionSense *directionSense, __int32 *presetPosition1, __int32 *presetPosition2, __int16 *displayIntensity, __int16 *displayTimeout, __int16 *displayDimIntensity)" />
	/// <seealso cref="BMC_SetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	/// <seealso cref="BMC_GetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_SetMMIParamsExt(char const * serialNo, KMOT_WheelMode wheelMode, __int32 wheelMaxVelocity, __int32 wheelAcceleration, KMOT_WheelDirectionSense directionSense,
		__int32 presetPosition1, __int32 presetPosition2, __int16 displayIntensity, __int16 displayTimeout, __int16 displayDimIntensity);

	/// \deprecated
	/// <summary> Set the MMI Parameters for the KCube Display Interface. </summary>
	/// <remarks> superceded by <see cref="BMC_SetMMIParams(char const * serialNo, KMOT_WheelMode wheelMode, __int32 wheelMaxVelocity, __int32 wheelAcceleration, KMOT_WheelDirectionSense directionSense, __int32 presetPosition1, __int32 presetPosition2, __int16 displayIntensity)"/> </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="wheelMode">	The device wheel mode.
	/// 					<list type=table>
	///							<item><term>1</term><term>Constant Velocity<br />The device will continue moving until the end stop is reached or the duration of the wheel action</term></item>
	///							<item><term>2</term><term>Jog<br />The device will jog forward or backward according to the wheel action.<br />
	///								  The device will jog according to the Jog parameters</term></item>
	///							<item><term>3</term><term>Move Absolute<br />The device will move to either Preset Po 1 or 2 according to the wheel action.</term></item>
	/// 					</list> </param>
	/// <param name="wheelMaxVelocity">  The wheel maximum velocity in \ref DeviceUnits_page. </param>
	/// <param name="wheelAcceleration"> The wheel acceleration in \ref DeviceUnits_page. </param>
	/// <param name="directionSense">	    The direction sense. </param>
	/// <param name="presetPosition1">	    The first preset position in \ref DeviceUnits_page. </param>
	/// <param name="presetPosition2">	    The second preset position in \ref DeviceUnits_page. </param>
	/// <param name="displayIntensity">	    The display intensity, range 0 to 100%. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestMMIParams(char const * serialNo)" />
	/// <seealso cref="BMC_GetMMIParams(char const * serialNo, KMOT_WheelMode *wheelMode, __int32 *wheelMaxVelocity, __int32 *wheelAcceleration, KMOT_WheelDirectionSense *directionSense, __int32 *presetPosition1, __int32 *presetPosition2, __int16 *displayIntensity)" />
	/// <seealso cref="BMC_SetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	/// <seealso cref="BMC_GetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_SetMMIParams(char const * serialNo, KMOT_WheelMode wheelMode, __int32 wheelMaxVelocity, __int32 wheelAcceleration, KMOT_WheelDirectionSense directionSense,
		__int32 presetPosition1, __int32 presetPosition2, __int16 displayIntensity);

	/// <summary> Requests the Trigger Configuration Parameters. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_SetTriggerConfigParams(char const * serialNo, KSC_TriggerPortMode trigger1Mode, KSC_TriggerPortPolarity trigger1Polarity, KSC_TriggerPortMode trigger2Mode, KSC_TriggerPortPolarity trigger2Polarity)" />
	/// <seealso cref="BMC_GeTriggerConfigParams(char const * serialNo, KSC_TriggerPortMode *trigger1Mode, KSC_TriggerPortPolarity *trigger1Polarity, KSC_TriggerPortMode *trigger2Mode, KSC_TriggerPortPolarity *trigger2Polarity)" />
	/// <seealso cref="BMC_SetTriggerConfigParamsBlock(const char * serialNo, KSC_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="BMC_GetTriggerConfigParamsBlock(const char * serialNo, KSC_TriggerConfig *triggerConfigParams)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_RequestTriggerConfigParams(char const * serialNo);

	/// <summary> Get the Trigger Configuration Parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
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
	/// <seealso cref="BMC_RequestTriggerConfigParams(char const * serialNo)" />
	/// <seealso cref="BMC_SetTriggerConfigParams(char const * serialNo, KMOT_TriggerPortMode trigger1Mode, KMOT_TriggerPortPolarity trigger1Polarity, KMOT_TriggerPortMode trigger2Mode, KMOT_TriggerPortPolarity trigger2Polarity)" />
	/// <seealso cref="BMC_SetTriggerConfigParamsBlock(const char * serialNo, KMOT_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="BMC_GetTriggerConfigParamsBlock(const char * serialNo, KMOT_TriggerConfig *triggerConfigParams)" />
	BRUSHLESSMOTOR_API  short BMC_GetTriggerConfigParams(char const * serialNo, KMOT_TriggerPortMode *trigger1Mode, KMOT_TriggerPortPolarity *trigger1Polarity, KMOT_TriggerPortMode *trigger2Mode, KMOT_TriggerPortPolarity *trigger2Polarity);

	/// <summary> Set the Trigger Configuration Parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
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
	/// <seealso cref="BMC_RequestTriggerConfigParams(char const * serialNo)" />
	/// <seealso cref="BMC_GeTriggerConfigParams(char const * serialNo, KMOT_TriggerPortMode *trigger1Mode, KMOT_TriggerPortPolarity *trigger1Polarity, KMOT_TriggerPortMode *trigger2Mode, KMOT_TriggerPortPolarity *trigger2Polarity)" />
	/// <seealso cref="BMC_SetTriggerConfigParamsBlock(const char * serialNo, KMOT_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="BMC_GetTriggerConfigParamsBlock(const char * serialNo, KMOT_TriggerConfig *triggerConfigParams)" />
	BRUSHLESSMOTOR_API short BMC_SetTriggerConfigParams(char const * serialNo, KMOT_TriggerPortMode trigger1Mode, KMOT_TriggerPortPolarity trigger1Polarity, KMOT_TriggerPortMode trigger2Mode, KMOT_TriggerPortPolarity trigger2Polarity);

	/// <summary> Requests the position trigger parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetTriggerParamsParams(char const * serialNo, __int32 *triggerStartPositionFwd, __int32 *triggerIntervalFwd, __int32 *triggerPulseCountFwd, 
	///									 __int32 *triggerStartPositionRev, __int32 *triggerIntervalRev, __int32 *triggerPulseCountRev, 
	///									 __int32 *triggerPulseWidth, __int32 *cycleCount)" />
	/// <seealso cref="BMC_SetTriggerParamsParams(char const * serialNo, __int32 triggerStartPositionFwd, __int32 triggerIntervalFwd, __int32 triggerPulseCountFwd,
	///										__int32 triggerStartPositionRev, __int32 triggerIntervalRev, __int32 triggerPulseCountRev,
	///										__int32 triggerPulseWidth, __int32 cycleCount)" />
	/// <seealso cref="BMC_GetTriggerParamsParamsBlock(const char * serialNo, KMOT_TriggerParams *triggerParamsParams)" />
	/// <seealso cref="BMC_SetTriggerParamsParamsBlock(const char * serialNo, KMOT_TriggerParams *triggerParamsParams)" />
	BRUSHLESSMOTOR_API  short __cdecl BMC_RequestPosTriggerParams(char const * serialNo);

	/// <summary> Get the Trigger Parameters Parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="triggerStartPositionFwd"> The trigger start position in \ref DeviceUnits_page. </param>
	/// <param name="triggerIntervalFwd">	    The trigger interval in \ref DeviceUnits_page. </param>
	/// <param name="triggerPulseCountFwd">    Number of trigger pulses. </param>
	/// <param name="triggerStartPositionRev"> The trigger start position in \ref DeviceUnits_page. </param>
	/// <param name="triggerIntervalRev">	    The trigger interval in \ref DeviceUnits_page. </param>
	/// <param name="triggerPulseCountRev">    Number of trigger pulses. </param>
	/// <param name="triggerPulseWidth">    Width of the trigger pulse in milliseconds, range 1 (1us) to 1000000 (1s). </param>
	/// <param name="cycleCount">   Number of cycles to perform triggering. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestPosTriggerParams(char const * serialNo)" />
	/// <seealso cref="BMC_SetTriggerParamsParams(char const * serialNo, __int32 triggerStartPositionFwd, __int32 triggerIntervalFwd, __int32 triggerPulseCountFwd,
	///										__int32 triggerStartPositionRev, __int32 triggerIntervalRev, __int32 triggerPulseCountRev,
	///										__int32 triggerPulseWidth, __int32 cycleCount)" />
	/// <seealso cref="BMC_GetTriggerParamsParamsBlock(const char * serialNo, KMOT_TriggerParams *triggerParamsParams)" />
	/// <seealso cref="BMC_SetTriggerParamsParamsBlock(const char * serialNo, KMOT_TriggerParams *triggerParamsParams)" />
	BRUSHLESSMOTOR_API  short BMC_GetTriggerParamsParams(char const * serialNo, __int32 *triggerStartPositionFwd, __int32 *triggerIntervalFwd, __int32 *triggerPulseCountFwd,
		__int32 *triggerStartPositionRev, __int32 *triggerIntervalRev, __int32 *triggerPulseCountRev,
		__int32 *triggerPulseWidth, __int32 *cycleCount);

	/// <summary> Set the Trigger Parameters Parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="triggerStartPositionFwd"> The trigger start position in \ref DeviceUnits_page. </param>
	/// <param name="triggerIntervalFwd">	    The trigger interval in \ref DeviceUnits_page. </param>
	/// <param name="triggerPulseCountFwd">    Number of trigger pulses. </param>
	/// <param name="triggerStartPositionRev"> The trigger start position in \ref DeviceUnits_page. </param>
	/// <param name="triggerIntervalRev">	    The trigger interval in \ref DeviceUnits_page. </param>
	/// <param name="triggerPulseCountRev">    Number of trigger pulses. </param>
	/// <param name="triggerPulseWidth">    Width of the trigger pulse in milliseconds, range 1 (1us) to 1000000 (1s). </param>
	/// <param name="cycleCount">   Number of cycles to perform triggering. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestPosTriggerParams(char const * serialNo)" />
	/// <seealso cref="BMC_GeTriggerParamsParams(char const * serialNo, __int32 *triggerStartPositionFwd, __int32 *triggerIntervalFwd, __int32 *triggerPulseCountFwd,
	///										 __int32 *triggerStartPositionRev, __int32 *triggerIntervalRev, __int32 *triggerPulseCountRev,
	///										 __int32 *triggerPulseWidth, __int32 *cycleCount)" />
	/// <seealso cref="BMC_GetTriggerParamsParamsBlock(const char * serialNo, KMOT_TriggerParams *triggerParamsParams)" />
	/// <seealso cref="BMC_SetTriggerParamsParamsBlock(const char * serialNo, KMOT_TriggerParams *triggerParamsParams)" />
	BRUSHLESSMOTOR_API short BMC_SetTriggerParamsParams(char const * serialNo, __int32 triggerStartPositionFwd, __int32 triggerIntervalFwd, __int32 triggerPulseCountFwd,
		__int32 triggerStartPositionRev, __int32 triggerIntervalRev, __int32 triggerPulseCountRev,
		__int32 triggerPulseWidth, __int32 cycleCount);

	/// <summary> Gets the MMI parameters for the device. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="mmiParams"> Options for controlling the mmi. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestMMIParams(char const * serialNo)" />
	/// <seealso cref="BMC_GetMMIParamsExt(char const * serialNo, KMOT_WheelMode *wheelMode, __int32 *wheelMaxVelocity, __int32 *wheelAcceleration, KMOT_WheelDirectionSense *directionSense, __int32 *presetPosition1, __int32 *presetPosition2, __int16 *displayIntensity, __int16 *displayTimeout, __int16 *displayDimIntensity)" />
	/// <seealso cref="BMC_SetMMIParamsExt(char const * serialNo, KMOT_WheelMode wheelMode, __int32 wheelMaxVelocity, __int32 wheelAcceleration, KMOT_WheelDirectionSense directionSense, __int32 presetPosition1, __int32 presetPosition2, __int16 displayIntensity, __int16 displayTimeout, __int16 displayDimIntensity)" />
	/// <seealso cref="BMC_SetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	BRUSHLESSMOTOR_API short BMC_GetMMIParamsBlock(char const * serialNo, KMOT_MMIParams *mmiParams);

	/// <summary> Sets the MMI parameters for the device. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="mmiParams"> Options for controlling the mmi. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestMMIParams(char const * serialNo)" />
	/// <seealso cref="BMC_GetMMIParamsExt(char const * serialNo, KMOT_WheelMode *wheelMode, __int32 *wheelMaxVelocity, __int32 *wheelAcceleration, KMOT_WheelDirectionSense *directionSense, __int32 *presetPosition1, __int32 *presetPosition2, __int16 *displayIntensity, __int16 *displayTimeout, __int16 *displayDimIntensity)" />
	/// <seealso cref="BMC_SetMMIParamsExt(char const * serialNo, KMOT_WheelMode wheelMode, __int32 wheelMaxVelocity, __int32 wheelAcceleration, KMOT_WheelDirectionSense directionSense, __int32 presetPosition1, __int32 presetPosition2, __int16 displayIntensity, __int16 displayTimeout, __int16 displayDimIntensity)" />
	/// <seealso cref="BMC_GetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	BRUSHLESSMOTOR_API short BMC_SetMMIParamsBlock(char const * serialNo, KMOT_MMIParams *mmiParams);

	/// <summary> Gets the trigger configuration parameters block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="triggerConfigParams"> Options for controlling the trigger configuration. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestTriggerConfigParams(char const * serialNo)" />
	/// <seealso cref="BMC_GeTriggerConfigParams(char const * serialNo, KMOT_TriggerPortMode *trigger1Mode, KMOT_TriggerPortPolarity *trigger1Polarity, KMOT_TriggerPortMode *trigger2Mode, KMOT_TriggerPortPolarity *trigger2Polarity)" />
	/// <seealso cref="BMC_SetTriggerConfigParams(char const * serialNo, KMOT_TriggerPortMode trigger1Mode, KMOT_TriggerPortPolarity trigger1Polarity, KMOT_TriggerPortMode trigger2Mode, KMOT_TriggerPortPolarity trigger2Polarity)" />
	/// <seealso cref="BMC_SetTriggerConfigParamsBlock(const char * serialNo, KMOT_TriggerConfig *triggerConfigParams)" />
	BRUSHLESSMOTOR_API short BMC_GetTriggerConfigParamsBlock(char const * serialNo, KMOT_TriggerConfig *triggerConfigParams);

	/// <summary> Sets the trigger configuration parameters block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="triggerConfigParams"> Options for controlling the trigger configuration. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestTriggerConfigParams(char const * serialNo)" />
	/// <seealso cref="BMC_GeTriggerConfigParams(char const * serialNo, KMOT_TriggerPortMode *trigger1Mode, KMOT_TriggerPortPolarity *trigger1Polarity, KMOT_TriggerPortMode *trigger2Mode, KMOT_TriggerPortPolarity *trigger2Polarity)" />
	/// <seealso cref="BMC_SetTriggerConfigParams(char const * serialNo, KMOT_TriggerPortMode trigger1Mode, KMOT_TriggerPortPolarity trigger1Polarity, KMOT_TriggerPortMode trigger2Mode, KMOT_TriggerPortPolarity trigger2Polarity)" />
	/// <seealso cref="BMC_GetTriggerConfigParamsBlock(const char * serialNo, KMOT_TriggerConfig *triggerConfigParams)" />
	BRUSHLESSMOTOR_API short BMC_SetTriggerConfigParamsBlock(char const * serialNo, KMOT_TriggerConfig *triggerConfigParams);

	/// <summary> Gets the trigger parameters block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="triggerParamsParams"> Options for controlling the trigger. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestPosTriggerParams(char const * serialNo)" />
	/// <seealso cref="BMC_GeTriggerParamsParams(char const * serialNo, __int32 *triggerStartPositionFwd, __int32 *triggerIntervalFwd, __int32 *triggerPulseCountFwd,
	///										 __int32 *triggerStartPositionRev, __int32 *triggerIntervalRev, __int32 *triggerPulseCountRev,
	///										 __int32 *triggerPulseWidth, __int32 *cycleCount)" />
	/// <seealso cref="BMC_SetTriggerParamsParams(char const * serialNo, __int32 triggerStartPositionFwd, __int32 triggerIntervalFwd, __int32 triggerPulseCountFwd,
	///										__int32 triggerStartPositionRev, __int32 triggerIntervalRev, __int32 triggerPulseCountRev,
	///										__int32 triggerPulseWidth, __int32 cycleCount)" />
	/// <seealso cref="BMC_SetTriggerParamsParamsBlock(const char * serialNo, KMOT_TriggerParams *triggerParamsParams)" />
	BRUSHLESSMOTOR_API short BMC_GetTriggerParamsParamsBlock(char const * serialNo, KMOT_TriggerParams *triggerParamsParams);

	/// <summary> Sets the trigger parameters block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="triggerParamsParams"> Options for controlling the trigger. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestPosTriggerParams(char const * serialNo)" />
	/// <seealso cref="BMC_GeTriggerParamsParams(char const * serialNo, __int32 *triggerStartPositionFwd, __int32 *triggerIntervalFwd, __int32 *triggerPulseCountFwd,
	///										 __int32 *triggerStartPositionRev, __int32 *triggerIntervalRev, __int32 *triggerPulseCountRev,
	///										 __int32 *triggerPulseWidth, __int32 *cycleCount)" />
	/// <seealso cref="BMC_SetTriggerParamsParams(char const * serialNo, __int32 triggerStartPositionFwd, __int32 triggerIntervalFwd, __int32 triggerPulseCountFwd,
	///										__int32 triggerStartPositionRev, __int32 triggerIntervalRev, __int32 triggerPulseCountRev,
	///										__int32 triggerPulseWidth, __int32 cycleCount)" />
	/// <seealso cref="BMC_GetTriggerParamsParamsBlock(const char * serialNo, KMOT_TriggerParams *triggerParamsParams)" />
	BRUSHLESSMOTOR_API short BMC_SetTriggerParamsParamsBlock(char const * serialNo, KMOT_TriggerParams *triggerParamsParams);

	/// <summary> Get the move velocity parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec11 "Positioning" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="velocityParams"> Address of the MOT_VelocityParameters to recieve the velocity parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestVelParams(char const * serialNo)" />
	/// <seealso cref="BMC_GetVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BMC_SetVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="BMC_SetVelParamsBlock(char const * serialNo, MOT_VelocityParameters *velocityParams)" />
	/// <seealso cref="BMC_MoveToPosition(char const * serialNo, int index)" />
	/// <seealso cref="BMC_MoveRelative(char const * serialNo, int displacement)" />
	/// <seealso cref="BMC_MoveAtVelocity(char const * serialNo, MOT_TravelDirection direction)" />
	/// 		  \include CodeSnippet_movepars.cpp
	BRUSHLESSMOTOR_API short __cdecl BMC_GetVelParamsBlock(const char * serialNo, MOT_VelocityParameters  *velocityParams);

	/// <summary> Set the move velocity parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec11 "Positioning" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="velocityParams"> The address of the MOT_VelocityParameters holding the new velocity parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BMC_SetVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="BMC_GetVelParamsBlock(char const * serialNo, MOT_VelocityParameters  *velocityParams)" />
	/// <seealso cref="BMC_MoveToPosition(char const * serialNo, int index)" />
	/// <seealso cref="BMC_MoveRelative(char const * serialNo, int displacement)" />
	/// <seealso cref="BMC_MoveAtVelocity(char const * serialNo, MOT_TravelDirection direction)" />
	/// 		  \include CodeSnippet_movepars.cpp
	BRUSHLESSMOTOR_API short __cdecl BMC_SetVelParamsBlock(const char * serialNo, MOT_VelocityParameters *velocityParams);

	/// <summary> Sets the move absolute position. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="position"> The absolute position in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestMoveAbsolutePosition(char const * serialNo)" />
	/// <seealso cref="BMC_GetMoveAbsolutePosition(const char * serialNo)" />
	/// <seealso cref="BMC_MoveAbsolute(const char * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_SetMoveAbsolutePosition(const char * serialNo, int position);

	/// <summary> Requests the position of next absolute move. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetMoveAbsolutePosition(const char * serialNo)" />
	/// <seealso cref="BMC_SetMoveAbsolutePosition(const char * serialNo, int position)" />
	/// <seealso cref="BMC_MoveAbsolute(const char * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_RequestMoveAbsolutePosition(char const * serialNo);

	/// <summary> Gets the move absolute position. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The move absolute position in \ref DeviceUnits_page. </returns>
	/// <seealso cref="BMC_RequestMoveAbsolutePosition(char const * serialNo)" />
	/// <seealso cref="BMC_SetMoveAbsolutePosition(const char * serialNo, int position)" />
	/// <seealso cref="BMC_MoveAbsolute(const char * serialNo)" />
	BRUSHLESSMOTOR_API int __cdecl BMC_GetMoveAbsolutePosition(const char * serialNo);

	/// <summary> Moves the device to the position defined in the SetMoveAbsolute command. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_SetMoveAbsolutePosition(const char * serialNo, int position)" />
	/// <seealso cref="BMC_RequestMoveAbsolutePosition(char const * serialNo)" />
	/// <seealso cref="BMC_GetMoveAbsolutePosition(const char * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_MoveAbsolute(const char * serialNo);

	/// <summary> Sets the move relative distance. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="distance"> The relative distance in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestMoveRelativeDistance(char const * serialNo)" />
	/// <seealso cref="BMC_GetMoveRelativeDistance(const char * serialNo)" />
	/// <seealso cref="BMC_MoveRelativeDistance(const char * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_SetMoveRelativeDistance(const char * serialNo, int distance);

	/// <summary> Requests the relative move distance. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetMoveRelativeDistance(const char * serialNo)" />
	/// <seealso cref="BMC_SetMoveRelativeDistance(const char * serialNo, int distance)" />
	/// <seealso cref="BMC_MoveRelativeDistance(const char * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_RequestMoveRelativeDistance(char const * serialNo);

	/// <summary> Gets the move relative distance. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The move relative distance in \ref DeviceUnits_page. </returns>
	/// <seealso cref="BMC_RequestMoveRelativeDistance(char const * serialNo)" />
	/// <seealso cref="BMC_SetMoveRelativeDistance(const char * serialNo, int distance)" />
	/// <seealso cref="BMC_MoveRelativeDistance(const char * serialNo)" />
	BRUSHLESSMOTOR_API int __cdecl BMC_GetMoveRelativeDistance(const char * serialNo);

	/// <summary> Moves the device by a relative distancce defined by SetMoveRelativeDistance. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_SetMoveRelativeDistance(const char * serialNo, int distance)" />
	/// <seealso cref="BMC_RequestMoveRelativeDistance(char const * serialNo)" />
	/// <seealso cref="BMC_GetMoveRelativeDistance(const char * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_MoveRelativeDistance(const char * serialNo);

	/// <summary> Get the homing parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec10 "Homing" for more detail.<remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="homingParams"> Address of the MOT_HomingParameters to recieve the homing parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestHomingParams(char const * serialNo)" />
	/// <seealso cref="BMC_GetHomingVelocity(char const * serialNo)" />
	/// <seealso cref="BMC_SetHomingVelocity(char const * serialNo, unsigned int velocity)" />
	/// <seealso cref="BMC_SetHomingParamsBlock(char const * serialNo, MOT_HomingParameters *homingParams)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_GetHomingParamsBlock(const char * serialNo, MOT_HomingParameters *homingParams);

	/// <summary> Set the homing parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec10 "Homing" for more detail.<remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="homingParams"> Address of the new homing parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestHomingParams(char const * serialNo)" />
	/// <seealso cref="BMC_GetHomingVelocity(char const * serialNo)" />
	/// <seealso cref="BMC_SetHomingVelocity(char const * serialNo, unsigned int velocity)" />
	/// <seealso cref="BMC_GetHomingParamsBlock(char const * serialNo, MOT_HomingParameters *homingParams)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_SetHomingParamsBlock(const char * serialNo, MOT_HomingParameters *homingParams);

	/// <summary> Get the jog parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">  The device serial no. </param>
	/// <param name="jogParams"> The address of the MOT_JogParameters block to recieve the jog parameters </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestJogParams(char const * serialNo)" />
	/// <seealso cref="BMC_GetJogMode(char const * serialNo, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="BMC_SetJogMode(char const * serialNo, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="BMC_GetJogStepSize(char const * serialNo)" />
	/// <seealso cref="BMC_SetJogStepSize(char const * serialNo, unsigned int stepSize)" />
	/// <seealso cref="BMC_SetJogVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="BMC_GetJogVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BMC_SetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BMC_MoveJog(char const * serialNo, MOT_TravelDirection jogDirection)" />
	/// 		  \include CodeSnippet_jogpars.cpp
	BRUSHLESSMOTOR_API short __cdecl BMC_GetJogParamsBlock(const char * serialNo, MOT_JogParameters *jogParams);

	/// <summary> Set the jog parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="jogParams"> The address of the new MOT_JogParameters block. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetJogMode(char const * serialNo, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="BMC_SetJogMode(char const * serialNo, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="BMC_GetJogStepSize(char const * serialNo)" />
	/// <seealso cref="BMC_SetJogStepSize(char const * serialNo, unsigned int stepSize)" />
	/// <seealso cref="BMC_SetJogVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="BMC_GetJogVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="BMC_GetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="BMC_MoveJog(char const * serialNo, MOT_TravelDirection jogDirection)" />
	/// 		  \include CodeSnippet_jogpars.cpp
	BRUSHLESSMOTOR_API short __cdecl BMC_SetJogParamsBlock(const char * serialNo, MOT_JogParameters *jogParams);

	// Advanced Motion Functions

	/// <summary> Requests the velocity profile parameters. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetVelocityProfileParams(const char * serialNo, MOT_VelocityProfileParameters *velocityProfileParams)" />
	/// <seealso cref="BMC_SetVelocityProfileParams(char const * serialNo, MOT_VelocityProfileParameters *velocityProfileParams)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_RequestVelocityProfileParams(char const * serialNo);

	/// <summary> Gets the velocity profile parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="velocityProfileParams"> The address of the MOT_VelocityProfileParameters parameter to receive the velocity profile options. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestVelocityProfileParams(char const * serialNo)" />
	/// <seealso cref="BMC_SetVelocityProfileParams(char const * serialNo, MOT_VelocityProfileParameters *velocityProfileParams)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_GetVelocityProfileParams(const char * serialNo, MOT_VelocityProfileParameters *velocityProfileParams);

	/// <summary> Sets the velocity profile parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="velocityProfileParams"> The address of the MOT_VelocityProfileParameters containing the new velocity profile options. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestVelocityProfileParams(char const * serialNo)" />
	/// <seealso cref="BMC_GetVelocityProfileParams(char const * serialNo, MOT_VelocityProfileParameters *velocityProfileParams)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_SetVelocityProfileParams(const char * serialNo, MOT_VelocityProfileParameters *velocityProfileParams);

	/// <summary> Requests the stage axis parameters. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetStageAxisParams(char const * serialNo, WORD *stageID, WORD *axisID, char * partNumber, DWORD size, DWORD *serialNumber, DWORD *countsPerUnit, int *minPosition, int *maxPosition, int *maxAcceleration, int *maxDecceleration, int *maxVelocity)" />
	/// <seealso cref="BMC_GetStageAxisMinPos(char const * serialNo)" />
	/// <seealso cref="BMC_GetStageAxisMaxPos(char const * serialNo)" />
	/// <seealso cref="BMC_GetStageAxisParamsBlock(const char * serialNo, MOT_StageAxisParameters *stageAxisParams)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_RequestStageAxisParams(char const * serialNo);

	/// <summary> Gets the Brushless Motor stage axis parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="stageAxisParams"> The address of the MOT_StageAxisParameters to receive the velocity stage axis parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestStageAxisParams(char const * serialNo)" />
	/// <seealso cref="BMC_GetStageAxisParams(char const * serialNo, WORD *stageID, WORD *axisID, char * partNumber, DWORD size, DWORD *serialNumber, DWORD *countsPerUnit, int *minPosition, int *maxPosition, int *maxAcceleration, int *maxDecceleration, int *maxVelocity)" />
	/// <seealso cref="BMC_GetStageAxisMinPos(char const * serialNo)" />
	/// <seealso cref="BMC_GetStageAxisMaxPos(char const * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_GetStageAxisParamsBlock(const char * serialNo, MOT_StageAxisParameters *stageAxisParams);

	/// <summary> Gets the Brushless Motor stage axis parameters. </summary>
	/// <param name="serialNo">			 The device serial no. </param>
	/// <param name="stageID">			 Address of the parameter to recieve the stage ID. </param>
	/// <param name="axisID">			 Address of the parameter to recieve the axis ID. </param>
	/// <param name="partNumber">		 Address of the parameter to recieve the part number. </param>
	/// <param name="size">				 Address of the parameter to recieve the size of part number string. </param>
	/// <param name="serialNumber">	 Address of the parameter to recieve the serial number. </param>
	/// <param name="countsPerUnit">    Address of the parameter to recieve the encoder counts per mm or degree. </param>
	/// <param name="minPosition">			 Address of the parameter to recieve the minimum position in encoder counts. </param>
	/// <param name="maxPosition">			 Address of the parameter to recieve the maximum position in encoder counts. </param>
	/// <param name="maxAcceleration">  Address of the parameter to recieve the maximum acceleration in encoder counts per cycle per cycle. </param>
	/// <param name="maxDecceleration"> Address of the parameter to recieve the maximum decceleration in encoder counts per cycle per cycle. </param>
	/// <param name="maxVelocity">		 Address of the parameter to recieve the maximum velocity in encoder counts per cycle. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestStageAxisParams(char const * serialNo)" />
	/// <seealso cref="BMC_GetStageAxisParamsBlock(char const * serialNo, MOT_StageAxisParameters *stageAxisParams)" />
	/// <seealso cref="BMC_GetStageAxisMinPos(char const * serialNo)" />
	/// <seealso cref="BMC_GetStageAxisMaxPos(char const * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_GetStageAxisParams(const char * serialNo, WORD *stageID, WORD *axisID, char * partNumber, DWORD size, DWORD *serialNumber, DWORD *countsPerUnit, int *minPosition, int *maxPosition, int *maxAcceleration, int *maxDecceleration, int *maxVelocity);

	/// <summary> Gets the Brushless Motor stage axis minimum position. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The Minimum position in \ref DeviceUnits_page. </returns>
	/// <seealso cref="BMC_RequestStageAxisParams(char const * serialNo)" />
	/// <seealso cref="BMC_GetStageAxisParamsBlock(char const * serialNo, MOT_StageAxisParameters *stageAxisParams)" />
	/// <seealso cref="BMC_GetStageAxisParams(char const * serialNo, WORD *stageID, WORD *axisID, char * partNumber, DWORD size, DWORD *serialNumber, DWORD *countsPerUnit, int *minPosition, int *maxPosition, int *maxAcceleration, int *maxDecceleration, int *maxVelocity)" />
	/// <seealso cref="BMC_GetStageAxisMaxPos(char const * serialNo)" />
	/// <seealso cref="BMC_SetStageAxisLimits(char const * serialNo, int minPosition, int maxPosition)" />
	BRUSHLESSMOTOR_API int __cdecl BMC_GetStageAxisMinPos(char const * serialNo);

	/// <summary> Gets the Brushless Motor stage axis maximum position. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The Maximum position in \ref DeviceUnits_page. </returns>
	/// <seealso cref="BMC_RequestStageAxisParams(char const * serialNo)" />
	/// <seealso cref="BMC_GetStageAxisParamsBlock(char const * serialNo, MOT_StageAxisParameters *stageAxisParams)" />
	/// <seealso cref="BMC_GetStageAxisParams(char const * serialNo, WORD *stageID, WORD *axisID, char * partNumber, DWORD size, DWORD *serialNumber, DWORD *countsPerUnit, int *minPosition, int *maxPosition, int *maxAcceleration, int *maxDecceleration, int *maxVelocity)" />
	/// <seealso cref="BMC_GetStageAxisMinPos(char const * serialNo)" />
	/// <seealso cref="BMC_SetStageAxisLimits(char const * serialNo, int minPosition, int maxPosition)" />
	BRUSHLESSMOTOR_API int __cdecl BMC_GetStageAxisMaxPos(char const * serialNo);

	/// <summary> Sets the stage axis position limits. </summary>
	/// <remarks> This function sets the limits of travel for the stage.<Br />
	/// 		  The implementation will depend upon the nature of the travel being requested and the Soft Limits mode which can be obtained using <see cref="BMC_GetSoftLimitMode(char const * serialNo)" />. <Br />
	/// 		  <B>MoveAbsolute</B>, <B>MoveRelative</B> and <B>Jog (Single Step)</B> will obey the Soft Limit Mode.
	/// 		  If the target position is outside the limits then either a full move, a partial move or no move will occur.<Br />
	/// 		  <B>Jog (Continuous)</B> and <B>Move Continuous</B> will attempt to obey the limits, but as these moves rely on position information feedback from the device to detect if the travel is exceeding the limits, the device will stop, but it is likely to overshoot the limit, especially at high velocity.<Br />
	/// 		  <B>Home</B> will always ignore the software limits.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="minPosition"> Minimum position in \ref DeviceUnits_page. </param>
	/// <param name="maxPosition"> Maximum position in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestStageAxisParams(char const * serialNo)" />
	/// <seealso cref="BMC_GetStageAxisMinPos(char const * serialNo)" />
	/// <seealso cref="BMC_GetStageAxisMaxPos(char const * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_SetStageAxisLimits(char const * serialNo, int minPosition, int maxPosition);

	/// <summary> Set the motor travel mode. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="travelMode"> The travel mode.
	/// 			<list type=table>
	///					<item><term>Linear</term><term>1</term></item>
	///					<item><term>Rotational</term><term>2</term></item>
	/// 			</list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetMotorTravelMode(char const * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_SetMotorTravelMode(char const * serialNo, MOT_TravelModes travelMode);

	/// <summary> Get motor travel mode. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The travel mode.
	/// 			<list type=table>
	///					<item><term>Linear</term><term>1</term></item>
	///					<item><term>Rotational</term><term>2</term></item>
	/// 			</list> </returns>
	/// <seealso cref="BMC_SetMotorTravelMode(char const * serialNo, int travelMode)" />
	BRUSHLESSMOTOR_API MOT_TravelModes __cdecl BMC_GetMotorTravelMode(char const * serialNo);

	/// \deprecated
	/// <summary> Set the motor parameters for the Brushless Votor. </summary>
	/// <remarks> superceded by <see cref="BMC_SetMotorParamsExt(char const * serialNo, short channel, double countsPerUnit)"/> </remarks>
	/// <param name="serialNo">		 The serial no. </param>
	/// <param name="countsPerUnit"> The counts per unit.<br/>
	/// 							 The counts per unit is the conversion factor that converts \ref DeviceUnits_page to real units.<br />
	/// 							 For example with a counts per unit of 1000, 1 device unit = 0.0001mm. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetMotorParams(char const * serialNo, long *countsPerUnit)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_SetMotorParams(char const * serialNo, long countsPerUnit);

	/// \deprecated
	/// <summary> Get the motor parameters for the Brushless Votor. </summary>
	/// <remarks> superceded by <see cref="BMC_GetMotorParamsExt(char const * serialNo, double *countsPerUnit)"/> </remarks>
	/// <param name="serialNo">		 The serial no. </param>
	/// <param name="countsPerUnit"> The Address of the parameter to receive the counts per unit value.<br/>
	/// 							 The counts per unit is the conversion factor that converts \ref DeviceUnits_page to real units.<br />
	/// 							 For example with a counts per unit of 1000, 1 device unit = 0.0001mm. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_SetMotorParams(char const * serialNo, long countsPerUnit)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_GetMotorParams(char const * serialNo, long *countsPerUnit);

	/// <summary> Set the motor parameters for the Brushless Votor. </summary>
	/// <param name="serialNo">		 The serial no. </param>
	/// <param name="countsPerUnit"> The counts per unit.<br/>
	/// 							 The counts per unit is the conversion factor that converts \ref DeviceUnits_page to real units.<br />
	/// 							 For example with a counts per unit of 1000, 1 device unit = 0.0001mm. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetMotorParamsExt(char const * serialNo, long *countsPerUnit)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_SetMotorParamsExt(char const * serialNo, double countsPerUnit);

	/// <summary> Get the motor parameters for the Brushless Votor. </summary>
	/// <param name="serialNo">		 The serial no. </param>
	/// <param name="countsPerUnit"> The Address of the parameter to receive the counts per unit value.<br/>
	/// 							 The counts per unit is the conversion factor that converts \ref DeviceUnits_page to real units.<br />
	/// 							 For example with a counts per unit of 1000, 1 device unit = 0.0001mm. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_SetMotorParamsExt(char const * serialNo, long countsPerUnit)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_GetMotorParamsExt(char const * serialNo, double *countsPerUnit);

	/// \deprecated
	/// <summary> Sets the absolute maximum velocity and acceleration constants for the current stage. </summary>
	/// <remarks> These parameters are maintained for user info only and do not reflect the current stage parameters.<Br />
    ///           The absolute maximum velocity and acceleration constants are initialized from the stage settings..</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="maxVelocity">  The absolute maximum velocity in real world units. </param>
	/// <param name="maxAcceleration"> The absolute maximum acceleration in real world units. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetMotorVelocityLimits(char const * serialNo, double *maxVelocity, double *maxAcceleration)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_SetMotorVelocityLimits(char const * serialNo, double maxVelocity, double maxAcceleration);

	/// <summary> Gets the absolute maximum velocity and acceleration constants for the current stage. </summary>
	/// <remarks> These parameters are maintained for user info only and do not reflect the current stage parameters.<Br />
    ///           The absolute maximum velocity and acceleration constants are initialized from the stage settings..</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="maxVelocity">  Address of the parameter to receive the absolute maximum velocity in real world units. </param>
	/// <param name="maxAcceleration"> Address of the parameter to receive the absolute maximum acceleration in real world units. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_SetMotorVelocityLimits(char const * serialNo, double maxVelocity, double maxAcceleration)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_GetMotorVelocityLimits(char const * serialNo, double *maxVelocity, double *maxAcceleration);

	/// <summary>	Reset the rotation modes for a rotational device. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_SetRotationModes(char const * serialNo, MOT_MovementModes mode, MOT_MovementDirections direction)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_ResetRotationModes(char const * serialNo);

	/// <summary>	Set the rotation modes for a rotational device. </summary>
	/// <param name="serialNo"> The device serial no. </param>
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
	/// <seealso cref="BMC_ResetRotationModes(char const * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_SetRotationModes(char const * serialNo, MOT_MovementModes mode, MOT_MovementDirections direction);

	/// \deprecated
	/// <summary> Sets the absolute minimum and maximum travel range constants for the current stage. </summary>
	/// <remarks> These parameters are maintained for user info only and do not reflect the current travel range of the stage.<Br />
    ///           The absolute minimum and maximum travel range constants are initialized from the stage settings. These values can be adjusted to relative positions based upon the Home Offset.<Br />
    ///           <Br />
    ///           To set the working travel range of the stage use the function <see cref="BMC_SetStageAxisLimits(char const * serialNo, int minPosition, int maxPosition)" /><Br />
    ///           Use the following to convert between real worl and device units.<Br />
    ///           <see cref="BMC_GetRealValueFromDeviceUnit(char const * serialNo, int device_unit, double *real_unit, int unitType)" /><Br />
    ///           <see cref="BMC_GetDeviceUnitFromRealValue(char const * serialNo, double real_unit, int *device_unit, int unitType)" /> </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="minPosition">  The absolute minimum position in real world units. </param>
	/// <param name="maxPosition"> The absolute maximum position in real world units. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetMotorTravelLimits(char const * serialNo, double *minPosition, double *maxPosition)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_SetMotorTravelLimits(char const * serialNo, double minPosition, double maxPosition);

	/// <summary> Gets the absolute minimum and maximum travel range constants for the current stage. </summary>
	/// <remarks> These parameters are maintained for user info only and do not reflect the current travel range of the stage.<Br />
    ///           The absolute minimum and maximum travel range constants are initialized from the stage settings. These values can be adjusted to relative positions based upon the Home Offset.</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="minPosition">  Address of the parameter to receive the absolute minimum position in real world units. </param>
	/// <param name="maxPosition"> Address of the parameter to receive the absolute maximum position in real world units. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_SetMotorTravelLimits(char const * serialNo, double minPosition, double maxPosition)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_GetMotorTravelLimits(char const * serialNo, double *minPosition, double *maxPosition);

	/// <summary>	Converts a device unit to a real world unit. </summary>
	/// <param name="serialNo">   	The serial no. </param>
	/// <param name="device_unit">	The device unit. </param>
	/// <param name="real_unit">  	The real unit. </param>
	/// <param name="unitType">   	Type of the unit.<list type=table>
	///								<item><term>Distance</term><term>0</term></item>
	///								<item><term>Velocity</term><term>1</term></item>
	///								<item><term>Acceleration</term><term>2</term></item>
	/// 						  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetDeviceUnitFromRealValue(char const * serialNo, double real_unit, int *device_unit, int unitType)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_GetRealValueFromDeviceUnit(char const * serialNo, int device_unit, double *real_unit, int unitType);

	/// <summary>	Converts a device unit to a real world unit. </summary>
	/// <param name="serialNo">   	The serial no. </param>
	/// <param name="device_unit">	The device unit. </param>
	/// <param name="real_unit">  	The real unit. </param>
	/// <param name="unitType">   	Type of the unit.<list type=table>
	///								<item><term>Distance</term><term>0</term></item>
	///								<item><term>Velocity</term><term>1</term></item>
	///								<item><term>Acceleration</term><term>2</term></item>
	/// 						  </list> </param>
	/// <returns>	Success. </returns>
	/// <seealso cref="BMC_GetRealValueFromDeviceUnit(char const * serialNo, int device_unit, double *real_unit, int unitType)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_GetDeviceUnitFromRealValue(char const * serialNo, double real_unit, int *device_unit, int unitType);

	/// <summary> Requests the position feedback loop parameters. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetPosLoopParams(const char * serialNo, MOT_PosLoopParameters *PosLoopParams)" />
	/// <seealso cref="BMC_SetPosLoopParams(char const * serialNo, MOT_PosLoopParameters *PosLoopParams)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_RequestPosLoopParams(char const * serialNo);

	/// <summary> Gets the position feedback loop parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="positionLoopParams"> The address of the MOT_BrushlessPositionLoopParameters parameter to receive the  position feedback options. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestPosLoopParams(char const * serialNo)" />
	/// <seealso cref="BMC_SetPosLoopParams(char const * serialNo, MOT_BrushlessPositionLoopParameters *positionLoopParams)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_GetPosLoopParams(const char * serialNo, MOT_BrushlessPositionLoopParameters *positionLoopParams);

	/// <summary> Sets the position feedback loop parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="positionLoopParams"> The address of the MOT_BrushlessPositionLoopParameters containing the new  position feedback options. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestPosLoopParams(char const * serialNo)" />
	/// <seealso cref="BMC_GetPosLoopParams(char const * serialNo, MOT_BrushlessPositionLoopParameters *positionLoopParams)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_SetPosLoopParams(const char * serialNo, MOT_BrushlessPositionLoopParameters *positionLoopParams);

	/// <summary> Requests the track settled parameters used to decide when settled at right position. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetTrackSettleParams(char const * serialNo, MOT_BrushlessTrackSettleParameters *settleParams)" />
	/// <seealso cref="BMC_SetTrackSettleParams(char const * serialNo, MOT_BrushlessTrackSettleParameters *settleParams)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_RequestTrackSettleParams(const char * serialNo);

	/// <summary> Gets the track settled parameters used to decide when settled at right position. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="settleParams"> The address of the MOT_BrushlessTrackSettleParameters parameter to receive the track settled parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestTrackSettleParams(char const * serialNo)" />
	/// <seealso cref="BMC_SetTrackSettleParams(char const * serialNo, MOT_BrushlessTrackSettleParameters *settleParams)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_GetTrackSettleParams(const char * serialNo, MOT_BrushlessTrackSettleParameters *settleParams);

	/// <summary> Sets the track settled parameters used to decide when settled at right position. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="settleParams"> The address of the MOT_BrushlessTrackSettleParameters containing the new track settled parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestTrackSettleParams(char const * serialNo)" />
	/// <seealso cref="BMC_GetTrackSettleParams(char const * serialNo, MOT_BrushlessTrackSettleParameters *settleParams)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_SetTrackSettleParams(const char * serialNo, MOT_BrushlessTrackSettleParameters *settleParams);

	/// <summary> Requests the current loop parameters for moving to required position. </summary>
	/// <remarks> Not supported by KVC type controller.</remarks>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetCurrentLoopParams(const char * serialNo, MOT_CurrentLoopParameters *CurrentLoopParams)" />
	/// <seealso cref="BMC_SetCurrentLoopParams(char const * serialNo, MOT_CurrentLoopParameters *CurrentLoopParams)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_RequestCurrentLoopParams(char const * serialNo);

	/// <summary> Gets the current loop parameters for moving to required position. </summary>
	/// <remarks> Not supported by KVC type controller.</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="currentLoopParams"> The address of the MOT_BrushlessCurrentLoopParameters parameter to receive the current loop parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestCurrentLoopParams(char const * serialNo)" />
	/// <seealso cref="BMC_SetCurrentLoopParams(char const * serialNo, MOT_BrushlessCurrentLoopParameters *currentLoopParams)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_GetCurrentLoopParams(const char * serialNo, MOT_BrushlessCurrentLoopParameters *currentLoopParams);

	/// <summary> Sets the current loop parameters for moving to required position. </summary>
	/// <remarks> Not supported by KVC type controller.</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="currentLoopParams"> The address of the MOT_BrushlessCurrentLoopParameters containing the new current loop parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestCurrentLoopParams(char const * serialNo)" />
	/// <seealso cref="BMC_GetCurrentLoopParams(char const * serialNo, MOT_BrushlessCurrentLoopParameters *currentLoopParams)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_SetCurrentLoopParams(const char * serialNo, MOT_BrushlessCurrentLoopParameters *currentLoopParams);

	/// <summary> Requests the electric output parameters. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetElectricOutputParams(const char * serialNo, MOT_ElectricOutputParameters *ElectricOutputParams)" />
	/// <seealso cref="BMC_SetElectricOutputParams(char const * serialNo, MOT_ElectricOutputParameters *ElectricOutputParams)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_RequestElectricOutputParams(char const * serialNo);

	/// <summary> Gets the electric output parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="electricOutputParams"> The address of the MOT_BrushlessElectricOutputParameters parameter to receive the electric output parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestElectricOutputParams(char const * serialNo)" />
	/// <seealso cref="BMC_SetElectricOutputParams(char const * serialNo, MOT_BrushlessElectricOutputParameters *electricOutputParams)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_GetElectricOutputParams(const char * serialNo, MOT_BrushlessElectricOutputParameters *electricOutputParams);

	/// <summary> Sets the electric output parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="electricOutputParams"> The address of the MOT_BrushlessElectricOutputParameters containing the new electric output parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestElectricOutputParams(char const * serialNo)" />
	/// <seealso cref="BMC_GetElectricOutputParams(char const * serialNo, MOT_BrushlessElectricOutputParameters *electricOutputParams)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_SetElectricOutputParams(const char * serialNo, MOT_BrushlessElectricOutputParameters *electricOutputParams);

	/// <summary> Requests the trigger switch bits. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetTriggerSwitches(const char * serialNo)" />
	/// <seealso cref="BMC_SetTriggerSwitches(char const * serialNo, byte indicatorBits)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_RequestTriggerSwitches(char const * serialNo);

	/// <summary> Gets the trigger switch bits. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> 8 bits indicating action on trigger input and events to trigger electronic output. </returns>
	/// <seealso cref="BMC_RequestTriggerSwitches(char const * serialNo)" />
	/// <seealso cref="BMC_SetTriggerSwitches(char const * serialNo, byte indicatorBits)" />
	BRUSHLESSMOTOR_API byte __cdecl BMC_GetTriggerSwitches(char const * serialNo);

	/// <summary> Sets the trigger switch bits. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="indicatorBits"> Sets the 8 bits indicating action on trigger input and events to trigger electronic output. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_RequestTriggerSwitches(char const * serialNo)" />
	/// <seealso cref="BMC_GetTriggerSwitches(char const * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_SetTriggerSwitches(char const * serialNo, byte indicatorBits);


	/// <summary> Suspend automatic messages at ends of moves. </summary>
	/// <remarks> Useful to speed up part of real-time system with lots of short moves. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_ResumeMoveMessages(char const * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_SuspendMoveMessages(char const * serialNo);

	/// <summary> Resume suspended move messages. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_SuspendMoveMessages(char const * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_ResumeMoveMessages(char const * serialNo);

	/// <summary> Requests the current position. </summary>
	/// <remarks> This needs to be called to get the device to send it's current position.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="BMC_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// 		  \include CodeSnippet_move.cpp
	/// <seealso cref="BMC_GetPosition(char const * serialNo)" />
	/// <seealso cref="BMC_StartPolling(char const * serialNo, int milliseconds)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_RequestPosition(char const * serialNo);

	/// <summary> Request the status bits which identify the current motor state. </summary>
	/// <remarks> This needs to be called to get the device to send it's current status bits.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="BMC_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="BMC_GetStatusBits(char const * serialNo)" />
	/// <seealso cref="BMC_StartPolling(char const * serialNo, int milliseconds)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_RequestStatusBits(char const * serialNo);

	/// <summary>Get the current status bits. </summary>
	/// <remarks> This returns the latest status bits received from the device.<br />
	/// 		  To get new status bits, use <see cref="BMC_RequestStatusBits(char const * serialNo)" />
	/// 		  or use the polling functions, <see cref="BMC_StartPolling(char const * serialNo, int milliseconds)" />.  </remarks>
	/// <param name="serialNo">	The device serial no. </param>
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
	/// <seealso cref="BMC_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="BMC_StartPolling(char const * serialNo, int milliseconds)" />
	BRUSHLESSMOTOR_API DWORD __cdecl BMC_GetStatusBits(char const * serialNo);

	/// <summary> Starts the internal polling loop which continuously requests position and status. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="milliseconds">The milliseconds polling rate. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="BMC_StopPolling(char const * serialNo)" />
	/// <seealso cref="BMC_PollingDuration(char const * serialNo)" />
	/// <seealso cref="BMC_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="BMC_RequestPosition(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	BRUSHLESSMOTOR_API bool __cdecl BMC_StartPolling(char const * serialNo, int milliseconds);

	/// <summary> Gets the polling loop duration. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The time between polls in milliseconds or 0 if polling is not active. </returns>
	/// <seealso cref="BMC_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="BMC_StopPolling(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	BRUSHLESSMOTOR_API long __cdecl BMC_PollingDuration(char const * serialNo);

	/// <summary> Stops the internal polling loop. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <seealso cref="BMC_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="BMC_PollingDuration(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	BRUSHLESSMOTOR_API void __cdecl BMC_StopPolling(char const * serialNo);

	/// <summary> Gets the time in milliseconds since tha last message was received from the device. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="lastUpdateTimeMS"> The time since the last message was received in milliseconds. </param>
	/// <returns> True if monitoring is enabled otherwize False. </returns>
	/// <seealso cref="BMC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// <seealso cref="BMC_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	BRUSHLESSMOTOR_API bool __cdecl BMC_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS);

	/// <summary> Enables the last message monitoring timer. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="enable"> True to enable monitoring otherwise False to disable. </param>
	/// <param name="lastMsgTimeout"> The last message error timeout in ms. 0 to disable. </param>
	/// <seealso cref="BMC_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="BMC_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	BRUSHLESSMOTOR_API void __cdecl BMC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout);

	/// <summary> Queries if the time since the last message has exceeded the lastMsgTimeout set by <see cref="BMC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )"/>. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> True if last message timer has elapsed, False if monitoring is not enabled or if time of last message received is less than lastMsgTimeout. </returns>
	/// <seealso cref="BMC_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="BMC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	BRUSHLESSMOTOR_API bool __cdecl BMC_HasLastMsgTimerOverrun(char const * serialNo);

	/// <summary> Requests that all settings are download from device. </summary>
	/// <remarks> This function requests that the device upload all it's settings to the DLL.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	BRUSHLESSMOTOR_API short __cdecl BMC_RequestSettings(char const * serialNo);

	/// <summary> Requests the digital output bits. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_SetDigitalOutputs(char const * serialNo, byte outputsBits)" />
	/// <seealso cref="BMC_GetDigitalOutputs(char const * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_RequestDigitalOutputs(char const * serialNo);

	/// <summary> Gets the digital output bits. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> Bit mask of states of the 4 digital output pins. </returns>
	/// <seealso cref="BMC_SetDigitalOutputs(char const * serialNo, byte outputsBits)" />
	/// <seealso cref="BMC_RequestDigitalOutputs(char const * serialNo)" />
	BRUSHLESSMOTOR_API byte __cdecl BMC_GetDigitalOutputs(char const * serialNo);

	/// <summary> Sets the digital output bits. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="outputsBits"> Bit mask to set states of the 4 digital output pins. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="BMC_GetDigitalOutputs(char const * serialNo)" />
	/// <seealso cref="BMC_RequestDigitalOutputs(char const * serialNo)" />
	BRUSHLESSMOTOR_API short __cdecl BMC_SetDigitalOutputs(char const * serialNo, byte outputsBits);

	/// <summary> Requests the scan move parameters. </summary>
	/// <remarks> Only supported by KVC type controller currently.</remarks>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BRUSHLESSMOTOR_API  short __cdecl BMC_RequestScanMoveParams(char const* serialNo);

	/// <summary> Gets the scan move parameters </summary>
	/// <remarks> Only supported by KVC type controller currently.</remarks>
	/// <param name="serialNo">    The serial no. </param>
	/// <param name="scanMoveParams"> [in,out] the scan move parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BRUSHLESSMOTOR_API  short __cdecl BMC_GetScanMoveParams(const char* serialNo, MOT_ScanMoveParams& scanMoveParams);

	/// <summary> Sets the scan move parameters. </summary>
	/// <remarks> Only supported by KVC type controller currently.</remarks>
	/// <param name="serialNo">    The serial no. </param>
	/// <param name="scanMoveParams"> [in,out] the scan move parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BRUSHLESSMOTOR_API  short __cdecl BMC_SetScanMoveParams(const char* serialNo, MOT_ScanMoveParams& scanMoveParams);

	/// <summary> Start the scan move. </summary>
	/// <remarks> Only supported by KVC type controller currently.</remarks>
	/// <param name="serialNo">    The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BRUSHLESSMOTOR_API  short __cdecl BMC_StartScanMove(const char* serialNo);

	/// <summary> Stop the scan move. </summary>
	/// <remarks> Only supported by KVC type controller currently.</remarks>
	/// <param name="serialNo">    The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BRUSHLESSMOTOR_API  short __cdecl BMC_StopScanMove(const char* serialNo);


	/// <summary> Requests the Analog IO config parameters. </summary>
	/// <remarks> Only supported by KVC type controller currently.</remarks>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BRUSHLESSMOTOR_API  short __cdecl BMC_RequestAnalogIOConfigParams(char const* serialNo);

	/// <summary> Gets the Analog IO config parameters </summary>
	/// <remarks> Only supported by KVC type controller currently.</remarks>
	/// <param name="serialNo">    The serial no. </param>
	/// <param name="AnalogIOConfigParams"> [in,out] the Analog IO config parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BRUSHLESSMOTOR_API  short __cdecl BMC_GetAnalogIOConfigParams(const char* serialNo, MOT_AnalogIOConfigParams& AnalogIOConfigParams);

	/// <summary> Sets the Analog IO config parameters. </summary>
	/// <remarks> Only supported by KVC type controller currently.</remarks>
	/// <param name="serialNo">    The serial no. </param>
	/// <param name="AnalogIOConfigParams"> [in,out] the Analog IO config parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BRUSHLESSMOTOR_API  short __cdecl BMC_SetAnalogIOConfigParams(const char* serialNo, MOT_AnalogIOConfigParams& AnalogIOConfigParams);

	/// <summary> Sets the Analog Input config mode. </summary>
	/// <remarks> Only supported by KVC type controller currently.</remarks>
	/// <param name="serialNo">    The serial no. </param>
	/// <param name="modes"> The Analog Input Mode. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BRUSHLESSMOTOR_API  short __cdecl BMC_SetAnalogInputMode(const char* serialNo, MOT_AnalogInputMode mode);

	/// <summary> Requests the Analog input parameters. </summary>
	/// <remarks> Only supported by KVC type controller currently.</remarks>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BRUSHLESSMOTOR_API  short __cdecl BMC_RequestAnalogInputParams(char const* serialNo);

	/// <summary> Gets the Analog input parameters </summary>
	/// <remarks> Only supported by KVC type controller currently.</remarks>
	/// <param name="serialNo">    The serial no. </param>
	/// <param name="AnalogInputParams"> [in,out] the Analog input parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	BRUSHLESSMOTOR_API  short __cdecl BMC_GetAnalogInputParams(const char* serialNo, MOT_AnalogInputParams& AnalogInputParams);
}
/** @} */ // KCubeBrushlessMotor
