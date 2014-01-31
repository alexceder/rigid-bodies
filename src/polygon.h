#include "precompiled.h"

class Polygon : public Shape {
private:

public:
    Polygon() { };

    void draw();
    int getType();
    float calculateMass();
    float calculateMomentOfInertia();
};