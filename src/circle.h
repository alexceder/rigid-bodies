#include "precompiled.h"

class Circle : public Shape {
private:
    float _radius;

public:
    Circle(float);

    void draw();
    int getType();
    float calculateMass();
    float calculateMomentOfInertia();
};
