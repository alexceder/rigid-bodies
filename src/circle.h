#include "precompiled.h"

class Circle : public RigidBody {
private:
    float _radius;

public:
    Circle(float);

    void draw();
};