#include <Input/Movement.h>
#include <Rendering/Camera.h>

#include "Config.h"

namespace Engine::Input
{
    Movement::Movement()
        : m_speed(Engine::appMovementSpeed)
    {
    }

    void Movement::Down() const
    {
        Engine::Rendering::Camera::Instance().Move(0, m_speed);
    }

    void Movement::Up() const
    {
        Engine::Rendering::Camera::Instance().Move(0, -m_speed);
    }

    void Movement::Right() const
    {
        Engine::Rendering::Camera::Instance().Move(m_speed, 0);
    }

    void Movement::Left() const
    {
        Engine::Rendering::Camera::Instance().Move(-m_speed, 0);
    }


}
