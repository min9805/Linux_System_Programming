#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 1024

int main(int argc, char *argv[]){
	FILE *src, *dst;
	char buf[MAX_BUF];
	
	//check number of argument
	if(argc != 3){
		printf("Usage : %s source destination", argv[0]);
		exit(1);
	}

	//feopn source file with error checking
	if((src = fopen(argv[1], "rt")) == NULL){
		perror("fopen");
		exit(1);
	}
	
	//fopen destination file with eroor checking
	if((dst = fopen(argv[2], "wt")) == NULL){
		perror("fopen");
		exit(1);
	}

	//read source file by line and put
	while(fgets(buf,MAX_BUF, src) != NULL){
		fputs(buf, dst);
	}

	fclose(src);
	fclose(dst);
}
