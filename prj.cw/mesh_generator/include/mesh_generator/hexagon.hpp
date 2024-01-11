#ifndef HEXAGON_06012024
#define HEXAGON_06012024

#include "point.hpp"
#include "triangle.hpp"

class Hexagon {
private:

    const int kNumVerts = 6;
    const int KNumPatches = 6;

    Vector3D center = {};
    float radius = 0.0f;
    std::vector<Vector3D> verts;
    

public:

    Hexagon() = default;
    ~Hexagon() = default;
    // pointly top rotation
    Hexagon(Vector3D c, float rad);
     
    // returns vertex number num
    // 6 will return center
    Vector3D GetSpecVert(int v) const;

    void SetSpecVertZ(int v, float z);

    std::vector<Triangle> Split() const;
    
};
#endif 