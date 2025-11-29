#pragma once

// Changeable
namespace Engine
{
    namespace Window
    {
        extern const char* appWindowTitle;
        extern int appDefaultWindowX;
        extern int appDefaultWindowY;
    }

    namespace Rendering
    {
        extern bool appWireframeMode;
    }

    extern int appMovementSpeed;
    extern int appMovementJumpHeight;
    extern int appCurrentGroundHeight;
    extern bool appEnableGroundCheck;
    extern bool appEnableVelocity;
    extern int appPlayerHeight; // Height of the player/rect for ground collisions

    inline extern const int appGravityValue = 2000;
}