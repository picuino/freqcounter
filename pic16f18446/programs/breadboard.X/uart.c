/*
 * UART functions
 *
 * Author: Carlos Pardo
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License Version 3. See the file "COPYING" in the main directory
 * of this archive for more details.
 *
 */

#include <xc.h>
#include "uart.h"
#include "config.h"
#include "math48.h"
#include "counter.h"


extern options_t options;

// Buffer for read input chars.
char uart_rx_buffer[UART_RX_BUFFER_SIZE];
char uart_tx_buffer[UART_TX_BUFFER_SIZE];
volatile unsigned char rx_buff_ptr, rx_buff_overrun;
volatile unsigned char tx_buff_init, tx_buff_end;
volatile unsigned char uart_newline, rcreg;


/*
 * Interrupt Service Routine of UART
 */
void uart_isr(void) {
   if (PIR3bits.RC1IF) {
      PIR3bits.RC1IF = 0;
      rcreg = RCREG;
      if (rx_buff_ptr >= UART_RX_BUFFER_SIZE - 1) {
         uart_rx_buffer[UART_RX_BUFFER_SIZE - 1] = '\n';
         uart_newline++;
      } else {
         uart_rx_buffer[rx_buff_ptr++] = rcreg;
         if (rcreg == '\n') {
            uart_newline++;
         }
      }
   }

   if (PIR3bits.TX1IF) {
      PIR3bits.TX1IF = 0;
      if (tx_buff_init != tx_buff_end) {
         TX1REG = uart_tx_buffer[tx_buff_init++];
         if (tx_buff_init == UART_TX_BUFFER_SIZE) {
            tx_buff_init = 0;
         }
      } else {
         // Empty TX Buffer. Disable transmission
         PIE3bits.TX1IE = 0;
      }
   }
}


/*
 * UART Peripheral Pin Select
 */
void uart_pps(void) {
   // Config TX PPS
   RC0PPS = 0x0F; // RC0 (PIN_16) = 0x0F = TX1
   TRISCbits.TRISC0 = 0;

   // Config RC PPS
   RX1PPS = 0x11; // 0x11 = RC1
   TRISCbits.TRISC1 = 1;
   WPUCbits.WPUC1 = 1;
}


/*
 * Configure UART Speed
 */
void uart_init_speed(void) {
   if (options.system_clk_mhz == 8) {
      SP1BRG = _FCYCLES / UART_BAUD;
   } else if (options.system_clk_mhz == 5) {
      SP1BRG = 5000000 / UART_BAUD;
   }
   TX1STAbits.BRGH = 1;
   BAUD1CONbits.BRG16 = 1;
}


/*
 * Inits UART Peripheral
 */
void uart_init(void) {
   uart_init_speed();
   RC1STA = (unsigned char)
           (1 << 7) // SPEN:  1 = Serial port enabled
           + (0 << 6) // RX9:   1 = Selects 9-bit reception
           + (0 << 5) // SREN:  1 = Enables single receive in Master Synchronous mode
           + (1 << 4) // CREN:  1 = Enables Continuous Receive
           + (0 << 3) // ADDEN: 1 = Enables address detection (RX9 = 1)
           + (0 << 2) // FERR:  1 = Framing error
           + (0 << 1) // OERR:  1 = Overrun error (can be cleared by clearing bit CREN)
           + (0 << 0); // RX9D:  Ninth bit of Received Data

   TX1STA = (unsigned char)
           (0 << 7) // CSRC:  1 = Syncronous Master mode
           + (0 << 6) // TX9:   1 = Selects 9-bit transmission
           + (1 << 5) // TXEN:  1 = Transmit enabled
           + (0 << 4) // SYNC:  1 = Synchronous mode
           + (0 << 3) // SENDB: 1 = Asynchronous mode: Send Sync Break on next transmission (cleared by hardware upon completion)
           + (1 << 2) // BRGH:  1 = Asynchronous mode: High speed
           + (1 << 1) // TRMT:  1 = TSR empty
           + (0 << 0); // TX9D:  Ninth bit of Transmit Data

   rx_buff_overrun = 0;
   rx_buff_ptr = 0;
   uart_newline = 0;

   tx_buff_init = 0;
   tx_buff_end = 0;
   TX1STAbits.TRMT = 1;

   // Enable UART Interrupts
   PIR3bits.TX1IF = 1;
   PIE3bits.TX1IE = 0;
   PIR3bits.RC1IF = 0;
   PIE3bits.RC1IE = 1;
}


/*
 * Return one character of the read buffer
 */
unsigned char uart_fgetc(void) {
   unsigned char last_char;
   if (rx_buff_ptr == 0)
      return EOF;
   last_char = uart_rx_buffer[0];
   uart_free(1);
   return last_char;
}


/*
 * Free i positions of read buffer
 */
void uart_free(unsigned char i) {
   unsigned char init, end;

   INTCONbits.GIE = 0;
   if (rx_buff_ptr == 0 || i >= rx_buff_ptr) {
      rx_buff_ptr = 0;
      INTCONbits.GIE = 1;
      return;
   }
   init = 0;
   end = i;
   while (end < rx_buff_ptr) {
      uart_rx_buffer[init++] = uart_rx_buffer[end++];
   }
   rx_buff_ptr = init;
   INTCONbits.GIE = 1;
}


/*
 * Return 1 if there is characters in the recepcion buffer
 */
char uart_kbhit(void) {
   if (rx_buff_ptr > 0)
      return 1;
   return 0;
}


/*
 * Send char to UART with buffer and interrupts
 */
void uart_fputc(char c) {
   char intcon;
   intcon = INTCON;
   INTCONbits.GIE = 0;
   uart_tx_buffer[tx_buff_end++] = c;
   if (tx_buff_end == UART_TX_BUFFER_SIZE) {
      tx_buff_end = 0;
   }
   if (tx_buff_end == tx_buff_init) {
      tx_buff_init++;
   }
   if (tx_buff_init == UART_TX_BUFFER_SIZE) {
      tx_buff_init = 0;
   }
   INTCON = intcon;
   PIE3bits.TX1IE = 1;
}


/*
 * Puts rom string to UART
 */
void uart_fputs(const char *str) {
   while (*str) {
      if (*str == '\n')
         uart_fputc('\r');
      uart_fputc(*str);
      str++;
   }
}


/*
 * Puts ram buffer to UART
 */
void uart_fputs_ram(char *str) {
   while (*str) {
      if (*str == '\n')
         uart_fputc('\r');
      uart_fputc(*str);
      str++;
   }
}

/*
 * Wait until transmit buffer is empty
 */
void uart_fflush(void) {
   while(tx_buff_init != tx_buff_end);
}