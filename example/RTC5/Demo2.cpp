//  File
//      Demo2.cpp
//
//  Abstract
//      A console application for continuously plotting Lissajous figures
//      by using a Nd:YAG laser
//
//  Author
//      Bernhard Schrems, SCANLAB AG
//      adapted for RTC5: Hermann Waibel, SCANLAB AG
//
//  Features
//      - explicit linking to the RTC5DLL.DLL 显式动态库链接
//      - use of the list buffer as a single list like a circular queue  
//        for continuous data transfer 使用单list作为循环队列操作
//      - exception handling
//
//  Comment
//      This application demonstrates how to explicitly link to the
//      RTC5DLL.DLL. For accomplishing explicit linking - also known as
//      dynamic load or run-time dynamic linking of a DLL, the header
//      file RTC5expl.H is included.
//      Before calling any RTC5 function, initialize the DLL by calling
//      the function RTC5open.
//      When the usage of the RTC5 is finished, close the DLL by 
//      calling the function RTC5close.
//      For building the executable, link with the RTC5EXPL.OBJ, which
//      you can generate from the source code RTC5expl.c.
//
//      This routine also shows how to use the list buffer as a circular
//      queue. Methods to halt and to resume the data transfer are also shown.
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

// Change these values according to your system
const UINT   DefaultCard          =            1;   //  number of default card
const UINT   ListMemory           =        10000;   //  size of list 1 memory (default 4000)
const UINT   LaserMode            =            1;   //  YAG 1 mode
const UINT   LaserControl         =         0x18;   //  Laser signals LOW active (Bits #3 and #4)
const UINT   StartGap             =         1000;   //  gap ahead between input_pointer and out_pointer
const UINT   LoadGap              =          100;   //  gap ahead between out_pointer and input_pointer
const UINT   PointerCount         =         0x3F;   //  pointer mask for checking the gap

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
const double MarkSpeed            =        250.0;   //  [16 Bits/ms]
const double JumpSpeed            =       1000.0;   //  [16 Bits/ms]

// Spiral Parameters
const double Amplitude            =      10000.0;
const double Period               =        512.0;   // amount of vectors per turn
const double Omega                = 2.0*Pi/Period;

// End Locus of a Line
struct locus { long xval, yval; };

const locus BeamDump              = { -32000, -32000 }; //  Beam Dump Location

 int PlotLine( const locus& destination, UINT* start );
void PlotFlush();
void terminateDLL();            //  waits for a keyboard hit to terminate


int main( void*, void* )
{
    if ( RTC5open() )
    {
        printf( "Error: RTC5DLL.DLL not found\n" );
        terminateDLL();
        return 0;

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
                return 1;

            }

        }
        else 
        {
            printf( "Initializing the DLL: Error %d detected; no cards;\n", ErrorCode );
            terminateDLL();
            return 1;

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
                return 1;

            }

            if ( ErrorCode )
            {
                printf( "No access to card no. %d\n", DefaultCard );
                terminateDLL();
                return 1;

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
        return 1;

    }

    ErrorCode = load_correction_file(   0,   // initialize like "D2_1to1.ct5",
                                        1,   // table; #1 is used by default
                                        2 ); // use 2D only
    if ( ErrorCode )
    {
        printf( "Correction file loading error: %d\n", ErrorCode );
        terminateDLL();
        return 1;

    }

    select_cor_table( 1, 0 );   //  table #1 at primary connector (default)

    //  stop_execution might have created a RTC5_TIMEOUT error
    reset_error( -1 );    //  clear all previous error codes


    //////////////////////////////////////////////////////////////////////////////

	printf( "Lissajous figures\n\n" );

    //  Configure list memory, default: config_list( 4000, 4000 ).
    //  One list only
    config_list( ListMemory, 0 );
    //  input_list_pointer and out_list_pointer will jump automatically 
    //  from the end of the list onto position 0 each without using
    //  set_end_of_list. auto_change won't be executed.
    //  RTC4::set_list_mode( 1 ) is no more supported

    set_laser_mode( LaserMode );
    set_firstpulse_killer( FirstPulseKiller );

    //  This function must be called at least once to activate laser 
    //  signals. Later on enable/disable_laser would be sufficient.
    set_laser_control( LaserControl );

    // Activate a home jump and specify the beam dump 
    home_position( BeamDump.xval, BeamDump.yval );

    // Turn on the optical pump source
    write_da_x( AnalogOutChannel, AnalogOutValue );



    //////////////////////////////////////////////////////////////////////////


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

    //  Wait until the execution is finished, before launching PlotLine.

    //  Pos denotes the position of the set_end_of_list command.
    //  The position of the input pointer is Pos + 1.
    //  set_start_list_pos( 1, Pos + 1 );   //  optional

    //  Do not send set_end_of_list(), unless you want to finish.
    //  The list buffer then behaves like a circular queue.
    //  Initialize the execution of the list explicitly, as soon as
    //  the input_pointer is StartGap ahead (see PlotLine) via
    //      execute_list_pos( 1, Pos + 1 )
    //  Make sure, that the input_pointer is always ahead of the 
    //  out_pointer and that they don't overtake each other.
    //  If they come too close (LoadGap), the input_pointer will wait or
    //  the out_pointer will be suspended via set_wait (see PlotLine).
    //
    //  CAUTION: WINDOWS might suspend the working thread at any time.
    //  Make sure, that StartGap is large enough so that the out_pointer
    //  can't overtake the input_pointer during that time.
    //  It is recommended to use two alternating lists with set_end_of_list 
    //  and auto_change instead of the continuous download demonstrated.
    //
    //  NOTE: Downloading list commands is buffered with buffer size 16.

    UINT    CarryOn, stopped, start, eventOff;
    int     i;
    locus   point;
    double  FrequencyFactor( 2.0 );

    // Plot
    printf( "Press 0, 1, ... or 9 to correspondingly modify the frequency ratio.\n" );
    printf( "Press S to suspend or R to resume plotting.\n" );
    printf( "Press O to turn off or R to restart plotting.\n" );
    printf( "Press F to flush the circular queue and to terminate.\n" );
    printf( "Any other key will halt plotting and terminate.\n\n" );
    printf( "\rY/X frequency ratio: %d", (int) FrequencyFactor );

    for ( eventOff = stopped = i = 0, start = CarryOn = 1; CarryOn; i++ )
    {
        point.xval = (long) ( Amplitude * sin( Omega * (double) i ) );
        point.yval = (long) ( Amplitude * sin( FrequencyFactor * Omega * (double) i ) );

        while ( !PlotLine( point, &start ) )// 返回false就是给rtc5失败了 就会进入循环一直重试, 同时看有无键盘输入; 如果成功了就打下一个点(但是这里有问题 如果plot一直成功 就不会接收用户输入)
        {
            if ( kbhit() )
            {
                const char ch( (char) getch() );

                switch( ch )
                {
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        // Frequency ratio setup requested
                        FrequencyFactor = (double) ( ch ^ '0' );
                        i = -1;
                        start |= 1;

                        if( !stopped )
                        {
                            printf( "\rY/X frequency ratio: %d", (int) FrequencyFactor );
                            // NOTE
                            //  Modifying the frequency ratio might not immediately
                            //  take effect, because the circular queue can still
                            //  hold lines from a previous frequency ratio setup.
                        }
                        else 
                        {
                            if ( eventOff )
                            {
                                disable_laser();
                                // In case there is a pending stop request, throw
                                // away the contents of the circular queue.
                                restart_list(); //  optional
                                //  Does nothing, if not paused previously
                                //  get_last_error returns 32 (RTC5_BUSY)
                                stop_execution();
                                start |= 2;     //  disable execute_list_pos

                            }

                        }
                        break;
                    case 'f':
                    case 'F':
                        // Buffer flushing requested
                        restart_list();
                        //  Does nothing, if not paused previously, 
                        //  get_last_error() returns 32 (RTC5_BUSY)
                        printf( "\r- flushing the queue -" );
                        CarryOn = 0;
                        start |= 8;    //  final flushing
                        break;
                    case 's':
                    case 'S':
                        // Sudden suspending requested
                        pause_list();
                        // Subsequent list commands will not be executed
                        // as long as "pause_list" is active
                        printf( "\r- plotting suspended -" );
                        stopped = 1;
                        break;
                    case 'r':
                    case 'R':
                        // Resume to plot
                        enable_laser();
                        restart_list();
                        //  Does nothing, if not paused previously, 
                        //  get_last_error() returns 32 (RTC5_BUSY)
                        printf( "\rY/X frequency ratio: %d", (int) FrequencyFactor );
                        stopped = 0;
                        eventOff = 0;
                        start &= ~2;    //  enable execute_list_pos
                        break;
                    case 'o':
                    case 'O':
                        // Stop request
                        printf( "\r-------- wait --------" );
                        disable_laser();
                        // Remove a pending "pause_list" call before calling 
                        // "stop_execution" 
                        restart_list(); //  optional
                        //  Does nothing, if not paused previously, 
                        //  get_last_error() returns 32 (RTC5_BUSY)
                        stop_execution();
                        printf( "\r- plotting turned off " );
                        stopped = 1;
                        i = -1;
                        eventOff = 1;
                        start = 3; //  start = 1 + 2 (disable execute_list_pos)
                        break;
                    default:
                        // Halt and terminate
                        disable_laser();
                        // Remove a pending "pause_list" call before calling 
                        // "stop_execution"
                        restart_list(); //  optional
                        //  Does nothing, if not paused previously, 
                        //  get_last_error() returns 32 (RTC5_BUSY)
                        stop_execution();
                        printf( "\r-- plotting terminated --\n" );
                        eventOff = 1;
                        CarryOn = 0;
                        start |= 8;     //  final flushing

                }   //  switch

            }   //   kbhit

            if ( eventOff || ( start & 1 ) ) break;

        }   //  while 

    }   //  for

    // Flush the circular queue, on request.
    if ( !eventOff )
    {
        set_end_of_list();

        do
        {
            get_status( &Busy, &Pos );

        }
        while ( Busy );
        //  Busy & 0x0001: list is still running
        //  Busy & 0x00fe: list has finished, but home_jump is still active
        //  Not possible after stop_execution:
        //  Busy & 0xff00: list paused (pause_list or set_wait)

    }

    // Finish
    printf( "\nFinished - press any key to terminate" );

    // Activate the pump source standby
    write_da_x( AnalogOutChannel, AnalogOutStandby );

    while ( !kbhit() );

    (void) getch();

    printf( "\n" );

    // Close the RTC5.DLL
    free_rtc5_dll();        //  optional
    RTC5close();
    
    return 0;

}

//  PlotLine
//
//  Description:
//
//  Function "PlotLine" tries to transfer a line to the circular queue.
//  On success, the return is 1.
//  Otherwise, 0 is returned - call function "PlotLine" again till it returns 1.
//  Then "PlotLine" can be called with a next line.
//  When the line transfer is finished, send set_end_of_list and wait for
//  executing the remaining lines in the list buffer.
//
//  If the input_pointer tends to overtake the out_pointer, downloading
//  list commands is suspended (return 0) until the out_pointer is more than
//  LoadGap ahead.
//  If the out_pointer tends to overtake the input_pointer (distance smaller
//  than StartGap/2, a set_wait command is sent and release_wait called,
//  as soon as the input_pointer is more than StartGap ahead again.
//  PointerCount allows a block download without checking for set_wait and
//  execute_list_pos (useful to increase the download speed if the PC is slow).
//  Warnings are displayed, if the pointers come too close.
//
//
//      Parameter   Meaning
//
//      destination The end location of a line
//
//      start       causes to mark a straight line from the current to the
//                  specified location, if "start & 1" is set to 0.
//                  Otherwise, it causes to jump to the specified location
//                  without marking and parameter "start" will automatically
//                  be reset to "start &= ~1".
//                  "start & 2" prevents execute_list_pos from being executed.
//                  "start & 4" set_wait has been sent already
//                  "start & 8" final flushing requested, no set_wait sent
//

int PlotLine( const locus& destination, UINT* start )
{
    UINT Busy, OutPos, InPos;

    InPos = get_input_pointer();
    
    if ( ( InPos & PointerCount ) == PointerCount )
    {
        get_status( &Busy, &OutPos );

        //  Busy & 0x0001: list is still executing, may be paused via pause_list
        //  Busy & 0x00fe: list has finished, but home_jumping is still active
        //  Busy & 0xff00: && (Busy & 0x00ff) = 0: set_wait
        //                 && (Busy & 0x00ff) > 0: pause_list

        //  List is running and not paused, no home_jumping
        if ( Busy == 0x0001 )
        {
            //  If OutPos comes too close to InPos it would overtake. Let the list wait.
            if (   ( ( InPos >= OutPos ) && ( InPos - OutPos < StartGap / 2 ) )
                || ( ( InPos <  OutPos ) && ( InPos + ListMemory - OutPos < StartGap / 2 ) )
               )
            {   //  *start & 4: Set_wait already pending
                //  *start & 8: Final flushing requested, the out_pointer MUST 
                //              come very close to the last input_pointer.
                if ( !( *start & 4 ) && !( *start & 8 ) )
                {
                    *start |= 4;
                    set_wait( 1 );
                    InPos = get_input_pointer();
                    printf( "\r\t\t\t\tWARNING: Wait In =%6d Out = %6d", InPos, OutPos );

                }

            }

        }   //  Busy == 0x0001

        //  List not running and not paused, no home_jumping
        if  ( !Busy )
        {
            if ( !( *start & 2 ) )   //  execute_list_pos enabled
            {
                //  If InPos is far enough ahead of OutPos, start the list
                if (   ( ( InPos > OutPos ) && ( InPos - OutPos > StartGap ) )
                    || ( ( InPos < OutPos ) && ( InPos + ListMemory - OutPos > StartGap ) )
                   )
                {
                    if ( ( OutPos + 1 ) == ListMemory ) 
                    {
                        execute_list_pos( 1, 0 );

                    }
                    else
                    {
                        execute_list_pos( 1, OutPos + 1 );

                    }

                    //const UINT Error( get_last_error() );
                    //if ( Error )
                    //{
                    //    printf( "\r\t\t\t\tError %d Pos = %5d", Error, OutPos );
                    //
                    //}

                }

            }   //  *start & 2

        }   //  !Busy

        //  List not running and not home_jumping, but paused via set_wait
        if ( !( Busy & 0x00ff ) && ( Busy & 0xff00 ) )
        {
            //  If InPos is far enough ahead of OutPos, release the list
            if ( *start & 4 )   //  set_wait pending
            {
                if (   ( ( InPos > OutPos ) && ( InPos - OutPos > StartGap ) )
                    || ( ( InPos < OutPos ) && ( InPos + ListMemory - OutPos > StartGap ) )
                   )
                {
                    release_wait();
                    *start &= ~4;
                    printf( "\r\t\t\t\tRelease" );

                }

            }   //  *start & 4
        
        }   //  !( Busy & 0x00ff ) && ( Busy & 0xff00 )

    }   //  PointerCount

    get_status( &Busy, &OutPos );

    if (   ( ( InPos > OutPos ) && ( ListMemory - InPos + OutPos > LoadGap ) )
        || ( ( InPos < OutPos ) && ( InPos + LoadGap ) < OutPos )
       )
    {
        if ( *start & 1 )
        {
            jump_abs( destination.xval, destination.yval );
            *start &= ~1;

        }
        else
        {
            mark_abs( destination.xval, destination.yval );

        }

        return 1;   //  success

    }
    else
    {
        //  NOTE: If so-called short list commands are used (mark and jump aren't short)
        //  more than one list command might be executed within the same 10 us period.
        //  Thus OutPos does not always behave like OutPos++.
        //  The same holds for list commands like mark_text (not used within this demonstration).
        //  They may occupy more than one list positions.

        //  *start & 8: at final flushing, the out_pointer MUST come very close to
        //  the last input_pointer.

        if ( Busy && !( *start & 8 )
             && ( abs( (long) InPos - (long) OutPos ) < LoadGap / 10 ) )
        {
            printf( "\r\t\t\t\tWARNING: In= %6d  Out= %6d", InPos, OutPos );

        }

        return 0;   //  repeat PlotLine

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
    RTC5close();

}


