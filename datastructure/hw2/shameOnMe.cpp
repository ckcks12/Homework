//
// Created by lec on 2016. 10. 26..
//

#include "DoublyLinkedList.cpp"

/*
 * the hell useless methods list
 */

template <typename T>
size_t list_length(const DoublyLinkedListNode<T>* head_ptr)
{
    const DoublyLinkedListNode<T>* node;
    size_t cnt = 0;

    if( head_ptr == NULL ) {
        return 0;
    }

    node = head_ptr;
    while( (node = node->next) != NULL )
    {
       cnt++;
    }

    return cnt;
}

template <typename T>
void list_head_insert(DoublyLinkedListNode<T>& head_ptr, const T& entry)
{
    DoublyLinkedListNode<T>* next_node;
    DoublyLinkedListNode<T>* node;

    node = new DoublyLinkedListNode<T>();
    node->data = entry;
    node->prev = &head_ptr;

    next_node = head_ptr.next;
    if( next_node == NULL )
        node->next = NULL;
    else
        node->next = next_node;
}

template <typename T>
void list_insert(DoublyLinkedListNode<T>* previous_ptr, const T& entry)
{
    DoublyLinkedListNode<T>* node;

    node = new DoublyLinkedListNode<T>();
    node->data = entry;
    node->prev = previous_ptr;
    node->next = NULL;

    previous_ptr->next = node;
}

template <typename T>
DoublyLinkedListNode<T>* list_search(DoublyLinkedListNode<T>* head_ptr, const T& target)
{
    DoublyLinkedListNode<T>* node;

    node = head_ptr;
    while( (node = node->next) != NULL )
    {
        if( node->data == target )
            return node;
    }

    return NULL;
}

template <typename T>
const DoublyLinkedListNode<T>* list_search(const DoublyLinkedListNode<T>* head_ptr, const T& target)
{
    const DoublyLinkedListNode<T>* node;

    node = head_ptr;
    while( (node = node->next) != NULL )
    {
        if( node->data == target )
            return node;
    }

    return NULL;
}

template <typename T>
DoublyLinkedListNode<T>* list_locate(DoublyLinkedListNode<T>* head_ptr, size_t position)
{
    DoublyLinkedListNode<T>* node;

    node = head_ptr;
    for( size_t i=0; i<=position; i++ )
    {
        node = node->next;
        if( node == NULL )
            return NULL;
    }

    return node;
}

template<typename T>
const DoublyLinkedListNode<T> *list_locate(DoublyLinkedListNode<T> *head_ptr, size_t position)
{
    const DoublyLinkedListNode<T>* node;

    node = head_ptr;
    for( size_t i=0; i<=position; i++ )
    {
        node = node->next;
        if( node == NULL )
            return NULL;
    }

    return node;
}

template<typename T>
void list_head_remove(DoublyLinkedListNode<T>*& head_ptr)
{
    DoublyLinkedListNode<T>* node;
    DoublyLinkedListNode<T>* next_node;

    node = head_ptr->next;
    if( node == NULL )
        return;

    next_node = node->next;

    head_ptr->next = next_node;
    delete node;
}

template<typename T>
void list_remove(DoublyLinkedListNode<T>*& previous_ptr)
{
    DoublyLinkedListNode<T>* node;
    DoublyLinkedListNode<T>* next_node;

    node = previous_ptr->next;
    if( node == NULL )
        return;

    next_node = node->next;

    previous_ptr->next = next_node;
    delete node;

}

template <typename T>
void list_clear(DoublyLinkedListNode<T>*& head_ptr)
{
    DoublyLinkedListNode<T>* node;

    while( list_length(head_ptr) > 0 )
        list_remove(head_ptr);
}