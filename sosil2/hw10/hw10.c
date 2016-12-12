#include <pthread.h>
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

#define SEMA_CNT (2)

static int sema_id_arr[SEMA_CNT];

typedef union _sema_un
{
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
} SEMA_UN;

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

void* thread_increment(void* arg);
char thread1[] = "A thread";
char thread2[] = "B thread";

pthread_mutex_t mutx;
int number = 0;

int main(int argc, char** argv)
{
    pthread_t t1, t2;
    void* thread_result;
    int state;

    // state = pthread_mutex_init(&mutx, NULL);
    // if( state )
    // {
    //     puts("Failed to init mutex");
    //     exit(1);
    // }
    
    semaInit();

    pthread_create(&t1, NULL, thread_increment, &thread1);
    pthread_create(&t2, NULL, thread_increment, &thread2);

    pthread_join(t1, &thread_result);
    pthread_join(t2, &thread_result);

    printf("final number : %d \n", number);
    semaDel();
    // pthread_mutex_destroy(&mutx);
    return 0;
}

void* thread_increment(void* arg)
{
    int i;

    semaLock(0);
    for( i=0; i<5; i++ )
    {
        // pthread_mutex_lock(&mutx);
        sleep(1);
        number++;
        printf("execute : %s, number : %d\n", (char*)arg, number);
        // pthread_mutex_unlock(&mutx);
    }
    semaUnlock(0);
}