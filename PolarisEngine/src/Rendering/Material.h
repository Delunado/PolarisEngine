#pragma once
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Color.h"

namespace Render {

	class ShaderProgram;
	class Texture;

	class Material
	{
	private:
		Color ambient;
		Color diffuse;
		Color specular;
		GLfloat exponent;

		ShaderProgram* shaderProgram;
		ShaderProgram* shaderProgramNormalMap;

		Texture* colorTexture;
		Texture* normalTexture;

		bool normalMapActive;

	public:
		Material(Color ambient, Color diffuse, Color specular, GLfloat exponent);

		Material(const Material& other);

		~Material();

		static Material* CreateMaterial(Color ambient, Color diffuse, Color specular, GLfloat exponent);

		Color& GetAmbient();
		Color& GetDiffuse();
		Color& GetSpecular();
		GLfloat GetExponent() const;

		void SetAmbient(Color& ambient);
		void SetDiffuse(Color& diffuse);
		void SetSpecular(Color& specular);
		void SetExponent(GLfloat exponent);

		void SetColorTexture(Texture* texture);
		Texture* GetColorTexture();		
		
		void SetNormalTexture(Texture* texture);
		Texture* GetNormalTexture();

		void SetShaderProgram(ShaderProgram* shaderProgram);
		ShaderProgram* GetShaderProgram();

		void SetShaderProgramNormalMap(ShaderProgram* shaderProgramNormalMap);
		ShaderProgram* GetShaderProgramNormalMap();

		void AddUniformMatrix4f(std::string uniformName, glm::mat4 uniformMatrix4f);
		void AddUniformVec3f(std::string uniformName, glm::vec3 uniformVec3f);
		void AddUniformFloat(std::string uniformName, GLfloat uniformFloat);

		void SetNormalMapActive(bool active);
		bool IsNormalMapActive();
	};
}