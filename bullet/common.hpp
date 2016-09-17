#ifndef COMMON_HPP
#define COMMON_HPP

#include <cstdio>
#include <type_traits>

#include <btBulletDynamicsCommon.h>

#define COMMON_PRINTF_FLOAT "%.3e"
#define COMMON_PRINTF_HEADER "step body x y z vx vy vz"

void commonPrintBodyState(const btRigidBody *body, int step, int bodyIndex) {
    btTransform trans;
    if (body && body->getMotionState()) {
        body->getMotionState()->getWorldTransform(trans);
    } else {
        trans = body->getWorldTransform();
    }
    btVector3 position = trans.getOrigin();
    btVector3 velocity = body->getLinearVelocity();
    std::printf(
        "%d %d "
        COMMON_PRINTF_FLOAT " " COMMON_PRINTF_FLOAT " " COMMON_PRINTF_FLOAT " "
        COMMON_PRINTF_FLOAT " " COMMON_PRINTF_FLOAT " " COMMON_PRINTF_FLOAT,
        step, bodyIndex,
        position.getX(), position.getY(), position.getZ(),
        velocity.getX(), velocity.getY(), velocity.getZ()
    );
}

#endif
