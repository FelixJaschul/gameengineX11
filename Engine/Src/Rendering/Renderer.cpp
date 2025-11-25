#include "Rendering/Renderer.h"
#include <iostream>

namespace Engine::Rendering
{
    Renderer::Renderer()
        : m_Display(nullptr), m_WindowID(0), m_GC(nullptr), m_Screen(0)
    {
    }

    Renderer::~Renderer()
    {
        if (m_Display && m_GC) {
            XFreeGC(m_Display, m_GC);
        }
    }

    bool Renderer::Initialize(Window* window)
    {
        if (!window) return false;

        m_Display = window->GetDisplay();
        m_WindowID = window->GetWindowID();

        if (!m_Display || !m_WindowID) {
            std::cerr << "[Renderer] Invalid Window or Display passed." << std::endl;
            return false;
        }

        m_Screen = DefaultScreen(m_Display);

        // Create the Graphics Context (GC)
        // We can pass 0 and nullptr if we don't want special flags immediately
        m_GC = XCreateGC(m_Display, m_WindowID, 0, nullptr);

        if (!m_GC) {
            std::cerr << "[Renderer] Failed to create Graphics Context." << std::endl;
            return false;
        }

        // Set a default drawing color (White)
        XSetForeground(m_Display, m_GC, WhitePixel(m_Display, m_Screen));

        std::cout << "[Renderer] Initialized successfully." << std::endl;
        return true;
    }

    void Renderer::SetColor(unsigned long color)
    {
        // Note: In true X11, 'color' is a pixel value.
        // For standard 24-bit TrueColor displays, 0x00RRGGBB usually works naturally.
        XSetForeground(m_Display, m_GC, color);
    }

    void Renderer::DrawLine(int x1, int y1, int x2, int y2)
    {
        XDrawLine(m_Display, m_WindowID, m_GC, x1, y1, x2, y2);
    }

    void Renderer::DrawRect(int x, int y, int width, int height)
    {
        XDrawRectangle(m_Display, m_WindowID, m_GC, x, y, width, height);
    }

    void Renderer::FillRect(int x, int y, int width, int height)
    {
        XFillRectangle(m_Display, m_WindowID, m_GC, x, y, width, height);
    }

    void Renderer::Clear()
    {
        XClearWindow(m_Display, m_WindowID);
    }

    void Renderer::Present()
    {
        XFlush(m_Display);
    }

}
