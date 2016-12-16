#include <stdio.h>
#include "Init.h"
#include "Thread.h"
#include "queue.h"
#include "hashmap.h"
#include "MsgQueue.h"

void Init(void)
{
    ReadyQHead = NULL;
    ReadyQTail = NULL;
    WaitQHead = NULL;
    WaitQTail = NULL;

    // message queue init
    int i = 0;
    for( i=0; i<MAX_QCB_SIZE; i++ )
    {
        qcbTblEntry[i].key =  -1;
        qcbTblEntry[i].pQcb = NULL;
    }

    ppid = getppid();
    if( __DEBUG__ )
    {
        printf("Init() : ppid : %d\n", ppid);
        printf("Init() : pid : %d\n", getpid());
    }
}