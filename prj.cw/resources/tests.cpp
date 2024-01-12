#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "point.hpp"
#include "triangle.hpp"
#include "hexagon.hpp"
#include "grid.hpp"

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
        t.SetVertZ(0, 5);
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
        CHECK(h.GetSpecVert(2) == Vector3D{0, 3.0f});
        CHECK(h.GetSpecVert(5) == Vector3D{0, -3.0f});
        CHECK(h.GetSpecVert(6) == Vector3D{ 0, 0.0f });
    }

    TEST_CASE("hexagon z setting") {
        Hexagon h(Vector3D{}, 3.0f);
        h.SetSpecVertZ(0, 5);
        CHECK(FloatCompare(h.GetSpecVert(0).z, 5.0f));
        CHECK(FloatCompare(h.GetSpecVert(1).z, 0.0f));
    }

    TEST_CASE("hexagon splitting") {
        Hexagon h(Vector3D{}, 3.0f);
        auto trigs = h.Split();
        CHECK(trigs[0].GetSpecVert(0) == h.GetSpecVert(0));
        CHECK(trigs[0].GetSpecVert(1) == h.GetSpecVert(1));
        CHECK(trigs[0].GetSpecVert(2) == h.GetSpecVert(6));
    }

}

TEST_SUITE("grid testing") {
    
    TEST_CASE("grid construction in 2d") {
        Grid g(5.0f);
        std::vector<Vector3D> first_hex = { {12.9904, 2.5},
 {12.9904, 7.5},
 {8.66025, 10},
 {4.33013, 7.5},
 {4.33013, 2.5},
 {8.66025, 0} };
        for (int i = 0; i < 6; ++i) {
            bool good = FloatCompare(g.GetHex(0).GetSpecVert(i).x, first_hex[i].x) &&
                FloatCompare(g.GetHex(0).GetSpecVert(i).y, first_hex[i].y);
            CHECK(good);
        }
    }

    TEST_CASE("grid levels setting") {
        Grid g(5.0f);
        for (int i = 0; i < g.Size(); ++i) {
            if (i != 3)
                CHECK(FloatCompare(g.GetHex(i).GetSpecVert(6).z, 5.0f));
            else
                CHECK(FloatCompare(g.GetHex(i).GetSpecVert(6).z, 15.0f));
        }
    }

    TEST_CASE("search for near hexes") {
        Grid g(5.0f);
        Vector3D tmp = g.GetHex(0).GetSpecVert(0);
        CHECK(g.GetHexesNearPoint(tmp) == Vector3D{ 0,1,3 });
        tmp = g.GetHex(0).GetSpecVert(5);
        CHECK(g.GetHexesNearPoint(tmp) == Vector3D{ 0,1,2 });
    }

    TEST_CASE("barycentric calculations test") {
        Grid g(5.0f);
        Vector3D p = g.GetHex(3).GetSpecVert(2);
        CHECK(g.GetBarycentricCords(g.GetHexesNearPoint(p), p) == Vector3D{1.0f/3.0f,
                                1.0f / 3.0f ,
                                1.0f / 3.0f });
        p = g.GetHex(6).GetSpecVert(3);
        auto res = g.GetBarycentricCords(g.GetHexesNearPoint(p), p);
        std::cout << res.x << " " << res.y << " " << res.z;
    }

    TEST_CASE("barycentric interpolation test") {
        Grid g(5.0f);
        for (int i = 0; i < 6; ++i) {
            CHECK(FloatCompare(g.GetHex(3).GetSpecVert(i).z, 25.0f / 3.0f));
        }
    }

    TEST_CASE("getting mesh data") {
        Grid g(5.0f);
        auto tmp = g.GetHexMesh(0);
        CHECK(tmp.size() == 6 * 3 * 3 * 3);//last 3 is a centers??
    }

}
