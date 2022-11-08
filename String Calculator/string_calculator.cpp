#include <iostream>
#include <string>
#include <sstream>
#include "./string_calculator.h"

using std::cout, std::endl;
using std::string;

unsigned int digit_to_decimal(char digit) {
    // TODO(student): implement
    // ascii numbers start from 48 or you can just sutract the asccii of char '0' and get the same result 
    int retInt; 
    if (digit >= 48 && digit <= 57) {
        retInt = digit - '0';
        return retInt;
    }
    else
        throw std::invalid_argument("Not a number");

    return 0;
}

char decimal_to_digit(unsigned int decimal) {
    // TODO(student): implement
    // 7 to '7' 
    char retChar; 
    if (decimal < 10) {
        retChar = decimal + '0'; 
        return retChar; 
    }
    else {
        throw std::invalid_argument("One digit only");
    }
}

bool isNeg(string num) {
    std::istringstream inSS(num); 
    char temp;
    inSS >> temp; 
    if (temp == '-')
        return true;
    return false; 
}

string trim_leading_zeros(string num) { // RETEST THIS !! -- it was modified future me 
    // TODO(student): implement
    // trim_leading_zeros(“00123”) should return “123”
    // trim_leading_zeros(“ - 00123”) should return “ - 123”

    std::istringstream inSS(num);
    char temp; 
    string retString = ""; 
    bool done = false;
    
    inSS >> temp;

    if (isNeg(num)) // if first char is a dash it is negative and we want to preserve that 
        retString += '-';
    else {
        if (temp != '0') { // it isn't negative, so is there a leading zero? 
            retString += temp; // no zero so we add to return string 
            done = true; // we don't need to keep looking for zeros 
        }
    }

    while (!done && inSS >> temp) { // find all the leading zeros char by char 

        if (temp != '0') {
            done = true;
            retString += temp;
        }
    }

    string restofnumber; 
    inSS >> restofnumber; 
    retString += restofnumber; 
    
    //while (inSS >> temp && !inSS.eof()) { // no more leading zeroes, go and add all the digits until end of stream 
    //    retString += temp;  // NO NEED FOR A WHILE LOOP lol why 
    //}

    if (retString == "-" || retString == "") // for edge case of -000 or 0000 -- as in it never goes and finds any actual numbers 
        return "0"; 

    return retString;
}

string padZeros(string num, int howMany) {
    for (int i = 0; i < howMany; i++) {
        num.insert(0, "0"); 
    }
    return num; 
}

string add(string lhs, string rhs) {
    // TODO(student): implement
    // keep them as strings!! 
    int carryOver = 0; 
    int tempAns = 0; 
    int left = 0;
    int right = 0; 
    int length; 
    bool neg; 
    //char currentDigit = 'a';
    string answer = ""; 

    // cout << "Before attempt trim zeros: " << lhs << endl; 
    lhs = trim_leading_zeros(lhs); 
    rhs = trim_leading_zeros(rhs);
    // cout << "After trim zeros: " << lhs <<endl; 

    if (isNeg(lhs) && isNeg(rhs)) {
        // cout << "Lhs before: " << lhs << endl; 
        lhs = lhs.substr(1); 
        rhs = rhs.substr(1); 
        // cout << "Lhs before: " << lhs << endl;
        neg = true; 
    }
    else if (!isNeg(lhs) == isNeg(rhs)) {
        throw std::invalid_argument("Both must be either positive or negative");
    }
    else {
        neg = false; // they are both positive 
    }

    if (lhs.length() > rhs.length()) { // pads zeros appropriately 
        int diff = lhs.length() - rhs.length();
        // cout << "Diff: " << diff << endl; 
        rhs = padZeros(rhs, diff); 
        length = rhs.length(); 
        // cout << "Bool: " << (rhs.length() == lhs.length()) << endl; 
    }
    else if (lhs.length() < rhs.length()) {
        int diff = rhs.length() - lhs.length();
        lhs = padZeros(lhs, diff);
        length = rhs.length(); 
    }
    else {
        length = rhs.length();
    }

    // cout << "length " << length << endl;
    for (int i = 1; i <= length; i++) {
        left = digit_to_decimal(lhs.at(lhs.length()-i));
        right = digit_to_decimal(rhs.at(rhs.length()-i));
        
        // cout << "left: " << left << " right: " << right << endl; 
        
        tempAns = (left + right) + carryOver;
        // cout << "Temp answer after add " << tempAns << endl; // the carry over is wrong very wrong 
        
        carryOver = tempAns / 10; // this was fixed 
        
        if (carryOver > 0) {
            tempAns = tempAns % 10;
        }

        // cout << "Carry over: " << carryOver << endl;
        // cout << "Temp answer " << tempAns << endl << endl;

        answer.insert(0, string(1, decimal_to_digit(tempAns)));
    }

    if (carryOver != 0 ) {
        char digit = decimal_to_digit(carryOver);                      
        answer.insert(0, string(1, digit));
        // cout << "current answer " << answer << endl << endl;
    }

    if (neg) {
        answer.insert(0, "-"); 
    }
        

    return answer;
}

string multiply(string lhs, string rhs) {
    // TODO(student): implement

    string ansLine = ""; 
    string currSum = "0"; 
    int left; 
    int right;
    int tempAns; 
    int carryOver = 0; 
    bool neg; 

    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);

    if (isNeg(lhs) != isNeg(rhs)) {
        // one of them is negative 
        neg = true; 
    }
    else { // both neg or pos 
        neg = false; 
    }

    if (isNeg(lhs))
        lhs = lhs.substr(1); 
    if (isNeg(rhs))
        rhs = rhs.substr(1); 

    int loopcnt = 0; 
    for (int L = lhs.length()-1; L >= 0; L--) {
        ansLine = ""; 
        carryOver = 0; 
        for (int r = rhs.length()-1; r >= 0; r--) {

            left = digit_to_decimal(lhs.at(L));
            right = digit_to_decimal(rhs.at(r));

            // cout << "left: " << left << " right: " << right << endl; 

            tempAns = (left * right) + carryOver;
            // cout << "Temp answer after multiply: " << tempAns << endl;

            carryOver = tempAns / 10; // this was fixed 

            if (carryOver > 0) {
                tempAns = tempAns % 10;
            }

            // cout << "Carry over: " << carryOver << endl;
            // cout << "Temp answer " << tempAns << endl << endl;

            ansLine.insert(0, string(1, decimal_to_digit(tempAns)));
            // cout << "Answer line: " << ansLine << endl << endl;
        }

        if (carryOver != 0) {
            char digit = decimal_to_digit(carryOver);
            ansLine.insert(0, string(1, digit));
            // cout << "current answer " << answer << endl << endl;
        }

        for (int i = 0; i < loopcnt; i++) {
            ansLine.append("0"); // start inserting zeros on the back based on where in the multiplication mess we are 
        }
        // cout << "ansLine after 0 cushion: " << ansLine << endl; 

        currSum = add(ansLine, currSum); 
        loopcnt++; 
        // cout << "Current sum: " << currSum << endl << endl; 
    }
    
    /*if (carryOver != 0) {
        char digit = decimal_to_digit(carryOver);
        currSum.insert(0, string(1, digit)); 
        // cout << "current answer " << answer << endl << endl;
    }*/

    if (neg)
        currSum.insert(0, "-");

    return currSum; 

    // Please may I have your attention. There is a fire emergency in the building. Please evacuate quickly. 

    //  56 
    // *12 
    // ----
    //  112  carry over 1,1  
    // +560
    // -----
    //  672

    //    12
    // * 234 
    // -----
    //    48
    //   360
    //  2400
    // -----
    //  2808

    // multiply the ones digit with all digits of the bigger in length number 
    // put each result into the ansLine 
        // manage carry over with carry = tempAns / 10 and result to insert as tempAns % 10   
    // that is one iteration of the big for loop 
    // the big for loop needs to go around the number of digits the smaller num has 
        // sum the ansLine + currentSum  (currentSum is initialized to "0")

    // yay return the answer (currentSum) & handle negatives (if isNeg of one != to the other viola poof) 
}


// For later maybe ? 

//std::istringstream inSS(num);
//char temp;
//int number;
//inSS >> temp;
//inSS >> number;
//
//cout << "Number is: " << number << " Char is: " << temp << endl;



// 12 + 19  
// 2+9 = 11 