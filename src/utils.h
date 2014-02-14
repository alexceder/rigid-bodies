#ifndef UTILS_H
#define UTILS_H

float cross(const glm::vec2 &lhs, const glm::vec2 &rhs);
glm::vec2 cross(float a, const glm::vec2 &rhs);
glm::vec2 cross(const glm::vec2 &lhs, float a);

void debug_float(const float f);

void debug_point(const glm::vec2 &pos);

void debug_vector(const glm::vec2 &start, const glm::vec2 &vector);
void debug_vector(const glm::vec2 &start, const glm::vec2 &vector, const glm::vec3 &color);

#endif // UTILS_H
