#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "prodcons.h"

int main(){
	BoundedBufferType			*pBuf;
	int 						shmid, i, data;

	//shared memory 생성 혹은 가져오기
	if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0)  {
		perror("shmget");
		exit(1);
	}
	//shared memory attach
	if ((pBuf = (BoundedBufferType *)shmat(shmid, 0, 0)) == (void *) -1)  {
		perror("shmat");
		exit(1);
	}

	//rand를 위한 seed 생성
	srand(0x9999);
	for (i=0; i<NLOOPS; i++){
		//bounded buffer에 data가 없으면 consume 할 수 없으니 wait
		if(pBuf->counter == 0){
			printf("Consumer: Buffer empty. Waiting ...\n");
			while (pBuf->counter == 0);
		}

		//bounded buffer에서 data를 가져온 후 counter--
		printf("Consumer: Consuming an item...\n");
		data = pBuf->buf[pBuf->out].data;
		pBuf->out = (pBuf->out + 1) % MAX_BUF;
		pBuf->counter--;

		usleep((rand()%100)*10000);
	}

	printf("Consumer: Consumed %d items ....\n", i);
	printf("Consumer: %d items in buffer ....\n", pBuf-> counter);
}
