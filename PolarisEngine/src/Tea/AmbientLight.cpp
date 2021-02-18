#include <GL/glew.h>
#include <glm/glm.hpp>

#include "LightData.h"
#include "AmbientLight.h"

namespace TEA {
	AmbientLight::AmbientLight(Color ambientIntensity): Light(LIGHT_TYPE::AMBIENT), ambientIntensity(ambientIntensity)
	{
	}

	AmbientLight::AmbientLight(const AmbientLight& other): Light(LIGHT_TYPE::AMBIENT)
	{
		this->ambientIntensity = other.ambientIntensity;
	}

	AmbientLight::~AmbientLight()
	{
	}

	void AmbientLight::SetAmbient(Color ambientIntensity)
	{
		this->ambientIntensity = ambientIntensity;
	}

	LightData AmbientLight::GetLightData()
	{
		LightData lightData;

		lightData.SetLightType(LIGHT_TYPE::AMBIENT);
		lightData.SetAmbient(ambientIntensity);

		return lightData;
	}
}