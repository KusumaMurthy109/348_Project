/*
Name: Tokens.h
Authors: Kusuma Murthy, Nimra Syed, Reeny Huang
Date: 11/08/2023
Last modified: 11/19/2023
Purpose: Header file for Tokenizer Module that creates a evaluatable vector expression from string.
*/

#ifndef TOKENS_H
#define TOKENS_H

#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Tokens
{
public:
    vector<string> tokenizer_input(const string &UserInput); // Parsers through user input expression and converts it to a vector of strings.
};

#endif