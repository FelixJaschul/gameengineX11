#include <Rendering/Window.h>
#include <iostream>

namespace Engine::Rendering
{
    Window::Window()
        : m_display(nullptr), m_window(0), m_screen(0), m_isRunning(false)
    {
    }

    Window::~Window()
    {
        Cleanup();
    }

    bool Window::Init(int width, int height, const std::string& title)
    {
        m_display = XOpenDisplay(nullptr);
        if (m_display == nullptr)
        {
            std::cerr << "[Engine] Failed to open X display." << std::endl;
            return false;
        }

        m_screen = DefaultScreen(m_display);

        m_window = XCreateSimpleWindow(
            m_display,
            RootWindow(m_display, m_screen),
            10, 10,
            width, height,
            1, 0, 0
        );

        // Select Events
        XSelectInput(m_display, m_window, ExposureMask | KeyPressMask | StructureNotifyMask);

        // Handle Close Button
        m_wmDeleteMessage = XInternAtom(m_display, "WM_DELETE_WINDOW", False);
        XSetWMProtocols(m_display, m_window, &m_wmDeleteMessage, 1);

        XStoreName(m_display, m_window, title.c_str());
        XMapWindow(m_display, m_window);

        m_isRunning = true;
        return true;
    }

    bool Window::PollEvents()
    {
        if (!m_isRunning) return false;

        while (XPending(m_display) > 0)
        {
            XEvent event;
            XNextEvent(m_display, &event);

            switch (event.type)
            {
                case ClientMessage:
                    if ((Atom)event.xclient.data.l[0] == m_wmDeleteMessage) {
                        m_isRunning = false;
                    }
                    break;
                case KeyPress:
                    // Close on ESC
                    if (event.xkey.keycode == 0x09) {
                        m_isRunning = false;
                    }
                    break;
                default: break;
            }
        }
        return m_isRunning;
    }

    void Window::Clear()
    {
        XClearWindow(m_display, m_window);
    }

    void Window::SwapBuffers()
    {
        XFlush(m_display);
    }

    void Window::Cleanup()
    {
        if (m_display)
        {
            XDestroyWindow(m_display, m_window);
            XCloseDisplay(m_display);
            m_display = nullptr;
            m_window = 0;
        }
    }
}
