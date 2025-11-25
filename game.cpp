#include "Engine/Include/App/EntryPoint.h"
#include <iostream>
#include <memory>

const char* Engine::appWindowTitle = "X11";
int Engine::appDefaultWindowX = 800;
int Engine::appDefaultWindowY = 600;

Engine::App* Engine::CreateApp()
{
    return new Engine::App();
}