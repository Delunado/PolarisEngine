#pragma once

#include "LightData.h"

namespace TEA {
	class Light
	{
	private:
		LIGHT_TYPE lightType;

	public:
		Light(LIGHT_TYPE lightType);

		Light(const Light& other);

		~Light();

		/// <summary>
		/// Returns a LightData object, with the info of this light.
		/// </summary>
		/// <returns></returns>
		virtual LightData GetLightData() = 0;
	};
}