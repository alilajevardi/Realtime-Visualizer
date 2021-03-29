#include <stdlib.h>
#include <assert.h>
#include "vector.h"

CVector::CVector() : x(0.0f), y(0.0f), z(0.0f) { /* do nothing */ }


CVector::CVector(float xxx, float yyy, float zzz)
{
	set(xxx, yyy, zzz);
}

// Copy constructor
CVector::CVector(const CVector &vec)
{
	set(vec);
}


bool CVector::operator ==(const CVector &vec)
{
	return (x == vec.x && y == vec.y && z == vec.z);
}


bool CVector::operator !=(const CVector &vec)
{
	return !(x == vec.x && y == vec.y && z == vec.z);
}


CVector& CVector::operator =(const CVector &vec)
{
	set(vec);
		return *this;
}


CVector CVector::operator +(const CVector &vec)
{
	return CVector(x + vec.x, y + vec.y, z + vec.z);
}

// Subtraction operator
CVector CVector::operator -(const CVector &vec)
{
	return CVector(x - vec.x, y - vec.y, z - vec.z);
}

// Plus/Equals operator
CVector& CVector::operator +=(const CVector &vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
		return *this;
}


CVector& CVector::operator -=(const CVector &vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
		return *this;
}

// Dot product
float CVector::operator *(const CVector &vec)
{
	return (x * vec.x + y * vec.y + z * vec.z);
}


void CVector::set(float xxx, float yyy, float zzz)
{
	x = xxx;
	y = yyy;
	z = zzz;
}


void CVector::set(const CVector &vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

// Negate the CVector
void CVector::negate()
{
	x = -x;
	y = -y;
	z = -z;
}


void CVector::normalize()
{
	float length = magnitude();
	assert(length != 0.0f);

	x /= length;
	y /= length;
	z /= length;
}


void CVector::scale(float amt)
{
	x *= amt;
	y *= amt;
	z *= amt;
}


float CVector::magnitude()
{
	return sqrtf((x * x) + (y * y) + (z * z));
}


void CVector::crossProduct(const CVector &vec, CVector &result)
{
	result.x = (y * vec.z) - (vec.y * z);
	result.y = (z * vec.x) - (vec.z * x);
	result.z = (x * vec.y) - (vec.x * y);
}


CVector CVector::crossProduct(const CVector &vec)
{
	CVector result;

	result.x = (y * vec.z) - (vec.y * z);
	result.y = (z * vec.x) - (vec.z * x);
	result.z = (x * vec.y) - (vec.x * y);
		return result;
}