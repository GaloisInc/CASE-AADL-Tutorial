#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#include "protocol.h"

#define TRY(_action) do{			\
    if(_action) { \
        perror(#_action); \
        exit(1); \
    } \
}while(0)

#define KEY 12345

bool authenticate(uint16_t key_them, uint16_t key_us) {
    return key_them == key_us;
}

void handle_messages(int sock) {
    msg_t msg;
    for (;;) {
	msg = receive_message(sock);
	printf("Received:\n");
	print_message(msg);

	if (msg.type == LOGIN) {
	    if (authenticate(msg.key, KEY)) {
		printf("Authenticated! Sending back AUTH\n");
		send_raw_message(sock, AUTH);
	    } else {
		printf("Failed to authenticate! Sending back UNAUTH\n");
		send_raw_message(sock, UNAUTH);
	    }
	}

	if (msg.auth == AUTH)
	    printf("Turning!\n");
	else
	    printf("Ignoring!\n");
    }
}

int main() {
    
    int sock;
    TRY((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0);
    
    struct sockaddr_in src = { .sin_family = AF_INET,
			       .sin_port = htons(SRV_PORT),
			       .sin_addr.s_addr = inet_addr("127.0.0.1") };
    socklen_t len = sizeof src;
    TRY(bind(sock, (struct sockaddr *)&src, len) < 0);

    listen(sock, 4);
    
    // thanks to https://www.freebsd.org/doc/en_US.ISO8859-1/books/developers-handbook/sockets-essential-functions.html
    // for this fun bit of code
    switch (fork()) {
    case -1: // fork didn't work
	perror("fork");
	return 0;
	break;
    default: // fork succeeded; this operation runs in the parent
	close(sock);
	return 0;
	break;
    case 0: // fork succeeded; this operation runs in the child
	break;
    }

    for (;;) {
	int comm;
	TRY((comm = accept(sock, (struct sockaddr *)&src, &len)) < 0);

	handle_messages(comm);
    }
}

