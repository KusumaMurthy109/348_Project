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
Function that determines if a string entry is a float (and a valid float).
*/

{
    bool is_valid; // Initilizes a bool variable that will return true or false if it is a float or not.
    int count = 0; // Counts how many decimal points there are in the string. There should only be one for it to be a valid float.
    // Iterates through each index of the string to check for how many decimal points there are.
    for (unsigned int i = 0; i < val.length(); i++)
    {
        if (val[i] == '.') // If there is a decimal point, increment count by 1.
        {
            count++;
        }
    }

    if (count == 1 && val.length() != 1) // For it to be a valid float, it must not just be a decimal point and it must have only one decimal point.
    {
        is_valid = true; // Returns true.
        return is_valid;
    }

    else
    {
        is_valid = false; // Otherwise, it is not a float and returns false.
        return is_valid;
    }
}

bool Parser::isExpr(string val)
/*
This function evaluates if a string is an operator or not.
*/

{
    return (val == "+" || val == "-" || val == "*" || val == "/" || val == "%" || val == "^" || val == "(" || val == ")"); // These are the valid operators, returns True if it is one of them.
}

bool Parser::isDigit(string val)
/*
This function evaluates if a string is a digit or not.
*/

{
    bool is_digit = true;                           // Initilizes a bool variable that will return true or false if it is a digit or not.
    for (unsigned int i = 0; i < val.length(); i++) // Iterates through each index of the string.
    {
        // If it is a number between 0-9 or contains a +/- for the sign of the number, then it is valid. Does a for loop so that it can see if more than 1-digit numbers are actual digits.
        if (val[i] == '0' || val[i] == '1' || val[i] == '2' || val[i] == '3' || val[i] == '4' || val[i] == '5' || val[i] == '6' || val[i] == '7' || val[i] == '8' || val[i] == '9' || val[i] == '-' || val[i] == '+')
        {
            is_digit = true; // Returns true if all of the digits are valid in the string.
        }

        else
        {
            is_digit = false; // Returns false if it finds one index where it is not a digit.
            break;            // Breaks the for loop because it found a case where the string is not a digt.
        }
    }

    return is_digit; // Returns the bool value of whether it is a digit or not.
}

bool Parser::isValidCharacter(const vector<string> &expression)
/*
This function evaluates if a vector contains all valid characters.
*/

{
    bool is_valid = true;                // Initilizes a bool variable that will return true or false if it is a valid vector or not.
    for (const string &val : expression) // Iterates through each entry of the vector.
    {
        if (!(isDigit(val) || isFloat(val) || isExpr(val))) // The correct characters are floats, integers, or operators. If it is anything other than these three, then it is invalid.
        {
            is_valid = false; // Finds a false case and so breaks the loop.
            break;
        }
    }

    return is_valid; // Returns the bool value of if the vector is valid or not.
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

    // Check if the beginning of the expressions starts with *,/,^,%, etc. and/or ends with *,/,^,%, etc.
    if (isExpr(expression[0]) && ((expression[0] != "+" && expression[0] != "-" && expression[0] != "(")))
    {
        is_valid = false; // If the expression start or ends with these operands, then it is not a good statement.
        return is_valid;
    }
    if (isExpr(expression.back()) && (expression.back() != ")"))
    {
        is_valid = false; // If there is an expression at the back that is not a parenthesis, then it is a bad statement.
        return is_valid;
    }

    // Checks for invalid consecutive operators and invalid expressions e.g. 5(1+3)
    for (int i = 0; i < exprSize - 1; ++i)
    {
        // std::cout << "i="<< expression[i] <<"  i + 1=" << expression[i + 1]<< endl;
        // If there are two consecutive operators together and one of them is not just a +,- sign or parenthesis, then it is invalid. Ex.: 5*^3.
        if (isExpr(expression[i]) && isExpr(expression[i + 1]) && (!(expression[i + 1] == "+" || expression[i + 1] == "-" || expression[i + 1] == "(" || expression[i] == ")")))
        {
            // std::cout << "condition 1";
            is_valid = false; // Returns false.
            return is_valid;
        }
        // If there are two parenthesis that goes closed then open, then it is an error. There should be an operator between them. Ex.: (10)(20).
        else if (isExpr(expression[i]) && isExpr(expression[i + 1]) && expression[i] == "(" && expression[i + 1] == ")")
        {
            is_valid = false; // Returns false.
            return is_valid;
        }
        // If there are two consecutive unary signs together, this is bad input, such as 5----2, or 5+-2, or 5^(--2).
        else if (isExpr(expression[i]) && isExpr(expression[i + 1]) && (expression[i] == "+" || expression[i] == "-") && (expression[i + 1] == "+" || expression[i + 1] == "-"))
        {
            is_valid = false;
            return is_valid;
        }
        // A valid expression should not have a closed parenthesis right after an operator. Ex of Bad Input.: 5*(3+).
        else if (isExpr(expression[i]) && (expression[i] == ")") && (expression[i + 1] == "("))
        {
            // std::cout << "condition 2";
            is_valid = false; // Returns false.
            return is_valid;
        }
        // If there is a digit, then the entry right after it, should not be an open parenthesis. Ex of Bad Input.: 5(3+2). It is valid if it is a sign like: -(3+2).
        else if (isDigit(expression[i]) && (expression[i + 1] == "(") && expression[i] != "-" && expression[i] != "+")
        {
            // std::cout << "condition 3";
            is_valid = false;
            return is_valid;
        }
    }
    return is_valid; // If all of the if statements are not executed, then returns true as it is a valid expression.
}

vector<string> Parser::goodInput(const vector<string> &expression)
/*
Function that verifying whether the vector expression is good input using other helper fucnctions.
*/

{
    bool character = isValidCharacter(expression);        // determines if expression has valid characters
    bool parenthesis = isBalancedParentheses(expression); // determines if expression has balanced parentheses
    bool math = isMathValid(expression);                  // determines if expression is mathematically correct
    vector<string> badInput;                              // initializes a string vector

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
        badInput.push_back("Missing or Misplaced Operands/Operators.");
    }

    // If expression has is valid, the original expression is returned.
    if (character != false and parenthesis != false and math != false)
    {
        return expression;
    }

    // If expression is invalid, badInput is returned will all the error messages.
    return badInput;
}