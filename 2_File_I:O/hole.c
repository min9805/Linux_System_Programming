#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int fd;
	char ch = '\0';
	
	//create the file 
	if((fd = creat("file.hole", 0400)) < 0){
		perror("creat");
		exit(1);
	}

	//파일의 처음부터 1023만큼 파일 포인터를 이동시킨다.
	//return value check
	if((lseek(fd, 1023, SEEK_SET)) < 0){
		perror("lseek");
		exit(1);
	}
	
	//write ch at 1024
	write(fd, &ch, 1);

	close(fd);
}
