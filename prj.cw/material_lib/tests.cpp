#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "point.hpp"
#include "triangle.hpp"
#include "hexagon.hpp"

TEST_SUITE("vector math") {

    TEST_CASE("vector equality") {
        Vector3D lhs{ 1,2,3 };
        Vector3D rhs{ 1,2,3 };
        CHECK(lhs == rhs);
        rhs.z -= 1;
        CHECK(lhs != rhs);
    }

    TEST_CASE("vector difference") {
        Vector3D a{ 1,2,3 };
        Vector3D b{ 1,2,1 };
        Vector3D c{ 0,0,2 };
        CHECK(a - b == c);
    }

    TEST_CASE("cross product test") {
        Vector3D a{ 1,2,3 };
        Vector3D b{ 1,5,7 };
        Vector3D res = a.Cross(b);
        CHECK(res == Vector3D{ -1,-4,3 });
        res = b.Cross(a);
        CHECK(res == Vector3D{ 1,4,-3 });
    }

    TEST_CASE("dot product test") {
        Vector3D a{ 1,2,1 };
        Vector3D b{ 2,1,2 };
        CHECK(a.Dot(b) == 6);
        CHECK(b.Dot(a) == 6);
    }

    TEST_CASE("vector length test") {
        Vector3D a{ 3,0,4 };
        CHECK(a.GetLen() == 5);
    }

    TEST_CASE("vector normalization test") {
        Vector3D a{ 0,3,4 };
        Vector3D norm = a.GetNormalizedCords();
        CHECK(norm == Vector3D{ 0,0.6f, 0.8f });
    }

    TEST_CASE("pseudo scalar test") {
        Vector3D a{ 1,2,1 };
        Vector3D b{ 2,1,2 };
        CHECK(a.Skew(b) == -3);
        CHECK(b.Skew(a) == 3);
    }

}

TEST_SUITE("triangle operations") {

    TEST_CASE("triangle construct") {
        Vector3D a{ 1,2,0 }, b{ 3,4,0 }, c{ 1,4,0 };
        Triangle abc(a, b, c);
        Triangle acb(a, c, b);
        for (int i = 0; i < 3; ++i) {
            CHECK(abc.GetSpecVert(i) == acb.GetSpecVert(i));
        }
    }

    TEST_CASE("triangle z setting") {
        Vector3D a{ 1,2,0 }, b{ 3,4,0 }, c{ 1,4,0 };
        Triangle t(a, b, c);
        t.SetSpecVertZ(0, 5);
        CHECK(t.GetSpecVert(0).z == 5);
        CHECK(t.GetSpecVert(1).z != 5);
        CHECK(t.GetSpecVert(2).z != 5);
    }

    TEST_CASE("triangle area calculation") {
        Vector3D a{ 1,2,0 }, b{ 3,4,0 }, c{ 1,4,0 };
        Triangle t(a, b, c);
        CHECK(FloatCompare(t.GetArea(), 2.0f));
    }

    TEST_CASE("triangle splitting") {
        Triangle t({ 1,2 }, { 3,4 }, { 1,4 });
        auto new_triangles = t.Split();
        CHECK(new_triangles[2].GetSpecVert(0) == Vector3D{ 1, 4 });
        CHECK(new_triangles[2].GetSpecVert(1) == Vector3D{ 1, 2 });
        CHECK(new_triangles[2].GetSpecVert(2) == Vector3D{ 5.0f / 3.0f, 10.0f / 3.0f });
    }

}

TEST_SUITE("hexagon operations") {

    TEST_CASE("hexagon construction") {
        Hexagon h(Vector3D{}, 3.0f);
        CHECK(h.GetSpecVert(2) == Vector3D{0, 3.0f, 3.0f});
        CHECK(h.GetSpecVert(5) == Vector3D{0, -3.0f, 3.0f });
        CHECK(h.GetSpecVert(6) == Vector3D{0, 0.0f, 3.0f });
    }

    TEST_CASE("hexagon interpolation all flat") {
        std::vector<Hexagon> grid;

        const float HEX_RADIUS = 5.0f;

        const float cell_height = 2.0f * HEX_RADIUS;
        const float cell_width = std::sqrt(3) * HEX_RADIUS;

        grid.push_back(Hexagon({ cell_width, cell_height / 2.0f }, HEX_RADIUS));
        grid.push_back(Hexagon({ cell_width * 2.0f, cell_height / 2.0f }, HEX_RADIUS));
        grid.push_back(Hexagon({ cell_width / 2.0f, cell_height / 4.0f * 5.0f }, HEX_RADIUS));
        grid.push_back(Hexagon({ cell_width / 2.0f * 3.0f, cell_height / 4.0f * 5.0f }, HEX_RADIUS));
        grid.push_back(Hexagon({ cell_width / 2.0f * 5.0f, cell_height / 4.0f * 5.0f }, HEX_RADIUS));
        grid.push_back(Hexagon({ cell_width, cell_height * 2.0f }, HEX_RADIUS));
        grid.push_back(Hexagon({ cell_width * 2.0f, cell_height * 2.0f }, HEX_RADIUS));

        for (int i = 0; i < grid.size(); ++i) {
            grid[i].SetLevel(HexLevels::kFirst);
        }

        for (int i = 0;i < grid.size();++i) {
            grid[i].RecalculateEdges(grid);
            for (int j = 0; j < 6; ++j) {
                CHECK(FloatCompare(grid[i].GetSpecVert(j).z, 5.0f));
            }
        }
    }

    TEST_CASE("hexagon interpolation mid up") {
        std::vector<Hexagon> grid;

        const float HEX_RADIUS = 5.0f;

        const float cell_height = 2.0f * HEX_RADIUS;
        const float cell_width = std::sqrt(3) * HEX_RADIUS;

        grid.push_back(Hexagon({ cell_width, cell_height / 2.0f }, HEX_RADIUS));
        grid.push_back(Hexagon({ cell_width * 2.0f, cell_height / 2.0f }, HEX_RADIUS));
        grid.push_back(Hexagon({ cell_width / 2.0f, cell_height / 4.0f * 5.0f }, HEX_RADIUS));
        grid.push_back(Hexagon({ cell_width / 2.0f * 3.0f, cell_height / 4.0f * 5.0f }, HEX_RADIUS));
        grid.push_back(Hexagon({ cell_width / 2.0f * 5.0f, cell_height / 4.0f * 5.0f }, HEX_RADIUS));
        grid.push_back(Hexagon({ cell_width, cell_height * 2.0f }, HEX_RADIUS));
        grid.push_back(Hexagon({ cell_width * 2.0f, cell_height * 2.0f }, HEX_RADIUS));

        for (int i = 0; i < grid.size(); ++i) {
            grid[i].SetLevel(HexLevels::kFirst);
        }
        grid[3].SetLevel(HexLevels::kThird);
        for (int i = 0;i<grid.size();++i) {
            grid[i].RecalculateEdges(grid);
        }

        for (int i = 0; i < 6; ++i) {
            CHECK(FloatCompare(grid[3].GetSpecVert(i).z, 25.0f/3.0f));
        }
    }

}
