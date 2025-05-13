//  File
//      Demo3.cpp
//
//  Abstract
//      A console application for continuously plotting Archimedean spirals
//      by using a Nd:YAG laser
//
//  Author
//      Bernhard Schrems, SCANLAB AG
//      adapted for RTC5: Hermann Waibel, SCANLAB AG
//
//  Features
//      - explicit linking to the RTC5DLL.DLL 显式动态库链接
//      - use of both list buffers for continuous data transfer 使用两个链表的autochange来打
//      - exception handling
//
//  Comment
//      This routine demonstrates how to use both list buffers for a
//      continuous data transfer by applying the command "auto_change"
//      on a loaded list buffer. Methods to halt and to resume the data
//      transfer are also shown.
//      The spirals are only exposing as Archimedean spirals, if the
//      scan head is built up with a F-Theta-lens.
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
#include <math.h>

// RTC5 header file for explicitly linking to the RTC5DLL.DLL
#include "RTC5expl.h"

// Definition of "pi"
const double Pi                   = 3.14159265358979323846;

//  Change these values according to your system
const UINT   DefaultCard        =           1;   //  number of default card
const UINT   ListMemory         =        4000;   //  size of list memory (default 4000)
const UINT   LaserMode          =           1;   //  YAG 1 mode
const UINT   LaserControl       =        0x18;   //  Laser signals LOW active (Bits #3 and #4)

//  RTC4 compatibility mode assumed
const UINT   AnalogOutChannel   =           1;   //  AnalogOut Channel 1 used
const UINT   AnalogOutValue     =         640;   //  Standard Pump Source Value
const UINT   AnalogOutStandby   =           0;   //  Standby Pump Source Value
const UINT   WarmUpTime         =  2000000/10;   //    2  s [10 us]
const UINT   LaserHalfPeriod    =        50*8;   //   50 us [1/8 us] must be at least 13
const UINT   LaserPulseWidth    =         5*8;   //    5 us [1/8 us]
const UINT   FirstPulseKiller   =       200*8;   //  200 us [1/8 us]
const long   LaserOnDelay       =       100*1;   //  100 us [1 us]
const UINT   LaserOffDelay      =       100*1;   //  100 us [1 us]

const UINT   JumpDelay          =      250/10;   //  250 us [10 us]
const UINT   MarkDelay          =      100/10;   //  100 us [10 us]
const UINT   PolygonDelay       =       50/10;   //   50 us [10 us]
const double MarkSpeed          =       250.0;   //  [16 Bits/ms]
const double JumpSpeed          =      1000.0;   //  [16 Bits/ms]

// Spiral Parameters
const double Amplitude          =     10000.0;
const double Period             =       512.0;   // amount of vectors per turn
const double Omega              = 2.0*Pi/Period;

// End Locus of a Vector
struct locus { long xval, yval; };

const locus BeamDump            = { -32000, -32000 }; //  Beam Dump Location

 int PlotVector( const locus& destination, UINT* start, UINT* PlotLaunch );
void PlotFlush();
void terminateDLL();            //  waits for a keyboard hit to terminate

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
    //  and load_correction_file from being executed.

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

    /// ***************************************draw
	printf( "Archimedean spirals\n\n" );

    //  Configure list memory, default: config_list( 4000, 4000 ).
    //  Two lists with the same size each
    config_list( ListMemory, ListMemory );

    set_laser_mode( LaserMode );
    set_firstpulse_killer( FirstPulseKiller );

    //  This function must be called at least once to activate laser 
    //  signals. Later on enable/disable_laser would be sufficient.
    set_laser_control( LaserControl );

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

    UINT Busy, Pos;
    
    do 
    {
        get_status( &Busy, &Pos );
    
    } while ( Busy );

    UINT    CarryOn, stopped, start, eventOff, PlotLaunch, flush;
    int     i, limit, status;
    locus   point;
    double  turns, span, increment;

    // Plot
    printf( "Press 1, 2, ... or 9 to set the number of revolutions.\n" );
    printf( "Press S to suspend or R to resume plotting.\n" );
    printf( "Press O to turn off or R to restart plotting.\n" );
    printf( "Press F to flush the list buffers and to terminate.\n" );
    printf( "Any other key will halt plotting and terminate.\n\n" );

    turns = 5.0;
    printf( "\r--- revolutions: %d ---", (int) turns );

    increment = Amplitude / turns / Period;
    limit = (int) Period * (int) turns;

    for ( flush = status = eventOff = stopped = i = 0, span = increment,
            PlotLaunch = start = CarryOn = 1; 
          CarryOn;
          i++, eventOff = 0, span += increment )
    {
        if ( i == limit )
        {
            i = 0;
            span = increment;
            start = 1;
        
        }

        point.xval = (long)( span * sin( Omega * (double) i ) );
        point.yval = (long)( span * cos( Omega * (double) i ) );
        
        while ( eventOff ? status : !PlotVector( point, &start, &PlotLaunch ) )
        {
            if ( kbhit() )
            {
                char ch;

                ch = (char) getch();

                switch( ch )
                {
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        // Turns setup requested
                        turns = (double) ( ch ^ '0' );

                        if ( !stopped && !eventOff )
                        {
                            printf( "\r--- revolutions: %d ---", (int) turns );

                        }

                        // NOTE
                        //  Modifying the number of turns might not immediately
                        //  take effect, because both list buffers can still
                        //  hold vectors from a previous setting.
                        
                        increment = Amplitude / turns / Period;
                        span = 0;
                        limit = (int) Period * (int) turns;
                        start = eventOff = 1;
                        i = -1;
                        break;
                    case 'f':
                    case 'F':
                        // Buffer flushing requested

                        if ( !eventOff )
                        {
                            restart_list();
                            //  If not paused previously, 
                            //  get_last_error() returns 32 (RTC5_BUSY)

                            printf( "\r- flushing the queue -" );
                            flush = eventOff = 1;
                            status = CarryOn = 0;

                        }
                        break;
                    case 's':
                    case 'S':
                        // Sudden suspending requested
                        
                        if ( !eventOff )
                        {
                            pause_list();
                            // Subsequent list commands will not be executed
                            // as long "pause_list" is active
                            printf( "\r- plotting suspended -" );
                            stopped = 1;

                        }
                        break;
                    case 'r':
                    case 'R':
                        // Resume to plot
                        
                        if ( eventOff )
                        {
                            status = 0;
                            span = 0;
                            i = -1;
                            PlotLaunch = start = 1;

                        }
                        else 
                        {
                            restart_list();
                            stopped = 0;
                        
                        }
                        
                        enable_laser();
                        printf( "\r--- revolutions: %d ---", (int) turns );
                        break;
                    case 'o':
                    case 'O':
                        // Stop request
                        disable_laser();
                        // Remove a pending "pause_list" call before calling 
                        // "stop_execution"
                        restart_list(); //  optional
                        //  If not stopped previously, 
                        //  get_last_error() returns 32 (RTC5_BUSY)
                        stop_execution();
                        printf( "\r- plotting turned off " );
                        // Do not transfer list commands as long
                        // "stop_execution" is active
                        eventOff = status = 1;
                        break;
                    default:
                        // Halt and terminate
                        disable_laser();
                        // Remove a pending "pause_list" call before calling 
                        // "stop_execution"
                        restart_list(); //  optional
                        //  If not stopped previously, 
                        //  get_last_error() returns 32 (RTC5_BUSY)
                        stop_execution();
                        printf( "\r-- plotting terminated --\n" );
                        status = CarryOn = 0;
                        eventOff = 1;

                }   //  switch

            }   //  kbhit()

        }   //  while

    }   //  for

    // Flush the list buffers, on request.
    if ( flush )  PlotFlush();

    // Finish
    printf( "\nFinished - press any key to terminate " );

    // Activate the pump source standby
    write_da_x( AnalogOutChannel, AnalogOutStandby );

    while ( !kbhit() );

    (void) getch();

    printf( "\n" );

    // Close the RTC5.DLL
    free_rtc5_dll();        //  optional
    RTC5close();
    
    return;

}

//  PlotVector
//
//  Description:
//
//  Function "PlotVector" tries to transfer the specified vector to one
//  of the two list buffers. If the particular list buffer is filled,
//  "PlotVector" automatically invokes the execution of that list buffer. 
//  A subsequent "PlotVector" call will swap the list buffer and load it
//  with the specified vector.
//  On success, the return is 1.
//  Otherwise, 0 is returned - call function "PlotVector" again till it
//  returns 1. Then "PlotVector" can be called with a next vector.
//  When the vector transfer is finished, call function "PlotFlush" to
//  execute the remaining vectors in the list buffers.
//  The first time "PlotVector" is called with a particular vector,
//  parameter "PlotLaunch" must be set to greater 0. That parameter will
//  automatically be reset to 0 on subsequent "PlotVector" calls.
//
//
//      Parameter   Meaning
//
//      destination The end location of a vector
//
//      start       causes to mark a vector from the current to the
//                  specified location, if "start" is set to 0.
//                  Otherwise, it causes to jump to the specified location
//                  without marking and parameter "start" will automatically
//                  be reset to 0.
//      PlotLaunch  launches the function "PlotVector", if set to greater 0.
//                  That parameter will automatically be reset to 0.

// PlotVector specific variables
UINT ListStart, FirstTime;

int PlotVector( const locus& destination, UINT* start, UINT* PlotLaunch )
{
    static UINT list;
    static UINT ListLevel;

    if ( *PlotLaunch )
    {
        list = 1;
        ListStart = 1;
        ListLevel = 0;
        FirstTime = 1;
        *PlotLaunch = 0;

        //  Wait for list 1 to be not busy,
        //  then open the list at the beginning
        while ( !load_list( list, 0 ) );
        // set_start_list_pos( list, 0 ) has been executed
    
    }
    else 
    {
        // On a list swap, check whether the list "list" is free to be loaded
        if ( ListStart )
        {
            //  Open the list at the beginning
            if ( !load_list( list, 0 ) ) return 0;
            //  load_list returns list, if not busy, otherwise 0
            //  set_start_list_pos( list, 0 ) has been executed
        }
   
    }

    ListStart = 0;
    ListLevel++;

    if ( *start )
    {
        jump_abs( destination.xval, destination.yval );
        *start = 0;

    }
    else
    {
        mark_abs( destination.xval, destination.yval );

    }

    if ( ListLevel < ListMemory - 1 ) return 1;      // Success

    set_end_of_list();
    ListStart = 1;

    // Only, apply execute_list for the very first time.
    // Otherwise, use auto_change.
    if ( FirstTime )
    {
        execute_list( 1 );    
        FirstTime = 0;

    }
    else
    {
        auto_change();

    }

    list = ( list == 1 ? 2 : 1 );
    ListLevel = 0;

    return 1;                                  // Success

}



//  PlotFlush
//
//  Description:
//
//  The call of that function ensures to empty and to execute the remaining
//  contents of the list buffers.
//

void PlotFlush()
{
    if ( ListStart ) return;

    set_end_of_list();
    FirstTime ? execute_list( 1 ) : auto_change();

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


