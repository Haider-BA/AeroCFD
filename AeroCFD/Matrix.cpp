#include "Proxy.h"
#include "Matrix.h"
#include <iostream>

// Constructor
Matrix::Matrix()
{}

// Destructor
Matrix::~Matrix()
{
	// Clean up memory from the Heap
	std::cout << "Matrix deallocation\n";
	for (int i = 0; i <= _Rows; i++)
	{
		delete[] _Array[i];
	}
	delete[] _Array;
}

// Constructor
void Matrix::Initialize(int Rows, int Columns)
{
	// Set the dimensions
	_Rows = Rows;
	_Columns = Columns;

	// Initialize array to zeros
	_Array = new double*[_Rows + 1];
	for (int i = 0; i <= _Rows; i++)
	{
		_Array[i] = new double[_Columns + 1];
	}
}

// Interpolation to the interior nodes using transfinite interpolation
void Matrix::TransfiniteInterpolation()
{
	for (int i = 1; i < _Rows; i++)
	{
		for (int j = 1; j < _Columns; j++)
		{
			double dI = (double(_Rows) - double(i)) / double(_Rows);
			double dJ = (double(_Columns) - double(j)) / double(_Columns);
			double JJ = double(j) / double(_Columns);
			double II = double(i) / double(_Rows);
			//TEST printf("%f %f %f %f\n",dI,dJ,II,JJ);
			_Array[i][j] = (dI*_Array[0][j] + II*_Array[_Rows][j] + dJ*_Array[i][0] + JJ*_Array[i][_Columns]) -
				(dI*dJ*_Array[0][0] + II*dJ*_Array[_Rows][0] + JJ*dI*_Array[0][_Columns] + II*JJ*_Array[_Rows][_Columns]);
		}
	}
}

// Overloaded operator [] to access the array
Proxy& Matrix::operator[](int Index)
{
	return Proxy(_Array[Index]);
}

// Access matrix rows
int Matrix::GetRows() const
{
	return _Rows;
}

// Access matrix columns
int Matrix::GetColumns() const
{
	return _Columns;
}

