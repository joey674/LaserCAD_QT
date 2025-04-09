//  File
//      Class1.cs
//
//  Abstract
//      A console application for plotting Archimedean spirals
//      by means of a Nd:YAG laser.
//
using System;
using System.Runtime.InteropServices;
using RTC5Import;

namespace DEMO3
{
    /// <summary>
    /// Summary description for Class1.
    /// </summary>
    class Class1
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            try
            {
                Console.WriteLine("Archimedean Spirals\n\n");

                uint ErrorCode;
                ErrorCode = RTC5Wrap.init_rtc5_dll();
                if(ErrorCode != 0U && ErrorCode != 2U) 
                {
                    Console.WriteLine(
                      "Error happened during RTC5's DLL initialization.\n\n");
                    Console.Read();
                    return;
                }
                RTC5Wrap.set_rtc4_mode();
                if(RTC5Wrap.select_rtc(1U) != 1U)
                {
                    Console.WriteLine(
                        "Error: Failed to select the 1st RTC5.\n\n");
                    Console.Read();
                    return;
                }
                //
                ErrorCode = RTC5Wrap.load_correction_file(
                    "D2_1to1.ct5",
                    1U,         // number
                    2U);        // dimension
                if(ErrorCode != 0) 
                {
                    Console.WriteLine("Error: Correction file loading.\n\n");
                    Console.Read();
                    return;
                }
                ErrorCode = RTC5Wrap.load_program_file(null);
                if (ErrorCode != 0) 
                {
                    Console.WriteLine("Program file loading error: {0:D}\n\n",
                        ErrorCode);
                    Console.Read();
                    return;
                }
                //
                RTC5Wrap.config_list(4000U, 4000U);
                RTC5Wrap.set_laser_mode(1U);      // YAG mode 1 selected
                RTC5Wrap.set_laser_control(0U);

                // Turn on the optical pump source and wait for 2 seconds.
                // (The following assumes that signal ANALOG OUT1 of the
                // laser connector controls the pump source.)
                RTC5Wrap.write_da_1(640U);

                // Timing, delay and speed preset.
                // Transmit the following list commands to the list buffer.
                RTC5Wrap.set_start_list(1U);
                // Wait for 1 seconds
                RTC5Wrap.long_delay(100000U);
                RTC5Wrap.set_laser_pulses(
                    40U,    // half of the laser signal period.
                    400U);  // pulse widths of signal LASER1.
                RTC5Wrap.set_scanner_delays(
                    25U,    // jump delay, in 10 microseconds.
                    10U,    // mark delay, in 10 microseconds.
                    5U);    // polygon delay, in 10 microseconds.
                RTC5Wrap.set_laser_delays(
                    100,    // laser on delay, in microseconds.
                    100);   // laser off delay, in microseconds.
                // jump speed in bits per milliseconds.
                RTC5Wrap.set_jump_speed(1000.0);
                // marking speed in bits per milliseconds.
                RTC5Wrap.set_mark_speed(250.0);
                RTC5Wrap.set_end_of_list();
                RTC5Wrap.execute_list(1U);

                Console.WriteLine("Pump source warming up - please wait.\r");
                uint Busy, Position;
                do 
                {
                    RTC5Wrap.get_status(out Busy, out Position);
                } while(Busy != 0U);

                Console.WriteLine("Plotting started.");


                const int cycles = 10;

                const double turns = 5.0;
                const double Period = 512.0;
                const double Omega = 2.0*3.141592/Period;
                const double increment = 10000.0/turns/Period;
                const int limit = (int)(Period*turns);

                double span = increment;
                uint list = 2U;
                uint ListLevel = 0U;
                bool ListStart = true;
                for(int i = 0,cycle = 0;cycle < cycles; i++,span += increment)
                {
                    if(i == limit) 
                    {
                        i = 0;
                        span = increment;
                        cycle++;
                    }

                    int x, y;
                    x = (short)(span*Math.Sin(Omega*(double)i));
                    y = (short)(span*Math.Cos(Omega*(double)i));

                    bool wait;
                    do 
                    {
                        wait = false;
                        RTC5Wrap.get_status(out Busy, out Position);
                        if(Busy != 0U) 
                        {
                            if((list & 0x1U) == 0x0U) 
                            {
                                if(Position >= 4000U) 
                                {
                                    wait = true;
                                }
                            }
                            else 
                            {
                                if(Position < 4000U) 
                                {
                                    wait = true;
                                }
                            }
                        }
                    } while(wait);

                    if(ListStart) 
                    {
                        // Open the list at the beginning.
                        RTC5Wrap.set_start_list(list);
                        ListLevel = 0U;
                        ListLevel++;
                        // Start to capture the X/Y-axis output.
                        RTC5Wrap.set_trigger(10U, 7U, 8U);
                        ListStart = false;
                    }

                    ListLevel++;
                    RTC5Wrap.mark_abs(x, y);

                    if(ListLevel < 4000U - 1U)    continue;

                    RTC5Wrap.set_end_of_list();
                    ListStart = true;

                    // Execute.
                    // Notice that execute_list was already called.
                    RTC5Wrap.auto_change();

                    list++;
                }

                // Terminate.
                RTC5Wrap.set_trigger(0U, 7U, 8U);
                RTC5Wrap.set_end_of_list();
                RTC5Wrap.auto_change();


                // Get the captured X/Y-axis output.
                RTC5Wrap.measurement_status(out Busy, out Position);
                int[] WaveArray;
                const uint Width = 10U;
                if(Position >= Width) 
                {
                    WaveArray = new int[Width];
                    RTC5Wrap.get_waveform(1U, Width, WaveArray);

                    Console.WriteLine("\nSome captured X-axis output values:");
                    for(uint o = 0U; o < Width; o++) 
                    {
                        Console.WriteLine("\t{0}", WaveArray[o]);
                    }
                }

                Console.WriteLine("\nEnter any character to terminate. ");
                Console.Read();
            }
            catch(Exception e) 
            {
                Console.WriteLine("Exception caught: \n{0}", e);
                Console.Read();
            }
        }
    }
}
