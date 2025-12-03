#include <App/App.h>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <Util/Time.h>
#include <Rendering/Camera.h>

namespace Engine
{
    App::App()
        : m_isRunning(false)
    {
        // Create systems in an order that respects dependencies
        m_window   = std::make_unique<Rendering::Window>();
        m_time     = std::make_unique<Util::Time>();
        m_camera   = std::make_unique<Rendering::Camera>(Engine::App::GetTime(), Engine::App::GetBlocks());
        m_renderer = std::make_unique<Rendering::Renderer>(Engine::App::GetWindow());
        m_movement = std::make_unique<Input::Movement>(Engine::App::GetCamera(), Engine::App::GetTime());

        std::cout << "[Engine] Creating Application..." << std::endl;
    }

    App::~App()
    {
        // Clean up blocks
        for (const auto* block : m_blocks) delete block;
        m_blocks.clear();

        std::cout << "[Engine] Destroying Application..." << std::endl;
    }

    void App::Run()
    {
        m_isRunning = true;

        while (m_isRunning)
        {
            if (!m_window->PollEvents()) m_isRunning = false;

            // Call Update
            Update();

            if (m_camera) m_camera->Jump(0, 0);

            // Render Shit
            Render();
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
        // Render
        // Will be overridden
    }

}