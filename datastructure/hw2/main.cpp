#include <iostream>
#include "Stack.cpp"
#include <string>

using namespace std;

int main()
{
    /**
     * 1. transform the infix to the postfix
     * 2. evaluate the postfix
     */

    Stack<string> postfix_stack;
    Stack<string> eval_stack;
    string infix_exp;
    string postfix_exp;

    cout << "input infix expression" << endl;
    cout << ">>> ";
    cin >> infix_exp;

    // validation
    if( infix_exp.length() == 0 )
    {
        cout << "wrong infix expression" << endl;
        return -1;
    }

    // transformation
    for( size_t i = 0; i < infix_exp.length(); i++ )
    {
        char& tkn = infix_exp.at(i);
    }
}