/*
 * File:   rn487x.h
 * Author: C40924
 *
 * Created on September 3, 2019, 11:30 AM
 */

#ifndef RN487X_H
#define	RN487X_H

#ifdef	__cplusplus
extern "C" {
#endif

/**
  Section: Macro Declarations
*/
//MCC will configure this Macro
#define RN487X_IO_CAPABILITY            4

//Time duration to put the RN487X in reset mode
#define RN487X_RESET_HIGH_DELAY_TIME    1
//Time delay for RN487X boot up
#define RN487X_STARTUP_DELAY            200

//Convert nibble to ASCII
#define NIBBLE2ASCII(nibble) (((nibble < 0x0A) ? (nibble + '0') : (nibble + 0x57)))

/**
  Section: Data Type Definitions
*/
typedef enum
{
    SET_IO_CAP_0,    //No input no output with bonding
    SET_IO_CAP_1,    //Display YesNo
    SET_IO_CAP_2,    //No input no output
    SET_IO_CAP_3,    //Key board only
    SET_IO_CAP_4,    //Display only
    SET_IO_CAP_5,    //Keyboard display
}RN487X_SET_IO_CAPABILITY_t;

typedef enum
{
    BR_921600,
    BR_460800,
    BR_230400,
    BR_115200,
    BR_57600,
    BR_38400,
    BR_28800,
    BR_19200,
    BR_14400,
    BR_9600,
    BR_4800,
    BR_2400,
}RN487X_BAUDRATE_t;

typedef enum
{
    RN487X_ENABLE_FLOW_CONTROL = 0x8000,
    RN487X_NO_PROMPT = 0x4000,
    RN487X_FAST_MODE = 0x2000,
    RN487X_NO_BEACON_SCAN = 0x1000,
    RN487X_NO_CONNECT_SCAN = 0x0800,
    RN487X_NO_DUPLICATE_SCAN_RESULT_FILTER = 0x0400,
    RN487X_PASSIVE_SCAN = 0x0200,
    RN487X_UART_TRANSPARENT_WITHOUT_ACK = 0x0100,
    RN487X_REBOOT_AFTER_DISCONNECTION = 0x0080,
    RN487X_RUNNING_SCRIPT_AFTER_POWER_ON = 0x0040,
    RN487X_SUPPORT_RN4020_MLDP_STREAMING_SERVICE = 0x0020,
    RN487X_DATA_LENGTH_EXTENSION = 0x0010,
    RN487X_COMMAND_MODE_GUARD = 0x0008,
}RN487X_FEATURES_BITMAP_t;

typedef enum
{
    SF_1 = 1,   //Reset to factory default
    SF_2 = 2,   //Reset to factory default including private services and script
}RN487X_FACTORY_RESET_MODE_t;

typedef enum
{
    SS_DEVICE_INFO = 0X80,
    SS_UART_TRANSPARENT = 0x40,
    SS_BEACON = 0x20,
    SS_RESERVED = 0x10,
}RN487X_DEFAULT_SERVICE_BITMAP_t;


/**
  Section: RN487x APIs
*/
 /**
  @Summary
    Initializes RN487X and its host interface.

  @Description
    This routine initializes RN487x interface with host MCU and the RN487x
  * itself. Puts the device in command mode.

  @Preconditions
    None

  @Param
    interfaceCb  - RN487x interface callback

  @Returns
    bool - true, if init succeeds; false, otherwise
*/
bool RN487X_Init(void);

 /**
  @Summary
    Sends out command to RN487x.

  @Description
    This routine takes command and its length as input and sends that command
  * to RN487x.

  @Preconditions
    RN487X_Init() function should have been called before calling this function

  @Param
    cmd  - RN487x command
    cmdLen - RN487x command length

  @Returns
  None
*/
void RN487X_SendCmd(uint8_t *cmd, uint8_t cmdLen);

 /**
  @Summary
    Sends out data to RN487x.

  @Description
    This routine takes data and its length as input and sends the data to RN487x.

  @Preconditions
    Device should have connected with remote device and transparent UART pipe
  * should be opened

  @Param
    data  - RN487x data
    dataLen - RN487x data length

  @Returns
  None
*/
void RN487X_SendData(const char *data, uint8_t dataLen);

 /**
  @Summary
    Gets config value from RN487x by sending get command

  @Description
    This routine gets the config value from RN487x by sending get command
  * For more details, refer section 2.5 GET COMMANDS in RN4870-71 user guide.

  @Preconditions
    Device should have been in command mode

  @Param
    getCmd  - Get command to send
    getCmdLen - Get command length
    getCmdResp - Buffer to store get command response

  @Returns
    uint8_t - Length of get command response
*/
uint8_t RN487X_GetCmd(char *getCmd, uint8_t getCmdLen, char *getCmdResp);

 /**
  @Summary
    Reads specific message from RN487x.

  @Description
    This routine takes input from application on the expected response/status
  * message. It starts read RN487X host interface immediately and look for
  * expected message.

  @Preconditions
    RN487X_Init() function should have been called before calling this function

  @Param
    expectedMsg  - Expected response/status message from RN487x
    msgLen - Expected response/status message length

  @Returns
    bool - true, if successfully gets expected message; false, otherwise
*/
bool RN487X_ReadMsg(const uint8_t *expectedMsg, uint8_t msgLen);

 /**
  @Summary
    Waits for specific message from RN487x.

  @Description
    This routine takes input from application on the expected response/status
  * message. It waits until it receives expected message from RN487x.
  * This helps to read the RN487x status messages.

  @Preconditions
    RN487X_Init() function should have been called before calling this function

  @Param
    expectedMsg  - Expected response/status message from RN487x
    msgLen - Expected response/status message length

  @Returns
    None
*/
void RN487X_WaitForMsg(const char *expectedMsg, uint8_t msgLen);

 /**
  @Summary
    Reads default response from RN487x.

  @Description
    This routine reads RN487x interface for default response which is AOK or ERR.

  @Preconditions
    RN487X_Init() function should have been called before calling this function.
  * RN487X_SendCmd() function should have been called before this function.

  @Param
    None

  @Returns
    bool - true, if successfully reads default response; false, otherwise
*/
bool RN487X_ReadDefaultResponse(void);

 /**
  @Summary
    Puts the RN487x in command mode.

  @Description
    This routine puts the RN487x in command mode.

  @Preconditions
    RN487X_Init() function should have been called before calling this function.

  @Param
    None

  @Returns
    bool - true, if successfully enters command mode; false, otherwise
*/
bool RN487X_EnterCmdMode(void);

 /**
  @Summary
    Puts the RN487x in data mode.

  @Description
    This routine puts the RN487x in data mode.

  @Preconditions
    RN487X_Init() function should have been called before calling this function.

  @Param
    None

  @Returns
    bool - true, if successfully enters data mode; false, otherwise
*/
bool RN487X_EnterDataMode(void);

 /**
  @Summary
    Sets device name.

  @Description
    This routine sets the RN487x device name. For more details, refer SN
  * command in RN4870-71 user guide.

  @Preconditions
    RN487X should be in command mode.

  @Param
  name - Device name [20 alphanumeric characters max]
  nameLen - Device name length

  @Returns
    bool - true, if successfully sets device name; false, otherwise
*/
bool RN487X_SetName(const char *name, uint8_t nameLen);

/* Set Output pin (1) on/off
 */
bool RN487X_SetIO(bool b);

 /**
  @Summary
    Sets the default supported services in RN487x.

  @Description
    This routine sets the supported services bitmap in RN487x. The service flag
  * values can be found in RN487X_DEFAULT_SERVICE_BITMAP_t. For more details,
  * refer SS command in RN4870-71 user guide.

  @Preconditions
    RN487X should be in command mode.

  @Param
    serviceBitmap - Supported services bitmap in RN487x

  @Returns
    bool - true, if successfully sets service bitmap; false, otherwise
*/
bool RN487X_SetServiceBitmap(uint8_t serviceBitmap);

 /**
  @Summary
    Sets the RN487x interface baud rate.

  @Description
    This routine sets the baud rate for RN487x interface. The possible baud rate
  * values can be found in RN487X_BAUDRATE_t. For more details, refer SB
  * command in RN4870-71 user guide.
  * Note: The RN487x is configured with 115200 baud rate in production line.

  @Preconditions
    RN487X should be in command mode.

  @Param
    baudRate - baudrate for RN487x interface

  @Returns
    bool - true, if successfully sets baud rate; false, otherwise
*/
bool RN487x_SetBaudRate(uint8_t baudRate);

 /**
  @Summary
    Sets the supported features of RN487x.

  @Description
    This routine sets the supported features bitmap of RN487x. The features list
  * can be found in RN487X_FEATURES_BITMAP_t. For more details, refer SR command
  * in RN4870-71 user guide.

  @Preconditions
    RN487X should be in command mode.

  @Param
    featuresBitmap - Supported features bitmap in RN487x

  @Returns
    bool - true, if successfully sets features bitmap; false, otherwise
*/
bool RN487X_SetFeaturesBitmap(uint16_t featuresBitmap);

 /**
  @Summary
    Sets the IO capability of RN487x and the system.

  @Description
    This routine sets the IO capability of RN487x and the system. This will be
  * used to determine BLE authentication method. The possible IO capabilities
  * can be found in RN487X_SET_IO_CAPABILITY_t. For more details, refer SA
  * command in RN4870-71 user guide.

  @Preconditions
    RN487X should be in command mode.

  @Param
    ioCapability - IO capability of RN487x

  @Returns
    bool - true, if successfully sets IO capability; false, otherwise
*/
bool RN487x_SetIOCapability(uint8_t ioCapability);

 /**
  @Summary
    Sets the security pin code on RN487x.

  @Description
    This routine sets the security pin code on RN487x. It can be 4 bytes or 6 bytes
  * in length. For more details, refer SP and SA command in RN4870-71 user guide.

  @Preconditions
    RN487X should be in command mode.

  @Param
    pinCode - Security pin code
    pinCodeLen - Security pin code length (4 or 6)

  @Returns
    bool - true, if successfully sets security pin code; false, otherwise
*/
bool RN487x_SetPinCode(const char *pinCode, uint8_t pinCodeLen);

 /**
  @Summary
    Resets RN487x.

  @Description
    This routine resets RN487x. For more details, refer R command in
  * RN4870-71 user guide.

  @Preconditions
    RN487X should be in command mode.

  @Param
    None

  @Returns
    bool - true, if successfully reboots; false, otherwise
*/
bool RN487X_RebootCmd(void);

 /**
  @Summary
    Resets RN487x to factory default.

  @Description
    This routine resets RN487x to factory default. The possible reset modes
  * can be found in RN487X_FACTORY_RESET_MODE_t. For more details, refer SF
  * commands in RN4870-71 user guide.

  @Preconditions
    RN487X should be in command mode.

  @Param
    resetMode - Mode of factory reset.

  @Returns
    bool - true, if successfully resets to factory default; false, otherwise
*/
bool RN487X_FactoryReset(RN487X_FACTORY_RESET_MODE_t resetMode);

 /**
  @Summary
    Disconnects the BLE link between RN487x and remote device.

  @Description
    This routine disconnects the BLE link between RN487x and remote device.
  * For more details, refer K command in RN4870-71 user guide.

  @Preconditions
    RN487X should be in command mode.

  @Param
    None

  @Returns
    bool - true, if successfully disconnects; false, otherwise
*/
bool RN487X_Disconnect(void);

 /**
  @Summary
    Instructs the RN487X_ReadDefaultResponse() function to expect "CMD>".

  @Description
    This routine instructs the RN487X_ReadDefaultResponse() function to expect
  * "CMD>" after the actual response.

  @Preconditions
    RN487X should be in command mode.

  @Param
    None

  @Returns
  None
*/
void RN487X_CmdPromptEnabled(void);

/**
  @Summary
    Instructs the RN487X_ReadDefaultResponse() function not to expect "CMD>".

  @Description
    This routine instructs the RN487X_ReadDefaultResponse() function not to
  * expect "CMD>" after the actual response.

  @Preconditions
    RN487X should be in command mode.

  @Param
    None

  @Returns
  None
*/
void RN487X_CmdPromptDisabled(void);

 /**
  @Summary
    Gets message from RN487x.

  @Description
    This routine gets one byte of data/status message from RN487x by reading
  * RN487x interface. If it receives message then it will update the message on the
  * data [out] parameter and return true, otherwise return false.

  @Preconditions
    RN487X_Init() function should have been called before calling this function.

  @Param
    data - one byte of data/status message received from RN487x

  @Returns
    bool - true, if successfully gets message; false, otherwise
*/
bool RN487X_GetMsg(uint8_t *data);

uint8_t RN487x_Read(void);
bool RN487x_DataReady(void);

typedef void (asyncHandlerCb_t)(uint8_t*);
bool RN487x_AsyncHandlerSet(asyncHandlerCb_t cb, uint8_t* b, uint8_t s);

#ifdef	__cplusplus
}
#endif

#endif	/* RN487X_H */

