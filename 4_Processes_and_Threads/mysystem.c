#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

#define MAX_CMD 256

void exec(char *cmd){
	//char* path = strcat("/bin/", cmd);
	//printf("%s",path);
	if (execl("/bin/sh", "sh", "-c" , cmd, NULL) < 0)  {
			perror("execl");
			exit(1);
	}
}

int mysystem(char *cmd){
	pthread_t tid;
	
	if(pthread_create(&tid,NULL, exec, cmd) < 0 ){
		perror("pthread_create");
	} 
	pthread_join(tid, NULL);
}

int main(){
	char cmd[MAX_CMD];

	while(1) {
		fgets(cmd, MAX_CMD, stdin);
		if(cmd[0] == 'q')
			break;
		mysystem(cmd);
	} 	 
}
