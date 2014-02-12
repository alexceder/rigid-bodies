#include "precompiled.h"

void Scene::checkCollisions()
{
    for (std::vector<RigidBody *>::iterator itA = _bodies.begin() ; itA != _bodies.end(); ++itA) {
        for (std::vector<RigidBody *>::iterator itB = itA + 1 ; itB != _bodies.end(); ++itB) {
        // for (std::vector<RigidBody *>::iterator itB = _bodies.begin() ; itB != _bodies.end(); ++itB) {
            // std::cout << "Checking: " << *itA << " and " << *itB << std::endl;

            // if (*itA == *itB) continue;

            Collision *collision = new Collision(*itA, *itB);
            CollisionPair *cp = collision->dispatcher();

            if (cp != NULL) {
                _collisions.push_back(cp);
            }
        }
    }
    // std::cout << "Collisions: " << _collisions.size() << std::endl;
    // assert(false);
}

// Not sure if we need this.
void Scene::getImpulse()
{
    for (std::vector<CollisionPair *>::iterator it = _collisions.begin() ; it != _collisions.end(); it++) {
        std::cout << (*it)->_A << (*it)->_B << std::endl << std::endl;
        (*it)->applyImpulse();
    }
}

void Scene::applyG()
{
    float dt = 0.01667;
    for (std::vector<RigidBody *>::iterator it = _bodies.begin() ; it != _bodies.end(); ++it) {
        (*it)->_velocity += glm::vec2(0, GRAVITATIONAL_FORCE) * dt / (*it)->_mass;
    }
}

void Scene::integrateVelocities()
{
    float dt = 0.01667;
    for (std::vector<RigidBody *>::iterator it = _bodies.begin() ; it != _bodies.end(); ++it) {
        if ( (*it)->_isStatic ) continue;
        (*it)->_position += (*it)->_velocity * dt;
        (*it)->_orientation += (*it)->_angularVelocity * dt;
        //std::cout << "ORIENTATION: " << (*it)->_orientation << std::endl;
        //std::cout << "angularvelo: " << (*it)->_angularVelocity << std::endl;
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
