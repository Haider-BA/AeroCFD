#include <iostream>

#include "Grid2.h"
#include "Proxy.h"
#include "BoundaryCondition.h"
#include "Elliptic.h"

void PrintHeader();

// TODO Print input options
int main(int argc, char* argv[])
{
	PrintHeader();
	int IMAX = 384;
	int JMAX = 64;
	Grid2 Grid(IMAX, JMAX);
	BoundaryCondition Boundary(Grid.IMax, Grid.JMax);
	Elliptic EllipticGridGen(Grid.IMax, Grid.JMax);

	Boundary.LoadBoundaryConditions("./BC");
	Grid.TransfiniteInterpolation(Boundary);
	Grid.WriteGrid("n0012_alg.grid");	
	EllipticGridGen.GridGeneration(Grid);
	Grid.WriteGrid("../../../../VM_Shared/n0012_ell.grid");

	
	std::cout << "Press any key to continue\n";
	std::getchar();
	return 0;
}

void PrintHeader()
{
	std::cout << "*************************************************\n";
	std::cout << "*                                               *\n";
	std::cout << "*         2-D ELLIPTIC GRID GENERATION          *\n";
	std::cout << "*                                               *\n";
	std::cout << "*               Edward Szwabowski               *\n";
	std::cout << "*                                               *\n";
	std::cout << "*                                               *\n";
	std::cout << "*             Version 1.0 10/07/2018            *\n";
	std::cout << "*                                               *\n";
	std::cout << "*************************************************\n\n";

}