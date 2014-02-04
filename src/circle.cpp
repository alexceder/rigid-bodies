#include "precompiled.h"

Circle::Circle(float r)
: _radius(r)
{ }

void Circle::draw()
{
    float num_segments = 25.0f;
    float theta = 2 * PI / num_segments;
    float _cos = cosf(theta);
    float _sin = sinf(theta);
    float temp;
    float temp1;

    float cosAng = cosf(_rigidBody->_orientation);
    float sinAng = sinf(_rigidBody->_orientation);

    //std::cout << "cosAng: " << cosAng << std::endl;

    float x = _radius;
    float y = 0;
    float x1 = _radius;
    float y1 = 0;
    float xPos = _rigidBody->_position[0];
    float yPos = _rigidBody->_position[1];

    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < num_segments; i++)
    {
        glVertex2f(x + xPos, y + yPos);

        // Apply rotation.
        temp = x;
        x = _cos * x - _sin * y;
        y = _sin * temp + _cos * y;
    }
    glEnd();

    glBegin(GL_LINES);

    temp1 = x1;
    x1 = cosAng * x1 - sinAng * y1;
    y1 = sinAng * temp1 + cosAng * y1;

    glVertex2f(xPos, yPos);
    glVertex2f(x1 + xPos, y1 + yPos);
    glEnd();
}

int Circle::getType()
{
    return CIRCLE_SHAPE;
}

float Circle::calculateMass()
{
    float area = _radius * _radius * PI;
    return area * DENSITY;
}

float Circle::calculateMomentOfInertia()
{
    // Moment of inertia:
    // http://en.wikipedia.org/wiki/List_of_area_moments_of_inertia
    return (PI / 4) * _radius * _radius * _radius * _radius;
}
