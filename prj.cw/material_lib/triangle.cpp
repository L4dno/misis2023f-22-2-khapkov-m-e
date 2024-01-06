#include "triangle.hpp"

Triangle::Triangle(Vector3D a, Vector3D b, Vector3D c) {
    // check on non colinear???
    verts.resize(kNumVerts);
    if (isRightTriple(a, b, c)) {
        verts[0] = a;
        verts[1] = b;
        verts[2] = c;
    }
    else {
        verts[0] = a;
        verts[1] = c;
        verts[2] = b;
    }
}