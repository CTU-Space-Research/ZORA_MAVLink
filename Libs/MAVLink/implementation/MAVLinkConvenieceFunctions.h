//
// Created by 42R0N on 03.01.2024.
//
#pragma once

#ifndef CTU_SR_ZORA_MAVLINK_MAVLINKCONVENIECEFUNCTIONS_H
#define CTU_SR_ZORA_MAVLINK_MAVLINKCONVENIECEFUNCTIONS_H

//#include "mavlink_types.h"
extern UART_HandleTypeDef huart1;

//-------------
// In the mavlink generated libraries, these functions are called by "_mavlink_send_uart" function
// It is misleading, it has NOTHING TO DO WITH UART. These functions are used as a general connection interface
// which every mavlink_msg....._send() / _send_struct() function uses

// By defining more channels, you can send different messages through different physical connections = UART/CAN/SPI...
// but their implementation has to be defined in these function
//-------------

//TODO:
// - create a TX queue
// - always push the message to a queue
// - scheduler /other worker will process the message once the line is idle
// - implement "delay" to the message - that the message will be send after X ms after adding it to the queue;
// to prevent line congestion


//convenience function for sending byte-wise data through a channel
static void mavlink_comm_send_ch(mavlink_channel_t chan, const uint8_t ch){

    switch (chan) {
        case MAVLINK_CHAN_DEFAULT:
            //do NOT use the 0 channel.
            //Always explicitly state what channel you want to use
            return;
            break;

        case MAVLINK_CHAN_UART:

            //wait until the TX register is not empty
            while(!__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TC)){}
            HAL_UART_Transmit_IT(&huart1, &ch, 1);

        case MAVLINK_CHAN_RocketBus:

            //TODO: IMMPLEMENT

        case MAVLINK_CHAN_RocketLink:

            //TODO: IMMPLEMENT

        default:
            return;

    }
}

//required define for the protocol to use "mavlink_comm_send_bytes" function
#define MAVLINK_SEND_UART_BYTES
//convenience function for sending whole data block at once through a channel
//even though it has UART in its name, it has nothing to do with uart itself
static void mavlink_comm_send_bytes(mavlink_channel_t chan, const char *buf, uint16_t len){

    switch (chan) {
        case MAVLINK_CHAN_DEFAULT:
                //do NOT use the 0 channel.
                //Always explicitly state what channel you want to use
                return;
            break;

        case MAVLINK_CHAN_UART:
            //wait until the TX register is not empty
            while(!__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TC)){}
            HAL_UART_Transmit_IT(&huart1, (uint8_t *)buf, len);

        case MAVLINK_CHAN_RocketBus:

            //TODO: IMMPLEMENT

        case MAVLINK_CHAN_RocketLink:

            //TODO: IMMPLEMENT

        default:
            return;

    }
}

#endif //CTU_SR_ZORA_MAVLINK_MAVLINKCONVENIECEFUNCTIONS_H
