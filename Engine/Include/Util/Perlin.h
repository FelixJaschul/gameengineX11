#pragma once
#include <vector>
#include <random>

namespace Engine::Util::Noise
{
    class Perlin
    {
        public:
        Perlin(unsigned int seed = 0)
        {
            m_permutation.resize(256);
            for (int i = 0; i < 256; i++)
                m_permutation[i] = i;

            std::mt19937 rng(seed);
            std::shuffle(m_permutation.begin(), m_permutation.end(), rng);

            m_p.resize(512);
            for (int i = 0; i < 256; i++)
            {
                m_p[i] = m_permutation[i];
                m_p[i + 256] = m_permutation[i];
            }
        }

        float Noise1D(float x) const
        {
            int xi = (int)x & 255;

            float xf = x - (int)x;
            float u = Fade(xf);

            int a = m_p[xi];
            int b = m_p[xi + 1];

            float g0 = Grad(a, xf);
            float g1 = Grad(b, xf - 1.0f);

            return Lerp(g0, g1, u);
        }

        float operator+(float x) const;

    private:
        std::vector<int> m_permutation;
        std::vector<int> m_p;

        static float Fade(float t)
        {
            return t * t * t * (t * (t * 6 - 15) + 10);
        }

        static float Lerp(float a, float b, float t)
        {
            return a + t * (b - a);
        }

        static float Grad(int hash, float x)
        {
            int h = hash & 15;
            float grad = 1.0f + float(h & 7);
            if (h & 8) grad = -grad;
            return grad * x;
        }
    };

}
