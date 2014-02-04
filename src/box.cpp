#include "precompiled.h"


Box::Box(glm::vec2 min, glm::vec2 max)
: _min(min)
, _max(max)
{ }

void Box::draw()
{
    glBegin(GL_LINE_LOOP);
        glVertex2f(_max[0], _max[1]);
        glVertex2f(_min[0], _max[1]);
        glVertex2f(_min[0], _min[1]);
        glVertex2f(_max[0], _min[1]);
    glEnd();
}

int Box::getType()
{
    return BOX_SHAPE;
}

float Box::calculateMass()
{
    return (_min[0] - _max[0]) * (_min[1] - _max[1])  * DENSITY;
}

float Box::calculateMomentOfInertia()
{
    float h = _min[1] - _max[1];
    return (_min[0] - _max[0]) * h * h * h / 12;
}
