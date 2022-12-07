#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include "shm.h"

#define	NLOOPS	10

int main()
{
	int shmid;
	char *ptr, *pData;
	int *pInt, *num, i;
	pid_t	pid;

	if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0)  {
		perror("shmget");
		exit(1);
	}
	ptr = shmat(shmid, 0, 0);
	pInt = (int *)ptr;
	*pInt = 1;

	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid > 0)  {
		for (i = 0 ; i < NLOOPS ; i += 2)  {		
			//while((*pInt) == 0);
			pData = ptr + sizeof(int);
			num = (int*)pData;
			(num)++;
			printf("parent : %d\n", (*num));
			//*pInt = 1;
		}
	}
	else  {
		for (i = 0 ; i < NLOOPS ; i += 2)  {
			//while((*pInt) == 1);
			pData = ptr + sizeof(int);
			num = (int*)pData;
			(*num)++;
			printf("child : %d\n", (*num));
			//*pInt = 0;
		}
	}

	sleep(2);
	if (shmctl(shmid, IPC_RMID, 0) < 0)  {
		perror("shmctl");
		exit(1);
	}
}

