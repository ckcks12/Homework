#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <string.h>

#define MAX_PATH_LEN 8192

void printPermission(mode_t perms)
{
    printf( S_ISDIR(perms) ? "d" : "-");
    printf( (perms & S_IRUSR) ? "r" : "-");
    printf( (perms & S_IWUSR) ? "w" : "-");
    printf( (perms & S_IXUSR) ? "x" : "-");
    printf( (perms & S_IRGRP) ? "r" : "-");
    printf( (perms & S_IWGRP) ? "w" : "-");
    printf( (perms & S_IXGRP) ? "x" : "-");
    printf( (perms & S_IROTH) ? "r" : "-");
    printf( (perms & S_IWOTH) ? "w" : "-");
    printf( (perms & S_IXOTH) ? "x" : "-");
}

void printSize(off_t size)
{
    if( size < 1024 )
	printf("%8ld", size);
    else if( size < 1024 * 1024 )
	printf("%7.1lfK", (double)size / 1024 );
    else if( size < 1024 * 1024 * 1024 )
	printf("%7.1lfM", (double)size / (1024 * 1024));
    else
	printf("%7.1lfG", (double)size / (1024 * 1024 * 1024));
}

void printDirInfo(const char* path, int depth)
{
    DIR* dir;
    struct dirent* dir_ent;
    struct stat stat_info;
    struct passwd* pwd;

    dir = opendir(path);
    if( dir == NULL )
    {
	return;
    }

    if( depth == 1)
	puts(".");

    while( dir_ent = readdir(dir) )
    {
	char file_path[MAX_PATH_LEN] = {0, };
	strcpy(file_path, path);
	strcat(file_path, "/");
	strcat(file_path, dir_ent->d_name);
	stat(file_path, &stat_info);
	pwd = getpwuid(stat_info.st_uid);

	if( strcmp(dir_ent->d_name, "..") == 0 )
	{
	    continue;
	} 
	else if( strcmp(dir_ent->d_name, ".") == 0 )
	{
	    continue;
	}

	int i=0;
	for( i=0; i<depth-1; i++)
	{
	    printf("%-8s", "│");
	}
	printf("├───");

	printf("[");
	printf("%lu ", stat_info.st_ino);
	printf("%lu ", stat_info.st_dev);
	printPermission(stat_info.st_mode); printf(" ");
	printf("%s ", pwd->pw_name);
	printSize(stat_info.st_size);
	printf("]");
	printf("\t%s\n", dir_ent->d_name);

	if( S_ISDIR(stat_info.st_mode) )
	{
	    char path2[MAX_PATH_LEN];
	    strcpy(path2, path);
	    strcat(path2, "/");
	    strcat(path2, dir_ent->d_name);
	    printDirInfo(path2, depth + 1);
	}
    }

    closedir(dir);
}


int main()
{
    printDirInfo(".", 1);
}
