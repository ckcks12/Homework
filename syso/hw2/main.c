#include "Init.h"
#include "Scheduler.h"
#include "Thread.h"
#include "Testcase.h"

#include<stdio.h>

int main(void)
{
     thread_id tid;
     int arg;


     Init();

     thread_create(&tid, NULL, AppTask, &arg);

    RunScheduler();
   while(1);

}

