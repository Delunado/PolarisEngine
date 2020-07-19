#include "Vector3f.h"

bool Urano::Vector3f::isVectorZero() const
{
	return (this->x == 0.0f && this->y == 0.0f && this->z == 0.0f);
}

Urano::Vector3f::Vector3f(float x, float y, float z) :x(x), y(y), z(z)
{}

Urano::Vector3f::Vector3f(const Vector3f& v) : x(v.x), y(v.y), z(v.z)
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
	Vector3f vector(x * scalar, y * scalar, z * scalar);

	return vector;
}

Urano::Vector3f Urano::Vector3f::operator/(const float scalar) const
{
	Vector3f vector(x / scalar, y / scalar, z / scalar);

	return vector;
}

Urano::Vector3f Urano::Vector3f::operator+(const Vector3f& v) const
{
	Vector3f vector(this->x + v.x, this->y + v.y, this->z + v.z);

	return vector;
}

Urano::Vector3f Urano::Vector3f::operator-(const Vector3f& v) const
{
	Vector3f vector(this->x - v.x, this->y - v.y, this->z - v.z);

	return vector;
}

float Urano::Vector3f::GetX()
{
	return this->x;
}

float Urano::Vector3f::GetY()
{
	return this->y;
}

float Urano::Vector3f::GetZ()
{
	return this->z;
}

float Urano::Vector3f::Magnitude() const
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

void Urano::Vector3f::Normalize()
{
	//If it is the vector 0 we can't normalize it, so it remains the same.
	if (this->isVectorZero())
		return;

	float magnitude = this->Magnitude();

	this->x /= magnitude;
	this->y /= magnitude;
	this->z /= magnitude;
}

Urano::Vector3f Urano::Vector3f::Normalized() const
{
	if (this->isVectorZero()) {
		return Vector3f(0.0f, 0.0f, 0.0f);
	}
	else {
		float magnitude = Magnitude();
		return Vector3f(this->x / magnitude, this->y / magnitude, this->z / magnitude);
	}
}

float Urano::Vector3f::Distance(Vector3f& vector1, Vector3f& vector2)
{
	return (vector2 - vector1).Magnitude();
}


