#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

unsigned char* text;
int edit_text_interrupt = 0;

void handler(int sig_no)
{
    edit_text_interrupt = 1;
}

void editText()
{
    edit_text_interrupt = 0;

    free(text);
    text = (unsigned char*)calloc(1, sizeof(unsigned char));
    text[0] = 0;
    int size = 1;

    while( ! edit_text_interrupt )
    {
	char tmp = (unsigned char)fgetc(stdin);
	if( edit_text_interrupt )
	    break;
	text = (unsigned char*)realloc(text, ++size * sizeof(unsigned char));
	text[size - 2] = tmp;
	text[size - 1] = 0;
    }

    puts(text);
}

int main()
{
    int input = 0;
    struct sigaction sa;

    sa.sa_handler = handler;
    sa.sa_flags = 0; // default signal flag
    sigemptyset(&sa.sa_mask); // no block signal
    if( sigaction(SIGINT, &sa, NULL) == -1 )
    {
	puts("sigaction() : error");
	return -1;
    }

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
		break;
	    case 3:
		break;
	    case 4:
		break;
	    default:
		break;
	}
    }

    free(text);
}
