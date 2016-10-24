//
// Created by lec on 2016. 10. 24..
//

#include <iostream>

using namespace std;

template <typename T>
class DoublyLinkedListNode
{
public:
    T data;
    DoublyLinkedListNode* prev;
    DoublyLinkedListNode* next;
};

template <typename T>
class DoublyLinkedList
{
public:
    DoublyLinkedListNode<T>* header;
    size_t size;

    DoublyLinkedList()
    {
        header = NULL;
        size = 0;
    }

    ~DoublyLinkedList()
    {
        if( isEmpty() )
            return;

        DoublyLinkedListNode<T>* node = header;
        DoublyLinkedListNode<T>* next;
        do
        {
            next = node->next;
            delete node;
            node = next;
        } while( node != NULL );
    }

    bool isEmpty()
    {
        return size == 0;
    }

    void printListTrace()
    {
        cout << "=========================" << endl;
        if( isEmpty() )
        {
            cout << "empty" << endl << endl;
            return;
        }

        DoublyLinkedListNode<T>* node = header;
        for( size_t i = 0; i < size; i++ )
        {
            cout << node << "(" << node->data << ") <-> ";
            node = node->next;
        }

        cout << "NULL" << endl << endl;
    }

    DoublyLinkedListNode<T>* at(size_t idx)
    {
        if( isEmpty() || idx >= size )
            return NULL;

        DoublyLinkedListNode<T>* node = header;
        for( size_t i = 0; i < idx; i++ )
        {
            node = node->next;
        }

        return node;
    }

    void create(T data)
    {
        if( ! isEmpty() )
        {
            insert(data);
            return;
        }

        DoublyLinkedListNode<T>* node;
        node = new DoublyLinkedListNode<T>();
        node->data = data;
        node->prev = NULL;
        node->next = NULL;
        header = node;
        size++;
    }

    void insert(size_t idx, T data)
    {
        if( idx > size )
        {
            //cout << "error occurred while insert at " << idx << " : size is " << size << endl;
            return;
        }

        if( isEmpty() )
        {
            create(data);
            return;
        }

        DoublyLinkedListNode<T>* node;
        DoublyLinkedListNode<T>* out_node;
        DoublyLinkedListNode<T>* prev;
        DoublyLinkedListNode<T>* next;
        node = new DoublyLinkedListNode<T>();
        node->data = data;

        prev = at(idx - 1);
        next = at(idx);
        node->prev = prev;
        node->next = next;

        if( prev != NULL )
            prev->next = node;
        if( next != NULL )
            next->prev = node;

        if( idx == 0 )
            header = node;

        size++;
    }

    void insert(T data)
    {
        insert(size, data);
    }

    void remove(size_t idx)
    {
        if( isEmpty() )
            return;

        DoublyLinkedListNode<T>* prev;
        DoublyLinkedListNode<T>* next;
        DoublyLinkedListNode<T>* node;
        node = at(idx);
        if( node == NULL )
            return;

        prev = node->prev;
        next = node->next;

        if( prev != NULL && next != NULL )
        {
            prev->next = next;
            next->prev = prev;
        }
        else if( ! (prev == NULL && next == NULL) )
        {
            if( prev == NULL )
                next->prev = NULL;
            if( next == NULL )
                prev->next = NULL;
        }

        if( idx == 0 )
            header = next;


        delete node;
        size--;
    }

    DoublyLinkedListNode<T>* search(T data)
    {
        if( isEmpty() )
            return NULL;

        DoublyLinkedListNode<T>* node = header;
        for( size_t i = 0; i < size; i++ )
        {
            if( node->data == data )
                return node;
            node = node->next;
        }

        return NULL;
    }

};