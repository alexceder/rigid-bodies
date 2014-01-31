#include "precompiled.h"

class Shape {

public:
    virtual void draw() = 0;
    virtual int getType() = 0;
    virtual float calculateMass() = 0;
    virtual float calculateMomentOfInertia() = 0;
};