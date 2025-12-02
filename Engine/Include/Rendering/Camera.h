#pragma once

#include <Math/Vec.h>
#include <Util/Time.h>
#include <vector>

namespace Engine::Rendering
{
    class Block;

    class Camera
    {
        public:
        explicit Camera(Engine::Util::Time* time, std::vector<Block*>& blocks);
        ~Camera() = default;

        Math::Vec::iVec2 Move(int dx, int dy);
        Math::Vec::iVec2 Jump(int dx, int dy);

        bool GetJump(int dy);
        [[nodiscard]] Math::Vec::iVec2 GetPosition() const { return m_position; }
        void SetPosition(Math::Vec::iVec2 position) { m_position = position; }

        private:
        [[nodiscard]] int FindGroundHeight() const;

        Math::Vec::iVec2 m_position;
        const std::vector<Block*>& m_blocks;
        Engine::Util::Time* m_time;
        double m_velocityY;
        bool m_air;
    };
}