#include<iostream>
#include<string>
#include "Node.h"
#include "CellData.h"

using std::cout; 
using std::endl;

// Default constructor
// remember to initialize next to nullptr
Node::Node() : data{},  next { nullptr }, prev{ nullptr } {}

// Parameterized constructor
// remember to initialize next to nullptr
Node::Node(std::string id, int fov, double volume, double center_x, double center_y, double min_x, 
	double max_x, double min_y, double max_y) : data{ id, fov, volume, center_x, center_y,
	min_x, max_x, min_y, max_y }, next {nullptr}, prev{ nullptr } { }


bool Node::operator<(const Node& b) {

	//cout << "In nodes's < operator definition! " << endl;

	if (this->data < b.data)
		return true;
	else
		return false;  
}

bool Node::operator==(const Node& b) {
	if (this->data == b.data)
		return true;
	else
		return false;
}

