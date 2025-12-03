#pragma once
#include "Math/Vec.h"
#include <vector>

#include "Util/Time.h"

namespace Engine::Rendering
{
    class Camera;
    class Block;
}

namespace Engine::Input
{
    class Movement
    {
        public:
        explicit Movement(Engine::Rendering::Camera* camera, Engine::Util::Time* time);
        ~Movement() = default;

        void Right();
        void Left();
        void Up();
        void Down();

        void SetBlocks(const std::vector<Engine::Rendering::Block*>* blocks) { m_blocks = blocks; }

        private:
        Math::Vec::iVec2 current_position{};
        Engine::Rendering::Camera* m_camera{nullptr};
        Engine::Util::Time* m_time{nullptr};
        const std::vector<Engine::Rendering::Block*>* m_blocks{nullptr};

        int m_speed;
    };
}