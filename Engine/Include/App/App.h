#pragma once

#include <memory>
#include <Rendering/Window.h>
#include <Rendering/Renderer.h>

namespace Engine
{
    class App
    {
        public:
        App();
        virtual ~App();

        void Run();

        private:
        // Internal loop functions
        void Update();
        void Render();

        private:
        // Smart pointers handle memory automatically
        std::unique_ptr<Rendering::Window> m_window;
        std::unique_ptr<Rendering::Renderer> m_renderer;

        bool m_isRunning;
    };

    App* CreateApp();
}