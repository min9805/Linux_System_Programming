#include <stdio.h>

int main(int argc, char *argv[], char* envp[]){
	int i;
	char **p;
	extern char **environ;

	printf("List command-line arguments\n");
	for (i =0; i< argc; i++){
		printf("%s\n", argv[i]);
	}
//extern 변수인 environ 을 사용해서 환경 변수를 출력하는 방법 두 가지
	printf("\n");
	printf("List environment variables from environ variable\n");
#if 0
	for(i = 0; environ[i] != NULL ; i++){
		printf("%s\n", environ[i]);
	}
#else

	for(p = environ ; *p != NULL ; p++){
		printf("%s\n", *p);
	}
#endif

//argument의 envp를 사용해서 환경 변수를 출력하는 방법 두 가지
	printf("\n");
	printf("List environment variables form envp variable\n");
#if 0	
	for(i = 0 ; envp[i] != NULL; i++){
		printf("%s\n", envp[i]);
	}
#else
	for(p = envp; *p != NULL; p++){
		printf("%s\n", *p);
	}
#endif
}
