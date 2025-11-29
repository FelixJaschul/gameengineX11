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
        Src/Input/Input.cpp
        Src/Input/Movement.cpp
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

# Platform guidance for X11/WSL/XQuartz during configuration
if(APPLE)
    message(STATUS "[Engine] macOS detected. Install XQuartz (https://www.xquartz.org/), log out/in, start XQuartz, and ensure DISPLAY is set (e.g., export DISPLAY=:0).")
elseif(WIN32)
    message(STATUS "[Engine] Windows detected. Native Windows builds are not supported with X11. Run this inside WSL. On Windows 11, WSLg works out of the box; otherwise use an X server (e.g., VcXsrv/X410) and set DISPLAY accordingly.")
else()
    message(STATUS "[Engine] Ensure an X server is running and DISPLAY is set. If you're on Wayland, install/enable XWayland. If using WSL, prefer WSLg or run an X server on Windows and export DISPLAY.")
endif()