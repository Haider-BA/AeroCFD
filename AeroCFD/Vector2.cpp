#include "Vector2.h"

// Overloaded operator [] to access the array
double & Vector2::operator[](int Index)
{
	if (Index == 0)
	{
		return _x;
	}
	else if (Index == 1)
	{
		return _y;
	}
	else
	{
		std::cout << "Error accessing vector with index: " << Index << "\n";
	}
}
