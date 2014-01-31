#include "precompiled.h"

class Scene {
private:
    std::vector<RigidBody *> _bodies;
    std::vector<int> _ints;
    std::vector<CollisionPair *> _collisions;
    float dt;

public:
    Scene() { };
    void checkCollisions();
    void applyImpulse(); // Not sure if we need this.
    void applyG();
    void integrateAcceleration();
    void integrateVelocities();
    void updatePositions();
    void step();
    void draw();
    void addBody(RigidBody *);
};
