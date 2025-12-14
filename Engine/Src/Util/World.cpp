#include <Util/World.h>
#include <cmath>

namespace Engine::Util
{
    // keep a simple global pointer similar to Config-style accessors
    static World* g_World = nullptr;

    World::World(std::vector<Rendering::Block*>& blocks)
        : m_blocks(blocks)
    {
        g_World = this;
    }

    // Simple integer hash -> [0,1)
    float World::hash01(int x, int seed)
    {
        uint32_t h = static_cast<uint32_t>(x) * 374761393u + static_cast<uint32_t>(seed) * 668265263u;
        h = (h ^ (h >> 13)) * 1274126177u;
        h ^= (h >> 16);
        return (h & 0xFFFFFFu) / 16777216.0f;
    }

    // 1D value noise with a couple of octaves (very cheap stand-in for Perlin)
    float World::fbm1D(float x, int seed)
    {
        float total = 0.0f;
        float amplitude = 1.0f;
        float frequency = 1.0f;
        float norm = 0.0f;
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
        const int tileSize = Engine::GetPlayerHeight();
        const int worldWidthBlocks = 200;
        const int worldHeightBlocks = 60;
        const int baseSurface = 10;
        const int surfaceAmplitude = 6;
        const unsigned long grassColor = 0x2E7D32FF;
        const unsigned long dirtColor  = 0x6D4C41FF;
        const unsigned long stoneColor = 0x424242FF;
        const int dirtDepth = 3;

        // Generate heightmap along X
        std::vector<int> surface(worldWidthBlocks);
        for (int x = 0; x < worldWidthBlocks; ++x)
        {
            constexpr int seed = 1337;
            const float n = fbm1D(static_cast<float>(x) * 0.07f, seed);
            int h = baseSurface + static_cast<int>(std::round((n - 0.5f) * 2.0f * surfaceAmplitude));
            h = std::max(2, std::min(h, worldHeightBlocks - 4));
            surface[x] = h;
        }

        for (int x = 0; x < worldWidthBlocks; ++x)
        {
            int surfaceY = surface[x];
            {
                Math::Vec::iVec2 pos{ x * tileSize, surfaceY * tileSize };
                m_blocks.push_back(new Engine::Rendering::Block(pos, tileSize, tileSize, false, grassColor));
            }

            for (int dy = 1; dy <= dirtDepth && (surfaceY + dy) < worldHeightBlocks; ++dy)
            {
                Math::Vec::iVec2 pos{ x * tileSize, (surfaceY + dy) * tileSize };
                m_blocks.push_back(new Engine::Rendering::Block(pos, tileSize, tileSize, false, dirtColor));
            }

            for (int y = surfaceY + dirtDepth + 1; y < worldHeightBlocks; ++y)
            {
                Math::Vec::iVec2 pos{ x * tileSize, y * tileSize };
                m_blocks.push_back(new Engine::Rendering::Block(pos, tileSize, tileSize, false, stoneColor));
            }
        }
    }

    World* GetWorld()
    {
        return g_World;
    }
}
