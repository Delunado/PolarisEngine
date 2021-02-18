#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Shader.h"
#include "UniformMatrix4f.h"
#include "UniformVec3f.h"
#include "UniformFloat.h"
#include "UniformSampler2D.h"

#include "ShaderProgram.h"

#include "Debug.h"

namespace TEA {
	ShaderProgram::ShaderProgram() : linkedShaders(std::vector<const Shader*>()), uniformVector(std::vector<UniformBase*>())
	{
		CreateProgram();
	}

	ShaderProgram::ShaderProgram(const ShaderProgram& sp) : id(sp.id), linkedShaders(sp.linkedShaders)
	{

	}

	ShaderProgram::~ShaderProgram()
	{
		for (GLuint i = 0; i < linkedShaders.size(); i++) {
			glDetachShader(id, linkedShaders[i]->GetID());
		}

		glDeleteProgram(id);
	}

	void ShaderProgram::CreateProgram()
	{
		id = glCreateProgram();

		assert(id != GL_FALSE);

		try {
			if (id == GL_FALSE) {
				throw std::runtime_error("Cannot create shader program");
			}
		}
		catch (std::exception& e) {
			const std::string message = " - in function CreateProgram()";
			throw std::runtime_error(e.what() + message);
		}
	}

	void ShaderProgram::LinkShaderProgram()
	{
		glLinkProgram(id);

		GLint errorStatus;

		try {
			glGetProgramiv(id, GL_LINK_STATUS, &errorStatus);
			if (errorStatus != GL_TRUE) {
				GLint logLen = 0;
				std::string logString = "";

				glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLen);

				if (logLen > 0) {
					char* cLogString = new char[logLen];
					GLint written = 0;
					glGetProgramInfoLog(id, logLen, &written, cLogString);
					logString.assign(cLogString);
					delete[] cLogString;
				}

				throw std::runtime_error("Error Linking Shader:\n" + logString);
			}
		}
		catch (std::exception& e) {
			const std::string message = " - in function LinkShader()";
			throw std::runtime_error(e.what() + message);
			return;
		}
	}

	void ShaderProgram::AttachShader(const Shader* shader)
	{
		//First we attach the shader
		glAttachShader(id, shader->GetID());

		linkedShaders.push_back(shader);
	}

	void ShaderProgram::AddUniformMatrix4f(std::string uniformName, glm::mat4 uniformMatrix4f)
	{
		uniformVector.push_back(new UniformMatrix4f(uniformName, uniformMatrix4f));
	}

	void ShaderProgram::AddUniformVec3f(std::string uniformName, glm::vec3 uniformVec3f)
	{
		uniformVector.push_back(new UniformVec3f(uniformName, uniformVec3f));
	}

	void ShaderProgram::AddUniformFloat(std::string uniformName, GLfloat uniformFloat)
	{
		uniformVector.push_back(new UniformFloat(uniformName, uniformFloat));
	}

	void ShaderProgram::AddUniformSampler2D(std::string uniformName, GLint uniformSampler2D)
	{
		uniformVector.push_back(new UniformSampler2D(uniformName, uniformSampler2D));
	}

	void ShaderProgram::Activate()
	{
		glUseProgram(id);

		for (int i = 0; i < uniformVector.size(); i++) {
			GLint uniformPosition = glGetUniformLocation(id, uniformVector[i]->GetUniformName().c_str());

			try {
				if (uniformPosition != -1) {
					uniformVector[i]->AddUniformToProgram(uniformPosition);
				} else {
					throw std::runtime_error("Cannot find uniform: " + uniformVector[i]->GetUniformName());
				}
			}
			catch (std::exception& e) {
				const std::string message = " - in function Activate()";
				throw std::runtime_error(e.what() + message);
			}

			delete uniformVector[i];
		}

		uniformVector.clear();
	}

	void ShaderProgram::SelectSubroutine(GLenum shaderType, std::string subroutineNameRender, std::string subroutineNameLight)
	{
		GLuint subroutines[2];
		GLuint lightIndex = glGetSubroutineUniformLocation(id, shaderType, "lightMode");
		GLuint renderIndex = glGetSubroutineUniformLocation(id, shaderType, "chosenColor");

		GLuint subroutineRenderIndex;
		GLuint subroutineLightIndex;

		subroutineRenderIndex = glGetSubroutineIndex(id, shaderType, subroutineNameRender.c_str());
		subroutineLightIndex = glGetSubroutineIndex(id, shaderType, subroutineNameLight.c_str());

		if (subroutineRenderIndex == GL_INVALID_INDEX || subroutineLightIndex == GL_INVALID_INDEX)
			throw std::runtime_error("Error Rendering Model - Can't find the subroutine.\n");

		subroutines[lightIndex] = subroutineLightIndex;
		subroutines[renderIndex] = subroutineRenderIndex;

		glUniformSubroutinesuiv(shaderType, 2, subroutines);
	}

	ShaderProgram* ShaderProgram::CreateShaderProgram(const Shader* vertexShader, const Shader* fragmentShader)
	{
		ShaderProgram* shaderProgram = new TEA::ShaderProgram();
		shaderProgram->AttachShader(vertexShader);
		shaderProgram->AttachShader(fragmentShader);
		shaderProgram->LinkShaderProgram();

		return shaderProgram;
	}

	GLuint ShaderProgram::GetID() const
	{
		return id;
	}
}