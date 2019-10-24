/*
 * cnano_minion.h
 *
 * Created: 19.08.2016 13:43:57
 *  Author: M43960
 */ 



#ifndef CNANO_MINION_H_
#define CNANO_MINION_H_

#include <stdint.h>
#include <stdarg.h>

typedef void (*putc_callback)(uint8_t data);

uint16_t crc16_update(uint16_t crc, uint8_t a, uint8_t reverse);
uint8_t crc7_update(uint8_t crc, uint8_t a, uint8_t reverse);
void print_printf(char * stream, ...);
void print_char(uint8_t byte);
void print_array_as_hex(uint8_t* uc_data, uint32_t len, uint8_t size);
void print_array_as_uint(uint8_t* uc_data, uint32_t len, uint8_t size);
void print_stdout(putc_callback func);
void base64(uint8_t * output_buf, uint8_t * input_buf, uint8_t size);

#endif /* CNANO_MINION_H_ */