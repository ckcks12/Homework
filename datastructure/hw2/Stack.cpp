//
// Created by lec on 2016. 10. 24..
//

#include <iostream>
#include "DoublyLinkedList.cpp"

using namespace std;

template <typename T>
class Stack
{
public:
    DoublyLinkedList<T> list;

    Stack()
    {

    }

    ~Stack()
    {

    }

    bool isEmpty()
    {
        return list.size == 0;
    }

    size_t count()
    {
        return list.size;
    }

    void printTrace()
    {
        cout << "========================" << endl;
        if( isEmpty() )
        {
            cout << "empty" << endl << endl;
            return;
        }

        DoublyLinkedListNode<T>* node;
        for( size_t i = list.size; i > 0; i-- )
        {
            node = list.at(i - 1);
            cout << node << "(" << node->data << ")" << endl;
        }
        cout << endl;
    }

    void push(T data)
    {
        list.insert(data);
    }

    T pop()
    {
        if( isEmpty() )
        {
            cerr << "pop() : empty stack" << endl;
            return 0; // failed to pop
        }

        T data = list.at(list.size - 1)->data;
        list.remove(list.size - 1);
        return data;
    }

    T peek()
    {
        if( isEmpty() )
        {
            cerr << "peak() : empty stack" << endl;
            return 0; // failed to peek
        }

        T data = list.at(list.size - 1)->data;
        return data;
    }
};