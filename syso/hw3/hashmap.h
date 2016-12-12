#ifndef __HASHMAP__
#define __HASHMAP__
#include "Thread.h"
#include <stdlib.h>


#define MAX_THREAD 100

pid_t map[MAX_THREAD][MAX_THREAD];
Thread* current_thread;
Thread* new_thread;

void hashInit();
pid_t* hashGet(pid_t);
pid_t* hashPutParent(pid_t);
void hashPut(pid_t, pid_t);
pid_t hashGetParent(pid_t);
void hashDelete(pid_t);
void hashDeleteParent(pid_t);
void hashStatus();

char getProcStatus(pid_t);

#endif

