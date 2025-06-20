// summary:	Declares the stepper motor class
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MODULARRACKDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MODULARRACK_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#pragma once

#ifdef MODULARRACKDLL_EXPORTS
#define MODULARRACK_API __declspec(dllexport)
#else
#define MODULARRACK_API __declspec(dllimport)
#endif

#include <OaIdl.h>

#include "Thorlabs.MotionControl.ModularRack.h"

/** @defgroup ModularStepper Modular Stepper Motor
 *  This section details the Structures and Functions relavent to the  @ref MST601_page "Modular Stepper Motor"<br />
 *  For an example of how to connect to the device and perform simple operations use the following links:
 *  <list type=bullet>
 *    <item> \ref namespaces_mst_ex_1 "Example of using the Thorlabs.MotionControl.ModularRack.DLL for a Stepper Motor from a C or C++ project."<br />
 *									  This requires the DLL to be dynamical linked. </item>
 *    <item> \ref namespaces_mst_ex_2 "Example of using the Thorlabs.MotionControl.ModularRack.DLL for a Stepper Motor from a C# project"<br />
 *									  This uses Marshalling to load and access the C DLL. </item>
 *  </list>
 *  The Thorlabs.MotionControl.ModularRack.DLL requires the following DLLs
 *  <list type=bullet>
 *    <item> Thorlabs.MotionControl.Benchtop.StepperMotor. </item>
 *    <item> Thorlabs.MotionControl.Benchtop.NanoTrak. </item>
 *    <item> Thorlabs.MotionControl.Benchtop.Piezo. </item>
 *    <item> Thorlabs.MotionControl.DeviceManager. </item>
 *  </list>
 *  @{
 */
extern "C"
{
	/// \cond NOT_MASTER
	
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

#pragma pack(1)
	
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

	#pragma pack()

	/// <summary> Disable the channel so that motor can be moved by hand. </summary>
	/// <remarks> When disabled power is removed from the motor and it can be freely moved.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">  The channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="MMR_EnableChannel(char const * serialNo, short channel)" />
	MODULARRACK_API short __cdecl SBC_DisableChannel(char const * serialNo, short channel);

	/// <summary> Enable channel for computer control. </summary>
	/// <remarks> When enabled power is applied to the motor so it is fixed in position.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="channel">  The channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="MMR_DisableChannel(char const * serialNo, short channel)" />
	MODULARRACK_API short __cdecl SBC_EnableChannel(char const * serialNo, short channel);

	/// <summary> Set the calibration file for this motor. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <param name="filename"> Filename of the calibration file to load. </param>
	/// <param name="enabled">  <c>true</c> to enable,  <c>false</c> to disable. </param>
	/// <seealso cref="SBC_IsCalibrationActive(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_GetCalibrationFile(char const * serialNo, short channel, char * filename, short sizeOfBuffer)" />
	MODULARRACK_API void __cdecl SBC_SetCalibrationFile(char const * serialNo, short channel, char const *filename, bool enabled);

	/// <summary> Is a calibration file active for this motor. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <returns> <c>true</c> if A calibration file is active. </returns>
	/// <seealso cref="SBC_GetCalibrationFile(char const * serialNo, short channel, char * filename, short sizeOfBuffer)" />
	/// <seealso cref="SBC_SetCalibrationFile(char const * serialNo, short channel, char const *filename, bool enabled)" />
	MODULARRACK_API bool __cdecl SBC_IsCalibrationActive(char const * serialNo, short channel);

	/// <summary> Get calibration file for this motor. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <param name="filename"> Address of an output buffer to receive the filename. </param>
	/// <param name="sizeOfBuffer"> The size of the filename output buffer. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="SBC_IsCalibrationActive(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_SetCalibrationFile(char const * serialNo, short channel, char const *filename, bool enabled)" />
	MODULARRACK_API bool __cdecl SBC_GetCalibrationFile(char const * serialNo, short channel, char * filename, short sizeOfBuffer);

	/// <summary> Get number of positions. </summary>
	/// <remarks> The GetNumberPositions function will get the maximum position reachable by the device.<br />
	/// 		  The motor may need to be \ref C_MOTOR_sec10 "Homed" before this parameter can be used. </remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <returns> The number of positions. </returns>
	/// <seealso cref="SBC_MoveToPosition(char const * serialNo, short channel, int index)" />
	/// <seealso cref="SBC_GetPosition(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_Home(char const * serialNo, short channel)" />
    /// 		  \include CodeSnippet_move.cpp
	MODULARRACK_API int __cdecl SBC_GetNumberPositions(char const * serialNo, short channel);

	/// <summary> Move the device to the specified position (index). </summary>
	/// <remarks> The motor may need to be \ref C_MOTOR_sec10 "Homed" before a position can be set<br />
	/// 		  see \ref C_MOTOR_sec11 "Positioning" for more detail. </remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <param name="index">   	The position in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if move successfully started. </returns>
	/// <seealso cref="SBC_GetNumberPositions(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_SetVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="SBC_GetPosition(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_GetVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="SBC_GetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters  *velocityParameters)" />
	/// <seealso cref="SBC_SetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters *velocityParameters)" />
	/// <seealso cref="SBC_MoveRelative(char const * serialNo, short channel, int displacement)" />
	/// <seealso cref="SBC_MoveAtVelocity(char const * serialNo, short channel, MOT_TravelDirection direction)" />
    /// 		  \include CodeSnippet_move.cpp
	MODULARRACK_API short __cdecl SBC_MoveToPosition(char const * serialNo, short channel, int index);

	/// <summary> Get the current position. </summary>
	/// <remarks> The current position is the last recorded position.<br />
	/// 		  The current position is updated either by the polling mechanism or<br />
	/// 		  by calling <see cref="RequestPosition" /> or <see cref="RequestStatus" />.</remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <returns> The current position in \ref DeviceUnits_page. </returns>
	/// <seealso cref="SBC_GetNumberPositions(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_MoveToPosition(char const * serialNo, short channel, int index)" />
	/// <seealso cref="SBC_Home(char const * serialNo, short channel)" />
    /// 		  \include CodeSnippet_move.cpp
	MODULARRACK_API int __cdecl SBC_GetPosition(char const * serialNo, short channel);

	/// <summary> Can the device perform a Home. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <returns> <c>true</c> if the device can home. </returns>
	MODULARRACK_API bool __cdecl SBC_CanHome(char const * serialNo, short channel);

	/// \deprecated
	/// <summary> Does the device need to be Homed before a move can be performed. </summary>
	/// <remarks> superceded by <see cref="SBC_CanMoveWithoutHomingFirst(char const * serialNo, short channel)"/> </remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <returns> <c>true</c> if the device needs homing. </returns>
	MODULARRACK_API bool __cdecl SBC_NeedsHoming(char const * serialNo, short channel);

	/// <summary> Can this device be moved without Homing. </summary>
	/// <param name="serialNo"> The serial no. </param>
	/// <param name="channel">  The channel. </param>
	/// <returns> <c>true</c> if the device does not need to be homed before a move can be commanded. </returns>
	MODULARRACK_API bool __cdecl SBC_CanMoveWithoutHomingFirst(char const * serialNo, short channel);

	/// <summary> Home the device. </summary>
	/// <remarks> Homing the device will set the device to a known state and determine the home position,<br />
	/// 		  see \ref C_MOTOR_sec10 "Homing" for more detail. </remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if move successfully started. </returns>
	/// <seealso cref="SBC_GetNumberPositions(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_MoveToPosition(char const * serialNo, short channel, int index)" />
	/// <seealso cref="SBC_GetPosition(char const * serialNo, short channel)" />
    /// 		  \include CodeSnippet_move.cpp
	MODULARRACK_API short __cdecl SBC_Home(char const * serialNo, short channel);

	/// <summary> Gets the homing velocity. </summary>
	/// <remarks> see \ref C_MOTOR_sec10 "Homing" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <returns> The homing velocity in \ref DeviceUnits_page. </returns>
	/// <seealso cref="SBC_SetHomingVelocity(char const * serialNo, short channel, unsigned int velocity)" />
	/// <seealso cref="SBC_GetHomingParamsBlock(char const * serialNo, short channel, MOT_HomingParameters *homingParams)" />
	/// <seealso cref="SBC_SetHomingParamsBlock(char const * serialNo, short channel, MOT_HomingParameters *homingParams)" />
	MODULARRACK_API unsigned int __cdecl SBC_GetHomingVelocity(char const * serialNo, short channel);

	/// <summary> Sets the homing velocity. </summary>
	/// <remarks> see \ref C_MOTOR_sec10 "Homing" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <param name="velocity"> The homing velocity in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetHomingVelocity(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_GetHomingParamsBlock(char const * serialNo, short channel, MOT_HomingParameters *homingParams)" />
	/// <seealso cref="SBC_SetHomingParamsBlock(char const * serialNo, short channel, MOT_HomingParameters *homingParams)" />
	MODULARRACK_API short __cdecl SBC_SetHomingVelocity(char const * serialNo, short channel, unsigned int velocity);

	/// <summary> Move the motor by a relative amount. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <param name="displacement"> Signed displacement in \ref DeviceUnits_page.</param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetNumberPositions(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_GetVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="SBC_SetVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="SBC_GetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters  *velocityParameters)" />
	/// <seealso cref="SBC_SetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters *velocityParameters)" />
	/// <seealso cref="SBC_MoveToPosition(char const * serialNo, short channel, int index)" />
	/// <seealso cref="SBC_MoveAtVelocity(char const * serialNo, short channel, MOT_TravelDirection direction)" />
    /// 		  \include CodeSnippet_move.cpp
	MODULARRACK_API short __cdecl SBC_MoveRelative(char const * serialNo, short channel, int displacement);

	/// <summary> Gets the jog mode. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
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
	/// <seealso cref="SBC_SetJogMode(char const * serialNo, short channel, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="SBC_GetJogStepSize(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_SetJogStepSize(char const * serialNo, short channel, unsigned int stepSize)" />
	/// <seealso cref="SBC_SetJogVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="SBC_GetJogVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="SBC_GetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParameters)" />
	/// <seealso cref="SBC_SetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParameters)" />
	/// <seealso cref="SBC_MoveJog(char const * serialNo, short channel, MOT_TravelDirection jogDirection)" />
    /// 		  \include CodeSnippet_jogpars.cpp
	MODULARRACK_API short __cdecl SBC_GetJogMode(char const * serialNo, short channel, MOT_JogModes * mode, MOT_StopModes * stopMode);

	/// <summary> Sets the jog mode. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
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
	/// <seealso cref="SBC_GetJogMode(char const * serialNo, short channel, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="SBC_GetJogStepSize(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_SetJogStepSize(char const * serialNo, short channel, unsigned int stepSize)" />
	/// <seealso cref="SBC_SetJogVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="SBC_GetJogVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="SBC_GetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParameters)" />
	/// <seealso cref="SBC_SetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParameters)" />
	/// <seealso cref="SBC_MoveJog(char const * serialNo, short channel, MOT_TravelDirection jogDirection)" />
    /// 		  \include CodeSnippet_jogpars.cpp
	MODULARRACK_API short __cdecl SBC_SetJogMode(char const * serialNo, short channel, MOT_JogModes mode, MOT_StopModes stopMode);

	/// <summary> Gets the distance to move when jogging. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <returns> The step in \ref DeviceUnits_page. </returns>
	/// <seealso cref="SBC_GetJogMode(char const * serialNo, short channel, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="SBC_SetJogMode(char const * serialNo, short channel, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="SBC_SetJogStepSize(char const * serialNo, short channel, unsigned int stepSize)" />
	/// <seealso cref="SBC_SetJogVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="SBC_GetJogVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="SBC_GetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParameters)" />
	/// <seealso cref="SBC_SetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParameters)" />
	/// <seealso cref="SBC_MoveJog(char const * serialNo, short channel, MOT_TravelDirection jogDirection)" />
    /// 		  \include CodeSnippet_jogpars.cpp
	MODULARRACK_API unsigned int __cdecl SBC_GetJogStepSize(char const * serialNo, short channel);

	/// <summary> Sets the distance to move on jogging. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <param name="stepSize"> The step in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetJogMode(char const * serialNo, short channel, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="SBC_SetJogMode(char const * serialNo, short channel, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="SBC_GetJogStepSize(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_SetJogVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="SBC_GetJogVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="SBC_GetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParameters)" />
	/// <seealso cref="SBC_SetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParameters)" />
	/// <seealso cref="SBC_MoveJog(char const * serialNo, short channel, MOT_TravelDirection jogDirection)" />
    /// 		  \include CodeSnippet_jogpars.cpp
	MODULARRACK_API short __cdecl SBC_SetJogStepSize(char const * serialNo, short channel, unsigned int stepSize);

	/// <summary> Gets the jog velocity parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <param name="acceleration"> Address of the parameter to receive the acceleration in \ref DeviceUnits_page. </param>
	/// <param name="maxVelocity"> Address of the parameter to receive the velocity in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetJogMode(char const * serialNo, short channel, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="SBC_SetJogMode(char const * serialNo, short channel, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="SBC_GetJogStepSize(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_SetJogStepSize(char const * serialNo, short channel, unsigned int stepSize)" />
	/// <seealso cref="SBC_SetJogVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="SBC_GetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParameters)" />
	/// <seealso cref="SBC_SetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParameters)" />
	/// <seealso cref="SBC_MoveJog(char const * serialNo, short channel, MOT_TravelDirection jogDirection)" />
    /// 		  \include CodeSnippet_jogpars.cpp
	MODULARRACK_API short __cdecl SBC_GetJogVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity);

	/// <summary> Sets jog velocity parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <param name="acceleration">   The acceleration in \ref DeviceUnits_page. </param>
	/// <param name="maxVelocity"> The maximum velocity in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetJogMode(char const * serialNo, short channel, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="SBC_SetJogMode(char const * serialNo, short channel, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="SBC_GetJogStepSize(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_SetJogStepSize(char const * serialNo, short channel, unsigned int stepSize)" />
	/// <seealso cref="SBC_GetJogVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="SBC_GetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParameters)" />
	/// <seealso cref="SBC_SetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParameters)" />
	/// <seealso cref="SBC_MoveJog(char const * serialNo, short channel, MOT_TravelDirection jogDirection)" />
    /// 		  \include CodeSnippet_jogpars.cpp
	MODULARRACK_API short __cdecl SBC_SetJogVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity);

	/// <summary> Perform a jog. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <param name="jogDirection"> The jog direction
	/// 					 <list type=table>
	///							<item><term>Forwards</term><term>1</term></item>
	///							<item><term>Backwards</term><term>2</term></item>
	/// 					 </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetJogMode(char const * serialNo, short channel, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="SBC_SetJogMode(char const * serialNo, short channel, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="SBC_GetJogStepSize(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_SetJogStepSize(char const * serialNo, short channel, unsigned int stepSize)" />
	/// <seealso cref="SBC_SetJogVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="SBC_GetJogVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="SBC_GetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParameters)" />
	/// <seealso cref="SBC_SetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParameters)" />
    /// 		  \include CodeSnippet_jog.cpp
	MODULARRACK_API short __cdecl SBC_MoveJog(char const * serialNo, short channel, MOT_TravelDirection jogDirection);

	/// <summary> Gets the move velocity parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec11 "Positioning" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <param name="acceleration"> Address of the parameter to receive the acceleration value in \ref DeviceUnits_page. </param>
	/// <param name="maxVelocity"> Address of the parameter to receive the maximum velocity value in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_SetVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="SBC_GetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters  *velocityParameters)" />
	/// <seealso cref="SBC_SetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters *velocityParameters)" />
	/// <seealso cref="SBC_MoveToPosition(char const * serialNo, short channel, int index)" />
	/// <seealso cref="SBC_MoveRelative(char const * serialNo, short channel, int displacement)" />
	/// <seealso cref="SBC_MoveAtVelocity(char const * serialNo, short channel, MOT_TravelDirection direction)" />
    /// 		  \include CodeSnippet_movepars.cpp
	MODULARRACK_API short __cdecl SBC_GetVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity);

	/// <summary> Sets the move velocity parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec11 "Positioning" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <param name="acceleration"> The new acceleration value in \ref DeviceUnits_page. </param>
	/// <param name="maxVelocity"> The new maximum velocity value in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="SBC_GetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters  *velocityParameters)" />
	/// <seealso cref="SBC_SetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters *velocityParameters)" />
	/// <seealso cref="SBC_MoveToPosition(char const * serialNo, short channel, int index)" />
	/// <seealso cref="SBC_MoveRelative(char const * serialNo, short channel, int displacement)" />
	/// <seealso cref="SBC_MoveAtVelocity(char const * serialNo, short channel, MOT_TravelDirection direction)" />
    /// 		  \include CodeSnippet_movepars.cpp
	MODULARRACK_API short __cdecl SBC_SetVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity);

	/// <summary> Start moving at the current velocity in the specified direction. </summary>
	/// <remarks> see \ref C_MOTOR_sec11 "Positioning" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <param name="direction"> The required direction of travel.
	/// 					 <list type=table>
	///							<item><term>Forwards</term><term>1</term></item>
	///							<item><term>Backwards</term><term>2</term></item>
	/// 					 </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="SBC_SetVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="SBC_GetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters  *velocityParameters)" />
	/// <seealso cref="SBC_SetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters *velocityParameters)" />
	/// <seealso cref="SBC_MoveToPosition(char const * serialNo, short channel, int index)" />
	/// <seealso cref="SBC_MoveRelative(char const * serialNo, short channel, int displacement)" />
    /// 		  \include CodeSnippet_move.cpp
	MODULARRACK_API short __cdecl SBC_MoveAtVelocity(char const * serialNo, short channel, MOT_TravelDirection direction);

	/// <summary> Sets the motor direction sense. </summary>
	/// <remarks> This function is used because some actuators use have directions of motion reversed.<br />
	/// 		  This parameter will tell the system to reverse the direction sense whnd moving, jogging etc. </remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <param name="reverse"> if  <c>true</c> then directions will be swapped on these moves. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	MODULARRACK_API short __cdecl SBC_SetDirection(char const * serialNo, short channel, bool reverse);

	/// <summary> Stop the current move immediately (with risk of losing track of position). </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_StopProfiled(char const * serialNo, short channel)" />
	MODULARRACK_API short __cdecl SBC_StopImmediate(char const * serialNo, short channel);

	/// <summary> Stop the current move using the current velocity profile. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_StopImmediate(char const * serialNo, short channel)" />
	MODULARRACK_API short __cdecl SBC_StopProfiled(char const * serialNo, short channel);

	/// <summary> Get the backlash distance setting (used to control hysteresis). </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <returns> The backlash distance in \ref DeviceUnits_page. </returns>
	/// <seealso cref="SBC_SetBacklash(char const * serialNo, short channel, long distance)" />
	MODULARRACK_API long __cdecl SBC_GetBacklash(char const * serialNo, short channel);

	/// <summary> Sets the backlash distance (used to control hysteresis). </summary>
	/// <param name="serialNo">  The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <param name="distance"> The distance in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetBacklash(char const * serialNo, short channel)" />
	MODULARRACK_API short __cdecl SBC_SetBacklash(char const * serialNo, short channel, long distance);

	/// <summary> Get the Position Counter. </summary>
	/// <remarks> The position counter is identical to the position parameter.<br />
	/// 		  The position counter is set to zero when homing is complete.<br />
	/// 		  The position counter can also be set using <see cref="SBC_SetPositionCounter(char const * serialNo, short channel, long count)" /> <br />
	/// 		  if homing is not to be perforned</remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <returns> Position count in \ref DeviceUnits_page. </returns>
	/// <seealso cref="SBC_GetPosition(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_SetPositionCounter(char const * serialNo, short channel, long count)" />
	MODULARRACK_API long __cdecl SBC_GetPositionCounter(char const * serialNo, short channel);

	/// <summary> Set the Position Counter. </summary>
	/// <remarks> Setting the position counter will locate the current position. <br />
	/// 		  Setting the position counter will effectively define the home position of a motor. </remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <param name="count"> Position count in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetPositionCounter(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_GetPosition(char const * serialNo, short channel)" />
	MODULARRACK_API short __cdecl SBC_SetPositionCounter(char const * serialNo, short channel, long count);

	/// <summary> Get the Encoder Counter. </summary>
	/// <remarks> For devices that have an encoder, the current encoder position can be read. </remarks>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <returns> Encoder count of encoder units. </returns>
	/// <seealso cref="SBC_SetEncoderCounter(char const * serialNo, short channel, long count)" />
	MODULARRACK_API long __cdecl SBC_GetEncoderCounter(char const * serialNo, short channel);

	/// <summary> Set the Encoder Counter values. </summary>
	/// <remarks> setting the encoder counter to zero, effectively defines a home position on the encoder strip.<br />
	/// 		  NOTE, setting this value does not move the device.</remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <param name="count"> The encoder count in encoder units. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetEncoderCounter(char const * serialNo, short channel)" />
	MODULARRACK_API short __cdecl SBC_SetEncoderCounter(char const * serialNo, short channel, long count);


	/// <summary> Gets the limit switch parameters. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
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
	/// <seealso cref="SBC_SetLimitSwitchParams(char const * serialNo, short channel, MOT_LimitSwitchModes clockwiseHardwareLimit, MOT_LimitSwitchModes anticlockwiseHardwareLimit, unsigned int clockwisePosition, unsigned int anticlockwisePosition, MOT_LimitSwitchSWModes softLimitMode)" />
	MODULARRACK_API short __cdecl SBC_GetLimitSwitchParams(char const * serialNo, short channel, MOT_LimitSwitchModes * clockwiseHardwareLimit, MOT_LimitSwitchModes * anticlockwiseHardwareLimit, unsigned int * clockwisePosition, unsigned int * anticlockwisePosition, MOT_LimitSwitchSWModes * softLimitMode);

	/// <summary> Sets the limit switch parameters. </summary>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <param name="serialNo">	The controller serial no. </param>
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
	/// <seealso cref="SBC_SetLimitSwitchParams(char const * serialNo, short channel, MOT_LimitSwitchModes clockwiseHardwareLimit, MOT_LimitSwitchModes anticlockwiseHardwareLimit, unsigned int clockwisePosition, unsigned int anticlockwisePosition, MOT_LimitSwitchSWModes softLimitMode)" />
	MODULARRACK_API short __cdecl SBC_SetLimitSwitchParams(char const * serialNo, short channel, MOT_LimitSwitchModes clockwiseHardwareLimit, MOT_LimitSwitchModes anticlockwiseHardwareLimit, unsigned int clockwisePosition, unsigned int anticlockwisePosition, MOT_LimitSwitchSWModes softLimitMode);

	/// <summary> Gets the software limits mode. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <returns>	The software limits mode <list type=table>
	///							<item><term> Disable any move outside of the current travel range of the stage. </term><term>0</term></item>
	///							<item><term> Truncate moves to within the current travel range of the stage. </term><term>1</term></item>
	///							<item><term> Allow all moves, regardless of whether they are within the current travel range of the stage. </term><term>2</term></item>
	/// 		  </list>. </returns>
	/// <returns> The software limits mode. </returns>
	/// <seealso cref="SBC_SetLimitsSoftwareApproachPolicy(const char * serialNo, MOT_LimitsSoftwareApproachPolicy limitsSoftwareApproachPolicy)" />
	MODULARRACK_API MOT_LimitsSoftwareApproachPolicy __cdecl SBC_GetSoftLimitMode(char const * serialNo, short channel);

	/// <summary> Sets the software limits mode. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <param name="limitsSoftwareApproachPolicy"> The soft limit mode
	/// 					 <list type=table>
	///							<item><term> Disable any move outside of the current travel range of the stage. </term><term>0</term></item>
	///							<item><term> Truncate moves to within the current travel range of the stage. </term><term>1</term></item>
	///							<item><term> Allow all moves, regardless of whether they are within the current travel range of the stage. </term><term>2</term></item>
	/// 					 </list> </param>
	/// <seealso cref="SBC_GetSoftLimitMode(const char * serialNo)" />
	MODULARRACK_API void __cdecl SBC_SetLimitsSoftwareApproachPolicy(char const * serialNo, short channel, MOT_LimitsSoftwareApproachPolicy limitsSoftwareApproachPolicy);

	/// <summary> Get the move velocity parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec11 "Positioning" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <param name="velocityParameters"> Address of the MOT_VelocityParameters to recieve the velocity parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="SBC_SetVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="SBC_SetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters *velocityParameters)" />
	/// <seealso cref="SBC_MoveToPosition(char const * serialNo, short channel, int index)" />
	/// <seealso cref="SBC_MoveRelative(char const * serialNo, short channel, int displacement)" />
	/// <seealso cref="SBC_MoveAtVelocity(char const * serialNo, short channel, MOT_TravelDirection direction)" />
    /// 		  \include CodeSnippet_movepars.cpp
    MODULARRACK_API short __cdecl SBC_GetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters  *velocityParameters);

	/// <summary> Set the move velocity parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec11 "Positioning" for more detail.<remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <param name="velocityParameters"> The address of the MOT_VelocityParameters holding the new velocity parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="SBC_SetVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="SBC_GetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters  *velocityParameters)" />
	/// <seealso cref="SBC_MoveToPosition(char const * serialNo, short channel, int index)" />
	/// <seealso cref="SBC_MoveRelative(char const * serialNo, short channel, int displacement)" />
	/// <seealso cref="SBC_MoveAtVelocity(char const * serialNo, short channel, MOT_TravelDirection direction)" />
    /// 		  \include CodeSnippet_movepars.cpp
	MODULARRACK_API short __cdecl SBC_SetVelParamsBlock(char const * serialNo, short channel, MOT_VelocityParameters *velocityParameters);

	/// <summary> Sets the move absolute position. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <param name="position"> The absolute position in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetMoveAbsolutePosition(const char * serialNo, short channel)" />
	/// <seealso cref="SBC_MoveAbsolute(const char * serialNo, short channel)" />
	MODULARRACK_API short __cdecl SBC_SetMoveAbsolutePosition(const char * serialNo, short channel, int position);

	/// <summary> Gets the move absolute position. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <returns> The move absolute position in \ref DeviceUnits_page. </returns>
	/// <seealso cref="SBC_SetMoveAbsolutePosition(const char * serialNo, short channel, int position)" />
	/// <seealso cref="SBC_MoveAbsolute(const char * serialNo, short channel)" />
	MODULARRACK_API int __cdecl SBC_GetMoveAbsolutePosition(const char * serialNo, short channel);

	/// <summary> Moves the device to the position defined in the SetMoveAbsolute command. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_SetMoveAbsolutePosition(const char * serialNo, short channel, int position)" />
	/// <seealso cref="SBC_GetMoveAbsolutePosition(const char * serialNo, short channel)" />
	MODULARRACK_API short __cdecl SBC_MoveAbsolute(const char * serialNo, short channel);

	/// <summary> Sets the move relative distance. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <param name="distance"> The relative distance in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetMoveRelativeDistance(const char * serialNo, short channel)" />
	/// <seealso cref="SBC_MoveRelativeDistance(const char * serialNo, short channel)" />
	MODULARRACK_API short __cdecl SBC_SetMoveRelativeDistance(const char * serialNo, short channel, int distance);

	/// <summary> Gets the move relative distance. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <returns> The move relative distance in \ref DeviceUnits_page. </returns>
	/// <seealso cref="SBC_SetMoveRelativeDistance(const char * serialNo, short channel, int distance)" />
	/// <seealso cref="SBC_MoveRelativeDistance(const char * serialNo, short channel)" />
	MODULARRACK_API int __cdecl SBC_GetMoveRelativeDistance(const char * serialNo, short channel);

	/// <summary> Moves the device by a relative distancce defined by SetMoveRelativeDistance. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_SetMoveRelativeDistance(const char * serialNo, short channel, int distance)" />
	/// <seealso cref="SBC_GetMoveRelativeDistance(const char * serialNo, short channel)" />
	MODULARRACK_API short __cdecl SBC_MoveRelativeDistance(const char * serialNo, short channel);

	/// <summary> Get the homing parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec10 "Homing" for more detail.<remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <param name="homingParams"> Address of the MOT_HomingParameters to recieve the homing parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetHomingVelocity(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_SetHomingVelocity(char const * serialNo, short channel, unsigned int velocity)" />
	/// <seealso cref="SBC_SetHomingParamsBlock(char const * serialNo, short channel, MOT_HomingParameters *homingParams)" />
	MODULARRACK_API short __cdecl SBC_GetHomingParamsBlock(char const * serialNo, short channel, MOT_HomingParameters *homingParams);

	/// <summary> Set the homing parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec10 "Homing" for more detail.<remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <param name="homingParams"> Address of the new homing parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetHomingVelocity(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_SetHomingVelocity(char const * serialNo, short channel, unsigned int velocity)" />
	/// <seealso cref="SBC_GetHomingParamsBlock(char const * serialNo, short channel, MOT_HomingParameters *homingParams)" />
	MODULARRACK_API short __cdecl SBC_SetHomingParamsBlock(char const * serialNo, short channel, MOT_HomingParameters *homingParams);

	/// <summary> Get the jog parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo">  The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <param name="jogParameters"> The address of the MOT_JogParameters block to recieve the jog parameters </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetJogMode(char const * serialNo, short channel, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="SBC_SetJogMode(char const * serialNo, short channel, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="SBC_GetJogStepSize(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_SetJogStepSize(char const * serialNo, short channel, unsigned int stepSize)" />
	/// <seealso cref="SBC_SetJogVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="SBC_GetJogVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="SBC_SetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParameters)" />
	/// <seealso cref="SBC_MoveJog(char const * serialNo, short channel, MOT_TravelDirection jogDirection)" />
    /// 		  \include CodeSnippet_jogpars.cpp
	MODULARRACK_API short __cdecl SBC_GetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParameters);

	/// <summary> Set the jog parameters. </summary>
	/// <remarks> see \ref C_MOTOR_sec12 "Jogging" for more detail.<remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <param name="jogParameters"> The address of the new MOT_JogParameters block. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetJogMode(char const * serialNo, short channel, MOT_JogModes * mode, MOT_StopModes * stopMode)" />
	/// <seealso cref="SBC_SetJogMode(char const * serialNo, short channel, MOT_JogModes mode, MOT_StopModes stopMode)" />
	/// <seealso cref="SBC_GetJogStepSize(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_SetJogStepSize(char const * serialNo, short channel, unsigned int stepSize)" />
	/// <seealso cref="SBC_SetJogVelParams(char const * serialNo, short channel, int acceleration, int maxVelocity)" />
	/// <seealso cref="SBC_GetJogVelParams(char const * serialNo, short channel, int * acceleration, int * maxVelocity)" />
	/// <seealso cref="SBC_GetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParameters)" />
	/// <seealso cref="SBC_MoveJog(char const * serialNo, short channel, MOT_TravelDirection jogDirection)" />
    /// 		  \include CodeSnippet_jogpars.cpp
	MODULARRACK_API short __cdecl SBC_SetJogParamsBlock(char const * serialNo, short channel, MOT_JogParameters *jogParameters);

	/// <summary> Get the limit switch parameters. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <param name="limitSwitchParams"> Address of the MOT_LimitSwitchParameters parameter to recieve the  limit switch parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_SetLimitSwitchParams(char const * serialNo, MOT_LimitSwitchModes clockwiseHardwareLimit, MOT_LimitSwitchModes anticlockwiseHardwareLimit, unsigned int clockwisePosition, unsigned int anticlockwisePosition, MOT_LimitSwitchSWModes softLimitMode)" />
	/// <seealso cref="SBC_GetLimitSwitchParams(char const * serialNo, MOT_LimitSwitchModes * clockwiseHardwareLimit, MOT_LimitSwitchModes * anticlockwiseHardwareLimit, unsigned int * clockwisePosition, unsigned int * anticlockwisePosition, MOT_LimitSwitchSWModes * softLimitMode)" />
	/// <seealso cref="SBC_SetLimitSwitchParamsBlock(const char * serialNo, MOT_LimitSwitchParameters *limitSwitchParams)" />
	MODULARRACK_API short __cdecl SBC_GetLimitSwitchParamsBlock(char const * serialNo, short channel, MOT_LimitSwitchParameters *limitSwitchParams);

	/// <summary> Set the limit switch parameters. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <param name="limitSwitchParams"> Address of the MOT_LimitSwitchParameters parameter containing the new limit switch parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetLimitSwitchParams(char const * serialNo, MOT_LimitSwitchModes * clockwiseHardwareLimit, MOT_LimitSwitchModes * anticlockwiseHardwareLimit, unsigned int * clockwisePosition, unsigned int * anticlockwisePosition, MOT_LimitSwitchSWModes * softLimitMode)" />
	/// <seealso cref="SBC_SetLimitSwitchParams(char const * serialNo, MOT_LimitSwitchModes clockwiseHardwareLimit, MOT_LimitSwitchModes anticlockwiseHardwareLimit, unsigned int clockwisePosition, unsigned int anticlockwisePosition, MOT_LimitSwitchSWModes softLimitMode)" />
	/// <seealso cref="SBC_GetLimitSwitchParamsBlock(const char * serialNo, MOT_LimitSwitchParameters *limitSwitchParams)" />
	MODULARRACK_API short __cdecl SBC_SetLimitSwitchParamsBlock(char const * serialNo, short channel, MOT_LimitSwitchParameters *limitSwitchParams);


	/// <summary> Gets the trigger switch parameter. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
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
	/// <seealso cref="SBC_SetTriggerSwitches(char const * serialNo, short channel, byte indicatorBits)" />
	MODULARRACK_API byte __cdecl SBC_GetTriggerSwitches(char const * serialNo, short channel);

	/// <summary> Sets the trigger switch parameter. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
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
	/// <seealso cref="SBC_GetTriggerSwitches(char const * serialNo, short channel)" />
	MODULARRACK_API short __cdecl SBC_SetTriggerSwitches(char const * serialNo, short channel, byte indicatorBits);

	/// <summary> Requests the digital output bits. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_SetDigitalOutputs(char const * serialNo, byte outputsBits)" />
	/// <seealso cref="SBC_GetDigitalOutputs(char const * serialNo)" />
	MODULARRACK_API short __cdecl SBC_RequestDigitalOutputs(char const * serialNo, short channel);

	/// <summary> Gets the digital output bits. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <returns> Bit mask of states of the 4 digital output pins. </returns>
	/// <seealso cref="SBC_SetDigitalOutputs(char const * serialNo, short channel, byte outputsBits)" />
	MODULARRACK_API byte __cdecl SBC_GetDigitalOutputs(char const * serialNo, short channel);

	/// <summary> Sets the digital output bits. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <param name="outputsBits"> Bit mask to set states of the 4 digital output pins. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetDigitalOutputs(char const * serialNo, short channel)" />
	MODULARRACK_API short __cdecl SBC_SetDigitalOutputs(char const * serialNo, short channel, byte outputsBits);

	/// <summary> Requests the analogue input voltage reading. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="SBC_GetDigitalOutputs(char const * serialNo, short channel)" />
	MODULARRACK_API short __cdecl SBC_RequestInputVoltage(char const * serialNo, short channel);

	/// <summary> Gets the analogue input voltage reading. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <returns> The input voltage 0-32768 corresponding to 0-5V. </returns>
	/// <seealso cref="SBC_RequestInputVoltage(char const * serialNo, short channel)" />
	MODULARRACK_API WORD __cdecl SBC_GetInputVoltage(char const * serialNo, short channel);

	/// <summary> Sets the power parameters for the stepper motor. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <param name="powerParams"> Address of the MOT_PowerParameters parameter to recieve the power parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_SetPowerParams(const char * serialNo, short channel, MOT_PowerParameters *powerParams)" />
	MODULARRACK_API short __cdecl SBC_GetPowerParams(const char * serialNo, short channel, MOT_PowerParameters *powerParams);

	/// <summary> Sets the power parameters for the stepper motor. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <param name="powerParams"> Address of the MOT_PowerParameters parameter containing the new power parameters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetPowerParams(const char * serialNo, short channel, MOT_PowerParameters *powerParams)" />
	MODULARRACK_API short __cdecl SBC_SetPowerParams(const char * serialNo, short channel, MOT_PowerParameters *powerParams);

	/// <summary> Gets the stepper motor bow index. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <returns> The bow index. </returns>
	/// <seealso cref="SBC_SetBowIndex(const char * serialNo, short channel, short bowIndex)" />
	MODULARRACK_API short __cdecl SBC_GetBowIndex(const char * serialNo, short channel);

	/// <summary> Sets the stepper motor bow index. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <param name="bowIndex"> The bow index. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetBowIndex(const char * serialNo, short channel)" />
	MODULARRACK_API short __cdecl SBC_SetBowIndex(const char * serialNo, short channel, short bowIndex);

	/// <summary> Gets the joystick parameters. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <param name="joystickParams"> The address of the MOT_JoystickParameters parameter to receive the joystick parammeters. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_SetJoystickParams(char const * serialNo, short channel, MOT_JoystickParameters *joystickParams)" />
	MODULARRACK_API short __cdecl SBC_GetJoystickParams(char const * serialNo, short channel, MOT_JoystickParameters *joystickParams);

	/// <summary> Sets the joystick parameters. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <param name="joystickParams"> The address of the MOT_JoystickParameters containing the new joystick options. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetJoystickParams(char const * serialNo, short channel, MOT_JoystickParameters *joystickParams)" />
	MODULARRACK_API short __cdecl SBC_SetJoystickParams(char const * serialNo, short channel, MOT_JoystickParameters *joystickParams);


	/// <summary> Suspend automatic messages at ends of moves. </summary>
	/// <remarks> Useful to speed up part of real-time system with lots of short moves. </remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_ResumeMoveMessages(char const * serialNo, short channel)" />
	MODULARRACK_API short __cdecl SBC_SuspendMoveMessages(char const * serialNo, short channel);

	/// <summary> Resume suspended move messages. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_SuspendMoveMessages(char const * serialNo, short channel)" />
	MODULARRACK_API short __cdecl SBC_ResumeMoveMessages(char const * serialNo, short channel);

	/// <summary> Requests the current position. </summary>
	/// <remarks> This needs to be called to get the device to send it's current position.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="SBC_StartPolling(char const * serialNo, short channel, int milliseconds)" />. </remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
    /// 		  \include CodeSnippet_move.cpp
	/// <seealso cref="SBC_GetPosition(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_StartPolling(char const * serialNo, short channel, int milliseconds)" />
	MODULARRACK_API short __cdecl SBC_RequestPosition(char const * serialNo, short channel);
	
	/// <summary> Request the status bits which identify the current motor state. </summary>
	/// <remarks> This needs to be called to get the device to send it's current status bits.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="SBC_StartPolling(char const * serialNo, short channel, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="SBC_GetStatusBits(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_StartPolling(char const * serialNo, short channel, int milliseconds)" />
	MODULARRACK_API short __cdecl SBC_RequestStatusBits(char const * serialNo, short channel);

	/// <summary>Get the current status bits. </summary>
	/// <remarks> This returns the latest status bits received from the device.<br />
	/// 		  To get new status bits, use <see cref="SBC_RequestStatusBits(char const * serialNo, short channel)" />
	/// 		  or use the polling functions, <see cref="SBC_StartPolling(char const * serialNo, short channel, int milliseconds)" />.  </remarks>
	/// <param name="channel">  The channel (1 or 2). </param>
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
	/// <seealso cref="SBC_RequestStatusBits(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_StartPolling(char const * serialNo, short channel, int milliseconds)" />
	MODULARRACK_API DWORD __cdecl SBC_GetStatusBits(char const * serialNo, short channel);

	/// <summary> Starts the internal polling loop which continuously requests position and status. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <param name="milliseconds">The milliseconds polling rate. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="SBC_StopPolling(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_PollingDuration(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_RequestStatusBits(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_RequestPosition(char const * serialNo, short channel)" />
	/// \include CodeSnippet_connectionN.cpp
	MODULARRACK_API bool __cdecl SBC_StartPolling(char const * serialNo, short channel, int milliseconds);

	/// <summary> Gets the polling loop duration. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <returns> The time between polls in milliseconds or 0 if polling is not active. </returns>
	/// <seealso cref="SBC_StartPolling(char const * serialNo, short channel, int milliseconds)" />
	/// <seealso cref="SBC_StopPolling(char const * serialNo, short channel)" />
	/// \include CodeSnippet_connectionN.cpp
	MODULARRACK_API long __cdecl SBC_PollingDuration(char const * serialNo, short channel);

	/// <summary> Stops the internal polling loop. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <seealso cref="SBC_StartPolling(char const * serialNo, short channel, int milliseconds)" />
	/// <seealso cref="SBC_PollingDuration(char const * serialNo, short channel)" />
	/// \include CodeSnippet_connectionN.cpp
	MODULARRACK_API void __cdecl SBC_StopPolling(char const * serialNo, short channel);

	/// <summary> Gets the time in milliseconds since tha last message was received from the device. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <param name="lastUpdateTimeMS"> The time since the last message was received in milliseconds. </param>
	/// <returns> True if monitoring is enabled otherwize False. </returns>
	/// <seealso cref="SBC_EnableLastMsgTimer(char const * serialNo, short channel, bool enable, __int32 lastMsgTimeout )" />
	/// <seealso cref="SBC_HasLastMsgTimerOverrun(char const * serialNo, short channel)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	MODULARRACK_API bool __cdecl SBC_TimeSinceLastMsgReceived(char const * serialNo, short channel, __int64 &lastUpdateTimeMS );

	/// <summary> Enables the last message monitoring timer. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <param name="enable"> True to enable monitoring otherwise False to disable. </param>
	/// <param name="lastMsgTimeout"> The last message error timeout in ms. 0 to disable. </param>
	/// <seealso cref="SBC_TimeSinceLastMsgReceived(char const * serialNo, short channel, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="SBC_HasLastMsgTimerOverrun(char const * serialNo, short channel)" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	MODULARRACK_API void __cdecl SBC_EnableLastMsgTimer(char const * serialNo, short channel, bool enable, __int32 lastMsgTimeout );

	/// <summary> Queries if the time since the last message has exceeded the lastMsgTimeout set by <see cref="SBC_EnableLastMsgTimer(char const * serialNo, bool enable, __int32 lastMsgTimeout )"/>. </summary>
	/// <remarks> This can be used to determine whether communications with the device is still good</remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel"> The channel (1 or 2). </param>
	/// <returns> True if last message timer has elapsed, False if monitoring is not enabled or if time of last message received is less than lastMsgTimeout. </returns>
	/// <seealso cref="SBC_TimeSinceLastMsgReceived(char const * serialNo, short channel, __int64 &lastUpdateTimeMS )" />
	/// <seealso cref="SBC_EnableLastMsgTimer(char const * serialNo, short channel, bool enable, __int32 lastMsgTimeout )" />
	/// \include CodeSnippet_connectionMonitoring.cpp
	MODULARRACK_API bool __cdecl SBC_HasLastMsgTimerOverrun(char const * serialNo, short channel);

	/// <summary> Requests that all settings are download from device. </summary>
	/// <remarks> This function requests that the device upload all it's settings to the DLL.</remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	MODULARRACK_API short __cdecl SBC_RequestSettings(char const * serialNo, short channel);

	/// <summary> Gets the Stepper Motor minimum stage position. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <returns> The Minimum position in \ref DeviceUnits_page. </returns>
	/// <seealso cref="SBC_SetStageAxisLimits(char const * serialNo, short channel, int minPosition, int maxPosition)" />
	/// <seealso cref="SBC_GetStageAxisMaxPos(char const * serialNo, short channel)" />
	MODULARRACK_API int __cdecl SBC_GetStageAxisMinPos(char const * serialNo, short channel);

	/// <summary> Gets the Stepper Motor maximum stage position. </summary>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <returns> The Maximum position in \ref DeviceUnits_page. </returns>
	/// <seealso cref="SBC_SetStageAxisLimits(char const * serialNo, short channel, int minPosition, int maxPosition)" />
	/// <seealso cref="SBC_GetStageAxisMinPos(char const * serialNo, short channel)" />
	MODULARRACK_API int __cdecl SBC_GetStageAxisMaxPos(char const * serialNo, short channel);

	/// <summary> Sets the stage axis position limits. </summary>
	/// <remarks> This function sets the limits of travel for the stage.<Br />
	/// 		  The implementation will depend upon the nature of the travel being requested and the Soft Limits mode which can be obtained using <see cref="SBC_GetSoftLimitMode(char const * serialNo)" />. <Br />
	/// 		  <B>MoveAbsolute</B>, <B>MoveRelative</B> and <B>Jog (Single Step)</B> will obey the Soft Limit Mode.
	/// 		  If the target position is outside the limits then either a full move, a partial move or no move will occur.<Br />
	/// 		  <B>Jog (Continuous)</B> and <B>Move Continuous</B> will attempt to obey the limits, but as these moves rely on position information feedback from the device to detect if the travel is exceeding the limits, the device will stop, but it is likely to overshoot the limit, especially at high velocity.<Br />
	/// 		  <B>Home</B> will always ignore the software limits.</remarks>
	/// <param name="serialNo">	The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <param name="minPosition"> The minimum position in \ref DeviceUnits_page. </param>
	/// <param name="maxPosition"> The maximum position in \ref DeviceUnits_page. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetStageAxisMinPos(char const * serialNo, short channel)" />
	/// <seealso cref="SBC_GetStageAxisMaxPos(char const * serialNo, short channel)" />
	MODULARRACK_API short __cdecl SBC_SetStageAxisLimits(char const * serialNo, short channel, int minPosition, int maxPosition);

	/// <summary> Set the motor travel mode. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <param name="travelMode"> The travel mode.
	/// 						  <list type=table>
	///								<item><term>Linear motion</term><term>1</term></item>
	///								<item><term>Rotational motion</term><term>2</term></item>
	/// 						  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetMotorTravelMode(char const * serialNo, short channel)" />
	MODULARRACK_API short __cdecl SBC_SetMotorTravelMode(char const * serialNo, short channel, MOT_TravelModes travelMode);

	/// <summary> Get the motor travel mode. </summary>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <returns> The travel mode.
	/// 						  <list type=table>
	///								<item><term>Linear motion</term><term>1</term></item>
	///								<item><term>Rotational motion</term><term>2</term></item>
	/// 						  </list> </returns>
	/// <seealso cref="SBC_SetMotorTravelMode(char const * serialNo, short channel, int travelMode)" />
	MODULARRACK_API MOT_TravelModes __cdecl SBC_GetMotorTravelMode(char const * serialNo, short channel);

	/// \deprecated
	/// <summary> Sets the motor stage parameters. </summary>
	/// <remarks> superceded by <see cref="SBC_SetMotorParamsExt(char const * serialNo, short channel, double stepsPerRevolution, double gearboxRatio, double pitch)"/> </remarks>
	/// <remarks> These parameters, when combined define the stage motion in terms of \ref RealWorldUnits_page. (mm or degrees)<br />
	/// 		  The real world unit is defined from stepsPerRev * gearBoxRatio / pitch.</remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <param name="stepsPerRev">  The steps per revolution. </param>
	/// <param name="gearBoxRatio"> The gear box ratio. </param>
	/// <param name="pitch">	    The pitch. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetMotorParams(char const * serialNo, short channel, long *stepsPerRev, long *gearBoxRatio, float *pitch)" />
	MODULARRACK_API short __cdecl SBC_SetMotorParams(char const * serialNo, short channel, long stepsPerRev, long gearBoxRatio, float pitch);

	/// \deprecated
	/// <summary> Sets the motor stage parameters. </summary>
	/// <remarks> superceded by <see cref="SBC_GetMotorParamsExt(char const * serialNo, short channel, double *stepsPerRevolution, double *gearboxRatio, double *pitch)"/> </remarks>
	/// <remarks> These parameters, when combined define the stage motion in terms of \ref RealWorldUnits_page. (mm or degrees)<br />
	/// 		  The real world unit is defined from stepsPerRev * gearBoxRatio / pitch.</remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <param name="stepsPerRev">  The steps per revolution. </param>
	/// <param name="gearBoxRatio"> The gear box ratio. </param>
	/// <param name="pitch">	    The pitch. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetMotorParams(char const * serialNo, short channel, long *stepsPerRev, long *gearBoxRatio, float *pitch)" />
	MODULARRACK_API short __cdecl SBC_GetMotorParams(char const * serialNo, short channel, long *stepsPerRev, long *gearBoxRatio, float *pitch);

	/// <summary> Sets the motor stage parameters. </summary>
	/// <remarks> These parameters, when combined define the stage motion in terms of \ref RealWorldUnits_page. (mm or degrees)<br />
	/// 		  The real world unit is defined from stepsPerRev * gearBoxRatio / pitch.</remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <param name="stepsPerRev">  The steps per revolution. </param>
	/// <param name="gearBoxRatio"> The gear box ratio. </param>
	/// <param name="pitch">	    The pitch. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetMotorParams(char const * serialNo, short channel, long *stepsPerRev, long *gearBoxRatio, float *pitch)" />
	MODULARRACK_API short __cdecl SBC_SetMotorParamsExt(char const * serialNo, short channel, double stepsPerRev, double gearBoxRatio, double pitch);

	/// <summary> Sets the motor stage parameters. </summary>
	/// <remarks> These parameters, when combined define the stage motion in terms of \ref RealWorldUnits_page. (mm or degrees)<br />
	/// 		  The real world unit is defined from stepsPerRev * gearBoxRatio / pitch.</remarks>
	/// <param name="serialNo"> The controller serial no. </param>
	/// <param name="channel">  The channel (1 or 2). </param>
	/// <param name="stepsPerRev">  The steps per revolution. </param>
	/// <param name="gearBoxRatio"> The gear box ratio. </param>
	/// <param name="pitch">	    The pitch. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetMotorParams(char const * serialNo, short channel, long *stepsPerRev, long *gearBoxRatio, float *pitch)" />
	MODULARRACK_API short __cdecl SBC_GetMotorParamsExt(char const * serialNo, short channel, double *stepsPerRev, double *gearBoxRatio, double *pitch);

	/// \deprecated
	/// <summary> Sets the absolute maximum velocity and acceleration constants for the current stage. </summary>
	/// <remarks> These parameters are maintained for user info only and do not reflect the current stage parameters.<Br />
    ///           The absolute maximum velocity and acceleration constants are initialized from the stage settings..</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="maxVelocity">  The absolute maximum velocity in real world units. </param>
	/// <param name="maxAcceleration"> The absolute maximum acceleration in real world units. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetMotorVelocityLimits(char const * serialNo, short channel, double *maxVelocity, double *maxAcceleration)" />
	MODULARRACK_API short __cdecl SBC_SetMotorVelocityLimits(char const * serialNo, short channel, double maxVelocity, double maxAcceleration);

	/// <summary> Gets the absolute maximum velocity and acceleration constants for the current stage. </summary>
	/// <remarks> These parameters are maintained for user info only and do not reflect the current stage parameters.<Br />
    ///           The absolute maximum velocity and acceleration constants are initialized from the stage settings..</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">  The channel (1 to n). </param>
	/// <param name="maxVelocity">  Address of the parameter to receive the absolute maximum velocity in real world units. </param>
	/// <param name="maxAcceleration"> Address of the parameter to receive the absolute maximum acceleration in real world units. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_SetMotorVelocityLimits(char const * serialNo, short channel, double maxVelocity, double maxAcceleration)" />
	MODULARRACK_API short __cdecl SBC_GetMotorVelocityLimits(char const * serialNo, short channel, double *maxVelocity, double *maxAcceleration);

	/// <summary>	Reset the rotation modes for a rotational device. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">		 The channel. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_SetRotationModes(char const * serialNo, MOT_MovementModes mode, MOT_MovementDirections direction)" />
	MODULARRACK_API short __cdecl SBC_ResetRotationModes(char const * serialNo, short channel);

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
	/// <seealso cref="SBC_ResetRotationModes(char const * serialNo)" />
	MODULARRACK_API short __cdecl SBC_SetRotationModes(char const * serialNo, short channel, MOT_MovementModes mode, MOT_MovementDirections direction);

	/// \deprecated
	/// <summary> Sets the absolute minimum and maximum travel range constants for the current stage. </summary>
	/// <remarks> These parameters are maintained for user info only and do not reflect the current travel range of the stage.<Br />
    ///           The absolute minimum and maximum travel range constants are initialized from the stage settings. These values can be adjusted to relative positions based upon the Home Offset.<Br />
    ///           <Br />
    ///           To set the working travel range of the stage use the function <see cref="SBC_SetStageAxisLimits(char const * serialNo, short channel, int minPosition, int maxPosition)" /><Br />
    ///           Use the following to convert between real worl and device units.<Br />
    ///           <see cref="SBC_GetRealValueFromDeviceUnit(char const * serialNo, short channel, int device_unit, double *real_unit, int unitType)" /><Br />
    ///           <see cref="SBC_GetDeviceUnitFromRealValue(char const * serialNo, short channel, double real_unit, int *device_unit, int unitType)" /> </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">		 The channel. </param>
	/// <param name="minPosition">  The absolute minimum position in real world units. </param>
	/// <param name="maxPosition"> The absolute maximum position in real world units. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetMotorTravelLimits(char const * serialNo, short channel, double *minPosition, double *maxPosition)" />
	MODULARRACK_API short __cdecl SBC_SetMotorTravelLimits(char const * serialNo, short channel, double minPosition, double maxPosition);

	/// <summary> Gets the absolute minimum and maximum travel range constants for the current stage. </summary>
	/// <remarks> These parameters are maintained for user info only and do not reflect the current travel range of the stage.<Br />
    ///           The absolute minimum and maximum travel range constants are initialized from the stage settings. These values can be adjusted to relative positions based upon the Home Offset.</remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="channel">		 The channel. </param>
	/// <param name="minPosition">  Address of the parameter to receive the absolute minimum position in real world units. </param>
	/// <param name="maxPosition"> Address of the parameter to receive the absolute maximum position in real world units. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_SetMotorTravelLimits(char const * serialNo, short channel, double minPosition, double maxPosition)" />
	MODULARRACK_API short __cdecl SBC_GetMotorTravelLimits(char const * serialNo, short channel, double *minPosition, double *maxPosition);

	/// <summary>	Converts a device unit to a real world unit. </summary>
	/// <param name="serialNo">   	The serial no. </param>
	/// <param name="device_unit">	The device unit. </param>
	/// <param name="channel">		 The channel. </param>
	/// <param name="real_unit">  	The real unit. </param>
	/// <param name="unitType">   	Type of the unit.<list type=table>
	///								<item><term>Distance</term><term>0</term></item>
	///								<item><term>Velocity</term><term>1</term></item>
	///								<item><term>Acceleration</term><term>2</term></item>
	/// 						  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="SBC_GetDeviceUnitFromRealValue(char const * serialNo, short channel, double real_unit, int *device_unit, int unitType)" />
	MODULARRACK_API short __cdecl SBC_GetRealValueFromDeviceUnit(char const * serialNo, short channel, int device_unit, double *real_unit, int unitType);

	/// <summary>	Converts a device unit to a real world unit. </summary>
	/// <param name="serialNo">   	The serial no. </param>
	/// <param name="channel">		 The channel. </param>
	/// <param name="device_unit">	The device unit. </param>
	/// <param name="real_unit">  	The real unit. </param>
	/// <param name="unitType">   	Type of the unit.<list type=table>
	///								<item><term>Distance</term><term>0</term></item>
	///								<item><term>Velocity</term><term>1</term></item>
	///								<item><term>Acceleration</term><term>2</term></item>
	/// 						  </list> </param>
	/// <returns>	Success. </returns>
	/// <seealso cref="SBC_GetRealValueFromDeviceUnit(char const * serialNo, short channel, int device_unit, double *real_unit, int unitType)" />
	MODULARRACK_API short __cdecl SBC_GetDeviceUnitFromRealValue(char const * serialNo, short channel, double real_unit, int *device_unit, int unitType);
}

/** @} */ // ModularStepper