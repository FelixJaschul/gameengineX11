#pragma once

#include <memory>
#include <Rendering/Window.h>
#include <Rendering/Renderer.h>
#include <Input/Input.h>
#include <Input/Movement.h>
#include <Rendering/Camera.h>

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
        [[nodiscard]] Rendering::Window* GetWindow() { return m_window.get(); }
        [[nodiscard]] Input::Movement* GetMovement() { return m_movement.get(); }
        static        Rendering::Camera* GetCamera() { return &Rendering::Camera::Instance(); }

        private:
        // Smart pointers handle memory automatically
        std::unique_ptr<Rendering::Window> m_window;
        std::unique_ptr<Rendering::Renderer> m_renderer;
        std::unique_ptr<Input::Movement> m_movement;

        bool m_isRunning;
    };

    App* CreateApp();
}
