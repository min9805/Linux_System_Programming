#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int Var = 6;
char Buf[] = "a write to stdout\n";

int main(int argc, char *argv[]){
	int var;
	pid_t pid;

	var = 88;	
	//printf 와 동일한 작업
	write(STDOUT_FILENO, Buf, sizeof(Buf)-1);
	printf("Before fork\n");	

	if((pid = fork()) < 0){
		perror("fork");
		exit(1);
	}
	else if (pid == 0) {
		Var++;
		var++;
	} else {
		sleep(2);
	}
	//fork 하는 순간 두 개의 메모리 공간이 생기기 때문에 각 프로세스의	
	//변수는 ㄱ별개의 변수이다. 저장 공간도 다르기 때문에 출력값이 다르다
	printf("pid = %d, Var = %d, var = %d \n", getpid(), Var, var);
}
