#include <Engine/Core.h>
#include <Math/Vec.h>
#include <Rendering/Block.h>

const char* Engine::Window::appWindowTitle = "X11";
int Engine::Window::appDefaultWindowX = 800;
int Engine::Window::appDefaultWindowY = 600;

bool Engine::Rendering::appWireframeMode = true;

int Engine::appMovementSpeed = 10;
int Engine::appCurrentGroundHeight = 400;
bool Engine::appEnableGroundCheck = true;
bool Engine::appEnableVelocity = true;
int Engine::appMovementJumpHeight = 900;
int Engine::appPlayerHeight = 40;

Math::Vec::iVec2 position = {.x = 400, .y = 400};

class game final : public Engine::App
{
    public:
    game()
    {
        AddBlock(new Engine::Rendering::Block({-10, 450}, 900, 50, 0x8B4513));
        AddBlock(new Engine::Rendering::Block({200, 300}, 200, 30, 0x654321));
        AddBlock(new Engine::Rendering::Block({450, 200}, 150, 30, 0x654321));
    }

    protected:
    void Update() override
    {
        // Init
        auto* camera   = Engine::App::GetCamera();
        auto* movement = Engine::App::GetMovement();
        auto& blocks   = Engine::App::GetBlocks();

        // Update
        position = camera->GetPosition();

        // Input
        if (Engine::Input::IsKeyPressed(Engine::Input::Key::W)) Engine::Rendering::appWireframeMode = !Engine::Rendering::appWireframeMode;
        if (Engine::Input::IsKeyPressed(Engine::Input::Key::G)) Engine::appEnableGroundCheck = !Engine::appEnableGroundCheck;

        if (Engine::Input::IsKeyDown(Engine::Input::Key::Right)) movement->Right();
        if (Engine::Input::IsKeyDown(Engine::Input::Key::Left))  movement->Left();
        if (Engine::Input::IsKeyDown(Engine::Input::Key::Down))  movement->Down();
        if (Engine::Input::IsKeyDown(Engine::Input::Key::Up))    movement->Up(blocks);
    }

    void Render() override
    {
        auto* renderer = Engine::App::GetRenderer();
        renderer->Clear();

        // Render all blocks first
        auto& blocks = Engine::App::GetBlocks();
        for (const auto* block : blocks) if (block) block->Render(renderer);

        // Render player
        renderer->DrawRect(position.x, position.y, Engine::appPlayerHeight, Engine::appPlayerHeight, 0x00FF00);

        renderer->Present();
    }
};

Engine::App* Engine::CreateApp()
{
    HELLOENGINE();
    return new game();
}