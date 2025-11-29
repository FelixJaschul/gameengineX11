#include <Input/Movement.h>
#include <Rendering/Camera.h>

#include "Config.h"

namespace Engine::Input
{
    Movement::Movement(Engine::Rendering::Camera* camera)
        : m_speed(Engine::appMovementSpeed), m_jumpHeight(Engine::appMovementJumpHeight), m_ground(Engine::appCurrentGroundHeight), m_camera(camera)
    {
    }

    bool Movement::GroundCheck() const
    {
        if (!Engine::appEnableGroundCheck) return false;

        int y = current_position.y;
        if (m_camera)
        {
            y = m_camera->GetPosition().y;
        }
        const int groundY = Engine::appCurrentGroundHeight - Engine::appPlayerHeight;
        return y >= groundY;
    }

    void Movement::Down()
    {
        if (Engine::appEnableGroundCheck) return;
        current_position = m_camera->Move(0, m_speed);
    }

    void Movement::Up()
    {
        if (!Engine::appEnableGroundCheck)
        {
            current_position = m_camera->Move(0, -m_speed);
        }
        else
        {
            m_camera->TryStartJump(-m_jumpHeight);
            current_position = m_camera->GetPosition();
        }
    }

    void Movement::Right()
    {
        current_position = m_camera->Move(m_speed, 0);
    }

    void Movement::Left()
    {
        current_position = m_camera->Move(-m_speed, 0);
    }


}
