//
// Created by Akira Mujawar on 25/06/26.
//

#ifndef MEOWENGINE_SHADERSERIALIZATION_HPP
#define MEOWENGINE_SHADERSERIALIZATION_HPP

#include <string>
#include <vector>

#include "Public/Core/Forward.hpp"
// #include "Public/IO/Forward.hpp"

#include "ShaderType.hpp"

namespace MeowEngine::Asset {
    class ShaderSerialization {
    public:
        static bool Serialize(const Path& path, const std::string& data, ShaderType type);
    };
}

#endif //MEOWENGINE_SHADERSERIALIZATION_HPP