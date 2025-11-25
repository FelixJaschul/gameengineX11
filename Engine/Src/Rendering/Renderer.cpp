#include "Rendering/Renderer.h"
#include <iostream>

namespace Engine::Rendering
{
    Renderer::Renderer()
        : m_display(nullptr), m_windowID(0), m_GC(nullptr), m_screen(0)
    {
    }

    Renderer::~Renderer()
    {
        if (m_display && m_GC) {
            XFreeGC(m_display, m_GC);
        }
    }

    bool Renderer::Init(Window* window)
    {
        if (!window) return false;

        m_display = window->GetDisplay();
        m_windowID = window->GetWindowID();

        if (!m_display || !m_windowID) {
            std::cerr << "[Renderer] Invalid Window or Display passed." << std::endl;
            return false;
        }

        m_screen = DefaultScreen(m_display);
        m_GC = XCreateGC(m_display, m_windowID, 0, nullptr);

        if (!m_GC) {
            std::cerr << "[Renderer] Failed to create Graphics Context." << std::endl;
            return false;
        }

        XSetForeground(m_display, m_GC, 0);

        std::cout << "[Renderer] Initialized successfully." << std::endl;
        return true;
    }

    void Renderer::SetColor(unsigned long color)
    {
        XSetForeground(m_display, m_GC, color);
    }

    void Renderer::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
    {
        XDrawLine(m_display, m_windowID, m_GC, x1, y1, x2, y2);
        XDrawLine(m_display, m_windowID, m_GC, x2, y2, x3, y3);
        XDrawLine(m_display, m_windowID, m_GC, x3, y3, x1, y1);
    }

    void Renderer::Clear()
    {
        XClearWindow(m_display, m_windowID);
    }

    void Renderer::Present()
    {
        XFlush(m_display);
    }

}
