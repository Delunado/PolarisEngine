#pragma once

namespace Render {
	class Shader
	{
	private:
		GLuint id; // Shader Identifier

		//Creates a new shader of the specified type and from the specified code
		void GenerateShader(GLenum shaderType, std::string shaderCode);

		//Load a file from memory and returns it as a string.
		std::string LoadShaderScript(std::string filePath);
	public:
		Shader(GLenum shaderType, std::string shaderCode);

		Shader(const Shader& other);

		~Shader();

		static Shader* CreateShader(GLenum shaderType, std::string shaderCode);

		GLuint GetID() const;
	};
}