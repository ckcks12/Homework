#include <stdio.h>
#include "hw1.h"

/**
insert an object into either tail of Hash Table and ObjList0, 1
**/
void InsertObjectToTail(Object* pObj, int objNum, ObjList listNum)
{
	Object			**obj_list_head = &ppObjListHead[listNum];
	Object			**obj_list_tail = &ppObjListTail[listNum];
	Object			*prev_obj;
	int			hash_tbl_idx;
	Object			**hash_list_head;
	Object			**hash_list_tail;

	pObj->objnum = objNum;

	//insert to ObjList
	//list is empty
	if( *obj_list_head == NULL )
	{
		pObj->poPrev = NULL;
		pObj->poNext = NULL;
		
		*obj_list_head = pObj;
		*obj_list_tail = pObj;
	}
	else
	{
		prev_obj = *obj_list_tail;
		prev_obj->poNext = pObj;
		pObj->poPrev = prev_obj;
		pObj->poNext = NULL;

		*obj_list_tail = pObj;
	}

	//insert to Hash Table
	hash_tbl_idx = objNum % HASH_TBL_SIZE;
	hash_list_head = &ppHashHead[hash_tbl_idx];
	hash_list_tail = &ppHashTail[hash_tbl_idx];
	
	//hash list is empty
	if( *hash_list_head == NULL )
	{
		pObj->phPrev = NULL;
		pObj->phNext = NULL;
		
		*hash_list_head = pObj;
		*hash_list_tail = pObj;
	}
	else
	{
		prev_obj = *hash_list_tail;
		prev_obj->phNext = pObj;
		pObj->phPrev = prev_obj;
		pObj->phNext = NULL;

		*hash_list_tail = pObj;
	}
}

/**
insert an object into either head of Hash Table and ObjList0, 1
**/
void	InsertObjectToHead(Object* pObj, int objNum, ObjList listNum)
{
	Object			**obj_list_head = &ppObjListHead[listNum];
	Object			**obj_list_tail = &ppObjListTail[listNum];
	Object			*prev_obj;
	int			hash_tbl_idx;
	Object			**hash_list_head;
	Object			**hash_list_tail;

	pObj->objnum = objNum;
	
	//insert into ObjList
	//list is empty
	if( *obj_list_head == NULL )
	{
		pObj->poPrev = NULL;
		pObj->poNext = NULL;

		*obj_list_head = pObj;
		*obj_list_tail = pObj;
	}
	else
	{
		prev_obj = *obj_list_tail;
		prev_obj->poNext = pObj;
		pObj->poPrev = prev_obj;
		pObj->poNext = NULL;

		*obj_list_tail = pObj;
	}
	
	//insert into Hash Table
	hash_tbl_idx = objNum % HASH_TBL_SIZE;
	hash_list_head = &ppHashHead[hash_tbl_idx];
	hash_list_tail = &ppHashTail[hash_tbl_idx];

	//hash list is empty
	if( *hash_list_head == NULL )
	{
		pObj->phPrev = NULL;
		pObj->phNext = NULL;

		*hash_list_head = pObj;
		*hash_list_tail = pObj;
	}
	else
	{
		prev_obj = *hash_list_head;
		prev_obj->phPrev = pObj;
		pObj->phPrev = NULL;
		pObj->phNext = prev_obj;

		*hash_list_head = pObj;
	}
}

/**
get the object which has objnum from Hash Table
**/
Object* GetObjectByNum(int objnum)
{
	int			hash_tbl_idx;
	Object			**hash_list_head;
	Object			*rtn_obj;
	Object			*tmp_obj;

	hash_tbl_idx = objnum % HASH_TBL_SIZE;
	hash_list_head = &ppHashHead[hash_tbl_idx];

	//if empty
	if( *hash_list_head == NULL )
	{
		rtn_obj = NULL;
	}
	else
	{
		hash_list_head = &ppHashHead[hash_tbl_idx];
		tmp_obj = *hash_list_head;		

		while( tmp_obj->objnum != objnum && tmp_obj != NULL )
		{
			tmp_obj = tmp_obj->phNext;
		}

		rtn_obj = tmp_obj;
	}
	
	return rtn_obj;
}

/**
remove the object from either Hash Table and ObjList0, 1
**/ 
void DeleteObject(Object* pObj)
{
	Object			**obj_list_head;
	Object			**obj_list_tail;
	ObjList			obj_list0_idx = OBJ_LIST0;
	ObjList			obj_list1_idx = OBJ_LIST1;
	Object			**hash_list_head;
	Object			**hash_list_tail;
	int			hash_tbl_idx;
	Object			*tmp_obj;

//	printf("DeleteObject() : pObj->poPrev = %p\tpObj->poNext = %p\tpObj->objnum = %d\n", pObj->poPrev, pObj->poNext, pObj->objnum);

	//find out which ObjList has the object
	tmp_obj = pObj;
	while( tmp_obj->poPrev != NULL )
	{
		tmp_obj = tmp_obj->poPrev;
	}

	if( tmp_obj == ppObjListHead[obj_list0_idx] )
	{
		obj_list_head = &ppObjListHead[obj_list0_idx];
		obj_list_tail = &ppObjListTail[obj_list0_idx];
	}
	else if( tmp_obj == ppObjListHead[obj_list1_idx] )
	{
		obj_list_head = &ppObjListHead[obj_list1_idx];
		obj_list_tail = &ppObjListTail[obj_list1_idx];
	}

	//remove it from ObjList
	//if this object is only one of its ObjList
	if( *obj_list_head == *obj_list_tail )
	{
//		printf("DeleteObject() : if ObjList only one\n");
		*obj_list_head = NULL;
		*obj_list_tail = NULL;
	}
	//if first one
	else if( *obj_list_head == pObj )
	{
//		printf("DeleteObject() : if ObjList first one\n");
		*obj_list_head = pObj->poNext;
		(*obj_list_head)->poPrev = NULL;
		pObj->poNext = NULL;
	}
	//if last one
	else if( *obj_list_tail == pObj )
	{
//		printf("DeleteObject() : if ObjList last one\n");
		*obj_list_tail = pObj->poPrev;
		(*obj_list_tail)->poNext = NULL;
		pObj->poPrev = NULL;
	}
	else
	{
//		printf("DeleteObject() : if ObjList middle one\n");
		pObj->poPrev->poNext = pObj->poNext;
		pObj->poNext->poPrev = pObj->poPrev;

		pObj->poPrev = NULL;
		pObj->poNext = NULL;
	}

	//remove it from Hash Table
	hash_tbl_idx = pObj->objnum % HASH_TBL_SIZE;
	hash_list_head = &ppHashHead[hash_tbl_idx];
	hash_list_tail = &ppHashTail[hash_tbl_idx];

	//if only one
	if( *hash_list_head == *hash_list_tail )
	{
//		printf("DelegeObject() : if Hash List only one\n");
		*hash_list_head = NULL;
		*hash_list_tail = NULL;
	}
	//if first one
	else if( *hash_list_head == pObj )
	{
//		printf("DeleteObject() : if hash list first one\n");
		*hash_list_head = pObj->phNext;
		(*hash_list_head)->phPrev = NULL;
		pObj->phNext = NULL;
	}
	//if last one
	else if( *hash_list_tail == pObj )
	{
//		printf("DelebeObject() : if hash list last one\n");
		*hash_list_tail = pObj->phPrev;
		(*hash_list_tail)->phNext = NULL;
		pObj->phPrev = NULL;
	}
	else
	{
//		printf("DeleteObject() : if hash list middle one\n");
		pObj->phPrev->phNext = pObj->phNext;
		pObj->phNext->phPrev = pObj->phPrev;

		pObj->phPrev = NULL;
		pObj->phNext = NULL;
	}
}

/**
pop the last object of ObjFreeList
@return	Object *	pointer to the object on success
			NULL when either failed or ObjFreeList is empty
**/
Object* GetObjectFromObjFreeList(void)
{
	ObjList			obj_list_idx = OBJ_FREELIST;
	Object			**queue_head = &ppObjListHead[obj_list_idx];
	Object			**queue_tail = &ppObjListTail[obj_list_idx];
	Object			*prev_obj;
	Object			*rtn_obj;

	//is empty
	if( *queue_head == NULL )
	{
		rtn_obj = NULL;
	}
	else
	{
		rtn_obj = *queue_tail;	
		
		//queue has only one object
		if( rtn_obj->poPrev == NULL )
		{
			*queue_head = NULL;
			*queue_tail = NULL;
		}
		//queue has more than one object
		else
		{
			prev_obj = rtn_obj->poPrev;
			prev_obj->poNext = NULL;
			
			*queue_tail = prev_obj;
		}

		rtn_obj->poPrev = NULL;
		rtn_obj->poNext = NULL;
		rtn_obj->objnum = OBJ_INVALID;
	}

	return rtn_obj;
}


/**
insert an object into ObjFreeList
@param	Object *	pointer to the object will be inserted
**/
void InsertObjectIntoObjFreeList(Object* pObj)
{
	ObjList			obj_list_idx = OBJ_FREELIST;
	Object			**queue_head = &ppObjListHead[obj_list_idx];
	Object			**queue_tail = &ppObjListTail[obj_list_idx];
	Object			*prev_obj;

	//if queue is empty
	if( *queue_head == NULL )
	{
		*queue_head = pObj;
		*queue_tail = pObj;
	}
	else
	{
		prev_obj = *queue_head;
		prev_obj->poPrev = pObj;
		pObj->poPrev = NULL;
		pObj->poNext = prev_obj;
		
		*queue_head = pObj;
	}
}

/**
gcc alwasys init all global variable.
**/
void Init(void)
{
	;
}

