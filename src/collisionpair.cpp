#include "precompiled.h"

CollisionPair::CollisionPair(RigidBody *A, RigidBody *B)
: _A(A)
, _B(B)
{ };

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

    // 1.
    glm::vec2 velocityAP;
    glm::vec2 velocityBP;

    // Vinkelräta vektorn mot r_ab
    glm::vec2 perpAP;
    glm::vec2 perpBP;
   
    if(_normal[0] > LOWER_LIMIT && _normal[0] < UPPER_LIMIT){
        std::cout << "limit clause" << std::endl;
        velocityAP = _A->_velocity;
        velocityBP = _B->_velocity;
        
    } else if ((_normal[0] > 0 && _normal[1] > 0) || (_normal[0] < 0 && _normal[1] < 0)) {
        std::cout << "right hit" << std::endl;
        perpAP = glm::vec2(-(_collisions[0][1] - _A->_position[1]), _collisions[0][0] - _A->_position[0]);
        perpBP = glm::vec2(-(_collisions[0][1] - _B->_position[1]), _collisions[0][0] - _B->_position[0]);
        velocityAP = _A->_velocity + _A->_angularVelocity * perpAP;
        velocityBP = _B->_velocity + _B->_angularVelocity * perpBP; 


    } else {
        std::cout << "left hit" << std::endl;
        perpAP = glm::vec2((_collisions[0][1] - _A->_position[1]), -(_collisions[0][0] - _A->_position[0]));
        perpBP = glm::vec2((_collisions[0][1] - _B->_position[1]), -(_collisions[0][0] - _B->_position[0]));
        velocityAP = _A->_velocity - _A->_angularVelocity * perpAP;
        velocityBP = _B->_velocity - _B->_angularVelocity * perpBP;

    }


    
    //std::cout << "normal X: " << _normal[0] << " normal Y: " << _normal[1] << std::endl; 
    std::cout << "PerpAP X: " << perpAP[0] << " PerpAP Y: " << perpAP[1] << std::endl; 
    std::cout << "PerpBP X: " << perpBP[0] << " PerpBP Y: " << perpBP[1] << std::endl; 

    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(perpAP[0], perpAP[1]);
    glVertex2f(_collisions[0][0], _collisions[0][1]);
    glColor3f(1.0,1.0,1.0);
    glEnd();
    // 2.
    glm::vec2 velocityAB = velocityAP - velocityBP;    

    // 3.
    float numerator = -(1 + _B->_restitution) * glm::dot(velocityAB, _normal);

    // 4.
  /*  float denominator = glm::dot(_normal, _normal) * ((1 / _A->_mass) + (1 / _B->_mass))
                        + ((perpAP[0]*_normal[1]-perpAP[1]*_normal[0]) * (perpAP[0]*_normal[1]-perpAP[1]*_normal[0])) / _A->_momentOfInertia
                        + ((perpBP[0]*_normal[1]-perpBP[1]*_normal[0]) * (perpBP[0]*_normal[1]-perpBP[1]*_normal[0])) / _B->_momentOfInertia;
  */
    float denominator = glm::dot(_normal, _normal) * ((1 / _A->_mass) + (1 / _B->_mass))
                        + (glm::dot(perpAP,_normal) * glm::dot(perpAP, _normal)) / _A->_momentOfInertia
                        + (glm::dot(perpBP,_normal) * glm::dot(perpBP, _normal)) / _B->_momentOfInertia;

    // 5.
    float impulse = numerator/denominator;

    std::cout << "impulse: " << impulse << std::endl;

    // 1 & 2.
    _A->_velocity = _A->_velocity + (impulse / _A->_mass) * _normal;
    _B->_velocity = _B->_velocity - (impulse / _B->_mass) * _normal;

    // 3 & 4.
    //FRICTION BITCHES!!!
    
    if((_normal[0] > 0 && _normal[1] > 0) || (_normal[0] < 0 && _normal[1] < 0)){
        _A->_angularVelocity += ( glm::dot(perpAP, impulse * (_A->_frictionalConstant*glm::normalize(perpAP)))) / _A->_momentOfInertia;
        _B->_angularVelocity += ( glm::dot(perpBP, impulse * (_B->_frictionalConstant*glm::normalize(perpBP)))) / _B->_momentOfInertia;
    } else if(_normal[0] > LOWER_LIMIT && _normal[0] < UPPER_LIMIT){
        _A->_angularVelocity = 0;
        _B->_angularVelocity = 0;
    }else{
        _A->_angularVelocity -= ( glm::dot(perpAP, impulse * (_A->_frictionalConstant*glm::normalize(perpAP)))) / _A->_momentOfInertia;
        _B->_angularVelocity -= ( glm::dot(perpBP, impulse * (_B->_frictionalConstant*glm::normalize(perpBP)))) / _B->_momentOfInertia;
    }

    std::cout << "1: A angl " << _A->_angularVelocity << std::endl;

    float dt = 0.01667;

    float torqueA;
    float torqueB;

    torqueA = _A->_momentOfInertia * _A->_angularVelocity / dt;
    torqueA = _B->_momentOfInertia * _B->_angularVelocity / dt;

    _A->_torque = torqueA;
    _B->_torque = torqueB;
    //assert(1==2);
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
