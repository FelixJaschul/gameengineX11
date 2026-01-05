#pragma once

#include <App/App.h>

int main()
{
    auto app = Engine::CreateApp();
    app->Run();
    delete app;
}