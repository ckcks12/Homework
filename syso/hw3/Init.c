#include <stdio.h>
#include "Init.h"
#include "Thread.h"
#include "queue.h"
#include "hashmap.h"

void Init(void)
{
    ReadyQHead = NULL;
    ReadyQTail = NULL;
    WaitQHead = NULL;
    WaitQTail = NULL;

    ppid = getppid();
    if( __DEBUG__ )
    {
        printf("Init() : ppid : %d\n", ppid);
        printf("Init() : pid : %d\n", getpid());
    }
}