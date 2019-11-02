
#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/drivers/uart.h"
#include "util.h"

void command_handler(char *);
bool get_command(char, char*);
void blue_acc(void);
void blue_temp(void);
void blue_leds(void);
void blue_button(void);
void blue_version(uint8_t);

#endif /* COMMAND_HANDLER_H */