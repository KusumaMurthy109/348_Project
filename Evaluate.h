/*
Name: Evaluate.h
Authors: Sophia Jacob, Anna Lin, Navya Nittala
Date: 11/08/2023
Last modified: 11/19/2023
Purpose: Header File for Evaluate Module that returns the accurate output, through stack implementation, of an expression given by a vector.
*/

#ifndef EVALUATE_H
#define EVALUATE_H

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Evaluate
{
public:
  vector<char> expression; // Input vector that needs to be evaluated.

  // private:
  bool isOperator(string c);                                                  // Checks if the character is an operator: +, -, *, /, %, ^.
  int getPrecedence(char op);                                                 // Returns which operator has a higher order of precedence (3 is highest).
  double evaluateExpression(const vector<string> &expression);                // Makes operators and operands into Stacks to represent expression's Structure and starts evaluating.
  double evaluateRemainding(stack<double> &operands, stack<char> &operators); // If there is any remaining operators in the stack (ex. outside of parenthesis), then evaluate and finish.
};

#endif