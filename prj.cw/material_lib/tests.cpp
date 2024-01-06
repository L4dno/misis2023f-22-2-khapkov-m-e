#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "point.hpp"

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

    }

}
