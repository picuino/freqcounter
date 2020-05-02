/*
 * LCD 16x2 manage routines
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
#include "lcd.h"


/****************************************************************************
      DEFINITIONS
 ****************************************************************************/

#define LCD_E      LATBbits.LATB4         // LCD CONTROL BIT. Enable
#define LCD_RS     LATCbits.LATC2         // LCD CONTROL BIT. Control/data mode
#define LCD_D4     LATCbits.LATC1         // LCD DATA BIT
#define LCD_D5     LATCbits.LATC0         // LCD DATA BIT
#define LCD_D6     LATAbits.LATA1         // LCD DATA BIT
#define LCD_D7     LATAbits.LATA0         // LCD DATA BIT

#define LCD_TRIS_OUT()   TRISC &= ~((1<<0)+(1<<1)+(1<<2)); TRISB &= ~((1<<4)); TRISA &= ~((1<<0)+(1<<1))
#define LCD_TRIS_IN()    TRISC |= ((1<<0)+(1<<1)+(1<<2)); TRISB |= ((1<<4)); TRISA |= ((1<<0)+(1<<1))


/****************************************************************************
      LCD ROUTINES
 ****************************************************************************/


/*
 *  INITIALIZE LCD IN 4-BIT MODE AND SET PREFERENCES
 */
void lcd_init(void) {

   // Init control pins
   LCD_RS = 0; // LCD IN CONTROL MODE
   LCD_E = 0;

   // Init data pins
   LCD_D4 = 0;
   LCD_D5 = 0;
   LCD_D6 = 0;
   LCD_D7 = 0;

   // Init control and data pins
   LCD_TRIS_OUT();

   // Wait at least 20 ms after Vdd rises to 4.5 V
   __delay_ms(50);

   // Reset procedure through software
   lcd_putnibble(0x30); // 8 bits mode
   __delay_us(4500);
   lcd_putnibble(0x30); // 8 bits mode
   __delay_us(4500);
   lcd_putnibble(0x30); // 8 bits mode
   __delay_us(150);
   lcd_putnibble(0x20); // 4 bits mode

   // CONFIGURE LCD
   lcd_putctrl(LCD_FUNCTION_SET + LCD_4_BIT_INTERFACE
           + LCD_2_LINES + LCD_5X8_DOTS);
   lcd_putctrl(LCD_DISPLAY_CONTROL + LCD_DISPLAY_ON
           + LCD_CURSOR_OFF + LCD_CURSOR_BLINK_OFF);
   lcd_clear();
   lcd_putctrl(LCD_ENTRY_MODE + LCD_ENTRY_LEFT + LCD_ENTRY_SHIFT_OFF);
}


/*
 * Clears entire display and sets DDRAM address 0 in address
 * counter
 */
void lcd_clear(void) {
   lcd_putctrl(0b00000001); // CLEAR DISPLAY.
   __delay_us(2000); // Execution time > 1.6 ms
}


/*
 * Sets DDRAM address 0 in address counter. Also returns
 * display from being shifted to original position. DDRAM
 * contents remain unchanged
 */
void lcd_home(void) {
   lcd_putctrl(0b00000010); // CURSOR TO POSITION 0
   __delay_us(2000); // Execution time > 1.6 ms
}


/*
 * Set address of cursor in LCD
 * Send addr to DDRAM address register
 * First line inits at address 0
 * Second line inits at address 40
 */
void lcd_goto(unsigned char x) {
   lcd_putctrl(0b10000000 + x); // CURSOR TO POSITION x
}


/*
 * Send control code to LCD
 */
void lcd_putctrl(unsigned char c) {
   LCD_RS = 0; // LCD IN CONTROL MODE
   lcd_putbyte(c);
}


/*
 * Send character to LCD
 */
void lcd_putc(unsigned char c) {
   LCD_RS = 1; // LCD IN DATA MODE
   lcd_putbyte(c);
}


/*
 * Send string in ram to LCD
 */
void lcd_puts_ram(char *str) {
   while (*str) {
      lcd_putc(*str++);
   }
}


/*
 * Send constant string to LCD
 */
void lcd_puts(const char *str) {
   while (*str) {
      lcd_putc(*str++);
   }
}


/*
 * Send byte to LCD
 */
void lcd_putbyte(unsigned char c) {
   LCD_TRIS_OUT();
   lcd_putnibble(c);
   lcd_putnibble(c << 4);
   LCD_D4 = 0;
   LCD_D5 = 0;
   LCD_D6 = 0;
   LCD_D7 = 0;
}


/*
 * Send high nibble of character 'c' to LCD
 */
void lcd_putnibble(unsigned char c) {
   if (c & 0x10) LCD_D4 = 1;
   else LCD_D4 = 0;
   if (c & 0x20) LCD_D5 = 1;
   else LCD_D5 = 0;
   if (c & 0x40) LCD_D6 = 1;
   else LCD_D6 = 0;
   if (c & 0x80) LCD_D7 = 1;
   else LCD_D7 = 0;
   lcd_enable();
}


/*
 * ENABLE LCD
 * Send enable signal to LCD
 */
void lcd_enable(void) {
   LCD_E = 0;
   __delay_us(1); // Enable signal must be set 1us min
   LCD_E = 1;
   __delay_us(1); // Enable signal must be set 1us min
   LCD_E = 0;
   __delay_us(140); // Command need > 37us to settle
}
