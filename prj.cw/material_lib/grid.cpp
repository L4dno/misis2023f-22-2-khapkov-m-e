#include "grid.hpp"

#include <iostream>
#include <map>

Grid::Grid(float rad) : kRadius(rad) {
    Init();
    SetLevels();
    InterpolateZ();
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

//void Hexagon::SetLevel(HexLevels level) {
//    height_level = level;
//    center.z = static_cast<int>(height_level) * kRadius;
//    
//}

//void Hexagon::RecalculateEdges(const std::vector<Hexagon>& grid) {
//    for (int i = 0; i < kNumVerts; ++i) {
//        InterpolateVertZ(i, grid);
//    }
//}

//void Hexagon::InterpolateVertZ(int v_ind, const std::vector<Hexagon>& grid) {
//    std::vector<int> closest_hexes = GetNearHexes(v_ind, grid);
//    Vector3D bary = GetBarycentricCords(v_ind, closest_hexes, grid);
//    verts[v_ind].z = bary.x * grid[closest_hexes[0]].center.z +
//                     bary.y * grid[closest_hexes[1]].center.z +
//                     bary.z * grid[closest_hexes[2]].center.z;
//}