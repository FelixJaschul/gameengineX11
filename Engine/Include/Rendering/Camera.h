#pragma once

#include <Math/Vec.h>

namespace Engine::Rendering
{
    class Camera
    {
        public:
        static Camera& Instance();

        void Move(int dx, int dy);
        void SetPosition(int x, int y);

        [[nodiscard]] Math::Vec::iVec2 GetPosition() const { return m_position; };

        private:
        Camera() = default;
        ~Camera() = default;

        Math::Vec::iVec2 m_position{0, 0};
    };
}
