#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	char buf[256];

	if(getcwd(buf, 256) == NULL){
		perror("getcwd");
		exit(1);
	}

	printf("%s\n", buf);
}
