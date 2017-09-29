#ifndef GRID2_H
#define GRID2_H
#pragma once

#include <string>
#include "BoundaryCondition.h"
#include "Matrix.h"

class Grid2
{
public:
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

	// Grid dimensions
	int IMax;
	int JMax;

	// Grid matrix
	Matrix X;
	Matrix Y;

private:
	// Initializes and sets up the matrices
	void InitializeMatrix(std::ifstream &FileID);

	// Reads in the matrix for a coordinate direction (X, Y, etc.)
	void ReadCoordinateMatrix(std::ifstream &FileID, Matrix& InputMatrix);

	// Grid input filename
	std::string _GridInputFilename;
};
#endif
