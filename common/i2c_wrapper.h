/*
 * i2c_wrapper.h
 *
 * Created: 05.02.2017 10:42:48
 *  Author: M43960
 */

#ifndef I2C_WRAPPER_H_
#define I2C_WRAPPER_H_

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
void i2c_read_reg(uint16_t addr, uint8_t * wbuf, uint8_t wcnt, uint8_t * rbuf, uint8_t rcnt);
void i2c_prober(void);
void delay_ms(uint16_t ms);

#endif /* I2C_WRAPPER_H_ */