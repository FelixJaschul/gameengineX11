#include <App/App.h>
#include <iostream>
#include <unistd.h>

namespace Engine
{
    App::App() : m_isRunning(false)
    {
        std::cout << "[Engine] Creating Application..." << std::endl;

        m_window    = std::make_unique<Rendering::Window>();
        m_renderer  = std::make_unique<Rendering::Renderer>();
        m_movement  = std::make_unique<Input::Movement>();
    }

    App::~App()
    {
        std::cout << "[Engine] Destroying Application..." << std::endl;
    }

    void App::Run()
    {
        if (!m_window->Init(Engine::Window::appDefaultWindowX, Engine::Window::appDefaultWindowY, Engine::Window::appWindowTitle)) return;
        if (!m_renderer->Init(m_window.get())) return;
        if (!m_movement) return;

        m_isRunning = true;

        while (m_isRunning)
        {
            // Mark the beginning of a new frame for input (captures presses/releases)
            Input::UpdateFrame();

            // Make Buttons usable
            if (!m_window->PollEvents()) m_isRunning = false;

            // Game Logic
            Update();

            // Rendering Logic
            Render();

            usleep(16000);
        }
    }

    void App::Quit()
    {
        m_isRunning = false;
    }

    void App::Update()
    {
        // Will Update once every frame
        // Will be overridden
    }

    void App::Render()
    {
        m_renderer->Clear();

        m_renderer->DrawTriangle(400, 100, 300, 400, 500, 400, 0xFF0000);
        m_renderer->DrawRect(250, 100, 100, 100, 0x00FF00);

        m_renderer->Present();
    }

}