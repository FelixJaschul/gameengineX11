#pragma once

#include <memory>
#include <vector>
#include <Rendering/Window.h>
#include <Rendering/Renderer.h>
#include <Rendering/Block.h>
#include <Input/Input.h>
#include <Input/Movement.h>
#include <Rendering/Camera.h>
#include <Util/Time.h>
#include <Util/World.h>

namespace Engine
{
    class App
    {
        public:
        App();
        virtual ~App();

        void Run();
        void Quit();

        protected:
        virtual void Update();
        virtual void Render();

        // Utilities available to subclasses
        [[nodiscard]] Engine::Rendering::Renderer* GetRenderer() const { return m_renderer.get(); }
        [[nodiscard]] Engine::Rendering::Window* GetWindow() const { return m_window.get(); }
        [[nodiscard]] Engine::Rendering::Camera* GetCamera() const { return m_camera.get(); }
        [[nodiscard]] Engine::Input::Movement* GetMovement() const { return m_movement.get(); }
        [[nodiscard]] Engine::Util::Time* GetTime() const { return m_time.get(); }
        [[nodiscard]] Engine::Util::World* GetWorld() const { return m_world.get(); }
        [[nodiscard]] std::vector<Rendering::Block*>& GetBlocks() { return m_blocks; }

        private:
        // Smart pointers handle memory automatically
        std::unique_ptr<Engine::Rendering::Window> m_window;
        std::unique_ptr<Engine::Rendering::Renderer> m_renderer;
        std::unique_ptr<Engine::Rendering::Camera> m_camera;
        std::unique_ptr<Engine::Input::Movement> m_movement;
        std::unique_ptr<Engine::Util::Time> m_time;
        std::unique_ptr<Engine::Util::World> m_world;

        std::vector<Engine::Rendering::Block*> m_blocks;

        bool m_isRunning;
    };

    App* CreateApp();
}