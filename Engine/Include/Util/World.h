#pragma once

#include <vector>
#include <Rendering/Block.h>
#include <Config.h>

namespace Engine::Util
{
    class World
    {
        public:
        explicit World(std::vector<Rendering::Block*>& blocks);
        ~World() = default;

        void Generate();

        private:
        static float hash01(int x, int seed);
        static float fbm1D(float x, int seed);

        std::vector<Rendering::Block*>& m_blocks;
    };
}
