/*
Name: Parser.h
Purpose: Parser Class for Arithmetic Parser


The code ...
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
    bool isValid(const vector<string> &expression);
};

#endif
