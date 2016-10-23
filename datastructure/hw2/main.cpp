#include <iostream>
#include "DoublyLinkedList.cpp"

using namespace std;

int main()
{
    DoublyLinkedList<int> list;

    list.printListTrace();
    list.insert(1);
    list.printListTrace();
    list.insert(3);
    list.printListTrace();
    list.insert(1, 2);
    list.printListTrace();
    list.remove(3);
    list.printListTrace();
}