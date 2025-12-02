#include <Engine/Core.h>

Math::Vec::iVec2 position = {.x = 400, .y = 400};

class game final : public Engine::App
{
    public:
    game()
    {
        Engine::Window::SetWindowTitle("X11"); Engine::Window::SetDefaultWindowX(800); Engine::Window::SetDefaultWindowY(600);
        Engine::Rendering::SetWireframeMode(true);
        Engine::SetGroundCheck(true); Engine::SetMovementSpeed(10); Engine::SetMovementJumpHeight(700); Engine::SetPlayerHeight(40);

        int x = -Engine::appPlayerHeight;
        for (int i = 0; i != 17; i++)
        {
            x += Engine::appPlayerHeight;
            AddBlock(new Engine::Rendering::Block({x, 450}, Engine::appPlayerHeight, Engine::appPlayerHeight, 0x8B4513));
        }
    }

    protected:
    void Update() override
    {
        // Init
        auto* Camera = Engine::App::GetCamera();
        auto* Move   = Engine::App::GetMovement();
        auto& Blocks = Engine::App::GetBlocks();

        // Update
        position = Camera->GetPosition();
        for (auto* Block : Blocks) if (Block) Block->Update();

        // Input
        if (Engine::Input::IsKeyPressed(Engine::Input::Key::W)) Engine::SetGroundCheck(!Engine::GetGroundCheck());
        if (Engine::Input::IsKeyPressed(Engine::Input::Key::G)) Engine::Rendering::SetWireframeMode(!Engine::Rendering::GetWireframeMode());

        if (Engine::Input::IsKeyDown(Engine::Input::Key::Right)) Move->Right();
        if (Engine::Input::IsKeyDown(Engine::Input::Key::Left))  Move->Left();
        if (Engine::Input::IsKeyDown(Engine::Input::Key::Down))  Move->Down();
        if (Engine::Input::IsKeyDown(Engine::Input::Key::Up))    Move->Up();
    }

    void Render() override
    {
        auto* Renderer = Engine::App::GetRenderer();
        Renderer->Clear();

        // Render all blocks first
        auto& Blocks = Engine::App::GetBlocks();
        for (const auto* Block : Blocks) if (Block) Block->Render(Renderer);

        // Render player
        Renderer->DrawRect(position.x, position.y, Engine::GetPlayerHeight(), Engine::GetPlayerHeight(), 0x00FF00);

        Renderer->Present();
    }
};

Engine::App* Engine::CreateApp()
{
    HELLOENGINE();
    return new game();
}