#include <iostream>
#include "DoublyLinkedList.cpp"

using namespace std;

int main()
{
    DoublyLinkedList<int> list;

    list.printListTrace();
    list.insert(1);
    list.remove(0);
    list.printListTrace();
    list.remove(0);
    list.printListTrace();
    list.remove(0);
    list.printListTrace();
    cout << "hi" << endl;
}