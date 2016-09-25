#include <cstdio>
#include <cstdlib>
#include <map>
#include <type_traits>
#include <vector>

#include <btBulletDynamicsCommon.h>

#include "common.hpp"

constexpr float gravity = 0.0f;
// How inclined the ground plane is towards +x.
constexpr float groundXNormal = 0.0f;
constexpr float initialX = 0.0f;
constexpr float initialY = 5.0f;
constexpr float initialZ = 10.0f;
constexpr float initialLinearVelocityX = 1.0f;
constexpr float initialLinearVelocityY = 2.0f;
constexpr float initialLinearVelocityZ = 30.0f;
constexpr float initialAngularVelocityX = 1.0f;
constexpr float initialAngularVelocityY = 2.0f;
constexpr float initialAngularVelocityZ = 3.0f;
constexpr float timeStep = 1.0f / 60.0f;
// TODO some combinations of coefficients smaller than 1.0
// make the ball go up higher / not lose height. Why?
constexpr float groundRestitution = 0.9f;
constexpr float objectRestitution = 0.9f;
constexpr int nSteps = 50;

std::map<const btCollisionObject*,std::vector<btManifoldPoint*>> objectsCollisions;
void myTickCallback(btDynamicsWorld *dynamicsWorld, btScalar timeStep) {
    objectsCollisions.clear();
    int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
    for (int i = 0; i < numManifolds; i++) {
        btPersistentManifold *contactManifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
        auto *objA = contactManifold->getBody0();
        auto *objB = contactManifold->getBody1();
        auto& collisionsA = objectsCollisions[objA];
        auto& collisionsB = objectsCollisions[objB];
        int numContacts = contactManifold->getNumContacts();
        for (int j = 0; j < numContacts; j++) {
            btManifoldPoint& pt = contactManifold->getContactPoint(j);
            collisionsA.push_back(&pt);
            collisionsB.push_back(&pt);
        }
    }
}

int main() {
    btDefaultCollisionConfiguration *collisionConfiguration
            = new btDefaultCollisionConfiguration();
    btCollisionDispatcher *dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btBroadphaseInterface *overlappingPairCache = new btDbvtBroadphase();
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
    btDiscreteDynamicsWorld *dynamicsWorld = new btDiscreteDynamicsWorld(
            dispatcher, overlappingPairCache, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0, gravity, 0));
    dynamicsWorld->setInternalTickCallback(myTickCallback);
    btAlignedObjectArray<btCollisionShape*> collisionShapes;

    // Object0
    {
        btCollisionShape *colShape;
#if 0
        colShape = new btSphereShape(btScalar(1.0));
#else
        // Because of numerical instabilities, the cube bumps all over,
        // moving on the x and z directions as well as y.
        colShape = new btBoxShape(
                btVector3(btScalar(1.0), btScalar(1.0), btScalar(1.0)));
#endif
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
		body->setRestitution(objectRestitution);
		body->setLinearVelocity(btVector3(initialLinearVelocityX, initialLinearVelocityY, initialLinearVelocityZ));
		body->setAngularVelocity(btVector3(initialAngularVelocityX, initialAngularVelocityY, initialAngularVelocityZ));
        dynamicsWorld->addRigidBody(body);
    }

    // Object1
    {
        btCollisionShape *colShape;
#if 0
        colShape = new btSphereShape(btScalar(1.0));
#else
        // Because of numerical instabilities, the cube bumps all over,
        // moving on the x and z directions as well as y.
        colShape = new btBoxShape(
                btVector3(btScalar(1.0), btScalar(1.0), btScalar(1.0)));
#endif
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
		body->setRestitution(objectRestitution);
		body->setLinearVelocity(btVector3(initialLinearVelocityX, initialLinearVelocityY, initialLinearVelocityZ));
		body->setAngularVelocity(btVector3(initialAngularVelocityX, initialAngularVelocityY, initialAngularVelocityZ));
        dynamicsWorld->addRigidBody(body);
    }

    // Main loop.
    std::printf(COMMON_PRINTF_HEADER "\n");
    for (std::remove_const<decltype(nSteps)>::type step = 0; step < nSteps; ++step) {
        dynamicsWorld->stepSimulation(timeStep);
        auto nCollisionObjects = dynamicsWorld->getNumCollisionObjects();
        for (decltype(nCollisionObjects) objectIndex = 0; objectIndex < nCollisionObjects; ++objectIndex) {
            btRigidBody *body = btRigidBody::upcast(dynamicsWorld->getCollisionObjectArray()[objectIndex]);
            commonPrintBodyState(body, step, objectIndex);
        }
        std::printf("\n");
    }

    // Cleanup.
    for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; --i) {
        btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
        btRigidBody* body = btRigidBody::upcast(obj);
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
