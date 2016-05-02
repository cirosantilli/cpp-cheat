/*
Adapted from https://github.com/bulletphysics/bullet3/tree/2.83/examples/HelloWorld

A sphere falling infinitely to gravity.
*/

#include <cstdio>
#include <cstdlib>

#include <btBulletDynamicsCommon.h>

#define PRINTF_FLOAT "%7.3f"

constexpr float gravity = -10.0f;
constexpr float initialY = 10.0f;
constexpr float timeStep = 1.0f / 60.0f;
constexpr int maxNPoints = 125;

int main() {
    int i, j;

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
        startTransform.setOrigin(btVector3(0, initialY, 0));
        btVector3 localInertia(0, 0, 0);
        btScalar mass(1.0f);
        colShape->calculateLocalInertia(mass, localInertia);
        btDefaultMotionState *myMotionState = new btDefaultMotionState(startTransform);
        btRigidBody *body = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(
                mass, myMotionState, colShape, localInertia));
        dynamicsWorld->addRigidBody(body);
    }

    // Main loop.
    std::printf("step body x y z\n");
    for (i = 0; i < maxNPoints; ++i) {
        dynamicsWorld->stepSimulation(timeStep);
        for (j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; --j) {
            btCollisionObject *obj = dynamicsWorld->getCollisionObjectArray()[j];
            btRigidBody *body = btRigidBody::upcast(obj);
            btTransform trans;
            if (body && body->getMotionState()) {
                body->getMotionState()->getWorldTransform(trans);
            } else {
                trans = obj->getWorldTransform();
            }
            btVector3 origin = trans.getOrigin();
            // TODO: how to get numbers out of this?
            btQuaternion rotation = trans.getRotation();
            std::printf("%d %d " PRINTF_FLOAT " " PRINTF_FLOAT " " PRINTF_FLOAT "\n",
                    i,
                    j,
                    float(origin.getX()),
                    float(origin.getY()),
                    float(origin.getZ()));
        }
    }

    // Cleanup.
    for (i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; --i) {
        btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
        btRigidBody* body = btRigidBody::upcast(obj);
        if (body && body->getMotionState()) {
            delete body->getMotionState();
        }
        dynamicsWorld->removeCollisionObject(obj);
        delete obj;
    }
    for (i = 0; i < collisionShapes.size(); ++i) {
        delete collisionShapes[i];
    }
    delete dynamicsWorld;
    delete solver;
    delete overlappingPairCache;
    delete dispatcher;
    delete collisionConfiguration;
    collisionShapes.clear();
}
