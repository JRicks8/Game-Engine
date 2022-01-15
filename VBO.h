#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>
#include <vector>

#include "Vertex.h"

class VBO
{
public:
	unsigned int id;

	VBO(std::vector<Vertex>& vertices);
	VBO();

	void BufferData(std::vector<Vertex>& vertices);
	void BufferData(Vertex vertices[]);
	void Bind();
	void Unbind();
};

#endif