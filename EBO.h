#ifndef EBO_H
#define EBO_H

#include <vector>
#include <glad/glad.h>

class EBO
{
public:
	unsigned int id;

	EBO(std::vector<GLuint>& indices);
	EBO();

	void BufferData(std::vector<GLuint>& indices);
	void Bind();
	void Unbind();
};

#endif