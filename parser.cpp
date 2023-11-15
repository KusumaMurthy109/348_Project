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
    try
    {
        double parsed_val = stod(val);
        is_valid = true;
        return is_valid;
    }
    catch (const exception &e)
    {
        is_valid = false;
        return is_valid;
    }
}
bool Parser::isValidCharacter(const vector<string> &expression)
{
    for (const string &val : expression)
    {
        if (isdigit(val[0]))
        {
            return (true);
        }
        else if (isFloat(val))
        {
            return (true);
        }
        else if (!(val == "+" || val == "-" || val == "*" || val == "/" || val == "%" || val == "^"))
        {
            return (false);
        }
        else
        {
            return (0);
        }
    }
}
int main()
{
    Parser ex1;
    bool result = ex1.isValidCharacter({"5", "+", "$", "3"});
    cout << result << endl;
}