#include "hashmap.h"





void hashInit()
{
    memset(map, 0, sizeof(map));
}

pid_t* hashGet(pid_t pid)
{
    int i = 0;

    for( i=0; i<MAX_THREAD; i++ )
    {
        if( map[i][0] == pid )
            return map[i];
    }

    return NULL;
}

pid_t* hashPutParent(pid_t pid)
{
    int i = 0;

    for( i=0; i<MAX_THREAD; i++ )
    {
        if( map[i][0] == 0 )
        {
            map[i][0] = pid;
            return map[i];
        }
    }
}

void hashPut(pid_t p, pid_t c)
{
    int i = 0;
    pid_t* m;

    m = hashGet(p);
    if( m == NULL )
        m = hashPutParent(p);

    for( i=1; i<MAX_THREAD; i++ )
    {
        if( m[i] == 0 )
        {
            m[i] = c;
            return;
        }
    }
}

pid_t hashGetParent(pid_t c)
{
    int i = 0;

    for( i=0; i<MAX_THREAD; i++ )
    {
        int j = 0;

        for( j=1; j<MAX_THREAD; j++ )
        {
            if( map[i][j] == c )
                return map[i][0];
        }
    }
}

void hashDelete(pid_t c)
{
    int i = 0;

    for( i=0; i<MAX_THREAD; i++ )
    {
        int j = 0;

        for( j=1; j<MAX_THREAD; j++ )
        {
            if( map[i][j] == c )
            {
                map[i][j] = 0;
                return;
            }
        }
    }
}

void hashDeleteParent(pid_t p)
{
    int i = 0;

    for( i=0; i<MAX_THREAD; i++ )
    {
        int j = 0;

        if( map[i][0] == p )
        {
            for( j=0; j<MAX_THREAD; j++ )
            {
                map[i][j] = 0;
            }
            
            return;
        }
    }
}


void hashStatus()
{
    int i = 0;
    int j = 0;

    for( i=0; i<MAX_THREAD; i++ )
    {
        if( map[i][0] != 0 )
        {
            printf("%d : ", map[i][0]);

            for( j=1; j<MAX_THREAD; j++ )
            {
                if( map[i][j] != 0 )
                    printf("%d ", map[i][j]);
            }

            printf("\n");
        }
    }
}

char getProcStatus(pid_t pid)
{
    char fn[256] = {0, };
    char pid_str[256] = {0, };
    strcat(fn, "/proc/");
    sprintf(pid_str, "%d", pid);
    strcat(fn, pid_str);
    strcat(fn, "/stat");

    FILE* fp;
    int pid_tmp;
    char comm[512];
    char state;

    if( fp = fopen(fn, "r") )
    {
        fscanf(fp, "%d %s %c", &pid_tmp, &comm, &state);
        fclose(fp);

        return state;
    }
    return 0;
}




