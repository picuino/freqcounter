/*
 * Internal EEPROM manage routines
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
#include "uart.h"
#include "math48.h"
#include "eprom.h"


/*
 * Unlock sequence of Flash eeprom
 */
void eeprom_unlock(void) {
   unsigned char stat;

   // Unlock sequence          (Chapter 13)
   // With interrupts disabled.
   stat = INTCON;
   INTCONbits.GIE = 0;
   NVMCON2 = 0x55;
   NVMCON2 = 0xAA;
   NVMCON1bits.WR = 1;
   NOP();
   NOP();
   INTCON = stat;
}


/*
 * Read flash eeprom address
 */
unsigned int eprom_read(unsigned int addr) {
   eprom_addr(addr);
   NVMCON1bits.RD = 1; // Init read operation
   return NVMDAT;
}


/*
 * Return low byte of 4 memory positions concatenated
 */
unsigned long eprom_read32(unsigned int addr) {
   uint32 num;
   num.byte[0] = eprom_read(addr++);
   num.byte[1] = eprom_read(addr++);
   num.byte[2] = eprom_read(addr++);
   num.byte[3] = eprom_read(addr);
   return num.dword;
}


/*
 * Return low byte of 2 memory positions concatenated
 */
unsigned int eprom_read16(unsigned int addr) {
   uint32 num;
   num.byte[0] = eprom_read(addr++);
   num.byte[1] = eprom_read(addr);
   return num.word[0];
}


/*
 * Write 4 bytes of data in 4 consecutive Flash words
 */
void eprom_write32(unsigned int addr, unsigned long data) {
   eprom_write(addr++, data);
   eprom_write(addr++, data>>8);
   eprom_write(addr++, data>>16);
   eprom_write(addr, data>>24);
}



/*
 * Write 4 bytes of data in 4 consecutive Flash words
 */
void eprom_write16(unsigned int addr, unsigned int data) {
   eprom_write(addr++, data);
   eprom_write(addr, data>>8);
}


/*
 * Clear 32 words of Flash memory begining in address addr
 */
void eprom_delete(unsigned int addr) {
   eprom_addr(addr); // Select word address

   // Clear memory row (32 words)
   NVMCON1bits.FREE = 1; // Select erase operation
   NVMCON1bits.WREN = 1; // Enable writes
   eeprom_unlock();
   NVMCON1bits.FREE = 0; // Deselect erase operation
   NVMCON1bits.WREN = 0; // Disable writes
}


/*
 * Write data word to flash memory buffer
 */
void eprom_write(unsigned int addr, unsigned int data) {
   NVMCON1bits.WREN = 1;
   NVMCON1bits.NVMREGS = 0;
   NVMCON1bits.LWLO = 1; // Write data to buffer
   eprom_addr(addr);
   NVMDAT = data; // Write data to buffer row
   eeprom_unlock();
}


/*
 * Write Flash buffer to Flash memory
 */
void eprom_flush(void) {
   // Write buffer row to memory (32 words in PIC 16F15xxx/16F18xxx )
   NVMCON1bits.LWLO = 0;
   eeprom_unlock();
}


/*
 * Select memory address
 */
void eprom_addr(unsigned int addr) {
   // Select memory type
   if (addr & 0x8000)
      NVMCON1bits.NVMREGS = 1; // 1 = config memory
   else
      NVMCON1bits.NVMREGS = 0; // 0 = program memory
   addr &= 0x7FFF;

   // Select Word Memory address
   NVMADR = addr;
}


/*
 * Dumps memory content
 */
void dump_mem(void) {
   unsigned int i, col, data;
   for (i = 0; i < 0x8000; i += 16) {
      uart_puthex(i >> 8);
      uart_puthex(i);
      uart_fputc(' ');
      for (col = 0; col < 16; col++) {
         data = eprom_read(i + col);
         uart_puthex(data >> 8);
         uart_puthex(data);
      }
      uart_fputs("\n");
   }
}
