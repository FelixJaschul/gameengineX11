#pragma once

#include <X11/Xlib.h>
#include <string>

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

        // Swap buffers (if we were using double buffering/GL, placeholder for now)
        void SwapBuffers();

        // Getters for raw X11 access if needed later
        [[nodiscard]] Display* GetDisplay() const { return m_display; }
        [[nodiscard]] ::Window GetWindowID() const { return m_window; }

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
