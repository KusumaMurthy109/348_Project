/*
Name: Error.h
Authors: Sophia Jacob, Anna Linn, Navya Nittala
Date: 11/15/2023
Last modified: 11/19/2023
Purpose: Header file for Error Module that takes in a vector of Error Messages and prints out accordingly.
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
    void errorMessage(const vector<string> &error); // Function that takes in a vector of Error Messages and prints them and deals with the errors accordingly.
};

#endif