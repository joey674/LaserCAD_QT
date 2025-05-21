//  File
//      DEMO4.cpp
//
//  Abstract
//      A console application for raster image reproduction
//      by means of a CO2 laser
//
//  Author
//      Bernhard Schrems, SCANLAB AG
//
//  Features
//      - explicit linking to the RTC4DLL.DLL
//      - use of raster image scanning
//
//  Necessary Sources
//      RTC4expl.H, RTC4expl.CPP, MESSAGE.CPP
//
//  Environment: Win32
//
//  Compiler
//      - compiler independent
//      - tested with Visual C++ 5.0 and Visual C++ 6.0


// system header files
#include <windows.h>
#include <stdio.h>
#include <conio.h>

// RTC4 header file for explicitly linking to the RTC4DLL.DLL
#include "RTC4expl.h"

// Desired Image Parameters
#define     PIXELS      512         // pixels per line
#define     LINES       100         // lines per image
#define     X_LOC       -8192       // location of the left side of the image
#define     Y_LOC       3200        // location of the upper side of the image
#define     DOTDIST     32.0        // pixel distance in bits
#define     DOTFREQ     5000        // pixel frequency in Hz
                                    // Note
                                    // The real pixel frequency may vary because
                                    // it will be derived from a multiple of the
                                    // minimum pixel period of 10 microseconds.

// The Image Structure
unsigned char frame[PIXELS][LINES];
struct image {
    short xLocus, yLocus;           // upper left corner of the image in bits
    double dotDistance;             // pixel distance in bits
    unsigned dotFrequency;          // pixel frequency in Hz
    unsigned short ppl;             // pixels per line
    unsigned short lpi;             // lines per image
    unsigned char *raster;          // pointer to the raster data
};

// The particular Image       
image grayStairs = {
    X_LOC, Y_LOC,
    DOTDIST,
    DOTFREQ,
    PIXELS,
    LINES,
    &frame[0][0]
};


int ImagePrint(image *picture);
void stairs2image(image *picture);
void ErrorMessage(short ErrorCode);


void main(void *, void *)
{
    short   ErrorCode;

	printf("Raster image reproduction with a CO2 laser\n\n");

    // Initialize the RTC4DLL.DLL
    if(RTC4open()) {
        printf("Error: RTC4DLL.DLL not found\n");
        printf("Press any key to shut down\n");
        while(!kbhit()) ;
        (void)getch();
        return;
    }

    // Initialize the RTC4
    ErrorCode = load_correction_file("cor_1to1.ctb",
                        1,          // table; #1 is used by default
                        1.0, 1.0,   // scale factor
                        0.0,        // rotation in degrees, counterclockwise
                        0.0, 0.0);  // offset in bits
    if(ErrorCode) {
        printf("Correction file loading error: ");
        ErrorMessage(ErrorCode);
        return;
    }
    ErrorCode = load_program_file("RTC4D2.hex");
    if(ErrorCode) {
        printf("Program file loading error: ");
        ErrorMessage(ErrorCode);
        return;
    }
    set_laser_mode(0);      // CO2 mode selected
    set_standby(0,          // half of the standby period in 1/8 microseconds
                0);         // pulse-width in 1/8 microseconds


    // Timing, delay and speed preset
    set_start_list(1);
    // Hints for using set_laser_timing for pulse-width modulation:
    // Select the 1/8 microseconds time base to get the best time resolution
    // for pulse-width modulation. Set the first three parameters to the
    // largest possible to enable any pixel period and laser pulse-width,
    // which you can set by set_pixel_line or set_pixel, respectively.
    set_laser_timing(0xffff,// half of the laser signal period
            0xffff,0xffff,  // pulse-widths of signals LASER1 and LASER2
                    1);     // time base; 0 corresponds to 1 microsecond.
                            // Otherwise, the time base is 1/8 microseconds.
    set_scanner_delays(25,  // jump delay in 10 microseconds
                    10,     // mark delay in 10 microseconds
                    5);     // polygon delay in 10 microseconds
    // Hints for using set_laser_delays for pulse-width modulation:
    // Set the first parameter (laser_on_delay) of set_laser_delays to 2 for
    // allowing maximum duty cycle of the pixel period. The maximum duty cycle
    // corresponds to a laser pulse-width that equals to the selected pixel
    // period minus 10 microseconds minus (laser on delay) 2 microseconds.
    // The laser pulse is available at pin 1 (LASER1) of the Laser Connector.
    // The second parameter (laser_off_delay) is irrelevant, when applying
    // pulse-width modulation.
    set_laser_delays(2,     // laser on delay in microseconds
                     2);    // laser off delay in microseconds
    set_jump_speed(1000.0); // jump speed in bits per milliseconds
    set_mark_speed(250.0);  // marking speed in bits per milliseconds
    set_end_of_list();
    execute_list(1);


    // Preset the Image
    stairs2image(&grayStairs);

    // Print the Image
    while(!ImagePrint(&grayStairs)) {
        // Do something else while the RTC4 is working. For example:
        // Samsara - turning the wheels
        static char wheel[] = "|/-\\";
        static unsigned index = 0;
        printf("\r- spending idle time %c %c", wheel[3 - index], wheel[index]);
        ++index &= 3;
    }
    printf("\n");


    // Finish
    printf("Finished - press any key to terminate ");
    while(!kbhit()) ;
    (void)getch();
    printf("\n");
    // Close the RTC4.DLL
    RTC4close();
    return;
}


//  ImagePrint
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
//  accomplish raster image reproduction with the RTC4.
//
//  NOTE
//      Make sure that the size of an image line (specified by member "ppl" of
//      the picture) is smaller than 4000 - 1 - X, where X depends on the 
//      amount of applied list commands during the pre-scan and post-scan
//      period.


//  CO2 Laser Parameters

//  Duty cycle range with which the CO2 laser should be controlled
//  NOTE: MAXDUTY should be smaller than the laser's tolerable maximum duty cycle.
#define     MAXDUTY     60                  // corresponds to black, in %
#define     MINDUTY     5                   // corresponds to white, in %

//  General
#define     MEGA        (1000*1000)
#define     FREQBASE    (8*MEGA)            // corresponds to 1/8 microseconds
#define     PERIOD      ((FREQBASE)/DOTFREQ)// period width in 1/8 microseconds

//  Offset and Gain
#define     BLACK       (PERIOD*MAXDUTY)
#define     GRAYGAIN    ((PERIOD*(MAXDUTY-MINDUTY))/255)

//  Pulse-Width
//  - a linear control of the pulse-width within the specified duty cycle range.
// NOTE: If you need an inverted pulse for modulating your CO2 laser, modify the
// jumper setting X10 on the RTC4 board.
#define     PW(gray)    ((unsigned short)((BLACK - GRAYGAIN*(gray))/100))


//  Scan Head Parameters

//  Drag Delay of the scanner
//  When you control a scanner with a constant speed, the scanner mirror will
//  have a particular drag delay. In general, that drag delay does not depend on
//  the selected speed. The drag delay of SCANLAB scanners is between 120 and
//  600 microseconds. Determine the drag delay DRAGDELAY:
#define     DRAGDELAY   360                 // typical drag delay in microseconds

//  Acceleration Period of the scanner
//  The acceleration period of SCANLAB scanners takes about 2 times the drag
//  delay. It is a good idea to select an acceleration period of
#define     AXELPERIOD  (3*DRAGDELAY)       // in microseconds

int ImagePrint(image *picture) {
    static unsigned line = 0;
    static unsigned short pixel_period;
    static unsigned char *pPixel;       // pointer to the current pixel
    static short xCounterbalance;
    static unsigned preDots;

    unsigned i;
    unsigned short busy, position;

    // Determine the pixel period and so on at the beginning of an image
    if(!line) {
        if(picture->dotFrequency < 2)
            pixel_period = 0xffff;
        else
            pixel_period = (unsigned short)(100000/picture->dotFrequency);

        pPixel = picture->raster;   // 1st pixel of the 1st line

        // Determine the amount of idle dots for the pre-scan period
        // and the corresponding counterbalance
        preDots = AXELPERIOD/pixel_period/10;
        xCounterbalance = (short)((double)((AXELPERIOD - DRAGDELAY)/
                            (double)pixel_period/10.0) * picture->dotDistance);
    }

    // Check whether the corresponding list is free to be loaded
    get_status(&busy, &position);
    if(busy)
        if(line & 1) {
            if(position >= 4000) return(0);     // list 2 is busy
        }
        else {
            if(position < 4000) return(0);      // list 1 is busy
        }

    // Open the alternate list
    set_start_list((unsigned short)((line & 1) + 1));

    // A counterbalanced jump to the beginning of the next line
    jump_abs((short)(picture->xLocus - xCounterbalance),
        (short)((double)picture->yLocus - (double)line*picture->dotDistance));

    set_pixel_line(1, pixel_period, picture->dotDistance, 0.0);
    // Pre-scan
    for(i = 0; i < preDots; i++)
        set_pixel(PW(255), 0, 0);
    // Scan
    for(i = 0; i < picture->ppl; i++, pPixel++)
        set_pixel(PW(*pPixel), 0, 0);
    // Post-scan
    set_pixel(0, 0, 0);

    set_end_of_list();

    // Only, apply execute_list for the first list. Otherwise, use auto_change.
    line ? auto_change() : execute_list(1);

    line++;
    if(line == picture->lpi) {
        line = 0;
        return(1);              // Success - image printing finished
    }
    return(0);                  // Image printing not yet finished
}




//  stairs2image
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

#define     STAIRSTEPS      9               // desired amount of gray steps
                                            // the image should contain

#define     IMAGEWHITE      255             // ... black corresponds to 0
#define     GRAYINTERVAL    ((IMAGEWHITE+1)/STAIRSTEPS)

void stairs2image(image *picture) {
    unsigned i, j, k;
    unsigned char *pPixel, *pPixel2;
    unsigned char grayStep;
    unsigned lineInterval, lines;

    lines = picture->lpi;

    // Preset the image to white
    for(j = 0, pPixel = picture->raster; j < lines; j++)
        for(i = 0; i < picture->ppl; i++, pPixel++)
            *pPixel = IMAGEWHITE;

    lineInterval = picture->ppl / STAIRSTEPS;
    // Load the 1st half of the image with a stair that begins with black
    for(j = 0, pPixel2 = pPixel = picture->raster; j < lines/2;
                        j++, pPixel += picture->ppl, pPixel2 = pPixel)
        for(i = 0, grayStep = 0; i < STAIRSTEPS; i++, grayStep += GRAYINTERVAL)
            for(k = 0; k < lineInterval; k++, pPixel2++)
                *pPixel2 = grayStep;

    // Load the 2nd half of the image with a stair that ends with black
    for(j = lines/2; j < lines; j++, pPixel += picture->ppl, pPixel2 = pPixel)
        for(i = 0, grayStep = STAIRSTEPS*GRAYINTERVAL; i < STAIRSTEPS;
                                                i++, grayStep -= GRAYINTERVAL)
            for(k = 0; k < lineInterval; k++, pPixel2++)
                *pPixel2 = grayStep;
}
