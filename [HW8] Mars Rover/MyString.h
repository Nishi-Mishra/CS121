// TODO: Implement this header file
#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>

//using std::ostream;

class MyString {
private: 
	char* arr; 
	size_t mysize; 
	size_t mycapacity; 
public:
	MyString();
	~MyString();
	MyString(const char* str); // copy constructor 
	MyString(const MyString &str); // copy constructor 
	// MyString(const MyString& str, size_t pos, size_t len); // substring equivalence ? 
	// MyString(size_t n, char c); // fill with char c 

	void resize(size_t n);
	size_t capacity() const;
	size_t size() const;
	size_t length() const;
	char* data() const noexcept; // this is the array itself 
	bool empty() const noexcept;
	const char& front() const; 
	const char& at(size_t pos) const; 
	void clear();
	MyString& operator=(const MyString &rhs);   
	MyString& operator+=(const MyString& rhs);
	MyString operator+(const MyString& rhs);
	bool operator==(const MyString& rhs);
	size_t find(const MyString& s, size_t ind = 0) const noexcept;
};

std::ostream& operator<<(std::ostream& os, const MyString& myString); 

#endif