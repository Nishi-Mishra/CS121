#include <iostream>
#include "MyString.h"
using std::cout, std::endl;

int main() {
    cout << "--- Running Mars Rover tester file ---" << endl;

    //MyString s = MyString();  
    //cout << s.size() << endl; 
    //const char* sequence = new char[6]{ 'h', 'o', 'w', 'd', 'y', '\0' };
    //MyString source = sequence;
    //cout << source << endl;  
    //MyString input = source;
    //cout << input << endl; 
    //const char* input_data = input.data(); 
    //cout << input_data << endl; 
    //delete [] sequence; 

    //const char* newstr = new char[2]{ 'c', '\0'};
    //MyString newc = MyString(newstr); // MyString: copy constructor
    //cout << "String : " << newc << endl; 
    //delete [] newstr;

    MyString str = "Sair";
                  //0123456789
    str += "hi"; 
    std::cout << str << std::endl;
    cout << "Size: " << str.size() << endl; 
    /*size_t ind = str.find("Sair");  
    cout << "Index found: " << ind << endl; */

    /*str.resize(20); 
    cout << "String: " << str << ": Cap : " << str.capacity() << " Size: " << str.size() << endl;
    str.clear();
    cout << "Cleared str:" << str << ":" << endl;*/

    //MyString comp = "hello"; 
    //MyString comp2 = "hello world";
    //MyString comp3 = comp + comp2;  
    //cout << "Bool : " << (comp == comp2) << endl; 
    //cout << comp3 << endl; 


    return 0;
}