#include "precompiled.h"

Circle::Circle(float r)
: _radius(r)
{ }

void Circle::draw()
{
    float num_segments = 50.0f;
    float theta = 2 * PI / num_segments;
    float _cos = cosf(theta);
    float _sin = sinf(theta);
    float temp;
    float x = _radius;
    float y = 0;

    float cosAng = cosf(_rigidBody->_orientation);
    float sinAng = sinf(_rigidBody->_orientation);
    float lineX = _radius;
    float lineY = 0;
    float tempLine;

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
        if (_rigidBody->_angularVelocity < 0)
            glColor3f(0.94f, 0.43f, 0.67f);
        else
            glColor3f(0.11f, 0.73f, 0.71f);
        tempLine = lineX;
        lineX = cosAng * lineX - sinAng * lineY;
        lineY = sinAng * tempLine + cosAng * lineY;

        glVertex2f(xPos, yPos);
        glVertex2f(lineX + xPos, lineY + yPos);
        glColor3f(1.0f, 1.0f, 1.0f);
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
