#ifndef CIRCLE_H
#define CIRCLE_H

class Circle : public Shape {
private:
    float _radius;

public:
    Circle(float);

    void draw();
    int getType();
    float calculateMass();
    float calculateMomentOfInertia();
};

#endif // CIRCLE_H