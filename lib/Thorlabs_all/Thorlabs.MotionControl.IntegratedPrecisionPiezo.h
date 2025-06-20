
#pragma once

#ifdef INTEGRATEDPRECISIONPIEZODLL_EXPORTS
#define INTEGRATEDPRECISIONPIEZO_API __declspec(dllexport)
#else
#define INTEGRATEDPRECISIONPIEZO_API __declspec(dllimport)
#endif

#include <OaIdl.h>

/*FOR C API */
/** @defgroup IntegratedPrecisionPiezo Integrated Precision Piezo
 *  This section details the Structures and Functions relavent to the  @ref CT1P_page "Integrated Precision Piezo"<br />
 *  For an example of how to connect to the device and perform simple operations use the following links:
 *  <list type=bullet>
 *    <item> \ref namespaces_ipp_ex_1 "Example of using the Thorlabs.MotionControl.IntegratedPrecisionPiezo.DLL from a C or C++ project."<br />
 *									  This requires the DLL to be dynamical linked. </item>
 *    <item> \ref namespaces_ipp_ex_2 "Example of using the Thorlabs.MotionControl.IntegratedPrecisionPiezo.DLL from a C# project"<br />
 *									  This uses Marshalling to load and access the C DLL. </item>
 *  </list>
 *  The Thorlabs.MotionControl.IntegratedPrecisionPiezo.DLL requires the following DLLs
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

	/// <summary> The Piezo Input Source Flags. </summary>
	/// \ingroup Common
	typedef enum PZ_InputSourceFlags : short
	{
		PZ_SoftwareOnly = 0, ///<Only read input from software.
		PZ_ExternalSignal = 0x01, ///<Read input from software and External Signal.
		PZ_Potentiometer = 0x02, ///<Read input from software and Potentiometer.
		PZ_All = PZ_ExternalSignal | PZ_Potentiometer ///<Read input from all sources.
	} PZ_InputSourceFlags;

	/// <summary>The Piezo Output LUT Operating Flags. </summary>
	/// \ingroup Common
	typedef enum PZ_OutputLUTModes : short
	{
		PZ_Continuous = 0x01, ///<LUT waveform output continuously.
		PZ_Fixed = 0x02, ///<LUT waveform output for a Fixed number of cycles.
		PZ_OutputTrigEnable = 0x04, ///<Enable Output Triggering.
		PZ_InputTrigEnable = 0x08, ///<Enable Input triggering.
		PZ_OutputTrigSenseHigh = 0x10, ///<Output trigger sense is high.
		PZ_InputTrigSenseHigh = 0x20, ///<Input trigger sense is high.
		PZ_OutputGated = 0x40, ///<Output is gated.
		PZ_OutputTrigRepeat = 0x80, ///<Output trigger repeats.
	} PZ_OutputLUTModes;

	/// \endcond

		/// <summary> Values that represent PPC_FilterState. </summary>
	typedef enum PPC_DerivFilterState : short
	{
		/// <summary> An enum constant representing the filter on option. </summary>
		DerivFilterOn = 0x01,
		/// <summary> An enum constant representing the filter off option. </summary>
		DerivFilterOff = 0x02,
	} PPC_DerivFilterState;

	/// <summary> Values that represent PPC_FilterState. </summary>
	typedef enum PPC_NotchFilterState : short
	{
		/// <summary> An enum constant representing the filter on option. </summary>
		NotchFilterOn = 0x01,
		/// <summary> An enum constant representing the filter off option. </summary>
		NotchFilterOff = 0x02,
	} PPC_NotchFilterState;

	/// <summary> Values that represent PPC_NotchFilterChannel. </summary>
	typedef enum PPC_NotchFilterChannel : short
	{
		/// <summary> An enum constant representing the notch filter 1 option. </summary>
		NotchFilter1 = 0x01,
		/// <summary> An enum constant representing the notch filter 2 option. </summary>
		NotchFilter2 = 0x02,
		/// <summary> An enum constant representing the notch filter both option. </summary>
		NotchFilterBoth = 0x03,
	} PPC_NotchFilterChannel;

	/// <summary> Values that represent PPC_IOControlMode. </summary>
	typedef enum PPC_IOControlMode : short
	{
		/// <summary> An enum constant representing the software only option. </summary>
		SWOnly = 0x00,
		/// <summary> An enum constant representing the extent bnc option. </summary>
		ExtBNC = 0x01,
		/// <summary> An enum constant representing the joystick option. </summary>
		Joystick = 0x02,
		/// <summary> An enum constant representing the joystick bnc option. </summary>
		JoystickBnc = 0x03,
	} PPC_IOControlMode;

	/// <summary> Values that represent PPC_IOOutputModeMode. </summary>
	typedef enum PPC_IOOutputMode : short
	{
		/// <summary> An enum constant representing the hv option. </summary>
		HV = 0x01,
		/// <summary> An enum constant representing the position raw option. </summary>
		PosRaw = 0x02,
		/// <summary> An enum constant representing the position corrected option. </summary>
		PosCorrected = 0x03,
	} PPC_IOOutputMode;

	/// <summary> Values that represent PPC_IOOutput Bandwidth. </summary>
	typedef enum PPC_IOOutputBandwidth : short
	{
		/// <summary> An enum constant representing the operation unfiltered option. </summary>
		OP_Unfiltered = 0x01,
		/// <summary> An enum constant representing the operation 200 Hz option. </summary>
		OP_200Hz = 0x02,
	} PPC_IOOutputBandwidth;

	/// <summary> Values that represent PPC_IOSourceDefinition. </summary>
	typedef enum PPC_IOFeedbackSourceDefinition : short
	{
		/// <summary> An enum constant representing the operation unfiltered option. </summary>
		StrainGauge = 0x01,
		/// <summary> An enum constant representing the operation 200 Hz option. </summary>
		Capacitive = 0x02,
		/// <summary>	An enum constant representing the optical option (Only appicable to the PPC102). </summary>
		Optical = 0x03,
	} PPC_IOFeedbackSourceDefinition;

	/// <summary> Values that represent PPC Feedback Polarities. </summary>
	typedef enum PPC_FeedbackPolarity : WORD
	{
		/// <summary> An enum constant representing the non inverted option. </summary>
		NonInverted = 0,
		/// <summary> An enum constant representing the inverted option. </summary>
		Inverted = (WORD) -1
	} PPC_FeedbackPolarity;

	/// <summary> Values that represent PPC_DisplayIntensity. </summary>
	typedef enum PPC_DisplayIntensity : short
	{
		/// <summary> An enum constant representing the bright option. </summary>
		Bright = 0x01,
		/// <summary> An enum constant representing the dim option. </summary>
		Dim = 0x02,
		/// <summary> An enum constant representing the off option. </summary>
		Off = 0x03,
	} PPC_DisplayIntensity;

	/// <summary> PPC PID consts. </summary>
	typedef struct PPC_PIDConsts
	{
		/// <summary> PID constants proportional. </summary>
		/// <remarks> The PID Proportional Gain constant, range 0 to 10000</remarks>
		float PIDConstsP;
		/// <summary> PID constants integral. </summary>
		/// <remarks> The PID Integral Gain constant, range 0 to 10000</remarks>
		float PIDConstsI;
		/// <summary> PID constants derivative. </summary>
		/// <remarks> The PID Derivative Gain constant, range 0 to 10000</remarks>
		float PIDConstsD;
		/// <summary> PID constants derivative low pass filter cut-off frequency. </summary>
		/// <remarks> The PID Derivative Gain filter, range 0 to 10000</remarks>
		float PIDConstsDFc;
		/// <summary> PID Derivative filter on or off. </summary>
		/// <remarks> The Filter Enabled state:
		/// 		  <list type=table>
		///				<item><term>1</term><term>Filter Enabled</term></item>
		///				<item><term>2</term><term>Filter Disabled.</term></item>
		/// 		  </list></remarks>
		PPC_DerivFilterState PIDDerivFilterOn;
		/// <summary> PID index, O for normal operation </summary>
		byte PIDIndex;
	} PPC_PIDConsts;

	/// <summary> Ppc PID criteria. </summary>
	struct PPC_PIDCriteria
	{
		/// <summary> The criteria ID, has to be byte to work with request . </summary>
		uint8_t criteriaID;
		/// <summary> unused byte. </summary>
		uint8_t unusedByte;
		/// <summary> The index of the PID constants  to apply for this critera. </summary>
		uint16_t PIDConstIndex;
		/// <summary> The priority of this PID criteria, 0 is highest. </summary>
		uint16_t priority;
		/// <summary> The target error window specified as % 0 full scale (32k = +/- 100% ), or encoder counts (device dependent). </summary>
		uint16_t targetErrorWindow;
		/// <summary> not used. </summary>
		WORD wReservedPar1;
		/// <summary> not used. </summary>
		WORD wReservedPar2;
		/// <summary> not used. </summary>
		WORD wReservedPar3;

	};

	/// <summary> PPC notch filter parameters. </summary>
	typedef struct PPC_NotchParams
	{
		/// <summary> Flags that define which filters are updated with this structure. </summary>
		/// <remarks> The Notch Filter selection flags:
		/// 		  <list type=table>
		///				<item><term>1</term><term>Filter 1 parameters are updated.</term></item>
		///				<item><term>2</term><term>Filter 2 parameters are updated.</term></item>
		///				<item><term>2</term><term>Filter 1 and 2 parameters are updated.</term></item>
		/// 		  </list></remarks>
		PPC_NotchFilterChannel filterNo;
		/// <summary> Notch filter 1 centre frequency. </summary>
		/// <remarks> The Notch Filter Center Frequency, range 20 to 500Hz</remarks>
		float filter1Fc;
		/// <summary> Notch filter 1 Q. </summary>
		/// <remarks> The Notch Filter Q Value, range 0.2 to 100</remarks>
		float filter1Q;
		/// <summary> Notch filter 1 on or off. </summary>
		/// <remarks> The Filter Enabled state:
		/// 		  <list type=table>
		///				<item><term>1</term><term>Filter Enabled</term></item>
		///				<item><term>2</term><term>Filter Disabled.</term></item>
		/// 		  </list></remarks>
		PPC_NotchFilterState notchFilter1On;
		/// <summary> Notch filter 2 centre frequency. </summary>
		/// <remarks> The Notch Filter Center Frequency, range 20 to 500Hz</remarks>
		float filter2Fc;
		/// <summary> Notch filter 2 Q. </summary>
		/// <remarks> The Notch Filter Q Value, range 0.2 to 100</remarks>
		float filter2Q;
		/// <summary> Notch filter 2 on or off. </summary>
		/// <remarks> The Filter Enabled state:
		/// 		  <list type=table>
		///				<item><term>1</term><term>Filter Enabled</term></item>
		///				<item><term>2</term><term>Filter Disabled.</term></item>
		/// 		  </list></remarks>
		PPC_NotchFilterState notchFilter2On;

	} PPC_NotchParams;



	/// <summary> Values that represent Trigger Port Mode. </summary>
	typedef enum KSG_TriggerPortMode : __int16
	{
		KSG_TrigDisabled = 0x00,///< Trigger Disabled
		KSG_TrigIn_GPI = 0x01,///< General purpose logic input (<see cref="SG_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)
		KSG_TrigOut_GPO = 0x0A,///< General purpose output (<see cref="SG_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)
		KSG_TrigOut_LessThanLowerLimit = 0x0B,///< Trigger when output < lower limit
		KSG_TrigOut_MoreThanLowerLimit = 0x0C,///< Trigger when output > lower limit
		KSG_TrigOut_LessThanUpperLimit = 0x0D,///< Trigger when output < upper limit
		KSG_TrigOut_MoreThanUpperLimit = 0x0E,///< Trigger when output > upper limit
		KSG_TrigOut_BetweenLimits = 0x0F,///< Trigger when output between limits
		KSG_TrigOut_OutsideLimits = 0x10,///< Trigger when output outside limit
	} KSG_TriggerPortMode;

	/// <summary> Values that represent Trigger Port Polarity. </summary>
	typedef enum KSG_TriggerPortPolarity : __int16
	{
		KSG_TrigPolarityHigh = 0x01,///< Trigger Polarity high
		KSG_TrigPolarityLow = 0x02,///< Trigger Polarity Low
	} KSG_TriggerPortPolarity;


	/// <summary> PPC i/o settings. </summary>
	typedef struct PPC_IOSettings
	{
		/// <summary> Voltage/Position control input source. </summary>
		/// <remarks> The enabled input sources:
		/// 		  <list type=table>
		///				<item><term>0</term><term>Software input only.</term></item>
		///				<item><term>1</term><term>Software and external BNC.</term></item>
		///				<item><term>2</term><term>Software and external joystick.</term></item>
		///				<item><term>2</term><term>Software, External BNC and Joystick.</term></item>
		/// 		  </list></remarks>
		PPC_IOControlMode controlSrc;
		/// <summary> Monitor output BNC signal. </summary>
		/// <remarks> The Monitor output modes:
		/// 		  <list type=table>
		///				<item><term>1</term><term>High Voltage output.</term></item>
		///				<item><term>2</term><term>Position (Uncorrected).</term></item>
		///				<item><term>2</term><term>Position (Corrected).</term></item>
		/// 		  </list></remarks>
		PPC_IOOutputMode monitorOPSig;
		/// <summary> Monitor output bandwidth. </summary>
		/// <remarks> The output bandwidth modes:
		/// 		  <list type=table>
		///				<item><term>1</term><term>Unfiltered.</term></item>
		///				<item><term>2</term><term>200Hz filter.</term></item>
		/// 		  </list></remarks>
		PPC_IOOutputBandwidth monitorOPBandwidth;
		/// <summary> Type of feedback in operation. </summary>
		/// <remarks> The feedback loop mode (read only):
		/// 		  <list type=table>
		///				<item><term>1</term><term>Strain Gauge.</term></item>
		///				<item><term>2</term><term>Capacitive.</term></item>
		///				<item><term>3</term><term>Optical (PPC102 only).</term></item>
		/// 		  </list></remarks>
		PPC_IOFeedbackSourceDefinition feedbackSrc;
		/// <summary> Brightness of the from panel LED's. </summary>
		/// <remarks> The display brightness:
		/// 		  <list type=table>
		///				<item><term>1</term><term>Bright.</term></item>
		///				<item><term>2</term><term>Dim.</term></item>
		///				<item><term>3</term><term>Off.</term></item>
		/// 		  </list></remarks>
		PPC_DisplayIntensity FPBrightness;
		/// <summary> The Feedback source polarity. </summary>
		/// <remarks> The Feedback Polarity:
		/// 		  <list type=table>
		///				<item><term>0</term><term>Non Inverted.</term></item>
		///				<item><term>-1</term><term>Inverted.</term></item>
		/// 		  </list></remarks>
		PPC_FeedbackPolarity feedbackPolarity;
	} PPC_IOSettings;

	/// <summary> KCube piezo trigger configuration. </summary>
	typedef struct KSG_TriggerConfig
	{
		/// <summary> The trigger 1 mode. </summary>
		/// <remarks> The trigger 1 operating mode:
		/// 		  <list type=table>
		///				<item><term>0</term><term>Trigger disabled</term></item>
		///				<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="SG_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
		///				<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
		///				<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
		///				<item><term>10</term><term>Trigger Output - General purpose output (<see cref="SG_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
		/// 		  </list>
		/// 		  </remarks>
		KSG_TriggerPortMode Trigger1Mode;
		/// <summary> The trigger 1 polarity. </summary>
		/// <remarks> The trigger 1 output polaritye:
		/// 		  <list type=table>
		///				<item><term>1</term><term>Output high when set</term></item>
		///				<item><term>2</term><term>Output low when set</term></item>
		/// 		  </list>
		/// 		  </remarks>
		KSG_TriggerPortPolarity Trigger1Polarity;
		/// <summary> The trigger 2 mode. </summary>
		/// <remarks> The trigger 2 operating mode:
		/// 		  <list type=table>
		///				<item><term>0</term><term>Trigger disabled</term></item>
		///				<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="SG_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
		///				<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
		///				<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
		///				<item><term>10</term><term>Trigger Output - General purpose output (<see cref="SG_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
		/// 		  </list>
		/// 		  </remarks>
		KSG_TriggerPortMode Trigger2Mode;
		/// <summary> The trigger 2 polarity. </summary>
		/// <remarks> The trigger 2 output polarity:
		/// 		  <list type=table>
		///				<item><term>1</term><term>Output high when set</term></item>
		///				<item><term>2</term><term>Output low when set</term></item>
		/// 		  </list>
		/// 		  </remarks>
		KSG_TriggerPortPolarity Trigger2Polarity;
		/// <summary> The lower limit. </summary>
		__int32 LowerLimit;
		/// <summary> The upper limit. </summary>
		__int32 UpperLimit;
		/// <summary> The smoothing samples. </summary>
		__int16 SmoothingSamples;
		/// <summary> reserved fields. </summary>
		__int16 reserved[6];
	} KSG_TriggerConfig;
	
	/// <summary> Values that represent Joystick Mode. </summary>
	enum KPZ_WheelMode : __int16
	{
		/// <summary> An enum constant representing the kmot js voltage option. </summary>
		KPZ_WM_MoveAtVoltage = 0x01,
		/// <summary> An enum constant representing the kmot js jog option. </summary>
		KPZ_WM_JogVoltage = 0x02,
		/// <summary> An enum constant representing the kmot js move absolute option. </summary>
		KPZ_WM_SetVoltage = 0x03,
	};

	/// <summary> Values that represent Joystich Rate of Change. </summary>
	enum KPZ_WheelChangeRate : __int16
	{
		/// <summary> An enum constant representing the kmot js high option. </summary>
		KPZ_WM_High = 0x01,
		/// <summary> An enum constant representing the kmot js medium option. </summary>
		KPZ_WM_Medium = 0x02,
		/// <summary> An enum constant representing the kmot js low option. </summary>
		KPZ_WM_Low = 0x03,
	};

	/// <summary> Values that represent wheel Direction. </summary>
	enum KPZ_WheelDirectionSense : __int16
	{
		/// <summary> An enum constant representing the positive direction option. </summary>
		KPZ_WM_Positive = 0x01,
		/// <summary> An enum constant representing the negative direction option. </summary>
		KPZ_WM_Negative = 0x02,
	};

#pragma pack()


	/// <summary> Open the device for communications. </summary>
	/// <param name="serialNo">	The serial no of the device to be connected. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// 		  \include CodeSnippet_connectionN.cpp
	/// <seealso cref="IPP_Close(char const * serialNo)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_Open(char const * serialNo);

	/// <summary> Disconnect and close the device. </summary>
	/// <param name="serialNo">	The serial no of the device to be disconnected. </param>
	/// 		  \include CodeSnippet_connectionN.cpp
	/// <seealso cref="IPP_Open(char const * serialNo)" />
	INTEGRATEDPRECISIONPIEZO_API void __cdecl IPP_Close(char const * serialNo);

	/// <summary>	Check connection. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> true if the USB is listed by the ftdi controller</returns>
	/// \include CodeSnippet_CheckConnection.cpp
	INTEGRATEDPRECISIONPIEZO_API bool __cdecl IPP_CheckConnection(char const * serialNo);

	/// <summary> Sends a command to the device to make it identify iteself. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	INTEGRATEDPRECISIONPIEZO_API  void __cdecl  IPP_Identify(char const * serialNo);

	/// <summary> Tells the device that it is being disconnected. </summary>
	/// <remarks> This does not disconnect the communications.<br />
	/// 		  To disconnect the communications, call the <see cref="IPP_Close(char const * serialNo)" /> function. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	INTEGRATEDPRECISIONPIEZO_API  short __cdecl  IPP_Disconnect(char const * serialNo);

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
	INTEGRATEDPRECISIONPIEZO_API  short __cdecl IPP_GetHardwareInfo(char const * serialNo, char * modelNo, DWORD sizeOfModelNo, WORD * type, WORD * numChannels,
		char * notes, DWORD sizeOfNotes, DWORD * firmwareVersion, WORD * hardwareVersion, WORD * modificationState);

	/// <summary> Gets the hardware information in a block. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="hardwareInfo"> Address of a TLI_HardwareInformation structure to receive the hardware information. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// 		  \include CodeSnippet_identify.cpp
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_GetHardwareInfoBlock(char const  *serialNo, TLI_HardwareInformation *hardwareInfo);

	/// <summary> Gets version number of the device firmware. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device firmware version number made up of 4 byte parts. </returns>
	/// 		  \include CodeSnippet_identify.cpp
	INTEGRATEDPRECISIONPIEZO_API DWORD __cdecl IPP_GetFirmwareVersion(char const * serialNo);

	/// <summary> Gets version number of the device software. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The device software version number made up of 4 byte parts. </returns>
	/// 		  \include CodeSnippet_identify.cpp
	INTEGRATEDPRECISIONPIEZO_API DWORD __cdecl IPP_GetSoftwareVersion(char const * serialNo);

	/// <summary> Update device with stored settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// 		  \include CodeSnippet_connection1.cpp
	INTEGRATEDPRECISIONPIEZO_API bool __cdecl IPP_LoadSettings(char const * serialNo);

	/// <summary> Update device with named settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="settingsName"> Name of settings stored away from device. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	///             \include CodeSnippet_connection1.cpp
	INTEGRATEDPRECISIONPIEZO_API bool __cdecl IPP_LoadNamedSettings(char const * serialNo, char const *settingsName);

	/// <summary>	Persist device settings to device. </summary>
	/// <param name="serialNo">	The serial no. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	INTEGRATEDPRECISIONPIEZO_API bool __cdecl IPP_PersistSettings(char const * serialNo);

	/// <summary> Disable the channel so that motor can be moved by hand. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="IPP_EnableChannel(char const * serialNo)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_DisableChannel(char const * serialNo);

	/// <summary> Enable channel for computer control. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="IPP_DisableChannel(char const * serialNo)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_EnableChannel(char const * serialNo);

	/// <summary> Registers a callback on the message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="functionPointer"> A function pointer to be called whenever messages are received. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_RegisterMessageCallback(char const * serialNo, void(*functionPointer)());

	/// <summary> Gets the MessageQueue size. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> number of messages in the queue. </returns>
	INTEGRATEDPRECISIONPIEZO_API int __cdecl IPP_MessageQueueSize(char const * serialNo);

	/// <summary> Clears the device message queue. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_ClearMessageQueue(char const * serialNo);

	/// <summary> Get the next MessageQueue item if it is available. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> Address of the WORD to receive the message type. </param>
	/// <param name="messageID"> Address of the WORD to receive themessage ID. </param>
	/// <param name="messageData"> Address of the DWORD to receive the messageData. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	INTEGRATEDPRECISIONPIEZO_API bool __cdecl IPP_GetNextMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Get the next MessageQueue item if it is available. </summary>
	/// <remarks> see \ref C_MESSAGES_page "Device Messages" for details on how to use messages. </remarks>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="messageType"> Address of the WORD to receive the message type. </param>
	/// <param name="messageID"> Address of the WORD to receive themessage ID. </param>
	/// <param name="messageData"> Address of the DWORD to receive the messageData. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	INTEGRATEDPRECISIONPIEZO_API bool __cdecl IPP_WaitForMessage(char const * serialNo, WORD * messageType, WORD * messageID, DWORD *messageData);

	/// <summary> Starts the internal polling loop which continuously requests position and status. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="milliseconds">The milliseconds polling rate. </param>
	/// <returns> <c>true</c> if successful, false if not. </returns>
	/// <seealso cref="IPP_StopPolling(char const * serialNo)" />
	/// <seealso cref="IPP_PollingDuration(char const * serialNo)" />
	/// <seealso cref="IPP_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="IPP_RequestPosition(char const * serialNo)" />
	/// \include CodeSnippet_connectionN.cpp
	INTEGRATEDPRECISIONPIEZO_API bool __cdecl IPP_StartPolling(char const * serialNo, int milliseconds);


	/// <summary> Gets the polling loop duration. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The time between polls in milliseconds or 0 if polling is not active. </returns>
	/// <seealso cref="IPP_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="IPP_StopPolling(char const * serialNo)" />
	/// \include CodeSnippet_connectionN.cpp
	INTEGRATEDPRECISIONPIEZO_API long __cdecl IPP_PollingDuration(char const * serialNo);

	/// <summary> Stops the internal polling loop. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <seealso cref="IPP_StartPolling(char const * serialNo, int milliseconds)" />
	/// <seealso cref="IPP_PollingDuration(char const * serialNo)" />
	/// \include CodeSnippet_connectionN.cpp
	INTEGRATEDPRECISIONPIEZO_API void __cdecl IPP_StopPolling(char const * serialNo);

	/// <summary> Requests that all settings are download from device. </summary>
	/// <remarks> This function requests that the device upload all it's settings to the DLL.</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_RequestSettings(char const * serialNo);

	/// <summary> Requests the status bits and position. </summary>
	/// <remarks> This needs to be called to get the device to send it's current position and status bits.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="IPP_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="IPP_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="IPP_GetPosition(char const * serialNo)" />
	/// <seealso cref="IPP_GetStatusBits(char const * serialNo)" />
	/// <seealso cref="IPP_StartPolling(char const * serialNo, int milliseconds)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_RequestStatus(char const * serialNo);

	/// <summary> Request the status bits which identify the current device state. </summary>
	/// <remarks> This needs to be called to get the device to send it's current status bits.<br />
	/// 		  NOTE this is called automatically if Polling is enabled for the device using <see cref="IPP_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successfully requested. </returns>
	/// <seealso cref="IPP_GetStatusBits(char const * serialNo)" />
	/// <seealso cref="IPP_StartPolling(char const * serialNo, int milliseconds)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_RequestStatusBits(char const * serialNo);

	/// <summary>Get the current status bits. </summary>
	/// <remarks> This returns the latest status bits received from the device.<br />
	/// 		  To get new status bits, use <see cref="IPP_RequestStatusBits(char const * serialNo)" /> <br />
	///			  or use <see cref="BPC_RequestStatus(char const * serialNo)" />
	/// 		  or use the polling functions, <see cref="IPP_StartPolling(char const * serialNo, int milliseconds)" />. </remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	The status bits from the device <list type=table>
	///				<item><term>0x00000001</term><term>Piezo actuator connected (1=Connected, 0=Not connected).</term></item>
	///				<item><term>0x00000002</term><term>For Future Use.</term></item>
	///				<item><term>0x00000004</term><term>For Future Use.</term></item>
	///				<item><term>0x00000008</term><term>For Future Use.</term></item>
	///				<item><term>0x00000010</term><term>For Future Use.</term></item>
	///				<item><term>0x00000020</term><term>For Future Use.</term></item>
	///				<item><term>0x00000040</term><term>For Future Use.</term></item>
	///				<item><term>0x00000080</term><term>For Future Use.</term></item>
	///				<item><term>0x00000100</term><term>For Future Use.</term></item>
	///				<item><term>0x00000200</term><term>For Future Use.</term></item>
	///				<item><term>0x00000400</term><term>Position control mode (1=Closed loop, 0=Open loop).</term></item>
	///				<item><term>0x00000800</term><term>For Future Use.</term></item>
	///				<item><term>0x00001000</term><term>5V supply below normal range</term></item>
	///				<item><term>0x00002000</term><term>5V supply is above normal range</term></item>
	///				<item><term>0x00004000</term><term>For Future Use.</term></item>
	///				<item><term>0x00080000</term><term>High Voltage Amp/PSU above normal temperature</term></item>
	///				<item><term>0x00100000</term><term>Digital input 1 state (1=Logic High, 0=Logic Low).</term></item>
	///				<item><term>0x00200000</term><term>Digital input 2 state (1=Logic High, 0=Logic Low).</term></item>
	///				<item><term>0x00400000</term><term>For Future Use.</term></item>
	///				<item><term>0x00800000</term><term>For Future Use.</term></item>
	///				<item><term>0x01000000</term><term>For Future Use.</term></item>
	///				<item><term>0x02000000</term><term>For Future Use.</term></item>
	///				<item><term>0x04000000</term><term>For Future Use.</term></item>
	///				<item><term>0x08000000</term><term>For Future Use.</term></item>
	///				<item><term>0x10000000</term><term>For Future Use.</term></item>
	///				<item><term>0x20000000</term><term>Active (1=Indicates Unit Is Active, 0=Not Active).</term></item>
	///				<item><term>0x40000000</term><term>Error (mirrors LED for rack based modules.</term></item>
	///				<item><term>0x80000000</term><term>Channel enabled (1=Enabled, 0=Disabled).</term></item>
	/// 		  </list> <remarks> Bits 21 to 28 (Digital Input States) are only applicable if the associated digital input is fitted to your controller - see the relevant handbook for more details. </remarks> </returns>
	/// <seealso cref="IPP_RequestStatusBits(char const * serialNo)" />
	/// <seealso cref="IPP_RequestStatus(char const * serialNo)" />
	/// <seealso cref="IPP_StartPolling(char const * serialNo, int milliseconds)" />
	INTEGRATEDPRECISIONPIEZO_API DWORD __cdecl IPP_GetStatusBits(char const * serialNo);

	/// <summary> Sets the voltage output to zero and defines the ensuing actuator position az zero. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_ResetParameters(char const * serialNo);

	/// <summary> Gets the minimum output voltage (-10V) in units of 1 tenth of a volt. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The minimum output voltage </returns>
	/// <seealso cref="IPP_SetMaxOutputVoltage(char const * serialNo, short maxVoltage)" />
	/// <seealso cref="IPP_GetMaxOutputVoltage(char const * serialNo)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_GetMinOutputVoltage(char const * serialNo);

	/// <summary> Gets the maximum output voltage (140V) in units of 1 tenth of a volt </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The maximum useable output voltage</returns>
	/// <seealso cref="IPP_RequestMaxOutputVoltage(char const * serialNo)" />
	/// <seealso cref="IPP_SetMaxOutputVoltage(char const * serialNo, short maxVoltage)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_GetMaxOutputVoltage(char const * serialNo);

	/// <summary> Gets the set Output Voltage. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The voltage using the range
	/// 		  -2184 to 30533 equivalent to -10V to 140V . </returns>
	/// <seealso cref="IPP_RequestOutputVoltage(char const * serialNo)" />
	/// <seealso cref="IPP_SetOutputVoltage(char const * serialNo, short volts)" />
	/// <seealso cref="IPP_SetMaxOutputVoltage(char const * serialNo, short eVoltage)" />
	/// <seealso cref="IPP_GetMaxOutputVoltage(char const * serialNo)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_GetOutputVoltage(char const * serialNo);

	/// <summary> Requests the maximum output voltage be read from the device. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="IPP_GetMaxOutputVoltage(char const * serialNo)" />
	/// <seealso cref="IPP_SetMaxOutputVoltage(char const * serialNo, short maxVoltage)" />
	INTEGRATEDPRECISIONPIEZO_API bool __cdecl IPP_RequestOutputVoltage(char const * serialNo);

	/// <summary> Sets the output voltage. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="volts">The voltage using the range
	/// 		  -2184 to 30533 equivalent to -10V to 140V .</param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="IPP_GetOutputVoltage(char const * serialNo)" />
	/// <seealso cref="IPP_RequestOutputVoltage(char const * serialNo)" />
	/// <seealso cref="IPP_SetMaxOutputVoltage(char const * serialNo, short eVoltage)" />
	/// <seealso cref="IPP_GetMaxOutputVoltage(char const * serialNo)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_SetOutputVoltage(char const * serialNo, short volts);

	/// <summary> Requests that the current input voltage source be read from the device. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="IPP_GetVoltageSource(char const * serialNo)" />
	/// <seealso cref="IPP_SetVoltageSource(char const * serialNo, PZ_InputSourceFlags source)" />
	INTEGRATEDPRECISIONPIEZO_API bool __cdecl IPP_RequestVoltageSource(char const * serialNo);

	/// <summary> Gets the control voltage source. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The voltage source. <list type=table>
	///				<item><term>Software Only</term><term>0</term></item>
	///				<item><term>Software and External</term><term>1</term></item>
	///				<item><term>Software and Potentiometer</term><term>2</term></item>
	///				<item><term>Software, External and Potentiometer</term><term>3</term></item>
	/// 		  </list> </returns>
	/// <seealso cref="IPP_RequestVoltageSource(char const * serialNo, short channel)" />
	/// <seealso cref="IPP_SetVoltageSource(char const * serialNo, PZ_InputSourceFlags source)" />
	INTEGRATEDPRECISIONPIEZO_API PZ_InputSourceFlags __cdecl IPP_GetVoltageSource(char const * serialNo);

	/// <summary> Sets the control voltage source. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="source"> The voltage source <list type=table>
	///				<item><term>Software Only</term><term>0</term></item>
	///				<item><term>Software and External</term><term>1</term></item>
	///				<item><term>Software and Potentiometer</term><term>2</term></item>
	///				<item><term>Software, External and Potentiometer</term><term>3</term></item>
	/// 		  </list> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="IPP_RequestVoltageSource(char const * serialNo)" />
	/// <seealso cref="IPP_GetVoltageSource(char const * serialNo)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_SetVoltageSource(char const * serialNo, PZ_InputSourceFlags source);

	/// <summary> Gets the PPC IO Settings. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="ioSettings"> The i/o settings <see cref="PPC_IOSettings"/>. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="IPP_SetIOSettings(const char * serialNo, PPC_IOSettings *ioSettings)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_GetIOSettings(const char * serialNo, PPC_IOSettings *ioSettings);

	/// <summary> Sets the PPC IO Setting. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="ioSettings"> The i/o setting <see cref="PPC_IOSettings"/>. </returns> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="IPP_GetIOSettings(const char * serialNo, PPC_IOSettings *ioSettings)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_SetIOSettings(const char * serialNo, PPC_IOSettings *ioSettings);

	/// <summary> Requests the curent  PPC IO Setting. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="IPP_GetIOSettings(const char * serialNo, PPC_IOSettings *ioSettings)" />
	/// <seealso cref="IPP_SetIOSettings(const char * serialNo, PPC_IOSettings *ioSettings)" />
	INTEGRATEDPRECISIONPIEZO_API bool __cdecl IPP_RequestIOSettings(char const * serialNo);

	/// <summary> Set the Trigger Configuration Parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="trigger1Mode">	    The trigger 1 mode.<list type=table>
	///						<item><term>0</term><term>Trigger disabled</term></item>
	///						<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="SG_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
	///						<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
	///						<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
	///						<item><term>10</term><term>Trigger Output - General purpose output (<see cref="SG_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
	///		 		  </list></param>
	/// <param name="trigger1Polarity"> The trigger 1 polarity.<list type=table>
	///						<item><term>1</term><term>Output high when set</term></item>
	///						<item><term>2</term><term>Output low when set</term></item>
	///		 		  </list> </param>
	/// <param name="trigger2Mode">	    The trigger 2 mode.<list type=table>
	///						<item><term>0</term><term>Trigger disabled</term></item>
	///						<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="SG_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
	///						<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
	///						<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
	///						<item><term>10</term><term>Trigger Output - General purpose output (<see cref="SG_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
	///		 		  </list></param>
	/// <param name="trigger2Polarity"> The trigger 2 polarity.<list type=table>
	///						<item><term>1</term><term>Output high when set</term></item>
	///						<item><term>2</term><term>Output low when set</term></item>
	///		 		  </list> </param>
	/// <param name="lowerLimit"> The lower trigger limit</param>
	/// <param name="upperLimit"> The upper trigger limit</param>
	/// <param name="smoothingSamples"> The number of samples to use for smoothing</param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="IPP_GeTriggerConfigParams(char const * serialNo, KSG_TriggerPortMode *trigger1Mode, KSG_TriggerPortPolarity *trigger1Polarity, KSG_TriggerPortMode *trigger2Mode, KSG_TriggerPortPolarity *trigger2Polarity, __int32 *lowerLimit, __int32 *upperLimit, __int16 *smoothingSamples)" />
	/// <seealso cref="IPP_SetTriggerConfigParamsBlock(const char * serialNo, KSG_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="IPP_GetTriggerConfigParamsBlock(const char * serialNo, KSG_TriggerConfig *triggerConfigParams)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_SetTriggerConfigParams(char const * serialNo, KSG_TriggerPortMode trigger1Mode, KSG_TriggerPortPolarity trigger1Polarity, KSG_TriggerPortMode trigger2Mode, KSG_TriggerPortPolarity trigger2Polarity, __int32 lowerLimit, __int32 upperLimit, __int16 smoothingSamples);
	
	/// <summary> Get the Trigger Configuration Parameters. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="trigger1Mode">	    The trigger 1 mode.<list type=table>
	///						<item><term>0</term><term>Trigger disabled</term></item>
	///						<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="SG_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
	///						<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
	///						<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
	///						<item><term>10</term><term>Trigger Output - General purpose output (<see cref="SG_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
	///		 		  </list></param>
	/// <param name="trigger1Polarity"> The trigger 1 polarity.<list type=table>
	///						<item><term>1</term><term>Output high when set</term></item>
	///						<item><term>2</term><term>Output low when set</term></item>
	///		 		  </list> </param>
	/// <param name="trigger2Mode">	    The trigger 2 mode.<list type=table>
	///						<item><term>0</term><term>Trigger disabled</term></item>
	///						<item><term>1</term><term>Trigger Input - General purpose logic input (<see cref="SG_GetStatusBits(const char * serialNo)"> GetStatusBits</see>)</term></item>
	///						<item><term>2</term><term>Trigger Input - Move relative using relative move parameters</term></item>
	///						<item><term>3</term><term>Trigger Input - Move absolute using absolute move parameters</term></item>
	///						<item><term>10</term><term>Trigger Output - General purpose output (<see cref="SG_SetDigitalOutputs(const char * serialNo, byte outputBits)"> SetDigitalOutputs</see>)</term></item>
	///		 		  </list></param>
	/// <param name="trigger2Polarity"> The trigger 2 polarity.<list type=table>
	///						<item><term>1</term><term>Output high when set</term></item>
	///						<item><term>2</term><term>Output low when set</term></item>
	///		 		  </list> </param>
	/// <param name="lowerLimit"> The lower trigger limit</param>
	/// <param name="upperLimit"> The upper trigger limit</param>
	/// <param name="smoothingSamples"> The number of samples to use for smoothing</param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="IPP_SetTriggerConfigParams(char const * serialNo, KSG_TriggerPortMode trigger1Mode, KSG_TriggerPortPolarity trigger1Polarity, KSG_TriggerPortMode trigger2Mode, KSG_TriggerPortPolarity trigger2Polarity, __int32 lowerLimit, __int32 upperLimit, __int16 smoothingSamples)" />
	/// <seealso cref="IPP_SetTriggerConfigParamsBlock(const char * serialNo, KSG_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="IPP_GetTriggerConfigParamsBlock(const char * serialNo, KSG_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="IPP_RequestTriggerConfigParams(char const * serialNo)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_GetTriggerConfigParams(char const * serialNo, KSG_TriggerPortMode *trigger1Mode, KSG_TriggerPortPolarity *trigger1Polarity, KSG_TriggerPortMode *trigger2Mode, KSG_TriggerPortPolarity *trigger2Polarity, __int32 *lowerLimit, __int32 *upperLimit, __int16 *smoothingSamples);


	/// <summary> Requests the trigger config parameters </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="IPP_SetTriggerConfigParams(char const * serialNo, KSG_TriggerPortMode trigger1Mode, KSG_TriggerPortPolarity trigger1Polarity, KSG_TriggerPortMode trigger2Mode, KSG_TriggerPortPolarity trigger2Polarity, __int32 lowerLimit, __int32 upperLimit, __int16 smoothingSamples)" />
	/// <seealso cref="IPP_SetTriggerConfigParamsBlock(const char * serialNo, KSG_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="IPP_GetTriggerConfigParamsBlock(const char * serialNo, KSG_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="IPP_GeTriggerConfigParams(char const * serialNo, KSG_TriggerPortMode *trigger1Mode, KSG_TriggerPortPolarity *trigger1Polarity, KSG_TriggerPortMode *trigger2Mode, KSG_TriggerPortPolarity *trigger2Polarity, __int32 *lowerLimit, __int32 *upperLimit, __int16 *smoothingSamples)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_RequestTriggerConfigParams(char const * serialNo);

	/// <summary> Gets the trigger configuration parameters block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="triggerConfigParams"> Options for controlling the trigger configuration. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="IPP_GetTriggerConfigParams(char const * serialNo, KSG_TriggerPortMode *trigger1Mode, KSG_TriggerPortPolarity *trigger1Polarity, KSG_TriggerPortMode *trigger2Mode, KSG_TriggerPortPolarity *trigger2Polarity, __int32 *lowerLimit, __int32 *upperLimit, __int16 *smoothingSamples)" />
	/// <seealso cref="IPP_SetTriggerConfigParams(char const * serialNo, KSG_TriggerPortMode trigger1Mode, KSG_TriggerPortPolarity trigger1Polarity, KSG_TriggerPortMode trigger2Mode, KSG_TriggerPortPolarity trigger2Polarity, __int32 lowerLimit, __int32 upperLimit, __int16 smoothingSamples)" />
	/// <seealso cref="IPP_SetTriggerConfigParamsBlock(const char * serialNo, KSG_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="IPP_RequestTriggerConfigParams(char const * serialNo)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_GetTriggerConfigParamsBlock(char const * serialNo, KSG_TriggerConfig *triggerConfigParams);

	/// <summary> Sets the trigger configuration parameters block. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="triggerConfigParams"> Options for controlling the trigger configuration. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="IPP_GetTriggerConfigParams(char const * serialNo, KSG_TriggerPortMode *trigger1Mode, KSG_TriggerPortPolarity *trigger1Polarity, KSG_TriggerPortMode *trigger2Mode, KSG_TriggerPortPolarity *trigger2Polarity, __int32 *lowerLimit, __int32 *upperLimit, __int16 *smoothingSamples)" />
	/// <seealso cref="IPP_SetTriggerConfigParams(char const * serialNo, KSG_TriggerPortMode trigger1Mode, KSG_TriggerPortPolarity trigger1Polarity, KSG_TriggerPortMode trigger2Mode, KSG_TriggerPortPolarity trigger2Polarity, __int32 lowerLimit, __int32 upperLimit, __int16 smoothingSamples)" />
	/// <seealso cref="IPP_GetTriggerConfigParamsBlock(const char * serialNo, KSG_TriggerConfig *triggerConfigParams)" />
	/// <seealso cref="IPP_RequestTriggerConfigParams(char const * serialNo)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_SetTriggerConfigParamsBlock(char const * serialNo, KSG_TriggerConfig *triggerConfigParams);

	/// <summary> Determine if the device front panel can be locked. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> True if we can lock the device front panel, false if not. </returns>
	/// <seealso cref="IPP_GetFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="IPP_RequestFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="IPP_SetFrontPanelLock(char const * serialNo, bool locked)" />
	INTEGRATEDPRECISIONPIEZO_API bool __cdecl IPP_CanDeviceLockFrontPanel(char const * serialNo);

	/// <summary> Query if the device front panel locked. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> True if the device front panel is locked, false if not. </returns>
	/// <seealso cref="IPP_CanDeviceLockFrontPanel(char const * serialNo)" />
	/// <seealso cref="IPP_RequestFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="IPP_SetFrontPanelLock(char const * serialNo, bool locked)" />
	INTEGRATEDPRECISIONPIEZO_API bool __cdecl  IPP_GetFrontPanelLocked(char const * serialNo);

	/// <summary> Ask the device if its front panel is locked. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="IPP_CanDeviceLockFrontPanel(char const * serialNo)" />
	/// <seealso cref="IPP_GetFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="IPP_SetFrontPanelLock(char const * serialNo, bool locked)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl  IPP_RequestFrontPanelLocked(char const * serialNo);

	/// <summary> Sets the device front panel lock state. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="locked"> True to lock the device, false to unlock. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="IPP_CanDeviceLockFrontPanel(char const * serialNo)" />
	/// <seealso cref="IPP_GetFrontPanelLocked(char const * serialNo)" />
	/// <seealso cref="IPP_RequestFrontPanelLocked(char const * serialNo)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl  IPP_SetFrontPanelLock(char const * serialNo, bool locked);

	/// <summary> Gets the Position Control Mode. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns> The control mode <list type=table>
	///				<item><term>Open Loop</term><term>1</term></item>
	///				<item><term>Closed Loop</term><term>2</term></item>
	///				<item><term>Open Loop smoothed</term><term>3</term></item>
	///				<item><term>Closed Loop smoothed</term><term>4</term></item>
	/// 		  </list> </returns>
	/// <seealso cref="IPP_RequestPositionControlMode(char const * serialNo)" />
	/// <seealso cref="IPP_SetPositionControlMode(char const * serialNo, PZ_ControlModeTypes mode)" />
	INTEGRATEDPRECISIONPIEZO_API PZ_ControlModeTypes __cdecl IPP_GetPositionControlMode(char const * serialNo);

	/// <summary> Requests that the Position Control Mode be read from the device. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="IPP_GetPositionControlMode(char const * serialNo)" />
	/// <seealso cref="IPP_SetPositionControlMode(char const * serialNo, PZ_ControlModeTypes mode)" />
	INTEGRATEDPRECISIONPIEZO_API bool __cdecl IPP_RequestPositionControlMode(char const * serialNo);

	/// <summary> Sets the Position Control Mode. </summary>
	/// <remarks> <I>Applies to Single Channel Precision Piezo Devices only. For multi channel use PPC2_ equivalent.</I></remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="mode"> The control mode <list type=table>
	///				<item><term>Open Loop</term><term>1</term></item>
	///				<item><term>Closed Loop</term><term>2</term></item>
	///				<item><term>Open Loop smoothed</term><term>3</term></item>
	///				<item><term>Closed Loop smoothed</term><term>4</term></item>
	/// 		  </list>. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="IPP_GetPositionControlMode(char const * serialNo)" />
	/// <seealso cref="IPP_RequestPositionControlMode(char const * serialNo)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl  IPP_SetPositionControlMode(char const * serialNo, PZ_ControlModeTypes mode);

	/// <summary> Gets the current Closed Loop position.</summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// <seealso cref="IPP_GetPosition(char const * serialNo)" />
	/// <seealso cref="IPP_SetPosition(char const * serialNo, short position)" />
	INTEGRATEDPRECISIONPIEZO_API bool __cdecl IPP_RequestPosition(char const * serialNo);

	/// <summary> Gets the current  position 
	/// Please note this is non linear</summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <returns>	The closed loop position as ,<br />
	/// as represented by the percentage of strain gauge extension, in the range:<Br />
	///		  0-32768 <Br/>
	/// Please note this is non linear</returns>
	/// <seealso cref="IPP_RequestPosition(char const * serialNo)" />
	/// <seealso cref="IPP_SetPosition(char const * serialNo, short position)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl  IPP_GetPosition(char const * serialNo);


	/// <summary> Sets the position when in closed loop mode. </summary>
	/// <remarks> The command is ignored if not in closed loop mode</remarks>
	/// <param name="serialNo">	The device serial no. </param>
	/// <param name="position"> The position as a percentage of maximum travel,<br />
	/// 		  range 0 to 32767, equivalent to 0 to 100%. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="IPP_RequestPosition(char const * serialNo)" />
	/// <seealso cref="IPP_GetPosition(char const * serialNo)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_SetPosition(char const * serialNo, short position);

	/// <summary> Requests the PID Constants. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="index"> The index of the PID set </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="IPP_GetPIDConsts(const char * serialNo, byte index, PPC_PIDConsts *pidConsts)" />
	/// <seealso cref="IPP_SetPIDConsts(const char * serialNo, PPC_PIDConsts *pidConsts)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_RequestPIDConsts(const char * serialNo, byte index);

	/// <summary> Gets the PPC PID Constants. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="index"> The index of the PID set </param>
	/// <param name="pidConsts"> The PID consts <see cref="PPC_PIDConsts"/>. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="IPP_RequestPIDConsts(const char * serialNo, byte index)" />
	/// <seealso cref="IPP_SetPIDConsts(const char * serialNo, PPC_PIDConsts *pidConsts)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_GetPIDConsts(const char * serialNo, byte index, PPC_PIDConsts *pidConsts);

	/// <summary> Sets the PPC PID Constants. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="pidConsts"> The PPC PID Constants. <see cref="PPC_PIDConsts"/>. </returns> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="IPP_RequestPIDConsts(const char * serialNo, byte index)" />
	/// <seealso cref="IPP_GetPIDConsts(const char * serialNo, PPC_PIDConsts *pidConsts)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_SetPIDConsts(const char * serialNo, PPC_PIDConsts *pidConsts);



	/// <summary> Requests the PID Criteria. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="criteriaID"> The criteria ID. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="IPP_GetPIDCriteria(const char * serialNo, byte criteriaID, PPC_PIDCriteria *pidCriteria)" />
	/// <seealso cref="IPP_SetPIDCriteria(const char * serialNo, PPC_PIDCriteria *pidCriteria)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_RequestPIDCriteria(const char * serialNo, byte criteriaID);

	/// <summary> Gets the PID Criteria. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="criteriaID"> The criteria ID. </param>
	/// <param name="pidCriteria"> The PID criteria. <see cref="PPC_PIDriteria"/>. </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="IPP_RequestPIDCriteria(const char * serialNo, byte criteriaID)" />
	/// <seealso cref="IPP_SetPIDCriteria(const char * serialNo, PPC_PIDCriteria *pidCriteria)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_GetPIDCriteria(const char * serialNo, byte criteriaID, PPC_PIDCriteria *pidCriteria);

	/// <summary> Sets the PID Criteria. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="pidCriteria"> The PID criteria. <see cref="PPC_PIDConsts"/>. </returns> </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="IPP_RequestPIDCriteria(const char * serialNo, byte criteriaID)" />
	/// <seealso cref="IPP_GetPIDCriteria(const char * serialNo, byte criteriaID, PPC_PIDCriteria *pidCriteria)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_SetPIDCriteria(const char * serialNo, PPC_PIDCriteria *pidCriteria);


	/// <summary> Request that the MMI Parameters for the Integrated Precision Piezo be read from the device. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <returns>	True if it succeeds, false if it fails. </returns>
	INTEGRATEDPRECISIONPIEZO_API  bool __cdecl IPP_RequestMMIParams(char const * serialNo);

	/// <summary> Get the MMI Parameters for the Integrated Precision Piezo. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="wheelMode">	Not currently settable in this device </param>
	/// <param name="voltageAdjustRate">  The voltage knob gearing.
	/// 					<list type=table>
	///							<item><term>1</term><term>Fast</term></item>
	///							<item><term>2</term><term>Medium</item>
	///							<item><term>3</term><term>Slow</term></item>
	/// 					</list> </param>
	/// <param name="voltageStep"> Not currently settable in this device </param>
	/// <param name="directionSense">Not currently settable in this device </param>
	/// <param name="presetVoltage1">Not currently settable in this device </param>
	/// <param name="presetVoltage2">	Not currently settable in this device</param>
	/// <param name="displayIntensity">	    Not currently settable in this device</param>
	/// <param name="displayTimeout">	    The display timeout, in seconds. </param>
	/// <param name="displayDimIntensity">	Not currently settable in this device </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="IPP_SetMMIParams(char const * serialNo, KPZ_WheelMode wheelMode, KPZ_WheelChangeRate voltageAdjustRate, __int32 voltageStep, KPZ_WheelDirectionSense directionSense, __int32 presetVoltage1, __int32 presetVoltage2, __int16 displayIntensity)" />
	/// <seealso cref="IPP_SetMMIParamsBlock(const char * serialNo, KPZ_MMIParams *mmiParams)" />
	/// <seealso cref="IPP_GetMMIParamsBlock(const char * serialNo, KPZ_MMIParams *mmiParams)" />
	INTEGRATEDPRECISIONPIEZO_API  short __cdecl IPP_GetMMIParams(char const * serialNo, KPZ_WheelMode *wheelMode, KPZ_WheelChangeRate *voltageAdjustRate, __int32 *voltageStep, KPZ_WheelDirectionSense *directionSense,
		__int32 *presetVoltage1, __int32 *presetVoltage2, __int16 *displayIntensity, __int16 *displayTimeout, __int16 *displayDimIntensity);


	/// <summary> Set the MMI Parameters for the Integrated PrecisionPiezo. </summary>
	/// <param name="serialNo"> The device serial no. </param>
	/// <param name="wheelMode">	Not currently settable in this device 
	/// 					 </param>
	/// <param name="voltageAdjustRate">  The voltage knob gearing.
	/// 					<list type=table>
	///							<item><term>1</term><term>Fast</term></item>
	///							<item><term>2</term><term>Medium</item>
	///							<item><term>3</term><term>Slow</term></item>
	/// 					</list> </param>
	/// <param name="voltageStep"> Not currently settable in this device  </param>
	/// <param name="directionSense">	   Not currently settable in this device  </param>
	/// <param name="presetVoltage1">	   Not currently settable in this device  </param>
	/// <param name="presetVoltage2">	 Not currently settable in this device . </param>
	/// <param name="displayIntensity">	    Not currently settable in this device  </param>
	/// <param name="displayTimeout">	   The display timeout, in seconds. </param>
	/// <param name="displayDimIntensity">	Not currently settable in this device </param>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	/// <seealso cref="IPP_GetMMIParamsExt(char const * serialNo, KPZ_WheelMode *wheelMode, KPZ_WheelChangeRate *voltageAdjustRate, __int32 *voltageStep, KPZ_WheelDirectionSense *directionSense, __int32 *presetVoltage1, __int32 *presetVoltage2, __int16 *displayIntensity)" />
	/// <seealso cref="IPP_SetMMIParamsBlock(const char * serialNo, KPZ_MMIParams *mmiParams)" />
	/// <seealso cref="IPP_GetMMIParamsBlock(const char * serialNo, KPZ_MMIParams *mmiParams)" />
	INTEGRATEDPRECISIONPIEZO_API short __cdecl IPP_SetMMIParams(char const * serialNo, KPZ_WheelMode wheelMode, KPZ_WheelChangeRate voltageAdjustRate, __int32 voltageStep, KPZ_WheelDirectionSense directionSense,
		__int32 presetVoltage1, __int32 presetVoltage2, __int16 displayIntensity, __int16 displayTimeout, __int16 displayDimIntensity);



	/// <summary> Performs a Set Zero operation. </summary>
	/// <param name="serialNo">	The device serial no. </param>
	/// <remarks>This operation performs will zero the output and set the position to zero</remarks>
	/// <returns> The error code (see \ref C_DLL_ERRORCODES_page "Error Codes") or zero if successful. </returns>
	INTEGRATEDPRECISIONPIEZO_API short __cdecl  IPP_SetZero(char const * serialNo);



	   	  
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
	INTEGRATEDPRECISIONPIEZO_API short __cdecl TLI_BuildDeviceList(void);

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
	INTEGRATEDPRECISIONPIEZO_API short __cdecl  TLI_GetDeviceListSize();

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
	INTEGRATEDPRECISIONPIEZO_API short __cdecl  TLI_GetDeviceList(SAFEARRAY** stringsReceiver);

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
	INTEGRATEDPRECISIONPIEZO_API short __cdecl TLI_GetDeviceListByType(SAFEARRAY** stringsReceiver, int typeID);


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
	INTEGRATEDPRECISIONPIEZO_API short __cdecl TLI_GetDeviceListByTypes(SAFEARRAY** stringsReceiver, int * typeIDs, int length);

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
	INTEGRATEDPRECISIONPIEZO_API short __cdecl TLI_GetDeviceListExt(char *receiveBuffer, DWORD sizeOfBuffer);

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
	INTEGRATEDPRECISIONPIEZO_API short __cdecl TLI_GetDeviceListByTypeExt(char *receiveBuffer, DWORD sizeOfBuffer, int typeID);

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
	INTEGRATEDPRECISIONPIEZO_API short __cdecl TLI_GetDeviceListByTypesExt(char *receiveBuffer, DWORD sizeOfBuffer, int * typeIDs, int length);


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
	INTEGRATEDPRECISIONPIEZO_API short __cdecl TLI_GetDeviceInfo(char const * serialNo, TLI_DeviceInfo *info);

	/// <summary> Initialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <remarks> Call TLI_InitializeSimulations before TLI_BuildDeviceList at the start of the program to make a connection to the simulation manager.<Br />
	/// 		  Any devices configured in the simulation manager will become visible TLI_BuildDeviceList is called and can be accessed using TLI_GetDeviceList.<Br />
	/// 		  Call TLI_InitializeSimulations at the end of the program to release the simulator.  </remarks>
	/// <seealso cref="TLI_UninitializeSimulations()" />
	/// <seealso cref="TLI_BuildDeviceList()" />
	/// <seealso cref="TLI_GetDeviceList(SAFEARRAY** stringsReceiver)" />
	INTEGRATEDPRECISIONPIEZO_API void __cdecl TLI_InitializeSimulations();

	/// <summary> Uninitialize a connection to the Simulation Manager, which must already be running. </summary>
	/// <seealso cref="TLI_InitializeSimulations()" />
	INTEGRATEDPRECISIONPIEZO_API void __cdecl TLI_UninitializeSimulations();

}
/** @} */ // IntegratedPrecisionPiezo
