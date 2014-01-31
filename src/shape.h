
#include "precompiled.h"

class RigidBody;

class Shape {
public:
    virtual void draw() = 0;
    virtual int getType() = 0;
    virtual float calculateMass() = 0;
    virtual float calculateMomentOfInertia() = 0;

    RigidBody *_rigidBody;
};