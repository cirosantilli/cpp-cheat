#ifndef COMMON_HPP
#define COMMON_HPP

#include <cstdio>
#include <type_traits>

#include <btBulletDynamicsCommon.h>

#define COMMON_PRINTF_FLOAT "%.3e"
#define COMMON_PRINTF_HEADER "step body x y z vx vy vz rx ry rz angle rvx rvy rvz"

constexpr double PI2 = 2 * acos(-1.0);

void commonPrintBodyState(const btRigidBody *body, int step, int bodyIndex) {
    btTransform trans;
    if (body && body->getMotionState()) {
        body->getMotionState()->getWorldTransform(trans);
    } else {
        trans = body->getWorldTransform();
    }
    auto position = trans.getOrigin();
    auto velocity = body->getLinearVelocity();

    auto rotationQuat = body->getCenterOfMassTransform().getRotation();
    auto rotationAxis = rotationQuat.getAxis();
    auto rotationAngle = rotationQuat.getAngle() / PI2;

    auto angularVelocity = body->getAngularVelocity();
    std::printf(
        "%d %d "
        COMMON_PRINTF_FLOAT " " COMMON_PRINTF_FLOAT " " COMMON_PRINTF_FLOAT " "
        COMMON_PRINTF_FLOAT " " COMMON_PRINTF_FLOAT " " COMMON_PRINTF_FLOAT " "
        COMMON_PRINTF_FLOAT " " COMMON_PRINTF_FLOAT " " COMMON_PRINTF_FLOAT " " COMMON_PRINTF_FLOAT " "
        COMMON_PRINTF_FLOAT " " COMMON_PRINTF_FLOAT " " COMMON_PRINTF_FLOAT " "
        ,
        step, bodyIndex,
        position.getX(), position.getY(), position.getZ(),
        velocity.getX(), velocity.getY(), velocity.getZ(),
        rotationAxis.getX(), rotationAxis.getY(), rotationAxis.getZ(), rotationAngle,
        angularVelocity.getX(), angularVelocity.getY(), angularVelocity.getZ()
    );
}

#endif
