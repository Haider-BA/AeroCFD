#ifndef VECTOR2_H
#define VECTOR2_H
#pragma once

#include <iostream>

class Vector2
{
public:
	// Default constructor
	Vector2();

	// Specified constructor
	Vector2(double InputX, double InputY);

	// Destructor
	~Vector2();

	// Vector addition
	Vector2 operator+(const Vector2& Vector) const;	

	// Vector subtraction
	Vector2 operator-(const Vector2& Vector) const;	

	// Scalar multiplication
	Vector2 operator*(const double Scalar) const;	

	// Magnitude squared
	double Length2() const;	

	// Magnitude
	double Length() const;	

	// Normalize
	void Normalize();	

	// Dot product
	double Dot(const Vector2& Vector) const;	

	// Cross product
	double Cross(const Vector2& Vector) const;	

	// Variables
	double x;
	double y;
private:
	
};

#endif