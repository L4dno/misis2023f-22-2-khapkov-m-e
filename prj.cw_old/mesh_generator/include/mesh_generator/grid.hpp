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
    const int kSize = 0;

    // may be write only configuration like 3x3, 4x4

    float max_x = 0;
    float max_y = 0;
    const float min_x = 0;
    const float min_y = 0;

    std::vector<Hexagon> grid;
    std::vector<HexLevels> grid_levels;
    std::vector<Hexagon> grid_uv;

    // method to fill 2d grid
    void Init(int);
    // method to set high for hexes on 2d
    void SetLevels();
    // calculates verticies z of a hexes
    void InterpolateZ();
    // set simple text cords
    // here we need to normalize them
    void InitTextureCords();

public:

    Grid() = delete;
    ~Grid() = default;
    Grid(int size, float rad);

    int Size() const;
    
    // returns vector from three indexes of a closest hexes to a point
    Vector3D GetHexesNearPoint(const Vector3D point) const;
    // returns barycentric coords for a point relative to a three hexes 
    Vector3D GetBarycentricCords(const Vector3D close_hexes, const Vector3D point) const;

    Hexagon GetHex(const int ind) const;
    Hexagon GetTextHex(const int ind) const;
    
    std::vector<Vector3D> GetHexMesh(int ind) const;
    std::vector<Vector3D> GetHexUV(int ind) const;

    std::vector<Vector3D> GetGridMesh() const;
    std::vector<Vector3D> GetGridUV() const;
    
};

#endif