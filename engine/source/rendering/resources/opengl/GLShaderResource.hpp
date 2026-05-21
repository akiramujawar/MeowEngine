//
// Created by Akira Mujawar on 20/05/26.
//

#ifndef MEOWENGINE_GLSHADERRESOURCE_HPP
#define MEOWENGINE_GLSHADERRESOURCE_HPP

#include <cstdint>
#include <AssetHandle.hpp>

namespace MeowEngine::Rendering {
    struct GLShaderResource {
        GLShaderResource(Asset::AssetHandle vertex, Asset::AssetHandle fragment) {

        }

        std::uint32_t ID;
    };
}

#endif //MEOWENGINE_GLSHADERRESOURCE_HPP