#ifndef VECTOR2_H
#define VECTOR2_H
#pragma once

#include <iostream>

class Vector2
{
public:
	// Default constructor
	Vector2();

	// Destructor
	~Vector2();

	// Access to the array
	double& operator[](int Index);

private:
	double _x;
	double _y;

};

#endif