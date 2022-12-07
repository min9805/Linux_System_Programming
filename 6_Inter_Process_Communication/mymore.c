#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int fd[2];
	pid_t child;

	if(pipe(fd) == -1){
		perror("pipe");
		exit(1);
	}

	child = fork();
	if(child == (pid_t)0){
		//dup는 파일 디스크립터를 copy하기에 stdin을 close 해준다
		close(1);
		//child pipe의read 부분을 close 
		close(fd[0]);

		//비어있는 파일 디스크립터에 fd[1]을 copy한다..
		dup(fd[1]);
		execlp("ls", "ls", "-l", NULL);
	} else {
		//위와 동일하게 stdout을 바꿀 것이므로 close
		close(0);
		close(fd[1]);

		//0번째 파일 디스크립터에 fd[0]을 copy한다..
		dup2(fd[0],0);	
		execlp("more", "more", NULL);
	}
}
