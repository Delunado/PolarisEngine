#pragma once
#include "Light.h"

namespace TEA {
	class PointLight: public Light
	{
	private:
		glm::vec3 position;

		Color diffuseIntensity;
		Color specularIntensity;

	public:
		PointLight(glm::vec3 position, Color diffuseIntensity, Color specularIntensity);

		PointLight(const PointLight& other);

		~PointLight();

		void SetDiffuse(Color diffuse);
		void SetSpecular(Color specular);
		void SetPosition(glm::vec3 position);

		virtual LightData GetLightData() override;
	};
}
