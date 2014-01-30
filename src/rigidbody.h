#include "precompiled.h"

class RigidBody {
protected:
    float _mass;
    float _invMass;

    glm::vec2 _velocity;
    glm::vec2 _force;

    float _angularVelocity;
    float _orient;
    float _torque;

    float _restitution;
    Shape *shape;
};