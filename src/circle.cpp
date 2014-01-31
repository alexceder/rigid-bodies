#include "precompiled.h"

Circle::Circle(float r)
: _radius(r)
{ }

void Circle::draw()
{
    // TODO
}

int Circle::getType()
{
    return CIRCLE_SHAPE;
}

float calculateMass()
{
    float area = _radius * _radius * PI;
    return area * DENSITY;
}

float calculateMomentOfInertia()
{
    // Moment of inertia:
    // http://en.wikipedia.org/wiki/List_of_area_moments_of_inertia
    return (PI / 4) * _radius * _radius * _radius * _radius;
}
