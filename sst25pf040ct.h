#ifndef _SST25PF040CT_H
#define	_SST25PF040CT_H

#define OPCODE_RDID     0xAB
#define OPCODE_JEDECID  0x9F

uint8_t sst25_read_status_register(void);
uint8_t sst25_read_id(void);
void sst25_read_jedec(uint8_t*);


#endif	/* _SST25PF040CT_H */

