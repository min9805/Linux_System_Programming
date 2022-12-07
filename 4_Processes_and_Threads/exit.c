#include <stdio.h>
#include <stdlib.h>

void myexit1(){
	printf("first exit handler\n");	
}

void myexit2(){
	printf("second exit handler\n");
}
	//exit handler 등록.. stack 에 저장되어 역순으로 출력된다:
int main(int argc, char *argv[]){
	if(atexit(myexit2) != 0){
		perror("atexit");
		exit(1);
	}
	if(atexit(myexit1) != 0){
		perror("atexit");
		exit(1);
	}
	if(atexit(myexit1) != 0){
		perror("atexit");
		exit(1);
	}

	printf("main is done\n");
}
