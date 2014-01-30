#include "precompiled.h"

enum ShapeType {
    Circle,
    Polygon
};

class Shape {
protected:
    virtual void draw();
    // virtual ShapeType getType();
};