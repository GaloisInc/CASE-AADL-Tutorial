#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "protocol.h"

#define TRY(_action) do{ \
    if(_action) { \
        perror(#_action); \
        exit(1); \
    } \
}while(0)

static void turn_left(double a) {
    printf("\tTURNING LEFT BY %.2f DEGREES\n", a);
}

static void turn_right(double a) {
    printf("\tTURNING RIGHT BY %.2f DEGREES\n", a);
}

static void handle_message(int sock) {
    int bytes;
    turn_msg_t msg = { .u16 = 0 };

    // Intentionally don't check the length of the received message
    bytes = recvfrom(sock, msg.bytes, sizeof msg, 0, NULL, NULL);
    msg.u16 = ntohs(msg.u16);

    printf("VEHICLE: received a turn msg: %s\n", turn_msg_string(msg));
    switch(msg.direction) {
        case LEFT:
            turn_left(angle(msg));
            break;
        case RIGHT:
            turn_right(angle(msg));
            break;
    }
}

int main(void) {
    int sock;
    TRY((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0);

    in_addr_t localhost;
    TRY(!(localhost = inet_addr("127.0.0.1")));

    struct sockaddr_in src = {
        .sin_family = AF_INET,
        .sin_port   = SRV_PORT,
        .sin_addr   = { .s_addr = localhost },
    };

    TRY(bind(sock, (struct sockaddr *)&src, sizeof src));

    for(;"ever";)
        handle_message(sock);

    return 0;
}
