#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "btBulletDynamicsCommon.h"

class PhysicsManager 
{
public:
	PhysicsManager(float gravity = -10.0f);

	void Cleanup();

	btDiscreteDynamicsWorld* dynamicsWorld;

private:
	btDefaultCollisionConfiguration* collConfig;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
};

#endif