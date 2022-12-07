#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc != 2)  {
		fprintf(stderr, "Usage: %s dirname\n", argv[0]);
		exit(1);
	}

	//argv[1]의 이름으로 디렉토리 생성
	if(mkdir(argv[1], 0755) < 0){
		perror("mkdir");
		exit(1);		
	}
}
