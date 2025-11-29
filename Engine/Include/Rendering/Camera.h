#pragma once

#include <Math/Vec.h>

#include <Util/Time.h>

namespace Engine::Rendering
{
    class Camera
    {
        public:
        explicit Camera(Engine::Util::Time* time);
        ~Camera() = default;

        Math::Vec::iVec2 Move(int dx, int dy);
        Math::Vec::iVec2 Jump(int dx, int dy);

        bool GetJump(int dy);
        [[nodiscard]] Math::Vec::iVec2 GetPosition() const { return m_position; }
        void SetPosition(Math::Vec::iVec2 position) { m_position = position; }

        private:
        Math::Vec::iVec2 m_position;
        Engine::Util::Time* m_time;
        double m_velocityY;
        bool m_air;
        int m_groundHeight;
    };
}
