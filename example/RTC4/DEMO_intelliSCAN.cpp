//  File
//      intelliSCAN.cpp
//
//  Abstract
//      A console application for demonstrating the communication
//      with the intelliSCAN
//     
//
//  Author
//      Gerald Schmid, SCANLAB AG
//
//  Comment
//      Besides demonstrating of how to initialize the RTC4 and how to
//      perform marking, this application also shows how to implicitly
//      link to the RTC4DLL.DLL. For accomplishing implicit linking -
//      also known as static load or load-time dynamic linking of a DLL,
//      the header file RTC4impl.H is included and for building the
//      executable, you must link with the (Visual C++) import library
//      RTC4DLL.LIB.
//
//  Necessary Sources
//      RTC4impl.H, RTC4DLL.LIB
//      NOTE: RTC4DLL.LIB is a Visual C++ library.
//
//  Environment: Win32
//
//  Compiler
//      - tested with Visual C++ 6.0


// system header files
#include <stdio.h>
#include <conio.h>

// RTC4 header file
#include "rtc4impl.h"



#define MaxWavePoints	32768	// maximum number of samples per channel
#define	SamplePeriod	1		// sampling period [10us]

#define	SendStatus		0x0500	// command codes for changing data on the status channel
#define	SendRealPos		0x0501
#define	SendStatus2		0x0512
#define	SendGalvoTemp	0x0514
#define	SendHeadTemp	0x0515
#define	SendAGC			0x0516
#define	SendVccDSP		0x0517
#define	SendVccDSPIO	0x0518
#define	SendVccANA		0x0519
#define	SendVccADC		0x051A

#define	HeadA			1
#define	XAxis			1
#define	YAxis			2
#define	StatusAX		1
#define	StatusAY		2


void delay(void)		// 100us delay
{
	for (short i=0; i<10; i++)
		z_out(0);		// dummy control function generates a 10us delay
}


void main(void)
{
	long			i;
    short			ErrorCode;
	unsigned short	WavePoints;
	short			Ch1[MaxWavePoints], Ch2[MaxWavePoints];



    // Initialize: load correction and program file
    ErrorCode = load_correction_file("cor_1to1.ctb",
                        1,          // table; #1 is used by default
                        1.0, 1.0,   // scale factor
                        0.0,        // rotation in degrees, counterclockwise
                        0.0, 0.0);  // offset in bits
    if(ErrorCode) {
        printf("Correction file loading error #%d\n",ErrorCode);
        return;
    }

    ErrorCode = load_program_file("RTC4D2.hex");
    if(ErrorCode) {
        printf("Program file loading error #%d\n",ErrorCode);
        return;
    }


	// get some status information from the head
	control_command(HeadA, XAxis, SendGalvoTemp);	// send X galvo temp on X status channel
	control_command(HeadA, YAxis, SendGalvoTemp);	// send Y galvo temp on Y status channel
	delay();	// wait until command is transfered to the head, executed and new status data is updated
	printf("Temperature X-Galvo: %4.1f degrees centigrade\n",0.1*get_value(StatusAX));	// read X status channel
	printf("Temperature Y-Galvo: %4.1f degrees centigrade\n",0.1*get_value(StatusAY));	// 1bit = 0.1 degree

	// display AGC voltage of each galvo
	control_command(HeadA, XAxis, SendAGC);
	control_command(HeadA, YAxis, SendAGC);
	delay();
	printf("AGC Voltage X-Galvo: %5.2f Volts\n",0.01*get_value(StatusAX));	// 1bit = 10mV
	printf("AGC Voltage Y-Galvo: %5.2f Volts\n",0.01*get_value(StatusAY));

	// display internal status information
	control_command(HeadA, XAxis, SendStatus2);
	control_command(HeadA, YAxis, SendStatus2);
	delay();
	printf("Status2 X-Axis: %hX\n",get_value(StatusAX));
	printf("Status2 Y-Axis: %hX\n",get_value(StatusAY));

	// send back the XY real position on the status channels
	control_command(HeadA, XAxis, SendRealPos);   // real position
	control_command(HeadA, YAxis, SendRealPos);

    printf("press any key to start ");
    while(!kbhit());
    (void)getch();
    printf("\n\n");




	// mark "SCANLAB", record the measured position bend and transfer it to the PC
    set_laser_mode(1);			// set YAG mode 1

    set_start_list(1);			// timing, delay and speed preset
		set_laser_timing(50,	// half of the laser signal period
						5,5,	// pulse width of signal LASER1 and dummy value
						0);     // time base; 0 corresponds to 1 microsecond.
								// Otherwise, the time base is 1/8 microseconds.

		set_firstpulse_killer_list(8*150);	// pulse width of signal LASER2
								// timebase is 1/8 microseconds

		set_scanner_delays(25,  // jump delay in 10 microseconds
			            10,     // mark delay in 10 microseconds
				        5);     // polygon delay in 10 microseconds
		set_laser_delays(100,   // laser on delay in microseconds
			            100);   // laser off delay in microseconds
		set_jump_speed(2500.0); // jump speed in bits per milliseconds
		set_mark_speed(1000.0); // marking speed in bits per milliseconds
		jump_abs(0,0);


		save_and_restart_timer();	// start marking time measurement
		set_trigger(SamplePeriod, StatusAX, StatusAY);	// start sampling, set sampling period and channels


		// mark "SCANLAB"
		jump_abs(-3040, 380);	// S
		mark_abs(-3230, 570);
		mark_abs(-3610, 570);
		mark_abs(-3800, 380);
		mark_abs(-3800, 190);
		mark_abs(-3610, 0);
		mark_abs(-3230, 0);
		mark_abs(-3040, -190);
		mark_abs(-3040, -380);
		mark_abs(-3230, -570);
		mark_abs(-3610, -570);
		mark_abs(-3800, -380);

		jump_abs(-1900, 380);	// C
		mark_abs(-2090, 570);
		mark_abs(-2470, 570);
		mark_abs(-2660, 380);
		mark_abs(-2660, -380);
		mark_abs(-2470, -570);
		mark_abs(-2090, -570);
		mark_abs(-1900, -380);

		jump_abs(-1520, -570);	// A
		mark_abs(-1520, 190);
		mark_abs(-1140, 570);
		mark_abs(-760, 190);
		mark_abs(-760, -570);
		jump_abs(-760, 0);
		mark_abs(-1520, 0);

		jump_abs(-380, -570);	// N
		mark_abs(-380, 570);
		mark_abs(380, -570);
		mark_abs(380, 570);

		jump_abs(760, 570);		// L
		mark_abs(760, -570);
		mark_abs(1520, -570);

		jump_abs(1900, -570);	// A
		mark_abs(1900, 190);
		mark_abs(2280, 570);
		mark_abs(2660, 190);
		mark_abs(2660, -570);
		jump_abs(2660, 0);
		mark_abs(1900, 0);

		jump_abs(3040, 0);		// B
		mark_abs(3610, 0);
		mark_abs(3800, 190);
		mark_abs(3800, 380);
		mark_abs(3610, 570);
		mark_abs(3040, 570);
		mark_abs(3040, -570);
		mark_abs(3610, -570);
		mark_abs(3800, -380);
		mark_abs(3800, -190);
		mark_abs(3610, 0);

		jump_abs(0,0);
		save_and_restart_timer();	// stop marking time measurement
    set_end_of_list();

    execute_list(1);				// start marking

    // wait as long the execution is finished
    do {} while(read_status() & 0x010);


	if (get_time() > (double)MaxWavePoints*SamplePeriod*1e-5)	// marking time > buffer time ?
		WavePoints = MaxWavePoints;
	else
		WavePoints = (unsigned short)(get_time()/((double)SamplePeriod*1e-5));


	get_waveform(1, WavePoints, &Ch1[0]);  // get the waveforms from channel 1&2
	get_waveform(2, WavePoints, &Ch2[0]);

	// print galvo measured positions 
	printf("Time [10us]  PhiX [Bit]  PhiY [Bit]\n");
	printf("-----------------------------------\n");
	for (i=0; i<WavePoints; i++)
		printf("%11d %11d %11d\n", i*SamplePeriod, Ch1[i], Ch2[i]);

    printf("press any key to terminate program ");
	while(!kbhit());
    return;
}
