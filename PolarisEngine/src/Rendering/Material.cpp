#include "ShaderProgram.h"
#include "Texture.h"

#include "Material.h"

namespace Render {
	Material::Material(Color ambient, Color diffuse, Color specular, GLfloat exponent): ambient(ambient), diffuse(diffuse), specular(specular), 
		exponent(exponent), colorTexture(nullptr), normalTexture(nullptr), shaderProgram(nullptr), shaderProgramNormalMap(nullptr), normalMapActive(false)
	{
	}

	Material::Material(const Material& other)
	{
		this->ambient = other.ambient;
		this->diffuse = other.diffuse;
		this->specular = other.specular;
		this->exponent = other.exponent;
		this->colorTexture = other.colorTexture;
		this->normalTexture = other.normalTexture;
		this->shaderProgram = other.shaderProgram;
		this->shaderProgramNormalMap = other.shaderProgramNormalMap;
		this->normalMapActive = false;
	}

	Material::~Material()
	{
		colorTexture = nullptr;
		normalTexture = nullptr;
	}

	Material* Material::CreateMaterial(Color ambient, Color diffuse, Color specular, GLfloat exponent)
	{
		Material* material = new Material(ambient, diffuse, specular, exponent);
		return material;
	}

	Color& Material::GetAmbient()
	{
		return ambient;
	}

	Color& Material::GetDiffuse()
	{
		return diffuse;
	}

	Color& Material::GetSpecular()
	{
		return specular;
	}

	GLfloat Material::GetExponent() const
	{
		return exponent;
	}

	void Material::SetAmbient(Color& ambient)
	{
		this->ambient = ambient;
	}

	void Material::SetDiffuse(Color& diffuse)
	{
		this->diffuse = diffuse;
	}

	void Material::SetSpecular(Color& specular)
	{
		this->specular = specular;
	}

	void Material::SetExponent(GLfloat exponent)
	{
		this->exponent = exponent;
	}

	void Material::SetColorTexture(Texture* texture)
	{
		this->colorTexture = texture;
	}

	Texture* Material::GetColorTexture()
	{
		return colorTexture;
	}

	void Material::SetNormalTexture(Texture* texture)
	{
		this->normalTexture = texture;
	}

	Texture* Material::GetNormalTexture()
	{
		return normalTexture;
	}

	void Material::SetShaderProgram(ShaderProgram* shaderProgram)
	{
		this->shaderProgram = shaderProgram;
	}

	ShaderProgram* Material::GetShaderProgram()
	{
		return shaderProgram;
	}

	void Material::SetShaderProgramNormalMap(ShaderProgram* shaderProgramNormalMap)
	{
		this->shaderProgramNormalMap = shaderProgramNormalMap;
	}

	ShaderProgram* Material::GetShaderProgramNormalMap()
	{
		return shaderProgramNormalMap;
	}

	void Material::AddUniformMatrix4f(std::string uniformName, glm::mat4 uniformMatrix4f)
	{
		if (shaderProgram != nullptr) {
			shaderProgram->AddUniformMatrix4f(uniformName, uniformMatrix4f);
		}

		if (shaderProgramNormalMap != nullptr) {
			shaderProgramNormalMap->AddUniformMatrix4f(uniformName, uniformMatrix4f);
		}
	}

	void Material::AddUniformVec3f(std::string uniformName, glm::vec3 uniformVec3f)
	{
		if (shaderProgram != nullptr) {
			shaderProgram->AddUniformVec3f(uniformName, uniformVec3f);
		}
	}

	void Material::AddUniformFloat(std::string uniformName, GLfloat uniformFloat)
	{
		if (shaderProgram != nullptr) {
			shaderProgram->AddUniformFloat(uniformName, uniformFloat);
		}
	}

	void Material::SetNormalMapActive(bool active)
	{
		normalMapActive = active;
	}

	bool Material::IsNormalMapActive() {
		return normalMapActive;
	}
}