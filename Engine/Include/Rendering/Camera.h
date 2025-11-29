#pragma once

#include <Math/Vec.h>

namespace Engine::Rendering
{
    class Camera
    {
        public:
        Camera();
        ~Camera() = default;

        Math::Vec::iVec2 Move(int dx, int dy);

        Math::Vec::iVec2 Jump(int dx, int dy);

        bool TryStartJump(int dy);


        [[nodiscard]] Math::Vec::iVec2 GetPosition() const { return m_position; }
        void SetPosition(Math::Vec::iVec2 position) { m_position = position; }

        private:
        Math::Vec::iVec2 m_position{0, 0};

        double m_velocityY{0.0};
        bool m_air{false};

        int m_groundHeight;
    };
}
