#include <Rendering/Window.h>
#include <iostream>
#include <X11/keysym.h>
#include <Input/Input.h>

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
        XSelectInput(m_display, m_window, ExposureMask | KeyPressMask | KeyReleaseMask | StructureNotifyMask);

        // Handle Close Button
        m_wmDeleteMessage = XInternAtom(m_display, "WM_DELETE_WINDOW", False);
        XSetWMProtocols(m_display, m_window, &m_wmDeleteMessage, 1);

        XStoreName(m_display, m_window, title.c_str());
        XMapWindow(m_display, m_window);

        m_isRunning = true;
        return true;
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
                {
                    KeySym sym = XLookupKeysym(&event.xkey, 0);
                    // Map to engine key and set down=true
                    auto mapKey = [](KeySym s) -> Engine::Input::Key {
                        using namespace Engine::Input;
                        switch (s)
                        {
                            case XK_Escape: return Key::Escape;
                            case XK_space: return Key::Space;
                            case XK_Return: return Key::Enter;
                            case XK_Tab: return Key::Tab;
                            case XK_BackSpace: return Key::Backspace;

                            case XK_Left: return Key::Left;
                            case XK_Right: return Key::Right;
                            case XK_Up: return Key::Up;
                            case XK_Down: return Key::Down;

                            case XK_a: case XK_A: return Key::A;
                            case XK_b: case XK_B: return Key::B;
                            case XK_c: case XK_C: return Key::C;
                            case XK_d: case XK_D: return Key::D;
                            case XK_e: case XK_E: return Key::E;
                            case XK_f: case XK_F: return Key::F;
                            case XK_g: case XK_G: return Key::G;
                            case XK_h: case XK_H: return Key::H;
                            case XK_i: case XK_I: return Key::I;
                            case XK_j: case XK_J: return Key::J;
                            case XK_k: case XK_K: return Key::K;
                            case XK_l: case XK_L: return Key::L;
                            case XK_m: case XK_M: return Key::M;
                            case XK_n: case XK_N: return Key::N;
                            case XK_o: case XK_O: return Key::O;
                            case XK_p: case XK_P: return Key::P;
                            case XK_q: case XK_Q: return Key::Q;
                            case XK_r: case XK_R: return Key::R;
                            case XK_s: case XK_S: return Key::S;
                            case XK_t: case XK_T: return Key::T;
                            case XK_u: case XK_U: return Key::U;
                            case XK_v: case XK_V: return Key::V;
                            case XK_w: case XK_W: return Key::W;
                            case XK_x: case XK_X: return Key::X;
                            case XK_y: case XK_Y: return Key::Y;
                            case XK_z: case XK_Z: return Key::Z;

                            case XK_0: return Key::Num0;
                            case XK_1: return Key::Num1;
                            case XK_2: return Key::Num2;
                            case XK_3: return Key::Num3;
                            case XK_4: return Key::Num4;
                            case XK_5: return Key::Num5;
                            case XK_6: return Key::Num6;
                            case XK_7: return Key::Num7;
                            case XK_8: return Key::Num8;
                            case XK_9: return Key::Num9;

                            case XK_Shift_L: return Key::LeftShift;
                            case XK_Shift_R: return Key::RightShift;
                            case XK_Control_L: return Key::LeftControl;
                            case XK_Control_R: return Key::RightControl;
                            case XK_Alt_L: return Key::LeftAlt;
                            case XK_Alt_R: return Key::RightAlt;
                            case XK_Super_L: return Key::LeftSuper;
                            case XK_Super_R: return Key::RightSuper;
                            default: return Engine::Input::Key::Unknown;
                        }
                    };

                    Engine::Input::Key k = mapKey(sym);
                    if (k != Engine::Input::Key::Unknown)
                        Engine::Input::SetKey(k, true);

                    // Close on ESC
                    if (sym == XK_Escape) {
                        m_isRunning = false;
                    }
                    break;
                }
                case KeyRelease:
                {
                    KeySym sym = XLookupKeysym(&event.xkey, 0);
                    auto mapKey = [](KeySym s) -> Engine::Input::Key {
                        using namespace Engine::Input;
                        switch (s)
                        {
                            case XK_Escape: return Key::Escape;
                            case XK_space: return Key::Space;
                            case XK_Return: return Key::Enter;
                            case XK_Tab: return Key::Tab;
                            case XK_BackSpace: return Key::Backspace;

                            case XK_Left: return Key::Left;
                            case XK_Right: return Key::Right;
                            case XK_Up: return Key::Up;
                            case XK_Down: return Key::Down;

                            case XK_a: case XK_A: return Key::A;
                            case XK_b: case XK_B: return Key::B;
                            case XK_c: case XK_C: return Key::C;
                            case XK_d: case XK_D: return Key::D;
                            case XK_e: case XK_E: return Key::E;
                            case XK_f: case XK_F: return Key::F;
                            case XK_g: case XK_G: return Key::G;
                            case XK_h: case XK_H: return Key::H;
                            case XK_i: case XK_I: return Key::I;
                            case XK_j: case XK_J: return Key::J;
                            case XK_k: case XK_K: return Key::K;
                            case XK_l: case XK_L: return Key::L;
                            case XK_m: case XK_M: return Key::M;
                            case XK_n: case XK_N: return Key::N;
                            case XK_o: case XK_O: return Key::O;
                            case XK_p: case XK_P: return Key::P;
                            case XK_q: case XK_Q: return Key::Q;
                            case XK_r: case XK_R: return Key::R;
                            case XK_s: case XK_S: return Key::S;
                            case XK_t: case XK_T: return Key::T;
                            case XK_u: case XK_U: return Key::U;
                            case XK_v: case XK_V: return Key::V;
                            case XK_w: case XK_W: return Key::W;
                            case XK_x: case XK_X: return Key::X;
                            case XK_y: case XK_Y: return Key::Y;
                            case XK_z: case XK_Z: return Key::Z;

                            case XK_0: return Key::Num0;
                            case XK_1: return Key::Num1;
                            case XK_2: return Key::Num2;
                            case XK_3: return Key::Num3;
                            case XK_4: return Key::Num4;
                            case XK_5: return Key::Num5;
                            case XK_6: return Key::Num6;
                            case XK_7: return Key::Num7;
                            case XK_8: return Key::Num8;
                            case XK_9: return Key::Num9;

                            case XK_Shift_L: return Key::LeftShift;
                            case XK_Shift_R: return Key::RightShift;
                            case XK_Control_L: return Key::LeftControl;
                            case XK_Control_R: return Key::RightControl;
                            case XK_Alt_L: return Key::LeftAlt;
                            case XK_Alt_R: return Key::RightAlt;
                            case XK_Super_L: return Key::LeftSuper;
                            case XK_Super_R: return Key::RightSuper;
                            default: return Engine::Input::Key::Unknown;
                        }
                    };

                    Engine::Input::Key k = mapKey(sym);
                    if (k != Engine::Input::Key::Unknown)
                        Engine::Input::SetKey(k, false);
                    break;
                }
                default: break;
            }
        }
        return m_isRunning;
    }
}
