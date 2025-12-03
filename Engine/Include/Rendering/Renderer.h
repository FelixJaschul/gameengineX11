#pragma once

#include <Rendering/Window.h>
#include <X11/Xlib.h>

namespace Engine::Rendering
{
    class Renderer
    {
        public:
        explicit Renderer(Engine::Rendering::Window* window);
        ~Renderer();

        void SetColor(unsigned long color) const;

        void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, unsigned long color) const;
        void DrawRect(int x, int y, int width, int height, unsigned long color) const;
        void DrawText(int x, int y, const char* text, unsigned long color) const;

        void Clear() const;
        void Present() const;

        private:
        Display* m_display;
        ::Window m_window;
        GC m_GC;
        int m_screen;
    };

}
