#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "tcp.h"

int main(int arc, char * argv[]){
	int 					sockfd, n;
	struct sockaddr_in		servAddr;
	MsgType					msg;

	//create socket
	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}
	
	//create servAddr info
	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
	servAddr.sin_port = htons(SERV_TCP_PORT);

	//connect with server 
	if (connect(sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
		perror("connect");
		exit(1);
	}
	
	//write data to server
	msg.type = MSG_REQUEST;
	sprintf(msg.data, "Client : This is a request from %d.", getpid());
	if (write(sockfd, (char *)&msg, sizeof(msg)) < 0){
		perror("write");
		exit(1);
	}
	printf("sent a request..");
	
	//read from server
	if ((n = read(sockfd, (char *)&msg, sizeof(msg))) < 0 ){
		perror("read");
		exit(1);
	}
	printf("Recieved reply: %s\n", msg.data);

	close(sockfd);
}
