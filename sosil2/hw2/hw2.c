#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

void showDirectoryInfo();
void makeDirectory(char* dir_name);
void removeDirectory(char* dir_name);

int main(int argc, char** argv)
{
    int user_input = 0;

    while( user_input != 4 )
    {
	puts("1. MAke directory");
	puts("2. Remove directory");
	puts("3. Shows Current Directory info");
	puts("4. Exit");
	puts("================");
	printf("Select Num : ");
	scanf("%d", &user_input);
	
	char input[256];
	int i;
	for( i=0; i<256; i++ )
	{
	    input[i] = 0;
	}

	switch( user_input )
	{
	    case 1:
		printf("Enter directory Name(Make) : ");
		scanf("%s", input);
		makeDirectory(input);
		showDirectoryInfo();
		break;
	    case 2:
		printf("Enter directory Name(remove) : ");
		scanf("%s", input);
		removeDirectory(input);
		showDirectoryInfo();
		break;
	    case 3:
	       showDirectoryInfo();
		break;
	}		
    }
}





void showDirectoryInfo()
{
    DIR* dir;

    dir = opendir("./");
    if( dir == NULL )
    {
	perror("error occurred while opendir()");
	return;
    }

    struct dirent* dirent;

    while( (dirent = readdir(dir)) != NULL )
    {
	printf("%s\n", dirent->d_name);
    }
    
    if( closedir(dir) )
    {
	perror("error occurred while closedir()");
	return;
    }
}


void makeDirectory(char* dir_name)
{
    if( mkdir(dir_name, 0755) )
    {
	perror("error occurred while mkdir()");
	return;
    }
}

void removeDirectory(char* dir_name)
{
    if( chdir(dir_name) )
    {
	perror("error occurred while chdir()");
	return;
    }

    chdir("..");

    if( rmdir(dir_name) )
    {
	perror("error occurred while rmdir()");
	return;
    }
}
