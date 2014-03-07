#ifndef SHAPE_H
#define SHAPE_H

class RigidBody;

/**
 * Shape abstraction class.
 *  This is an abstract class for the shapes it contains
 *  all that is required in a shape.
 */
class Shape {
public:
    virtual void draw() = 0;
    virtual int getType() = 0;
    virtual float calculateMass() = 0;
    virtual float calculateMomentOfInertia() = 0;

    RigidBody *_rigidBody;
};

#endif // SHAPE_H
