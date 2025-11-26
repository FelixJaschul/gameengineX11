#include <Rendering/Camera.h>
#include <Math/Math.h>

namespace Engine::Rendering
{
    Camera::Camera(Rendering::Window* window, Math::Vec::Vec3 position, Math::Vec::Vec3 direction, float fov)
        : m_window(window->GetWindow()), m_position(position), m_direction(direction), m_fov(fov)
    {

    }

    // constructor with scalar values
    Camera::Camera(Rendering::Window* window, float posX, float posY, float posZ, float roll, float pitch, float yaw, float fov)
        : m_window(window->GetWindow()), m_fov(fov)
    {
        m_position = Math::Vec::Vec3{posX, posY, posZ};
        m_direction = Math::Vec::Vec3{pitch, yaw, roll};
    }

    Math::Vec::Vec3 Camera::Front()
    {
        // calculate the new Front vector
        Math::Vec::Vec3 front;
        front.x = cos(Math::Radians(m_direction.y)) * cos(Math::Radians(m_direction.x));
        front.y = sin(Math::Radians(m_direction.x));
        front.z = sin(Math::Radians(m_direction.y)) * cos(Math::Radians(m_direction.x));
        return Math::Vec::Normalize(front);
    }

    Math::Vec::Vec3 Camera::Right()
    {
        return Math::Vec::Normalize(Math::Vec::Cross(Front(), Math::Vec::Vec3{0, 1, 0}));
    }

    Math::Vec::Vec3 Camera::Up()
    {
        return Math::Vec::Normalize(Math::Vec::Cross(Right(), Front()));
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    Math::Mat4::Mat4 Camera::GetViewMatrix()
    {
        return Math::Mat4::LookAt(m_position, m_position + Front(), Up());
    }

    Math::Mat4::Mat4 Camera::GetProjectionMatrix()
    {
        Math::Vec::iVec2 w = m_window.GetWindowSize();
        return Math::Mat4::Perspective(Math::Radians(m_fov), (float)w.x / (float)w.y, 0.1f, 1000.0f);
    }
}
