#include <App/App.h>
#include <iostream>
#include <unistd.h>
#include <Util/Time.h>
#include <Rendering/Camera.h>

namespace Engine
{
    App::App()
        : m_isRunning(false)
    {
        // Create systems in an order that respects dependencies
        m_window   = std::make_unique<Rendering::Window>(Engine::Window::appDefaultWindowX, Engine::Window::appDefaultWindowY, Engine::Window::appWindowTitle);
        m_time     = std::make_unique<Util::Time>();
        m_camera   = std::make_unique<Rendering::Camera>(m_time.get());
        m_renderer = std::make_unique<Rendering::Renderer>(GetWindow());
        m_movement = std::make_unique<Input::Movement>(GetCamera());

        std::cout << "[Engine] Creating Application..." << std::endl;
    }

    App::~App()
    {
        std::cout << "[Engine] Destroying Application..." << std::endl;
    }

    void App::Run()
    {
        m_isRunning = true;

        while (m_isRunning)
        {
            // Update time at the start of the frame so physics uses current dt
            m_time->Update();

            // Mark the beginning of a new frame for input (captures presses/releases)
            Input::UpdateFrame();

            // Process window events
            if (!m_window->PollEvents()) m_isRunning = false;

            // Game Logic
            Update();

            // Apply gravity/fall even when no input is pressed
            if (m_camera) m_camera->Jump(0, 0);

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