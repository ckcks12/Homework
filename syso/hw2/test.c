#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sched.h>
#include <string.h> 
#include <sys/wait.h>

void handler(int sig)
{
    printf("got signal : %d\n", sig);
    kill(getpid(), SIGCONT);
} 

void handler2(int sig, siginfo_t* info, void* param)
{
    if( info->si_signo == SIGCHLD )
    {
        printf("handler2() : SIGCHLD from %d\n", info->si_pid);
    }

    printf("handler2() : %d from %d\n", info->si_signo, info->si_pid);

    // pause();
}

int f(void* i)
{
    printf("my pid : %d, got : %d\n", getpid(), *(int*)i);

    // sleep(*(int*)i);
    sleep(3);
    // kill(getppid(), SIGCHLD);
}

int main()
{
    printf("my pid : %d\n", getpid());

    void* stack[5];
    void* param[5];
    int i=0;
    for( i=0; i<5; i++ )
    {
        stack[i] = malloc(1024 * 64);
        param[i] = malloc(sizeof(int));
    }

    pid_t pid;
    for( i=0; i<5; i++ )
    {
        *((int*)param[i]) = i;
        clone(f, (char*)stack[i] + 1024 * 64, CLONE_VM | SIGCHLD | CLONE_SIGHAND | CLONE_FS | CLONE_FILES, param[i]);
    }

    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_sigaction = handler2;
    sa.sa_flags = SA_NOCLDSTOP | SA_SIGINFO;
    // sigaddset(&(sa.sa_mask), SIGCHLD);
    // sigfillset(&sa.sa_mask);
    sigaction(SIGCHLD, &sa, NULL);


    // signal(SIGCHLD, handler);
    // kill(getpid(), SIGSTOP);
    pause();
    printf("done\n");

    for( i=0; i<5; i++ )
    {
        free(stack[i]);
        free(param[i]);
    }
}

// int main()
// {
//     printf("my pid : %d\n", getpid());

//     if( fork() )
//     {
//         signal(SIGCHLD, handler);
//         printf("pause() : %d\n", pause());        
//     }
//     else
//     {
//         printf("my pid : %d\n", getpid());
//         sleep(2);
//     }
//     printf("%d : done\n", getpid());
// }

// int main()
// {
//     printf("my pid : %d\n", getpid());

    

//     void* stack;
//     stack = malloc(1024 * 64);
//     sigset_t sigset;
//     sigfillset(&sigset);
//     sigprocmask(SIG_UNBLOCK, &sigset, NULL);
//     signal(SIGCHLD, handler);

//     // pid = clone(f, (char*)stack + 1024 * 64, CLONE_VM | CLONE_SIGHAND | CLONE_FS | CLONE_FILES, 0);
//     pid = clone(f, (char*)stack + 1024 * 64, CLONE_VM | CLONE_FS | CLONE_SIGHAND | CLONE_FILES, 0);




//     signal(SIGCHLD, handler);
//     // sigaction(SIGCHLD, &sa, NULL);
    

//     printf("%d\n", handler == &handler);
    
//     int sig;
//     sig = pause();
//     printf("pause() : %d\n", sig);

//     printf("somebody awake me\n");

//     free(stack);

//     return 0;
// }
