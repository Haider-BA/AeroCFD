#include "Vector2.h"

// Default constructor
Vector2::Vector2()
{
	// Initialize to 0
	x = 0.0;
	y = 0.0;
}

Vector2::Vector2(double InputX, double InputY) :
												x(InputX),
												y(InputY)
{}

Vector2::~Vector2()
{}

// Vector addition
Vector2 Vector2::operator+(const Vector2& Vector) const
{
	return Vector2(x + Vector.x, y + Vector.y);
}

// Vector subtraction
Vector2 Vector2::operator-(const Vector2& Vector) const
{
	return Vector2(x - Vector.x, y - Vector.y);
}

// Scalar multiplication
Vector2 Vector2::operator*(const double Scalar) const
{
	return Vector2(x*Scalar, y*Scalar);
}

// Magnitude squared
double Vector2::Length2() const
{
	return (x*x + y*y);
}

// Magnitude
double Vector2::Length() const
{
	return (sqrt(x*x + y*y));
}

// Normalize
void Vector2::Normalize()
{
	double Magnitude = Length();
	x /= Magnitude;
	y /= Magnitude;
}

// Dot product
double Vector2::Dot(const Vector2& Vector) const
{
	return (x*Vector.x + y*Vector.y);
}

// Cross product
double Vector2::Cross(const Vector2& Vector) const
{
	// Mostly a hack since 2D cross product isnt well defined
	return (x*Vector.y - y*Vector.x);
}
