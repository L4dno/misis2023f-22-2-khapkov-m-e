#ifndef TRIANGLE_06012024
#define TRIANGLE_06012024

#include <vector>
#include "point.hpp"

class Triangle {
private:
    // invariant: three ccw ordered verts with non zero area
    // also splits into 3 more triangles
    std::vector<Vector3D> verts;
    std::vector<Vector3D> tex_cords;
    const int kNumVerts = 3;
    const int kNumPatches = 3;

    bool isCcwOrder(Vector3D a, Vector3D b, Vector3D c) const;
public:
    Triangle() = delete;
    ~Triangle() = default;
    // order ccw (checking inside)
    Triangle(Vector3D a, Vector3D b, Vector3D c);

    Vector3D GetSpecVert(int v) const;

    void SetVertZ(int v, float z);

    // func returns cords of smaller fractial triangles
    std::vector<Triangle> Split() const;

    float GetArea() const;

    void SetVertTexCords(int v, Vector3D uv);
};

#endif