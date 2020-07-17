#include <iostream>
#include "Vector3f.h"

using namespace std;
using namespace Urano;

void ReadVector3f(Vector3f& vector);

int main()
{
	Vector3f vector(2.0f, 500.0f, 12.45f);
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
}

void ReadVector3f(Vector3f& vector) 
{
	std::cout << "Vector: " << vector.getX() << " " << vector.getY() << " " << vector.getZ() << std::endl;
}
