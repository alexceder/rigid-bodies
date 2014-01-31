#ifndef POLYGON_H
#define POLYGON_H

class Polygon : public Shape {

public:
    Polygon() { };

    void draw();
    int getType();
    float calculateMass();
    float calculateMomentOfInertia();
};

#endif // POLYGON_H
