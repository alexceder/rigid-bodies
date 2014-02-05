#include "precompiled.h"

Box::Box(float b, float h)
: _base(b)
, _height(h)
{
    _max = glm::vec2(-_base/2, _height/2);
    _min = glm::vec2(_base/2, -_height/2);
}

void Box::draw()
{
    glm::vec2 topLeft = _rigidBody->_position + _max;
    glm::vec2 topRight = _rigidBody->_position + glm::vec2(_base/2, _max[1]);
    glm::vec2 bottomRight = _rigidBody->_position + _min;
    glm::vec2 bottomLeft = _rigidBody->_position + glm::vec2(-_base/2, _min[1]);

    glBegin(GL_LINE_LOOP);
        glVertex2f(topLeft[0], topLeft[1]);
        glVertex2f(topRight[0], topRight[1]);
        glVertex2f(bottomRight[0], bottomRight[1]);
        glVertex2f(bottomLeft[0], bottomLeft[1]);
    glEnd();
}

int Box::getType()
{
    return BOX_SHAPE;
}

float Box::calculateMass()
{
    return _base * _height  * DENSITY;
}

float Box::calculateMomentOfInertia()
{
    return _base * _height * _height * _height / 12;
}
