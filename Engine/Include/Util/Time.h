#pragma once

#include <chrono>

namespace Engine::Util
{
    // Class-style time system (like Renderer/Window)
    class Time
    {
        public:
        Time();
        ~Time() = default;

        void Update();

        [[nodiscard]] double GetDeltaSeconds() const { return m_deltaSeconds; }
        [[nodiscard]] double GetElapsedSeconds() const;

        private:
        using m_clock = std::chrono::steady_clock;
        m_clock::time_point m_start;
        m_clock::time_point m_prev;
        double m_deltaSeconds;
    };

    void SetCurrent(Time* time);

    void Init();
    void Update();
    double GetDeltaSeconds();
    double GetElapsedSeconds();
}
