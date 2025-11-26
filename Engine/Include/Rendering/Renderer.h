#pragma once

#include "Window.h"
#include <X11/Xlib.h>

namespace Engine::Rendering
{
    extern bool appWireframeMode;

    class Renderer
    {
        public:
        Renderer();
        ~Renderer();

        bool Init(Window* window);

        void SetColor(unsigned long color); // 0xRRGGBB format usually requires XAllocColor, using raw pixel for now

        void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, unsigned long color);
        void DrawRect(int x, int y, int width, int height, unsigned long color);

        void Clear();
        void Present();

        private:
        Display* m_display;
        ::Window m_windowID;
        GC m_GC;
        int m_screen;
    };

}
