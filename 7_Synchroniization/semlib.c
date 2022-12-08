#include <stdio.h>
#include "semlib.h"

//making POSIX semaphore-like library by System V semaphore


//Semaphore Init
int semInit(key_t key){
    int     semid;
	
	//Obtain a semaphore set ID
    if ((semid = semget(key, 1, 0600 | IPC_CREAT)) < 0)  {
		perror("semget");
        return -1;
    }

    return semid;
} 

//Set Semaphore value
int semInitValue(int semid, int value){
    union semun {
            int     val;
    } semun;

    semun.val = value;
	//SETVAL : set the semaphore value
    if (semctl(semid, 0, SETVAL, semun) < 0)  {
		perror("semctl");
        return -1;
    }
 
    return semid;
}

//Make Semaphore wait operation ( -1 )
int semWait(int semid){
	//sembuf {num, op, flg}
    struct sembuf   semcmd;
 
    semcmd.sem_num = 0;
    semcmd.sem_op = -1;
    semcmd.sem_flg = SEM_UNDO;
	//make semaphore operation
    if (semop(semid, &semcmd, 1) < 0)  {
		perror("semop");
        return -1;
    }
 
    return 0;
}

//Retrun fail not wait
int semTryWait(int semid){
    struct sembuf   semcmd;
 
    semcmd.sem_num = 0;
    semcmd.sem_op = -1;
    semcmd.sem_flg = IPC_NOWAIT | SEM_UNDO;
    if (semop(semid, &semcmd, 1) < 0)  {
		perror("semop");
        return -1;
    }
 
    return 0;
}

//Make Semaphore signal operation ( +1 )
int semPost(int semid){
    struct sembuf   semcmd;
 
    semcmd.sem_num = 0;
    semcmd.sem_op = 1;
    semcmd.sem_flg = SEM_UNDO;
    if (semop(semid, &semcmd, 1) < 0)  {
		perror("semop");
        return -1;
    }
 
    return 0;
}

//Get value of Semaphore
int semGetValue(int semid){
    union semun {
            int     val;
    } dummy;
 
    return semctl(semid, 0, GETVAL, dummy);
}

//Destory Semaphore by IPC RMID
int semDestroy(int semid){
    union semun {
            int     val;
    } dummy;
 
    if (semctl(semid, 0, IPC_RMID, dummy) < 0)  {
		perror("semctl");
        return -1;
    }
    close(semid);
 
    return 0;
}
