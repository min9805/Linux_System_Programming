#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define MAX_PATH 256

void permittion(struct stat st){
    int kind;   // 현재 파일이 어떤 종류인지 확인하기 위해
    char* permit = (char*)malloc(sizeof(BUFSIZ));     // 퍼미션의 문자열을 저장하기 위해
    
    kind=st.st_mode & S_IFMT;    // 파일의 종류를 정의한 부분을 가져온다
    
    switch(kind){
      case S_IFDIR:
                   strcat(permit, "d"); // 디렉토리 파일인 경우 문자열에 d를 추가한다
                   break;
      case S_IFREG:
                   strcat(permit, "-"); // 일반 파일인 경우 문자열에 -를 추가한다
                   break;
      case S_IFIFO:
          strcat(permit, "p");    // FIFO  파일인 경우 문자열에 p를 추가한다
          break;
        case S_IFBLK:
            strcat(permit, "b");    // 블록 장치 특수 파일인 경우 문자열에 b를 추가한다
            break;
        case S_IFCHR:
            strcat(permit, "c");    // 문자 장치 특수 파일인 경우 문자열에 c를 추가한다
            break;
    }
 
       // user, group, other 별로 읽기, 쓰기, 실행에 대한 권한이 있는지 따져본다
    if((st.st_mode & S_IRUSR))
        strcat(permit, "r");
    else
        strcat(permit, "-");
    if((st.st_mode & S_IWUSR))
        strcat(permit, "w");
    else
        strcat(permit, "-");
    if((st.st_mode & S_IXUSR))
        strcat(permit, "x");
    else
        strcat(permit, "-");
    if((st.st_mode & S_IRGRP))
        strcat(permit, "r");
    else
        strcat(permit, "-");
    if((st.st_mode & S_IWGRP))
        strcat(permit, "w");
    else
        strcat(permit, "-");
    if((st.st_mode & S_IXGRP))
        strcat(permit, "x");
    else
        strcat(permit, "-");
    if((st.st_mode & S_IROTH))
        strcat(permit, "r");
    else
        strcat(permit, "-");
    if((st.st_mode & S_IWOTH))
        strcat(permit, "w");
    else
        strcat(permit, "-");
    if((st.st_mode & S_IXOTH))
        strcat(permit, "x");
    else
        strcat(permit, "-");
     
    printf("%s ", permit);             // 문자열을 출력한다
    free(permit);          // 할당 받은 메모리를 해제한다 
}


int main(int argc, char *argv[]){
	DIR *dp;
	struct dirent *dep;
	struct stat statbuf;
	struct group *g;
	struct passwd *pwd;
	char timebuf[MAX_PATH];


	//path를 받아서 그 디렉토리를 오픈한다
	if((dp = opendir(".")) == NULL) {
		perror("opendir");
		exit(0);
	}
;
	while(dep = readdir(dp)){
		if(strcmp(".", dep->d_name) == 0 || strcmp("..", dep->d_name) == 0){
			continue;
		}
		if(lstat(dep-> d_name, &statbuf) < 0 ){
			perror("lstat");
			exit(1);
		}		
		pwd = getpwuid(statbuf.st_uid);
		g = getgrgid(statbuf.st_gid);
		
		struct tm *tp;
		time_t t;
		t=time(NULL);
		tp=localtime(&t);
		strftime(timebuf, sizeof(timebuf), "%b %d %R", tp);

		permittion(statbuf);
		printf("%ld\t", statbuf.st_nlink);
		printf("%s\t", pwd->pw_name);
		printf("%s\t", g->gr_name);
		printf("%ld\t", statbuf.st_size);
		printf("%s\t", timebuf);;
		printf("%s\n", dep->d_name);
	}
}
