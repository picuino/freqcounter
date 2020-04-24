/*
 * Command Line Interpreter
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
#include "command.h"
#include "uart.h"
#include "math48.h"
#include "counter.h"
#include "eprom.h"
#include "peripheral.h"
#include "calibration.h"


extern options_t options;
extern calibration_t calibration;
extern char uart_rx_buffer[];
extern volatile unsigned char uart_newline;
extern char counter_reset_inputs;
unsigned char cmd_ptr, cmd_newline, cmd_token;
long cmd_number;


/*
 * Inits command section
 */
void cmd_init() {
   cmd_ptr = 0;
   cmd_newline = 0;
   cmd_token = 0;
}


/*
 * Get first token from UART buffer
 */
void cmd_get_token(void) {
   unsigned char c;

   cmd_token = 0;
   if (cmd_newline) {
      return;
   }

   // Delete initial spaces
   while (uart_rx_buffer[0] == ' ') {
      uart_free(1);
   }

   cmd_newline = 0;
   cmd_ptr = 0;
   while (1) {
      c = uart_rx_buffer[cmd_ptr++];
      if (c == ' ' || c == '\t' ||
              c == '\n' || c == '\r') {
         if (c == '\n')
            cmd_newline = 1;
         uart_rx_buffer[cmd_ptr - 1] = 0;
         cmd_token = 1;
         return;
      }
   }
}


/*
 * Compares uart_buffer with string
 * return 1 if match
 */
char cmd_str_cmp(const char *str) {
   char *p;

   if (cmd_token == 0)
      return 0;
   p = uart_rx_buffer;
   while (1) {
      if (*p++ != *str++)
         return 0;
      if (*p == 0 && *str == 0)
         return 1;
      if (*p == 0 || *str == 0)
         return 0;
   }
   return 0;
}


/*
 * Delete first token in buffer
 */
void cmd_delete_token(void) {
   uart_free(cmd_ptr);
   cmd_ptr = 0;
}


/*
 * Read long number from buffer
 */
void cmd_get_number(void) {
   char sign, c;

   cmd_number = 0;
   if (cmd_newline)
      return;

   sign = 0;
   c = uart_rx_buffer[cmd_ptr++];
   if (c == '-') {
      sign = -1;
      c = uart_rx_buffer[cmd_ptr++];
   }

   while (1) {
      if (c >= '0' && c <= '9') {
         cmd_number *= 10;
         cmd_number += (c - '0');
      } else break;
      c = uart_rx_buffer[cmd_ptr++];
   }
   if (sign == (char) - 1)
      cmd_number = -cmd_number;
   cmd_ptr--;
}


/*
 * Read token "on" or token "off"
 * and return 1, 0 or previous value.
 */
char cmd_read_on_off(char old_value) {
   cmd_delete_token();
   cmd_get_token();
   if (cmd_str_cmp("on")) {
      return 1;
   }
   if (cmd_str_cmp("off")) {
      return 0;
   }
   return old_value;
}


void cmd_print_on_off(char value) {
   if (value == 0)
      uart_fputs("OFF\n");
   else
      uart_fputs("ON\n");
}


long cmd_get_calibration(void) {
   if (options.system_clk_mhz == 8)
      return calibration.calibration_8mhz;
   else
      return calibration.calibration_5mhz;
}


long cmd_get_calibration_eprom(void) {
   if (options.system_clk_mhz == 8)
      return eprom_read32(SAF_ADDRESS);
   else
      return eprom_read32(SAF_ADDRESS + 8);
}


void cmd_set_calibration(void) {
   if (options.system_clk_mhz == 8) {
      calibration.calibration_8mhz = cmd_number;
   } else {
      calibration.calibration_5mhz = cmd_number;
   }
}


/*
 * Calibration subcommands
 */
void cmd_calibration(void) {
   cmd_delete_token();
   cmd_get_token();
   if (cmd_str_cmp("read")) {
      uart_fputs(">Calibration (RAM)=\t");
      print_long(cmd_get_calibration());
      uart_fputs("\tPPB\n");
      uart_fputs(">Calibration (EPROM)=\t");
      print_long(cmd_get_calibration_eprom());
      uart_fputs("\tPPB\n");
   } else if (cmd_str_cmp("save")) {
      calibration_eprom_write();
      uart_fputs(">Calibration (EPROM)=\t");
      print_long(cmd_get_calibration_eprom());
      uart_fputs("\tPPB\n");
   } else if (cmd_str_cmp("write")) {
      cmd_delete_token();
      cmd_get_number();
      uart_fputs(">Old Calibration (RAM)=\t");
      print_long(cmd_get_calibration());
      cmd_set_calibration();
      uart_fputs("\n>New Calibration (RAM)=\t");
      print_long(cmd_get_calibration());
      uart_fputs("\n");
   } else if (cmd_str_cmp("auto")) {
      options.autocalibrate = cmd_read_on_off(options.autocalibrate);
      uart_fputs(">Autocalibration=\t");
      cmd_print_on_off(options.autocalibrate);
   } else {
      cmd_unknown();
   }
}


/*
 * Reset frequency counter options
 */
void cmd_reset(void) {
   counter_options_init();
   counter_reset_inputs = 1;
}


/*
 * Manage outputs
 */
void cmd_output(void) {
   cmd_delete_token();
   cmd_get_token();

   if (cmd_str_cmp("pulses")) {
      options.print_pulses = cmd_read_on_off(options.print_pulses);
      uart_fputs(">Print pulses=\t");
      cmd_print_on_off(options.print_pulses);
   } else if (cmd_str_cmp("time")) {
      options.print_time = cmd_read_on_off(options.print_time);
      uart_fputs(">Print time=\t");
      cmd_print_on_off(options.print_time);
   } else if (cmd_str_cmp("longfreq")) {
      options.print_long_frequency = cmd_read_on_off(options.print_long_frequency);
      uart_fputs(">Print long frequency=\t");
      cmd_print_on_off(options.print_long_frequency);
   } else if (cmd_str_cmp("period")) {
      options.print_period = cmd_read_on_off(options.print_period);
      uart_fputs(">Print period=\t");
      cmd_print_on_off(options.print_period);
   } else if (cmd_str_cmp("phase")) {
      options.print_phase = cmd_read_on_off(options.print_phase);
      uart_fputs(">Print phase=\t");
      cmd_print_on_off(options.print_phase);
   } else {
      cmd_unknown();
   }
}


/*
 * Manage inputs
 */
void cmd_input(void) {
   cmd_delete_token();
   cmd_get_token();

   if (cmd_str_cmp("ch")) {
      cmd_delete_token();
      cmd_get_token();
      if (cmd_str_cmp("A")) {
         if (options.input_a == 0) {
            counter_reset_inputs = 1;
         }
         options.input_a = 1;
         options.input_b = 0;
      } else if (cmd_str_cmp("B")) {
         if (options.input_b == 0) {
            counter_reset_inputs = 1;
         }
         options.input_a = 0;
         options.input_b = 1;
      } else if (cmd_str_cmp("AB")) {
         if (options.input_a == 0) {
            counter_reset_inputs = 1;
         }
         if (options.input_b == 0) {
            counter_reset_inputs = 1;
         }
         options.input_a = 1;
         options.input_b = 1;
      }
      uart_fputs(">Active Inputs=\t");
      if (options.input_a) uart_fputc('A');
      if (options.input_b) uart_fputc('B');
      uart_fputs("\n");
      uart_fputs(">Prescaler A=\t");
      uart_fputc(options.prescaler_a + '0');
      uart_fputs("\tB=\t");
      uart_fputc(options.prescaler_b + '0');
      uart_fputs("\n");
   } else if (cmd_str_cmp("fast")) {
      options.fast_measure = cmd_read_on_off(options.fast_measure);
      uart_fputs(">Fast measure=\t");
      cmd_print_on_off(options.fast_measure);
      counter_reset_inputs = 1;
   } else if (cmd_str_cmp("ctmu")) {
      options.ctmu_enable = cmd_read_on_off(options.ctmu_enable);
      uart_fputs(">CTMU measure=\t");
      cmd_print_on_off(options.ctmu_enable);
      counter_reset_inputs = 1;
   } else if (cmd_str_cmp("zcd")) {
      options.input_zcd = cmd_read_on_off(options.input_zcd);
      uart_fputs(">Input Zero Cross Detection=\t");
      cmd_print_on_off(options.input_zcd);
      clc_input_a_zcd();
   } else {
      cmd_unknown();
   }
}


/*
 * Show firmware version
 */
void cmd_version(void) {
   uart_fputs(">Version=\t");
   uart_fputs(COUNTER_VERSION);
   uart_fputs("\n");
}


/*
 * Show "Unknown command" message
 */
void cmd_unknown(void) {
   uart_fputs(">Unknown command: ");
   uart_fputs_ram(uart_rx_buffer);
   uart_fputs("\n");
}


/*
 * Delete all characters until newline '\n'
 */
void delete_line(void) {
   if (cmd_newline == 0) {
      while (uart_rx_buffer[cmd_ptr++] != '\n');
   }
   cmd_delete_token();
   cmd_newline = 0;
   uart_newline--;
}


/*
 * Main loop of Command Line Interface
 */
void cmd_loop(void) {
   if (uart_newline == 0)
      return;

   // Get first token and parse it
   cmd_get_token();
   if (cmd_str_cmp("version")) {
      cmd_version();
   } else if (cmd_str_cmp("cal")) {
      cmd_calibration();
   } else if (cmd_str_cmp("input")) {
      cmd_input();
   } else if (cmd_str_cmp("output")) {
      cmd_output();
   } else if (cmd_str_cmp("reset")) {
      cmd_reset();
   } else {
      cmd_unknown();
   }
   delete_line();
}
