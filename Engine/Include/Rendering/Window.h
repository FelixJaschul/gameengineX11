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

        bool Init(int width, int height, const std::string& title);

        bool PollEvents();

        void Clear();

        void SwapBuffers();

        [[nodiscard]] Display* GetDisplay() const { return m_display; }
        [[nodiscard]] ::Window GetWindow()  const { return m_window;  }

        static Math::Vec::iVec2 GetWindowSize() { return Math::Vec::iVec2{Engine::Window::appDefaultWindowX, Engine::Window::appDefaultWindowY}; }

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
