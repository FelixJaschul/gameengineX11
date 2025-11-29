#include <Util/Time.h>

namespace Engine::Util
{
    Time::Time()
        : m_start(m_clock::now()), m_prev(m_start), m_deltaSeconds(0.0), s_current(nullptr)
    {
    }

    void Time::Update()
    {
        auto now = m_clock::now();
        m_deltaSeconds = std::chrono::duration<double>(now - m_prev).count();
        m_prev = now;
    }

    double Time::GetElapsedSeconds() const
    {
        return std::chrono::duration<double>(m_clock::now() - m_start).count();
    }
}
