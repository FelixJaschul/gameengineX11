#pragma once

#include <cmath>

namespace Math::Vec
{
    typedef struct { float x, y; } Vec2;
    typedef struct { float x, y, z; } Vec3;

    typedef struct { int x, y; } iVec2;
    typedef struct { int x, y, z; } iVec3;

    Vec3 operator+(const Vec3& a, const Vec3& b);
    Vec3 operator-(const Vec3& a, const Vec3& b);
    Vec3 operator*(const Vec3& v, float s);

    float Dot(const Vec3& a, const Vec3& b);
    Vec3 Cross(const Vec3& a, const Vec3& b);
    Vec3 Normalize(const Vec3& v);
}
