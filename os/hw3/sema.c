#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "sema.h"

struct sembuf sema_buf_lock = 
{
	.sem_num = 0,
	.sem_op = -1,
	.sem_flg = SEM_UNDO
};

struct sembuf sema_buf_unlock = 
{
	.sem_num = 0,
	.sem_op = +1,
	.sem_flg = SEM_UNDO
};

void semaInit()
{
	SEMA_UN sema_un;
	sema_un.val = 1;

	int i;

	for( i=0; i<SEMA_CNT; i++ )
	{
		sema_id_arr[i] = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
		if( sema_id_arr[i] == -1 )
		{
			puts("failed to create semaphore");
			return;
		}
		semctl(sema_id_arr[i], 0, SETVAL, sema_un);
	}
}

void semaDel()
{
	SEMA_UN sema_un;
	sema_un.val = 1;

	int i;

	for( i=0; i<SEMA_CNT; i++ )
	{
		semctl(sema_id_arr[i], 0, IPC_RMID, sema_un);
	}
}

void semaLock(int idx)
{
	semop(sema_id_arr[idx], &sema_buf_lock, 1);
}

void semaUnlock(int idx)
{
	semop(sema_id_arr[idx], &sema_buf_unlock, 1);
}