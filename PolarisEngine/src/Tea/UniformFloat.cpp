#include "UniformBase.h"

#include "UniformFloat.h"

TEA::UniformFloat::UniformFloat(std::string uniformName, GLfloat floatValue): UniformBase(uniformName), floatValue(floatValue)
{

}

void TEA::UniformFloat::AddUniformToProgram(GLuint uniformPosition)
{
	glUniform1f(uniformPosition, floatValue);
}
