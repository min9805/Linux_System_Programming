#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	FILE *src;
	char buf[256];
	int ch;	
	
	//argument 개수 체크
	if(argc != 2){
		fprintf(stderr, "Usage: %s source destination\n", argv[0]);
		exit(1);
	}

	//r+ 로 file open, return value check	
	if((src = fopen(argv[1],"r+t")) <0 ){
		perror("fopen");
		exit(1);
	}

	//fgetc로 char 단위로 받아와서 대문자인지 검사 후 대문자면 32를 빼고
	//파일의 포인터를 하나 다시 미룬다음 fputc
	while((ch = fgetc(src)) != EOF){
		if(ch>96 && ch < 123){
			ch = ch - 32;
			ungetc(ch, src);	
			fputc(ch,src);
		}
	}

	fclose(src);
}
