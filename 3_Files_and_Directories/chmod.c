#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	struct stat statbuf;
	
	//extract stat of "bar"
	if( stat("bar", &statbuf) < 0 ) {
		perror("stat");
		exit(1);
	}

	//IWGRP 를 0으로 만들고 ISUID 비트 추가
	if (chmod("bar", (statbuf.st_mode & ~S_IWGRP) | S_ISUID) < 0 ) {
		perror("chmod");
		exit(1);
	}

	//turn on the bit
	if( chmod("foo", (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0 ) {
		perror("chmod");
		exit(1);
	}
}
