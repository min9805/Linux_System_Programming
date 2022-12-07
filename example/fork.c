#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
	pid_t	pid;

	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  {
		/* child */
		if (execl("./power","power","3","4", NULL) < 0)  {
			perror("execl");
			exit(1);
		}
	}
	else  {
		/* parent */
		wait(NULL);
	}

}
