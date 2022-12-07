#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int			fdin, fdout;
	char		*src, *dst;
	struct stat	statbuf;

	if (argc != 3)  {
		fprintf(stderr, "Usage: %s source destination\n", argv[0]);
		exit(1);
	}
	
	if ((fdin = open(argv[1], O_RDONLY)) < 0)  {
		perror("open");
		exit(1);
	}
	if ((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0)  {
		perror("open");
		exit(1);
	}

	if (fstat(fdin, &statbuf) < 0)  {
		perror("fstat");
		exit(1);
	}

	//파일이 하나도 없는 상태이므로 매핑할 수 없다
	//따라서 빈 파일을 만들어주는 코드
	if (lseek(fdout, statbuf.st_size-1, SEEK_SET) < 0)  {
		perror("lseek");
		exit(1);
	}
	write(fdout, "", 1);

	//mmap(0, 매핑할 때 길이 (파일 사이즈), 옵션, 옵션, file discriptor, offset)
	if ((src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0)) 
		== (caddr_t) -1)  {
		perror("mmap");
		exit(1);
	}
	//copy 할 것도 똑같이하면 write할 파일의 포인터인 dst가 존재한다
	if ((dst = mmap(0, statbuf.st_size, PROT_WRITE, MAP_SHARED, fdout, 0)) 
		== (caddr_t) -1)  {
		perror("mmap");
		exit(1);
	}
	
	//src 포인터에서 dst 포인터로 size만큼 copy한다!
	//파일에서 copy가 이루어진다
	memcpy(dst, src, statbuf.st_size);

	close(fdin);
	close(fdout);
}
