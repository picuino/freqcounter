/*
    Declaration file for lcd.c
 */

#ifndef LCD_H
#define LCD_H

#define LCD_FUNCTION_SET        0b00100000
#define LCD_4_BIT_INTERFACE     0b00000000
#define LCD_8_BIT_INTERFACE     0b00010000
#define LCD_2_LINES             0b00001000
#define LCD_5X8_DOTS            0b00000000

#define LCD_DISPLAY_CONTROL     0b00001000
#define LCD_DISPLAY_OFF         0b00000000
#define LCD_DISPLAY_ON          0b00000100
#define LCD_CURSOR_OFF          0b00000000
#define LCD_CURSOR_ON           0b00000010
#define LCD_CURSOR_BLINK_OFF    0b00000000
#define LCD_CURSOR_BLINK_ON     0b00000001

#define LCD_ENTRY_MODE          0b00000100
#define LCD_ENTRY_LEFT          0b00000010
#define LCD_ENTRY_RIGHT         0b00000000
#define LCD_ENTRY_SHIFT_ON      0b00000001
#define LCD_ENTRY_SHIFT_OFF     0b00000000

#define LCD_GOTO_LINE2          40

void lcd_clear(void);
void lcd_enable(void);
void lcd_goto(unsigned char x);
void lcd_home(void);
void lcd_init(void);
void lcd_putbyte(unsigned char c);
void lcd_putc(unsigned char c);
void lcd_putctrl(unsigned char c);
void lcd_putnibble(unsigned char c);
void lcd_puts(const char *str);
void lcd_puts_ram(char *str);
void lcd_data_tris_out(void);
void lcd_control_tris_out(void);

#endif


