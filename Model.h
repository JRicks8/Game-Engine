#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

class Model
{
public:
	Model(const char* filepath)
	{
		LoadModel(filepath);
	}

	std::vector<Mesh> meshes;

	void Draw(Shader& shader, glm::vec3 t = glm::vec3(0.0f), glm::vec3 s = glm::vec3(1.0f));
	Mesh* GetMesh(int indMesh);

private:
	std::vector<Texture> texturesLoaded;
	std::string directory;

	void LoadModel(const std::string& filepath);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, aiMatrix4x4 transform, std::string meshName);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

#endif