/*
 * sensor_handling.h
 *
*/

#ifndef SENSOR_HANDLING_H_
#define SENSOR_HANDLING_H_

#include "sst25pf040ct.h"

#define TEMP_SENS_I2C_ADDRESS     0x18
#define ACCEL_SENS_I2C_ADDRESS    0x19
#define ECC608_I2C_ADDRESS        0x58

// MCP9808 register defines
#define MCP9808_RFU         0
#define MCP9808_CONFIG      1
#define MCP9808_TUPPER      2
#define MCP9808_TLOWER      3
#define MCP9808_TCRIT       4
#define MCP9808_TEMP        5
#define MCP9808_MAN         6
#define MCP9808_DEVICE      7
#define MCP9808_RESOLUTION  8
#define MCP9808_RESERVED    9


uint8_t atecc508_read_serial(uint16_t addr, uint8_t * serial);
uint8_t atecc508_read_slot(uint16_t addr, uint16_t slot, uint8_t * serial);
void atecc508_sleep(uint16_t addr);
void i2c_prober(void);
void delay_ms(uint16_t ms);
void i2c_read_reg(uint16_t addr, uint8_t reg, uint8_t * buf, uint8_t len);

uint16_t temp_read(uint8_t * buffer);
void acc_read(uint8_t* buffer, uint16_t* xyz);

#endif /* SENSOR_HANDLING_H_ */