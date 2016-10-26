#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

unsigned char* text;
int edit_text_interrupt = 0;
size_t size;
struct sigaction sa1, sa2;

void handler(int sig_no)
{
    edit_text_interrupt = 1;
}

 void setHandler()
{
    sa1.sa_handler = handler;
    sa1.sa_flags = 0;
    sigemptyset(&sa1.sa_mask);
    if( sigaction(SIGINT, &sa1, &sa2) == -1 )
	puts("sigaction() : error");
}

void unsetHandler()
{
    if( sigaction(SIGINT, &sa2, NULL) == -1 )
        puts("sigaction() : error");
}

void editText()
{
    setHandler();

    edit_text_interrupt = 0;

    free(text);
    text = (unsigned char*)calloc(1, sizeof(unsigned char));
    text[0] = 0;
    size = 1;

    system("clear");
    
    // trash input
    fgetc(stdin);

    while( ! edit_text_interrupt )
    {
	char tmp = (unsigned char)fgetc(stdin);
	if( edit_text_interrupt == 1 || tmp == EOF || feof(stdin) )
	    break;
	text = (unsigned char*)realloc(text, ++size * sizeof(unsigned char));
	text[size - 2] = tmp;
	text[size - 1] = 0;
    }

    // cut last \n
    text[size - 2] = 0;
    text[size - 1] = 0;
    size -= 1;

    unsetHandler();
}

void saveText()
{
    char file_name[256];
    int fd;

    system("clear");
    printf("Input save path : ");
    scanf("%s", file_name);

    fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if( fd <= 0 )
    {
	puts("error occurred while opening file");
	return;
    }

    write(fd, text, size - 1);
    close(fd);

    printf("file save in %s\n", file_name);
}

void loadText()
{
    char file_name[256];
    int fd;
    char buf[1024];

    system("clear");
    printf("Input Load Path : ");
    scanf("%s", file_name);

    fd = open(file_name, O_RDONLY);
    if( fd <= 0 )
    {
	puts("error occurred while opening file");
	return;
    }

    while( read(fd, buf, 1024) > 0 )
    {
	printf("%s", buf);
    }
    printf("\n");

    close(fd);
}

int main()
{
    int input = 0;

    while( input != 4 )
    {
	puts("=== Text Editor ===");
	puts("1. Edit Text");
	puts("2. Save Text");
	puts("3. Load Text");
	puts("4. Exit");
	scanf("%d", &input);

	switch( input )
	{
	    case 1:
		editText();
		break;
	    case 2:
		saveText();
		break;
	    case 3:
		loadText();
		break;
	    case 4:
		break;
	    default:
		break;
	}
    }

    free(text);
}
