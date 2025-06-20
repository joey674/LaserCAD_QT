// summary:	Declares the cube class
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the KCUBEDCSERVO_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// KCUBEDCSERVO_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#pragma once

#ifdef KCUBEDCSERVODLL_EXPORTS
#define KCUBEDCSERVO_API __declspec(dllexport)
#else
#define KCUBEDCSERVO_API __declspec(dllimport)
#endif

#include <OaIdl.h>

extern "C"
{


/** @defgroup KCubeDCServo KCube DCServo
 *  This section details the Structures and Functions relavent to the  @ref KDC101_page "KCube DC Motor Controller"<br />
 *  For an example of how to connect to the device and perform simple operations use the following links:
 *  <list type=bullet>
 *    <item> \ref namespaces_kdc_ex_1 "Example of using the Thorlabs.MotionControl.KCube.DCServo.DLL from a C or C++ project."<br />
 *									  This requires the DLL to be dynamical linked. </item>
 *    <item> \ref namespaces_kdc_ex_2 "Example of using the Thorlabs.MotionControl.KCube.DCServo.DLL from a C# project"<br />
 *									  This uses Marshalling to load and access the C DLL. </item>
 *  </list>
 *  The Thorlabs.MotionControl.KCube.DCServo.DLL requires the following DLLs
 *  <list type=bullet>
 *    <item> Thorlabs.MotionControl.DeviceManager. </item>
 *  </list>
 *  @{
 */

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
		MOT_Backwards = 0x02,///<Move in a Backward / Reverse direction
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
		MOT_Reverse = 0x01,///<Move / Jog direction is reversed (anti clockwise).
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
		KMOT_TrigIn_GPI = 0x01,///< General purpose logic input (<see cref="CC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)
		KMOT_TrigIn_RelativeMove = 0x02,///< Move relative using relative move parameters
		KMOT_TrigIn_AbsoluteMove = 0x03,///< Move absolute using absolute move parameters
		KMOT_TrigIn_Home = 0x04,///< Perform a Home action
		KMOT_TrigIn_Stop = 0x05,///< Perform a Stop Immediate action
		KMOT_TrigIn_StartScan = 0x06,///< Perform a Scan Start (on supported devices)
		KMOT_TrigIn_ShuttleMove = 0x07,///< Move shuttle using absolute move parameters (on supported devices)
		KMOT_TrigOut_GPO = 0x0A,///< General purpose output (<see cref="CC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)
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
		///				<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="CC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
		///				<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
		///				<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
		///				<item><term>4</term><term>Trigger Input - Perform a Home action</term></item>
		///				<item><term>5</term><term>Trigger Input - Perform a Stop action</term></item>
		/// 			<item><term>6</term><term>Trigger Input - Perform a Start scan move</term></item>
		/// 			<item><term>7</term><term>Trigger Input - Move shuttle using absolute move parameters</term></item>
		///				<item><term>10</term><term>Trigger Output - General purpose output (<see cref="CC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
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
		///				<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="CC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
		///				<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
		///				<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
		///				<item><term>4</term><term>Trigger Input - Perform a Home action</term></item>
		///				<item><term>5</term><term>Trigger Input - Perform a Stop action</term></item>
		/// 			<item><term>6</term><term>Trigger Input - Perform a Start scan move</term></item>
		/// 			<item><term>7</term><term>Trigger Input - Move shuttle using absolute move parameters</term></item>
		///				<item><term>10</term><term>Trigger Output - General purpose output (<see cref="CC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
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
	KCUBEDCSERVO_API short __cdecl TLI_BuildDeviceList(void);

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
	KCUBEDCSERVO_API short __cdecl TLI_GetDeviceListSize();

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
	KCUBEDCSERVO_API short __cdecl TLI_GetDeviceList(SAFEARRAY** stringsReceiver);

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
	KCUBEDCSERVO_API short __cdecl TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID);

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
	KCUBEDCSERVO_API short __cdecl TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length);

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
	KCUBEDCSERVO_API short __cdecl TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer);

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
	KCUBEDCSERVO_API short __cdecl TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID);

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
	KCUBEDCSERVO_API short __cdecl TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length);

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
	KCUBEDCSERVO_API short __cdecl TLI_GetDeviceInfo(char const * serialNo, TLI_DeviceInfo *info);

	/// <summary> Initialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <remarks> Call TLI_InitializeSimulations before TLI_BuildDeviceList at the start of the program to make a connection to the simulation manager.<Br />
	/// 		  Any devices configured in the simulation manager will become visible TLI_BuildDeviceList is called and can be accessed using TLI_GetDeviceList.<Br />
	/// 		  Call TLI_InitializeSimulations at the end of the program to release the simulator.  </remarks>
	/// <seealso cref="TLI_UninitializeSimulations()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	KCUBEDCSERVO_API void __cdecl TLI_InitializeSimulations();

	/// <summary> Uninitialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <seealso cref="TLI_InitializeSimulations()" />
	KCUBEDCSERVO_API void __cdecl TLI_UninitializeSimulations();

	/// <summary> Open the device for communications. </summary>
	/// <param name="serialNo">	The serial no of the device to be connected. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="CC_Close(char const * serialNo)" />
	KCUBEDCSERVO_API short __cdecl CC_Open(char const * serialNo);

	/// <summary> Disconnect and close the device. </summary>
	/// <param name="serialNo">	The serial no of the device to be disconnected. </param>
	/// 		  \include CodeSnippet_connection1.cpp
	/// <seealso cref="CC_Open(char const * serialNo)" />
	KCUBEDCSERVO_API void __cdecl CC_Close(char const * serialNo);

	/// <summary>	Check connection. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> true if the USB is listed by the ftdi controller</returns>
	/// \include CodeSnippet_CheckConnection.cpp
	KCUBEDCSERVO_API bool __cdecl CC_CheckConnection(char const * serialNo);

	/// <summary> Sends a command to the device to make it identify iteself. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	KCUBEDCSERVO_API void __cdecl CC_Identify(char const * serialNo);

	/// <summary> Request the LED indicator bits on cube. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetLEDswitches(char const * serialNo)" />
	/// <seealso cref="CC_SetLEDswitches(char const * serialNo, WORD LEDswitches)" />
	KCUBEDCSERVO_API short __cdecl CC_RequestLEDswitches(char const * serialNo);

	/// <summary> Get the LED indicator bits on cube. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> Sum of: 8 to indicate moving 2 to indicate end of track and 1 to flash on identify command. </returns>
	/// <seealso cref="CC_RequestLEDswitches(char const * serialNo)" />
	/// <seealso cref="CC_SetLEDswitches(char const * serialNo, WORD LEDswitches)" />
	KCUBEDCSERVO_API WORD __cdecl CC_GetLEDswitches(char const * serialNo);

	/// <summary> Set the LED indicator bits on cube. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="LEDswitches"> Sum of: 8 to indicate moving 2 to indicate end of track and 1 to flash on identify command. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_RequestLEDswitches(char const * serialNo)" />
	/// <seealso cref="CC_GetLEDswitches(char const * serialNo)" />
	KCUBEDCSERVO_API short __cdecl CC_SetLEDswitches(char const * serialNo, WORD LEDswitches);

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
	KCUBEDCSERVO_API short __cdecl CC_GetHardwareInfo(char const * serialNo, char * modelNo, DWORD sizeOfModelNo, WORD * type, WORD * numChannels,
		char * notes, DWORD sizeOfNotes, DWORD * firmwareVersion, WORD * hardwareVersion, WORD * modificationState);

	/// <summary> Gets the hardware information in a block. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="hardwareInfo"> Address of a TLI_HardwareInformation structure to receive the hardware information. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// 		  \include CodeSnippet_identify.cpp
	KCUBEDCSERVO_API short __cdecl CC_GetHardwareInfoBlock(char const * serialNo, TLI_HardwareInformation *hardwareInfo);

	/// <summary> Gets the hub bay number this device is fitted to. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The number, 0x00 if unknown or 0xff if not on a hub. </returns>
	KCUBEDCSERVO_API char __cdecl CC_GetHubBay(char const * serialNo);

	/// <summary> Gets version number of the device software. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device software version number made up of 4 byte parts. </returns>
	/// 		  \include CodeSnippet_identify.cpp
	KCUBEDCSERVO_API DWORD __cdecl CC_GetSoftwareVersion(char const * serialNo);

	/// <summary> Update device with stored settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// 		  \include CodeSnippet_connection1.cpp
	KCUBEDCSERVO_API bool __cdecl CC_LoadSettings(char const * serialNo);

	/// <summary> Update device with named settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="settingsName"> Name of settings stored away from device. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	///             \include CodeSnippet_connection1.cpp
	KCUBEDCSERVO_API bool __cdecl CC_LoadNamedSettings(char const * serialNo, char const *settingsName);

	/// <summary> Update device with stored settings. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	KCUBEDCSERVO_API bool __cdecl CC_PersistSettings(char const * serialNo);

	/// <summary> Reset the stage settings to defaults. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	KCUBEDCSERVO_API short __cdecl CC_ResetStageToDefaults(char const * serialNo);

	/// <summary> Disable the channel so that motor can be moved by hand. </summary>
	/// <remarks> When disabled power is removed from the motor and it can be freely moved.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_EnableChannel(char const * serialNo)" />
	KCUBEDCSERVO_API short __cdecl CC_DisableChannel(char const * serialNo);

	/// <summary> Enable channel for computer control. </summary>
	/// <remarks> When enabled power is applied to the motor so it is fixed in position.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_DisableChannel(char const * serialNo)" />
	KCUBEDCSERVO_API short __cdecl CC_EnableChannel(char const * serialNo);

	/// <summary> Determine if the device front panel can be locked. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> True if we can lock the device front panel, false if not. </returns>
	/// <seealso cref="CC_GetFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="CC_RequestFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="CC_SetFrontPanelLock(char const * serialNo, bool locked)" />
	KCUBEDCSERVO_API bool __cdecl CC_CanDeviceLockFrontPanel(char const * serialNo);

	/// <summary> Query if the device front panel locked. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> True if the device front panel is locked, false if not. </returns>
	/// <seealso cref="CC_CanDeviceLockFrontPanel(char const * serialNo)" />
	/// <seealso cref="CC_RequestFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="CC_SetFrontPanelLock(char const * serialNo, bool locked)" />
	KCUBEDCSERVO_API bool __cdecl  CC_GetFrontPanelLocked(char const * serialNo);

	/// <summary> Ask the device if its front panel is locked. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_CanDeviceLockFrontPanel(char const * serialNo)" />
	/// <seealso cref="CC_GetFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="CC_SetFrontPanelLock(char const * serialNo, bool locked)" />
	KCUBEDCSERVO_API short __cdecl  CC_RequestFrontPanelLocked(char const * serialNo);

	/// <summary> Sets the device front panel lock state. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="locked"> True to lock the device, false to unlock. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_CanDeviceLockFrontPanel(char const * serialNo)" />
	/// <seealso cref="CC_GetFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="CC_RequestFrontPanelLocked(char const * serialNo)" />
	KCUBEDCSERVO_API short __cdecl  CC_SetFrontPanelLock(char const * serialNo, bool locked);

	/// <summary> Get number of positions. </summary>
	/// <remarks> The GetNumberPositions function will get the maximum position reachable by the device.<br />
	/// 		  The motor may need to be \ref C_MOTOR_sec10 "Homed" before this parameter can be used. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The number of positions. </returns>
	/// <seealso cref="CC_MoveToPosition(char const * serialNo, int index)" />
	/// <seealso cref="CC_GetPosition(char const * serialNo)" />
	/// <seealso cref="CC_Home(char const * serialNo)" />
	/// 		  \include CodeSnippet_move.cpp
	KCUBEDCSERVO_API int __cdecl CC_GetNumberPositions(char const * serialNo);

	/// <summary> Move the device to the specified position (index). </summary>
	/// <remarks> The motor may need to be \ref C_MOTOR_sec10 "Homed" before a position can be set<br />
	/// 		  see \ref C_MOTOR_sec11 "Positioning" for more detail. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="index">   	The position in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if move successfully started. </returns>
	/// <seealso cref="CC_GetNumberPositions(char const * serialNo)" />
	/// <seealso cref="CC_SetVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="CC_GetPosition(char const * serialNo)" />
	/// <seealso cref="CC_GetVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="CC_GetVelParamsBlock(char const * serialNo, MOT_VelocityParameters  *velocityParams)" />
	/// <seealso cref="CC_SetVelParamsBlock(char const * serialNo, MOT_VelocityParameters *velocityParams)" />
	/// <seealso cref="CC_MoveRelative(char const * serialNo, int displacement)" />
	/// <seealso cref="CC_MoveAtVelocity(char const * serialNo, MOT_TravelDirection direction)" />
	/// 		  \include CodeSnippet_move.cpp
	KCUBEDCSERVO_API short __cdecl CC_MoveToPosition(char const * serialNo, int index);

	/// <summary> Get the current position. </summary>
	/// <remarks> The current position is the last recorded position.<br />
	/// 		  The current position is updated either by the polling mechanism or<br />
	/// 		  by calling <see cref="RequestPosition" /> or <see cref="RequestStatus" />.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The current position in \ref DeviceUnits_page. </returns>
	/// <seealso cref="CC_GetNumberPositions(char const * serialNo)" />
	/// <seealso cref="CC_MoveToPosition(char const * serialNo, int index)" />
	/// <seealso cref="CC_Home(char const * serialNo)" />
	/// 		  \include CodeSnippet_move.cpp
	KCUBEDCSERVO_API int __cdecl CC_GetPosition(char const * serialNo);

	/// <summary> Can the device perform a Home. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> <c>true</c> if the device can home. </returns>
	KCUBEDCSERVO_API bool __cdecl CC_CanHome(char const * serialNo);

	/// \deprecated
	/// <summary> Does the device need to be Homed before a move can be performed. </summary>
	/// <remarks> superceded by <see cref="CC_CanMoveWithoutHomingFirst(char const * serialNo)"/> </remarks>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> <c>true</c> if the device needs homing. </returns>
	KCUBEDCSERVO_API bool __cdecl CC_NeedsHoming(char const * serialNo);

	/// <summary> Can this device be moved without Homing. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> <c>true</c> if the device does not need to be homed before a move can be commanded. </returns>
	KCUBEDCSERVO_API bool __cdecl CC_CanMoveWithoutHomingFirst(char const * serialNo);

	/// <summary> Home the device. </summary>
	/// <remarks> Homing the device will set the device to a known state and determine the home position,<br />
	/// 		  see \ref C_MOTOR_sec10 "Homing" for more detail. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if move successfully started. </returns>
	/// <seealso cref="CC_GetNumberPositions(char const * serialNo)" />
	/// <seealso cref="CC_MoveToPosition(char const * serialNo, int index)" />
	/// <seealso cref="CC_GetPosition(char const * serialNo)" />
	/// 		  \include CodeSnippet_move.cpp
	KCUBEDCSERVO_API short __cdecl CC_Home(char const * serialNo);

	/// <summary> Clears the device message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	KCUBEDCSERVO_API void __cdecl CC_ClearMessageQueue(char const * serialNo);

	/// <summary> Registers a callback on the message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="functionPointer"> A function pointer to be called whenever messages are received. </param>
	/// <seealso cref="CC_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="CC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="CC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KCUBEDCSERVO_API void __cdecl CC_RegisterMessageCallback(char const * serialNo, void(*functionPointer)());

	/// <summary> Gets the MessageQueue size. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> number of messages in the queue. </returns>
	/// <seealso cref="CC_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="CC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	/// <seealso cref="CC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KCUBEDCSERVO_API int __cdecl CC_MessageQueueSize(char const * serialNo);

	/// <summary> Get the next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="CC_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="CC_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="CC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KCUBEDCSERVO_API bool __cdecl CC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Wait for next MessageQueue item. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> The address of the parameter to receive the message Type. </param>
	/// <param name="messageID">   The address of the parameter to receive the message id. </param>
	/// <param name="messageData"> The address of the parameter to receive the message data. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="CC_RegisterMessageCallback(char const * serialNo, void (* functionPointer)())" />
	/// <seealso cref="CC_MessageQueueSize(char const * serialNo)" />
	/// <seealso cref="CC_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData)" />
	KCUBEDCSERVO_API bool __cdecl CC_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Requests the homing parameters. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetHomingVelocity(char const * serialNo)" />
	/// <seealso cref="CC_GetHomingParamsBlock(char const * serialNo, MOT_HomingParameters *homingParams)" />
	KCUBEDCSERVO_API short __cdecl CC_RequestHomingParams(char const * serialNo);

	/// <summary> Gets the homing velocity. </summary>
	/// <remarks> see \ref C_MOTOR_sec10 "Homing" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The homing velocity in \ref DeviceUnits_page. </returns>
	/// <seealso cref="CC_RequestHomingParams(char const * serialNo)" />
	/// <seealso cref="CC_SetHomingVelocity(char const * serialNo, unsigned int velocity)" />
	/// <seealso cref="CC_GetHomingParamsBlock(char const * serialNo, MOT_HomingParameters *homingParams)" />
	/// <seealso cref="CC_SetHomingParamsBlock(char const * serialNo, MOT_HomingParameters *homingParams)" />
	KCUBEDCSERVO_API unsigned int __cdecl CC_GetHomingVelocity(char const * serialNo);

	/// <summary> Sets the homing velocity. </summary>
	/// <remarks> see \ref C_MOTOR_sec10 "Homing" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="velocity"> The homing velocity in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_RequestHomingParams(char const * serialNo)" />
	/// <seealso cref="CC_GetHomingVelocity(char const * serialNo)" />
	/// <seealso cref="CC_GetHomingParamsBlock(char const * serialNo, MOT_HomingParameters *homingParams)" />
	/// <seealso cref="CC_SetHomingParamsBlock(char const * serialNo, MOT_HomingParameters *homingParams)" />
	KCUBEDCSERVO_API short __cdecl CC_SetHomingVelocity(char const * serialNo, unsigned int velocity);

	/// <summary> Move the motor by a relative amount. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="displacement"> Signed displacement in \ref DeviceUnits_page.</param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetNumberPositions(char const * serialNo)" />
	/// <seealso cref="CC_GetVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="CC_SetVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="CC_GetVelParamsBlock(char const * serialNo, MOT_VelocityParameters  *velocityParams)" />
	/// <seealso cref="CC_SetVelParamsBlock(char const * serialNo, MOT_VelocityParameters *velocityParams)" />
	/// <seealso cref="CC_MoveToPosition(char const * serialNo, int index)" />
	/// <seealso cref="CC_MoveAtVelocity(char const * serialNo, MOT_TravelDirection direction)" />
	/// 		  \include CodeSnippet_move.cpp
	KCUBEDCSERVO_API short __cdecl CC_MoveRelative(char const * serialNo, int displacement);

	/// <summary> Requests the jog parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetJogMode(char const * serialNo, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="CC_GetJogStepSize(char const * serialNo)" />
	/// <seealso cref="CC_GetJogVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="CC_GetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// 		  \include CodeSnippet_jogpars.cpp
	KCUBEDCSERVO_API short __cdecl CC_RequestJogParams(const char * serialNo);

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
	/// <seealso cref="CC_RequestJogParams(char const * serialNo)" />
	/// <seealso cref="CC_SetJogMode(char const * serialNo, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="CC_GetJogStepSize(char const * serialNo)" />
	/// <seealso cref="CC_SetJogStepSize(char const * serialNo, unsigned int stepSize)" />
	/// <seealso cref="CC_SetJogVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="CC_GetJogVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="CC_GetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="CC_SetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="CC_MoveJog(char const * serialNo, MOT_TravelDirection jogDirection)" />
	/// 		  \include CodeSnippet_jogpars.cpp
	KCUBEDCSERVO_API short __cdecl CC_GetJogMode(char const * serialNo, MOT_JogModes * mode, MOT_StopModes * stopMode);

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
	/// <seealso cref="CC_GetJogMode(char const * serialNo, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="CC_GetJogStepSize(char const * serialNo)" />
	/// <seealso cref="CC_SetJogStepSize(char const * serialNo, unsigned int stepSize)" />
	/// <seealso cref="CC_SetJogVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="CC_GetJogVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="CC_GetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="CC_SetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="CC_MoveJog(char const * serialNo, MOT_TravelDirection jogDirection)" />
	/// 		  \include CodeSnippet_jogpars.cpp
	KCUBEDCSERVO_API short __cdecl CC_SetJogMode(char const * serialNo, MOT_JogModes mode, MOT_StopModes stopMode);

	/// <summary> Gets the distance to move when jogging. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The step in \ref DeviceUnits_page. </returns>
	/// <seealso cref="CC_RequestJogParams(char const * serialNo)" />
	/// <seealso cref="CC_GetJogMode(char const * serialNo, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="CC_SetJogMode(char const * serialNo, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="CC_SetJogStepSize(char const * serialNo, unsigned int stepSize)" />
	/// <seealso cref="CC_SetJogVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="CC_GetJogVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="CC_GetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="CC_SetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="CC_MoveJog(char const * serialNo, MOT_TravelDirection jogDirection)" />
	/// 		  \include CodeSnippet_jogpars.cpp
	KCUBEDCSERVO_API unsigned int __cdecl CC_GetJogStepSize(char const * serialNo);

	/// <summary> Sets the distance to move on jogging. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="stepSize"> The step in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetJogMode(char const * serialNo, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="CC_SetJogMode(char const * serialNo, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="CC_GetJogStepSize(char const * serialNo)" />
	/// <seealso cref="CC_SetJogVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="CC_GetJogVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="CC_GetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="CC_SetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="CC_MoveJog(char const * serialNo, MOT_TravelDirection jogDirection)" />
	/// 		  \include CodeSnippet_jogpars.cpp
	KCUBEDCSERVO_API short __cdecl CC_SetJogStepSize(char const * serialNo, unsigned int stepSize);

	/// <summary> Gets the jog velocity parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="acceleration"> Address of the parameter to receive the acceleration in \ref DeviceUnits_page. </param>
	/// <param name="maxVelocity"> Address of the parameter to receive the velocity in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_RequestJogParams(char const * serialNo)" />
	/// <seealso cref="CC_GetJogMode(char const * serialNo, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="CC_SetJogMode(char const * serialNo, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="CC_GetJogStepSize(char const * serialNo)" />
	/// <seealso cref="CC_SetJogStepSize(char const * serialNo, unsigned int stepSize)" />
	/// <seealso cref="CC_SetJogVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="CC_GetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="CC_SetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="CC_MoveJog(char const * serialNo, MOT_TravelDirection jogDirection)" />
	/// 		  \include CodeSnippet_jogpars.cpp
	KCUBEDCSERVO_API short __cdecl CC_GetJogVelParams(char const * serialNo, int * acceleration, int * maxVelocity);

	/// <summary> Sets jog velocity parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="acceleration">   The acceleration in \ref DeviceUnits_page. </param>
	/// <param name="maxVelocity"> The maximum velocity in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetJogMode(char const * serialNo, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="CC_SetJogMode(char const * serialNo, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="CC_GetJogStepSize(char const * serialNo)" />
	/// <seealso cref="CC_SetJogStepSize(char const * serialNo, unsigned int stepSize)" />
	/// <seealso cref="CC_GetJogVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="CC_GetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="CC_SetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="CC_MoveJog(char const * serialNo, MOT_TravelDirection jogDirection)" />
	/// 		  \include CodeSnippet_jogpars.cpp
	KCUBEDCSERVO_API short __cdecl CC_SetJogVelParams(char const * serialNo, int acceleration, int maxVelocity);

	/// <summary> Perform a jog. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="jogDirection"> The jog direction
	/// 					 <list type=table>
	///							<item><term>Forwards</term><term>1</term></item>
	///							<item><term>Backwards</term><term>2</term></item>
	/// 					 </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetJogMode(char const * serialNo, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="CC_SetJogMode(char const * serialNo, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="CC_GetJogStepSize(char const * serialNo)" />
	/// <seealso cref="CC_SetJogStepSize(char const * serialNo, unsigned int stepSize)" />
	/// <seealso cref="CC_SetJogVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="CC_GetJogVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="CC_GetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="CC_SetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// 		  \include CodeSnippet_jog.cpp
	KCUBEDCSERVO_API short __cdecl CC_MoveJog(char const * serialNo, MOT_TravelDirection jogDirection);

	/// <summary> Requests the velocity parameters. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="CC_GetVelParamsBlock(char const * serialNo, MOT_VelocityParameters  *velocityParams)" />
	KCUBEDCSERVO_API short __cdecl CC_RequestVelParams(char const * serialNo);

	/// <summary> Gets the move velocity parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec11 "Positioning" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="acceleration"> Address of the parameter to receive the acceleration value in \ref DeviceUnits_page. </param>
	/// <param name="maxVelocity"> Address of the parameter to receive the maximum velocity value in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_RequestVelParams(char const * serialNo)" />
	/// <seealso cref="CC_SetVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="CC_GetVelParamsBlock(char const * serialNo, MOT_VelocityParameters  *velocityParams)" />
	/// <seealso cref="CC_SetVelParamsBlock(char const * serialNo, MOT_VelocityParameters *velocityParams)" />
	/// <seealso cref="CC_MoveToPosition(char const * serialNo, int index)" />
	/// <seealso cref="CC_MoveRelative(char const * serialNo, int displacement)" />
	/// <seealso cref="CC_MoveAtVelocity(char const * serialNo, MOT_TravelDirection direction)" />
	/// 		  \include CodeSnippet_movepars.cpp
	KCUBEDCSERVO_API short __cdecl CC_GetVelParams(char const * serialNo, int * acceleration, int * maxVelocity);

	/// <summary> Sets the move velocity parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec11 "Positioning" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="acceleration"> The new acceleration value in \ref DeviceUnits_page. </param>
	/// <param name="maxVelocity"> The new maximum velocity value in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_RequestVelParams(char const * serialNo)" />
	/// <seealso cref="CC_GetVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="CC_GetVelParamsBlock(char const * serialNo, MOT_VelocityParameters  *velocityParams)" />
	/// <seealso cref="CC_SetVelParamsBlock(char const * serialNo, MOT_VelocityParameters *velocityParams)" />
	/// <seealso cref="CC_MoveToPosition(char const * serialNo, int index)" />
	/// <seealso cref="CC_MoveRelative(char const * serialNo, int displacement)" />
	/// <seealso cref="CC_MoveAtVelocity(char const * serialNo, MOT_TravelDirection direction)" />
	/// 		  \include CodeSnippet_movepars.cpp
	KCUBEDCSERVO_API short __cdecl CC_SetVelParams(char const * serialNo, int acceleration, int maxVelocity);

	/// <summary> Start moving at the current velocity in the specified direction. </summary>
	/// <remarks> see \ref C_MOTOR_sec11 "Positioning" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="direction"> The required direction of travel.
	/// 					 <list type=table>
	///							<item><term>Forwards</term><term>1</term></item>
	///							<item><term>Backwards</term><term>2</term></item>
	/// 					 </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="CC_SetVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="CC_GetVelParamsBlock(char const * serialNo, MOT_VelocityParameters  *velocityParams)" />
	/// <seealso cref="CC_SetVelParamsBlock(char const * serialNo, MOT_VelocityParameters *velocityParams)" />
	/// <seealso cref="CC_MoveToPosition(char const * serialNo, int index)" />
	/// <seealso cref="CC_MoveRelative(char const * serialNo, int displacement)" />
	/// 		  \include CodeSnippet_move.cpp
	KCUBEDCSERVO_API short __cdecl CC_MoveAtVelocity(char const * serialNo, MOT_TravelDirection direction);

	/// <summary> Sets the motor direction sense. </summary>
	/// <remarks> This function is used because some actuators use have directions of motion reversed.<br />
	/// 		  This parameter will tell the system to reverse the direction sense whnd moving, jogging etc. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="reverse"> if  <c>true</c> then directions will be swapped on these moves. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	KCUBEDCSERVO_API void __cdecl CC_SetDirection(char const * serialNo, bool reverse);


	/// <summary> Stop the current move immediately (with risk of losing track of position). </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_StopProfiled(char const * serialNo)" />
	KCUBEDCSERVO_API short __cdecl CC_StopImmediate(char const * serialNo);

	/// <summary> Stop the current move using the current velocity profile. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_RequestBacklash(char const * serialNo)" />
	/// <seealso cref="CC_StopImmediate(char const * serialNo)" />
	KCUBEDCSERVO_API short __cdecl CC_StopProfiled(char const * serialNo);

	/// <summary> Requests the backlash. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetBacklash(char const * serialNo)" />
	/// <seealso cref="CC_SetBacklash(char const * serialNo, long distance)" />
	KCUBEDCSERVO_API short __cdecl CC_RequestBacklash(char const * serialNo);

	/// <summary> Get the backlash distance setting (used to control hysteresis). </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The backlash distance in \ref DeviceUnits_page. </returns>
	/// <seealso cref="CC_RequestBacklash(char const * serialNo)" />
	/// <seealso cref="CC_SetBacklash(char const * serialNo, long distance)" />
	KCUBEDCSERVO_API long __cdecl CC_GetBacklash(char const * serialNo);

	/// <summary> Sets the backlash distance (used to control hysteresis). </summary>
	/// <param name="serialNo">  The serial no. </param>
	/// <param name="distance"> The distance in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetBacklash(char const * serialNo)" />
	KCUBEDCSERVO_API short __cdecl CC_SetBacklash(char const * serialNo, long distance);

	/// <summary> Get the Position Counter. </summary>
	/// <remarks> The position counter is identical to the position parameter.<br />
	/// 		  The position counter is set to zero when homing is complete.<br />
	/// 		  The position counter can also be set using <see cref="CC_SetPositionCounter(char const * serialNo, short channel, long count)" /> <br />
	/// 		  if homing is not to be perforned</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> Position count in \ref DeviceUnits_page. </returns>
	/// <seealso cref="CC_GetPosition(char const * serialNo)" />
	/// <seealso cref="CC_SetPositionCounter(char const * serialNo, long count)" />
	KCUBEDCSERVO_API long __cdecl CC_GetPositionCounter(char const * serialNo);

	/// <summary> Set the Position Counter. </summary>
	/// <remarks> Setting the position counter will locate the current position. <br />
	/// 		  Setting the position counter will effectively define the home position of a motor. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="count"> Position count in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetPositionCounter(char const * serialNo)" />
	/// <seealso cref="CC_GetPosition(char const * serialNo)" />
	KCUBEDCSERVO_API short __cdecl CC_SetPositionCounter(char const * serialNo, long count);

	/// <summary> Requests the encoder counter. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetEncoderCounter(char const * serialNo)" />
	/// <seealso cref="CC_SetEncoderCounter(char const * serialNo, long count)" />
	KCUBEDCSERVO_API short __cdecl CC_RequestEncoderCounter(char const * serialNo);

	/// <summary> Get the Encoder Counter. </summary>
	/// <remarks> For devices that have an encoder, the current encoder position can be read. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> Encoder Count of encoder units. </returns>
	/// <seealso cref="CC_RequestEncoderCounter(char const * serialNo)" />
	/// <seealso cref="CC_SetEncoderCounter(char const * serialNo, long count)" />
	KCUBEDCSERVO_API long __cdecl CC_GetEncoderCounter(char const * serialNo);

	/// <summary> Set the Encoder Counter values. </summary>
	/// <remarks> setting the encoder counter to zero, effectively defines a home position on the encoder strip.<br />
	/// 		  NOTE, setting this value does not move the device.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="count"> The encoder count in encoder units. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_RequestEncoderCounter(char const * serialNo)" />
	/// <seealso cref="CC_GetEncoderCounter(char const * serialNo)" />
	KCUBEDCSERVO_API short __cdecl CC_SetEncoderCounter(char const * serialNo, long count);


	/// <summary> Requests the limit switch parameters. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetLimitSwitchParams(char const * serialNo, MOT_LimitSwitchModes * clockwiseHardwareLimit, MOT_LimitSwitchModes * anticlockwiseHardwareLimit, unsigned int * clockwisePosition, unsigned int * anticlockwisePosition, MOT_LimitSwitchSWModes * softLimitMode)" />
	/// <seealso cref="CC_GetLimitSwitchParamsBlock(const char * serialNo, MOT_LimitSwitchParameters *limitSwitchParams)" />
	KCUBEDCSERVO_API short __cdecl CC_RequestLimitSwitchParams(char const * serialNo);

	/// <summary> Gets the limit switch parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
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
	/// <seealso cref="CC_RequestLimitSwitchParams(char const * serialNo)" />
	/// <seealso cref="CC_SetLimitSwitchParams(char const * serialNo, MOT_LimitSwitchModes clockwiseHardwareLimit, MOT_LimitSwitchModes anticlockwiseHardwareLimit, unsigned int clockwisePosition, unsigned int anticlockwisePosition, MOT_LimitSwitchSWModes softLimitMode)" />
	/// <seealso cref="CC_SetLimitSwitchParamsBlock(const char * serialNo, MOT_LimitSwitchParameters *limitSwitchParams)" />
	/// <seealso cref="CC_GetLimitSwitchParamsBlock(const char * serialNo, MOT_LimitSwitchParameters *limitSwitchParams)" />
	KCUBEDCSERVO_API short __cdecl CC_GetLimitSwitchParams(char const * serialNo, MOT_LimitSwitchModes * clockwiseHardwareLimit, MOT_LimitSwitchModes * anticlockwiseHardwareLimit, unsigned int * clockwisePosition, unsigned int * anticlockwisePosition, MOT_LimitSwitchSWModes * softLimitMode);

	/// <summary> Sets the limit switch parameters. </summary>
	/// <param name="serialNo">	The device serial no. </param>
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
	/// <seealso cref="CC_RequestLimitSwitchParams(char const * serialNo)" />
	/// <seealso cref="CC_GetLimitSwitchParams(char const * serialNo, MOT_LimitSwitchModes * clockwiseHardwareLimit, MOT_LimitSwitchModes * anticlockwiseHardwareLimit, unsigned int * clockwisePosition, unsigned int * anticlockwisePosition, MOT_LimitSwitchSWModes * softLimitMode)" />
	/// <seealso cref="CC_SetLimitSwitchParamsBlock(const char * serialNo, MOT_LimitSwitchParameters *limitSwitchParams)" />
	/// <seealso cref="CC_GetLimitSwitchParamsBlock(const char * serialNo, MOT_LimitSwitchParameters *limitSwitchParams)" />
	KCUBEDCSERVO_API short __cdecl CC_SetLimitSwitchParams(char const * serialNo, MOT_LimitSwitchModes clockwiseHardwareLimit, MOT_LimitSwitchModes anticlockwiseHardwareLimit, unsigned int clockwisePosition, unsigned int anticlockwisePosition, MOT_LimitSwitchSWModes softLimitMode);

	/// <summary> Gets the software limits mode. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	The software limits mode <list type=table>
	///							<item><term> Disable any move outside of the current travel range of the stage. </term><term>0</term></item>
	///							<item><term> Truncate moves to within the current travel range of the stage. </term><term>1</term></item>
	///							<item><term> Allow all moves, regardless of whether they are within the current travel range of the stage. </term><term>2</term></item>
	/// 		  </list>. </returns>
	/// <returns> The software limits mode. </returns>
	/// <seealso cref="CC_SetLimitsSoftwareApproachPolicy(const char * serialNo, MOT_LimitsSoftwareApproachPolicy limitsSoftwareApproachPolicy)" />
	KCUBEDCSERVO_API MOT_LimitsSoftwareApproachPolicy __cdecl CC_GetSoftLimitMode(char const * serialNo);

	/// <summary> Sets the software limits mode. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="limitsSoftwareApproachPolicy"> The soft limit mode
	/// 					 <list type=table>
	///							<item><term> Disable any move outside of the current travel range of the stage. </term><term>0</term></item>
	///							<item><term> Truncate moves to within the current travel range of the stage. </term><term>1</term></item>
	///							<item><term> Allow all moves, regardless of whether they are within the current travel range of the stage. </term><term>2</term></item>
	/// 					 </list> </param>
	/// <seealso cref="CC_GetSoftLimitMode(const char * serialNo)" />
	KCUBEDCSERVO_API void __cdecl CC_SetLimitsSoftwareApproachPolicy(char const * serialNo, MOT_LimitsSoftwareApproachPolicy limitsSoftwareApproachPolicy);

	/// <summary> Requests the MMI Parameters for the KCube Display Interface. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetMMIParams(char const * serialNo, __int16 *displayIntensity)" />
	/// <seealso cref="CC_GetMMIParamsExt(char const * serialNo, __int16 *displayIntensity, __int16 *displayTimeout, __int16 *displayDimIntensity)" />
	/// <seealso cref="CC_GetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	KCUBEDCSERVO_API short __cdecl CC_RequestMMIparams(char const * serialNo);

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
	/// <seealso cref="CC_RequestMMIParams(char const * serialNo)" />
	/// <seealso cref="CC_SetMMIParamsExt(char const * serialNo, KMOT_WheelMode wheelMode, __int32 wheelMaxVelocity, __int32 wheelAcceleration, KMOT_WheelDirectionSense directionSense, __int32 presetPosition1, __int32 presetPosition2, __int16 displayIntensity, __int16 displayTimeout, __int16 displayDimIntensity)" />
	/// <seealso cref="CC_SetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	/// <seealso cref="CC_GetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	KCUBEDCSERVO_API  short __cdecl CC_GetMMIParamsExt(char const * serialNo, KMOT_WheelMode *wheelMode, __int32 *wheelMaxVelocity, __int32 *wheelAcceleration, KMOT_WheelDirectionSense *directionSense,
		__int32 *presetPosition1, __int32 *presetPosition2, __int16 *displayIntensity, __int16 *displayTimeout, __int16 *displayDimIntensity);

	/// \deprecated
	/// <summary> Get the MMI Parameters for the KCube Display Interface. </summary>
	/// <remarks> superceded by <see cref="CC_GetMMIParamsExt(char const * serialNo, KMOT_WheelMode *wheelMode, __int32 *wheelMaxVelocity, __int32 *wheelAcceleration, KMOT_WheelDirectionSense *directionSense, __int32 *presetPosition1, __int32 *presetPosition2, __int16 *displayIntensity, __int16 *displayTimeout, __int16 *displayDimIntensity)"/> </remarks>
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
	/// <seealso cref="CC_SetMMIParams(char const * serialNo, KMOT_WheelMode wheelMode, __int32 wheelMaxVelocity, __int32 wheelAcceleration, KMOT_WheelDirectionSense directionSense, __int32 presetPosition1, __int32 presetPosition2, __int16 displayIntensity)" />
	/// <seealso cref="CC_SetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	/// <seealso cref="CC_RequestMMIParams(char const * serialNo)" />
	/// <seealso cref="CC_GetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	KCUBEDCSERVO_API  short __cdecl CC_GetMMIParams(char const * serialNo, KMOT_WheelMode *wheelMode, __int32 *wheelMaxVelocity, __int32 *wheelAcceleration, KMOT_WheelDirectionSense *directionSense,
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
	/// <seealso cref="CC_RequestMMIParams(char const * serialNo)" />
	/// <seealso cref="CC_GetMMIParamsExt(char const * serialNo, KMOT_WheelMode *wheelMode, __int32 *wheelMaxVelocity, __int32 *wheelAcceleration, KMOT_WheelDirectionSense *directionSense, __int32 *presetPosition1, __int32 *presetPosition2, __int16 *displayIntensity, __int16 *displayTimeout, __int16 *displayDimIntensity)" />
	/// <seealso cref="CC_SetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	/// <seealso cref="CC_GetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	KCUBEDCSERVO_API short __cdecl CC_SetMMIParamsExt(char const * serialNo, KMOT_WheelMode wheelMode, __int32 wheelMaxVelocity, __int32 wheelAcceleration, KMOT_WheelDirectionSense directionSense,
		__int32 presetPosition1, __int32 presetPosition2, __int16 displayIntensity, __int16 displayTimeout, __int16 displayDimIntensity);

	/// \deprecated
	/// <summary> Set the MMI Parameters for the KCube Display Interface. </summary>
	/// <remarks> superceded by <see cref="CC_SetMMIParams(char const * serialNo, KMOT_WheelMode wheelMode, __int32 wheelMaxVelocity, __int32 wheelAcceleration, KMOT_WheelDirectionSense directionSense, __int32 presetPosition1, __int32 presetPosition2, __int16 displayIntensity)"/> </remarks>
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
	/// <seealso cref="CC_RequestMMIParams(char const * serialNo)" />
	/// <seealso cref="CC_GetMMIParams(char const * serialNo, KMOT_WheelMode *wheelMode, __int32 *wheelMaxVelocity, __int32 *wheelAcceleration, KMOT_WheelDirectionSense *directionSense, __int32 *presetPosition1, __int32 *presetPosition2, __int16 *displayIntensity)" />
	/// <seealso cref="CC_SetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	/// <seealso cref="CC_GetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	KCUBEDCSERVO_API short __cdecl CC_SetMMIParams(char const * serialNo, KMOT_WheelMode wheelMode, __int32 wheelMaxVelocity, __int32 wheelAcceleration, KMOT_WheelDirectionSense directionSense,
		__int32 presetPosition1, __int32 presetPosition2, __int16 displayIntensity);

	/// <summary> Requests the Trigger Configuration Parameters. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_SetTriggerConfigParams(char const * serialNo, KSC_TriggerPortMode trigger1Mode, KSC_TriggerPortPolarity trigger1Polarity, KSC_TriggerPortMode trigger2Mode, KSC_TriggerPortPolarity trigger2Polarity)" />
	/// <seealso cref="CC_GeTriggerConfigParams(char const * serialNo, KSC_TriggerPortMode *trigger1Mode, KSC_TriggerPortPolarity *trigger1Polarity, KSC_TriggerPortMode *trigger2Mode, KSC_TriggerPortPolarity *trigger2Polarity)" />
	/// <seealso cref="CC_SetTriggerConfigParamsBlock(const char * serialNo, KSC_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="CC_GetTriggerConfigParamsBlock(const char * serialNo, KSC_TriggerConfig *triggerConfigParams)" />
	KCUBEDCSERVO_API short __cdecl CC_RequestTriggerConfigParams(char const * serialNo);

	/// <summary> Get the Trigger Configuration Parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="trigger1Mode">	    The trigger 1 mode.<list type=table>
	///						<item><term>0</term><term>Trigger disabled</term></item>
	///						<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="CC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
	///						<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
	///						<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
	///						<item><term>4</term><term>Trigger Input - Perform a Home action</term></item>
	///						<item><term>10</term><term>Trigger Output - General purpose output (<see cref="CC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
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
	///						<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="CC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
	///						<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
	///						<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
	///						<item><term>4</term><term>Trigger Input - Perform a Home action</term></item>
	///						<item><term>10</term><term>Trigger Output - General purpose output (<see cref="CC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
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
	/// <seealso cref="CC_SetTriggerConfigParams(char const * serialNo, KMOT_TriggerPortMode trigger1Mode, KMOT_TriggerPortPolarity trigger1Polarity, KMOT_TriggerPortMode trigger2Mode, KMOT_TriggerPortPolarity trigger2Polarity)" />
	/// <seealso cref="CC_SetTriggerConfigParamsBlock(const char * serialNo, KMOT_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="CC_RequestTriggerConfigParams(char const * serialNo)" />
	/// <seealso cref="CC_GetTriggerConfigParamsBlock(const char * serialNo, KMOT_TriggerConfig *triggerConfigParams)" />
	KCUBEDCSERVO_API  short __cdecl CC_GetTriggerConfigParams(char const * serialNo, KMOT_TriggerPortMode *trigger1Mode, KMOT_TriggerPortPolarity *trigger1Polarity, KMOT_TriggerPortMode *trigger2Mode, KMOT_TriggerPortPolarity *trigger2Polarity);

	/// <summary> Set the Trigger Configuration Parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="trigger1Mode">	    The trigger 1 mode.<list type=table>
	///						<item><term>0</term><term>Trigger disabled</term></item>
	///						<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="CC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
	///						<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
	///						<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
	///						<item><term>4</term><term>Trigger Input - Perform a Home action</term></item>
	///						<item><term>5</term><term>Trigger Input - Perform a Stop action</term></item>
	///						<item><term>10</term><term>Trigger Output - General purpose output (<see cref="CC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
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
	///						<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="CC_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
	///						<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
	///						<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
	///						<item><term>4</term><term>Trigger Input - Perform a Home action</term></item>
	///						<item><term>5</term><term>Trigger Input - Perform a Stop action</term></item>
	///						<item><term>10</term><term>Trigger Output - General purpose output (<see cref="CC_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
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
	/// <seealso cref="CC_RequestTriggerConfigParams(char const * serialNo)" />
	/// <seealso cref="CC_GeTriggerConfigParams(char const * serialNo, KMOT_TriggerPortMode *trigger1Mode, KMOT_TriggerPortPolarity *trigger1Polarity, KMOT_TriggerPortMode *trigger2Mode, KMOT_TriggerPortPolarity *trigger2Polarity)" />
	/// <seealso cref="CC_SetTriggerConfigParamsBlock(const char * serialNo, KMOT_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="CC_GetTriggerConfigParamsBlock(const char * serialNo, KMOT_TriggerConfig *triggerConfigParams)" />
	KCUBEDCSERVO_API short __cdecl CC_SetTriggerConfigParams(char const * serialNo, KMOT_TriggerPortMode trigger1Mode, KMOT_TriggerPortPolarity trigger1Polarity, KMOT_TriggerPortMode trigger2Mode, KMOT_TriggerPortPolarity trigger2Polarity);

	/// <summary> Requests the position trigger parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetTriggerParamsParams(char const * serialNo, __int32 *triggerStartPositionFwd, __int32 *triggerIntervalFwd, __int32 *triggerPulseCountFwd, 
	///									 __int32 *triggerStartPositionRev, __int32 *triggerIntervalRev, __int32 *triggerPulseCountRev, 
	///									 __int32 *triggerPulseWidth, __int32 *cycleCount)" />
	/// <seealso cref="CC_SetTriggerParamsParams(char const * serialNo, __int32 triggerStartPositionFwd, __int32 triggerIntervalFwd, __int32 triggerPulseCountFwd,
	///										__int32 triggerStartPositionRev, __int32 triggerIntervalRev, __int32 triggerPulseCountRev,
	///										__int32 triggerPulseWidth, __int32 cycleCount)" />
	/// <seealso cref="CC_GetTriggerParamsParamsBlock(const char * serialNo, KMOT_TriggerParams *triggerParamsParams)" />
	/// <seealso cref="CC_SetTriggerParamsParamsBlock(const char * serialNo, KMOT_TriggerParams *triggerParamsParams)" />
	KCUBEDCSERVO_API  short __cdecl CC_RequestPosTriggerParams(char const * serialNo);

	/// <summary> Get the Trigger Parameters Parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="triggerStartPositionFwd"> The trigger start position in \ref DeviceUnits_page. </param>
	/// <param name="triggerIntervalFwd">	    The trigger interval in \ref DeviceUnits_page. </param>
	/// <param name="triggerPulseCountFwd">    Number of trigger pulses. </param>
	/// <param name="triggerStartPositionRev"> The trigger start position in \ref DeviceUnits_page. </param>
	/// <param name="triggerIntervalRev">	    The trigger interval in \ref DeviceUnits_page. </param>
	/// <param name="triggerPulseCountRev">    Number of trigger pulses. </param>
	/// <param name="triggerPulseWidth">    Width of the trigger pulse in milliseconds, range 1000 (1ms) to 32767000 (32767ms). </param>
	/// <param name="cycleCount">   Number of cycles to perform triggering. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_RequestPosTriggerParams(char const * serialNo)" />
	/// <seealso cref="CC_SetTriggerParamsParams(char const * serialNo, __int32 triggerStartPositionFwd, __int32 triggerIntervalFwd, __int32 triggerPulseCountFwd,
	///										__int32 triggerStartPositionRev, __int32 triggerIntervalRev, __int32 triggerPulseCountRev,
	///										__int32 triggerPulseWidth, __int32 cycleCount)" />
	/// <seealso cref="CC_GetTriggerParamsParamsBlock(const char * serialNo, KMOT_TriggerParams *triggerParamsParams)" />
	/// <seealso cref="CC_SetTriggerParamsParamsBlock(const char * serialNo, KMOT_TriggerParams *triggerParamsParams)" />
	KCUBEDCSERVO_API  short __cdecl CC_GetTriggerParamsParams(char const * serialNo, __int32 *triggerStartPositionFwd, __int32 *triggerIntervalFwd, __int32 *triggerPulseCountFwd,
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
	/// <param name="triggerPulseWidth">    Width of the trigger pulse in milliseconds, range 1000 (1ms) to 32767000 (32767ms). </param>
	/// <param name="cycleCount">   Number of cycles to perform triggering. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_RequestPosTriggerParams(char const * serialNo)" />
	/// <seealso cref="CC_GeTriggerParamsParams(char const * serialNo, __int32 *triggerStartPositionFwd, __int32 *triggerIntervalFwd, __int32 *triggerPulseCountFwd,
	///										 __int32 *triggerStartPositionRev, __int32 *triggerIntervalRev, __int32 *triggerPulseCountRev,
	///										 __int32 *triggerPulseWidth, __int32 *cycleCount)" />
	/// <seealso cref="CC_GetTriggerParamsParamsBlock(const char * serialNo, KMOT_TriggerParams *triggerParamsParams)" />
	/// <seealso cref="CC_SetTriggerParamsParamsBlock(const char * serialNo, KMOT_TriggerParams *triggerParamsParams)" />
	KCUBEDCSERVO_API short __cdecl CC_SetTriggerParamsParams(char const * serialNo, __int32 triggerStartPositionFwd, __int32 triggerIntervalFwd, __int32 triggerPulseCountFwd,
		__int32 triggerStartPositionRev, __int32 triggerIntervalRev, __int32 triggerPulseCountRev,
		__int32 triggerPulseWidth, __int32 cycleCount);

	/// <summary> Gets the MMI parameters for the device. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="mmiParams"> Options for controlling the mmi. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_RequestMMIParams(char const * serialNo)" />
	/// <seealso cref="CC_GetMMIParamsExt(char const * serialNo, KMOT_WheelMode *wheelMode, __int32 *wheelMaxVelocity, __int32 *wheelAcceleration, KMOT_WheelDirectionSense *directionSense, __int32 *presetPosition1, __int32 *presetPosition2, __int16 *displayIntensity, __int16 *displayTimeout, __int16 *displayDimIntensity)" />
	/// <seealso cref="CC_SetMMIParamExts(char const * serialNo, KMOT_WheelMode wheelMode, __int32 wheelMaxVelocity, __int32 wheelAcceleration, KMOT_WheelDirectionSense directionSense, __int32 presetPosition1, __int32 presetPosition2, __int16 displayIntensity, __int16 displayTimeout, __int16 displayDimIntensity)" />
	/// <seealso cref="CC_SetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	KCUBEDCSERVO_API short __cdecl CC_GetMMIParamsBlock(char const * serialNo, KMOT_MMIParams *mmiParams);

	/// <summary> Sets the MMI parameters for the device. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="mmiParams"> Options for controlling the mmi. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_RequestMMIParams(char const * serialNo)" />
	/// <seealso cref="CC_GetMMIParamsExt(char const * serialNo, KMOT_WheelMode *wheelMode, __int32 *wheelMaxVelocity, __int32 *wheelAcceleration, KMOT_WheelDirectionSense *directionSense, __int32 *presetPosition1, __int32 *presetPosition2, __int16 *displayIntensity, __int16 *displayTimeout, __int16 *displayDimIntensity)" />
	/// <seealso cref="CC_SetMMIParamsExt(char const * serialNo, KMOT_WheelMode wheelMode, __int32 wheelMaxVelocity, __int32 wheelAcceleration, KMOT_WheelDirectionSense directionSense, __int32 presetPosition1, __int32 presetPosition2, __int16 displayIntensity, __int16 displayTimeout, __int16 displayDimIntensity)" />
	/// <seealso cref="CC_GetMMIParamsBlock(const char * serialNo, KMOT_MMIParams *mmiParams)" />
	KCUBEDCSERVO_API short __cdecl CC_SetMMIParamsBlock(char const * serialNo, KMOT_MMIParams *mmiParams);

	/// <summary> Gets the trigger configuration parameters block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="triggerConfigParams"> Options for controlling the trigger configuration. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_RequestTriggerConfigParams(char const * serialNo)" />
	/// <seealso cref="CC_GeTriggerConfigParams(char const * serialNo, KMOT_TriggerPortMode *trigger1Mode, KMOT_TriggerPortPolarity *trigger1Polarity, KMOT_TriggerPortMode *trigger2Mode, KMOT_TriggerPortPolarity *trigger2Polarity)" />
	/// <seealso cref="CC_SetTriggerConfigParams(char const * serialNo, KMOT_TriggerPortMode trigger1Mode, KMOT_TriggerPortPolarity trigger1Polarity, KMOT_TriggerPortMode trigger2Mode, KMOT_TriggerPortPolarity trigger2Polarity)" />
	/// <seealso cref="CC_SetTriggerConfigParamsBlock(const char * serialNo, KMOT_TriggerConfig *triggerConfigParams)" />
	KCUBEDCSERVO_API short __cdecl CC_GetTriggerConfigParamsBlock(char const * serialNo, KMOT_TriggerConfig *triggerConfigParams);

	/// <summary> Sets the trigger configuration parameters block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="triggerConfigParams"> Options for controlling the trigger configuration. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_RequestTriggerConfigParams(char const * serialNo)" />
	/// <seealso cref="CC_GeTriggerConfigParams(char const * serialNo, KMOT_TriggerPortMode *trigger1Mode, KMOT_TriggerPortPolarity *trigger1Polarity, KMOT_TriggerPortMode *trigger2Mode, KMOT_TriggerPortPolarity *trigger2Polarity)" />
	/// <seealso cref="CC_SetTriggerConfigParams(char const * serialNo, KMOT_TriggerPortMode trigger1Mode, KMOT_TriggerPortPolarity trigger1Polarity, KMOT_TriggerPortMode trigger2Mode, KMOT_TriggerPortPolarity trigger2Polarity)" />
	/// <seealso cref="CC_GetTriggerConfigParamsBlock(const char * serialNo, KMOT_TriggerConfig *triggerConfigParams)" />
	KCUBEDCSERVO_API short __cdecl CC_SetTriggerConfigParamsBlock(char const * serialNo, KMOT_TriggerConfig *triggerConfigParams);

	/// <summary> Gets the trigger parameters block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="triggerParamsParams"> Options for controlling the trigger. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_RequestPosTriggerParams(char const * serialNo)" />
	/// <seealso cref="CC_GeTriggerParamsParams(char const * serialNo, __int32 *triggerStartPositionFwd, __int32 *triggerIntervalFwd, __int32 *triggerPulseCountFwd,
	///										 __int32 *triggerStartPositionRev, __int32 *triggerIntervalRev, __int32 *triggerPulseCountRev,
	///										 __int32 *triggerPulseWidth, __int32 *cycleCount)" />
	/// <seealso cref="CC_SetTriggerParamsParams(char const * serialNo, __int32 triggerStartPositionFwd, __int32 triggerIntervalFwd, __int32 triggerPulseCountFwd,
	///										__int32 triggerStartPositionRev, __int32 triggerIntervalRev, __int32 triggerPulseCountRev,
	///										__int32 triggerPulseWidth, __int32 cycleCount)" />
	/// <seealso cref="CC_SetTriggerParamsParamsBlock(const char * serialNo, KMOT_TriggerParams *triggerParamsParams)" />
	KCUBEDCSERVO_API short __cdecl CC_GetTriggerParamsParamsBlock(char const * serialNo, KMOT_TriggerParams *triggerParamsParams);

	/// <summary> Sets the trigger parameters block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="triggerParamsParams"> Options for controlling the trigger. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_RequestPosTriggerParams(char const * serialNo)" />
	/// <seealso cref="CC_GeTriggerParamsParams(char const * serialNo, __int32 *triggerStartPositionFwd, __int32 *triggerIntervalFwd, __int32 *triggerPulseCountFwd,
	///										 __int32 *triggerStartPositionRev, __int32 *triggerIntervalRev, __int32 *triggerPulseCountRev,
	///										 __int32 *triggerPulseWidth, __int32 *cycleCount)" />
	/// <seealso cref="CC_SetTriggerParamsParams(char const * serialNo, __int32 triggerStartPositionFwd, __int32 triggerIntervalFwd, __int32 triggerPulseCountFwd,
	///										__int32 triggerStartPositionRev, __int32 triggerIntervalRev, __int32 triggerPulseCountRev,
	///										__int32 triggerPulseWidth, __int32 cycleCount)" />
	/// <seealso cref="CC_GetTriggerParamsParamsBlock(const char * serialNo, KMOT_TriggerParams *triggerParamsParams)" />
	KCUBEDCSERVO_API short __cdecl CC_SetTriggerParamsParamsBlock(char const * serialNo, KMOT_TriggerParams *triggerParamsParams);

	/// <summary> Get the move velocity parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec11 "Positioning" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="velocityParams"> Address of the MOT_VelocityParameters to recieve the velocity parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_RequestVelParams(char const * serialNo)" />
	/// <seealso cref="CC_GetVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="CC_SetVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="CC_SetVelParamsBlock(char const * serialNo, MOT_VelocityParameters *velocityParams)" />
	/// <seealso cref="CC_MoveToPosition(char const * serialNo, int index)" />
	/// <seealso cref="CC_MoveRelative(char const * serialNo, int displacement)" />
	/// <seealso cref="CC_MoveAtVelocity(char const * serialNo, MOT_TravelDirection direction)" />
	/// 		  \include CodeSnippet_movepars.cpp
	KCUBEDCSERVO_API short __cdecl CC_GetVelParamsBlock(const char * serialNo, MOT_VelocityParameters  *velocityParams);

	/// <summary> Set the move velocity parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec11 "Positioning" for more detail.<remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="velocityParams"> The address of the MOT_VelocityParameters holding the new velocity parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="CC_SetVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="CC_GetVelParamsBlock(char const * serialNo, MOT_VelocityParameters  *velocityParams)" />
	/// <seealso cref="CC_MoveToPosition(char const * serialNo, int index)" />
	/// <seealso cref="CC_MoveRelative(char const * serialNo, int displacement)" />
	/// <seealso cref="CC_MoveAtVelocity(char const * serialNo, MOT_TravelDirection direction)" />
	/// 		  \include CodeSnippet_movepars.cpp
	KCUBEDCSERVO_API short __cdecl CC_SetVelParamsBlock(const char * serialNo, MOT_VelocityParameters *velocityParams);

	/// <summary> Sets the move absolute position. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="position"> The absolute position in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_RequestMoveAbsolutePosition(char const * serialNo)" />
	/// <seealso cref="CC_GetMoveAbsolutePosition(const char * serialNo)" />
	/// <seealso cref="CC_MoveAbsolute(const char * serialNo)" />
	KCUBEDCSERVO_API short __cdecl CC_SetMoveAbsolutePosition(const char * serialNo, int position);

	/// <summary> Requests the position of next absolute move. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetMoveAbsolutePosition(const char * serialNo)" />
	/// <seealso cref="CC_SetMoveAbsolutePosition(const char * serialNo, int position)" />
	/// <seealso cref="CC_MoveAbsolute(const char * serialNo)" />
	KCUBEDCSERVO_API short __cdecl CC_RequestMoveAbsolutePosition(char const * serialNo);

	/// <summary> Gets the move absolute position. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The move absolute position in \ref DeviceUnits_page. </returns>
	/// <seealso cref="CC_RequestMoveAbsolutePosition(char const * serialNo)" />
	/// <seealso cref="CC_SetMoveAbsolutePosition(const char * serialNo, int position)" />
	/// <seealso cref="CC_MoveAbsolute(const char * serialNo)" />
	KCUBEDCSERVO_API int __cdecl CC_GetMoveAbsolutePosition(const char * serialNo);

	/// <summary> Moves the device to the position defined in the SetMoveAbsolute command. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_SetMoveAbsolutePosition(const char * serialNo, int position)" />
	/// <seealso cref="CC_RequestMoveAbsolutePosition(char const * serialNo)" />
	/// <seealso cref="CC_GetMoveAbsolutePosition(const char * serialNo)" />
	KCUBEDCSERVO_API short __cdecl CC_MoveAbsolute(const char * serialNo);

	/// <summary> Sets the move relative distance. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="distance"> The relative distance in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_RequestMoveRelativeDistance(char const * serialNo)" />
	/// <seealso cref="CC_GetMoveRelativeDistance(const char * serialNo)" />
	/// <seealso cref="CC_MoveRelativeDistance(const char * serialNo)" />
	KCUBEDCSERVO_API short __cdecl CC_SetMoveRelativeDistance(const char * serialNo, int distance);

	/// <summary> Requests the relative move distance. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetMoveRelativeDistance(const char * serialNo)" />
	/// <seealso cref="CC_SetMoveRelativeDistance(const char * serialNo, int distance)" />
	/// <seealso cref="CC_MoveRelativeDistance(const char * serialNo)" />
	KCUBEDCSERVO_API short __cdecl CC_RequestMoveRelativeDistance(char const * serialNo);

	/// <summary> Gets the move relative distance. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The move relative distance in \ref DeviceUnits_page. </returns>
	/// <seealso cref="CC_RequestMoveRelativeDistance(char const * serialNo)" />
	/// <seealso cref="CC_SetMoveRelativeDistance(const char * serialNo, int distance)" />
	/// <seealso cref="CC_MoveRelativeDistance(const char * serialNo)" />
	KCUBEDCSERVO_API int __cdecl CC_GetMoveRelativeDistance(const char * serialNo);

	/// <summary> Moves the device by a relative distancce defined by SetMoveRelativeDistance. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_SetMoveRelativeDistance(const char * serialNo, int distance)" />
	/// <seealso cref="CC_RequestMoveRelativeDistance(char const * serialNo)" />
	/// <seealso cref="CC_GetMoveRelativeDistance(const char * serialNo)" />
	KCUBEDCSERVO_API short __cdecl CC_MoveRelativeDistance(const char * serialNo);

	/// <summary> Get the homing parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec10 "Homing" for more detail.<remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="homingParams"> Address of the MOT_HomingParameters to recieve the homing parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_RequestHomingParams(char const * serialNo)" />
	/// <seealso cref="CC_GetHomingVelocity(char const * serialNo)" />
	/// <seealso cref="CC_SetHomingVelocity(char const * serialNo, unsigned int velocity)" />
	/// <seealso cref="CC_SetHomingParamsBlock(char const * serialNo, MOT_HomingParameters *homingParams)" />
	KCUBEDCSERVO_API short __cdecl CC_GetHomingParamsBlock(const char * serialNo, MOT_HomingParameters *homingParams);

	/// <summary> Set the homing parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec10 "Homing" for more detail.<remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="homingParams"> Address of the new homing parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_RequestHomingParams(char const * serialNo)" />
	/// <seealso cref="CC_GetHomingVelocity(char const * serialNo)" />
	/// <seealso cref="CC_SetHomingVelocity(char const * serialNo, unsigned int velocity)" />
	/// <seealso cref="CC_GetHomingParamsBlock(char const * serialNo, MOT_HomingParameters *homingParams)" />
	KCUBEDCSERVO_API short __cdecl CC_SetHomingParamsBlock(const char * serialNo, MOT_HomingParameters *homingParams);

	/// <summary> Get the jog parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">  The device serial no. </param>
	/// <param name="jogParams"> The address of the MOT_JogParameters block to recieve the jog parameters </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_RequestJogParams(char const * serialNo)" />
	/// <seealso cref="CC_GetJogMode(char const * serialNo, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="CC_SetJogMode(char const * serialNo, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="CC_GetJogStepSize(char const * serialNo)" />
	/// <seealso cref="CC_SetJogStepSize(char const * serialNo, unsigned int stepSize)" />
	/// <seealso cref="CC_SetJogVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="CC_GetJogVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="CC_SetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="CC_MoveJog(char const * serialNo, MOT_TravelDirection jogDirection)" />
	/// 		  \include CodeSnippet_jogpars.cpp
	KCUBEDCSERVO_API short __cdecl CC_GetJogParamsBlock(const char * serialNo, MOT_JogParameters *jogParams);

	/// <summary> Set the jog parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="jogParams"> The address of the new MOT_JogParameters block. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetJogMode(char const * serialNo, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="CC_SetJogMode(char const * serialNo, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="CC_GetJogStepSize(char const * serialNo)" />
	/// <seealso cref="CC_SetJogStepSize(char const * serialNo, unsigned int stepSize)" />
	/// <seealso cref="CC_SetJogVelParams(char const * serialNo, int acceleration, int maxVelocity)" />
	/// <seealso cref="CC_GetJogVelParams(char const * serialNo, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="CC_GetJogParamsBlock(char const * serialNo, MOT_JogParameters *jogParams)" />
	/// <seealso cref="CC_MoveJog(char const * serialNo, MOT_TravelDirection jogDirection)" />
	/// 		  \include CodeSnippet_jogpars.cpp
	KCUBEDCSERVO_API short __cdecl CC_SetJogParamsBlock(const char * serialNo, MOT_JogParameters *jogParams);

	/// <summary> Get the limit switch parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="limitSwitchParams"> Address of the MOT_LimitSwitchParameters parameter to recieve the  limit switch parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_SetLimitSwitchParams(char const * serialNo, MOT_LimitSwitchModes clockwiseHardwareLimit, MOT_LimitSwitchModes anticlockwiseHardwareLimit, unsigned int clockwisePosition, unsigned int anticlockwisePosition, MOT_LimitSwitchSWModes softLimitMode)" />
	/// <seealso cref="CC_RequestLimitSwitchParams(char const * serialNo)" />
	/// <seealso cref="CC_GetLimitSwitchParams(char const * serialNo, MOT_LimitSwitchModes * clockwiseHardwareLimit, MOT_LimitSwitchModes * anticlockwiseHardwareLimit, unsigned int * clockwisePosition, unsigned int * anticlockwisePosition, MOT_LimitSwitchSWModes * softLimitMode)" />
	/// <seealso cref="CC_SetLimitSwitchParamsBlock(const char * serialNo, MOT_LimitSwitchParameters *limitSwitchParams)" />
	KCUBEDCSERVO_API short __cdecl CC_GetLimitSwitchParamsBlock(const char * serialNo, MOT_LimitSwitchParameters *limitSwitchParams);

	/// <summary> Set the limit switch parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="limitSwitchParams"> Address of the MOT_LimitSwitchParameters parameter containing the new limit switch parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_RequestLimitSwitchParams(char const * serialNo)" />
	/// <seealso cref="CC_GetLimitSwitchParams(char const * serialNo, MOT_LimitSwitchModes * clockwiseHardwareLimit, MOT_LimitSwitchModes * anticlockwiseHardwareLimit, unsigned int * clockwisePosition, unsigned int * anticlockwisePosition, MOT_LimitSwitchSWModes * softLimitMode)" />
	/// <seealso cref="CC_SetLimitSwitchParams(char const * serialNo, MOT_LimitSwitchModes clockwiseHardwareLimit, MOT_LimitSwitchModes anticlockwiseHardwareLimit, unsigned int clockwisePosition, unsigned int anticlockwisePosition, MOT_LimitSwitchSWModes softLimitMode)" />
	/// <seealso cref="CC_GetLimitSwitchParamsBlock(const char * serialNo, MOT_LimitSwitchParameters *limitSwitchParams)" />
	KCUBEDCSERVO_API short __cdecl CC_SetLimitSwitchParamsBlock(const char * serialNo, MOT_LimitSwitchParameters *limitSwitchParams);

	/// <summary> Request the PID parameters for DC motors used in an algorithm involving calculus. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetDCPIDParams(const char * serialNo, MOT_DC_PIDParameters *DCproportionalIntegralDerivativeParams)" />
	/// <seealso cref="CC_SetDCPIDParams(const char * serialNo, MOT_DC_PIDParameters *DCproportionalIntegralDerivativeParams)" />
	KCUBEDCSERVO_API short __cdecl CC_RequestDCPIDParams(const char * serialNo);

	/// <summary> Get the DC PID parameters for DC motors used in an algorithm involving calculus. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="DCproportionalIntegralDerivativeParams"> [in,out] If non-null, a variable-length parameters list containing DC PID parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_RequestDCPIDParams(char const * serialNo)" />
	/// <seealso cref="CC_SetDCPIDParams(const char * serialNo, MOT_DC_PIDParameters *DCproportionalIntegralDerivativeParams)" />
	KCUBEDCSERVO_API short __cdecl CC_GetDCPIDParams(const char * serialNo, MOT_DC_PIDParameters *DCproportionalIntegralDerivativeParams);

	/// <summary> Set the PID parameters for DC motors used in an algorithm involving calculus. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="DCproportionalIntegralDerivativeParams"> [in,out] If non-null, a variable-length parameters list containing DC PID parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_RequestDCPIDParams(char const * serialNo)" />
	/// <seealso cref="CC_GetDCPIDParams(const char * serialNo, MOT_DC_PIDParameters *DCproportionalIntegralDerivativeParams)" />
	KCUBEDCSERVO_API short __cdecl CC_SetDCPIDParams(const char * serialNo, MOT_DC_PIDParameters *DCproportionalIntegralDerivativeParams);


	/// <summary> Suspend automatic messages at ends of moves. </summary>
	/// <remarks> Useful to speed up part of real-time system with lots of short moves. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_ResumeMoveMessages(char const * serialNo)" />
	KCUBEDCSERVO_API short __cdecl CC_SuspendMoveMessages(char const * serialNo);

	/// <summary> Resume suspended move messages. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_SuspendMoveMessages(char const * serialNo)" />
	KCUBEDCSERVO_API short __cdecl CC_ResumeMoveMessages(char const * serialNo);

	/// <summary> Requests the current position. </summary>
	/// <remarks> This needs to be called to get the device to send it's current position.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="CC_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// 		  \include CodeSnippet_move.cpp
	/// <seealso cref="CC_GetPosition(char const * serialNo)" />
	/// <seealso cref="CC_StartPolling(char const * serialNo, int milliseconds)" />
	KCUBEDCSERVO_API short __cdecl CC_RequestPosition(char const * serialNo);

	/// <summary> Request the status bits which identify the current motor state. </summary>
	/// <remarks> This needs to be called to get the device to send it's current status bits.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="CC_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="CC_GetStatusBits(char const * serialNo)" />
	/// <seealso cref="CC_StartPolling(char const * serialNo, int milliseconds)" />
	KCUBEDCSERVO_API short __cdecl CC_RequestStatusBits(char const * serialNo);

	/// <summary>Get the current status bits. </summary>
	/// <remarks> This returns the latest status bits received from the device.<br />
	/// 		  To get new status bits, use <see cref="CC_RequestStatusBits(char const * serialNo)" />
	/// 		  or use the polling functions, <see cref="CC_StartPolling(char const * serialNo, int milliseconds)" />.  </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	The status bits from the device <list type=table>
	///				<item><term>0x00000001</term><term>CW hardware limit switch (0=No contact, 1=Contact).</term></item>
	///				<item><term>0x00000002</term><term>CCW hardware limit switch (0=No contact, 1=Contact).</term></item>
	///				<item><term>0x00000004</term><term>Not applicable.</term></item>
	///				<item><term>0x00000008</term><term>Not applicable.</term></item>
	///				<item><term>0x00000010</term><term>Motor shaft moving clockwise (1=Moving, 0=Stationary).</term></item>
	///				<item><term>0x00000020</term><term>Motor shaft moving counterclockwise (1=Moving, 0=Stationary).</term></item>
	///				<item><term>0x00000040</term><term>Shaft jogging clockwise (1=Moving, 0=Stationary).</term></item>
	///				<item><term>0x00000080</term><term>Shaft jogging counterclockwise (1=Moving, 0=Stationary).</term></item>
	///				<item><term>0x00000100</term><term>Not applicable.</term></item>
	///				<item><term>0x00000200</term><term>Motor homing (1=Homing, 0=Not homing).</term></item>
	///				<item><term>0x00000400</term><term>Motor homed (1=Homed, 0=Not homed).</term></item>
	///				<item><term>0x00000800</term><term>For Future Use.</term></item>
	///				<item><term>0x00001000</term><term>Not applicable.</term></item>
	///				<item><term>0x00002000</term><term></term></item>
	///				<item><term>...</term><term></term></item>
	///				<item><term>0x00080000</term><term></term></item>
	///				<item><term>0x00100000</term><term>General Digital Input 1.</term></item>
	///				<item><term>0x00200000</term><term>General Digital Input 2.</term></item>
	///				<item><term>0x00400000</term><term>General Digital Input 3.</term></item>
	///				<item><term>0x00800000</term><term>General Digital Input 4.</term></item>
	///				<item><term>0x01000000</term><term>General Digital Input 5.</term></item>
	///				<item><term>0x02000000</term><term>General Digital Input 6.</term></item>
	///				<item><term>0x04000000</term><term>For Future Use.</term></item>
	///				<item><term>0x08000000</term><term>For Future Use.</term></item>
	///				<item><term>0x10000000</term><term>For Future Use.</term></item>
	///				<item><term>0x20000000</term><term>Active (1=Active, 0=Not active).</term></item>
	///				<item><term>0x40000000</term><term>For Future Use.</term></item>
	///				<item><term>0x80000000</term><term>Channel enabled (1=Enabled, 0=Disabled).</term></item>
	/// 		  </list>. </returns>
	/// <seealso cref="CC_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="CC_StartPolling(char const * serialNo, int milliseconds)" />
	KCUBEDCSERVO_API DWORD __cdecl CC_GetStatusBits(char const * serialNo);

	/// <summary> Starts the internal polling loop which continuously requests position and status. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="milliseconds">The milliseconds polling rate. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="CC_StopPolling(char const * serialNo)" />
	/// <seealso cref="CC_PollingDuration(char const * serialNo)" />
	/// <seealso cref="CC_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="CC_RequestPosition(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	KCUBEDCSERVO_API bool __cdecl CC_StartPolling(char const * serialNo, int milliseconds);

	/// <summary> Gets the polling loop duration. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The time between polls in milliseconds or 0 if polling is not active. </returns>
	/// <seealso cref="CC_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="CC_StopPolling(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	KCUBEDCSERVO_API long __cdecl CC_PollingDuration(char const * serialNo);

	/// <summary> Stops the internal polling loop. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <seealso cref="CC_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="CC_PollingDuration(char const * serialNo)" />
	/// \include CodeSnippet_connection1.cpp
	KCUBEDCSERVO_API void __cdecl CC_StopPolling(char const * serialNo);

	/// <summary> Gets the time in milliseconds since tha last message was received from the device. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="lastUpdateTimeMS"> The time since the last message was received in milliseconds. </param>
	/// <returns> True if monitoring is enabled otherwize False. </returns>
	/// <seealso cref="CC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// <seealso cref="CC_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	KCUBEDCSERVO_API bool __cdecl CC_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS);

	/// <summary> Enables the last message monitoring timer. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="enable"> True to enable monitoring otherwise False to disable. </param>
	/// <param name="lastMsgTimeout"> The last message error timeout in ms. 0 to disable. </param>
	/// <seealso cref="CC_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="CC_HasLastMsgTimerOverrun(char const * serialNo)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	KCUBEDCSERVO_API void __cdecl CC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout);

	/// <summary> Queries if the time since the last message has exceeded the lastMsgTimeout set by <see cref="CC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )"/>. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> True if last message timer has elapsed, False if monitoring is not enabled or if time of last message received is less than lastMsgTimeout. </returns>
	/// <seealso cref="CC_TimeSinceLastMsgReceived(char const * serialNo, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="CC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	KCUBEDCSERVO_API bool __cdecl CC_HasLastMsgTimerOverrun(char const * serialNo);

	/// <summary> Requests that all settings are download from device. </summary>
	/// <remarks> This function requests that the device upload all it's settings to the DLL.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	KCUBEDCSERVO_API short __cdecl CC_RequestSettings(char const * serialNo);

	/// <summary> Gets the DC Motor minimum stage position. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The Minimum position in \ref DeviceUnits_page. </returns>
	/// <seealso cref="CC_SetStageAxisLimits(char const * serialNo, int minPosition, int maxPosition)" />
	/// <seealso cref="CC_GetStageAxisMaxPos(char const * serialNo)" />
	KCUBEDCSERVO_API int __cdecl CC_GetStageAxisMinPos(char const * serialNo);

	/// <summary> Gets the DC Motor maximum stage position. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The Maximum position in \ref DeviceUnits_page. </returns>
	/// <seealso cref="CC_SetStageAxisLimits(char const * serialNo, int minPosition, int maxPosition)" />
	/// <seealso cref="CC_GetStageAxisMinPos(char const * serialNo)" />
	KCUBEDCSERVO_API int __cdecl CC_GetStageAxisMaxPos(char const * serialNo);

	/// <summary> Sets the stage axis position limits. </summary>
	/// <remarks> This function sets the limits of travel for the stage.<Br />
	/// 		  The implementation will depend upon the nature of the travel being requested and the Soft Limits mode which can be obtained using <see cref="CC_GetSoftLimitMode(char const * serialNo)" />. <Br />
	/// 		  <B>MoveAbsolute</B>, <B>MoveRelative</B> and <B>Jog (Single Step)</B> will obey the Soft Limit Mode.
	/// 		  If the target position is outside the limits then either a full move, a partial move or no move will occur.<Br />
	/// 		  <B>Jog (Continuous)</B> and <B>Move Continuous</B> will attempt to obey the limits, but as these moves rely on position information feedback from the device to detect if the travel is exceeding the limits, the device will stop, but it is likely to overshoot the limit, especially at high velocity.<Br />
	/// 		  <B>Home</B> will always ignore the software limits.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="minPosition"> The minimum position in \ref DeviceUnits_page. </param>
	/// <param name="maxPosition"> The maximum position in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetStageAxisMinPos(char const * serialNo)" />
	/// <seealso cref="CC_GetStageAxisMaxPos(char const * serialNo)" />
	KCUBEDCSERVO_API short __cdecl CC_SetStageAxisLimits(char const * serialNo, int minPosition, int maxPosition);

	/// <summary> Set the motor travel mode. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="travelMode"> The travel mode.
	/// 						  <list type=table>
	///								<item><term>Linear motion</term><term>1</term></item>
	///								<item><term>Rotational motion</term><term>2</term></item>
	/// 						  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetMotorTravelMode(char const * serialNo)" />
	KCUBEDCSERVO_API short __cdecl CC_SetMotorTravelMode(char const * serialNo, MOT_TravelModes travelMode);

	/// <summary> Get the motor travel mode. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The travel mode.
	/// 						  <list type=table>
	///								<item><term>Linear motion</term><term>1</term></item>
	///								<item><term>Rotational motion</term><term>2</term></item>
	/// 						  </list> </returns>
	/// <seealso cref="CC_SetMotorTravelMode(char const * serialNo, int travelMode)" />
	KCUBEDCSERVO_API MOT_TravelModes __cdecl CC_GetMotorTravelMode(char const * serialNo);

	/// \deprecated
	/// <summary> Sets the motor stage parameters. </summary>
	/// <remarks> superceded by <see cref="CC_SetMotorParamsExt(char const * serialNo, double stepsPerRevolution, double gearboxRatio, double pitch)"/> </remarks>
	/// <remarks> These parameters, when combined define the stage motion in terms of \ref RealWorldUnits_page. (mm or degrees)<br />
	/// 		  The real world unit is defined from stepsPerRev * gearBoxRatio / pitch.</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="stepsPerRev">  The steps per revolution. </param>
	/// <param name="gearBoxRatio"> The gear box ratio. </param>
	/// <param name="pitch">	    The pitch. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetMotorParams(char const * serialNo, long *stepsPerRev, long *gearBoxRatio, float *pitch)" />
	KCUBEDCSERVO_API short __cdecl CC_SetMotorParams(char const * serialNo, long stepsPerRev, long gearBoxRatio, float pitch);

	/// \deprecated
	/// <summary> Gets the motor stage parameters. </summary>
	/// <remarks> superceded by <see cref="CC_GetMotorParamsExt(char const * serialNo, double *stepsPerRevolution, double *gearboxRatio, double *pitch)"/> </remarks>
	/// <remarks> These parameters, when combined define the stage motion in terms of \ref RealWorldUnits_page. (mm or degrees)<br />
	/// 		  The real world unit is defined from stepsPerRev * gearBoxRatio / pitch.</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="stepsPerRev">  Address of the parameter to receive the steps per revolution. </param>
	/// <param name="gearBoxRatio"> Address of the parameter to receive the gear box ratio. </param>
	/// <param name="pitch">	    Address of the parameter to receive the pitch. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_SetMotorParams(char const * serialNo, long stepsPerRev, long gearBoxRatio, float pitch)" />
	KCUBEDCSERVO_API short __cdecl CC_GetMotorParams(char const * serialNo, long *stepsPerRev, long *gearBoxRatio, float *pitch);

	/// <summary> Sets the motor stage parameters. </summary>
	/// <remarks> These parameters, when combined define the stage motion in terms of \ref RealWorldUnits_page. (mm or degrees)<br />
	/// 		  The real world unit is defined from stepsPerRev * gearBoxRatio / pitch.</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="stepsPerRev">  The steps per revolution. </param>
	/// <param name="gearBoxRatio"> The gear box ratio. </param>
	/// <param name="pitch">	    The pitch. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetMotorParamsExt(char const * serialNo, long *stepsPerRev, long *gearBoxRatio, float *pitch)" />
	KCUBEDCSERVO_API short __cdecl CC_SetMotorParamsExt(char const * serialNo, double stepsPerRev, double gearBoxRatio, double pitch);

	/// <summary> Gets the motor stage parameters. </summary>
	/// <remarks> These parameters, when combined define the stage motion in terms of \ref RealWorldUnits_page. (mm or degrees)<br />
	/// 		  The real world unit is defined from stepsPerRev * gearBoxRatio / pitch.</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="stepsPerRev">  Address of the parameter to receive the steps per revolution. </param>
	/// <param name="gearBoxRatio"> Address of the parameter to receive the gear box ratio. </param>
	/// <param name="pitch">	    Address of the parameter to receive the pitch. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_SetMotorParamsExt(char const * serialNo, long stepsPerRev, long gearBoxRatio, float pitch)" />
	KCUBEDCSERVO_API short __cdecl CC_GetMotorParamsExt(char const * serialNo, double *stepsPerRev, double *gearBoxRatio, double *pitch);

	/// \deprecated
	/// <summary> Sets the absolute maximum velocity and acceleration constants for the current stage. </summary>
	/// <remarks> These parameters are maintained for user info only and do not reflect the current stage parameters.<Br />
    ///           The absolute maximum velocity and acceleration constants are initialized from the stage settings..</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="maxVelocity">  The absolute maximum velocity in real world units. </param>
	/// <param name="maxAcceleration"> The absolute maximum acceleration in real world units. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetMotorVelocityLimits(char const * serialNo, double *maxVelocity, double *maxAcceleration)" />
	KCUBEDCSERVO_API short __cdecl CC_SetMotorVelocityLimits(char const * serialNo, double maxVelocity, double maxAcceleration);

	/// <summary> Gets the absolute maximum velocity and acceleration constants for the current stage. </summary>
	/// <remarks> These parameters are maintained for user info only and do not reflect the current stage parameters.<Br />
    ///           The absolute maximum velocity and acceleration constants are initialized from the stage settings..</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="maxVelocity">  Address of the parameter to receive the absolute maximum velocity in real world units. </param>
	/// <param name="maxAcceleration"> Address of the parameter to receive the absolute maximum acceleration in real world units. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_SetMotorVelocityLimits(char const * serialNo, double maxVelocity, double maxAcceleration)" />
	KCUBEDCSERVO_API short __cdecl CC_GetMotorVelocityLimits(char const * serialNo, double *maxVelocity, double *maxAcceleration);

	/// <summary>	Reset the rotation modes for a rotational device. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_SetRotationModes(char const * serialNo, MOT_MovementModes mode, MOT_MovementDirections direction)" />
	KCUBEDCSERVO_API short __cdecl CC_ResetRotationModes(char const * serialNo);

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
	/// <seealso cref="CC_ResetRotationModes(char const * serialNo)" />
	KCUBEDCSERVO_API short __cdecl CC_SetRotationModes(char const * serialNo, MOT_MovementModes mode, MOT_MovementDirections direction);

	/// \deprecated
	/// <summary> Sets the absolute minimum and maximum travel range constants for the current stage. </summary>
	/// <remarks> These parameters are maintained for user info only and do not reflect the current travel range of the stage.<Br />
    ///           The absolute minimum and maximum travel range constants are initialized from the stage settings. These values can be adjusted to relative positions based upon the Home Offset.<Br />
    ///           <Br />
    ///           To set the working travel range of the stage use the function <see cref="CC_SetStageAxisLimits(char const * serialNo, int minPosition, int maxPosition)" /><Br />
    ///           Use the following to convert between real worl and device units.<Br />
    ///           <see cref="CC_GetRealValueFromDeviceUnit(char const * serialNo, int device_unit, double *real_unit, int unitType)" /><Br />
    ///           <see cref="CC_GetDeviceUnitFromRealValue(char const * serialNo, double real_unit, int *device_unit, int unitType)" /> </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="minPosition">  The absolute minimum position in real world units. </param>
	/// <param name="maxPosition"> The absolute maximum position in real world units. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetMotorTravelLimits(char const * serialNo, double *minPosition, double *maxPosition)" />
	KCUBEDCSERVO_API short __cdecl CC_SetMotorTravelLimits(char const * serialNo, double minPosition, double maxPosition);

	/// <summary> Gets the absolute minimum and maximum travel range constants for the current stage. </summary>
	/// <remarks> These parameters are maintained for user info only and do not reflect the current travel range of the stage.<Br />
    ///           The absolute minimum and maximum travel range constants are initialized from the stage settings. These values can be adjusted to relative positions based upon the Home Offset.</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="minPosition">  Address of the parameter to receive the absolute minimum position in real world units. </param>
	/// <param name="maxPosition"> Address of the parameter to receive the absolute maximum position in real world units. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_SetMotorTravelLimits(char const * serialNo, double minPosition, double maxPosition)" />
	KCUBEDCSERVO_API short __cdecl CC_GetMotorTravelLimits(char const * serialNo, double *minPosition, double *maxPosition);

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
	/// <seealso cref="CC_GetDeviceUnitFromRealValue(char const * serialNo, double real_unit, int *device_unit, int unitType)" />
	KCUBEDCSERVO_API short __cdecl CC_GetRealValueFromDeviceUnit(char const * serialNo, int device_unit, double *real_unit, int unitType);

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
	/// <seealso cref="CC_GetRealValueFromDeviceUnit(char const * serialNo, int device_unit, double *real_unit, int unitType)" />
	KCUBEDCSERVO_API short __cdecl CC_GetDeviceUnitFromRealValue(char const * serialNo, double real_unit, int *device_unit, int unitType);

	/// <summary> Requests the digital output bits. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_SetDigitalOutputs(char const * serialNo, byte outputsBits)" />
	/// <seealso cref="CC_GetDigitalOutputs(char const * serialNo)" />
	KCUBEDCSERVO_API short __cdecl CC_RequestDigitalOutputs(char const * serialNo);

	/// <summary> Gets the digital output bits. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> Bit mask of states of the 4 digital output pins. </returns>
	/// <seealso cref="CC_SetDigitalOutputs(char const * serialNo, byte outputsBits)" />
	/// <seealso cref="CC_RequestDigitalOutputs(char const * serialNo)" />
	KCUBEDCSERVO_API byte __cdecl CC_GetDigitalOutputs(char const * serialNo);

	/// <summary> Sets the digital output bits. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="outputsBits"> Bit mask to set states of the 4 digital output pins. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="CC_GetDigitalOutputs(char const * serialNo)" />
	/// <seealso cref="CC_RequestDigitalOutputs(char const * serialNo)" />
	KCUBEDCSERVO_API short __cdecl CC_SetDigitalOutputs(char const * serialNo, byte outputsBits);
/** @} */ // KCubeDCServo
}
