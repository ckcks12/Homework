#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    const char* file_name = "./hw1.txt";
    // open
    int fd = open(file_name, O_RDONLY);
    if( fd < 0 )
    {
	printf("error occured while opening the file - %s\n", file_name);
	return -1;
    }

    // lseek
    int offset = lseek(fd, 4, SEEK_SET);
    if( offset < 0 )
    {
	printf("error occured while seeking the file - %s\n", file_name);
	return -2;
    }

    // read
    char buf;
    while( read(fd, &buf, 1) > 0 )
	printf("%c", buf);

    // close
    close(fd);

    return 0;
}
