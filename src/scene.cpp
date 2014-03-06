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
    // for (std::vector<RigidBody *>::iterator it = _bodies.begin() ; it != _bodies.end(); ++it) {
    //     if ( (*it)->_isStatic ) continue;

    //     (*it)->_velocity += glm::vec2(0, GRAVITATIONAL_FORCE) * dt;
    // }
    // RECONSIDER
}

Derivative evaluate(const RigidBody *initial, float t, float dt, const Derivative &d)
{
    State state;
    state.x = initial->_position + d.dx * dt;
    state.v = initial->_velocity + d.dv * dt;
    state.ori = initial->_orientation + d.w * dt;
    state.dori = initial->_angularVelocity + d.dw * dt;

    Derivative output;
    output.dx = state.v;
    output.dv = acceleration();
    output.w = state.dori;
    output.dw = 0;

    return output;
}

Derivative evaluate(const RigidBody *initial, float t)
{
    Derivative output;
    output.dx = initial->_velocity;
    output.dv = acceleration();
    output.w = initial->_angularVelocity;
    output.dw = 0;
    return output;
}

glm::vec2 acceleration()
{
    // (*it)->_velocity += glm::vec2(0, GRAVITATIONAL_FORCE) * dt;
    return glm::vec2(0, GRAVITATIONAL_FORCE);
}

void Scene::integrateVelocities()
{
    for (std::vector<RigidBody *>::iterator it = _bodies.begin() ; it != _bodies.end(); ++it) {
        if ( (*it)->_isStatic ) continue;

        // (*it)->_position += (*it)->_velocity * dt;
        // (*it)->_orientation += (*it)->_angularVelocity * dt;

        Derivative a = evaluate(*it, t);
        Derivative b = evaluate(*it, t, dt*0.5f, a);
        Derivative c = evaluate(*it, t, dt*0.5f, b);
        Derivative d = evaluate(*it, t, dt, c);

        const glm::vec2 dxdt = 1.0f/6.0f * (a.dx + 2.0f*(b.dx + c.dx) + d.dx);
        const glm::vec2 dvdt = 1.0f/6.0f * (a.dv + 2.0f*(b.dv + c.dv) + d.dv);
        const float wdt = 1.0f/6.0f * (a.w + 2.0f*(b.w + c.w) + d.w);
        const float dwdt = 1.0f/6.0f * (a.dw + 2.0f*(b.dw + c.dw) + d.dw);

        (*it)->_position += dxdt*dt;
        (*it)->_velocity += dvdt*dt;
        (*it)->_orientation += wdt*dt;
        (*it)->_angularVelocity += dwdt*dt;
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
    t += dt;
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
