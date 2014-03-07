#ifndef CIRCLE_H
#define CIRCLE_H

/**
 * Circle is a Shape.
 *  A circle is an easy to work with primitive in these kind
 *  of applications since they are always convex and really
 *  only their radius matters.
 */
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