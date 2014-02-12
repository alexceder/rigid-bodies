#include "precompiled.h"

CollisionPair::CollisionPair(RigidBody *A, RigidBody *B)
: _A(A)
, _B(B)
{ };

void CollisionPair::applyImpulse()
{
    glm::vec2 velocityAP, velocityBP;

    float dt = 0.01667;

    glm::vec2 perpAP = glm::vec2(-(_collisions[0][1] - _A->_position[1]), _collisions[0][0] - _A->_position[0]);
    glm::vec2 perpBP = glm::vec2(-(_collisions[0][1] - _B->_position[1]), _collisions[0][0] - _B->_position[0]);;

    // In the case of a right hit.
    if ((_normal[0] > 0 && _normal[1] > 0) || (_normal[0] < 0 && _normal[1] < 0)) {
        velocityAP = _A->_velocity + _A->_angularVelocity * perpAP;
        velocityBP = _B->_velocity + _B->_angularVelocity * perpBP;

    // In the case of a left hit.
    } else {
        velocityAP = _A->_velocity - _A->_angularVelocity * _normal;
        velocityBP = _B->_velocity - _B->_angularVelocity * _normal;
    }

    glm::vec2 velocityAB = velocityAP - velocityBP;

    // Calcing the impulse coefficient.
    float numerator = -(1 + _B->_restitution) * glm::dot(velocityAB, _normal);

    float denominator = glm::dot(_normal, _normal) * ((1 / _A->_mass) + (1 / _B->_mass))
                        + glm::dot(perpAP, _normal) * glm::dot(perpAP, _normal)  / _A->_momentOfInertia
                        + glm::dot(perpBP, _normal) * glm::dot(perpBP, _normal)  / _B->_momentOfInertia;
                        // + cross(perpAP, _normal) * cross(perpAP, _normal)  / _A->_momentOfInertia
                        // + cross(perpBP, _normal) * cross(perpBP, _normal)  / _B->_momentOfInertia;

    float impulse = numerator / denominator;

    // Apply impulse
    if ( ! _A->_isStatic ) _A->_velocity = _A->_velocity + (impulse / _A->_mass) * _normal;
    if ( ! _A->_isStatic ) _B->_velocity = _B->_velocity - (impulse / _B->_mass) * _normal;
    std::cout << "Applying impulse: " << impulse << std::endl;

    if ((_normal[0] > 0 && _normal[1] > 0) || (_normal[0] < 0 && _normal[1] < 0)) {
        _A->_angularVelocity += ( glm::dot(perpAP,  impulse * ( _A->_frictionalConstant * perpAP ) ) ) / _A->_momentOfInertia;
        _B->_angularVelocity += ( glm::dot(perpBP,  impulse * ( _B->_frictionalConstant * perpBP ) ) ) / _B->_momentOfInertia;
    } else {
        _A->_angularVelocity += ( glm::dot(perpAP, -impulse * ( _A->_frictionalConstant * perpAP ) ) ) / _A->_momentOfInertia;
        _B->_angularVelocity += ( glm::dot(perpBP, -impulse * ( _B->_frictionalConstant * perpBP ) ) ) / _B->_momentOfInertia;
    }

    _A->_torque = _A->_momentOfInertia * _A->_angularVelocity / dt;
    _B->_torque = _B->_momentOfInertia * _B->_angularVelocity / dt;
}

void CollisionPair::correctPosition()
{
    const float k_slop = 0.05f; // Penetration allowance
    const float percent = 0.4f; // Penetration percentage to correct
    glm::vec2 correction = (std::max( _penetration - k_slop, 0.0f ) / ((1/_A->_mass) + (1/_B->_mass))) * _normal * percent;
    if ( !_A->_isStatic) _A->_position -= correction / _A->_mass;
    if ( !_B->_isStatic) _B->_position += correction / _B->_mass;
}
