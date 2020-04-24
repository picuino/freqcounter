/*
    Declaration file for math48.c
 */

#ifndef MATH48_H
#define MATH48_H

/*
 *  Unsigned 48 bit integer type
 */
typedef union {
   unsigned char byte[6];
   unsigned int word[3];

   struct {
      unsigned int __word;
      unsigned long dword;
   };

   struct {
      unsigned char mantissa[5];
      unsigned long exp;
   };

   struct {
      unsigned b0 : 1; // LSB
      unsigned b1 : 1;
      unsigned b2 : 1;
      unsigned b3 : 1;
      unsigned b4 : 1;
      unsigned b5 : 1;
      unsigned b6 : 1;
      unsigned b7 : 1;
      unsigned b8 : 1;
      unsigned b9 : 1;
      unsigned b10 : 1;
      unsigned b11 : 1;
      unsigned b12 : 1;
      unsigned b13 : 1;
      unsigned b14 : 1;
      unsigned b15 : 1;
      unsigned b16 : 1;
      unsigned b17 : 1;
      unsigned b18 : 1;
      unsigned b19 : 1;
      unsigned b20 : 1;
      unsigned b21 : 1;
      unsigned b22 : 1;
      unsigned b23 : 1;
      unsigned b24 : 1;
      unsigned b25 : 1;
      unsigned b26 : 1;
      unsigned b27 : 1;
      unsigned b28 : 1;
      unsigned b29 : 1;
      unsigned b30 : 1;
      unsigned b31 : 1;
      unsigned b32 : 1;
      unsigned b33 : 1;
      unsigned b34 : 1;
      unsigned b35 : 1;
      unsigned b36 : 1;
      unsigned b37 : 1;
      unsigned b38 : 1;
      unsigned b39 : 1; // MSB=1  // MANTISSA SIGN
      unsigned b40 : 1;
      unsigned b41 : 1;
      unsigned b42 : 1;
      unsigned b43 : 1;
      unsigned b44 : 1;
      unsigned b45 : 1;
      unsigned b46 : 1;
      unsigned b47 : 1;
   };
} uint48, float48;

/*
 * Internal options
 */
typedef struct {
   unsigned char carry : 1;
   unsigned char overflow : 1;
   unsigned char numformat : 2;
} st48_t;

#define FORMAT_SCIENTIFIC    0
#define FORMAT_ENGINEERING   1
#define DEC_DIG_48          15
#define MANTISA_BITS        39



/*
 * Macros
 */
#define ILOAD48(u48, i) { u48.word[0]=(unsigned int)i&0xFFFF; u48.word[1]=(unsigned int)(i>>16)&0xFFFF; u48.word[2]=0; }
#define CLEAR48(u48) ILOAD48(u48, 0UL)


/*
 * Functions
 */
uint48 add48(uint48 a, uint48 b);
uint48 sub48(uint48 a, uint48 b);
signed char comp48(uint48 a, uint48 b);
uint48 fdiv48(uint48 a, uint48 b);
uint48 fmul48(uint48 a, uint48 b);
uint48 ftod48(uint48 n);
void head(char *str);
uint48 inc48(uint48 a);
uint48 itof48(uint48 a);
uint48 ftoi48(uint48 num);
unsigned char len(char *str);
void ltoa48(char *str, uint48 bin);
void round48(char *str, unsigned char n);
uint48 sl48(uint48 a);
void sprintf48(char *str, char digits, uint48 n);
uint48 sr48(uint48 a);


void print_f48(uint48 num, char resolution);
void print_lcd_f48(uint48 num, char resolution);
void print_u48(uint48 n);
void uart_dump48(uint48 n);
void uart_puthex(unsigned char byte);
void print_long(long n);

#endif