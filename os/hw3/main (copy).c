#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <assert.h>
#include "hw2.h"
#include "FileSystem.h"

#define DIR_NUM_MAX		100

extern FileSysInfo		*pFileSysInfo;

extern bitmapGet(char*, int);

void printBitmap(char* bitmap_blk)
{
	int i;
	for( i=0; i<20; i++ )
	{
		printf("%d", bitmapGet(bitmap_blk, i));
	}
	puts("");
}

void printStatus()
{
	printf("inode bitmap : ");
	printBitmap(pFileSysInfo->pInodeBitmap);

	printf("data block bitmap : ");
	printBitmap(pFileSysInfo->pBlockBitmap);
}


void ListDirContentsAndSize(const char* dirName)
{
	int i ;
	int count;
	DirEntry pDirEntry[DIR_NUM_MAX];
	InodeInfo pInodeInfo;
	count = DIR_NUM_MAX;

	EnumerateDirStatus(dirName, pDirEntry, &count);
	
	for (i = 0;i < count;i++)
	{
		if (pDirEntry[i].type == FILE_TYPE_FILE){
			//ReadInode(&pInodeInfo, pDirEntry[i].inodeNum);
			getInode(pDirEntry[i].inodeNum, &pInodeInfo);
			printf("\t name:%s, inode no:%d, type:file, size:%d, blocks:%d\n", pDirEntry[i].name, pDirEntry[i].inodeNum, pInodeInfo.size, pInodeInfo.blocks);
		}
		else if (pDirEntry[i].type == FILE_TYPE_DIR)
				printf("\t name:%s, inode no:%d, type:directory\n", pDirEntry[i].name, pDirEntry[i].inodeNum);
		else
		{
			assert(0);
		}
	}
}

int main()
{
	char blk[BLOCK_SIZE];
	char data[BLOCK_SIZE * 3 + 50];

	Mount(MT_TYPE_FORMAT);
	//Mount(MT_TYPE_READWRITE);

	printStatus();
	ListDirContentsAndSize("/");

	int file_desc = OpenFile("/a", OPEN_FLAG_CREATE);

	printStatus();
	ListDirContentsAndSize("/");
	
	memset(data, 1, BLOCK_SIZE * 3 + 50);
	printf("data : %s\n", data);

	printf("writefile : %d\n", WriteFile(file_desc, data, BLOCK_SIZE * 3 + 50));

	printStatus();
	ListDirContentsAndSize("/");

	memset(data, 0, BLOCK_SIZE * 3 + 50);
	printf("readFile : %d\n", ReadFile(file_desc, data, BLOCK_SIZE * 3 + 50));
	printf("data : %s\n", data);

	CloseFile(file_desc);
	printf("remove file : %d\n", RemoveFile("/a"));

	printStatus();
	ListDirContentsAndSize("/");

	Unmount();
}