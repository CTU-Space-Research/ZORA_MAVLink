//
// Created by 42R0N on 03.01.2024.
//
#pragma once

#ifndef CTU_SR_ZORA_MAVLINK_MAVLINKMESSAGES_H
#define CTU_SR_ZORA_MAVLINK_MAVLINKMESSAGES_H

#include <string.h>

static void MAVlinkWriteLEDstatus(){

    GPIO_PinState G = HAL_GPIO_ReadPin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
    GPIO_PinState O = HAL_GPIO_ReadPin(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin);
    GPIO_PinState R = HAL_GPIO_ReadPin(LED_RED_GPIO_Port, LED_RED_Pin);

    mavlink_zora_led_status_t ledStatus = {
            .LED_GREEN_STATUS = G,
            .LED_ORANGE_STATUS = O,
            .LED_RED_STATUS = R
    };

    mavlink_msg_zora_led_status_send_struct(MAVLINK_COMM_0,&ledStatus);
}

#endif //CTU_SR_ZORA_MAVLINK_MAVLINKMESSAGES_H
