#include "precompiled.h"

/**
 * Constructor that you probably will use most of the time
 * it makes some calculations dependning on the Shape.
 *
 * @param glm::vec2 p
 * @param float o
 * @param Shape *s
 */
RigidBody::RigidBody(glm::vec2 p, float o, Shape *s)
: _position(p)
, _orientation(o)
, _shape(s)
{
    _shape->_rigidBody = this;

    _mass = _shape->calculateMass();
    _imass = 1/_mass;
    _momentOfInertia = _shape->calculateMomentOfInertia();
    _imomentOfInertia = _momentOfInertia;
    _restitution = 0.8f;

    _velocity = glm::vec2(0.0f);
    _angularVelocity = 0.0f;
    _force = glm::vec2(0.0f);
    _torque = 0.0f;
    _isStatic = false;
    _frictionalConstant = 0.1f;
}

/**
 * Constructor that let you decide everything yourself.
 *
 * @param glm::vec2 p
 * @param glm::vec2 v
 * @param float o
 * @param float av
 * @param glm::vec2 f
 * @param float t
 * @param bool is
 * @param float m
 * @param float I
 * @param float e
 * @param Shape *s
 */
RigidBody::RigidBody(glm::vec2 p,
                     glm::vec2 v,
                     float o,
                     float av,
                     glm::vec2 f,
                     float t,
                     bool is,
                     float m,
                     float I,
                     float e,
                     Shape *s)
: _position(p)
, _velocity(v)
, _orientation(o)
, _angularVelocity(av)
, _force(f)
, _torque(t)
, _isStatic(is)
, _mass(m)
, _momentOfInertia(I)
, _restitution(e)
, _shape(s)
{ }

// No idea how this should work.
/**
 * Make sure to delete the shape also.
 */
// RigidBody::~RigidBody()
// {
//     delete _shape;
// }

/**
 * Setup a rigid body to be static.
 */
void RigidBody::setStatic(bool s)
{
    this->_imass = 0;
    this->_isStatic = s;
}

/**
 * Apply sn impulse to the RigidBody
 * i.e. updating the velocity and angular velocity.
 *
 * @param const glm::vec2 &impulse
 * @param const glm::vec2 &collisionVector
 * @return void
 */
void RigidBody::applyImpulse(const glm::vec2 &impulse, const glm::vec2 &collisionVector)
{
    if (!this->_isStatic) {
        _velocity += (1/_mass) * impulse;
        // Maybe not glm::dot should be cross, I think.
        _angularVelocity += (1/_momentOfInertia) * cross(collisionVector, impulse);
    }
}
