#pragma once
#include "Light.h"

namespace Render {
	class SpotLight: public Light
	{
	private:
		glm::vec3 position;
		glm::vec3 direction;

		Color diffuseIntensity;
		Color specularIntensity;

		GLfloat openingAngle;

	public:
		SpotLight(glm::vec3 position, glm::vec3 direction, GLfloat openingAngle, 
				  Color diffuseIntensity, Color specularIntensity);

		SpotLight(const SpotLight &other);

		~SpotLight();

		void SetDiffuse(Color diffuse);
		void SetSpecular(Color specular);
		void SetPosition(glm::vec3 position);
		void SetDirection(glm::vec3 direction);
		void SetOpeningAngle(GLfloat openingAngle);

		virtual LightData GetLightData() override;
	};
}