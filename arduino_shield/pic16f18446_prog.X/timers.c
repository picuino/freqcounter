/*
 * Timers configuration
 *
 * Author: Carlos Pardo
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License Version 3. See the file "COPYING" in the main directory
 * of this archive for more details.
 *
 */

#include <xc.h>
#include "math48.h"
#include "timers.h"
#include "config.h"
#include "counter.h"


/*
 * GLOBAL VARIABLES
 */
extern options_t options;
extern unsigned char counter_capturing_channel;
volatile unsigned long milliseconds_var;
volatile unsigned char timer0_ticks;
volatile uint48 timer1, timer3, timer5;
extern uint48 pulses_a, pulses_b, time;
volatile unsigned char timers_readed;


/*
 * Interrupt Service Routine for timers
 */
void timers_isr(void) {
   // Read counters
   if (PIR6bits.CCP3IF == 1) {
      PIR6bits.CCP3IF = 0;
      if (counter_capturing_channel == INPUT_A) {
         // Read pulses of input A in CCP1
         pulses_a.word[0] = CCPR1;
         pulses_a.dword = timer1.dword;
         if (PIR4bits.TMR1IF == 1) {
            if (pulses_a.word[0] < 5000)
               pulses_a.dword++;
         }
      } else {
         // Read pulses of input B in CCP2
         pulses_b.word[0] = CCPR2;
         pulses_b.dword = timer5.dword;
         if (PIR4bits.TMR5IF == 1) {
            if (pulses_b.word[0] < 5000)
               pulses_b.dword++;
         }
      }
      
      // Read time (clk cycles) in CCP3
      time.word[0] = CCPR3;
      time.dword = timer3.dword;
      if (PIR4bits.TMR3IF == 1) {
         if (time.word[0] < 5000)
            time.dword++;
      }
      timers_readed = 1;
   }

   // Timer0 interrupt counter
   if (PIR0bits.TMR0IF == 1) {
      PIR0bits.TMR0IF = 0;
      timer0_ticks++;
      if (timer0_ticks >= options.system_clk_mhz) {
         timer0_ticks = 0;
         milliseconds_var++;
      }
   }

   // Timer1 interrupt counter
   if (PIR4bits.TMR1IF == 1) {
      PIR4bits.TMR1IF = 0;
      timer1.dword++;
   }

   // Timer3 interrupt counter
   if (PIR4bits.TMR3IF == 1) {
      PIR4bits.TMR3IF = 0;
      timer3.dword++;
   }

   // Timer5 interrupt counter
   if (PIR4bits.TMR5IF == 1) {
      PIR4bits.TMR5IF = 0;
      timer5.dword++;
   }
}


/*
 *  Timer0 initialization (Cycles/1000 for milliseconds generator)
 */
void timer0_init(void) {
   T0CON1bits.T0CS = 2; // 2 = Fosc/4

   T0CON1bits.T0ASYNC = 0; // 1 = counter not syncronized with system clocks
   TMR0H = 125 - 1;
   TMR0L = 0;
   milliseconds_var = 0;
   T0CON0bits.T016BIT = 0;
   T0CON0bits.T0EN = 1;
   T0CON1bits.T0CKPS = 3; // 0 = 1/8 prescaler

   // Timer0 Reset and enable interrupts
   PIR0bits.TMR0IF = 0;
   PIE0bits.TMR0IE = 1;
}


/*
 * Return milliseconds since last reset
 */
unsigned long milliseconds(void) {
   unsigned long value;
   char intcon;
   intcon = INTCON;
   INTCONbits.GIE = 0;
   value = milliseconds_var;
   INTCON = intcon;
   return value;
}


/*
 *  Timer1 initialization (Count input A pulses)
 */
void timer1_init(void) {
   T1CLKbits.CS = 0b1101; // 0b1101 = CLC1_OUT

   T1CONbits.RD16 = 1; // 1 = enables 16bit operation
   TMR1H = 0;
   TMR1L = 0;
   CLEAR48(timer1);
   T1CONbits.ON = 1;

   // Timer1 Reset and enable interrupts
   PIR4bits.TMR1IF = 0;
   PIE4bits.TMR1IE = 1;
}


/*
 *  Timer3 initialization  (Count system clock cycles)
 */
void timer3_init(void) {
   T3CLKbits.CS = 0b0001; // 0b0001 Clock select = Fosc/4
   // 0b1101 CLC1
   T3CONbits.RD16 = 1; // 1 = enables 16bit operation
   TMR3H = 0;
   TMR3L = 0;
   CLEAR48(timer3);
   T3CONbits.ON = 1;

   // Timer1 Reset and enable interrupts
   PIR4bits.TMR3IF = 0;
   PIE4bits.TMR3IE = 1;
}


/*
 *  Timer5 initialization  (Count input B pulses)
 */
void timer5_init(void) {
   T5CLKbits.CS = 0b1110; // 0b1110 = CLC2_OUT

   T5CONbits.RD16 = 1; // 1 = enables 16bit operation
   TMR5H = 0;
   TMR5L = 0;
   CLEAR48(timer5);
   T5CONbits.ON = 1;

   // Timer1 Reset and enable interrupts
   PIR4bits.TMR5IF = 0;
   PIE4bits.TMR5IE = 1;
}


/*
 *  Capture1 module initialization
 */
void ccp1_init() {
   CCP1CONbits.CCP1MODE = 0b0101; // 0b0101 Capture every rising edge
   CCP1CAPbits.CTS = 0b110; // 0b110 = CLC3 output
   CCPTMRS0bits.C1TSEL = 0b01; // 0b01 = Based off Timer 1
   CCP1CONbits.CCP1EN = 1;

   // Enable interrupts
   PIR6bits.CCP1IF = 0;
   PIE6bits.CCP1IE = 0;
}


/*
 *  Capture2 module initialization
 */
void ccp2_init() {
   CCP2CONbits.CCP2MODE = 0b0101; // 0b0101 Capture every rising edge
   CCP2CAPbits.CTS = 0b110; // 0b110 = CLC3 output
   CCPTMRS0bits.C2TSEL = 0b11; // 0b11 = Based off Timer 5
   CCP2CONbits.CCP2EN = 1;

   // Enable interrupts
   PIR6bits.CCP2IF = 0;
   PIE6bits.CCP2IE = 0;
}


/*
 *  Capture3 module initialization
 */
void ccp3_init() {
   CCP3CONbits.CCP3MODE = 0b0101; // 0b0101 Capture every rising edge
   CCP3CAPbits.CTS = 0b110; // 0b110 = CLC3 output
   CCPTMRS0bits.C3TSEL = 0b10; // 0b10 = Based off Timer 3
   CCP3CONbits.CCP3EN = 1;

   // Enable interrupts
   PIR6bits.CCP3IF = 0;
   PIE6bits.CCP3IE = 1;
}

