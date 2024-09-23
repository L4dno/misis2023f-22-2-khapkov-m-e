#include <cmath>

#include "include/mesh_generator/point.hpp"

bool FloatCompare(float lhs, float rhs) {
    const float eps = 1e-4;
    return std::abs(lhs - rhs) < eps;
}

bool Vector3D::operator==(Vector3D rhs) const {
    bool xs = FloatCompare(x, rhs.x);
    bool ys = FloatCompare(y, rhs.y);
    bool zs = FloatCompare(z, rhs.z);
    return xs && ys && zs;
}

Vector3D Vector3D::Cross(Vector3D rhs) const  {
    // which vector order should i use
    // i need positive area
    float res_x = y * rhs.z - z * rhs.y;
    float res_y = z * rhs.x - x * rhs.z;
    float res_z = x * rhs.y - y * rhs.x;
    return Vector3D{ res_x, res_y, res_z };
}

float Vector3D::Dot(Vector3D rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

Vector3D Vector3D::operator-(Vector3D rhs) const {
    float res_x = x - rhs.x;
    float res_y = y - rhs.y;
    float res_z = z - rhs.z;
    return Vector3D{ res_x, res_y, res_z };
}

float Vector3D::GetLen() const {
    return std::sqrt(x * x + y * y + z * z);
}

Vector3D Vector3D::GetNormalizedCords() const {
    float norm = GetLen();
    return Vector3D{ x / norm, y / norm, z / norm };
}

float Vector3D::Skew(Vector3D rhs) const {
    return x * rhs.y - y * rhs.x;
}