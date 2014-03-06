#include "precompiled.h"

void Scene::checkCollisions()
{
    for (std::vector<RigidBody *>::iterator itA = _bodies.begin() ; itA != _bodies.end(); ++itA) {
        for (std::vector<RigidBody *>::iterator itB = itA + 1 ; itB != _bodies.end(); ++itB) {

            Collision *collision = new Collision(*itA, *itB);
            CollisionPair *cp = collision->dispatcher();

            if (cp != NULL) {
                _collisions.push_back(cp);
            }
        }
    }
}

void Scene::getImpulse()
{
    for (std::vector<CollisionPair *>::iterator it = _collisions.begin() ; it != _collisions.end(); it++) {
        (*it)->applyImpulse();
    }
}

void Scene::applyG()
{
    float dt = 0.01667;
    for (std::vector<RigidBody *>::iterator it = _bodies.begin() ; it != _bodies.end(); ++it) {
        if ( (*it)->_isStatic ) continue;

        (*it)->_velocity += glm::vec2(0, GRAVITATIONAL_FORCE) * dt;
    }
}

void Scene::integrateVelocities()
{
    float dt = 0.01667;
    for (std::vector<RigidBody *>::iterator it = _bodies.begin() ; it != _bodies.end(); ++it) {
        if ( (*it)->_isStatic ) continue;

        (*it)->_position += (*it)->_velocity * dt;
        (*it)->_orientation += (*it)->_angularVelocity * dt;
    }
}

void Scene::updatePositions()
{
    for (std::vector<CollisionPair *>::iterator it = _collisions.begin() ; it != _collisions.end(); ++it) {
        (*it)->correctPosition();
    }
}

void Scene::step()
{
    checkCollisions();
    applyG();
    getImpulse();
    integrateVelocities();
    updatePositions();
    clearStep();
}

void Scene::clearStep()
{
    _collisions.clear();
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
