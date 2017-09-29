#include "Proxy.h"
#include "Matrix.h"

// Constructor
Matrix::Matrix()
{}

// Destructor
Matrix::~Matrix()
{
	// Clean up memory from the Heap
	for (int i = 0; i < _Rows; i++)
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
	_Array = new double*[_Rows];
	for (int i = 0; i < _Rows; i++)
	{
		_Array[i] = new double[_Columns];
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

// Perform Gauss Seidel Relaxtion
void Matrix::GaussSeidel(void(*InputFunction)(int i, int j))
{}
