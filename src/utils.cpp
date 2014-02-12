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
