/******************************************************************************

File: main.cpp
Author: Prof. Lupoli & Andrew Nemec
Date: 2/16/2021
Section: 
E-mail: slupoli@tamu.edu
Description:
This file contains C++  code that will simulate data collected from a track 
event with 9 lanes. The code will sort the order, then display the results

Updates
Author: J. Michael Moore & Paul Taele

Data File Information
name: data.csv
content: The csv file will contain data in the constant form of:
<Time (double)> <Abbreviated Country (String)> <Uniform number (int)> <Lastname (String)>
32.7 USA 12 Moore
36.5 RUS 35 Polsley
45.8 ENG 73 Teale
52.34 CHN 14 Nemec
76.45 ITY 23 Lupoli     

*******************************************************************************/

#include <iostream>
#include "parallel_tracks.h"
#include <fstream>

using std::cin; using std::cout; using std::endl;
using std::string; using std::getline; using std::ifstream;
using std::invalid_argument; using std::domain_error;

int main()
{
    // TODO: create arrays needed
    double timeArray[SIZE]; 
    string countryArray[SIZE];
    unsigned int numberArray[SIZE];
    string lastnameArray[SIZE]; 
    unsigned int rankArray[SIZE];
	
    // TOTO: prep all arrays
    prep_double_array(timeArray); 
    prep_string_array(countryArray);
    prep_unsigned_int_array(numberArray);
    prep_string_array(lastnameArray); 
    prep_unsigned_int_array(rankArray);

    
    // TODO: prompt until both the file and the contained data are valid
    
    //string fileName = "good_data01.txt";
    //string fileName = "bad_missing02.txt";
    //

    /*try {
        file.open(fileName); 
        if (file.isOpen())
            throw invalid_argument("Invalid file name"); 
    }
    catch {

    }*/

    /*int num = 0; 
    while (cin >> num && num != -1) 
        cout << "Good num function: " << goodNum(num) << endl << endl;*/


    //THIS IS REQUIRED !!! -------------------------------------------> 
    string fileName = ""; 
    
    //bool done = false; // the try and file validation is supposed to happen in main() 
    //while (!done) {
    //    cout << "Enter file name: ";
    //    cin >> fileName;
    //    
    //    //cout << "File name: " << fileName << endl;
    //    //cout << "File name substr: " << fileName.substr(fileName.length()-3, fileName.length()) << endl;

    //    try {
    //        ifstream fileStream(fileName);
    //        if (fileName.length() < 5 || fileName.substr(fileName.length() - 3, fileName.length()) != "txt" || !fileStream.is_open()) // shortest fileName is g.txt 5 chars 
    //            throw invalid_argument("Cannot open file");
    //        else
    //            done = true;
    //    } catch (invalid_argument & err){
    //        cout << "Invalid File: " << err.what() << endl;
    //    }
    //}
    bool done = false; 
    while (!done) {
        try {
            string fileName = "";
            cout << "Enter file name: ";
            cin >> fileName;
            get_runner_data(fileName, timeArray, countryArray, numberArray, lastnameArray);
            done = true; 
        } 
        catch (invalid_argument &err) {
            cout << "Invalid File: " << err.what() << endl;

        }
        catch (domain_error& err) { 
            cout << "Invalid File: " << err.what() << endl;
        }

    }
    
    //double tArray [] = {97.831, 38.3608, 60.8176, 77.5583, 71.9368, 53.3277, 46.9393, 74.7743, 64.1635};
    get_ranking(timeArray, rankArray); 
    print_results(timeArray, countryArray, lastnameArray, rankArray);
    cout << endl; 

    
    
    
    /*cout << "CountryArray: "; 
    for (unsigned int i = 0; i < SIZE; i++) {
        cout << countryArray[i] << " ";
    }
    cout << endl << endl;
    
    cout << "Time Array: ";
    for (unsigned int i = 0; i < SIZE; i++) {
        cout << timeArray[i] << " ";
    }
    cout << endl << endl;

    cout << "Number Array: ";
    for (unsigned int i = 0; i < SIZE; i++) {
        cout << numberArray[i] << " ";
    }
    cout << endl << endl;

    cout << "Name Array: ";
    for (unsigned int i = 0; i < SIZE; i++) {
        cout << lastnameArray[i] << " ";
    }
    cout << endl << endl;*/

    // TODO: determine ranking, notice the rank array receives the results
    
    // TODO: Output results

    return 0;
}

