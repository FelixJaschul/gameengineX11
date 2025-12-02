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

        void Clear() const;
        void SwapBuffers() const;

        [[nodiscard]] Display* GetDisplay() const { return m_display; }
        [[nodiscard]] ::Window GetWindow()  const { return m_window;  }

        bool PollEvents();

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
