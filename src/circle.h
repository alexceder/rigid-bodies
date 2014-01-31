#include "precompiled.h"

class Circle : public Shape {
private:
    float _radius;

public:
    Circle(float);

    void draw( glm::vec2 );
    int getType();
    float calculateMass();
    float calculateMomentOfInertia();
};
