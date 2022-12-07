#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	FILE *src, *dst;
	int ch;

	//number of argument check
	if(argc != 3){
		printf("Usage: %s source destination\n", argv[0]);
		exit(1);
	}

	//fopen source file
	if((src = fopen(argv[1], "rt")) == NULL) {
		perror("fopen");
		exit(1);
	}

	//fopen destination file
	if((dst = fopen(argv[2], "wt")) == NULL) {
		perror("fopen");
		exit(1);
	}

	//read source file by Char until EOF
	//put Char to destination file
	while((ch = fgetc(src)) != EOF){
		fputc(ch, dst);
	}

	fclose(src);
	fclose(dst);
}
