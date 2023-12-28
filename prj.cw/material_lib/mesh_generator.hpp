#include <array>
#include <vector>

#define NumOfHexPatches 6
#define NumOfTrianglePatches 4

struct Vertex {
    float x = 0;
    float y = 0;
    bool operator==(Vertex rhs) const;
};

class Triangle {
private:
    std::array<Vertex, 3> core;
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

    // func returns cords of 4 smaller fractial triangles
    std::array<Triangle, NumOfTrianglePatches> split();
};

class Hexagon {
private:
    Vertex center = { 0,0 };
    float radius = 0;
public:
    Hexagon() = default;
    ~Hexagon() = default;
    Hexagon(Vertex c, float rad) : center(c), radius(rad) {}

    // returns cords of vertex number i, calculated
    Vertex GetSpecVert(int i);
    
    std::array<Triangle, NumOfHexPatches> split();

    // from hex or triangle get simple enum of vertexes
    std::vector<Vertex> GetMeshData();
};