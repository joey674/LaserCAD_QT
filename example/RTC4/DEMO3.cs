//  File: DEMO3.cs
//----------------------------------------------------------------------------
//  Copyright (c) 2015 by SCANLAB AG.                     All rights reserved.
//----------------------------------------------------------------------------
//
//
//  Abstract
//      A console application for continuously plotting Archimedean spirals
//      by means of a Nd:YAG laser
//
//  Author
//      Bernhard Schrems, SCANLAB AG
//
//  Features
//      - explicit linking to the RTC4DLL.DLL or RTC4DLLx64.DLL
//      - use of both list buffers for continuous data transfer
//      - exception handling
//
//  Comment
//      This routine demonstrates how to use both list buffers for a
//      continuous data transfer by applying the command "auto_change"
//      on a loaded list buffer. Methods to halt and to resume the data
//      transfer are also shown.
//      Notice that the spirals are only exposing as Archimedean spirals,
//      if there is a F-Theta-lens in use.
//
//  Necessary Sources
//      RTC4Wrap.cs
//
//  NOTE
//      THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//      KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//      IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//      PURPOSE.
//
//----------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using RTC4Import;


namespace Demo
{
    // End Locus of the vector to plot
    struct locus
    {
        public short xval, yval;
        public locus(short x, short y)
        {
            xval = x;
            yval = y;
        }
    }

    class RTC4Exception : ApplicationException
    {
        public RTC4Exception(string ErrMsg) : base(ErrMsg) {}
    }

    class Plotter : RTC4Wrap
    {
        // Desired Nd:YAG Laser Timing for YAG mode 1
        const uint LASER = 10000;           // Laser pulse frequency in Hz.
        const uint PULSE = 5;               // Pulse width in microseconds.
        const uint PULSE1ST = 2;            // Amount of pulses the first
                                            // pulse killer FPK
                                            // should be active.
        // Frequency Base
        const uint MEGA = (1000 * 1000);
        const uint FREQBASE = (8 * MEGA);   // Corresponding to a time base
                                            // of 1/8 microseconds.
        // Derived Laser Timing in microseconds
        const uint FPK = ((100 * PULSE1ST + 50) * FREQBASE / 100 / LASER);
        const uint HALF_PERIOD = (FREQBASE / LASER / 2);
        const uint PULSE_WIDTH = (PULSE * FREQBASE / MEGA);

        uint list = 1;
        uint ListLevel = 0;
        bool ListStart = false;
        bool FirstTime = false;
        bool Suspended = false;

        public Plotter()
        {
            // Initialize the RTC
            short ErrorCode = load_correction_file(
                                    "cor_1to1.ctb",
                                    1,          // table; #1 is used by default
                                    1.0, 1.0,   // scale factor
                                    0.0,        // rotation in degrees, counterclockwise
                                    0.0, 0.0);  // offset in bits
            if (ErrorCode != 0)
            {
                string Msg = String.Format("Correction file loading error: {0}\n\n", ErrorCode);
                throw new RTC4Exception(Msg);
            }
            ErrorCode = load_program_file("RTC4d2.hex");
            if (ErrorCode != 0)
            {
                string Msg = String.Format("Program file loading error: {0}\n\n", ErrorCode);
                throw new RTC4Exception(Msg);
            }

            set_laser_mode(1);      // YAG mode 1 selected
            set_firstpulse_killer((ushort)FPK);

            // Activate a home jump and specify the beam dump 
            locus BeamDump = new locus(-32000, -32000);
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
                    (ushort)HALF_PERIOD,    // half of the laser signal period
                    (ushort)PULSE_WIDTH, 2, // pulse widths of signal LASER1
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

            // Wait on "Pump source warming up" is done.
            ushort busy, position;
            do
            {
                get_status(out busy, out position);
            } while (busy != 0);
        }

        public bool Plot(locus destination, ref bool StartLocus, ref bool PlotLaunch)
        {
            ushort busy, position;

            if (PlotLaunch)
            {
                do
                {
                    get_status(out busy, out position);
                } while (busy != 0);
                list = 1;
                ListStart = true;
                ListLevel = 0;
                FirstTime = true;
                PlotLaunch = false;
            }
            else
            {
                // On a list swap, check whether the list "list" is free to be loaded
                if (ListStart)
                {
                    get_status(out busy, out position);
                    if (busy != 0)
                        if (list == 2)
                        {
                            if (position >= 4000) return (true);    // list 2 is busy
                        }
                        else
                        {
                            if (position < 4000) return (true);     // list 1 is busy
                        }
                }
            }

            // Open the list at the beginning
            if (ListStart) set_start_list((ushort)list);
            ListStart = false;
            ListLevel++;

            if (StartLocus)
            {
                jump_abs(destination.xval, destination.yval);
                StartLocus = false;
            }
            else
                mark_abs(destination.xval, destination.yval);

            if (ListLevel < 4000 - 1) return (false);   // Done

            set_end_of_list();
            ListStart = true;

            // Only, apply execute_list for the very first time.
            // Otherwise, use auto_change.
            if (FirstTime)
            {
                execute_list(1);
                FirstTime = false;
            }
            else auto_change();

            list = (list == 1) ? (uint)2 : (uint)1;
            ListLevel = 0;

            return (false);                             // Done
        }
        public void Resume()
        {
            if (Suspended)
            {
                restart_list();
                Suspended = false;
            }
            enable_laser();
        }
        public void Suspend()
        {
            stop_list();
            // Subsequent list commands will not be executed
            // as long "stop_list" is active
            Suspended = true;
        }
        public bool IsSuspended()
        {
            return(Suspended);
        }
        public void Flush()
        {
            if (ListStart) return;
            else
            {
                set_end_of_list();
                if (FirstTime)
                {
                    execute_list(1);
                }
                else
                {
                    auto_change();
                }
            }
        }
        public void Stop()
        {
            disable_laser();

            // Remove a pending "stop_list" call before calling 
            // "stop_execution"
            if (Suspended) restart_list();

            stop_execution();

            // Finish
            // Activate the pump source standby
            write_da_1(0);
        }
    }

    class DEMO3 
    {
        static void Main(string[] args)
        {
            // Spiral Parameters
            const double AMPLITUDE = 10000.0;
            const double PERIOD    = 512.0;      // amount of vectors per turn
            const double OMEGA = (2 * Math.PI / PERIOD);

            Console.Title = "RTC®4 Demo Program 3";
            Console.WriteLine("Archimedean spirals\n\n");

            try
            {
                // Initialize the scan-system and the laser.
                Console.WriteLine("Pump source warming up - please wait ...\n");
                Plotter plotter = new Plotter();

                // Plotting Routine
                Console.WriteLine("Press 1, 2, ... or 9 to set the number of revolutions.");
                Console.WriteLine("Press S to suspend or R to resume plotting.");
                Console.WriteLine("Press O to turn off or R to restart plotting.");
                Console.WriteLine("Press F to flush the list buffers and to terminate.");
                Console.WriteLine("Any other key will halt plotting and terminate.\n");

                double turns = 5.0;
                Console.WriteLine("--- revolutions: {0} ---", (int)turns);
                double increment = AMPLITUDE / turns / PERIOD;
                int limit = (int)PERIOD * (int)turns;

                bool IsEventOff = false, flush = false;
                bool StartLocus = true, PlotLaunch = true;
                bool status = false;
                int i = 0;

                locus point = new locus();
                double span = increment;
                for (bool CarryOn = true; CarryOn; i++, IsEventOff = false, span += increment)
                {
                    if (i == limit)
                    {
                        i = 0;
                        span = increment;
                        StartLocus = true;
                    }

                    point.xval = (short)(span * Math.Sin(OMEGA * (double)i));
                    point.yval = (short)(span * Math.Cos(OMEGA * (double)i));

                    while (IsEventOff ? status : plotter.Plot(point, ref StartLocus, ref PlotLaunch))
                    {
                        if (Console.KeyAvailable)
                        {
                            ConsoleKeyInfo ch = Console.ReadKey(true);
                            char LowerCaseKey = char.ToLower(ch.KeyChar);
                            switch (LowerCaseKey)
                            {
                                case '1':
                                    turns = 1.0;
                                    goto TurnsSetup;
                                case '2':
                                    turns = 2.0;
                                    goto TurnsSetup;
                                case '3':
                                    turns = 3.0;
                                    goto TurnsSetup;
                                case '4':
                                    turns = 4.0;
                                    goto TurnsSetup;
                                case '5':
                                    turns = 5.0;
                                    goto TurnsSetup;
                                case '6':
                                    turns = 6.0;
                                    goto TurnsSetup;
                                case '7':
                                    turns = 7.0;
                                    goto TurnsSetup;
                                case '8':
                                    turns = 8.0;
                                    goto TurnsSetup;
                                case '9':
                                    turns = 9.0;
                                TurnsSetup:
                                    // Turns setup requested
                                    if (!IsEventOff && !plotter.IsSuspended())
                                        Console.WriteLine("--- revolutions: {0} ---", (int)turns);
                                    // NOTE
                                    //  Modifying the number of turns might not immediately
                                    //  take effect, because both list buffers can still
                                    //  hold vectors from a previous setting.
                                    increment = AMPLITUDE / turns / PERIOD;
                                    span = 0;
                                    limit = (int)PERIOD * (int)turns;
                                    IsEventOff = true;
                                    StartLocus = true;
                                    i = -1;
                                    break;
                                case 'f':
                                    // Buffer flushing requested
                                    if (!IsEventOff)
                                    {
                                        plotter.Resume();
                                        Console.WriteLine("- flushing the queue -");
                                        flush = true;
                                        IsEventOff = true;
                                        status = false;
                                        CarryOn = false;
                                    }
                                    break;
                                case 's':
                                    // Sudden suspending requested
                                    if (!IsEventOff)
                                    {
                                        plotter.Suspend();
                                        Console.WriteLine("- plotting suspended -");
                                    }
                                    break;
                                case 'r':
                                    // Resume to plot
                                    if (IsEventOff)
                                    {
                                        status = false;
                                        span = 0;
                                        i = -1;
                                        PlotLaunch = true;
                                        StartLocus = true;
                                    }
                                    else
                                    {
                                        plotter.Resume();
                                    }
                                    Console.WriteLine("--- revolutions: {0} ---", (int)turns);
                                    break;
                                case 'o':
                                    // Stop request
                                    plotter.Stop();
                                    Console.WriteLine("- plotting turned off ");

                                    // Do not transfer list commands as long
                                    // "stop_execution" is active
                                    IsEventOff = true;
                                    status = true;
                                    break;
                                default:
                                    plotter.Stop();
                                    Console.WriteLine("-- plotting terminated --\n");
                                    status = false;
                                    CarryOn = false;
                                    IsEventOff = true;
                                    break;
                            }
                        }
                    }
                }

                // Flush the list buffers, on request.
                if (flush) plotter.Flush();
            }
            catch (TypeInitializationException x)
            {
                Console.WriteLine("\n" + x.Message.ToString());
                Console.WriteLine("\t\"" + x.InnerException.Message.ToString() + "\"");
            }
            catch (ApplicationException x)
            {
                Console.WriteLine("Exception: " + x.Message.ToString());
            }
            catch (SystemException x)
            {
                Console.WriteLine("System Exception: " + x.Message.ToString());
            }
            Console.WriteLine("\nFinished - press any key to exit ");
            while (!Console.KeyAvailable) ;
            Console.ReadKey();
       }
    }
}
