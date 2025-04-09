//  File
//      Demo6.cpp
//
//  Abstract
//      A console application for demonstrating marking on the fly and 
//      pixelmode for CO2 laser with alternating lists, additionally 
//      using 16 Bit-IO-Port and showing data sampling and time measurement.
//      The preset control switches mark a chess field centered to (0,0),
//      not using fly corrections nor manipulating the 16 Bit-IO-Port.
//
//  Author
//      Hermann Waibel, SCANLAB AG
//
//  Comment
//      Besides demonstrating of how to initialize the RTC5 and how to
//      perform marking, this application also shows how to implicitly
//      link to the RTC5DLL.DLL. For accomplishing implicit linking -
//      also known as static load or load-time dynamic linking of a DLL,
//      the header file RTC5impl.h is included and for building the
//      executable, you must link with the (Visual C++) import library
//      RTC5DLL.LIB.
//      In case the operating system does not find the RTC5DLL.DLL on
//      program startup, it will respond with a corresponding error
//      message and it will terminate the program.
//
//  Necessary Sources
//      RTC5impl.h, RTC5DLL.LIB
//      NOTE: RTC5DLL.LIB is a Visual C++ library.
//
//  Environment: Win32
//
//  Compiler
//      - tested with Visual C++ 7.1

//  Do not change this value
const unsigned int MinDLL = 505;         //  at least release 505 is required
//  set_n_pixel is not available with earlier versions

// System header files
#include <windows.h>
#include <stdio.h>
#include <conio.h>

// RTC5 header file to implicitly link to the RTC5DLL.DLL
#include "RTC5impl.h"

void terminateDLL();            //  waits for a keyboard hit to terminate

// Change these values according to your system
const UINT   DefaultCard          =        1;  //  number of default card
const UINT   LaserMode            =        0;  //  CO2
const UINT   LaserControl         =     0x18;  //  Laser signals LOW active (Bits #3 and #4)

const UINT   StandbyHalfPeriod    =     0*64;  //    0 us [1/64 us] must be at least 104
const UINT   StandbyPulseWidth    =     0*64;  //    0 us [1/64 us]
const UINT   LaserHalfPeriod      =    20*64;  //   20 us [1/64 us] must be at least 104
const UINT   LaserPulseWidth      =    10*64;  //   10 us [1/64 us]
const long   LaserOnDelay         =    100*2;  //  100 us [1/2 us]
const UINT   LaserOffDelay        =    100*2;  //  100 us [1/2 us]

const UINT   JumpDelay            =   250/10;  //  250 us [10 us]
const UINT   MarkDelay            =   100/10;  //  100 us [10 us]
const UINT   PolygonDelay         =    50/10;  //   50 us [10 us]
const double MarkSpeed            =   2500.0;  //  [Bits/ms]
const double JumpSpeed            =  10000.0;  //  [Bits/ms]

const UINT   Calibration          =    10000;  //  [Bit/mm] (depending on the scanner model)

// Constants for chess bitmap
const double SquareSize           =      1.0;  //  single square's side length [mm]
const UINT   SquareNumber         =      4*2;  //  size of chess field, should be even
const UINT   PixelNumber          =       20;  //  pixels per single square's side length

// Constants for pixelmode
const UINT   AnalogBlack          =        0;  //  0 - 4095
const UINT   AnalogWhite          =     1023;  //  0 - 4095
const UINT   DigitalBlack         =        0;
const UINT   DigitalWhite         = LaserPulseWidth;
const UINT   AnalogChannel        =        1;  //  channel must be 1 or 2
const UINT   LaserOffAnalog       = (UINT)-1;  //  DefaultValue
const UINT   LaserOffDigital      = (UINT)-1;  //  DefaultValue
const UINT   DefaultPixel         =        0;  //  'last' pixel in Pixelmode

// Constants for encoder
const double CountRate            =      1.0;  //  CountRate [MHz] (encoder pulses)
const double EncoderSpeed         =      1.0;  //  Speed of conveyor belt

// Control switches
const bool   CheckMode            =    false;  //  true: use 16 Bit-IO-Port and test print out
const bool   FlyCorrection        =    false;  //  true: on
const bool   SimulateEncoder      =     true;  //  use encoder signals (true:simulated, false:external)
const bool   SampleData           =     true;  //  true: on

void __cdecl main( void*, void* )
{
    const UINT DLLVersion = get_dll_version();

    if ( DLLVersion < MinDLL )
    {
        printf( "DLL version %d too low, at least %d required!\n", DLLVersion, MinDLL );
        terminateDLL();
        return;

    }

    UINT ErrorCode;

    printf( "Initializing the DLL\n\n" );

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
        if ( DefaultCard != select_rtc( DefaultCard ) )
        {   //  Exclusive ownership of DefaultCard was not possible
            ErrorCode = n_get_last_error( DefaultCard );

            if ( ErrorCode & 256 )    //  RTC5_VERSION_MISMATCH
            {
                //  In this case load_program_file( 0 ) would not work.
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
                printf("load_program_file failed! Error %d\n", ErrorCode );
                terminateDLL();
                return;

            }
            else
            {   //  n_load_program_file was successfull
                (void) select_rtc( DefaultCard );

            }

        }

    }

    // Initialize the RTC5
    stop_execution();
    //  If the DefaultCard has been used previously by another application 
    //  a list might still be running. This would prevent load_program_file
    //  and load_correction_file from being executed.

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

    //  stop_execution might have created a RTC5_TIMEOUT error
    reset_error( -1 );  //  clear all previous errors

    //  Configure list memory
    //  Using two lists
    config_list( 100000,    //  list space 1 (default: 4000)
                 100000 );  //  list space 2 (default: 4000)
    //  Using total space as a single list
    //config_list( -1,        //  list space 1 is 2^20 (maximum)
    //              0 );      //  list space 2 is 0
    //  CAUTION: The code below must be modified for marking the bitmap

    //  Initializing laser parameters
    set_laser_mode( LaserMode );
    set_standby( StandbyHalfPeriod, StandbyPulseWidth );

    //  This function must be called at least once to activate laser 
    //  signals. Later on enable/disable_laser would be sufficient.
    set_laser_control( LaserControl );
    
    set_default_pixel( DefaultPixel );
    set_laser_off_default( LaserOffAnalog, LaserOffAnalog, LaserOffDigital );
    
    set_control_mode( 1 );       //  allow external start/stop

    // Timing, delay and speed preset
    set_start_list( 1 );
        set_laser_pulses( LaserHalfPeriod, LaserPulseWidth );
        set_scanner_delays( JumpDelay, MarkDelay, PolygonDelay );
        set_laser_delays( LaserOnDelay, LaserOffDelay );
        set_jump_speed( JumpSpeed );
        set_mark_speed( MarkSpeed );
    set_end_of_list();
    
    execute_list( 1 );

    printf( "Initializing...\n" );

    //  Demo example: marking a chess field of about N mm * N mm (N = SquareSize), 

    //  Calibration 10000 means a field size of about 105 mm * 105 mm
    //  i. e. N*N single squares of 1 mm * 1 mm each or 10000 bits per length (= Calibration)
    
    //  LaserFullPeriod 40 us and assuming 100 * 100 pulses (pixels) per single square
    //  means 100 Bits pixel distance or marking speed 2500.0 Bits/ms or 25.0 [Bits/10us]

    const double PixelDistance = (double) Calibration * SquareSize / (double) PixelNumber;
    
    //  The scan-axis' starting position needs some offset due to LaserOnDelay
    //  Adjust LaserOnDelay to eliminate scan-axis' accelerating effect.

    const double SpeedFactor   = 1.0 / 1000.0;
    const long Offset = (long) ( (double) LaserOnDelay / 2.0 * MarkSpeed * SpeedFactor + 0.5 );

    //  Offset assumes a constant average MarkSpeed during LaserOnDelay, because in real life 
    //  the scan-axes must be accelerated and therefore move somewhat less than they would do
    //  with full MarkSpeed, depending on the actual model used. For a precise positioning 
    //  the SpeedFactor takes this into account, besides converting from bits/ms into bits/us.

    //  EstimatedTime means the time for marking the Offset (Laser Off) and the complete
    //  pixel line (Laser On, N*PixelNumber pixels at PixelDistance) 
    //  and the time for jumping back to the beginning of the next pixel line, 
    //  neglecting some minor delays for reading list commands.

    const double Length = (double) Offset + PixelDistance * (double) ( SquareNumber * PixelNumber );
    const double EstimatedTime = Length / MarkSpeed * 1000.0 + Length / JumpSpeed * 1000.0
                                + (double) ( JumpDelay * 10 ); //   [us]

    //  If the speed of the conveyor belt equals about 
    //      PixelDistance / Calibration / EstimatedTime * 1e6 [mm/s]
    //  then the x-Position is quite stable. 
    
    //  If it's much slower, then the x-position will leave the field limits towards one side of 
    //  the image field (against the moving direction of the conveyor belt). But then you can 
    //  use wait_for_encoder to let the conveyor belt move into the field limits again.
    
    //  In that case (much slower) you can use the virtual image field to load list commands with 
    //  coordinates up to eight times of the original field size and use wait_for_encoder at run time
    //  to let the conveyor belt move into the original field. Virtual image field coordinates 
    //  in the moving direction of the conveyor belt or perpendicular to it cannot be compensated
    //  and would be clipped at the original image field limits.

    //  If it's much faster, then the x-position will leave the field limits towards the opposite side
    //  (same side as the moving direction of the conveyor belt) with no chance to compensate for it. 
    //  The virtual image field will not help in this case (see above).

    //  Prepare marking on the fly
        //  Assuming conveyor belt moving in -x direction
        //  Marking pixel lines in +y direction
        //  Assuming 1 MHz count rate (frequency of encoder simulation)
        //  Assuming a simulated speed of the conveyor belt
        //  1 pulse at 40 us period needs 100/40 [Bit/us] = 2.5 Bit/Count as scale factor

    const double ScaleFactor = PixelDistance / CountRate * EncoderSpeed
                                / (double) LaserHalfPeriod * 64.0 / 2.0;   //  [Bits/Count]
    //  It might be neccessary to change the sign of ScaleFactor due to the incoming encoder pulses.
    //  See RTC5 manual (Chap. 8.6) how to determine the ScaleFactor for real systems.
    //  ScaleFactor [Bits/Count] = Calibration [Bit/mm] * ConveyorSpeed [mm/s] / CountRate / 1e6;

    //  Centered Bitmap, beginning at the right side (against the moving direction 
    //  of the conveyor belt) and stepping towards the left side

    const double EdgePos = PixelDistance * (double) ( SquareNumber / 2 * PixelNumber );

    if ( SimulateEncoder )
    {
        simulate_encoder( 1 );  //  simulates 1 MHz encoder pulses

    }

    printf( "Marking Chess field\n\n" );

    //  Using alternating lists (one list per pixel line each).
    //  Next auto_change would start list 2, as soon as list 1 has finished,
    //  therefore start with list no 2.

    UINT ListNo1( 1 );                  //  denotes ListNo - 1, in order to use "& 1" for 
                                        //  odd/even detection for list 1 / list 2

    (void) load_list( ListNo1 + 1, 0 ); //  list 2 definitely isn't busy in this case

        if ( FlyCorrection )
        {
            set_fly_x( ScaleFactor );   //  option "processing on the fly" must be enabled

        }

        if ( SampleData )
        {
            set_trigger( 1, 7, 8 );     //  Period, SampleX, SampleY

        }

        save_and_restart_timer();       //  time measurement

    //  set_end_of_list and auto_change are placed within the following loop.
    
    UINT IOValue;   //  used for CheckMode only

    for ( UINT i = 0; i < SquareNumber; i++ )
    {  
        printf( "Chess field line no. %d\n", i );

        if ( CheckMode )
        {
            printf( "This: No i  j prev: No i  j\n\n" );
        
        }

        for ( UINT j = 0; j < PixelNumber; j++ )
        { 
            set_end_of_list();  //  close this list
            auto_change();      //  execute this list as soon as previous list has finished
            
            ListNo1++;          //  propagate to next list no.

            //  Do not overwrite the previous list, as long as it is in use.
            //  Dait for the list, until it is no more busy.

            while ( !( load_list( ( ListNo1 & 1 ) + 1, 0 ) ) );

            //  Now set_start_list_pos( ListNo1 + 1, 0 ) has been executed 

            if ( CheckMode )
            {
                IOValue = get_io_status();              //  16 Bit-IO-Port value of previous list
                write_io_port_list( ( ListNo1 & 1 ) * 10000 + i * 100 + j );  //  same for this list

            }

            //  Jump to the beginning of the line
            jump_abs( (long) (  EdgePos - (double) ( i * PixelNumber + j ) * PixelDistance ),
                      (long) ( -EdgePos - (double) Offset ) );

            //  Initialize the pixel line
            set_pixel_line( AnalogChannel,      //  channel no. for analog output
                            LaserHalfPeriod,    //  pixel frequency
                            0.0,                //  not moving in x direction
                            PixelDistance );    //  moving towards +y direction
 
            //  Write the pixels
            for ( UINT k = 0; k < SquareNumber / 2; k++ )
            {
                if ( i & 1 )    //  odd 
                {
                    set_n_pixel( DigitalWhite, AnalogWhite, PixelNumber );
                    set_n_pixel( DigitalBlack, AnalogBlack, PixelNumber );

                }
                else            //  even
                {
                    set_n_pixel( DigitalBlack, AnalogBlack, PixelNumber );
                    set_n_pixel( DigitalWhite, AnalogWhite, PixelNumber );

                }

            }   //  end of for k

            if ( CheckMode )
            {
                printf( "%8d%2d%3d%8d%2d%3d\n", (ListNo1 & 1)+1, i, j, 
                               IOValue/10000+1, (IOValue%10000)/100, IOValue%100 );

            }

        }   //  end of for j

    }   //  end of for i

    //  Complete and close the last list.
    save_and_restart_timer();   //  measure elapsed time

    if ( SampleData )
    {
        set_trigger( 0, 7, 8 );

    }

    //  Finish marking on the fly and return to the center of the image field.
    if ( FlyCorrection )
    {
        fly_return( 0, 0 );

    }

    set_end_of_list();

    //  Start the just loaded list, when the currently executing list has finished.
    auto_change_pos( 0 );

    UINT Busy, Pos;

    //  Wait for no list busy
    do
    {
        get_status( &Busy, &Pos );

    }
    while ( Busy );

    if ( CheckMode )
    {
        IOValue = get_io_status();
        printf( "Final:       %8d%2d%3d\n", IOValue/10000+1, (IOValue%10000)/100, IOValue%100 );
    
    }

    printf( "\nElapsed marking time: %.3f seconds\n\n", get_time() );

    printf( "Finished!\n" );
    terminateDLL();
	return;

}

void terminateDLL()
{
    printf( "- Press any key to shut down \n" );

    while( !kbhit() );

    (void) getch();
    printf( "\n" );

    free_rtc5_dll();

}
