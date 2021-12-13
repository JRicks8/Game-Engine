#include "Model.h"

void Model::Draw(Shader& shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].Draw(shader);
}

void Model::LoadModel(const std::string& filepath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	directory = filepath.substr(0, filepath.find_last_of('/') + 1);
	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	aiMatrix4x4 m = node->mTransformation;

	// process node meshes
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* aimesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(aimesh, scene, m));
	}
	// recursive calls for children nodes
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene, aiMatrix4x4 transform)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	// vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		glm::vec3 vec3;
		vec3.x = mesh->mVertices[i].x;
		vec3.y = mesh->mVertices[i].y;
		vec3.z = mesh->mVertices[i].z;
		vertex.position = vec3;
		vec3.x = mesh->mNormals[i].x;
		vec3.y = mesh->mNormals[i].y;
		vec3.z = mesh->mNormals[i].z;
		vertex.normals = vec3;
		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec2;
			vec2.x = mesh->mTextureCoords[0][i].x;
			vec2.y = mesh->mTextureCoords[0][i].y;
			vertex.UVs = vec2;
		}
		else
			vertex.UVs = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	// indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// textures
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		
		std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	Mesh m(vertices, indices, textures);

	// process transformation
	transform.Transpose();

	float data[16];
	memcpy(data, &transform, sizeof(float) * 16);

	glm::mat4 trans = glm::mat4(data[0],  data[1],  data[2],  data[3],
								data[4],  data[5],  data[6],  data[7],
								data[8],  data[9],  data[10], data[11],
								data[12], data[13], data[14], data[15]);
	m.transformMat = trans;

	return m;
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < texturesLoaded.size(); j++)
		{
			if (std::strcmp(texturesLoaded[j].filepath.data(), (directory + str.C_Str()).c_str()) == 0)
			{
				textures.push_back(texturesLoaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{
			std::string path = (directory + str.C_Str()).c_str();
			Texture	texture(path, i);
			textures.push_back(texture);
			texturesLoaded.push_back(texture);
		}
	}
	return textures;
}