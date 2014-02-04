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

CollisionPair * Collision::box2circle()
{
    Box *shape_A = reinterpret_cast<Circle *>(_A->_shape);
    Circle *shape_B = reinterpret_cast<Circle *>(_B->_shape);

    // CollisionPair *cp = new CollisionPair(_A, _B);

    // return cp;
    return NULL;
}

CollisionPair * Collision::circle2box()
{
    RigidBody *temp = _A;
    _A = _B;
    _B = temp;
    return circle2box;
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

// CollisionPair * Collision::circle2polygon()
// {
//     Circle *shapeA = reinterpret_cast<Circle *>(_A->_shape);
//     Polygon *shapeB = reinterpret_cast<Polygon *>(_A->_shape);

//     CollisionPair *cp = new CollisionPair(_A, _B);

//     cp->_collision_count = 0;

  //   // Transform circle center to Polygon model space
  //   glm::vec2 center = _A->position;
  //   center = B->u.Transpose( ) * (center - b->position);

  // // Find edge with minimum penetration
  // // Exact concept as using support points in Polygon vs Polygon
  // real separation = -FLT_MAX;
  // uint32 faceNormal = 0;
  // for(uint32 i = 0; i < B->m_vertexCount; ++i)
  // {
  //   real s = Dot( B->m_normals[i], center - B->m_vertices[i] );

  //   if(s > A->radius)
  //     return;

  //   if(s > separation)
  //   {
  //     separation = s;
  //     faceNormal = i;
  //   }
  // }

  // // Grab face's vertices
  // Vec2 v1 = B->m_vertices[faceNormal];
  // uint32 i2 = faceNormal + 1 < B->m_vertexCount ? faceNormal + 1 : 0;
  // Vec2 v2 = B->m_vertices[i2];

  // Check to see if center is within polygon
  // if(separation < EPSILON)
  // {
  //   m->contact_count = 1;
  //   m->normal = -(B->u * B->m_normals[faceNormal]);
  //   m->contacts[0] = m->normal * A->radius + a->position;
  //   m->penetration = A->radius;
  //   return;
  // }

  // // Determine which voronoi region of the edge center of circle lies within
  // real dot1 = Dot( center - v1, v2 - v1 );
  // real dot2 = Dot( center - v2, v1 - v2 );
  // m->penetration = A->radius - separation;

  // // Closest to v1
  // if(dot1 <= 0.0f)
  // {
  //   if(DistSqr( center, v1 ) > A->radius * A->radius)
  //     return;

  //   m->contact_count = 1;
  //   Vec2 n = v1 - center;
  //   n = B->u * n;
  //   n.Normalize( );
  //   m->normal = n;
  //   v1 = B->u * v1 + b->position;
  //   m->contacts[0] = v1;
  // }

  // // Closest to v2
  // else if(dot2 <= 0.0f)
  // {
  //   if(DistSqr( center, v2 ) > A->radius * A->radius)
  //     return;

  //   m->contact_count = 1;
  //   Vec2 n = v2 - center;
  //   v2 = B->u * v2 + b->position;
  //   m->contacts[0] = v2;
  //   n = B->u * n;
  //   n.Normalize( );
  //   m->normal = n;
  // }

  // // Closest to face
  // else
  // {
  //   Vec2 n = B->m_normals[faceNormal];
  //   if(Dot( center - v1, n ) > A->radius)
  //     return;

  //   n = B->u * n;
  //   m->normal = -n;
  //   m->contacts[0] = m->normal * A->radius + a->position;
  //   m->contact_count = 1;
  // }
    // std::cout << "Circle to polygon" << std::endl;
    // return new CollisionPair(_A, _B);
//     return NULL;
// }

// CollisionPair * Collision::polygon2circle()
// {
//     RigidBody *t = _A;
//     _A = _B;
//     _B = t;
//     return circle2polygon();
// }

// CollisionPair * Collision::polygon2polygon()
// {
//     std::cout << "Polygon to polygon" << std::endl;
//     return new CollisionPair(_A, _B);
// }





