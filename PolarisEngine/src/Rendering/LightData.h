#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include "LightType.h"
#include "Color.h"

namespace Render {
	struct LightData
	{
	private:
		LIGHT_TYPE lightType;

		Color ambientIntensity;
		Color diffuseIntensity;
		Color specularIntensity;

		glm::vec3 position;

		glm::vec3 direction;

		GLfloat openingAngle;

		bool hasAmbientIntensity;
		bool hasDiffuseIntensity;
		bool hasSpecularIntensity;
		bool hasPosition;
		bool hasDirection;
		bool hasOpeningAngle;

	public:
		LightData() : hasAmbientIntensity(false), hasDiffuseIntensity(false), hasSpecularIntensity(false),
			hasPosition(false), hasDirection(false), hasOpeningAngle(false), ambientIntensity(Color(0.0f, 0.0f, 0.0f)),
			diffuseIntensity(Color(0.0f, 0.0f, 0.0f)), specularIntensity(Color(0.0f, 0.0f, 0.0f)),
			position(glm::vec3(0.0f, 0.0f, 0.0f)), direction(glm::vec3(0.0f, 0.0f, 0.0f)), openingAngle(0.0f), lightType(LIGHT_TYPE::NONE)
		{

		}

		void SetLightType(LIGHT_TYPE lightType) { this->lightType = lightType; }

		void SetAmbient(Color ambientIntensity) {
			this->ambientIntensity = ambientIntensity;
			hasAmbientIntensity = true;
		}

		void SetDiffuse(Color diffuseIntensity) {
			this->diffuseIntensity = diffuseIntensity;
			hasDiffuseIntensity = true;
		}

		void SetSpecular(Color specularIntensity) {
			this->specularIntensity = specularIntensity;
			hasSpecularIntensity = true;
		}

		void SetDirection(glm::vec3 direction) {
			this->direction = direction;
			hasDirection = true;
		}

		void SetPosition(glm::vec3 position) {
			this->position = position;
			hasPosition = true;
		}

		void SetOpeningAngle(GLfloat openingAngle) {
			this->openingAngle = openingAngle;
			hasOpeningAngle = true;
		}

		LIGHT_TYPE GetLightType() { return lightType; }
		Color GetAmbient() { return ambientIntensity; }
		Color GetDiffuse() { return diffuseIntensity; }
		Color GetSpecular() { return specularIntensity; }
		glm::vec3 GetDirection() { return direction; }
		glm::vec3 GetPosition() { return position; }
		GLfloat GetOpeningAngle() { return openingAngle; }

		bool HasAmbient() { return hasAmbientIntensity; }
		bool HasDiffuse() { return hasDiffuseIntensity; }
		bool HasSpecular() { return hasSpecularIntensity; }
		bool HasDirection() { return hasDirection; }
		bool HasPosition() { return hasPosition; }
		bool HasOpeningAngle() { return hasOpeningAngle; }
	};
}