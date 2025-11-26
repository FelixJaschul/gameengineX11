#pragma once

#include <cmath>

namespace Math::Vec
{
    typedef struct { float x, y; } Vec2;
    typedef struct { float x, y, z; } Vec3;

    typedef struct { int x, y; } iVec2;
    typedef struct { int x, y, z; } iVec3;

    inline Vec3 operator+(const Vec3& a, const Vec3& b);
    inline Vec3 operator-(const Vec3& a, const Vec3& b);
    inline Vec3 operator*(const Vec3& v, float s);

    inline Vec3 Add(const Vec3& a, const Vec3& b);
    inline Vec3 Subtract(const Vec3& a, const Vec3& b);
    inline Vec3 Multiply(const Vec3& a, float s);
    inline float Dot(const Vec3& a, const Vec3& b);
    inline Vec3 Cross(const Vec3& a, const Vec3& b);
    inline Vec3 Normalize(const Vec3& v);
}
