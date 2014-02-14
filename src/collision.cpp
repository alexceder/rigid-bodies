#include "precompiled.h"

Collision::Collision(RigidBody *a, RigidBody *b)
: _A(a)
, _B(b)
{ }

CollisionPair * Collision::circle2circle()
{
    Circle *shapeA = reinterpret_cast<Circle *>(_A->_shape);
    Circle *shapeB = reinterpret_cast<Circle *>(_B->_shape);
    // Calculate translational vector, which is normal
    glm::vec2 normal = _B->_position - _A->_position;

    // float dist_sqr = std::sqrt( normal.length() );
    float dist_sqr = glm::dot(normal, normal);
    float radius = shapeA->_radius + shapeB->_radius;

    // Not in contact
    if (dist_sqr >= radius * radius) {
        return NULL;
    }

    float distance = glm::length(normal);

    // In contact
    CollisionPair *cp = new CollisionPair(_A, _B);

    cp->_collision_count = 1;
    // cp->_penetration = radius - distance;
    cp->_penetration = radius - distance;
    // Faster than using Normalized since we already performed sqrt
    cp->_normal = normal / distance;
    // cp->_normal = glm::normalize(normal);
    // std::cout << cp->_normal.x << ", " << cp->_normal.y << std::endl;
    cp->_collisions[0] = cp->_normal * shapeA->_radius + _A->_position;

    return cp;
}

CollisionPair * Collision::box2circle()
{
    Box *shapeA = reinterpret_cast<Box *>(_A->_shape);
    Circle *shapeB = reinterpret_cast<Circle *>(_B->_shape);

    glm::vec2 closest;
    closest[0] = glm::clamp(_B->_position[0], _A->_position[0] - shapeA->_base/2, _A->_position[0] + shapeA->_base/2);
    closest[1] = glm::clamp(_B->_position[1], _A->_position[1] - shapeA->_height/2, _A->_position[1] + shapeA->_height/2);

    glm::vec2 normal = _B->_position - closest;

    float distance_squared = glm::dot(normal, normal);

    // glBegin(GL_LINES);
    //     glColor3f(0.0f, 1.0f, 0.0f);
    //     glVertex2f(_B->_position[0], _B->_position[1]);
    //     glVertex2f(closest[0], closest[1]);
    //     glColor3f(1.0f, 1.0f, 1.0f);
    // glEnd();

    if (distance_squared > shapeB->_radius * shapeB->_radius) {
        return NULL;
    }

    CollisionPair *cp = new CollisionPair(_A, _B);
    cp->_collision_count = 1;
    cp->_penetration = shapeB->_radius - glm::length(normal);
    cp->_normal = glm::normalize(normal);
    cp->_collisions[0] = closest;
    return cp;
}

CollisionPair * Collision::circle2box()
{
    RigidBody *temp = _A;
    _A = _B;
    _B = temp;
    CollisionPair *cp = this->box2circle();
    if (cp != NULL) {
        // Not sure about this whole deal.
        cp->_normal *= -1;
        return cp;
    }
    return NULL;
}

CollisionPair * Collision::dispatcher()
{
    if ( _A->_shape->getType() == CIRCLE_SHAPE && _B->_shape->getType() == CIRCLE_SHAPE ) {
        return circle2circle();
    } else if ( _A->_shape->getType() == BOX_SHAPE && _B->_shape->getType() == CIRCLE_SHAPE ) {
        return box2circle();
    } else if ( _A->_shape->getType() == CIRCLE_SHAPE && _B->_shape->getType() == BOX_SHAPE ) {
        return circle2box();
    }
    return NULL;
}
