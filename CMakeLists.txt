cmake_minimum_required(VERSION 3.10)
project(GameEngineX11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(Engine)


add_executable(GameEngineX11
        main.cpp
)

# Link the app against the Engine library. The Engine target exposes its
# public include directories and dependencies (like X11) transitively.
target_link_libraries(GameEngineX11 PRIVATE Engine)