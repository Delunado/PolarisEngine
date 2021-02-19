#include <stdexcept>

#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "ShaderProgram.h"
#include "Material.h"

#include "Mesh.h"

namespace Render {
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices) : vertices(vertices), indices(indices)
	{
		Config();
	}

	Mesh::Mesh(const Mesh& other)
	{
		this->idIBO = other.idIBO;
		this->idVAO = other.idVAO;
		this->idVBO = other.idVBO;

		this->indices = other.indices;
		this->vertices = other.vertices;

		Config();
	}

	Mesh::~Mesh()
	{
		glDeleteBuffers(1, &idIBO);
		glDeleteBuffers(1, &idVBO);
		glDeleteVertexArrays(1, &idVAO);
	}

	void Mesh::Config()
	{
		//First we create the VAO
		glGenVertexArrays(1, &idVAO);
		glBindVertexArray(idVAO);

		//Then we create the linked VBO and pass all the data 
		glGenBuffers(1, &idVBO);
		glBindBuffer(GL_ARRAY_BUFFER, idVBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(GLfloat), GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLubyte*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, sizeof(glm::vec3) / sizeof(GLfloat), GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLubyte*)0 + offsetof(Vertex, Normal));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, sizeof(glm::vec2) / sizeof(GLfloat), GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLubyte*)0 + offsetof(Vertex, TexCoords));
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(3, sizeof(glm::vec3) / sizeof(GLfloat), GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLubyte*)0 + offsetof(Vertex, Tangent));
		glEnableVertexAttribArray(3);

		glVertexAttribPointer(4, sizeof(glm::vec3) / sizeof(GLfloat), GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLubyte*)0 + offsetof(Vertex, Bitangent));
		glEnableVertexAttribArray(4);

		//Finally, we set the IBO and the indices
		glGenBuffers(1, &idIBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	}

	void Mesh::Render(RenderData &renderInfo)
	{
		try {
			if (renderInfo.material->GetShaderProgram() != nullptr) {
				glBindVertexArray(idVAO);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);

				std::string renderMode;
				std::string lightMode;

				ShaderProgram* shaderToUse = renderInfo.material->GetShaderProgram();

				switch (renderInfo.modelRepresentation)
				{
				case MODEL_REPRESENTATION::WIREFRAME:
					renderMode = "WireframeColor";
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					break;

				case MODEL_REPRESENTATION::SOLID:
					renderMode = "LightColor";
					shaderToUse->AddUniformVec3f("Ka", renderInfo.material->GetAmbient().GetData());
					shaderToUse->AddUniformVec3f("Kd", renderInfo.material->GetDiffuse().GetData());
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					break;

				case MODEL_REPRESENTATION::TEXTURE:
					renderMode = "LightColor";

					if (renderInfo.material != nullptr) {
						Texture* colorTexture = renderInfo.material->GetColorTexture();

						if (colorTexture != nullptr) {
							Texture* normalTexture = renderInfo.material->GetNormalTexture();

							if (renderInfo.material->IsNormalMapActive() && normalTexture != nullptr) {

								shaderToUse = renderInfo.material->GetShaderProgramNormalMap();

								shaderToUse->AddUniformSampler2D("normalText", 1);
								normalTexture->ActivateTexture(1);
							}
							else {
								shaderToUse->AddUniformVec3f("Ka", renderInfo.material->GetAmbient().GetData());
								shaderToUse->AddUniformVec3f("Kd", renderInfo.material->GetDiffuse().GetData());
							}

							shaderToUse->AddUniformSampler2D("text", 0);
							colorTexture->ActivateTexture(0);
							renderMode = "TextureColor";
						}
					}

					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					break;
				}

				shaderToUse->AddUniformMatrix4f("mModelView", renderInfo.mvMatrix);
				shaderToUse->AddUniformMatrix4f("mModelViewIT", renderInfo.mvITMatrix);
				shaderToUse->AddUniformMatrix4f("matrixMVP", renderInfo.mvpMatrix);

				if (renderInfo.material != nullptr) {
					shaderToUse->AddUniformVec3f("Ks", renderInfo.material->GetSpecular().GetData());
					shaderToUse->AddUniformFloat("shininess", renderInfo.material->GetExponent());
				}

				if (renderInfo.lightData.HasAmbient()) {
					shaderToUse->AddUniformVec3f("Ia", renderInfo.lightData.GetAmbient().GetData());
				}

				if (renderInfo.lightData.HasDiffuse()) {
					shaderToUse->AddUniformVec3f("Id", renderInfo.lightData.GetDiffuse().GetData());
				}

				if (renderInfo.lightData.HasSpecular()) {
					shaderToUse->AddUniformVec3f("Is", renderInfo.lightData.GetSpecular().GetData());
				}

				if (renderInfo.lightData.HasPosition()) {
					shaderToUse->AddUniformVec3f("lightPos", renderInfo.mvMatrix * glm::vec4(renderInfo.lightData.GetPosition(), 1.0f));
				}

				if (renderInfo.lightData.HasDirection()) {
					shaderToUse->AddUniformVec3f("lightDir", glm::normalize(renderInfo.mvITMatrix * glm::vec4(renderInfo.lightData.GetDirection(), 0.0f)));
				}

				if (renderInfo.lightData.HasOpeningAngle()) {
					shaderToUse->AddUniformFloat("spotAngle", glm::radians(renderInfo.lightData.GetOpeningAngle()));
				}

				switch (renderInfo.lightData.GetLightType())
				{
				case LIGHT_TYPE::AMBIENT:
					lightMode = "Ambient";
					break;
				case LIGHT_TYPE::DIRECTIONAL:
					lightMode = "Directional";
					break;
				case LIGHT_TYPE::POINT:
					lightMode = "Point";
					break;
				case LIGHT_TYPE::SPOT:
					lightMode = "Spot";
					break;
				default:
					break;
				}

				shaderToUse->Activate();
				shaderToUse->SelectSubroutine(GL_FRAGMENT_SHADER, renderMode, lightMode);
			}
			else {
				throw std::runtime_error("Error Rendering Model - No Shader Program:\n");
			}

			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
		}
		catch (std::exception& e) {
			const std::string message = " - in function Render()";
			throw std::runtime_error(e.what() + message);
		}
	}

}