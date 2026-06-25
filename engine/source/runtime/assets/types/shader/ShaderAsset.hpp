//
// Created by Akira Mujawar on 25/06/26.
//

#ifndef MEOWENGINE_SHADERASSET_HPP
#define MEOWENGINE_SHADERASSET_HPP

#include <string>

#include "IAsset.hpp"

namespace MeowEngine::Asset{
    struct ShaderAsset : IAsset {
        std::string VertexSource;
        std::string FragmentSource;
    };
}

#endif //MEOWENGINE_SHADERASSET_HPP