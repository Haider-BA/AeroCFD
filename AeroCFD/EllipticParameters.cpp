#include "EllipticParameters.h"
#include <iostream>
#include <iomanip>

EllipticParameters::EllipticParameters()
{
	std::cout << "Elliptic Grid Input Parameters\n";
	std::cout << "  Laplace Iterations    " << std::setw(9) << std::setprecision(6) << LaplaceIterations << "\n";
	std::cout << "  Poisson Iterations    " << std::setw(9) << std::setprecision(6) << PoissonIterations << "\n";
	std::cout << "  Matrix Iterations     " << std::setw(9) << std::setprecision(6) << RelaxationIterations << "\n";
	std::cout << "  Spacial Damping       " << std::setw(9) << std::setprecision(6) << SpaceDamping << "\n";
	std::cout << "  Angular Damping       " << std::setw(9) << std::setprecision(6) << AngleDamping << "\n";
	std::cout << "  Spacial Decay         " << std::setw(9) << std::setprecision(6) << SpaceDecay << "\n";
	std::cout << "  Angular Decay         " << std::setw(9) << std::setprecision(6) << AngleDecay << "\n";
	std::cout << "  Relaxation Parameter  " << std::setw(9) << std::setprecision(6) << OverrelaxationFactor << "\n\n";
}

void EllipticParameters::LoadInputParameters()
{}
