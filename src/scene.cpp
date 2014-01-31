#include "precompiled.h"

void Scene::checkCollisions()
{
    // TODO
};

// Not sure if we need this.
void Scene::applyImpulse()
{
    // TODO
};

void Scene::applyG()
{
    // TODO
};

void Scene::integrateAcceleration()
{
    // TODO
};

void Scene::integrateVelocities()
{
    // position += velocity * dt;
    // orientation += angularVelocity * dt;
};

void Scene::updatePositions()
{
    // TODO
};

void Scene::step()
{
    checkCollisions();
    applyG();
    integrateAcceleration();
    applyImpulse();
    integrateVelocities();
    updatePositions();
}

void Scene::draw()
{
    for (std::vector<RigidBody *>::iterator it = _bodies.begin() ; it != _bodies.end(); ++it) {
        (*it)->_shape->draw();
    }
}

void Scene::addBody(RigidBody *rb)
{
    _bodies.push_back(rb);
}
