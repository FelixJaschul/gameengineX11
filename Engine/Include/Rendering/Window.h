#pragma once

#include <X11/Xlib.h>
#include <string>

#include <Math/Vec.h>

// Do this forward declaration here because otherwise the terminal screams at you
namespace Engine
{
    extern const char* appWindowTitle;
    extern int appDefaultWindowX;
    extern int appDefaultWindowY;
}

namespace Engine::Rendering
{
    class Window
    {
        public:
        Window();
        ~Window();

        bool Init(int width, int height, const std::string& title);

        bool PollEvents();

        void Clear();

        void SwapBuffers();

        [[nodiscard]] Display* GetDisplay() const { return m_display; }
        [[nodiscard]] ::Window GetWindow()  const { return m_window;  }

        static Math::Vec::iVec2 GetWindowSize() { return Math::Vec::iVec2{Engine::appDefaultWindowX, Engine::appDefaultWindowY}; }

        private:
        void Cleanup();

        private:
        Display* m_display;
        ::Window m_window;
        int m_screen;
        Atom m_wmDeleteMessage;
        bool m_isRunning;
    };

}
