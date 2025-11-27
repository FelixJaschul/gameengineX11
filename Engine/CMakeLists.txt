cmake_minimum_required(VERSION 3.10)

# Build the Engine as a reusable library
project(Engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies required by the Engine public headers/implementation
find_package(X11 REQUIRED)

set(ENGINE_SOURCES
        Src/Rendering/Window.cpp
        Src/Rendering/Renderer.cpp
        Src/Rendering/Camera.cpp
        Src/Math/Math.cpp
        Src/Math/Mat.cpp
        Src/Math/Vec.cpp
        Src/App/App.cpp
)

add_library(Engine STATIC ${ENGINE_SOURCES})

# Public headers live under Engine/Include and are included internally as
# e.g. "Rendering/Window.h". The app also includes "Engine/Core.h" from the
# repository root, so we expose the parent directory as a PUBLIC include dir.
target_include_directories(Engine
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Include
            ${CMAKE_CURRENT_SOURCE_DIR}/..
            ${X11_INCLUDE_DIR}
)

# Link to X11 so consumers don't have to remember to do it.
# Use PUBLIC to propagate the requirement to executables linking Engine.
target_link_libraries(Engine PUBLIC ${X11_LIBRARIES})