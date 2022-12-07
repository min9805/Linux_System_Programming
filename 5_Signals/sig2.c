#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void SigUsrHandler(int signo){
	if(signo == SIGUSR1){
		printf("Received a SIGUSR1 signal\n");
	}
	else if(signo == SIGUSR2){
		printf("Received a SIGUSR2 signal\n");
	}
	else{
		printf("Recieved unknown signal\n");
		printf("Terminate this process\n");
		exit(0);
	}
}

int main(){
	//signal handler 등록
	if(signal(SIGUSR1, SigUsrHandler) == SIG_ERR){
		perror("signal1");
		exit(1);
	}
	if(signal(SIGUSR2, SigUsrHandler) == SIG_ERR){
		perror("signal2");
		exit(1);
	}
	
	for ( ; ; )
		pause();
}
