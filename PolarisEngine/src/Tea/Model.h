#pragma once

#include <vector>
#include <glm/ext.hpp>

#include "assimp/Importer.hpp"
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "RenderData.h"

namespace TEA {
	enum class MODEL_TYPE
	{
		TRIANGLE,
		TETRAHEDRON,
		OBJ
	};

	class Mesh;
	class Transform;
	class Material;

	class Model
	{
	private:
		Material* material;

		Transform* transform;

		MODEL_TYPE modelType;
		MODEL_REPRESENTATION modelRepresentation;

		std::vector<Mesh> meshes;

		/// <summary>
		/// Create a model of the indicated type
		/// </summary>
		/// <param name="modelType"></param>
		void BuildModel(MODEL_TYPE modelType);

		/// <summary>
		/// Load a model from memory.
		/// </summary>
		/// <param name="modelPath"></param>
		void LoadModel(std::string modelPath);

		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	public:
		Model(MODEL_TYPE modelType, Material* material = nullptr);
		Model(std::string modelPath, Material* material = nullptr);

		Model(const Model& e);

		~Model();

		static Model* CreateModel(std::string modelPath, Material* material = nullptr);

		void SetModelRepresentation(MODEL_REPRESENTATION modelRepresentation);
		MODEL_REPRESENTATION GetModelRepresentation() const;

		void SetMaterial(Material* material);
		Material* GetMaterial() const;

		Transform* GetTransform() const;

		void Render(RenderData &renderInfo);
	};
}