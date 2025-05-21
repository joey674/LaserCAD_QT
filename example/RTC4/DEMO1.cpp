//  File
//      DEMO1.cpp
//
//  Abstract
//      A console application for marking a square and a triangle
//      by using a CO2 laser
//
//  Author
//      Bernhard Schrems, SCANLAB AG
//
//  Comment
//      Besides demonstrating of how to initialize the RTC4 and how to
//      perform marking, this application also shows how to implicitly
//      link to the RTC4DLL.DLL. For accomplishing implicit linking -
//      also known as static load or load-time dynamic linking of a DLL,
//      the header file RTC4impl.H is included and for building the
//      executable, you must link with the (Visual C++) import library
//      RTC4DLL.LIB.
//      In case the operating system does not find the RTC4DLL.DLL on
//      program startup, it will respond with a corresponding error
//      message and it will terminate the program.
//
//  Necessary Sources
//      RTC4impl.H, RTC4DLL.LIB, MESSAGE.CPP
//      NOTE: RTC4DLL.LIB is a Visual C++ library.
//
//  Environment: Win32
//
//  Compiler
//      - tested with Visual C++ 5.0 and Visual C++ 6.0


// system header files
#include <stdio.h>
#include <conio.h>

// RTC4 header file
#include "rtc4impl.h"


struct polygon{
    short xval, yval;
};


#define R (20000)

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

#define POLYGONSIZE(figure) (sizeof(figure)/sizeof(polygon))


void ErrorMessage(short ErrorCode);
void draw(polygon *figure, unsigned size);


void main(void *, void *)
{
    short   ErrorCode;

	printf("Polygon Marking with a CO2 laser\n\n");


    // Initialize
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
    set_standby(100*8,      // half of the standby period in 1/8 microseconds
                8);         // pulse width in 1/8 microseconds


    // Timing, delay and speed preset
    set_start_list(1);
    set_laser_timing(100,   // half of the laser signal period
                    50,50,  // pulse widths of signals LASER1 and LASER2
                    0);     // time base; 0 corresponds to 1 microsecond.
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


    // Draw
    draw(square, POLYGONSIZE(square));
    draw(triangle, POLYGONSIZE(triangle));


    // Finish
    printf("Finished - press any key to terminate ");
    while(!kbhit()) ;
    (void)getch();
    printf("\n");
    return;
}



//  draw
//
//  Description:
//
//  Function "draw" transfers the specified figure to the RTC4 and invokes
//  the RTC4 to mark that figure, when the transfer is finished. "draw" waits
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
//  This function demonstrates the usage of a single list. Using list 1 only
//  means that you can utilize the space of both lists, which equals 8000 entries
//  totally.
//
//  NOTE
//      Make sure that "size" is smaller than 8000.

void draw(polygon *figure, unsigned size) {
    unsigned short  busy, position;
    unsigned        i;

    if(size) {
        do {
            get_status(&busy, &position);
        } while(busy);

        // Only, use list 1, which can hold up to 8000 entries
        set_start_list(1);
        jump_abs(figure->xval, figure->yval);
        for(i = 0, figure++; i < size - 1; i++, figure++)
            mark_abs(figure->xval, figure->yval);
        set_end_of_list();
        execute_list(1);
    }
}
