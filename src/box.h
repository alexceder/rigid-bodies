#ifndef BOX_H
#define BOX_H

/**
 * Box is a Shape.
 *  A box for now only implemented to work as a static object
 *  i.e. a floor or a wall.
 */
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
