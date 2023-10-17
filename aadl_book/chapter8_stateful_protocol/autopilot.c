#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#include "common.h"

static enum state do_state(int sock, enum state state)
{
    enum state next_state = state;
    union { char bytes[1024]; struct msg msg; } buf;

    printf("VEHICLE:\t\t\t\tstate is %s\n", state_string(state));

    switch(state) {
        case BOOTING:
            next_state = STANDBY;
            break;
        case UPDATING:
            next_state = BOOTING;
            break;
        default:
            TRY(recv(sock, buf.bytes, sizeof buf, 0) < 0);
            printf("VEHICLE: got a message: %s\n", msg_string(&buf.msg));

            switch(buf.msg.tag) {
                case LAND:
                    next_state = STANDBY;
                    break;
                case TAKE_OFF:
                    next_state = FLYING;
                    break;
                case UPDATE:
                    next_state = UPDATING;
                    break;
                case REBOOT:
                    if(state != FLYING)
                        next_state = BOOTING;
                    else
                        puts("VEHICLE: ignoring reboot while in flight");
                    break;
                default:
                    break;
            }
    }

    return next_state;
}

int main(void)
{
    srand(time(NULL));

    int sock;
    TRY((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0);

    in_addr_t localhost;
    TRY(!(localhost = inet_addr("127.0.0.1")));

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port   = SRV_PORT,
        .sin_addr   = { .s_addr = localhost },
    };
    TRY(bind(sock, (struct sockaddr *)&addr, sizeof addr));

    enum state state = BOOTING;
    for(;"ever";)
        state = do_state(sock, state);

    return 0;
}
