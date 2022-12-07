#include <stdio.h>
#include <signal.h>
#include <pwd.h>
#include <stdlib.h>

void MyAlarmHandler(int signo){
	struct passwd *rootptr;

	signal(SIGALRM, MyAlarmHandler);
	alarm(1);
	
	printf("in signal handler\n");
	
	if((rootptr = getpwnam("root")) == NULL) {
		perror("getpwnam");
		exit(1);
	}
	return;
}
//같은 함수내로 들어가서 struct 를 root로 변경해버리기 때문에 
//충돌이 발생한다
int main(){
	struct passwd *ptr;
	
	signal(SIGALRM, MyAlarmHandler);
	alarm(1);

	for( ; ; ) {
		if((ptr = getpwnam("lsp07")) == NULL){
			perror("getpwnam");
			exit(1);
		}
		if (strcmp(ptr->pw_name, "lsp07") != 0){
			printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
			exit(0);
		}
	}
}
