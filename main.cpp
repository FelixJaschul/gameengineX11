#include <Engine/Core.h>

const char* Engine::Window::appWindowTitle = "X11";
int Engine::Window::appDefaultWindowX = 800;
int Engine::Window::appDefaultWindowY = 600;

bool Engine::Rendering::appWireframeMode = true;
bool Engine::appEnableGroundCheck = true;

int Engine::appMovementSpeed = 10;
int Engine::appCurrentGroundHeight = 400;
int Engine::appMovementJumpHeight = 900;
int Engine::appPlayerHeight = 40;

Math::Vec::iVec2 position = {.x = 400, .y = 400};

class game final : public Engine::App
{
    public:
    game()
    {
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

        // Input
        if (Engine::Input::IsKeyPressed(Engine::Input::Key::W)) Engine::Rendering::appWireframeMode = !Engine::Rendering::appWireframeMode;
        if (Engine::Input::IsKeyPressed(Engine::Input::Key::G)) Engine::appEnableGroundCheck = !Engine::appEnableGroundCheck;

        if (Engine::Input::IsKeyDown(Engine::Input::Key::Right)) Move->Right();
        if (Engine::Input::IsKeyDown(Engine::Input::Key::Left))  Move->Left();
        if (Engine::Input::IsKeyDown(Engine::Input::Key::Down))  Move->Down();
        if (Engine::Input::IsKeyDown(Engine::Input::Key::Up))    Move->Up(Blocks);
    }

    void Render() override
    {
        auto* Renderer = Engine::App::GetRenderer();
        Renderer->Clear();

        // Render all blocks first
        auto& Blocks = Engine::App::GetBlocks();
        for (const auto* Block : Blocks) if (Block) Block->Render(Renderer);

        // Render player
        Renderer->DrawRect(position.x, position.y, Engine::appPlayerHeight, Engine::appPlayerHeight, 0x00FF00);

        Renderer->Present();
    }
};

Engine::App* Engine::CreateApp()
{
    HELLOENGINE();
    return new game();
}