#include <Input/Input.h>
#include <cstddef>
#include <array>

namespace Engine::Input
{
    static std::array<bool, static_cast<size_t>(Key::COUNT)> s_curr{};
    static std::array<bool, static_cast<size_t>(Key::COUNT)> s_prev{};

    void UpdateFrame()
    {
        s_prev = s_curr;
    }

    void SetKey(Key key, bool down)
    {
        auto idx = static_cast<size_t>(key);
        if (idx < s_curr.size()) s_curr[idx] = down;
    }

    bool IsKeyDown(Key key)
    {
        auto idx = static_cast<size_t>(key);
        return idx < s_curr.size() ? s_curr[idx] : false;
    }

    bool IsKeyPressed(Key key)
    {
        auto idx = static_cast<size_t>(key);
        return idx < s_curr.size() ? (s_curr[idx] && !s_prev[idx]) : false;
    }

    bool IsKeyReleased(Key key)
    {
        auto idx = static_cast<size_t>(key);
        return idx < s_curr.size() ? (!s_curr[idx] && s_prev[idx]) : false;
    }
}
