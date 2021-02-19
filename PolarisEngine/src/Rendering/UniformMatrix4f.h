#pragma once

#include "UniformBase.h"
#include <glm/glm.hpp>

namespace Render {
	class UniformMatrix4f : public UniformBase
	{
	private:
		glm::mat4 matrix4f;

	public:
		UniformMatrix4f(std::string uniformName, glm::mat4 matrix4f);

		void AddUniformToProgram(GLuint uniformPosition) override;
	};
}