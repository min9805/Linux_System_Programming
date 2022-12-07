#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	DIR *dp;
	struct dirent *drp;

	//현재 디렉토리를 open 하는 데 에러로 NULL 이 반환되는 경우 체크
	if((dp = opendir(".")) == NULL){
		perror("opendir");
		exit(0);
	}
	
	//readdir 의 반환값이 dirent 이므로 받아서 루프를 돌리고
	//struct ㄴ의 디렉토리 네임을 출력한다
	while(drp = readdir(dp)){
		printf("%s\n", drp->d_name);
	}

	closedir(dp);
}
