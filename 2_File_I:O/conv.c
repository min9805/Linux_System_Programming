#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h" 

int main(int argc, char *argv[]){
	FILE *src, *dst;
	Record rec;
	
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

	//repeat for 3 lines.. chang \n to \0
	//convert to one line
	while(fgets(rec.stud, SMAX, src)){
		*strchr(rec.stud, '\n') = '\0';
		fgets(rec.num, NMAX, src);
		*strchr(rec.num, '\n') = '\0';
		fgets(rec.dept, DMAX, src);
		*strchr(rec.dept, '\n') = '\0';

		fwrite(&rec, sizeof(rec), 1, dst);
	}

	fclose(src);
	fclose(dst);
}
