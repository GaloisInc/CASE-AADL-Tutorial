#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#include "protocol.h"

#define TRY(_action) do{ \
    if(_action) { \
        perror(#_action); \
        exit(1); \
    } \
}while(0)

static void send_command(int sock, struct sockaddr_in *dst) {
    turn_msg_t msg = {
        .direction   = rand() % 2,
        .angle_fixed = 100 * (rand() % 180) + (rand() % 100),
    };
    printf("CONTROL: sending turn msg: %s\n", turn_msg_string(msg));

    msg.u16 = htons(msg.u16);
    sendto(sock, msg.bytes, sizeof msg, 0,
            (struct sockaddr *)dst, sizeof *dst);
}

int main(void) {
    srand(time(NULL));

    int sock;
    TRY((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0);

    in_addr_t localhost;
    TRY(!(localhost = inet_addr("127.0.0.1")));

    struct sockaddr_in dst = {
        .sin_family = AF_INET,
        .sin_port   = SRV_PORT,
        .sin_addr   = { .s_addr = localhost },
    };

    for(;"ever";) {
        send_command(sock, &dst);

        sleep(rand() % 3 + 1);
    };

    return 0;
}
