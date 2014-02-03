#ifndef CIRCLE_H
#define CIRCLE_H

class Circle : public Shape {

public:
    Circle(float);

    void draw();
    int getType();
    float calculateMass();
    float calculateMomentOfInertia();

    float _radius;
};

#endif // CIRCLE_H