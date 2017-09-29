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
	if (FileID.is_open())
	{
		// Read in IMax, JMax, and nodes
		InitializeMatrix(FileID);

		// Cleanup
		FileID.close();
	}
	else
	{
		std::cout << "Unable to open " << _GridInputFilename << "\n";
	}

	return;
}

void Grid2::InitializeMatrix(std::ifstream &FileID)
{
	// Read in IMax and JMax
	FileID >> IMax;
	FileID >> JMax;
	printf("IMAX = %d, JMAX = %d\n", IMax, JMax);

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
