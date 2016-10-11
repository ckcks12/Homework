#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)

void setBlindInput(int on)
{
    int error;
    struct termios term;

    if( tcgetattr(STDIN_FILENO, &term) == -1 )
	return;
    if( on == 0 )
	term.c_lflag |= ECHOFLAGS;
    else
	term.c_lflag &= ~ECHOFLAGS;

    while(((error = tcsetattr(STDIN_FILENO, TCSAFLUSH, &term)) == -1) && (errno == EINTR))
	    ;

    return;
}

int checkId(const char* id)
{
    DIR* dir;
    struct dirent* dir_ent;

    dir = opendir(".");
    if( dir == NULL )
    {
	closedir(dir);
	return -1;
    }

    
    while( dir_ent = readdir(dir) )
    {
       	if( strcmp(dir_ent->d_name, id) == 0 )
	{
	    closedir(dir);
	    return 1;
	}
    }

    closedir(dir);
    return 0;
}

int checkIdPw(const char* id, const char* pw)
{
    DIR* dir;
    struct dirent* dir_ent;
    char _pw[80];
    FILE* f;

    dir = opendir(".");
    if( dir == NULL )
    {
	closedir(dir);
	return -1;
    }

    while( dir_ent = readdir(dir) )
    {
	if( strcmp(dir_ent->d_name, id) == 0 )
	{
	    f = fopen(dir_ent->d_name, "r");
	    if( f == NULL )
	    {
		closedir(dir);
		return -1;
	    }
	    fscanf(f, "%s", _pw);
	    if( strcmp(_pw, pw) == 0 )
	    {
		fclose(f);
		closedir(dir);
		return 1;
	    }
	    fclose(f);
	}
    }

    closedir(dir);
    return 0;
}

int createIdPw(const char* id, const char* pw)
{
    FILE* f;

    f = fopen(id, "w+");
    if( f == NULL )
	return -1;
    
    fprintf(f, "%s", pw);
    fclose(f);
    return 1;
}

int main()
{
    int input = 0;
    char id[80];
    char pw[80];

    while(1)
    {
	puts("====Select Menu====");
	puts("1. Make ID&PW");
	puts("2. Login");
	puts("3. Exit");
	puts("===================");

	scanf("%d", &input);

	if( input == 3 )
	    break;

	if( input == 1 )
	{
	    printf("ID : ");
	    scanf("%s", id);
	    printf("PW : ");
	    setBlindInput(1);
	    scanf("%s", pw);
	    setBlindInput(0);


	    createIdPw(id, pw);
	}

	if( input == 2 )
	{
	    printf("ID : "); scanf("%s", id);
	    if( checkId(id) )
	    {
		for( int i=0; i<3; i++ )
		{
        		printf("PW : "); 
			setBlindInput(1);
			scanf("%s", pw);
			setBlindInput(0);
			if( checkIdPw(id, pw) )
			{
		    	    puts("Login Success");
			    break;
			}
			else
			{
			    printf("Wrong Password : count %d\n", i + 1);
			    continue;
			}
		}
	    }
	    else
	    {
		puts("ID does not exist");
	    }
	}
    }
}
