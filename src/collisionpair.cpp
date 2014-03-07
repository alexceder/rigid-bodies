#include "precompiled.h"

CollisionPair::CollisionPair(RigidBody *A, RigidBody *B)
: _A(A)
, _B(B)
{ };

void CollisionPair::applyImpulse()
{
    // Calculate the compound restitution constant.
    float e = glm::min(_A->_restitution, _B->_restitution);

    for (size_t i = 0; i < _collision_count; i++)
    {
        // Show the collision point.
        // debug_point(_collisions[i]);

        // Vectors from com to collision point.
        glm::vec2 ra = _collisions[i] - _A->_position;
        glm::vec2 rb = _collisions[i] - _B->_position;

        // Relative velocity, cross product is (x, y) => -(-ay, ax).
        glm::vec2 rv = _B->_velocity + cross(_B->_angularVelocity, rb) - _A->_velocity - cross(_A->_angularVelocity, ra);

        float x = glm::dot( rv, _normal );

        // If separating, do nothing.
        if (x > 0) continue;

        // Calculate the impulse coefficient.
        float raxn = glm::dot(ra, _normal);
        float rbxn = glm::dot(rb, _normal);
        float denominator = _A->_imass + _B->_imass + raxn * raxn * _A->_imomentOfInertia + rbxn * rbxn * _B->_imomentOfInertia;
        float j = -(1.0f + e) * x;
        j /= denominator * _collision_count;

        // Calculate the impulse vector.
        glm::vec2 impulse = glm::normalize(_normal) * j;

        // Apply the impulse to the rigid bodies.
        _A->applyImpulse(-impulse, ra);
        _B->applyImpulse(impulse, rb);

        // Calculate the collisions tangent vector.
        glm::vec2 t = rv - (_normal * glm::dot( rv, _normal ));
        // debug_vector(_collisions[i], t);

        // Calculate the friction impulse coefficient.
        float jt = -glm::dot( rv, t );
        jt /= denominator * _collision_count;

        // Calculate the relative friction.
        float fc = std::sqrt( _A->_frictionalConstant * _B->_frictionalConstant );

        // Coulumb's law
        glm::vec2 tangentImpulse;
        if (std::abs( jt ) < j * fc) tangentImpulse = t * jt;
        else tangentImpulse = t * -j * fc;

        // Apply friction impulse
        _A->applyImpulse( -tangentImpulse, ra );
        _B->applyImpulse( tangentImpulse, rb );
    }
}

void CollisionPair::correctPosition()
{
    // There is something wrong with this function as shown in the simulation.

    // Penetration allowance
    const float k_slop = 0.001f;
    // Penetration percentage to correct
    const float percent = 0.8f;
    float tempMass;

    // Kinda ugly fix, but it works.
    if (!_A->_isStatic && !_B->_isStatic)
        tempMass = _A->_imass + _B->_imass;
    else if (_A->_isStatic)
        tempMass = _B->_imass + _B->_imass;
    else if (_B->_isStatic)
        tempMass = _A->_imass + _A->_imass;

    glm::vec2 correction = (std::max( _penetration - k_slop, 0.0f ) / (_A->_imass + _B->_imass)) * _normal * percent;
    if (!_A->_isStatic) _A->_position -= correction * _A->_imass;
    if (!_B->_isStatic) _B->_position += correction * _B->_imass;
}
