#pragma once
#include <math.h>

namespace Urano 
{
	class Vector3f
	{
		private:
			float x, y, z;

			bool isVectorZero() const;

		public:
			//Constructor
			Vector3f(float x, float y, float z);

			//Copy Constructors
			Vector3f(const Vector3f& v);
			Vector3f& operator=(const Vector3f& v);

			//Destructor
			~Vector3f();

			//Operations
			Vector3f operator*(const float scalar) const;
			Vector3f operator/(const float scalar) const;
			Vector3f operator+(const Vector3f& v) const;
			Vector3f operator-(const Vector3f& v) const;

			//Getters/Setters
			float GetX();
			float GetY();
			float GetZ();

			//Methods
			float Magnitude() const;

			void Normalize();
			Vector3f Normalized() const;

			static float Distance(Vector3f& vector1, Vector3f& vector2);
	};
}


