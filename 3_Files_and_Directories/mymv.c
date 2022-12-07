#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	//chech number of arguments
	if(argc !3) {
		fprintf(stderr, "Usage: %s old new\n", argv[0]);
		exit(1);
	}

	//argv[1] 파일의 이름을 argv[2]로 변경한다
	if (rename(argv[1], argv[2]) < 0){
		perror("rename");
		exit(1);
	}	
}
