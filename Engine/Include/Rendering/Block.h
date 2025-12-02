#pragma once

#include <Math/Vec.h>

namespace Engine::Rendering
{
    class Renderer;

    class Block
    {
        public:
        Block(Math::Vec::iVec2 position, int width, int height, unsigned long color);
        ~Block() = default;

        void Update();
        void Render(Renderer* renderer) const;

        // Getters
        [[nodiscard]] Math::Vec::iVec2 GetPosition() const { return m_position; }
        [[nodiscard]] int GetWidth() const { return m_width; }
        [[nodiscard]] int GetHeight() const { return m_height; }
        [[nodiscard]] int GetGroundHeight() const { return m_position.y; }

        // Check if a point is within this block's bounds
        [[nodiscard]] bool ContainsPoint(int x, int y) const;
        [[nodiscard]] bool IsPlayerAbove(Math::Vec::iVec2 playerPos, int playerHeight) const;

        private:
        Math::Vec::iVec2 m_position;
        int m_width;
        int m_height;
        unsigned long m_color;
    };
}