#ifndef MATRIX_H
#define MATRIX_H
#pragma once

class Proxy;

class Matrix
{
public:
	// Constructor
	Matrix();
	// Destructor
	~Matrix();
	
	// Initialize Matrix
	void Initialize(int Rows, int Columns);

	// Interpolation to the interior nodes using transfinite interpolation
	void TransfiniteInterpolation();
	
	// Access to the matrix
	Proxy& operator[](int Index);

	// Access matrix dimensions
	int GetRows() const;
	int GetColumns() const;

private:
	// Dimensions
	int _Rows;
	int _Columns;

	// Array
	double** _Array;

};
#endif