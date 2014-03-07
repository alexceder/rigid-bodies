#ifndef RIGIDBODY_H
#define RIGIDBODY_H

/**
 * RigidBody
 *  All objects in the simulation is a RigidBody they contain
 *  a shape and physical quantities.
 */
class RigidBody {
public:
    // Create an empty RigidBody
    RigidBody() {};

    // Create a RigidBody and make calculations depending on the Shape.
    RigidBody(glm::vec2 p,
              float o,
              Shape *s);

    // Decide everything yourself.
    RigidBody(glm::vec2 p,
              glm::vec2 v,
              float o,
              float av,
              glm::vec2 f,
              float t,
              bool is,
              float m,
              float I,
              float e,
              Shape *s);

    // No idea how to implement this.
    // ~RigidBody();

    // Apply impulse to a RigidBody.
    void applyImpulse(const glm::vec2 &impulse, const glm::vec2 &collisionNormal);

    // Make a rigid body static.
    void setStatic(bool s);

// This is commented so I don't have to create getters and setters at this point in time.
// private:
    // Positional quantities
    glm::vec2 _position;
    glm::vec2 _velocity;

    // Orientational quantities
    float _orientation;
    float _angularVelocity;

    // Acting forces
    glm::vec2 _force;
    float _torque;
    bool _isStatic;


    // Material
    float _mass;
    float _imass;
    float _momentOfInertia;
    float _imomentOfInertia;
    float _restitution;
    float _frictionalConstant;

    Shape *_shape;
};

#endif // RIGIDBODY_H
