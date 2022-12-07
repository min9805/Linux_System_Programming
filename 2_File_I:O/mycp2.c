#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 1024

int main(int argc, char *argv[]){
	FILE *src, *dst;
	char buf[MAX_BUF];
	int cnt;
	
	//number of argument check
	if(argc != 3){
		printf("Usage: %s source destination", argv[0]);
		exit(1);
	}		
	
	//fopen source file, error check
	if((src = fopen(argv[1], "rt")) == NULL){
		perror("fopen");
		exit(1);
	}

	//fopen destination file, error check
	if((dst = fopen(argv[2], "wt")) == NULL){
		perror("fopen");
		exit(1);
	}
	
	//read, write by Direct I/O
	//save number of read bytes to cnt
	while((cnt = fread(buf, 1, MAX_BUF, src)) > 0){
		fwrite(buf, 1, cnt, dst);
	}
	
	fclose(src);
	fclose(dst);		
}
