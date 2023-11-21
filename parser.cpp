/*
Name: parser.cpp
Authors: ALL
Date: 11/10/2023
Last modified: 11/19/2023
Purpose: Parser Module that goes through the expression stored in vector, before it goes to Evaluate, to check for bad input and raise Errors if necessary.
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


bool Parser::isMathValid(const vector<string> &expression)
/*
Function that verifying whether the vector expression is mathematically correct.
Verifies that expression does not begin and end with an operator,
and verifies that expression does not have invalid consecutive operands.
*/

{
    // correct expression = "8 - (5 - 2)", "(((2 + 3))) + (((1 + 2)))", "+(-2) * (-3) – ((-4) / (+5))", "-(-(-3)) + (-4) + (+5)", "(+2) * (+3) - (-4) / (-5)"
    // incorrect expression = "* 5 + 2", "(((3 + 4) - 2) + (1)", "((4 * 2) + ( - ))", "5 (2 + 3)"
    int exprSize = expression.size();
    bool is_valid = true;

    // Check if the beginning of the expressions starts with +,-,*,/,etc. and/or ends with +,-,*,/, etc.
    if (isExpr(expression[0]) && ((expression[0] != "+" && expression[0] != "-" && expression[0] != "(")))
    {
        is_valid = false;
        return is_valid;
    }
    if (isExpr(expression.back()) && (expression.back() != ")"))
    {
        is_valid = false;
        return is_valid;
    }

    // Checks for invalid consecutive operands and invalid expresions e.g. 5(1+3)
    for (int i = 0; i < exprSize - 1; ++i)
    {
        // std::cout << "i="<< expression[i] <<"  i + 1=" << expression[i + 1]<< endl;

        if (isExpr(expression[i]) && isExpr(expression[i + 1]) && (!(expression[i + 1] == "+" || expression[i + 1] == "-" || expression[i + 1] == "(" || expression[i + 1] == ")" || expression[i] == ")")))
        {
            // std::cout << "condition 1";
            is_valid = false;
            return is_valid;
        }
        else if (isExpr(expression[i]) && (expression[i] != ")") && (expression[i + 1] == ")"))
        {
            // std::cout << "condition 2";
            is_valid = false;
            return is_valid;
        }

        else if (isDigit(expression[i]) && (expression[i + 1] == "(") && expression[i] != "-" && expression[i] != "+")
        {
            // std::cout << "condition 3";
            is_valid = false;
            return is_valid;
        }
        else if (isExpr(expression[i]) && expression[i] != ")" && expression[i + 1] == ")")
        {
            // std::cout << "condition 4" << expression[i] << expression[i + 1];
            is_valid = false;
            return is_valid;
        }
    }
    return is_valid;
}


vector<string> Parser::goodInput(const vector<string> &expression)
/*
Function that verifying whether the vector expression is good input using other helper fucnctions.
*/

{ 
    bool character = isValidCharacter(expression); // determines if expression has valid characters
    bool parenthesis = isBalancedParentheses(expression); // determines if expression has balanced parentheses
    bool math = isMathValid(expression); // determines if expression is mathematically correct
    vector<string> badInput; // initializes a string vector
    
    // If expression has invalid characters, a corresponding error is added to badInput.
    if (character == false)
    {
        badInput.push_back("Invalid Character Error.");
    }

    // If expression has unbalanced parentheses, a corresponding error is added to badInput.
    if (parenthesis == false)
    {
        badInput.push_back("Parentheses Error.");
    }

    // If expression is mathematically incorrect , a corresponding error is added to badInput.
    if (math == false)
    {
        badInput.push_back("Operands (or not enough operands) is in the wrong position.");
    }

    // If expression has is valid, the original expression is returned.
    if (character != false and parenthesis != false and math != false)
    {
        return expression;
    }

    // If expression is invalid, badInput is returned will all the error messages.
    return badInput;
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
