#include <Rendering/Block.h>
#include <Rendering/Renderer.h>

namespace Engine::Rendering
{
    Block::Block(Math::Vec::iVec2 position, int width, int height, unsigned long color)
        : m_position(position), m_width(width), m_height(height), m_color(color)
    {
    }

    void Block::Update()
    {
        // Future: Add block logic here (animations, state changes, etc.)
    }

    void Block::Render(Renderer* renderer) const
    {
        if (!renderer) return;
        renderer->DrawRect(m_position.x, m_position.y, m_width, m_height, m_color);
    }

    bool Block::ContainsPoint(int x, int y) const
    {
        return x >= m_position.x && x <= m_position.x + m_width &&
               y >= m_position.y && y <= m_position.y + m_height;
    }

    bool Block::IsPlayerAbove(Math::Vec::iVec2 playerPos, int playerWidth) const
    {
        int playerLeft = playerPos.x;
        int playerRight = playerPos.x + playerWidth;

        // Check horizontal overlap
        return playerRight > m_position.x && playerLeft < m_position.x + m_width;
    }

}