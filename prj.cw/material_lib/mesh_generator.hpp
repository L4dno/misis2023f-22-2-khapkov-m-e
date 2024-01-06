#include <array>
#include <vector>

#define NumOfHexPatches 6
#define NumOfTrianglePatches 3

#define HexVertsCount 6
#define TriangleVertsCount 3

#define HEX_RADIUS 5.0f

enum class HexLevels {
    kFirst = 1,
    kSecond = 2,
    kThird = 3,
    kFourth = 4,
    kFifth = 5,
    kSixth = 6,
};

struct Vertex {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    bool operator==(Vertex rhs) const;
};

float GetDistanceBetweenPoints2D(Vertex a, Vertex b);

class Triangle {
private:
    std::array<Vertex, TriangleVertsCount> core;
public:
    Triangle() = default;
    ~Triangle() = default;

    // order a->b->c
    Triangle(Vertex a, Vertex b, Vertex c) {
        core[0] = a;
        core[1] = b;
        core[2] = c;
    }

    Vertex GetSpecVert(int number);

    

    // func returns cords of smaller fractial triangles
    std::array<Triangle, NumOfTrianglePatches> split();
};

class Hexagon {
private:
    Vertex center = {};
    float radius = 0.0f;
    std::array<Vertex, HexVertsCount> verts;
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

float SmoothStep(float edge0, float edge1, float x);
float Clamp(float x, float lower_limit = 0.0f, float upper_limit = 1.0f);

void InitGrid(std::vector<Hexagon>& grid);

std::array<int, 3> GetNearestHexesToPoint(std::vector<Hexagon>& grid, Vertex p);

float GetTriangleArea(Vertex a, Vertex b, Vertex c);

float InterpolateValue(float u, float v, float w, float val1, float val2, float val3);