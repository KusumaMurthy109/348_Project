/*
Name: main.cpp
Purpose: Driver for Arthimetic Parser


The code ...
*/

#include <iostream>
#include <string>
#include <algorithm>
#include "Tokens.h"
#include "Parser.h"
#include "Evaluate.h"
#include "Parser.h"
#include "Error.h"

using namespace std;

int main()
{
   string UserInput;
   cout << "Enter you expression: ";
   getline(cin, UserInput);
   UserInput.erase(std::remove_if(UserInput.begin(), UserInput.end(), ::isspace), UserInput.end());

   Tokens token;
   Evaluate ex1;
   Parser parser;
   Error error;
   vector<string> expression = token.tokenizer_input(UserInput);
   vector<string> parse = parser.goodInput(expression);

   if (parse != expression)
   {

      error.errorMessage(parse);
   }
   else
   {
      double result = ex1.evaluateExpression(expression);
      cout << result << endl;
   }

   // double result = ex1.evaluateExpression(expression);
   // cout << result << endl;
   //  double result = ex1.evaluateExpression(expression);
   //  cout << result << endl;

   return 0;
}

/*
TO RUN THE CODE:
Type into you terminal:
  g++ -c main.cpp -o main.o
  g++ -c tokens.cpp -o tokens.o
  g++ main.o tokens.o -o myprogram


and then enter the following command into the terminal:
  ./myprogram
*/
