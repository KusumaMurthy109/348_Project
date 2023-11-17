/*
Name: parser.cpp
Purpose: Defines the Parser Class for Arithmetic Parser

The code ...
*/

#include <iostream>
#include <math.h>
#include <cmath>
#include <stack>
#include <sstream>
#include <string>
#include <exception>
#include <vector>
#include "Parser.h"

using namespace std;

bool Parser::isFloat(string val)
/*
Function ...
*/

{
    bool is_valid;
    int count = 0;

    for (unsigned int i = 0; i < val.length(); i++)
    {
        if (val[i] == '.')
        {
            count++;
        }
    }

    if (count == 1)
    {
        is_valid = true;
        // cout << count << endl;
        return is_valid;
    }

    else
    {
        is_valid = false;
        // cout << count << endl;
        return is_valid;
    }
}


bool Parser::isExpr(string val)
/*
Function ...
*/

{
    return (val == "+" || val == "-" || val == "*" || val == "/" || val == "%" || val == "^" || val == "(" || val == ")");
}


bool Parser::isDigit(string val)
/*
Function ...
*/

{
    bool is_digit = true;
    for (unsigned int i = 0; i < val.length(); i++)
    {
        if (val[i] == '0' || val[i] == '1' || val[i] == '2' || val[i] == '3' || val[i] == '4' || val[i] == '5' || val[i] == '6' || val[i] == '7' || val[i] == '8' || val[i] == '9' || val[i] == '-' || val[i] == '+')
        {
            is_digit = true;
        }

        else
        {
            is_digit = false;
            break;
        }
    }

    return is_digit;
}


bool Parser::isValidCharacter(const vector<string> &expression)
/*
Function ...
*/

{
    bool is_valid = true;
    for (const string &val : expression)
    {
        if (!(isDigit(val) || isFloat(val) || isExpr(val)))
        {
            is_valid = false;
            break;
        }
    }

    return is_valid;
}


bool Parser::isBalancedParentheses(const vector<string> &expression)
/*
Function utilizes a stack to check to see if the parentheses in the vector expression are balanced. Returns a bool.
*/

{
    stack<char> parentheses; // intializes a stack for parentheses

    for (const string &val : expression) // iterates through each value of the vector expression
    {
        // Case: val is '('
        if (val == "(")
        {
            parentheses.push('('); //push '(' onto the stack
        }

        // Case: val is ')'
        else if (val == ")")
        {
            //If the stack is empty then the parentheses are not balanced and fasle is returned.
            if (parentheses.empty())
            {
                return false;
            }

            //Otherwise, a parentheses '(' is removed from the stack.
            else
            {
                parentheses.pop();
            }
        }
    }

    // If the the stack is empty, then the parentheses are balanced and true is returned.
    // If the stack is not empty, then the parentheses are not balanced and false is returned.
    return parentheses.empty();
}


bool Parser::goodInput(const vector<string> &expression)
/*
Function ...
*/

{
    bool character = isValidCharacter(expression);
    bool parenthesis = isBalancedParentheses(expression);

    if (character == false || parenthesis == false)
    {
        return false;
    }

    else
    {
        return true;
    }
}
/*
int main()
{
    Parser ex1;
    bool result = ex1.isBalancedParentheses({")", "("});
    if (!result)
    {
        cout << "Expression has inbalanced parentheses." << endl;
    }
    else
    {
        cout << "All good" << endl;
    }
}
*/