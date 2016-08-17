#ifndef CONVOLUTION_CPP
#define CONVOLUTION_CPP

#include "../include/convolution.h"

namespace convolution
{
	template <typename T>
	T mix(const T &a, const T &b, T c)
	{
		return a*c + ((T)1.0 - c)*b;
	}
}

#endif