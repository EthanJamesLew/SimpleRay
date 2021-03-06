#ifndef VECTOR3D_CPP
#define VECTOR3D_CPP
#include "..\include\Vector3d.h"
#include "..\include\Convolution.h"

#include <cmath>
#include <limits>
#include "..\include\Convolution.h"


//Constructors
template<typename T>
Vector3d<T>::Vector3d() : x(T(0)), y(T(0)), z(T(0)) {}

template<typename T>
Vector3d<T>::Vector3d(T xx) : x(xx), y(xx), z(xx) {}

template<typename T>
Vector3d<T>::Vector3d(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}

template<typename T>
Vector3d<T>& Vector3d<T>::normalize()
{
	T nor2 = length2();
	if (nor2 > 0) {
		T invNor = 1 / sqrt(nor2);
		x *= invNor, y *= invNor, z *= invNor;
	}
	return *this;
}



//Products
//TODO: Add Cross Product
template<typename T>
Vector3d<T> Vector3d<T>::operator * (const T &f) const { return Vector3d<T>(x * f, y * f, z * f); }

template<typename T>
Vector3d<T> Vector3d<T>::operator * (const Vector3d<T> &v) const { return Vector3d<T>(x * v.x, y * v.y, z * v.z); }

template<typename T>
T Vector3d<T>::dot(const Vector3d<T> &v) const { return x * v.x + y * v.y + z * v.z; }



//Arithmetic Operations
template<typename T>
Vector3d<T> Vector3d<T>::operator - (const Vector3d<T> &v) const { return Vector3d<T>(x - v.x, y - v.y, z - v.z); }

template<typename T>
Vector3d<T> Vector3d<T>::operator + (const Vector3d<T> &v) const { return Vector3d<T>(x + v.x, y + v.y, z + v.z); }

template<typename T>
Vector3d<T>& Vector3d<T>::operator += (const Vector3d<T> &v) { x += v.x, y += v.y, z += v.z; return *this; }

template<typename T>
Vector3d<T>& Vector3d<T>::operator *= (const Vector3d<T> &v) { x *= v.x, y *= v.y, z *= v.z; return *this; }

template<typename T>
Vector3d<T> Vector3d<T>::operator - () const { return Vector3d<T>(-x, -y, -z); }



//Convolution Vector Operations
template<typename T>
Vector3d<T> Vector3d<T>::mix(const Vector3d<T> &v, T bias)
{
	return Vector3d<T>(convolution::mix(x, v.x, bias), convolution::mix(y, v.y, bias), convolution::mix(z, v.z, bias));
}

//Comparators
template<typename T>
bool Vector3d<T>::operator == (const Vector3d<T> &v)
{
	T e = std::numeric_limits<T>::epsilon();
	if ((abs(v.x - x) <= e) && (abs(v.y - y) <= e) && (abs(v.z - z) <= e))
	{
		return true;
	}
	else
	{
		return false;
	}
}



//Lengths
template<typename T>
T Vector3d<T>::length2() const { return x * x + y * y + z * z; }

template<typename T>
T Vector3d<T>::length() const { return sqrt(length2()); }


#endif