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

        //std::cout << "collisions aids: " << cp->_collisions[0][0] << " " << cp->_collisions[0][1] << std::endl;
    }

    return cp;
}


bool operator==(const glm::vec2 &vecA, const glm::vec2 &vecB) {
    const double epsilion = 0.0001;
    return fabs(vecA[0] -vecB[0]) < epsilion && fabs(vecA[1] -vecB[1]) < epsilion;
}

CollisionPair * Collision::box2circle()
{
    Box *shapeA = reinterpret_cast<Box *>(_A->_shape);
    Circle *shapeB = reinterpret_cast<Circle *>(_B->_shape);

    std::cout << "A-POS: " << _A->_position[0] << ", " << _A->_position[1] << std::endl;
    std::cout << "B-POS: " << _B->_position[0] << ", " << _B->_position[1] << std::endl;

    glm::vec2 normal = _B->_position - _A->_position;

    glm::vec2 closest = normal;

    // glBegin(GL_LINES);
    //     glColor3f(1.0f, 0.0f, 0.0f);
    //     glVertex2f(_A->_position[0], _A->_position[1]);
    //     glVertex2f(_B->_position[0], _B->_position[1]);
    //     glColor3f(1.0f, 1.0f, 1.0f);
    // glEnd();

    // Calculate half extents along each axis
    float x_extent = (shapeA->_max[0] - shapeA->_min[0]) / 2;
    float y_extent = (shapeA->_max[1] - shapeA->_min[1]) / 2;

    // Clamp point to edges of the AABB
    closest[0] = glm::clamp(closest[0], -x_extent, x_extent);
    closest[1] = glm::clamp(closest[1], -y_extent, y_extent);

    bool inside = false;

    // Circle is inside the AABB, so we need to clamp the circle's center to the closest edge
    if (normal == closest) {
        inside = true;

        // Find closest axis
        if (glm::abs(normal[0]) > glm::abs(normal[1])) {
            // Clamp to closest extent
            if (closest[0] > 0)
                closest[0] = x_extent;
            else
                closest[0] = -x_extent;
        }
        // y axis is shorter
        else {
          // Clamp to closest extent
            if (closest[1] > 0)
                closest[1] = y_extent;
            else
                closest[1] = -y_extent;
        }
    }

    glm::vec2 collisionNormal = normal - closest;
    float d = glm::dot(collisionNormal, collisionNormal);
    float r = shapeB->_radius;

    glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(_A->_position[0], _A->_position[1]);
        glVertex2f(collisionNormal[0], collisionNormal[1]);
        glColor3f(1.0f, 1.0f, 1.0f);
    glEnd();

    // Early out of the radius is shorter than distance to closest point and Circle not inside the AABB
    if (d > r * r && !inside)
        return NULL;

    // Avoided sqrt until we needed
    d = std::sqrt( d );

    CollisionPair *cp = new CollisionPair(_A, _B);

    // Collision normal needs to be flipped to point outside if circle was inside the AABB
    if (inside) {
        cp->_normal = -normal;
        cp->_penetration = r + d;
    } else {
        cp->_normal = normal;
        cp->_penetration = r + d;
    }

    std::cout << "BOX 2 CIRCLE, BITCH!" << std::endl;
    return cp;
}

CollisionPair * Collision::circle2box()
{
    RigidBody *temp = _A;
    _A = _B;
    _B = temp;
    return box2circle();
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





