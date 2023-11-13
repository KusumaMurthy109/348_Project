//mian file
#include <iostream>
#include <string>
#include "tokens.h"

using namespace std;

int main(){
    string UserInput;

    cout << "Enter you expression: ";
    cin >> UserInput;

    tokenizer_input(UserInput);

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