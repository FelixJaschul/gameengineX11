#pragma once

#include "Engine/App/App.h"

extern Engine::App* Engine::CreateApp();

int main(int argc, char** argv)
{
    auto app = Engine::CreateApp();
    app->Run();
    delete app;
}