#include "precompiled.h"

CollisionPair::CollisionPair(RigidBody *A, RigidBody *B)
: _A(A)
, _B(B)
{ };

float CollisionPair::calculateImpulse(CollisionPair cp)    //cp bästa vi kom på
{
    /**********************************************

    Räkna ut impulsen:

    1. Ta ut hastigheterna i kollisionspunkterna
        Hastighet i kollisionspunkten = masscentrums linjära hastighet + vinkelhastigheten * en vektor vinkelrät mot r
        (r är vektorn från O till punkten)
        V_ap = V_0 + w * r_0B(vinkelrät)

    2. Ta ut gemensamma hastigheten i kollisionen
        Hastighet i kollisionen = hastighet i punkt A - hastighet i punkt B
        V_ab = V_ap - V_bp

    3. Ta ut en vektor vinkelrät mot vektorn r_AP
        vektor vinkelrät mot vektorn r_AP = (hastighet för obj kollis.punkt - hastighet för obj) / vinkelhastighet för obj
        r_ap(vinkelrät) = (V_ap - V_a) / w;
        (alla hastigheter är post-collision)

    4. TÄLJAREN
        -(1 + restitution) * hastighet i kollision * kollisionsnormalen

    5. NÄMNAREN
        normal * normal (1 / M_a + 1 / M_b)
        + ( (r_ap(vinkelrät) * normal)^2  / moment of inertia för A)
        + ( (r_bp(vinkelrät) * normal)^2  / moment of inertia för B)

    6. impuls = täljare / nämnare

    **********************************************/
    return 0.0f;
}

void CollisionPair::applyImpulse(float impulse) //var float innan. ska den verkligen returna något?
{
    /**********************************************

    Applicera impuls

    1. A:s nya hastighet = A:s gamla hastighet + (impuls / massa) * normal
        V_a2 = V_a1 + (impuls / massa) * n

    2. B:s nya hastighet = B:s gamla hastighet - (impuls / massa) * normal
        V_b2 = V_b1 - (impuls / massa) * n

    3. A:s nya vinkelhastighet = A:s gamla vinkelhastighet + (r_ap(vinkerät) * impuls * normal) / moment of inertia
        w_a2 = w_a1 + (r_ap(_|_) * impuls * n) / I_a

    4. B:s nya vinkelhastighet = B:s gamla vinkelhastighet + (r_bp(vinkerät) * impuls * normal) / moment of inertia
        w_b2 = w_b1 + (r_bp(_|_) * impuls * n) / I_b

    **********************************************/
}

glm::vec2 CollisionPair::calculateCollisionNormal(RigidBody* A, RigidBody* B)
{
    // TODO
    return glm::vec2(0.0f);
}