/*
Name: error.cpp
Purpose: Defines the Error Class for Arithmetic Parser

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
#include "Error.h"

using namespace std;

void Error::errorMessage(const vector<string> &error)
{
    // Iterating over vector elements
    for (int i = 0; i < error.size(); i++)
    {
        cout << error[i] << endl;
    }
}

/*
int main()
{
    // declaring and initializing string vector
    Error er1;
    vector<string> V;
    V.push_back("Hello");
    V.push_back("One");

    // Printing all vector elements with ',' separator
    er1.errorMessage(V);
    return 0;
}
*/