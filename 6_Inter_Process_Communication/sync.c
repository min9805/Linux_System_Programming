#include <stdio.h>
#include "synclib.h"

#define NLOOPS 5

int main(){
	int i;
	pid_t pid;

	//두 개의 pipe 생성
	TELL_WAIT();

	if((pid = fork()) < 0){
		perror("fork");
		exit(1);
	} else if (pid >0) {
		for (i = 0; i < NLOOPS; i++){
			//parent do something ..
			TELL_CHILD();
			//parent의 작업이 끝났음을 CHILD에게 알린
			printf("parent : tell to child\n");
			printf("parent : wait for child to tell\n");
			//child가 pipe를 통해 데이터를 전달하는 것을 기다린다
			WAIT_CHILD();
		}
	} else {
		for (i = 0; i < NLOOPS ; i++){
			printf("child : wait for parent to tell\n");
			//parent가 tell 할 때 까지 기다린다	
			WAIT_PARENT();
			//child do something
			//child가 할 일을 끝냈다고 parent에게 tell 한다
			TELL_PARENT();
			printf("child : tell to parent\n");
		}
	}
}
