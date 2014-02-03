#ifndef COLLISIONPAIR_H
#define COLLISIONPAIR_H

class CollisionPair {

public:
    CollisionPair() { };
    CollisionPair(RigidBody *A, RigidBody *B);
    float calculateImpulse(CollisionPair);
    void applyImpulse(float);
    glm::vec2 calculateCollisionNormal(RigidBody* A, RigidBody* B);

    RigidBody* _A;
    RigidBody* _B;
    glm::vec2 _normal;
    glm::vec2 _collisions[2];
    unsigned int _collision_count;
    float _penetration;
};

#endif // COLLISIONPAIR_H