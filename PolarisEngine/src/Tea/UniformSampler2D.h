#pragma once
#include "UniformBase.h"

namespace TEA {
	class UniformSampler2D : public UniformBase
	{
	private:
		GLint uniformSampler;

	public:
		UniformSampler2D(std::string uniformName, GLint value);

		void AddUniformToProgram(GLuint uniformPosition) override;
	};
}