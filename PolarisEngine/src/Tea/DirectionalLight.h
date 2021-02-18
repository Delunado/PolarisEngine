#pragma once
#include "Light.h"

namespace TEA {
	class DirectionalLight : public Light
	{
	private:
		glm::vec3 direction;

		Color diffuseIntensity;
		Color specularIntensity;

	public:
		DirectionalLight(glm::vec3 direction, Color diffuseIntensity, Color specularIntensity);

		DirectionalLight(const DirectionalLight &other);

		~DirectionalLight();

		void SetDiffuse(Color diffuse);
		void SetSpecular(Color specular);
		void SetDirection(glm::vec3 direction);

		virtual LightData GetLightData() override;
	};
}

