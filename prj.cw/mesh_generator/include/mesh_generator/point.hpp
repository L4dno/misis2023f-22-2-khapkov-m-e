#pragma once
#ifndef POINT_06012024
#define POINT_06012024

bool FloatCompare(float lhs, float rhs);

// somehow we should maintein CCW order
struct Vector3D {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    // also need a function to compare floats
    bool operator==(Vector3D rhs) const;
    Vector3D operator-(Vector3D rhs) const;
    // distance we can get as a len of a new vector
    // float GetDistanceToPoint(Vector3D rhs);
    Vector3D Cross(Vector3D rhs) const;
    float Dot(Vector3D rhs) const;
    float GetLen() const;
    Vector3D GetNormalizedCords() const;
    float Skew(Vector3D rhs) const;
};

//float SmoothStep(float edge0, float edge1, float x);
//float Clamp(float x, float lower_limit = 0.0f, float upper_limit = 1.0f);
//float InterpolateValue(float u, float v, float w, float val1, float val2, float val3);

#endif