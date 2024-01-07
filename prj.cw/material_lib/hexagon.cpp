#include "hexagon.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <map>
#include <stdexcept>

Hexagon::Hexagon(Vector3D c, float rad) : center(c), radius(rad){
    verts.resize(kNumVerts);
    center.z = static_cast<int>(height_level) * radius;
    for (int i = 0; i < kNumVerts; ++i) {
        float angle_deg = 60 * i - 30;
        float angle_rad = M_PI / 180.0f * angle_deg;
        verts[i] = Vector3D{ center.x + radius * std::cos(angle_rad),
                           center.y + radius * std::sin(angle_rad),
                            static_cast<int>(height_level)* radius };
    }
}

Vector3D Hexagon::GetSpecVert(int num) const {
    if (num < 0 || num > 6)
        throw std::invalid_argument("not a vertex number");
    if (num == 6)
        return center;
    return verts[num];
}

void Hexagon::SetLevel(HexLevels level) {
    height_level = level;
    center.z = static_cast<int>(height_level) * radius;
    
}

void Hexagon::RecalculateEdges(const std::vector<Hexagon>& grid) {
    for (int i = 0; i < kNumVerts; ++i) {
        InterpolateVertZ(i, grid);
    }
}

std::vector<Triangle> Hexagon::Split() const {
    return {};
}

void Hexagon::InterpolateVertZ(int v_ind, const std::vector<Hexagon>& grid) {
    std::vector<int> closest_hexes = GetNearHexes(v_ind, grid);
    Vector3D bary = GetBarycentricCords(v_ind, closest_hexes, grid);
    verts[v_ind].z = bary.x * grid[closest_hexes[0]].center.z +
                     bary.y * grid[closest_hexes[1]].center.z +
                     bary.z * grid[closest_hexes[2]].center.z;
}

Vector3D Hexagon::GetBarycentricCords(int v_ind, const std::vector<int> near_hexes,
    const std::vector<Hexagon>& grid) {
    Vector3D bary;

    Vector3D a = grid[near_hexes[0]].center;
    Vector3D b = grid[near_hexes[1]].center;
    Vector3D c = grid[near_hexes[2]].center;
    Vector3D p = verts[v_ind];

    Vector3D ab = b - a, ac = c - a, ap = p - a;

    float area_abc = Triangle(a, b, c).GetArea();
    float area_pbc = Triangle(p, b, c).GetArea();
    float area_pca = Triangle(p, c, a).GetArea();

    bary.x = area_pbc / area_abc;
    bary.y = area_pca / area_abc;
    bary.z = 1.0f - bary.x - bary.y;

    return bary;
}

// num - ind of a point in verts of hexagon
std::vector<int> Hexagon::GetNearHexes(int v_ind, const std::vector<Hexagon>& grid) {

    std::multimap<float, int> distances;
    for (int i = 0; i < grid.size(); ++i) {
        Vector3D rad = grid[i].GetSpecVert(6) - verts[v_ind];
        distances.insert({ rad.GetLen(), i });
    }

    const int kMaxNearHexes = 3;

    std::vector<int> near_hexes_inds(kMaxNearHexes);
    auto it_distances = distances.begin();
    for (int i = 0; i < kMaxNearHexes; ++i) {
        near_hexes_inds[i] = it_distances->second;
        it_distances++;
    }

    return near_hexes_inds;
}