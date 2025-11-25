#include "Engine/Include/Rendering/Window.h"
#include "Engine/Include/Rendering/Renderer.h" // Include the new Renderer
#include <iostream>
#include <memory>
#include <unistd.h> // For usleep/sleep just to cap FPS slightly in this basic loop

int main() {
    std::cout << "Starting Game Engine..." << std::endl;

    auto window = std::make_unique<Engine::Rendering::Window>();
    auto renderer = std::make_unique<Engine::Rendering::Renderer>();

    if (!window->Initialize(800, 600, "GameEngine X11")) {
        return -1;
    }

    if (!renderer->Initialize(window.get())) {
        return -1;
    }

    bool running = true;
    while (running) {
        // --- Input ---
        running = window->PollEvents();

        // --- Render ---
        renderer->Clear();

        // Draw a Red Box (0xFF0000)
        renderer->SetColor(0xFF0000);
        renderer->FillRect(100, 100, 50, 50);

        // Draw a White Line
        renderer->SetColor(0xFFFFFF);
        renderer->DrawLine(100, 100, 200, 200);

        // Draw a Green Hollow Rect
        renderer->SetColor(0x00FF00);
        renderer->DrawRect(300, 300, 100, 50);

        renderer->Present();

        // Simple sleep to prevent 100% CPU usage in this basic loop
        usleep(16000); // ~60 FPS
    }

    return 0;
}