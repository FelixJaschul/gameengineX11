#pragma once

#include <Math/Vec.h>
#include <Util/Time.h>
#include <vector>

#include "Config.h"

namespace Engine::Rendering
{
    class Block;

    class Camera
    {
        public:
        explicit Camera(Engine::Util::Time* time, const std::vector<Rendering::Block*>&);
        ~Camera() = default;

        Math::Vec::iVec2 Move(int dx, int dy);
        Math::Vec::iVec2 Jump(int dx, int dy);

        bool GetJump(int dy);
        void SetPosition(Math::Vec::iVec2 position) { m_position = position; }

        [[nodiscard]] Math::Vec::iVec2 GetPosition() const { return m_position; }
        [[nodiscard]] const Block* GetBlockBeneath() const;
        [[nodiscard]] Math::Vec::iVec2 WorldToScreen(Math::Vec::iVec2 worldPos) const;

        private:
        [[nodiscard]] int ResolveHorizontalCollision(int nextX, int nextY, int dx) const;

        Math::Vec::iVec2 m_position;
        const std::vector<Block*>& m_blocks;
        Engine::Util::Time* m_time;
        double m_velocityY;
        bool m_air;
    };
}
