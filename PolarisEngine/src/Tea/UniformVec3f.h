#pragma once
#include "UniformBase.h"

namespace TEA {
	class UniformVec3f : public UniformBase
	{
	private:
		glm::vec3 vec3f;

	public:
		UniformVec3f(std::string uniformName, glm::vec3 vec3f);

		void AddUniformToProgram(GLuint uniformPosition) override;
	};
}

