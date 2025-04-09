//  File
//      Demo5.cpp
//
//  Abstract
//      A console application for marking squares and triangles
//      by using a Nd:YAG laser
//
//  Author
//      Bernhard Schrems, SCANLAB AG
//      adapted for RTC5: Hermann Waibel, SCANLAB AG
//
//  Features
//      - explicit linking to the RTC5DLL.DLL
//      - use of external control inputs
//      - use of structured programming
//
//  Comment
//      In case the operating system does not find the RTC5DLL.DLL on
//      program startup, it will respond with a corresponding error
//      message and it will terminate the program.
//
//  Necessary Sources
//      RTC5expl.h, RTC5expl.c
//
//  Environment: Win32
//
//  Compiler
//      - tested with Visual C++ 7.1

// System header files
#include <windows.h>
#include <stdio.h>
#include <conio.h>

// RTC5 header file for explicitly linking to the RTC5DLL.DLL
#include "RTC5expl.h"

struct polygon { long xval, yval; };

#define POLYGONSIZE( figure ) ( sizeof( figure ) / sizeof( polygon ) )

void ProgramDraw( polygon* figure, UINT size, UINT list );
void terminateDLL();

// Change these values according to your system
const UINT   DefaultCard          =            1;   //  number of default card
const UINT   ListMemory1          =         4000;   //  size of list1's memory (default 4000)
const UINT   ListMemory2          =         4000;   //  size of list2's memory (default 4000)
const UINT   LaserMode            =            1;   //  YAG 1 mode
const UINT   LaserControl         =         0x18;   //  Laser signals LOW active (Bits #3 and #4)

// RTC4 compatibility mode assumed
const UINT   AnalogOutChannel     =            1;   //  AnalogOut Channel 1 used
const UINT   AnalogOutValue       =          640;   //  Standard Pump Source Value
const UINT   AnalogOutStandby     =            0;   //  Standby Pump Source Value
const UINT   WarmUpTime           =   2000000/10;   //    2  s [10 us]
const UINT   LaserHalfPeriod      =         50*8;   //   50 us [1/8 us] must be at least 13
const UINT   LaserPulseWidth      =          5*8;   //    5 us [1/8 us]
const UINT   FirstPulseKiller     =        200*8;   //  200 us [1/8 us]
const long   LaserOnDelay         =        100*1;   //  100 us [1 us]
const UINT   LaserOffDelay        =        100*1;   //  100 us [1 us]

const UINT   JumpDelay            =       250/10;   //  250 us [10 us]
const UINT   MarkDelay            =       100/10;   //  100 us [10 us]
const UINT   PolygonDelay         =        50/10;   //   50 us [10 us]
const double MarkSpeed            =        125.0;   //  [16 Bits/ms]
const double JumpSpeed            =       1000.0;   //  [16 Bits/ms]

const UINT   BounceSuppression    =            0;   //    0 ms [ ms ], must be less than 1024

const polygon BeamDump            = { -32000, -32000 }; //  Beam Dump Location

const long   R                    =        10000;   //  size of the figures  

polygon square[] = 
{
    -R, -R,
    -R,  R,
     R,  R,
     R, -R,
    -R, -R
};

polygon triangle[] =
{
    -R,  0,
     R,  0,
     0,  R,
    -R,  0
};

polygon triangle_[] = {
    -R,  0,
     R,  0,
     0, -R,
    -R,  0
};


void __cdecl main( void*, void* )
{
    if ( RTC5open() )
    {
        printf( "Error: RTC5DLL.DLL not found\n" );
        terminateDLL();
        return;

    }

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
                const UINT error = n_get_last_error( i );

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

    ErrorCode = load_correction_file(   0,   // initialize like "D2_1to1.ct5",
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
    reset_error( -1 );    //  Clear all previous error codes

	printf( "Polygon Marking with a Nd:YAG laser\n\n" );

    //  Configure list memory, default: config_list( 4000, 4000 )
    config_list( ListMemory1, ListMemory2 );

    set_laser_mode( LaserMode );

    //  This function must be called at least once to activate laser 
    //  signals. Later on enable/disable_laser would be sufficient.
    set_laser_control( LaserControl );

    set_firstpulse_killer( FirstPulseKiller );

    // Activate a home jump and specify the beam dump 
    home_position( BeamDump.xval, BeamDump.yval );

    // Turn on the optical pump source and wait
    write_da_x( AnalogOutChannel, AnalogOutValue );

    // Timing, delay and speed preset
    set_start_list( 1 );
        long_delay( WarmUpTime );
        set_laser_pulses( LaserHalfPeriod, LaserPulseWidth );
        set_scanner_delays( JumpDelay, MarkDelay, PolygonDelay );
        set_laser_delays( LaserOnDelay, LaserOffDelay );
        set_jump_speed( JumpSpeed );
        set_mark_speed( MarkSpeed );
    set_end_of_list();
    
    execute_list( 1 );

    printf( "Pump source warming up - please wait\r" );

    bounce_supp( BounceSuppression );

    // Load List1 and List2 with triangle or square respectively
    ProgramDraw( triangle, POLYGONSIZE( triangle ), 0 );
    ProgramDraw(   square, POLYGONSIZE(   square ), 1 );

    UINT Busy, Pos;
    UINT StartStop;
    UINT triangleToggle, startFlag, stopFlag;
    long count;

    printf( "Activate /START or press any key to invoke polygon marking \n" );

    triangleToggle = startFlag = 0;
    count = 0;
    stopFlag = 1;
    
    while ( !kbhit() )
    {
        if ( startFlag )
        {
            // Alternately select list buffer 1 or buffer 2, when the
            // execution of the previous figure is finished.
            get_status( &Busy, &Pos );
            
            if ( !Busy )
            {
                if ( triangleToggle )
                {
                    set_extstartpos( 0 );
                    triangleToggle = 0;

                }
                else
                {
                    set_extstartpos( ListMemory1 );
                    triangleToggle = 1;

                }

                startFlag = 0;
            
            }
        
        }
        else 
        {
            // Interrogation of the External Control Inputs

            UINT startActive, startActiveMessage;

            startActive = startActiveMessage = 0;
            
            do 
            {
                // Get the state of the START and STOP signal
                StartStop = get_startstop_info();
                startActive = ~StartStop & 0x1000;  //  bit #12
                StartStop &= 0xA;                   //  bit #1, bit #3
                
                if ( StartStop == 0x2 )             //  bit #1
                {
                    // There was a START request (the programmed figure
                    // is already called) and STOP is not activated
                    startFlag = 1;
                    printf( "START request %d\n", ++count );
                    break;
                    // NOTE
                    // Make use of a bounce-free START signal, only.
                    // Otherwise, the bounces might invoke extra START
                    // requests. Use bounce_supp( BounceSuppression ).

                }
                
                if ( StartStop == 0x8 )             //  bit #3
                {
                    // The STOP is activated. A current execution of the
                    // programmed figure might be stopped.
                    if ( !stopFlag ) printf( "STOP\n" );
                    stopFlag = 1;

                }
                else 
                {
                    if ( StartStop == 0xA )         //  bit #1, bit #3
                    {
                        // There was a START request and the STOP is activated.
                        // A current execution of the programmed figure might
                        // be stopped.
                        if ( stopFlag != 2 ) printf( "START & STOP\n" );
                        stopFlag = 2;

                    }

                    if ( stopFlag && startActive )
                    {
                        // Do not enable the START input as long the START and 
                        // the STOP are activated because a de-activation of
                        // the STOP signal might trigger a START, when the START
                        // input was enabled.
                        if ( !startActiveMessage )
                        {
                            printf( "De-activate the START input to continue\n" );
                            startActiveMessage = 1;
 
                        }

                    }

                }

            } while ( StartStop || startActive );

            if ( stopFlag )
            {
                // Here, before deciding to continue, your application could
                // analyse the reason why there was a STOP initiated.
                printf( "Ready to continue\n" );
                // Enable the START input
                set_control_mode( 1 );
                stopFlag = 0;

            }

        }

    }

    (void) getch();

    if ( startFlag ) stop_execution();

    ProgramDraw( triangle_, POLYGONSIZE( triangle_ ), 0 );
    execute_at_pointer( 0 );

    // Finish
    printf( "\nFinished - press any key to terminate" );

    while ( !kbhit() );

    (void) getch();

    printf( "\n" );
    stop_execution();

    // Activate the pump source standby
    write_da_x( AnalogOutChannel, AnalogOutStandby );

    // Close the RTC5.DLL
    free_rtc5_dll();        //  optional
    RTC5close();
    
    return;

}



//  ProgramDraw
//
//  Description:
//
//  This function programs the specified list buffer with the specified figure.
//  That is, a subsequent call of "execute_at_pointer(ADR)" invokes the
//  execution of the programmed figure, where ADR has to be set to 0, if list
//  buffer 1 was selected or ADR has to be set to ListMemory1, if list buffer 2 
//  was selected. In addition, an activated START signal (pin 8 of the Laser
//  Connector) invokes the execution of the programmed figure, if previously
//  the particular list buffer was selected by calling the corresponding
//  command set_extstartpos(ADR). An activated STOP signal (pin 9 of the Laser
//  Connector) will immediately terminate the execution of the figure.
//  Before "ProgramDraw" begins to program the list buffer, it waits until the
//  marking of a previously transferred polygon is finished.
//
//
//      Parameter   Meaning
//
//      figure      Pointer to a polygon array
//                  The first element of that array specifies the first location
//                  from where the figure will be marked until the last location,
//                  which is specified by the last array element.
//
//      size        Amount of polygons the polygon array contains
//                  In case "size" equals 0, the function immediately returns
//                  without drawing a line.
//
//      list        specifies the list buffer to be loaded. If "list" is set
//                  to 0, list buffer 1 will be loaded. Otherwise, list buffer 2
//                  will be loaded.
//
//  NOTE
//      Make sure that "size" is smaller than configured entries.

void ProgramDraw( polygon* figure, UINT size, UINT list )
{
    //  Do not overwrite the previous list, as long as it is in use.
    //  Wait for the list, until it is no more busy
    while ( !( load_list( ( list ? 2 : 1 ), 0 ) ) );
    //  Now set_start_list_pos( ( list ? 2 : 1 ), 0 ) has been executed 

    UINT i;

    if ( size )
    {
        jump_abs( figure->xval, figure->yval );
        
        for ( i = 0, figure++; i < size - 1; i++, figure++ )
        {
            mark_abs( figure->xval, figure->yval );

        }

    }

    set_end_of_list();

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
    RTC5close();

}


