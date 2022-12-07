#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

void PrintDir(char *path){
	DIR *dp;
	struct dirent *dep;
	struct stat statbuf;
	char fullpath[MAX_PATH];

	//path를 받아서 그 디렉토리를 오픈한다
	if((dp = opendir(path)) == NULL) {
		perror("opendir");
		exit(0);
	}

	printf("\n%s: \n", path);
	while(dep = readdir(dp)){
		//d_name이 ., .. 이면 print 하지 않는다	
		if(strcmp(".", dep->d_name) == 0 || strcmp("..", dep->d_name) == 0){
			continue;
		}
		printf("%s\n", dep->d_name);
	}

	rewinddir(dp);
	while(dep = readdir(dp)) {
		if(strcmp(".", dep->d_name) == 0 || strcmp("..", dep->d_name) == 0){
			continue;
		}
		strcpy(fullpath, path);
		strcat(fullpath, "/");
		strcat(fullpath, dep->d_name);
		if(lstat(fullpath, &statbuf) < 0){
			perror("lstat");
			exit(1);
		}
		if (S_ISDIR(statbuf.st_mode)){
			PrintDir(fullpath);
		}
	}
}

int main(int argc, char *argv[]){
	PrintDir(".");
}
