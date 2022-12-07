#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include "prodcons.h"

BoundedBufferType	Buf;

//usecs 만큼 sleep 하도록 만드는 method
void ThreadUsleep(int usecs){
	pthread_cond_t		cond;
	pthread_mutex_t		mutex;
	struct timespec		ts;
	struct timeval		tv;

	pthread_cond_init(&cond, NULL);
	pthread_mutex_init(&mutex, NULL);

	gettimeofday(&tv, NULL);
	ts.tv_sec = tv.tv_sec + usecs/1000000;
	ts.tv_nsec = (tv.tv_usec + (usecs%1000000)) * 1000;
	
	if(ts.tv_nsec >= 1000000000) {
		ts.tv_nsec -= 1000000000;
		ts.tv_sec++;
	}

	pthread_mutex_lock(&mutex);
	pthread_cond_timedwait(&cond, &mutex, &ts);
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mutex);
}

//data 생성
void Producer(void *dummy){
	int 		i, data;
	printf("Producer : Start ... \n");

	for (i = 0 ; i < NLOOPS ; i++)	{
		//Buf에 데이터가 없으면 무한루프를 돌면서 기다린다
		if (Buf.counter == MAX_BUF)	{
			printf("Producer : Buffer full. Waiting ... \n");
			while (Buf.counter == MAX_BUF);
		}
		printf("Producer : Producing an item ... \n");
		data = (rand()%100)*10000;
		Buf.buf[Buf.in].data = data;
		//데이터를 생성했기에 Buf.in을 하나 증가시킨다
		Buf.in = (Buf.in + 1) % MAX_BUF;
		Buf.counter++;

		ThreadUsleep(data);
	}

	printf("Producer : Produced %d items .... \n", i);
	printf("Producer : %d items in buffer .... \n", Buf.counter);

	pthread_exit(NULL);
}

//data 사용
void Consumer(void *dummy){
	int 		i, data;
	
	printf("Consumer : Start .... \n");

	for (i = 0 ; i < NLOOPS ; i++)	{
		//Buf에 데이터가 없으면 Producer가 생성할 때까지 기다리기위해 무한루프
		if (Buf.counter == 0){
			printf("Consumer : Buffer empty. Waiting ... \n");
			while (Buf.counter == 0);
		}

		printf("Consumer : Consuming an item ... \n");
		data = Buf.buf[Buf.out].data;
		//데이터를 사용했기 때문에 Buf.out을 증가시킨다
		Buf.out = (Buf.out + 1) % MAX_BUF;
		Buf.counter--;

		ThreadUsleep((rand()%100)*10000);
	}
	
	printf("Consumer : Consumed %d items .... \n", i);
	printf("Consumer : %d items in buffer .... \n", Buf.counter);

	pthread_exit(NULL);
}

int main(){
	pthread_t		tid1, tid2;
	
	srand(0x8888);

	pthread_create(&tid1, NULL, (void *)Producer, (void *)NULL);
	pthread_create(&tid2, NULL, (void *)Consumer, (void *)NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	printf("Main	: %d items in buffer .... \n", Buf.counter);
}
