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


//convenience function for sending byte-wise data through a channel
static void mavlink_comm_send_ch(mavlink_channel_t chan, const uint8_t ch){
    if(chan == MAVLINK_COMM_0){
        HAL_UART_Transmit_IT(&huart1, &ch, 1);
    }

    //example
    /*
     * if(chan == MAVLINK_COMM_1){
     *  SEND WITH CAN
     *
     * }
     */
}

//required define for the protocol to use "mavlink_comm_send_bytes" function
#define MAVLINK_SEND_UART_BYTES
//convenience function for sending whole data block at once through a channel
//even though it has UART in its name, it has nothing to do with uart itself
static void mavlink_comm_send_bytes(mavlink_channel_t chan, const char *buf, uint16_t len){
    if(chan == MAVLINK_COMM_0){
        HAL_UART_Transmit_IT(&huart1, (uint8_t *)buf, len);
    }
}

#endif //CTU_SR_ZORA_MAVLINK_MAVLINKCONVENIECEFUNCTIONS_H
