/*
 * CellData.h
 *
 *  Created on: Nov 9, 2021
 *      Author: student
 */

#include <iostream>
#include <string>
#include "CellData.h"

using std::cout;
using std::endl;
using std::string;

CellData::CellData() : id{ "-1" }, fov{ -1 }, volume{ -1 }, center_x{ -1 }, center_y{ -1 }, 
	min_x{ -1 }, min_y{ -1 }, max_x{ -1 }, max_y{-1} {} //initialize everything

CellData::CellData(std::string id, int fov, double volume, double center_x, double center_y, 
	double min_x, double max_x, double min_y, double max_y) : id{id}, fov{fov}, volume{volume},
	center_x{ center_x}, center_y{ center_y }, min_x{ min_x }, min_y{ min_y }, max_x{ max_x }, max_y{max_y} {} //initialize everything


CellData::~CellData() {} // You should not need to implement this

bool CellData::operator<(const CellData& rhs) {
	// Implement this -- First ordered by FOV number then by id

	//cout << "In cellData's < operator definition! " << endl; 

	if (this->fov < rhs.fov) {
		return true; 
	}
	else if (this->fov > rhs.fov) {
		return false; 
	}
	else { // FOVs are equal 
		if (this->id < rhs.id)
			return true;
		else
			return false; // hopefully there isn't an equal case .. 
	}
 
}

bool CellData::operator==(const CellData& rhs)
{
    // Implement this
	if (id == rhs.id && fov == rhs.fov && volume == rhs.volume && center_x == rhs.center_x
		&& center_y == rhs.center_y && min_x == rhs.min_x && min_y == rhs.min_y && max_x == max_x && max_y == rhs.max_y)
		return true;
	else
		return false; 
}

