#ifndef __HW1_H__

#define __HW1_H__


#define HASH_TBL_SIZE    (8)
#define MAX_OBJLIST_NUM  (3)
#define OBJ_INVALID  (-1)


typedef struct Object Object;

typedef enum {   
	FALSE = 0,
	TRUE = 1
} BOOL;


typedef enum __ObjList
{
    OBJ_LIST0 = 0,
    OBJ_LIST1 = 1,
    OBJ_FREELIST = 2
} ObjList;

struct Object
{
    int			objnum;
    Object*		phPrev;	/* the previous pointer in hash linked list */
    Object*		phNext; /* the next pointer in hash linked list */
    Object*		poPrev; /* the previous pointer in object linked list */
    Object*		poNext; /* the next pointer in object linked list */
};

Object*  ppHashHead[HASH_TBL_SIZE];
Object*  ppHashTail[HASH_TBL_SIZE];

Object*  ppObjListHead[MAX_OBJLIST_NUM];
Object*  ppObjListTail[MAX_OBJLIST_NUM];



extern void		Init(void);
extern void		InsertObjectToTail(Object* pObj, int objNum, ObjList listNum);
extern void		InsertObjectToHead(Object* pObj, int objNum, ObjList listNum);
extern Object*		GetObjectByNum(int objnum);
extern void 		DeleteObject(Object* pObj);
extern Object*		GetObjectFromObjFreeList(void);
extern void		InsertObjectIntoObjFreeList(Object* pObj);


#endif /* __HW1_H__ */
