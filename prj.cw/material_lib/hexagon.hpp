#ifndef HEXAGON_06012024
#define HEXAGON_06012024

#define HEX_RADIUS 5.0f

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
    float radius = 0.0f;
    std::vector<Vector3D> verts;
public:
    Hexagon() = default;
    ~Hexagon() = default;
    // pointly top rotation
    Hexagon(Vertex c, float rad);

    // returns vertex number i
    // 6 will return center
    Vertex GetSpecVert(int i);

    //void SetZToSpecVert(int i, int z);
    std::array<Triangle, NumOfHexPatches> split();

    // from hex or triangle get simple enum of vertexes
    std::vector<Vertex> GetMeshData();

    void SetLevel(HexLevels level);
    // method for calculating z value for all 6 verts
    void InterpolateVerts(std::vector<Hexagon>& grid);
};
#endif 