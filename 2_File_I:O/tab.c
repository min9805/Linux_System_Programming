#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 1024

int main(int argc, char *argv[]){
	FILE *src, *dst;
	char buf[MAX_BUF];
	int ch;
	
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

	if((dst = fopen(argv[2], "wt")) == NULL){
		perror("fopen");
		exit(1);
	}

	//get char from src, check it is \t
	//if \t put 4 space, else put ch
	while((ch = fgetc(src)) != EOF){
		if(ch == '\t'){
			fputc(' ', dst);
			fputc(' ', dst);
			fputc(' ', dst);
			fputc(' ', dst);
		}
		else {
			fputc(ch, dst);
		}
	}

	fclose(src);
	fclose(dst);
}
