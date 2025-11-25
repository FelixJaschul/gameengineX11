#pragma once

#include <X11/Xlib.h>
#include <string>

namespace Engine {
    namespace Rendering {

        class Window {
        public:
            Window();
            ~Window();

            // Initialize the X11 Display and Window
            bool Initialize(int width, int height, const std::string& title);

            // Handle X11 events (inputs, window close, etc.)
            // Returns false if the window should close
            bool PollEvents();

            // Clear the window (Basic rendering stub)
            void Clear();

            // Swap buffers (if we were using double buffering/GL, placeholder for now)
            void SwapBuffers();

            // Getters for raw X11 access if needed later
            Display* GetDisplay() const { return m_display; }
            ::Window GetWindowID() const { return m_window; }

        private:
            void Cleanup();

        private:
            Display* m_display;
            ::Window m_window;
            int m_screen;
            Atom m_wmDeleteMessage; // Handle window close button
            bool m_isRunning;
        };

    }
}