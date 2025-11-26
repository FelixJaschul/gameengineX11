#pragma once

#include <Math/Vec.h>

namespace Math::Mat4
{
    typedef struct { float m[16]; } Mat4;

    inline Mat4 Identity();

    inline Mat4 Multiply(const Mat4& a, const Mat4& b);
    inline Mat4 Translation(const Math::Vec::Vec3& v);

    inline Mat4 RotationX(float angleDeg);
    inline Mat4 RotationY(float angleDeg);
    inline Mat4 RotationZ(float angleDeg);

    inline Mat4 Perspective(float fovDeg, float aspect, float nearZ, float farZ);
    inline Mat4 LookAt(const Math::Vec::Vec3& eye, const Math::Vec::Vec3& target, const Math::Vec::Vec3& up);
}