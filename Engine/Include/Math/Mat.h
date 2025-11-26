#pragma once

#include <Math/Vec.h>

namespace Math::Mat4
{
    typedef struct { float m[16]; } Mat4;

    Mat4 Identity();

    Mat4 Multiply(const Mat4& a, const Mat4& b);
    Mat4 Translation(const Math::Vec::Vec3& v);

    Mat4 RotationX(float angleDeg);
    Mat4 RotationY(float angleDeg);
    Mat4 RotationZ(float angleDeg);

    Mat4 Perspective(float fovDeg, float aspect, float nearZ, float farZ);
    Mat4 LookAt(const Math::Vec::Vec3& eye, const Math::Vec::Vec3& target, const Math::Vec::Vec3& up);
}