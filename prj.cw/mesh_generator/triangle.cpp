#include <stdexcept>

#include "include/mesh_generator/triangle.hpp"

Triangle::Triangle(Vector3D a, Vector3D b, Vector3D c) {
    // check on non colinear???
    verts.resize(kNumVerts);
    tex_cords.resize(kNumVerts);

    if (isCcwOrder(a, b, c)) {
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

bool Triangle::isCcwOrder(Vector3D a, Vector3D b, Vector3D c) const {
    Vector3D ab = b - a;
    Vector3D ac = c - a;
    return ab.Skew(ac) > 0;
}

Vector3D Triangle::GetSpecVert(int num) const{
    if (num < 0 || num >= kNumVerts)
        throw std::invalid_argument("not a vertex number");
    return verts[num];
}

void Triangle::SetVertZ(int num, float z) {
    if (num < 0 || num >= kNumVerts)
        throw std::invalid_argument("not a vertex number");
    verts[num].z = z;
}

float Triangle::GetArea() const {
    Vector3D ab = verts[1] - verts[0];
    Vector3D ac = verts[2] - verts[0];
    return ab.Skew(ac) / 2.0f;
}

std::vector<Triangle> Triangle::Split() const {
    Vector3D a = verts[0];
    Vector3D b = verts[1];
    Vector3D c = verts[2];

    Vector3D mid{
        (a.x + b.x + c.x) / 3.0f,
        (a.y + b.y + c.y) / 3.0f,
        (a.z + b.z + c.z) / 3.0f
    };
    return {
        Triangle(a,b,mid),
        Triangle(b,c,mid),
        Triangle(c,a,mid),
    };
}

void Triangle::SetVertTexCords(int v, Vector3D uv) {
    if (v < 0 || v >= kNumVerts)
        throw std::invalid_argument("not a vertex number");
    tex_cords[v] = uv;
}