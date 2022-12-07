#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include "shm.h"


int main()
{
	int		shmid;
	char	*ptr, *pData;
	int		*pInt;

	//shmget으로 pysical memory를 만든다
	//SHM_KEY를 통해 만든다
	if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0)  {
		perror("shmget");
		exit(1);
	}
	
	//아무곳에 매핑해달라는 의미
	if ((ptr = shmat(shmid, 0, 0)) == (void *) -1)  {
		perror("shmat");
		exit(1);
	}

	//integer에 대한 포인터로, shm의 첫 4바이트(flag)를 가르킨다
	pInt = (int *)ptr;
	//아직 데이터가 쓰여있지 않으면 무한루프를 돈다
	//sipc2.c에서 데이터를 쓰면 무한루프를 빠져나온다
	while ((*pInt) == 0)
		;

	//데이터를 다시 쓰고 flag를 바꿔놓는다.
	pData = ptr + sizeof(int);
	printf("Received request: %s.....", pData);
	sprintf(pData, "This is a reply from %d.", getpid());
	*pInt = 0;
	printf("Replied.\n");

	sleep(1);
	
	//sleep 없이 종료하면 sipc2.c 가 사용하기 전에 종료할 수 있으니,,
	if (shmctl(shmid, IPC_RMID, 0) < 0)  {
		perror("shmctl");
		exit(1);
	}
}
