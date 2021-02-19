#include "UniformBase.h"

#include "UniformFloat.h"

Render::UniformFloat::UniformFloat(std::string uniformName, GLfloat floatValue): UniformBase(uniformName), floatValue(floatValue)
{

}

void Render::UniformFloat::AddUniformToProgram(GLuint uniformPosition)
{
	glUniform1f(uniformPosition, floatValue);
}
