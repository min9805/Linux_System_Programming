#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){
	pid_t pid;
	int status;	

	if((pid = fork()) < 0){
		perror("fork");
		exit(1);
	}
	else if (pid == 0) {
		printf("I'm a child\n");
		sleep(2);
	} else {
		wait(&satus);
		printf("A child killed with %d status\n", status);
	}
}
