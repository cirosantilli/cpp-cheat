#include <stdio.h>
#include <stdlib.h>

#include <btBulletDynamicsCommon.h>

int main() {
    int i, j;

    btDefaultCollisionConfiguration* collisionConfiguration
            = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(
            dispatcher, overlappingPairCache, solver, collisionConfiguration);

    dynamicsWorld->setGravity(btVector3(0, -10, 0));
    btCollisionShape* groundShape = new btBoxShape(
            btVector3(btScalar(50.0), btScalar(50.0), btScalar(50.0)));
    btAlignedObjectArray<btCollisionShape*> collisionShapes;
    collisionShapes.push_back(groundShape);
    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(0, 0, 0));

    // Shpere at position 0, 10, 0.
    {
        btCollisionShape *colShape = new btSphereShape(btScalar(1.0));
        collisionShapes.push_back(colShape);
        btTransform startTransform;
        startTransform.setIdentity();
        startTransform.setOrigin(btVector3(0, 10, 0));
        btVector3 localInertia(0, 0, 0);
        btScalar mass(1.0f);
        colShape->calculateLocalInertia(mass, localInertia);
        btDefaultMotionState *myMotionState = new btDefaultMotionState(startTransform);
        btRigidBody *body = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(
                mass, myMotionState, colShape, localInertia));
        dynamicsWorld->addRigidBody(body);
    }

    // Main loop. Update state and print it.
    for (i = 0; i < 100; ++i) {
        dynamicsWorld->stepSimulation(1.0f / 60.0f, 10);
        for (j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; --j) {
            btCollisionObject *obj = dynamicsWorld->getCollisionObjectArray()[j];
            btRigidBody *body = btRigidBody::upcast(obj);
            btTransform trans;
            if (body && body->getMotionState()) {
                body->getMotionState()->getWorldTransform(trans);
            } else {
                trans = obj->getWorldTransform();
            }
            printf("%d = %7.3f, %7.3f, %7.3f\n",
                    j,
                    float(trans.getOrigin().getX()),
                    float(trans.getOrigin().getY()),
                    float(trans.getOrigin().getZ()));
        }
    }

    // Cleanup.
    for (i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; --i) {
        btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
        btRigidBody* body = btRigidBody::upcast(obj);
        if (body && body->getMotionState()) {
            delete body->getMotionState();
        }
        dynamicsWorld->removeCollisionObject( obj );
        delete obj;
    }
    for (i = 0; i < collisionShapes.size(); ++i) {
        btCollisionShape* shape = collisionShapes[i];
        collisionShapes[i] = 0;
        delete shape;
    }
    delete dynamicsWorld;
    delete solver;
    delete overlappingPairCache;
    delete dispatcher;
    delete collisionConfiguration;
    collisionShapes.clear();
}
