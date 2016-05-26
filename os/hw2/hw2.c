#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "hw2.h"
#include "Disk.h"
#include "sema.h"
#include <string.h>
#include <sched.h>

#define SEMA_IDX_MAIN 0
#define SEMA_IDX_DAEMON 1

void before()
{
	puts("before====================");
}

void after()
{
	puts("after=====================");
}

void insertHash(Buf* pBuf)
{
	Buf** list_head = &ppHashHead[pBuf->blkno % HASH_TBL_SIZE];
	Buf** list_tail = &ppHashTail[pBuf->blkno % HASH_TBL_SIZE];

	if( *list_head == NULL && *list_tail == NULL )
	{
		pBuf->phPrev = NULL;
		pBuf->phNext = NULL;
		*list_head = pBuf;
		*list_tail = pBuf;
	}
	else
	{
		(*list_tail)->phNext = pBuf;
		pBuf->phPrev = (*list_tail);
		pBuf->phNext = NULL;
		*list_tail = pBuf;
	}
}

void removeHash(int blkno)
{
	Buf** list_head = &ppHashHead[blkno % HASH_TBL_SIZE];
	Buf** list_tail = &ppHashTail[blkno % HASH_TBL_SIZE];
	Buf* pBuf;

	pBuf = *list_head;
	while( pBuf != NULL )
	{
		if( pBuf->blkno == blkno )
		{
			break;
		}
		else
		{
			pBuf = pBuf->phNext;
		}
	}	
	if( pBuf != NULL )
	{
		if( *list_head == *list_tail )
		{
			*list_head = NULL;
			*list_tail = NULL;
		}
		else if( pBuf == *list_head )
		{
			*list_head = pBuf->phNext;
			pBuf->phNext->phPrev = pBuf->phPrev;
		}
		else if( pBuf == *list_tail )
		{
			*list_tail = pBuf->phPrev;
			pBuf->phPrev->phNext = pBuf->phNext;
		}
		else
		{
			pBuf->phPrev->phNext = pBuf->phNext;
			pBuf->phNext->phPrev = pBuf->phPrev;
		}
		pBuf->phPrev = NULL;
		pBuf->phNext = NULL;
	}
}

void insertClean(Buf* pBuf)
{
	Buf** list_head = &ppObjListHead[BUF_LIST_CLEAN];
	Buf** list_tail = &ppObjListTail[BUF_LIST_CLEAN];

	if( *list_head == NULL && *list_tail == NULL )
	{
		*list_head = pBuf;
		*list_tail = pBuf;
		pBuf->poPrev = NULL;
		pBuf->poNext = NULL;
	}
	else
	{
		(*list_tail)->poNext = pBuf;
		pBuf->poPrev = *list_tail;
		pBuf->poNext = NULL;
		*list_tail = pBuf;
	}
}

void removeClean(int blkno)
{
	Buf** list_head = &ppObjListHead[BUF_LIST_CLEAN];
	Buf** list_tail = &ppObjListTail[BUF_LIST_CLEAN];
	Buf* pBuf;

	pBuf = *list_head;
	while( pBuf != NULL )
	{
		if( pBuf->blkno == blkno )
		{
			break;
		}
		else
		{
			pBuf = pBuf->poNext;
		}
	}	
	if( pBuf != NULL )
	{
		if( *list_head == *list_tail )
		{
			*list_head = NULL;
			*list_tail = NULL;
		}
		else if( pBuf == *list_head )
		{
			*list_head = pBuf->poNext;
			pBuf->poNext->poPrev = pBuf->poPrev;
		}
		else if( pBuf == *list_tail )
		{
			*list_tail = pBuf->poPrev;
			pBuf->poPrev->poNext = pBuf->poNext;
		}
		else
		{
			pBuf->poPrev->poNext = pBuf->poNext;
			pBuf->poNext->poPrev = pBuf->poPrev;
		}
		pBuf->poPrev = NULL;
		pBuf->poNext = NULL;
	}
}

void insertDirty(Buf* pBuf)
{

	Buf** list_head = &ppObjListHead[BUF_LIST_DIRTY];
	Buf** list_tail = &ppObjListTail[BUF_LIST_DIRTY];

	if( *list_head == NULL && *list_tail == NULL )
	{
		*list_head = pBuf;
		*list_tail = pBuf;
		pBuf->poPrev = NULL;
		pBuf->poNext = NULL;
	}
	else
	{
		(*list_tail)->poNext = pBuf;
		pBuf->poPrev = *list_tail;
		pBuf->poNext = NULL;
		*list_tail = pBuf;
	}
}

void removeDirty(int blkno)
{
	Buf** list_head = &ppObjListHead[BUF_LIST_DIRTY];
	Buf** list_tail = &ppObjListTail[BUF_LIST_DIRTY];
	Buf* pBuf;

	pBuf = *list_head;
	while( pBuf != NULL )
	{
		if( pBuf->blkno == blkno )
		{
			break;
		}
		else
		{
			pBuf = pBuf->poNext;
		}
	}	
	if( pBuf != NULL )
	{
		if( *list_head == *list_tail )
		{
			*list_head = NULL;
			*list_tail = NULL;
		}
		else if( pBuf == *list_head )
		{
			*list_head = pBuf->poNext;
			pBuf->poNext->poPrev = pBuf->poPrev;
		}
		else if( pBuf == *list_tail )
		{
			*list_tail = pBuf->poPrev;
			pBuf->poPrev->poNext = pBuf->poNext;
		}
		else
		{
			pBuf->poPrev->poNext = pBuf->poNext;
			pBuf->poNext->poPrev = pBuf->poPrev;
		}
		pBuf->poPrev = NULL;
		pBuf->poNext = NULL;
	}
}

Buf* popDirty()
{
	Buf** list_head = &ppObjListHead[BUF_LIST_DIRTY];
	Buf** list_tail = &ppObjListTail[BUF_LIST_DIRTY];
	Buf* pBuf;

	if( *list_head == NULL )
	{
		pBuf = NULL;
	}
	else if( *list_head == *list_tail )
	{
		pBuf = *list_tail;
		(*list_tail)->poPrev = NULL;
		(*list_tail)->poNext = NULL;
		*list_head = NULL;
		*list_tail = NULL;
	}
	else
	{
		pBuf = *list_head;
		(*list_head)->poNext->poPrev = NULL;
		*list_head = (*list_head)->poNext;
		pBuf->poPrev = NULL;
		pBuf->poNext = NULL;
	}

	return pBuf;
}

int existDirty(int blkno)
{
	Buf** list_head = &ppObjListHead[BUF_LIST_DIRTY];
	Buf** list_tail = &ppObjListTail[BUF_LIST_DIRTY];
	Buf* pBuf;

	if( *list_head == NULL )
	{
		return 0;
	}
	
	pBuf = *list_head;
	while( pBuf != NULL )
	{
		if( pBuf->blkno == blkno )
		{
			return 1;
		}
		else
		{
			pBuf = pBuf->poNext;
		}
	}

	return 0;
}

void pushFree(Buf* pBuf)
{
	Buf** list_head = &ppObjListHead[BUF_LIST_FREE];
	Buf** list_tail = &ppObjListTail[BUF_LIST_FREE];

	if( *list_head == NULL && *list_tail == NULL )
	{
		*list_head = pBuf;
		*list_tail = pBuf;
		pBuf->poPrev = NULL;
		pBuf->poNext = NULL;
	}
	else
	{
		(*list_tail)->poNext = pBuf;
		pBuf->poPrev = *list_tail;
		pBuf->poNext = NULL;
		*list_tail = pBuf;
	}
}

Buf* popFree()
{
	Buf** list_head = &ppObjListHead[BUF_LIST_FREE];
	Buf** list_tail = &ppObjListTail[BUF_LIST_FREE];
	Buf* pBuf;

	if( *list_head == NULL )
	{
		pBuf = NULL;
	}
	else if( *list_head == *list_tail )
	{
		pBuf = *list_tail;
		(*list_tail)->poPrev = NULL;
		(*list_tail)->poNext = NULL;
		*list_head = NULL;
		*list_tail = NULL;
		pBuf->blkno = BLKNO_INVALID;
	}
	else
	{
		pBuf = *list_head;
		(*list_head)->poNext->poPrev = NULL;
		*list_head = (*list_head)->poNext;
		pBuf->poPrev = NULL;
		pBuf->poNext = NULL;
		pBuf->blkno = BLKNO_INVALID;
	}

	return pBuf;
}

int countFree()
{
	Buf** list_head = &ppObjListHead[BUF_LIST_FREE];
	Buf** list_tail = &ppObjListTail[BUF_LIST_FREE];
	Buf* pBuf;
	int cnt = 0;

	pBuf = *list_head;
	while( pBuf != NULL )
	{
		cnt++;
		pBuf = pBuf->poNext;
	}

	return cnt;
}

void insertLru(Buf* pBuf)
{
	Buf** list_head = &pLruListHead;
	Buf** list_tail = &pLruListTail;

	if( *list_head == NULL && *list_tail == NULL )
	{
		*list_head = pBuf;
		*list_tail = pBuf;
		pBuf->plPrev = NULL;
		pBuf->plNext = NULL;
	}
	else
	{
		(*list_tail)->plNext = pBuf;
		pBuf->plPrev = *list_tail;
		pBuf->plNext = NULL;
		*list_tail = pBuf;
	}
}

void removeLru(int blkno)
{
	Buf** list_head = &pLruListHead;
	Buf** list_tail = &pLruListTail;
	Buf* pBuf;

	pBuf = *list_head;
	while( pBuf != NULL )
	{
		if( pBuf->blkno == blkno )
		{
			break;
		}
		else
		{
			pBuf = pBuf->plNext;
		}
	}	
	if( pBuf != NULL )
	{
		if( *list_head == *list_tail )
		{
			*list_head = NULL;
			*list_tail = NULL;
		}
		else if( pBuf == *list_head )
		{
			*list_head = pBuf->plNext;
			pBuf->plNext->plPrev = pBuf->plPrev;
		}
		else if( pBuf == *list_tail )
		{
			*list_tail = pBuf->plPrev;
			pBuf->plPrev->plNext = pBuf->plNext;
		}
		else
		{
			pBuf->plPrev->plNext = pBuf->plNext;
			pBuf->plNext->plPrev = pBuf->plPrev;
		}
		pBuf->plPrev = NULL;
		pBuf->plNext = NULL;
	}
}

Buf* popLru()
{
	Buf** list_head = &pLruListHead;
	Buf** list_tail = &pLruListTail;
	Buf* pBuf;

	if( *list_head == NULL )
	{
		pBuf = NULL;
	}
	else if( *list_head == *list_tail )
	{
		pBuf = *list_tail;
		(*list_tail)->plPrev = NULL;
		(*list_tail)->plNext = NULL;
		*list_head = NULL;
		*list_tail = NULL;
	}
	else
	{
		pBuf = *list_head;
		(*list_head)->plNext->plPrev = NULL;
		*list_head = (*list_head)->plNext;
		pBuf->plPrev = NULL;
		pBuf->plNext = NULL;
	}

	return pBuf;
}

Buf* BufFind(int blkno)
{
	//check count of buffers in free list
	int free_buf_cnt = countFree();
	if( free_buf_cnt <= MAX_BUFLIST_NUM / 10 )
	{
		//wake daemon
		semaUnlock(SEMA_IDX_DAEMON);
		//wait for daemon's work 
		semaLock(SEMA_IDX_MAIN);
	}

	Buf** list_head = &ppHashHead[blkno % HASH_TBL_SIZE];
	Buf** list_tail = &ppHashTail[blkno % HASH_TBL_SIZE];
	Buf* pBuf = NULL;

	pBuf = *list_head;
	while( pBuf != NULL )
	{
		if( pBuf->blkno == blkno )
		{
			break;
		}
		else
		{
			pBuf = pBuf->phNext;
		}
	}	
	return pBuf;
}

void copyBlock(char* src, char* dest)
{
	int i;
	for( i=0; i<BLOCK_SIZE; i++ )
	{
		dest[i] = src[i];
	}
}

int BufDaemon()
{
	Buf* pBuf;

	while(1)
	{
		semaLock(SEMA_IDX_DAEMON);
		while( countFree() <= ((MAX_BUF_NUM / 10) * 3) )
		{
			pBuf = popLru();
			removeHash(pBuf->blkno);
			if( existDirty(pBuf->blkno) )
			{
				//write to device.
				DevWriteBlock(pBuf->blkno, (char*)pBuf->pMem);
				removeDirty(pBuf->blkno);
			}
			else
			{
				removeClean(pBuf->blkno);
			}
			free(pBuf->pMem);
			memset(pBuf, 0, sizeof(Buf));
			pBuf->pMem = malloc(BLOCK_SIZE);
			pushFree(pBuf);
		}
		semaUnlock(SEMA_IDX_MAIN);
	}
}

void BufInit(void)
{
	int i = 0;
	Buf* pBuf;

	//init all list
	for( i=0; i<HASH_TBL_SIZE; i++ )
	{
		ppHashHead[i] = NULL;
		ppHashTail[i] = NULL;
	}
	for( i=0; i<3; i++ )
	{
		ppObjListHead[i] = NULL;
		ppObjListTail[i] = NULL;
	}
	pLruListHead = NULL;
	pLruListTail = NULL;

	//create buffers
	for( i=0; i<MAX_BUF_NUM; i++ )
	{
		pBuf = (Buf*)malloc(sizeof(Buf));
		pBuf->pMem = malloc(BLOCK_SIZE);
		pushFree(pBuf);
	}

	//init device
	DevCreateDisk();
	DevOpenDisk();

	//init semaphore
	semaInit();
	semaLock(SEMA_IDX_MAIN);
	semaLock(SEMA_IDX_DAEMON);

	//init daemon
	const int stack_size = 1024;
	char* stack = (char*)malloc(stack_size);
	memset(stack, 0, stack_size);
	char* stack_top = stack + stack_size;

	clone(BufDaemon, stack_top, CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0);
}


void BufRead(int blkno, void* pData)
{
	Buf* pBuf;

	pBuf = BufFind(blkno);
	if( pBuf != NULL )
	{
		removeLru(blkno);
		insertLru(pBuf);
		copyBlock((char*)pBuf->pMem, (char*)pData);
		return;
	}

	pBuf = popFree();
	pBuf->blkno = blkno;
	//pBuf->pMem = (void*)malloc(BLOCK_SIZE);
	DevReadBlock(blkno, (char*)pBuf->pMem);
	insertHash(pBuf);
	insertClean(pBuf);
	removeLru(blkno);
	insertLru(pBuf);

	copyBlock((char*)pBuf->pMem, (char*)pData);
}


void BufWrite(int blkno, void* pData)
{
	Buf* pBuf;

	pBuf = BufFind(blkno);
	if( pBuf == NULL )
	{
		char ptr_tmp_data[BLOCK_SIZE];
		BufRead(blkno, ptr_tmp_data);
		pBuf = BufFind(blkno);
	}

	removeClean(blkno);
	if( ! existDirty(blkno) )
	{
		insertDirty(pBuf);
	}
	removeLru(blkno);
	insertLru(pBuf);

	copyBlock((char*)pData, (char*)pBuf->pMem);
}

void BufSync(void)
{
	Buf* pBuf;

	while( (pBuf = popDirty()) != NULL )
	{
		//write to device.
		DevWriteBlock(pBuf->blkno, (char*)pBuf->pMem);
		removeDirty(pBuf->blkno);
		insertClean(pBuf);
	}
}

void BufFinish(void)
{
	semaDel();
}

void GetBufInfoByListNum(BufList listnum, Buf** ppBufInfo, int* pNumBuf)
{ 
	Buf** list_head = &ppObjListHead[listnum];
	Buf** list_tail = &ppObjListTail[listnum];
	Buf* pBuf = NULL;
	int i = 0;

	pBuf = *list_head;
	while( pBuf != NULL )
	{
		ppBufInfo[i++] = pBuf;
		pBuf = pBuf->poNext;
	}

	*pNumBuf = i;
}

void GetBufInfoInLruList(Buf** ppBufInfo, int* pNumBuf)
{
	Buf** list_head = &pLruListHead;
	Buf** list_tail = &pLruListTail;
	Buf* pBuf = NULL;
	int i = 0;

	pBuf = *list_head;
	while( pBuf != NULL )
	{
		ppBufInfo[i++] = pBuf;
		pBuf = pBuf->plNext;
	}

	*pNumBuf = i;
}