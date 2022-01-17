#ifndef MESH_H
#define MESH_H

#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "PhysicsBody.h"

class Mesh
{
public:
	// mesh properties
	std::string name;

	bool hasPhysicsBody = false;
	PhysicsBody* physBody;

	float shininess = 32.0f;

	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	
	void Draw(Shader& shader, glm::vec3 t = glm::vec3(0.0f), glm::vec3 s = glm::vec3(1.0f));
	void GeneratePhysBody(bool convex, float mass);
	void GeneratePhysBody(bool convex, float mass, btCollisionShape* shape);
	void SyncRigidBody();

	void SetPosition(glm::vec3 p);
	void SetRotation(glm::quat r);
	void SetScale(glm::vec3 s);
	glm::vec3 GetPosition() { return position; }
	glm::quat GetRotation() { return rotation; }
	glm::vec3 GetRotationEuler(bool radians = false);
	glm::vec3 GetScale() { return scale; }

	void PrintInfo();

private:
	VAO vao;
	VBO vbo;
	EBO ebo;

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

	void SetupBuffers();
};

#endif