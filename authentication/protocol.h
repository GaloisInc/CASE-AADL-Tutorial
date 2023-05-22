#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#define SRV_PORT 9001

#define TURN  0
#define LOGIN 1

#define UNAUTH 0
#define AUTH   1

#define LEFT  0
#define RIGHT 1

#define TRY(_action) do{ \
    if(_action) { \
        perror(#_action); \
        exit(1); \
    } \
}while(0)

typedef union {
    char bytes[sizeof(uint16_t)];
    uint16_t u16;
    struct {
	uint16_t type : 1;
        uint16_t _body : 15;
    };
    struct {
	uint16_t _type : 1;
	uint16_t auth : 1;
	uint16_t direction : 1;
	uint16_t angle : 13;
    } ;
    struct {
	uint16_t __type : 1;
	uint16_t key : 15;
    } ;
} msg_t;

msg_t send_raw_message(int sock, uint16_t msg);
msg_t send_message(int sock, uint16_t auth,
		   uint16_t angle, uint16_t direction);
msg_t send_login(int sock, uint16_t key);

uint16_t msg_u16(msg_t msg);

msg_t receive_message(int sock);

void print_message(msg_t msg);

#endif // _PROTOCOL_H
