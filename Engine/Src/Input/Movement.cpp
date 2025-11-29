#include <Input/Movement.h>
#include <Rendering/Camera.h>

#include "Config.h"

namespace Engine::Input
{
    Movement::Movement()
        : m_speed(Engine::appMovementSpeed), m_ground(Engine::appCurrentGroundHeight)
    {
    }

    bool Movement::GroundCheck() const
    {
        if (current_position.y == m_ground) return true;
        return false;
    }


    void Movement::Down()
    {
        if (Movement::GroundCheck()) return;
        current_position = Engine::Rendering::Camera::Instance().Move(0, m_speed);
    }

    void Movement::Up()
    {
        current_position = Engine::Rendering::Camera::Instance().Move(0, -m_speed);
    }

    void Movement::Right()
    {
        current_position = Engine::Rendering::Camera::Instance().Move(m_speed, 0);
    }

    void Movement::Left()
    {
        current_position = Engine::Rendering::Camera::Instance().Move(-m_speed, 0);
    }


}
