#ifndef MESH_H
#define MESH_H

#include <vector>

#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	
	void Draw(Shader& shader);

private:
	VAO vao;
	VBO vbo;
	EBO ebo;

	void SetupMesh();
};

#endif