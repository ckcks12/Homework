#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* NodeDataType;
typedef int (*dll_SearchPredict)(NodeDataType, NodeDataType);

typedef struct _Node
{
    struct _Node* prev;
    struct _Node* next;
    NodeDataType data;
} Node;

typedef struct _HeadNode
{
    size_t size;
    struct _Node* node;
} HeadNode;

void dll_init(HeadNode** hn)
{
    *hn = (HeadNode*)malloc(sizeof(HeadNode));
    (*hn)->size = 0;
    (*hn)->node = NULL;
}

Node* dll_at(HeadNode* hn, size_t idx)
{
    if( hn == NULL )
	return NULL;

    // out of bound
    if( idx >= hn->size )
	return NULL;

    Node* n = hn->node;
    if( n == NULL )
	return NULL;

    size_t i;
    for( i=0; i<idx; i++ )
    {
	n = n->next;
	if( n == NULL )
	    return NULL;
    }

    return n;
}

int dll_index(HeadNode* hn, Node** target)
{
    size_t i;
    Node* n;
    for( i=0; i<hn->size; i++ )
    {
	if( *target == dll_at(hn, i) )
	    return i;
    }
    return -1;
}

int equalPredict(NodeDataType d1, NodeDataType d2)
{
    if( strcmp(d1, d2) == 0 )
	return 1;
    else
	return 0;
}

Node* dll_searchPredict(HeadNode* hn, NodeDataType data, dll_SearchPredict predict)
{
    if( hn == NULL )
	return NULL;

    Node* n = hn->node;
    if( n == NULL )
	return NULL;

    while( n != NULL )
    {
	if( predict(n->data, data) )
	    return n;
	n = n->next;
    }

    return NULL;
}

Node* dll_search(HeadNode* hn, NodeDataType data)
{
    return dll_searchPredict(hn, data, &equalPredict);
}    

void dll_insert(HeadNode* hn, size_t idx, NodeDataType data)
{
    Node* nn = (Node*)malloc(sizeof(Node));
    nn->data = strdup(data);

    // insert to head
    if( idx == 0 )
    {
	if( hn->node == NULL )
	{
	    nn->prev = NULL;
	    nn->next = NULL;
	    hn->node = nn;
	}
	else
	{
	    nn->prev = NULL;
	    nn->next = hn->node;
	    hn->node->prev = nn;
	    hn->node = nn;
	}
	
	hn->size++;
	return;
    }
    // insert to tail
    else if( idx == hn->size )
    {
	Node* tail = dll_at(hn, hn->size - 1);
	nn->prev = tail;
	nn->next = NULL;
	tail->next = nn;

	hn->size++;
	return;
    }

    Node* n = dll_at(hn, idx);
    if( n == NULL )
    {
	free(nn);
	return;
    }

    nn->prev = n->prev;
    nn->next = n;
    n->prev->next = nn;
    n->prev = nn;
    
    hn->size++;
    return;    
}

void dll_remove(HeadNode* hn, size_t idx)
{
    Node* n = dll_at(hn, idx);
    if( n == NULL )
	return;

    if( idx == 0 )
	hn->node = n->next;

    if( n->prev != NULL )
        n->prev->next = n->next;
    if( n->next != NULL )
        n->next->prev = n->prev;

    free(n->data);
    free(n);
    hn->size--;
    return;
}

void dll_removeAll(HeadNode* hn)
{
    while( hn->size > 0 )
    {
	dll_remove(hn, 0);
    }
}

void dll_close(HeadNode** hn)
{
    dll_removeAll(*hn);
    free(*hn);
    return;
}

void dll_printList(HeadNode* hn)
{
    size_t i;
    Node* n;

    printf("==========count:%zu=============\n", hn->size);

    for( i=0; i<hn->size; i++ )
    {
	n = dll_at(hn, i);
	printf("[%zu]%p(%s)-->", i, n, n->data);
    }

    printf("\n\n");
}

int main()
{
    HeadNode* hn;

    dll_init(&hn);

    dll_printList(hn);
    dll_insert(hn, 0, "0");
    dll_printList(hn);
    dll_insert(hn, 0, "-1");
    dll_printList(hn);
    dll_insert(hn, 1, "a");
    dll_printList(hn);
    dll_insert(hn, 2, "c");
    dll_printList(hn);
    dll_insert(hn, 2, "b");
    dll_printList(hn);
    dll_remove(hn, 0);
    dll_printList(hn);
    printf("find b's next : %s\n", dll_search(hn, "b")->next->data);
    dll_remove(hn, 3);
    dll_printList(hn);
    dll_removeAll(hn);
    dll_printList(hn);

    dll_close(&hn);
}
