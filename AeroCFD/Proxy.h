#ifndef PROXY_H
#define PROXY_H
#pragma once

class Proxy
{
public:
	// Default constructor
	Proxy();

	// Constructor
	Proxy(double* Array);

	// Access to the array
	double& operator[](int Index);

	// Destructor
	~Proxy();
private:	
	double* _Array;
};

#endif
