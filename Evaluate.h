/*
Name: Evaluate.h
Authors: Sophia Jacob, Anna Linn, Navya Nittala
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

// Note: intially assume that inputs are integers
class Evaluate
{
public:
  vector<char> expression; // vector

  // private:
  bool isOperator(string c);
  int getPrecedence(char op);
  double evaluateExpression(const vector<string> &expression);
  double evaluateRemainding(stack<double> &operands, stack<char> &operators);
  /*
  void CreateStack(vector<char> expression, stack<char>* operators, stack<double>* operands);
  bool isOperator(char expression);
  void ParenthesesHandler(stack<char> &operators, stack<double> &operands);
  void OperatorPrecedence(char expression, stack<char> *operators, stack<double> *operands);
  int getPrecedence(char expression);
  double SimplyRemainding(stack<char> &operators, stack<double> &operands);
  double Solve(vector<char> expression);
  */
};

#endif