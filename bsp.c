/*
 * bsp.c
 *
 *
 */

#include "bsp.h"

bool SW0_get(void)
{
    return (SW0_PORT);
}

void LED0_set(uint8_t v)
{
    LED_0_LAT = 1 - v;
}

uint8_t LED0_get(void)
{
    return 1 - LED_0_PORT;
}
