/*
Drop an object to a planar ground with gravity.

It may bounce up a few times depending on the restitution coefficients.

Collisions are detected and printed to stdout. Releated threads:

- http://stackoverflow.com/questions/11175694/bullet-physics-simplest-collision-example
- http://stackoverflow.com/questions/9117932/detecting-collisions-with-bullet
- http://gamedev.stackexchange.com/questions/22442/how-get-collision-callback-of-two-specific-objects-using-bullet-physics
- http://www.bulletphysics.org/mediawiki-1.5.8/index.php?title=Collision_Callbacks_and_Triggers

Derived from gravity.cpp
*/

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
constexpr float initialY = 10.0f;
constexpr float initialZ = 0.0f;
constexpr float initialLinearVelocityX = 0.0f;
constexpr float initialLinearVelocityY = -10.0f;
constexpr float initialLinearVelocityZ = 0.0f;
constexpr float timeStep = 1.0f / 60.0f;
// TODO some combinations of coefficients smaller than 1.0
// make the ball go up higher / not lose height. Why?
constexpr float groundRestitution = 1.0f;
constexpr float objectRestitution = 1.0f;
constexpr int nSteps = 500;

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

    // Ground.
    {
        btTransform groundTransform;
        groundTransform.setIdentity();
        groundTransform.setOrigin(btVector3(0, 0, 0));
        btCollisionShape* groundShape;
#if 0
        // x / z plane at y = -1 (not 0 to compensate the radius of the falling object).
        groundShape = new btStaticPlaneShape(btVector3(groundXNormal, 1, 0), -1);
#else
        // A cube of width 10 at y = -6 (upper surface at -1).
        // Does not fall because we won't call:
        // colShape->calculateLocalInertia
        // TODO: remove this from this example into a collision shape example.
        groundTransform.setOrigin(btVector3(-5, -6, 0));
        groundShape = new btBoxShape(
                btVector3(btScalar(5.0), btScalar(5.0), btScalar(5.0)));

#endif
        collisionShapes.push_back(groundShape);
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(0, myMotionState, groundShape, btVector3(0, 0, 0));
		btRigidBody* body = new btRigidBody(rbInfo);
		body->setRestitution(groundRestitution);
		dynamicsWorld->addRigidBody(body);
    }

    // Object.
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
        dynamicsWorld->addRigidBody(body);
    }

    // Main loop.
    std::printf(COMMON_PRINTF_HEADER " collision a b normal\n");
    for (std::remove_const<decltype(nSteps)>::type step = 0; step < nSteps; ++step) {
        dynamicsWorld->stepSimulation(timeStep);
        auto nCollisionObjects = dynamicsWorld->getNumCollisionObjects();
        for (decltype(nCollisionObjects) objectIndex = 0; objectIndex < nCollisionObjects; ++objectIndex) {
            btRigidBody *body = btRigidBody::upcast(dynamicsWorld->getCollisionObjectArray()[objectIndex]);
            commonPrintBodyState(body, step, objectIndex);
            auto& manifoldPoints = objectsCollisions[body];
            if (manifoldPoints.empty()) {
                std::printf("0 ");
            } else {
                std::printf("1 ");
                for (auto& pt : manifoldPoints) {
                    std::vector<btVector3> data;
                    data.push_back(pt->getPositionWorldOnA());
                    data.push_back(pt->getPositionWorldOnB());
                    data.push_back(pt->m_normalWorldOnB);
                    for (auto& v : data) {
                        std::printf(
                            COMMON_PRINTF_FLOAT " " COMMON_PRINTF_FLOAT " " COMMON_PRINTF_FLOAT " ",
                            v.getX(), v.getY(), v.getZ()
                        );
                    }
                }
            }
            std::printf("\n");
        }
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
