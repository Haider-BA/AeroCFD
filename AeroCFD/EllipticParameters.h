#pragma once
#ifndef ELLIPTICPARAMETERS_H
#define ELLIPTICPARAMETERS_H

class EllipticParameters
{
public:
	EllipticParameters();

	void LoadInputParameters();

	/// Input parameters (default)
	double WallAngle = 90.;
	double WallSpace = 4.0E-6;
	double AngleDamping = 0.1;
	double SpaceDamping = 0.15;
	double AngleDecay = 1.0;
	double SpaceDecay = 1.0;
	double OverrelaxationFactor = 1.4;
	int PoissonIterations = 5;
	int LaplaceIterations = 0;
	int RelaxationIterations = 30;
	double Tolerance = 1.0E-5;
	double Residual = 0.;

private:

};

#endif