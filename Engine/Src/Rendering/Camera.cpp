#include <Rendering/Camera.h>
#include <Util/Time.h>
#include <App/App.h>
#include <algorithm>
#include <Config.h>

namespace Engine::Rendering
{
    Camera::Camera(Engine::Util::Time* time, const std::vector<Rendering::Block*>& blocks)
        : m_position({0, 0}), m_time(time), m_velocityY(0.0), m_air(false), m_blocks(blocks)
    {
    }

    // Helper: resolve horizontal collisions against non-walkthrough blocks.
    // Returns corrected nextX based on overlap at nextY and movement direction dx.
    int Camera::ResolveHorizontalCollision(int nextX, const int nextY, const int dx) const
    {
        if (dx == 0) return nextX;

        for (const auto* Block : m_blocks)
        {
            if (!Block || Block->IsWalkthrough()) continue;

            const int  bRight  = Block->GetPosition().x + Block->GetWidth();
            const int  bBottom = Block->GetPosition().y + Block->GetHeight();

            if (const bool verticalOverlap = (nextY + Engine::GetPlayerHeight() > Block->GetPosition().y) &&
                (nextY < bBottom); !verticalOverlap) continue;

            if (dx > 0)
            {
                if (nextX + Engine::GetPlayerHeight() > Block->GetPosition().x &&
                    m_position.x + Engine::GetPlayerHeight() <= Block->GetPosition().x)
                    nextX = Block->GetPosition().x - Engine::GetPlayerHeight();
            }
            else
            {
                if (nextX < bRight && m_position.x >= bRight) nextX = bRight;
            }
        }

        return nextX;
    }

    Math::Vec::iVec2 Camera::Move(const int dx, const int dy)
    {
        // Simple move if ground check is disabled (no collisions)
        if (!Engine::GetGroundCheck())
        {
            m_position.x += dx;
            m_position.y += dy;
            return m_position;
        }

        // IF GROUND CHECK IS ENABLED ::::: apply horizontal collision against non-walkthrough blocks
        m_position.x = ResolveHorizontalCollision(m_position.x + dx, m_position.y + dy, dx);
        m_position.y = m_position.y + dy;
        return m_position;
    }

    const Block *Camera::GetBlockBeneath() const
    {
        for (const auto* block : m_blocks)
        {
            // Only consider blocks horizontally under the player
            if (block->IsPlayerAbove(m_position))
            {
                // Block must be below or slightly overlapping the player's bottom
                if (block->GetGroundHeight() >= m_position.y + Engine::GetPlayerHeight() &&
                    block->GetGroundHeight() <  std::numeric_limits<int>::max()) return block;
            }
        }
        return nullptr; // crash game if no block
    }

    Math::Vec::iVec2 Camera::Jump(const int dx, const int dy)
    {
        m_position.x += dx;

        if (!Engine::GetGroundCheck())
        {
            m_position.y += dy;
            return m_position;
        }

        // IF GROUND CHECK IS ENABLED ::::: DO THIS ALL

        if (!m_air && dy < 0) // Jump
        {
            m_air = true;
            m_velocityY = static_cast<double>(dy);
        }

        const double dt = std::max(0.0, m_time->GetDeltaSeconds());
        m_velocityY += Engine::GetGravityValue() * dt; // Math bla bla
        double newY = static_cast<double>(m_position.y) + m_velocityY * dt;

        // Snap to ground
        if (newY + Engine::GetPlayerHeight() >= Engine::GetCurrentGroundHeight())
        {
            newY = Engine::GetCurrentGroundHeight() - Engine::GetPlayerHeight();
            m_velocityY = 0.0;
            m_air = false;
        }
        else
        {
            m_air = true;
        }

        m_position.y = static_cast<int>(newY);

        return m_position;
    }

    bool Camera::GetJump(const int dy)
    {
        if (!Engine::GetGroundCheck()) return false;
        if (!Engine::Rendering::Camera::GetBlockBeneath()) m_position.y = Engine::GetCurrentGroundHeight() - Engine::GetPlayerHeight();

        if (!m_air &&
            m_position.y + Engine::GetPlayerHeight() >= Engine::Rendering::Camera::GetBlockBeneath()->GetGroundHeight() &&
            dy < 0)
        {
            m_air = true;
            m_velocityY = static_cast<double>(dy);
            return true;
        }

        return false;
    }

    Math::Vec::iVec2 Camera::WorldToScreen(Math::Vec::iVec2 worldPos) const
    {
        return {
            worldPos.x - m_position.x + Engine::Window::GetDefaultWindowX() / 2,
            worldPos.y - m_position.y + Engine::Window::GetDefaultWindowY() / 2
        };
    }

}
