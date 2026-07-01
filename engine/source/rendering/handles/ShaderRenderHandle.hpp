//
// Created by Akira Mujawar on 19/05/26.
//

#ifndef MEOWENGINE_SHADERRENDERHANDLE_HPP
#define MEOWENGINE_SHADERRENDERHANDLE_HPP

// combo of 2 asset handles
// .frag & .vert
#include <IRenderHandle.hpp>

namespace MeowEngine::Rendering {
    struct ShaderRenderHandle : IRenderHandle {
        ShaderRenderHandle() = default;
        ShaderRenderHandle(const Asset::AssetHandle& handle) {
            AssetHandle = handle;
        }

        ~ShaderRenderHandle() override = default;

        bool operator==(const ShaderRenderHandle& handle) const {
            return AssetHandle == handle.AssetHandle;
        }

        bool operator!=(const ShaderRenderHandle& handle) const {
            return !(*this == handle);
        }

        bool IsValid() const override { return AssetHandle.GetIsValid(); };

        Asset::AssetHandle AssetHandle;
    };
}

namespace std {
    template<>
    struct hash<MeowEngine::Rendering::ShaderRenderHandle> {
        std::size_t operator()(const MeowEngine::Rendering::ShaderRenderHandle& handle) const noexcept {
            return std::hash<uint64_t>()(handle.AssetHandle.GetUUID());
        }
    };
}

#endif //MEOWENGINE_SHADERRENDERHANDLE_HPP