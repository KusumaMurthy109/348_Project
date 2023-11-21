/*
Name: parser.cpp
Authors: ALL
Date: 11/10/2023
Last modified: 11/19/2023
Purpose: Header file for Parser Module that goes through the expression stored in vector, before it goes to Evaluate, to check for bad input and raise Errors if necessary.
*/

#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Parser
{
public:
    bool isValidCharacter(const vector<string> &expression);      // Checks if all the entries of a vector are either floats, digits, or operators, thus valid characters.
    bool isFloat(string val);                                     // Helper that determines if an entry is a float.
    bool isExpr(string val);                                      // Helper that determines if an entry is an operator.
    bool isDigit(string val);                                     // Helper that determiens if an entry is a digit.
    bool isBalancedParentheses(const vector<string> &expression); // Checks if the inputted expression contains balanced parentheses.
    bool isMathValid(const vector<string> &expression);           // Checks if the vector contains enough operators to satisfy the Evaluate module, and is mathematically correct input.
    vector<string> goodInput(const vector<string> &expression);   // Uses the helper functions to determine, overall, if the expression is good input, and gives back original vector if it is, otherwise goes to Error module.
};

#endif
