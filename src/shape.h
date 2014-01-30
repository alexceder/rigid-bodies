#include "precompiled.h"

class Shape {

protected:
    virtual void draw();
    virtual int getType() = -1;
};