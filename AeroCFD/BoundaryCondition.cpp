#include <iostream>
#include <fstream>
#include "BoundaryCondition.h"

// Resize boundary condition array based on IMax and JMax and 4 boundary edges
BoundaryCondition::BoundaryCondition(int IMax, int JMax) :
																_IMax(IMax),
																_JMax(JMax)
{
	BC.resize(_NumberEdges);
	BC[0].resize(_JMax + 1);
	BC[1].resize(_IMax + 1);
	BC[2].resize(_JMax + 1);
	BC[3].resize(_IMax + 1);
}

BoundaryCondition::~BoundaryCondition()
{}

void BoundaryCondition::LoadBoundaryConditions(std::string BCDirectory)
{
	std::cout << " Opening Boundary Condition files:\n";
	for (int f = 0; f < _NumberEdges; f++)
	{
		// Loop through boundary files (I=1, J=1, IMax, and JMax)
		std::string BCFile = BCDirectory + "/" + _BCFiles[f] + ".BC";
		std::ifstream FileID(BCFile);

		// Verify file is open and read in boundary file
		CheckFileIsOpen(FileID, BCFile);
		std::cout << "   " << BCFile << "\n";
		ReadBoundaryConditionFile(FileID, f);

	}
	std::cout << "\n";
	return;
}

void BoundaryCondition::ReadBoundaryConditionFile(std::ifstream &FileID, int f)
{
	int NumberElements; // Note: in general number of elements will be (IMAX OR JMAX) + 1
	FileID >> NumberElements;
	for (int i = 0; i < NumberElements; i++)
	{
		FileID >> BC[f][i].x >> BC[f][i].y;
	}
}

void BoundaryCondition::CheckFileIsOpen(std::ifstream &FileID, std::string BCFile)
{
	if (!FileID.is_open())
	{
		std::cout << " Error!: Unable to open " << BCFile << ".\n";
		exit(EXIT_FAILURE);
	}
}
