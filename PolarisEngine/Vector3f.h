#pragma once

namespace Urano 
{
	class Vector3f
	{
		private:
			float x, y, z;

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
			float getX();
			float getY();
			float getZ();
	};
}


