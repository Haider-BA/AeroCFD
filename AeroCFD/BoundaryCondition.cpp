#include <iostream>
#include <fstream>
#include "BoundaryCondition.h"

// Resize boundary condition array based on IMax and JMax and 4 boundary edges
BoundaryCondition::BoundaryCondition(int IMax, int JMax) :
																_IMax(IMax),
																_JMax(JMax)
{
	BC.resize(_NumberEdges);
	BC[0].resize(_IMax);
	BC[1].resize(_JMax);
	BC[2].resize(_IMax);
	BC[3].resize(_JMax);
}

BoundaryCondition::~BoundaryCondition()
{}

void BoundaryCondition::LoadBoundaryConditions(std::string BCDirectory)
{
	for (int f = 0; f < _NumberEdges; f++)
	{
		std::ifstream FileID(BCDirectory + "/" + _BCFiles[f] + ".BC");
		if (FileID.is_open())
		{
			std::cout << "Opening BC File: " << (BCDirectory + "/" + _BCFiles[f] + ".BC") << "\n";
			ReadBoundaryConditionFile(FileID, f);
		}
		else
		{
			std::cout << "Unable to open " << (BCDirectory + "/" + _BCFiles[f] + ".BC") << "\n";
		}
	}
	return;
}

void BoundaryCondition::ReadBoundaryConditionFile(std::ifstream &FileID, int f)
{
	int NumberElements;
	FileID >> NumberElements;
	std::cout << "NumberElements = " << NumberElements << "\n";
	for (int i = 0; i < NumberElements; i++)
	{
		FileID >> BC[f][i].x >> BC[f][i].y;
		std::cout << "(x,y) = (" << BC[f][i].x << ", "<< BC[f][i].y << ")\n";
	}
	// Cleanup
	FileID.close();
}
