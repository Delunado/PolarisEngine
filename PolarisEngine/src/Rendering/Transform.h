#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace Render {
	class Transform
	{
	private:
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		glm::mat4 modelMatrix;

		void CalculateModelMatrix();

	public:
		Transform();

		~Transform();

		glm::vec3 GetPosition();
		void SetPosition(glm::vec3 position);

		glm::vec3 GetRotation();
		void SetRotation(glm::vec3 rotation);

		glm::vec3 GetScale();
		void SetScale(glm::vec3 scale);

		glm::mat4 GetModelMatrix();
	};
}