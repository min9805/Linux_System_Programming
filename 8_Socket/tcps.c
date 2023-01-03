#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include "tcp.h"

int 	Sockfd;

void CloseServer()
{
	close(Sockfd);
	printf("\nTCP Server exit.....\n");

	exit(0);
}

int main(int argc, char *argv[])
{
	int 				newSockfd, cliAddrLen, n;
	struct sockaddr_in	cliAddr, servAddr;
	MsgType				msg;

	signal(SIGINT, CloseServer);

	if ((Sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	//bzero는 servAddr 을 0으로 채운다
	bzero((char*)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	//INADDR_ANY는 이 컴퓨터에 존재하는 랜 카드 중 사용가능한 랜카드의
	//ip 주소를 사용하라는 의미
	//host to network long : Host System의 Byte order에 맞게 데이터 변
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(SERV_TCP_PORT);

	//Sockfd에 server address binding 
	if (bind(Sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
		perror("bind");
		exit(1);
	}

	//동시에 얼마나 많은 커넥션을 유지할 것인가
	listen(Sockfd, 5);

	printf("TCP Server started.....\n");

	cliAddrLen = sizeof(cliAddr);
	while(1){
		//현재 Sockfd 에client accept
		newSockfd = accept(Sockfd, (struct sockaddr *) &cliAddr, &cliAddrLen);
		if (newSockfd < 0)  {
			perror("accept");
			exit(1);
		}
		
		
		if ((n = read(newSockfd, (char *)&msg, sizeof(msg))) < 0) {
			perror("read");
			exit(1);
		}
		printf("Received request: %s.....", msg.data);

		msg.type = MSG_REPLY;
		sprintf(msg.data, "Server : This is a reply from %d.", getpid());
		if (write(newSockfd, (char *)&msg, sizeof(msg)) < 0)  {
			perror("write");
			exit(1);
		}
		printf("Replied.\n");

		usleep(10000);
		close(newSockfd);
	}
}
