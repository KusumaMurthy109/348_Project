#include <iostream>
#include <vector>
#include <sstream>
#include "tokenizer.h"

using namespace std;

void tokenizer_input(const string& UserInput)
{
    vector<string> tokenizer_vector;
    for (int i = 0; i < UserInput.length(); i++){

        if ((UserInput[i] == ' ') || (UserInput[i] == '\0')){
            continue;
        }





        else if ((UserInput[i] == '0' || UserInput[i] == '1' || UserInput[i] == '2' || UserInput[i] == '3' || UserInput[i] == '4' || UserInput[i] == '5' || UserInput[i] == '6' || UserInput[i] == '7' || UserInput[i] == '8' || UserInput[i] == '9')){
            if((UserInput[i + 1] != '\0') and (UserInput[i+1] != ' ') and (UserInput[i+1] == '0' || UserInput[i+1] == '1' || UserInput[i+1] == '2' || UserInput[i+1] == '3' || UserInput[i+1] == '4' || UserInput[i+1] == '5' || UserInput[i+1] == '6' || UserInput[i+1] == '7' || UserInput[i+1] == '8' || UserInput[i+1] == '9')){
                    int j = 0;
                    int k = i;
                    while ((UserInput[k] != '\0') and (UserInput[k] != ' ') and (UserInput[k] == '0' || 
                    UserInput[k] == '1' || UserInput[k] == '2' || UserInput[k] == '3' || 
                    UserInput[k] == '4' || UserInput[k] == '5' || UserInput[k] == '6' || 
                    UserInput[k] == '7' || UserInput[k] == '8' || UserInput[k] == '9')){
                        j++;
                        k++;
                    }

                    tokenizer_vector.push_back(UserInput.substr(i, j));

                    i = i+ j -1;
            }
            else if ((UserInput[i] == ' ') || (UserInput[i] == '\0')){
                continue;
            }

            else{
                tokenizer_vector.push_back(UserInput.substr(i, 1));
            }
        }


        else if(UserInput[i] == '('){
            if((UserInput[i + 1] != '\0') and (UserInput[i+1] == '-' )){
                    tokenizer_vector.push_back(UserInput.substr(i, 1));
                    int j = 0;
                    int k = i + 1;
                    while ((UserInput[k] != '\0') and ((UserInput[k] != ')' || UserInput[k] != '(' || UserInput[k] != '+' || UserInput[k] != '-' || UserInput[k] != '*' || UserInput[k] != '/' || UserInput[k] != '%'))){
                        j++;
                        k++;
                    }

                    tokenizer_vector.push_back(UserInput.substr(i+1, j - 1));

            i = i + j - 1;
            }

            else{
                tokenizer_vector.push_back(UserInput.substr(i, 1));
            }

        }


        /* 
        works for negative sybmols but when you input 12+(-2(3)) it gives you:
        12
        +
        (
        -2(3)
        )

        we want:
        12
        +
        (
        -2
        (
        3
        )
        )
        */

        else if((UserInput[i] != '\0') and (UserInput[i] == '-' )){
            int j = 0;
            int k = i + 1;
            while ((UserInput[k] != '\0') and ((UserInput[k] != ')' || UserInput[k] != '(' || UserInput[k] != '+' || UserInput[k] != '-' || UserInput[k] != '*' || UserInput[k] != '/' || UserInput[k] != '%'))){
                j++;
                k++;
            }

            tokenizer_vector.push_back(UserInput.substr(i+1, j - 1));

            i = i + j - 1;
        }



        else{
            tokenizer_vector.push_back(UserInput.substr(i, 1));
        }



    }


    //Iterates through the vector and shows what is stored inside of it, th sis only for the purpose of testing our code
    for (int i = 0; i < tokenizer_vector.size(); i ++){
        cout << tokenizer_vector[i] << endl;
    }
}





































































/*First Version with sstream*/
/*
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class Tokenizer {
public:
    Tokenizer(const std::string& expression) : expression(expression) {}

    // Function to convert the user's string expression into tokens
    std::vector<std::string> tokenize() {
        std::vector<std::string> tokens;
        std::istringstream iss(expression);

        // Tokenizing based on spaces
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        return tokens;
    }

    // Function to convert the user's string expression into valid numeric values
    std::vector<double> convertToNumericValues() {
        std::vector<std::string> tokens = tokenize();
        std::vector<double> numericValues;

        for (const std::string& token : tokens) {
            try {
                // Attempt to convert the token to a numeric value
                size_t pos;
                double numericValue = std::stod(token, &pos);

                // Ensure the entire token is converted to a numeric value
                if (pos == token.length()) {
                    numericValues.push_back(numericValue);
                } else {
                    // Token contains non-numeric characters
                    std::cerr << "Error: Invalid token - " << token << std::endl;
                }
            } catch (const std::invalid_argument&) {
                // Token cannot be converted to a numeric value
                std::cerr << "Error: Invalid token - " << token << std::endl;
            }
        }

        return numericValues;
    }

private:
    std::string expression;
};

int main() {
    std::string userExpression;
    std::cout << "Enter a mathematical expression: ";
    std::getline(std::cin, userExpression);

    // Create a Tokenizer object and tokenize/convert the expression
    Tokenizer tokenizer(userExpression);
    std::vector<double> numericValues = tokenizer.convertToNumericValues();

    // Display the numeric values obtained from the expression
    std::cout << "Numeric Values: ";
    for (double value : numericValues) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}

*/

/*Another version

#include <iostream>
#include <string>
#include <vector>

class Tokenizer {
public:
    // Constructor that initializes the Tokenizer with the user's expression
    Tokenizer(const std::string& expression) : expression(expression) {}

    // Function to convert the user's string expression into tokens
    std::vector<std::string> tokenize() {
        std::vector<std::string> tokens;  // Vector to store the tokens
        std::string currentToken;  // Variable to store the current token being formed

        // Loop through each character in the expression
        for (char c : expression) {
            if (isWhitespace(c)) {
                // Whitespace encountered, add current token if not empty
                if (!currentToken.empty()) {
                    tokens.push_back(currentToken);
                    currentToken.clear();  // Clear the current token for the next one
                }
            } else {
                // Append character to current token
                currentToken.push_back(c);
            }
        }

        // Add the last token if not empty
        if (!currentToken.empty()) {
            tokens.push_back(currentToken);
        }

        return tokens;  // Return the vector of tokens
    }

    // Function to convert the user's string expression into valid numeric values
    std::vector<double> convertToNumericValues() {
        std::vector<std::string> tokens = tokenize();  // Tokenize the expression
        std::vector<double> numericValues;  // Vector to store the numeric values

        // Loop through each token obtained from the expression
        for (const std::string& token : tokens) {
            try {
                // Attempt to convert the token to a numeric value
                size_t pos;
                double numericValue = std::stod(token, &pos);

                // Ensure the entire token is converted to a numeric value
                if (pos == token.length()) {
                    numericValues.push_back(numericValue);
                } else {
                    // Token contains non-numeric characters
*/