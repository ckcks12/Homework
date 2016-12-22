#include "Thread.h"
#include "MsgQueue.h"
#include <stdio.h>
#include "Init.h"
#include "Thread.h"
#include "queue.h"
#include "hashmap.h"




/* ¹Ýµå½Ã ±¸ÇöÇÒ ÇÊ¿ä´Â ¾øÀ½. ¸¸ÀÏ ±¸ÇöÇß´Ù¸é, Init.c¿¡ ÀÖ´Â Init()¿¡ Ãß°¡ÇØ¾ß ÇÔ.*/ 
void _InitMsgQueue(void)
{
}

int checkQcb(int key)
{
	int i = 0;
	for( i=0; i<MAX_QCB_SIZE; i++ )
	{
		if( qcbTblEntry[i].key == key )
			return 1;
	}
	return 0;
}

Qcb* getQcb(int key)
{
	int debug = 0;

	if( __DEBUG__ && debug )
	{
		printf("getQcb(%d) : \n", key);
	}

	int i = 0;
	int empty_key_idx = -1;

	for( i=0; i<MAX_QCB_SIZE; i++ )
	{
		if( qcbTblEntry[i].key == -1 && empty_key_idx == -1 )
		{
			empty_key_idx = i;
		}
		else if( qcbTblEntry[i].key == key )
		{
			if( __DEBUG__ && debug )
			{
				printf("getQcb() : %d has been selected\n", i);
			}
			return qcbTblEntry[i].pQcb;
		}
	}

	if( empty_key_idx > -1 )
	{
		Qcb* qcb;
		qcb = (Qcb*)malloc(sizeof(Qcb));
		memset(qcb, 0, sizeof(Qcb));

		qcbTblEntry[empty_key_idx].key = key;
		qcbTblEntry[empty_key_idx].pQcb = qcb;

		if( __DEBUG__ && debug )
		{
			printf("getQcb() : %d has been created\n", empty_key_idx);
		}
		return qcb;
	}

	return NULL;
}

int 	mymsgget(int key, int msgflg)
{
	int debug = 0;
	if( getQcb(key) != NULL )
	{
		if( __DEBUG__ && debug )
			printf("mymsgget() : %d\n", key);

		return key;
	}

	// queue entry table is full
	perror("Queue Table Entry is full");

	return 0;
}



void deleteQcb(int key)
{
	int i = 0;
	for( i=0; i<MAX_QCB_SIZE; i++ )
	{
		if( qcbTblEntry[i].key == key )
		{
			Qcb* qcb = qcbTblEntry[i].pQcb;
			Message* msg = qcb->pMsgHead;
			Message* msg2;
			Thread* th = qcb->pThreadHead;
			Thread* th2;

			while( msg != NULL )
			{
				msg2 = msg;
				msg = msg->pNext;
				// free(msg2->data);
				free(msg2);
			}

			while( th != NULL )
			{
				th2 = th;
				th = th->pNext;
				th2->pPrev = NULL;
				th2->pNext = NULL;
				// thread_cancel(th2->pid);
				th2->status = THREAD_STATUS_READY;
				rqEnqueue(th2);
			}

			free(qcbTblEntry[i].pQcb);
			qcbTblEntry[i].key = -1;
			return;
		}
	}
}

void putMsg(Qcb* qcb, long type, char* data, int size)
{
	if( qcb == NULL )
		return;

	Message* msg = (Message*)malloc(sizeof(Message));
	memset(msg, 0, sizeof(Message));

	msg->type = type;
	// msg->data = (char*)malloc(MAX_MSG_SIZE);
	strncpy(msg->data, data, size);
	msg->size = size;

	if( qcb->pMsgHead == NULL )
	{
		qcb->pMsgHead = msg;
		qcb->pMsgTail = msg;
		qcb->msgCount = 1;
	}
	else
	{
		qcb->pMsgTail->pNext = msg;
		msg->pPrev = qcb->pMsgTail;
		qcb->pMsgTail = msg;
		qcb->msgCount++;
	}
}

int getMsg(Qcb* qcb, long type, Message* data)
{
	if( qcb == NULL )
		return -1;

	Message* msg;

	memset(data, 0, sizeof(Message));

	msg = qcb->pMsgHead;
	while( msg != NULL )
	{
		// if( __DEBUG__ )
		// 	printf("getMsg() : msg == NULL ? %d", msg == NULL);

		if( msg->type == type )
		{
			if( msg->pPrev == NULL && msg->pNext != NULL )
			{
				msg->pNext->pPrev = NULL;
				qcb->pMsgHead = msg->pNext;
				msg->pNext = NULL;
			}
			else if( msg->pPrev != NULL && msg->pNext != NULL )
			{
				msg->pPrev->pNext = msg->pNext;
				msg->pNext->pPrev = msg->pPrev;
				msg->pPrev = NULL;
				msg->pNext = NULL;
			}
			else if( msg->pPrev != NULL && msg->pNext == NULL )
			{
				msg->pPrev->pNext = NULL;
				qcb->pMsgTail = msg->pPrev;
				msg->pPrev = NULL;
			}
			else if( msg->pPrev == NULL && msg->pNext == NULL )
			{
				qcb->pMsgHead = NULL;
				qcb->pMsgTail = NULL;
			}

			// if( __DEBUG__ )
			// 	printf("getMsg() : %ld size message delivered\n", strlen(msg->data));

			data->type = msg->type;
			strcpy(data->data, msg->data);
			data->size = msg->size;
			free(msg);
			qcb->msgCount--;
			return 0;
		}
		msg = msg->pNext;
	}

	if( __DEBUG__ )
		printf("getMsg() : -1\n");
	return -1;
}

// void mqPutThread(Qcb* qcb, Thread* th, long type)
// {
// 	if( qcb == NULL )
// 		return;

// 	th->type = type;
// 	th->status = THREAD_STATUS_BLOCKED;
// 	th->pPrev = NULL;
// 	th->pNext = NULL;

// 	if( qcb->pThreadHead == NULL )
// 	{
// 		qcb->pThreadHead = th;
// 		qcb->waitThreadCount = 1;
// 	}
// 	else
// 	{
// 		qcb->pThreadTail->pNext = th;
// 		th->pPrev = qcb->pThreadTail;
// 		qcb->pThreadTail = th;
// 		qcb->waitThreadCount++;
// 	}

//     kill(th->pid, SIGSTOP);
// }

void mqPutThread(Qcb* qcb, Thread* th)
{
	if( qcb == NULL )
		return;

	th->pPrev = NULL;
	th->pNext = NULL;

	if( qcb->pThreadHead == NULL )
	{
		qcb->pThreadHead = th;
		qcb->pThreadTail = th;
		qcb->waitThreadCount = 1;
	}
	else
	{
		qcb->pThreadTail->pNext = th;
		th->pPrev = qcb->pThreadTail;
		qcb->pThreadTail = th;
		qcb->waitThreadCount++;
	}
}

Thread* mqGetThread(Qcb* qcb, long type)
{
	if( qcb == NULL )
		return NULL;

	Thread* th = qcb->pThreadHead;

	while( th != NULL )
	{
		if( th->type == type )
		{
			if( th->pPrev == NULL && th->pNext != NULL )
			{
				th->pNext->pPrev = NULL;
				qcb->pThreadHead = th->pNext;
				th->pPrev = NULL;
				th->pNext = NULL;
			}
			else if( th->pPrev != NULL && th->pNext != NULL )
			{
				th->pPrev->pNext = th->pNext;
				th->pNext->pPrev = th->pPrev;
				th->pPrev = NULL;
				th->pNext = NULL;
			}
			else if( th->pPrev != NULL && th->pNext == NULL )
			{
				th->pPrev->pNext = NULL;
				qcb->pThreadTail = th->pPrev;
				th->pPrev = NULL;
				th->pNext = NULL;
			}
			else if( th->pPrev == NULL && th->pNext == NULL )
			{
				qcb->pThreadHead = NULL;
				qcb->pThreadTail = NULL;
			}

			qcb->waitThreadCount--;
			return th;
		}

		th = th->pNext;
	}

	return NULL;
}

int 	mymsgsnd(int msqid, const void *msgp, int msgsz, int msgflg)
{
	MyMsg* mymsg = (MyMsg*)msgp;
	long type = mymsg->mtype;
	char* text = mymsg->mtext;

	Qcb* qcb = getQcb(msqid);
	putMsg(qcb, type, text, msgsz);

	// awake if somebody listen it
	Thread* th = mqGetThread(qcb, type);
	if( th != NULL )
	{
		th->status = THREAD_STATUS_READY;
		rqEnqueue(th);
	}
	return 0;
}

int	mymsgrcv(int msqid, void *msgp, int msgsz, long msgtyp, int msgflg)
{
	// printf("rqDequeue() : ReadyQHead : %d(%p), ReadyQTail : %d(%p)\n", ReadyQHead->pid, ReadyQHead, ReadyQTail->pid, ReadyQTail);
	Message msg;
	
	memset(msgp, 0, sizeof(MyMsg));

	Qcb* qcb = getQcb(msqid);
	if( qcb == NULL )
		return -1; // error

	// if msg exists in mq
	if( getMsg(qcb, msgtyp, &msg) == 0 )
	{
		((MyMsg*)msgp)->mtype = msg.type;
		strncpy(((MyMsg*)msgp)->mtext, msg.data, msgsz);
		return 0;
	}

	// wait
	if( __DEBUG__ )
		printf("mymsgrcv() : gonna wait\n");
	current_thread->type = msgtyp;
	current_thread->status = THREAD_STATUS_BLOCKED;
	mqPutThread(qcb, current_thread);
	current_thread = NULL;
	kill(thread_self(), SIGSTOP);
	if( __DEBUG__ )
		printf("mymsgrcv() : somebody awake me\n");

	// if wake, a message had been arrived
	if( checkQcb(msqid) == 1 )
	{
		if( getMsg(qcb, msgtyp, &msg) == 0 )
		{
			((MyMsg*)msgp)->mtype = msg.type;
			strncpy(((MyMsg*)msgp)->mtext, msg.data, msgsz);
			return 0;
		}
	}
	
	return -1;
}

int 	mymsgctl(int msqid, int cmd, void* buf)
{
	deleteQcb(msqid);
	return 0;
}