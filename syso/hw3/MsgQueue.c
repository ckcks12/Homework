#include "Thread.h"
#include "MsgQueue.h"
#include <stdio.h>
#include "Init.h"
#include "Thread.h"
#include "queue.h"
#include "hashmap.h"

#define MSG_TEXT_SIZE          1024
typedef struct _MyMsg{
     long mtype;                /* message type */
     char mtext[MSG_TEXT_SIZE]; /*message text (or body) */
} MyMsg;


/* 반드시 구현할 필요는 없음. 만일 구현했다면, Init.c에 있는 Init()에 추가해야 함.*/ 
void _InitMsgQueue(void)
{
}

int 	mymsgget(int key, int msgflg)
{
	if( getQcb(key) != NULL )
		return key;

	// queue entry table is full
	perror("Queue Table Entry is full");

	return 0;
}

Qcb* getQcb(int key)
{
	int i = 0;
	int empty_key_idx = -1;

	for( i=0; i<MAX_QCB_SIZE; i++ )
	{
		if( qcbTblEntry[i].key == -1 )
			empty_key_idx = i;
		else if( qcbTblEntry[i].key == key )
			return qcbTblEntry[i].pQcb;
	}

	if( empty_key_idx > -1 )
	{
		qcb = (Qcb*)malloc(sizeof(Qcb));
		memset(qcb, 0, sizeof(Qcb));

		qcbTblEntry[empty_key_idx].key = key;
		qcbTblEntry[empty_key_idx].pQcb = qcb;
		return qcb;
	}

	return NULL;
}

void deleteQcb(int key)
{
	int i = 0;
	for( i=0; i<MAX_QCB_SIZE; i++ )
	{
		if( qcbTblEntry[i].key == key )
		{
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
	msg->data = (char*)malloc(MAX_MSG_SIZE);
	strcpy(msg->data, data);
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

int getMsg(Qcb* qcb, long type, char* data, int size)
{
	if( qcb == NULL )
		return;

	Message* msg;

	memset(data, 0, size);

	msg = qcb->pMsgHead;
	while( msg != NULL )
	{
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
				qcb->pMsgTail - msg->pPrev;
				msg->pPrev = NULL;
			}
			else if( msg->pPrev == NULL && msg->pNext == NULL )
			{
				qcb->pMsgHead = NULL;
				qcb->pMsgTail = NULL;
			}

			strcpy(data, msg->data, size);
			free(msg->data);
			free(msg);
			qcb->msgCount--;
			return 0;
		}
		msg = msg->pNext;
	}

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

	if( qcb->pThreadHead == NULL )
	{
		qcb->pThreadHead = th;
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
				qcb->PThreadTail = NULL;
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

	Qcb* qcb = getQcb(msgid);
	putMSg(qcb, type, text, msgsz);

	// awake if somebody listen it
	Thread* th = mqGetThread(qcb, type);
	if( th != NULL )
	{
		th->status = THREAD_STATUS_READY;
		rqEnqueue(th);
	}
	return 0;
}

int	mymsgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg)
{
	memset(msgp, 0, msgsz);

	Qcb* qcb = getQcb(msgid);
	if( qcb == NULL )
		return 0; // error

	// if msg exists in mq
	getMsg(Qcb* qcb, long type, char* data, int size)
	if( getMsg(qcb, msgtyp, (char*)msgp, ))
	Message* msg = 

	return 0;
}

int 	mymsgctl(int msqid, int cmd, void* buf)
{
	return 0;
}