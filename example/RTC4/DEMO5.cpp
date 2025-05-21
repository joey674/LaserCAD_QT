//  File
//      DEMO5.cpp
//
//  Abstract
//      A console application for marking squares and triangles
//      by using a Nd:YAG laser
//
//  Author
//      Bernhard Schrems, SCANLAB AG
//
//  Features
//      - explicit linking to the RTC4DLL.DLL
//      - use of external control inputs
//      - use of structured programming
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


struct polygon{
    short xval, yval;
};

// Beam Dump Location
polygon BeamDump = {
    -32000, -32000
};


#define R (10000)

polygon square[] = {
    -R, -R,
    -R,  R,
     R,  R,
     R, -R,
    -R, -R
};

polygon triangle[] = {
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

#define POLYGONSIZE(figure) (sizeof(figure)/sizeof(polygon))


void ErrorMessage(short ErrorCode);
void ProgramDraw(polygon *figure, unsigned size, unsigned list);

void main(void *, void *)
{
    unsigned short  busy, position;
    short           ErrorCode;

    unsigned short  StartStop;
    unsigned        triangleToggle, startFlag, stopFlag;
    long            count;


	printf("Polygon Marking with a Nd:YAG laser\n\n");

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
    set_mark_speed(125.0);  // marking speed in bits per milliseconds
    set_end_of_list();
    execute_list(1);

    printf("Pump source warming up - please wait\r");
    do {
        get_status(&busy, &position);
    } while(busy);

    // Program list buffer 1 and buffer 2 with the triangle or the square,
    // respectively.
    ProgramDraw(triangle, POLYGONSIZE(triangle), 0);
    ProgramDraw(square, POLYGONSIZE(square), 1);

    printf("Activate /START or press any key to invoke polygon marking \n");

    triangleToggle = startFlag = 0;
    count = 0;
    stopFlag = 1;
    while(!kbhit()) {
        if(startFlag) {
            // Alternately select list buffer 1 or buffer 2, when the
            // execution of the previous figure is finished.
            get_status(&busy, &position);
            if(!busy) {
                if(triangleToggle) {
                    select_list(0);
                    triangleToggle = 0;
                }
                else {
                    select_list(1);
                    triangleToggle = 1;
                }
                startFlag = 0;
            }
        }
        else {
            // Interrogation of the External Control Inputs

            unsigned startActive, startActiveMessage;

            startActive = startActiveMessage = 0;
            do {
                // Get the state of the START and STOP signal
                StartStop = get_startstop_info();
                startActive = ~StartStop & 0x1000;
                StartStop &= 0xA;
                if(StartStop == 0x2) {
                    // There was a START request (the programmed figure
                    // is already called) and STOP is not activated
                    startFlag = 1;
                    printf("START request %d\n", ++count);
                    break;
                    // NOTE
                    // Make use of a bounce-free START signal, only.
                    // Otherwise, the bounces might invoke extra START
                    // requests.
                }
                if(StartStop == 0x8) {
                    // The STOP is activated. A current execution of the
                    // programmed figure might be stopped.
                    if(!stopFlag) printf("STOP\n");
                    stopFlag = 1;
                }
                else if(StartStop == 0xA) {
                    // There was a START request and the STOP is activated.
                    // A current execution of the programmed figure might
                    // be stopped.
                    if(stopFlag != 2) printf("START & STOP\n");
                    stopFlag = 2;
                }
                if(stopFlag && startActive) {
                    // Do not enable the START input as long the START and 
                    // the STOP are activated because a de-activation of
                    // the STOP signal might trigger a START, when the START
                    // input was enabled.
                    if(!startActiveMessage) {
                        printf("de-activate the START input to continue\n");
                        startActiveMessage = 1;
                    }
                }
            } while(StartStop || startActive);
            if(stopFlag) {
                // Here, before deciding to continue, your application could
                // analyse the reason why there was a STOP initiated.
                printf("ready to continue\n");
                // Enable the START input
                set_control_mode(1);
                stopFlag = 0;
            }
        }
    }
    (void)getch();

    if(startFlag) stop_execution();

    ProgramDraw(triangle_, POLYGONSIZE(triangle_), 0);
    execute_at_pointer(0);


    // Finish
    printf("\nFinished - press any key to terminate ");
    while(!kbhit()) ;
    (void)getch();
    printf("\n");
    stop_execution();
    // Activate the pump source standby
    write_da_1(0);
    // Close the RTC4.DLL
    RTC4close();
    return;
}



//  ProgramDraw
//
//  Description:
//
//  This function programs the specified list buffer with the specified figure.
//  That is, a subsequent call of "execute_at_pointer(ADR)" invokes the
//  execution of the programmed figure, where ADR has to be set to 0, if list
//  buffer 1 was selected or ADR has to be set to 4000, if list buffer 2 was
//  selected. In addition, an activated START signal (pin 8 of the Laser
//  Connector) invokes the execution of the programmed figure, if previously
//  the particular list buffer was selected by calling the corresponding
//  command select_list(). An activated STOP signal (pin 9 of the Laser
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
//      Make sure that "size" is smaller than 4000 - 1.

void ProgramDraw(polygon *figure, unsigned size, unsigned list) {
    unsigned short  busy, position;
    unsigned        i;

    do {
        get_status(&busy, &position);
    } while(busy);

    // Now, the commands that were in the list buffer are executed.
    // Therefore, the input pointer can trouble-freely be set.
    if(list) set_input_pointer(4000);
    else set_input_pointer(0);

    if(size) {
        jump_abs(figure->xval, figure->yval);
        for(i = 0, figure++; i < size - 1; i++, figure++)
            mark_abs(figure->xval, figure->yval);
    }
    else list_nop();

    set_end_of_list();
}
