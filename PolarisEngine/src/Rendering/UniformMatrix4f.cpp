#include "UniformMatrix4f.h"

namespace Render {
	UniformMatrix4f::UniformMatrix4f(std::string uniformName, glm::mat4 matrix4f) : UniformBase(uniformName), matrix4f(matrix4f)
	{
	}

	void UniformMatrix4f::AddUniformToProgram(GLuint uniformPosition)
	{
		glUniformMatrix4fv(uniformPosition, 1, GL_FALSE, glm::value_ptr(matrix4f));
	}
}