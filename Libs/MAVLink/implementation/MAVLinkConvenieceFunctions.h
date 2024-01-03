//
// Created by 42R0N on 03.01.2024.
//
#pragma once

#ifndef CTU_SR_ZORA_MAVLINK_MAVLINKCONVENIECEFUNCTIONS_H
#define CTU_SR_ZORA_MAVLINK_MAVLINKCONVENIECEFUNCTIONS_H

//#include "mavlink_types.h"
extern UART_HandleTypeDef huart1;
//declare functions before they
static void comm_send_ch(mavlink_channel_t chan, const uint8_t ch){
    if(chan == MAVLINK_COMM_0){
        HAL_UART_Transmit_IT(&huart1, &ch, 1);
    }
}

//mavlink convenience function
static void MAVLINK_SEND_UART_BYTES(mavlink_channel_t chan, const char *buf, uint16_t len){
    if(chan == MAVLINK_COMM_0){
        HAL_UART_Transmit_IT(&huart1, (uint8_t *)buf, len);
    }
}

#endif //CTU_SR_ZORA_MAVLINK_MAVLINKCONVENIECEFUNCTIONS_H
