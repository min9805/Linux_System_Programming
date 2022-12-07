#include <stdio.h>
#include <signal.h>

void SigIntHandler(int signo){
	printf("Received a SIGINT signal\n");
	printf("Terminate this process\n");

	exit(0);
}

int main(){
	//signal handler 등록
	signal(SIGINT, SigIntHandler);
	
	printf("Press ^C to quit \n");
	for ( ; ; )
		pause();
}
