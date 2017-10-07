#include "Elliptic.h"
#include "Proxy.h"
#include <math.h>
#include <algorithm>

#define PI 3.1415926545

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
	ComputeSourceTerms(Grid);
	_P.TransfiniteInterpolation();
	_Q.TransfiniteInterpolation();
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
	for (int i = 0; i <= _IMax; i++)
	{
		JMinSourceTerms(Grid, i);
		JMaxSourceTerms(Grid, i);		
	}

	// Constant I-Boundaries
	for (int j = 0; j <= _JMax; j++)
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
	double dxi = Grid.X[_IMax][j] - Grid.Y[_IMax - 1][j];
	double dyi = Grid.Y[_IMax][j] - Grid.Y[_IMax - 1][j];

	_P[_IMax][j] += std::max(0.0, SpaceResidual(dxj, dyj));
	_Q[_IMax][j] += std::max(0.0, AngleResidual(dxi, dyi, dxj, dyj));
}

void Elliptic::IMinSourceTerms(Grid2& Grid, int j)
{
	// Wall vector
	double dxj = (Grid.X[0][j + 1] - Grid.X[0][j - 1]) / 2.;
	double dyj = (Grid.Y[0][j + 1] - Grid.Y[0][j - 1]) / 2.;

	// Normal vector from the wall
	double dxi = Grid.X[1][j] - Grid.Y[0][j];
	double dyi = Grid.Y[1][j] - Grid.Y[0][j];

	_P[0][j] += std::max(0.0, SpaceResidual(dxj, dyj));
	_Q[0][j] += std::max(0.0, AngleResidual(dxi, dyi, dxj, dyj));
}

void Elliptic::JMaxSourceTerms(Grid2& Grid, int i)
{
	// Wall vector
	double dxi = (Grid.X[i + 1][_JMax] - Grid.X[i - 1][_JMax]) / 2.;
	double dyi = (Grid.Y[i + 1][_JMax] - Grid.Y[i - 1][_JMax]) / 2.;

	// Normal vector from the wall
	double dxj = Grid.X[i][_JMax] - Grid.Y[i][_JMax - 1];
	double dyj = Grid.Y[i][_JMax] - Grid.Y[i][_JMax - 1];

	_P[i][_JMax] += std::max(0.0, AngleResidual(dxi, dyi, dxj, dyj));
	_Q[i][_JMax] += std::max(0.0, SpaceResidual(dxj, dyj));
}

void Elliptic::JMinSourceTerms(Grid2& Grid, int i)
{
	// Wall vector
	double dxi = (Grid.X[i + 1][0] - Grid.X[i - 1][0]) / 2.;
	double dyi = (Grid.Y[i + 1][0] - Grid.Y[i - 1][0]) / 2.;

	// Normal vector from the wall
	double dxj = Grid.X[i][1] - Grid.Y[i][0];
	double dyj = Grid.Y[i][1] - Grid.Y[i][0];

	_P[i][0] += std::max(0.0, AngleResidual(dxi, dyi, dxj, dyj));
	_Q[i][0] += std::max(0.0, SpaceResidual(dxj, dyj));
}

double Elliptic::AngleResidual(double dxi, double dyi, double dxj, double dyj)
{
	// Compute current wall angle from dot product definition
	double Dot = dxi*dxj + dyi*dyj;
	double MagnitudeI = sqrt(dxi*dxi + dyi*dyi);
	double MagnitudeJ = sqrt(dxj*dxj + dyj*dyj);
	double CurrentWallAngle = acos(Dot / (MagnitudeI*MagnitudeJ));

	double Residual = -_AngleDamping * atan((_WallAngle*PI / 180 - CurrentWallAngle)/_WallAngle*PI / 180);

	return Residual;
}

double Elliptic::SpaceResidual(double dx, double dy)
{
	double CurrentSpace = sqrt(dx*dx + dy*dy);
	double Residual = _SpaceDamping * atan((_WallSpace - CurrentSpace) / _WallSpace);

	return Residual;
}

/// Relaxation schemes
void Elliptic::SuccessiveOverRelaxation()
{}

void Elliptic::GaussSeidel()
{}
