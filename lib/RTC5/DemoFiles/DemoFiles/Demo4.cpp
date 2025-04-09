//  File
//      Demo4.cpp
//
//  Abstract
//      A console application for raster image reproduction
//      by means of a CO2 laser
//
//  Author
//      Bernhard Schrems, SCANLAB AG
//      adapted for RTC5: Hermann Waibel, SCANLAB AG
//
//  Features
//      - explicit linking to the RTC5DLL.DLL
//      - use of raster image scanning
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

//  Do not change this value
const unsigned int MinDLL = 505;         //  at least release 505 is required
//  set_n_pixel is not available with earlier versions

// System header files
#include <windows.h>
#include <stdio.h>
#include <conio.h>

// RTC5 header file for explicitly linking to the RTC5DLL.DLL
#include "RTC5expl.h"

void terminateDLL();        //  waits for a keyboard hit to terminate

//  Change these values according to your system
const UINT   DefaultCard          =            1;   //  number of default card
const UINT   ListMemory1          =       100000;   //  size of list1's memory (default 4000)
const UINT   ListMemory2          =       100000;   //  size of list2's memory (default 4000)
const UINT   LaserMode            =            0;   //  CO2 mode
const UINT   LaserControl         =         0x18;   //  Laser signals LOW active (Bits #3 and #4)

//  RTC4 compatibility mode assumed
const UINT   LaserHalfPeriod      =        100*8;   //  100 us [1/8 us] must be at least 13
const UINT   LaserPulseWidth      =         50*8;   //   50 us [1/8 us]
const UINT   StandbyHalfPeriod    =          0*8;   //    0 us [1/8 us] must be at least 13
const UINT   StandbyPulseWidth    =          0*8;   //    0 us [1/8 us]
const long   LaserOnDelay         =        100*1;   //  100 us [1 us]
const UINT   LaserOffDelay        =        100*1;   //  100 us [1 us]

const UINT   JumpDelay            =       250/10;   //  250 us [10 us]
const UINT   MarkDelay            =       100/10;   //  100 us [10 us]
const UINT   PolygonDelay         =        50/10;   //   50 us [10 us]
const double MarkSpeed            =        250.0;   //  [16 Bits/ms]
const double JumpSpeed            =       1000.0;   //  [16 Bits/ms]

//  Additional constants for pixelmode
const UINT   AnalogOutChannel     =            1;   //  must be 1 or 2, (used in Pixelmode)
const UINT   LaserOffAnalog       =    (UINT) -1;   //  DefaultValue
const UINT   LaserOffDigital      =    (UINT) -1;   //  DefaultValue
const UINT   DefaultPixel         =            0;   //  'last' pixel in Pixelmode

const UINT   AnalogBlack          =            0;   //  0 - 4095
const UINT   AnalogWhite          =         1023;   //  0 - 4095
const UINT   DigitalBlack         =            0;   //  PulseWidth for Black
const UINT   DigitalWhite         = LaserPulseWidth;//  PulseWidth for White

//  Pulse Width and AnalogOut
//  - a linear control of the pulse width and AnalogOut 
//    within the specified black and white range.
const long   AnalogGain           = ( (long)  AnalogWhite - (long)  AnalogBlack ) / 255;
const long   DigitalGain          = ( (long) DigitalWhite - (long) DigitalBlack ) / 255;

const double SpeedFactor          = 1.0 / 1000.0;
const long   Offset = (long) ( (double) LaserOnDelay * MarkSpeed * SpeedFactor );
//  During the LaserOnDelay [us] the scan-axes move at an average speed of 
//  MarkSpeed [bits/ms] * SpeedFactor. SpeedFactor takes into account the accelerating 
//  period, depending on the scan model used, besides converting from bits/ms into bits/us.

//  Desired Image Parameters
const UINT   Pixels               =          512;   //  pixels per line
const UINT   Lines                =          100;   //  lines per image
const long   X_Location           =        -8192;   //  location of the left side of the image
const long   Y_Location           =         3200;   //  location of the upper side of the image
const double DotDistance          =         32.0;   //  pixel distance  [bits]
const UINT   PixelHalfPeriod      =        100*8;   //  100 us [1/8 us] must be at least 13

// The Image Structure
unsigned char frame[ Pixels ][ Lines ];

struct image 
{
    long    xLocus, yLocus;     // upper left corner of the image in bits
    double  dotDistance;        // pixel distance in bits
    UINT    dotHalfPeriod;      // pixel half period in 1/8 us
    UINT    ppl;                // pixels per line
    UINT    lpi;                // lines per image
    unsigned char *raster;      // pointer to the raster data
};

// The particular Image       
image grayStairs = 
{
    X_Location, Y_Location,
    DotDistance,
    PixelHalfPeriod,
    Pixels,
    Lines,
    &frame[ 0 ][ 0 ]
};

void MakeStairs( image* picture );      //  creates the image data
int  PrintImage( image* picture );

void __cdecl main( void*, void* )
{
    printf( "Initializing the DLL\n\n" );

    if ( RTC5open() )
    {
        printf( "Error: RTC5DLL.DLL not found\n" );
        terminateDLL();
        return;

    }

    const UINT DLLVersion = get_dll_version();

    if ( DLLVersion < MinDLL )
    {
        printf( "DLL version %d too low, at least %d required!\n", DLLVersion, MinDLL );
        terminateDLL();
        return;

    }

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
    reset_error( -1 );    //  clear all previous error codes

	printf( "Raster image reproduction with a CO2 laser\n\n" );

    //  Configure list memory, default: config_list( 4000, 4000 ).
    //  Make sure, that the list memories exceed a pixel line
    config_list( ListMemory1, ListMemory2 );

    set_laser_mode( LaserMode );
    set_standby( StandbyHalfPeriod, StandbyPulseWidth );

    //  This function must be called at least once to activate laser 
    //  signals. Later on enable/disable_laser would be sufficient.
    set_laser_control( LaserControl );

    set_default_pixel( DefaultPixel );
    set_laser_off_default( LaserOffAnalog, LaserOffAnalog, LaserOffDigital );

    // Timing, delay and speed preset
    set_start_list( 1 );
        set_laser_pulses( LaserHalfPeriod, LaserPulseWidth );
        set_scanner_delays( JumpDelay, MarkDelay, PolygonDelay );
        set_laser_delays( LaserOnDelay, LaserOffDelay );
        set_jump_speed( JumpSpeed );
        set_mark_speed( MarkSpeed );
    set_end_of_list();
    
    execute_list( 1 );

    //  set_laser_pulses is optional, laser parameters are newly defined 
    //  in set_pixel_line and set_[n_]pixel.
    //  The first pixel will be marked LaserOnDelay after set_pixel_line.
    //  Adjust LaserOnDelay to eliminate scan-axis' accelerating effect.
    //  LaserOffDelay is irrelevant in Pixelmode.
    //  set_mark_speed is optional. In Pixelmode the marking speed is
    //  defined by the pixel distance and the pixel (half) period.

    //  Preset the Image
    MakeStairs( &grayStairs );

    //  Print the Image
    while ( !PrintImage( &grayStairs ) )
    {
        // Do something else while the RTC5 is working. For example:
        // Samsara - turning the wheels
        static char wheel[] = "||//--\\\\";
        static UINT index = 0;
        printf( "\r- spending idle time %c %c", wheel[ 7 - index ], wheel[ index ] );
        ++index &= 7;

    }

    printf( "\n" );

    // Finish
    printf( "\nFinished - press any key to terminate " );

    while ( !kbhit() );

    (void) getch();

    printf( "\n" );

    // Close the RTC5.DLL
    free_rtc5_dll();        //  optional
    RTC5close();
    
    return;

}


//  MakeStairs
//
//  Description:
//
//  This function loads the upper and the lower half of the specified picture
//  with equidistant gray stairs that begin with black and end with black,
//  respectively.
//
//
//      Parameter   Meaning
//
//      picture     Pointer to a picture to be loaded with gray stairs

void MakeStairs( image* picture )
{
    const UINT STAIRSTEPS   =   9;   
    // Desired amount of gray steps the image should contain.
    // White corresponds to 255 and black corresponds to 0.
    const UINT GRAYINTERVAL = 256 / STAIRSTEPS;

    UINT i, j, k;
    UINT lineInterval, lines;
    unsigned char *pPixel, *pPixel2;
    unsigned char grayStep;

    lines = picture->lpi;

    // Preset the image to white
    for ( j = 0, pPixel = picture->raster; j < lines; j++ )
    {
        for ( i = 0; i < picture->ppl; i++, pPixel++ )
        {
            *pPixel = 255;  //  image white;

        }

    }

    lineInterval = picture->ppl / STAIRSTEPS;
    
    // Load the 1st half of the image with a stair that begins with black
    for ( j = 0, pPixel2 = pPixel = picture->raster; 
          j < lines / 2;
          j++, pPixel += picture->ppl, pPixel2 = pPixel )
    {
        for ( i = 0, grayStep = 0; i < STAIRSTEPS; i++, grayStep += GRAYINTERVAL )
        {
            for ( k = 0; k < lineInterval; k++, pPixel2++ )
            {
                *pPixel2 = grayStep;

            }

        }

    }

    // Load the 2nd half of the image with a stair that ends with black
    for ( j = lines / 2; 
          j < lines; 
          j++, pPixel += picture->ppl, pPixel2 = pPixel )
    {
        for ( i = 0, grayStep = STAIRSTEPS * GRAYINTERVAL;
              i < STAIRSTEPS;
              i++, grayStep -= GRAYINTERVAL )
        {
            for ( k = 0; k < lineInterval; k++, pPixel2++ )
            {
                *pPixel2 = grayStep;

            }

        }

    }

}

//  PrintImage
//
//  Description:
//
//  This function prints the specified picture by means of a CO2 laser.
//  On success, that is when printing is finished, 1 is returned.
//  Otherwise, 0 is returned - in this case, call it again until 1 is returned.
//
//
//      Parameter   Meaning
//
//      picture     Pointer to an image to be printed
//
//
//  Comment
//  This function demonstrates how to utilize both list buffers for an
//  uninterrupted, continuous data transfer. Furthermore, it shows how to
//  accomplish raster image reproduction with the RTC5.
//
//  NOTE
//      Make sure that the configured ListMemory1 and ListMemory2 are 
//      larger than the size of an image line (specified by member "ppl" of
//      the picture) and the amount of applied list commands during 
//      the pre-scan and post-scan period.

int PrintImage( image* picture )
{
    static int line = 0;                // current line
    static unsigned char *pPixel;       // pointer to the current pixel

    if ( !line )
    {
        pPixel = picture->raster;       // 1st pixel of the 1st line

    }

    //  Check whether the corresponding list is free to be loaded.
    //  If successful load_list returns the list number, otherwise 0 
    if ( !load_list( ( line & 1 ) + 1, 0 ) ) return 0;

    //  Now, the list is no more busy and already opened 
    //  set_start_list_pos( ( line & 1 ) + 1, 0 ) has been excuted

    // A jump to the beginning of the next line
    jump_abs( picture->xLocus - Offset,
              picture->yLocus - (long) ( (double) line * picture->dotDistance ) );

    set_pixel_line( AnalogOutChannel, PixelHalfPeriod, picture->dotDistance, 0.0 );

    unsigned char Pixel( *pPixel++ );
    UINT PixelCount( 1 );

    for ( UINT i = 1; i < picture->ppl; i++, pPixel++ )
    {
        //  Save list buffer space for identical pixel values
        if ( *pPixel == Pixel )
        {
            PixelCount++;

        }
        else
        {
            set_n_pixel( (UINT) ( DigitalBlack + DigitalGain * Pixel ),
                         (UINT) (  AnalogBlack +  AnalogGain * Pixel ),
                         PixelCount );
            PixelCount = 1;
            Pixel = *pPixel;

        }

    }

    set_n_pixel( (UINT) ( DigitalBlack + DigitalGain * Pixel ),
                 (UINT) (  AnalogBlack +  AnalogGain * Pixel ),
                 PixelCount );
    
    set_end_of_list();

    // Only, apply execute_list for the first list. Otherwise, use auto_change.
    line ? auto_change() : execute_list( 1 );

    line++;

    if ( line == picture->lpi )
    {
        line = 0;
        return 1;              // Success - image printing finished

    }

    return 0;                  // Image printing not yet finished

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


