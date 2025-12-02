#pragma once

#include <X11/Xlib.h>
#include <string>

#include <Math/Vec.h>
#include <Config.h>

namespace Engine::Rendering
{
    class Window
    {
        public:
        Window();
        ~Window();

        bool PollEvents();

        void Clear();

        void SwapBuffers();

        [[nodiscard]] Display* GetDisplay() const { return m_display; }
        [[nodiscard]] ::Window GetWindow()  const { return m_window;  }

        static Math::Vec::iVec2 GetWindowSize() { return Math::Vec::iVec2{Engine::Window::GetDefaultWindowX(), Engine::Window::GetDefaultWindowY()}; }

        private:
        void Cleanup();

        private:
        Display* m_display;
        ::Window m_window;
        const char* m_title;
        int m_screen;
        Atom m_wmDeleteMessage;
        bool m_isRunning;
    };

}
