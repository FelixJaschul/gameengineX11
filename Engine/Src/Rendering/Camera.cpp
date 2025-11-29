#include <Rendering/Camera.h>

namespace Engine::Rendering
{
    Camera& Camera::Instance()
    {
        static Camera s_instance;
        return s_instance;
    }

    void Camera::Move(int dx, int dy)
    {
        m_position.x += dx;
        m_position.y += dy;
    }

    void Camera::SetPosition(int x, int y)
    {
        m_position.x = x;
        m_position.y = y;
    }
}
