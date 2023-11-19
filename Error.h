/*
Name: Error.h
Purpose: Error Class for Arithmetic Parser

The code ...
*/

#ifndef ERROR_H
#define ERROR_H

#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Error
{
public:
    void errorMessage(const vector<string> &error);
};

#endif