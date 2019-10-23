/*
 * i2c_wrapper.c
 *
 * Created: 05.02.2017 10:42:37
 *  Author: M43960
 */

#include "../mcc_generated_files/mcc.h"
#include "minion.h"
#include "i2c_wrapper.h"

// #define delay_ms(d) {__delay32((uint32_t) (((uint32_t) d)*(FCY/1000UL))); }

void delay_ms(uint16_t ms)
{
    for(uint16_t x=ms; x > 0; x--){
        for(uint16_t dly=2000; dly>0; dly--){
            NOP();
        }
    }
}


void i2c_prober(void) 
{
	uint8_t data = 0;
    uint8_t length = 1;
    I2C2_MESSAGE_STATUS status = I2C2_MESSAGE_PENDING;
   
    for (uint32_t probe_num = 0; probe_num < 0x7F; probe_num++) {
        
        I2C2_MasterWrite(&data, length,(uint16_t) probe_num, &status);
        
        // Wait until message is sent
        while (I2C2_MESSAGE_PENDING == status) {}
        delay_ms(10);
        
        if (I2C2_MESSAGE_COMPLETE == status ) {
            print_printf("I2C device found at: ");
            print_printf("address: 0x%2X\r\n", probe_num);
        }
    }
}

void i2c_read_reg(uint16_t addr, uint8_t * wbuf, uint8_t wcnt, uint8_t * rbuf, uint8_t rcnt)
{   
    I2C2_MESSAGE_STATUS status = I2C2_MESSAGE_PENDING; 

    I2C2_MasterWrite(wbuf, wcnt,(uint16_t) addr, &status);

    // Wait until message is sent
    while (I2C2_MESSAGE_PENDING == status) {}
    delay_ms(10);
    
	I2C2_MasterRead(rbuf, rcnt, addr, &status);

    // Wait until message is sent
    while (I2C2_MESSAGE_PENDING == status) {}
}

#define ECC_WA_RESET 0x00
#define ECC_WA_SLEEP 0x01
#define ECC_WA_IDLE  0x02
#define ECC_WA_CMD   0x03

void atecc508_sleep(uint16_t addr)
{
	uint8_t cmd_buf[1] = {ECC_WA_SLEEP};
    I2C2_MESSAGE_STATUS status = I2C2_MESSAGE_PENDING;
	I2C2_MasterWrite(&cmd_buf[0], 1, addr, &status);
    // Wait until message is sent
    while (I2C2_MESSAGE_PENDING == status) {}
}

uint8_t atecc508_read_serial(uint16_t addr, uint8_t * serial)
{
    I2C2_MESSAGE_STATUS status = I2C2_MESSAGE_PENDING; 

    // Word Address, Count=7, Command=READ, Param1, Param2, Start Address=0x0000, CRC
	uint8_t cmd_buf[8] = {ECC_WA_CMD, 0x07, 0x02, 0x80, 0x00, 0x00, 0x09, 0xAD}; //Read 32 bytes of Config Zone

	//Run a probe on the with address 0 to wake device with min 60us low
    I2C2_MasterWrite(0, 1, 0, &status);

    // Wait until message is sent
    while (I2C2_MESSAGE_PENDING == status) {}
    delay_ms(10);

	I2C2_MasterWrite(&cmd_buf[0], 8, addr, &status);
    while (I2C2_MESSAGE_PENDING == status) {
        // Wait until message is sent
    }

    if(I2C2_MESSAGE_COMPLETE != status)
        return status;
    delay_ms(10);

	I2C2_MasterRead(serial, 35, addr, &status);

    // Wait until message is sent
    while (I2C2_MESSAGE_PENDING == status) {}

    return status;
}

uint8_t atecc508_read_slot(uint16_t addr, uint16_t slot, uint8_t * serial)
{
    I2C2_MESSAGE_STATUS status = I2C2_MESSAGE_PENDING; 

    // Word Address, Count=7, Command=READ, Param1, Param2, Start Address=0x0000, CRC
    uint8_t cmd_buf[8] = {ECC_WA_CMD, 0x07, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00}; //Read 64 bytes key from GenKey

    uint16_t crc = 0;
    for (uint8_t x = 1; x < 6; x++) {
        crc = crc16_update(crc, cmd_buf[x], 1);
    }
    
    cmd_buf[6] = (uint8_t) crc & 0xFF;
    cmd_buf[7] = (uint8_t) (crc >> 8) & 0xFF;

	//Run a probe on the with address 0 to wake device with min 60us low
    I2C2_MasterWrite(0, 1, 0, &status);
    // Wait until message is sent
    while (I2C2_MESSAGE_PENDING == status) {}
    delay_ms(10);
    
    status = I2C2_MESSAGE_PENDING;
	I2C2_MasterWrite(&cmd_buf[0], 8, addr, &status);

    // Wait until message is sent
    while (I2C2_MESSAGE_PENDING == status) {}
    
    if(I2C2_MESSAGE_COMPLETE != status)
        return status;
    delay_ms(60);

	status = I2C2_MESSAGE_PENDING;
	I2C2_MasterRead(serial, 67, addr, &status);

    // Wait until message is sent
    while (I2C2_MESSAGE_PENDING == status) {}

    return status;
}


