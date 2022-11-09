#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include "parallel_tracks.h"

using std::string; using std::getline; using std::ifstream; using std::stringstream; using std::cout; using std::endl; 

bool goodCountry(string country) {
	for (char c : country)
		if (!isalpha(c) || !isupper(c)) // it isn't a letter or it isn't uppercase 
			return false;
	return true; 
}

bool goodNum(unsigned int number) { // test this function -- yep works perfect 
	int count = 0; 
	while (number != 0)
	{                  //  end of 1     2     3   
		number /= 10; // 123 --> 12 --> 1 --> 0 (3 digits) 
		count++; 

		if (count > 2)
			return false; 
	}
	return true; 
}

bool goodName(string name) {
	//cout << "Name: " << name << endl; 
	if (name.length() <= 1)
		return false;
	for (char c : name)
		if (!isalpha(c) && !isspace(c)) // not a space & not a letter
			return false; 
	return true; 
}

 
void printArr(const double arr[]) { 
	for (unsigned int i = 0; i < SIZE; i++) {
		cout << arr[i] << " ";
	}
	cout << endl; 
}

void printArr(unsigned int arr[]) {
	for (unsigned int i = 0; i < SIZE; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

//-------------------------------------------------------
// Name: get_runner_data
// PreCondition:  the prepped parallel arrays , and a legit filename is pass
// PostCondition: all arrays contain data from the csv file given
//---------------------------------------------------------
void get_runner_data( const std::string& file, double timeArray[], std::string countryArray[], 
		unsigned int numberArray[], std::string lastnameArray[]) 
{
  //TODO
	// takes in the fileName! not the file as a string 
	string fileLine = ""; 
	ifstream ifstrm1(file);
	ifstream ifstrm2(file); 
	//std::stringstream ss;   
	
	// If the file fails to open, throw an invalid_argument exception with message: “Cannot open file” 

	if (file.length() < 5 || file.substr(file.length() - 3, file.length()) != "txt" || !ifstrm1.is_open() || !ifstrm2.is_open()) // shortest fileName is g.txt 5 chars 
		throw std::invalid_argument("Cannot open file"); 


	while (getline(ifstrm2, fileLine)) {
		//cout << "File line : " << fileLine << " Length: " << fileLine.length() << endl;
		if (fileLine.length() < 3) 
			throw std::domain_error("File missing data");
	}

	// throw an domain_error exception with message: “File contains invalid data” followed by which piece of data is invalid {time, country, number, name}:
	unsigned int i = 0;

	while (!ifstrm1.eof() && ifstrm1.good() && i < SIZE) {
	
		ifstrm1 >> timeArray[i];
		// cout << "Time array: " << timeArray[i] << endl; 
		if (!ifstrm1.good() || timeArray[i] <= 0) {
			//cout << "Time: " << timeArray[i] << endl;
			throw std::domain_error("File contains invalid data (time)");
		}
			
		// must be a floating point num & be non-zero positive number 
		
		ifstrm1 >> countryArray[i]; // stream can't fail here
		// cout << "Country array: " << countryArray[i] << endl;
		if (countryArray[i].length() != 3 || !goodCountry(countryArray[i])) // create a function to check if alphabet exists or not 
			throw std::domain_error("File contains invalid data (country)"); 
		// Contains only capital letters ‘A’ - ‘Z’;  Contains exactly 3 characters;  Note that an empty string is not valid

		ifstrm1 >> numberArray[i];
		if (!ifstrm1.good() || !goodNum(numberArray[i]))
			throw std::domain_error("File contains invalid data (number)"); // create a func to check if contains 1 or 2 digits

		ifstrm1 >> lastnameArray[i];
		//cout << "Before good name call. " << lastnameArray[i] << endl; 
		if (!goodName(lastnameArray[i]))
			throw std::domain_error("File contains invalid data (name)"); // stream can't fail here 

		/*Contains only alphabet characters ‘A’ - ‘Z’, ‘a’ - ‘z’ and ‘ ‘ (space)
		You should trim whitespace from the beginning and end before checking for valid characters.
		Contains more than one character
		Note that an empty string is not valid
		You should trim whitespace from the beginning and end before checking if it is long enough.*/

		i++; 
	}
	
}

// I need to be able to throw specific things(say where exactly there was invalid data inputting
// after reading elements in check stream state if failed  -- then throw appropriate exception 
// dd another check to see if three letters were given for the country and if letters were given to 

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  a double arrays is pass in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_double_array(double ary[])
// making sure all values within the array are set to 0.0;
{
  //TODO
	for (unsigned int i = 0; i < SIZE; i++) {
		ary[i] = 0.0; 
	}
}

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  a double arrays is pass in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_unsigned_int_array(unsigned int ary[])
// making sure all values within the array are set to 0;
{
	//TODO
	for (unsigned int i = 0; i < SIZE; i++) {
		ary[i] = 0;
	}
}

//-------------------------------------------------------
// Name: prep_string_array
// PreCondition:  a string arrays is pass in
// PostCondition: data in the array is "N/A" out to determine if
// a value has changed
//---------------------------------------------------------
void prep_string_array(std::string ary[])
// making sure all values within the array are set to "N/A";
{
	//TODO
	for (unsigned int i = 0; i < SIZE; i++) {
		ary[i] = "N/A";
	}
}

//-------------------------------------------------------
// Name: get_ranking
// PreCondition:  just the time array is passed in, and has valid data
// PostCondition: after a very inefficient nested loop, determine the placements 
// and places the ranks in a new array. That new array is returned
//---------------------------------------------------------
void get_ranking(const double timeArray[], unsigned int rankArray[])
{
	//TODO
	/*cout << "Time array: " << endl; 
	printArr(timeArray); 
	cout << "Rank array: " << endl;
	printArr(rankArray); 
	cout << endl; */
	int count; 
	for (unsigned int j = 0; j < SIZE; j++) {
		count = 1;  // first rank (nothing less than itself) 
		for (unsigned int i = 0; i < SIZE; i++) {
			
			if (timeArray[j] > timeArray[i]) // count whichever ones are smaller than the current one 
				count++;
			 
		}
		/*printArr(rankArray);
		cout << endl;*/
		rankArray[j] = count; 
	}
	//cout << "Time array: "; 
	//double timeA[SIZE]; 
	//for (unsigned int i = 0; i < SIZE; i++) {
	//	timeA[i] = timeArray[i]; 
	//	rankArray[i] = i + 1; 
	//	//cout << timeArray[i] << " "; 
	//}

	//cout << endl; 
	 
	// try to loop through; find the min and then switch place 0 with whichever place min is 
	// then loop thru 1 to size
	//double min; 
	//double temp1; // for holding a time 
	//int temp2; // for holding a rank 

	//for (unsigned int outer = 0; outer < SIZE; outer++) {
	//	min = timeA[outer];
	//	for (unsigned int inner = outer + 1; inner < SIZE; inner++) { // outer + 1 bc min is already = outer index 
	//		if (min > timeA[inner]) {
	//			temp1 = min; // old min goes into temp 
	//			temp2 = rankArray[outer]; 

	//			min = timeA[inner]; // min is reassigned correctly 

	//			rankArray[outer] = rankArray[inner]; // new rank 
	//			timeA[outer] = min; // new min  

	//			rankArray[inner] = temp2; 
	//			timeA[inner] = temp1; 

	//			cout << "Time array: ";
	//			printArr(timeA);

	//			cout << "Rank array: ";
	//			printArr(rankArray);

	//			cout << endl; 

	//		}
	//	}
	//}

	// time array is now in order
	// do a loop through the timeArray and find where the time min is within time (sorted)  
	// that index is now the value in rank array 

	/*for (unsigned int unsorted = 0; unsorted < SIZE; unsorted++) {
		for (unsigned int sorted = 0; sorted < SIZE; sorted++) {
		}
	}*/

	// cout << endl; 


	/*cout << "Final Rank array: ";
	printArr(rankArray);*/

}
    
// 10 5 2 3 1 
// min = 10 inner = 1 
// min = 5 temp = 10  10 5 2 3 1  ---> ind[0
//         


//-------------------------------------------------------
// Name: print_results
// PreCondition:  almost all parallel arrays are passed in and have valid data
// PostCondition: after a very inefficient nested loop to determine the ranks
// it then displays then along with a delta in time from the start
//---------------------------------------------------------
void print_results(const double timeArray[], const std::string countryArray[],
		const std::string lastnameArray[], const unsigned int rankArray[])
{

	std::cout << "Final results!!";
	std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::endl;
	double best_time = 0.0;
		
	// print the results, based on rank, but measure the time difference_type
	for(unsigned int j = 1; j <= SIZE; j++)
	{
		
		// go thru each array, find who places in "i" spot
		for(unsigned int i = 0; i < SIZE; i++)
		{
			if(rankArray[i] == 1) // has to be a better way, but need the starting time
			{
				best_time = timeArray[i];
			}
			
			
			if(rankArray[i] == j) // then display this person's data
			{
				// this needs precision display
				std::cout << "[" << j << "]  " << timeArray[i] << " " << std::setw(15) << std::left << lastnameArray[i] << "\t" << "(" << countryArray[i] << ")  +" << (timeArray[i] - best_time) << std::endl; 
			}
			
		}
	}	
}

std::string trim(const std::string word) {
	string ret = word;

	// remove whitespace from the beginning
	while (!ret.empty() && isspace(ret.at(0))) {
			ret.erase(0, 1);
		}

	// remove whitespace from the end
	//  Note: last index is (.size() - 1) due to 0 based indexing
	while (!ret.empty() && isspace(ret.at(ret.size()-1))) {
		ret.erase(ret.size()-1, 1);
	}
	
	return ret;
}