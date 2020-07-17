#include "Vector3f.h"

Urano::Vector3f::Vector3f(float x, float y, float z):x(x), y(y), z(z)
{}

Urano::Vector3f::Vector3f(const Vector3f& v):x(v.x), y(v.y), z(v.z)
{}

Urano::Vector3f& Urano::Vector3f::operator=(const Vector3f& v)
{
	x = v.x;
	y = v.y;
	z = v.z;

	return *this;
}

Urano::Vector3f::~Vector3f()
{
}

Urano::Vector3f Urano::Vector3f::operator*(const float scalar) const
{
	Vector3f vector(x*scalar, y*scalar, z*scalar);

	return vector;
}

Urano::Vector3f Urano::Vector3f::operator/(const float scalar) const
{
	Vector3f vector(x/scalar, y/scalar, z/scalar);

	return vector;
}

Urano::Vector3f Urano::Vector3f::operator+(const Vector3f& v) const
{
	Vector3f vector(this->x+v.x, this->y+v.y, this->z+v.z);

	return vector;
}

Urano::Vector3f Urano::Vector3f::operator-(const Vector3f& v) const
{
	Vector3f vector(this->x - v.x, this->y - v.y, this->z - v.z);

	return vector;
}

float Urano::Vector3f::getX()
{
	return this->x;
}

float Urano::Vector3f::getY()
{
	return this->y;
}

float Urano::Vector3f::getZ()
{
	return this->z;
}


