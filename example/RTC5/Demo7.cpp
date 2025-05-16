//  File
//      intelliSCAN.cpp
//
//  Abstract
//      A console application for demonstrating the communication
//      with the intelliSCAN and using load_char, mark_text_abs.
//
//  Author
//      Gerald Schmid, SCANLAB AG
//      adapted for RTC5: Hermann Waibel, SCANLAB AG
//
//  Comment
//      Besides demonstrating of how to initialize the RTC5 and how to
//      perform marking, this application also shows how to implicitly
//      link to the RTC5DLL.DLL. For accomplishing implicit linking -
//      also known as static load or load-time dynamic linking of a DLL,
//      the header file RTC5impl.H is included and for building the
//      executable, you must link with the (Visual C++) import library
//      RTC5DLL.LIB.
//
//  Necessary Sources
//      RTC5impl.H, RTC5DLL.LIB
//      NOTE: RTC5DLL.LIB is a Visual C++ library.
//
//  Environment: Win32
//
//  Compiler
//      - tested with Visual C++ 7.1

//  Do not change this value
const unsigned int MinDLL = 507;         //  at least release 507 is required
//  mark_text_abs and load_char not working correctly in earlier versions

// System header files
#include <windows.h>
#include <stdio.h>
#include <conio.h>

// RTC5 header file for implicitly linking to the RTC5DLL.DLL
#include "RTC5impl.h"

// Change these values according to your system
const UINT   DefaultCard        =            1;   //  number of default card
const UINT   LaserMode          =            1;   //  YAG 1 mode
const UINT   LaserControl       =         0x18;   //  Laser signals LOW active (Bits #3 and #4)

// RTC4 compatibility mode assumed
const UINT   AnalogOutChannel   =            1;   //  AnalogOut Channel 1 used
const UINT   AnalogOutValue     =          640;   //  Standard Pump Source Value
const UINT   AnalogOutStandby   =            0;   //  Standby  Pump Source Value
const UINT   WarmUpTime         =   2000000/10;   //    2  s [10 us]
const UINT   LaserHalfPeriod    =         50*8;   //   50 us [1/8 us] must be at least 13
const UINT   LaserPulseWidth    =          5*8;   //    5 us [1/8 us]
const UINT   FirstPulseKiller   =        150*8;   //  200 us [1/8 us]
const long   LaserOnDelay       =        100*1;   //  100 us [1 us]
const UINT   LaserOffDelay      =        100*1;   //  100 us [1 us]

const UINT   JumpDelay          =       250/10;   //  250 us [10 us]
const UINT   MarkDelay          =       100/10;   //  100 us [10 us]
const UINT   PolygonDelay       =        50/10;   //   50 us [10 us]
const double MarkSpeed          =       1000.0;   //  [16 Bits/ms]
const double JumpSpeed          =       2500.0;   //  [16 Bits/ms]

// Command codes for changing data on the status channel
const UINT SendStatus		    = 0x0500;
const UINT SendRealPos		    = 0x0501;
const UINT SendStatus2		    = 0x0512;
const UINT SendGalvoTemp	    = 0x0514;
const UINT SendHeadTemp	        = 0x0515;
const UINT SendAGC			    = 0x0516;
const UINT SendVccDSP		    = 0x0517;
const UINT SendVccDSPIO	        = 0x0518;
const UINT SendVccANA		    = 0x0519;
const UINT SendVccADC		    = 0x051A;
const UINT SendFirmWare		    = 0x0522;

// Constants for triggering data
const UINT HeadA			    =      1;
const UINT XAxis			    =      1;
const UINT YAxis			    =      2;
const UINT StatusAX		        =      1;
const UINT StatusAY		        =      2;
const UINT SampleX              =      7;
const UINT SampleY              =      8;

const UINT MaxWavePoints	    =  32768;	// maximum number of samples per channel
const UINT SamplePeriod	        =      1;   // sampling period [10us]
const UINT TriggerCh1           = StatusAX;  // for none intelliSCANs: use SampleX
const UINT TriggerCh2           = StatusAY;  // for none intelliSCANs: use SampleY

// Constants for chars (Char Cell 4*6, Hot Spot (0,0))
const long SizeX                =     600;  // CharSizeX = 4 * SizeX
const long SizeY                =     600;  // CharSizeY = 6 * SizeY
const long CharSpace            =     300;  // CharSpace = 0.5 * SizeX
const long TextOffsetX          =   -8400;  // 7/2 times char width
const long TextOffsetY          =    4200;  // 7/6 times char height

void delay( const UINT n );                 //  n * 10us delay
void terminateDLL();                        //  waits for a keyboard hit to terminate
short GetValue( const UINT Signal );        //  calls get_value( Signal )

void __cdecl main( void*, void* )
{
    printf( "Initializing the DLL\n\n" );

    UINT  ErrorCode;

    //  This function must be called at the very first
    ErrorCode = init_rtc5_dll();    

    if ( ErrorCode )
    {
        const UINT RTC5CountCards = rtc5_count_cards();   //  number of cards found
        
        if ( RTC5CountCards )
        {
            UINT AccError( 0 );

            //  Error analysis in detail
            for ( UINT i = 1; i <= RTC5CountCards; i++ )
            {
                const UINT Error = n_get_last_error( i );

                if ( Error != 0 ) 
                {
                    AccError |= Error;
                    printf( "Card no. %d: Error %d detected\n", i, Error );
                    n_reset_error( i, Error );

                }

            }

            if ( AccError )
            {
                terminateDLL();
                return;

            }

        }
        else
        {
            printf( "Initializing the DLL: Error %d detected\n", ErrorCode );
            terminateDLL();
            return;

        }

    }
    else
    {
        if ( DefaultCard != select_rtc( DefaultCard ) )     //  use card no. 1 as default, 
        {
            ErrorCode = n_get_last_error( DefaultCard );

            if ( ErrorCode & 256 )    //  RTC5_VERSION_MISMATCH
            {
                //  In this case load_program_file(0) would not work.
                ErrorCode = n_load_program_file( DefaultCard, 0 ); //  current working path

            }
            else
            {
                printf( "No acces to card no. %d\n", DefaultCard );
                terminateDLL();
                return;

            }

            if ( ErrorCode )
            {
                printf( "No access to card no. %d\n", DefaultCard );
                terminateDLL();
                return;

            }
            else
            {   //  n_load_program_file was successfull
                (void) select_rtc( DefaultCard );

            }

        }

    }

    set_rtc4_mode();            //  for RTC4 compatibility

    // Initialize the RTC5
    stop_execution();
    //  If the DefaultCard has been used previously by another application 
    //  a list might still be running. This would prevent load_program_file
    //  and load_correction_file from being executed!

    ErrorCode = load_program_file( 0 );     //  path = current working path

    if ( ErrorCode )
    {
        printf( "Program file loading error: %d\n", ErrorCode );
        terminateDLL();
        return;

    }

    ErrorCode = load_correction_file( 0,   // initialize like "D2_1to1.ct5",
                                      1,   // table; #1 is used by default
                                      2 ); // use 2D only
    if ( ErrorCode )
    {
        printf( "Correction file loading error: %d\n", ErrorCode );
        terminateDLL();
        return;

    }

    select_cor_table( 1, 0 );   //  table #1 at primary connector (default)

    //  stop_execution might have created an RTC5_TIMEOUT error
    reset_error( -1 );    //  Clear all previous error codes


    /////////////////////////////////////////////////////////////////////


    printf( "Press any key to start " );
    while ( !kbhit() );
    (void) getch();
    printf( "\n\n" );

    //  Check wether an intelliSCAN is connected or not
	control_command( HeadA, XAxis, SendStatus );	// send Status on X status channel
    delay( 10 );	// Wait until command is transfered to the head, executed and new status data is updated
    const short Test1( GetValue( StatusAX ) );
	
    control_command( HeadA, XAxis, SendFirmWare );	// send FirmWare No on X status channel
    delay( 10 );	// Wait until command is transfered to the head, executed and new status data is updated
    const short Test2( GetValue( StatusAX ) );

    if ( Test1 == Test2 )
    {
        printf( "Please check HeadA: no intelliSCAN connected\n\n" );
        
    }
    else
    {
	    // Get some status information from the head
	    control_command( HeadA, XAxis, SendGalvoTemp );	// send X galvo temp on X status channel
	    control_command( HeadA, YAxis, SendGalvoTemp );	// send Y galvo temp on Y status channel
	    delay( 10 );
	    printf( "Temperature X-Galvo: %4.1f degrees centigrade\n", 0.1 * GetValue( StatusAX ) );	// read X status channel
	    printf( "Temperature Y-Galvo: %4.1f degrees centigrade\n", 0.1 * GetValue( StatusAY ) );	// 1 bit = 0.1 degrees

	    // Display AGC voltage of each galvo
	    control_command( HeadA, XAxis, SendAGC );
	    control_command( HeadA, YAxis, SendAGC );
	    delay( 10 );
	    printf( "AGC Voltage X-Galvo: %5.2f Volts\n", 0.01 * GetValue( StatusAX ) );	// 1 bit = 10 mV
	    printf( "AGC Voltage Y-Galvo: %5.2f Volts\n", 0.01 * GetValue( StatusAY ) );

	    // Display internal status information
	    control_command( HeadA, XAxis, SendStatus2 );
	    control_command( HeadA, YAxis, SendStatus2 );
	    delay( 10 );
	    printf( "Status2 X-Axis: %hX\n", GetValue( StatusAX) );
	    printf( "Status2 Y-Axis: %hX\n", GetValue( StatusAY) );

	    // Send back the XY real position on the status channels
	    control_command( HeadA, XAxis, SendRealPos );   // real position
	    control_command( HeadA, YAxis, SendRealPos );

    }

    const UINT DLLVersion = get_dll_version();

    if ( DLLVersion < MinDLL )
    {
        printf( "DLL version %d too low, at least %d required!\n", DLLVersion, MinDLL );
        terminateDLL();
        return;

    }

    //  Load some chars (character set 0):
    load_char( 'A' );
    {
		jump_abs( 0 * SizeX, 0 * SizeY );
		mark_abs( 0 * SizeX, 4 * SizeY );
		mark_abs( 2 * SizeX, 6 * SizeY );
		mark_abs( 4 * SizeX, 4 * SizeY );
		mark_abs( 4 * SizeX, 0 * SizeY );
		jump_abs( 4 * SizeX, 3 * SizeY );
		mark_abs( 0 * SizeX, 3 * SizeY );
		jump_abs( 4 * SizeX + CharSpace, 0 * SizeY );
        list_return();
    }

    load_char( 'B' );
    {
		jump_abs( 0 * SizeX, 3 * SizeY );
		mark_abs( 3 * SizeX, 3 * SizeY );
		mark_abs( 4 * SizeX, 4 * SizeY );
		mark_abs( 4 * SizeX, 5 * SizeY );
		mark_abs( 3 * SizeX, 6 * SizeY );
		mark_abs( 0 * SizeX, 6 * SizeY );
		mark_abs( 0 * SizeX, 0 * SizeY );
		mark_abs( 3 * SizeX, 0 * SizeY );
		mark_abs( 4 * SizeX, 1 * SizeY );
		mark_abs( 4 * SizeX, 2 * SizeY );
		mark_abs( 3 * SizeX, 3 * SizeY );
		jump_abs( 4 * SizeX + CharSpace, 0 * SizeY );
        list_return();
    }

    load_char( 'C' );
    {
		jump_abs( 4 * SizeX, 5 * SizeY );
		mark_abs( 3 * SizeX, 6 * SizeY );
		mark_abs( 1 * SizeX, 6 * SizeY );
		mark_abs( 0 * SizeX, 5 * SizeY );
		mark_abs( 0 * SizeX, 1 * SizeY );
		mark_abs( 1 * SizeX, 0 * SizeY );
		mark_abs( 3 * SizeX, 0 * SizeY );
		mark_abs( 4 * SizeX, 1 * SizeY );
		jump_abs( 4 * SizeX + CharSpace, 0 * SizeY );
        list_return();
    }

    load_char( 'L' );
    {
		jump_abs( 0 * SizeX, 6 * SizeY );
		mark_abs( 0 * SizeX, 0 * SizeY );
		mark_abs( 4 * SizeX, 0 * SizeY );
		jump_abs( 4 * SizeX + CharSpace, 0 * SizeY );
        list_return();
    }

    load_char( 'N' );
    {
		jump_abs( 0 * SizeX, 0 * SizeY );
		mark_abs( 0 * SizeX, 6 * SizeY );
		mark_abs( 4 * SizeX, 0 * SizeY );
		mark_abs( 4 * SizeX, 6 * SizeY );
		jump_abs( 4 * SizeX + CharSpace, 0 * SizeY );
        list_return();
    }

    load_char( 'S' );
    {
		jump_abs( 4 * SizeX, 5 * SizeY );
		mark_abs( 3 * SizeX, 6 * SizeY );
		mark_abs( 1 * SizeX, 6 * SizeY );
		mark_abs( 0 * SizeX, 5 * SizeY );
		mark_abs( 0 * SizeX, 4 * SizeY );
		mark_abs( 1 * SizeX, 3 * SizeY );
		mark_abs( 3 * SizeX, 3 * SizeY );
		mark_abs( 4 * SizeX, 2 * SizeY );
		mark_abs( 4 * SizeX, 1 * SizeY );
		mark_abs( 3 * SizeX, 0 * SizeY );
		mark_abs( 1 * SizeX, 0 * SizeY );
		mark_abs( 0 * SizeX, 1 * SizeY );
		jump_abs( 4 * SizeX + CharSpace, 0 * SizeY );
        list_return();
    }

	// Mark "SCANLAB", record the measured position bend and transfer it to the PC
    set_laser_mode( LaserMode );

    //  This function must be called at least once to activate laser 
    //  signals. Later on enable/disable_laser would be sufficient.
    set_laser_control( LaserControl );

	// Timing, delay and speed preset
    set_start_list( 1 );
        
        if ( LaserMode )
        {
            // Turn on the optical pump source and wait
            write_da_x_list( AnalogOutChannel, AnalogOutValue );
            long_delay( WarmUpTime );
		    set_firstpulse_killer_list( FirstPulseKiller );

        }

		set_laser_pulses( LaserHalfPeriod, LaserPulseWidth );
		set_laser_delays( LaserOnDelay, LaserOffDelay );
		set_scanner_delays( JumpDelay, MarkDelay, PolygonDelay );
		set_jump_speed( JumpSpeed );
		set_mark_speed( MarkSpeed );

		jump_abs( TextOffsetX, TextOffsetY );

    	// Start sampling, set sampling period and channels	
        set_trigger( SamplePeriod, TriggerCh1, TriggerCh2 );

	    // Start marking time measurement
		save_and_restart_timer();

        mark_text_abs( "SCANLAB" );
        //  For comparison try the following:
        mark_text( "SCANLAB" );

		save_and_restart_timer();	                // stop marking time measurement
        set_trigger( 0, TriggerCh1, TriggerCh2 );   // stop triggering data

		jump_abs( 0, 0 );
    set_end_of_list();

    execute_list( 1 );				// start marking

    UINT Busy, Pos;
    // Wait as long as the execution is finished
    do { get_status( &Busy, &Pos ); } while ( Busy );

    printf( "Elapsed marking time = %.3f milli seconds \n\n", get_time() * 1000.0 );

    measurement_status( &Busy, &Pos );

	long	Ch1[ MaxWavePoints ], Ch2[ MaxWavePoints ];
    memset( Ch1, 0, MaxWavePoints * sizeof(long) );
    memset( Ch2, 0, sizeof(Ch2) );

    UINT WavePoints( Pos > MaxWavePoints ? MaxWavePoints : Pos );

	get_waveform( 1, WavePoints, (UINT) (UINT64) Ch1 );  // get the waveforms from channel 1&2
	get_waveform( 2, WavePoints, (UINT) (UINT64) Ch2 );

    printf( "\nPress any key to display triggered values " );
	while ( !kbhit() );
    (void) getch();

	// Print measured galvo positions 
	printf( "\nTime [10us]  PhiX [Bit]  PhiY [Bit]" );
	printf( "\n-----------------------------------\n" );
	
    for ( UINT i = 0; i < WavePoints; i++ )
    {
		printf( "%11d %11d %11d\n", i * SamplePeriod, Ch1[ i ], Ch2[ i ] );
        
        if ( ( i & 31 ) == 31 )
        {
            printf( "\nPress any key to continue or <ESC> to abort " );
	        
            while ( !kbhit() ); 
            
            if ( 27 == getch() )
            {
                free_rtc5_dll();
                return;

            }
            else
            {
	            printf( "\nTime [10us]  PhiX [Bit]  PhiY [Bit]" );
	            printf( "\n-----------------------------------\n" );

            }

        }

    }

    terminateDLL();
    return;

}

//  delay
//
//  Description
//
//  The function waits for a n * 10s delay
//
//
//  Parameter   Meaning
//
//  n           n times 10us delay
//
//  Comment
//  This function calls a dummy control command n times
//

void delay( const UINT n )		// n * 10us delay
{
	for ( UINT i = 0; i < n; i++ )
    {
		(void) read_status();		// dummy control function generates a 10us delay

    }

}

//  terminateDLL
//
//  Description
//
//  The function waits for a keyboard hit
//  and then calls free_rtc5_dll().
//  

void terminateDLL()
{
    printf( "- Press any key to shut down \n" );
    
    while( !kbhit() );

    (void) getch();
    printf( "\n" );

    free_rtc5_dll();

}

//  GetValue
//
//  Description
//
//  The function calls get_value( Signal )
//
//
//  Parameter   Meaning
//
//  Signal      Signal to be read
//
//  Comment
//  This function converts from SL2-100 values (20 bits) 
//                           to XY2-100 values (16 bits)
//

short GetValue( const UINT Signal )
{
    return (short) ( get_value( Signal ) >> 4 );

}




