#include <iostream>
#include <string>
#include <sstream>
#include "CellDatabase.h"
#include "CellData.h"
#include <fstream>

using std::cout;
using std::vector; 
using std::string; 
using std::fstream;
using std::ofstream;
using std::endl;

// Default constructor/destructor. Modify them if you need to.
CellDatabase::CellDatabase() {}
CellDatabase::~CellDatabase() {}

vector<string> CellDatabase::inspectLine(string line) {

    vector<std::string> data; // add the elements 

    //cout << "Current line: " << line << endl;

    std::stringstream ss (line); 

    string temp; 

    while (ss.good()) { 
        getline(ss, temp, ',');
        data.push_back(temp);   
    }

    if (data.size() != 9)
        throw std::invalid_argument("This line has too many or too few arguments, size is : " + std::to_string(data.size()));

    bool foundDecimal = false; 

    int incr = 0; 
    for (string s : data) { 
        // cout << "-" << s << "-" << endl; // ----- uncomment if you wanna see which one fails 
        if (incr <= 1) { // the fov is an integer , only access if data.at(1) even exists 
            // cout << "in the if statement" << endl; 
            for (size_t i = 0; i < s.length(); i++) {
                if (isspace(s.at(i))) // is a space 
                    throw std::invalid_argument("Argument: " + s + " contains a space");
                if (!isdigit(s.at(i))) { // is not a digit if decimal throw 
                    throw std::invalid_argument("Argument: " + s + " contains invalid characters");
                }
            } 
        }

        else if (incr == 2) {
            foundDecimal = false;
            for (size_t i = 0; i < s.length(); i++) {
                if (isspace(s.at(i))) // is a space 
                    throw std::invalid_argument("Argument: " + s + " contains a space");

                if ((s.at(i) == '.') && foundDecimal == true)
                    throw std::invalid_argument("Argument: " + s + " contains more than one decimal point");
                else if (s.at(i) == '.')
                    foundDecimal = true;

                if (!isdigit(s.at(i)) && !(s.at(i) == '.')) { // is not a digit and not a decimal point 
                    throw std::invalid_argument("Argument: " + s + " contains invalid characters");
                }
            }
        } 
        
        else if (incr > 2) { 
            foundDecimal = false;
            for (size_t i = 0; i < s.length(); i++) {

                if (i == 0 && s.at(i) == '-')
                    continue;

                if (isspace(s.at(i))) // is a space 
                    throw std::invalid_argument("Argument: " + s + " contains a space");

                if ((s.at(i) == '.') && foundDecimal == true)
                    throw std::invalid_argument("Argument: " + s + " contains more than one decimal point");
                else if (s.at(i) == '.')
                    foundDecimal = true;

                if (!isdigit(s.at(i)) && !(s.at(i) == '.')) { // is not a digit and not a decimal point 
                    throw std::invalid_argument("Argument: " + s + " contains invalid characters " + std::to_string(incr));
                }
            }
        }

        incr++;
        
    }

    return data;
}


void CellDatabase::loadData(const string& filename) 
{
    // Implement this function
    // columns are : id,fov,volume,center_x,center_y,min_x,max_x,min_y,max_y 
    std::ifstream file(filename);
    
    if (file.is_open()) {
        string id;
        int fov;
        double volume;
        double center_x;
        double center_y;
        double min_x;
        double max_x;
        double min_y;
        double max_y;
        
        string line;
        vector<string> data; 

        /*"Error, Invalid input : " followed by that invalid line on the
            console, and continue executing the program. Do not throw an exception. 
            A line is valid if all of the following are true :
            ▪ It consists of only id, fov, volume, center_x, center_y, min_x, max_x, 
              min_y, max_y, where each item is separated by a comma without any whitespaces.
            ▪ id consists of only number digits.
            ▪ fov is an integer.
            ▪ volume, center_x, center_y, min_x, max_x, min_y, max_y are double and
              volume is positive.
        */

        getline(file, line); // get rid of the fov line 

        while (file.good() && !file.eof()) {
            getline(file, line); // line being a string declared above 

            if (line == "")
                continue; 
            
            try {
                data = inspectLine(line);

                id = data.at(0); // already checked if only digits 
                fov = stoi(data.at(1)); // -- check if integer happened above 
                
                volume = stod(data.at(2));
                if (volume <= 0.0)
                    throw std::invalid_argument("Volume = 0");

                center_x = stod(data.at(3));
                center_y = stod(data.at(4));

                min_x = stod(data.at(5));
                max_x = stod(data.at(6));
                /*if (max_x <= min_x)
                    throw std::invalid_argument("Max is greater than min");*/ 
                
                min_y = stod(data.at(7));
                max_y = stod(data.at(8)); 
                /*if (max_y <= min_y)
                    throw std::invalid_argument("Max is greater than min");*/


                /*if (center_x < min_x || center_x > max_x)
                    throw std::invalid_argument("center is out of bounds of the min/max");
                if (center_y < min_y || center_y > max_y)
                    throw std::invalid_argument("center is out of bounds of the min/max");*/ 

                records.insert(id, fov, volume, center_x, center_y, min_x, max_x, min_y, max_y);  
            }
            catch (.../*std::invalid_argument &err*/) {
                cout << "Error, Invalid input: " << line << endl; 
                //cout << err.what() << endl; 
            }
             
        } // end of while 

    }
    else {
        cout << "Error: Unable to open" << endl; 
        return;
    }
    

}

// Do not modify
void CellDatabase::outputData(const string& filename) {
    ofstream dataout("sorted." + filename);

    if (!dataout.is_open()) 
    {
        cout << "Error: Unable to open " << filename << endl;
        exit(1);
    }
    dataout << records.print();
}

void CellDatabase::performQuery(const string& filename) 
{
    std::ifstream file(filename);

    // Implement this function
    //if (file.is_open()) {

        string currType = "";
        /*
        "Error, Invalid input: " followed by that invalid line on the console, and continue
        executing the program. Do not throw an exception. A line is valid if it is one of the following:
            ▪ AVG k, where k is a positive integer
            ▪ VAR k, where k is a positive integer
            ▪ COUNT k, where k is a positive integer
            ▪ OUTLIER k, j, N, where k and N are positive integers
        */
        string line;
        string garbage;
        std::ofstream outputfile("result.data");
        while (!file.eof()) {

            getline(file, line);

            if (line == "")
                continue;

            std::stringstream ss(line);

            ss >> currType;

            if (ss.bad() || ss.fail()) {
                outputfile << "Error, Invalid input: " << line << endl;
                // cout << currType << endl;
                continue;
            }

            if (currType == "AVG") {

                int fov;
                ss >> fov;

                if (ss.bad() || ss.fail() || fov < 0 || !ss.eof()) {
                    outputfile << "Error, Invalid input: " << line << endl;
                    // cout << fov << endl;
                    continue;
                }

                ss >> garbage;
                if (!ss.fail()) {
                    cout << "Error, Invalid input: " << line << endl;
                    continue;
                }

                double avg = records.average(fov);
                outputfile << "AVG " << fov << ": " << avg << '\n';
            }
            else if (currType == "VAR") {

                int fov;
                ss >> fov;

                if (ss.bad() || ss.fail() || fov < 0 || !ss.eof()) {
                    outputfile << "Error, Invalid input: " << line << endl;
                    // cout << fov << endl;
                    continue;
                }

                ss >> garbage;
                if (!ss.fail()) {
                    cout << "Error, Invalid input: " << line << endl;
                    continue;
                }

                double var = records.variance(fov);
                outputfile << "VAR " << fov << ": " << var << '\n';
            }
            else if (currType == "COUNT") {

                int fov;
                ss >> fov;

                if (ss.bad() || ss.fail() || fov < 0 || !ss.eof()) {
                    outputfile << "Error, Invalid input: " << line << endl;
                    // cout << fov << endl;
                    continue;
                }

                ss >> garbage;
                if (!ss.fail()) {
                    cout << "Error, Invalid input: " << line << endl;
                    continue;
                }

                double count = records.countN(fov);
                outputfile << "COUNT " << fov << ": " << count << '\n';
            }
            else if (currType == "OUTLIER") {
                int fov;
                int k; // can be negative 
                int n;

                ss >> fov;

                if (ss.bad() || ss.fail() || fov < 0 || ss.eof()) {
                    outputfile << "Error, Invalid input: " << line << endl;
                    // cout << fov << endl;
                    continue;
                }

                ss >> k;
                if (ss.bad() || ss.fail() || ss.eof()) {
                    outputfile << "Error, Invalid input: " << line << endl;
                    continue;
                }
                ss >> n;
                if (ss.bad() || ss.fail() || n < 0 || !ss.eof()) {
                    outputfile << "Error, Invalid input: " << line << endl;
                    continue;
                }

                ss >> garbage;
                if (!ss.fail()) {
                    outputfile << "Error, Invalid input: " << line << endl;
                    continue;
                }

                outputfile << "OUTLIER " << fov << " " << k << " " << n << ": " << records.outliers(fov, k, n) << "\n";
            }
            else {
                outputfile << "Error, Invalid input: " << line << endl;
                continue;
            }

        }

    /*}
    else {
        cout << "Error: Unable to open" << endl;
    }*/


}
