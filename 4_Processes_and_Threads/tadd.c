#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int *add1(){
	int i;
	int *ret;
	int sum = 0;
	for(i = 1; i<= 50 ; i++){
		sum += i;
	}
	ret = (int *)malloc(sizeof(int));
	*ret = sum;
	return (void *)ret;
}
int *add2(void *p){
	int i;
	int *ret;
	int n = *(int *)p;
	int sum = 0;
	for(i = 51; i<= n ; i++){
		sum += i;
	}
	ret= (int *)malloc(sizeof(int));
	*ret = sum;
	return (void *) ret;
}

int main(){
	pthread_t tid1, tid2;
	int sum;
	int *ret1, *ret2;
	int n = 100;

	if(pthread_create(&tid1, NULL,(void *) add1, NULL) < 0){
		perror("pthread_create");
		exit(1);
	}
	if(pthread_create(&tid2, NULL,(void *) add2, &n) < 0){
		perror("pthread_create");
		exit(1);
	}
	
	pthread_join(tid1, (void **)&ret1);
	pthread_join(tid2, (void **)&ret2);

	sum = *ret1 + *ret2;
	printf("sum : %d\n",sum);
}
