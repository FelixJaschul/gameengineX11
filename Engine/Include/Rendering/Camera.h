#pragma once

#include <Rendering/Window.h>
#include <Math/Vec.h>
#include <Math/Mat.h>

namespace Engine::Rendering
{
    class Camera
    {
        public:
        explicit Camera(Window* window,
                        Math::Vec::Vec3 position  = Math::Vec::Vec3{0.0f, 0.0f, 0.0f},
                        Math::Vec::Vec3 direction = Math::Vec::Vec3{30, -90.0f, 0},
                        float fov = 70.0f);

        Camera(Window* window, float posX, float posY, float posZ, float roll, float pitch, float yaw, float fov = 70.0f);

        Math::Vec::Vec3 Front();
        Math::Vec::Vec3 Right();
        Math::Vec::Vec3 Up();

        Math::Mat4::Mat4 GetViewMatrix();
        Math::Mat4::Mat4 GetProjectionMatrix();

        Math::Vec::Vec3 m_position{};
        Math::Vec::Vec3 m_direction{};
        float m_fov;

        private:
        Window* m_window{nullptr};
    };
}