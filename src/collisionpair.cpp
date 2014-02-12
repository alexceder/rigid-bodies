#include "precompiled.h"

CollisionPair::CollisionPair(RigidBody *A, RigidBody *B)
: _A(A)
, _B(B)
{ };

void CollisionPair::applyImpulse()
{
    glm::vec2 velocityAP, velocityBP;

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
                        + cross(perpAP, _normal) * cross(perpAP, _normal)  / _A->_momentOfInertia
                        + cross(perpBP, _normal) * cross(perpBP, _normal)  / _B->_momentOfInertia;
                        // + (perpAP[0]*_normal[1]-perpAP[1]*_normal[0]) * (perpAP[0]*_normal[1]-perpAP[1]*_normal[0]) / _A->_momentOfInertia
                        // + (perpBP[0]*_normal[1]-perpBP[1]*_normal[0]) * (perpBP[0]*_normal[1]-perpBP[1]*_normal[0]) / _B->_momentOfInertia;

    float impulse = numerator / denominator;

    // Apply impulse
    _A->_velocity = _A->_velocity + (impulse / _A->_mass) * _normal;
    _B->_velocity = _B->_velocity - (impulse / _B->_mass) * _normal;

    std::cout << "1: A angl " << _A->_angularVelocity << std::endl;
    /*
        fricVec = friktionsvektor
        my = frictions konstant
        m = massa
        deltaV =

        friVec = -my (m * )
        */
    float dt = 0.01667;

    float torqueA;
    float torqueB;

    torqueA = _A->_momentOfInertia * _A->_angularVelocity / dt;
    torqueA = _B->_momentOfInertia * _B->_angularVelocity / dt;

    _A->_torque = torqueA;
    _B->_torque = torqueB;

}

void CollisionPair::correctPosition()
{
    const float k_slop = 0.05f; // Penetration allowance
    const float percent = 0.4f; // Penetration percentage to correct
    glm::vec2 correction = (std::max( _penetration - k_slop, 0.0f ) / ((1/_A->_mass) + (1/_B->_mass))) * _normal * percent;
    _A->_position -= correction / _A->_mass;
    _B->_position += correction / _B->_mass;
}

glm::vec2 CollisionPair::calculateCollisionNormal(RigidBody* A, RigidBody* B)
{
    _normal = glm::vec2(B->_position[0] + A->_position[0], B->_position[1] + A->_position[1]);
    return _normal;
}
