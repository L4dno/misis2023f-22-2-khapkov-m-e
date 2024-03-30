#include "include/mesh_generator/hexagon.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <map>
#include <stdexcept>

Hexagon::Hexagon(Vector3D c, float rad) : center(c), radius(rad){
    verts.resize(kNumVerts);
    for (int i = 0; i < kNumVerts; ++i) {
        float angle_deg = 60 * i - 30;
        float angle_rad = M_PI / 180.0f * angle_deg;
        verts[i] = Vector3D{ center.x + radius * std::cos(angle_rad),
                           center.y + radius * std::sin(angle_rad)};
    }
}

Vector3D Hexagon::GetSpecVert(int num) const {
    if (num < 0 || num > 6)
        throw std::invalid_argument("not a vertex number");
    if (num == 6)
        return center;
    return verts[num];
}

std::vector<Triangle> Hexagon::Split() const {
    std::vector<Triangle> res;
    for (int i = 0; i < KNumPatches; ++i) {
        res.push_back(Triangle(GetSpecVert(i),
            GetSpecVert((i + 1) % kNumVerts),
            center));
    }
    return res;
}

void Hexagon::SetSpecVert(int num, Vector3D point) {
    if (num < 0 || num > 6)
        throw std::invalid_argument("not a vertex number");
    if (num == 6)
        center = point;
    else 
        verts[num] = point;
}
