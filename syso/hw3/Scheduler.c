#include "Init.h"
#include "Thread.h"
#include "Scheduler.h"
#include "queue.h"
#include "hashmap.h"
#define _GNU_SOURCE

int is_alarm = 0;
int is_chld = 0;
int schedule_cnt = 0;

int trap = 1; // for running scheduler

void handler()
{
    // RunScheduler();
    trap = 1;
}

void chldHandler(int sig, siginfo_t* info, void* param)
{
    // if( info->si_signo == SIGCHLD )
    // {
    //     pid_t pid;

    //     pid = info->si_pid;
    //     if( __DEBUG__ )
    //     {
    //         printf("chldHandler() : pid() : %d SIGCHLD form %d\n", getpid(), pid);
    //     }

                
    //     // thread_cancel(pid);
    // }
}

int		RunScheduler( void )
{
    while( 1 )
    {
        if( current_thread != NULL )
        {
            switch( getProcStatus(current_thread->pid) )
            {
                case 'Z':
                case 'X':
                case 'x':
                    if( __DEBUG__ )
                    {
                        printf("RunScheduler() : Zombie detected : %d\n", current_thread->pid);
                    }
                    thread_cancel(current_thread->pid);
                    trap = 1;
                    break;
                case 'T':
                    trap = 1;
                    break;
                default:
                    break;
            }
        }
        else
        {
            if( __DEBUG__ )
                printf("RunScheduler() : current_thread is NULL, so trap myself!\n");
            trap = 1;
        }

        if( trap > 0 )
        {
            

            if( is_alarm == 0 )
            {
                signal(SIGALRM, handler);
                is_alarm = 1;
            }

            // if( is_chld == 0 )
            // {
            //     struct sigaction sa;
            //     memset(&sa, 0, sizeof(struct sigaction));
            //     sa.sa_sigaction = chldHandler;
            //     sa.sa_flags = SA_NOCLDSTOP | SA_SIGINFO;
            //     sigaction(SIGCHLD, &sa, NULL);
            //     is_chld = 1;
            // }

            // check current thread status
            if( current_thread != NULL )
            {
                // if( kill(current_thread->pid, 0) < 0 )
                // {
                //     thread_cancel(current_thread->pid);
                // }
                // else
                // {
                //     current_thread->status = THREAD_STATUS_READY;
                //     rqEnqueue(current_thread);
                // }
                current_thread->status = THREAD_STATUS_READY;
                rqEnqueue(current_thread);
            }

            if( ! rqIsEmpty() )
            {
                if( __DEBUG__ && !rqIsEmpty() )
                {
                    printf("RunSchedule() : 1 ReadyQHead : %d(%p), ReadyQTail : %d(%p)\n", ReadyQHead->pid, ReadyQHead, ReadyQTail->pid, ReadyQTail);
                }
                new_thread = rqDequeue();
                new_thread->status = THREAD_STATUS_RUN;
                if( __DEBUG__ && !rqIsEmpty() )
                {
                    printf("RunSchedule() : 2 ReadyQHead : %d(%p), ReadyQTail : %d(%p)\n", ReadyQHead->pid, ReadyQHead, ReadyQTail->pid, ReadyQTail);
                }

                pid_t c;
                if( current_thread != NULL )
                    c = current_thread->pid;
                else
                    c = 0;

                _ContextSwitch(c, new_thread->pid);

                if( __DEBUG__ && !rqIsEmpty() )
                {
                    printf("RunSchedule() : 3 ReadyQHead : %d(%p), ReadyQTail : %d(%p)\n", ReadyQHead->pid, ReadyQHead, ReadyQTail->pid, ReadyQTail);
                }
                
            }

            // Debug Console
            if( __DEBUG__ )
            {
                printf("\n");
                printf("==========================\n");
                printf("Scheduling!!! (%d)\n", ++schedule_cnt);
                printf("==========================\n");

                printf("ReadyQueue Status\n");
                Thread* th;
                th = ReadyQHead;

                if( current_thread != NULL )
                {
                    printf("(((%d(%p))))-> ", current_thread->pid, current_thread);
                }

                if( __DEBUG__ && !rqIsEmpty() )
                {
                    printf("RunSchedule() : 4 ReadyQHead : %d(%p), ReadyQTail : %d(%p)\n", ReadyQHead->pid, ReadyQHead, ReadyQTail->pid, ReadyQTail);
                }

                while( th != NULL )
                {
                    printf("%d(%p)-> ", th->pid, th);
                    th = th->pNext;
                }
                printf("\n");

                if( __DEBUG__ && !rqIsEmpty() )
                {
                    printf("RunSchedule() : 5 ReadyQHead : %d(%p), ReadyQTail : %d(%p)\n", ReadyQHead->pid, ReadyQHead, ReadyQTail->pid, ReadyQTail);
                }

                printf("WaitQueue Status\n");
                th = WaitQHead;
                while( th != NULL )
                {
                    printf("%d(%p)-> ", th->pid, th);
                    th = th->pNext;
                }
                printf("\n");

                printf("HashMap Status\n");
                hashStatus();
                printf("\n");

                printf("\n\n");
            }
            
            if( __DEBUG__ && !rqIsEmpty() )
            {
                printf("RunSchedule() : - ReadyQHead : %d(%p), ReadyQTail : %d(%p)\n", ReadyQHead->pid, ReadyQHead, ReadyQTail->pid, ReadyQTail);
            }

            alarm(TIMESLICE);
            trap = 0;
        }
    }
}

void rqStatus() {
    printf("\nReadyQueue Status\n");
    Thread* th;
    th = ReadyQHead;

    if( current_thread != NULL )
    {
        printf("(((%d(%p))))-> ", current_thread->pid, current_thread);
    }

    while( th != NULL )
    {
        printf("%d(%p)-> ", th->pid, th);
        th = th->pNext;
    }
    printf("\n");
}

// void		_ContextSwitch(int curpid, int tpid)
void _ContextSwitch(int c, int n)
{
    if( __DEBUG__ && !rqIsEmpty() )
        printf("_ContextSwitch() : 1 ReadyQHead : %d(%p), ReadyQTail : %d(%p)\n", ReadyQHead->pid, ReadyQHead, ReadyQTail->pid, ReadyQTail);

    if( c != 0 )
    {
        kill(c, SIGSTOP);
        // kill(c, SIGCONT);
    }
    kill(n, SIGCONT);
    current_thread = new_thread;

    if( __DEBUG__ && !rqIsEmpty() )
        printf("_ContextSwitch() : 2 ReadyQHead : %d(%p), ReadyQTail : %d(%p)\n", ReadyQHead->pid, ReadyQHead, ReadyQTail->pid, ReadyQTail);
}

