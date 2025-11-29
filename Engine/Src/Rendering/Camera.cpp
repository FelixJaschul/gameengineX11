#include <Rendering/Camera.h>
#include <Util/Time.h>
#include <App/App.h>
#include <algorithm>
#include <Config.h>

namespace Engine::Rendering
{
    Camera::Camera(Engine::Util::Time* time)
        : m_position({0, 0}), m_time(time), m_velocityY(0.0), m_air(false),
        m_groundHeight(Engine::appCurrentGroundHeight)
    {
    }

    Math::Vec::iVec2 Camera::Move(int dx, int dy)
    {
        m_position.x += dx;
        m_position.y += dy;
        return m_position;
    }

    Math::Vec::iVec2 Camera::Jump(int dx, int dy)
    {
        m_position.x += dx;

        // Allow free vertical movement
        if (!Engine::appEnableGroundCheck)
        {
            m_position.y += dy;
            return m_position;
        }

        const double dt = std::max(0.0, m_time->GetDeltaSeconds());

        if (!m_air)
        {
            if (dy < 0)
            {
                m_air = true;
                m_velocityY = static_cast<double>(dy);
            }
            else
            {
                if (m_position.y < m_groundHeight)
                {
                    m_air = true; // start falling under gravity
                }
                else
                {
                    m_position.y = m_groundHeight;
                    return m_position;
                }
            }
        }

        m_velocityY += appGravityValue * dt;
        double newY = static_cast<double>(m_position.y) + m_velocityY * dt;

        if (newY >= m_groundHeight)
        {
            newY = m_groundHeight;
            m_velocityY = 0.0;
            m_air = false;
        }

        m_position.y = static_cast<int>(newY);
        return m_position;
    }

    bool Camera::GetJump(int dy)
    {
        if (!Engine::appEnableGroundCheck) return false;

        if (!m_air && m_position.y >= m_groundHeight)
        {
            if (dy < 0)
            {
                m_air = true;
                m_velocityY = static_cast<double>(dy);
                return true;
            }
        }
        return false;
    }
}
