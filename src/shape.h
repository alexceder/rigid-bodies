#include "precompiled.h"

class Shape {

protected:
    virtual void draw();
    virtual int getType() = 0;
    virtual float calculateMass() = 0;
    virtual float calculateMomentOfInertia() = 0;
};