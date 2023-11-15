// tokenizer template
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
    bool isFloat(string val);
};

#endif