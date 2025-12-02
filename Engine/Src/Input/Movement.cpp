#include <Input/Movement.h>
#include <Rendering/Camera.h>
#include <Rendering/Block.h>
#include <Config.h>

namespace Engine::Input
{
    Movement::Movement(Engine::Rendering::Camera* camera)
        : m_speed(Engine::GetMovementSpeed()), m_jumpHeight(Engine::GetMovementJumpHeight()), m_camera(camera), m_blocks(nullptr)
    {
    }

    void Movement::Down()
    {
        if (Engine::GetGroundCheck()) return;
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
            m_camera->GetJump(-m_jumpHeight);
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