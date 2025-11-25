cmake_minimum_required(VERSION 3.10)
project(GameEngineX11)

# Set C++ Standard (C++17 is good for modern engines)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the X11 package on the system
find_package(X11 REQUIRED)

# Define the source files
set(SOURCES
        game.cpp
        Engine/Src/Rendering/Window.cpp
        Engine/Src/Rendering/Renderer.cpp
        Engine/Src/App/App.cpp
)

# Create the executable named "GameEngineX11"
add_executable(GameEngineX11 ${SOURCES})

# Configure Include Directories
# 1. ${CMAKE_CURRENT_SOURCE_DIR}: Allows game.cpp to find "Engine/Include/..."
# 2. .../Engine/Include: Allows Window.cpp to find "Rendering/Window.h"
# 3. ${X11_INCLUDE_DIR}: Where X11 headers live
target_include_directories(GameEngineX11 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Include
        ${X11_INCLUDE_DIR}
)

# Link the X11 library
target_link_libraries(GameEngineX11 ${X11_LIBRARIES})