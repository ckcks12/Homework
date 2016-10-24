#include <iostream>
#include "Stack.cpp"

using namespace std;

int main()
{
    Stack<int> stack;

    stack.printTrace();
    stack.push(1);
    stack.push(2);
    stack.printTrace();
    stack.push(3);
    stack.printTrace();
    cout << "pop() : " << stack.pop() << endl;
    stack.printTrace();
    stack.pop();stack.pop();
    stack.printTrace();

}