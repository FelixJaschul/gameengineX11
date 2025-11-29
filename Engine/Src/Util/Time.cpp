#include <Util/Time.h>

namespace Engine::Util
{
    Time::Time()
        : m_start(m_clock::now()), m_prev(m_start), m_deltaSeconds(0.0)
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

    static Time* s_current = nullptr;

    void SetCurrent(Time* time)
    {
        s_current = time;
    }

    void Update()
    {
        if (s_current)
        {
            s_current->Update();
        }
    }

    double GetDeltaSeconds()
    {
        return s_current ? s_current->GetDeltaSeconds() : 0.0;
    }

    double GetElapsedSeconds()
    {
        return s_current ? s_current->GetElapsedSeconds() : 0.0;
    }
}
