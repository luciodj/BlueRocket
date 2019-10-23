/*
 * File:   sst25pf040ct.c
 * Author: M43896
 *
 * Created on September 12, 2019, 2:19 PM
 */
#include "mcc_generated_files/mcc.h"

#include "sst25pf040ct.h"

uint8_t sst25_read_id(void){
    uint8_t id = 0;
    SST25_CS_SetLow();
    SPI1_Exchange8bit(OPCODE_RDID);
    SPI1_Exchange8bit(0x00);
    SPI1_Exchange8bit(0x00);
    SPI1_Exchange8bit(0x00);
    id = SPI1_Exchange8bit(0xFF);
    SST25_CS_SetHigh();
    return id;
}

void sst25_read_jedec(uint8_t *data){
    SST25_CS_SetLow();
    SPI1_Exchange8bit(OPCODE_JEDECID);
    data[0] = SPI1_Exchange8bit(0xFF);
    data[1] = SPI1_Exchange8bit(0xFF);
    data[2] = SPI1_Exchange8bit(0xFF);
    data[3] = SPI1_Exchange8bit(0xFF);
    SST25_CS_SetHigh();
}