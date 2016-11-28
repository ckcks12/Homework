#include "Thread.h"
#include "Init.h"
#include "Scheduler.h"

/* what the fuck queue fuck Q */
int rqIsEmpty()
{
    return ReadyQead == NULL;
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
    th->pPrev = NULL;
    th->pNext = NULL;

    if( ReadQHead == ReadyQTail )
    {
	ReadQHead = NULL;
	ReadQTail = NULL;
    }
    else
    {
	ReadQHead = ReadyQHead->pNext;
	ReadQHead->pPrev = NULL;
    }

    return th;
}

int wqIsEmpty()
{
    return WaitQHead == NULL;
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
    th->pPrev = NULL;
    th->pNext = NULL;

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

    return th;
}


int 	thread_create(thread_t *thread, thread_attr_t *attr, void *(*start_routine) (void *), void *arg)
{

}


int 	thread_join(thread_t thread, void **retval)
{

}


int 	thread_suspend(thread_t tid)
{

}


int	thread_resume(thread_t tid)
{

}


int 		thread_cancel(thread_t tid)
{

}


thread_t	thread_self()
{

}	
