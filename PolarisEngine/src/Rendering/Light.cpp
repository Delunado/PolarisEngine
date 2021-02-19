#include <stdexcept>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "LightType.h"
#include "LightData.h"
#include "Light.h"

namespace Render {
	Light::Light(LIGHT_TYPE lightType): lightType(lightType)
	{
	}

	Light::Light(const Light& other)
	{
		this->lightType = other.lightType;
	}

	Light::~Light()
	{
	}

}
