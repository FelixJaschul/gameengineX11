#pragma once

#include "Window.h"
#include <X11/Xlib.h>

namespace Engine::Rendering {

    class Renderer
    {
        public:
        Renderer();
        ~Renderer();

        bool Initialize(Window* window);

        void SetColor(unsigned long color); // 0xRRGGBB format usually requires XAllocColor, using raw pixel for now
        void DrawLine(int x1, int y1, int x2, int y2);
        void DrawRect(int x, int y, int width, int height);
        void FillRect(int x, int y, int width, int height);

        void Clear();
        void Present();

        private:
        Display* m_Display;
        ::Window m_WindowID;
        GC m_GC; // The X11 Graphics Context
        int m_Screen;
    };

}
