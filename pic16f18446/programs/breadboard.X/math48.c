/*
 * Matematical and print functions with 48 bits arithmetic
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
#include "math48.h"
#include "uart.h"
#include "lcd.h"


/*
 * GLOBAL VARS AND DEFINITIONS
 */
static uint48 ans; // Variable for store answer and status register
char str_buf[30];

static st48_t st48;


/****************************************************************************
      BASIC MATH ROUTINES
 ****************************************************************************/


/*
 * Compare 2 unsigned uint48 numbers
 * (a = b) return 0
 * (a > b) return 1
 * (a < b) return -1
 */
signed char comp48(uint48 a, uint48 b) {
   if (a.word[2] > b.word[2]) return 1;
   if (a.word[2] < b.word[2]) return -1;
   if (a.word[1] > b.word[1]) return 1;
   if (a.word[1] < b.word[1]) return -1;
   if (a.word[0] > b.word[0]) return 1;
   if (a.word[0] < b.word[0]) return -1;
   return 0;
}


/*
 * Sub 2 uint48 numbers
 * return a - b
 */
uint48 sub48(uint48 a, uint48 b) {
   ans.dword = a.dword - b.dword;
   if (b.word[0] > a.word[0])
      ans.dword--;
   ans.word[0] = a.word[0] - b.word[0];
   return ans;
}


/*
 * Add 2 uint48 numbers
 * return a + b
 */
uint48 add48(uint48 a, uint48 b) {
   ans.dword = a.dword + b.dword;
   ans.word[0] = a.word[0] + b.word[0];
   if (ans.word[0] < a.word[0])
      ans.dword++;
   return ans;
}


/*
 * Increment uint48 number
 * return a + 1
 */
uint48 inc48(uint48 a) {
   ans.word[0] = a.word[0] + 1;
   ans.dword = a.dword;
   if (ans.word[0] == 0)
      ans.dword++;
   return ans;
}


/*
 * Shift left
 * return a<<1
 */
uint48 sl48(uint48 a) {
   st48.carry = 0;
   if (a.b47 == 1) st48.carry = 1;
   ans.dword = a.dword << 1;
   if (a.b15 == 1) ans.b16 = 1;
   ans.word[0] = a.word[0] << 1;
   return ans;
}


/*
 * Shift right
 * return a>>1
 */
uint48 sr48(uint48 a) {
   st48.carry = 0;
   if (a.b0 == 1) st48.carry = 1;
   ans.word[0] = a.word[0] >> 1;
   if (a.b16 == 1) ans.b15 = 1;
   ans.dword = a.dword >> 1;
   return ans;
}


/****************************************************************************
      FLOATING POINT MATH ROUTINES
 ****************************************************************************/


/*
 * Transform 48bit integer to float format.
 * [8 bit exponent][40 bit mantissa]
 */
uint48 itof48(uint48 a) {
   signed char i, exp;

   exp = 47;
   for (i = 47; i > 0; i--) {
      if (a.b47 == 1) break;
      a = sl48(a);
      exp--;
   }
   a.byte[0] = a.byte[1];
   a.byte[1] = a.byte[2];
   a.byte[2] = a.byte[3];
   a.byte[3] = a.byte[4];
   a.byte[4] = a.byte[5];
   a.byte[5] = (unsigned char) exp;
   return a;
}


/*
 * multiply 48bit positive float with 48bit positive float
 * return a * b
 * [8 bit exp][40 bit mantissa] -> number = mantissa * 2 ^ (exp)
 */
uint48 fmul48(uint48 a, uint48 b) {
   signed char i, exp;
   uint48 f48;

   // Clear variables
   CLEAR48(f48);

   exp = a.byte[5] + b.byte[5];
   a.byte[5] = b.byte[5] = 0;

   // multiply f48 = a * b
   for (i = 40; i > 0; i--) {
      if (f48.b0 == 1)
         f48 = inc48(f48); // Rounding
      f48 = sr48(f48);
      if (b.b0 == 1) {
         f48 = add48(f48, a);
      }
      b = sr48(b);
   }
   while (f48.byte[5]) {
      f48 = sr48(f48);
      exp++;
   }

   // Move mantissa, add exponent and return
   f48.byte[5] = (unsigned char) exp;
   return f48;
}


/*
 * Divide 48bit positive float with 48bit positive float
 * return a / b in float format
 * manage only 32 bit precision for fast calc
 * [8 bit exp][32 bit mantissa] -> number = mantissa * 2 ^ (exp)
 */
uint48 fdiv48(uint48 a, uint48 b) {
   signed char i, exp;
   uint48 f48;

   // Clear variables
   CLEAR48(f48);

   exp = a.byte[5] - b.byte[5];
   a.byte[5] = b.byte[5] = 0;

   // if (argument == zero) return zero
   if (b.b39 == 0 || a.b39 == 0)
      return f48;

   // divide a / b
   if (comp48(a, b) < 0) {
      a = sl48(a);
      exp--;
   }
   for (i = 40; i > 0; i--) {
      if (comp48(a, b) >= 0) {
         a = sub48(a, b);
         f48.b0 = 1;
      }
      if (f48.b39 == 1) break;
      f48 = sl48(f48);
      a = sl48(a);
   }

   // Move mantissa, add exponent and return
   f48.byte[5] = (unsigned char) exp;
   return f48;
}


/****************************************************************************
      DECIMAL MATH ROUTINES
 ****************************************************************************/


/*
 * Transform 48bit float number to
 * 48 bit integer
 */
uint48 ftoi48(uint48 num) {
   signed char exp, i;

   exp = num.byte[5] - MANTISA_BITS;
   num.byte[5] = 0;

   if (exp >= 0) {
      while (exp--) {
         num = sl48(num);
      }
   } else {
      exp = -exp;
      while (exp--) {
         num = sr48(num);
      }
   }
   return num;
}


/*
 * Transform 48bit float number to
 * 40 bit integer + decimal dot
 */
uint48 ftod48(uint48 n) {
   signed char exp, dot, i;

   // Read exponent and set bit 41
   exp = n.byte[5] - MANTISA_BITS;
   n.byte[5] = 0x00;

   // Adjust binary to decimal
   dot = 0;
   for (i = 30; i > 0; i--) {
      if (exp>-3) break;

      // Test overflow
      if (exp == -3) {
         if (n.byte[4] >= 204) break;
      }
      // n = n * 10/8
      n = inc48(n);
      ans = sr48(n);
      ans = sr48(ans);
      n = add48(n, ans);
      exp += 3;
      dot--;

      // n = n / 2
      if (n.b40 == 1) {
         inc48(n);
         n = sr48(ans); // 1/2
         exp++;
      }
   };

   for (; exp < 0; exp++) {
      inc48(n);
      n = sr48(ans);
   }
   // Add decimal exponent
   n.byte[5] = (unsigned char) dot;
   return n;
}


/*
 * Transform 48bit unsigned integer to BCD string
 */
void ltoa48(char *str, uint48 bin) {
   unsigned char maxdig, digcnt, bitcnt;
   static char *p, carry;

   // Clear string
   p = str;
   digcnt = DEC_DIG_48 + 1;
   do {
      *p++ = 0;
   } while (--digcnt);

   // Transform binary to BCD
   bitcnt = 48;
   maxdig = (DEC_DIG_48 - 1);
   str += (DEC_DIG_48 - 1);
   do {
      // Shift left binary number with carry
      carry = 0;
      if (bin.b47 == 1) carry |= 1;
      bin = sl48(bin);

      // Shift left decimal number with carry
      p = str;
      digcnt = (unsigned char) (DEC_DIG_48 - maxdig);
      do {
         carry = (*p << 1) + carry;
         if (carry >= 10) {
            *p-- = carry - 10;
            carry = 1;
            if (digcnt == 1) {
               maxdig--;
               digcnt++;
            }
         } else {
            *p-- = carry;
            carry = 0;
         }
      } while (--digcnt);
   } while (--bitcnt);

   // Transform BCD to ASCII
   digcnt = DEC_DIG_48;
   do *str-- += '0'; while (--digcnt);
}


/*
 * Reduce n digits in decimal string rounding it.
 * len(decimal string) must be less than 20
 * n < len(decimal string)
 */
void round48(char *str, unsigned char n) {
   signed char i;
   char *p;

   // init pointers
   p = str;

   // Find first right digit
   while (*p == '0') p++;

   // Count n digits
   for (i = n; i > 0; i--) {
      if (*p == 0) break;
      p++;
   }

   // round last digit if > '5'
   if (*p < '5') {
      *p = 0;
      return;
   }

   // add carry rounding
   *p = 0;
   i = n;
   while (1) {
      if (p == str) break;
      p--;
      i--;
      if (*p < '9') {
         *p = *p + 1;
         break;
      } else *p = '0';
   }
}


/*
 * Transform 40 bit integer and decimal dot
 * to string number in scientific or engeenering format
 */
void sprintf48(char *str, char digits, uint48 n) {
   signed char dot, i;
   unsigned char eng;
   char *p;

   // Transform integer to ASCII
   dot = n.byte[5];
   n.byte[5] = 0;
   ltoa48(str, n);

   // Round decimal number
   round48(str, digits);

   // Shift left string
   p = str;
   for (i = 14; i > 0; i--) {
      if (*p != '0') break;
      p++;
   }

   dot += i;
   for (i = 4; i > 0; i--) {
      *str++ = *p++;
      if (dot % 3 == 0) {
         *str++ = DOT_CHAR;
         break;
      }
      dot--;
   }

   while (*p != 0) {
      *str++ = *p++;
   }

   // Add postfix
   if (st48.numformat == FORMAT_ENGINEERING) {
      // Add Unit Prefix
      *str++ = ' ';
      switch (dot) {
         case -15: dot = 'f';
            break; // femto
         case -12: dot = 'p';
            break; // pico
         case -9: dot = 'n';
            break; // nano
         case -6: dot = 'u';
            break; // micro
         case -3: dot = 'm';
            break; // mili
         case 3: dot = 'k';
            break; // kilo
         case 6: dot = 'M';
            break; // Mega
         case 9: dot = 'G';
            break; // Giga
         default:
            dot = 0; // error
      }
      if (dot != 0) {
         *str++ = (unsigned char) dot;
      }
   } else {
      *str++ = 'E';
      if (dot < 0) {
         dot = -dot;
         *str++ = '-';
      }
      if (dot > 9) {
         *str++ = dot / 10 + '0';
         dot = dot % 10;
      }
      *str++ = dot + '0';
   }
   *str = 0;
}


/****************************************************************************
      PRINT FUNCTIONS
 ****************************************************************************/


/*
 * Print 48 bit integer in hex format
 */
void uart_dump48(uint48 n) {
   uart_puthex(n.byte[5]);
   uart_puthex(n.byte[4]);
   uart_puthex(n.byte[3]);
   uart_puthex(n.byte[2]);
   uart_puthex(n.byte[1]);
   uart_puthex(n.byte[0]);
}


/*
 * Send hexadecimal value of byte c
 */
void uart_puthex(unsigned char byte) {
   char bin2hex[] = "0123456789ABCDEF";
   uart_fputc(bin2hex[(byte >> 4) & 0x0F]);
   uart_fputc(bin2hex[byte & 0x0F]);
}


/*
 * Print 48 bit unsigned int
 * in decimal radix
 */
void print_u48(uint48 num) {
   ltoa48(str_buf, num);
   uart_fputs_ram(str_buf);
}


/*
 * Print 48 bit float to UART
 */
void print_f48(uint48 num, char resolution) {
   st48.numformat = FORMAT_SCIENTIFIC;
   num = ftod48(num); // Convert float to integer with decimal dot
   sprintf48(str_buf, resolution, num); // Convert integer with decimal dot to string number
   if (str_buf[0] > '5')
      sprintf48(str_buf, resolution - 1, num); // Convert integer with decimal dot to string number
   uart_fputs_ram(str_buf);
}


/*
 * Print 48 bit float to LCD
 */
void print_lcd_f48(uint48 num, char resolution) {
   st48.numformat = FORMAT_ENGINEERING;
   num = ftod48(num); // Convert float to integer with decimal dot
   sprintf48(str_buf, resolution, num); // Convert integer with decimal dot to string number
   if (str_buf[0] > '5')
      sprintf48(str_buf, resolution - 1, num); // Convert integer with decimal dot to string number
   lcd_puts_ram(str_buf);
}


/*
 * Print signed long integer
 */
void print_long(long n) {
   if (n < 0) {
      uart_fputc('-');
      n = -n;
   }
   ans.word[0] = n;
   ans.word[1] = n >> 16;
   ans.word[2] = 0;
   ltoa48(str_buf, ans);
   uart_fputs_ram(str_buf + 5);
}