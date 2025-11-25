#include "Engine/Include/App/App.h"
#include <iostream>
#include <memory>

int main() {
    // Heap allocation is usually preferred for the App instance
    // to prevent stack overflow if the class gets huge.
    auto app = std::make_unique<Engine::App>();

    app->Run();

    return 0;
}