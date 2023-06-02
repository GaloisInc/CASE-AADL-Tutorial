#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#include "protocol.h"

uint16_t msg_u16(msg_t msg) {
    return msg.u16;
}

msg_t send_message(int sock, uint16_t auth,
		  uint16_t angle, uint16_t direction) {
    msg_t msg;
    msg.type = TURN;
    msg.auth = auth;
    msg.direction = direction;
    msg.angle = angle;
    
    msg.u16 = htons(msg.u16);
    send(sock, msg.bytes, sizeof msg, 0);

    msg.u16 = ntohs(msg.u16);
    return msg;
}

msg_t send_login(int sock, uint16_t key) {
    msg_t msg;
    msg.type = LOGIN;
    msg.key = key & 0x7fff;
    
    msg.u16 = htons(msg.u16);
    send(sock, msg.bytes, sizeof msg, 0);

    msg.u16 = ntohs(msg.u16);
    return msg;
}

msg_t receive_message(int sock) {
    msg_t msg;
    int received;
    TRY((received = recv(sock, msg.bytes, sizeof msg, 0)) < 0);
    assert(received > 0);
    msg.u16 = ntohs(msg.u16);
    return msg;
}

msg_t send_raw_message(int sock, uint16_t u16) {
    msg_t msg;
    msg.u16 = htons(u16);
    send(sock, msg.bytes, sizeof msg, 0);

    msg.u16 = ntohs(u16);
    return msg;
}

void print_message(msg_t msg) {
    if (msg.type == LOGIN) {
	printf("  Type: LOGIN\n"
	       "  Key: %#06x\n",
	       msg.key);
    } else {
	printf("  Type: TURN\n"
	       "  Auth: %s\n"
	       "  Direction: %s\n"
	       "  Angle: %i\n",
	       msg.auth == AUTH ? "AUTH" : "UNAUTH",
	       msg.direction == LEFT ? "LEFT" : "RIGHT",
	       msg.angle);
    }
}
