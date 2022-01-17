#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(bool convex, float mass)
{
	PhysicsBody::mass = mass;
	PhysicsBody::convex = convex;
}

void PhysicsBody::GenerateShape(const std::vector<Vertex>& verts, const std::vector<GLuint>& indices, float scale)
{
	if (convex)
	{
		shape = new btConvexHullShape();
		for (int i = 0; i < indices.size(); i++)
		{
			Vertex v = verts[indices[i]];
			btVector3 btv = btVector3(v.position.x, v.position.y, v.position.z);
			((btConvexHullShape*)shape)->addPoint(btv);
		}
	}
	else
	{
		btTriangleMesh* m = new btTriangleMesh();
		for (unsigned int i = 0; i < indices.size(); i += 3) {
			Vertex v1 = verts[indices[i]];
			Vertex v2 = verts[indices[i + 1]];
			Vertex v3 = verts[indices[i + 2]];

			btVector3 bv1 = scale * btVector3(v1.position.x, v1.position.y, v1.position.z);
			btVector3 bv2 = scale * btVector3(v2.position.x, v2.position.y, v2.position.z);
			btVector3 bv3 = scale * btVector3(v3.position.x, v3.position.y, v3.position.z);

			m->addTriangle(bv1, bv2, bv3);
		}
		shape = new btBvhTriangleMeshShape(m, true);
	}
}

btRigidBody* PhysicsBody::GenerateBodyWithMass(float mass, btVector3 pos, btQuaternion rot, void* parentPtr)
{
	btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(rot, pos));

	btScalar bodyMass = mass;
	btVector3 bodyInertia;
	shape->calculateLocalInertia(bodyMass, bodyInertia);

	btRigidBody::btRigidBodyConstructionInfo bodyCI = btRigidBody::btRigidBodyConstructionInfo(bodyMass, motionState, shape, bodyInertia);

	bodyCI.m_restitution = 1.0f;
	bodyCI.m_friction = 0.5f;

	body = new btRigidBody(bodyCI);
	body->setUserPointer(parentPtr);
	body->setLinearFactor(btVector3(1, 1, 1));
	std::cout << body->getAngularSleepingThreshold() << '\n';
	body->setSleepingThresholds(0.1, 1.0);
	return body;
}