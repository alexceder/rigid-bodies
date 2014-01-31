#include "precompiled.h"


class Scene {
private:
    // Collision[] collisions[];
    // RigidBody[] bodies[];
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
};