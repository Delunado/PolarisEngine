#pragma once

#include <vector>

#include "RenderData.h"

namespace Render {
	struct Vertex
	{
	public:
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
		glm::vec3 Tangent;
		glm::vec3 Bitangent;

		Vertex(glm::vec3 position, glm::vec3 normal, glm::vec3 tangent, glm::vec3 bitangent, glm::vec2 texCoords) : 
			Position(position), Normal(normal), Tangent(tangent), Bitangent(bitangent), TexCoords(texCoords)
		{}

	};

	class Mesh
	{

	private:
		GLuint idVAO; // Vertex Array Object Identifier
		GLuint idVBO; // Vertex Buffer Object Identifier
		GLuint idIBO; // Index Buffer Object Identifier

		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;

		void Config();

	public:
		Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);

		Mesh(const Mesh &other);

		~Mesh();

		void Render(RenderData &renderInfo);
	};
}

