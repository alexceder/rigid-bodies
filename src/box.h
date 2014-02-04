#ifndef BOX_H
#define BOX_H

class Box : public Shape {

public:
    Box() { };
    Box(glm::vec2, glm::vec2);

    void draw();
    int getType();
    float calculateMass();
    float calculateMomentOfInertia();

    glm::vec2 _min;
    glm::vec2 _max;
};

#endif // BOX_H
