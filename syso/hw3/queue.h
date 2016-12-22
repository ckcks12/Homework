#ifndef __queue__
#define __queue__
#define _GNU_SOURCE
#include "Thread.h"
#include "Init.h"
#include "Scheduler.h"
#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sched.h>
#include <string.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <sched.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "MsgQueue.h"
#include <unistd.h>

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

#define MSG_TEXT_SIZE          512
typedef struct _MyMsg{
     long mtype;                /* message type */
     char mtext[MSG_TEXT_SIZE]; /*message text (or body) */
} MyMsg;

#endif 