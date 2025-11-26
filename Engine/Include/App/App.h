#pragma once

#include <memory>
#include "Rendering/Window.h"
#include "Rendering/Renderer.h"
#include "Rendering/Camera.h"

namespace Engine
{
    extern const char* appWindowTitle;
    extern int appDefaultWindowX;
    extern int appDefaultWindowY;

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
        std::unique_ptr<Rendering::Camera> m_camera;

        bool m_isRunning;
    };

    App* CreateApp();
}