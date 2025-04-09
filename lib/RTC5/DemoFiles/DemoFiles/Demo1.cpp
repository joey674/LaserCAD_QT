//  File
//      demo1.cpp
//
//  Abstract
//      A console application for marking a square and a triangle
//      by using a CO2 laser.
//
//  Authors
//      Bernhard Schrems, SCANLAB AG
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
//      If you intend to build a 64-bit executable, you need to link
//      with the RTC5DLLx64.LIB import library to accomplish implicit
//      linking of the 64-bit DLL version RTC5DLLx64.DLL.
//
//  Platform
//      Win32 - 32-bit Windows or
//      x64   - 64-bit Windows.
//
//  Necessary Sources
//      RTC5impl.h, RTC5DLL.LIB for Win32 or RTC5DLLx64.LIB for x64.
//      Notice that RTC5DLL.LIB, RTC5DLLx64.LIB are Visual C++ library.
//
//  Compiler
//      - tested with Visual C++ 2010.

#include <stdio.h>
#include <tchar.h>
#include <conio.h>

// RTC5 header file for implicitly linking to the RTC5DLL.DLL
#include "RTC5impl.h"


// Useful constants
const UINT      ResetCompletely(UINT_MAX);
const LONG      R(20000L);                  //  size parameter of the figures

// Change these values according to your system
const UINT      DefaultCard(1U);            //  number of default card
const UINT      LaserMode(0U);              //  CO2
const UINT      LaserControl(0x18U);        //  Laser signals LOW active
                                            //  (Bit 3 and 4)

// RTC4 compatibility mode assumed
const UINT      StandbyHalfPeriod(100U*8U); //  100 us [1/8 us]
const UINT      StandbyPulseWidth(1U*8U);   //    0 us [1/8 us]
const UINT      LaserHalfPeriod(100U*8U);   //  100 us [1/8 us]
const UINT      LaserPulseWidth(50U*8U);    //   50 us [1/8 us]
const LONG      LaserOnDelay(100L*1L);      //  100 us [1 us]
const UINT      LaserOffDelay(100U*1U);     //  100 us [1 us]

const UINT      JumpDelay(250U/10U);        //  250 us [10 us]
const UINT      MarkDelay(100U/10U);        //  100 us [10 us]
const UINT      PolygonDelay(50U/10U);      //   50 us [10 us]
const double    MarkSpeed(250.0);           //  [16 Bits/ms]
const double    JumpSpeed(1000.0);          //  [16 Bits/ms]


struct polygon
{
    LONG xval, yval;
};

const polygon square[] = 
{
      {-R, -R}
    , {-R,  R}
    , {R,  R}
    , {R, -R}
    , {-R, -R}
};

const polygon triangle[] =
{
      {-R,  0L}
    , {R,  0L}
    , {0L,  R}
    , {-R,  0L}
};


void draw(const polygon *figure, const size_t &size);
void terminateDLL(void);


int _tmain( int     // argc
          , _TCHAR* // argv[]
          )
{
    printf( "Initializing the DLL\n\n" );

    //  This function must be called at the very first
    UINT ErrorCode(init_rtc5_dll());

    if ( ErrorCode != 0U )
    {
        const UINT QuantityOfRTC5s(rtc5_count_cards());

        if ( QuantityOfRTC5s )
        {
            UINT AccError( 0U );

            //  Detailed error analysis
            for ( UINT i(0U); i < QuantityOfRTC5s; i++ )
            {
                const UINT Error(n_get_last_error( i ));

                if ( Error != 0U ) 
                {
                    AccError |= Error;
                    printf( "Card no. %u: Error %u detected\n", i, Error );
                    n_reset_error( i, Error );
                }
            }

            if ( AccError != 0U )
            {
                terminateDLL();
                return(1);
            }
        }
        else
        {
            printf( "Initializing the DLL: Error %u detected\n", ErrorCode );
            terminateDLL();
            return(1);
        }
    }
    else
    {
        if ( DefaultCard != select_rtc( DefaultCard ) )
        {
            ErrorCode = n_get_last_error( DefaultCard );

            if ( ErrorCode & 256U ) //  RTC5_VERSION_MISMATCH
            {
                //  In this case load_program_file(0) would not work.
                ErrorCode = n_load_program_file( DefaultCard, 0 );
            }
            else
            {
                printf( "No acces to card no. %u\n", DefaultCard );
                terminateDLL();
                return(2);
            }

            if ( ErrorCode )
            {
                printf( "No access to card no. %u\n", DefaultCard );
                terminateDLL();
                return(2);
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
        printf( "Program file loading error: %u\n", ErrorCode );
        terminateDLL();
        return(3);
    }

    ErrorCode = load_correction_file( 0,   // initialize like "D2_1to1.ct5",
                                      1U,  // table; #1 is used by default
                                      2U); // use 2D only
    if ( ErrorCode != 0U )
    {
        printf( "Correction file loading error: %u\n", ErrorCode );
        terminateDLL();
        return(4);
    }

    select_cor_table( 1U, 0U ); //  table #1 at primary connector (default)

    //  stop_execution might have created an RTC5_TIMEOUT error
    reset_error(ResetCompletely);

    printf( "Polygon Marking with a CO2 laser\n\n" );

    //  Configure list memory, default: config_list(4000,4000)
    config_list(UINT_MAX,           //  use the list space as a single list
                0U);                //  no space for list 2

    set_laser_mode( LaserMode );

    //  This function must be called at least once to activate laser 
    //  signals. Later on enable/disable_laser would be sufficient.
    set_laser_control( LaserControl );

    set_standby( StandbyHalfPeriod, StandbyPulseWidth );

    // Timing, delay and speed preset
    set_start_list( 1U );
        set_laser_pulses( LaserHalfPeriod, LaserPulseWidth );
        set_scanner_delays( JumpDelay, MarkDelay, PolygonDelay );
        set_laser_delays( LaserOnDelay, LaserOffDelay );
        set_jump_speed( JumpSpeed );
        set_mark_speed( MarkSpeed );
    set_end_of_list();

    execute_list( 1U );

    // Draw
    draw(square, sizeof(square)/sizeof(square[0]));
    draw(triangle, sizeof(triangle)/sizeof(triangle[0]));

    // Finish
    printf( "Finished!\n" );
    terminateDLL();
    return(0);

}



//  draw
//
//  Description:
//
//  Function "draw" transfers the specified figure to the RTC5 and invokes
//  the RTC5 to mark that figure, when the transfer is finished. "draw" waits
//  as long as the marking of a previously tranferred figure is finished before
//  it starts to transfer the specified figure.
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
//  Comment
//  This function demonstrates the usage of a single list. Using list 1 only.
//  You may configure the space of the list up to 2^20 entries totally.
//
//  NOTE
//      Make sure that "size" is smaller than the configured entries.

void draw(const polygon *figure, const size_t &size)
{
    if ( size )
    {
        // Only, use list 1, which can hold up to the configured entries
        while ( !load_list( 1U, 0U ) ) {} //  wait for list 1 to be not busy
        //  load_list( 1, 0 ) returns 1 if successful, otherwise 0
        //  set_start_list_pos( 1, 0 ) has been executed

        jump_abs( figure->xval, figure->yval );
        
        size_t i(0U);
        for ( figure++; i < size - 1U; i++, figure++ )
        {
            mark_abs( figure->xval, figure->yval );
        }

        set_end_of_list();
        execute_list( 1U );

    }
}

//  terminateDLL
//
//  Description
//
//  The function waits for a keyboard hit
//  and then calls free_rtc5_dll().
//  

void terminateDLL(void)
{
    printf( "- Press any key to exit.\n" );
    
    while(!_kbhit()) {}
    printf( "\n" );

    free_rtc5_dll();
}
