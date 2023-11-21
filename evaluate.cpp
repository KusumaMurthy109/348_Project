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
The functionality of Evaluate is to represent the expression as a Stack and evaluate from there.
Operator precedence and Parenthesis Precedence is considered and final answer is returned.
*/

{
    try // Enters try block to see if it can try to evaluate the expression.
    {

        int index = 0;
        stack<double> operands; // Initializes a stack for numbers
        stack<char> operators;  // Initializes a stack for operators

        // Iterates through each value of the vector expression, adds its corresponding stack, and performs evaluations throughout.
        for (const string &val : expression)
        {
            // Case: val is a number
            if (!isOperator(val) && (val[0] != '(') && (val[0] != ')'))
            {
                double d1;               // Creates a variable of type double
                stringstream(val) >> d1; // Converts the string of a number into a double
                operands.push(d1);       // Pushes number into operands stack
                index++;                 // We can move onto the next index.
            }

            // Case: val is '('
            else if (val == "(")
            {
                operators.push('('); // pushes '(' to operators stack
                index++;             // We can move onto the next index.
            }
            // Case: val is )
            else if (val == ")")
            {
                // Start evaluating expression until the '(' parenthesis.
                // This is done to ensure that the right parenthesis and the expression in it, gets evaluated first.
                while (!operators.empty() && operators.top() != '(')
                {
                    char op = operators.top();        // Op is set to the operator at the top of the stack
                    operators.pop();                  // Operator is then removed from stack
                    double operand2 = operands.top(); // The right operand is set to the number at the top of the stack
                    operands.pop();                   // Operand is then removed from stack
                    double operand1 = operands.top(); // The left operand is set to the number at the top of the stack
                    operands.pop();                   // Operand is then removed from stack

                    if (op == '+')
                    {
                        operands.push(operand1 + operand2); // Performs addition and pushes the sum onto the stack
                    }

                    else if (op == '-')
                    {
                        operands.push(operand1 - operand2); // Performs substraction and pushes the difference onto the stack
                    }

                    else if (op == '*')
                    {
                        operands.push(operand1 * operand2); // Perfoms multiplication and pushes the product onto the stack
                    }

                    else if (op == '/')
                    {
                        try
                        {
                            if (operand2 == 0) // Division by Zero is an error. If the second operand that we are dividing by is 0, throw an error.
                            {
                                throw(operand2); // Throws the error.
                            }
                            else
                            {
                                double new_operand = operand2;          // Otherwise, it is valid division.
                                double result = operand1 / new_operand; // Performs division and stores it into a double.
                                operands.push(result);                  // Pushes the quotient onto the stack
                            }
                        }
                        catch (...) // Catches the error.
                        {
                            Error er1;                    // Gives error to the Error Module.
                            vector<string> error_message; // The Error Message is set to Division by Zero error.
                            error_message.push_back("Division by Zero Error.");
                            er1.errorMessage(error_message); // Error Module prints error.
                            break;                           // Loop is broken as this is bad input.
                        }
                    }

                    else if (op == '%')
                    {
                        long new_op1 = operand1;
                        long new_op2 = operand2;
                        operands.push(new_op1 % new_op2); // Pushes the remainder onto the stack.
                    }

                    else if (op == '^')
                        operands.push(pow(operand1, operand2)); // Pushes the power onto the stack.
                }
                operators.pop(); // Removes '(' since we have finished evaluating the expression inside parenthesis.
                index++;         // We can move onto the next index.
            }

            // Case: If the beginning of the expression starts with a + sign, then it can be ignored since it is the same expression.
            else if (isOperator(val) && index == 0 && val == "+")
            {
                index++; // Moves on to the next index.
            }

            // Case: If the beginning expression starts with a - sign, then we can do -1*the rest of the expression which is an equivalent expression.
            else if (isOperator(val) && index == 0 && val == "-")
            {
                operands.push(-1);   // Push a -1 to the operand stack.
                operators.push('*'); // Push a multiplication sign to the operator stack.
                index++;             // Moves on to the next index.
            }

            // Case: This checks to see if there is a - sign sandwiched between two open parenthesis like: (-(-(3+2))), which again is the equivalent of saying -1*expression.
            else if (isOperator(val) && index != 0 && val == "-" && expression[index - 1] == "(" and expression[index + 1] == "(")
            {
                operands.push(-1);   // Push a -1 to the operand stack.
                operators.push('*'); // Push a multiplication sign to the operator stack.
                index++;             // Moves on to the next index.
            }

            // Case: If the value is an operator, then we can add it to the operator stack and start evaluating based on precedence.
            else if (isOperator(val))
            {
                // Starts evaluating expression until the operators in the operators stack is in order of precedence.
                // Evaluates while there are still more operators that need evaluating, and until the precedence of the operator at the top is greater than the operator the for loop is currently on.
                // We need to evaluate based on precedence, so first we evaluate all that is in the stack that has greater precedence and then we can push the new operator into the stack with less precedence.
                while (!operators.empty() && (getPrecedence(operators.top()) >= getPrecedence(val[0])))
                {
                    char op = operators.top();        // op is set to the operator at the top of the stack
                    operators.pop();                  // operator is then removed from stack
                    double operand2 = operands.top(); // the right operand is set to the number at the top of the stack
                    operands.pop();                   // operand is then removed from stack
                    double operand1 = operands.top(); // the left operand is set to the number at the top of the stack
                    operands.pop();                   // operand is then removed from stack

                    if (op == '+')
                    {
                        operands.push(operand1 + operand2); // Performs addition and pushes the sum onto the stack
                    }

                    else if (op == '-')
                    {
                        operands.push(operand1 - operand2); // Performs substraction and pushes the difference onto the stack
                    }

                    else if (op == '*')
                    {
                        operands.push(operand1 * operand2); // Perfoms multiplication and pushes the product onto the stack
                    }

                    else if (op == '/')
                    {
                        try
                        {
                            if (operand2 == 0) // Division by Zero is an error. If the second operand that we are dividing by is 0, throw an error.
                            {
                                throw(operand2); // Throws the error.
                            }
                            else
                            {
                                double new_operand = operand2;          // Otherwise, it is valid division.
                                double result = operand1 / new_operand; // Performs division and stores it into a double.
                                operands.push(result);                  // Pushes the quotient onto the stack.
                            }
                        }

                        catch (...) // Catches the error.
                        {
                            Error er1;                    // Gives error to the Error Module.
                            vector<string> error_message; // The Error Message is set to Division by Zero error.
                            error_message.push_back("Division by Zero Error.");
                            er1.errorMessage(error_message); // Error Module prints message.
                            break;                           // Loop is broken as this is bad input.
                        }
                    }

                    else if (op == '%')

                    {
                        long new_op1 = operand1;
                        long new_op2 = operand2;
                        operands.push(new_op1 % new_op2); // Pushes the remainder onto the stack.
                    }
                    else if (op == '^')
                        operands.push(pow(operand1, operand2)); // Pushes the power onto the stack.
                }
                operators.push(val[0]); // Pushes the new operator at the very end so that we can evaluate the one with precedence first.
                index++;                // Move on to the next index.
            }
        }

        double result = evaluateRemainding(operands, operators); // Calls to the function that will evaluate the remainding values and operators that are in the respective stacks.
        return result;                                           // Returns the answer.
    }

    catch (...) // Catches any error.
    {
        throw(expression); // Throws the expression if there was an error encountered when evaluating the expression.
    }
}

double Evaluate::evaluateRemainding(stack<double> &operands, stack<char> &operators)
/*
Function evaluates any remainding values and operands in the stacks, by taking in the two stacks from the evaluateExpression function
and evaluating any remainding values.
*/
{
    while (!operators.empty())
    {
        char op = operators.top();        // Op is set to the operator at the top of the stack
        operators.pop();                  // Operator is then removed from stack
        double operand2 = operands.top(); // The right operand is set to the number at the top of the stack
        operands.pop();                   // Operand is then removed from stack
        double operand1 = operands.top(); // The left operand is set to the number at the top of the stack
        operands.pop();                   // Operand is then removed from stack

        if (op == '+')
        {
            operands.push(operand1 + operand2); // Performs addition and pushes the sum onto the stack
        }

        else if (op == '-')
        {
            operands.push(operand1 - operand2); // Performs substraction and pushes the difference onto the stack
        }

        else if (op == '*')
        {
            operands.push(operand1 * operand2); // Perfoms multiplication and pushes the product onto the stack
        }

        else if (op == '/')
        {
            try
            {
                if (operand2 == 0) // Division by Zero is an error. If the second operand that we are dividing by is 0, throw an error.
                {
                    throw(operand2); // Throws the error.
                }

                else
                {
                    double new_operand = operand2;          // Otherwise, it is valid division.
                    double result = operand1 / new_operand; // Performs division and stores it into a double.
                    operands.push(result);                  // Performs division and pushes the quotient onto the stack.
                }
            }

            catch (...) // Catches the error.
            {
                Error er1;                    // Gives error to the Error Module.
                vector<string> error_message; // The Error Message is set to Division by Zero error.
                error_message.push_back("Division by Zero Error.");
                er1.errorMessage(error_message); // Error Module prints message.
                break;                           // Loop is broken as this is bad input.
            }
        }

        else if (op == '%')
        {
            long new_op1 = operand1;
            long new_op2 = operand2;
            operands.push(new_op1 % new_op2); // Pushes the remainder onto the stack.
        }

        else if (op == '^')
        {
            operands.push(pow(operand1, operand2)); // Pushes the power onto the stack.
        }
    }

    if (operands.empty() == false)
    {
        return operands.top(); // Ending of calculating expression and operands has the final result of the remaining calcualations.
    }

    else
    {
        throw(false); // If there isn't a result because of an error (such as a Division by Zero), then it will throw the error to evaluateExpression which will go to Error Module.
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
