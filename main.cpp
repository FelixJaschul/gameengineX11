#include <Engine/Core.h>

#include <Math/Vec.h>

const char* Engine::Window::appWindowTitle = "X11";
int Engine::Window::appDefaultWindowX = 800;
int Engine::Window::appDefaultWindowY = 600;

bool Engine::Rendering::appWireframeMode = true;

int Engine::appMovementSpeed = 10;
int Engine::appCurrentGroundHeight = 400;
bool Engine::appEnableGroundCheck = true;
bool Engine::appEnableVelocity = true;
int Engine::appMovementJumpHeight = 600;
int Engine::appPlayerHeight = 100; // Must match the rendered rect height

Math::Vec::iVec2 position;

class game final : public Engine::App
{
    protected:
    void Update() override
    {
        // Init
        auto* camera   = Engine::App::GetCamera();
        auto* movement = Engine::App::GetMovement();

        // Update
        position = camera->GetPosition();

        // Input
        if (Engine::Input::IsKeyPressed(Engine::Input::Key::W)) Engine::Rendering::appWireframeMode = !Engine::Rendering::appWireframeMode;
        if (Engine::Input::IsKeyPressed(Engine::Input::Key::G)) Engine::appEnableGroundCheck = !Engine::appEnableGroundCheck;

        if (Engine::Input::IsKeyDown(Engine::Input::Key::Right)) movement->Right();
        if (Engine::Input::IsKeyDown(Engine::Input::Key::Left))  movement->Left();
        if (Engine::Input::IsKeyDown(Engine::Input::Key::Down))  movement->Down();
        if (Engine::Input::IsKeyDown(Engine::Input::Key::Up))    movement->Up();
    }

    void Render() override
    {
        auto* renderer = Engine::App::GetRenderer();
        renderer->Clear();

        renderer->DrawTriangle(400, 100, 300, 400, 500, 400, 0xFF0000);
        renderer->DrawRect(position.x, position.y, 100, 100, 0x00FF00);

        renderer->Present();
    }
};

Engine::App* Engine::CreateApp()
{
    HELLOENGINE();
    return new game();
}