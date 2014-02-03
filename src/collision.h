#ifndef COLLISION_H
#define COLLISION_H

class CollisionPair;

class Collision {
private:
    RigidBody *_A;
    RigidBody *_B;
public:
    Collision(RigidBody *A, RigidBody *B);

    CollisionPair * circle2circle();
    CollisionPair * circle2polygon();
    CollisionPair * polygon2circle();
    CollisionPair * polygon2polygon();

    CollisionPair * dispatcher();
};

#endif // COLLISION_H
