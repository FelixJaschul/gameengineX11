#pragma once

#include "../EnginePch.h"

struct X11Window;

namespace Engine
{
    class Window
    {
        public:
        static Window& GetInstance()
        {
            return *m_instance;
        }

        static void InitWindow(int width, int height, const char* title)
        {
            m_instance = new Window(width, height, title);
        }

        Window(int width, int height, const char* title);
        ~Window();

        void SetBackgroundColor(float r, float g, float b);

        // GetWindowSize() { return m_windowSize; }
        Window GetWindow() { return m_window; }

        void Clear();
        void PollEvents();
        void SwapBuffer();

        bool ShouldClose() const;

        private:
        static Window* m_instance;
        // m_windowSize;
        Window m_window;
    };
}