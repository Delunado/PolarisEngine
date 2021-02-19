#pragma once
#include "Light.h"
#include "Color.h"

namespace Render {
	class AmbientLight : public Light
	{
	private:
		Color ambientIntensity;

	public:
		AmbientLight(Color ambientIntensity);

		AmbientLight(const AmbientLight& other);

		~AmbientLight();

		void SetAmbient(Color ambientIntensity);

		virtual LightData GetLightData() override;
	};
}
