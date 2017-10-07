#include "Elliptic.h"
#include "Proxy.h"
#include <math.h>
#include <algorithm>

#define PI 3.1415926545
#define OUT

Elliptic::Elliptic(int InputIMax, int InputJMax) :
												 _IMax(InputIMax),
												 _JMax(InputJMax)
{
	// Allocate memory for the arrays
	_P.Initialize(_IMax, _JMax);
	_Q.Initialize(_IMax, _JMax);
}

void Elliptic::LoadInputParameters()
{}

void Elliptic::GridGeneration(Grid2 & Grid)
{
	ZeroSourceTerms();
	if (InputParams.LaplaceIterations)
	{
		std::cout << "  Smoothing the Laplace Equations:\n";
		LaplaceSmoothing(Grid);
	}

	EllipticSmoothing(Grid);
}


/// Source terms
void Elliptic::ZeroSourceTerms()
{
	for (int i = 0; i <= _IMax; i++)
	{
		for (int j = 0; j <= _JMax; j++)
		{
			_P[i][j] = 0.0;
			_Q[i][j] = 0.0;
		}
	}
}

void Elliptic::ComputeSourceTerms(Grid2& Grid)
{
	/// Wall angle
	// Constant J-Boundaries
	for (int i = 1; i < _IMax; i++)
	{
		JMinSourceTerms(Grid, i);
		JMaxSourceTerms(Grid, i);		
	}

	// Constant I-Boundaries
	for (int j = 1; j < _JMax; j++)
	{
		IMinSourceTerms(Grid, j);
		IMaxSourceTerms(Grid, j);
	}
}

void Elliptic::IMaxSourceTerms(Grid2& Grid, int j)
{
	// Wall vector
	double dxj = (Grid.X[_IMax][j + 1] - Grid.X[_IMax][j - 1]) / 2.;
	double dyj = (Grid.Y[_IMax][j + 1] - Grid.Y[_IMax][j - 1]) / 2.;

	// Normal vector from the wall
	double dxi = Grid.X[_IMax - 1][j] - Grid.X[_IMax][j];
	double dyi = Grid.Y[_IMax - 1][j] - Grid.Y[_IMax][j];

	_P[_IMax][j] -= 0.*SpaceResidual(dxi, dyi);
	_Q[_IMax][j] += 0.*AngleResidual(dxi, dyi, dxj, dyj);
}

void Elliptic::IMinSourceTerms(Grid2& Grid, int j)
{
	// Wall vector
	double dxj = (Grid.X[0][j + 1] - Grid.X[0][j - 1]) / 2.;
	double dyj = (Grid.Y[0][j + 1] - Grid.Y[0][j - 1]) / 2.;

	// Normal vector from the wall
	double dxi = Grid.X[1][j] - Grid.X[0][j];
	double dyi = Grid.Y[1][j] - Grid.Y[0][j];

	_P[0][j] += 0.*SpaceResidual(dxi, dyi);
	_Q[0][j] += 0.*AngleResidual(dxi, dyi, dxj, dyj);
}

void Elliptic::JMaxSourceTerms(Grid2& Grid, int i)
{
	// Wall vector
	double dxi = (Grid.X[i + 1][_JMax] - Grid.X[i - 1][_JMax]) / 2.;
	double dyi = (Grid.Y[i + 1][_JMax] - Grid.Y[i - 1][_JMax]) / 2.;

	// Normal vector from the wall
	double dxj = Grid.X[i][_JMax - 1] - Grid.X[i][_JMax];
	double dyj = Grid.Y[i][_JMax - 1] - Grid.Y[i][_JMax];

	_P[i][_JMax] += AngleResidual(dxi, dyi, dxj, dyj);
	_Q[i][_JMax] -= 0.*SpaceResidual(dxj, dyj);
}

void Elliptic::JMinSourceTerms(Grid2& Grid, int i)
{
	// Wall vector
	double dxi = (Grid.X[i + 1][0] - Grid.X[i - 1][0]) / 2.;
	double dyi = (Grid.Y[i + 1][0] - Grid.Y[i - 1][0]) / 2.;

	// Normal vector from the wall
	double dxj = Grid.X[i][1] - Grid.X[i][0];
	double dyj = Grid.Y[i][1] - Grid.Y[i][0];

	_P[i][0] += AngleResidual(dxi, dyi, dxj, dyj);
	_Q[i][0] += SpaceResidual(dxj, dyj);
}

double Elliptic::AngleResidual(double dxi, double dyi, double dxj, double dyj)
{
	// Compute current wall angle from dot product definition
	double Dot = dxi*dxj + dyi*dyj;
	double MagnitudeI = sqrt(dxi*dxi + dyi*dyi);
	double MagnitudeJ = sqrt(dxj*dxj + dyj*dyj);
	double CurrentWallAngle = acos(Dot / (MagnitudeI*MagnitudeJ));

	double Residual = -InputParams.AngleDamping * atan(InputParams.WallAngle*PI / 180. - CurrentWallAngle);

	return Residual;
}

double Elliptic::SpaceResidual(double dx, double dy)
{
	double CurrentSpace = sqrt(dx*dx + dy*dy);
	double Residual = InputParams.SpaceDamping * atan((InputParams.WallSpace - CurrentSpace) / InputParams.WallSpace);

	return Residual;
}

void Elliptic::PowerLawInterp()
{
	for (int i = 1; i < _IMax; i++)
	{
		double Ratio = (double(i)) / (double(_IMax));
			for (int j = 1; j < _JMax; j++)
			{
				_P[i][j] = _P[0][j] * (1.0 - Ratio) + _P[_IMax][j] * Ratio;
				_Q[i][j] = _Q[0][j] * (1.0 - Ratio) + _Q[_IMax][j] * Ratio;
			}
	}

	for (int j = 1; j < _JMax; j++)
	{
		double Ratio = (double(j)) / (double(_JMax));
		for (int i = 1; i < _IMax; i++)
		{
			_P[i][j] = _P[i][0] * (1.0 - Ratio) + _P[i][_JMax] * Ratio;
			_Q[i][j] = _Q[i][0] * (1.0 - Ratio) + _Q[i][_JMax] * Ratio;
		}
	}
}

/// Relaxation schemes
void Elliptic::LaplaceSmoothing(Grid2& Grid)
{
	for (int n = 1; n <= InputParams.LaplaceIterations; n++)
	{
		std::cout << "  Iteration " << n << "\n";
		SuccessiveOverRelaxation(Grid);
	}
}

void Elliptic::EllipticSmoothing(Grid2& Grid)
{
	std::cout << "  Smoothing the Poisson equations with Source Terms:\n";
	for (int n = 1; n <= InputParams.PoissonIterations; n++)
	{
		std::cout << "  Iteration " << n << "\n";
		ComputeSourceTerms(Grid);
		//_P.TransfiniteInterpolation();
		//_Q.TransfiniteInterpolation();
		PowerLawInterp();
		SuccessiveOverRelaxation(Grid);
	}
}

// TODO Refactor
// TODO Print results
void Elliptic::SuccessiveOverRelaxation(Grid2& Grid)
{
	double ResX0 = 0.;
	double ResY0 = 0.;

	for (int n = 1; n <= InputParams.RelaxationIterations; n++)
	{
		double ResX = 0.;
		double ResY = 0.;

		for (int i = 1; i < _IMax; i++)
		{
			for (int j = 1; j < _JMax; j++)
			{
				FirstDerivatives(Grid, i, j);
				SecndDerivatives(Grid, i, j);
				MixedDerivatives(Grid, i, j);

				double Alpha = _XJ*_XJ + _YJ*_YJ;
				double Gamma = _XI*_XI + _YI*_YI;
				double Beta = _XI*_XJ + _YI*_YJ;
				double Coef = 2.*(Alpha + Gamma);

				double XResidual = Alpha*(_XII + _P[i][j] * _XI) -
					2.0*Beta*_XIJ +
					Gamma*(_XJJ + _Q[i][j] * _XJ);

				double YResidual = Alpha*(_YII + _P[i][j] * _YI) -
					2.0*Beta*_YIJ +
					Gamma*(_YJJ + _Q[i][j] * _YJ);

				// Update residual tracking for convergence
				ResX += XResidual*XResidual;
				ResY += YResidual*YResidual;

				Grid.X[i][j] += InputParams.OverrelaxationFactor*XResidual / Coef;
				Grid.Y[i][j] += InputParams.OverrelaxationFactor*YResidual / Coef;
			}
		}

		if (n == 0)
		{
			double ResX0 = ResX;
			double ResY0 = ResY;
		}
		else
		{
			ResX = ResX / ResX0;
			ResY = ResY / ResY0;
		}
	}
}

void Elliptic::GaussSeidel(Grid2& Grid)
{}

void Elliptic::FirstDerivatives(Grid2& Grid, int i, int j)
{
	_XI = 0.5*(Grid.X[i + 1][j] - Grid.X[i - 1][j]);
	_XJ = 0.5*(Grid.X[i][j + 1] - Grid.X[i][j - 1]);
	_YI = 0.5*(Grid.Y[i + 1][j] - Grid.Y[i - 1][j]);
	_YJ = 0.5*(Grid.Y[i][j + 1] - Grid.Y[i][j - 1]);
}

void Elliptic::SecndDerivatives(Grid2& Grid, int i, int j)
{
	_XII = Grid.X[i + 1][j] + Grid.X[i - 1][j] - 2.0*Grid.X[i][j];
	_XJJ = Grid.X[i][j + 1] + Grid.X[i][j - 1] - 2.0*Grid.X[i][j];	

	_YII = Grid.Y[i + 1][j] + Grid.Y[i - 1][j] - 2.0*Grid.Y[i][j];
	_YJJ = Grid.Y[i][j + 1] + Grid.Y[i][j - 1] - 2.0*Grid.Y[i][j];
}


void Elliptic::MixedDerivatives(Grid2& Grid, int i, int j)
{
	_XIJ = 0.25*(Grid.X[i + 1][j + 1] - Grid.X[i + 1][j - 1] -
		Grid.X[i - 1][j + 1] + Grid.X[i - 1][j - 1]);
	_YIJ = 0.25*(Grid.Y[i + 1][j + 1] - Grid.Y[i + 1][j - 1] -
		Grid.Y[i - 1][j + 1] + Grid.Y[i - 1][j - 1]);
}

