#include <Util/World.h>
#include <cmath>

namespace Engine::Util
{
    World::World(std::vector<Rendering::Block*>& blocks)
        : m_blocks(blocks)
    {
    }

    float World::hash01(const int x, const int seed)
    {
        uint32_t h = static_cast<uint32_t>(x) * 374761393u + static_cast<uint32_t>(seed) * 668265263u;
        h = (h ^ (h >> 13)) * 1274126177u;
        h ^= (h >> 16);
        return (h & 0xFFFFFFu) / 16777216.0f;
    }

    float World::fbm1D(const float x, const int seed)
    {
        float total = 0.0f, amplitude = 1.0f, frequency = 1.0f, norm = 0.0f;

        for (int i = 0; i < 4; ++i)
        {
            int xi = static_cast<int>(std::floor(x * frequency));
            float t = x * frequency - static_cast<float>(xi);
            float a = hash01(xi, seed);
            float b = hash01(xi + 1, seed);
            float v = a + (b - a) * t; // linear interp
            total += v * amplitude;
            norm  += amplitude;
            amplitude *= 0.5f;
            frequency *= 2.0f;
        }
        return total / std::max(0.0001f, norm); // [0,1]
    }

    void World::Generate()
    {
        const int tileSize = Engine::GetPlayerHeight(), worldWidthBlocks = 200, worldHeightBlocks = 60;

        // Generate heightmap along X
        std::vector<int> surface(worldWidthBlocks);
        for (int x = 0; x < worldWidthBlocks; ++x)
        {
            constexpr int surfaceAmplitude = 6, baseSurface = 10;
            constexpr int seed = 1337;
            const float n = fbm1D(static_cast<float>(x) * 0.07f, seed);
            int h = baseSurface + static_cast<int>(std::round((n - 0.5f) * 2.0f * surfaceAmplitude));
            h = std::max(2, std::min(h, worldHeightBlocks - 4));
            surface[x] = h;
        }

        for (int x = 0; x < worldWidthBlocks; ++x)
        {
            constexpr int dirtDepth = 3;
            const int surfaceY = surface[x];
            {
                const Math::Vec::iVec2 pos{ x * tileSize, surfaceY * tileSize };
                m_blocks.push_back(new Engine::Rendering::Block(pos, tileSize, tileSize, false, 0x2E7D32FF));
            }

            for (int dy = 1; dy <= dirtDepth && (surfaceY + dy) < worldHeightBlocks; ++dy)
            {
                const Math::Vec::iVec2 pos{ x * tileSize, (surfaceY + dy) * tileSize };
                m_blocks.push_back(new Engine::Rendering::Block(pos, tileSize, tileSize, false, 0x6D4C41FF));
            }

            for (int y = surfaceY + dirtDepth + 1; y < worldHeightBlocks; ++y)
            {
                const Math::Vec::iVec2 pos{ x * tileSize, y * tileSize };
                m_blocks.push_back(new Engine::Rendering::Block(pos, tileSize, tileSize, false, 0x424242FF));
            }
        }
    }
}
