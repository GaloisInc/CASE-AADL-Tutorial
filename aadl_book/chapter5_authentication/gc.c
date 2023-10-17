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

#define KEY_GOOD 12345
#define KEY_BAD  12346

int main() {
    int sock;
    TRY((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0);
    
    struct sockaddr_in dst = { .sin_family = AF_INET,
			       .sin_port = htons(SRV_PORT),
			       .sin_addr.s_addr = inet_addr("127.0.0.1") };
    socklen_t len = sizeof dst;
    TRY(connect(sock, (struct sockaddr *)&dst, len) < 0);

    srand(time(0));
    
    printf("Sending:\n");
    if (rand() % 2 == 0) 
	print_message(send_login(sock, KEY_GOOD));
    else
	print_message(send_login(sock, KEY_BAD));

    msg_t response = receive_message(sock);
    uint16_t auth;
    if (msg_u16(response) == AUTH) {
	printf("Authorized!\n");
	auth = AUTH;
    } else {
	printf("Unauthorized!\n");
	auth = UNAUTH;
    }
    
    uint16_t angle, dir;
    for (;;) {
	sleep(rand() % 3 + 1);

	angle = rand() % 360;
    	if (rand() % 2 == 0)
	    dir = LEFT;
    	else
	    dir = RIGHT;
	
	printf("\nSending:\n");
	print_message(send_message(sock, auth, angle, dir));

    }
}


