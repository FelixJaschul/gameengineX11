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
    extern int appPlayerHeight;

    // random number that just seemed to work:: default value
    inline extern const int appGravityValue = 2000;
}