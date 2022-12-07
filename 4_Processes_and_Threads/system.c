#include <stdio.h>
#include <stdlib.h>

int main(){
	int status;
	
	//system 함수를 통해 date 라는 명령어를 실행하고 종료 반환값을 
	//status 에 저장한다
	if((status = system("date")) <0) {
		perror("system");
		exit(1);
	}
	printf("exit status = %d\n", status);

	if((status = system("nosuchcommand")) < 0) {
		perror("system");
		exit(1);
	}
	printf("exit status = %d\n", status);
			
	if((status = system("who; exit 44")) < 0) {
		perror("system");
		exit(1);
	}
	printf("exit status = %d\n", status);
}
