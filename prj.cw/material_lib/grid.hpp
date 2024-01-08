#ifndef GRID_07012024
#define GRID_07012024

#include "point.hpp"
#include "hexagon.hpp"

#include <cmath>

enum class HexLevels {
    kFirst = 1,
    kSecond = 2,
    kThird = 3,
    kFourth = 4,
    kFifth = 5,
    kSixth = 6,
};

class Grid {
private:
    const float kRadius = 0.0f;
    const float kCellHeight = 2.0f * kRadius;
    const float kCellWidth = std::sqrt(3) * kRadius;

    std::vector<Hexagon> grid;
    std::vector<HexLevels> grid_levels;

    //void InterpolateVertZ(int v_ind, const std::vector<Hexagon>& grid

    // method to fill 2d grid
    void Init();
    // method to set high for hexes on 2d
    void SetLevels();
    // calculates verticies z of a hexes
    void InterpolateZ();

public:

    Grid() = delete;
    ~Grid() = default;
    Grid(float rad);

    int Size() const;
    

    // returns vector from three indexes of a closest hexes to a point
    Vector3D GetHexesNearPoint(const Vector3D point) const;
    // returns barycentric coords for a point relative to a three hexes 
    Vector3D GetBarycentricCords(const Vector3D close_hexes, const Vector3D point) const;

    Hexagon GetHex(const int ind) const;

    // need method for setting level
    // with recalculating of a z value for verts

    //void SetHexLevel(HexLevels level);
    //void RecalculateEdges(const std::vector<Hexagon>& grid);
    
    //std::vector<Vector3D> GetMeshData() const;
};

#endif