#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	//chech number of arguments
	if(argc == 1) {
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		exit(1);
	}

	//argument를 모두 돌아가면서 remove
	int i;
	for (i=0; i < argc ; i++){
		if (remove(argv[i]) < 0){
			perror("remove");
			exit(1);
		}
	}	
}
