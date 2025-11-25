#pragma once

#include <../EnginePch.h>

namespace Engine
{
    template<typename T>
    struct AssetLoader
    {
        static std::shared_ptr<T> Load(const std::string& name);
    };
}