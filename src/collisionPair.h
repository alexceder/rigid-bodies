#include "precompiled.h"

class CollisionPair {
private:
    RigidBody* _A;
    RigidBody* _B;
    glm::vec2 _normal;
    glm::vec2 _collisions;
    float _penetration;

public:
    CollisionPair() { };
    CollisionPair(RigidBody *A, RigidBody *B);
    float calculateImpulse(CollisionPair);
    void applyImpulse(float);
    glm::vec2 calculateCollisionNormal(RigidBody* A, RigidBody* B);
};