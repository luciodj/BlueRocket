/*
 * sensor_handling.c
 *
 */

#include "mcc_generated_files/mcc.h"
#include "util.h"
#include "sensor_handling.h"

//void i2c_prober(void)
//{
//	uint8_t data = 0;
//    uint8_t length = 1;
//    I2C2_MESSAGE_STATUS status = I2C2_MESSAGE_PENDING;
//
//    for (uint32_t probe_num = 0; probe_num < 0x7F; probe_num++) {
//
//        I2C2_MasterWrite(&data, length,(uint16_t) probe_num, &status);
//
//        // Wait until message is sent
//        while (I2C2_MESSAGE_PENDING == status) {}
//        __delay_ms(10);
//
//        if (I2C2_MESSAGE_COMPLETE == status ) {
//            print_printf("I2C device found at: ");
//            print_printf("address: 0x%2X\r\n", probe_num);
//        }
//    }
//}


void i2c_read_reg(uint16_t addr, uint8_t reg, uint8_t * buf, uint8_t len)
{
   i2c_readDataBlock(addr, reg, buf, len);
}


#define ECC_WA_RESET 0x00
#define ECC_WA_SLEEP 0x01
#define ECC_WA_IDLE  0x02
#define ECC_WA_CMD   0x03


void atecc_wakeup(uint8_t adr)
{
	//transfer_descriptor_t d = {data, size};
	while (!i2c_open(adr))
	; // sit here until we get the bus..

	i2c_setDataCompleteCallback(i2c_returnStop, NULL);

	// Transmit specified number of bytes
	i2c_setBuffer((void *)&adr, 1);
	// Start a Write operation
	i2c_masterWrite();
	while (I2C_BUSY == i2c_close())
	; // sit here until the entire chained operation has finished
}

void atecc508_sleep(uint16_t addr)
{
	uint8_t cmd_buf[1] = {ECC_WA_SLEEP};
//    I2C2_MESSAGE_STATUS status = I2C2_MESSAGE_PENDING;
//	I2C2_MasterWrite(&cmd_buf[0], 1, addr, &status);
    // Wait until message is sent
//    while (I2C2_MESSAGE_PENDING == status) {}
    i2c_writeNBytes(addr, cmd_buf, 1);
}

uint8_t atecc508_read_serial(uint16_t addr, uint8_t * serial)
{
    // Word Address, Count=7, Command=READ, Param1, Param2, Start Address=0x0000, CRC
	uint8_t cmd_buf[8] = {ECC_WA_CMD, 0x07, 0x02, 0x80, 0x00, 0x00, 0x09, 0xAD}; //Read 32 bytes of Config Zone

    atecc_wakeup(0);
    __delay_ms(10);

    i2c_writeNBytes(addr, cmd_buf, 8);
    __delay_ms(10);

    i2c_readNBytes(addr, serial, 35);

    return true;
}

uint8_t atecc508_read_slot(uint16_t addr, uint16_t slot, uint8_t * serial)
{
//    I2C2_MESSAGE_STATUS status = I2C2_MESSAGE_PENDING;

    // Word Address, Count=7, Command=READ, Param1, Param2, Start Address=0x0000, CRC
    uint8_t cmd_buf[8] = {ECC_WA_CMD, 0x07, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00}; //Read 64 bytes key from GenKey

    uint16_t crc = 0;
    for (uint8_t x = 1; x < 6; x++) {
        crc = crc16_update(crc, cmd_buf[x], 1);
    }
    cmd_buf[6] = (uint8_t) crc & 0xFF;
    cmd_buf[7] = (uint8_t) (crc >> 8) & 0xFF;

	atecc_wakeup(0);
    __delay_ms(10);

    i2c_writeNBytes(addr, cmd_buf, 8);
    __delay_ms(60);

    i2c_readNBytes(addr, serial, 67);
    return true;
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

