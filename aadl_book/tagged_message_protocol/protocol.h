#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#include <stdint.h>
#include <stdio.h>

#define SRV_PORT 9001

typedef union {
    char bytes[sizeof(uint16_t)];
    uint16_t u16;
    struct {
        uint16_t direction   : 1;
        uint16_t angle_fixed : 15;
    };
} turn_msg_t;

_Static_assert(sizeof(turn_msg_t) == sizeof(uint16_t),
        "turn_msg_t must be 16 bits");

#define LEFT 0
#define RIGHT 1

static double angle(turn_msg_t msg) {
    return ((float)msg.angle_fixed) / 100;
}

static char *turn_msg_string(turn_msg_t msg) {
    static char buf[1024];

    snprintf(buf, sizeof buf, "turn %s %.2f degrees",
            msg.direction == LEFT ? "left" : "right", angle(msg));

    return buf;
}

#endif
