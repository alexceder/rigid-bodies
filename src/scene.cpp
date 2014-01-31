#include "precompiled.h"

void Scene::checkCollisions()
{
    // TODO
};

void Scene::applyImpulse()
{
    // for (std::vector<RigidBody *>::iterator it = _collisions.begin() ; it != _collisions.end(); ++it) {
    //     it->applyImpulse();
    // }
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

void Scene::updatePosistions()
{
    // TODO
};

void Scene::step()
{
    // TODO
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
