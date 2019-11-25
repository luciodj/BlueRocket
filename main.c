/**
  PIC-BLE LightBlue demo

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the default (Out of Box) demo firmware for PIC-BLE board.

  Description:
    It implements a simple serial protocol using the Transparent UART of the
    RN4870 module to report sensor data to the LightBlue mobile App.
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

#include "lightblue.h"
#include "rn487x.h"

#define VERSION     8

uint8_t version[] = {
    02,     // 1 = AVR, 2 = PIC
    00,     // major
    VERSION // minor
};

static char     buffer[80];         // buffer for status messages
static char     serial[80];         // buffer for LightBlue
static uint8_t  sp = 0;             // insertion pointer
static bool     connected = false;  // LightBlue is connected

void message_handler(char* msg)
{
    //    Status Messages Handler
    printf("<<< %s >>>\n", msg);
    if (strstr(msg, "DISCONNECT")){
        connected = false;
        puts("]");
    }
    else if (strstr(msg, "STREAM_OPEN")) {
        connected = true;
        puts("[");
    }
}

void main(void)
{
    SYSTEM_Initialize();
    RN487x_AsyncHandlerSet(message_handler, buffer, sizeof(buffer));
    INTERRUPT_PeripheralInterruptEnable();
    INTERRUPT_GlobalInterruptEnable();
    // temporarily configure BLE UART for 115,200
    SP2BRGH = 0; SP2BRGL = 0x44;
    RN487X_Init();

    printf("PIC-BLE Configurator\n");
    RN487X_EnterCmdMode();
    puts("Setting Baud Rate to 9,600");
    bool success = false;
    if (RN487X_SetBaud('9')) {
        puts("SettingBoard Name set to PIC-BLE");
        if (RN487X_SetName("PIC-BLE")) {
            puts("Rebooting...");
            if (RN487X_RebootCmd()){
                puts("You can download fw v.8 and above now!");
            }
        }
    } else {
        puts("Configurator failed, was the module already configured?");
    }
    // reconfigure BLE UART for 9600
    SP2BRGH = 3; SP2BRGL = 0x40;

    while (1)  {
        while (RN487x_DataReady())
            uart[CDC_UART].Write(RN487x_Read());
        //  mirror CDC to BLE
        while (uart[CDC_UART].DataReady())
            uart[BLE_UART].Write(uart[CDC_UART].Read());
    } // main loop
}
