#include "precompiled.h"

class Polygon : public Shape {

public:
    Polygon() { };

    void draw();
    int getType();
    float calculateMass();
    float calculateMomentOfInertia();
};