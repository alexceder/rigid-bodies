#ifndef POLYGON_H
#define POLYGON_H

class Polygon : public Shape {

public:
    Polygon() { };
    Polygon(std::vector<glm::vec2>, std::vector<glm::vec2>);

    void draw();
    int getType();
    float calculateMass();
    float calculateMomentOfInertia();

    std::vector<glm::vec2> _vertices;
    std::vector<glm::vec2> _normals;
};

#endif // POLYGON_H
