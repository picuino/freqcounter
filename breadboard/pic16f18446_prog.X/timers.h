/*
    Declaration file for timer.c
 */

#ifndef TIMERS_H
#define TIMERS_H

void timers_isr(void);
void timer0_init(void);
unsigned long milliseconds(void);
void timer1_init(void);
void timer3_init(void);
void timer5_init(void);
void ccp1_init(void);
void ccp2_init(void);
void ccp3_init(void);

#endif