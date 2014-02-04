#ifndef BOX_H
#define BOX_H

class Box : public Shape {

public:
    Box() { };
    Box(float, float);

    void draw();
    int getType();
    float calculateMass();
    float calculateMomentOfInertia();

    float _base;
    float _height;

    glm::vec2 _min;
    glm::vec2 _max;
};

#endif // BOX_H
