#include <Rendering/Camera.h>
#include <Util/Time.h>
#include <App/App.h>
#include <algorithm>
#include <Config.h>

namespace Engine::Rendering
{
    Camera::Camera(Engine::Util::Time* time, std::vector<Block*>& blocks)
        : m_position({0, 0}), m_time(time), m_velocityY(0.0), m_air(false)
        , m_blocks(blocks)
    {
    }

    Math::Vec::iVec2 Camera::Move(int dx, int dy)
    {
        m_position.x += dx;
        m_position.y += dy;
        return m_position;
    }

    const Block *Camera::GetBlockBeneath() const
    {
        for (const auto* block : m_blocks)
        {
            // Only consider blocks horizontally under the player
            if (block->IsPlayerAbove(m_position, Engine::appPlayerHeight))
            {
                // Block must be below or slightly overlapping the player's bottom
                if (block->GetGroundHeight() >= m_position.y + Engine::appPlayerHeight &&
                    block->GetGroundHeight() <  std::numeric_limits<int>::max())
                {
                    return block;
                }
            }
        }
        return nullptr; // crash game if no block
    }

    Math::Vec::iVec2 Camera::Jump(int dx, int dy)
    {
        m_position.x += dx;

        if (!Engine::appEnableGroundCheck)
        {
            m_position.y += dy;
            return m_position;
        }

        // IF GROUND CHECK IS ENABLED ::::: DO THIS ALL
        Engine::appCurrentGroundHeight = GetBlockBeneath()->GetGroundHeight();

        if (!m_air && dy < 0) // Jump
        {
            m_air = true;
            m_velocityY = static_cast<double>(dy);
        }

        const double dt = std::max(0.0, m_time->GetDeltaSeconds());
        m_velocityY += appGravityValue * dt; // Math bla bla
        double newY = static_cast<double>(m_position.y) + m_velocityY * dt;

        // Snap to ground
        if (newY + Engine::appPlayerHeight >= Engine::appCurrentGroundHeight)
        {
            newY = Engine::appCurrentGroundHeight - Engine::appPlayerHeight;
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

    bool Camera::GetJump(int dy)
    {
        if (!Engine::appEnableGroundCheck) return false;

        if (!m_air &&
            m_position.y + Engine::appPlayerHeight >= GetBlockBeneath()->GetGroundHeight() &&
            dy < 0)
        {
            m_air = true;
            m_velocityY = static_cast<double>(dy);
            return true;
        }

        return false;
    }
}
