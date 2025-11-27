#pragma once

#include <cstdint>

namespace Engine::Input
{
    // Common keyboard keys (extend as needed)
    enum class Key : uint16_t
    {
        Unknown = 0,

        // Control keys
        Escape,
        Space,
        Enter,
        Tab,
        Backspace,

        // Arrows
        Left,
        Right,
        Up,
        Down,

        // Letters
        A, B, C, D, E, F, G, H, I, J,
        K, L, M, N, O, P, Q, R, S, T,
        U, V, W, X, Y, Z,

        // Digits
        Num0, Num1, Num2, Num3, Num4,
        Num5, Num6, Num7, Num8, Num9,

        // Modifiers
        LeftShift, RightShift,
        LeftControl, RightControl,
        LeftAlt, RightAlt,
        LeftSuper, RightSuper,

        COUNT
    };

    void UpdateFrame();

    // Engine-internal: feed key events from the platform layer
    void SetKey(Key key, bool down);

    bool IsKeyDown(Key key);
    bool IsKeyPressed(Key key);
    bool IsKeyReleased(Key key);
}
