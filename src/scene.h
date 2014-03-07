#ifndef SCENE_H
#define SCENE_H

/**
 * Scene class to handle the simulation.
 *  This class is the heart of the simulation, it contains all objects/collisions
 *  and deal with them accordingly.
 */
class Scene {
private:
    std::vector<RigidBody *> _bodies;
    std::vector<int> _ints;
    std::vector<CollisionPair *> _collisions;

public:
    Scene() { };
    void checkCollisions();
    void getImpulse();
    // EULER
    // void applyG();
    void integrateVelocities();
    void updatePositions();
    void clearStep();
    void step();
    void draw();
    void addBody(RigidBody *);

    float t, dt;
};


/**
 * Runge-Kutta declarations.
 *  These are helper structs and function to make
 *  life easier when dealing with RK4.
 */
struct Derivative
{
    glm::vec2 dx;
    glm::vec2 dv;
    float w;
    float dw;
};

struct State
{
    glm::vec2 x;
    glm::vec2 v;
    float ori;
    float dori;
};

glm::vec2 acceleration();

Derivative evaluate(const RigidBody *initial, float t, float dt, const Derivative &d);
Derivative evaluate(const RigidBody *initial, float t);

#endif // SCENE_H
