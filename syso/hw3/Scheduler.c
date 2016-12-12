#include "Init.h"
#include "Thread.h"
#include "Scheduler.h"
#include "queue.h"
#include "hashmap.h"

int is_alarm = 0;
int is_chld = 0;
int schedule_cnt = 0;
int trap = 1;

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

        if( trap == 1 )
        {
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

                while( th != NULL )
                {
                    printf("%d(%p)-> ", th->pid, th);
                    th = th->pNext;
                }
                printf("\n");

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

            if( is_alarm == 0 )
            {
                signal(SIGALRM, handler);
                is_alarm = 1;
            }

            if( is_chld == 0 )
            {
                struct sigaction sa;
                memset(&sa, 0, sizeof(struct sigaction));
                sa.sa_sigaction = chldHandler;
                sa.sa_flags = SA_NOCLDSTOP | SA_SIGINFO;
                sigaction(SIGCHLD, &sa, NULL);
                is_chld = 1;
            }

            // check current thread status
            if( current_thread != NULL )
            {
                if( kill(current_thread->pid, 0) < 0 )
                {
                    thread_cancel(current_thread->pid);
                }
                else
                {
                    current_thread->status = THREAD_STATUS_READY;
                    rqEnqueue(current_thread);
                }
            }

            if( ! rqIsEmpty() )
            {
                new_thread = rqDequeue();
                new_thread->status = THREAD_STATUS_RUN;

                pid_t c;
                if( current_thread != NULL )
                    c = current_thread->pid;
                else
                    c = 0;

                _ContextSwitch(c, new_thread->pid);
            }

            alarm(TIMESLICE);
            trap = 0;
        }
    }
}


// void		_ContextSwitch(int curpid, int tpid)
void _ContextSwitch(int c, int n)
{
    if( c != 0 )
    {
        kill(c, SIGSTOP);
        // kill(c, SIGCONT);
    }
    kill(n, SIGCONT);
    current_thread = new_thread;
}

