//#include "earcut.hpp"
#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <array>
#include <exception>
#include <cmath>

#include <raylib.h>

//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_DISABLE
#include <doctest/doctest.h>



#define NumOfHexPatches 6
#define NumOfTrianglePatches 4

struct Vertex {
    float x = 0;
    float y = 0;
    bool operator==(Vertex rhs) const{
        return x == rhs.x && y == rhs.y;
    }
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
    Vertex GetSpecVert(int number) {
        if (number < 0 || number >= core.size())
            throw std::invalid_argument("not a vertex number");
        return core[number];
    }
    // func returns cords of 4 smaller fractial triangles
    std::array<Triangle, NumOfTrianglePatches> split() {
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
};

class Hexagon {
private:
    Vertex center = { 0,0 };
    float radius = 0;
public:
    Hexagon() = default;
    ~Hexagon() = default;
    Hexagon(Vertex c, float rad) {
        center = c;
        radius = rad;
    }
    // returns cords of vertex number i, calculated
    Vertex GetSpecVert(int i) {
        if (i < 0 || i >= 6)
            throw std::invalid_argument("not a vertex number");
         float angle_rad = i / 6.0 * 2 * M_PI;
         return Vertex{ center.x + radius * std::cos(angle_rad),
                        center.y + radius * std::sin(angle_rad) };
    }
    std::array<Triangle, NumOfHexPatches> split() {
        std::array<Triangle, NumOfHexPatches> res;
        for (int i = 0; i < NumOfHexPatches; ++i) {
            res[i] = Triangle(GetSpecVert(i),
                              GetSpecVert((i + 1) % NumOfHexPatches),
                              center);
        }
        return res;
    }

    // from hex or triangle get simple enum of vertexes
    std::vector<Vertex> GetMeshData() {
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
};

Mesh TranslateMesh(std::vector<Vertex> tmp) {
    Mesh mesh = { 0 };
    mesh.triangleCount = tmp.size()/3;
    mesh.vertexCount = tmp.size();
    mesh.vertices = (float*)MemAlloc(mesh.vertexCount * 3 * sizeof(float));
    
    for (int i = 0; i < tmp.size();++i) {
        mesh.vertices[i*3] = tmp[i].x;
        mesh.vertices[i*3+1] = tmp[i].y;
        mesh.vertices[i*3+2] = 0;
    }

    return mesh;
    
    //mesh.texcoords = (float*)MemAlloc(mesh.vertexCount * 2 * sizeof(float));
    //mesh.normals = (float*)MemAlloc(mesh.vertexCount * 3 * sizeof(float));

    //mesh.vertices[0] = 0;
    //mesh.vertices[1] = 0;
    //mesh.vertices[2] = 0;
    ///* mesh.normals[0] = 0;
    // mesh.normals[1] = 1;
    // mesh.normals[2] = 0;*/
    //mesh.texcoords[0] = 0;
    //mesh.texcoords[1] = 0;
}


TEST_CASE("triangle init") {
    Triangle f();
    Triangle s({1,2}, {3,4}, {1,4});
    CHECK(s.GetSpecVert(2).x == 1);
}

TEST_CASE("triangle split test") {
    Triangle t({ 1,2 }, { 3,4 }, { 1,4 });
    auto new_triangles = t.split();
    CHECK(new_triangles[0].GetSpecVert(0) == Vertex{1, 2});
    CHECK(new_triangles[0].GetSpecVert(1) == Vertex{2, 3});
    CHECK(new_triangles[0].GetSpecVert(2) == Vertex{1, 3});
}

void PrintHex(Hexagon h) {
    std::cout << "HEXAGON\n";
    for (int i = 0; i < NumOfHexPatches; ++i) {
        std::cout << "x: " << h.GetSpecVert(i).x << " "
                  << "y: " << h.GetSpecVert(i).y << "\n";
    }
    std::cout << "END\n";
}

TEST_CASE("hexagon verts location test + hex construction") {
    Hexagon g({ 0,0 }, 1);
    PrintHex(g);
}

TEST_CASE("hexagon split test") {
    Hexagon g({ 0,0 }, 1);
    auto HexParts = g.split();
    CHECK(HexParts[5].GetSpecVert(1) == Vertex{1,0});
}

TEST_CASE("hexagon division test") {
    Hexagon h({ 0,0 }, 10);
    auto mesh = h.GetMeshData();
    CHECK(mesh.size() == 288);
}

void ShowMesh(Mesh m) {
    const int screenWidth = 1080;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "mesh generator");

    Camera camera = { {5.0f, 5.0f,5.0f}, {0.0f,0.0f, 0.0f},
        {0.0f,1.0f,0.0f},45.0f,CAMERA_PERSPECTIVE };

    Vector3 position = { 0.0f, 0.0f, 0.0f };

    Model ter = LoadModelFromMesh(m);
    //ter.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;


    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();

        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        // drawing 3d shapes
        DrawModel(ter, position, 1.0f, WHITE);
        //DrawModel(tr., position, 2.0f, WHITE);
        DrawGrid(10, 1.0);
        DrawLine3D({ 0,0,0 }, { 0,5.0f,0.0f }, GOLD);
        DrawLine3D({ 0,0,0 }, { 5.0f,0.0f,0.0f }, LIME);
        DrawLine3D({ 0,0,0 }, { 0,0.0f,5.0f }, RED);
        //DrawPoint3D({ 5.0f,5.0f,5.0f }, PURPLE);

        EndMode3D();

        EndDrawing();
    }
    UnloadModel(ter);
}

int main() {
    Hexagon g({ 0,0 }, 10);
    auto mesh = g.GetMeshData();
    ShowMesh(TranslateMesh(mesh));
    return 0;
}


