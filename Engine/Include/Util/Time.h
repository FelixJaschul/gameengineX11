#pragma once

#include <chrono>

namespace Engine::Util
{
    class Time
    {
        public:
        Time();
        ~Time() = default;

        void Update();

        [[nodiscard]] double GetDeltaSeconds() const { return m_deltaSeconds; }
        [[nodiscard]] double GetElapsedSeconds() const;
        [[nodiscard]] double GetFPS() const { return m_fps; }

        private:
        using m_clock = std::chrono::steady_clock;
        m_clock::time_point m_start;
        m_clock::time_point m_prev;
        double m_deltaSeconds;
        double m_fps;
        Time* s_current;
    };
}
