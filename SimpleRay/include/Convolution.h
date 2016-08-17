
#ifndef CONVOLUTION_H
#define CONVOLUTION_H

namespace convolution
{
	template <typename T>
	T mix(const T &a, const T &b, T c = (T)0.5);
}
#include "../src/convolution.cpp"
#endif