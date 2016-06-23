#ifndef __sema__

#define __sema__
#define _GNU_SOURCE
#define SEMA_CNT (2)

static int sema_id_arr[SEMA_CNT];

typedef union _sema_un
{
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
} SEMA_UN;

void semaInit();
void semaDel();
void semaLock(int idx);
void semaUnlock(int idx);


#endif // __sema__