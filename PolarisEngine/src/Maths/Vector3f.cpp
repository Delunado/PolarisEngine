#include "Vector3f.h"

namespace Math {
	bool Vector3f::isVectorZero() const
	{
		return (this->x == 0.0f && this->y == 0.0f && this->z == 0.0f);
	}

	Vector3f::Vector3f(float x, float y, float z) :x(x), y(y), z(z)
	{}

	Vector3f::Vector3f(const Vector3f& v) : x(v.x), y(v.y), z(v.z)
	{}

	Vector3f& Vector3f::operator=(const Vector3f& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}

	Vector3f::~Vector3f()
	{
	}

	Vector3f Vector3f::operator*(const float scalar) const
	{
		Vector3f vector(x * scalar, y * scalar, z * scalar);

		return vector;
	}

	Vector3f Vector3f::operator/(const float scalar) const
	{
		Vector3f vector(x / scalar, y / scalar, z / scalar);

		return vector;
	}

	Vector3f Vector3f::operator+(const Vector3f& v) const
	{
		Vector3f vector(this->x + v.x, this->y + v.y, this->z + v.z);

		return vector;
	}

	Vector3f Vector3f::operator-(const Vector3f& v) const
	{
		Vector3f vector(this->x - v.x, this->y - v.y, this->z - v.z);

		return vector;
	}

	float Vector3f::GetX()
	{
		return this->x;
	}

	float Vector3f::GetY()
	{
		return this->y;
	}

	float Vector3f::GetZ()
	{
		return this->z;
	}

	float Vector3f::Magnitude() const
	{
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}

	void Vector3f::Normalize()
	{
		//If it is the vector 0 we can't normalize it, so it remains the same.
		if (this->isVectorZero())
			return;

		float magnitude = this->Magnitude();

		this->x /= magnitude;
		this->y /= magnitude;
		this->z /= magnitude;
	}

	Vector3f Vector3f::Normalized() const
	{
		if (this->isVectorZero()) {
			return Vector3f(0.0f, 0.0f, 0.0f);
		}
		else {
			float magnitude = Magnitude();
			return Vector3f(this->x / magnitude, this->y / magnitude, this->z / magnitude);
		}
	}

	float Vector3f::Distance(const Vector3f& vector1, const Vector3f& vector2)
	{
		return (vector2 - vector1).Magnitude();
	}

	float Vector3f::DotProduct(const Vector3f& vector1, const Vector3f& vector2)
	{
		return (vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z);
	}

	Vector3f Vector3f::CrossProduct(const Vector3f& vector1, const Vector3f& vector2)
	{
		return Vector3f(vector1.y * vector2.z - vector1.z * vector2.y,
			vector1.z * vector2.x - vector1.x * vector2.z,
			vector1.x * vector2.y - vector1.y * vector2.x);
	}
}