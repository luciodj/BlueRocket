/*
 * cmd.c
 *
 * Created: 03.01.2013 14:21:49
 *  Author: are.halvorsen
 */
#include "cmd.h"
#include "mcc_generated_files/mcc.h"
#include <string.h>
#include <stdio.h>
#include "common/minion.h"
#include "common/i2c_wrapper.h"

#include "sst25pf040ct.h"

uint8_t cmd[80];


uint8_t public_key_x509_header[128] = { 0x30, 0x59, 0x30, 0x13, 0x06, 0x07, 0x2A, 0x86,
                                        0x48, 0xCE, 0x3D, 0x02, 0x01, 0x06, 0x08, 0x2A,
                                        0x86, 0x48, 0xCE, 0x3D, 0x03, 0x01, 0x07, 0x03,
                                        0x42, 0x00, 0x04 };

uint8_t buffer[80];
uint32_t temp_word = 0;
uint8_t key_buffer[128];

#define TEMP_SENS_I2C_ADDRESS     0x18
#define ACCEL_SENS_I2C_ADDRESS    0x19
#define ECC608_I2C_ADDRESS        0x58

#define NUM_ELEM(x) (sizeof (x) / sizeof (*(x)))


#define CMD_HELLO		   0
#define CMD_CHIPREV        1
#define CMD_CHIPID         2
#define CMD_UNIQUE		   3
#define CMD_LED0_OFF       4
#define CMD_LED0_ON        5
#define CMD_BLE2_OFF       6
#define CMD_BLE2_ON        7
#define CMD_DGI_INIT       8
#define CMD_GPIO0_LOW      9
#define CMD_GPIO0_HIGH     10
#define CMD_TEMP_SENSOR    11
#define CMD_TEMP_MANDEV    12
#define CMD_ECC_SERIAL     13
#define CMD_ECC_KEY        14
#define CMD_ACCEL_SENSOR   15
#define CMD_ACCEL_MANDEV   16
#define CMD_BT_MAC         17
#define CMD_BT_REV         18
#define CMD_BT_STATUS      19
#define CMD_SST25_READID   20
#define CMD_SST25_JEDEC    21
#define CMD_I2C_PROBE      22
#define CMD_TEST_VERSION   23
#define CMD_HELP           24
#define CMD_BLUE           25
#define CMD_NOT_FOUND     -1

/** \brief Array of command strings.
 *
 * Add new commands to this array.
 */
const char *commands[] = {
    "hello",
    "chiprev",
    "chipid",
    "unique",
    "led0 off",
    "led0 on",
    "ble2 off",
    "ble2 on",
    "dgi init",
    "gpio0 low",
    "gpio0 high",
    "temp sensor",
    "temp mandev",
    "ecc serial",
    "ecc key",
    "accel sensor",
    "accel chipid",
    "bt mac",
    "bt info",
    "bt status led",
    "sst25 id",
    "sst25 jedec",
    "I2C probe",
    "version",
    "help",
    "blue"
};

uint32_t CONFIG_ReadWord(uint32_t configAddr)
{
    uint8_t GIEBitValue = INTCONbits.GIE;   // Save interrupt enable

    INTCONbits.GIE = 0;     // Disable interrupts
    NVMADRL = (configAddr & 0x00FF);
    NVMADRH = ((configAddr & 0xFF00) >> 8);

    NVMCON1bits.NVMREGS = 1;    // Deselect Configuration space
    NVMCON1bits.RD = 1;      // Initiate Read
    NOP();
    NOP();
    INTCONbits.GIE = GIEBitValue;	// Restore interrupt enable

    return ((uint16_t)((NVMDATH << 8) | NVMDATL));
}

/** \brief Get the command from a stream.
 *
 * Will block until a "\r\n" terminated string has been received.
 */
static void get_command(uint8_t *cmd)
{

    uint8_t i = 0;
    bool command = false;

    while (!command) {
        // Blocking read of CDC UART
        cmd[i] = EUSART1_Read();

        if ((cmd[i] == '\r') || (cmd[i] == '\n')) {
            cmd[i] = '\0';
            command = true;
        }
        // If the command is 1 character long (e.g /r/n sent), ignore it to prevent double trigger
        if (command && i == 0) {
            command = false;
            i = 0;
        } else {
            i++;
            // Check for buffer overflow of cmd buffer and handle it
            if (i >= 80) {
                i = 80 - 1;
                cmd[i] = '\0';
                command = true;
            }
        }
    }
}


/** \brief Searches for the command in the command array
 *
 * \param cmd Pointer to the command string that should be searched in the
 * commands[].
 *
 * \returns Array index of the command when the command exists, otherwise
 * it will return -1 aka CMD_NOT_FOUND.
 */
static int32_t parse_command(uint8_t *cmd)
{
    uint32_t i;

    for (i = 0; i < NUM_ELEM(commands); i++) {
        if (strcmp((char *) cmd, commands[i]) == 0) {
            return i;
        }
    }
    return CMD_NOT_FOUND;
}

void bt_read_reg(char * cmd, uint8_t * response)
{
    // Get into command mode
    delay_ms(5);
    EUSART2_Write('$');
    EUSART2_Write('$');
    EUSART2_Write('$');
    delay_ms(5);

    // CR to clear input if already in CMD mode
    EUSART2_Write('\r');
    delay_ms(5);

    // Read out garbage data
    while(EUSART2_is_rx_ready()){
        EUSART2_Read();
    }

    // Command to send
    while(*cmd != 0){
        EUSART2_Write(*cmd);
        cmd++;
    }

    uint8_t i = 0;
    uint8_t done = false;
    while (!done){
        // Blocking read of CDC UART
        response[i] = EUSART2_Read();
        if ((response[i] == '\r') || (response[i] == '\n')) {
            response[i] = 0;
            done = true;
        }
        i++;
    }
}

static uint8_t blue_sequence = 0;

void blue_print(char id, char* payload)
{
    char s[3];
    char hex[] = "0123456789ABCDEF";        // sequence

    EUSART1_Write('[');                     // start packet
    EUSART1_Write(hex[blue_sequence++]);
    if (blue_sequence > 15) blue_sequence = 0;
    EUSART1_Write(id);                      // packet ID
    sprintf(s, "%02X", strlen(payload));    // payload length
    EUSART1_Write(s[0]);
    EUSART1_Write(s[1]);
    while (*payload) {                      // payload
        EUSART1_Write(*(uint8_t*)payload++);
    }
    EUSART1_Write(']');                     // close packet

}

void blue_int(char * payload, uint16_t value)
{
    payload += strlen(payload);     // append
    sprintf(payload, "%04X", value);
//    payload += strlen(payload);     // append
//    sprintf(payload, "%02X", value >> 8);
}

/* \brief Handles incoming commands from the test PC
 *
 * Current implementation will block until a command has been received.
 * When a not identified command as detected a "nak\r\n" will be sent
 * back to the test PC.
 */
void command_handler(void)
{
    char payload[32];

    get_command(cmd);

    switch(parse_command(cmd)) {
        case CMD_BLUE:
          while(1){
            *payload = '\0';
            // read temp in deg C
            i2c_read_reg(TEMP_SENS_I2C_ADDRESS, &buffer[0], 1, &buffer[0], 2);
//            uint8_t deg = ((buffer[0] << 4) & 0xF0) | ((buffer[1] >> 4) & 0x0F);
//            temp_word = (uint32_t) (buffer[1] & 0x0F) * 625;
            // simulate output to LightBlue protocol
            blue_int(payload, (*(uint16_t *)buffer) & 0xfc1f);
            blue_print('T', payload);
            // read accelerometer
            *payload = '\0';
            buffer[0] = 2;
            i2c_read_reg(ACCEL_SENS_I2C_ADDRESS, &buffer[0], 1, &buffer[0], 6);
            uint16_t *p = (uint16_t*)buffer;
            for(uint8_t i=0; i<3; i++){
                temp_word = (buffer[i*2 + 1] << 4) | (buffer[i*2] >> 4);
                uint16_t lsb_first = ((temp_word >> 8 & 0xff)) | (temp_word << 8);
                blue_int(payload, lsb_first);
                if(temp_word & 0x800){
                    temp_word = ~temp_word + 1;
                    print_printf("-%d, ", temp_word & 0xFFF);
                }else{
                    print_printf("%d, ", temp_word & 0xFFF);
                }
            }
            blue_print('X', payload);
            if (EUSART1_Read() == 'x') break;
          }
          break;

        case CMD_HELLO:
            print_printf("good day\r\n");
            break;

        case CMD_LED0_ON:
            LED_0_SetLow();
            print_printf("ok\r\n");
            break;

        case CMD_LED0_OFF:
            LED_0_SetHigh();
            print_printf("ok\r\n");
            break;

        case CMD_BLE2_ON:
            bt_read_reg("|O,01,00\r", &buffer[0]);
            print_printf("ok\r\n");
            break;

        case CMD_BLE2_OFF:
            bt_read_reg("|O,01,01\r", &buffer[0]);
            print_printf("ok\r\n");
            break;

        case CMD_CHIPID:
            print_printf("0x%4x\r\n", CONFIG_ReadWord(0x8006));
            break;

        case CMD_CHIPREV:
            print_printf("0x%2x\r\n", CONFIG_ReadWord(0x8005));
            break;

        case CMD_UNIQUE:
            print_printf("0x");
            for (uint8_t i=0; i<9; i++) {
                print_printf("%4x", CONFIG_ReadWord(DIA_MUI + i));
            }
            print_printf("\r\n");
            break;

        case CMD_DGI_INIT:
            SW0_SetDigitalOutput();
            SW0_SetLow();
            print_printf("ok\r\n");
            break;

        case CMD_GPIO0_LOW:
            SW0_SetLow();
            print_printf("ok\r\n");
            break;

        case CMD_GPIO0_HIGH:
            SW0_SetHigh();
            print_printf("ok\r\n");
            break;

        case CMD_I2C_PROBE:
            i2c_prober();
            print_printf("ok\r\n");
            break;

        case CMD_TEMP_MANDEV:
            buffer[0] = MCP9808_MAN;
            i2c_read_reg(TEMP_SENS_I2C_ADDRESS, &buffer[0], 1, &buffer[0], 2);
            buffer[2] = MCP9808_DEVICE;
            i2c_read_reg(TEMP_SENS_I2C_ADDRESS, &buffer[2], 1, &buffer[2], 2);
            temp_word = (uint32_t) buffer[0] << 24 | (uint32_t) buffer[1] << 16 | (uint32_t) buffer[2] << 8 | (uint32_t) buffer[3];
            print_printf("0x%8x\r\n", temp_word);
            break;

        case CMD_TEMP_SENSOR:
            buffer[0] = MCP9808_TEMP;
            i2c_read_reg(TEMP_SENS_I2C_ADDRESS, &buffer[0], 1, &buffer[0], 2);
            uint8_t degree = ((buffer[0] << 4) & 0xF0) | ((buffer[1] >> 4) & 0x0F);
            temp_word = (uint32_t) (buffer[1] & 0x0F) * 625;
            print_printf("%d.%4dC\r\n", (uint32_t) degree, temp_word);
            break;

        case CMD_SST25_READID:
            print_printf("0x%2x\r\n", (uint32_t)sst25_read_id());
            break;

        case CMD_SST25_JEDEC:
            sst25_read_jedec(buffer);
            temp_word = (uint32_t) buffer[0] << 24 | (uint32_t) buffer[1] << 16 | (uint32_t) buffer[2] << 8 | (uint32_t) buffer[3];
            print_printf("0x%8x\r\n", temp_word);
            break;

        case CMD_ACCEL_MANDEV:
            buffer[0] = 0;
            i2c_read_reg(ACCEL_SENS_I2C_ADDRESS, &buffer[0], 1, &buffer[0], 1);
            print_printf("0x%2x\r\n", buffer[0]);
            break;

        case CMD_ACCEL_SENSOR:
            buffer[0] = 2;
            i2c_read_reg(ACCEL_SENS_I2C_ADDRESS, &buffer[0], 1, &buffer[0], 6);
            for(uint8_t i=0; i<3; i++){
                temp_word = (buffer[i*2 + 1] << 4) | (buffer[i*2] >> 4);
                if(temp_word & 0x800){
                    temp_word = ~temp_word + 1;
                    print_printf("-%d, ", temp_word & 0xFFF);
                }else{
                    print_printf("%d, ", temp_word & 0xFFF);
                }
            }
            print_printf("\r\n");
            break;

        case CMD_BT_MAC:
            bt_read_reg("D\r", &buffer[0]);
            print_printf("%s\r\n", &buffer[4]);//Skip the 4 first bytes ('BTA=')
            break;

        case CMD_BT_REV:
            bt_read_reg("GDH\r", &buffer[0]);
            bt_read_reg("GDF\r", &buffer[20]);
            bt_read_reg("GDR\r", &buffer[40]);
            print_printf("HW: %s, FW: %s, SW: %s\r\n", &buffer[0], &buffer[20], &buffer[40]);
            break;

        case CMD_BT_STATUS:
            bt_read_reg("SW,02,07\r", &buffer[0]);
            print_printf("ok\r\n");
            break;

        case CMD_ECC_KEY:
            atecc508_read_slot(ECC608_I2C_ADDRESS, 0, buffer);
            if (buffer[0] == 0x43) {
                for (uint8_t x = 1; x < 65; x++) {
                    print_printf("%2x", (uint32_t) buffer[x]);
                }
                print_printf("\r\n");
            } else {
                print_printf("Error!\r\n");
            }
            break;

        case CMD_ECC_SERIAL:
            if (I2C2_MESSAGE_COMPLETE != atecc508_read_serial(ECC608_I2C_ADDRESS, buffer)) {
                print_printf("Error!\r\n");
            } else {
                print_printf("%2x", (uint32_t) buffer[1]);
                print_printf("%2x", (uint32_t) buffer[2]);
                print_printf("%2x", (uint32_t) buffer[3]);
                print_printf("%2x", (uint32_t) buffer[4]);
                print_printf("%2x", (uint32_t) buffer[9]);
                print_printf("%2x", (uint32_t) buffer[10]);
                print_printf("%2x", (uint32_t) buffer[11]);
                print_printf("%2x", (uint32_t) buffer[12]);
                print_printf("%2x\4\r\n", (uint32_t) buffer[13]);
            }
            break;

        case CMD_TEST_VERSION:
            print_printf("Build Date: %s\r\n", __DATE__);
            break;

        case CMD_HELP:
            print_printf("Available commands:\r\n");
            for (uint8_t i = 0; i < NUM_ELEM(commands); i++){
                print_printf(" - %s\r\n", commands[i]);
            }
            break;

        case CMD_NOT_FOUND: // intentionally no break here to fall through
        default:
            print_printf("nak\r\n");
            break;
    }
}