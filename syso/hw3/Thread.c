#include "Thread.h"
#include "Init.h"
#include "Scheduler.h"
#include "queue.h"
#include "hashmap.h"
#include <string.h>

#define STACK_SIZE 1024 * 64


int 	thread_create(thread_t *thread, thread_attr_t *attr, void *(*start_routine) (void *), void *arg)
{
    Thread* th = (Thread*)malloc(sizeof(Thread));
    memset(th, 0, sizeof(Thread));

    th->entryPt = start_routine;
    th->stackAddr = malloc(STACK_SIZE);
    th->stackSize = STACK_SIZE;
    th->status = THREAD_STATUS_READY;
    if( ppid == getppid() )
        th->pid = clone(th->entryPt, th->stackAddr + th->stackSize, CLONE_VM | SIGCHLD | CLONE_SIGHAND | CLONE_FS | CLONE_FILES, arg);    
    else
        th->pid = clone(th->entryPt, th->stackAddr + th->stackSize, CLONE_VM | SIGCHLD | CLONE_SIGHAND | CLONE_FS | CLONE_FILES | CLONE_PARENT, arg);
    th->type = 0;

    kill(th->pid, SIGSTOP);

    hashPut(getpid(), th->pid);

    rqEnqueue(th);

    *thread = th->pid;
}


int 	thread_join(thread_t thread, void **retval)
{
    Thread* th1 = current_thread;
    Thread* th2 = rqGet(thread);
    if( th2 == NULL )
        th2 = wqGet(thread);

    if( th2 == NULL )
        return 0;

    // if thread can join to another thread which not been created by it
    // need to implement joining-mapping table.

    th1->status = THREAD_STATUS_BLOCKED;
    current_thread = NULL;
    wqEnqueue(th1);
    kill(th1->pid, SIGSTOP);
}


int 	thread_suspend(thread_t tid)
{
    Thread* th;

    if( tid == current_thread->pid )
        th = current_thread;
    else
        th = rqGet(tid);

    if( th == NULL )
        return -1;

    th->status = THREAD_STATUS_BLOCKED;
    rqDelete(th);
    wqEnqueue(th);
    kill(th->pid, SIGSTOP);
}


int	thread_resume(thread_t tid)
{
    Thread* th;

    th = wqGet(tid);

    if( th == NULL )
        return -1;

    th->status = THREAD_STATUS_READY;
    wqDelete(th);
    rqEnqueue(th);
}


int 		thread_cancel(thread_t tid)
{
    if( __DEBUG__ )
    {
        // printf("thread_cancel() : %d\n", tid);
    }

    kill(tid, SIGKILL);

    if( current_thread != NULL && current_thread->pid == tid )
    {
        current_thread->status = THREAD_STATUS_READY;
        rqEnqueue(current_thread);
        current_thread = NULL;
    }

    Thread* th;
    th = ReadyQHead;

    while( th != NULL )
    {
        if( th->pid == tid )
        {
            if( __DEBUG__ )
            {
                // printf("thread_cancel() : th->pid == tid : true\n");
            }

            rqDelete(th);

            // unblock parent if blocked
            thread_t parent_pid = hashGetParent(th->pid);
            Thread* parent_th = wqGet(parent_pid);

            if( parent_th != NULL && parent_th->status == THREAD_STATUS_BLOCKED )
            {
                wqDelete(parent_th);
                rqEnqueue(parent_th);
            }

            hashDelete(th->pid);

            break;
        }
        else
        {
            th = th->pNext;
        }
    }

    if( th != NULL )
    {
        free(th->stackAddr);
        free(th);
    }
}


thread_t	thread_self()
{
    return getpid();
}	
