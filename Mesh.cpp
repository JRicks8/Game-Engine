#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	SetupMesh();
}

void Mesh::Draw(Shader& shader)
{
	// determine # of diffuse and specular textures and send info to the shader
	unsigned int diffuseNr = 0;
	unsigned int specularNr = 0;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		textures[i].Bind();

		std::string number;
		std::string type = textures[i].type;
		if (type == "diffuse")
			number = std::to_string(diffuseNr++);
		else if (type == "specular")
			number = std::to_string(specularNr++);

		shader.SetFloat(("material.texture_" + type + number).c_str(), i);
		textures[i].Bind();
	}
	glActiveTexture(GL_TEXTURE0);

	vao.Bind();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0); // unbind vao
}

void Mesh::SetupMesh()
{
	vao.Bind();
	vbo.BufferData(vertices);
	ebo.BufferData(indices);

	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));

	glBindVertexArray(0);
}