/*
    Declaration file for uart.c
 */

#ifndef UART_H
#define UART_H

#define EOF                  (-1)
#define UART_RX_BUFFER_SIZE  120
#define UART_TX_BUFFER_SIZE  250

void uart_isr(void);
void uart_init(void);
void uart_init_speed(void);
void uart_pps(void);

unsigned char uart_fgetc(void);
char uart_kbhit(void);
void uart_free(unsigned char i);

void uart_fputc(char c);
void uart_fputs(const char *str);
void uart_fputs_ram(char *str);
void uart_fflush(void);

#endif

