#include <Util/Time.h>

namespace Engine::Util
{
    Time::Time()
        : m_start(m_clock::now()), m_prev(m_start), m_deltaSeconds(0.0), m_fps(0.0), s_current(nullptr)
    {
    }

    void Time::Update()
    {
        m_deltaSeconds = std::chrono::duration<double>(m_clock::now() - m_prev).count();
        m_prev = m_clock::now();

        if (m_deltaSeconds > 0.0) m_fps = m_fps * 0.9 + (1.0 / m_deltaSeconds) * 0.1;
    }

    double Time::GetElapsedSeconds() const
    {
        return std::chrono::duration<double>(m_clock::now() - m_start).count();
    }
}
