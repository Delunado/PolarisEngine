#include "UniformVec3f.h"

namespace Render {
	UniformVec3f::UniformVec3f(std::string uniformName, glm::vec3 vec3f) : UniformBase(uniformName), vec3f(vec3f)
	{
	}

	void UniformVec3f::AddUniformToProgram(GLuint uniformPosition)
	{
		glUniform3f(uniformPosition, vec3f.x, vec3f.y, vec3f.z);
	}
}
