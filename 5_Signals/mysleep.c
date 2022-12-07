#include <stdio.h>
#include <signal.h>

void SigAlarmHandler(int signo){
	printf("Terminate this process\n");

	return;
}

unsigned int mysleep(unsigned int nsecs){
	if(signal(SIGALRM, SigAlarmHandler) == SIG_ERR){
		return nsecs;
	}
	//alarm을 통해 nsecs 후에 자신에게 signal을 보낸다	
	alarm(nsecs);
	pause();
	return alarm(0);
	
}

int main(){
	printf("Wait for 5 seconds \n");

	mysleep(5);
}
