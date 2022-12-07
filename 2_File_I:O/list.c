#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 1024

int main(int argc, char *argv[]){
	FILE *fp;
	int line;
	char buf[MAX_BUF];

	//number of argument check
	if(argc != 2){
		printf("Usage: %s filename\n",argv[0]);
		exit(1);
	}

	//open argument file by read mode until EOF
	if((fp = fopen(argv[1], "rt")) == NULL){
		perror("open");
		exit(1);
	}

	//read file until EOF, print lines with line number
	line = 1;
	while((fgets(buf, MAX_BUF, fp)) != NULL){
		printf("%4d: %s", line++, buf);
	}

	fclose(fp);
}
