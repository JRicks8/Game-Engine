#include "PhysicsManager.h"

PhysicsManager::PhysicsManager(float gravity)
{
	//default setup for memory and collisions
	PhysicsManager::collConfig = new btDefaultCollisionConfiguration();
	PhysicsManager::dispatcher = new btCollisionDispatcher(collConfig);
	PhysicsManager::overlappingPairCache = new btDbvtBroadphase();
	PhysicsManager::solver = new btSequentialImpulseConstraintSolver();
	PhysicsManager::dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collConfig);

	dynamicsWorld->setGravity(btVector3(0, gravity, 0));
}

void PhysicsManager::Cleanup()
{
	delete dynamicsWorld;
	delete solver;
	delete overlappingPairCache;
	delete dispatcher;
	delete collConfig;
}