#include <GL/glew.h>
#include <glm/glm.hpp>

#include "LightData.h"

#include "SpotLight.h"

namespace TEA {
	SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, GLfloat openingAngle,
						 Color diffuseIntensity, Color specularIntensity): Light(LIGHT_TYPE::SPOT),
					     position(position), direction(direction), openingAngle(openingAngle), diffuseIntensity(diffuseIntensity), 
						 specularIntensity(specularIntensity)
	{
	}

	SpotLight::SpotLight(const SpotLight& other) : Light(LIGHT_TYPE::SPOT)
	{
		this->position = other.position;
		this->direction = other.direction;
		this->diffuseIntensity = other.diffuseIntensity;
		this->specularIntensity = other.specularIntensity;
		this->openingAngle = other.openingAngle;
	}

	SpotLight::~SpotLight()
	{
	}


	void SpotLight::SetDiffuse(Color diffuse)
	{
		this->diffuseIntensity = diffuse;
	}

	void SpotLight::SetSpecular(Color specular)
	{
		this->specularIntensity = specular;
	}

	void SpotLight::SetDirection(glm::vec3 direction)
	{
		this->direction = direction;
	}

	void SpotLight::SetPosition(glm::vec3 position)
	{
		this->position = position;
	}

	void SpotLight::SetOpeningAngle(GLfloat openingAngle)
	{
		this->openingAngle = openingAngle;
	}


	LightData SpotLight::GetLightData()
	{
		LightData lightData;

		lightData.SetLightType(LIGHT_TYPE::SPOT);
		lightData.SetPosition(position);
		lightData.SetDirection(direction);
		lightData.SetDiffuse(diffuseIntensity);
		lightData.SetSpecular(specularIntensity);
		lightData.SetOpeningAngle(openingAngle);

		return lightData;
	}
}