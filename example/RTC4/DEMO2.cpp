//  File
//      DEMO2.cpp
//
//  Abstract
//      A console application for continuously plotting Lissajous figures
//      by means of a Nd:YAG laser
//
//  Author
//      Bernhard Schrems, SCANLAB AG
//
//  Features
//      - explicit linking to the RTC4DLL.DLL
//      - use of the list buffers as a circular queue for continuous data
//        transfer
//      - exception handling
//
//  Comment
//      This application demonstrates how to explicitly link to the
//      RTC4DLL.DLL. For accomplishing explicit linking - also known as
//      dynamic load or run-time dynamic linking of a DLL, the header
//      file RTC4EXPL.H is included.
//      Before calling any RTC4 function, initialize the DLL by calling
//      the function RTC4open.
//      When the usage of the RTC4 is finished, close the DLL by 
//      calling the function RTC4close.
//      For building the executable, link with the RTC4EXPL.OBJ, which
//      you can generate from the source code RTC4EXPL.CPP.
//
//      This routine also shows how to use the list buffers as a circular
//      queue. Methods to halt and to resume the data transfer are also shown.
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

// Figure Parameters
#define     AMPLITUDE   20000.0
#define     PERIOD      512.0               // amount of lines per figure
#define     OMEGA       (2*SL_PI/PERIOD)


// Desired Nd:YAG Laser Timing for YAG mode 1
#define     LASER       10000               // Laser pulse frequency in Hz
#define     PULSE       5                   // pulse width in microseconds
#define     PULSE1ST    2                   // amount of pulses the first
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


// End Locus of a Line
struct locus {
    short xval, yval;
};

// Beam Dump Location
locus BeamDump = {
    -32000, -32000
};

void ErrorMessage(short ErrorCode);
int PlotLine(const locus &destination, unsigned *start);
void PlotFlush(void);


void main(void *, void *)
{
    unsigned short  busy, position;
    short           ErrorCode;
    unsigned        CarryOn, stopped, start, eventOff;
    int             i;
    locus           point;
    double          FrequencyFactor;

	printf("Lissajous figures\n\n");


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
    // Enable the circular queue
    // Make the decision for the circular queue mode immediately after the
    // program file is loaded.
    set_list_mode(1);       // from now on, the list buffers are configured
                            // as a circular queue

    set_laser_mode(1);      // YAG mode 1 selected
    set_firstpulse_killer(FPK);

    // Activate a home jump and specify the beam dump 
    home_position(BeamDump.xval, BeamDump.yval);

    // Turn on the optical pump source and wait for 2 seconds
    // (The following assumes that signal ANALOG OUT1 of the laser connector
    //  controls the pump source)
    write_da_1(640);
    // Wait for 2 seconds
    long_delay(50000);
    long_delay(50000);
    long_delay(50000);
    long_delay(50000);

    // Timing, delay and speed preset
    // Following list commands are written to the circular queue
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

    // Execute the list commands in the circular queue and tell about the
    // wait period.
    PlotFlush();
    printf("Pump source warming up - please wait\r");
    // Wait as long the execution is finished, before launching PlotLine
    do {
        get_status(&busy, &position);
    } while(busy);

    // Plot
    printf("Press 0, 1, ... or 9 to correspondingly modify the frequency ratio.\n");
    printf("Press S to suspend or R to resume plotting.\n");
    printf("Press O to turn off or R to restart plotting.\n");
    printf("Press F to flush the circular queue and to terminate.\n");
    printf("Any other key will halt plotting and terminate.\n\n");
    FrequencyFactor = 2.0;
    printf("\rY/X frequency ratio: %d", (int)FrequencyFactor);

    for(eventOff = stopped = i = 0, start = CarryOn = 1; CarryOn; i++) {
        point.xval = (short)(AMPLITUDE*sin(OMEGA*(double)i));
        point.yval = (short)(AMPLITUDE*sin(FrequencyFactor*OMEGA*(double)i));
        while(!PlotLine(point, &start)) {
            if(kbhit()) {
                short   currentX, currentY;
                char    ch;

                ch = (char)getch();
                switch(ch) {
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
                        FrequencyFactor = (double)(ch ^ '0');
                        i = -1;
                        start = 1;

                        if(!stopped)
                            printf("\rY/X frequency ratio: %d", (int)FrequencyFactor);
                            // NOTE
                            //  Modifying the frequency ratio might not immediately
                            //  take effect, because the circular queue can still
                            //  hold lines from a previous frequency ratio setup.
                        else if(eventOff) {
                            // In case there is a pending stop request, throw
                            // away the contents of the circular queue.
                            disable_laser();
                            restart_list();
                            stop_execution();
                            stop_list();
                        }
                        break;
                    case 'f':
                    case 'F':
                        // Buffer flushing requested
                        if(stopped) restart_list();

                        printf("\r- flushing the queue -");
                        CarryOn = 0;
                        break;
                    case 's':
                    case 'S':
                        // Sudden suspending requested
                        stop_list();
                        // Subsequent list commands will not be executed
                        // as long "stop_list" is active

                        printf("\r- plotting suspended -");
                        stopped = 1;
                        break;
                    case 'r':
                    case 'R':
                        // Resume to plot
                        restart_list();
                        enable_laser();
                        printf("\rY/X frequency ratio: %d",(int)FrequencyFactor);
                        stopped = 0;
                        eventOff = 0;
                        break;
                    case 'o':
                    case 'O':
                        // Stop request
                        printf("\r-------- wait --------");
                        // Remove a pending "stop_list" call before calling 
                        // "stop_execution"
                        disable_laser();
                        if(stopped) restart_list();

                        stop_execution();
                        // For a subsequent "stop_list" call, wait till the
                        // home jump is finished.
                        do {
                            get_xy_pos(&currentX, &currentY);
                        } while( currentX != BeamDump.xval ||
                                 currentY != BeamDump.yval);
                        stop_list();
                        // Further list commands will not be executed as long
                        // "stop_list" is active.

                        printf("\r- plotting turned off ");
                        stopped = 1;
                        i = -1;
                        eventOff = start = 1;
                        break;
                    default:
                        // Halt and terminate
                        // Remove a pending "stop_list" call before calling 
                        // "stop_execution"
                        disable_laser();
                        if(stopped) restart_list();
                        stop_execution();
                        printf("\r-- plotting terminated --\n");
                        eventOff = 1;
                        CarryOn = 0;
                }
            }
            if(eventOff || start) break;
        } 
    }
    // Flush the circular queue, on request.
    if(!eventOff)    PlotFlush();

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



//  PlotLine
//
//  Description:
//
//  Function "PlotLine" tries to transfer a line to the circular queue.
//  On success, the return is 1.
//  Otherwise, 0 is returned - call function "PlotLine" again till is returns 1.
//  Then "PlotLine" can be called with a next line.
//  When the line transfer is finished, call function "PlotFlush" to
//  execute the remaining lines in the list buffers.
//
//
//      Parameter   Meaning
//
//      destination The end location of a line
//
//      start       causes to mark a straight line from the current to the
//                  specified location, if "start" is set to 0.
//                  Otherwise, it causes to jump to the specified location
//                  without marking and parameter "start" will automatically
//                  be reset to 0.
//
//  NOTE
//      Use that function for the circular mode of the list buffers, only.

// PlotLine specific variable
unsigned short ListSpace = 0;

int PlotLine(const locus &destination, unsigned *start) {

    if(!ListSpace) {
        ListSpace = get_list_space();
        if(!ListSpace)
            return(0);
    }
    ListSpace--;


    if(*start) {
        jump_abs(destination.xval, destination.yval);
        *start = 0;
    }
    else
        mark_abs(destination.xval, destination.yval);

    return(1);
}


//  PlotFlush
//
//  Description:
//
//  The call of that function ensures to empty and to execute the remaining
//  contents of the circular queue.
//
//  NOTE
//      Use that function for the circular mode of the list buffers, only.

void PlotFlush(void) {
    while(!get_list_space()) ;
    set_end_of_list();
    ListSpace = 0;
}
