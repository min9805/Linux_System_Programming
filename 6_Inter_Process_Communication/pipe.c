#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_BUF 128

int main(){
	int n, fd[2];
	pid_t pid;
	char buf[MAX_BUF];

	if(pipe(fd) <0){
		perror("pipe");
		exit(1);
	}
	if((pid = fork()) < 0){
		perror("fork");
		exit(1);
	} else if (pid ==0) {
		//child process는 데이터를 받기만 하므로 보내는 fd[1] close
		close(fd[1]);
		printf("child : wait for parent to send data\n");
		//pipe에 읽을 데이터가 없을 때 read 하면 해당 프로세스를 wait 시킨다
		if((n = read(fd[0], buf, MAX_BUF)) < 0 ){
			perror("read");
			exit(1);
		}
		printf("child : received data from parent : ");
		fflush(stdout);
		write(STDOUT_FILENO, buf, n); 
	} else {
		sleep(1);
		//parent process는 데이터를 보낼 역할이므로 fd[0] close
		close(fd[0]);
		strcpy(buf, "Hello, world!\n");
		printf("parent: send data to child\n");
		write(fd[1], buf, strlen(buf)+1);
	}

	exit(0);
}
