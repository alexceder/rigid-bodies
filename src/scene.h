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
    void applyImpulse();
    void integrateAcceleration();
    void integrateVelocities();
    void updatePosistions();
    void step();
    void draw();
    void addBody(RigidBody *);
};