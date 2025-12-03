#include <Engine/Core.h>

Math::Vec::iVec2 position = {.x = 400, .y = 400};

namespace Game
{
    class App final : public Engine::App
    {
        public:
        App()
        {
            Engine::Window::SetWindowTitle("X11"); Engine::Window::SetDefaultWindowX(800); Engine::Window::SetDefaultWindowY(600);
            Engine::Window::SetDesiredFPS(180);
            Engine::Rendering::SetWireframeMode(true);
            Engine::SetGroundCheck(true); Engine::SetMovementSpeed(10); Engine::SetMovementJumpHeight(700); Engine::SetPlayerHeight(40);
            GenerateWorld(GetBlocks());
        }

        protected:
        static void GenerateWorld(std::vector<Engine::Rendering::Block*>& Blocks)
        {
            int x = -Engine::appPlayerHeight;
            for (int i = 0; i != 17; i++)
            {
                x += Engine::appPlayerHeight;
                Blocks.push_back(new Engine::Rendering::Block({x, 450}, Engine::appPlayerHeight, Engine::appPlayerHeight, 0x8B4513));
            }
        }

        void Update() override
        {
            // Update
            position = GetCamera()->GetPosition();
            for (auto* Block : GetBlocks()) if (Block) Block->Update();
            GetTime()->Update();

            // Input
            if (Engine::Input::IsKeyPressed(Engine::Input::Key::G)) Engine::SetGroundCheck(!Engine::GetGroundCheck());
            if (Engine::Input::IsKeyPressed(Engine::Input::Key::W)) Engine::Rendering::SetWireframeMode(!Engine::Rendering::GetWireframeMode());

            if (Engine::Input::IsKeyDown(Engine::Input::Key::Right)) GetMovement()->Right();
            if (Engine::Input::IsKeyDown(Engine::Input::Key::Left))  GetMovement()->Left();
            if (Engine::Input::IsKeyDown(Engine::Input::Key::Down))  GetMovement()->Down();
            if (Engine::Input::IsKeyDown(Engine::Input::Key::Up))    GetMovement()->Up();
        }

        void Render() override
        {
            auto* Renderer = Engine::App::GetRenderer();
            Renderer->Clear();

            // Render all blocks first
            for (const auto* Block : GetBlocks()) if (Block) Block->Render(Renderer);

            // Render player
            Renderer->DrawRect(position.x, position.y, Engine::GetPlayerHeight(), Engine::GetPlayerHeight(), 0x00FF00);

            char Text[32];
            snprintf(Text, sizeof(Text), "FPS: %.1f", Engine::App::GetTime()->GetFPS());
            Renderer->DrawText(10, 20, Text, 0xFFFFFF);
            snprintf(Text, sizeof(Text), "GroundCheck Value: %.d", Engine::GetGroundCheck());
            Renderer->DrawText(100, 20, Text, 0xFFFFFF);

            Renderer->Present();
        }
    };
}

Engine::App* Engine::CreateApp()
{
    HELLOENGINE();
    return new Game::App();
}