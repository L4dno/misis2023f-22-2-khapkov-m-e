#include "mesh_generator.hpp"
#include <iostream>

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
    CHECK(HexParts[5].GetSpecVert(1) == Vertex{ 1,0 });
}

TEST_CASE("hexagon division test") {
    Hexagon h({ 0,0 }, 10);
    auto mesh = h.GetMeshData();
    CHECK(mesh.size() == NumOfTrianglePatches * NumOfTrianglePatches * 
                            NumOfHexPatches * TriangleVertsCount);
}