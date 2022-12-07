#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	if(argc != 2){
		fprintf(stderr, "Usage: %s dirname\n", argv[0]);
		exit(1);
	}

	if(chdir(argv[1]) < 0 ){
		perror("chdir");
		exit(1);
	}
}
