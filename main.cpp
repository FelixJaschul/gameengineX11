#include <Engine/Core.h>

const char* Engine::appWindowTitle = "X11";
int Engine::appDefaultWindowX = 800;
int Engine::appDefaultWindowY = 600;

bool Engine::Rendering::appWireframeMode = true;

class game final : public Engine::App
{
    protected:
    void Update() override
    {
        if (Engine::Input::IsKeyPressed(Engine::Input::Key::Escape)) Quit();

        if (Engine::Input::IsKeyPressed(Engine::Input::Key::W))
            Engine::Rendering::appWireframeMode = !Engine::Rendering::appWireframeMode;
    }

    void Render() override
    {
        auto* renderer = Engine::App::GetRenderer();
        renderer->Clear();

        renderer->DrawTriangle(400, 100, 300, 400, 500, 400, 0xFF0000);
        renderer->DrawRect(250, 100, 100, 100, 0x00FF00);

        renderer->Present();
    }
};

Engine::App* Engine::CreateApp()
{
    HELLOENGINE();
    return new game();
}