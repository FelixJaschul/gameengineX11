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

        protected:
        virtual void Update();
        virtual void Render();

        // Utilities available to subclasses
        void Quit();
        [[nodiscard]] Rendering::Renderer* GetRenderer() { return m_renderer.get(); }
        [[nodiscard]] Rendering::Window*   GetWindow()   { return m_window.get(); }

        private:
        // Smart pointers handle memory automatically
        std::unique_ptr<Rendering::Window> m_window;
        std::unique_ptr<Rendering::Renderer> m_renderer;

        bool m_isRunning;
    };

    App* CreateApp();
}