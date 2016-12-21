#include "Thread.h"
#include "queue.h"

/* what the fuck queue fuck Q */
int rqIsEmpty()
{
    return ReadyQHead == NULL;
}
void rqEnqueue(Thread* th)
{
    if( rqIsEmpty() )
    {
        th->pPrev = NULL;
        th->pNext = NULL;
        ReadyQHead = th;
        ReadyQTail = th;
    }
    else
    {
        th->pPrev = ReadyQTail;
        th->pNext = NULL;
        ReadyQTail->pNext = th;
        ReadyQTail = th;
    }
}
Thread* rqDequeue()
{
    if( rqIsEmpty() )
       return NULL;

    Thread* th;
    th = ReadyQHead;

    if( __DEBUG__ )
    {
        printf("rqDequeue() : ReadyQHead : %d(%p), ReadyQTail : %d(%p)\n", ReadyQHead->pid, ReadyQHead, ReadyQTail->pid, ReadyQTail);
    }

    if( ReadyQHead == ReadyQTail )
    {
        ReadyQHead = NULL;
        ReadyQTail = NULL;
    }
    else
    {
        ReadyQHead = ReadyQHead->pNext;
        ReadyQHead->pPrev = NULL;
    }

    th->pPrev = NULL;
    th->pNext = NULL;
    return th;
}
void rqDelete(Thread* th)
{
    if( rqIsEmpty() )
        return;

    // center
    if( th->pPrev != NULL && th->pNext != NULL )
    {
        th->pPrev->pNext = th->pNext;
        th->pNext->pPrev = th->pPrev;
    }
    // tail
    else if( th->pPrev != NULL )
    {
        th->pPrev->pNext = NULL;
        ReadyQTail = th->pPrev;
    }
    // head
    else if( th->pNext != NULL )
    {
        th->pNext->pPrev = NULL;
        ReadyQHead = th->pNext;
    }
    // alone
    else
    {
        ReadyQHead = NULL;
        ReadyQTail = NULL;
    }

    th->pPrev = NULL;
    th->pNext = NULL;
}
Thread* rqGet(thread_t tid)
{
    if( rqIsEmpty() )
        return NULL;

    Thread* th;
    th = ReadyQHead;

    while( th != NULL )
    {
        if( th->pid == tid )
            return th;
        th = th->pNext;
    }

    return NULL;
}

int wqIsEmpty()
{
    return WaitQHead == NULL;]
}
void wqEnqueue(Thread* th)
{
    if( wqIsEmpty() )
    {
    th->pPrev = NULL;
    th->pNext = NULL;
    WaitQHead = th;
    WaitQTail = th;
    }
    else
    {
    th->pPrev = WaitQTail;
    th->pNext = NULL;
    WaitQTail->pNext = th;
    WaitQTail = th;
    }
}
Thread* wqDequeue()
{
    if( wqIsEmpty() )
    return NULL;

    Thread* th;
    th = WaitQHead;

    if( WaitQHead == WaitQTail )
    {
    WaitQHead = NULL;
    WaitQTail = NULL;
    }
    else
    {
    WaitQHead = WaitQHead->pNext;
    WaitQHead->pPrev = NULL;
    }

    th->pPrev = NULL;
    th->pNext = NULL;
    return th;
}
void wqDelete(Thread* th)
{
    if( wqIsEmpty() )
        return;

    // center
    if( th->pPrev != NULL && th->pNext != NULL )
    {
        th->pPrev->pNext = th->pNext;
        th->pNext->pPrev = th->pPrev;
    }
    // tail
    else if( th->pPrev != NULL )
    {
        th->pPrev->pNext = NULL;
        WaitQTail = th->pPrev;
    }
    // head
    else if( th->pNext != NULL )
    {
        th->pNext->pPrev = NULL;
        WaitQHead = th->pNext;
    }
    // alone
    else
    {
        WaitQHead = NULL;
        WaitQTail = NULL;
    }

    th->pPrev = NULL;
    th->pNext = NULL;
}
Thread* wqGet(thread_t tid)
{
    if( wqIsEmpty() )
        return NULL;

    Thread* th;
    th = WaitQHead;

    while( th != NULL )
    {
        if( th->pid == tid )
            return th;
        th = th->pNext;
    }

    return NULL;
}




