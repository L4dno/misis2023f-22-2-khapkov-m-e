//#include "mesh_generator.hpp"
#include <iostream>
#include <cmath>

#include "point.hpp"


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
//#define DOCTEST_CONFIG_DISABLE
#include <doctest/doctest.h>

TEST_CASE("triangle init") {
    Triangle f();
    Triangle s({ 1,2 }, { 3,4 }, { 1,4 });
    CHECK(s.GetSpecVert(2).x == 1);
}

TEST_CASE("triangle split test") {
    Triangle t({ 1,2 }, { 3,4 }, { 1,4 });
    auto new_triangles = t.split();
    CHECK(new_triangles[2].GetSpecVert(0) == Vertex{ 1, 4 });
    CHECK(new_triangles[2].GetSpecVert(1) == Vertex{ 1, 2 });
    CHECK(new_triangles[2].GetSpecVert(2) == Vertex{ 5.0f/3.0f, 10.0f/3.0f });
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
    CHECK(HexParts[5].GetSpecVert(2) == Vertex{ 0,0 });
}

TEST_CASE("hexagon division test") {
    Hexagon h({ 0,0 }, 10);
    auto mesh = h.GetMeshData();
    CHECK(mesh.size() == NumOfTrianglePatches * NumOfTrianglePatches * 
                            NumOfHexPatches * TriangleVertsCount);
}

//TEST_CASE("hexagon z change") {
//    Hexagon h{ {0,0}, 5 };
//    h.SetZToSpecVert(2, 3);
//    CHECK(h.GetSpecVert(2).z == 3);
//}

TEST_CASE("clamping test") {
    CHECK(Clamp(1.5) == 1.0f);
    CHECK(Clamp(-2) == 0.0f);
    CHECK(Clamp(0.8) == 0.8f);
}



TEST_CASE("smoothstep test") {
    //std::cout << "\n" << SmoothStep(0, 1, 0.29) << "\n";
    CHECK(Compare(SmoothStep(0, 1, 0.5), 0.5f));
    auto tmp = SmoothStep(0, 1, 0.29);
    CHECK(Compare(tmp, 0.2035f));
}

TEST_CASE("initting grid test") {
    std::vector<Hexagon> grid;
    InitGrid(grid);
    PrintHex(grid[0]);
}

TEST_CASE("nearest hexes in grid") {
    std::vector<Hexagon> grid;
    InitGrid(grid);
    Vertex zero = { 0,0 };
    auto hex_indexes = GetNearestHexesToPoint(grid, zero);
    CHECK(hex_indexes[0] == 0);
    CHECK(hex_indexes[1] == 2);
    CHECK(hex_indexes[2] == 3);
}

TEST_CASE("hexagon interpolation test") {
    std::vector<Hexagon> grid;
    InitGrid(grid);
    for (auto& hex : grid) {
        hex.SetLevel(HexLevels::kFirst);
    }
    grid[3].InterpolateVerts(grid);
    for (int i = 0; i < HexVertsCount; ++i) {
        CHECK(Compare(grid[3].GetSpecVert(i).z, 5.0f));
    }
}