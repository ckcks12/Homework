#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

#define MAX_PATH_LEN 8192

int pipe_fd[2];
pid_t pid;

void ls()
{
    DIR* dir;
    struct dirent* dir_ent;

    dir = opendir("./");
    if( dir == NULL )
	return;
    
    while( dir_ent = readdir(dir) )
    {
	const char* name = dir_ent->d_name;
	
	if( strcmp(name, "..") == 0 )
	    continue;
	else if( strcmp(name, ".") == 0 )
	    continue;

	printf("%s\n", dir_ent->d_name);
    }

    closedir(dir);
}

void sort()
{
    char data[MAX_PATH_LEN];
    while( fgets(data, MAX_PATH_LEN, stdin) != NULL )
    {
	printf("%s", data);
    }
}

int main()
{
    if( pipe(pipe_fd) == -1 )
    {
	perror("pipe()");
	exit(-1);
    }

    pid = fork();
    if( pid == -1 )
    {
	perror("fork()");
	exit(-2);
    }

    // parent
    if( pid > 0 )
    {
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	ls();	
    }
    // child
    else
    {
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	sort();
    }
}   
