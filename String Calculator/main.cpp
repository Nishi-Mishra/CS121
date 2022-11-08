#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"

using std::cout, std::endl, std::cin;
using std::string;

int main() {
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
 
    string lhs; 
    char oper; 
    string rhs; 
    string ans; 
    string inp;  

    cin >> inp;  

    while (cin.good() && (inp != "quit" && inp != "q")) {
        lhs = inp; 
        cin >> oper; 
        if (oper == 'q') {
            break;
        }
        cin >> rhs; 
        if (rhs == "q" || rhs == "quit") {
            break; 
        }

        if (oper == '+') {
            ans = add(lhs, rhs); 
            cout << ">> " << endl << "ans =\n\n    " << ans << endl << endl;
        }
        else if (oper == '*') {
            ans = multiply(lhs, rhs); 
            cout << ">> " << endl << "ans =\n\n    " << ans << endl << endl;
        } else {}

        cin >> inp; 
    }

    cout << ">>" << "\nfarvel!" << endl; 
    // cout << add("-4383", "-483") << endl;
    // TODO(student): implement the UI
}

