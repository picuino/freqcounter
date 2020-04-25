/*
    Declaration file for command.c
 */

#ifndef COMMAND_H
#define COMMAND_H

void cmd_init(void);
void cmd_get_token(void);
char cmd_str_cmp(const char *str);
void cmd_delete_token(void);
void cmd_get_number(void);
void cmd_calibration(void);
void cmd_version(void);
void cmd_unknown(void);
void delete_line(void);
void cmd_loop(void);
char cmd_read_on_off(char old_value);
void cmd_input(void);
void cmd_reset(void);
void cmd_output(void);

long cmd_get_calibration(void);
long cmd_get_calibration_eprom(void);
void cmd_set_calibration(void);

#endif


