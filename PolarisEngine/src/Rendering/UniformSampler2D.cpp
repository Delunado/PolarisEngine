#include "UniformSampler2D.h"

namespace Render {
	UniformSampler2D::UniformSampler2D(std::string uniformName, GLint value): UniformBase(uniformName), uniformSampler(value)
	{
	}

	void UniformSampler2D::AddUniformToProgram(GLuint uniformPosition)
	{
		glUniform1i(uniformPosition, uniformSampler);
	}
}
