#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <stdlib.h>

#define THREAD_MAIN

#define THREAD_1
#define THREAD_2

void SigIntHandler(int signo){
	printf("Received a SIGINT signal by thread %d\n", pthread_self());
	printf("Terminate this process\n");
	//마지막에 종료시키는 스레드가 어느 스레드인지 확인하는 작업,, main thread 이다!	
	exit(0);
}

void Thread1(void *dummy){
	signal(SIGINT, SigIntHandler);
}
void Thread2(void *dummy){
	signal(SIGINT, SigIntHandler);
}

int main(){
	pthread_t tid1, tid2;

	if(pthread_create(&tid1, NULL, (void*)Thread1, NULL) < 0){
		perror("pthread_create");
		exit(1);
	}
	if(pthread_create(&tid2, NULL, (void*)Thread1, NULL) < 0){
		perror("pthread_create");
		exit(1);
	}
	
	printf("Create two threads: tid1=%d, tid2=%d\n", tid1, tid2);
	printf("Main thread: tid=%d\n", pthread_self());

	signal(SIGINT, SigIntHandler);

	printf("Press ^C to quit\n");

	for ( ; ; )
		pause();
}
