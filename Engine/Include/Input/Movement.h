#pragma once
#include "Math/Vec.h"

namespace Engine::Rendering { class Camera; }

namespace Engine::Input
{
    class Movement
    {
        public:
        explicit Movement(Engine::Rendering::Camera* camera);
        ~Movement() = default;

        void Right();
        void Left();

        void Up();
        void Down();

        private:
        [[nodiscard]] bool GroundCheck() const;

        Math::Vec::iVec2 current_position{};
        Engine::Rendering::Camera* m_camera{nullptr};

        int m_speed;
        int m_jumpHeight;
        int m_ground;
    };
}
