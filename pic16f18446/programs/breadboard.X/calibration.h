/*
    Declaration file for adf4112.c
 */

#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "math48.h"
#include "config.h"

const unsigned long CALIBRATION_PPB_8MHZ __at(SAF_ADDRESS) = 0;
const unsigned long CALIBRATION_PPB_5MHZ __at(SAF_ADDRESS + 8) = 0;


typedef struct {
   long calibration_8mhz;
   long calibration_5mhz;
} calibration_t;


void ctmu_calibrate(void);
void ctmu_discharge(void);
void calibrate_init(void);
uint48 ppb_f48(long ppb);
void counter_1pps_autocalibrate(void);
void counter_10mhz_autocalibrate(void);
void counter_autocalibrate(uint48 billion);
uint48 calibration_get(void);
void system_speed(void);
void calibration_eprom_read(void);
void calibration_eprom_write(void);

#endif
