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
        if (!m_window->Init(appDefaultWindowX, appDefaultWindowY, appWindowTitle)) return;
        if (!m_renderer->Init(m_window.get())) return;

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

        //m_renderer->DrawTriangle(400, 100, 300, 400, 500, 400, 0x00FF00);
        m_renderer->DrawRect(250, 100, 100, 100, 0x00FF00);

        m_renderer->Present();
    }

}