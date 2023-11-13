//tokenizer.cpp
#include <iostream>
#include <vector>
#include <sstream>
#include "tokens.h"

using namespace std;

void tokenizer_input(const string& UserInput)
{
    vector<string> tokenizer_vector;
    for (int i = 0; i < UserInput.length(); i++){

        //only accomidating if there is a space at index 0 ,but its not working for the rest of the test cases
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