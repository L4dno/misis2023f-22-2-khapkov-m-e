#ifndef HEXAGON_06012024
#define HEXAGON_06012024

#include "point.hpp"
#include "triangle.hpp"

enum class HexLevels {
    kFirst = 1,
    kSecond = 2,
    kThird = 3,
    kFourth = 4,
    kFifth = 5,
    kSixth = 6,
};

class Hexagon {
private:

    const int kNumVerts = 6;
    const int KNumPatches = 6;
    Vector3D center = {};
    HexLevels height_level = HexLevels::kFirst;
    float radius = 0.0f;
    std::vector<Vector3D> verts;
    void InterpolateVertZ(int v_ind, const std::vector<Hexagon>& grid);
    // return indexes of a three closest hexes in grid to a point
    std::vector<int> GetNearHexes(int v_ind, const std::vector<Hexagon>& grid);
    Vector3D GetBarycentricCords(int v_ind, const std::vector<int> near_hexes,
                                            const std::vector<Hexagon>& grid);

public:

    Hexagon() = default;
    ~Hexagon() = default;
    // pointly top rotation
    Hexagon(Vector3D c, float rad);

    // need method for setting level
    // with recalculating of a z value for verts
    void SetLevel(HexLevels level);
    void RecalculateEdges(const std::vector<Hexagon>& grid);
            
    // returns vertex number num
    // 6 will return center
    Vector3D GetSpecVert(int num) const;
    std::vector<Triangle> Split() const;

    // from hex or triangle get simple enum of vertexes
    // interesting how to recalculate mesh
    //std::vector<Vector3D> GetMeshData() const;
};
#endif 