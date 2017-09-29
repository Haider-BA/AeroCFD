#ifndef GRID2_H
#define GRID2_H
#pragma once

#include <string>
#include "BoundaryCondition.h"
#include "Matrix.h"

class Grid2
{
public:
	// Default constructor
	Grid2();

	// Constructor with an input file
	Grid2(std::string GridInputFilename);

	// Destructor
	~Grid2();

	// Read in grid
	void LoadGrid();

	// Write out grid to file
	void WriteGrid(std::string GridOutputFilename);

	// Transfinite interpolation
	void TransfiniteInterpolation(BoundaryCondition* BC);

	// Elliptic grid generation
	void EllipticGridGeneration();

private:
	// Initializes and sets up the matrices
	void InitializeMatrix(std::ifstream &FileID);

	// Reads in the matrix for a coordinate direction (X, Y, etc.)
	void ReadCoordinateMatrix(std::ifstream &FileID, Matrix& InputMatrix);

	// Grid input filename
	std::string _GridInputFilename;

	// Grid dimensions
	int _IMax;
	int _JMax;

	// Grid indices
	int _i, _j;

	// Grid matrix
	Matrix _XMatrix;
	Matrix _YMatrix;

};
#endif