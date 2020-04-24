/*
 * Calibration routines for frequency counter
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
#include "calibration.h"
#include "math48.h"
#include "counter.h"
#include "uart.h"
#include "peripheral.h"
#include "command.h"
#include "eprom.h"


/*
 * Variables
 */
extern uint48 dpulses, dtime;
extern options_t options;
extern unsigned char counter_reset_inputs;
calibration_t calibration;

unsigned int ctmu_constant;


/*
 * Inits calibration
 */
void calibrate_init(void) {
   calibration_eprom_read();   
}


/*
 * Read calibration from EPROM
 */
void calibration_eprom_read(void) {
   calibration.calibration_8mhz = eprom_read32(SAF_ADDRESS);
   calibration.calibration_5mhz = eprom_read32(SAF_ADDRESS + 8);
}


/*
 * Write calibration to EPROM
 */
void calibration_eprom_write(void) {
   eprom_delete(SAF_ADDRESS);
   eprom_write32(SAF_ADDRESS, calibration.calibration_8mhz);
   eprom_write32(SAF_ADDRESS + 8, calibration.calibration_5mhz);
   eprom_flush();
}


/*
 * Measure system main clock speed in MHz
 */
void system_speed(void) {
   char intcon;

   T2CON = 0;
   T2HLT = 0;
   T2TMR = 0;
   T2PR = 0xFF;
   T2CLKCON = 5; // 5 = MFINTOSC(500 kHz)
   T2CONbits.CKPS = 0; // 0 = 1:1 prescaler

   intcon = INTCON;
   INTCONbits.GIE = 0;
   T2CONbits.ON = 1;
   __delay_us(100);   // 50 tics of MFINTOSC @ 8MHz
   T2CONbits.ON = 0;
   INTCON = intcon;
   
   if (T2TMR < (50+80)/2 && options.system_clk_mhz == 5) {
      options.system_clk_mhz = 8;
      counter_reset_inputs = 1;
   }
   if (T2TMR > (50+80)/2 && options.system_clk_mhz == 8) {
      options.system_clk_mhz = 5;
      counter_reset_inputs = 1;
   }
   if (counter_reset_inputs) {
      uart_init_speed();
   }
}


/*
 * Compute float number 1+ppb (parts per billion)
 * Example:
 *    if ppb = 1234, return float number 1.000001234
 */
uint48 ppb_f48(long ppb) {
   uint48 adjust, billion;

   adjust.word[0] = ppb;
   adjust.word[1] = ppb >> 16;
   if (adjust.b31 == 1)
      adjust.word[2] = 0xffff;
   else
      adjust.word[2] = 0;

   ILOAD48(billion, 1000000000UL)
   adjust = add48(adjust, billion);
   billion = itof48(billion);
   adjust = itof48(adjust);
   adjust = fdiv48(adjust, billion);
   return adjust;
}


/*
 * Autocalibrate frequency counter with a 1PPS input signal
 * Inputs: dtime, dpulses, freq from long term frequency
 */
void counter_1pps_autocalibrate(void) {
   extern uint48 frequency;
   long temp;
   uint48 billion;

   if (options.autocalibrate == 0)
      return;

   // Test if input signal is 1 Hz +-0.3%
   if (dpulses.dword != 0) return;
   temp = dtime.dword;
   if (options.ctmu_enable) {
      temp >>= 7;
   }
   if (dpulses.word[0] == 10) {
      if (temp > (_FCYCLES * (COUNTER_BUFFER_SIZE - 1) * 1.01 / 65536)) return;
      if (temp < (_FCYCLES * (COUNTER_BUFFER_SIZE - 1) * 0.99 / 65536)) return;
   } else if (dpulses.word[0] == 20) {
      if (temp > (_FCYCLES * 2 * (COUNTER_BUFFER_SIZE - 1) * 1.01 / 65536)) return;
      if (temp < (_FCYCLES * 2 * (COUNTER_BUFFER_SIZE - 1) * 0.99 / 65536)) return;
   } else return;

   // Obtain 1e9 number and calibrate
   ILOAD48(billion, 1000000000L);
   billion = itof48(billion);
   billion = fmul48(frequency, billion);
   counter_autocalibrate(billion);
}


/*
 * Autocalibrate frequency counter with a 10MHZ input signal
 * Inputs: dtime, dpulses, freq from long term frequency
 */
void counter_10mhz_autocalibrate(void) {
   extern uint48 frequency;
   uint48 billion;

   if (options.autocalibrate == 0)
      return;

   // Test if input signal is 10MHz Hz +-1%
   if (dpulses.dword > 10000000 * (COUNTER_BUFFER_SIZE - 1) * 1.01 / 65536) return;
   if (dpulses.dword < 10000000 * (COUNTER_BUFFER_SIZE - 1) * 0.99 / 65536) return;

   // Obtain 1e9 number and calibrate
   ILOAD48(billion, 100L);
   billion = itof48(billion);
   billion = fmul48(frequency, billion);
   counter_autocalibrate(billion);
}


/*
 * Calibrate frequency counter with a base frequency of 1000 000 000
 */
void counter_autocalibrate(uint48 billion) {
   long dfrequency;

   billion = ftoi48(billion);
   dfrequency = billion.word[0] + ((long) billion.word[1] << 16);
   dfrequency -= 1000000000;
   if (options.system_clk_mhz == 8)
      calibration.calibration_8mhz -= dfrequency;
   else
      calibration.calibration_5mhz -= dfrequency;
   uart_fputs(">New calibration=\t");
   print_long(cmd_get_calibration());
   uart_fputs("\n");
}


/*
 * Calculate calibration needed to compensate errors
 */
uint48 calibration_get(void) {
   uint48 cal;
   // If system frequency == 5MHz, there is no calibration
   if (options.system_clk_mhz == 8) {
      cal = ppb_f48(calibration.calibration_8mhz);
   } else {
      cal = ppb_f48(calibration.calibration_5mhz);
   }

   // Calculate calibration
   return cal;
}


/*
 * Return ADC read of CTMU with pulse of 1 Cycle
 */
void ctmu_calibrate(void) {
   unsigned int level;
   char i;

   // PPS direct control of ctmu pulses
   pps_unlock();
   DISP_LAT = 0;
   DISP_PPS = 0x00;
   pps_lock();

   // Pulses on RB4
   level = 0;
   for (i = 0; i < 4; i++) {
      ctmu_discharge();
      DISP_LAT = 1;
      DISP_LAT = 0;
      level += adc_read();
   }
   level += 2;
   level >>= 2;

   // Reasign PPS
   pps_unlock();
   DISP_PPS = 0x04; // 4 = CLC4OUT
   pps_lock();

   // Calculate CTMU constant
   ctmu_constant = (unsigned int) 128 * 256 / level;
}


/*
 * Discharge CTMU capacitor
 */
void ctmu_discharge(void) {
   // Discharge CTMU capacitor
   DTIME_ANS = 0;
   DTIME_TRIS = 0;
   DTIME_LAT = 0;
   __delay_us(10);
   DTIME_TRIS = 1;
   DTIME_ANS = 1;
}