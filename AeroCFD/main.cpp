#include <iostream>

#include "Grid2.h"
#include "Proxy.h"
#include "BoundaryCondition.h"


int main(int argc, char* argv[])
{
	int IMAX = 192;
	int JMAX = 32;
	Grid2 Grid(IMAX, JMAX);
	BoundaryCondition Boundary(Grid.IMax, Grid.JMax);

	Boundary.LoadBoundaryConditions("./BC");

	Grid.TransfiniteInterpolation(Boundary);

	Grid.WriteGrid("n0012_alg.grid");


	/// TEST
	for (int i = 0; i <= Grid.IMax; i++)
	{
		for (int j = 0; j <= Grid.JMax; j++)
		{
			//printf("(X,Y)[%d,%d] = (%f, %f)\n", i, j, Grid.X[i][j], Grid.Y[i][j]);
		}
	}	

	

	
	std::cout << "Press any key to continue\n";
	std::getchar();
	return 0;
}
