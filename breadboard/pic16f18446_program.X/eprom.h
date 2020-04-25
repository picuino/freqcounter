/*
    Declaration file for eprom.c
 */

#ifndef EPROM_H
#define EPROM_H

/*
 *  Unsigned 32 bit integer
 */
typedef union {
   unsigned long dword;
   unsigned char byte[4];
   unsigned int word[2];

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
   };
} uint32;


void eeprom_unlock(void);
unsigned int eprom_read(unsigned int addr);
void eprom_delete(unsigned int addr);
void eprom_write(unsigned int addr, unsigned int data);
void eprom_flush(void);
void eprom_addr(unsigned int addr);

unsigned long eprom_read32(unsigned int addr);
unsigned int eprom_read16(unsigned int addr);
void eprom_write32(unsigned int addr, unsigned long data);
void eprom_write16(unsigned int addr, unsigned int data);

#endif


