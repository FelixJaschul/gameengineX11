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
        return static_cast<float>(h & 0xFFFFFFu) / 16777216.0f;
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

    void World::Generate() const
    {
        const int tile   = Engine::GetPlayerHeight(), width  = 200, height = 60;
        constexpr int seed = 1337, baseY = 10, amp = 6, dirtDepth = 3;

        for (int x = 0; x < width; ++x)
        {
            const float n = fbm1D(x * 0.07f, seed);

            const int surfaceY = std::clamp(baseY + static_cast<int>(std::round((n - 0.5f) * 2.0f * amp)), 2, height - 4);

            for (int y = surfaceY; y < height; ++y)
            {
                const uint32_t color = (y == surfaceY) ? 0x2E7D32FF : (y <= surfaceY + dirtDepth) ? 0x6D4C41FF : 0x424242FF;

                m_blocks.push_back(
                    new Engine::Rendering::Block(
                        { x * tile, y * tile },
                        tile,
                        tile,
                        false,
                        color
                    )
                );
            }
        }
    }
}
