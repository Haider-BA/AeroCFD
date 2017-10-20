#ifndef ELLIPTIC_H
#define ELLIPTIC_H
#pragma once

#include "Matrix.h"
#include "Grid2.h"
#include "EllipticParameters.h"

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

	EllipticParameters InputParams;

	/// 1st derivative approximations
	double _XI = 0.;
	double _XJ = 0.;
	double _YI = 0.;
	double _YJ = 0.;

	/// 2nd derivative approximations
	double _XII = 0.;
	double _XJJ = 0.;
	double _YII = 0.;
	double _YJJ = 0.;

	/// Mixed derivative approximations
	double _XIJ = 0.;
	double _YIJ = 0.;

	/// Residuals
	double _Xrms0 = 0.;
	double _Yrms0 = 0.;
	double _Xrms = 0.;
	double _Yrms = 0.;

	/// Source terms
	void ZeroSourceTerms();
	void ComputeSourceTerms(Grid2& Grid);
	void IMaxSourceTerms(Grid2& Grid, int j);
	void IMinSourceTerms(Grid2& Grid, int j);
	void JMaxSourceTerms(Grid2& Grid, int i);
	void JMinSourceTerms(Grid2& Grid, int i);
	double AngleResidual(double dxi, double dyi, double dxj, double dyj);
	double SpaceResidual(double dx, double dy);
	void PowerLawInterp();

	/// Relaxation schemes
	void LaplaceSmoothing(Grid2& Grid);
	void EllipticSmoothing(Grid2& Grid);
	void SuccessiveOverRelaxation(Grid2& Grid);
	void GaussSeidel(Grid2& Grid);

	/// Finite difference approximations
	void FirstDerivatives(Grid2& Grid, int i, int j);
	void SecndDerivatives(Grid2& Grid, int i, int j);
	void MixedDerivatives(Grid2& Grid, int i, int j);

	/// Residual handling
	void ComputeResiduals(int i, int j, double& XResidual, double& YResidual, double& Coef);
	bool HasConverged(int n);
};

#endif