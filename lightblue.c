/*
 * cmd.c
 *
 */
#include "lightblue.h"
#include "sensor_handling.h"
#include "rn487x.h"
#include "bsp.h"

static uint8_t blue_sequence = 0;


#define NUM_ELEM(x) (sizeof (x) / sizeof (*(x)))

typedef enum { _idle=0, _seq, _cmd, _len0, _len1, _payload0, _payload1} blue_state;

static char _hex[] = "0123456789ABCDEF";
#define Hex(x) _hex[(x) & 0xf]

void blue_byte(char * payload, uint8_t value)
{
    payload += strlen(payload);
    *payload++ = Hex(value >> 4);    // append LSB
    *payload++ = Hex(value);
    *payload = '\0';
}
void blue_word(char* payload, uint16_t value)
{
    blue_byte(payload, value);  // append LSB
    blue_byte(payload, value >> 8);
}

void blue_print(char id, char* payload)
{
    char s[3];

    uart[BLE_UART].Write('[');                      // start packet
    uart[BLE_UART].Write(Hex(blue_sequence++));
    uart[BLE_UART].Write(id);                       // packet ID
    uart[BLE_UART].Write(Hex(strlen(payload)>>4));  // packet size
    uart[BLE_UART].Write(Hex(strlen(payload)));
    while (*payload) {                              // payload
        uart[BLE_UART].Write(*(uint8_t*)payload++);
    }
    uart[BLE_UART].Write(']');                      // close packet
}

/* \brief collects temperature sensor data
*/
void blue_temp(void){
    char payload[32];
    uint8_t buffer[2];

    *payload = '\0';
    uint16_t word = temp_read(buffer);
    blue_word(payload, word);

    // also expose on terminal
    uint16_t degree = ((buffer[0] << 4) & 0xF0) | ((buffer[1] >> 4) & 0x0F);
    uint16_t temp_word = (uint16_t) (buffer[1] & 0x0F) * 625;
    blue_print('T', payload);
}

/* \brief collects the XYZ from teh accel sensor
*/
void blue_acc(void){
    char payload[32];
    uint8_t buffer[6];

    *payload = '\0';
    uint8_t i;
    uint16_t xyz[3], temp_word;

    acc_read(buffer, xyz);
    for(i=0; i<3; i++) {
        temp_word = xyz[i];
        blue_word(payload, temp_word);

        // also expose on terminal
        if(temp_word & 0x800){
            temp_word = ~temp_word + 1;
        }
    }
    blue_print('X', payload);
}

void blue_button(void)
{
    char payload[16];
    *payload = '\0';
    blue_byte(payload, SW0_get()? 0 : 1); // Button 0, state ( 1 = pushed )
    blue_print('P', payload);
}

// led1 RED, is managed as a global as we cannot poll its status
uint8_t led1 = 0;       // off by default
uint8_t led1_new = 0;   // off by default

void LED1_set(uint8_t v)
{
    led1_new = v;
}

/*
 * LED1 (RED) cannot be set while in transparent mode, it must be deferred to main loop
 * RED is controlled by the BLE module in CMD mode
 * switching mode while in the middle of a receive sequence would clear the BLE buffers
 */
void LED1_update(void)
{
    if (led1 != led1_new) {  // value change
        led1 = led1_new;
        RN487X_EnterCmdMode();
        RN487X_SetIO(led1 == 0);
        RN487X_EnterDataMode();
    }
}

uint8_t LED1_get(void)
{
    return led1;
}

void blue_leds(void)
{
    char payload[16];
    *payload = '\0';
    blue_byte(payload, 0x00 + LED0_get());
    blue_print('L', payload);
    *payload = '\0';
    blue_byte(payload, 0x10 + LED1_get());  // LED1 state (1 = on)
    blue_print('L', payload);
}

void blue_serial(char* serial)
{
    uint8_t len = strlen(serial)*2; // packet ID
    uart[BLE_UART].Write('[');                      // start packet
    uart[BLE_UART].Write(Hex(blue_sequence++));
    uart[BLE_UART].Write('S');
    uart[BLE_UART].Write(Hex(len>>4));              // packet size
    uart[BLE_UART].Write(Hex(len));
    while (*serial) {                               // payload
        uart[BLE_UART].Write(Hex(*serial>>4));
        uart[BLE_UART].Write(Hex(*serial++));
    }
    uart[BLE_UART].Write(']');                      // close packet
}

void blue_version(uint8_t version)
{
    char payload[16];
    *payload = '\0';
    blue_byte(payload, version);
    blue_print('V', payload);
}

void dispatch(char cmd, uint16_t data)
{
    uint8_t led;
    switch(cmd){
        case 'L':   // LED command
            led = (data >> 4) & 1;
            if (led == 0)    // LED 0
                LED0_set(data & 1);
            else             // LED 1
                LED1_set(data & 1);
            break;
        case 'S':   // serial data
            // send data to serial port
            uart[CDC_UART].Write(data);
            break;
        default:    // command unknown (return Error R?)
            break;
    }
}

#define h2d(c)  (((c) <= '9') ? (c) - '0' : (c & 0x5f) - 'A' + 10)

/* \brief Parses the LightBLUE commands according to the serial protocol defined
 *
 * [ seq cmd len payload ]
 * where:
 *   seq: a single hex digit changing at each cycle
 *   cmd: L for LED, S for serial data string ...
 *   len: two hex digits, 00-ff len of payload, # of hex digits following
 *   payload: hex digits
 */
void blue_parse(char c)
{
    static blue_state state = _idle;
    static uint8_t length = 0;
    static uint16_t data = 0;
    static char cmd = '\0';

    switch(state) {
        case _seq:
            //ignore sequence
            state = _cmd;
            break;
        case _cmd:
            cmd = c;
            state = _len0;
            break;
        case _len0:
            length = h2d(c);
            state = _len1;
            break;
        case _len1:
            length = (length << 4) + h2d(c);
            state = _payload0;
            break;
        case _payload0:
            data = h2d(c);
            length--;
            if (length == 0)
                state = _idle;
            else
                state = _payload1;
            break;
        case _payload1:
            data = (data << 4) + h2d(c);
            dispatch(cmd, data);
            length--;
            if (length == 0)
                state = _idle;
            else
                state = _payload0;
            break;
        case _idle:
        default:
            if (c == '[')
                state = _seq;
            break;
    }
}

