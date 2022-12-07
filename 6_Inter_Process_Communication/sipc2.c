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

	//같은 key를 통해 같은 shm를 할당받는다
	if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0)  {
		perror("shmget");
		exit(1);
	}
	if ((ptr = shmat(shmid, 0, 0)) == (void *) -1)  {
		perror("shmat");
		exit(1);
	}
	//integer에 대한 포인터로 flag를 가르킨다
	pInt = (int *)ptr;
	//처음에서 4바이트를 더한 위치로 flag 이후 첫 위치를 가르킨다
	pData = ptr + sizeof(int);
	//flag 이후에 데이터를 작성
	sprintf(pData, "This is a request from %d.", getpid());
	//데이터 작성 후 flag를 1로 변경해서 synchronization
	*pInt = 1;
	printf("Sent a request.....");

	//1이 아닐 때까지 무한루프
	while ((*pInt) == 1)
		;

	printf("Received reply: %s\n", pData);
}
