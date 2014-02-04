#include "precompiled.h"


Polygon::Polygon(std::vector<glm::vec2> v, std::vector<glm::vec2> n)
: _vertices(v)
, _normals(n)
{ }

void Polygon::draw()
{
    glBegin(GL_LINE_LOOP);
    for (std::vector<glm::vec2>::iterator it = _vertices.begin() ; it != _vertices.end(); ++it) {
        glVertex2f((*it)[0], (*it)[1]);
    }
    glEnd();
}

int Polygon::getType()
{
    return POLYGON_SHAPE;
}

float Polygon::calculateMass()
{
    // TODO
    return 1.0f;
}

float Polygon::calculateMomentOfInertia()
{
    // TODO
    return 1.0f;
}
