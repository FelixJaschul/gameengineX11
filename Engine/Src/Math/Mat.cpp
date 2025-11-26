#include <Math/Mat.h>

namespace Math::Mat4
{
    inline Mat4 Identity()
    {
        Mat4 r{};
        r.m[0] = r.m[5] = r.m[10] = r.m[15] = 1.0f;
        return r;
    }

    inline Mat4 Multiply(const Mat4& a, const Mat4& b)
    {
        Mat4 r{};
        for (int col = 0; col < 4; col++)
        {
            for (int row = 0; row < 4; row++)
            {
                r.m[col*4 + row] =
                    a.m[0*4 + row] * b.m[col*4 + 0] +
                    a.m[1*4 + row] * b.m[col*4 + 1] +
                    a.m[2*4 + row] * b.m[col*4 + 2] +
                    a.m[3*4 + row] * b.m[col*4 + 3];
            }
        }
        return r;
    }

    inline Mat4 Translation(const Math::Vec::Vec3& v)
    {
        Mat4 r = Identity();
        r.m[12] = v.x;
        r.m[13] = v.y;
        r.m[14] = v.z;
        return r;
    }

    inline Mat4 RotationX(float angleDeg)
    {
        float a = angleDeg * (3.1415926f/180.0f);
        float c = cosf(a);
        float s = sinf(a);

        Mat4 r = Identity();
        r.m[5] =  c;
        r.m[6] =  s;
        r.m[9] = -s;
        r.m[10] = c;
        return r;
    }

    inline Mat4 RotationY(float angleDeg)
    {
        float a = angleDeg * (3.1415926f/180.0f);
        float c = cosf(a);
        float s = sinf(a);

        Mat4 r = Identity();
        r.m[0] = c;
        r.m[2] = -s;
        r.m[8] = s;
        r.m[10] = c;
        return r;
    }

    inline Mat4 RotationZ(float angleDeg)
    {
        float a = angleDeg * (3.1415926f/180.0f);
        float c = cosf(a);
        float s = sinf(a);

        Mat4 r = Identity();
        r.m[0] =  c;
        r.m[1] =  s;
        r.m[4] = -s;
        r.m[5] =  c;
        return r;
    }

    inline Mat4 Perspective(float fovDeg, float aspect, float nearZ, float farZ)
    {
        float fovRad = fovDeg * (3.1415926f/180.0f);
        float f = 1.0f / tanf(fovRad * 0.5f);

        Mat4 r{};
        r.m[0] = f / aspect;
        r.m[5] = f;
        r.m[10] = (farZ + nearZ) / (nearZ - farZ);
        r.m[11] = -1.0f;
        r.m[14] = (2 * farZ * nearZ) / (nearZ - farZ);
        return r;
    }

    inline Mat4 LookAt(const Math::Vec::Vec3& eye, const Math::Vec::Vec3& target, const Math::Vec::Vec3& up)
    {
        Math::Vec::Vec3 f = Normalize(Subtract(target, eye));
        Math::Vec::Vec3 r = Math::Vec::Normalize(Math::Vec::Cross(f, up));
        Math::Vec::Vec3 u = Math::Vec::Cross(r, f);

        Mat4 m = Identity();

        m.m[0] = r.x;   m.m[4] = r.y;   m.m[8]  = r.z;
        m.m[1] = u.x;   m.m[5] = u.y;   m.m[9]  = u.z;
        m.m[2] = -f.x;  m.m[6] = -f.y;  m.m[10] = -f.z;

        Mat4 t = Translation({ -eye.x, -eye.y, -eye.z });

        return Multiply(m, t);
    }
}