#ifndef TRIANGLE_06012024
#define TRIANGLE_06012024

#include <vector>
#include "point.hpp"

class Triangle {
private:
    // invariant: three ccw ordered verts with non zero area
    // also splits into 3 more triangles
    std::vector<Vector3D> verts;
    const int kNumVerts = 3;
    const int kNumPatches = 3;

    bool isRightTriple(Vector3D a, Vector3D b, Vector3D c) const;
public:
    Triangle() = default;
    ~Triangle() = default;

    // order ccw (checking inside)
    Triangle(Vector3D a, Vector3D b, Vector3D c);

    Vector3D& GetSpecVert(int number);

    // func returns cords of smaller fractial triangles
    std::vector<Triangle> split();

    float GetArea();
};

#endif