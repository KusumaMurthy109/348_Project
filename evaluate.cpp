/*
Name: evaluate.cpp
Authors: Sophia Jacob, Anna Lin, Navya Nittala
Date: 11/08/2023
Last modified: 11/19/2023
Purpose: Evaluate Module that returns the accurate output, through stack implementation, of an expression given by a vector.
*/

#include <iostream>
#include <math.h>
#include <cmath>
#include <stack>
#include <sstream>
#include <string>
#include <vector>
#include "Evaluate.h"
#include "Error.h"

using namespace std;

bool Evaluate::isOperator(string c)
/*
Function determines if a string is an operator and returns a bool.
*/

{
    return c == "+" || c == "-" || c == "*" || c == "/" || c == "%" || c == "^";
}

int Evaluate::getPrecedence(char op)
/*
Function determines the precedence of operators and returns corresponding integer rank value.
*/

{
    if (op == '^')
    {
        return 3;
    }

    else if (op == '*' || op == '/' || op == '%')
    {
        return 2;
    }

    else if (op == '+' || op == '-')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


double Evaluate::evaluateExpression(const vector<string> &expression)
/*
Function evaluates the input vector expression through the manipulation of a operands stack and a operators stack.
Operator precedence is consider and final answer is returned.
*/

{
    try
    {

        int index = 0;
        stack<double> operands; // initializes a stack for numbers
        stack<char> operators;  // initializes a stack for operators

        /*
        Iterates through each value of the vector expression, adds its corresponding stack, and performs evaluations throughout.
        */

        for (const string &val : expression)
        {
            // Case: val is a number
            if (!isOperator(val) && (val[0] != '(') && (val[0] != ')'))
            {
                double d1;               // creates a variable of type double
                stringstream(val) >> d1; // converts the string of a number into a double
                operands.push(d1);       // pushes number into operands stack
                index++;
            }

            // Case: val is '('
            else if (val == "(")
            {
                operators.push('('); // pushes '(' to operators stack
                index++;
            }
            // Case: val is )
            else if (val == ")")
            {
                // Start evaluating expression until the '(' parenthesis.
                while (!operators.empty() && operators.top() != '(')
                {
                    char op = operators.top();        // op is set to the operator at the top of the stack
                    operators.pop();                  // operator is then removed from stack
                    double operand2 = operands.top(); // the right operand is set to the number at the top of the stack
                    operands.pop();                   // operand is then removed from stack
                    double operand1 = operands.top(); // the left operand is set to the number at the top of the stack
                    operands.pop();                   // operand is then removed from stack

                    if (op == '+')
                    {
                        operands.push(operand1 + operand2); // performs addition and pushes the sum onto the stack
                    }

                    else if (op == '-')
                    {
                        operands.push(operand1 - operand2); // performs substraction and pushes the difference onto the stack
                    }

                    else if (op == '*')
                    {
                        operands.push(operand1 * operand2); // perfoms multiplication and pushes the product onto the stack
                    }

                    else if (op == '/')
                    {
                        try
                        {
                            if (operand2 == 0)
                            {
                                throw(operand2);
                            }
                            else
                            {
                                double new_operand = operand2;
                                double result = operand1 / new_operand;
                                operands.push(result); // pushes the quotient onto the stack
                            }
                        }
                        catch (...)
                        {
                            Error er1;
                            vector<string> error_message;
                            error_message.push_back("Division by Zero Error.");
                            er1.errorMessage(error_message);
                            break;
                        }
                    }

                    else if (op == '%')
                    {
                        long new_op1 = operand1;
                        long new_op2 = operand2;
                        operands.push(new_op1 % new_op2); // pushes the remainder onto the stack
                    }

                    else if (op == '^')
                        operands.push(pow(operand1, operand2)); // pushes the power onto the stack
                }
                operators.pop(); // removes '('
                index++;
            }

            // Case:
            else if (isOperator(val) && index == 0 && val == "+")
            {
                index++;
            }

            // Case:
            else if (isOperator(val) && index == 0 && val == "-")
            {
                operands.push(-1);
                operators.push('*');
                index++;
            }

            // Case:
            else if (isOperator(val) && index != 0 && val == "-" && expression[index - 1] == "(" and expression[index + 1] == "(")
            {
                operands.push(-1);
                operators.push('*');
                index++;
            }

            // Case: val is an operator
            else if (isOperator(val))
            {
                // Starts evaluating expression until the operators in the operators stack is in order of precedence.
                while (!operators.empty() && (getPrecedence(operators.top()) >= getPrecedence(val[0])))
                {
                    char op = operators.top(); // op is set to the operator at the top of the stack
                    operators.pop(); // operator is then removed from stack
                    double operand2 = operands.top(); // the right operand is set to the number at the top of the stack
                    operands.pop(); // operand is then removed from stack
                    double operand1 = operands.top(); // the left operand is set to the number at the top of the stack
                    operands.pop(); // operand is then removed from stack

                    if (op == '+')
                    {
                        operands.push(operand1 + operand2); // performs addition and pushes the sum onto the stack
                    }

                    else if (op == '-')
                    {
                        operands.push(operand1 - operand2); // performs substraction and pushes the difference onto the stack
                    }

                    else if (op == '*')
                    {
                        operands.push(operand1 * operand2); // perfoms multiplication and pushes the product onto the stack
                    }

                    else if (op == '/')
                    {
                        try
                        {
                            if (operand2 == 0)
                            {
                                throw(operand2);
                            }
                            else
                            {
                                double new_operand = operand2;
                                double result = operand1 / new_operand;
                                operands.push(result); // performs division and pushes the quotient onto the stack
                            }
                        }

                        catch (...)
                        {
                            Error er1;
                            vector<string> error_message;
                            error_message.push_back("Division by Zero Error.");
                            er1.errorMessage(error_message);
                            break;
                        }
                    }
                    
                    else if (op == '%')
                    
                    {
                        long new_op1 = operand1;
                        long new_op2 = operand2;
                        operands.push(new_op1 % new_op2);
                    }
                    else if (op == '^')
                        operands.push(pow(operand1, operand2));
                }
                operators.push(val[0]); // Pushes the new operator at the very end so that we can evaluate the one with precedence first.
                index++;
            }
        }

        double result = evaluateRemainding(operands, operators);
        return result;
    }

    catch (...)
    {
        throw(expression);
    }
}

double Evaluate::evaluateRemainding(stack<double> &operands, stack<char> &operators)
{
    while (!operators.empty())
    {
        char op = operators.top();        // op is set to the operator at the top of the stack
        operators.pop();                  // operator is then removed from stack
        double operand2 = operands.top(); // the right operand is set to the number at the top of the stack
        operands.pop();                   // operand is then removed from stack
        double operand1 = operands.top(); // the left operand is set to the number at the top of the stack
        operands.pop();                   // operand is then removed from stack

        if (op == '+')
        {
            operands.push(operand1 + operand2); // performs addition and pushes the sum onto the stack
        }

        else if (op == '-')
        {
            operands.push(operand1 - operand2); // performs substraction and pushes the difference onto the stack
        }

        else if (op == '*')
        {
            operands.push(operand1 * operand2); // perfoms multiplication and pushes the product onto the stack
        }

        else if (op == '/')
        {
            try
            {
                if (operand2 == 0)
                {
                    throw(operand2);
                }
                
                else
                {
                    double new_operand = operand2;
                    double result = operand1 / new_operand;
                    operands.push(result); // performs division and pushes the quotient onto the stack
                }
            }

            catch (...)
            {
                Error er1;
                vector<string> error_message;
                error_message.push_back("Division by Zero Error.");
                er1.errorMessage(error_message);
                break;
            }
        }

        else if (op == '%')
        {
            long new_op1 = operand1;
            long new_op2 = operand2;
            operands.push(new_op1 % new_op2); // pushes the remainder onto the stack
        }

        else if (op == '^')
        {
            operands.push(pow(operand1, operand2)); // pushes the power onto the stack
        }
    }

    if (operands.empty() == false)
    {
        return operands.top(); // Ending of calculating expression.
    }

    else
    {
        throw(false);
    }
}
/*
int main() {
   // Example expression represented as an array of tokens
   //4 * (3 + 2) % 7 - 1
   // (((2 + 3))) + (((1 + 2)))
   // +(-2) * (-3) – ((-4) / (+5))
   // ((5 * 2) - ((3 / 1) + ((4 % 3))))
   // (((2 ^ (1 + 1)) + ((3 - 1) ^ 2)) / ((4 / 2) % 3))
   // (((((5 - 3))) * (((2 + 1))) + ((2 * 3))))
   // ((9 + 6)) / ((3 * 1) / (((2 + 2))) - 1)
   //-(+1) + (+2)
   // -(+2) * (+3) - (-4) / (-5)
   // -(-(-3)) + (-4) + (+5)
   vector<string> tokens = {"41", "*", "(", "32", "+", "21", ")", "+", "71", "-", "12"};
   vector<string>tokens2 = {"-", "(", "+1", ")", "+", "(", "+2", ")"};
   vector<string> token2 = {"+2", "^", "-3"};
   vector<string> token3 = {"10.2", "*", "2", "/", "5"};
   vector<string> token4 = {"(", "(", "(", "2", "+", "3", ")", ")", ")", "+", "(",  "(", "(", "1", "+", "2", ")", ")", ")"};
   vector <string> token5 = {"+", "(", "-2", ")", "*", "(", "-3", ")", "-",  "(", "(", "-4", ")", "/", "(", "+5", ")", ")"};
   //vector<string> token5 = {"-2", "+", "1"};
   vector <string> token6 = {"-2", "*", "-3", "-", "(", "-4", "/", "5", ")"};
   vector <string> token7 = {"(", "-2", ")", "*", "(", "-3", ")", "-",  "(", "(", "-4", ")", "/", "(", "+5", ")", ")"};
  //vector <string> token8 = {"-", "(", "+1", ")", "+", "(", "+2", ")"};
  vector <string> token8 = {"8", "-", "(", "5", "-", "2", ")"};
  vector <string> token9 = {"(", "(", "5", "*", "2", ")", "-", "(",  "(", "3", "/", "1", ")", "+", "(", "(", "4", "%", "3", ")", ")", ")", ")"};
  vector <string> token10 = {"(", "(", "(", "2", "^", "(", "1", "+",  "1", ")", ")", "+", "(", "(", "3", "-", "1", ")", "^", "2", ")", ")", "/", "(", "(", "4", "/", "2", ")", "%", "3", ")", ")"};
  vector <string> token11 = {"(", "(", "(", "(", "(", "5", "-", "3", ")",  ")", ")", "*", "(", "(", "(", "2", "+", "1", ")", ")", ")", "+", "(", "(", "2", "*", "3", ")", ")", ")", ")"};
  vector <string> token12 = {"(", "(", "9", "+", "6", ")", ")", "/", "(",  "(", "3", "*", "1", ")", "/", "(", "(", "(", "2", "+", "2", ")", ")", ")", "-", "1", ")"};
  vector <string> token14 = {"-", "(", "+2", ")", "*", "(", "+3", ")", "-", "(", "-4", ")", "/", "(", "-5", ")"};
  vector <string> token15 = {"+", "(", "+2", ")", "*", "(", "+3", ")", "+", "(", "-4", ")", "/", "(", "-5", ")"};
  vector <string> token16 = {"-", "(", "-", "(", "-3", ")", ")", "+", "(", "-4", ")", "+", "(", "+5", ")"};


 // Evaluate the expression
 Evaluate ex1;
 double result = ex1.evaluateExpression(tokens);
 double result2 = ex1.evaluateExpression(token2);
 double result3 = ex1.evaluateExpression(token3);
 double result4 = ex1.evaluateExpression(token4);
 double result5 = ex1.evaluateExpression(token5);
 double result6 = ex1.evaluateExpression(token6);
 double result7 = ex1.evaluateExpression(token7);
 double result8 = ex1.evaluateExpression(token8);
 double result9 = ex1.evaluateExpression(token9);
 double result10 = ex1.evaluateExpression(token10);
 double result11 = ex1.evaluateExpression(token11);
 double result12 = ex1.evaluateExpression(token12);
 double resultt2 = ex1.evaluateExpression(tokens2);
 double result14 = ex1.evaluateExpression(token14);
 double result15 = ex1.evaluateExpression(token15);
 double result16 = ex1.evaluateExpression(token16);
 // Output the result
 cout << result << endl;
 cout << result2 << endl;
 cout << result3 << endl;
 cout << result4 << endl;
 cout << result5 << endl;
 cout << result6 << endl;
 cout << result7 << endl;
 cout << result8 << endl;
 cout << result9 << endl;
 cout << result10 << endl;
 cout << result11 << endl;
 cout << result12 << endl;
 cout << resultt2 << endl;
 cout << result14 << endl;
 cout << result15 << endl;
 cout << result16 << endl;




 return 0;


}
*/
