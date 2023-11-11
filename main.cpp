#include <iostream>
#include <string>
#include "tokenizer.h"

using namespace std;

int main(){
    string UserInput;

    cout << "Enter you expression: ";
    cin >> UserInput;

    tokenizer_input(UserInput);

    return 0;
}