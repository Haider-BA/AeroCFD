//
// Note that min grid index is 0 and max index is IMAX
// Number of nodes is IMAX + 1 and number of cells is IMAX


#ifndef GRID2_H
#define GRID2_H
#pragma once

#include <string>
#include "BoundaryCondition.h"
#include "Matrix.h"

class Grid2
{
public:
	// Constructor only specifying grid dimensions
	Grid2(int InputIMax, int InputJMax);

	// Constructor with an input file
	Grid2(std::string GridInputFilename);

	// Destructor
	~Grid2();

	// Write out grid to file
	void WriteGrid(std::string GridOutputFilename);

	// Transfinite interpolation
	void TransfiniteInterpolation();
	void TransfiniteInterpolation(const BoundaryCondition& Boundary);

	// Elliptic grid generation
	void EllipticGridGeneration();

	// Grid dimensions
	int IMax;
	int JMax;

	// Grid matrix
	Matrix X;
	Matrix Y;

private:
	// Read in grid
	void LoadGrid();

	// Initializes and sets up the matrices
	void InitializeMatrix(std::ifstream &FileID);

	// Reads in the matrix for a coordinate direction (X, Y, etc.)
	void ReadCoordinateMatrix(std::ifstream &FileID, Matrix& InputMatrix);

	// Fill in boundaries of the grid matrices
	void FillGridBoundary(const BoundaryCondition& Boundary);

	// Write out the given coordinate matrix
	void PrintCoordinateMatrix(std::ofstream &FileID, Matrix& OutputMatrix) const;

	// Checks for opening the grid file
	void CheckFileIsOpen(const std::ifstream &FileID) const;
	void CheckFileIsOpen(const std::ofstream &FileID) const;

	// Grid input filename
	std::string _GridInputFilename;
};
#endif
