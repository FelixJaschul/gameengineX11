#include <Rendering/Camera.h>

namespace Engine::Rendering
{
    Camera& Camera::Instance()
    {
        static Camera s_instance;
        return s_instance;
    }

    Math::Vec::iVec2 Camera::Move(int dx, int dy)
    {
        m_position.x += dx;
        m_position.y += dy;
        return m_position;
    }

    void Camera::SetPosition(int x, int y)
    {
        m_position.x = x;
        m_position.y = y;
    }
}
