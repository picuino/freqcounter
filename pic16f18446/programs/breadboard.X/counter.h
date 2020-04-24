/*
    Declaration file for adf4112.c
 */

#ifndef COUNTER_H
#define COUNTER_H

#define COUNTER_BUFFER_SIZE    11

#define DISP_TRIS   TRISCbits.TRISC6
#define DISP_LAT    LATCbits.LATC6
#define DISP_PPS    RC6PPS

#define DTIME_TRIS  TRISCbits.TRISC3
#define DTIME_LAT   LATCbits.LATC3
#define DTIME_ANS   ANSELCbits.ANSC3

#define INPUT_A           0
#define INPUT_B           1


typedef union {
    unsigned long data[2];
    
    struct {
        unsigned char numformat;
        unsigned char prescaler_a;
        unsigned char prescaler_b;
        unsigned char system_clk_mhz;

        unsigned input_a : 1;
        unsigned input_b : 1;
        unsigned input_zcd : 1;
        unsigned autocalibrate : 1;
        unsigned ctmu_enable : 1;
        unsigned fast_measure : 1;

        unsigned print_pulses : 1;
        unsigned print_time : 1;
        unsigned print_long_frequency : 1;
        unsigned print_period : 1;
        unsigned print_phase : 1;
        unsigned print_lcd : 1;
        
    };
} options_t;


#include "math48.h"

void counter_calculate_frequency(void);
void counter_period_a(void);
void counter_period_b(void);
void counter_capture(void);
void counter_wait_period(void);

void counter_init(void);
void counter_options_init(void);
void counter_save_old_values(void);
void counter_buffer_inc(void);
void counter_unprescaler(char prescaler);
void counter_reset(void);

void counter_prescaler_channel_a(void);
void counter_capture_channel_a(void);
void counter_print_channel_a(void);

void counter_prescaler_channel_b(void);
void counter_capture_channel_b(void);
void counter_print_channel_b(void);

void counter_print_end(void);
void counter_blink_lcd(void);

#endif
