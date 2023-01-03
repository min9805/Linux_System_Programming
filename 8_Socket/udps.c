#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdlib.h>
#include "udp.h"

int Sockfd;

//registe signal
void CloseServer(){
	close(Sockfd);
	printf("\nUDP Server exit...\n");
	
	exit(0);
}

int main(int argc, char *argv[]){
	int						cliAddrLen, n;
	struct sockaddr_in		cliAddr, servAddr;
	MsgType					msg;

	signal(SIGINT, CloseServer);

	//create socket
	if ((Sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(SERV_UDP_PORT);

	//binding this socket to server
	if (bind(Sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
		perror("bind");
		exit(1);
	}

	printf("UDP Server started ... \n");
	//UDP add address, len for recv, send

	cliAddrLen = sizeof(cliAddr);
	while(1) {
		//recvfrom clisocket.
		if ((n = recvfrom(Sockfd, (char *)&msg, sizeof(msg), 0,
					(struct sockaddr *)&cliAddr, &cliAddrLen)) < 0) {
			perror("recvfrom");
			exit(1);
		}
		printf("Received request: %s ....", msg.data);
		
		msg.type = MSG_REPLY;
		sprintf(msg.data, "Server : This is a reply from %d", getpid());
		if (sendto(Sockfd, (char *)&msg, sizeof(msg), 0,
					(struct sockaddr *)&cliAddr, cliAddrLen) < 0 ) {
			perror("sendto");
			exit(1);
		}
		printf("Replied.\n");
	}
}
