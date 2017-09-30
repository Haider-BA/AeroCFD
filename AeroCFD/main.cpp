#include <iostream>

#include "Grid2.h"
#include "Proxy.h"
#include "BoundaryCondition.h"

int main(int argc, char* argv[])
{
	Grid2 Grid("n0012p3d.grid");

	/// TEST
	for (int i = 0; i < Grid.IMax; i++)
	{
		for (int j = 0; j < Grid.JMax; j++)
		{
			//printf("(X,Y)[%d,%d] = (%f, %f)\n", i, j, Grid.X[i][j], Grid.Y[i][j]);
		}
	}	

	
	BoundaryCondition Boundary(Grid.IMax, Grid.JMax);
	Boundary.LoadBoundaryConditions("./BC");

	Grid.TransfiniteInterpolation(Boundary);

	Grid.WriteGrid("n0012_alg.grid");
	
	std::cout << "Press any key to continue\n";
	std::getchar();
	return 0;
}
