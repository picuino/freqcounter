/*
    Declaration file for peripheral.c
 */

#ifndef PERIPHERAL_H
#define PERIPHERAL_H

#define CLC3_DATA   CLC3POLbits.G2POL
#define CLC3_RESET  CLC3POLbits.G3POL
#define INPUT_A_PPS  0x15   // 0x15 = RC5
#define INPUT_B_PPS  0x14   // 0x14 = RC4

void pps_lock(void);
void pps_unlock(void);
void pps_init(void);
void clc_init(void);
void zcd_init(void);
void adc_init(void);

void clc_capture_channel_a(void);
void clc_capture_channel_b(void);
void clc_input_a_zcd(void);
void clc_prescaler_a_on(void);
void clc_prescaler_a_off(void);
void clc_prescaler_b_on(void);
void clc_prescaler_b_off(void);

void adc_ctmu(void);
int adc_read(void);

#endif