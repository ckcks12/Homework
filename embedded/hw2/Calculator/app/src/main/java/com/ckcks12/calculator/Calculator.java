package com.ckcks12.calculator;

import android.util.Log;

import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

/**
 * Created by lec on 2016. 9. 21..
 */
public class Calculator
{
    public String calculate(String exp)
    {
        Queue<String> postfix = convertToPostfixQueue(exp);

        for(int i=0; i<postfix.size(); i++ )
        {
            Log.d("eunchan", "[" + i + "]\t" + postfix.toArray()[i].toString());
        }

        return calculatePostfixQueue(postfix);

    }

    private int getType(char c)
    {
        switch( c )
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

    private Queue<String> convertToPostfixQueue(String exp)
    {
        Stack<Character> stack = new Stack<>();
        Queue<String> queue = new LinkedList<>();
        char[] exp_char_arr = exp.toCharArray();

        for( int i = 0; i < exp_char_arr.length; i++ )
        {
            char c = exp_char_arr[i];
            int type = getType(c);

            // numeric
            if( type == 0 )
            {
                String tmp = "";
                while( i < exp_char_arr.length && getType(exp_char_arr[i]) == 0 )
                    tmp += exp_char_arr[i++];

                // now the index variable i is on the next of the numeric token
                // so we should i--;
                i--;
                queue.offer(tmp);
            }
            // parenthesis
            else if( type == 1 )
            {
                if( c == '(' )
                {
                    stack.push(c);
                }
                else if( c == ')' )
                {
                    while( !stack.isEmpty() && stack.peek() != '(' )
                        queue.offer(stack.pop().toString());
                    if( stack.peek() == '(' )
                        stack.pop(); // useless left-parenthesis
                }
            }
            // operator
            else if( type == 2 || type == 3 )
            {
                while( !stack.isEmpty() && getType(stack.peek()) >= type )
                    queue.offer(stack.pop().toString());
                stack.push(c);
            }
        }

        while( !stack.isEmpty() )
            queue.offer(stack.pop().toString());

        return queue;
    }

    private String calculatePostfixQueue(Queue<String> postfix)
    {
        if( postfix.isEmpty() )
            return "0";

        try
        {
            Stack<String> stack = new Stack<>();
            while( !postfix.isEmpty() )
            {
                String token = postfix.poll();
                int token_type = getType(token.charAt(0));

                // operator
                if( token_type > 0 )
                {
                    Double operand2 = Double.parseDouble(stack.pop());
                    Double operand1 = Double.parseDouble(stack.pop());
                    Double rslt = 0.0;

                    if( token.equals("+") )
                        rslt = operand1 + operand2;
                    else if( token.equals("-") )
                        rslt = operand1 - operand2;
                    else if( token.equals("*") )
                        rslt = operand1 * operand2;
                    else if( token.equals("/") )
                        rslt = operand1 / operand2;

                    stack.push(rslt.toString());
                }
                // operand
                else
                {
                    stack.push(token);
                }
            }

            if( stack.isEmpty() )
                return "(error)";
            else
                return stack.pop();
        }
        catch( Exception e )
        {
            return e.toString();
        }
    }
}
