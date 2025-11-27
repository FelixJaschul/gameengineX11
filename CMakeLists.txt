cmake_minimum_required(VERSION 3.10)
project(GameEngineX11)

# Set C++ Standard (C++17 is good for modern engines)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build the Engine as a reusable library from the Engine/ directory
add_subdirectory(Engine)

# App/executable that uses the Engine library
add_executable(GameEngineX11
        game.cpp
)

# Link the app against the Engine library. The Engine target exposes its
# public include directories and dependencies (like X11) transitively.
target_link_libraries(GameEngineX11 PRIVATE Engine)