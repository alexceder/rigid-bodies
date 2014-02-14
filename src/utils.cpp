#include "precompiled.h"

float cross(const glm::vec2 &lhs, const glm::vec2 &rhs)
{
    return lhs[0] * rhs[1] - rhs[0] * lhs[1];
}

glm::vec2 cross(float a, const glm::vec2 &rhs)
{
    return glm::vec2( -a * rhs[1], a * rhs[0] );
}

glm::vec2 cross(const glm::vec2 &lhs, float a)
{
    return glm::vec2( a * lhs[1], -a * lhs[0] );
}

void debug_float(const float f)
{
    std::cout << f << std::endl;
}

void debug_point(const glm::vec2 &pos)
{
    glPointSize(5.0f);
    glBegin(GL_POINTS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(pos.x, pos.y);
        glColor3f(1.0f, 1.0f, 1.0f);
    glEnd();
}

void debug_vector(const glm::vec2 &start, const glm::vec2 &vector)
{
    glBegin(GL_LINES);
        glVertex2f(start.x, start.y);
        glVertex2f(start.x+vector.x, start.y+vector.y);
    glEnd();
}

void debug_vector(const glm::vec2 &start, const glm::vec2 &vector, const glm::vec3 &color)
{
    glBegin(GL_LINES);
        glColor3f(color.x, color.y, color.z);
        glVertex2f(start.x, start.y);
        glVertex2f(start.x+vector.x, start.y+vector.y);
        glColor3f(1.0f, 1.0f, 1.0f);
    glEnd();
}
