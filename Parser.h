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
    bool isValidCharacter(const vector<string> &expression);
    bool isFloat(string val); // helper
    bool isExpr(string val);  // helper
    bool isDigit(string val); // helper
    bool isBalancedParentheses(const vector<string> &expression);
    vector<string> goodInput(const vector<string> &expression);
    bool isMathValid(const vector<string> &expression);
};

#endif
