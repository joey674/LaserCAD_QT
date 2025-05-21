//  File
//      DEMO3.cpp
//
//  Abstract
//      A console application for continuously plotting Archimedean spirals
//      by means of a Nd:YAG laser
//
//  Author
//      Bernhard Schrems, SCANLAB AG
//
//  Features
//      - explicit linking to the RTC4DLL.DLL
//      - use of both list buffers for continuous data transfer
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
#include <math.h>

// RTC4 header file for explicitly linking to the RTC4DLL.DLL
#include "RTC4expl.h"


// Definition of "pi"
#define     SL_PI       3.14159265358979323846

// Spiral Parameters
#define     AMPLITUDE   10000.0
#define     PERIOD      512.0       // amount of vectors per turn
#define     OMEGA       (2*SL_PI/PERIOD)


// Desired Nd:YAG Laser Timing for YAG mode 1
#define     LASER       10000       // Laser pulse frequency in Hz
#define     PULSE       5           // pulse width in microseconds
#define     PULSE1ST    2           // amount of pulses the first
                                    // pulse killer FPK
                                    // should be active
// Frequency Base
#define     MEGA        (1000*1000)
#define     FREQBASE    (8*MEGA)            // corresponding to a time base
                                            // of 1/8 microseconds
// Derived Laser Timing in microseconds
#define     FPK         ((100*PULSE1ST+50)*FREQBASE/100/LASER)
#define     HALF_PERIOD (FREQBASE/LASER/2)
#define     PULSE_WIDTH (PULSE*FREQBASE/MEGA)


// End Locus of a Vector
struct locus {
    short xval, yval;
};

// Beam Dump Location
locus BeamDump = {
    -32000, -32000
};


void ErrorMessage(short ErrorCode);
int PlotVector(const locus &destination, unsigned *start, unsigned *PlotLaunch);
void PlotFlush(void);


void main(void *, void *)
{
    unsigned short  busy, position;
    short           ErrorCode;
    unsigned        CarryOn, stopped, start, eventOff, PlotLaunch, flush;
    int             i, limit, status;
    locus           point;
    double          turns, span, increment;

	printf("Archimedean spirals\n\n");

    // Initialize the RTC4DLL.DLL
    if(RTC4open()) {
        printf("Error: RTC4DLL.DLL not found\n");
        printf("Press any key to shut down\n");
        while(!kbhit()) ;
        (void)getch();
        return;
    }


    // Initialize the RTC

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
    set_laser_mode(1);      // YAG mode 1 selected
    set_firstpulse_killer(FPK);

    // Activate a home jump and specify the beam dump 
    home_position(BeamDump.xval, BeamDump.yval);

    // Turn on the optical pump source and wait for 2 seconds
    // (The following assumes that signal ANALOG OUT1 of the laser connector
    //  controls the pump source)
    write_da_1(640);

    // Timing, delay and speed preset
    // Transmit the following list commands to the list buffer
    set_start_list(1);
    // Wait for 2 seconds
    long_delay(50000);
    long_delay(50000);
    long_delay(50000);
    long_delay(50000);
    set_laser_timing(
            HALF_PERIOD,    // half of the laser signal period
            PULSE_WIDTH, 2, // pulse widths of signal LASER1
            1);             // time base; 0 corresponds to 1 microsecond.
                            // Otherwise, the time base is 1/8 microseconds.
    set_scanner_delays(25,  // jump delay in 10 microseconds
                    10,     // mark delay in 10 microseconds
                    5);     // polygon delay in 10 microseconds
    set_laser_delays(100,   // laser on delay in microseconds
                    100);   // laser off delay in microseconds
    set_jump_speed(1000.0); // jump speed in bits per milliseconds
    set_mark_speed(250.0);  // marking speed in bits per milliseconds
    set_end_of_list();
    execute_list(1);

    printf("Pump source warming up - please wait\r");
    do {
        get_status(&busy, &position);
    } while(busy);

    // Plot
    printf("Press 1, 2, ... or 9 to set the number of revolutions.\n");
    printf("Press S to suspend or R to resume plotting.\n");
    printf("Press O to turn off or R to restart plotting.\n");
    printf("Press F to flush the list buffers and to terminate.\n");
    printf("Any other key will halt plotting and terminate.\n\n");
    turns = 5.0;
    printf("\r--- revolutions: %d ---", (int)turns);
    increment = AMPLITUDE/turns/PERIOD;
    limit = (int)PERIOD*(int)turns;

    for(flush = status = eventOff = stopped = i = 0, span = increment,
            PlotLaunch = start = CarryOn = 1; CarryOn;
            i++, eventOff = 0, span += increment) {
        if(i == limit) {
            i = 0;
            span = increment;
            start = 1;
        }
        point.xval = (short)(span*sin(OMEGA*(double)i));
        point.yval = (short)(span*cos(OMEGA*(double)i));
        while(eventOff ? status : !PlotVector(point, &start, &PlotLaunch)) {
            if(kbhit()) {
                char ch;

                ch = (char)getch();
                switch(ch) {
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
                        turns = (double)(ch ^ '0');
                        if(!stopped && !eventOff)
                            printf("\r--- revolutions: %d ---", (int)turns);
                        // NOTE
                        //  Modifying the number of turns might not immediately
                        //  take effect, because both list buffers can still
                        //  hold vectors from a previous setting.
                        increment = AMPLITUDE/turns/PERIOD;
                        span = 0;
                        limit = (int)PERIOD*(int)turns;
                        start = eventOff = 1;
                        i = -1;
                        break;
                    case 'f':
                    case 'F':
                        // Buffer flushing requested
                        if(!eventOff) {
                            if(stopped) restart_list();
                            printf("\r- flushing the queue -");
                            flush = eventOff = 1;
                            status = CarryOn = 0;
                        }
                        break;
                    case 's':
                    case 'S':
                        // Sudden suspending requested
                        if(!eventOff) {
                            stop_list();
                            // Subsequent list commands will not be executed
                            // as long "stop_list" is active
                            printf("\r- plotting suspended -");
                            stopped = 1;
                        }
                        break;
                    case 'r':
                    case 'R':
                        // Resume to plot
                        if(eventOff) {
                            status = 0;
                            span = 0;
                            i = -1;
                            PlotLaunch = start = 1;
                        }
                        else {
                            restart_list();
                            stopped = 0;
                        }
                        enable_laser();
                        printf("\r--- revolutions: %d ---", (int)turns);
                        break;
                    case 'o':
                    case 'O':
                        // Stop request
                        // Remove a pending "stop_list" call before calling 
                        // "stop_execution"
                        disable_laser();
                        if(stopped) restart_list();
                        stop_execution();
                        printf("\r- plotting turned off ");
                        // Do not transfer list commands as long
                        // "stop_execution" is active
                        eventOff = status = 1;
                        break;
                    default:
                        // Halt and terminate
                        // Remove a pending "stop_list" call before calling 
                        // "stop_execution"
                        disable_laser();
                        if(stopped) restart_list();
                        stop_execution();
                        printf("\r-- plotting terminated --\n");
                        status = CarryOn = 0;
                        eventOff = 1;
                }
            }
        }
    }
    // Flush the list buffers, on request.
    if(flush)   PlotFlush();

    // Finish
    printf("\nFinished - press any key to terminate ");
    // Activate the pump source standby
    write_da_1(0);
    while(!kbhit()) ;
    (void)getch();
    printf("\n");
    // Close the RTC4.DLL
    RTC4close();
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
unsigned ListStart, FirstTime;

int PlotVector(const locus &destination, unsigned *start, unsigned *PlotLaunch) {
    static unsigned list;
    static unsigned ListLevel;
    unsigned short busy, position;

    if(*PlotLaunch) {
        do {
            get_status(&busy, &position);
        } while(busy);
        list = 1;
        ListStart = 1;
        ListLevel = 0;
        FirstTime = 1;
        *PlotLaunch = 0;
    }
    else {
        // On a list swap, check whether the list "list" is free to be loaded
        if(ListStart) {
            get_status(&busy, &position);
            if(busy)
                if(list == 2) {
                    if(position >= 4000) return(0);     // list 2 is busy
                }
                else {
                    if(position < 4000) return(0);      // list 1 is busy
                }
        }
    }

    // Open the list at the beginning
    if(ListStart)  set_start_list((unsigned short)list);
    ListStart = 0;
    ListLevel++;

    if(*start) {
        jump_abs(destination.xval, destination.yval);
        *start = 0;
    }
    else
        mark_abs(destination.xval, destination.yval);

    if(ListLevel < 4000 - 1)    return(1);      // Success

    set_end_of_list();
    ListStart = 1;

    // Only, apply execute_list for the very first time.
    // Otherwise, use auto_change.
    if(FirstTime) {
        execute_list(1);    
        FirstTime = 0;
    }
    else auto_change();

    list = list == 1 ? 2 : 1;
    ListLevel = 0;

    return(1);                                  // Success
}



//  PlotFlush
//
//  Description:
//
//  The call of that function ensures to empty and to execute the remaining
//  contents of the list buffers.
//

void PlotFlush(void) {
    if(ListStart) return;
    else {
        set_end_of_list();
        FirstTime ? execute_list(1) : auto_change();
    }
}
