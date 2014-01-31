#include "precompiled.h"

Circle::Circle(float r)
: _radius(r)
{ }

void Circle::draw( glm::vec2 pos)
{
    float num_segments = 25.0f;
    float theta = 2 * PI / num_segments; 
    float _cos = cosf(theta);//precalculate the sine and cosine
    float _sin = sinf(theta);
    float temp;

    float x = _radius;//we start at angle = 0
    float y = 0;
    float xPos = pos[0];
    float yPos = pos[1];
    
    glBegin(GL_LINE_LOOP); 
    for(int i = 0; i < num_segments; i++)
    {
        glVertex2f(x + xPos, y + yPos);//output vertex 
        
        //apply the rotation matrix
        temp = x;
        x = _cos * x - _sin * y;
        y = _sin * temp + _cos * y;
    }
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
