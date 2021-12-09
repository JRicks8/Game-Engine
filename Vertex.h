#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normals;
	glm::vec2 UVs;
};

#endif