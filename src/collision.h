#ifndef COLLISION_H
#define COLLISION_H

class CollisionPair;

/**
 * Collision between objects.
 *  This class handles the collisions between two rigid bodies.
 *  If this class is used a CollisionPair is probably returned.
 */
class Collision {
private:
    RigidBody *_A;
    RigidBody *_B;
public:
    Collision(RigidBody *A, RigidBody *B);

    CollisionPair * circle2circle();
    CollisionPair * box2circle();
    CollisionPair * circle2box();

    // TODO
    // CollisionPair * circle2polygon();
    // CollisionPair * polygon2circle();
    // CollisionPair * polygon2polygon();

    CollisionPair * dispatcher();
};

#endif // COLLISION_H
