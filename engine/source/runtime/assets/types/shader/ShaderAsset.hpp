//
// Created by Akira Mujawar on 25/06/26.
//

#ifndef MEOWENGINE_SHADERASSET_HPP
#define MEOWENGINE_SHADERASSET_HPP

#include <string>

#include "IAsset.hpp"
#include "ShaderType.hpp"

namespace MeowEngine::Asset {
    struct ShaderAsset : IAsset {
        std::string VertexSource;
        std::string FragmentSource;

        void SetSource(ShaderType type, const std::string& source);
    };
}

#endif //MEOWENGINE_SHADERASSET_HPP