#pragma once

#include <vector>
#include "UniformBase.h"

namespace Render {
	class Shader;

	class ShaderProgram
	{
	private:
		GLuint id;

		std::vector<const Shader*> linkedShaders;
		std::vector<UniformBase*> uniformVector;

		void CreateProgram();
	public:
		ShaderProgram();

		ShaderProgram(const ShaderProgram& sp);

		~ShaderProgram();

		static ShaderProgram* CreateShaderProgram(const Shader* vertexShader, const Shader* fragmentShader);

		//Links the given Shader to this Shader Program 
		void LinkShaderProgram();

		//Attach a new Shader to the Shader Program
		void AttachShader(const Shader* shader);

		void AddUniformMatrix4f(std::string uniformName, glm::mat4 uniformMatrix4f);
		void AddUniformVec3f(std::string uniformName, glm::vec3 uniformVec3f);
		void AddUniformFloat(std::string uniformName, GLfloat uniformFloat);
		void AddUniformSampler2D(std::string uniformName, GLint uniformSampler2D);

		//Activate the Shader Program and send the given Uniforms
		void Activate();

		//Select the subroutine to use in the linked Shaders
		void SelectSubroutine(GLenum shaderType, std::string subroutineNameRender, std::string subroutineNameLight);



		GLuint GetID() const;
	};
}