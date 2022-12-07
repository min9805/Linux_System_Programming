#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	struct stat statbuf;
	char *mode;
	int i;

	//argument 가 들어오는 만큼 작동
	for (i = 1; i < argc ; i++) {
		printf("%s: " , argv[i]);
		if (lstat(argv[i], &statbuf) < 0){
			perror("lstat");
			exit(1);
		}

		//타입 판별
		if (S_ISREG(statbuf.st_mode))
			mode = "regular";
		else if (S_ISDIR(statbuf.st_mode))
			mode = "directory";
		else if (S_ISCHR(statbuf.st_mode))
			mode = "character special";
		else if (S_ISBLK(statbuf.st_mode))
			mode = "block special";
		else if (S_ISFIFO(statbuf.st_mode))
			mode = "pipe";
		else if (S_ISLNK(statbuf.st_mode))
			mode = "symbolic link";
		else if (S_ISSOCK(statbuf.st_mode))
			mode = "socket";
		printf("%s\n", mode);

		//stat struct에 존재하는 인자들 모두 출력
		printf("st_mode : %d\n", statbuf.st_mode );
		printf("st_ino : %ld\n", statbuf.st_ino );
		printf("st_dev : %ld\n", statbuf.st_dev );
		printf("st_rdev : %ld\n", statbuf.st_rdev );
		printf("st_nlink : %ld\n", statbuf.st_nlink );
		printf("st_uid : %d\n", statbuf.st_uid );
		printf("st_gid : %d\n", statbuf.st_gid );
		printf("st_size : %ld\n", statbuf.st_size );
		printf("st_atime : %ld\n", statbuf.st_atime );
		printf("st_mtime : %ld\n", statbuf.st_mtime );
		printf("st_ctime : %ld\n", statbuf.st_ctime );
		printf("st_blksize : %ld\n", statbuf.st_blksize );
		printf("st_blocks : %ld\n", statbuf.st_blocks );
	}
}
