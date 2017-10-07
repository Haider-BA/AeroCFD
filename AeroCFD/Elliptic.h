#ifndef ELLIPTIC_H
#define ELLIPTIC_H
#pragma once

#include "Matrix.h"
#include "Grid2.h"

class Elliptic
{
public:
	Elliptic(int InputIMax, int InputJMax);

	void LoadInputParameters();

	void GridGeneration(Grid2& Grid);

private:
	int _IMax;
	int _JMax;
	Matrix _P;
	Matrix _Q;

	/// Input parameters (default)
	double _WallAngle = 90.;
	double _WallSpace = 4.0E-6;
	double _AngleDamping = 0.1;
	double _SpaceDamping = 0.15;
	double _AngleDecay = 1.0;
	double _SpaceDecay = 1.0;
	double _OverrelaxationFactor = 1.4;
	int _MaxIterations = 30;
	int _SmoothIterations = 100;
	double _Tolerance = 1.0E-5;
	double _Residual = 0.;

	/// Source terms
	void ZeroSourceTerms();
	void ComputeSourceTerms(Grid2& Grid);
	void IMaxSourceTerms(Grid2& Grid, int j);
	void IMinSourceTerms(Grid2& Grid, int j);
	void JMaxSourceTerms(Grid2& Grid, int i);
	void JMinSourceTerms(Grid2& Grid, int i);
	double AngleResidual(double dxi, double dyi, double dxj, double dyj);
	double SpaceResidual(double dx, double dy);

	/// Relaxation schemes
	void SuccessiveOverRelaxation();
	void GaussSeidel();
};

#endif