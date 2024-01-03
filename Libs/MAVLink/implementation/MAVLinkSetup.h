//
// Created by 42R0N on 03.01.2024.
//

//-------------
// Probably no need to touch this header
//-------------
#pragma once

#ifndef CTU_SR_ZORA_MAVLINK_MAVLINKSETUP_H
#define CTU_SR_ZORA_MAVLINK_MAVLINKSETUP_H

//-------------
// Mavlink helper function necessary workarounds and methods. ORDER MATTERS
//-------------

//neccesary define in order to define the mavlink_channel_t BEFORE the header is loaded
#define HAVE_MAVLINK_CHANNEL_T
typedef enum {
    MAVLINK_COMM_0,
    MAVLINK_COMM_1,
    MAVLINK_COMM_2,
    MAVLINK_COMM_3
} mavlink_channel_t;

#include "MAVLinkConvenieceFunctions.h"

#define MAVLINK_USE_CONVENIENCE_FUNCTIONS

#define MAVLINK_ENUM_MAVLINK_SYSTEM
typedef struct MAVLinkSystemStruct {
    uint8_t sysid;   ///< Used by the MAVLink message_xx_send() convenience function
    uint8_t compid;  ///< Used by the MAVLink message_xx_send() convenience function
} mavlink_system_t;

//required to be
static mavlink_system_t mavlink_system = {.sysid=0,.compid = 0};

#include "ctu_sr_illustria_2/mavlink.h"

//-------------
// END - Mavlink helper function necessary workarounds and methods. ORDER MATTERS
//-------------

#endif //CTU_SR_ZORA_MAVLINK_MAVLINKSETUP_H

