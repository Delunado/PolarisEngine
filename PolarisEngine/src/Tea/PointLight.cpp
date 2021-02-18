#include <GL/glew.h>
#include <glm/glm.hpp>

#include "LightData.h"

#include "PointLight.h"

namespace TEA {
	PointLight::PointLight(glm::vec3 position, Color diffuseIntensity, Color specularIntensity): Light(LIGHT_TYPE::POINT),
		position(position), diffuseIntensity(diffuseIntensity), specularIntensity(specularIntensity)
	{
	}

	PointLight::PointLight(const PointLight& other): Light(LIGHT_TYPE::POINT)
	{
		this->position = other.position;
		this->diffuseIntensity = other.diffuseIntensity;
		this->specularIntensity = other.specularIntensity;
	}

	PointLight::~PointLight()
	{
	}

	void PointLight::SetDiffuse(Color diffuse)
	{
		this->diffuseIntensity = diffuse;
	}

	void PointLight::SetSpecular(Color specular)
	{
		this->specularIntensity = specular;
	}

	void PointLight::SetPosition(glm::vec3 position)
	{
		this->position = position;
	}

	LightData PointLight::GetLightData()
	{
		LightData lightData;

		lightData.SetLightType(LIGHT_TYPE::POINT);
		lightData.SetPosition(position);
		lightData.SetDiffuse(diffuseIntensity);
		lightData.SetSpecular(specularIntensity);

		return lightData;
	}
}
