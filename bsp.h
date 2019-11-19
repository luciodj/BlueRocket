/*
 * bsp.h
 *
 */

#ifndef BSP_H
#define	BSP_H

#include "mcc_generated_files/mcc.h"

bool SW0_get(void);

void LED0_set(uint8_t v);    // GREEN - DATA
uint8_t LED0_get(void);      // GREEN - DATA

#endif	/* BSP_H */

