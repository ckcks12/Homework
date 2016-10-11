#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void logPid(int idx)
{
    printf("%d. this message from %d\n", idx, getpid());
}

int main()
{
    int idx = 1;
    pid_t pid = 0;
    int stat = 0;

    logPid(idx);
    pid = fork();
    if( pid > 0 )
    {
	wait(&stat);
	puts("all fork is ended");
	return 0;
    }
    logPid(idx);

    ++idx;
    
    logPid(idx);
    pid = fork();
    if( pid > 0 )
    {
	wait(&stat);
	return 0;
    }
    logPid(idx);

    ++idx;

    logPid(idx);
    pid = fork();
    if( pid > 0 )
    {
	wait(&stat);
	return 0;
    }
    logPid(idx);
    return 0;

}
