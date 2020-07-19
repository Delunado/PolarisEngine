#include <iostream>
#include "Vector3f.h"

using namespace std;
using namespace Urano;

void ReadVector3f(Vector3f& vector);

int main()
{
	Vector3f vector(0.0f, 0.0f, 0.0f);
	ReadVector3f(vector);
	std::cout << std::endl;

	std::cout << "Constructor copy: " << std::endl;
	Vector3f constructorCopy(vector);
	ReadVector3f(constructorCopy);
	std::cout << std::endl;

	std::cout << "Assignment copy: " << std::endl;
	Vector3f assignmentCopy = vector;
	ReadVector3f(assignmentCopy);
	std::cout << std::endl;

	std::cout << "Scalar multiplication: " << std::endl;
	Vector3f scalarMulVector = vector * 3.0f;
	ReadVector3f(scalarMulVector);
	std::cout << std::endl;

	std::cout << "Vector negation: " << std::endl;
	Vector3f negatedVector = vector * -1.0f;
	ReadVector3f(negatedVector);
	std::cout << std::endl;

	std::cout << "Sum vector + negated vector: " << std::endl;
	Vector3f sumVector = vector + negatedVector;
	ReadVector3f(sumVector);
	std::cout << std::endl;

	std::cout << "Difference vector - multiplicated vector: " << std::endl;
	Vector3f diffVector = vector - scalarMulVector;
	ReadVector3f(diffVector);
	std::cout << std::endl;

	std::cout << "Vector length" << std::endl;
	std::cout << vector.Magnitude() << std::endl;

	std::cout << "Normalized vector from vector: " << std::endl;
	Vector3f normalizedVector = vector.Normalized();
	ReadVector3f(normalizedVector);
	std::cout << std::endl;

	std::cout << "Vector normalized: " << std::endl;
	vector.Normalize();
	ReadVector3f(vector);
	std::cout << std::endl;

	std::cout << "Distance from v1 to v2: " << std::endl;
	Vector3f v1(2.0f, 2.0f, 0.0f);
	Vector3f v2(4.0f, 4.0f, 0.0f);

	std::cout << "Distance: " << Vector3f::Distance(vector, v2) << std::endl;
}

void ReadVector3f(Vector3f& vector) 
{
	std::cout << "Vector: " << vector.GetX() << " " << vector.GetY() << " " << vector.GetZ() << std::endl;
}
