//
// Created by 42R0N on 03.01.2024.
//
#pragma once

#ifndef CTU_SR_ZORA_MAVLINK_MAVLINKMESSAGES_H
#define CTU_SR_ZORA_MAVLINK_MAVLINKMESSAGES_H

#include <string.h>

static bool MAVlinkWriteLEDstatus(){

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

#endif //CTU_SR_ZORA_MAVLINK_MAVLINKMESSAGES_H
