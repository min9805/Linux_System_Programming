#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void SigChildHandler(int signo){
	printf("SIGCHLD .. child process killed\n");
}

int main()
{
	pid_t	pid;
	int		status;
	
	signal(SIGCHLD, SigChildHandler);

	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  {
		printf("I'm a child\n");
		sleep(2);
	}
	else  {
		while(1){
		}
		printf("A child killed with %d status\n", status);
	}
}
