/*
 * sensor_handling.c
 *
 */

#include "mcc_generated_files/mcc.h"
#include "util.h"
#include "sensor_handling.h"

void i2c_read_reg(uint16_t addr, uint8_t reg, uint8_t * rbuf, uint8_t rcnt)
{
    uint8_t reg_buf = reg;

    I2C2_MESSAGE_STATUS status = I2C2_MESSAGE_PENDING;
    I2C2_MasterWrite(&reg_buf, 1,(uint16_t) addr, &status);

    // Wait until message is sent
    while (I2C2_MESSAGE_PENDING == status) {}
    __delay_ms(10);

	I2C2_MasterRead(rbuf, rcnt, addr, &status);

    // Wait until message is sent
    while (I2C2_MESSAGE_PENDING == status) {}
}


uint16_t temp_read(uint8_t *buffer) {
// read temp in deg C
    i2c_read_reg(TEMP_SENS_I2C_ADDRESS, MCP9808_TEMP, buffer, 2);
    uint16_t uTemp = ((buffer[0] << 8) | buffer[1]) & 0x1fff;
    return uTemp;
}

void acc_read(uint8_t *buffer, uint16_t *out) {
    i2c_read_reg(ACCEL_SENS_I2C_ADDRESS, 2, buffer, 6);
    uint16_t *p = (uint16_t*)buffer;
    for(uint8_t i=0; i<3; i++){
        uint16_t temp_word = (buffer[i*2 + 1] << 4) | (buffer[i*2] >> 4);
//        *out++ = ((temp_word >> 8 & 0xff)) | (temp_word << 8);
        *out++ = temp_word;
    }
}

