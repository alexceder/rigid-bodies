#ifndef SCENE_H
#define SCENE_H

class Scene {
private:
    std::vector<RigidBody *> _bodies;
    std::vector<int> _ints;
    std::vector<CollisionPair *> _collisions;
    float dt;

public:
    Scene() { };
    void checkCollisions();
    void getImpulse(); // Not sure if we need this.
    void applyG();
    void integrateVelocities();
    void updatePositions();
    void clearStep();
    void step();
    void draw();
    void addBody(RigidBody *);
};

#endif // SCENE_H
