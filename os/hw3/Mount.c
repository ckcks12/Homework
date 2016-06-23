#include <stdio.h>
#include <stdlib.h>
#include "FileSystem.h"
#include "Disk.h"

extern int		bitmapGet(char *bitmap, int idx);
extern void		bitmapSet(char *bitmap, int idx);
extern int		bitmapFirstFit(char *bitmap);

FileSysInfo* pFileSysInfo = NULL;

void printBitmap1(char* bitmap_blk)
{
	int i;
	for( i=0; i<20; i++ )
	{
		printf("%d", bitmapGet(bitmap_blk, i));
	}
	puts("");
}

void		Mount(MountType type)
{
	char *tmp_blk;

	if( type == MT_TYPE_READWRITE )
	{
		DevOpenDisk();
	}
	else if( type == MT_TYPE_FORMAT )
	{
		// open device
		DevCreateDisk();
		DevOpenDisk();

		// temporary block for packing data
		tmp_blk = (char *)malloc(BLOCK_SIZE);

		// allocate FileSysInfo
		pFileSysInfo					=		(FileSysInfo *)malloc(sizeof(FileSysInfo));
		memset(pFileSysInfo, 0, sizeof(FileSysInfo));
		// init FileSysInfo 
		pFileSysInfo->blocks			=		BLOCK_SIZE;
		pFileSysInfo->rootInodeNum		=		0;
		pFileSysInfo->diskCapacity		=		FS_DISK_CAPACITY / BLOCK_SIZE;
		pFileSysInfo->numAllocBlocks	=		4; // super, inode bit, data block bit, root inode
		pFileSysInfo->numFreeBlocks		=		pFileSysInfo->diskCapacity - pFileSysInfo->numAllocBlocks;
		pFileSysInfo->numInodes			=		FS_INODE_COUNT;
		pFileSysInfo->numAllocInodes	=		1; // root inode
		pFileSysInfo->numFreeInodes		=		pFileSysInfo->numInodes - pFileSysInfo->numAllocInodes;
		pFileSysInfo->inodeBitmapStart	=		1;
		pFileSysInfo->blockBitmapStart	=		2;
		pFileSysInfo->inodeListStart	=		3;
		pFileSysInfo->dataStart			=		pFileSysInfo->inodeListStart + pFileSysInfo->numInodes;
		// packing FileSysInfo into one block
		memset(tmp_blk, 0, BLOCK_SIZE);
		memcpy(tmp_blk, pFileSysInfo, sizeof(FileSysInfo));
		// write FileSysInfo
		DevWriteBlock(0, tmp_blk);
		// free FileSysInfo
		free(pFileSysInfo);

		// allocate and init inode bitmap
		memset(tmp_blk, 0, BLOCK_SIZE);
		bitmapSet(tmp_blk, 0); // root inode
		// write inode bitmap
		DevWriteBlock(1, tmp_blk);

		// allocate and init data block bitmap
		memset(tmp_blk, 0, BLOCK_SIZE);
		// write data block bitmap
		DevWriteBlock(2, tmp_blk);

		// allocate root inode
		InodeInfo *i_root;
		i_root = (InodeInfo *)malloc(sizeof(InodeInfo));
		memset(i_root, 0, sizeof(InodeInfo));
		// init root inode
		i_root->size		=		0;
		i_root->type		=		FILE_TYPE_DIR;
		//i_root->mode		=
		i_root->blocks		=		0;
		//memset(i_root->directPtr, 0, sizeof(int) * NUM_OF_DIRECT_BLK_PTR);
		// packing root inode into one block
		memset(tmp_blk, 0, BLOCK_SIZE);
		memcpy(tmp_blk, i_root, sizeof(InodeInfo));
		// write root inode
		DevWriteBlock(3, tmp_blk);
		// free root inode
		free(i_root);

		// free tmp_blk
		free(tmp_blk);
	}

	// allocate tmp_blk
	tmp_blk = (char *)malloc(BLOCK_SIZE);
	memset(tmp_blk, 0, BLOCK_SIZE);
	// read block 0
	DevReadBlock(0, tmp_blk);
	// allocate FileSysInfo
	pFileSysInfo = (FileSysInfo *)malloc(sizeof(FileSysInfo));
	memset(pFileSysInfo, 0, sizeof(FileSysInfo));
	// init FileSysInfo 
	memcpy(pFileSysInfo, tmp_blk, sizeof(FileSysInfo));

	// indicate inode bitmap
	tmp_blk = (char *)calloc(1, BLOCK_SIZE);
	DevReadBlock(1, tmp_blk);
	pFileSysInfo->pInodeBitmap = tmp_blk;

	// indicate data block bitmap
	tmp_blk = (char *)malloc(BLOCK_SIZE);
	memset(tmp_blk, 0, BLOCK_SIZE);
	DevReadBlock(2, tmp_blk);
	pFileSysInfo->pBlockBitmap = tmp_blk;

	FileSysInit();
}


void		Unmount(void)
{
	FileSysFinish();
	if( pFileSysInfo )
	{
		free(pFileSysInfo);
	}
}