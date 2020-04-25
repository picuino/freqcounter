/*
 * Peripheral configuration
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
#include "counter.h"
#include "uart.h"

extern options_t options;


/*
 * Unlock Peripheral Pin Select
 */
void pps_unlock(void) {
   char temp;

   // Save GIE state
   temp = INTCON;
   INTCONbits.GIE = 0;

   // Unlock PPS
   PPSLOCK = 0x55;
   PPSLOCK = 0xAA;
   PPSLOCKbits.PPSLOCKED = 0; // Unlock

   // Load GIE state
   INTCON = temp;
}


/*
 * Lock Peripheral Pin Select changes
 */
void pps_lock(void) {
   char temp;

   // Save GIE state
   temp = INTCON;
   INTCONbits.GIE = 0;

   // Unlock PPS
   PPSLOCK = 0x55;
   PPSLOCK = 0xAA;
   PPSLOCKbits.PPSLOCKED = 1; // Lock

   // Load GIE state
   INTCON = temp;
}


/*
 *  Peripheral pin select configuration
 */
void pps_init(void) {
   // Unlock PPS
   pps_unlock();

   uart_pps();

   // Config CLC inputs PPS
   CLCIN1PPS = INPUT_A_PPS;
   CLCIN2PPS = INPUT_B_PPS;

   // Config CLC4 PPS (CTMU Pulse output)
   RC6PPS = 0x04; // 4 = CLC4OUT
   TRISCbits.TRISC6 = 0;

   // Lock PPS
   pps_lock();
}


/*
 *  Configurable Logic Cell Init (Cap. 17)
 */
void clc_init(void) {
   clc_prescaler_a_on();
   clc_prescaler_b_on();
   clc_prescaler_a_off();
   clc_prescaler_b_off();
}


/*
 * Selects between Input A or Input ZCD
 */
void clc_input_a_zcd(void) {
   if (options.input_zcd)
      CLC1SEL0 = 29; // Data select 29 = ZCD_out
   else
      CLC1SEL0 = 1; // Data select 1 = CLCIN1PPS
}


void clc_prescaler_a_on(void) {
   options.prescaler_a = 2;

   // CLC1 setup
   // JK biestable divisor by 2
   // Divide input signal by 2
   CLC1CON = (1 << 7) // Enable
           | (0b110); // 110=J/K flip-flop
   CLC1POL = 0b00001010; // Polarity

   clc_input_a_zcd();
   CLC1SEL1 = 0; // Data select
   CLC1SEL2 = 0; // Data select
   CLC1SEL3 = 0; // Data select

   CLC1GLS0 = 0b00000010; // GATE 1 (CLK) = CLCIN1PPS
   CLC1GLS1 = 0b00000000; // GATE 2 (J)   = 1
   CLC1GLS2 = 0b00000000; // GATE 3 (RST) = 0
   CLC1GLS3 = 0b00000000; // GATE 4 (K)   = 1
}


void clc_prescaler_a_off(void) {
   options.prescaler_a = 1;

   // CLC1 setup
   // Input gate with TTL levels
   CLC1CON = (1 << 7) // Enable
           | (0b000); // 000= AND-OR
   CLC1POL = 0b00000010; // Polarity
}


void clc_prescaler_b_on(void) {
   options.prescaler_b = 2;

   // CLC2 setup
   // JK biestable divisor by 2
   // Divide input signal by 2
   CLC2CON = (1 << 7) // Enable
           | (0b110); // 110=J/K flip-flop
   CLC2POL = 0b00001010; // Polarity

   CLC2SEL0 = 2; // Data select CLCIN2PPS
   CLC2SEL1 = 0; // Data select
   CLC2SEL2 = 0; // Data select
   CLC2SEL3 = 0; // Data select

   CLC2GLS0 = 0b00000010; // GATE 1 (CLK) = CLCIN2PPS
   CLC2GLS1 = 0b00000000; // GATE 2 (J)   = 1
   CLC2GLS2 = 0b00000000; // GATE 3 (RST) = 0
   CLC2GLS3 = 0b00000000; // GATE 4 (K)   = 1
}


void clc_prescaler_b_off(void) {
   options.prescaler_b = 1;

   // CLC2 setup
   // Input gate with TTL levels
   CLC2CON = (1 << 7) // Enable
           | (0b000); // 000= AND-OR
   CLC2POL = 0b00000010; // Polarity
}


/*
 * Configure CLC for capture Input A rising edge
 */
void clc_capture_channel_a(void) {
   // CLC3 setup
   // Biestable input.
   // Send capture signal after input rising edge
   CLC3CON = (1 << 7) // Enable
           | (0b100); // 100= D Flip-Flop with S and R
   CLC3POL = 0b00000000; // Polarity

   CLC3SEL0 = 32; // Data select 32 = CLC1 Output
   CLC3SEL1 = 0; // Data select
   CLC3SEL2 = 0; // Data select
   CLC3SEL3 = 0; // Data select

   CLC3GLS0 = 0b00000010; // GATE 1 (CLK) = CLC1 Output
   CLC3GLS1 = 0b00000000; // GATE 2 (D)   = 0
   CLC3GLS2 = 0b00000000; // GATE 3 (RST) = 0
   CLC3GLS3 = 0b00000000; // GATE 4 (SET) = 0


   // CLC4 setup
   // Biestable.
   // Make a pulse between rise input and capture event for CTMU measure
   CLC4CON = (1 << 7) // Enable
           | (0b100); // 100= D Flip-Flop with S and R
   CLC4POL = 0b00000010; // Polarity

   CLC4SEL0 = 34; // Data select CLC3 Output
   CLC4SEL1 = 20; // Data select CCP1 Output
   CLC4SEL2 = 0; // Data select
   CLC4SEL3 = 0; // Data select

   CLC4GLS0 = 0b00000010; // GATE 1 (CLK) = CLC3 Output
   CLC4GLS1 = 0b00000000; // GATE 2 (D)   = 1
   CLC4GLS2 = 0b00001000; // GATE 3 (RST) = CCP1 Output
   CLC4GLS3 = 0b00000000; // GATE 4 (SET) = 0
}


/*
 * Configure CLC for capture Input B rising edge
 */
void clc_capture_channel_b(void) {
   // CLC3 setup
   // Biestable input.
   // Send capture signal after Input B rising edge
   CLC3CON = (1 << 7) // Enable
           | (0b100); // 100= D Flip-Flop with S and R
   CLC3POL = 0b00000000; // Polarity

   CLC3SEL0 = 33; // Data select 33 = CLC2 Output
   CLC3SEL1 = 0; // Data select
   CLC3SEL2 = 0; // Data select
   CLC3SEL3 = 0; // Data select

   CLC3GLS0 = 0b00000010; // GATE 1 (CLK) = CLC2 Output
   CLC3GLS1 = 0b00000000; // GATE 2 (D)   = 0
   CLC3GLS2 = 0b00000000; // GATE 3 (RST) = 0
   CLC3GLS3 = 0b00000000; // GATE 4 (SET) = 0


   // CLC4 setup
   // Biestable.
   // Make a pulse between rise input and capture event for CTMU measure
   CLC4CON = (1 << 7) // Enable
           | (0b100); // 100= D Flip-Flop with S and R
   CLC4POL = 0b00000010; // Polarity

   CLC4SEL0 = 34; // Data select CLC3 Output
   CLC4SEL1 = 21; // Data select CCP2 Output
   CLC4SEL2 = 0; // Data select
   CLC4SEL3 = 0; // Data select

   CLC4GLS0 = 0b00000010; // GATE 1 (CLK) = CLC3 Output
   CLC4GLS1 = 0b00000000; // GATE 2 (D)   = 1
   CLC4GLS2 = 0b00001000; // GATE 3 (RST) = CCP2 Output
   CLC4GLS3 = 0b00000000; // GATE 4 (SET) = 0
}


/*
 * Zero Cross Detection Module
 */
void zcd_init(void) {
   ZCDCONbits.ZCDPOL = 0;
   ZCDCONbits.ZCDSEN = 1;
}


/*
 *  ADC init
 */
void adc_init(void) {
   adc_ctmu();

   // Configure ADC
   ADCON0bits.FM = 1; // 1 = right justified
   ADCON0bits.CS = 0; // 0 = Clock Fosc/ADCLK
   ADCLK = 31; // 5 = ADC Frequency = Fosc / 64

   ADREFbits.NREF = 0; // 0 = Vref- is VSS
   ADREFbits.PREF = 3; // 3 = Vref+ is FVR_buffer1

   // Configure Fixed Voltage Feference FVR
   FVRCONbits.FVREN = 1; // Enable FVR
   FVRCONbits.TSEN = 0; // Temperature indicator disable
   FVRCONbits.ADFVR = 3; // 3 = 4.096v
   while (FVRCONbits.FVRRDY == 0);

   // Enable ADC
   ADCON0bits.ADON = 1;
}


/*
 * Define ADC input as CTMU
 */
void adc_ctmu(void) {
   // Define CTMU as analog Input
   TRISCbits.TRISC3 = 1;
   ANSELCbits.ANSC3 = 1;
   ADPCH = 0x13; // 010011 = RC3
   ADREFbits.PREF = 3; // 3 = Vref+ is FVR_buffer1
   __delay_us(100);
}


/*
 * Read ADC after pulse in CTMU
 */
int adc_read(void) {
   // Read ADC module
   __delay_us(10);
   ADCON0bits.GO_nDONE = 1;
   while (ADCON0bits.GO_nDONE);
   return ADRES;
}