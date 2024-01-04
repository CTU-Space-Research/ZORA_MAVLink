//
// Created by 42R0N on 03.01.2024.
//
#pragma once

#ifndef CTU_SR_ZORA_MAVLINK_MAVLINKCOMMANDS_HPP
#define CTU_SR_ZORA_MAVLINK_MAVLINKCOMMANDS_HPP

static void setLEDs(bool green, bool orange, bool red){
    HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, green);
    HAL_GPIO_WritePin(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin, orange);
    HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, red);
}

static void MAVlinkWriteLEDstatus();
static void MAVlinkSetLEDs(const mavlink_command_long_t * const command){

    setLEDs((bool)command->param1, (bool)command->param2, (bool)command->param3);

    mavlink_command_ack_t ack = {
            .command = command->command,
             .progress = 100, //meaning that 100% of command has been executed; only relevant for COMMAND_IN_PROGRESS
            .result = MAV_RESULT_ACCEPTED
    };
    mavlink_msg_command_ack_send_struct(MAVLINK_COMM_0,&ack);

    HAL_Delay(150);

    MAVlinkWriteLEDstatus();
}


#endif //CTU_SR_ZORA_MAVLINK_MAVLINKCOMMANDS_HPP
