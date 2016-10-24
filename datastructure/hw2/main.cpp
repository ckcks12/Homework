#include <iostream>
#include "DoublyLinkedList.cpp"

using namespace std;

int main()
{
    DoublyLinkedList<int> list;

    list.insert(1);
    list.insert(2);
    list.insert(2);
    list.insert(3);

    cout << list.at(1) << endl;
    cout << list.search(2) << endl;

}