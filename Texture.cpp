#include "Texture.h"

Texture::Texture(const std::string& filepath, GLuint slot)
{
	Initialize(filepath, slot);
}

Texture::Texture() {}

void Texture::Initialize(const std::string& filepath, GLuint slot)
{
	stbi_set_flip_vertically_on_load(true);
	Texture::slot = slot;
	Texture::filepath = filepath;

	// find texture type
	if (filepath.find("diffuse") != std::string::npos || filepath.find("baseColor") != std::string::npos)
		type = "diffuse";
	else if (filepath.find("specular") != std::string::npos)
		type = "specular";
	else
		std::cout << "ERROR: CANNOT FIND TEXTURE TYPE. TEXTURE: " << filepath << std::endl;

	// create and bind texture
	glGenTextures(1, &id);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);
	// image settings
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// image to data variable using stb
	unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &numColChannels, 0);

	if (data)
	{
		if (numColChannels == 1)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
		}
		else if (numColChannels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else if (numColChannels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR: UNABLE TO LOAD TEXTURE: " << filepath << std::endl;
	}
	stbi_image_free(data); // free up memory
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
