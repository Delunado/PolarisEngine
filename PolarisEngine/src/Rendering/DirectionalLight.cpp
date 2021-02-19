#include <GL/glew.h>
#include <glm/glm.hpp>

#include "LightData.h"
#include "DirectionalLight.h"

namespace Render {
	DirectionalLight::DirectionalLight(glm::vec3 direction, Color diffuseIntensity, Color specularIntensity): Light(LIGHT_TYPE::DIRECTIONAL),
		direction(direction), diffuseIntensity(diffuseIntensity), specularIntensity(specularIntensity)
	{
	}

	DirectionalLight::DirectionalLight(const DirectionalLight& other): Light(LIGHT_TYPE::DIRECTIONAL)
	{
		this->direction = other.direction;
		this->specularIntensity = other.specularIntensity;
		this->diffuseIntensity = other.diffuseIntensity;
	}

	DirectionalLight::~DirectionalLight()
	{
	}

	void DirectionalLight::SetDiffuse(Color diffuse)
	{
		this->diffuseIntensity = diffuse;
	}

	void DirectionalLight::SetSpecular(Color specular)
	{
		this->specularIntensity = specular;
	}

	void DirectionalLight::SetDirection(glm::vec3 direction)
	{
		this->direction = direction;
	}

	LightData DirectionalLight::GetLightData()
	{
		LightData lightData;

		lightData.SetLightType(LIGHT_TYPE::DIRECTIONAL);
		lightData.SetDirection(direction);
		lightData.SetDiffuse(diffuseIntensity);
		lightData.SetSpecular(specularIntensity);

		return lightData;
	}
}
