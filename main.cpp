#include <Engine/Core.h>

#include <Input/Movement.h>
#include <Math/Vec.h>

#include "Rendering/Camera.h"

const char* Engine::appWindowTitle = "X11";
int Engine::appDefaultWindowX = 800;
int Engine::appDefaultWindowY = 600;

bool Engine::Rendering::appWireframeMode = true;

Math::Vec::iVec2 position;

class game final : public Engine::App
{
    protected:
    void Update() override
    {
        // Init
        auto* camera = Engine::App::GetCamera();
        auto* movement = Engine::App::GetMovement();

        // Update
        position = Engine::App::GetCamera()->GetPosition();

        // Input
        if (Engine::Input::IsKeyPressed(Engine::Input::Key::W)) Engine::Rendering::appWireframeMode = !Engine::Rendering::appWireframeMode;

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