//
// Created by Akira Mujawar on 25/06/26.
//

#ifndef MEOWENGINE_SHADERBUILDER_HPP
#define MEOWENGINE_SHADERBUILDER_HPP

#include "Public/Core/Forward.hpp"

namespace MeowEngine::Asset {
    class ShaderBuilder {
    public:
        static void CreateShaderAssets();

    private:
        static void Create(const Path& rawPath, const Path& cachePath);
    };
}

#endif //MEOWENGINE_SHADERBUILDER_HPP