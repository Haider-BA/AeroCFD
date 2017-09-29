#ifndef BOUNDARYCONDITION_H
#define BOUNDARYCONDITION_H
#pragma once

#include <string>
#include <vector>
#include "Vector2.h"

class BoundaryCondition
{
public:
	// Constructor
	BoundaryCondition(int IMax, int JMax);

	// Destructor
	~BoundaryCondition();

	// Load in boundary condition input files
	void LoadBoundaryConditions(std::string BCDirectory);

	// BC Arrays
	// The BC array has 4 vectors
	// BC[0]: I = 1
	// BC[1]: J = 1
	// BC[2]: I = IMax
	// BC[3]: J = JMax
	std::vector< std::vector <Vector2> > BC;

private:
	int _IMax;
	int _JMax;
	const static int _NumberEdges = 4;

	std::string _BCFiles[_NumberEdges] = { "I1", "J1", "IMax", "JMax" };

	// Read in boundary condition file
	void ReadBoundaryConditionFile(std::ifstream &FileID, int f);
};

#endif
