#include "include/mesh_generator/grid.hpp"

#include <iostream>
#include <map>

Grid::Grid(float rad) : kRadius(rad) {
    Init();
    SetLevels();
    InterpolateZ();
    InitTextureCords();
}

void Grid::Init() {

    grid.push_back(Hexagon({ kCellWidth, kCellHeight / 2.0f }, kRadius));
    grid.push_back(Hexagon({ kCellWidth * 2.0f, kCellHeight / 2.0f }, kRadius));
    grid.push_back(Hexagon({ kCellWidth / 2.0f, kCellHeight / 4.0f * 5.0f }, kRadius));
    grid.push_back(Hexagon({ kCellWidth / 2.0f * 3.0f, kCellHeight / 4.0f * 5.0f }, kRadius));
    grid.push_back(Hexagon({ kCellWidth / 2.0f * 5.0f, kCellHeight / 4.0f * 5.0f }, kRadius));
    grid.push_back(Hexagon({ kCellWidth, kCellHeight * 2.0f }, kRadius));
    grid.push_back(Hexagon({ kCellWidth * 2.0f, kCellHeight * 2.0f }, kRadius));

}

void Grid::SetLevels() {
    grid_levels.resize(Size());
    for (int i = 0; i < Size(); ++i) {
        grid_levels[i] = HexLevels::kFirst;
    }
    grid_levels[3] = HexLevels::kThird;
    grid_levels[5] = HexLevels::kFifth;
    for (int i = 0; i < Size(); ++i) {
        grid[i].SetSpecVertZ(6, static_cast<int>(grid_levels[i]) * kRadius);
    }
}

void Grid::InterpolateZ() {
    for (int i = 0; i < Size(); ++i) {
        for (int j = 0; j < 6; ++j) {
            Vector3D cur_p = grid[i].GetSpecVert(j);
            Vector3D near = GetHexesNearPoint(cur_p);
            Vector3D bary = GetBarycentricCords(near, cur_p);
            float new_z =
                bary.x * grid[near.x].GetSpecVert(6).z + 
                bary.y* grid[near.y].GetSpecVert(6).z + 
                bary.z* grid[near.z].GetSpecVert(6).z;
            grid[i].SetSpecVertZ(j, new_z);
        }
    }
}

Hexagon Grid::GetHex(const int ind) const {
    if (ind < 0 || ind > grid.size())
        throw std::invalid_argument("not a hex number");
    return grid[ind];
}

int Grid::Size() const {
    return grid.size();
}

Vector3D Grid::GetHexesNearPoint(const Vector3D point) const {
    std::multimap<float, int> distances;
    for (int i = 0; i < Size(); ++i) {
        Vector3D rad = grid[i].GetSpecVert(6) - point;
        rad.z = 0; // 2D projection
        distances.insert({ rad.GetLen(), i });
    }

    auto dist_it = distances.begin();
    Vector3D near_inds;

    near_inds.x = dist_it->second;
    near_inds.y = (++dist_it)->second;
    near_inds.z = (++(dist_it))->second;

    return near_inds;
}

Vector3D Grid::GetBarycentricCords(const Vector3D close_hexes, const Vector3D p) const {
    Vector3D bary;

    Vector3D a = grid[close_hexes.x].GetSpecVert(6);
    Vector3D b = grid[close_hexes.y].GetSpecVert(6);
    Vector3D c = grid[close_hexes.z].GetSpecVert(6);

    float area_abc = Triangle(a, b, c).GetArea();
    float area_pbc = Triangle(p, b, c).GetArea();
    float area_pca = Triangle(p, c, a).GetArea();

    bary.x = area_pbc / area_abc;
    bary.y = area_pca / area_abc;
    bary.z = 1.0f - bary.x - bary.y;

    return bary;
}

void Grid::InitTextureCords() {
    grid_uv.reserve(grid.size());
    for (int i = 0; i < grid.size();++i) {
        grid_uv.push_back(Hexagon({ 0.5f,0.5f }, 0.1f));
    }
}

std::vector<Vector3D> Grid::GetHexMesh(int ind) const {
    std::vector<Vector3D> out;
    out.reserve(6 * 3 * 3 * 3);

    auto trigs = grid[ind].Split();
        for (int i = 0; i < 6; ++i) {
            auto first_div = trigs[i].Split();
            for (int j = 0; j < 3; ++j) {
                auto second_div = first_div[j].Split();
                for (int k = 0; k < 3; ++k) {
                    for (int r = 0; r < 3; ++r) {
                        out.push_back(second_div[k].GetSpecVert(r));
                    }
                }
            }
        }

    return out;
}

std::vector<Vector3D> Grid::GetHexUV(int ind) const {
    std::vector<Vector3D> out;
    out.reserve(6 * 3 * 3 * 3);

    auto trigs = grid_uv[ind].Split();
    for (int i = 0; i < 6; ++i) {
        auto first_div = trigs[i].Split();
        for (int j = 0; j < 3; ++j) {
            auto second_div = first_div[j].Split();
            for (int k = 0; k < 3; ++k) {
                for (int r = 0; r < 3; ++r) {
                    out.push_back(second_div[k].GetSpecVert(r));
                }
            }
        }
    }

    return out;
}