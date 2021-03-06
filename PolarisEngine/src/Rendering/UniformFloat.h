#pragma once

namespace Render {
	class UniformFloat : public UniformBase
	{
	private:
		GLfloat floatValue;

	public:
		UniformFloat(std::string uniformName, GLfloat floatValue);

		void AddUniformToProgram(GLuint uniformPosition) override;
	};
}

