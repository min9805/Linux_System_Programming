#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

static unsigned int AlarmSecs;

void SigAlarmHandler(int signo){
	//unix 에서는 핸들러를 한 번 사용하면 사라지기 때문에 매 번 재등록해주는 과정이다
	if(signal(SIGALRM, SigAlarmHandler) == SIG_ERR){
		perror("signal");
		exit(1);
	}

	alarm(AlarmSecs);
	
	//do Something

	printf(".");
	fflush(stdout);
	
	return;
}

void SetPeriodAlarm(unsigned int nsecs){
	if(signal(SIGALRM, SigAlarmHandler) == SIG_ERR){
		return -1;
	}
	AlarmSecs = nsecs;

	alarm(nsecs);
		
	return 0;
	
}

int main(){
	printf("Doing something every one seconds\n");
	
	SetPeriodAlarm(1);

	for( ; ; )
		pause();	
}
