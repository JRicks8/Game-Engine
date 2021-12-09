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
	void Draw(Shader& shader);
	
private:
	std::vector<Mesh> meshes;
	std::vector<Texture> texturesLoaded;
	std::string directory;

	void LoadModel(const std::string& filepath);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

#endif