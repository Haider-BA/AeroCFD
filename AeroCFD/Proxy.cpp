#include "Proxy.h"

// Default constructor
Proxy::Proxy()
{}

// Access to the array
Proxy::Proxy(double * Array) :
								_Array(Array)
{}

// Overloaded operator [] to access the array
double& Proxy::operator[](int Index)
{
	return _Array[Index];
}

// Destructor
Proxy::~Proxy()
{}