#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_BUF 1024

//save current location of file pointer
//move fp to end of file for get the size of file
long filesize(FILE *fp){
	long cur, size;

	cur = ftell(fp);
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, cur, SEEK_SET);
	return size;
}

int main(int argc, char *argv[]){
	FILE *src, *dst1, *dst2;
	char buf[MAX_BUF];
	int count, size;

	if(argc != 4) {
		printf("Usage : %s source destination1 destination2\n", argv[0]);
		exit(1);		
	}	

	if((src = fopen(argv[1], "rt")) == NULL){
		perror("fopen");
		exit(1);
	}
	if((dst1 = fopen(argv[2], "wt")) == NULL){
		perror("fopen");
		exit(1);
	}
	if((dst2 = fopen(argv[3], "wt")) == NULL){
		perror("fopen");
		exit(1);
	}

	//save split file size
	size = filesize(src) / 2;
	
	//rw to split file size,,
	while(size > 0) {
		count = (size > MAX_BUF) ? MAX_BUF : size;
		fread(buf, 1, count, src);
		fwrite(buf, 1, count, dst1);
		size -= count;
	}

	//rw others
	while((count = fread(buf, 1, MAX_BUF, src)) > 0){
		fwrite(buf, 1, count, dst2);
	}

	fclose(src);
	fclose(dst1);
	fclose(dst2);
}
