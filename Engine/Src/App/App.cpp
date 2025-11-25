#include "App/App.h"
#include <iostream>
#include <unistd.h>

namespace Engine
{

    App::App() : m_isRunning(false)
    {
        std::cout << "[Engine] Creating Application..." << std::endl;

        m_window = std::make_unique<Rendering::Window>();
        m_renderer = std::make_unique<Rendering::Renderer>();
    }

    App::~App()
    {
        std::cout << "[Engine] Destroying Application..." << std::endl;
    }

    void App::Run()
    {

        if (!m_window->Init(800, 600, "Felix Engine X11")) return;
        if (!m_renderer->Initialize(m_window.get())) return;

        m_isRunning = true;

        while (m_isRunning) {

            // Poll Events (Input)
            // If the user clicks 'X', PollEvents returns false
            if (!m_window->PollEvents()) {
                m_isRunning = false;
            }

            // Game Logic
            Update();

            // Rendering Logic
            Render();

            usleep(16000);
        }
    }

    void App::Update()
    {

    }

    void App::Render()
    {
        m_renderer->Clear();

        // Red Box
        m_renderer->SetColor(0xFF0000);
        m_renderer->FillRect(100, 100, 50, 50);

        // White Line
        m_renderer->SetColor(0xFFFFFF);
        m_renderer->DrawLine(100, 100, 200, 200);

        m_renderer->Present();
    }

}