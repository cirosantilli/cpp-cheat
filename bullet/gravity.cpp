/*
Adapted from https://github.com/bulletphysics/bullet3/tree/2.83/examples/HelloWorld

A sphere falling infinitely to gravity.

Expected outcome: x and z are constant, y is a parabola downwards.
*/

#include <cstdio>
#include <cstdlib>

#include <btBulletDynamicsCommon.h>
#include <type_traits>

#include "common.hpp"

constexpr float gravity = -10.0f;
constexpr float initialX = 0.0f, initialY = 10.0f, initialZ = 0.0f;
constexpr float timeStep = 1.0f / 60.0f;
constexpr unsigned int nSteps = 125;

int main() {
    // Setup.
    btDefaultCollisionConfiguration* collisionConfiguration
            = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(
            dispatcher, overlappingPairCache, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0, gravity, 0));
    // This is not used by the actual simulation, only cleanup.
    btAlignedObjectArray<btCollisionShape*> collisionShapes;

    // Sphere.
    {
        btCollisionShape* colShape = new btSphereShape(btScalar(1.0));
        collisionShapes.push_back(colShape);
        btTransform startTransform;
        startTransform.setIdentity();
        startTransform.setOrigin(btVector3(initialX, initialY, initialZ));
        btVector3 localInertia(0, 0, 0);
        btScalar mass(1.0f);
        colShape->calculateLocalInertia(mass, localInertia);
        btDefaultMotionState *myMotionState = new btDefaultMotionState(startTransform);
        btRigidBody *body = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(
                mass, myMotionState, colShape, localInertia));
        dynamicsWorld->addRigidBody(body);
    }

    // Main loop.
    std::printf(COMMON_PRINTF_HEADER "\n");
    for (std::remove_const<decltype(nSteps)>::type step = 0; step < nSteps; ++step) {
        dynamicsWorld->stepSimulation(timeStep);
        auto nCollisionObjects = dynamicsWorld->getNumCollisionObjects();
        for (decltype(nCollisionObjects) objectIndex = 0; objectIndex < nCollisionObjects; ++objectIndex) {
            commonPrintBodyState(
                btRigidBody::upcast(dynamicsWorld->getCollisionObjectArray()[objectIndex]),
                step,
                objectIndex
            );
            std::printf("\n");
        }
    }

    // Cleanup.
    for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; --i) {
        btCollisionObject *obj = dynamicsWorld->getCollisionObjectArray()[i];
        btRigidBody *body = btRigidBody::upcast(obj);
        if (body && body->getMotionState()) {
            delete body->getMotionState();
        }
        dynamicsWorld->removeCollisionObject(obj);
        delete obj;
    }
    for (int i = 0; i < collisionShapes.size(); ++i) {
        delete collisionShapes[i];
    }
    delete dynamicsWorld;
    delete solver;
    delete overlappingPairCache;
    delete dispatcher;
    delete collisionConfiguration;
    collisionShapes.clear();
}
