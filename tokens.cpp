/*
Name: tokens.cpp
Authors: Kusuma Murthy, Nimra Syed, Reeny Huang
Date: 11/08/2023
Last modified: 11/19/2023
Purpose: To create a Tokenizer Module that takes in the user's string expression and makes it into an evaluatable vector expression.
*/

#include <iostream>
#include <vector>
#include <sstream>
#include "Tokens.h"

using namespace std;

vector<string> Tokens::tokenizer_input(const string &UserInput)
/*
This function takes in user's expression as a string and separates it into a vector expression that is then passed to the Parser Module.
*/

{
    vector<string> tokenizer_vector; // Initializes a vector string named tokenizer_vector that will be returned after separation.
    for (unsigned int i = 0; i < UserInput.length(); i++) // Iterates through each index of the string (character) one by one.
    {

        // If there a number greater than 1 digit.
        if ((UserInput[i] == '0' || UserInput[i] == '1' || UserInput[i] == '2' || UserInput[i] == '3' || UserInput[i] == '4' || UserInput[i] == '5' || UserInput[i] == '6' || UserInput[i] == '7' || UserInput[i] == '8' || UserInput[i] == '9' || UserInput[i] == '.')) // Checks if index i of the string is a digit including a decimal.
        {
            if ((UserInput[i + 1] != '\0') && (UserInput[i + 1] != ' ') && (UserInput[i + 1] == '0' || UserInput[i + 1] == '1' || UserInput[i + 1] == '2' || UserInput[i + 1] == '3' || UserInput[i + 1] == '4' || UserInput[i + 1] == '5' || UserInput[i + 1] == '6' || UserInput[i + 1] == '7' || UserInput[i + 1] == '8' || UserInput[i + 1] == '9' || UserInput[i + 1] == '.')) // Checks if the following index i + 1 is a digit or a decimal and not a zero or a space.
            {
                int j = 0; // Initialize j as 0.
                int k = i; // Initialize k as the current index i.
                // Checks if the current index is a digit or a decimal and keep track of the length of this string.
                while ((UserInput[k] != '\0') && (UserInput[k] == '0' ||
                                                  UserInput[k] == '1' || UserInput[k] == '2' || UserInput[k] == '3' ||
                                                  UserInput[k] == '4' || UserInput[k] == '5' || UserInput[k] == '6' ||
                                                  UserInput[k] == '7' || UserInput[k] == '8' || UserInput[k] == '9' || UserInput[k] == '.'))
                {
                    j++; // Increment j.
                    k++; // Increment k.
                }

                tokenizer_vector.push_back(UserInput.substr(i, j)); // Add this substring of number to the vector.

                i = i + j - 1; // Set i to the current index after the substring.
            }

            else
            {
                tokenizer_vector.push_back(UserInput.substr(i, 1)); // If it is not a number more than one digit, add it to the vector. 
            }
        }

        // If there is  a '-' or '+' at index 0 eg: '-1+2' or '+5-4'
        else if ((UserInput[i] != '\0') && (i == 0) && (UserInput[i] == '-' || UserInput[i] == '+')) // Checks if the first index (0) is a '-' or '+'.
        {
            // If the number is greater than 1 digit.
            if ((UserInput[i + 1] != '\0') && (UserInput[i + 1] == '0' || UserInput[i + 1] == '1' || UserInput[i + 1] == '2' || UserInput[i + 1] == '3' || UserInput[i + 1] == '4' || UserInput[i + 1] == '5' || UserInput[i + 1] == '6' || UserInput[i + 1] == '7' || UserInput[i + 1] == '8' || UserInput[i + 1] == '9' || UserInput[i + 1] == '.')) // Checks if the following index is a digit or a decimal.
            {
                int j = 1;     // Initialize j as 1.
                int k = i + 1; // Initialize k as i + 1.
                // Checks if the current k is a digit or a decimal and keep track of the number string length.
                while ((UserInput[k] != '\0') && (UserInput[k] == '0' ||
                                                  UserInput[k] == '1' || UserInput[k] == '2' || UserInput[k] == '3' ||
                                                  UserInput[k] == '4' || UserInput[k] == '5' || UserInput[k] == '6' ||
                                                  UserInput[k] == '7' || UserInput[k] == '8' || UserInput[k] == '9' || UserInput[k] == '.'))
                {
                    j++; // Increment j.
                    k++; // Increment k.
                }

                tokenizer_vector.push_back(UserInput.substr(i, j)); // Add this substring of number to the vector.

                i = i + j - 1; // Set i to the current index after substring.
            }

            else
            {
                tokenizer_vector.push_back(UserInput.substr(i, 1)); // If it is not a number more than one digit, add it to the vector. 
            }
        }

        // If there is negative numbers inside of a parentheses.
        else if (UserInput[i] == '(') // Checks for Parentheses.
        {
            if ((UserInput[i + 1] != '\0') && (UserInput[i + 1] == '-' || UserInput[i + 1] == '+')) // Checks for '-' and '+' in the following index.
            {
                tokenizer_vector.push_back(UserInput.substr(i, 1)); // Add the parentheses to the vector.
                if ((UserInput[i + 2] != '\0') && (UserInput[i + 2] == '0' || UserInput[i + 2] == '1' || UserInput[i + 2] == '2' || UserInput[i + 2] == '3' || UserInput[i + 2] == '4' || UserInput[i + 2] == '5' || UserInput[i + 2] == '6' || UserInput[i + 2] == '7' || UserInput[i + 2] == '8' || UserInput[i + 2] == '9' || UserInput[i + 2] == '.')) // Checks if there is a number (digit or a decimal).
                {
                    int j = 1;      // Initialize j to 1.
                    int k = i + 2;  // Initialize k to i + 2.
                    // Checks if the current k is a digit or a decimal and keep track of the number string length.
                    while ((UserInput[k] != '\0') && (UserInput[k] == '0' ||
                                                      UserInput[k] == '1' || UserInput[k] == '2' || UserInput[k] == '3' ||
                                                      UserInput[k] == '4' || UserInput[k] == '5' || UserInput[k] == '6' ||
                                                      UserInput[k] == '7' || UserInput[k] == '8' || UserInput[k] == '9' || UserInput[k] == '.'))
                    {
                        j++; // Increment j.
                        k++; // Increment k.
                    }

                    tokenizer_vector.push_back(UserInput.substr(i + 1, j)); // Add this substring of number to the vector.

                    i = i + j; // Set i to the current index after substring.
                }
            }

            else
            {
                tokenizer_vector.push_back(UserInput.substr(i, 1)); // If it is not a number following, add the parentheses to the vector. 
            }
        }

        // Accounts for inputs which 2 consecutive symbols, eg: 1++3 or +2^-3
        else if (UserInput[i] == '+' || UserInput[i] == '-' || UserInput[i] == '*' ||
                 UserInput[i] == '^' || UserInput[i] == '%' || UserInput[i] == '/') // Checks for operands.
        {
            if ((UserInput[i + 1] != '\0') && (UserInput[i + 1] == '-' || UserInput[i + 1] == '+')) // Checks if the next index is a '-' or '+'.
            {
                tokenizer_vector.push_back(UserInput.substr(i, 1)); // Add the operand to the vector.
                if ((UserInput[i + 2] != '\0') && (UserInput[i + 2] == '0' || UserInput[i + 2] == '1' || UserInput[i + 2] == '2' || UserInput[i + 2] == '3' || UserInput[i + 2] == '4' || UserInput[i + 2] == '5' || UserInput[i + 2] == '6' || UserInput[i + 2] == '7' || UserInput[i + 2] == '8' || UserInput[i + 2] == '9' || UserInput[i + 2] == '.')) // Checks if there is a number (digit or a decimal).
                {
                    int j = 1;      // Initialize j to 1.
                    int k = i + 2;  // Initialize k to i + 2.
                    // Checks if the current k is a digit or a decimal and keep track of the number string length.
                    while ((UserInput[k] != '\0') && (UserInput[k] == '0' ||
                                                      UserInput[k] == '1' || UserInput[k] == '2' || UserInput[k] == '3' ||
                                                      UserInput[k] == '4' || UserInput[k] == '5' || UserInput[k] == '6' ||
                                                      UserInput[k] == '7' || UserInput[k] == '8' || UserInput[k] == '9'))
                    {
                        j++; // Increment j.
                        k++; // Increment k.
                    }

                    tokenizer_vector.push_back(UserInput.substr(i + 1, j)); // Add this substring of number to the vector.

                    i = i + j; // Set i to the current index after substring.
                }

                if ((UserInput[i + 1] != '\0') && (UserInput[i + 1] == '-' || UserInput[i + 1] == '+')) // Checks if the index following the operand is another operand.
                {

                    if (UserInput[i + 1] == '-') // Checks if the next index is '-'.
                    {
                        tokenizer_vector.push_back("-1"); // If so, add "-1" to the vector.
                        tokenizer_vector.push_back("*");  // Add "*" to the vector.
                        i = i + 1; // Set i to the current, new index after accounting for the '-'.
                    }
                }
            }

            else
            {
                tokenizer_vector.push_back(UserInput.substr(i, 1)); // If it is not another operand following, add the operand to the vector. 
            }
        }

        // Appends to the vector if all the above statments is false.
        else
        {
            tokenizer_vector.push_back(UserInput.substr(i, 1)); // Add the index of the string to the vector.
        }
    }

    // Iterates through the vector and shows what is stored inside of it, th sis only for the purpose of testing our code
    /*
       for (int i = 0; i < tokenizer_vector.size(); i ++){
           cout << tokenizer_vector[i] << endl;
       }
   */

    return tokenizer_vector; // After iterating through the user string, return the vector.
}