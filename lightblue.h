
#ifndef LIGHTBLUE_H
#define LIGHTBLUE_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/drivers/uart.h"

bool get_command(char, char*);
void blue_acc(void);
void blue_temp(void);
void blue_leds(void);
void blue_button(void);
void blue_version(uint8_t);
void blue_parse(char);
void blue_serial(char*);
void LED1_update(void);

#endif // LIGHTBLUE_H