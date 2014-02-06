#include "precompiled.h"

CollisionPair::CollisionPair(RigidBody *A, RigidBody *B)
: _A(A)
, _B(B)
{ };

float CollisionPair::calculateImpulse(CollisionPair *cp)
{
    /*
    1. Ta ut hastigheterna i kollisionspunkterna
        Hastighet i kollisionspunkten = masscentrums linjära hastighet + vinkelhastigheten * en vektor vinkelrät mot r
        (r är vektorn från O till punkten)
        V_ap = V_0 + w * r_0B(vinkelrät)

    2. Ta ut gemensamma hastigheten i kollisionen
        Hastighet i kollisionen = hastighet i punkt A - hastighet i punkt B

    3. Ta ut en vektor vinkelrät mot vektorn r_AP
        vektor vinkelrät mot vektorn r_AP = (hastighet för obj kollis.punkt - hastighet för obj) / vinkelhastighet för obj
        r_ap(vinkelrät) = (V_ap - V_a) / w;
        (alla hastigheter är post-collision)

    4. TÄLJAREN:
        -(1 + restitution) * hastighet i kollision * kollisionsnormalen

    5. NÄMNAREN
        normal * normal (1 / M_a + 1 / M_b)
        + ( (r_ap(vinkelrät) * normal)^2 / moment of inertia för A)
        + ( (r_bp(vinkelrät) * normal)^2 / moment of inertia för B)

    6. impuls = täljare / nämnare
    */

    // 1.
   /// KOLLLA RIKTNING X PÅ NORMAAAAL ! SÄTT ALLTID DEN MED HÖGST Ypos SOM A OBJEKKT!!!!
    glm::vec2 velocityAP = _A->_velocity + _A->_angularVelocity * _normal;
    glm::vec2 velocityBP = _B->_velocity + _B->_angularVelocity * _normal;

    // 2.
    glm::vec2 velocityAB = velocityAP - velocityBP;

    // 3.
    glm::vec2 perpAP = glm::vec2(-(_collisions[0][1] - _A->_position[1]), _collisions[0][0] - _A->_position[0]);
    glm::vec2 perpBP = glm::vec2(-(_collisions[0][1] - _B->_position[1]), _collisions[0][0] - _B->_position[0]);

    // 4.
    float numerator = -(1 - _B->_restitution) * glm::dot(velocityAB, _normal);

    // 5.
    float denominator = glm::dot(_normal, _normal) * ((1 / _A->_mass) + (1 / _B->_mass))
                        + (glm::dot(perpAP, _normal) * glm::dot(perpAP, _normal)) / _A->_momentOfInertia
                        + (glm::dot(perpBP, _normal) * glm::dot(perpBP, _normal)) / _B->_momentOfInertia;

    // 6.
    float impulse = numerator/denominator;

    return impulse;
}

void CollisionPair::applyImpulse()
{
    /*

    Applicera impuls

    1. A:s nya hastighet = A:s gamla hastighet + (impuls / massa) * normal
        V_a2 = V_a1 + (impuls / massa) * n

    2. B:s nya hastighet = B:s gamla hastighet - (impuls / massa) * normal
        V_b2 = V_b1 - (impuls / massa) * n

    3. A:s nya vinkelhastighet = A:s gamla vinkelhastighet + (r_ap(vinkerät) * impuls * normal) / moment of inertia
        w_a2 = w_a1 + (r_ap(_|_) * impuls * n) / I_a

    4. B:s nya vinkelhastighet = B:s gamla vinkelhastighet + (r_bp(vinkerät) * impuls * normal) / moment of inertia
        w_b2 = w_b1 + (r_bp(_|_) * impuls * n) / I_b
    */

    float impulse = calculateImpulse(this);

    // 1 & 2.
    _A->_velocity = _A->_velocity + (impulse / _A->_mass) * _normal;
    _B->_velocity = _B->_velocity - (impulse / _B->_mass) * _normal;

    // Vinkelräta vektorn mot r_ab
    glm::vec2 perpAP = glm::vec2(-(_collisions[0][1] - _A->_position[1]), _collisions[0][0] - _A->_position[0]);
    glm::vec2 perpBP = glm::vec2(-(_collisions[0][1] - _B->_position[1]), _collisions[0][0] - _B->_position[0]);

    // 3 & 4.
    _A->_angularVelocity += ( glm::dot(perpAP, impulse * _normal) ) / _A->_momentOfInertia;
    _B->_angularVelocity += ( glm::dot(perpBP, impulse * _normal) ) / _B->_momentOfInertia;

    /*
        fricVec = friktionsvektor
        my = frictions konstant
        m = massa
        deltaV = 

        friVec = -my (m * ) 
        */
        float dt = 0.01667;

        glm::vec2 velocityAP = _A->_velocity + _A->_angularVelocity * _normal;
        glm::vec2 velocityBP = _B->_velocity + _B->_angularVelocity * _normal;

        glm::vec2 normVelA = glm::dot(_A->_velocity, -_normal) * (-_normal);
        glm::vec2 normVelB = glm::dot(_B->_velocity, _normal) * (_normal);

        glm::vec2 deltaVelA = normVelA - normVelB;
        glm::vec2 deltaVelB = normVelB - normVelA;

        glm::vec2 tanVelA = normVelA - _A->_velocity;
        glm::vec2 tanVelB = normVelB - _B->_velocity;

        glm::vec2 fricForceA = (-_A->_frictionalConstant) * ( (_A->_mass * deltaVelA) / (dt) ) * ((velocityAP + tanVelB) / glm::length(velocityAP + tanVelB));
        glm::vec2 fricForceB = (-_B->_frictionalConstant) * ( (_B->_mass * deltaVelB) / (dt) ) * ((velocityBP + tanVelA) / glm::length(velocityBP + tanVelA));

        _A->_torque = glm::dot(_B->_position, fricForceA);
        _B->_torque = glm::dot(_A->_position, fricForceB);

        _A->_angularVelocity += (_A->_torque * dt) / _A->_momentOfInertia;
        _B->_angularVelocity += (_B->_torque * dt) / _B->_momentOfInertia;

        std::cout << "fricForceA: " << fricForceA[0] << "   " << fricForceA[1] << std::endl;
        std::cout << "fricForceB: " << fricForceB[0] << "   " << fricForceB[1] << std::endl;
        
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
