#include <Engine/Core.h>
#include <cmath>
#include <cstdint>
#include <vector>
#include <Util/World.h>

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
            Engine::App::GetWorld()->Generate();
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
                const auto[x, y] = Camera->WorldToScreen(Block->GetPosition());
                Renderer->DrawRect(x, y, Block->GetWidth(), Block->GetHeight(), Block->GetColor());
            }

            // Render player at screen center
            Renderer->DrawRect(
                Engine::Window::GetDefaultWindowX() / 2,
                Engine::Window::GetDefaultWindowY() / 2,
                Engine::GetPlayerHeight(),
                Engine::GetPlayerHeight(), 0x00FF00);

            // UI stays fixed on screen
            char Text[32];
            snprintf(Text, sizeof(Text), "FPS: %.1f", Engine::App::GetTime()->GetFPS()); Renderer->DrawText(10, 20, Text, 0xFFFFFF);
            snprintf(Text, sizeof(Text), "GroundCheck: %d", Engine::GetGroundCheck()); Renderer->DrawText(10, 40, Text, 0xFFFFFF);
            snprintf(Text, sizeof(Text), "Pos: %d, %d", position.x, position.y); Renderer->DrawText(10, 60, Text, 0xFFFFFF);

            Renderer->Present();
        }
    };
}

Engine::App* Engine::CreateApp()
{
    HELLOENGINE();
    return new Game::App();
}
