#pragma once

#include <memory>
#include <Rendering/Window.h>
#include <Rendering/Renderer.h>
#include <Input/Input.h>
#include <Input/Movement.h>
#include <Rendering/Camera.h>
#include <Util/Time.h>

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
        [[nodiscard]] Rendering::Renderer* GetRenderer() const { return m_renderer.get(); }
        [[nodiscard]] Rendering::Window* GetWindow() const { return m_window.get(); }
        [[nodiscard]] Rendering::Camera* GetCamera() const { return m_camera.get(); }
        [[nodiscard]] Input::Movement* GetMovement() const { return m_movement.get(); }
        [[nodiscard]] Util::Time* GetTime() const { return m_time.get(); }

        private:
        // Smart pointers handle memory automatically
        std::unique_ptr<Rendering::Window> m_window;
        std::unique_ptr<Rendering::Renderer> m_renderer;
        std::unique_ptr<Rendering::Camera> m_camera;
        std::unique_ptr<Input::Movement> m_movement;
        std::unique_ptr<Util::Time> m_time;

        bool m_isRunning;
    };

    App* CreateApp();
}
