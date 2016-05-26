#include <stdio.h>
#include "hw2.h"
#include "Disk.h"
#include "sema.h"

void printBuf(Buf* pbuf)
{
	printf("(%p)%d => ", pbuf, pbuf->blkno);
}

void showHash()
{
	Buf* pBuf;
	int i;

	puts("-----------------");
	puts("Hash Table");
	for( i=0; i<HASH_TBL_SIZE; i++ )
	{
		printf("\n%d : \n", i);
		pBuf = ppHashHead[i];
		while( pBuf != NULL )
		{
			printBuf(pBuf);
			pBuf = pBuf->phNext;
		}
	}
	puts("\n-----------------");
}

void showClean()
{
	Buf* pBuf;

	puts("-----------------");
	puts("Clean List");

	pBuf = ppObjListHead[BUF_LIST_CLEAN];
	while( pBuf != NULL )
	{
		printBuf(pBuf);
		pBuf = pBuf->poNext;
	}
	puts("\n-----------------");
}

void showDirty()
{
	Buf* pBuf;

	puts("-----------------");
	puts("Dirty List");
	//puts("-----------------");

	pBuf = ppObjListHead[BUF_LIST_DIRTY];
	while( pBuf != NULL )
	{
		printBuf(pBuf);
		pBuf = pBuf->poNext;
	}
	puts("\n-----------------");
}

void showFree()
{
	Buf* pBuf;

	puts("-----------------");
	puts("Free List");
	//puts("-----------------");

	pBuf = ppObjListHead[BUF_LIST_FREE];
	while( pBuf != NULL )
	{
		printBuf(pBuf);
		pBuf = pBuf->poNext;
	}
	puts("\n-----------------");
}

void showLru()
{
	Buf* pBuf;

	puts("-----------------");
	puts("Lru List");
	//puts("-----------------");

	pBuf = pLruListHead;
	while( pBuf != NULL )
	{
		printBuf(pBuf);
		pBuf = pBuf->plNext;
	}
	puts("\n-----------------");
}

void printData(char* data)
{
	int i;
	for( i=0; i<BLOCK_SIZE; i++ )
	{
		printf("%d ", data[i]);
	}
	puts("----");
}

void main(void)
{

	Buf* pBuf;
	int blkno;
	char pData[BLOCK_SIZE];

	BufInit();

	BufRead(0, pData);
	printData(pData);

	pData[10] = 11;
	BufWrite(0, pData);	
	BufSync();

	BufRead(0, pData);
	printData(pData);

}