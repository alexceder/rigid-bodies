#include "precompiled.h"

Collision::Collision(RigidBody *a, RigidBody *b)
: _A(a)
, _B(b)
{ }

CollisionPair * Collision::circle2circle()
{
    Circle *shape_A = reinterpret_cast<Circle *>(_A->_shape);
    Circle *shape_B = reinterpret_cast<Circle *>(_B->_shape);

    // Calculate translational vector, which is normal
    glm::vec2 normal = _B->_position - _A->_position;

    // float dist_sqr = std::sqrt( normal.length() );
    float dist_sqr = glm::dot(normal, normal);
    float radius = shape_A->_radius + shape_B->_radius;

    // Not in contact
    if (dist_sqr >= radius * radius) {
        return NULL;
    }

    // In contact
    CollisionPair *cp = new CollisionPair(_A, _B);

    float distance = normal.length();
    cp->_collision_count = 1;

    // I dont know...
    if (distance == 0.0f) {
        assert(false);

        cp->_penetration = shape_A->_radius;
        cp->_normal = glm::vec2(1.0f, 0.0f);
        cp->_collisions[0] = _A->_position;
    } else {
        cp->_penetration = radius - distance;
        // Faster than using Normalized since we already performed sqrt
        cp->_normal = normal / distance;
        cp->_collisions[0] = cp->_normal * shape_A->_radius + _A->_position;
    }

    return cp;
}

CollisionPair * Collision::circle2polygon()
{
    std::cout << "Circle to polygon" << std::endl;
    return new CollisionPair(_A, _B);
}

CollisionPair * Collision::polygon2circle()
{
    std::cout << "Polygon to circle" << std::endl;
    return new CollisionPair(_A, _B);
}

CollisionPair * Collision::polygon2polygon()
{
    std::cout << "Polygon to polygon" << std::endl;
    return new CollisionPair(_A, _B);
}

CollisionPair * Collision::dispatcher()
{
    if ( _A->_shape->getType() == CIRCLE_SHAPE && _B->_shape->getType() == CIRCLE_SHAPE ) {
        return circle2circle();
    } else if ( _A->_shape->getType() == CIRCLE_SHAPE && _B->_shape->getType() == POLYGON_SHAPE ) {
        return circle2polygon();
    } else if ( _A->_shape->getType() == POLYGON_SHAPE && _B->_shape->getType() == CIRCLE_SHAPE ) {
        return polygon2circle();
    } else if ( _A->_shape->getType() == POLYGON_SHAPE && _B->_shape->getType() == POLYGON_SHAPE ) {
        return polygon2polygon();
    }
    return NULL;
}





