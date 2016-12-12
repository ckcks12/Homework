#ifndef __queue__
#define __queue__
#include "Thread.h"

#define __DEBUG__ 0

int rqIsEmpty();
void rqEnqueue(Thread*);
Thread* rqDequeue();
void rqDelete(Thread*);
Thread* rqGet(thread_t);

int wqIsEmpty();
void wqEnqueue(Thread*);
Thread* wqDequeue();
void wqDelete(Thread*);
Thread* wqGet(thread_t);


pid_t ppid;

#endif 