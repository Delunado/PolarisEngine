#include "Transform.h"

namespace TEA {
	Transform::Transform() : position(glm::vec3(0, 0, 0)), rotation(glm::vec3(0, 0, 0)), scale(glm::vec3(1.0f))
	{

	}

	Transform::~Transform()
	{
	}

	glm::vec3 Transform::GetPosition()
	{
		return position;
	}

	void Transform::SetPosition(glm::vec3 position)
	{
		this->position = position;
	}

	glm::vec3 Transform::GetRotation()
	{
		return rotation;
	}

	void Transform::SetRotation(glm::vec3 rotation)
	{
		this->rotation = rotation;
	}

	glm::vec3 Transform::GetScale()
	{
		return scale;
	}

	void Transform::SetScale(glm::vec3 scale)
	{
		this->scale = scale;
	}

	glm::mat4 Transform::GetModelMatrix()
	{
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);

		glm::mat4 rotationZ = glm::rotate(translation, glm::radians(rotation[2]), glm::vec3(0, 0, 1));
		glm::mat4 rotationY = glm::rotate(rotationZ, glm::radians(rotation[1]), glm::vec3(0, 1, 0));
		glm::mat4 rotationX = glm::rotate(rotationY, glm::radians(rotation[0]), glm::vec3(1, 0, 0));

		glm::mat4 scaled = glm::scale(rotationX, scale);

		return scaled;
	}
}