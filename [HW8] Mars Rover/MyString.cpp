// TODO: Implement this source file
#include <iostream>
#include "MyString.h"
using std::cout, std::endl;

MyString::MyString() : arr(new char[1]{'\0'}), mysize(0), mycapacity(1) {}

MyString::MyString(const MyString& str) : arr(new char[str.capacity()]), mysize(str.size()), mycapacity(str.capacity()) {

	for (unsigned int i = 0; i < mysize; i++) {
		arr[i] = str.arr[i]; 
	}
	arr[mysize] = '\0'; 

}

MyString::MyString(const char* str) : arr(new char[1]{'\0'}), mysize( 0 ), mycapacity(1) {
	if (str == nullptr)
		return;

	size_t len = 0;
	while (str[len] != '\0') {
		len++;
	}
	//cout << "About to delete" << endl; 
	delete[] arr; 
	arr = new char[len+1];
	mysize = len;
	mycapacity = len+1;

	for (unsigned int i = 0; i < mysize; i++) {
		arr[i] = str[i];
	}

	arr[mysize] = '\0'; 
	//cout << "Done and exiting" << endl;
}

MyString::~MyString() { 

	if (arr != 0) {
		//printf("Address of x is %p\n", (void*)arr);
		//cout << arr << endl; 
		delete[] arr;
		arr = nullptr;
	}
} 

size_t MyString::capacity() const{
	return mycapacity; 
}
size_t MyString::size() const {
	return mysize;
}
size_t MyString::length() const {
	return mysize;
}

char* MyString::data() const noexcept {
	return arr;
}

bool MyString::empty() const noexcept{
	if (mysize == 0)
		return true;
	else
		return false;
}

const char& MyString::at(size_t pos) const {
	if (pos < mysize) // >= 0 is already covered with size_t variable 
		return arr[pos];
	throw std::out_of_range("Bad index");
}

void MyString::clear() {
	delete [] arr;
	arr = new char[1]{'\0'};
	mysize = 0;
	mycapacity = 1;
}

const char& MyString::front() const {
	if (mysize != 0) {
		return arr[0];
	}
	throw std::out_of_range("Bad index");
}

void MyString::resize(size_t n) {
	bool debug = 0; 
	
	if (debug) { cout << "My cap: " << mycapacity << " N: " << n << endl; }

	if (arr == nullptr)
		return; 

	if (mycapacity < n) {
		mycapacity = n; // size is unchanged 
		char* newArr = new char[mycapacity];

		size_t i = 0;
		while (arr[i] != '\0') {
			newArr[i] = arr[i];
			if (debug) { cout << "Elem: " << newArr[i] << endl; }
			i++;
		}
		newArr[i] = '\0';

		delete[] arr;
		arr = newArr;
	}
	else if (mycapacity == n) { 
		return; 
	}
	else { // capacity is greater than n
		if (debug) cout << "In the else block " << endl;
		mycapacity = n;
		char* newArr = new char[mycapacity];

		size_t i = 0;
		while (i < (n-1) && arr[i] != '\0') {
			newArr[i] = arr[i];
			if (debug) { cout << "Elem: " << newArr[i] << endl; }
			i++;
		}
		
		newArr[i] = '\0';
		if (debug) { cout << "Null index: " << i << endl; }
		mysize = mycapacity - 1; 

		delete[] arr;
		arr = newArr;
	}
	

}

MyString& MyString::operator = (const MyString& rhs) { // other copy constructor 
	mysize = rhs.size();
	mycapacity = rhs.capacity();

	delete[] arr; 
	arr = new char[mycapacity]; 

	for (size_t i = 0; i < rhs.size(); i++) {
		arr[i] = rhs.arr[i]; 
	}

	return *this;
}


MyString& MyString::operator += (const MyString& rhs) {

	bool debug = 0; 

	if (debug) cout << "In the += operator" << endl; 
	mycapacity = mycapacity + rhs.size();
	size_t currSize = mysize + rhs.size();


	char * newArr = new char[mycapacity];  

	if (debug) cout << "Resize occured : cap is now " << mycapacity << " Size: " << mysize << " Before adding elems: " << arr << endl;
	if (debug) cout << "Big size: " << currSize << " " << mysize << endl;

	for (unsigned int i = 0; i < mysize; i++) {
		newArr[i] = arr[i];
		//if (debug) cout << "Elem added to arr : " << arr[i] << ";  location of rhs elem: " << i - mysize << "  " << arr << endl;
	}

	for (unsigned int i = mysize; i < currSize; i++) {
		newArr[i] = rhs.arr[i - mysize];
		if (debug) cout << "Elem added to arr : " << arr[i] << ";  location of rhs elem: " << i - mysize << "  " << arr << endl;
	}

	mysize = currSize;
	if (debug) cout << "Big size: " << currSize  << " " << mysize << endl;
	newArr[mysize] = '\0'; 

	delete[] arr;
	arr = newArr; 

	return *this;
}


MyString MyString::operator+(const MyString& rhs) {
	
	//cout <<"This obj : " << arr << endl;
	//cout << "Rhs obj : " << rhs << endl;

	size_t newsize = mysize + rhs.size();
	size_t newcap = mycapacity + rhs.size(); // only one '\0' spot  
	MyString newstr; 
	//cout << "New size : " << newsize << endl;

	newstr.resize(newcap); 
	//cout << "Size : " << newstr.size() << endl; 

	for (unsigned int i = 0; i < mysize; i++) {
		newstr.arr[i] = this->arr[i];
	} 
	
	//newstr.arr[mysize] = '\0';
	//cout << "First copy obj : " << newstr.arr << endl;

	for (unsigned int i = mysize; i < newsize; i++) { 
		newstr.arr[i] = rhs.arr[i - mysize];
	}
	//newstr.arr[newsize] = '\0';
	newstr.mysize = newsize; 
	//cout << "Size : " << newstr.size() << endl; 
	//cout << "Second copy obj : " << newstr.arr << endl;

	//cout << "Newstr was created" << endl;
	return newstr;
}

bool MyString::operator == (const MyString& rhs) {
	if (rhs.size() == mysize) {
		// for loop thru 
		for (size_t i = 0; i < mysize; i++) { 
			if (arr[i] != rhs.arr[i])
				return false;
		}
		return true;
	}
	return false;
}

size_t MyString::find(const MyString& s, size_t ind) const noexcept {

	bool debug = 0; 
	unsigned int foundLetters = 0;

	if (s.size() == 0 || mysize <= ind)
		return -1; 

	for (size_t i = ind; i < mysize; i++) {
		if (debug) cout << "Current letter : " << arr[i] << endl;  
		if (arr[i] == s.at(0)) { // found the first letter 
			foundLetters++;
			if (debug) cout << "In Found First Letter if : " << "curr letter : " << arr[i] << "   letter in word comp : " << s.data()[0] << endl;
			
			if (foundLetters == s.size()) { // the word we are comparing is only one character 
				if (debug) cout << "   Found the full word (it was a character)" << endl;
				return i;
			}
			
			for (size_t j = 1; j < s.size(); j++) {
				if (debug) cout << "In Found First Letter if : " << "curr letter : " << arr[i+j] << "   letter in word comp : " << s.data()[j] << endl; 
				
				if ((i + j) >= mysize) {
					if (debug) cout << "This if just saved us from out of bounds comparisons" << endl; 
					break; //if checking the word comparison goes out of bounds of the OG array don't do it and break 

				}
					
				if (arr[i + j] == s.data()[j]) {  
					if(debug) cout << "   Found match" << endl;
					foundLetters++;
				}
				else {
					if (debug) cout << "   Not a match; breaking out of for loop" << endl;
					foundLetters = 0; 
					break; // inner for loop and continue looking for the first letter again 
				}

				if (foundLetters == s.size()) { // yay found the full word!!!
					if (debug) cout << "   Found the full word" << endl;
					return i; 
				}
			} // end inner for 
		} // end if for finding first letter 
	} // end big for loop 

	return -1; // went through entire array and couldn't find anything 

}


std::ostream& operator<<(std::ostream& os, const MyString& str) {
	for (size_t i = 0; i < str.size(); i++) {
		os << str.at(i); 
	}
	
	return os; 
}
