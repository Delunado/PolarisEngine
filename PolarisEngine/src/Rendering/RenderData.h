#pragma once

#include "ModelRepresentation.h"
#include "LightData.h"

namespace Render {
	class Material;

	struct RenderData
	{
	public:
		Material* material;
		MODEL_REPRESENTATION modelRepresentation;
		LightData lightData;
		glm::mat4 mvMatrix;
		glm::mat4 mvITMatrix;
		glm::mat4 mvpMatrix;

		RenderData() : material(nullptr), modelRepresentation(), lightData(LightData()),
			mvMatrix(glm::mat4()), mvITMatrix(glm::mat4()), mvpMatrix(glm::mat4())
		{}
	};
}