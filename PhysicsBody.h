#ifndef PHYSICSBODY_H
#define PHYSICSBODY_H

#include <vector>
#include <iostream>

#include "glfw/glfw3.h"

#include "Vertex.h"
#include "btBulletDynamicsCommon.h"

struct PhysicsBody
{
	PhysicsBody(bool convex, float mass);

	void GenerateShape(const std::vector<Vertex>& verts, const std::vector<GLuint>& indices, float scale = 1.0f);

	btRigidBody* GenerateBodyWithMass(float mass, btVector3 pos, btQuaternion rot, void* parentPtr);

	btRigidBody* body;
	btCollisionShape* shape;

	float mass;
	bool convex;
};

#endif