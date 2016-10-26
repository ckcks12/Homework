#include <iostream>
#include "Stack.cpp"
#include <string>

using namespace std;

int getType(char c)
{
    switch(c)
    {
        case '*':
        case '/':
            return 3;
        case '+':
        case '-':
            return 2;
        case '(':
        case ')':
            return 1;
        case '.':
        default:
            return 0;
    }
}

int main()
{
    /**
     * 1. transform the infix to the postfix
     * 2. evaluate the postfix
     */

    Stack<string> postfix_stack;
    Stack<string> eval_stack;
    Stack<string> tmp_stack;
    string infix_exp;
    string postfix_exp;

    cout << "input infix expression" << endl;
    cout << ">>> ";
    getline(cin, infix_exp);

    // validation
    if( infix_exp.length() == 0 )
    {
        cout << "wrong infix expression" << endl;
        return -1;
    }

    // remove white space
    infix_exp.erase(remove_if(infix_exp.begin(), infix_exp.end(), ::isspace), infix_exp.end());

    // transform
    for( size_t i = 0; i < infix_exp.length(); i++ )
    {
        char tkn = infix_exp.at(i);
        int type = getType(tkn);

        // numeric, variable, dot
        if( type == 0 )
        {
            string tmp = "";
            while( i < infix_exp.length() && getType(infix_exp.at(i)) == 0 )
                tmp += infix_exp.at(i++);

            // variable
            //if( ! isdigit(tmp.at(0)) )
            if( isalpha(tmp.at(0)) )
            {
                cout << "input variable value - " << tmp << " : ";
                cin >> tmp;
            }

            tmp_stack.push(tmp);
            postfix_exp += tmp;
            postfix_exp += " "; // beautify
            i--; // for's 3th statement will increase it
        }
        // parenthesis
        else if( type == 1 )
        {
            if( tkn == '(' )
            {
                postfix_stack.push(string(1, tkn));
            }
            else if( tkn == ')' )
            {
                while( ! postfix_stack.isEmpty() && postfix_stack.peek().at(0) != '(' )
                {
                    tmp_stack.push(postfix_stack.peek());
                    postfix_exp += postfix_stack.pop();
                    postfix_exp += " "; // beautify
                }
                if( postfix_stack.peek().at(0) == '(' )
                    postfix_stack.pop(); // useless left-parenthesis
            }
        }
        // operator
        else if( type == 2 || type == 3 )
        {
            while( ! postfix_stack.isEmpty() && getType(postfix_stack.peek().at(0)) >= type )
            {
                tmp_stack.push(postfix_stack.peek());
                postfix_exp += postfix_stack.pop();
                postfix_exp += " "; // beautify
            }
            postfix_stack.push(string(1, tkn));
        }
    }
    // remained operator
    while( ! postfix_stack.isEmpty() )
    {
        tmp_stack.push(postfix_stack.peek());
        postfix_exp += postfix_stack.pop();
    }

    cout << "postfix expression : " << postfix_exp << endl;

    // stack reverse
    while( ! tmp_stack.isEmpty() )
    {
        postfix_stack.push(tmp_stack.pop());
    }

    // calculate
    while( ! postfix_stack.isEmpty() )
    {
        string tkn = postfix_stack.pop();
        int type = getType(tkn.at(0));

        // operator
        if( type > 0 )
        {
            double operand2 = stod(eval_stack.pop());
            double operand1 = stod(eval_stack.pop());
            double rslt = 0.0;
            char op = tkn.at(0);

            if( op == '+' )
                rslt = operand1 + operand2;
            else if( op == '-' )
                rslt = operand1 - operand2;
            else if( op == '*' )
                rslt = operand1 * operand2;
            else if( op == '/' )
                rslt = operand1 / operand2;

            eval_stack.push(to_string(rslt));
        }
        // operand
        else
        {
            eval_stack.push(tkn);
        }
    }

    // verify
    if( eval_stack.isEmpty() )
    {
        cerr << "eval_stack is empty. error occured while calculating" << endl;
        return -1;
    }

    cout << "evaluated successfully." << endl;
    cout << "the answer is " << eval_stack.pop() << endl;
}