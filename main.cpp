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
   string UserInput;                                                                                // This is the variable in which we will store the user's expression.
   cout << "Enter you expression: ";                                                                // Asks the user to input their expression.
   getline(cin, UserInput);                                                                         // Stores whatever the user inputs into the command line in the UserInput variable.
   UserInput.erase(std::remove_if(UserInput.begin(), UserInput.end(), ::isspace), UserInput.end()); // Erases all unnecessary spaces in the whole string the user inputted.

   Tokens token;                                                 // Makes an instance of the Tokens class.
   Evaluate ex1;                                                 // Makes an instance of the Evaluate class.
   Parser parser;                                                // Makes an instance of the Parser class.
   Error error;                                                  // Makes an instance of the Error class.
   vector<string> expression = token.tokenizerInput(UserInput); // First, we want to tokenize the input expression, so we call to this function from the Tokens class.
   vector<string> parse = parser.goodInput(expression);          // Then, we want to pass this vector into the Parser class to see if what the user has inputted is good or bad input.
   
   // If it is good input, then the Parser goodInput function will return the vector from Tokenizer unchanged.
   // If the expression is badInput, it will return a string vector with the corresponding reason why there is bad input.
   if (parse != expression) // If the vector returned from the Tokenizer module and the vector returned from the Parser module are different, then a bad input occured.
   {

      error.errorMessage(parse); // Since there is an error in what the user has inputted, we will call to the Error Module and its function to print out the corresponding error message.
   }

   else // Otherwise, the input is valid, meaning that the Parser module returned the exact same vector as was given by Tokenizer.
   {
      try // Enter the try block to see if we can evaluate this expression.
      {
         double result = ex1.evaluateExpression(expression); // Calls to the Evaluate Module and its evaluateExpression functio to make the user input into a stack and evaluate.
         cout << result << endl;                             // If the result is evaluated with no errors (such as a Division by Zero error), then it will print the result.
      }
      
      catch (...) // If there is an error that occurs while evaluating the expression (like Division by Zero), then it is caught.
      {
         vector<string> er1; // We make a string vector that will have the error message, "Bad Input".
         er1.push_back("Bad Input.");
         error.errorMessage(er1); // It is then passed to the Error Module to print and handle the error.
      }
   }

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
