#pragma once
//Epsilon to compare floating point values
template <typename T>
bool floatEq(T a, T b, T tol = (T)0)
{
	double e = std::numeric_limits<T>::epsilon();
	if ((a - b) <= (e + tol))
	{
		return true;
	}
	else
	{
		return false;
	}
}