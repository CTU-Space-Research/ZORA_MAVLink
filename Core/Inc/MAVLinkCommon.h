//
// Created by 42R0N on 03.01.2024.
//

#ifndef CTU_SR_ZORA_MAVLINK_MAVLINKLIB_H

#include <string.h>

//#include "mavlink_types.h"
extern UART_HandleTypeDef huart1;


//-------------
// Mavlink helper function necessary workarounds and methods. ORDER MATTERS
//-------------

    //workaround, again, mavlink_system_t wont be defined until the header
    struct systemID {
        uint8_t sysid;
        uint8_t compid;
    };

    //neccesary define in order to define the mavlink_channel_t BEFORE the header is loaded
    #define HAVE_MAVLINK_CHANNEL_T
    typedef enum {
        MAVLINK_COMM_0,
        MAVLINK_COMM_1,
        MAVLINK_COMM_2,
        MAVLINK_COMM_3
    } mavlink_channel_t;

    //declare functions before they
    void comm_send_ch(mavlink_channel_t chan, const uint8_t ch){
        if(chan == MAVLINK_COMM_0){
            HAL_UART_Transmit_IT(&huart1, &ch, 1);
        }
    }

    //mavlink convenience function
    void MAVLINK_SEND_UART_BYTES(mavlink_channel_t chan, const char *buf, uint16_t len){
        if(chan == MAVLINK_COMM_0){
            HAL_UART_Transmit_IT(&huart1, (uint8_t *)buf, len);
        }
    }

    //struct systemID mavlink_system = {.sysid=0,.compid = 0};

    #define MAVLINK_USE_CONVENIENCE_FUNCTIONS

    #include "mavlink_types.h"

    //NEEDS TO BE COPIED AGAIN ON EVERY COMPONENT/SYSTEM CHANGE
    //copied over from ctu_sr_illustria_2.h
    #define HAVE_ENUM_MAV_SYSTEM
    typedef enum MAV_SYSTEM
    {
        MAV_SYS_ID_ALL=0, /* Target id (target_component) used to broadcast messages to all components of the receiving system. Components should attempt to process messages with this component ID and forward to components on any other interfaces. Note: This is not a valid *source* component id for a message. | */
        MAV_SYS_ROCKET=1, /* System flight controller component ("autopilot"). Only one autopilot is expected in a particular system. | */
        MAV_SYS_GSE=2, /* System flight controller component ("autopilot"). Only one autopilot is expected in a particular system. | */
        MAV_SYS_COMMAND_CENTER=3, /* System flight controller component ("autopilot"). Only one autopilot is expected in a particular system. | */
        MAV_SYSTEM_ENUM_END=4, /*  | */
    } MAV_SYSTEM;

    //copied over from ctu_sr_illustria_2.h
    #define HAVE_ENUM_MAV_COMPONENT
    typedef enum MAV_COMPONENT
    {
        MAV_COMP_ID_ALL=0, /* Target id (target_component) used to broadcast messages to all components of the receiving system. Components should attempt to process messages with this component ID and forward to components on any other interfaces. Note: This is not a valid *source* component id for a message. | */
        MAV_COMP_ID_AUTOPILOT1=1, /* System flight controller component ("autopilot"). Only one autopilot is expected in a particular system. | */
        MAV_COMP_ID_ZORA_RECOVERY=10, /* Id for a component on privately managed MAVLink network. Can be used for any purpose but may not be published by components outside of the private network. | */
        MAV_COMP_ID_ZORA_PRESSURISER=11, /* Id for a component on privately managed MAVLink network. Can be used for any purpose but may not be published by components outside of the private network. | */
        MAV_COMP_ID_ZORA_ENGINE=12, /* Id for a component on privately managed MAVLink network. Can be used for any purpose but may not be published by components outside of the private network. | */
        MAV_COMP_ID_ROCKETLINK_ROCKET=13, /* Id for a component on privately managed MAVLink network. Can be used for any purpose but may not be published by components outside of the private network. | */
        MAV_COMP_ID_WIRELESS_CHARGER=14, /* Id for a component on privately managed MAVLink network. Can be used for any purpose but may not be published by components outside of the private network. | */
        MAV_COMP_ID_ARMIMG_BOARD=15, /* Id for a component on privately managed MAVLink network. Can be used for any purpose but may not be published by components outside of the private network. | */
        MAV_COMP_ID_GSE_CONTROLLER=100, /* Id for a component on privately managed MAVLink network. Can be used for any purpose but may not be published by components outside of the private network. | */
        MAV_COMP_ID_ROCKETLINK_GROUND=200, /* Id for a component on privately managed MAVLink network. Can be used for any purpose but may not be published by components outside of the private network. | */
        MAV_COMP_ID_CC_COMPUTER=201, /* Id for a component on privately managed MAVLink network. Can be used for any purpose but may not be published by components outside of the private network. | */
        MAV_COMPONENT_ENUM_END=202, /*  | */
    } MAV_COMPONENT;

    mavlink_system_t mavlink_system = {.sysid=MAV_SYS_ROCKET,.compid = MAV_COMP_ID_ZORA_ENGINE};

    #include "ctu_sr_illustria_2/mavlink.h"

   //mavlink_system.sysid = 2;
    /*
    mavlink_system_t mavlink_system =

    mavlink_system.sysid = MAV_SYS_ROCKET;
    mavlink_system.compid = MAV_COMP_ID_ZORA_ENGINE;
    */

//-------------
// END - Mavlink helper function necessary workarounds and methods. ORDER MATTERS
//-------------

int MAVlinkWriteHearbeat(){

    mavlink_message_t message;

    char buf[300];

    unsigned len = mavlink_msg_heartbeat_pack( MAVlinkSystemID,MAVlinkComponentID, &message,MAV_TYPE_ROCKET,MAV_AUTOPILOT_INVALID,MAV_MODE_FLAG_DECODE_POSITION_SAFETY, 0,MAV_STATE_STANDBY);

    // Translate message to buffer
    len = mavlink_msg_to_send_buffer((uint8_t*)buf, &message);

    // Write buffer to serial port, locks port while writing
    int bytesWritten = HAL_UART_Transmit_IT(&huart1,(uint8_t *)&buf,len);

    return bytesWritten;
}

int MAVlinkWriteProtocolVersion(){

    mavlink_message_t message;

    char buf[300];
    const uint8_t testLibHash[8] = "ABCDASDF";
    const uint8_t tesProstHash[8] = "PROTPROT";

    unsigned len = mavlink_msg_protocol_version_pack_chan( MAVlinkSystemID,
                                                           MAVlinkComponentID,
                                                           MAVLINK_COMM_0,
                                                           &message,
                                                           MAVLINK_MSG_ID_PROTOCOL_VERSION,
                                                           MAVLINK_MSG_ID_PROTOCOL_VERSION,
                                                           MAVLINK_MSG_ID_PROTOCOL_VERSION,
                                                           (uint8_t *)&tesProstHash,
                                                           (uint8_t *)&testLibHash);

    // Translate message to buffer
    len = mavlink_msg_to_send_buffer((uint8_t*)buf, &message);

    // Write buffer to serial port, locks port while writing
    int bytesWritten = HAL_UART_Transmit_IT(&huart1,(uint8_t *)&buf,len);

    return bytesWritten;
}

bool MAVlinkWriteLEDstatus(){

    GPIO_PinState G = HAL_GPIO_ReadPin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
    GPIO_PinState O = HAL_GPIO_ReadPin(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin);
    GPIO_PinState R = HAL_GPIO_ReadPin(LED_RED_GPIO_Port, LED_RED_Pin);

    mavlink_message_t message;

    char buf[300];

    // REMOVE THE TARGET SYSTEM!! THIS IS NOT A COMMAND
    mavlink_msg_zora_led_status_pack(MAVlinkSystemID,MAVlinkComponentID,&message, G,O,R);

    // Translate message to buffer
    uint16_t len = mavlink_msg_to_send_buffer((uint8_t*)buf, &message);

    // Write buffer to serial port, locks port while writing
    uint16_t bytesWritten = HAL_UART_Transmit_IT(&huart1,(uint8_t *)&buf,len);

    return (bool)bytesWritten;


}

void setLEDs(bool green, bool orange, bool red){
    HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, green);
    HAL_GPIO_WritePin(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin, orange);
    HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, red);
}

void MAVlinkSetLEDs(const mavlink_command_long_t * const command){

    setLEDs((bool)command->param1, (bool)command->param2, (bool)command->param3);

}

bool MAVLinkHandleLongCommands(const mavlink_command_long_t * const command){
    switch (command->command){

        //if the command request the system to send a message:
        case MAV_CMD_REQUEST_MESSAGE:
            uint16_t requestedMessageID = (uint16_t)command->param1;

            switch (requestedMessageID) {
                case MAVLINK_MSG_ID_PROTOCOL_VERSION:
                    MAVlinkWriteProtocolVersion();
                    return true;

                case MAVLINK_MSG_ID_ZORA_LED_STATUS:
                    MAVlinkWriteLEDstatus();
                    return true;

                default:
                    return false;


            }
            break;

        case MAV_CMD_SET_LEDS:
            MAVlinkSetLEDs(command); return true;

        default:
            return false;
            break;
    }
    return false;
}

bool MAVLinkHandleReceivedMessage(mavlink_message_t * message, mavlink_status_t * messageStatus){
    switch (message->msgid) {
        case MAVLINK_MSG_ID_HEARTBEAT:
            HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
            mavlink_heartbeat_t hb;
            mavlink_msg_heartbeat_decode(message,&hb);
            return true;

        case MAVLINK_MSG_ID_PROTOCOL_VERSION:
            HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
            mavlink_protocol_version_t protocol;
            mavlink_msg_protocol_version_decode(message, &protocol);
            return true;

            //receive message of type Command
        case MAVLINK_MSG_ID_COMMAND_LONG:
            HAL_GPIO_TogglePin(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin);
            mavlink_command_long_t _command;
            mavlink_msg_command_long_decode(message, &_command);
            const mavlink_command_long_t command = _command; //convert it to a const data variable to prevent change later


            //parse the command
            return MAVLinkHandleLongCommands(&command);
            break;

        default:
            return false;
    }

    return false;
}

void MAVLinkParseBuffer(const uint8_t * receivedBuffer){
    mavlink_message_t message;
    mavlink_status_t messageStatus;

    //figure out what to do when the mavlink parses the buffer before it should end??
    for(uint16_t i = 0; i < UART_RX_Received_NextFreeByteIndex;i++){
        const uint8_t byte = receivedBuffer[i];

        //parse the data until its the message is decoded/refused
        if(mavlink_parse_char(MAVLINK_USART1_CHANNEL_NUM,byte,&message,&messageStatus)){
            const bool parse = MAVLinkHandleReceivedMessage(&message,&messageStatus);
        }
    }

}

#define CTU_SR_ZORA_MAVLINK_MAVLINKLIB_H

#endif //CTU_SR_ZORA_MAVLINK_MAVLINKLIB_H
