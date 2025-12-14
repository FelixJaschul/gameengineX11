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
            Engine::SetGroundCheck(true); Engine::SetMovementSpeed(10); Engine::SetMovementJumpHeight(700);
            Engine::SetPlayerHeight(40);
            GenerateWorld(GetBlocks());
        }

        protected:
        static void GenerateWorld(std::vector<Engine::Rendering::Block*>& Blocks)
        {
            for (int x = 0; x < 800; x += Engine::GetPlayerHeight())
            {
                Blocks.push_back(
                    new Engine::Rendering::Block(
                        {x, 400},
                        Engine::GetPlayerHeight(),
                        Engine::GetPlayerHeight(),
                        false,
                        0x101013FF
                    )
                );
            }
            Blocks.push_back(
                new Engine::Rendering::Block(
                    {600, 300},
                    Engine::GetPlayerHeight(),
                    Engine::GetPlayerHeight(),
                    true,
                    0x00FFFFFF
                )
            );
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
            const auto* Renderer = Engine::App::GetRenderer();
            const auto* Camera = Engine::App::GetCamera();
            Renderer->Clear();

            // Render all blocks with camera offset
            for (const auto* Block : GetBlocks())
            {
                if (Block)
                {
                    const auto[x, y] = Camera->WorldToScreen(Block->GetPosition());
                    Renderer->DrawRect(x, y, Block->GetWidth(), Block->GetHeight(), Block->GetColor());
                }
            }

            // Render player at screen center
            const int playerScreenX = Engine::Window::GetDefaultWindowX() / 2;
            const int playerScreenY = Engine::Window::GetDefaultWindowY() / 2;
            Renderer->DrawRect(playerScreenX, playerScreenY, Engine::GetPlayerHeight(), Engine::GetPlayerHeight(), 0x00FF00);

            // UI stays fixed on screen
            char Text[32];
            snprintf(Text, sizeof(Text), "FPS: %.1f", Engine::App::GetTime()->GetFPS());
            Renderer->DrawText(10, 20, Text, 0xFFFFFF);
            snprintf(Text, sizeof(Text), "GroundCheck: %d", Engine::GetGroundCheck());
            Renderer->DrawText(10, 40, Text, 0xFFFFFF);
            snprintf(Text, sizeof(Text), "Pos: %d, %d", position.x, position.y);
            Renderer->DrawText(10, 60, Text, 0xFFFFFF);

            Renderer->Present();
        }
    };
}

Engine::App* Engine::CreateApp()
{
    HELLOENGINE();
    return new Game::App();
}