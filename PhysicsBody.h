#ifndef PHYSICSBODY_H
#define PHYSICSBODY_H

#include <vector>

#include "glfw/glfw3.h"

#include "Vertex.h"
#include "btBulletDynamicsCommon.h"

struct PhysicsBody
{
	btRigidBody* body;
	btCollisionShape* shape;

	float mass = 0;
	bool convex = true;

	void GenerateShape(std::vector<Vertex> verts, std::vector<GLuint> indices, float scale = 1.0f);

	void GenerateBodyWithMass(float mass, btVector3 pos, btQuaternion rot, void* parentPtr);
};

#endif