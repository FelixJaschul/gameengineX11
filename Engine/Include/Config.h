#pragma once

// Changeable
namespace Engine
{
    namespace Window
    {
        inline const char* appWindowTitle = "X11";
        inline int appDefaultWindowX = 800;
        inline int appDefaultWindowY = 600;

        inline const char* GetWindowTitle() { return Engine::Window::appWindowTitle; }
        inline int  GetDefaultWindowX() { return Engine::Window::appDefaultWindowX; }
        inline int  GetDefaultWindowY() { return Engine::Window::appDefaultWindowY; }

        inline void SetWindowTitle(const char* TITLE) { Engine::Window::appWindowTitle = TITLE; }
        inline void SetDefaultWindowX(int WIDTH) { Engine::Window::appDefaultWindowX = WIDTH; }
        inline void SetDefaultWindowY(int HEIGHT) { Engine::Window::appDefaultWindowY = HEIGHT; }
    }

    namespace Rendering
    {
        inline bool appWireframeMode = false;

        inline bool GetWireframeMode() { return Engine::Rendering::appWireframeMode; }

        inline void SetWireframeMode(bool MODE) { Engine::Rendering::appWireframeMode = MODE; }
    }

    inline int  appMovementSpeed = 10;
    inline int  appMovementJumpHeight = 700;
    inline int  appCurrentGroundHeight = 400;
    inline int  appPlayerHeight = 50;
    // random number that just seemed to work:: default value
    inline int  appGravityValue = 2000;
    inline bool appEnableGroundCheck = false;

    inline int  GetMovementSpeed() { return Engine::appMovementSpeed; }
    inline int  GetMovementJumpHeight() { return Engine::appMovementJumpHeight; }
    inline int  GetCurrentGroundHeight() { return Engine::appCurrentGroundHeight; }
    inline int  GetPlayerHeight() { return Engine::appPlayerHeight; }
    inline int  GetGravityValue() { return Engine::appGravityValue; }
    inline bool GetGroundCheck() { return Engine::appEnableGroundCheck; }

    inline void SetMovementSpeed(int SPEED) { Engine::appMovementSpeed = SPEED; }
    inline void SetMovementJumpHeight(int JUMP) { Engine::appMovementJumpHeight = JUMP; }
    inline void SetCurrentGroundHeight(int HEIGHT) { Engine::appCurrentGroundHeight = HEIGHT; }
    inline void SetPlayerHeight(int HEIGHT) { Engine::appPlayerHeight = HEIGHT; }
    inline void setGravityValue(int value) { Engine::appGravityValue = value; }
    inline void SetGroundCheck(bool MODE) { Engine::appEnableGroundCheck = MODE; }
}