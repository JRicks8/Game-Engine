#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <iostream>

class Texture
{
public:
	unsigned int id, slot;
	int width, height, numColChannels;
	std::string type;
	std::string filepath;

	Texture(const std::string& filepath, GLuint slot);
	Texture();

	void Initialize(const std::string& filepath, GLuint slot);
	void Bind();
	void Unbind();
};

#endif