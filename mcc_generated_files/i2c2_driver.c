/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>
#include "device_config.h"
#include "i2c2_driver.h"

#pragma warning disable 520        

inline void i2c2_driver_close(void)
{
    SSP2CON1bits.SSPEN = 0;
}

/* Interrupt Control */
inline void mssp2_enableIRQ(void)
{
    PIE3bits.SSP2IE = 1;
}

inline __bit mssp2_IRQisEnabled(void)
{
    return PIE3bits.SSP2IE;
}

inline void mssp2_disableIRQ(void)
{
    PIE3bits.SSP2IE = 0;
}

inline void mssp2_clearIRQ(void)
{
    PIR3bits.SSP2IF = 0;
}

inline void mssp2_setIRQ(void)
{
    PIR3bits.SSP2IF = 1;
}

inline __bit mssp2_IRQisSet(void)
{
    return PIR3bits.SSP2IF;
}

inline void mssp2_waitForEvent(uint16_t *timeout)
{
    //uint16_t to = (timeout!=NULL)?*timeout:100;
    //to <<= 8;

    if(PIR3bits.SSP2IF == 0)
    {
        while(1)// to--)
        {
            if(PIR3bits.SSP2IF) break;
            __delay_us(100);
        }
    }
}

__bit i2c2_driver_open(void)
{
    if(!SSP2CON1bits.SSPEN)
    {
        SSP2STAT = 0x00;
        SSP2CON1 = 0x28;
        SSP2CON2 = 0x00;
        SSP2ADD = 0x4f;
        return true;
    }
    else
        return false;
}

__bit i2c2_driver_initSlaveHardware(void)
{
    if(!SSP2CON1bits.SSPEN)
    {
/* NOTE on AHEN:
 * If multiple slaves are to be emulated, then AHEN must be set.  It must be set
 * because the driver needs to selectively ACK/NACK the address depending on its
 * ability to handle the address.
*/

/* NOTE on DHEN:
 * DHEN must be set so that the data is not automatically NACK'ed if it is not read
 * from the SSPBUF.  This driver will ALWAYS read the SSPBUF so that it can pass
 * the value to the appropriate slave handler.  Because the data is ALWAYS read
 * the data will always be ACK'd if DHEN is cleared.  If the slave does not want
 * the data byte from the master then it will return false and a NACK will be returned.
 */

/* NOTE on SEN:
 * SEN will be set enabling clock stretching.  This is because we don't know how
 * long the user will take to process data bytes in their callbacks.  If they are fast,
 * we may not need to stretch the clock.  If they are slow, we need to stretch the clock.
 * If we ALWAYS stretch the clock, we will release the clock when the ISR is complete.
 */

/* NOTE on PCIE:
 * PCIE will be set to enable interrupts on STOP.  This will allow us know when
 * the master is finished
 */
        
/* NOTE on SCIE:
 * SCIE will be set to enable interrupts on START.  This will allow us to detect
 * both a START and a RESTART event and prepare to restart communications.
 */
        SSP2CON1 |= 0x06; //setup I2C Slave (7-bit Addressing)
        SSP2STAT = 0x00;
        SSP2CON2 = 0x00;
        
        SSP2CON1bits.SSPEN = 1;
        return true;
    }
    return false;
}

inline void i2c2_driver_resetBus(void)
{
    
}

inline void i2c2_driver_start(void)
{
    SSP2CON2bits.SEN = 1;
}

inline void i2c2_driver_restart(void)
{
    SSP2CON2bits.RSEN = 1;
}

inline void i2c2_driver_stop(void)
{
    SSP2CON2bits.PEN = 1;
}

inline __bit i2c2_driver_isNACK(void)
{
    return SSP2CON2bits.ACKSTAT;
}

inline void i2c2_driver_startRX(void)
{
    SSP2CON2bits.RCEN = 1;
}

inline char i2c2_driver_getRXData(void)
{
    return SSP2BUF;
}

inline void i2c2_driver_setAddr(char addr)
{
    SSP2ADD = addr;
}

inline void i2c2_driver_setMask(char mask)
{
    SSP2MSK = mask;
}

inline void i2c2_driver_TXData(char d)
{
    SSP2BUF = d;
}

inline char i2c2_driver_getAddr(void)
{
    return SSP2ADD;
}

inline void i2c2_driver_sendACK(void)
{
    SSP2CON2bits.ACKDT = 0;
    SSP2CON2bits.ACKEN = 1; // start the ACK/NACK
}

inline void i2c2_driver_sendNACK(void)
{
    SSP2CON2bits.ACKDT = 1;
    SSP2CON2bits.ACKEN = 1; // start the ACK/NACK
}

inline void i2c2_driver_releaseClock(void)
{
    SSP2CON1bits.CKP = 1;
}

inline __bit i2c2_driver_isBufferFull(void)
{
    return SSP2STATbits.BF;
}

inline __bit i2c2_driver_isStart(void)
{
    return SSP2STATbits.S;
}

inline __bit i2c2_driver_isAddress(void)
{
    return !SSP2STATbits.D_nA;
}

inline __bit i2c2_driver_isStop(void)
{
    return SSP2STATbits.P;
}

inline __bit i2c2_driver_isData(void)
{
    return SSP2STATbits.D_nA;
}

inline __bit i2c2_driver_isRead(void)
{
    return SSP2STATbits.R_nW;
}

inline __bit i2c2_driver_isWriteCollision(void)
{
    return SSP2CON1bits.WCOL;
}

inline __bit i2c2_driver_isReceiveOverflow(void)
{
    return SSP2CON1bits.SSPOV;
}

inline void i2c2_driver_clearBusCollision(void)
{
    PIR3bits.BCL2IF = 0; // clear the bus collision.
}

inline void i2c2_driver_setBusCollisionISR(interruptHandler handler){
    i2c2_driver_busCollisionISR = handler;
}

inline void i2c2_driver_setI2cISR(interruptHandler handler){
    i2c2_driver_i2cISR = handler;
}
