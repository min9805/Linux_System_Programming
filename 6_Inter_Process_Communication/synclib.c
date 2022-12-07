#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static int Pfd1[2], Pfd2[2];

void TELL_WAIT(void){
	if (pipe(Pfd1) < 0 || pipe(Pfd2) < 0) {
		perror("pipe");
		exit(1);
	}
}

void TELL_PARENT(void){
	if (write(Pfd2[1], "c", 1) != 1){
		perror("write");
		exit(1);
	}
}

void WAIT_PARENT(void){
	char c;
	if (read(Pfd1[0], &c, 1) != 1){
		perror("read");
		exit(1);
	}
}
	
void TELL_CHILD(void){
	if (write(Pfd1[1], "p", 1) != 1){
		perror("write");
		exit(1);
	}	
}

void WAIT_CHILD(void){
	char c;
	
	if (read(Pfd2[0], &c, 1) != 1){
		perror("read");
		exit(1);
	}
	if (c != 'c'){
		fprintf(stderr, "WAIT_CHILD : incorrect data");
		exit(1);
	}
}
