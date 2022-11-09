#include <iostream>
#include "functions.h"

using std::cout, std::endl;

bool is_valid_range(int a, int b) {
	// TODO(student): validate input range
	// 10 <= a <= b < 10000 is the valid range 
	if ( 10 <= a && a <= b && b < 10000) {
		return true; 
	}
	return false;
}

char classify_mv_range_type(int number) {
	// TODO(student): return 'M' if number has /\/\... pattern,
	// return 'V' if number has \/\/ pattern, and return 'N' otherwise
	
	// int orig_num = number; // for preservation purposes -- this was for debugging but this produces a warning 
	
	/*
		1. number <-- 8675309
		2. while number is not 0 do
		3.   digit <-- remainder after dividing number by 10
		4.   number <-- number divided by 10
		5. end
	*/

	bool high1 = 0;
	bool high2 = 0; 

	// test is the number pair small then big --> high = true
	// 						or big then small --> high = false 
	// if we have two highs or two lows that is problematic and auto return N 
	// keep reassigning high1 & high2 as you slowly go across the full number; 
	// if the last one is high2 is high it is a valley, else it is a mountain 
	// theoretically should work? hopefully 

	int digit1 = number % 10; // 1 
	number /= 10; // prepare for peeling numbers off the end -- example we are working with: 12151 

	int digit2 = -1;  
	int iterator = 0; // counts where we are in the loop of digits; numDigits = iterator + 1 at the end     
	while (number != 0) { // num = 1215 
		// cout << " iterator: " << iterator << endl << " number: " << number << " the high2 is " << high2 << " & high1 is " << high1 << " digit1: " << digit1 << " digit2: " << digit2 << endl; 
		if (iterator >= 1) { // this part has been moved so many times!!! PREP MUST OCCUR -- figure out when pls 
			high2 = high1; // prep for next iteratation and everything is going fine 
			digit1 = digit2;  // these are opposites bc they get initialized at different times unfortunately -- DONT CHANGE (unless you must) 
		}
		

		digit2 = number % 10; // 5 
		number /= 10;

		// assign high1 and high2 
		if (digit2 > digit1) // true 
			high1 = true;
		else if (digit2 < digit1)
			high1 = false; 
		else
			return 'N'; 
			//they equal


		// do a check for the 'high's 
		if (iterator >= 1) {
			if (high1 == high2) {
				// cout << "returning N"; 
				return 'N'; // this means both are either sloping upwards or downwards and that is a nope  
			}	
		}

		iterator++;  
		// cout << " iterator: " << iterator << " number: " << number << " the high2 is " << high2 << " & high1 is " << high1 << " digit1: " << digit1 << " digit2: " << digit2 << endl; 

	} // end of while  
	
	// cout << "" << endl; // just to get a space before the debugs 

	if (iterator == 1) {
		// the number is only two digits then high2 was never even changed from initialization and that is unhelpful to compare 
		if (high1 == true) {
			// cout << orig_num << " is considered a valley" << endl; 
			return 'V';
		}	
		else {
			// cout << orig_num << " is considered a mountain" << endl; 
			return 'M'; 
		}
			
	} else if (iterator > 1) {
		if (high1 == true) {
			// cout << orig_num << " is considered a valley" << endl; 
			return 'V';
		}
		else {
			// cout << orig_num << " is considered a mountain and the iterator says " << iterator 
				// << " the high2 is " << high2 << " & high1 is " << high1 << endl; 
			return 'M'; 
		}
			
	}


	return '-'; // ask why this no work and also how did it get through every return statement before this ?? 
}

void count_valid_mv_numbers(int a, int b) {
	// TODO(student): count the number of valid mountain ranges and valley
	// ranges in the range [a, b] and print out to console using the format
	// in Requirement 4 of the homework prompt

	// output format: There are 753 mountain ranges and 351 valley ranges between 1234 and 4321.↵

	int valleyCount = 0; int mountCount = 0; int neitherCount = 0; 
	char numType; 

	for (int i = a; i <= b; i++) {
		numType = classify_mv_range_type(i); 

		if (numType == 'V')
			valleyCount++;
		else if (numType == 'M')
			mountCount++; 
		else if (numType == 'N')
			neitherCount++; 
	}

	cout << "There are " << mountCount <<" mountain ranges and " << valleyCount << " valley ranges between " << a << " and " << b << "." << endl; 

}