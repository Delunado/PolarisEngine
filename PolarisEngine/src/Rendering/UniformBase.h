#pragma once

#include <string>
#include <gl/glew.h>
#include <glm/gtc/type_ptr.hpp>

namespace Render {
	class UniformBase
	{
	protected:
		std::string uniformName;

	public:
		UniformBase(std::string uniformName);
		std::string GetUniformName();

		virtual void AddUniformToProgram(GLuint uniformPosition) = 0;
	};
}