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
        [[nodiscard]] std::vector<Rendering::Block*>& GetBlocks() { return m_blocks; }

        void AddBlock(Rendering::Block* block) { m_blocks.push_back(block); }

        private:
        // Smart pointers handle memory automatically
        std::unique_ptr<Rendering::Window> m_window;
        std::unique_ptr<Rendering::Renderer> m_renderer;
        std::unique_ptr<Rendering::Camera> m_camera;
        std::unique_ptr<Input::Movement> m_movement;
        std::unique_ptr<Util::Time> m_time;

        std::vector<Rendering::Block*> m_blocks;

        bool m_isRunning;
    };

    App* CreateApp();
}