#include "precompiled.h"

void Scene::checkCollisions()
{
    for (std::vector<RigidBody *>::iterator itA = _bodies.begin() ; itA != _bodies.end(); ++itA) {
        for (std::vector<RigidBody *>::iterator itB = _bodies.begin() ; itB != _bodies.end(); ++itB) {
            // Do not continue if they are the same object
            if (itA == itB) continue;

            Collision *collision = new Collision(*itA, *itB);
            CollisionPair *cp = collision->dispatcher();
            if (cp != NULL) {
                _collisions.push_back(cp);
            }
        }
    }
}

// Not sure if we need this.
void Scene::applyImpulse()
{
    // TODO
}

void Scene::applyG()
{
    float dt = 0.01667;
    for (std::vector<RigidBody *>::iterator it = _bodies.begin() ; it != _bodies.end(); ++it) {
        if ( (*it)->_isStatic ) continue;

        (*it)->_velocity += glm::vec2(0, GRAVITATIONAL_FORCE) * dt / (*it)->_mass;
        // std::cout << (*it)->_velocity[1] << std::endl;
        // (*it)->_angularVelocity += dt / (*it)->_momentOfInertia;
    }
}

// Do not think we need this.
void Scene::integrateAcceleration()
{
    // TODO
}

void Scene::integrateVelocities()
{
    float dt = 0.01667;
    for (std::vector<RigidBody *>::iterator it = _bodies.begin() ; it != _bodies.end(); ++it) {
        (*it)->_position += (*it)->_velocity * dt;
        std::cout << "velo: " << (*it)->_velocity[1] << std::endl;
        std::cout << "pos:  " << (*it)->_position[1] << std::endl;
        // (*it)->orient += (*it)->angularVelocity * dt;
    }
}

void Scene::updatePositions()
{
    // TODO
}

void Scene::step()
{
    checkCollisions();
    applyG();
    integrateAcceleration();
    applyImpulse();
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
