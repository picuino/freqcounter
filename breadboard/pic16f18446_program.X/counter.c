/*
 * Frequency counter routines
 *
 * Author: Carlos Pardo
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License Version 3. See the file "COPYING" in the main directory
 * of this archive for more details.
 *
 */

#include <xc.h>
#include "config.h"
#include "peripheral.h"
#include "timers.h"
#include "math48.h"
#include "uart.h"
#include "lcd.h"
#include "eprom.h"
#include "command.h"
#include "counter.h"
#include "calibration.h"


/*
 * GLOBAL VARIABLES
 */
extern volatile uint48 timer0, timer1, timer3, timer5;
extern volatile unsigned char timers_readed;
extern unsigned char str_buf[];
extern unsigned int ctmu_constant;
extern calibration_t calibration;

uint48 buff_pulses_a[COUNTER_BUFFER_SIZE];
uint48 buff_time_a[COUNTER_BUFFER_SIZE];
uint48 buff_pulses_b[COUNTER_BUFFER_SIZE];
uint48 buff_time_b[COUNTER_BUFFER_SIZE];
uint48 frequency, period;
uint48 temp, time;
uint48 pulses_a, time_a;
uint48 pulses_b, time_b;
uint48 pulses_a_old, time_a_old;
uint48 pulses_b_old, time_b_old;
uint48 dpulses, dtime, dpulsesf, dtimef;
char buff_init, buff_end;
options_t options;
unsigned long millis;
unsigned char blink_lcd_state;
unsigned char counter_reset_inputs;
unsigned char counter_capturing_channel;
unsigned char counter_overrange_input_a, counter_overrange_input_b;


/*
 * Calculate frequency
 * input: dpulses and dtime as uint48 integer numbers
 *        options.calibration as long integer.
 * output: frequency as float48 float number
 */
void counter_calculate_frequency(void) {

   // Calculate pulses in floating point format
   dpulsesf = itof48(dpulses);

   // Calculate time in floating point format and change units to seconds
   if (options.ctmu_enable) {
      if (options.system_clk_mhz == 8) {
         ILOAD48(temp, 128 * _FCYCLES);
      } else {
         ILOAD48(temp, 128 * 5000000);
      }
   } else {
      if (options.system_clk_mhz == 8) {
         ILOAD48(temp, _FCYCLES);
      } else {
         ILOAD48(temp, 5000000);
      }
   }

   temp = itof48(temp);
   dtimef = itof48(dtime);
   dtimef = fdiv48(dtimef, temp);
   dtimef = fdiv48(dtimef, calibration_get());

   // Calculate frequency
   frequency = dpulsesf;
   frequency = fdiv48(frequency, dtimef);

   // Calculate period if pulses > 0
   if (dpulses.word[0] > 0 || dpulses.dword > 0) {
      ILOAD48(temp, 1UL);
      temp = itof48(temp);
      period = fdiv48(temp, frequency);
   }
}


/*
 * Calculate period of input A
 * Input:
 *    pulses_a, pulses_a_old,
 *    time_a, time_a_old
 *
 * Output:
 *    dpulses (difference of pulses in period)
 *    dtime   (difference of time in period in cycle units)
 */
void counter_period_a(void) {
   // calculate differencies
   dpulses = sub48(pulses_a, pulses_a_old);
   counter_unprescaler(options.prescaler_a);

   // Calculate time in cycles
   dtime = sub48(time_a, time_a_old);
}


/*
 * Calculate period of input B
 * Input:
 *    pulses_b, pulses_b_old,
 *    time_b, time_b_old
 *
 * Output:
 *    dpulses (difference of pulses in period)
 *    dtime   (difference of time in period in cycle units)
 */
void counter_period_b(void) {
   // calculate differencies
   dpulses = sub48(pulses_b, pulses_b_old);
   counter_unprescaler(options.prescaler_b);

   // Calculate time in cycles
   dtime = sub48(time_b, time_b_old);
}


/*
 * Capture pulses and time
 * Read CTMU for more precise time measure
 */
void counter_capture(void) {
   unsigned int ctmu;

   // discharge ctmu capacitor
   ctmu_discharge();

   // Inits capture
   timers_readed = 0;
   CLC3_RESET = 0;
   CLC3_DATA = 1;

   // Read timer1
   while (timers_readed == 0)
      cmd_loop();

   // Reset capture
   CLC3_RESET = 1;
   CLC3_DATA = 0;

   // Read CTMU capacitor with ADC
   ctmu = adc_read();

   // Compute time adjust
   ctmu *= ctmu_constant;
   ctmu >>= 8;

   if (options.ctmu_enable) {
      temp.byte[5] = time.byte[5];
      time.byte[5] = time.byte[4];
      time.byte[4] = time.byte[3];
      time.byte[3] = time.byte[2];
      time.byte[2] = time.byte[1];
      time.byte[1] = time.byte[0];
      time.byte[0] = 0x00;

      // Shift right (Divide by 2)
      time = sr48(time);
      time.b47 = temp.b40;

      // copy ctmu to temp
      temp.dword = 0;
      temp.word[0] = ctmu;

      // time = time - ctmu
      time = sub48(time, temp);
   }
}


/*
 * wait one measuring period since the last wait.
 */
void counter_wait_period(void) {
   // Wait one measuring period
   if (options.fast_measure) {
      millis += 100;
      if ((long) (millis - milliseconds()) < 0)
         millis = milliseconds() + 50;
   } else {
      millis += 1000;
      if ((long) (millis - milliseconds()) < 0)
         millis = milliseconds() + 950;
   }
   while ((long) (millis - milliseconds()) > 0)
      cmd_loop();
}


/*
 * Reset options
 */
void counter_options_init(void) {
   options.autocalibrate = 0;
   options.ctmu_enable = 1;
   options.input_a = 1;
   options.input_b = 0;
   options.input_zcd = 0;
   options.fast_measure = 0;

   options.print_pulses = 0;
   options.print_time = 0;
   options.print_long_frequency = 0;
   options.print_period = 0;
   options.print_phase = 0;
   options.print_lcd = 1;

   // Read calibration (in Parts Per Billion)
   calibration.calibration_8mhz = eprom_read32(SAF_ADDRESS);
   calibration.calibration_5mhz = eprom_read32(SAF_ADDRESS + 4);
}


/*
 * Inits frequency counter
 */
void counter_init(void) {
   // Inits capture modules
   ccp1_init();
   ccp3_init();
   ccp2_init();

   // Reset options
   counter_options_init();
   clc_init(); // conect Input A or Input ZCD (Must be executed before reset counters)

   counter_reset();
}


/*
 * Reset timers, buffer and time counter
 */
void counter_reset(void) {
   // Reset timers
   timer1_init();
   timer3_init();
   timer5_init();

   // Wait for Input A pulse and capture
   ctmu_calibrate();
   counter_capture_channel_a();
   counter_capture_channel_b();

   // Inits buffer
   buff_init = 0;
   buff_end = 0;
   buff_pulses_a[0] = pulses_a;
   buff_pulses_b[0] = pulses_b;
   buff_time_a[0] = time_a;
   buff_time_b[0] = time_b;

   // Inits time counter between samples
   millis = milliseconds();
}


void counter_unprescaler(char prescaler) {
   // Change pulses depending on prescaler
   if (prescaler >= 2) {
      dpulses = sl48(dpulses);
   }
   if (prescaler >= 4) {
      dpulses = sl48(dpulses);
   }
   if (prescaler == 8) {
      dpulses = sl48(dpulses);
   }
}


/*
 * Determine prescaler and detects overrange on Input A
 */
void counter_prescaler_channel_a(void) {
   char intcon;

   // Configure Timer2
   T2CON = 0;
   T2HLT = 0;
   T2PR = 0xFF;
   T2CLKCON = 0; // 0 = T2CKIPPS
   T2CONbits.CKPS = 5; // 0 = 1:32 prescaler

   // Measure frequency overrange in channel A
   pps_unlock();
   T2INPPS = INPUT_A_PPS;
   pps_lock();
   T2TMR = 0;

   intcon = INTCON;
   INTCONbits.GIE = 0;
   T2CONbits.ON = 1;
   __delay_us(100);
   T2CONbits.ON = 0;
   INTCON = intcon;

   // Select prescaler
   if (T2TMR < 2 && options.prescaler_a == 2) {
      clc_prescaler_a_off();
      uart_fputs("# Prescaler A=\t1\n");
      counter_reset();
   }
   if (T2TMR > 10 && options.prescaler_a == 1) {
      clc_prescaler_a_on();
      uart_fputs("# Prescaler A=\t2\n");
      counter_reset();
   }

   // Detects overrange
   if (T2TMR >= 48) {
      counter_overrange_input_a = 1;
      uart_fputs("# Over range at input A\n");
   } else {
      counter_overrange_input_a = 0;
   }
}


/*
 * Determine prescaler and detects overrange on Input B
 */
void counter_prescaler_channel_b(void) {
   char intcon;

   // Configure Timer2
   T2CON = 0;
   T2HLT = 0;
   T2PR = 0xFF;
   T2CLKCON = 0; // 0 = T2CKIPPS
   T2CONbits.CKPS = 5; // 0 = 1:32 prescaler

   // Measure frequency overrange in channel A
   pps_unlock();
   T2INPPS = INPUT_B_PPS;
   pps_lock();
   T2TMR = 0;

   intcon = INTCON;
   INTCONbits.GIE = 0;
   T2CONbits.ON = 1;
   __delay_us(100);
   T2CONbits.ON = 0;
   INTCON = intcon;

   // Select prescaler
   if (T2TMR < 2 && options.prescaler_b == 2) {
      clc_prescaler_b_off();
      uart_fputs("# Prescaler B=\t1\n");
      counter_reset();
   }
   if (T2TMR > 10 && options.prescaler_b == 1) {
      clc_prescaler_b_on();
      uart_fputs("# Prescaler B=\t2\n");
      counter_reset();
   }

   // Detects overrange
   if (T2TMR >= 48) {
      counter_overrange_input_b = 1;
      uart_fputs("# Over range at input B\n");
   } else {
      counter_overrange_input_b = 0;
   }
}


/*
 * Save Old values
 */
void counter_save_old_values(void) {
   // save old values
   pulses_a_old = pulses_a;
   time_a_old = time_a;

   // save old values
   pulses_b_old = pulses_b;
   time_b_old = time_b;

   // Buffers
   counter_buffer_inc();
   buff_pulses_a[buff_end] = pulses_a;
   buff_time_a[buff_end] = time_a;
   buff_pulses_b[buff_end] = pulses_b;
   buff_time_b[buff_end] = time_b;
}


/*
 * Measure frequency in channel A
 */
void counter_capture_channel_a(void) {

   if (options.input_a == 0)
      return;

   // Wait for input pulse and capture
   clc_capture_channel_a();
   counter_capturing_channel = INPUT_A;
   counter_capture();
   time_a = time;
}


/*
 * Measure frequency in channel B
 */
void counter_capture_channel_b(void) {

   if (options.input_b == 0)
      return;

   // Wait for input pulse and capture
   clc_capture_channel_b();
   counter_capturing_channel = INPUT_B;
   counter_capture();
   time_b = time;
}


/*
 * Print frequency of channel A
 * Input: dpulses, dtime (pulses and time of last period)
 * Output: pulses, time in short and long period via UART and LCD
 */
void counter_print_channel_a(void) {
   char resolution;

   if (options.input_a == 0)
      return;

   // Calculate decimals of resolution
   resolution = 8;
   if (options.fast_measure) {
      resolution--;
   }
   if (options.ctmu_enable) {
      resolution++;
   }

   // Calculate pulses, time and frequency
   counter_period_a();
   counter_calculate_frequency();

   // Print pulses and time
   if (options.print_pulses) {
      uart_fputs("Pulses A=\t");
      print_u48(dpulses);
      uart_fputc('\t');
   }
   if (options.print_time) {
      uart_fputs("Time A=\t");
      print_f48(dtimef, resolution);
      uart_fputc('\t');
   }
   if (options.print_period) {
      uart_fputs("Period A=\t");
      print_f48(period, resolution);
   } else {
      uart_fputs("Freq. A=\t");
      print_f48(frequency, resolution);
   }
   uart_fputc('\t');

   // Print frequency on LCD
   if (options.print_lcd) {
      lcd_goto(0);
      print_lcd_f48(frequency, resolution);
      lcd_puts("Hz   ");
   }

   // Calculate long term frequency
   dpulses = buff_pulses_a[buff_init];
   dpulses = sub48(buff_pulses_a[buff_end], dpulses);
   counter_unprescaler(options.prescaler_a);
   dtime = buff_time_a[buff_init];
   dtime = sub48(buff_time_a[buff_end], dtime);
   counter_calculate_frequency();

   // Print long term frequency
   if (options.print_long_frequency) {
      uart_fputs("Freq. A=\t");
      print_f48(frequency, resolution + 1);
      uart_fputc('\t');
   }

   // Print frequency on LCD
   if (options.print_lcd) {
      lcd_goto(LCD_GOTO_LINE2);
      if (counter_overrange_input_a) {
         lcd_puts("Over range!");
      } else {
         print_lcd_f48(frequency, resolution + 1);
         lcd_puts("Hz   ");
      }
   }

}


/*
 * Print frequency of channel B
 * Input: dpulses, dtime (pulses and time of last period)
 * Output: pulses, time in short and long period via UART and LCD
 */
void counter_print_channel_b(void) {
   char resolution;

   if (options.input_b == 0)
      return;

   // Calculate decimals of resolution
   resolution = 8;
   if (options.fast_measure) {
      resolution--;
   }
   if (options.ctmu_enable) {
      resolution++;
   }

   // Calculate pulses, time and frequency
   counter_period_b();
   counter_calculate_frequency();

   // Print pulses, time and frequency
   if (options.print_pulses) {
      uart_fputs("Pulses B=\t");
      print_u48(dpulses);
      uart_fputc('\t');
   }
   if (options.print_time) {
      uart_fputs("Time B=\t");
      print_f48(dtimef, resolution);
      uart_fputc('\t');
   }
   if (options.print_period) {
      uart_fputs("Period B=\t");
      print_f48(period, resolution);
   } else {
      uart_fputs("Freq. B=\t");
      print_f48(frequency, resolution);
   }
   uart_fputc('\t');

   // Calculate long term frequency
   dpulses = buff_pulses_b[buff_init];
   dpulses = sub48(buff_pulses_b[buff_end], dpulses);
   counter_unprescaler(options.prescaler_b);
   dtime = buff_time_b[buff_init];
   dtime = sub48(buff_time_b[buff_end], dtime);
   counter_calculate_frequency();

   // Print long term frequency
   if (options.print_long_frequency) {
      uart_fputs("Freq. B=\t");
      print_f48(frequency, resolution + 1);
      uart_fputc('\t');
   }

   if (options.input_a && options.print_phase) {
      dtime = sub48(time_b, time_a);
      counter_calculate_frequency();
      uart_fputs("Time B-A=\t");
      print_f48(dtimef, resolution);
   }
}


/*
 * Print end of line
 */
void counter_print_end(void) {
   uart_fputs("\n");
   counter_blink_lcd();
}


/*
 * Blinks LCD every measurement of frequency
 * showing that input signal is active.
 */
void counter_blink_lcd(void) {
   lcd_goto(15);
   if (blink_lcd_state == 0) {
      lcd_puts("*");
      blink_lcd_state = 1;
   } else {
      lcd_puts(" ");
      blink_lcd_state = 0;
   }
}


/*
 * Increment buffer pointers
 */
void counter_buffer_inc(void) {
   buff_end++;
   if (buff_end == COUNTER_BUFFER_SIZE)
      buff_end = 0;
   if (buff_init == buff_end)
      buff_init++;
   if (buff_init == COUNTER_BUFFER_SIZE)
      buff_init = 0;
}
