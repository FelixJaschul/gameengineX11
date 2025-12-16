#include <Math/Vec.h>

namespace Math::Vec
{
    Vec3 operator+(const Vec3& a, const Vec3& b)
    {
        return { a.x + b.x, a.y + b.y, a.z + b.z };
    }

    Vec3 operator-(const Vec3& a, const Vec3& b)
    {
        return { a.x - b.x, a.y - b.y, a.z - b.z };
    }

    Vec3 operator*(const Vec3& v, float s)
    {
        return { v.x * s, v.y * s, v.z * s };
    }

    float Dot(const Vec3& a, const Vec3& b)
    {
        return a.x*b.x + a.y*b.y + a.z*b.z;
    }

    Vec3 Cross(const Vec3& a, const Vec3& b)
    {
        return {
            a.y*b.z - a.z*b.y,
            a.z*b.x - a.x*b.z,
            a.x*b.y - a.y*b.x
        };
    }

    Vec3 Normalize(const Vec3& v)
    {
        float len = std::sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
        if (len == 0.0f) return {0,0,0};
        return { v.x/len, v.y/len, v.z/len };
    }
}
