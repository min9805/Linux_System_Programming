#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 1024

int main(int argc, char *argv[]){
	FILE *src1, *src2, *dst;
	char buf[MAX_BUF];
	int count;
	
	//check number of arguments
	if(argc != 4){
		printf("Usage: %s soruce1 source2 destination", argv[0]);
		exit(1);
	}

	//open source file 1
	if((src1 = fopen(argv[1],"rt")) == NULL){
		perror("fopen");
		exit(1);
	}
	
	//open source file 2
	if((src2 = fopen(argv[2],"rt")) == NULL){
		perror("fopen");
		exit(1);
	}

	//open destination file
	if((dst = fopen(argv[3],"wt")) == NULL){
		perror("fopen");
		exit(1);
	}

	//read,write source file 1 then rw source file 2
	while((count = fread(buf, 1, MAX_BUF, src1)) > 0){
		fwrite(buf, 1, count, dst);
	}
	
	while((count = fread(buf, 1, MAX_BUF, src2)) > 0){
		fwrite(buf, 1, count, dst);
	}

	fclose(src1);
	fclose(src2);
	fclose(dst);
}
