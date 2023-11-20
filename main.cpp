/*
Name: main.cpp
Authors: ALL
Date: 11/08/2023
Last modified: 11/19/2023
Purpose: Input Module that asks for User Input, stores it, allows it to go to the Tokenizer, Parser, and Evaluate Modules, all while handling errors in the process through Error Module.
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
      try
      {
         double result = ex1.evaluateExpression(expression);
         cout << result << endl;
      }
      catch (...)
      {
         vector<string> er1;
         er1.push_back("Bad Input.");
         error.errorMessage(er1);
      }
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
