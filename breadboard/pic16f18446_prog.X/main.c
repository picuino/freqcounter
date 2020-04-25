/*
 * Frequency counter with PIC16F18446
 *
 * Author: Carlos Pardo
 *
 * Inputs:
 *    RC5 (Pin_5) Input A
 *    RC4 (Pin_6) Input B
 *
 * UART:
 *   TX on RA2 (Pin_17)
 *   RX on RC0 (Pin_16)
 *
 *
 * TO-DO:
 *  - Refactor and clean code
 *
 * License:
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
#include "counter.h"
#include "lcd.h"
#include "eprom.h"
#include "command.h"
#include "calibration.h"

extern options_t options;


/*
 *  INTERRUPT SERVICE ROUTINE
 */
void __interrupt() isr(void) {

   // Interrupt service routine of timers
   timers_isr();

   // Interrupt service routine of UART
   uart_isr();
}


/*
 *  Inits CPU
 */
void cpu_init(void) {
   // Disable interrupts
   INTCON = 0;

   // Oscillator
   WDTCON0bits.SWDTEN = 0; // Watchdog disabled

   // Init ports
   ANSELA = 0;
   ANSELB = 0;
   ANSELC = 0;
   LATA = 0x00;
   LATB = 0x00;
   LATC = 0x00;
   TRISA = 0xFF;
   TRISB = 0xFF;
   TRISC = 0xFF;

   // Weak pull up resistors
   WPUA = 0;
   WPUB = 0;
   WPUC = 0;
   WPUAbits.WPUA3 = 1; // MCLR wpu

   // Enable interrupts
   INTCONbits.PEIE = 1;
   INTCONbits.GIE = 0;
}

/*
 *  MAIN FUNCTION
 */
void main(void) {
   extern char counter_reset_inputs;

   // Configure System clock frequency
   options.system_clk_mhz = 8;

   // Init CPU and peripherals
   cpu_init();
   pps_init();
   uart_init();
   timer0_init();
   lcd_init();
   adc_init();
   clc_init();
   zcd_init();

   // Enable interrupts and send wellcome message
   INTCONbits.GIE = 1;
   counter_wait_period();
   cmd_version();
   lcd_puts("System OK");


   // Init modules
   cmd_init();
   calibrate_init();
   counter_init();

   // Frequency counter main loop
   while (1) {
      counter_prescaler_channel_a();
      counter_prescaler_channel_b();

      counter_wait_period();
      system_speed();

      if (counter_reset_inputs == 1) {
         counter_reset_inputs = 0;
         uart_fputs("# Reset counters\n");
         counter_reset();
         continue;
      }

      counter_save_old_values();
      ctmu_calibrate();
      counter_capture_channel_a();
      counter_capture_channel_b();

      counter_print_channel_a();
      counter_print_channel_b();
      counter_print_end();

      // Autocalibrate with the last signal measured
      counter_1pps_autocalibrate();
      counter_10mhz_autocalibrate();
   }
}

