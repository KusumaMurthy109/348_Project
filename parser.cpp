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
{
    return (val == "+" || val == "-" || val == "*" || val == "/" || val == "%" || val == "^" || val == "(" || val == ")");
}
bool Parser::isDigit(string val)
{
    return (val == "0" || val == "1" || val == "2" || val == "3" || val == "4" || val == "5" || val == "6" || val == "7" || val == "8" || val == "9");
}
bool Parser::isValidCharacter(const vector<string> &expression)
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
int main()
{
    Parser ex1;
    bool result = ex1.isValidCharacter({"5.5.1", "+", "3"});
    // bool result2 = ex1.isValidCharacter({"(", ")"});
    if (result == 0)
    {
        cout << "Invalid character expression." << endl;
    }
    else
    {
        cout << "All good" << endl;
    }
}