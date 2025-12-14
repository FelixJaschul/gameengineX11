#pragma once

#include <Math/Vec.h>
#include <Rendering/Renderer.h>

namespace Engine::Rendering
{
    class Block
    {
        public:
        Block(Math::Vec::iVec2 position, int width, int height, bool walkthrough, unsigned long color);
        ~Block() = default;

        void Update();
        void Render(Engine::Rendering::Renderer* renderer) const;

        // Getters
        [[nodiscard]] Math::Vec::iVec2 GetPosition() const { return m_position; }
        [[nodiscard]] int GetWidth() const { return m_width; }
        [[nodiscard]] int GetHeight() const { return m_height; }
        [[nodiscard]] int GetGroundHeight() const { return m_position.y; }
        [[nodiscard]] unsigned long GetColor() const { return m_color; }
        [[nodiscard]] bool IsWalkthrough() const { return m_walkthrough; }

        // Check if a point is within this block's bounds
        [[nodiscard]] bool ContainsPoint(int x, int y) const;
        [[nodiscard]] bool IsPlayerAbove(Math::Vec::iVec2 playerPos) const;

        private:
        Math::Vec::iVec2 m_position;
        int m_width;
        int m_height;
        bool m_walkthrough;
        unsigned long m_color;
    };
}
