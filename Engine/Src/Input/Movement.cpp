#include <Input/Movement.h>
#include <Rendering/Camera.h>
#include <Config.h>

namespace Engine::Input
{
    Movement::Movement(Engine::Rendering::Camera* camera, Engine::Util::Time* time)
        : m_speed(Engine::GetMovementSpeed()), m_camera(camera), m_time(time), m_blocks(nullptr)
    {
    }

    void Movement::Down()
    {
        if (Engine::GetGroundCheck()) return;
        current_position = m_camera->Move(0, static_cast<int>(m_speed * m_time->GetDeltaSeconds() * Engine::Window::GetDesiredFPS()));
    }

    void Movement::Up()
    {
        if (!Engine::GetGroundCheck())
        {
            current_position = m_camera->Move(0, static_cast<int>(-m_speed * m_time->GetDeltaSeconds() * Engine::Window::GetDesiredFPS()));
        }
        else
        {
            m_camera->GetJump(-Engine::GetMovementJumpHeight());
            current_position = m_camera->GetPosition();
        }
    }

    void Movement::Right()
    {
        current_position = m_camera->Move(static_cast<int>(m_speed * m_time->GetDeltaSeconds() * Engine::Window::GetDesiredFPS()), 0);
    }

    void Movement::Left()
    {
        current_position = m_camera->Move(static_cast<int>(-m_speed * m_time->GetDeltaSeconds() * Engine::Window::GetDesiredFPS()), 0);
    }
}