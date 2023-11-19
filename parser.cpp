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
            parentheses.push('('); // push '(' onto the stack
        }

        // Case: val is ')'
        else if (val == ")")
        {
            // If the stack is empty then the parentheses are not balanced and fasle is returned.
            if (parentheses.empty())
            {
                return false;
            }

            // Otherwise, a parentheses '(' is removed from the stack.
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

vector<string> Parser::goodInput(const vector<string> &expression)
/*
Function ...
*/

{
    bool character = isValidCharacter(expression);
    bool parenthesis = isBalancedParentheses(expression);
    vector<string> badInput;

    if (character == false)
    {
        badInput.push_back("Invalid Character Error.");
    }
    if (parenthesis == false)
    {
        badInput.push_back("Parenthesis Error.");
    }

    if (character != false and parenthesis != false)
    {
        return expression;
    }
    return badInput;
}

bool Parser::isValid(const vector<string> &expression)
{
    // correct expression = "8 - (5 - 2)", "(((2 + 3))) + (((1 + 2)))", "+(-2) * (-3) – ((-4) / (+5))", "-(-(-3)) + (-4) + (+5)", "(+2) * (+3) - (-4) / (-5)"
    // incorrect expression = "* 5 + 2", "(((3 + 4) - 2) + (1)", "((4 * 2) + ( - ))", "5 (2 + 3)"
    int exprSize = expression.size();
    bool valid = true;

    // check if the beginning of the expressions starts with +,-,*,/,etc. and/or the ends with +,-,*,/, etc.
    if (isExpr(expression[0]) && ((expression[0] != "+" && expression[0] != "-" && expression[0] != "(")))
    {
        valid = false;
        return valid;
    }
    if (isExpr(expression.back()) && (expression.back() != ")"))
    {
        valid = false;
        return valid;
    }

    // checks for invalid consecutive operands and invalid expresions e.g. 5(1+3)
    for (int i = 0; i < exprSize - 1; ++i)
    {
        // std::cout << "i="<< expression[i] <<"  i + 1=" << expression[i + 1]<< endl;
        if (isExpr(expression[i]) && isExpr(expression[i + 1]) && (!(expression[i + 1] == "+" || expression[i + 1] == "-" || expression[i + 1] == "(" || expression[i + 1] == ")")))
        {
            // std::cout << "condition 1";
            valid = false;
            return valid;
        }
        else if (isExpr(expression[i]) && (expression[i] != ")") && (expression[i + 1] == ")"))
        {
            // std::cout << "condition 2";
            valid = false;
            return valid;
        }

        else if (isDigit(expression[i]) && (expression[i + 1] == "("))
        {
            // std::cout << "condition 3";
            valid = false;
            return valid;
        }
        else if (isExpr(expression[i]) && expression[i] != ")" && expression[i + 1] == ")")
        {
            // std::cout << "condition 4" << expression[i] << expression[i + 1];
            valid = false;
            return valid;
        }
    }
    return valid;
}
/*int main()
{
   Parser ex1;
   bool result = ex1.isValid({"(", "(", "(", "3", "+4", ")", "-2", ")", ")"});
   if (result)
   {
       cout << "true." << endl;
   }
   else
   {
       cout << "false" << endl;
   }
}*/
