#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int total = 0;

void* f(void* param)
{
    int p = *((int*)param);
    int v = p;
    int i = 0;
    for( i=1; i<p; i++ )
	v *= i;

    printf("%d! = %d\n", p, v);
    total += v;
    free(param);
}

int main(int argc, char* argv[])
{
    int val = atoi(argv[1]);
    pthread_t* tids = (pthread_t*)calloc(val, sizeof(pthread_t));
    int i;
    for( i=val; i>=1; i-- )
    {
	int* param = (int*)malloc(sizeof(int));
	*param = i;
	pthread_create(&tids[i - 1], NULL, f, param);
    }
    for( i=0; i<val; i++ )
    {
	pthread_join(tids[i], NULL);
    }

    puts("=====All Thread Ended=====");
    printf("Result = %d\n", total);
}
