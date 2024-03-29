//
// Created by 42R0N on 03.01.2024.
//
#pragma once

#ifndef CTU_SR_ZORA_MAVLINK_MAVLINKLIB_H

#include <string.h>

//-------------
// USE THIS FUNCTION TO SET THE MAVLINK SYSTEM PARAMETRS
//-------------
//system = mavlink_system defined in MAVLinkSetup.h
static void MAVLinkSetCurrentSystem(mavlink_system_t * system, uint8_t SysId, uint8_t CompId){
    system->sysid = SysId;
    system->compid = CompId;
}

static void MAVlinkWriteHearbeat(){


	/*
    mavlink_message_t message;
    char buf[300]= {100};

    unsigned len = mavlink_msg_heartbeat_pack( MAVlinkSystemID,MAVlinkComponentID, &message,MAV_TYPE_ROCKET,MAV_AUTOPILOT_INVALID,MAV_MODE_FLAG_DECODE_POSITION_SAFETY, 0,MAV_STATE_STANDBY);	    // Translate message to buffer	    len = mavlink_msg_to_send_buffer((uint8_t*)buf, &message);
    len = mavlink_msg_to_send_buffer((uint8_t*)buf, &message);

	 */

	mavlink_heartbeat_t heartbeat = {
	            .type = MAV_TYPE_ROCKET,
	            .autopilot = MAV_AUTOPILOT_INVALID,
	            .base_mode = MAV_MODE_FLAG_DECODE_POSITION_SAFETY,
	            .custom_mode = 0,
	            .system_status = MAV_STATE_STANDBY,
				.mavlink_version = 3
	    };

	    mavlink_msg_heartbeat_send_struct(MAVLINK_COMM_0,&heartbeat);

}

static void MAVlinkWriteProtocolVersion(){

    //TODO: Figure out the correct version hash data
    mavlink_protocol_version_t data = {
           .version = MAVLINK_MSG_ID_PROTOCOL_VERSION,
           .max_version = MAVLINK_MSG_ID_PROTOCOL_VERSION,
           .min_version = MAVLINK_MSG_ID_PROTOCOL_VERSION,
           .library_version_hash = "TESTTEST",
           .spec_version_hash = "PROTPROT"
    };

    mavlink_msg_protocol_version_send_struct(MAVLINK_COMM_0,&data);
}

static bool MAVLinkHandleLongCommands(const mavlink_command_long_t * const command){
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

static bool MAVLinkHandleReceivedMessage(mavlink_message_t * message, mavlink_status_t * messageStatus){
    switch (message->msgid) {
        case MAVLINK_MSG_ID_HEARTBEAT:
            mavlink_heartbeat_t hb;
            mavlink_msg_heartbeat_decode(message,&hb);
            return true;

        case MAVLINK_MSG_ID_PROTOCOL_VERSION:
            mavlink_protocol_version_t protocol;
            mavlink_msg_protocol_version_decode(message, &protocol);
            return true;

            //receive message of type Command
        case MAVLINK_MSG_ID_COMMAND_LONG:
            mavlink_command_long_t _command;
            mavlink_msg_command_long_decode(message, &_command);
            const mavlink_command_long_t command = _command; //convert it to a const data variable to prevent change later

            //TODO: manage ACKs


            //parse the command
            return MAVLinkHandleLongCommands(&command);
            break;

        //TODO: Implement MAVLINK_MSG_ID_COMMAND_INT

        default:
            return false;
    }

    return false;
}

static void MAVLinkParseBuffer(const uint8_t * receivedBuffer){
    mavlink_message_t message;
    mavlink_status_t messageStatus;

    //figure out what to do when the mavlink parses the buffer before it should end??

    //TODO:
    // - buffer must always be tied to the index - the index must not change during the buffer reading
    // -> implement the RX and parsing buffer as a structs and always create new instance with buffer-index pair
    // - pass const struct const pointer to this function

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
