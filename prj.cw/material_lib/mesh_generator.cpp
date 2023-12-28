#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <array>
#include <exception>
#include <cmath>

#include <raylib.h>
#include "mesh_generator.hpp"

bool Vertex::operator==(Vertex rhs) const {
    return x == rhs.x && y == rhs.y;
}

std::array<Triangle, NumOfTrianglePatches> Triangle::split() {
    Vertex mid1 = {
                    (core[0].x + core[1].x) / 2.0f,
                    (core[0].y + core[1].y) / 2.0f,
    };
    Vertex mid2 = {
                    (core[1].x + core[2].x) / 2.0f,
                    (core[1].y + core[2].y) / 2.0f,
    };
    Vertex mid3 = {
                    (core[2].x + core[0].x) / 2.0f,
                    (core[2].y + core[0].y) / 2.0f,
    };

    return {
            Triangle(core[0], mid1, mid3),
            Triangle(mid1, core[1], mid2),
            Triangle(mid2,core[2], mid3),
            Triangle(mid1,mid2,mid3),
    };
}

Vertex Triangle::GetSpecVert(int number) {
    if (number < 0 || number >= core.size())
        throw std::invalid_argument("not a vertex number");
    return core[number];
}

std::vector<Vertex> Hexagon::GetMeshData() {
    std::vector<Vertex> res;
    const int kVertCount = 3;
    auto hex_parts = split();
    for (int i = 0; i < NumOfHexPatches; ++i) {
        auto first_div = hex_parts[i].split();
        for (int j = 0; j < NumOfTrianglePatches; ++j) {
            auto second_div = first_div[j].split();
            for (int k = 0; k < NumOfTrianglePatches; ++k) {
                for (int r = 0; r < kVertCount; ++r) {
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
            GetSpecVert((i + 1) % NumOfHexPatches),
            center);
    }
    return res;
}

Vertex Hexagon::GetSpecVert(int i) {
    if (i < 0 || i >= 6)
        throw std::invalid_argument("not a vertex number");
    float angle_rad = i / 6.0 * 2 * M_PI;
    return Vertex{ center.x + radius * std::cos(angle_rad),
                   center.y + radius * std::sin(angle_rad) };
}






