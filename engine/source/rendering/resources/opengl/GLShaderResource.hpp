//
// Created by Akira Mujawar on 20/05/26.
//

#ifndef MEOWENGINE_GLSHADERRESOURCE_HPP
#define MEOWENGINE_GLSHADERRESOURCE_HPP

#include <cstdint>
#include <AssetHandle.hpp>

namespace MeowEngine::Rendering {
    struct GLShaderResource {
        GLShaderResource(Asset::AssetHandle handle);

        [[nodiscard]] std::uint32_t GetID() const { return ID; };

    private:
        std::uint32_t Compile(const std::uint32_t& shaderType, const std::string& shaderSource);

    private:
        std::uint32_t ID;
    };
}

#endif //MEOWENGINE_GLSHADERRESOURCE_HPP