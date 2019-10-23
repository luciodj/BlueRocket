/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC16LF18456
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.05 and above
        MPLAB 	          :  MPLAB X 5.20	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set BT_RST aliases
#define BT_RST_TRIS                 TRISAbits.TRISA0
#define BT_RST_LAT                  LATAbits.LATA0
#define BT_RST_PORT                 PORTAbits.RA0
#define BT_RST_WPU                  WPUAbits.WPUA0
#define BT_RST_OD                   ODCONAbits.ODCA0
#define BT_RST_ANS                  ANSELAbits.ANSA0
#define BT_RST_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define BT_RST_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define BT_RST_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define BT_RST_GetValue()           PORTAbits.RA0
#define BT_RST_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define BT_RST_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define BT_RST_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define BT_RST_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define BT_RST_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define BT_RST_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define BT_RST_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define BT_RST_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set MBUS_RST aliases
#define MBUS_RST_TRIS                 TRISAbits.TRISA3
#define MBUS_RST_LAT                  LATAbits.LATA3
#define MBUS_RST_PORT                 PORTAbits.RA3
#define MBUS_RST_WPU                  WPUAbits.WPUA3
#define MBUS_RST_OD                   ODCONAbits.ODCA3
#define MBUS_RST_ANS                  ANSELAbits.ANSA3
#define MBUS_RST_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define MBUS_RST_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define MBUS_RST_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define MBUS_RST_GetValue()           PORTAbits.RA3
#define MBUS_RST_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define MBUS_RST_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define MBUS_RST_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define MBUS_RST_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define MBUS_RST_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define MBUS_RST_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define MBUS_RST_SetAnalogMode()      do { ANSELAbits.ANSA3 = 1; } while(0)
#define MBUS_RST_SetDigitalMode()     do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set LED_0 aliases
#define LED_0_TRIS                 TRISAbits.TRISA5
#define LED_0_LAT                  LATAbits.LATA5
#define LED_0_PORT                 PORTAbits.RA5
#define LED_0_WPU                  WPUAbits.WPUA5
#define LED_0_OD                   ODCONAbits.ODCA5
#define LED_0_ANS                  ANSELAbits.ANSA5
#define LED_0_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define LED_0_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define LED_0_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define LED_0_GetValue()           PORTAbits.RA5
#define LED_0_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define LED_0_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define LED_0_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define LED_0_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define LED_0_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define LED_0_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define LED_0_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define LED_0_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set ACCEL_INT aliases
#define ACCEL_INT_TRIS                 TRISAbits.TRISA6
#define ACCEL_INT_LAT                  LATAbits.LATA6
#define ACCEL_INT_PORT                 PORTAbits.RA6
#define ACCEL_INT_WPU                  WPUAbits.WPUA6
#define ACCEL_INT_OD                   ODCONAbits.ODCA6
#define ACCEL_INT_ANS                  ANSELAbits.ANSA6
#define ACCEL_INT_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define ACCEL_INT_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define ACCEL_INT_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define ACCEL_INT_GetValue()           PORTAbits.RA6
#define ACCEL_INT_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define ACCEL_INT_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define ACCEL_INT_SetPullup()          do { WPUAbits.WPUA6 = 1; } while(0)
#define ACCEL_INT_ResetPullup()        do { WPUAbits.WPUA6 = 0; } while(0)
#define ACCEL_INT_SetPushPull()        do { ODCONAbits.ODCA6 = 0; } while(0)
#define ACCEL_INT_SetOpenDrain()       do { ODCONAbits.ODCA6 = 1; } while(0)
#define ACCEL_INT_SetAnalogMode()      do { ANSELAbits.ANSA6 = 1; } while(0)
#define ACCEL_INT_SetDigitalMode()     do { ANSELAbits.ANSA6 = 0; } while(0)

// get/set SW0 aliases
#define SW0_TRIS                 TRISAbits.TRISA7
#define SW0_LAT                  LATAbits.LATA7
#define SW0_PORT                 PORTAbits.RA7
#define SW0_WPU                  WPUAbits.WPUA7
#define SW0_OD                   ODCONAbits.ODCA7
#define SW0_ANS                  ANSELAbits.ANSA7
#define SW0_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define SW0_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define SW0_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define SW0_GetValue()           PORTAbits.RA7
#define SW0_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define SW0_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define SW0_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define SW0_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define SW0_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define SW0_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define SW0_SetAnalogMode()      do { ANSELAbits.ANSA7 = 1; } while(0)
#define SW0_SetDigitalMode()     do { ANSELAbits.ANSA7 = 0; } while(0)

// get/set SCL2 aliases
#define SCL2_TRIS                 TRISBbits.TRISB1
#define SCL2_LAT                  LATBbits.LATB1
#define SCL2_PORT                 PORTBbits.RB1
#define SCL2_WPU                  WPUBbits.WPUB1
#define SCL2_OD                   ODCONBbits.ODCB1
#define SCL2_ANS                  ANSELBbits.ANSB1
#define SCL2_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define SCL2_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define SCL2_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define SCL2_GetValue()           PORTBbits.RB1
#define SCL2_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define SCL2_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define SCL2_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define SCL2_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define SCL2_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define SCL2_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define SCL2_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define SCL2_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set SDA2 aliases
#define SDA2_TRIS                 TRISBbits.TRISB2
#define SDA2_LAT                  LATBbits.LATB2
#define SDA2_PORT                 PORTBbits.RB2
#define SDA2_WPU                  WPUBbits.WPUB2
#define SDA2_OD                   ODCONBbits.ODCB2
#define SDA2_ANS                  ANSELBbits.ANSB2
#define SDA2_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define SDA2_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define SDA2_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define SDA2_GetValue()           PORTBbits.RB2
#define SDA2_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define SDA2_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define SDA2_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define SDA2_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define SDA2_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define SDA2_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define SDA2_SetAnalogMode()      do { ANSELBbits.ANSB2 = 1; } while(0)
#define SDA2_SetDigitalMode()     do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set RB4 procedures
#define RB4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define RB4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define RB4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define RB4_GetValue()              PORTBbits.RB4
#define RB4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define RB4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define RB4_SetPullup()             do { WPUBbits.WPUB4 = 1; } while(0)
#define RB4_ResetPullup()           do { WPUBbits.WPUB4 = 0; } while(0)
#define RB4_SetAnalogMode()         do { ANSELBbits.ANSB4 = 1; } while(0)
#define RB4_SetDigitalMode()        do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set RB5 procedures
#define RB5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define RB5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define RB5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RB5_GetValue()              PORTBbits.RB5
#define RB5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define RB5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define RB5_SetPullup()             do { WPUBbits.WPUB5 = 1; } while(0)
#define RB5_ResetPullup()           do { WPUBbits.WPUB5 = 0; } while(0)
#define RB5_SetAnalogMode()         do { ANSELBbits.ANSB5 = 1; } while(0)
#define RB5_SetDigitalMode()        do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set ICSPCLK aliases
#define ICSPCLK_TRIS                 TRISBbits.TRISB6
#define ICSPCLK_LAT                  LATBbits.LATB6
#define ICSPCLK_PORT                 PORTBbits.RB6
#define ICSPCLK_WPU                  WPUBbits.WPUB6
#define ICSPCLK_OD                   ODCONBbits.ODCB6
#define ICSPCLK_ANS                  ANSELBbits.ANSB6
#define ICSPCLK_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define ICSPCLK_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define ICSPCLK_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define ICSPCLK_GetValue()           PORTBbits.RB6
#define ICSPCLK_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define ICSPCLK_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define ICSPCLK_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define ICSPCLK_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define ICSPCLK_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define ICSPCLK_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define ICSPCLK_SetAnalogMode()      do { ANSELBbits.ANSB6 = 1; } while(0)
#define ICSPCLK_SetDigitalMode()     do { ANSELBbits.ANSB6 = 0; } while(0)

// get/set ICSPDAT aliases
#define ICSPDAT_TRIS                 TRISBbits.TRISB7
#define ICSPDAT_LAT                  LATBbits.LATB7
#define ICSPDAT_PORT                 PORTBbits.RB7
#define ICSPDAT_WPU                  WPUBbits.WPUB7
#define ICSPDAT_OD                   ODCONBbits.ODCB7
#define ICSPDAT_ANS                  ANSELBbits.ANSB7
#define ICSPDAT_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define ICSPDAT_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define ICSPDAT_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define ICSPDAT_GetValue()           PORTBbits.RB7
#define ICSPDAT_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define ICSPDAT_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define ICSPDAT_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define ICSPDAT_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)
#define ICSPDAT_SetPushPull()        do { ODCONBbits.ODCB7 = 0; } while(0)
#define ICSPDAT_SetOpenDrain()       do { ODCONBbits.ODCB7 = 1; } while(0)
#define ICSPDAT_SetAnalogMode()      do { ANSELBbits.ANSB7 = 1; } while(0)
#define ICSPDAT_SetDigitalMode()     do { ANSELBbits.ANSB7 = 0; } while(0)

// get/set SPI1_CS aliases
#define SPI1_CS_TRIS                 TRISCbits.TRISC0
#define SPI1_CS_LAT                  LATCbits.LATC0
#define SPI1_CS_PORT                 PORTCbits.RC0
#define SPI1_CS_WPU                  WPUCbits.WPUC0
#define SPI1_CS_OD                   ODCONCbits.ODCC0
#define SPI1_CS_ANS                  ANSELCbits.ANSC0
#define SPI1_CS_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define SPI1_CS_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define SPI1_CS_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define SPI1_CS_GetValue()           PORTCbits.RC0
#define SPI1_CS_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define SPI1_CS_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define SPI1_CS_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define SPI1_CS_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define SPI1_CS_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define SPI1_CS_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define SPI1_CS_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define SPI1_CS_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set SCK1 aliases
#define SCK1_TRIS                 TRISCbits.TRISC1
#define SCK1_LAT                  LATCbits.LATC1
#define SCK1_PORT                 PORTCbits.RC1
#define SCK1_WPU                  WPUCbits.WPUC1
#define SCK1_OD                   ODCONCbits.ODCC1
#define SCK1_ANS                  ANSELCbits.ANSC1
#define SCK1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define SCK1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define SCK1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define SCK1_GetValue()           PORTCbits.RC1
#define SCK1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define SCK1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define SCK1_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define SCK1_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define SCK1_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define SCK1_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define SCK1_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define SCK1_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set SDI1 aliases
#define SDI1_TRIS                 TRISCbits.TRISC2
#define SDI1_LAT                  LATCbits.LATC2
#define SDI1_PORT                 PORTCbits.RC2
#define SDI1_WPU                  WPUCbits.WPUC2
#define SDI1_OD                   ODCONCbits.ODCC2
#define SDI1_ANS                  ANSELCbits.ANSC2
#define SDI1_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define SDI1_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define SDI1_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define SDI1_GetValue()           PORTCbits.RC2
#define SDI1_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define SDI1_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define SDI1_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define SDI1_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define SDI1_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define SDI1_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define SDI1_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define SDI1_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set SDO1 aliases
#define SDO1_TRIS                 TRISCbits.TRISC3
#define SDO1_LAT                  LATCbits.LATC3
#define SDO1_PORT                 PORTCbits.RC3
#define SDO1_WPU                  WPUCbits.WPUC3
#define SDO1_OD                   ODCONCbits.ODCC3
#define SDO1_ANS                  ANSELCbits.ANSC3
#define SDO1_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define SDO1_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define SDO1_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define SDO1_GetValue()           PORTCbits.RC3
#define SDO1_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define SDO1_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define SDO1_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define SDO1_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define SDO1_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define SDO1_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define SDO1_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define SDO1_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()              PORTCbits.RC5
#define RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define RC5_SetPullup()             do { WPUCbits.WPUC5 = 1; } while(0)
#define RC5_ResetPullup()           do { WPUCbits.WPUC5 = 0; } while(0)
#define RC5_SetAnalogMode()         do { ANSELCbits.ANSC5 = 1; } while(0)
#define RC5_SetDigitalMode()        do { ANSELCbits.ANSC5 = 0; } while(0)

// get/set BT_IND aliases
#define BT_IND_TRIS                 TRISCbits.TRISC6
#define BT_IND_LAT                  LATCbits.LATC6
#define BT_IND_PORT                 PORTCbits.RC6
#define BT_IND_WPU                  WPUCbits.WPUC6
#define BT_IND_OD                   ODCONCbits.ODCC6
#define BT_IND_ANS                  ANSELCbits.ANSC6
#define BT_IND_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define BT_IND_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define BT_IND_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define BT_IND_GetValue()           PORTCbits.RC6
#define BT_IND_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define BT_IND_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define BT_IND_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define BT_IND_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define BT_IND_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define BT_IND_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define BT_IND_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define BT_IND_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set SST25_CS aliases
#define SST25_CS_TRIS                 TRISCbits.TRISC7
#define SST25_CS_LAT                  LATCbits.LATC7
#define SST25_CS_PORT                 PORTCbits.RC7
#define SST25_CS_WPU                  WPUCbits.WPUC7
#define SST25_CS_OD                   ODCONCbits.ODCC7
#define SST25_CS_ANS                  ANSELCbits.ANSC7
#define SST25_CS_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define SST25_CS_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define SST25_CS_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define SST25_CS_GetValue()           PORTCbits.RC7
#define SST25_CS_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define SST25_CS_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define SST25_CS_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define SST25_CS_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define SST25_CS_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define SST25_CS_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define SST25_CS_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define SST25_CS_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/