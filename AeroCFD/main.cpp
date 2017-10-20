#include <iostream>

#include "Grid2.h"
#include "Proxy.h"
#include "BoundaryCondition.h"
#include "Elliptic.h"

void PrintHeader();
void PrintGridInfo(Grid2& Grid);

// TODO Print input options
int main(int argc, char* argv[])
{
	PrintHeader();

	int IMAX = 384;
	int JMAX = 64;
	Grid2 Grid(IMAX, JMAX);
		
	PrintGridInfo(Grid);
	
	// Boundary conditions
	BoundaryCondition Boundary(Grid.IMax, Grid.JMax);
	Boundary.LoadBoundaryConditions("./BC");	
	
	// Algebraic grid
	std::cout << " Generating algebraic grid...\n";
	Grid.TransfiniteInterpolation(Boundary);
	Grid.WriteGrid("n0012_alg.grid");

	// Elliptic Grid
	Elliptic EllipticGridGen(Grid.IMax, Grid.JMax);
	EllipticGridGen.GridGeneration(Grid);
	//Grid.WriteGrid("../../../../VM_Shared/n0012_ell.grid");

	
	std::cout << " Press any key to continue\n";
	std::getchar();
	return 0;
}

void PrintHeader()
{
	std::cout << " *************************************************\n";
	std::cout << " *                                               *\n";
	std::cout << " *         2-D ELLIPTIC GRID GENERATION          *\n";
	std::cout << " *                                               *\n";
	std::cout << " *               Edward Szwabowski               *\n";
	std::cout << " *                                               *\n";
	std::cout << " *                                               *\n";
	std::cout << " *             Version 1.0 10/07/2018            *\n";
	std::cout << " *                                               *\n";
	std::cout << " *************************************************\n\n";

}

void PrintGridInfo(Grid2& Grid)
{
	std::cout << " Grid size: \n";
	std::cout << "   IMax = " << Grid.IMax << "\n";
	std::cout << "   JMax = " << Grid.JMax << "\n\n";
}