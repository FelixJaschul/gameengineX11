#pragma once
#include "Math/Vec.h"

namespace Engine::Input
{
    class Movement
    {
        public:
        explicit Movement();
        ~Movement() = default;

        void Right();
        void Left();

        void Up();
        void Down();

        private:
        [[nodiscard]] bool GroundCheck() const;

        Math::Vec::iVec2 current_position{};
        int m_speed;
        int m_ground;
    };
}
