#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <array>
#include <exception>
#include <cmath>
#include <algorithm>
#include <utility>

#include <raylib.h>
#include "mesh_generator.hpp"

Hexagon::Hexagon(Vertex c, float rad) : center(c), radius(rad) {
    for (int i = 0; i < HexVertsCount; ++i) {
        float angle_deg = 60 * i - 30;
        float angle_rad = M_PI / 180.0f * angle_deg;
        verts[i] = Vertex{ center.x + radius * std::cos(angle_rad),
                           center.y + radius * std::sin(angle_rad) };
    }
}

bool Vertex::operator==(Vertex rhs) const {
    return x == rhs.x && y == rhs.y;
}

std::array<Triangle, NumOfTrianglePatches> Triangle::split() {
    Vertex mid = {
                    (core[0].x + core[1].x + core[2].x) / 3.0f,
                    (core[0].y + core[1].y + core[2].y) / 3.0f,
    };

    return {
            Triangle(core[0], core[1], mid),
            Triangle(core[1], core[2], mid),
            Triangle(core[2], core[0], mid)
    };
}

Vertex Triangle::GetSpecVert(int number) {
    if (number < 0 || number >= core.size())
        throw std::invalid_argument("not a vertex number");
    return core[number];
}

std::vector<Vertex> Hexagon::GetMeshData() {
    std::vector<Vertex> res;
    
    auto hex_parts = split();
    for (int i = 0; i < NumOfHexPatches; ++i) {
        auto first_div = hex_parts[i].split();
        for (int j = 0; j < NumOfTrianglePatches; ++j) {
            auto second_div = first_div[j].split();
            for (int k = 0; k < NumOfTrianglePatches; ++k) {
                for (int r = 0; r < TriangleVertsCount; ++r) {
                    res.push_back(second_div[k].GetSpecVert(r));
                }
            }
        }
    }
    return res;
}

std::array<Triangle, NumOfHexPatches> Hexagon::split() {
    std::array<Triangle, NumOfHexPatches> res;
    for (int i = 0; i < NumOfHexPatches; ++i) {
        res[i] = Triangle(GetSpecVert(i),
            GetSpecVert((i + 1) % HexVertsCount),
            center);
    }
    return res;
}

Vertex Hexagon::GetSpecVert(int i) {
    if (i < 0 || i > 6)
        throw std::invalid_argument("not a vertex number");
    if (i == 6)
        return center;
    return verts[i];
}

//void Hexagon::SetZToSpecVert(int i, int z) {
//    if (i < 0 || i >= 6)
//        throw std::invalid_argument("not a vertex number");
//    /*if (i == 6) {
//        center.z = z;
//    }
//    else {
//        verts[i].z = z;
//    }*/
//    verts[i].z = z;
//}

float Clamp(float x, float lower_limit, float upper_limit) {
    if (x < lower_limit)
        return lower_limit;
    if (x > upper_limit)
        return upper_limit;
    return x;
}

float SmoothStep(float edge0, float edge1, float x) {
    x = Clamp((x - edge0) / (edge1 - edge0));
    return x * x * (3.0f - 2.0f * x);
}

void Hexagon::SetLevel(HexLevels level) {
    if (level < HexLevels::kFirst || HexLevels::kSixth < level)
        throw std::invalid_argument("wrong hex level");
    center.z = static_cast<int>(level) * HEX_RADIUS;
}

void InitGrid(std::vector<Hexagon>& grid) {

    const float cell_height = 2.0f * HEX_RADIUS;
    const float cell_width = std::sqrt(3) * HEX_RADIUS;

    grid.push_back(Hexagon({cell_width, cell_height/2.0f}, HEX_RADIUS));
    grid.push_back(Hexagon({cell_width * 2.0f, cell_height/2.0f}, HEX_RADIUS));
    grid.push_back(Hexagon({cell_width/2.0f, cell_height/4.0f*5.0f}, HEX_RADIUS));
    grid.push_back(Hexagon({cell_width/2.0f*3.0f, cell_height / 4.0f * 5.0f }, HEX_RADIUS));
    grid.push_back(Hexagon({cell_width/2.0f*5.0f, cell_height / 4.0f * 5.0f }, HEX_RADIUS));
    grid.push_back(Hexagon({cell_width, cell_height * 2.0f }, HEX_RADIUS));
    grid.push_back(Hexagon({cell_width * 2.0f, cell_height * 2.0f}, HEX_RADIUS));

}

float GetDistanceBetweenPoints2D(Vertex a, Vertex b) {
    return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

std::array<int, 3> GetNearestHexesToPoint(std::vector<Hexagon>& grid, Vertex p) {
    std::vector<std::pair<float, int>> distances(grid.size());
    for (int i = 0; i < grid.size(); ++i) {
        distances[i] = { GetDistanceBetweenPoints2D(p, grid[i].GetSpecVert(6)), i};
    }
    std::sort(distances.begin(), distances.end(), [](auto lhs, auto rhs) 
                                                    {return lhs.first < rhs.first; });
    std::array<int, 3> res;
    res[0] = distances[0].second;
    res[1] = distances[1].second;
    res[2] = distances[2].second;
    return res;
}

float InterpolateValue(float u, float v, float w, float val1, float val2, float val3) {
    return u * val1 + v * val2 + w * val3;
}

float GetTriangleArea(Vertex a, Vertex b, Vertex c) {
    Vertex ab = { b.x - a.x, b.y - a.y };
    Vertex ac = { c.x - a.x, c.y - a.y };
    return std::abs(ab.x * ac.x + ab.y * ac.y);
}

void Hexagon::InterpolateVerts(std::vector<Hexagon>& grid) {
    for (auto& vert : verts) {
        auto near_hexes = GetNearestHexesToPoint(grid, vert);
        float nearest_triangle_area = GetTriangleArea(grid[near_hexes[0]].center, 
                                                    grid[near_hexes[1]].center, 
                                                    grid[near_hexes[2]].center) / 2.0f;
        float u = GetTriangleArea(grid[near_hexes[0]].center,
                                grid[near_hexes[1]].center,
                                vert) / nearest_triangle_area;
        float v = GetTriangleArea(grid[near_hexes[0]].center,
            grid[near_hexes[2]].center,
            vert) / nearest_triangle_area;
        float w = 1 - u - v;
        if (w < 0) {
            w = 1 - std::abs(w);
        }
        if (v < 0) {
            v = 1 - std::abs(v);
        }
        if (u < 0) {
            u = 1 - std::abs(u);
        }
        vert.z = InterpolateValue(u, v, w, grid[near_hexes[0]].center.z, grid[near_hexes[1]].center.z,
            grid[near_hexes[2]].center.z);
    }
}




