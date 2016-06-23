#include <stdio.h>
#include <stdlib.h>
#include "hw2.h"
#include "FileSystem.h"


FileDescTable* pFileDescTable = NULL;

int bitmapGet(char *bitmap, int idx)
{
	int bit_mask[8] = {128, 64, 32, 16, 8, 4, 2, 1};
	if( bitmap[idx / 8] & bit_mask[idx % 8] )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void bitmapSet(char *bitmap, int idx)
{
	int bit_mask[8] = {128, 64, 32, 16, 8, 4, 2, 1};
	bitmap[idx / 8] = bitmap[idx / 8] | bit_mask[idx % 8];
}

void bitmapUnset(char *bitmap, int idx)
{
	int bit_mask[8] = {128, 64, 32, 16, 8, 4, 2, 1};
	bitmap[idx / 8] = bitmap[idx / 8] & ~bit_mask[idx % 8];
}

int bitmapFirstFit(char *bitmap)
{
	int bit_mask[8] = {128, 64, 32, 16, 8, 4, 2, 1};
	int i;
	for( i=0; i<FS_INODE_COUNT; i++ )
	{
		if( ! bitmapGet(bitmap, i) )
		{
			return i;
		}
	}
	return -1;
}

int addFileDesc(int inode_no)
{
	int i;
	FileDesc *table;

	table = pFileDescTable->file;

	for( i=0; i<FS_INODE_COUNT; i++ )
	{
		if( ! table[i].valid_bit )
		{
			table[i].inodeNo = inode_no;
			table[i].offset = inode_no % NUM_OF_INODE_PER_BLK;
			table[i].valid_bit = 1;
			return i;
		}
	}

	return -1;
}

int removeFileDesc(int idx)
{
	memset(pFileDescTable->file + idx, 0, sizeof(FileDesc));
}

char * padding(void *tmp_blk, void *data, size_t size)
{
	memset(tmp_blk, 0, BLOCK_SIZE);
	if( size > 0 )
	{
		memcpy(tmp_blk, data, size);
	}
	return (char *)tmp_blk;
}

int findFileDesc(int inode_no)
{
	int i;
	for( i=0; i<FS_INODE_COUNT; i++ )
	{
		if( pFileDescTable->file[i].inodeNo == inode_no )
		{
			return i;
		}
	}
	return -1;
}

/*
update file system info
*/
void  syncFileSysInfo()
{
	char blk[BLOCK_SIZE];
	FileSysInfo fsi;

	memcpy(&fsi, pFileSysInfo, sizeof(FileSysInfo));
	fsi.pInodeBitmap = 0;
	fsi.pBlockBitmap = 0; // protrect itself

	BufWrite(0, padding(blk, &fsi, sizeof(FileSysInfo)));
	BufSync();

	// inode bitmap
	BufWrite(1, padding(blk, pFileSysInfo->pInodeBitmap, BLOCK_SIZE));
	BufSync();

	// data block bitmpa
	BufWrite(2, padding(blk, pFileSysInfo->pBlockBitmap, BLOCK_SIZE));
	BufSync();
}

/*
data block gpud
*/
void getData(int data_no, void *data)
{
	BufRead(pFileSysInfo->dataStart + data_no, data);
}

int putData(void *data)
{
	char blk[BLOCK_SIZE];
	int data_no;

	data_no = bitmapFirstFit(pFileSysInfo->pBlockBitmap);

	BufWrite(pFileSysInfo->dataStart + data_no, padding(blk, data, BLOCK_SIZE));
	BufSync();

	// file system info update
	pFileSysInfo->numAllocBlocks++;
	pFileSysInfo->numFreeBlocks--;
	bitmapSet(pFileSysInfo->pBlockBitmap, data_no);
	syncFileSysInfo();

	return data_no;
}

void updateData(int data_no, void *data)
{
	char blk[BLOCK_SIZE];
	BufWrite(pFileSysInfo->dataStart + data_no, padding(blk, data, BLOCK_SIZE));
	BufSync();
}

void deleteData(int data_no)
{
	char blk[BLOCK_SIZE];
	BufWrite(pFileSysInfo->dataStart + data_no, padding(blk, 0, 0));
	BufSync();

	// file system info update
	pFileSysInfo->numAllocBlocks--;
	pFileSysInfo->numFreeBlocks++;
	bitmapUnset(pFileSysInfo->pBlockBitmap, data_no);
	syncFileSysInfo();
}

/*
inode gpud
*/
void getInode(int inode_no, InodeInfo *inode)
{
	int blk_no;
	int offset;
	char tmp_blk[BLOCK_SIZE];
	InodeInfo inode_arr[NUM_OF_INODE_PER_BLK];

	blk_no = inode_no / NUM_OF_INODE_PER_BLK;
	offset = inode_no % NUM_OF_INODE_PER_BLK;
	BufRead(pFileSysInfo->inodeListStart + blk_no, inode_arr);
	memcpy(inode, &inode_arr[offset], sizeof(InodeInfo));
}

int putInode(int size, FileType type, FileMode mode, int blocks)
{
	int blk_no;
	int offset;
	InodeInfo inode_arr[NUM_OF_INODE_PER_BLK];
	char blk[BLOCK_SIZE];
	InodeInfo inode;
	int inode_no;

	inode.size = size;
	inode.type = type;
	inode.mode = mode;
	inode.blocks = blocks;
	memset(inode.directPtr, 0, sizeof(int) * NUM_OF_DIRECT_BLK_PTR);

	inode_no = bitmapFirstFit(pFileSysInfo->pInodeBitmap);
	blk_no = inode_no / NUM_OF_INODE_PER_BLK;
	offset = inode_no % NUM_OF_INODE_PER_BLK;

	BufRead(pFileSysInfo->inodeListStart + blk_no, inode_arr);
	inode_arr[offset] = inode;

	BufWrite(pFileSysInfo->inodeListStart + blk_no, padding(blk, inode_arr, BLOCK_SIZE));
	BufSync();

	// file system info update
	pFileSysInfo->numAllocInodes++;
	pFileSysInfo->numFreeInodes--;
	bitmapSet(pFileSysInfo->pInodeBitmap, inode_no);
	syncFileSysInfo();

	return inode_no;
}

void updateInode(int inode_no, InodeInfo inode)
{
	int blk_no;
	int offset;
	InodeInfo inode_arr[NUM_OF_INODE_PER_BLK];
	char blk[BLOCK_SIZE];

	blk_no = inode_no / NUM_OF_INODE_PER_BLK;
	offset = inode_no % NUM_OF_INODE_PER_BLK;
	BufRead(pFileSysInfo->inodeListStart + blk_no, inode_arr);
	inode_arr[offset] = inode;

	BufWrite(pFileSysInfo->inodeListStart + blk_no, padding(blk, inode_arr, BLOCK_SIZE));
	BufSync();
}

void deleteInode(int inode_no)
{
	int blk_no;
	int offset;
	InodeInfo inode_arr[NUM_OF_INODE_PER_BLK];
	char blk[BLOCK_SIZE];
	InodeInfo inode;
	int i;

	getInode(inode_no, &inode);
	for( i=0; i<inode.blocks; i++ )
	{
		deleteData(inode.directPtr[i]);
	}

	blk_no = inode_no / NUM_OF_INODE_PER_BLK;
	offset = inode_no % NUM_OF_INODE_PER_BLK;
	BufRead(pFileSysInfo->inodeListStart + blk_no, inode_arr);
	memset(&inode_arr[offset], 0, sizeof(InodeInfo));

	BufWrite(pFileSysInfo->inodeListStart + blk_no, padding(blk, inode_arr, BLOCK_SIZE));
	BufSync();

	// file system info update
	pFileSysInfo->numAllocInodes--;
	pFileSysInfo->numFreeInodes++;
	bitmapUnset(pFileSysInfo->pInodeBitmap, inode_no);
	syncFileSysInfo();
}

int parsePath(const char *path, int idx, char *parsed)
{
	char *path2;
	path2 = (char *)calloc(sizeof(char), strlen(path) + 1);
	strcpy(path2, path);

	if( strrchr(path2, '/') == strchr(path2, 0) -1 )
	{
		*(strrchr(path2, '/')) = 0;
	}

	char	name[NAME_LEN_MAX];
	int		i;
	int		pos;
	int		cnt;
	
	pos = 0;
	cnt = 0;

	do
	{
		i = 0;
		while( path[pos] != '/' && path2[pos] != 0 )
		{
			name[i++] = path2[pos++];
		}
		name[i] = 0;
		cnt++;

		if( idx == 0 )
		{
			strcpy(parsed, name);
		}
		idx--;
	} while( path2[pos++] > 0 );

	return cnt;
}

char * parseParentPath(const char *path, char *parsed)
{
	strcpy(parsed, path);

	if( strrchr(parsed, '/') == strchr(parsed, 0) - 1 )
	{
		*(strrchr(parsed, '/')) = 0;
	}

	*(strrchr(parsed, '/')) = 0;
	return parsed;
}

char * parseFileName(const char *path, char *parsed)
{
	memcpy(parsed, strrchr(path, '/') + 1, (size_t)(strrchr(path, 0) - strrchr(path, '/')));
	return parsed;
}

int getDirEntryAll(int inode_no, DirEntry *dir_entry)
{
	InodeInfo	inode;
	char		tmp_blk[BLOCK_SIZE];
	DirEntry	*de;
	int			blk_idx;
	int			cnt;
	int			dir_cnt;
	int			i;

	// get inode
	getInode(inode_no, &inode);

	// get out not directory inode
	if( inode.type == FILE_TYPE_FILE )
	{
		return -1;
	}

	// get entries according to its size
	cnt = 0;
	dir_cnt = inode.size / sizeof(DirEntry);
	blk_idx = 0;
	while( cnt < dir_cnt )
	{
		getData(inode.directPtr[blk_idx++], tmp_blk);
		de = (DirEntry *)tmp_blk;

		for( i=0; i<NUM_OF_DIRENT_PER_BLK; i++ )
		{
			// not empty dir entry
			if( de[i].inodeNum > 0 )
			{
				memcpy(&dir_entry[cnt], &de[i], sizeof(DirEntry));
				cnt++;
			}
		}
	}

	return cnt;
}

int isExists(const char *file_name)
{
	char name[NAME_LEN_MAX * 3];
	DirEntry dir_entry_arr[NUM_OF_DIRENT_PER_BLK * NUM_OF_DIRECT_BLK_PTR];
	int dir_cnt;
	int i;

	if( ! strcmp(file_name, "") || ! strcmp(file_name, "/") )
	{
		return pFileSysInfo->rootInodeNum;
	}

	parseParentPath(file_name, name);

	// root node
	if( ! strcmp(name, "") )
	{
		parseFileName(file_name, name);

		dir_cnt = getDirEntryAll(pFileSysInfo->rootInodeNum, dir_entry_arr);
		for( i=0; i<dir_cnt; i++ )
		{
			// find dir
			if( ! strcmp(dir_entry_arr[i].name, name) )
			{
				return dir_entry_arr[i].inodeNum;
			}
		}
		return -1;
	}
	else
	{
		int dir_inode_no;
		dir_inode_no = isExists(name);
		if( dir_inode_no < 0 )
		{
			return -1;
		}
		parseFileName(file_name, name);
		dir_cnt = getDirEntryAll(dir_inode_no, dir_entry_arr);
		if( dir_cnt < 0 )
		{
			return -1;
		}
		for( i=0; i<dir_cnt; i++ )
		{
			// find file
			if( ! strcmp(dir_entry_arr[i].name, name) )
			{
				return dir_entry_arr[i].inodeNum;
			}
		}
		return -1;
	}
}

int putDirEntry(int inode_no, DirEntry de)
{
	InodeInfo inode;
	DirEntry dir_entry_arr[NUM_OF_DIRENT_PER_BLK];
	// update parent inode
	getInode(inode_no, &inode);
	// find empty dir entry
	int i;
	for( i=0; inode.blocks; i++ )
	{
		getData(inode.directPtr[i], dir_entry_arr);
		int j;
		for( j=0; j<NUM_OF_DIRENT_PER_BLK; j++ )
		{
			if( dir_entry_arr[j].inodeNum == 0 )
			{
				dir_entry_arr[j] = de;
				updateData(inode.directPtr[i], dir_entry_arr);
				inode.size += sizeof(DirEntry);
				updateInode(inode_no, inode);
				return 0;
			}
		}
	}
	// no empty direct blk
	if( i == NUM_OF_DIRECT_BLK_PTR )
	{
		return -1;
	}
	// create new direct blk
	int data_no;
	memset(dir_entry_arr, 0, sizeof(DirEntry) * NUM_OF_DIRENT_PER_BLK);
	dir_entry_arr[0] = de;
	data_no = putData(dir_entry_arr);
	inode.size += sizeof(DirEntry);
	inode.blocks++;
	inode.directPtr[inode.blocks - 1] = data_no;

	updateInode(inode_no, inode);
	return 0;
}

int deleteDirEntry(int inode_no, const char *file_name)
{
	InodeInfo inode;
	DirEntry de[NUM_OF_DIRENT_PER_BLK];

	// get parent
	getInode(inode_no, &inode);

	// delete
	inode.size -= sizeof(DirEntry);
	int i;
	for( i=0; i<inode.blocks; i++ )
	{
		getData(inode.directPtr[i], de);
		int j;
		for( j=0; j<NUM_OF_DIRENT_PER_BLK; j++ )
		{
			if( ! strcmp(de[j].name, file_name) )
			{
				memset(de[j].name, 0, NAME_LEN_MAX);
				de[j].inodeNum = 0;
				de[j].type = 0;
				updateData(inode.directPtr[i], de);
				// need to release data... but not now
				updateInode(inode_no, inode);
				return 0;
			}
		}
	}
	// ? why you're here?
	return -1;
}

void		FileSysInit(void)
{
	BufInit();
	// allocate FileDescTable
	if( ! pFileDescTable )
	{
		pFileDescTable = (FileDescTable *)malloc(sizeof(FileDescTable));
		memset(pFileDescTable, 0, sizeof(FileDescTable));
	}
}

void		FileSysFinish(void) 
{
	// free FileDescTable
	if( pFileDescTable )
	{
		free(pFileDescTable);
	}
	BufFinish();
}

int		OpenFile(const char* szFileName, OpenFlag flag)
{
	/*
	create flag : create file if doesn't exist
	create inode
	get parent node 
	add file inode to praent node 
	add description
	size type mode blocks
	*/

	int inode_no;
	InodeInfo inode;
	int parent_inode_no;
	InodeInfo parent_inode;
	char parent_name[NAME_LEN_MAX * 3];
	char name[NAME_LEN_MAX];
	int i;
	int j;
	DirEntry de;

	if( flag == OPEN_FLAG_CREATE )
	{
		// file doesnt exists
		if( (inode_no = isExists(szFileName)) < 0 )
		{
			// create inode
			inode_no = putInode(0, FILE_TYPE_FILE, 0, 0);
			// file dir entry
			parseFileName(szFileName, name);
			strcpy(de.name, name);
			de.inodeNum = inode_no;
			de.type = FILE_TYPE_FILE;
			// get parent node
			parseParentPath(szFileName, parent_name);
			parent_inode_no = isExists(parent_name);
			if( putDirEntry(parent_inode_no, de) < 0 )
			{
				return -1;
			}
		}
		return addFileDesc(inode_no);
	}
	// flag read write
	else
	{
		if( (inode_no = isExists(szFileName)) < 0 )
		{
			return -1;
		}
		return addFileDesc(inode_no);
	}
}


int		WriteFile(int fileDesc, char* pBuffer, int length)
{
	/*
	is opened
	get inode
	remove all block
	realloc block
	length / block size
	update inoe
	return size;
	*/

	InodeInfo inode;
	int inode_no;
	int i;
	int j;
	int pos;
	char blk[BLOCK_SIZE];

	inode_no = pFileDescTable->file[fileDesc].inodeNo;
	if( ! inode_no > 0 )
	{
		return -1;
	}
	getInode(inode_no, &inode);

	for( i=0; i<inode.blocks; i++ )
	{
		deleteData(inode.directPtr[i]);
	}

	inode.blocks = length / BLOCK_SIZE;
	if( length % BLOCK_SIZE > 0 )
	{
		inode.blocks++;
	}
	pos = 0;
	for( i=0; i<inode.blocks; i++ )
	{
		memset(blk, 0, BLOCK_SIZE);
		for( j=0; j<BLOCK_SIZE; j++ )
		{
			blk[j] = pBuffer[pos++];
			if( pos == length )
			{
				break;
			}
		}
		inode.directPtr[i] = putData(blk);
	}

	inode.size = pos;

	updateInode(inode_no, inode);
	return length;
}

int		ReadFile(int fileDesc, char* pBuffer, int length)
{
	/*
	is opened
	get inode
	read length
	return length;
	*/

	InodeInfo inode;
	int inode_no;
	int i;
	int j;
	int pos;
	char blk[BLOCK_SIZE];

	inode_no = pFileDescTable->file[fileDesc].inodeNo;
	if( ! inode_no > 0 )
	{
		return -1;
	}
	getInode(inode_no, &inode);

	pos = 0;
	for( i=0; i<inode.blocks; i++ )
	{
		getData(inode.directPtr[i], blk);

		for( j=0; j<BLOCK_SIZE; j++ )
		{
			pBuffer[pos++] = blk[j];
			if( pos == length )
			{
				return pos;
			}
		}
	}

	return -1;
}


int		CloseFile(int fileDesc)
{
	removeFileDesc(fileDesc);
	return 0;
}

int		RemoveFile(const char* szFileName)
{
	/*
	file exists
	file opend
	get inode
	remove file
	remove from parent dir
	*/
	InodeInfo inode;
	int inode_no;
	char name[NAME_LEN_MAX * 3];
	int parent_inode_no;

	if( (inode_no = isExists(szFileName)) < 0 )
	{
		return -1;
	}

	if( findFileDesc(inode_no) >= 0 )
	{
		return -1;
	}

	// get inode
	getInode(inode_no, &inode);
	int i;
	for( i=0; i<inode.blocks; i++ )
	{
		deleteData(inode.directPtr[i]);
	}

	// delete inote
	deleteInode(inode_no);

	// get parent node
	parseParentPath(szFileName, name);
	parent_inode_no = isExists(name);
	// remove from parent dir entry
	parseFileName(szFileName, name);
	return deleteDirEntry(parent_inode_no, name);

}

int		MakeDir(const char* szDirName)
{
	char name[NAME_LEN_MAX];
	char path[NAME_LEN_MAX * 3];
	int parent_inode_no;
	InodeInfo parent_inode;
	int i;
	DirEntry dir_entry_arr[NUM_OF_DIRENT_PER_BLK];
	DirEntry dir_entry;

	// chekc already exists
	if( isExists(szDirName) > 0)
	{
		return -1;
	}

	// check its parent is exists
	parseParentPath(szDirName, path);
	parent_inode_no = isExists(path);
	if( parent_inode_no < 0 )
	{
		return -1;
	}

	// new inode
	int inode_no;
	inode_no = putInode(0, FILE_TYPE_DIR, 0, 0);
	// new dir entry
	parseFileName(szDirName, name);
	strcpy(dir_entry.name, name);
	dir_entry.inodeNum = inode_no;
	dir_entry.type = FILE_TYPE_DIR;

	return putDirEntry(parent_inode_no, dir_entry);

	// update parent inode
	getInode(parent_inode_no, &parent_inode);
	// find empty dir entry
	for( i=0; parent_inode.blocks; i++ )
	{
		getData(parent_inode.directPtr[i], dir_entry_arr);
		int j;
		for( j=0; j<NUM_OF_DIRENT_PER_BLK; j++ )
		{
			if( dir_entry_arr[j].inodeNum == 0 )
			{
				dir_entry_arr[j] = dir_entry;
				updateData(parent_inode.directPtr[i], dir_entry_arr);
				parent_inode.size += sizeof(DirEntry);
				updateInode(parent_inode_no, parent_inode);
				return 0;
			}
		}
	}
	// no empty direct blk
	if( i == NUM_OF_DIRECT_BLK_PTR )
	{
		return -1;
	}
	// create new direct blk
	int data_no;
	memset(dir_entry_arr, 0, sizeof(DirEntry) * NUM_OF_DIRENT_PER_BLK);
	dir_entry_arr[0] = dir_entry;
	data_no = putData(dir_entry_arr);
	parent_inode.size += sizeof(DirEntry);
	parent_inode.blocks++;
	parent_inode.directPtr[parent_inode.blocks - 1] = data_no;

	updateInode(parent_inode_no, parent_inode);
	return 0;
}


int		RemoveDir(const char* szDirName)
{
	/*
	root = false
	not empty = false
	get parent
	remove myself
	remove from parent
	*/

	int inode_no;
	InodeInfo inode;
	int parent_inode_no;
	InodeInfo parent_inode;
	DirEntry dir_entry_arr[NUM_OF_DIRECT_BLK_PTR * NUM_OF_DIRENT_PER_BLK];
	char path[NAME_LEN_MAX * 3];
	int i;
	int j;
	DirEntry de[NUM_OF_DIRENT_PER_BLK];
	char name[NAME_LEN_MAX];

	// root
	if( ! strcmp(szDirName, "") || ! strcmp(szDirName, "/") )
	{
		return -1;
	}

	// check exists
	if( (inode_no = isExists(szDirName)) < 0 )
	{
		return -1;
	}
	// check not empty
	if( getDirEntryAll(inode_no, dir_entry_arr) > 0 )
	{
		return -1;
	}

	// get parent
	parseParentPath(szDirName, path);
	parent_inode_no = isExists(path);
	getInode(parent_inode_no, &parent_inode);

	// delete myself
	deleteInode(inode_no);

	// parse name will be deleted
	parseFileName(szDirName, name);
	return deleteDirEntry(parent_inode_no, name);

	// delete from parent
	parent_inode.size -= sizeof(DirEntry);
	for( i=0; i<parent_inode.blocks; i++ )
	{
		getData(parent_inode.directPtr[i], de);
		for( j=0; j<NUM_OF_DIRENT_PER_BLK; j++ )
		{
			if( de[j].inodeNum == inode_no )
			{
				memset(de[j].name, 0, NAME_LEN_MAX);
				de[j].inodeNum = 0;
				de[j].type = 0;
				updateData(parent_inode.directPtr[i], de);
				// need to release data... but not now
				updateInode(parent_inode_no, parent_inode);
				return 0;
			}
		}
	}
	// ? why you're here?
	return -1;
}


void		EnumerateDirStatus(const char* szDirName, DirEntry* pDirEntry, int* pNum)
{
	InodeInfo	inode;
	int			i;
	char		name[NAME_LEN_MAX];
	int			dir_cnt;
	DirEntry	dir_entry_arr[NUM_OF_DIRECT_BLK_PTR * NUM_OF_DIRENT_PER_BLK];
	int			inode_no;

	if( (inode_no = isExists(szDirName)) < 0 )
	{
		*pNum = -1;
		return;
	}

	dir_cnt = getDirEntryAll(inode_no, dir_entry_arr);
	if( dir_cnt > *pNum )
	{
		dir_cnt = *pNum;
	}
	else
	{
		*pNum = dir_cnt;
	}
	for( i=0; i<dir_cnt; i++ )
	{
		pDirEntry[i] = dir_entry_arr[i];
	}
	return;

	/*
	for( i=0; i<parsePath(szDirName, i, name); i++ )
	{
		// root node
		if( ! strcmp(name, "") && i == 0 )
		{
			dir_cnt = getDirEntryAll(pFileSysInfo->rootInodeNum, dir_entry_arr);
		}
		// check is exist
		else
		{
			int j;
			for( j=0; j<dir_cnt; j++ )
			{
				// dir found
				if( dir_entry_arr[i].type == FILE_TYPE_DIR && ! strcmp(dir_entry_arr[j].name, name) )
				{
					dir_cnt = getDirEntryAll(dir_entry_arr[j].inodeNum, dir_entry_arr);
					j=-1;
					break;
				}
			}
			// dir not found
			if( j == dir_cnt )
			{
				*pNum = -1;
				return;
			}
		}
	}

	// copy to pDirEntry
	memset(pDirEntry, 0, sizeof(DirEntry) * (*pNum));
	int min_dir_cnt;
	if( dir_cnt < *pNum )
	{
		min_dir_cnt = dir_cnt;
	}
	else
	{
		min_dir_cnt = *pNum;
	}
	for( i=0; i<min_dir_cnt; i++ )
	{
		pDirEntry[i] = dir_entry_arr[i];
	}

	*pNum = min_dir_cnt;
	return;
	*/
}