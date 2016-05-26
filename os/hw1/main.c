#include <stdio.h>

#include <stdlib.h>

#include "hw1.h"



#define NUM_OBJECTS  50



#ifndef false

#define false 0

#endif



#ifndef true

#define true !(false)

#endif



#ifndef bool

#define bool int

#endif



extern void validate_tc1_1();

extern void validate_tc1_2();

extern void validate_tc2_1();

extern void validate_tc2_2();

extern void validate_tc3_1();

extern void validate_tc3_2();

extern void validate_tc4_1();

extern void validate_tc4_2();



char log_msg[256];



int testcase1()

{

    int      i;

    Object*  pObj;



    // 오브젝트 생성 후 프리리스트에 삽입

    pObj = NULL;

    for( i = 0; i < NUM_OBJECTS; i++ ){

		pObj = (Object*)malloc( sizeof(Object) );

		InsertObjectIntoObjFreeList( pObj );

    }



    // 프리리스트에서 오브젝트를 꺼낸 후 오브젝트 번호를 붙여서 리스트1에 삽입

    pObj = NULL;

    for( i = 0; i < NUM_OBJECTS; i++ ){

		pObj = GetObjectFromObjFreeList();

		InsertObjectToTail( pObj, i, OBJ_LIST0 );

    }



	validate_tc1_1();

	printf("validating tc1-1 : %s", log_msg);



	// 리스트1의 오브젝트를 하나씩 빼낸 후 리스트2에 삽입

	for( i = 0; i < NUM_OBJECTS; i++ ){

		pObj = GetObjectByNum( i );

		DeleteObject( pObj );

		InsertObjectToTail( pObj, i, OBJ_LIST1 );

    }



	validate_tc1_2();

	printf("validating tc1-2 : %s", log_msg);





	// 리스트 오브젝트를 모두 삭제한 후 프리리스트에 다시 삽입

    for( i = 0; i < NUM_OBJECTS; i++ ){

		pObj = GetObjectByNum( i );

		DeleteObject( pObj );

		InsertObjectIntoObjFreeList( pObj );

    }



    return 1;

}



int testcase2()

{

    int      i;

    Object*  pObj;



    // 프리리스트에서 오브젝트를 꺼낸 후 오브젝트 번호를 붙여서 리스트1에 삽입

    pObj = NULL;

    for( i = 0; i < NUM_OBJECTS; i++ ){

		pObj         = GetObjectFromObjFreeList();

		InsertObjectToTail( pObj, i, OBJ_LIST0 );

    }



	// 리스트1의 오브젝트 중 절반을 리스트2에 삽입

	for( i = 0; i < NUM_OBJECTS; i+=2 ){

		pObj = GetObjectByNum( i );

		DeleteObject( pObj );

		InsertObjectToTail( pObj, i, OBJ_LIST1 );

    }



	validate_tc2_1();

	printf("validating tc2-1 : %s", log_msg);





	// 리스트2의 오브젝트 중 다시 절반을 리스트1에 삽입

	for( i = 0; i < NUM_OBJECTS; i+=4 ){

		pObj = GetObjectByNum( i );

		DeleteObject( pObj );

		InsertObjectToTail( pObj, i, OBJ_LIST0 );

    }



	validate_tc2_2();

	printf("validating tc2-2 : %s", log_msg);



	// 리스트 오브젝트를 모두 삭제한 후 프리리스트에 다시 삽입

    for( i = 0; i < NUM_OBJECTS; i++ ){

		pObj = GetObjectByNum( i );

		DeleteObject( pObj );

		InsertObjectIntoObjFreeList( pObj );

    }



    return 1;

}



int testcase3()

{

    int      i;

    Object*  pObj;



    // 프리리스트에서 오브젝트를 꺼낸 후 오브젝트 번호를 붙여서 리스트1에 삽입

    pObj = NULL;

    for( i = 0; i < NUM_OBJECTS; i++ ){

		pObj         = GetObjectFromObjFreeList();

		InsertObjectToTail( pObj, i, OBJ_LIST0 );

    }



	// 리스트1의 오브젝트 중 절반을 오브젝트 번호를 변경하여 리스트2에 삽입

	for( i = 0; i < NUM_OBJECTS/2; i++ ){

		pObj = GetObjectByNum( i );

		DeleteObject( pObj );



		pObj->objnum = i + NUM_OBJECTS;

		InsertObjectToTail( pObj, i + NUM_OBJECTS, OBJ_LIST1 );

    }



	validate_tc3_1();

	printf("validating tc3-1 : %s", log_msg);





	// 리스트1의 오브젝트 중 나머지 절반을 오브젝트 번호를 변경하여 리스트1에 삽입

	for( i = NUM_OBJECTS/2; i < NUM_OBJECTS; i++ ){

		pObj = GetObjectByNum( i );

		DeleteObject( pObj );

		InsertObjectToTail( pObj, i + NUM_OBJECTS, OBJ_LIST0 );

    }



	validate_tc3_2();

	printf("validating tc3-2: %s", log_msg);





	// 리스트 오브젝트를 모두 삭제한 후 프리리스트에 다시 삽입

    for( i = NUM_OBJECTS; i < NUM_OBJECTS*2; i++ ){

		pObj = GetObjectByNum( i );

		DeleteObject( pObj );

		InsertObjectIntoObjFreeList( pObj );

    }



    return 1;

}





/* combine multiple APIs including InsertObjectToHead */



int testcase4()

{

	int      i;

    Object*  pObj;



    pObj = NULL;



    for( i = 0 ; i < NUM_OBJECTS/2 ; i++ )

    	InsertObjectToHead(GetObjectFromObjFreeList(), i, OBJ_LIST0);



    for( i = NUM_OBJECTS/2 ; i < NUM_OBJECTS ; i++ )

    	InsertObjectToTail(GetObjectFromObjFreeList(), i, OBJ_LIST1);



	validate_tc4_1();



    for ( i = NUM_OBJECTS/4 ; i < NUM_OBJECTS/4 + NUM_OBJECTS/2 ; i++ )

    {// 12 ~ 36 삭제

    	pObj = GetObjectByNum( i );

    	DeleteObject( pObj );

    	InsertObjectIntoObjFreeList( pObj );

    }

	validate_tc4_2();



    return 1;

}



int main()

{

    Init();



	if ( testcase1() == 1 )

		printf("\n testcase 1 complete. \n\n");

	else

		return -1;



	if ( testcase2() == 1 )

		printf("\n testcase 2 complete. \n\n");

	else

		return -1;



	if ( testcase3() == 1 )

		printf("\n testcase 3 complete. \n\n");

	else

		return -1;



	if ( testcase4() == 1 )

		printf("\n testcase 4 complete. \n\n");

	else

		return -1;



    return 0;

}
