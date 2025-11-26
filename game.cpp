#include <Engine/Core.h>

const char* Engine::appWindowTitle = "X11";
int Engine::appDefaultWindowX = 800;
int Engine::appDefaultWindowY = 600;

bool Engine::Rendering::appWireframeMode = true;

Engine::App* Engine::CreateApp()
{
    HELLOENGINE();
    return new Engine::App();
}