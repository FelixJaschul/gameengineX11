#include <Rendering/Renderer.h>
#include <iostream>
#include <cstring>
#include <App/App.h>
#include <Config.h>

namespace Engine::Rendering
{
    Renderer::Renderer(Engine::Rendering::Window* window)
        : m_display(window->GetDisplay()), m_window(window->GetWindow()),
        m_GC(XCreateGC(m_display, m_window, 0, nullptr)), m_screen(DefaultScreen(m_display))
    {
        if (!m_display || !m_window) {
            std::cerr << "[Renderer] Invalid Window or Display passed." << std::endl;
            return;
        }

        if (!m_GC) {
            std::cerr << "[Renderer] Failed to create Graphics Context." << std::endl;
            return;
        }

        XSetForeground(m_display, m_GC, 0);

        std::cout << "[Renderer] Initialized successfully." << std::endl;
    }

    Renderer::~Renderer()
    {
        if (m_display && m_GC) XFreeGC(m_display, m_GC);
    }

    void Renderer::SetColor(const unsigned long color) const
    {
        XSetForeground(m_display, m_GC, color);
    }

    void Renderer::DrawText(const int x, const int y, const char* text, const unsigned long color) const
    {
        Renderer::SetColor(color);
        XDrawString(m_display, m_window, m_GC, x, y, text, strlen(text));
    }

    void Renderer::DrawTriangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, const unsigned long color) const
    {
        Renderer::SetColor(color);
        if (appWireframeMode)
        {
            XDrawLine(m_display, m_window, m_GC, x1, y1, x2, y2);
            XDrawLine(m_display, m_window, m_GC, x2, y2, x3, y3);
            XDrawLine(m_display, m_window, m_GC, x3, y3, x1, y1);
        }

        if (!appWireframeMode)
        {
            XFillPolygon(m_display, m_window, m_GC, (XPoint[]) {
                    { (short)x1, (short)y1 },
                    { (short)x2, (short)y2 },
                    { (short)x3, (short)y3 } }, 3, Convex, CoordModeOrigin
            );
        }
    }

    void Renderer::DrawRect(const int x, const int y, const int width, const int height, const unsigned long color) const
    {
        // View culling
        if (x + width < 0 || y + height < 0 || x >= Engine::Window::GetDefaultWindowX() || y >= Engine::Window::GetDefaultWindowY()) return;

        Renderer::SetColor(color);
        if (appWireframeMode)
        {
            XDrawRectangle(m_display, m_window, m_GC, x, y, width, height);
        }

        if (!appWireframeMode)
        {
            XFillRectangle(m_display, m_window, m_GC, x, y, width, height);
        }
    }

    void Renderer::Clear() const
    {
        XClearWindow(m_display, m_window);
    }

    void Renderer::Present() const
    {
        XFlush(m_display);
    }
}
