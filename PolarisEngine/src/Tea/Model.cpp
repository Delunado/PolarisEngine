#include <stdexcept>
#include <GL/glew.h>

#include <iostream>

#include "Transform.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Material.h"

#include "Model.h"

namespace TEA {
	Model::Model(MODEL_TYPE modelType, Material* material) : modelType(modelType),
		material(material), modelRepresentation(MODEL_REPRESENTATION::SOLID), transform(new Transform())

	{
		BuildModel(modelType);
	}

	Model::Model(std::string modelPath, Material* material): modelType(MODEL_TYPE::OBJ),
		material(material), modelRepresentation(MODEL_REPRESENTATION::SOLID), transform(new Transform())
	{
		try {
			LoadModel(modelPath);
		}
		catch (std::exception & e) {
			const std::string message = " - in function Model()";
			throw std::runtime_error(e.what() + message);
		}
	}

	Model::Model(const Model& other)
	{
		this->modelType = other.modelType;
		this->modelRepresentation = other.modelRepresentation;

		this->material = other.material;

		this->transform = other.transform;
	}

	Model::~Model()
	{
		material = nullptr;

		delete transform;
	}

	Model* Model::CreateModel(std::string modelPath, Material* material)
	{
		Model* model = new Model(modelPath, material);
		return model;
	}

	void Model::BuildModel(MODEL_TYPE modelType)
	{
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;

		////Depending on the model type, we create a different VBO
		switch (modelType)
		{
		case MODEL_TYPE::TRIANGLE:
		{
			Vertex vertex1(glm::vec3(-.5, -.5, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec2(0, 0.5));
			Vertex vertex2(glm::vec3(.5, -.5, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec2(0.5, 0.5));
			Vertex vertex3(glm::vec3(.0, .5, 0), glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec2(0.5, 0));

			vertices.push_back(vertex1);
			vertices.push_back(vertex2);
			vertices.push_back(vertex3);

			indices.push_back(0);
			indices.push_back(1);
			indices.push_back(2);

			meshes.push_back(Mesh(vertices, indices));
		}

		break;

		case MODEL_TYPE::TETRAHEDRON:
		{
			Vertex vertex1(glm::vec3(-.5, -.5, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec2(0, 0.5));
			Vertex vertex2(glm::vec3(.5, -.5, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec2(0.5, 0.5));
			Vertex vertex3(glm::vec3(0, .5, 0), glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec2(0.5, 0));
			Vertex vertex4(glm::vec3(0, -.5, -.5), glm::vec3(1, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec2(0, 0));

			vertices.push_back(vertex1);
			vertices.push_back(vertex2);
			vertices.push_back(vertex3);
			vertices.push_back(vertex4);

			indices.push_back(0);
			indices.push_back(1);
			indices.push_back(2);

			indices.push_back(1);
			indices.push_back(2);
			indices.push_back(3);

			indices.push_back(0);
			indices.push_back(2);
			indices.push_back(3);

			indices.push_back(0);
			indices.push_back(1);
			indices.push_back(3);

			meshes.push_back(Mesh(vertices, indices));
		}

		break;
		}

		////This calculates the normals for the vertices
		//for (int i = 0, j = 0; i < indices.size(); i++, j++) {
		//	glm::vec3 edge1 = vertices[i].Position - vertices[i+1].Position;
		//	glm::vec3 edge2 = vertices[i].Position - vertices[i+2].Position;;

		//	vertices[j].Normal = glm::cross(edge1, edge2);
		//}
	}

	void Model::LoadModel(std::string modelPath)
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(modelPath, aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_GenSmoothNormals |
		aiProcess_CalcTangentSpace);

		if (scene && scene->mRootNode && !(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)) {
			ProcessNode(scene->mRootNode, scene);
		}
		else {
			throw std::runtime_error("Error Loading Model - Can't Load Model: \n");
		}
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{

		for (GLuint i = 0; i < node->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(ProcessMesh(mesh, scene));
		}

		for (GLuint i = 0; i < node->mNumChildren; i++) {
			ProcessNode(node->mChildren[i], scene);
		}

	}

	Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;

		//First we process the vertices
		for (GLuint i = 0; i < mesh->mNumVertices; i++) {
			glm::vec3 position(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
			glm::vec3 normal(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

			glm::vec2 texCoords(0.0f, 0.0f);

			if (mesh->mTextureCoords[0]) {
				texCoords.x = mesh->mTextureCoords[0][i].x; 
				texCoords.y = mesh->mTextureCoords[0][i].y;
			}

			glm::vec3 tangent(0.0f, 0.0f, 0.0f);
			glm::vec3 bitangent(0.0f, 0.0f, 0.0f);

			if (mesh->mTangents) {
				tangent.x = mesh->mTangents[i].x;
				tangent.y = mesh->mTangents[i].y;
				tangent.z = mesh->mTangents[i].z;

				bitangent.x = mesh->mBitangents[i].x;
				bitangent.y = mesh->mBitangents[i].y;
				bitangent.z = mesh->mBitangents[i].z;
			}

			Vertex vertex(position, normal, tangent, bitangent, texCoords);

			vertices.push_back(vertex);
		}

		//Then the indices
		for (GLuint i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];

			for (GLuint j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}

		return Mesh(vertices, indices);
	}

	void Model::SetModelRepresentation(MODEL_REPRESENTATION modelRepresentation)
	{
		this->modelRepresentation = modelRepresentation;
	}

	MODEL_REPRESENTATION Model::GetModelRepresentation() const
	{
		return this->modelRepresentation;
	}

	void Model::SetMaterial(Material* material)
	{
		this->material = material;
	}

	Material* Model::GetMaterial() const
	{
		return material;
	}

	Transform* Model::GetTransform() const
	{
		return transform;
	}

	void Model::Render(RenderData &renderInfo)
	{
		try {
			renderInfo.material = material;
			renderInfo.modelRepresentation = modelRepresentation;

			for (GLuint i = 0; i < meshes.size(); i++) {
				meshes[i].Render(renderInfo);
			}
		}
		catch (std::exception& e) {
			const std::string message = " - in function Render()";
			throw std::runtime_error(e.what() + message);
		}
	}

}