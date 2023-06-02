#ifndef _COMMON_H
#define _COMMON_H

#include <stdint.h>
#include <stdio.h>

#define TRY(_action) do{ \
    if(_action) { \
        perror(#_action); \
        exit(1); \
    } \
}while(0)

#define SRV_PORT 9001

enum state {
    BOOTING,
    STANDBY,
    FLYING,
    UPDATING,
    _STATE_CT,
};

enum msg_type {
    TAKE_OFF,
    LAND,
    REBOOT,
    UPDATE,
    _MSG_TYPE_CT,
};

#define MSG_SIZE(_msg) \
    (sizeof(_msg) + ((_msg).tag == UPDATE ? (_msg).fw_datasz : 0))

struct msg {
    union {
        uint16_t u16;
        struct {
            uint16_t tag       : 2;
            uint16_t fw_datasz : 14;
        };
    };
    char fw_data[];
};

_Static_assert(sizeof(struct msg) == sizeof(uint16_t),
        "struct msg must be 16 bits");

static const char * __attribute__((unused))
state_string(enum state state)
{
    static char buf[64];

    switch(state) {
        case BOOTING:
            strcpy(buf, "BOOTING");
            break;
        case STANDBY:
            strcpy(buf, "STANDBY");
            break;
        case FLYING:
            strcpy(buf, "FLYING");
            break;
        case UPDATING:
            strcpy(buf, "UPDATING");
            break;
        default:
            snprintf(buf, sizeof buf, "Unknown state: %d", state);
    }

    return buf;
}

static const char * __attribute__((unused))
msg_string(struct msg *msg)
{
    static char buf[64];

    switch(msg->tag) {
        case TAKE_OFF:
            strcpy(buf, "TAKEOFF");
            break;
        case LAND:
            strcpy(buf, "LAND");
            break;
        case REBOOT:
            strcpy(buf, "REBOOT");
            break;
        case UPDATE:
            snprintf(buf, sizeof buf, "UPDATE: %u bytes", msg->fw_datasz);
            break;
        default:
            snprintf(buf, sizeof buf, "Unknown tag: %d", msg->tag);
    }

    return buf;
}

#endif // _COMMON_H
