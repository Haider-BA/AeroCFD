#include "Grid2.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Proxy.h"

#define OUT

// Constructor
Grid2::Grid2(std::string GridInputFilename) :
											_GridInputFilename(GridInputFilename)
{
	LoadGrid();
};

// Destructor
Grid2::~Grid2()
{};

// Load grid
void Grid2::LoadGrid()
{
	std::ifstream FileID(_GridInputFilename);

	// Verify file is open then load file into the grid matrices
	CheckFileIsOpen(FileID);
	std::cout << "Reading grid file: " << _GridInputFilename << "\n";	
	InitializeMatrix(FileID);

	return;
}

void Grid2::WriteGrid(std::string GridOutputFilename)
{
	std::ofstream FileID(GridOutputFilename);
	
	// Verify file is open then load file into the grid matrices
	CheckFileIsOpen(FileID);
	std::cout << "Writing grid to file: " << GridOutputFilename << "\n";
	FileID << IMax << " " << JMax << "\n";
	PrintCoordinateMatrix(FileID, X);
	PrintCoordinateMatrix(FileID, Y);
}

// Perform Linear Transfinite Interpolation
void Grid2::TransfiniteInterpolation(const BoundaryCondition& Boundary)
{
	for (int i = 1; i < IMax - 1; i++)
	{
		for (int j = 1; j < JMax - 1; j++)
		{
			double dI = (double(IMax) - double(i)) / double(IMax);
			double dJ = (double(JMax) - double(j)) / double(JMax);
			double JJ = double(j) / double(JMax);
			double II = double(i) / double(IMax);
			//TEST printf("(%d,%d) = %f, %f, %f, %f\n", i, j, dI, dJ, JJ, II);
			X[i][j] = dI*Boundary.BC[0][j].x + 
					  II*Boundary.BC[2][j].x + 
					  dJ*Boundary.BC[1][i].x +
					  JJ*Boundary.BC[3][i].x -
				(	  dI*dJ*Boundary.BC[1][0].x +
					  II*dJ*Boundary.BC[2][0].x +
					  JJ*dI*Boundary.BC[0][JMax - 1].x +
					  II*JJ*Boundary.BC[3][IMax - 1].x	);
			Y[i][j] = dI*Boundary.BC[0][j].y +
					  II*Boundary.BC[2][j].y +
					  dJ*Boundary.BC[1][i].y +
					  JJ*Boundary.BC[3][i].y -
				(	  dI*dJ*Boundary.BC[1][0].y +
					  II*dJ*Boundary.BC[2][0].y +
					  JJ*dI*Boundary.BC[0][JMax - 1].y +
					  II*JJ*Boundary.BC[3][IMax - 1].y	);
		}
	}
}

void Grid2::InitializeMatrix(std::ifstream &FileID)
{
	// Read in IMax and JMax
	FileID >> IMax;
	FileID >> JMax;
	printf("  with IMax = %d, JMax = %d\n", IMax, JMax);

	// Allocate memory for the arrays
	X.Initialize(IMax, JMax);
	Y.Initialize(IMax, JMax);

	// Read in the X and Y coordinates
	ReadCoordinateMatrix(FileID, OUT X);
	ReadCoordinateMatrix(FileID, OUT Y);
}

// Read in array for a given coordinate direction
void Grid2::ReadCoordinateMatrix(std::ifstream &FileID, Matrix &InputMatrix)
{
	double Value;
	// Populate array from file
	for (int j = 0; j < JMax; j++)
	{
		for (int i = 0; i < IMax; i++)
		{
			FileID >> Value;
			InputMatrix[i][j] = Value;
			//TEST printf("X(%d,%d) = %f\n", i, j, InputMatrix[i][j]);
		}
	}
	return;
}

// Fills the edges of the grid with the boundary condition
void Grid2::FillGridBoundary(const BoundaryCondition& Boundary)
{
	// Fill I = 1 and I = IMax boundaries
	for (int j = 0; j < JMax; j++)
	{
		X[0		  ][j] = Boundary.BC[0][j].x;
		Y[0		  ][j] = Boundary.BC[0][j].y;
		X[IMax - 1][j] = Boundary.BC[2][j].x;
		Y[IMax - 1][j] = Boundary.BC[2][j].y;
	}

	// Fill J = 1 and J = JMax boundaries
	for (int i = 0; i < IMax; i++)
	{
		X[i][0		 ] = Boundary.BC[1][i].x;
		Y[i][0		 ] = Boundary.BC[1][i].y;
		X[i][JMax - 1] = Boundary.BC[3][i].x;
		Y[i][JMax - 1] = Boundary.BC[3][i].y;
	}
}

void Grid2::PrintCoordinateMatrix(std::ofstream &FileID, Matrix& OutputMatrix)
{
	// Print matrix to file
	for (int j = 0; j < JMax; j++)
	{
		for (int i = 0; i < IMax; i++)
		{
			FileID << OutputMatrix[i][j] << " ";
		}
	}
	FileID << "\n";
	return;
}

/// Overloads for checking if the grid input/output files are opened
void Grid2::CheckFileIsOpen(std::ifstream & FileID)
{
	if (!FileID.is_open())
	{
		std::cout << "  Error!: Unable to open grid file.\n";
		exit(EXIT_FAILURE);
	}
}

void Grid2::CheckFileIsOpen(std::ofstream & FileID)
{
	if (!FileID.is_open())
	{
		std::cout << "  Error!: Unable to open grid file.\n";
		exit(EXIT_FAILURE);
	}
}