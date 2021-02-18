#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>

#include "Shader.h"

namespace TEA {
	Shader::Shader(GLenum shaderType, std::string shaderFilePath) : id(0)
	{
		try {
			std::string shaderCode = LoadShaderScript(shaderFilePath);

			GenerateShader(shaderType, shaderCode);
		}
		catch (std::exception& e) {
			const std::string message = " - in function PAGShader()";
			throw std::runtime_error(e.what() + message);
		}
	}

	Shader::Shader(const Shader& other)
	{
		this->id = other.id;
	}

	Shader::~Shader()
	{
		glDeleteShader(id);
	}

	Shader* Shader::CreateShader(GLenum shaderType, std::string shaderCode)
	{
		Shader* shader = new Shader(shaderType, shaderCode);
		return shader;
	}

	void Shader::GenerateShader(GLenum shaderType, std::string shaderCode)
	{
		GLint errorStatus;

		const GLchar* code = shaderCode.c_str();

		id = glCreateShader(shaderType);
		glShaderSource(id, 1, &code, nullptr);
		glCompileShader(id);

		try {
			glGetShaderiv(id, GL_COMPILE_STATUS, &errorStatus);

			if (errorStatus != GL_TRUE) {
				GLint logLen = 0;
				std::string logString = "";

				glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLen);

				if (logLen > 0) {
					char* cLogString = new char[logLen];
					GLint written = 0;
					glGetShaderInfoLog(id, logLen, &written, cLogString);
					logString.assign(cLogString);
					delete[] cLogString;
					throw std::runtime_error("Error Compiling Shader:\n" + logString + "\n");
				}
			}
		}
		catch (std::exception& e) {
			const std::string message = " - in function GenerateShader()";
			throw std::runtime_error(e.what() + message);
		}
	}

	std::string Shader::LoadShaderScript(std::string filePath)
	{
		std::fstream scriptFile;
		scriptFile.open(filePath);

		std::string scriptCode = "";

		if (scriptFile.is_open()) {
			std::string line;
			while (getline(scriptFile, line)) {
				scriptCode += (line + "\n");
			}

			scriptFile.close();
		}
		else {
			const std::string message = "Can't open " + filePath + " file!";
			throw std::runtime_error(message);
		}

		return scriptCode;
	}

	GLuint Shader::GetID() const
	{
		return id;
	}
}